#include "S84.CTCode.Transpiler.CSharpTranspiler.ctcode.hpp"

namespace s84 {
namespace ctcode {
namespace transpiler {
namespace csharptranspiler {
namespace ctcode {

CSharpTranspiler::CSharpTranspiler()
{
    this->system = NULL;
    this->c_t_code_file = NULL;
    this->base_name = "";
    this->logger = NULL;
    this->string_helper = NULL;
    /*this->imports = NO_DEFAULT;*/
    this->current_interface = "";
    /*this->interface_definitions = NO_DEFAULT;*/
    this->current_class = "";
    /*this->class_definitions = NO_DEFAULT;*/
    /*this->class_members = NO_DEFAULT;*/
    /*this->class_init = NO_DEFAULT;*/
    /*this->class_functions = NO_DEFAULT;*/
}

void CSharpTranspiler::Initialize()
{
    this->string_helper = std::shared_ptr<s84::ctcode::transpiler::stringhelper::ctcode::StringHelper>(new s84::ctcode::transpiler::stringhelper::ctcode::StringHelper());
}

void CSharpTranspiler::SetSystem(OmniPointer<s84::ctcode::system::ctcode::System> system)
{
    this->system = system;
}

void CSharpTranspiler::SetCTCodeFile(OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file)
{
    this->c_t_code_file = c_t_code_file;
}

void CSharpTranspiler::SetBaseName(std::string base_name)
{
    this->base_name = base_name;
}

void CSharpTranspiler::SetLogger(OmniPointer<s84::ctcode::system::ctcode::OutputStream> logger)
{
    this->logger = logger;
}

int CSharpTranspiler::GetBaseIndentation()
{
    return 1;
}

bool CSharpTranspiler::IsReserved(std::string name)
{
    return false||this->string_helper->BeginsWith(std::string("ReservedPrefix"),name)||this->string_helper->BeginsWith(std::string("reserved_prefix_"),name)||name==std::string("GetType")||name==std::string("boolean")||name==std::string("float")||name==std::string("decimal");
}

std::string CSharpTranspiler::GetCallName(std::string name)
{
    std::string value = this->string_helper->SnakeCaseToCamelCase(name);
    if (this->IsReserved(value))
    {
        return Concat(std::string("ReservedPrefix"),value);
    }
    return value;
}

std::string CSharpTranspiler::GetVariableName(std::string name)
{
    std::string value = this->string_helper->CamelCaseToSnakeCase(name);
    if (value==std::string("myself"))
    {
        return std::string("this");
    }
    if (this->IsReserved(value))
    {
        return Concat(std::string("reserved_prefix_"),value);
    }
    return value;
}

std::string CSharpTranspiler::GetVariableChain(std::vector<std::string> name_parts)
{
    std::string delimiter = std::string(".");
    std::string first_name = Element(name_parts,0);
    std::string result = this->GetVariableName(first_name);
    int name_parts_index = 1;
    while (name_parts_index<Size(name_parts))
    {
        std::string name = Element(name_parts,name_parts_index);
        result = Concat(Concat(result,delimiter),this->GetVariableName(name));
        name_parts_index = name_parts_index+1;
    }
    return result;
}

std::string CSharpTranspiler::ConvertCall(std::vector<std::string> name_chain, std::vector<std::string> parameters)
{
    std::string result = Element(name_chain,0);
    int name_chain_index = 1;
    while (name_chain_index<Size(name_chain))
    {
        std::string name_part = Element(name_chain,name_chain_index);
        result = Concat(Concat(result,std::string("?.")),name_part);
        name_chain_index = name_chain_index+1;
    }
    result = Concat(result,std::string("("));
    if (Size(parameters)>0)
    {
        result = Concat(result,Element(parameters,0));
        int parameters_index = 1;
        while (parameters_index<Size(parameters))
        {
            std::string parameter = Element(parameters,parameters_index);
            result = Concat(result,std::string(","));
            result = Concat(result,parameter);
            parameters_index = parameters_index+1;
        }
    }
    result = Concat(result,std::string(")"));
    return result;
}

std::string CSharpTranspiler::ConvertAllocate(std::string type)
{
    return Concat(Concat(std::string("new "),type),std::string("()"));
}

std::string CSharpTranspiler::ConvertByte(std::string high, std::string low)
{
    return Concat(Concat(std::string("0x"),high),low);
}

std::string CSharpTranspiler::ConvertDecimal(std::string decimal)
{
    return decimal;
}

std::string CSharpTranspiler::ConvertNumber(std::string number)
{
    return number;
}

std::string CSharpTranspiler::ConvertBoolean(std::string boolean)
{
    if (boolean==std::string("true"))
    {
        return std::string("true");
    }
    if (boolean==std::string("false"))
    {
        return std::string("false");
    }
    return std::string("");
}

std::string CSharpTranspiler::ConvertVariable(std::string variable)
{
    std::string result = std::string("");
    int variable_index = 0;
    while (variable_index<Length(variable))
    {
        std::string character = At(variable,variable_index);
        if (character==std::string("."))
        {
            result = Concat(result,std::string("?"));
        }
        result = Concat(result,character);
        variable_index = variable_index+1;
    }
    return result;
}

std::string CSharpTranspiler::ConvertString(std::string literal)
{
    return Concat(Concat(std::string("\""),literal),std::string("\""));
}

std::string CSharpTranspiler::UnaryOperator(std::string op, std::string r_value)
{
    if (op==std::string("!"))
    {
        return Concat(std::string("!"),r_value);
    }
    return r_value;
}

std::string CSharpTranspiler::BinaryOperator(std::string op, std::string r_value_l, std::string r_value_r)
{
    if (op==std::string("+"))
    {
        return Concat(Concat(r_value_l,std::string("+")),r_value_r);
    }
    if (op==std::string("-"))
    {
        return Concat(Concat(r_value_l,std::string("-")),r_value_r);
    }
    if (op==std::string("<="))
    {
        return Concat(Concat(r_value_l,std::string("<=")),r_value_r);
    }
    if (op==std::string(">="))
    {
        return Concat(Concat(r_value_l,std::string(">=")),r_value_r);
    }
    if (op==std::string("=="))
    {
        return Concat(Concat(r_value_l,std::string("==")),r_value_r);
    }
    if (op==std::string("!="))
    {
        return Concat(Concat(r_value_l,std::string("!=")),r_value_r);
    }
    if (op==std::string("<"))
    {
        return Concat(Concat(r_value_l,std::string("<")),r_value_r);
    }
    if (op==std::string(">"))
    {
        return Concat(Concat(r_value_l,std::string(">")),r_value_r);
    }
    if (op==std::string("||"))
    {
        return Concat(Concat(Concat(Concat(std::string("AsBoolean("),r_value_l),std::string(")||AsBoolean(")),r_value_r),std::string(")"));
    }
    if (op==std::string("&&"))
    {
        return Concat(Concat(Concat(Concat(std::string("AsBoolean("),r_value_l),std::string(")&&AsBoolean(")),r_value_r),std::string(")"));
    }
    return std::string("");
}

std::string CSharpTranspiler::GetTypeName(std::string name)
{
    return this->string_helper->SnakeCaseToCamelCase(name);
}

std::string CSharpTranspiler::GetDimensionalType(std::string singleton_type, int dimensions)
{
    std::string result = singleton_type;
    while (dimensions>0)
    {
        result = Concat(Concat(std::string("List<"),result),std::string(">?"));
        dimensions = dimensions-1;
    }
    return result;
}

std::string CSharpTranspiler::GetMapType(std::string singleton_type)
{
    return Concat(Concat(std::string("Dictionary<string,"),singleton_type),std::string(">?"));
}

std::string CSharpTranspiler::GetPrimativeType(std::string c_t_type)
{
    if (c_t_type==std::string("int"))
    {
        return std::string("int?");
    }
    if (c_t_type==std::string("string"))
    {
        return std::string("string?");
    }
    if (c_t_type==std::string("bool"))
    {
        return std::string("bool?");
    }
    if (c_t_type==std::string("float"))
    {
        return std::string("float?");
    }
    if (c_t_type==std::string("void"))
    {
        return std::string("void");
    }
    return std::string("");
}

std::string CSharpTranspiler::GetDefinedType(std::string c_t_type)
{
    return Concat(c_t_type,std::string("?"));
}

std::string CSharpTranspiler::GetQualifiedTypeName(std::vector<std::string> name_parts)
{
    std::string delimiter = std::string(".");
    int name_parts_index = Size(name_parts)-1;
    std::string type_part = Element(name_parts,name_parts_index);
    std::string result = this->GetTypeName(type_part);
    if (name_parts_index>0)
    {
        while (name_parts_index>0)
        {
            name_parts_index = name_parts_index-1;
            result = Concat(delimiter,result);
            std::string name_part = Element(name_parts,name_parts_index);
            result = Concat(name_part,result);
        }
    }
    return result;
}

void CSharpTranspiler::BeginProcessingCTCodeFile()
{
    ClearList(this->imports);
    this->current_interface = std::string("");
    ClearList(this->interface_definitions);
    this->current_class = std::string("");
    ClearList(this->class_definitions);
    ClearList(this->class_members);
    ClearList(this->class_init);
    ClearList(this->class_functions);
}

void CSharpTranspiler::FinishProcessingCTCodeFile()
{
    std::string destination_file_name = Concat(this->base_name,std::string(".cs"));
    OmniPointer<s84::ctcode::system::ctcode::OutputStream> destination_file = this->system->OpenFileWriter(destination_file_name);
    destination_file->WriteLine(Concat(Concat(std::string("namespace "),this->base_name),std::string(";")));
    destination_file->WriteLine(std::string(""));
    this->string_helper->WriteLines(destination_file,this->interface_definitions);
    this->string_helper->WriteLines(destination_file,this->class_definitions);
}

void CSharpTranspiler::ProcessExdef(std::string exdef)
{
    Append(this->imports,Concat(Concat(std::string("using "),exdef),std::string(";")));
}

void CSharpTranspiler::ProcessUnmanagedType(std::string unmanaged_type)
{
}

void CSharpTranspiler::BeginProcessingInterface(std::string interface_name)
{
    this->current_interface = interface_name;
    Append(this->interface_definitions,Concat(std::string("public interface "),interface_name));
    Append(this->interface_definitions,std::string("{"));
}

void CSharpTranspiler::ProcessInterfaceFunctionDeclaration(std::string return_type, std::string function_name, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    Append(this->interface_definitions,Concat(Concat(Concat(Concat(Concat(this->string_helper->Indentation(1),return_type),std::string(" ")),function_name),this->MakeParametersString(this->current_interface,parameters)),std::string(";")));
}

void CSharpTranspiler::FinishProcessingInterface(std::string interface_name)
{
    Append(this->interface_definitions,std::string("}"));
    Append(this->interface_definitions,std::string(""));
    this->current_interface = std::string("");
}

void CSharpTranspiler::BeginProcessingClass(std::string class_name, std::string implementing)
{
    this->current_class = class_name;
    if (implementing==std::string(""))
    {
        Append(this->class_definitions,Concat(std::string("public class "),class_name));
    }
    else
    {
        Append(this->class_definitions,Concat(Concat(Concat(std::string("public class "),class_name),std::string(" : ")),implementing));
    }
    Append(this->class_definitions,std::string("{"));
    ClearList(this->class_members);
    ClearList(this->class_init);
    ClearList(this->class_functions);
    Append(this->class_init,Concat(Concat(Concat(this->string_helper->Indentation(1),std::string("public ")),class_name),std::string("()")));
    Append(this->class_init,Concat(this->string_helper->Indentation(1),std::string("{")));
}

void CSharpTranspiler::BeginProcessingClassFunctionDefinition(std::string return_type, std::string function_name, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    Append(this->class_functions,Concat(Concat(Concat(Concat(Concat(this->string_helper->Indentation(1),std::string("public ")),return_type),std::string(" ")),function_name),this->MakeParametersString(this->current_class,parameters)));
}

void CSharpTranspiler::BeginProcessCodeBlock(int indent)
{
    Append(this->class_functions,Concat(this->string_helper->Indentation(indent),std::string("{")));
}

void CSharpTranspiler::FinishProcessCodeBlock(int indent)
{
    Append(this->class_functions,Concat(this->string_helper->Indentation(indent),std::string("}")));
}

void CSharpTranspiler::BeginProcessConditional(int indent, std::string r_value)
{
    Append(this->class_functions,Concat(Concat(Concat(this->string_helper->Indentation(indent),std::string("if (AsBoolean(")),r_value),std::string("))")));
}

void CSharpTranspiler::ProcessElse(int indent)
{
    Append(this->class_functions,Concat(this->string_helper->Indentation(indent),std::string("else")));
}

void CSharpTranspiler::FinishProcessConditional(int indent, std::string r_value)
{
}

void CSharpTranspiler::BeginProcessLoop(int indent, std::string r_value)
{
    Append(this->class_functions,Concat(Concat(Concat(this->string_helper->Indentation(indent),std::string("while (AsBoolean(")),r_value),std::string("))")));
}

void CSharpTranspiler::FinishProcessLoop(int indent, std::string r_value)
{
}

void CSharpTranspiler::ProcessRtn(int indent, std::string r_value)
{
    Append(this->class_functions,Concat(Concat(Concat(this->string_helper->Indentation(indent),std::string("return ")),r_value),std::string(";")));
}

void CSharpTranspiler::ProcessDeclaration(int indent, std::string type, std::string l_value, std::string r_value)
{
    if (r_value==std::string(""))
    {
        r_value = this->GetDefault(type);
    }
    Append(this->class_functions,Concat(Concat(Concat(Concat(Concat(Concat(this->string_helper->Indentation(indent),type),std::string(" ")),l_value),std::string(" = ")),r_value),std::string(";")));
}

void CSharpTranspiler::ProcessAssignment(int indent, std::string l_value, std::string r_value)
{
    Append(this->class_functions,Concat(Concat(Concat(Concat(this->string_helper->Indentation(indent),l_value),std::string(" = ")),r_value),std::string(";")));
}

void CSharpTranspiler::ProcessCall(int indent, std::string call)
{
    Append(this->class_functions,Concat(Concat(this->string_helper->Indentation(indent),call),std::string(";")));
}

void CSharpTranspiler::FinishProcessingClassFunctionDefinition(std::string return_type, std::string function_name, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    Append(this->class_functions,std::string(""));
}

void CSharpTranspiler::ProcessClassMemberDeclaration(std::string member_type, std::string member_name)
{
    Append(this->class_init,Concat(Concat(Concat(Concat(Concat(this->string_helper->Indentation(2),std::string("this.")),member_name),std::string(" = ")),this->GetDefault(member_type)),std::string(";")));
    Append(this->class_members,Concat(Concat(Concat(Concat(Concat(this->string_helper->Indentation(1),std::string("private ")),member_type),std::string(" ")),member_name),std::string(";")));
}

void CSharpTranspiler::FinishProcessingClass(std::string class_name, std::string implementing)
{
    if (Size(this->class_members)>0)
    {
        int class_members_index = 0;
        while (class_members_index<Size(this->class_members))
        {
            std::string line = Element(this->class_members,class_members_index);
            Append(this->class_definitions,line);
            class_members_index = class_members_index+1;
        }
        Append(this->class_definitions,std::string(""));
    }
    Append(this->class_init,Concat(this->string_helper->Indentation(1),std::string("}")));
    int class_init_index = 0;
    while (class_init_index<Size(this->class_init))
    {
        std::string line = Element(this->class_init,class_init_index);
        Append(this->class_definitions,line);
        class_init_index = class_init_index+1;
    }
    Append(this->class_definitions,std::string(""));
    int class_functions_index = 0;
    while (class_functions_index<Size(this->class_functions))
    {
        std::string line = Element(this->class_functions,class_functions_index);
        Append(this->class_definitions,line);
        class_functions_index = class_functions_index+1;
    }
    this->WriteCommonFunctions();
    Append(this->class_definitions,std::string("}"));
    this->current_class = std::string("");
}

void CSharpTranspiler::WriteCommonFunctions()
{
    Append(this->class_definitions,Concat(this->string_helper->Indentation(1),std::string("private static void ClearList<T>(List<T>? input) { input?.Clear(); }")));
    Append(this->class_definitions,Concat(this->string_helper->Indentation(1),std::string("private static int? Size<T>(List<T>? input) { return input?.Count; }")));
    Append(this->class_definitions,Concat(this->string_helper->Indentation(1),std::string("private static T? Element<T>(List<T>? input, int? element) { return input != null ? input[element??0] : default; }")));
    Append(this->class_definitions,Concat(this->string_helper->Indentation(1),std::string("private static void Append<T>(List<T>? input, T element) { input?.Add(element); }")));
    Append(this->class_definitions,Concat(this->string_helper->Indentation(1),std::string("private static void ClearMap<T>(Dictionary<string, T>? input) { input?.Clear();  }")));
    Append(this->class_definitions,Concat(this->string_helper->Indentation(1),std::string("private static void SetKV<T>(Dictionary<string, T>? input, string? key, T element) { input?.Add(key??\"\", element); }")));
    Append(this->class_definitions,Concat(this->string_helper->Indentation(1),std::string("private static List<string?>? Keys<T>(Dictionary<string, T>? input) { return new List<string?>(input?.Keys?.ToList()??new List<string>()); }")));
    Append(this->class_definitions,Concat(this->string_helper->Indentation(1),std::string("private static bool? HasKV<T>(Dictionary<string, T>? input, string? key) { return input?.ContainsKey(key??\"\"); }")));
    Append(this->class_definitions,Concat(this->string_helper->Indentation(1),std::string("private static T? GetKV<T>(Dictionary<string, T>? input, string? key) { return input != null ? input[key??\"\"] : default; }")));
    Append(this->class_definitions,Concat(this->string_helper->Indentation(1),std::string("private static int? Length(string? input) { return input?.Length;  }")));
    Append(this->class_definitions,Concat(this->string_helper->Indentation(1),std::string("private static string? At(string? input, int? index) { return input?.Length > index ? input?.Substring(index??0, 1) : \"\";  }")));
    Append(this->class_definitions,Concat(this->string_helper->Indentation(1),std::string("private static int? IntAt(string? input, int? index) { return input?.Length > index ? (input[index??0] + 255 % 255) : 0;  }")));
    Append(this->class_definitions,Concat(this->string_helper->Indentation(1),std::string("private static string? Concat(string? left, string? right) { return left + right; }")));
    Append(this->class_definitions,Concat(this->string_helper->Indentation(1),std::string("private static bool AsBoolean(bool value) { return value; }")));
    Append(this->class_definitions,Concat(this->string_helper->Indentation(1),std::string("private static bool AsBoolean<T>(T? value) { return value != null && !value.Equals(false); }")));
}

std::string CSharpTranspiler::StripLast(std::string input)
{
    std::string result = std::string("");
    int index = Length(input)-1;
    while (index>0)
    {
        index = index-1;
        result = Concat(At(input,index),result);
    }
    return result;
}

std::string CSharpTranspiler::GetDefault(std::string csharp_type)
{
    if (csharp_type==std::string("int?"))
    {
        return std::string("0");
    }
    if (csharp_type==std::string("string?"))
    {
        return std::string("\"\"");
    }
    if (csharp_type==std::string("bool?"))
    {
        return std::string("false");
    }
    if (csharp_type==std::string("float?"))
    {
        return std::string("0.0");
    }
    if (csharp_type==std::string("void"))
    {
        return std::string("void");
    }
    if (this->string_helper->BeginsWith(std::string("Dictionary<string,"),csharp_type))
    {
        return Concat(Concat(std::string("new "),this->StripLast(csharp_type)),std::string("()"));
    }
    if (this->string_helper->BeginsWith(std::string("List<"),csharp_type))
    {
        return Concat(Concat(std::string("new "),this->StripLast(csharp_type)),std::string("()"));
    }
    return std::string("null");
}

std::string CSharpTranspiler::MakeParametersString(std::string self_type, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    std::string result = std::string("(");
    int parameters_index = 0;
    while (parameters_index<Size(parameters))
    {
        OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration> parameter = Element(parameters,parameters_index);
        if (parameters_index!=0)
        {
            result = Concat(result,std::string(","));
        }
        result = Concat(Concat(Concat(result,parameter->GetType()),std::string(" ")),parameter->GetName());
        parameters_index = parameters_index+1;
    }
    result = Concat(result,std::string(")"));
    return result;
}


};
};
};
};
};
