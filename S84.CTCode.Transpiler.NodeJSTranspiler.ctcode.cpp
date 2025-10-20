#include "S84.CTCode.Transpiler.NodeJSTranspiler.ctcode.hpp"

namespace s84 {
namespace ctcode {
namespace transpiler {
namespace nodejstranspiler {
namespace ctcode {

NodeJSTranspiler::NodeJSTranspiler()
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

void NodeJSTranspiler::Initialize()
{
    this->string_helper = std::shared_ptr<s84::ctcode::transpiler::stringhelper::ctcode::StringHelper>(new s84::ctcode::transpiler::stringhelper::ctcode::StringHelper());
}

void NodeJSTranspiler::SetSystem(OmniPointer<s84::ctcode::system::ctcode::System> system)
{
    this->system = system;
}

void NodeJSTranspiler::SetCTCodeFile(OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file)
{
    this->c_t_code_file = c_t_code_file;
}

void NodeJSTranspiler::SetBaseName(std::string base_name)
{
    this->base_name = base_name;
}

void NodeJSTranspiler::SetLogger(OmniPointer<s84::ctcode::system::ctcode::OutputStream> logger)
{
    this->logger = logger;
}

int NodeJSTranspiler::GetBaseIndentation()
{
    return 1;
}

std::string NodeJSTranspiler::GetCallName(std::string name)
{
    std::string value = this->string_helper->SnakeCaseToCamelCase(name);
    if (this->string_helper->IsReserved(value))
    {
        return Concat(std::string("ReservedPrefix"),value);
    }
    return value;
}

std::string NodeJSTranspiler::GetVariableName(std::string name)
{
    std::string value = this->string_helper->CamelCaseToSnakeCase(name);
    if (value==std::string("myself"))
    {
        return std::string("this");
    }
    if (value==std::string("nothing"))
    {
        return std::string("null");
    }
    if (this->string_helper->IsReserved(value))
    {
        return Concat(std::string("reserved_prefix_"),value);
    }
    return value;
}

std::string NodeJSTranspiler::GetVariableChain(std::vector<std::string> name_parts)
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

std::string NodeJSTranspiler::ConvertCall(std::vector<std::string> name_chain, std::vector<std::string> parameters)
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

std::string NodeJSTranspiler::ConvertAllocate(std::string type)
{
    return Concat(Concat(std::string("new "),type),std::string("()"));
}

std::string NodeJSTranspiler::ConvertByte(std::string high, std::string low)
{
    return Concat(Concat(std::string("0x"),high),low);
}

std::string NodeJSTranspiler::ConvertDecimal(std::string reserved_prefix_decimal)
{
    return reserved_prefix_decimal;
}

std::string NodeJSTranspiler::ConvertNumber(std::string number)
{
    return number;
}

std::string NodeJSTranspiler::ConvertBoolean(std::string reserved_prefix_boolean)
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

std::string NodeJSTranspiler::ConvertVariable(std::string variable)
{
    return variable;
}

std::string NodeJSTranspiler::ConvertString(std::string literal)
{
    return Concat(Concat(std::string("\""),literal),std::string("\""));
}

std::string NodeJSTranspiler::UnaryOperator(std::string op, std::string r_value)
{
    if (op==std::string("!"))
    {
        return Concat(std::string("! "),r_value);
    }
    return r_value;
}

std::string NodeJSTranspiler::BinaryOperator(std::string op, std::string r_value_l, std::string r_value_r)
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

std::string NodeJSTranspiler::GetTypeName(std::string name)
{
    std::string value = this->string_helper->SnakeCaseToCamelCase(name);
    if (this->string_helper->IsReserved(value))
    {
        return Concat(std::string("ReservedPrefix"),value);
    }
    return value;
}

std::string NodeJSTranspiler::GetDimensionalType(std::string singleton_type, int dimensions)
{
    std::string result = singleton_type;
    while (dimensions>0)
    {
        result = Concat(Concat(std::string("list["),result),std::string("]"));
        dimensions = dimensions-1;
    }
    return result;
}

std::string NodeJSTranspiler::GetMapType(std::string singleton_type)
{
    return Concat(Concat(std::string("dict[str, "),singleton_type),std::string("]"));
}

std::string NodeJSTranspiler::GetPrimativeType(std::string c_t_type)
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

std::string NodeJSTranspiler::GetDefinedType(std::string c_t_type)
{
    return c_t_type;
}

std::string NodeJSTranspiler::GetQualifiedTypeName(std::vector<std::string> name_parts)
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

void NodeJSTranspiler::BeginProcessingCTCodeFile()
{
    ClearList(this->imports);
    this->current_interface = std::string("");
    ClearList(this->interface_definitions);
    this->current_class = std::string("");
    ClearList(this->class_definitions);
    ClearList(this->class_init);
    ClearList(this->class_functions);
}

void NodeJSTranspiler::ProcessExdef(std::string exdef)
{
    Append(this->imports,Concat(Concat(Concat(Concat(std::string("import * as "),this->string_helper->StripDot(exdef)),std::string(" from \"./")),this->string_helper->StripDot(exdef)),std::string(".js\"")));
}

void NodeJSTranspiler::ProcessUnmanagedType(std::string unmanaged_type)
{
}

void NodeJSTranspiler::BeginProcessingInterface(std::string interface_name)
{
    this->current_interface = interface_name;
    Append(this->interface_definitions,Concat(Concat(std::string("export class "),interface_name),std::string(" {")));
}

void NodeJSTranspiler::ProcessInterfaceFunctionDeclaration(std::string return_type, std::string function_name, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    Append(this->interface_definitions,Concat(Concat(Concat(this->string_helper->Indentation(1),function_name),this->MakeParametersString(parameters)),std::string(" {}")));
}

void NodeJSTranspiler::FinishProcessingInterface(std::string interface_name)
{
    Append(this->interface_definitions,std::string("}"));
    Append(this->interface_definitions,std::string(""));
    this->current_interface = std::string("");
}

void NodeJSTranspiler::BeginProcessingClass(std::string class_name, std::string implementing)
{
    this->current_class = class_name;
    Append(this->class_definitions,Concat(Concat(std::string("export class "),class_name),std::string(" {")));
    ClearList(this->class_init);
    ClearList(this->class_functions);
    Append(this->class_init,Concat(this->string_helper->Indentation(1),std::string("constructor() {")));
}

void NodeJSTranspiler::BeginProcessingClassFunctionDefinition(std::string return_type, std::string function_name, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    Append(this->class_functions,std::string(""));
    Append(this->class_functions,Concat(Concat(this->string_helper->Indentation(1),function_name),this->MakeParametersString(parameters)));
}

void NodeJSTranspiler::BeginProcessCodeBlock(int indent)
{
    Append(this->class_functions,Concat(this->string_helper->Indentation(indent),std::string("{")));
}

void NodeJSTranspiler::FinishProcessCodeBlock(int indent)
{
    Append(this->class_functions,Concat(this->string_helper->Indentation(indent),std::string("}")));
}

void NodeJSTranspiler::BeginProcessConditional(int indent, std::string r_value)
{
    Append(this->class_functions,Concat(Concat(Concat(this->string_helper->Indentation(indent),std::string("if (")),r_value),std::string(")")));
}

void NodeJSTranspiler::ProcessElse(int indent)
{
    Append(this->class_functions,Concat(this->string_helper->Indentation(indent),std::string("else")));
}

void NodeJSTranspiler::FinishProcessConditional(int indent, std::string r_value)
{
}

void NodeJSTranspiler::BeginProcessLoop(int indent, std::string r_value)
{
    Append(this->class_functions,Concat(Concat(Concat(this->string_helper->Indentation(indent),std::string("while (")),r_value),std::string(")")));
}

void NodeJSTranspiler::FinishProcessLoop(int indent, std::string r_value)
{
}

void NodeJSTranspiler::ProcessRtn(int indent, std::string r_value)
{
    Append(this->class_functions,Concat(Concat(this->string_helper->Indentation(indent),std::string("return ")),r_value));
}

void NodeJSTranspiler::ProcessDeclaration(int indent, std::string type, std::string l_value, std::string r_value)
{
    if (r_value==std::string(""))
    {
        r_value = this->GetDefault(type);
    }
    Append(this->class_functions,Concat(Concat(Concat(Concat(this->string_helper->Indentation(indent),std::string("var ")),l_value),std::string(" = ")),r_value));
}

void NodeJSTranspiler::ProcessAssignment(int indent, std::string l_value, std::string r_value)
{
    Append(this->class_functions,Concat(Concat(Concat(this->string_helper->Indentation(indent),l_value),std::string(" = ")),r_value));
}

void NodeJSTranspiler::ProcessCall(int indent, std::string call)
{
    Append(this->class_functions,Concat(this->string_helper->Indentation(indent),call));
}

void NodeJSTranspiler::FinishProcessingClassFunctionDefinition(std::string return_type, std::string function_name, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
}

void NodeJSTranspiler::ProcessClassMemberDeclaration(std::string member_type, std::string member_name)
{
    Append(this->class_init,Concat(Concat(Concat(Concat(this->string_helper->Indentation(2),std::string("this.")),member_name),std::string(" = ")),this->GetDefault(member_type)));
}

void NodeJSTranspiler::FinishProcessingClass(std::string class_name, std::string implementing)
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
    Append(this->class_definitions,std::string("}"));
    Append(this->class_definitions,std::string(""));
    this->current_class = std::string("");
}

void NodeJSTranspiler::WriteCommonFunctions(OmniPointer<s84::ctcode::system::ctcode::OutputStream> destination_file)
{
    destination_file->WriteLine(std::string("function ClearList(input) { input.length = 0; }"));
    destination_file->WriteLine(std::string("function Size(input) { return input.length; }"));
    destination_file->WriteLine(std::string("function Element(input, element) { return input[element]; }"));
    destination_file->WriteLine(std::string("function Append(input, element) { input.push(element); }"));
    destination_file->WriteLine(std::string("function ClearMap(input) { input.clear(); }"));
    destination_file->WriteLine(std::string("function SetKV(input, key, element) { input.set(key, element); }"));
    destination_file->WriteLine(std::string("function Keys(input) { return Array.from(input.keys()); }"));
    destination_file->WriteLine(std::string("function HasKV(input, key) { return input.has(key); }"));
    destination_file->WriteLine(std::string("function GetKV(input, key) { return input.get(key); }"));
    destination_file->WriteLine(std::string("function Length(input) { return input.length; }"));
    destination_file->WriteLine(std::string("function At(input, index) { return input[index]; }"));
    destination_file->WriteLine(std::string("function IntAt(input, index) { return input.charCodeAt(index); }"));
    destination_file->WriteLine(std::string("function Concat(left, right) { return left + right; }"));
}

void NodeJSTranspiler::FinishProcessingCTCodeFile()
{
    std::string destination_file_name = Concat(this->string_helper->StripDot(this->base_name),std::string(".js"));
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

std::string NodeJSTranspiler::GetDefault(std::string javascript_type)
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
        return std::string("null");
    }
    if (this->string_helper->BeginsWith(std::string("dict[str"),javascript_type))
    {
        return std::string("new Map()");
    }
    if (this->string_helper->BeginsWith(std::string("list["),javascript_type))
    {
        return std::string("[]");
    }
    return std::string("null");
}

std::string NodeJSTranspiler::MakeParametersString(std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
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
