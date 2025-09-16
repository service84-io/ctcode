#include "S84.CTCode.Transpiler.Python3Transpiler.ctcode.hpp"

namespace s84 {
namespace ctcode {
namespace transpiler {
namespace python3transpiler {
namespace ctcode {

Python3Transpiler::Python3Transpiler()
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

void Python3Transpiler::Initialize()
{
    this->string_helper = std::shared_ptr<s84::ctcode::transpiler::stringhelper::ctcode::StringHelper>(new s84::ctcode::transpiler::stringhelper::ctcode::StringHelper());
}

void Python3Transpiler::SetSystem(OmniPointer<s84::ctcode::system::ctcode::System> system)
{
    this->system = system;
}

void Python3Transpiler::SetCTCodeFile(OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file)
{
    this->c_t_code_file = c_t_code_file;
}

void Python3Transpiler::SetBaseName(std::string base_name)
{
    this->base_name = base_name;
}

void Python3Transpiler::SetLogger(OmniPointer<s84::ctcode::system::ctcode::OutputStream> logger)
{
    this->logger = logger;
}

int Python3Transpiler::GetBaseIndentation()
{
    return 1;
}

std::string Python3Transpiler::GetCallName(std::string name)
{
    return this->string_helper->SnakeCaseToCamelCase(name);
}

std::string Python3Transpiler::GetVariableName(std::string name)
{
    std::string value = this->string_helper->CamelCaseToSnakeCase(name);
    if (value==std::string("myself"))
    {
        return std::string("self");
    }
    return value;
}

std::string Python3Transpiler::GetVariableChain(std::vector<std::string> name_parts)
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

std::string Python3Transpiler::ConvertCall(std::vector<std::string> name_chain, std::vector<std::string> parameters)
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
            result = Concat(result,std::string(","));
            result = Concat(result,parameter);
            parameters_index = parameters_index+1;
        }
    }
    result = Concat(result,std::string(")"));
    return result;
}

std::string Python3Transpiler::ConvertAllocate(std::string type)
{
    return Concat(type,std::string("()"));
}

std::string Python3Transpiler::ConvertByte(std::string high, std::string low)
{
    return Concat(Concat(std::string("0x"),high),low);
}

std::string Python3Transpiler::ConvertDecimal(std::string decimal)
{
    return decimal;
}

std::string Python3Transpiler::ConvertNumber(std::string number)
{
    return number;
}

std::string Python3Transpiler::ConvertBoolean(std::string boolean)
{
    if (boolean==std::string("true"))
    {
        return std::string("True");
    }
    if (boolean==std::string("false"))
    {
        return std::string("False");
    }
    return std::string("");
}

std::string Python3Transpiler::ConvertVariable(std::string variable)
{
    return variable;
}

std::string Python3Transpiler::ConvertString(std::string literal)
{
    return Concat(Concat(std::string("\""),literal),std::string("\""));
}

std::string Python3Transpiler::UnaryOperator(std::string op, std::string r_value)
{
    if (op==std::string("!"))
    {
        return Concat(std::string("not "),r_value);
    }
    return r_value;
}

std::string Python3Transpiler::BinaryOperator(std::string op, std::string r_value_l, std::string r_value_r)
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
        return Concat(Concat(r_value_l,std::string(" or ")),r_value_r);
    }
    if (op==std::string("&&"))
    {
        return Concat(Concat(r_value_l,std::string(" and ")),r_value_r);
    }
    return std::string("");
}

std::string Python3Transpiler::GetTypeName(std::string name)
{
    return this->string_helper->SnakeCaseToCamelCase(name);
}

std::string Python3Transpiler::GetDimensionalType(std::string singleton_type, int dimensions)
{
    std::string result = singleton_type;
    while (dimensions>0)
    {
        result = Concat(Concat(std::string("list["),result),std::string("]"));
        dimensions = dimensions-1;
    }
    return result;
}

std::string Python3Transpiler::GetMapType(std::string singleton_type)
{
    return Concat(Concat(std::string("dict[str, "),singleton_type),std::string("]"));
}

std::string Python3Transpiler::GetPrimativeType(std::string c_t_type)
{
    if (c_t_type==std::string("int"))
    {
        return std::string("int");
    }
    if (c_t_type==std::string("string"))
    {
        return std::string("str");
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
        return std::string("None");
    }
    return std::string("");
}

std::string Python3Transpiler::GetDefinedType(std::string c_t_type)
{
    return c_t_type;
}

std::string Python3Transpiler::GetQualifiedTypeName(std::vector<std::string> name_parts)
{
    std::string package_delimiter = std::string("_");
    std::string package_name_delimiter = std::string(".");
    int name_parts_index = Size(name_parts)-1;
    int last_package_index = Size(name_parts)-2;
    std::string type_part = Element(name_parts,name_parts_index);
    std::string result = this->GetTypeName(type_part);
    if (name_parts_index>0)
    {
        result = Concat(package_name_delimiter,result);
        while (name_parts_index>0)
        {
            name_parts_index = name_parts_index-1;
            std::string name_part = Element(name_parts,name_parts_index);
            if (name_parts_index!=last_package_index)
            {
                result = Concat(package_delimiter,result);
            }
            result = Concat(name_part,result);
        }
    }
    return result;
}

void Python3Transpiler::BeginProcessingCTCodeFile()
{
    ClearList(this->imports);
    this->current_interface = std::string("");
    ClearList(this->interface_definitions);
    this->current_class = std::string("");
    ClearList(this->class_definitions);
    ClearList(this->class_init);
    ClearList(this->class_functions);
}

void Python3Transpiler::ProcessExdef(std::string exdef)
{
    Append(this->imports,Concat(std::string("import "),this->string_helper->StripDot(exdef)));
}

void Python3Transpiler::ProcessUnmanagedType(std::string unmanaged_type)
{
    int noop = 0;
}

void Python3Transpiler::BeginProcessingInterface(std::string interface_name)
{
    this->current_interface = interface_name;
    Append(this->interface_definitions,Concat(Concat(std::string("class "),interface_name),std::string(":")));
}

void Python3Transpiler::ProcessInterfaceFunctionDeclaration(std::string return_type, std::string function_name, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    Append(this->interface_definitions,Concat(Concat(Concat(Concat(Concat(Concat(this->string_helper->Indentation(1),std::string("def ")),function_name),this->MakeParametersString(this->current_interface,parameters)),std::string(" -> '")),return_type),std::string("': pass")));
}

void Python3Transpiler::FinishProcessingInterface(std::string interface_name)
{
    Append(this->interface_definitions,std::string(""));
    this->current_interface = std::string("");
}

void Python3Transpiler::BeginProcessingClass(std::string class_name, std::string implementing)
{
    this->current_class = class_name;
    if (implementing==std::string(""))
    {
        Append(this->class_definitions,Concat(Concat(std::string("class "),class_name),std::string(":")));
    }
    else
    {
        Append(this->class_definitions,Concat(Concat(Concat(Concat(std::string("class "),class_name),std::string("(")),implementing),std::string("):")));
    }
    ClearList(this->class_init);
    ClearList(this->class_functions);
    Append(this->class_init,Concat(Concat(Concat(this->string_helper->Indentation(1),std::string("def __init__(self: '")),class_name),std::string("'):")));
}

void Python3Transpiler::BeginProcessingClassFunctionDefinition(std::string return_type, std::string function_name, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    Append(this->class_functions,Concat(Concat(Concat(Concat(Concat(Concat(this->string_helper->Indentation(1),std::string("def ")),function_name),this->MakeParametersString(this->current_class,parameters)),std::string(" -> '")),return_type),std::string("':")));
}

void Python3Transpiler::BeginProcessCodeBlock(int indent)
{
    int noop = 0;
}

void Python3Transpiler::FinishProcessCodeBlock(int indent)
{
    int noop = 0;
}

void Python3Transpiler::BeginProcessConditional(int indent, std::string r_value)
{
    Append(this->class_functions,Concat(Concat(Concat(this->string_helper->Indentation(indent),std::string("if ")),r_value),std::string(":")));
}

void Python3Transpiler::ProcessElse(int indent)
{
    Append(this->class_functions,Concat(this->string_helper->Indentation(indent),std::string("else:")));
}

void Python3Transpiler::FinishProcessConditional(int indent, std::string r_value)
{
    int noop = 0;
}

void Python3Transpiler::BeginProcessLoop(int indent, std::string r_value)
{
    Append(this->class_functions,Concat(Concat(Concat(this->string_helper->Indentation(indent),std::string("while ")),r_value),std::string(":")));
}

void Python3Transpiler::FinishProcessLoop(int indent, std::string r_value)
{
    int noop = 0;
}

void Python3Transpiler::ProcessRtn(int indent, std::string r_value)
{
    Append(this->class_functions,Concat(Concat(this->string_helper->Indentation(indent),std::string("return ")),r_value));
}

void Python3Transpiler::ProcessDeclaration(int indent, std::string type, std::string l_value, std::string r_value)
{
    if (r_value==std::string(""))
    {
        r_value = this->GetDefault(type);
    }
    Append(this->class_functions,Concat(Concat(Concat(Concat(Concat(this->string_helper->Indentation(indent),l_value),std::string(": '")),type),std::string("' = ")),r_value));
}

void Python3Transpiler::ProcessAssignment(int indent, std::string l_value, std::string r_value)
{
    Append(this->class_functions,Concat(Concat(Concat(this->string_helper->Indentation(indent),l_value),std::string(" = ")),r_value));
}

void Python3Transpiler::ProcessCall(int indent, std::string call)
{
    Append(this->class_functions,Concat(this->string_helper->Indentation(indent),call));
}

void Python3Transpiler::FinishProcessingClassFunctionDefinition(std::string return_type, std::string function_name, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    Append(this->class_functions,std::string(""));
}

void Python3Transpiler::ProcessClassMemberDeclaration(std::string member_type, std::string member_name)
{
    Append(this->class_init,Concat(Concat(Concat(Concat(Concat(Concat(this->string_helper->Indentation(2),std::string("self.")),member_name),std::string(": ")),member_type),std::string(" = ")),this->GetDefault(member_type)));
}

void Python3Transpiler::FinishProcessingClass(std::string class_name, std::string implementing)
{
    if (Size(this->class_init)==1)
    {
        Append(this->class_init,Concat(this->string_helper->Indentation(2),std::string("pass")));
    }
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
    this->current_class = std::string("");
}

void Python3Transpiler::WriteCommonFunctions(OmniPointer<s84::ctcode::system::ctcode::OutputStream> destination_file)
{
    destination_file->WriteLine(std::string("def ClearList(input: list) -> None: input.clear()"));
    destination_file->WriteLine(std::string("def Size(input: list) -> int: return len(input)"));
    destination_file->WriteLine(std::string("def Element(input: list, element: int ) -> any: return input[element]"));
    destination_file->WriteLine(std::string("def Append(input: list, element: any) -> None: input.append(element)"));
    destination_file->WriteLine(std::string("def ClearMap(input: dict) -> None: input.clear()"));
    destination_file->WriteLine(std::string("def SetKV(input: dict, key: str, element: any) -> None: input[key] = element"));
    destination_file->WriteLine(std::string("def Keys(input: dict) -> list[str]:"));
    destination_file->WriteLine(std::string("    result: list[str] = []"));
    destination_file->WriteLine(std::string("    for key in input.keys():"));
    destination_file->WriteLine(std::string("        result.append(key)"));
    destination_file->WriteLine(std::string("    return result"));
    destination_file->WriteLine(std::string("def HasKV(input: dict, key: str) -> bool: return key in input"));
    destination_file->WriteLine(std::string("def GetKV(input: dict, key: str) -> any: return input[key]"));
    destination_file->WriteLine(std::string("def Length(input: str) -> int: return len(input)"));
    destination_file->WriteLine(std::string("def At(input: str, index: int) -> str: return input[index:index+1]"));
    destination_file->WriteLine(std::string("def IntAt(input: str, index: int) -> int: return ord(input[index:index+1])"));
    destination_file->WriteLine(std::string("def Concat(left: str, right: str) -> str: return left + right"));
}

void Python3Transpiler::FinishProcessingCTCodeFile()
{
    std::string destination_file_name = Concat(this->string_helper->StripDot(this->base_name),std::string(".py"));
    OmniPointer<s84::ctcode::system::ctcode::OutputStream> destination_file = this->system->OpenFileWriter(destination_file_name);
    if (Size(this->imports)>0)
    {
        this->string_helper->WriteLines(destination_file,this->imports);
        destination_file->WriteLine(std::string(""));
    }
    this->WriteCommonFunctions(destination_file);
    destination_file->WriteLine(std::string(""));
    this->string_helper->WriteLines(destination_file,this->interface_definitions);
    this->string_helper->WriteLines(destination_file,this->class_definitions);
}

std::string Python3Transpiler::GetDefault(std::string python_type)
{
    if (python_type==std::string("int"))
    {
        return std::string("0");
    }
    if (python_type==std::string("str"))
    {
        return std::string("\"\"");
    }
    if (python_type==std::string("bool"))
    {
        return std::string("False");
    }
    if (python_type==std::string("float"))
    {
        return std::string("0.0");
    }
    if (python_type==std::string("None"))
    {
        return std::string("None");
    }
    if (this->string_helper->BeginsWith(std::string("dict[str"),python_type))
    {
        return std::string("{}");
    }
    if (this->string_helper->BeginsWith(std::string("list["),python_type))
    {
        return std::string("[]");
    }
    return std::string("None");
}

std::string Python3Transpiler::MakeParametersString(std::string self_type, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    std::string result = Concat(Concat(std::string("(self: '"),self_type),std::string("'"));
    int parameters_index = 0;
    while (parameters_index<Size(parameters))
    {
        OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration> parameter = Element(parameters,parameters_index);
        result = Concat(result,std::string(","));
        result = Concat(Concat(Concat(Concat(result,parameter->GetName()),std::string(": '")),parameter->GetType()),std::string("'"));
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
