#include "S84.CTCode.Transpiler.Java11Transpiler.ctcode.hpp"

namespace s84 {
namespace ctcode {
namespace transpiler {
namespace java11transpiler {
namespace ctcode {

Java11Transpiler::Java11Transpiler()
{
    this->system = NULL;
    this->c_t_code_file = NULL;
    this->base_name = "";
    this->logger = NULL;
    this->string_helper = NULL;
    /*this->imports = NO_DEFAULT;*/
    this->current_interface = "";
    /*this->interface_definition = NO_DEFAULT;*/
    this->current_class = "";
    /*this->class_definition = NO_DEFAULT;*/
    /*this->class_init = NO_DEFAULT;*/
    /*this->class_members = NO_DEFAULT;*/
}

void Java11Transpiler::Initialize()
{
    this->string_helper = std::shared_ptr<s84::ctcode::transpiler::stringhelper::ctcode::StringHelper>(new s84::ctcode::transpiler::stringhelper::ctcode::StringHelper());
}

void Java11Transpiler::SetSystem(OmniPointer<s84::ctcode::system::ctcode::System> system)
{
    this->system = system;
}

void Java11Transpiler::SetCTCodeFile(OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file)
{
    this->c_t_code_file = c_t_code_file;
}

void Java11Transpiler::SetBaseName(std::string base_name)
{
    this->base_name = base_name;
}

void Java11Transpiler::SetLogger(OmniPointer<s84::ctcode::system::ctcode::OutputStream> logger)
{
    this->logger = logger;
}

int Java11Transpiler::GetBaseIndentation()
{
    return 1;
}

std::string Java11Transpiler::GetCallName(std::string name)
{
    return this->string_helper->SnakeCaseToCamelCase(name);
}

bool Java11Transpiler::IsReserved(std::string name)
{
    return false||this->string_helper->BeginsWith(std::string("reserved_prefix_"),name)||name==std::string("boolean")||name==std::string("char")||name==std::string("float");
}

std::string Java11Transpiler::GetVariableName(std::string name)
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

std::string Java11Transpiler::GetVariableChain(std::vector<std::string> name_parts)
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

std::string Java11Transpiler::ConvertCall(std::vector<std::string> name_chain, std::vector<std::string> parameters)
{
    std::string result = Element(name_chain,0);
    int name_chain_index = 1;
    while (name_chain_index<Size(name_chain))
    {
        std::string name_part = Element(name_chain,name_chain_index);
        result = Concat(Concat(result,std::string(".")),name_part);
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
            result = Concat(result,std::string(", "));
            result = Concat(result,parameter);
            parameters_index = parameters_index+1;
        }
    }
    result = Concat(result,std::string(")"));
    return result;
}

std::string Java11Transpiler::ConvertAllocate(std::string type)
{
    return Concat(Concat(std::string("new "),type),std::string("()"));
}

std::string Java11Transpiler::ConvertByte(std::string high, std::string low)
{
    return Concat(Concat(std::string("0x"),high),low);
}

std::string Java11Transpiler::ConvertDecimal(std::string decimal)
{
    return decimal;
}

std::string Java11Transpiler::ConvertNumber(std::string number)
{
    return number;
}

std::string Java11Transpiler::ConvertBoolean(std::string boolean)
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

std::string Java11Transpiler::ConvertVariable(std::string variable)
{
    return variable;
}

std::string Java11Transpiler::ConvertString(std::string literal)
{
    return Concat(Concat(std::string("\""),literal),std::string("\""));
}

std::string Java11Transpiler::UnaryOperator(std::string op, std::string r_value)
{
    if (op==std::string("!"))
    {
        return Concat(Concat(std::string("(! AsBoolean("),r_value),std::string("))"));
    }
    return r_value;
}

std::string Java11Transpiler::BinaryOperator(std::string op, std::string r_value_l, std::string r_value_r)
{
    if (op==std::string("+"))
    {
        return Concat(Concat(Concat(Concat(std::string("("),r_value_l),std::string("+")),r_value_r),std::string(")"));
    }
    if (op==std::string("-"))
    {
        return Concat(Concat(Concat(Concat(std::string("("),r_value_l),std::string("-")),r_value_r),std::string(")"));
    }
    if (op==std::string("<="))
    {
        return Concat(Concat(Concat(Concat(std::string("("),r_value_l),std::string("<=")),r_value_r),std::string(")"));
    }
    if (op==std::string(">="))
    {
        return Concat(Concat(Concat(Concat(std::string("("),r_value_l),std::string(">=")),r_value_r),std::string(")"));
    }
    if (op==std::string("=="))
    {
        return Concat(Concat(Concat(Concat(std::string("Equals("),r_value_l),std::string(",")),r_value_r),std::string(")"));
    }
    if (op==std::string("!="))
    {
        return Concat(Concat(Concat(Concat(std::string("!Equals("),r_value_l),std::string(",")),r_value_r),std::string(")"));
    }
    if (op==std::string("<"))
    {
        return Concat(Concat(Concat(Concat(std::string("("),r_value_l),std::string("<")),r_value_r),std::string(")"));
    }
    if (op==std::string(">"))
    {
        return Concat(Concat(Concat(Concat(std::string("("),r_value_l),std::string(">")),r_value_r),std::string(")"));
    }
    if (op==std::string("||"))
    {
        return Concat(Concat(Concat(Concat(std::string("(AsBoolean("),r_value_l),std::string(") || AsBoolean(")),r_value_r),std::string("))"));
    }
    if (op==std::string("&&"))
    {
        return Concat(Concat(Concat(Concat(std::string("(AsBoolean("),r_value_l),std::string(") && AsBoolean(")),r_value_r),std::string("))"));
    }
    return std::string("");
}

std::string Java11Transpiler::GetTypeName(std::string name)
{
    return this->string_helper->SnakeCaseToCamelCase(name);
}

std::string Java11Transpiler::GetDimensionalType(std::string singleton_type, int dimensions)
{
    std::string result = singleton_type;
    while (dimensions>0)
    {
        result = Concat(Concat(std::string("java.util.ArrayList<"),result),std::string(">"));
        dimensions = dimensions-1;
    }
    return result;
}

std::string Java11Transpiler::GetMapType(std::string singleton_type)
{
    return Concat(Concat(std::string("java.util.HashMap<java.lang.String, "),singleton_type),std::string(">"));
}

std::string Java11Transpiler::GetPrimativeType(std::string c_t_type)
{
    if (c_t_type==std::string("int"))
    {
        return std::string("int");
    }
    if (c_t_type==std::string("string"))
    {
        return std::string("java.lang.String");
    }
    if (c_t_type==std::string("bool"))
    {
        return std::string("boolean");
    }
    if (c_t_type==std::string("float"))
    {
        return std::string("float");
    }
    if (c_t_type==std::string("void"))
    {
        return std::string("void");
    }
    return std::string("");
}

std::string Java11Transpiler::GetDefinedType(std::string c_t_type)
{
    return c_t_type;
}

std::string Java11Transpiler::GetQualifiedTypeName(std::vector<std::string> name_parts)
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
            result = Concat(this->string_helper->ToLower(name_part),result);
        }
    }
    return result;
}

void Java11Transpiler::BeginProcessingCTCodeFile()
{
    ClearList(this->imports);
    this->current_interface = std::string("");
    ClearList(this->interface_definition);
    this->current_class = std::string("");
    ClearList(this->class_definition);
    ClearList(this->class_init);
    ClearList(this->class_members);
}

void Java11Transpiler::ProcessExdef(std::string exdef)
{
    Append(this->imports,Concat(Concat(std::string("import "),this->string_helper->ToLower(exdef)),std::string(".*;")));
}

void Java11Transpiler::ProcessUnmanagedType(std::string unmanaged_type)
{
}

void Java11Transpiler::BeginProcessingInterface(std::string interface_name)
{
    ClearList(this->interface_definition);
    this->current_interface = interface_name;
}

void Java11Transpiler::ProcessInterfaceFunctionDeclaration(std::string return_type, std::string function_name, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    Append(this->interface_definition,Concat(Concat(Concat(Concat(Concat(this->string_helper->Indentation(1),return_type),std::string(" ")),function_name),this->MakeParametersString(parameters)),std::string(";")));
}

void Java11Transpiler::FinishProcessingInterface(std::string interface_name)
{
    OmniPointer<s84::ctcode::system::ctcode::OutputStream> destination = this->system->OpenFileWriter(Concat(Concat(Concat(this->string_helper->DotToSlash(this->string_helper->ToLower(this->base_name)),std::string("/")),this->current_interface),std::string(".java")));
    destination->WriteLine(Concat(Concat(std::string("package "),this->string_helper->ToLower(this->base_name)),std::string(";")));
    destination->WriteLine(std::string(""));
    if (Size(this->imports)>0)
    {
        this->string_helper->WriteLines(destination,this->imports);
        destination->WriteLine(std::string(""));
    }
    destination->WriteLine(Concat(Concat(std::string("public interface "),interface_name),std::string(" {")));
    this->string_helper->WriteLines(destination,this->interface_definition);
    destination->WriteLine(std::string("}"));
    this->current_interface = std::string("");
}

void Java11Transpiler::BeginProcessingClass(std::string class_name, std::string implementing)
{
    ClearList(this->class_definition);
    ClearList(this->class_init);
    ClearList(this->class_members);
    this->current_class = class_name;
    Append(this->class_init,Concat(Concat(Concat(this->string_helper->Indentation(1),std::string("public ")),class_name),std::string("()")));
    Append(this->class_init,Concat(this->string_helper->Indentation(1),std::string("{")));
}

void Java11Transpiler::BeginProcessingClassFunctionDefinition(std::string return_type, std::string function_name, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    Append(this->class_definition,Concat(Concat(Concat(Concat(Concat(this->string_helper->Indentation(1),std::string("public ")),return_type),std::string(" ")),function_name),this->MakeParametersString(parameters)));
}

void Java11Transpiler::BeginProcessCodeBlock(int indent)
{
    Append(this->class_definition,Concat(this->string_helper->Indentation(indent),std::string("{")));
}

void Java11Transpiler::FinishProcessCodeBlock(int indent)
{
    Append(this->class_definition,Concat(this->string_helper->Indentation(indent),std::string("}")));
}

void Java11Transpiler::BeginProcessConditional(int indent, std::string r_value)
{
    Append(this->class_definition,Concat(Concat(Concat(this->string_helper->Indentation(indent),std::string("if (AsBoolean(")),r_value),std::string("))")));
}

void Java11Transpiler::ProcessElse(int indent)
{
    Append(this->class_definition,Concat(this->string_helper->Indentation(indent),std::string("else")));
}

void Java11Transpiler::FinishProcessConditional(int indent, std::string r_value)
{
}

void Java11Transpiler::BeginProcessLoop(int indent, std::string r_value)
{
    Append(this->class_definition,Concat(Concat(Concat(this->string_helper->Indentation(indent),std::string("while (AsBoolean(")),r_value),std::string("))")));
}

void Java11Transpiler::FinishProcessLoop(int indent, std::string r_value)
{
}

void Java11Transpiler::ProcessRtn(int indent, std::string r_value)
{
    Append(this->class_definition,Concat(Concat(Concat(this->string_helper->Indentation(indent),std::string("return ")),r_value),std::string(";")));
}

void Java11Transpiler::ProcessDeclaration(int indent, std::string type, std::string l_value, std::string r_value)
{
    if (r_value==std::string(""))
    {
        r_value = this->GetDefault(type);
    }
    Append(this->class_definition,Concat(Concat(Concat(Concat(Concat(Concat(this->string_helper->Indentation(indent),type),std::string(" ")),l_value),std::string(" = ")),r_value),std::string(";")));
}

void Java11Transpiler::ProcessAssignment(int indent, std::string l_value, std::string r_value)
{
    Append(this->class_definition,Concat(Concat(Concat(Concat(this->string_helper->Indentation(indent),l_value),std::string(" = ")),r_value),std::string(";")));
}

void Java11Transpiler::ProcessCall(int indent, std::string call)
{
    Append(this->class_definition,Concat(Concat(this->string_helper->Indentation(indent),call),std::string(";")));
}

void Java11Transpiler::FinishProcessingClassFunctionDefinition(std::string return_type, std::string function_name, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    Append(this->class_definition,std::string(""));
}

void Java11Transpiler::ProcessClassMemberDeclaration(std::string member_type, std::string member_name)
{
    Append(this->class_init,Concat(Concat(Concat(Concat(Concat(this->string_helper->Indentation(2),std::string("this.")),member_name),std::string(" = ")),this->GetDefault(member_type)),std::string(";")));
    Append(this->class_members,Concat(Concat(Concat(Concat(Concat(this->string_helper->Indentation(1),std::string("private ")),member_type),std::string(" ")),member_name),std::string(";")));
}

void Java11Transpiler::FinishProcessingClass(std::string class_name, std::string implementing)
{
    OmniPointer<s84::ctcode::system::ctcode::OutputStream> destination = this->system->OpenFileWriter(Concat(Concat(Concat(this->string_helper->DotToSlash(this->string_helper->ToLower(this->base_name)),std::string("/")),this->current_class),std::string(".java")));
    destination->WriteLine(Concat(Concat(std::string("package "),this->string_helper->ToLower(this->base_name)),std::string(";")));
    destination->WriteLine(std::string(""));
    if (Size(this->imports)>0)
    {
        this->string_helper->WriteLines(destination,this->imports);
        destination->WriteLine(std::string(""));
    }
    if (implementing==std::string(""))
    {
        destination->WriteLine(Concat(Concat(std::string("public class "),class_name),std::string(" {")));
    }
    else
    {
        destination->WriteLine(Concat(Concat(Concat(Concat(std::string("public class "),class_name),std::string(" implements ")),implementing),std::string(" {")));
    }
    this->string_helper->WriteLines(destination,this->class_init);
    destination->WriteLine(Concat(this->string_helper->Indentation(1),std::string("}")));
    destination->WriteLine(std::string(""));
    this->string_helper->WriteLines(destination,this->class_definition);
    if (Size(this->class_members)>0)
    {
        this->string_helper->WriteLines(destination,this->class_members);
        destination->WriteLine(std::string(""));
    }
    this->WriteCommonFunctions(destination);
    destination->WriteLine(std::string("}"));
    this->current_class = std::string("");
}

void Java11Transpiler::WriteCommonFunctions(OmniPointer<s84::ctcode::system::ctcode::OutputStream> destination_file)
{
    destination_file->WriteLine(Concat(this->string_helper->Indentation(1),std::string("private static <T> void ClearList(java.util.ArrayList<T> input) { input.clear(); }")));
    destination_file->WriteLine(Concat(this->string_helper->Indentation(1),std::string("private static <T> int Size(java.util.ArrayList<T> input) { return input.size(); }")));
    destination_file->WriteLine(Concat(this->string_helper->Indentation(1),std::string("private static <T> T Element(java.util.ArrayList<T> input, int element) { return input.get(element); }")));
    destination_file->WriteLine(Concat(this->string_helper->Indentation(1),std::string("private static <T> void Append(java.util.ArrayList<T> input, T element) { input.add(element); }")));
    destination_file->WriteLine(Concat(this->string_helper->Indentation(1),std::string("private static <T> void ClearMap(java.util.HashMap<java.lang.String, T> input) { input.clear(); }")));
    destination_file->WriteLine(Concat(this->string_helper->Indentation(1),std::string("private static <T> void SetKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key, T element) { input.put(key, element); }")));
    destination_file->WriteLine(Concat(this->string_helper->Indentation(1),std::string("private static <T> java.util.ArrayList<java.lang.String> Keys(java.util.HashMap<java.lang.String, T> input) { return new java.util.ArrayList<>(input.keySet()); }")));
    destination_file->WriteLine(Concat(this->string_helper->Indentation(1),std::string("private static <T> boolean HasKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key) { return input.containsKey(key); }")));
    destination_file->WriteLine(Concat(this->string_helper->Indentation(1),std::string("private static <T> T GetKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key) { return input.get(key); }")));
    destination_file->WriteLine(Concat(this->string_helper->Indentation(1),std::string("private static int Length(java.lang.String input) { return input.length(); }")));
    destination_file->WriteLine(Concat(this->string_helper->Indentation(1),std::string("private static java.lang.String At(java.lang.String input, int index) { try { return input.substring(index, index + 1);} catch(Exception e) { return \"\"; }}")));
    destination_file->WriteLine(Concat(this->string_helper->Indentation(1),std::string("private static int IntAt(java.lang.String input, int index) { return (int)input.charAt(index); }")));
    destination_file->WriteLine(Concat(this->string_helper->Indentation(1),std::string("private static java.lang.String Concat(java.lang.String left, java.lang.String right) { return left + right; }")));
    destination_file->WriteLine(Concat(this->string_helper->Indentation(1),std::string("private static <T extends java.lang.Object> boolean AsBoolean(T value) { return value != null; }")));
    destination_file->WriteLine(Concat(this->string_helper->Indentation(1),std::string("private static boolean AsBoolean(boolean value) { return value; }")));
    destination_file->WriteLine(Concat(this->string_helper->Indentation(1),std::string("private static boolean Equals(java.lang.String left, java.lang.String right) { return left.equals(right); }")));
    destination_file->WriteLine(Concat(this->string_helper->Indentation(1),std::string("private static boolean Equals(boolean left, boolean right) { return left == right; }")));
    destination_file->WriteLine(Concat(this->string_helper->Indentation(1),std::string("private static boolean Equals(int left, int right) { return left == right; }")));
    destination_file->WriteLine(Concat(this->string_helper->Indentation(1),std::string("private static boolean Equals(float left, float right) { return left == right; }")));
}

void Java11Transpiler::FinishProcessingCTCodeFile()
{
}

std::string Java11Transpiler::GetDefault(std::string java_type)
{
    if (java_type==std::string("int"))
    {
        return std::string("0");
    }
    if (java_type==std::string("java.lang.String"))
    {
        return std::string("\"\"");
    }
    if (java_type==std::string("boolean"))
    {
        return std::string("false");
    }
    if (java_type==std::string("float"))
    {
        return std::string("0.0");
    }
    if (java_type==std::string("void"))
    {
        return std::string("null");
    }
    if (this->string_helper->BeginsWith(std::string("java.util.HashMap<java.lang.String"),java_type))
    {
        return std::string("new java.util.HashMap<>()");
    }
    if (this->string_helper->BeginsWith(std::string("java.util.ArrayList<"),java_type))
    {
        return std::string("new java.util.ArrayList<>()");
    }
    return std::string("null");
}

std::string Java11Transpiler::MakeParametersString(std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    std::string result = std::string("(");
    int parameters_index = 0;
    while (parameters_index<Size(parameters))
    {
        OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration> parameter = Element(parameters,parameters_index);
        if (parameters_index!=0)
        {
            result = Concat(result,std::string(", "));
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
