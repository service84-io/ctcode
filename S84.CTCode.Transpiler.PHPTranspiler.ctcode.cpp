#include "S84.CTCode.Transpiler.PHPTranspiler.ctcode.hpp"

namespace s84 {
namespace ctcode {
namespace transpiler {
namespace phptranspiler {
namespace ctcode {

PHPTranspiler::PHPTranspiler()
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
    /*this->class_members = NO_DEFAULT;*/
}

void PHPTranspiler::Initialize()
{
    this->string_helper = std::shared_ptr<s84::ctcode::transpiler::stringhelper::ctcode::StringHelper>(new s84::ctcode::transpiler::stringhelper::ctcode::StringHelper());
}

void PHPTranspiler::SetSystem(OmniPointer<s84::ctcode::system::ctcode::System> system)
{
    this->system = system;
}

void PHPTranspiler::SetCTCodeFile(OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file)
{
    this->c_t_code_file = c_t_code_file;
}

void PHPTranspiler::SetBaseName(std::string base_name)
{
    this->base_name = base_name;
}

void PHPTranspiler::SetLogger(OmniPointer<s84::ctcode::system::ctcode::OutputStream> logger)
{
    this->logger = logger;
}

int PHPTranspiler::GetBaseIndentation()
{
    return 1;
}

std::string PHPTranspiler::GetCallName(std::string name)
{
    std::string value = this->string_helper->SnakeCaseToCamelCase(name);
    if (this->string_helper->IsReserved(value))
    {
        return Concat(std::string("ReservedPrefix"),value);
    }
    return value;
}

std::string PHPTranspiler::GetVariableName(std::string name)
{
    std::string value = this->string_helper->CamelCaseToSnakeCase(name);
    if (value==std::string("myself"))
    {
        return std::string("this");
    }
    if (this->string_helper->IsReserved(value))
    {
        return Concat(std::string("reserved_prefix_"),value);
    }
    return value;
}

std::string PHPTranspiler::GetVariableChain(std::vector<std::string> name_parts)
{
    std::string delimiter = std::string("->");
    std::string first_name = Element(name_parts,0);
    std::string result = this->GetVariableName(first_name);
    int name_parts_index = 1;
    while (name_parts_index<Size(name_parts))
    {
        std::string name = Element(name_parts,name_parts_index);
        result = Concat(Concat(result,delimiter),this->GetVariableName(name));
        name_parts_index = name_parts_index+1;
    }
    return Concat(std::string("$"),result);
}

std::string PHPTranspiler::ConvertCall(std::vector<std::string> name_chain, std::vector<std::string> parameters)
{
    std::string result = Element(name_chain,0);
    if (Size(name_chain)>1)
    {
        result = Concat(std::string("$"),result);
    }
    int name_chain_index = 1;
    while (name_chain_index<Size(name_chain))
    {
        std::string name_part = Element(name_chain,name_chain_index);
        result = Concat(Concat(result,std::string("->")),name_part);
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

std::string PHPTranspiler::ConvertAllocate(std::string type)
{
    return Concat(Concat(std::string("new "),type),std::string("()"));
}

std::string PHPTranspiler::ConvertByte(std::string high, std::string low)
{
    return Concat(Concat(std::string("0x"),high),low);
}

std::string PHPTranspiler::ConvertDecimal(std::string reserved_prefix_decimal)
{
    return reserved_prefix_decimal;
}

std::string PHPTranspiler::ConvertNumber(std::string number)
{
    return number;
}

std::string PHPTranspiler::ConvertBoolean(std::string reserved_prefix_boolean)
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

std::string PHPTranspiler::ConvertVariable(std::string variable)
{
    return variable;
}

std::string PHPTranspiler::Escape(std::string input)
{
    std::string result = std::string("");
    int input_index = 0;
    bool in_escape = false;
    while (input_index<Length(input))
    {
        std::string character = At(input,input_index);
        if (character==std::string("'"))
        {
            result = Concat(result,std::string("\\"));
        }
        if (!in_escape&&character==std::string("\\"))
        {
            in_escape = true;
        }
        else
        {
            in_escape = false;
            if (character==std::string("\\"))
            {
                result = Concat(result,std::string("\\"));
            }
            result = Concat(result,character);
        }
        input_index = input_index+1;
    }
    return result;
}

std::string PHPTranspiler::ConvertString(std::string literal)
{
    return Concat(Concat(std::string("'"),this->Escape(literal)),std::string("'"));
}

std::string PHPTranspiler::UnaryOperator(std::string op, std::string r_value)
{
    if (op==std::string("!"))
    {
        return Concat(std::string("!"),r_value);
    }
    return r_value;
}

std::string PHPTranspiler::BinaryOperator(std::string op, std::string r_value_l, std::string r_value_r)
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
        return Concat(Concat(r_value_l,std::string("||")),r_value_r);
    }
    if (op==std::string("&&"))
    {
        return Concat(Concat(r_value_l,std::string("&&")),r_value_r);
    }
    return std::string("");
}

std::string PHPTranspiler::GetTypeName(std::string name)
{
    std::string value = this->string_helper->SnakeCaseToCamelCase(name);
    if (this->string_helper->IsReserved(value))
    {
        return Concat(std::string("ReservedPrefix"),value);
    }
    return value;
}

std::string PHPTranspiler::GetDimensionalType(std::string singleton_type, int dimensions)
{
    return std::string("?array");
}

std::string PHPTranspiler::GetMapType(std::string singleton_type)
{
    return std::string("?array");
}

std::string PHPTranspiler::GetPrimativeType(std::string c_t_type)
{
    if (c_t_type==std::string("int"))
    {
        return std::string("?int");
    }
    if (c_t_type==std::string("string"))
    {
        return std::string("?string");
    }
    if (c_t_type==std::string("bool"))
    {
        return std::string("?bool");
    }
    if (c_t_type==std::string("float"))
    {
        return std::string("?float");
    }
    if (c_t_type==std::string("void"))
    {
        return std::string("void");
    }
    return std::string("");
}

std::string PHPTranspiler::GetDefinedType(std::string c_t_type)
{
    return Concat(std::string("?"),c_t_type);
}

std::string PHPTranspiler::GetQualifiedTypeName(std::vector<std::string> name_parts)
{
    std::string delimiter = std::string("\\");
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
        result = Concat(delimiter,result);
    }
    return result;
}

void PHPTranspiler::BeginProcessingCTCodeFile()
{
    ClearList(this->imports);
    this->current_interface = std::string("");
    ClearList(this->interface_definitions);
    this->current_class = std::string("");
    ClearList(this->class_definitions);
    ClearList(this->class_init);
    ClearList(this->class_functions);
    ClearList(this->class_members);
}

void PHPTranspiler::FinishProcessingCTCodeFile()
{
    std::string destination_file_name = Concat(this->base_name,std::string(".php"));
    OmniPointer<s84::ctcode::system::ctcode::OutputStream> destination_file = this->system->OpenFileWriter(destination_file_name);
    destination_file->WriteLine(std::string("<?php"));
    destination_file->WriteLine(Concat(Concat(std::string("namespace "),this->string_helper->DotToFwdSlash(this->base_name)),std::string(";")));
    destination_file->WriteLine(std::string(""));
    if (Size(this->imports)>0)
    {
        this->string_helper->WriteLines(destination_file,this->imports);
        destination_file->WriteLine(std::string(""));
    }
    this->WriteCommonFunctions(destination_file);
    destination_file->WriteLine(std::string(""));
    this->string_helper->WriteLines(destination_file,this->interface_definitions);
    this->string_helper->WriteLines(destination_file,this->class_definitions);
    destination_file->WriteLine(std::string("?>"));
}

void PHPTranspiler::ProcessExdef(std::string exdef)
{
    Append(this->imports,Concat(Concat(std::string("include_once \""),exdef),std::string(".php\";")));
}

void PHPTranspiler::ProcessUnmanagedType(std::string unmanaged_type)
{
}

void PHPTranspiler::BeginProcessingInterface(std::string interface_name)
{
    this->current_interface = interface_name;
    Append(this->interface_definitions,Concat(Concat(std::string("interface "),interface_name),std::string(" {")));
}

void PHPTranspiler::ProcessInterfaceFunctionDeclaration(std::string return_type, std::string function_name, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    Append(this->interface_definitions,Concat(Concat(Concat(Concat(Concat(Concat(this->string_helper->Indentation(1),std::string("public function ")),function_name),this->MakeParametersString(parameters)),std::string(": ")),return_type),std::string(";")));
}

void PHPTranspiler::FinishProcessingInterface(std::string interface_name)
{
    Append(this->interface_definitions,std::string("}"));
    Append(this->interface_definitions,std::string(""));
    this->current_interface = std::string("");
}

void PHPTranspiler::BeginProcessingClass(std::string class_name, std::string implementing)
{
    this->current_class = class_name;
    if (implementing==std::string(""))
    {
        Append(this->class_definitions,Concat(Concat(std::string("class "),class_name),std::string(" {")));
    }
    else
    {
        Append(this->class_definitions,Concat(Concat(Concat(Concat(std::string("class "),class_name),std::string(" implements ")),implementing),std::string(" {")));
    }
    ClearList(this->class_init);
    ClearList(this->class_functions);
    ClearList(this->class_members);
    Append(this->class_init,Concat(this->string_helper->Indentation(1),std::string("public function __construct() {")));
}

void PHPTranspiler::BeginProcessingClassFunctionDefinition(std::string return_type, std::string function_name, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    Append(this->class_functions,std::string(""));
    Append(this->class_functions,Concat(Concat(Concat(Concat(Concat(this->string_helper->Indentation(1),std::string("public function ")),function_name),this->MakeParametersString(parameters)),std::string(": ")),return_type));
}

void PHPTranspiler::BeginProcessCodeBlock(int indent)
{
    Append(this->class_functions,Concat(this->string_helper->Indentation(indent),std::string("{")));
}

void PHPTranspiler::FinishProcessCodeBlock(int indent)
{
    Append(this->class_functions,Concat(this->string_helper->Indentation(indent),std::string("}")));
}

void PHPTranspiler::BeginProcessConditional(int indent, std::string r_value)
{
    Append(this->class_functions,Concat(Concat(Concat(this->string_helper->Indentation(indent),std::string("if (")),r_value),std::string(")")));
}

void PHPTranspiler::ProcessElse(int indent)
{
    Append(this->class_functions,Concat(this->string_helper->Indentation(indent),std::string("else")));
}

void PHPTranspiler::FinishProcessConditional(int indent, std::string r_value)
{
}

void PHPTranspiler::BeginProcessLoop(int indent, std::string r_value)
{
    Append(this->class_functions,Concat(Concat(Concat(this->string_helper->Indentation(indent),std::string("while (")),r_value),std::string(")")));
}

void PHPTranspiler::FinishProcessLoop(int indent, std::string r_value)
{
}

void PHPTranspiler::ProcessRtn(int indent, std::string r_value)
{
    Append(this->class_functions,Concat(Concat(Concat(this->string_helper->Indentation(indent),std::string("return ")),r_value),std::string(";")));
}

void PHPTranspiler::ProcessDeclaration(int indent, std::string type, std::string l_value, std::string r_value)
{
    if (r_value==std::string(""))
    {
        r_value = this->GetDefault(type);
    }
    Append(this->class_functions,Concat(Concat(Concat(Concat(Concat(this->string_helper->Indentation(indent),std::string("$")),l_value),std::string(" = ")),r_value),std::string(";")));
}

void PHPTranspiler::ProcessAssignment(int indent, std::string l_value, std::string r_value)
{
    Append(this->class_functions,Concat(Concat(Concat(Concat(this->string_helper->Indentation(indent),l_value),std::string(" = ")),r_value),std::string(";")));
}

void PHPTranspiler::ProcessCall(int indent, std::string call)
{
    Append(this->class_functions,Concat(Concat(this->string_helper->Indentation(indent),call),std::string(";")));
}

void PHPTranspiler::FinishProcessingClassFunctionDefinition(std::string return_type, std::string function_name, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
}

void PHPTranspiler::ProcessClassMemberDeclaration(std::string member_type, std::string member_name)
{
    Append(this->class_init,Concat(Concat(Concat(Concat(Concat(this->string_helper->Indentation(2),std::string("$this->")),member_name),std::string(" = ")),this->GetDefault(member_type)),std::string(";")));
    Append(this->class_members,Concat(Concat(Concat(this->string_helper->Indentation(1),std::string("private $")),member_name),std::string(";")));
}

void PHPTranspiler::FinishProcessingClass(std::string class_name, std::string implementing)
{
    Append(this->class_init,Concat(this->string_helper->Indentation(1),std::string("}")));
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
    Append(this->class_definitions,std::string(""));
    int class_members_index = 0;
    while (class_members_index<Size(this->class_members))
    {
        std::string line = Element(this->class_members,class_members_index);
        Append(this->class_definitions,line);
        class_members_index = class_members_index+1;
    }
    Append(this->class_definitions,std::string("}"));
    Append(this->class_definitions,std::string(""));
    this->current_class = std::string("");
}

void PHPTranspiler::WriteCommonFunctions(OmniPointer<s84::ctcode::system::ctcode::OutputStream> destination_file)
{
    destination_file->WriteLine(std::string("function ClearList(array & $input): void { $input = array(); }"));
    destination_file->WriteLine(std::string("function Size(array $input): int { return count($input); }"));
    destination_file->WriteLine(std::string("function Element(array $input, int $element) { return $input[$element]; }"));
    destination_file->WriteLine(std::string("function Append(array & $input, mixed $element): void { $input[] = $element; }"));
    destination_file->WriteLine(std::string("function ClearMap(array & $input): void { reset($input); }"));
    destination_file->WriteLine(std::string("function SetKV(array & $input, string $key, mixed $element): void { $input[$key] = $element; }"));
    destination_file->WriteLine(std::string("function Keys(array $input): array { return array_keys($input); }"));
    destination_file->WriteLine(std::string("function HasKV(array $input, string $key): bool { return array_key_exists($key, $input); }"));
    destination_file->WriteLine(std::string("function GetKV(array $input, string $key) { return $input[$key]; }"));
    destination_file->WriteLine(std::string("function Length(string $input): int { return strlen($input); }"));
    destination_file->WriteLine(std::string("function At(string $input, int $index): string { return substr($input, $index, 1); }"));
    destination_file->WriteLine(std::string("function IntAt(string $input, int $index): int { return ord(substr($input, $index, 1)); }"));
    destination_file->WriteLine(std::string("function Concat(string $left, string $right): string { return $left . $right; }"));
}

std::string PHPTranspiler::GetDefault(std::string php_type)
{
    if (php_type==std::string("?int"))
    {
        return std::string("0");
    }
    if (php_type==std::string("?string"))
    {
        return std::string("\"\"");
    }
    if (php_type==std::string("?bool"))
    {
        return std::string("false");
    }
    if (php_type==std::string("?float"))
    {
        return std::string("0.0");
    }
    if (php_type==std::string("void"))
    {
        return std::string("null");
    }
    if (php_type==std::string("?array"))
    {
        return std::string("array()");
    }
    return std::string("null");
}

std::string PHPTranspiler::MakeParametersString(std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
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
        result = Concat(Concat(Concat(result,parameter->ReservedPrefixGetType()),std::string(" $")),parameter->GetName());
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
