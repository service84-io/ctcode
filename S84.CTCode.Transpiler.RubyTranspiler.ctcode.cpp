#include "S84.CTCode.Transpiler.RubyTranspiler.ctcode.hpp"

namespace s84 {
namespace ctcode {
namespace transpiler {
namespace rubytranspiler {
namespace ctcode {

RubyTranspiler::RubyTranspiler()
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
    /*this->class_init = NO_DEFAULT;*/
    /*this->class_functions = NO_DEFAULT;*/
}

void RubyTranspiler::Initialize()
{
    this->string_helper = std::shared_ptr<s84::ctcode::transpiler::stringhelper::ctcode::StringHelper>(new s84::ctcode::transpiler::stringhelper::ctcode::StringHelper());
}

void RubyTranspiler::SetSystem(OmniPointer<s84::ctcode::system::ctcode::System> system)
{
    this->system = system;
}

void RubyTranspiler::SetCTCodeFile(OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file)
{
    this->c_t_code_file = c_t_code_file;
}

void RubyTranspiler::SetBaseName(std::string base_name)
{
    this->base_name = base_name;
}

void RubyTranspiler::SetLogger(OmniPointer<s84::ctcode::system::ctcode::OutputStream> logger)
{
    this->logger = logger;
}

int RubyTranspiler::GetBaseIndentation()
{
    return 1;
}

std::string RubyTranspiler::GetCallName(std::string name)
{
    std::string value = this->string_helper->SnakeCaseToCamelCase(name);
    if (this->string_helper->IsReserved(value))
    {
        return Concat(std::string("ReservedPrefix"),value);
    }
    return value;
}

std::string RubyTranspiler::GetVariableName(std::string name)
{
    std::string value = this->string_helper->CamelCaseToSnakeCase(name);
    if (value==std::string("myself"))
    {
        return std::string("self");
    }
    if (value==std::string("nothing"))
    {
        return std::string("nil");
    }
    if (this->string_helper->IsReserved(value))
    {
        return Concat(std::string("reserved_prefix_"),value);
    }
    return value;
}

std::string RubyTranspiler::GetVariableChain(std::vector<std::string> name_parts)
{
    std::string delimiter = std::string(".");
    std::string first_name = Element(name_parts,0);
    std::string result = this->GetVariableName(first_name);
    int name_parts_index = 1;
    while (name_parts_index<Size(name_parts))
    {
        std::string name = Element(name_parts,name_parts_index);
        result = Concat(result,delimiter);
        if (result==std::string("self."))
        {
            result = std::string("@");
        }
        result = Concat(result,this->GetVariableName(name));
        name_parts_index = name_parts_index+1;
    }
    return result;
}

std::string RubyTranspiler::ConvertCall(std::vector<std::string> name_chain, std::vector<std::string> parameters)
{
    std::string result = Element(name_chain,0);
    int name_chain_index = 1;
    int last_name_chain_index = Size(name_chain)-1;
    while (name_chain_index<Size(name_chain))
    {
        std::string name_part = Element(name_chain,name_chain_index);
        result = Concat(result,std::string("."));
        if (name_chain_index!=last_name_chain_index)
        {
            if (result==std::string("self."))
            {
                result = std::string("@");
            }
        }
        result = Concat(result,name_part);
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

std::string RubyTranspiler::ConvertAllocate(std::string type)
{
    return Concat(type,std::string(".new()"));
}

std::string RubyTranspiler::ConvertByte(std::string high, std::string low)
{
    return Concat(Concat(std::string("0x"),high),low);
}

std::string RubyTranspiler::ConvertDecimal(std::string reserved_prefix_decimal)
{
    return reserved_prefix_decimal;
}

std::string RubyTranspiler::ConvertNumber(std::string number)
{
    return number;
}

std::string RubyTranspiler::ConvertBoolean(std::string reserved_prefix_boolean)
{
    if (reserved_prefix_boolean==std::string("true"))
    {
        return std::string("true");
    }
    if (reserved_prefix_boolean==std::string("false"))
    {
        return std::string("false");
    }
    return std::string("");
}

std::string RubyTranspiler::ConvertVariable(std::string variable)
{
    return variable;
}

std::string RubyTranspiler::ConvertString(std::string literal)
{
    return Concat(Concat(std::string("\""),literal),std::string("\""));
}

std::string RubyTranspiler::UnaryOperator(std::string op, std::string r_value)
{
    if (op==std::string("!"))
    {
        return Concat(std::string("! "),r_value);
    }
    return r_value;
}

std::string RubyTranspiler::BinaryOperator(std::string op, std::string r_value_l, std::string r_value_r)
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
        return Concat(Concat(r_value_l,std::string(" || ")),r_value_r);
    }
    if (op==std::string("&&"))
    {
        return Concat(Concat(r_value_l,std::string(" && ")),r_value_r);
    }
    return std::string("");
}

std::string RubyTranspiler::GetTypeName(std::string name)
{
    std::string value = this->string_helper->SnakeCaseToCamelCase(name);
    if (this->string_helper->IsReserved(value))
    {
        return Concat(std::string("ReservedPrefix"),value);
    }
    return value;
}

std::string RubyTranspiler::GetDimensionalType(std::string singleton_type, int dimensions)
{
    std::string result = singleton_type;
    while (dimensions>0)
    {
        result = Concat(Concat(std::string("list["),result),std::string("]"));
        dimensions = dimensions-1;
    }
    return result;
}

std::string RubyTranspiler::GetMapType(std::string singleton_type)
{
    return Concat(Concat(std::string("dict[str, "),singleton_type),std::string("]"));
}

std::string RubyTranspiler::GetPrimativeType(std::string c_t_type)
{
    if (c_t_type==std::string("int"))
    {
        return std::string("int");
    }
    if (c_t_type==std::string("string"))
    {
        return std::string("string");
    }
    if (c_t_type==std::string("bool"))
    {
        return std::string("bool");
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

std::string RubyTranspiler::GetDefinedType(std::string c_t_type)
{
    return c_t_type;
}

std::string RubyTranspiler::GetQualifiedTypeName(std::vector<std::string> name_parts)
{
    std::string delimiter = std::string("::");
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
            result = Concat(this->string_helper->ToUpper(name_part),result);
        }
        result = Concat(delimiter,result);
    }
    return result;
}

void RubyTranspiler::BeginProcessingCTCodeFile()
{
    ClearList(this->imports);
    this->current_interface = std::string("");
    ClearList(this->interface_definitions);
    this->current_class = std::string("");
    ClearList(this->class_definitions);
    ClearList(this->class_init);
    ClearList(this->class_functions);
}

void RubyTranspiler::ProcessExdef(std::string exdef)
{
    Append(this->imports,Concat(Concat(std::string("require '"),exdef),std::string("'")));
}

void RubyTranspiler::ProcessUnmanagedType(std::string unmanaged_type)
{
}

void RubyTranspiler::BeginProcessingInterface(std::string interface_name)
{
    this->current_interface = interface_name;
    Append(this->interface_definitions,Concat(std::string("class "),interface_name));
}

void RubyTranspiler::ProcessInterfaceFunctionDeclaration(std::string return_type, std::string function_name, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    Append(this->interface_definitions,Concat(Concat(Concat(Concat(this->string_helper->Indentation(1),std::string("def ")),function_name),this->MakeParametersString(parameters)),std::string("; end")));
}

void RubyTranspiler::FinishProcessingInterface(std::string interface_name)
{
    Append(this->interface_definitions,std::string("end"));
    Append(this->interface_definitions,std::string(""));
    this->current_interface = std::string("");
}

void RubyTranspiler::BeginProcessingClass(std::string class_name, std::string implementing)
{
    this->current_class = class_name;
    if (implementing==std::string(""))
    {
        Append(this->class_definitions,Concat(std::string("class "),class_name));
    }
    else
    {
        Append(this->class_definitions,Concat(Concat(Concat(std::string("class "),class_name),std::string(" < ")),implementing));
    }
    ClearList(this->class_init);
    ClearList(this->class_functions);
    Append(this->class_init,Concat(this->string_helper->Indentation(1),std::string("def initialize()")));
}

void RubyTranspiler::BeginProcessingClassFunctionDefinition(std::string return_type, std::string function_name, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    Append(this->class_functions,std::string(""));
    Append(this->class_functions,Concat(Concat(Concat(this->string_helper->Indentation(1),std::string("def ")),function_name),this->MakeParametersString(parameters)));
}

void RubyTranspiler::BeginProcessCodeBlock(int indent)
{
}

void RubyTranspiler::FinishProcessCodeBlock(int indent)
{
}

void RubyTranspiler::BeginProcessConditional(int indent, std::string r_value)
{
    Append(this->class_functions,Concat(Concat(Concat(this->string_helper->Indentation(indent),std::string("if (")),r_value),std::string(")")));
}

void RubyTranspiler::ProcessElse(int indent)
{
    Append(this->class_functions,Concat(this->string_helper->Indentation(indent),std::string("else")));
}

void RubyTranspiler::FinishProcessConditional(int indent, std::string r_value)
{
    Append(this->class_functions,Concat(this->string_helper->Indentation(indent),std::string("end")));
}

void RubyTranspiler::BeginProcessLoop(int indent, std::string r_value)
{
    Append(this->class_functions,Concat(Concat(Concat(this->string_helper->Indentation(indent),std::string("while (")),r_value),std::string(")")));
}

void RubyTranspiler::FinishProcessLoop(int indent, std::string r_value)
{
    Append(this->class_functions,Concat(this->string_helper->Indentation(indent),std::string("end")));
}

void RubyTranspiler::ProcessRtn(int indent, std::string r_value)
{
    Append(this->class_functions,Concat(Concat(this->string_helper->Indentation(indent),std::string("return ")),r_value));
}

void RubyTranspiler::ProcessDeclaration(int indent, std::string type, std::string l_value, std::string r_value)
{
    if (r_value==std::string(""))
    {
        r_value = this->GetDefault(type);
    }
    Append(this->class_functions,Concat(Concat(Concat(this->string_helper->Indentation(indent),l_value),std::string(" = ")),r_value));
}

void RubyTranspiler::ProcessAssignment(int indent, std::string l_value, std::string r_value)
{
    Append(this->class_functions,Concat(Concat(Concat(this->string_helper->Indentation(indent),l_value),std::string(" = ")),r_value));
}

void RubyTranspiler::ProcessCall(int indent, std::string call)
{
    Append(this->class_functions,Concat(this->string_helper->Indentation(indent),call));
}

void RubyTranspiler::FinishProcessingClassFunctionDefinition(std::string return_type, std::string function_name, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    Append(this->class_functions,Concat(this->string_helper->Indentation(1),std::string("end")));
}

void RubyTranspiler::ProcessClassMemberDeclaration(std::string member_type, std::string member_name)
{
    Append(this->class_init,Concat(Concat(Concat(Concat(this->string_helper->Indentation(2),std::string("@")),member_name),std::string(" = ")),this->GetDefault(member_type)));
}

void RubyTranspiler::FinishProcessingClass(std::string class_name, std::string implementing)
{
    Append(this->class_init,Concat(this->string_helper->Indentation(1),std::string("end")));
    int class_init_index = 0;
    while (class_init_index<Size(this->class_init))
    {
        std::string line = Element(this->class_init,class_init_index);
        Append(this->class_definitions,line);
        class_init_index = class_init_index+1;
    }
    int class_functions_index = 0;
    while (class_functions_index<Size(this->class_functions))
    {
        std::string line = Element(this->class_functions,class_functions_index);
        Append(this->class_definitions,line);
        class_functions_index = class_functions_index+1;
    }
    Append(this->class_definitions,std::string("end"));
    Append(this->class_definitions,std::string(""));
    this->current_class = std::string("");
}

void RubyTranspiler::WriteCommonFunctions(OmniPointer<s84::ctcode::system::ctcode::OutputStream> destination_file)
{
    destination_file->WriteLine(std::string("def ClearList(input); input.clear(); end"));
    destination_file->WriteLine(std::string("def Size(input); return input.length(); end"));
    destination_file->WriteLine(std::string("def Element(input, element); return input[element]; end"));
    destination_file->WriteLine(std::string("def Append(input, element); input.push(element); end"));
    destination_file->WriteLine(std::string("def ClearMap(input); input.clear(); end"));
    destination_file->WriteLine(std::string("def SetKV(input, key, element); input[key] = element; end"));
    destination_file->WriteLine(std::string("def Keys(input); return input.keys(); end"));
    destination_file->WriteLine(std::string("def HasKV(input, key); return input.has_key?(key); end"));
    destination_file->WriteLine(std::string("def GetKV(input, key); return input[key]; end"));
    destination_file->WriteLine(std::string("def Length(input); return input.length(); end"));
    destination_file->WriteLine(std::string("def At(input, index); return input[index]; end"));
    destination_file->WriteLine(std::string("def IntAt(input, index); return input[index].ord(); end"));
    destination_file->WriteLine(std::string("def Concat(left, right); return left + right; end"));
}

std::vector<std::string> RubyTranspiler::TokenizeBaseName(std::string name)
{
    std::vector<std::string> base_name_tokens;
    std::string current_token = std::string("");
    int index = 0;
    while (index<Length(name))
    {
        std::string character = At(name,index);
        if (character==std::string("."))
        {
            Append(base_name_tokens,current_token);
            current_token = std::string("");
        }
        else
        {
            current_token = Concat(current_token,character);
        }
        index = index+1;
    }
    Append(base_name_tokens,current_token);
    return base_name_tokens;
}

void RubyTranspiler::WriteBeginingNamespace(OmniPointer<s84::ctcode::system::ctcode::OutputStream> file)
{
    std::vector<std::string> base_name_tokens = this->TokenizeBaseName(this->base_name);
    int base_name_tokens_index = 0;
    while (base_name_tokens_index<Size(base_name_tokens))
    {
        std::string base_name_token = Element(base_name_tokens,base_name_tokens_index);
        file->WriteLine(Concat(std::string("module "),this->string_helper->ToUpper(base_name_token)));
        base_name_tokens_index = base_name_tokens_index+1;
    }
}

void RubyTranspiler::WriteEndingNamespace(OmniPointer<s84::ctcode::system::ctcode::OutputStream> file)
{
    std::vector<std::string> base_name_tokens = this->TokenizeBaseName(this->base_name);
    int base_name_tokens_index = 0;
    while (base_name_tokens_index<Size(base_name_tokens))
    {
        std::string base_name_token = Element(base_name_tokens,base_name_tokens_index);
        file->WriteLine(std::string("end"));
        base_name_tokens_index = base_name_tokens_index+1;
    }
}

void RubyTranspiler::FinishProcessingCTCodeFile()
{
    std::string destination_file_name = Concat(this->base_name,std::string(".rb"));
    OmniPointer<s84::ctcode::system::ctcode::OutputStream> destination_file = this->system->OpenFileWriter(destination_file_name);
    if (Size(this->imports)>0)
    {
        this->string_helper->WriteLines(destination_file,this->imports);
        destination_file->WriteLine(std::string(""));
    }
    this->WriteCommonFunctions(destination_file);
    destination_file->WriteLine(std::string(""));
    this->WriteBeginingNamespace(destination_file);
    destination_file->WriteLine(std::string(""));
    this->string_helper->WriteLines(destination_file,this->interface_definitions);
    this->string_helper->WriteLines(destination_file,this->class_definitions);
    this->WriteEndingNamespace(destination_file);
}

std::string RubyTranspiler::GetDefault(std::string javascript_type)
{
    if (javascript_type==std::string("int"))
    {
        return std::string("0");
    }
    if (javascript_type==std::string("string"))
    {
        return std::string("\"\"");
    }
    if (javascript_type==std::string("bool"))
    {
        return std::string("false");
    }
    if (javascript_type==std::string("float"))
    {
        return std::string("0.0");
    }
    if (javascript_type==std::string("void"))
    {
        return std::string("nil");
    }
    if (this->string_helper->BeginsWith(std::string("dict[str"),javascript_type))
    {
        return std::string("Hash.new()");
    }
    if (this->string_helper->BeginsWith(std::string("list["),javascript_type))
    {
        return std::string("Array.new()");
    }
    return std::string("nil");
}

std::string RubyTranspiler::MakeParametersString(std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
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
        result = Concat(result,parameter->GetName());
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
