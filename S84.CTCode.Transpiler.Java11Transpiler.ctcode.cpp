#include "S84.CTCode.Transpiler.Java11Transpiler.ctcode.hpp"

namespace s84 {
namespace ctcode {
namespace transpiler {
namespace java11transpiler {
namespace ctcode {

ParameterDeclaration::ParameterDeclaration()
{
    this->type = "";
    this->name = "";
}

std::string ParameterDeclaration::GetType()
{
    return this->type;
}

void ParameterDeclaration::SetType(std::string input)
{
    this->type = input;
}

std::string ParameterDeclaration::GetName()
{
    return this->name;
}

void ParameterDeclaration::SetName(std::string input)
{
    this->name = input;
}

IntegerReference::IntegerReference()
{
    this->value = 0;
}

int IntegerReference::GetValue()
{
    return this->value;
}

void IntegerReference::SetValue(int value)
{
    this->value = value;
}

Java11Transpiler::Java11Transpiler()
{
    this->system = NULL;
    this->c_t_code_file = NULL;
    this->base_name = "";
    /*this->operator_precedent = NO_DEFAULT;*/
    this->logger = NULL;
    /*this->imports = NO_DEFAULT;*/
    this->current_interface = "";
    /*this->interface_definition = NO_DEFAULT;*/
    this->current_class = "";
    /*this->class_definition = NO_DEFAULT;*/
    /*this->class_init = NO_DEFAULT;*/
    /*this->class_members = NO_DEFAULT;*/
}

int Java11Transpiler::GetBaseIndentation()
{
    return 1;
}

std::string Java11Transpiler::GetCallName(OmniPointer<s84::ctcode::dbnf::ctcode::Name> name)
{
    if (name)
    {
        return this->SnakeCaseToCamelCase(name->UnParse());
    }
    else
    {
        return std::string("");
    }
}

bool Java11Transpiler::IsReserved(std::string name)
{
    return false||this->BeginsWith(std::string("reserved_prefix_"),name)||name==std::string("boolean")||name==std::string("float");
}

std::string Java11Transpiler::GetVariableName(OmniPointer<s84::ctcode::dbnf::ctcode::Name> name)
{
    if (name)
    {
        std::string value = this->CamelCaseToSnakeCase(name->UnParse());
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
    else
    {
        return std::string("");
    }
}

std::string Java11Transpiler::GetVariableChainNameTail(OmniPointer<s84::ctcode::dbnf::ctcode::NameTail> tail)
{
    std::string accessor = std::string(".");
    if (tail)
    {
        return Concat(Concat(accessor,this->GetVariableName(tail->GetName())),this->GetVariableChainNameTail(tail->GetTail()));
    }
    else
    {
        return std::string("");
    }
}

std::string Java11Transpiler::GetVariableChain(OmniPointer<s84::ctcode::dbnf::ctcode::QualfiedName> l_value)
{
    if (l_value)
    {
        return Concat(this->GetVariableName(l_value->GetName()),this->GetVariableChainNameTail(l_value->GetTail()));
    }
    else
    {
        return std::string("");
    }
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

std::string Java11Transpiler::GetTypeName(OmniPointer<s84::ctcode::dbnf::ctcode::Name> name)
{
    if (name)
    {
        return this->SnakeCaseToCamelCase(name->UnParse());
    }
    else
    {
        return std::string("");
    }
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

std::string Java11Transpiler::GetQualifiedTypeName(std::vector<OmniPointer<s84::ctcode::dbnf::ctcode::Name>> name_parts)
{
    std::string delimiter = std::string(".");
    int name_parts_index = Size(name_parts)-1;
    int last_package_index = Size(name_parts)-2;
    OmniPointer<s84::ctcode::dbnf::ctcode::Name> type_part = Element(name_parts,name_parts_index);
    std::string result = this->GetTypeName(type_part);
    if (name_parts_index>0)
    {
        result = Concat(delimiter,result);
        while (name_parts_index>0)
        {
            name_parts_index = name_parts_index-1;
            OmniPointer<s84::ctcode::dbnf::ctcode::Name> name_part = Element(name_parts,name_parts_index);
            if (name_parts_index!=last_package_index)
            {
                result = Concat(delimiter,result);
            }
            result = Concat(this->ToLower(name_part->UnParse()),result);
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
    Append(this->imports,Concat(Concat(std::string("import "),this->ToLower(exdef)),std::string(".*;")));
}

void Java11Transpiler::ProcessUnmanagedType(std::string unmanaged_type)
{
    int noop = 0;
}

void Java11Transpiler::BeginProcessingInterface(std::string interface_name)
{
    ClearList(this->interface_definition);
    this->current_interface = interface_name;
}

void Java11Transpiler::ProcessInterfaceFunctionDeclaration(std::string return_type, std::string function_name, std::vector<OmniPointer<ParameterDeclaration>> parameters)
{
    Append(this->interface_definition,Concat(Concat(Concat(Concat(Concat(this->Indentation(1),return_type),std::string(" ")),function_name),this->MakeParametersString(parameters)),std::string(";")));
}

void Java11Transpiler::FinishProcessingInterface(std::string interface_name)
{
    OmniPointer<s84::ctcode::system::ctcode::OutputStream> destination = this->system->OpenFileWriter(Concat(Concat(Concat(this->DotToSlash(this->ToLower(this->base_name)),std::string("/")),this->current_interface),std::string(".java")));
    destination->WriteLine(Concat(Concat(std::string("package "),this->ToLower(this->base_name)),std::string(";")));
    destination->WriteLine(std::string(""));
    if (Size(this->imports)>0)
    {
        this->WriteLines(destination,this->imports);
        destination->WriteLine(std::string(""));
    }
    destination->WriteLine(Concat(Concat(std::string("public interface "),interface_name),std::string(" {")));
    this->WriteLines(destination,this->interface_definition);
    destination->WriteLine(std::string("}"));
    this->current_interface = std::string("");
}

void Java11Transpiler::BeginProcessingClass(std::string class_name, std::string implementing)
{
    ClearList(this->class_definition);
    ClearList(this->class_init);
    ClearList(this->class_members);
    this->current_class = class_name;
    Append(this->class_init,Concat(Concat(Concat(this->Indentation(1),std::string("public ")),class_name),std::string("()")));
    Append(this->class_init,Concat(this->Indentation(1),std::string("{")));
}

void Java11Transpiler::BeginProcessingClassFunctionDefinition(std::string return_type, std::string function_name, std::vector<OmniPointer<ParameterDeclaration>> parameters)
{
    Append(this->class_definition,Concat(Concat(Concat(Concat(Concat(this->Indentation(1),std::string("public ")),return_type),std::string(" ")),function_name),this->MakeParametersString(parameters)));
}

void Java11Transpiler::BeginProcessCodeBlock(int indent)
{
    Append(this->class_definition,Concat(this->Indentation(indent),std::string("{")));
}

void Java11Transpiler::FinishProcessCodeBlock(int indent)
{
    Append(this->class_definition,Concat(this->Indentation(indent),std::string("}")));
}

void Java11Transpiler::BeginProcessConditional(int indent, std::string r_value)
{
    Append(this->class_definition,Concat(Concat(Concat(this->Indentation(indent),std::string("if (AsBoolean(")),r_value),std::string("))")));
}

void Java11Transpiler::ProcessElse(int indent)
{
    Append(this->class_definition,Concat(this->Indentation(indent),std::string("else")));
}

void Java11Transpiler::FinishProcessConditional(int indent, std::string r_value)
{
    int noop = 0;
}

void Java11Transpiler::BeginProcessLoop(int indent, std::string r_value)
{
    Append(this->class_definition,Concat(Concat(Concat(this->Indentation(indent),std::string("while (AsBoolean(")),r_value),std::string("))")));
}

void Java11Transpiler::FinishProcessLoop(int indent, std::string r_value)
{
    int noop = 0;
}

void Java11Transpiler::ProcessRtn(int indent, std::string r_value)
{
    Append(this->class_definition,Concat(Concat(Concat(this->Indentation(indent),std::string("return ")),r_value),std::string(";")));
}

void Java11Transpiler::ProcessDeclaration(int indent, std::string type, std::string l_value, std::string r_value)
{
    if (r_value==std::string(""))
    {
        r_value = this->GetDefault(type);
    }
    Append(this->class_definition,Concat(Concat(Concat(Concat(Concat(Concat(this->Indentation(indent),type),std::string(" ")),l_value),std::string(" = ")),r_value),std::string(";")));
}

void Java11Transpiler::ProcessAssignment(int indent, std::string l_value, std::string r_value)
{
    Append(this->class_definition,Concat(Concat(Concat(Concat(this->Indentation(indent),l_value),std::string(" = ")),r_value),std::string(";")));
}

void Java11Transpiler::ProcessCall(int indent, std::string call)
{
    Append(this->class_definition,Concat(Concat(this->Indentation(indent),call),std::string(";")));
}

void Java11Transpiler::FinishProcessingClassFunctionDefinition(std::string return_type, std::string function_name, std::vector<OmniPointer<ParameterDeclaration>> parameters)
{
    Append(this->class_definition,std::string(""));
}

void Java11Transpiler::ProcessClassMemberDeclaration(std::string member_type, std::string member_name)
{
    Append(this->class_init,Concat(Concat(Concat(Concat(Concat(this->Indentation(2),std::string("this.")),member_name),std::string(" = ")),this->GetDefault(member_type)),std::string(";")));
    Append(this->class_members,Concat(Concat(Concat(Concat(Concat(this->Indentation(1),std::string("private ")),member_type),std::string(" ")),member_name),std::string(";")));
}

std::string Java11Transpiler::DotToSlash(std::string input)
{
    std::string result = std::string("");
    int input_index = 0;
    while (input_index<Length(input))
    {
        std::string character = At(input,input_index);
        if (character==std::string("."))
        {
            result = Concat(result,std::string("/"));
        }
        else
        {
            result = Concat(result,character);
        }
        input_index = input_index+1;
    }
    return result;
}

void Java11Transpiler::FinishProcessingClass(std::string class_name, std::string implementing)
{
    OmniPointer<s84::ctcode::system::ctcode::OutputStream> destination = this->system->OpenFileWriter(Concat(Concat(Concat(this->DotToSlash(this->ToLower(this->base_name)),std::string("/")),this->current_class),std::string(".java")));
    destination->WriteLine(Concat(Concat(std::string("package "),this->ToLower(this->base_name)),std::string(";")));
    destination->WriteLine(std::string(""));
    if (Size(this->imports)>0)
    {
        this->WriteLines(destination,this->imports);
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
    this->WriteLines(destination,this->class_init);
    destination->WriteLine(Concat(this->Indentation(1),std::string("}")));
    destination->WriteLine(std::string(""));
    this->WriteLines(destination,this->class_definition);
    if (Size(this->class_members)>0)
    {
        this->WriteLines(destination,this->class_members);
        destination->WriteLine(std::string(""));
    }
    this->WriteCommonFunctions(destination);
    destination->WriteLine(std::string("}"));
    this->current_class = std::string("");
}

void Java11Transpiler::WriteCommonFunctions(OmniPointer<s84::ctcode::system::ctcode::OutputStream> destination_file)
{
    destination_file->WriteLine(Concat(this->Indentation(1),std::string("private static <T> void ClearList(java.util.ArrayList<T> input) { input.clear(); }")));
    destination_file->WriteLine(Concat(this->Indentation(1),std::string("private static <T> int Size(java.util.ArrayList<T> input) { return input.size(); }")));
    destination_file->WriteLine(Concat(this->Indentation(1),std::string("private static <T> T Element(java.util.ArrayList<T> input, int element) { return input.get(element); }")));
    destination_file->WriteLine(Concat(this->Indentation(1),std::string("private static <T> void Append(java.util.ArrayList<T> input, T element) { input.add(element); }")));
    destination_file->WriteLine(Concat(this->Indentation(1),std::string("private static <T> void ClearMap(java.util.HashMap<java.lang.String, T> input) { input.clear(); }")));
    destination_file->WriteLine(Concat(this->Indentation(1),std::string("private static <T> void SetKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key, T element) { input.put(key, element); }")));
    destination_file->WriteLine(Concat(this->Indentation(1),std::string("private static <T> java.util.ArrayList<java.lang.String> Keys(java.util.HashMap<java.lang.String, T> input) { return new java.util.ArrayList<>(input.keySet()); }")));
    destination_file->WriteLine(Concat(this->Indentation(1),std::string("private static <T> boolean HasKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key) { return input.containsKey(key); }")));
    destination_file->WriteLine(Concat(this->Indentation(1),std::string("private static <T> T GetKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key) { return input.get(key); }")));
    destination_file->WriteLine(Concat(this->Indentation(1),std::string("private static int Length(java.lang.String input) { return input.length(); }")));
    destination_file->WriteLine(Concat(this->Indentation(1),std::string("private static java.lang.String At(java.lang.String input, int index) { try { return input.substring(index, index + 1);} catch(Exception e) { return \"\"; }}")));
    destination_file->WriteLine(Concat(this->Indentation(1),std::string("private static int IntAt(java.lang.String input, int index) { return (int)input.charAt(index); }")));
    destination_file->WriteLine(Concat(this->Indentation(1),std::string("private static java.lang.String Concat(java.lang.String left, java.lang.String right) { return left + right; }")));
    destination_file->WriteLine(Concat(this->Indentation(1),std::string("private static <T extends Object> boolean AsBoolean(T value) { return value != null; }")));
    destination_file->WriteLine(Concat(this->Indentation(1),std::string("private static boolean AsBoolean(boolean value) { return value; }")));
    destination_file->WriteLine(Concat(this->Indentation(1),std::string("private static boolean Equals(java.lang.String left, java.lang.String right) { return left.equals(right); }")));
    destination_file->WriteLine(Concat(this->Indentation(1),std::string("private static boolean Equals(boolean left, boolean right) { return left == right; }")));
    destination_file->WriteLine(Concat(this->Indentation(1),std::string("private static boolean Equals(int left, int right) { return left == right; }")));
    destination_file->WriteLine(Concat(this->Indentation(1),std::string("private static boolean Equals(float left, float right) { return left == right; }")));
}

void Java11Transpiler::FinishProcessingCTCodeFile()
{
    if (false)
    {
        std::string destination_file_name = Concat(this->StripDot(this->base_name),std::string(".py"));
        OmniPointer<s84::ctcode::system::ctcode::OutputStream> destination_file = this->system->OpenFileWriter(destination_file_name);
        if (Size(this->imports)>0)
        {
            this->WriteLines(destination_file,this->imports);
            destination_file->WriteLine(std::string(""));
        }
        this->WriteCommonFunctions(destination_file);
        destination_file->WriteLine(std::string(""));
        this->WriteLines(destination_file,this->interface_definition);
        this->WriteLines(destination_file,this->class_definition);
    }
}

bool Java11Transpiler::BeginsWith(std::string prefix, std::string value)
{
    if (Length(prefix)>Length(value))
    {
        return false;
    }
    int prefix_index = 0;
    while (prefix_index<Length(prefix))
    {
        if (At(prefix,prefix_index)!=At(value,prefix_index))
        {
            return false;
        }
        prefix_index = prefix_index+1;
    }
    return true;
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
    if (this->BeginsWith(std::string("java.util.HashMap<java.lang.String"),java_type))
    {
        return std::string("new java.util.HashMap<>()");
    }
    if (this->BeginsWith(std::string("java.util.ArrayList<"),java_type))
    {
        return std::string("new java.util.ArrayList<>()");
    }
    return std::string("null");
}

std::string Java11Transpiler::MakeParametersString(std::vector<OmniPointer<ParameterDeclaration>> parameters)
{
    std::string result = std::string("(");
    int parameters_index = 0;
    while (parameters_index<Size(parameters))
    {
        OmniPointer<ParameterDeclaration> parameter = Element(parameters,parameters_index);
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

std::string Java11Transpiler::StripDot(std::string input)
{
    int index = 0;
    index = 0;
    std::string result = "";
    result = std::string("");
    while (index<Length(input))
    {
        std::string character = "";
        character = At(input,index);
        if (character==std::string("."))
        {
            result = Concat(result,std::string("_"));
        }
        else
        {
            result = Concat(result,character);
        }
        index = index+1;
    }
    return result;
}

void Java11Transpiler::WriteLines(OmniPointer<s84::ctcode::system::ctcode::OutputStream> destination, std::vector<std::string> lines)
{
    int lines_index = 0;
    while (lines_index<Size(lines))
    {
        std::string line = Element(lines,lines_index);
        destination->WriteLine(line);
        lines_index = lines_index+1;
    }
}

int Java11Transpiler::Transpile(OmniPointer<s84::ctcode::system::ctcode::System> system, OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file, std::string base_name)
{
    ClearList(this->operator_precedent);
    this->PopulateOperatorPrecedent();
    this->system = system;
    this->c_t_code_file = c_t_code_file;
    this->base_name = base_name;
    this->logger = system->GetLoggerDestination();
    this->ProcessCTCodeFile(c_t_code_file);
    return 0;
}

void Java11Transpiler::ProcessCTCodeFile(OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file)
{
    this->BeginProcessingCTCodeFile();
    this->ProcessExdefs(c_t_code_file);
    this->ProcessUnmanagedTypes(c_t_code_file);
    this->ProcessDefinitions(c_t_code_file);
    this->FinishProcessingCTCodeFile();
}

void Java11Transpiler::ProcessExdefs(OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file)
{
    std::vector<OmniPointer<s84::ctcode::dbnf::ctcode::ExternalDefinition>> exdefs = c_t_code_file->GetDeclarations();
    int exdefs_index = 0;
    while (exdefs_index<Size(exdefs))
    {
        OmniPointer<s84::ctcode::dbnf::ctcode::ExternalDefinition> exdef = Element(exdefs,exdefs_index);
        OmniPointer<s84::ctcode::dbnf::ctcode::QualfiedName> exdef_name = exdef->GetExdef();
        this->ProcessExdef(exdef_name->UnParse());
        exdefs_index = exdefs_index+1;
    }
}

void Java11Transpiler::ProcessUnmanagedTypes(OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file)
{
    std::vector<OmniPointer<s84::ctcode::dbnf::ctcode::UnmanagedType>> unmanaged_types = c_t_code_file->GetUnmanagedTypes();
    int unmanaged_types_index = 0;
    while (unmanaged_types_index<Size(unmanaged_types))
    {
        OmniPointer<s84::ctcode::dbnf::ctcode::UnmanagedType> unmanaged_type = Element(unmanaged_types,unmanaged_types_index);
        this->ProcessUnmanagedType(this->GetQualifiedTypeNameInternal(unmanaged_type->GetUnmanagedType()));
        unmanaged_types_index = unmanaged_types_index+1;
    }
}

void Java11Transpiler::ProcessDefinitions(OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file)
{
    std::vector<OmniPointer<s84::ctcode::dbnf::ctcode::Definition>> definitions = c_t_code_file->GetDefinitions();
    int definitions_index = 0;
    while (definitions_index<Size(definitions))
    {
        OmniPointer<s84::ctcode::dbnf::ctcode::Definition> definition = NULL;
        definition = Element(definitions,definitions_index);
        if (definition->GetInterfaceDef())
        {
            this->ProcessInterfaceDefinition(definition->GetInterfaceDef());
        }
        if (definition->GetClassDef())
        {
            this->ProcessClassDefinition(definition->GetClassDef());
        }
        definitions_index = definitions_index+1;
    }
}

std::vector<OmniPointer<ParameterDeclaration>> Java11Transpiler::GetParameters(OmniPointer<s84::ctcode::dbnf::ctcode::ParameterListDef> parameter_list_def)
{
    std::vector<OmniPointer<ParameterDeclaration>> result;
    while (parameter_list_def)
    {
        OmniPointer<ParameterDeclaration> parameter = std::shared_ptr<ParameterDeclaration>(new ParameterDeclaration());
        parameter->SetType(this->GetType(parameter_list_def->GetType()));
        parameter->SetName(this->GetVariableName(parameter_list_def->GetName()));
        Append(result,parameter);
        parameter_list_def = parameter_list_def->GetParameterTail();
    }
    return result;
}

void Java11Transpiler::ProcessInterfaceDefinition(OmniPointer<s84::ctcode::dbnf::ctcode::InterfaceDef> interface_definition)
{
    std::string interface_name = this->GetTypeName(interface_definition->GetName());
    this->BeginProcessingInterface(interface_name);
    std::vector<OmniPointer<s84::ctcode::dbnf::ctcode::ContentDeclaration>> declarations = interface_definition->GetDeclarations();
    int declarations_index = 0;
    while (declarations_index<Size(declarations))
    {
        OmniPointer<s84::ctcode::dbnf::ctcode::ContentDeclaration> declaration = Element(declarations,declarations_index);
        std::string return_type = this->GetType(declaration->GetType());
        std::string function_name = this->GetCallName(declaration->GetName());
        std::vector<OmniPointer<ParameterDeclaration>> parameters = this->GetParameters(declaration->GetParameters());
        this->ProcessInterfaceFunctionDeclaration(return_type,function_name,parameters);
        declarations_index = declarations_index+1;
    }
    this->FinishProcessingInterface(interface_name);
}

void Java11Transpiler::ProcessClassDefinition(OmniPointer<s84::ctcode::dbnf::ctcode::ClassDef> class_definition)
{
    std::string class_name = this->GetTypeName(class_definition->GetName());
    std::string implementing = std::string("");
    OmniPointer<s84::ctcode::dbnf::ctcode::ImplementationSpec> implementation_spec = class_definition->GetImplementing();
    if (implementation_spec)
    {
        implementing = this->GetQualifiedTypeNameInternal(implementation_spec->GetInterface());
    }
    this->BeginProcessingClass(class_name,implementing);
    std::vector<OmniPointer<s84::ctcode::dbnf::ctcode::ContentDefinition>> definitions = class_definition->GetDefinitions();
    int definitions_index = 0;
    while (definitions_index<Size(definitions))
    {
        OmniPointer<s84::ctcode::dbnf::ctcode::ContentDefinition> definition = Element(definitions,definitions_index);
        if (definition->GetFunctionBody())
        {
            std::string return_type = this->GetType(definition->GetType());
            std::string function_name = this->GetCallName(definition->GetName());
            std::vector<OmniPointer<ParameterDeclaration>> parameters = this->GetParameters(definition->GetParameters());
            this->BeginProcessingClassFunctionDefinition(return_type,function_name,parameters);
            this->ProcessCodeBlockInternal(this->GetBaseIndentation(),definition->GetFunctionBody());
            this->FinishProcessingClassFunctionDefinition(return_type,function_name,parameters);
        }
        else
        {
            std::string member_type = this->GetType(definition->GetType());
            std::string member_name = this->GetVariableName(definition->GetName());
            this->ProcessClassMemberDeclaration(member_type,member_name);
        }
        definitions_index = definitions_index+1;
    }
    this->FinishProcessingClass(class_name,implementing);
}

void Java11Transpiler::ProcessInstructionInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::Instruction> instruction)
{
    if (instruction->GetCodeBlock())
    {
        this->ProcessCodeBlockInternal(indent,instruction->GetCodeBlock());
    }
    if (instruction->GetRtn())
    {
        this->ProcessRtnInternal(indent,instruction->GetRtn());
    }
    if (instruction->GetDeclaration())
    {
        this->ProcessDeclarationInternal(indent,instruction->GetDeclaration());
    }
    if (instruction->GetAssignment())
    {
        this->ProcessAssignmentInternal(indent,instruction->GetAssignment());
    }
    if (instruction->GetCall())
    {
        this->ProcessCallInternal(indent,instruction->GetCall());
    }
    if (instruction->GetConditional())
    {
        this->ProcessConditionalInternal(indent,instruction->GetConditional());
    }
    if (instruction->GetLoop())
    {
        this->ProcessLoopInternal(indent,instruction->GetLoop());
    }
}

void Java11Transpiler::ProcessCodeBlockInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::CodeBlock> code_block)
{
    this->BeginProcessCodeBlock(indent);
    std::vector<OmniPointer<s84::ctcode::dbnf::ctcode::Instruction>> instructions = code_block->GetInstructions();
    int instructions_index = 0;
    while (instructions_index<Size(instructions))
    {
        this->ProcessInstructionInternal(indent+1,Element(instructions,instructions_index));
        instructions_index = instructions_index+1;
    }
    this->FinishProcessCodeBlock(indent);
}

void Java11Transpiler::ProcessConditionalInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::Conditional> conditional)
{
    std::string r_value = this->GetRValueInternal(conditional->GetRValue());
    this->BeginProcessConditional(indent,r_value);
    this->ProcessCodeBlockInternal(indent,conditional->GetCodeBlock());
    if (conditional->GetElseTail())
    {
        OmniPointer<s84::ctcode::dbnf::ctcode::ElseTail> else_tail = conditional->GetElseTail();
        this->ProcessElse(indent);
        this->ProcessCodeBlockInternal(indent,else_tail->GetCodeBlock());
    }
    this->FinishProcessConditional(indent,r_value);
}

void Java11Transpiler::ProcessLoopInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::Loop> loop)
{
    std::string r_value = this->GetRValueInternal(loop->GetRValue());
    this->BeginProcessLoop(indent,r_value);
    this->ProcessCodeBlockInternal(indent,loop->GetCodeBlock());
    this->FinishProcessLoop(indent,r_value);
}

void Java11Transpiler::ProcessRtnInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::Return> rtn)
{
    std::string r_value = this->GetRValueInternal(rtn->GetRValue());
    this->ProcessRtn(indent,r_value);
}

void Java11Transpiler::ProcessDeclarationInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::Declaration> declaration)
{
    std::string type = this->GetType(declaration->GetType());
    std::string l_value = this->GetVariableName(declaration->GetName());
    std::string r_value = std::string("");
    OmniPointer<s84::ctcode::dbnf::ctcode::DeclarationAssign> declaration_assignment = declaration->GetAssignment();
    if (declaration_assignment)
    {
        r_value = this->GetRValueInternal(declaration_assignment->GetRValue());
    }
    this->ProcessDeclaration(indent,type,l_value,r_value);
}

void Java11Transpiler::ProcessAssignmentInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::Assignment> assignment)
{
    this->ProcessAssignment(indent,this->GetVariableChain(assignment->GetLValue()),this->GetRValueInternal(assignment->GetRValue()));
}

void Java11Transpiler::ProcessCallInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::Call> call)
{
    this->ProcessCall(indent,this->ConvertCallInternal(call));
}

std::string Java11Transpiler::ConvertCallInternal(OmniPointer<s84::ctcode::dbnf::ctcode::Call> call)
{
    std::vector<std::string> name_chain;
    std::vector<std::string> parameters;
    if (call->GetVariable())
    {
        Append(name_chain,this->GetVariableName(call->GetVariable()));
    }
    if (call->GetFunction())
    {
        Append(name_chain,this->GetCallName(call->GetFunction()));
    }
    if (call->GetFunctionChain())
    {
        OmniPointer<s84::ctcode::dbnf::ctcode::QualfiedName> function_chain = call->GetFunctionChain();
        OmniPointer<s84::ctcode::dbnf::ctcode::NameTail> name_tail = function_chain->GetTail();
        if (function_chain->GetTail())
        {
            Append(name_chain,this->GetVariableName(function_chain->GetName()));
        }
        else
        {
            Append(name_chain,this->GetCallName(function_chain->GetName()));
        }
        while (name_tail)
        {
            if (name_tail->GetTail())
            {
                Append(name_chain,this->GetVariableName(name_tail->GetName()));
            }
            else
            {
                Append(name_chain,this->GetCallName(name_tail->GetName()));
            }
            name_tail = name_tail->GetTail();
        }
    }
    OmniPointer<s84::ctcode::dbnf::ctcode::ParameterList> parameter_list = call->GetParameters();
    while (parameter_list)
    {
        Append(parameters,this->GetRValueInternal(parameter_list->GetRValue()));
        parameter_list = parameter_list->GetParameterTail();
    }
    return this->ConvertCall(name_chain,parameters);
}

std::string Java11Transpiler::GetSingletonType(OmniPointer<s84::ctcode::dbnf::ctcode::SingletonType> singleton_type)
{
    if (singleton_type->GetPrimativeType())
    {
        return this->GetPrimativeType(singleton_type->UnParse());
    }
    if (singleton_type->GetDefinedType())
    {
        OmniPointer<s84::ctcode::dbnf::ctcode::DefinedType> defined_type = singleton_type->GetDefinedType();
        return this->GetQualifiedTypeNameInternal(defined_type->GetName());
    }
    return std::string("");
}

std::string Java11Transpiler::GetRValueSingleBasisInternal(OmniPointer<s84::ctcode::dbnf::ctcode::RValueSingle> r_value_single)
{
    OmniPointer<s84::ctcode::dbnf::ctcode::Call> call = r_value_single->GetCall();
    if (call)
    {
        return this->ConvertCallInternal(call);
    }
    OmniPointer<s84::ctcode::dbnf::ctcode::Allocate> allocate = r_value_single->GetAllocate();
    if (allocate)
    {
        return this->ConvertAllocate(this->GetQualifiedTypeNameInternal(allocate->GetManagedType()));
    }
    OmniPointer<s84::ctcode::dbnf::ctcode::Byte> byte_literal = r_value_single->GetByteLiteral();
    if (byte_literal)
    {
        OmniPointer<s84::ctcode::dbnf::ctcode::ByteDigit> high = byte_literal->GetHigh();
        OmniPointer<s84::ctcode::dbnf::ctcode::ByteDigit> low = byte_literal->GetLow();
        return this->ConvertByte(high->UnParse(),low->UnParse());
    }
    OmniPointer<s84::ctcode::dbnf::ctcode::Decimal> decimal_literal = r_value_single->GetDecimalLiteral();
    if (decimal_literal)
    {
        return this->ConvertDecimal(decimal_literal->UnParse());
    }
    OmniPointer<s84::ctcode::dbnf::ctcode::Number> integer_literal = r_value_single->GetIntegerLiteral();
    if (integer_literal)
    {
        return this->ConvertNumber(integer_literal->UnParse());
    }
    OmniPointer<s84::ctcode::dbnf::ctcode::Boolean> boolean_literal = r_value_single->GetBooleanLiteral();
    if (boolean_literal)
    {
        return this->ConvertBoolean(boolean_literal->UnParse());
    }
    OmniPointer<s84::ctcode::dbnf::ctcode::QualfiedName> variable = r_value_single->GetVariable();
    if (variable)
    {
        return this->ConvertVariable(this->GetVariableChain(variable));
    }
    OmniPointer<s84::ctcode::dbnf::ctcode::Literal> string_literal = r_value_single->GetStringLiteral();
    if (string_literal)
    {
        return this->ConvertString(string_literal->UnParse());
    }
    return std::string("");
}

std::string Java11Transpiler::GetRValueSingleInternal(OmniPointer<s84::ctcode::dbnf::ctcode::RValueSingle> r_value_single)
{
    OmniPointer<s84::ctcode::dbnf::ctcode::UnaryOperator> unary_operator = r_value_single->GetUnaryOperator();
    if (unary_operator)
    {
        return this->UnaryOperator(unary_operator->UnParse(),this->GetRValueSingleBasisInternal(r_value_single));
    }
    return this->GetRValueSingleBasisInternal(r_value_single);
}

void Java11Transpiler::PopulateOperatorPrecedent()
{
    std::vector<std::string> precedent__0_operators;
    Append(precedent__0_operators,std::string("+"));
    Append(precedent__0_operators,std::string("-"));
    Append(this->operator_precedent,precedent__0_operators);
    std::vector<std::string> precedent__1_operators;
    Append(precedent__1_operators,std::string("<="));
    Append(precedent__1_operators,std::string(">="));
    Append(precedent__1_operators,std::string("=="));
    Append(precedent__1_operators,std::string("!="));
    Append(precedent__1_operators,std::string("<"));
    Append(precedent__1_operators,std::string(">"));
    Append(this->operator_precedent,precedent__1_operators);
    std::vector<std::string> precedent__2_operators;
    Append(precedent__2_operators,std::string("&&"));
    Append(this->operator_precedent,precedent__2_operators);
    std::vector<std::string> precedent__3_operators;
    Append(precedent__3_operators,std::string("||"));
    Append(this->operator_precedent,precedent__3_operators);
    std::vector<std::string> precedent__4_operators;
    Append(precedent__4_operators,std::string(""));
    Append(this->operator_precedent,precedent__4_operators);
}

bool Java11Transpiler::OverPrecedent(std::string op, int precedent)
{
    precedent = precedent+1;
    while (precedent<Size(this->operator_precedent))
    {
        std::vector<std::string> precedent_operators = Element(this->operator_precedent,precedent);
        int index = 0;
        while (index<Size(precedent_operators))
        {
            std::string checking_op = Element(precedent_operators,index);
            if (checking_op==op)
            {
                return true;
            }
            index = index+1;
        }
        precedent = precedent+1;
    }
    return false;
}

std::string Java11Transpiler::BinaryOperatorPrecedentMerge(std::vector<std::string> values, std::vector<std::string> operators, OmniPointer<IntegerReference> index, int precedent)
{
    if (precedent==-1)
    {
        return Element(values,index->GetValue());
    }
    std::string r_value_l = this->BinaryOperatorPrecedentMerge(values,operators,index,precedent-1);
    while (index->GetValue()<Size(operators))
    {
        std::string op = Element(operators,index->GetValue());
        if (this->OverPrecedent(op,precedent))
        {
            return r_value_l;
        }
        index->SetValue(index->GetValue()+1);
        std::string r_value_r = this->BinaryOperatorPrecedentMerge(values,operators,index,precedent-1);
        r_value_l = this->BinaryOperator(op,r_value_l,r_value_r);
    }
    return r_value_l;
}

std::string Java11Transpiler::GetRValueInternal(OmniPointer<s84::ctcode::dbnf::ctcode::RValue> r_value)
{
    std::vector<std::string> values;
    std::vector<std::string> operators;
    OmniPointer<IntegerReference> index = std::shared_ptr<IntegerReference>(new IntegerReference());
    index->SetValue(0);
    Append(values,this->GetRValueSingleInternal(r_value->GetValue()));
    OmniPointer<s84::ctcode::dbnf::ctcode::RValueTail> r_value_tail = r_value->GetTail();
    while (r_value_tail)
    {
        OmniPointer<s84::ctcode::dbnf::ctcode::BinaryOperator> binary_operator = r_value_tail->GetBinaryOperator();
        Append(values,this->GetRValueSingleInternal(r_value_tail->GetValue()));
        Append(operators,binary_operator->UnParse());
        r_value_tail = r_value_tail->GetTail();
    }
    return this->BinaryOperatorPrecedentMerge(values,operators,index,Size(this->operator_precedent));
}

std::string Java11Transpiler::GetQualifiedTypeNameInternal(OmniPointer<s84::ctcode::dbnf::ctcode::QualfiedName> qualified_name)
{
    std::vector<OmniPointer<s84::ctcode::dbnf::ctcode::Name>> name_parts;
    Append(name_parts,qualified_name->GetName());
    OmniPointer<s84::ctcode::dbnf::ctcode::NameTail> tail = qualified_name->GetTail();
    while (tail)
    {
        Append(name_parts,tail->GetName());
        tail = tail->GetTail();
    }
    return this->GetQualifiedTypeName(name_parts);
}

std::string Java11Transpiler::GetType(OmniPointer<s84::ctcode::dbnf::ctcode::ValueType> type)
{
    if (type->GetDimensionalType())
    {
        OmniPointer<s84::ctcode::dbnf::ctcode::DimensionalType> dimensional_type = type->GetDimensionalType();
        OmniPointer<s84::ctcode::dbnf::ctcode::SingletonType> singleton_type = dimensional_type->GetSingletonType();
        return this->GetDimensionalType(this->GetSingletonType(singleton_type),Size(dimensional_type->GetDimensionalNote()));
    }
    if (type->GetMapType())
    {
        OmniPointer<s84::ctcode::dbnf::ctcode::MapType> map_type = type->GetMapType();
        OmniPointer<s84::ctcode::dbnf::ctcode::SingletonType> singleton_type = map_type->GetSingletonType();
        return this->GetMapType(this->GetSingletonType(singleton_type));
    }
    if (type->GetSingletonType())
    {
        OmniPointer<s84::ctcode::dbnf::ctcode::SingletonType> singleton_type = type->GetSingletonType();
        return this->GetSingletonType(singleton_type);
    }
    return std::string("");
}

std::string Java11Transpiler::Indentation(int indent)
{
    std::string result = "";
    result = std::string("");
    while (indent>0)
    {
        indent = indent-1;
        result = Concat(result,std::string("    "));
    }
    return result;
}

std::string Java11Transpiler::SnakeCaseToCamelCase(std::string snake_case)
{
    bool capitalize_this_letter = true;
    std::string camel_case = std::string("");
    int index = 0;
    index = 0;
    while (index<Length(snake_case))
    {
        std::string source_character = At(snake_case,index);
        if (source_character==std::string("_"))
        {
            capitalize_this_letter = true;
        }
        else
        {
            if (capitalize_this_letter==true)
            {
                std::string upper_character = this->CharacterToUpper(source_character);
                capitalize_this_letter = false;
                camel_case = Concat(camel_case,upper_character);
            }
            else
            {
                capitalize_this_letter = false;
                camel_case = Concat(camel_case,source_character);
            }
        }
        index = index+1;
    }
    return camel_case;
}

std::string Java11Transpiler::CamelCaseToSnakeCase(std::string camel_case)
{
    std::string delimiter = std::string("_");
    std::string snake_case = std::string("");
    int index = 0;
    while (index<Length(camel_case))
    {
        std::string source_character = At(camel_case,index);
        std::string lower_character = this->CharacterToLower(source_character);
        if (this->IsUpper(source_character)||this->IsDigit(source_character))
        {
            bool is_first_character = Length(snake_case)==0;
            if (!is_first_character)
            {
                snake_case = Concat(snake_case,delimiter);
            }
        }
        snake_case = Concat(snake_case,lower_character);
        index = index+1;
    }
    return snake_case;
}

bool Java11Transpiler::IsUpper(std::string character)
{
    bool result = false;
    result = false;
    result = result||character==std::string("A");
    result = result||character==std::string("B");
    result = result||character==std::string("C");
    result = result||character==std::string("D");
    result = result||character==std::string("E");
    result = result||character==std::string("F");
    result = result||character==std::string("G");
    result = result||character==std::string("H");
    result = result||character==std::string("I");
    result = result||character==std::string("J");
    result = result||character==std::string("K");
    result = result||character==std::string("L");
    result = result||character==std::string("M");
    result = result||character==std::string("N");
    result = result||character==std::string("O");
    result = result||character==std::string("P");
    result = result||character==std::string("Q");
    result = result||character==std::string("R");
    result = result||character==std::string("S");
    result = result||character==std::string("T");
    result = result||character==std::string("U");
    result = result||character==std::string("V");
    result = result||character==std::string("W");
    result = result||character==std::string("X");
    result = result||character==std::string("Y");
    result = result||character==std::string("Z");
    return result;
}

bool Java11Transpiler::IsDigit(std::string character)
{
    bool result = false;
    result = false;
    result = result||character==std::string("0");
    result = result||character==std::string("1");
    result = result||character==std::string("2");
    result = result||character==std::string("3");
    result = result||character==std::string("4");
    result = result||character==std::string("5");
    result = result||character==std::string("6");
    result = result||character==std::string("7");
    result = result||character==std::string("8");
    result = result||character==std::string("9");
    return result;
}

std::string Java11Transpiler::ToLower(std::string input)
{
    int index = 0;
    std::string result = std::string("");
    while (index<Length(input))
    {
        std::string character = At(input,index);
        std::string lower_character = this->CharacterToLower(character);
        result = Concat(result,lower_character);
        index = index+1;
    }
    return result;
}

std::string Java11Transpiler::CharacterToLower(std::string input)
{
    if (input==std::string("A"))
    {
        return std::string("a");
    }
    if (input==std::string("B"))
    {
        return std::string("b");
    }
    if (input==std::string("C"))
    {
        return std::string("c");
    }
    if (input==std::string("D"))
    {
        return std::string("d");
    }
    if (input==std::string("E"))
    {
        return std::string("e");
    }
    if (input==std::string("F"))
    {
        return std::string("f");
    }
    if (input==std::string("G"))
    {
        return std::string("g");
    }
    if (input==std::string("H"))
    {
        return std::string("h");
    }
    if (input==std::string("I"))
    {
        return std::string("i");
    }
    if (input==std::string("J"))
    {
        return std::string("j");
    }
    if (input==std::string("K"))
    {
        return std::string("k");
    }
    if (input==std::string("L"))
    {
        return std::string("l");
    }
    if (input==std::string("M"))
    {
        return std::string("m");
    }
    if (input==std::string("N"))
    {
        return std::string("n");
    }
    if (input==std::string("O"))
    {
        return std::string("o");
    }
    if (input==std::string("P"))
    {
        return std::string("p");
    }
    if (input==std::string("Q"))
    {
        return std::string("q");
    }
    if (input==std::string("R"))
    {
        return std::string("r");
    }
    if (input==std::string("S"))
    {
        return std::string("s");
    }
    if (input==std::string("T"))
    {
        return std::string("t");
    }
    if (input==std::string("U"))
    {
        return std::string("u");
    }
    if (input==std::string("V"))
    {
        return std::string("v");
    }
    if (input==std::string("W"))
    {
        return std::string("w");
    }
    if (input==std::string("X"))
    {
        return std::string("x");
    }
    if (input==std::string("Y"))
    {
        return std::string("y");
    }
    if (input==std::string("Z"))
    {
        return std::string("z");
    }
    return input;
}

std::string Java11Transpiler::ToUpper(std::string input)
{
    int index = 0;
    std::string result = std::string("");
    while (index<Length(input))
    {
        std::string character = At(input,index);
        std::string upper_character = this->CharacterToUpper(character);
        result = Concat(result,upper_character);
        index = index+1;
    }
    return result;
}

std::string Java11Transpiler::CharacterToUpper(std::string input)
{
    if (input==std::string("a"))
    {
        return std::string("A");
    }
    if (input==std::string("b"))
    {
        return std::string("B");
    }
    if (input==std::string("c"))
    {
        return std::string("C");
    }
    if (input==std::string("d"))
    {
        return std::string("D");
    }
    if (input==std::string("e"))
    {
        return std::string("E");
    }
    if (input==std::string("f"))
    {
        return std::string("F");
    }
    if (input==std::string("g"))
    {
        return std::string("G");
    }
    if (input==std::string("h"))
    {
        return std::string("H");
    }
    if (input==std::string("i"))
    {
        return std::string("I");
    }
    if (input==std::string("j"))
    {
        return std::string("J");
    }
    if (input==std::string("k"))
    {
        return std::string("K");
    }
    if (input==std::string("l"))
    {
        return std::string("L");
    }
    if (input==std::string("m"))
    {
        return std::string("M");
    }
    if (input==std::string("n"))
    {
        return std::string("N");
    }
    if (input==std::string("o"))
    {
        return std::string("O");
    }
    if (input==std::string("p"))
    {
        return std::string("P");
    }
    if (input==std::string("q"))
    {
        return std::string("Q");
    }
    if (input==std::string("r"))
    {
        return std::string("R");
    }
    if (input==std::string("s"))
    {
        return std::string("S");
    }
    if (input==std::string("t"))
    {
        return std::string("T");
    }
    if (input==std::string("u"))
    {
        return std::string("U");
    }
    if (input==std::string("v"))
    {
        return std::string("V");
    }
    if (input==std::string("w"))
    {
        return std::string("W");
    }
    if (input==std::string("x"))
    {
        return std::string("X");
    }
    if (input==std::string("y"))
    {
        return std::string("Y");
    }
    if (input==std::string("z"))
    {
        return std::string("Z");
    }
    return input;
}


};
};
};
};
};
