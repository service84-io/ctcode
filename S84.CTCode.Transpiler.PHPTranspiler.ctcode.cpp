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
    return this->string_helper->SnakeCaseToCamelCase(name);
}

std::string PHPTranspiler::GetVariableName(std::string name)
{
    std::string value = this->string_helper->CamelCaseToSnakeCase(name);
    if (value==std::string("myself"))
    {
        return std::string("this");
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
    return result;
}

std::string PHPTranspiler::ConvertCall(std::vector<std::string> name_chain, std::vector<std::string> parameters)
{
    std::string result = Element(name_chain,0);
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
    return Concat(std::string("new "),type);
}

std::string PHPTranspiler::ConvertByte(std::string high, std::string low)
{
    return Concat(Concat(std::string("0x"),high),low);
}

std::string PHPTranspiler::ConvertDecimal(std::string decimal)
{
    return decimal;
}

std::string PHPTranspiler::ConvertNumber(std::string number)
{
    return number;
}

std::string PHPTranspiler::ConvertBoolean(std::string boolean)
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

std::string PHPTranspiler::ConvertVariable(std::string variable)
{
    return variable;
}

std::string PHPTranspiler::ConvertString(std::string literal)
{
    return Concat(Concat(std::string("\""),literal),std::string("\""));
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
    return this->string_helper->SnakeCaseToCamelCase(name);
}

std::string PHPTranspiler::GetDimensionalType(std::string singleton_type, int dimensions)
{
    std::string result = singleton_type;
    while (dimensions>0)
    {
        result = Concat(result,std::string("[]"));
        dimensions = dimensions-1;
    }
    return result;
}

std::string PHPTranspiler::GetMapType(std::string singleton_type)
{
    return Concat(singleton_type,std::string("{}"));
}

std::string PHPTranspiler::GetPrimativeType(std::string c_t_type)
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

std::string PHPTranspiler::GetDefinedType(std::string c_t_type)
{
    return c_t_type;
}

std::string PHPTranspiler::GetQualifiedTypeName(std::vector<std::string> name_parts)
{
    std::string delimiter = std::string(".");
    std::string first_name = Element(name_parts,0);
    std::string result = first_name;
    int name_parts_index = 1;
    while (name_parts_index<Size(name_parts))
    {
        std::string name = Element(name_parts,name_parts_index);
        result = Concat(Concat(result,delimiter),name);
        name_parts_index = name_parts_index+1;
    }
    return result;
}

void PHPTranspiler::BeginProcessingCTCodeFile()
{
    this->logger->WriteLine(std::string("BeginProcessingCTCodeFile"));
}

void PHPTranspiler::FinishProcessingCTCodeFile()
{
    this->logger->WriteLine(std::string("FinishProcessingCTCodeFile"));
}

void PHPTranspiler::ProcessExdef(std::string exdef)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(1),std::string("ProcessExdef: ")),exdef));
}

void PHPTranspiler::ProcessUnmanagedType(std::string unmanaged_type)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(1),std::string("ProcessUnmanagedType: ")),unmanaged_type));
}

void PHPTranspiler::BeginProcessingInterface(std::string interface_name)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(1),std::string("BeginProcessingInterface: ")),interface_name));
}

void PHPTranspiler::ProcessInterfaceFunctionDeclaration(std::string return_type, std::string function_name, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    this->logger->WriteLine(Concat(Concat(Concat(Concat(this->string_helper->Indentation(2),std::string("ProcessInterfaceFunctionDeclaration: ")),return_type),std::string(" ")),function_name));
}

void PHPTranspiler::FinishProcessingInterface(std::string interface_name)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(1),std::string("FinishProcessingInterface: ")),interface_name));
}

void PHPTranspiler::BeginProcessingClass(std::string class_name, std::string implementing)
{
    this->logger->WriteLine(Concat(Concat(Concat(Concat(this->string_helper->Indentation(1),std::string("BeginProcessingClass: ")),class_name),std::string(" ")),implementing));
}

void PHPTranspiler::BeginProcessingClassFunctionDefinition(std::string return_type, std::string function_name, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    this->logger->WriteLine(Concat(Concat(Concat(Concat(this->string_helper->Indentation(2),std::string("BeginProcessingClassFunctionDefinition: ")),return_type),std::string(" ")),function_name));
}

void PHPTranspiler::BeginProcessCodeBlock(int indent)
{
    this->logger->WriteLine(Concat(this->string_helper->Indentation(indent),std::string("BeginProcessCodeBlock")));
}

void PHPTranspiler::FinishProcessCodeBlock(int indent)
{
    this->logger->WriteLine(Concat(this->string_helper->Indentation(indent),std::string("FinishProcessCodeBlock")));
}

void PHPTranspiler::BeginProcessConditional(int indent, std::string r_value)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(indent),std::string("BeginProcessConditional: ")),r_value));
}

void PHPTranspiler::ProcessElse(int indent)
{
    this->logger->WriteLine(Concat(this->string_helper->Indentation(indent),std::string("ProcessElse")));
}

void PHPTranspiler::FinishProcessConditional(int indent, std::string r_value)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(indent),std::string("FinishProcessConditional: ")),r_value));
}

void PHPTranspiler::BeginProcessLoop(int indent, std::string r_value)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(indent),std::string("BeginProcessLoop: ")),r_value));
}

void PHPTranspiler::FinishProcessLoop(int indent, std::string r_value)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(indent),std::string("FinishProcessLoop: ")),r_value));
}

void PHPTranspiler::ProcessRtn(int indent, std::string r_value)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(indent),std::string("ProcessRtn: ")),r_value));
}

void PHPTranspiler::ProcessDeclaration(int indent, std::string type, std::string l_value, std::string r_value)
{
    this->logger->WriteLine(Concat(Concat(Concat(Concat(Concat(Concat(this->string_helper->Indentation(indent),std::string("ProcessDeclaration: ")),type),std::string(" ")),l_value),std::string(" ")),r_value));
}

void PHPTranspiler::ProcessAssignment(int indent, std::string l_value, std::string r_value)
{
    this->logger->WriteLine(Concat(Concat(Concat(Concat(this->string_helper->Indentation(indent),std::string("ProcessAssignment: ")),l_value),std::string(" ")),r_value));
}

void PHPTranspiler::ProcessCall(int indent, std::string call)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(indent),std::string("ProcessCall: ")),call));
}

void PHPTranspiler::FinishProcessingClassFunctionDefinition(std::string return_type, std::string function_name, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    this->logger->WriteLine(Concat(Concat(Concat(Concat(this->string_helper->Indentation(2),std::string("FinishProcessingClassFunctionDefinition: ")),return_type),std::string(" ")),function_name));
}

void PHPTranspiler::ProcessClassMemberDeclaration(std::string member_type, std::string member_name)
{
    this->logger->WriteLine(Concat(Concat(Concat(Concat(this->string_helper->Indentation(2),std::string("ProcessClassMemberDeclaration: ")),member_type),std::string(" ")),member_name));
}

void PHPTranspiler::FinishProcessingClass(std::string class_name, std::string implementing)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(1),std::string("FinishProcessingClass: ")),class_name));
}


};
};
};
};
};
