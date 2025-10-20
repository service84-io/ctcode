#include "S84.CTCode.Transpiler.LogToConsole.ctcode.hpp"

namespace s84 {
namespace ctcode {
namespace transpiler {
namespace logtoconsole {
namespace ctcode {

LogToConsole::LogToConsole()
{
    this->system = NULL;
    this->c_t_code_file = NULL;
    this->base_name = "";
    this->logger = NULL;
    this->string_helper = NULL;
}

void LogToConsole::Initialize()
{
    this->string_helper = std::shared_ptr<s84::ctcode::transpiler::stringhelper::ctcode::StringHelper>(new s84::ctcode::transpiler::stringhelper::ctcode::StringHelper());
}

void LogToConsole::SetSystem(OmniPointer<s84::ctcode::system::ctcode::System> system)
{
    this->system = system;
}

void LogToConsole::SetCTCodeFile(OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file)
{
    this->c_t_code_file = c_t_code_file;
}

void LogToConsole::SetBaseName(std::string base_name)
{
    this->base_name = base_name;
}

void LogToConsole::SetLogger(OmniPointer<s84::ctcode::system::ctcode::OutputStream> logger)
{
    this->logger = logger;
}

int LogToConsole::GetBaseIndentation()
{
    return 3;
}

std::string LogToConsole::GetCallName(std::string name)
{
    std::string value = this->string_helper->SnakeCaseToCamelCase(name);
    if (this->string_helper->IsReserved(value))
    {
        return Concat(std::string("ReservedPrefix"),value);
    }
    return value;
}

std::string LogToConsole::GetVariableName(std::string name)
{
    std::string value = this->string_helper->CamelCaseToSnakeCase(name);
    if (value==std::string("myself"))
    {
        return std::string("thyself");
    }
    if (value==std::string("nothing"))
    {
        return std::string("NoBaDe");
    }
    if (this->string_helper->IsReserved(value))
    {
        return Concat(std::string("reserved_prefix_"),value);
    }
    return value;
}

std::string LogToConsole::GetVariableChain(std::vector<std::string> name_parts)
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

std::string LogToConsole::ConvertCall(std::vector<std::string> name_chain, std::vector<std::string> parameters)
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

std::string LogToConsole::ConvertAllocate(std::string type)
{
    return Concat(std::string("new "),type);
}

std::string LogToConsole::ConvertByte(std::string high, std::string low)
{
    return Concat(Concat(std::string("0x"),high),low);
}

std::string LogToConsole::ConvertDecimal(std::string reserved_prefix_decimal)
{
    return reserved_prefix_decimal;
}

std::string LogToConsole::ConvertNumber(std::string number)
{
    return number;
}

std::string LogToConsole::ConvertBoolean(std::string reserved_prefix_boolean)
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

std::string LogToConsole::ConvertVariable(std::string variable)
{
    return variable;
}

std::string LogToConsole::ConvertString(std::string literal)
{
    return Concat(Concat(std::string("\""),literal),std::string("\""));
}

std::string LogToConsole::UnaryOperator(std::string op, std::string r_value)
{
    if (op==std::string("!"))
    {
        return Concat(std::string("!"),r_value);
    }
    return r_value;
}

std::string LogToConsole::BinaryOperator(std::string op, std::string r_value_l, std::string r_value_r)
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

std::string LogToConsole::GetTypeName(std::string name)
{
    std::string value = this->string_helper->SnakeCaseToCamelCase(name);
    if (this->string_helper->IsReserved(value))
    {
        return Concat(std::string("ReservedPrefix"),value);
    }
    return value;
}

std::string LogToConsole::GetDimensionalType(std::string singleton_type, int dimensions)
{
    std::string result = singleton_type;
    while (dimensions>0)
    {
        result = Concat(result,std::string("[]"));
        dimensions = dimensions-1;
    }
    return result;
}

std::string LogToConsole::GetMapType(std::string singleton_type)
{
    return Concat(singleton_type,std::string("{}"));
}

std::string LogToConsole::GetPrimativeType(std::string c_t_type)
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

std::string LogToConsole::GetDefinedType(std::string c_t_type)
{
    return c_t_type;
}

std::string LogToConsole::GetQualifiedTypeName(std::vector<std::string> name_parts)
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

void LogToConsole::BeginProcessingCTCodeFile()
{
    this->logger->WriteLine(std::string("BeginProcessingCTCodeFile"));
}

void LogToConsole::FinishProcessingCTCodeFile()
{
    this->logger->WriteLine(std::string("FinishProcessingCTCodeFile"));
}

void LogToConsole::ProcessExdef(std::string exdef)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(1),std::string("ProcessExdef: ")),exdef));
}

void LogToConsole::ProcessUnmanagedType(std::string unmanaged_type)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(1),std::string("ProcessUnmanagedType: ")),unmanaged_type));
}

void LogToConsole::BeginProcessingInterface(std::string interface_name)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(1),std::string("BeginProcessingInterface: ")),interface_name));
}

void LogToConsole::ProcessInterfaceFunctionDeclaration(std::string return_type, std::string function_name, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    this->logger->WriteLine(Concat(Concat(Concat(Concat(this->string_helper->Indentation(2),std::string("ProcessInterfaceFunctionDeclaration: ")),return_type),std::string(" ")),function_name));
}

void LogToConsole::FinishProcessingInterface(std::string interface_name)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(1),std::string("FinishProcessingInterface: ")),interface_name));
}

void LogToConsole::BeginProcessingClass(std::string class_name, std::string implementing)
{
    this->logger->WriteLine(Concat(Concat(Concat(Concat(this->string_helper->Indentation(1),std::string("BeginProcessingClass: ")),class_name),std::string(" ")),implementing));
}

void LogToConsole::BeginProcessingClassFunctionDefinition(std::string return_type, std::string function_name, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    this->logger->WriteLine(Concat(Concat(Concat(Concat(this->string_helper->Indentation(2),std::string("BeginProcessingClassFunctionDefinition: ")),return_type),std::string(" ")),function_name));
}

void LogToConsole::BeginProcessCodeBlock(int indent)
{
    this->logger->WriteLine(Concat(this->string_helper->Indentation(indent),std::string("BeginProcessCodeBlock")));
}

void LogToConsole::FinishProcessCodeBlock(int indent)
{
    this->logger->WriteLine(Concat(this->string_helper->Indentation(indent),std::string("FinishProcessCodeBlock")));
}

void LogToConsole::BeginProcessConditional(int indent, std::string r_value)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(indent),std::string("BeginProcessConditional: ")),r_value));
}

void LogToConsole::ProcessElse(int indent)
{
    this->logger->WriteLine(Concat(this->string_helper->Indentation(indent),std::string("ProcessElse")));
}

void LogToConsole::FinishProcessConditional(int indent, std::string r_value)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(indent),std::string("FinishProcessConditional: ")),r_value));
}

void LogToConsole::BeginProcessLoop(int indent, std::string r_value)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(indent),std::string("BeginProcessLoop: ")),r_value));
}

void LogToConsole::FinishProcessLoop(int indent, std::string r_value)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(indent),std::string("FinishProcessLoop: ")),r_value));
}

void LogToConsole::ProcessRtn(int indent, std::string r_value)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(indent),std::string("ProcessRtn: ")),r_value));
}

void LogToConsole::ProcessDeclaration(int indent, std::string type, std::string l_value, std::string r_value)
{
    this->logger->WriteLine(Concat(Concat(Concat(Concat(Concat(Concat(this->string_helper->Indentation(indent),std::string("ProcessDeclaration: ")),type),std::string(" ")),l_value),std::string(" ")),r_value));
}

void LogToConsole::ProcessAssignment(int indent, std::string l_value, std::string r_value)
{
    this->logger->WriteLine(Concat(Concat(Concat(Concat(this->string_helper->Indentation(indent),std::string("ProcessAssignment: ")),l_value),std::string(" ")),r_value));
}

void LogToConsole::ProcessCall(int indent, std::string call)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(indent),std::string("ProcessCall: ")),call));
}

void LogToConsole::FinishProcessingClassFunctionDefinition(std::string return_type, std::string function_name, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    this->logger->WriteLine(Concat(Concat(Concat(Concat(this->string_helper->Indentation(2),std::string("FinishProcessingClassFunctionDefinition: ")),return_type),std::string(" ")),function_name));
}

void LogToConsole::ProcessClassMemberDeclaration(std::string member_type, std::string member_name)
{
    this->logger->WriteLine(Concat(Concat(Concat(Concat(this->string_helper->Indentation(2),std::string("ProcessClassMemberDeclaration: ")),member_type),std::string(" ")),member_name));
}

void LogToConsole::FinishProcessingClass(std::string class_name, std::string implementing)
{
    this->logger->WriteLine(Concat(Concat(this->string_helper->Indentation(1),std::string("FinishProcessingClass: ")),class_name));
}


};
};
};
};
};
