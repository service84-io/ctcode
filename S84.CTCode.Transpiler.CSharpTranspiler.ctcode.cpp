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
    return 3;
}

std::string CSharpTranspiler::GetCallName(std::string name)
{
    return this->string_helper->SnakeCaseToCamelCase(name);
}

std::string CSharpTranspiler::GetVariableName(std::string name)
{
    std::string value = this->string_helper->CamelCaseToSnakeCase(name);
    if (value==std::string("myself"))
    {
        return std::string("thyself");
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

std::string CSharpTranspiler::ConvertAllocate(std::string type)
{
    return Concat(std::string("new "),type);
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
    return variable;
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
        return Concat(Concat(r_value_l,std::string("||")),r_value_r);
    }
    if (op==std::string("&&"))
    {
        return Concat(Concat(r_value_l,std::string("&&")),r_value_r);
    }
    return std::string("");
}

std::string CSharpTranspiler::GetTypeName(std::string name)
{
    if (name!=std::string(""))
    {
        return this->string_helper->SnakeCaseToCamelCase(name);
    }
    else
    {
        return std::string("");
    }
}

std::string CSharpTranspiler::GetDimensionalType(std::string singleton_type, int dimensions)
{
    std::string result = singleton_type;
    while (dimensions>0)
    {
        result = Concat(result,std::string("[]"));
        dimensions = dimensions-1;
    }
    return result;
}

std::string CSharpTranspiler::GetMapType(std::string singleton_type)
{
    return Concat(singleton_type,std::string("{}"));
}

std::string CSharpTranspiler::GetPrimativeType(std::string c_t_type)
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

std::string CSharpTranspiler::GetDefinedType(std::string c_t_type)
{
    return c_t_type;
}

std::string CSharpTranspiler::GetQualifiedTypeName(std::vector<std::string> name_parts)
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

void CSharpTranspiler::BeginProcessingCTCodeFile()
{
    this->logger->WriteLine(std::string("BeginProcessingCTCodeFile"));
}

void CSharpTranspiler::FinishProcessingCTCodeFile()
{
    this->logger->WriteLine(std::string("FinishProcessingCTCodeFile"));
}

void CSharpTranspiler::ProcessExdef(std::string exdef)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(1),std::string("ProcessExdef: ")),exdef));
}

void CSharpTranspiler::ProcessUnmanagedType(std::string unmanaged_type)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(1),std::string("ProcessUnmanagedType: ")),unmanaged_type));
}

void CSharpTranspiler::BeginProcessingInterface(std::string interface_name)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(1),std::string("BeginProcessingInterface: ")),interface_name));
}

void CSharpTranspiler::ProcessInterfaceFunctionDeclaration(std::string return_type, std::string function_name, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    this->logger->WriteLine(Concat(Concat(Concat(Concat(this->string_helper->Indentation(2),std::string("ProcessInterfaceFunctionDeclaration: ")),return_type),std::string(" ")),function_name));
}

void CSharpTranspiler::FinishProcessingInterface(std::string interface_name)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(1),std::string("FinishProcessingInterface: ")),interface_name));
}

void CSharpTranspiler::BeginProcessingClass(std::string class_name, std::string implementing)
{
    this->logger->WriteLine(Concat(Concat(Concat(Concat(this->string_helper->Indentation(1),std::string("BeginProcessingClass: ")),class_name),std::string(" ")),implementing));
}

void CSharpTranspiler::BeginProcessingClassFunctionDefinition(std::string return_type, std::string function_name, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    this->logger->WriteLine(Concat(Concat(Concat(Concat(this->string_helper->Indentation(2),std::string("BeginProcessingClassFunctionDefinition: ")),return_type),std::string(" ")),function_name));
}

void CSharpTranspiler::BeginProcessCodeBlock(int indent)
{
    this->logger->WriteLine(Concat(this->string_helper->Indentation(indent),std::string("BeginProcessCodeBlock")));
}

void CSharpTranspiler::FinishProcessCodeBlock(int indent)
{
    this->logger->WriteLine(Concat(this->string_helper->Indentation(indent),std::string("FinishProcessCodeBlock")));
}

void CSharpTranspiler::BeginProcessConditional(int indent, std::string r_value)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(indent),std::string("BeginProcessConditional: ")),r_value));
}

void CSharpTranspiler::ProcessElse(int indent)
{
    this->logger->WriteLine(Concat(this->string_helper->Indentation(indent),std::string("ProcessElse")));
}

void CSharpTranspiler::FinishProcessConditional(int indent, std::string r_value)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(indent),std::string("FinishProcessConditional: ")),r_value));
}

void CSharpTranspiler::BeginProcessLoop(int indent, std::string r_value)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(indent),std::string("BeginProcessLoop: ")),r_value));
}

void CSharpTranspiler::FinishProcessLoop(int indent, std::string r_value)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(indent),std::string("FinishProcessLoop: ")),r_value));
}

void CSharpTranspiler::ProcessRtn(int indent, std::string r_value)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(indent),std::string("ProcessRtn: ")),r_value));
}

void CSharpTranspiler::ProcessDeclaration(int indent, std::string type, std::string l_value, std::string r_value)
{
    this->logger->WriteLine(Concat(Concat(Concat(Concat(Concat(Concat(this->string_helper->Indentation(indent),std::string("ProcessDeclaration: ")),type),std::string(" ")),l_value),std::string(" ")),r_value));
}

void CSharpTranspiler::ProcessAssignment(int indent, std::string l_value, std::string r_value)
{
    this->logger->WriteLine(Concat(Concat(Concat(Concat(this->string_helper->Indentation(indent),std::string("ProcessAssignment: ")),l_value),std::string(" ")),r_value));
}

void CSharpTranspiler::ProcessCall(int indent, std::string call)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(indent),std::string("ProcessCall: ")),call));
}

void CSharpTranspiler::FinishProcessingClassFunctionDefinition(std::string return_type, std::string function_name, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    this->logger->WriteLine(Concat(Concat(Concat(Concat(this->string_helper->Indentation(2),std::string("FinishProcessingClassFunctionDefinition: ")),return_type),std::string(" ")),function_name));
}

void CSharpTranspiler::ProcessClassMemberDeclaration(std::string member_type, std::string member_name)
{
    this->logger->WriteLine(Concat(Concat(Concat(Concat(this->string_helper->Indentation(2),std::string("ProcessClassMemberDeclaration: ")),member_type),std::string(" ")),member_name));
}

void CSharpTranspiler::FinishProcessingClass(std::string class_name, std::string implementing)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(1),std::string("FinishProcessingClass: ")),class_name));
}


};
};
};
};
};
