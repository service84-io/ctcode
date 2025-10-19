#include "S84.CTCode.Transpiler.CPPTranspiler.ctcode.hpp"

namespace s84 {
namespace ctcode {
namespace transpiler {
namespace cpptranspiler {
namespace ctcode {

CPPTranspiler::CPPTranspiler()
{
    this->system = NULL;
    this->c_t_code_file = NULL;
    this->base_name = "";
    this->logger = NULL;
    this->string_helper = NULL;
    /*this->includes = NO_DEFAULT;*/
    /*this->interface_declarations = NO_DEFAULT;*/
    /*this->class_declarations = NO_DEFAULT;*/
    this->current_interface = "";
    /*this->interface_definitions = NO_DEFAULT;*/
    this->current_class = "";
    /*this->class_definitions = NO_DEFAULT;*/
    /*this->class_init = NO_DEFAULT;*/
    /*this->class_functions = NO_DEFAULT;*/
    /*this->class_members = NO_DEFAULT;*/
    /*this->function_definitions = NO_DEFAULT;*/
}

void CPPTranspiler::Initialize()
{
    this->string_helper = std::shared_ptr<s84::ctcode::transpiler::stringhelper::ctcode::StringHelper>(new s84::ctcode::transpiler::stringhelper::ctcode::StringHelper());
}

void CPPTranspiler::SetSystem(OmniPointer<s84::ctcode::system::ctcode::System> system)
{
    this->system = system;
}

void CPPTranspiler::SetCTCodeFile(OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file)
{
    this->c_t_code_file = c_t_code_file;
}

void CPPTranspiler::SetBaseName(std::string base_name)
{
    this->base_name = base_name;
}

void CPPTranspiler::SetLogger(OmniPointer<s84::ctcode::system::ctcode::OutputStream> logger)
{
    this->logger = logger;
}

int CPPTranspiler::GetBaseIndentation()
{
    return 0;
}

std::string CPPTranspiler::GetCallName(std::string name)
{
    std::string value = this->string_helper->SnakeCaseToCamelCase(name);
    if (this->string_helper->IsReserved(value))
    {
        return Concat(std::string("ReservedPrefix"),value);
    }
    return value;
}

std::string CPPTranspiler::GetVariableName(std::string name)
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

std::string CPPTranspiler::GetVariableChain(std::vector<std::string> name_parts)
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

std::string CPPTranspiler::ConvertCall(std::vector<std::string> name_chain, std::vector<std::string> parameters)
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

std::string CPPTranspiler::ConvertAllocate(std::string type)
{
    return Concat(Concat(Concat(Concat(std::string("std::shared_ptr<"),type),std::string(">(new ")),type),std::string("())"));
}

std::string CPPTranspiler::ConvertByte(std::string high, std::string low)
{
    return Concat(Concat(std::string("0x"),high),low);
}

std::string CPPTranspiler::ConvertDecimal(std::string reserved_prefix_decimal)
{
    return reserved_prefix_decimal;
}

std::string CPPTranspiler::ConvertNumber(std::string number)
{
    return number;
}

std::string CPPTranspiler::ConvertBoolean(std::string reserved_prefix_boolean)
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

std::string CPPTranspiler::ConvertVariable(std::string variable)
{
    return variable;
}

std::string CPPTranspiler::ConvertString(std::string literal)
{
    return Concat(Concat(std::string("std::string(\""),literal),std::string("\")"));
}

std::string CPPTranspiler::UnaryOperator(std::string op, std::string r_value)
{
    if (op==std::string("!"))
    {
        return Concat(std::string("!"),r_value);
    }
    return r_value;
}

std::string CPPTranspiler::BinaryOperator(std::string op, std::string r_value_l, std::string r_value_r)
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

std::string CPPTranspiler::GetTypeName(std::string name)
{
    std::string value = this->string_helper->SnakeCaseToCamelCase(name);
    if (this->string_helper->IsReserved(value))
    {
        return Concat(std::string("ReservedPrefix"),value);
    }
    return value;
}

std::string CPPTranspiler::GetDimensionalType(std::string singleton_type, int dimensions)
{
    std::string result = singleton_type;
    while (dimensions>0)
    {
        result = Concat(Concat(std::string("std::vector<"),result),std::string(">"));
        dimensions = dimensions-1;
    }
    return result;
}

std::string CPPTranspiler::GetMapType(std::string singleton_type)
{
    return Concat(Concat(std::string("std::unordered_map<std::string, "),singleton_type),std::string(">"));
}

std::string CPPTranspiler::GetPrimativeType(std::string c_t_type)
{
    if (c_t_type==std::string("int"))
    {
        return std::string("int");
    }
    if (c_t_type==std::string("string"))
    {
        return std::string("std::string");
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

std::string CPPTranspiler::GetDefinedType(std::string c_t_type)
{
    return Concat(Concat(std::string("OmniPointer<"),c_t_type),std::string(">"));
}

std::string CPPTranspiler::GetQualifiedTypeName(std::vector<std::string> name_parts)
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
            result = Concat(this->string_helper->ToLower(name_part),result);
        }
    }
    return result;
}

void CPPTranspiler::BeginProcessingCTCodeFile()
{
    ClearList(this->includes);
    ClearList(this->interface_declarations);
    ClearList(this->class_declarations);
    this->current_interface = std::string("");
    ClearList(this->interface_definitions);
    this->current_class = std::string("");
    ClearList(this->class_definitions);
    ClearList(this->class_init);
    ClearList(this->class_functions);
    ClearList(this->class_members);
    ClearList(this->function_definitions);
}

void CPPTranspiler::ProcessExdef(std::string exdef)
{
    Append(this->includes,Concat(std::string("#include \""),Concat(exdef,std::string(".hpp\""))));
}

void CPPTranspiler::ProcessUnmanagedType(std::string unmanaged_type)
{
}

void CPPTranspiler::BeginProcessingInterface(std::string interface_name)
{
    this->current_interface = interface_name;
    Append(this->interface_declarations,Concat(Concat(std::string("class "),interface_name),std::string(";")));
    Append(this->interface_definitions,Concat(Concat(std::string("class "),interface_name),std::string(" {")));
    Append(this->interface_definitions,std::string("public:"));
}

void CPPTranspiler::ProcessInterfaceFunctionDeclaration(std::string return_type, std::string function_name, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    Append(this->interface_definitions,Concat(Concat(Concat(Concat(Concat(Concat(this->string_helper->Indentation(1),std::string("virtual ")),return_type),std::string(" ")),function_name),this->MakeParametersString(parameters)),std::string(" = 0;")));
}

void CPPTranspiler::FinishProcessingInterface(std::string interface_name)
{
    Append(this->interface_definitions,std::string("};"));
    Append(this->interface_definitions,std::string(""));
    this->current_interface = std::string("");
}

void CPPTranspiler::BeginProcessingClass(std::string class_name, std::string implementing)
{
    this->current_class = class_name;
    Append(this->class_declarations,Concat(Concat(std::string("class "),class_name),std::string(";")));
    if (implementing==std::string(""))
    {
        Append(this->class_definitions,Concat(Concat(std::string("class "),class_name),std::string(" {")));
    }
    else
    {
        Append(this->class_definitions,Concat(Concat(Concat(Concat(std::string("class "),class_name),std::string(" : public ")),implementing),std::string(" {")));
    }
    Append(this->class_definitions,std::string("public:"));
    Append(this->class_definitions,Concat(Concat(this->string_helper->Indentation(1),class_name),std::string("();")));
    Append(this->class_definitions,Concat(Concat(Concat(this->string_helper->Indentation(1),std::string("inline ~")),class_name),std::string("() {}")));
    Append(this->class_definitions,std::string(""));
    ClearList(this->class_init);
    ClearList(this->class_functions);
    ClearList(this->class_members);
    Append(this->class_init,Concat(Concat(Concat(class_name,std::string("::")),class_name),std::string("()")));
    Append(this->class_init,std::string("{"));
}

void CPPTranspiler::BeginProcessingClassFunctionDefinition(std::string return_type, std::string function_name, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    Append(this->class_definitions,Concat(Concat(Concat(Concat(Concat(this->string_helper->Indentation(1),return_type),std::string(" ")),function_name),this->MakeParametersString(parameters)),std::string(";")));
    Append(this->class_functions,Concat(Concat(Concat(Concat(Concat(return_type,std::string(" ")),this->current_class),std::string("::")),function_name),this->MakeParametersString(parameters)));
}

void CPPTranspiler::BeginProcessCodeBlock(int indent)
{
    Append(this->class_functions,Concat(this->string_helper->Indentation(indent),std::string("{")));
}

void CPPTranspiler::FinishProcessCodeBlock(int indent)
{
    Append(this->class_functions,Concat(this->string_helper->Indentation(indent),std::string("}")));
}

void CPPTranspiler::BeginProcessConditional(int indent, std::string r_value)
{
    Append(this->class_functions,Concat(Concat(Concat(this->string_helper->Indentation(indent),std::string("if (")),r_value),std::string(")")));
}

void CPPTranspiler::ProcessElse(int indent)
{
    Append(this->class_functions,Concat(this->string_helper->Indentation(indent),std::string("else")));
}

void CPPTranspiler::FinishProcessConditional(int indent, std::string r_value)
{
}

void CPPTranspiler::BeginProcessLoop(int indent, std::string r_value)
{
    Append(this->class_functions,Concat(Concat(Concat(this->string_helper->Indentation(indent),std::string("while (")),r_value),std::string(")")));
}

void CPPTranspiler::FinishProcessLoop(int indent, std::string r_value)
{
}

void CPPTranspiler::ProcessRtn(int indent, std::string r_value)
{
    Append(this->class_functions,Concat(Concat(Concat(this->string_helper->Indentation(indent),std::string("return ")),r_value),std::string(";")));
}

void CPPTranspiler::ProcessDeclaration(int indent, std::string type, std::string l_value, std::string r_value)
{
    if (r_value==std::string(""))
    {
        r_value = this->GetDefault(type);
    }
    if (r_value==std::string(""))
    {
        Append(this->class_functions,Concat(Concat(Concat(Concat(this->string_helper->Indentation(indent),type),std::string(" ")),l_value),std::string(";")));
    }
    else
    {
        Append(this->class_functions,Concat(Concat(Concat(Concat(Concat(Concat(this->string_helper->Indentation(indent),type),std::string(" ")),l_value),std::string(" = ")),r_value),std::string(";")));
    }
}

void CPPTranspiler::ProcessAssignment(int indent, std::string l_value, std::string r_value)
{
    Append(this->class_functions,Concat(Concat(Concat(Concat(this->string_helper->Indentation(indent),l_value),std::string(" = ")),r_value),std::string(";")));
}

void CPPTranspiler::ProcessCall(int indent, std::string call)
{
    Append(this->class_functions,Concat(Concat(this->string_helper->Indentation(indent),call),std::string(";")));
}

void CPPTranspiler::FinishProcessingClassFunctionDefinition(std::string return_type, std::string function_name, std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
{
    Append(this->class_functions,std::string(""));
}

void CPPTranspiler::ProcessClassMemberDeclaration(std::string member_type, std::string member_name)
{
    std::string default_value = this->GetDefault(member_type);
    if (default_value!=std::string(""))
    {
        Append(this->class_init,Concat(Concat(Concat(Concat(Concat(this->string_helper->Indentation(1),std::string("this->")),member_name),std::string(" = ")),default_value),std::string(";")));
    }
    else
    {
        Append(this->class_init,Concat(Concat(Concat(Concat(Concat(this->string_helper->Indentation(1),std::string("/*this->")),member_name),std::string(" = ")),std::string("NO_DEFAULT")),std::string(";*/")));
    }
    Append(this->class_members,Concat(Concat(Concat(Concat(this->string_helper->Indentation(1),member_type),std::string(" ")),member_name),std::string(";")));
}

void CPPTranspiler::FinishProcessingClass(std::string class_name, std::string implementing)
{
    if (Size(this->class_members)>0)
    {
        Append(this->class_definitions,std::string(""));
        Append(this->class_definitions,std::string("private:"));
        int class_members_index = 0;
        while (class_members_index<Size(this->class_members))
        {
            std::string line = Element(this->class_members,class_members_index);
            Append(this->class_definitions,line);
            class_members_index = class_members_index+1;
        }
    }
    Append(this->class_definitions,std::string("};"));
    Append(this->class_definitions,std::string(""));
    Append(this->class_init,std::string("}"));
    Append(this->class_init,std::string(""));
    int class_init_index = 0;
    while (class_init_index<Size(this->class_init))
    {
        std::string line = Element(this->class_init,class_init_index);
        Append(this->function_definitions,line);
        class_init_index = class_init_index+1;
    }
    int class_functions_index = 0;
    while (class_functions_index<Size(this->class_functions))
    {
        std::string line = Element(this->class_functions,class_functions_index);
        Append(this->function_definitions,line);
        class_functions_index = class_functions_index+1;
    }
    this->current_class = std::string("");
}

void CPPTranspiler::WriteCommonFunctions(OmniPointer<s84::ctcode::system::ctcode::OutputStream> destination)
{
    destination->WriteLine(std::string("#ifndef CTCODE_COMMON_FUNCTIONS_VERSION_1"));
    destination->WriteLine(std::string("#define CTCODE_COMMON_FUNCTIONS_VERSION_1"));
    destination->WriteLine(std::string("template<typename T>"));
    destination->WriteLine(std::string("class OmniPointer"));
    destination->WriteLine(std::string("{"));
    destination->WriteLine(std::string("public:"));
    destination->WriteLine(std::string("    OmniPointer() { value_raw = NULL; }"));
    destination->WriteLine(std::string("    OmniPointer(T* value) { value_raw = value; }"));
    destination->WriteLine(std::string("    template<typename U>"));
    destination->WriteLine(std::string("    OmniPointer(U* value) { value_raw = value; }"));
    destination->WriteLine(std::string("    OmniPointer(std::shared_ptr<T> value) { value_raw = NULL; value_shared = value; }"));
    destination->WriteLine(std::string("    template<typename U>"));
    destination->WriteLine(std::string("    OmniPointer(std::shared_ptr<U> value) { value_raw = NULL; value_shared = value; }"));
    destination->WriteLine(std::string("    template<typename U>"));
    destination->WriteLine(std::string("    OmniPointer(OmniPointer<U> value) { value_raw = value.value_raw; value_shared = value.value_shared; }"));
    destination->WriteLine(std::string(""));
    destination->WriteLine(std::string("    operator bool()"));
    destination->WriteLine(std::string("    {"));
    destination->WriteLine(std::string("        if (value_raw) return true;"));
    destination->WriteLine(std::string("        return value_shared.get() != NULL;"));
    destination->WriteLine(std::string("    }"));
    destination->WriteLine(std::string("    T& operator*()"));
    destination->WriteLine(std::string("    {"));
    destination->WriteLine(std::string("        if (value_raw) return *value_raw;"));
    destination->WriteLine(std::string("        return *value_shared;"));
    destination->WriteLine(std::string("    }"));
    destination->WriteLine(std::string("    T* operator->()"));
    destination->WriteLine(std::string("    {"));
    destination->WriteLine(std::string("        if (value_raw) return value_raw;"));
    destination->WriteLine(std::string("        return value_shared.get();"));
    destination->WriteLine(std::string("    }"));
    destination->WriteLine(std::string("    T* raw()"));
    destination->WriteLine(std::string("    {"));
    destination->WriteLine(std::string("        if (value_raw) return value_raw;"));
    destination->WriteLine(std::string("        return value_shared.get();"));
    destination->WriteLine(std::string("    }"));
    destination->WriteLine(std::string(""));
    destination->WriteLine(std::string("    T* value_raw;"));
    destination->WriteLine(std::string("    std::shared_ptr<T> value_shared;"));
    destination->WriteLine(std::string("};"));
    destination->WriteLine(std::string(""));
    destination->WriteLine(std::string("template<typename T>"));
    destination->WriteLine(std::string("inline std::vector<T*> UnwrapOmniList(std::vector<OmniPointer<T>> input) {"));
    destination->WriteLine(std::string("	std::vector<T*> result;"));
    destination->WriteLine(std::string("	for (typename std::vector<OmniPointer<T>>::iterator index = input.begin();index != input.end();index++) {"));
    destination->WriteLine(std::string("		result.push_back(index->raw());"));
    destination->WriteLine(std::string("	}"));
    destination->WriteLine(std::string("	return result;"));
    destination->WriteLine(std::string("};"));
    destination->WriteLine(std::string("template<typename T>"));
    destination->WriteLine(std::string("inline void ClearList(std::vector<T>& input) { input.clear(); };"));
    destination->WriteLine(std::string("template<typename T>"));
    destination->WriteLine(std::string("inline int Size(const std::vector<T>& input) { return input.size(); };"));
    destination->WriteLine(std::string("template<typename T>"));
    destination->WriteLine(std::string("inline T Element(const std::vector<T>& input, int element) { return input.at(element); };"));
    destination->WriteLine(std::string("template<typename T>"));
    destination->WriteLine(std::string("inline void Append(std::vector<T>& input, T element) { input.push_back(element); };"));
    destination->WriteLine(std::string("template<typename T>"));
    destination->WriteLine(std::string("inline void ClearMap(std::unordered_map<std::string, T>& input) { input.clear(); };"));
    destination->WriteLine(std::string("template<typename T>"));
    destination->WriteLine(std::string("inline void SetKV(std::unordered_map<std::string, T>& input, const std::string& key, T element)"));
    destination->WriteLine(std::string("{"));
    destination->WriteLine(std::string("    input.erase(key);"));
    destination->WriteLine(std::string("    input.insert(std::pair<std::string, T>(key, element));"));
    destination->WriteLine(std::string("}"));
    destination->WriteLine(std::string("template<typename T>"));
    destination->WriteLine(std::string("inline std::vector<std::string> Keys(const std::unordered_map<std::string, T>& input)"));
    destination->WriteLine(std::string("{"));
    destination->WriteLine(std::string("    std::vector<std::string> result;"));
    destination->WriteLine(std::string("    for(typename std::unordered_map<std::string, T>::const_iterator index = input.begin();index != input.end();index++) {"));
    destination->WriteLine(std::string("        result.push_back(index->first);"));
    destination->WriteLine(std::string("    }"));
    destination->WriteLine(std::string("    return result;"));
    destination->WriteLine(std::string("}"));
    destination->WriteLine(std::string("template<typename T>"));
    destination->WriteLine(std::string("inline bool HasKV(const std::unordered_map<std::string, T>& input, const std::string& key)"));
    destination->WriteLine(std::string("{"));
    destination->WriteLine(std::string("    typename std::unordered_map<std::string, T>::const_iterator beginning = input.find(key);"));
    destination->WriteLine(std::string("    return beginning != input.end();"));
    destination->WriteLine(std::string("}"));
    destination->WriteLine(std::string("template<typename T>"));
    destination->WriteLine(std::string("inline T GetKV(const std::unordered_map<std::string, T>& input, const std::string& key) { return input.at(key); }"));
    destination->WriteLine(std::string("inline int Length(const std::string& input) { return (int)input.length(); };"));
    destination->WriteLine(std::string("inline std::string At(const std::string& input, int index) { return input.substr(index, 1); };"));
    destination->WriteLine(std::string("inline int IntAt(const std::string& input, int index) { return (input.at(index) + 256) % 256; };"));
    destination->WriteLine(std::string("inline std::string Concat(const std::string& left, const std::string& right) { return left + right; };"));
    destination->WriteLine(std::string("#endif"));
}

void CPPTranspiler::WriteBeginingGuard(OmniPointer<s84::ctcode::system::ctcode::OutputStream> file)
{
    std::string guard_name = this->string_helper->ToUpper(this->string_helper->StripDot(Concat(this->base_name,std::string("_H"))));
    file->WriteLine(Concat(std::string("#ifndef "),guard_name));
    file->WriteLine(Concat(std::string("#define "),guard_name));
}

std::vector<std::string> CPPTranspiler::TokenizeBaseName(std::string name)
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

void CPPTranspiler::WriteBeginingNamespace(OmniPointer<s84::ctcode::system::ctcode::OutputStream> file)
{
    std::vector<std::string> base_name_tokens = this->TokenizeBaseName(this->base_name);
    int base_name_tokens_index = 0;
    while (base_name_tokens_index<Size(base_name_tokens))
    {
        std::string base_name_token = Element(base_name_tokens,base_name_tokens_index);
        file->WriteLine(Concat(Concat(std::string("namespace "),this->string_helper->ToLower(base_name_token)),std::string(" {")));
        base_name_tokens_index = base_name_tokens_index+1;
    }
}

void CPPTranspiler::WriteEndingNamespace(OmniPointer<s84::ctcode::system::ctcode::OutputStream> file)
{
    std::vector<std::string> base_name_tokens = this->TokenizeBaseName(this->base_name);
    int base_name_tokens_index = 0;
    while (base_name_tokens_index<Size(base_name_tokens))
    {
        std::string base_name_token = Element(base_name_tokens,base_name_tokens_index);
        file->WriteLine(std::string("};"));
        base_name_tokens_index = base_name_tokens_index+1;
    }
}

void CPPTranspiler::WriteEndingGuard(OmniPointer<s84::ctcode::system::ctcode::OutputStream> file)
{
    file->WriteLine(std::string("#endif"));
}

void CPPTranspiler::FinishProcessingCTCodeFile()
{
    std::string header_file_name = Concat(this->base_name,std::string(".hpp"));
    OmniPointer<s84::ctcode::system::ctcode::OutputStream> header_file = this->system->OpenFileWriter(header_file_name);
    std::string source_file_name = Concat(this->base_name,std::string(".cpp"));
    OmniPointer<s84::ctcode::system::ctcode::OutputStream> source_file = this->system->OpenFileWriter(source_file_name);
    this->WriteBeginingGuard(header_file);
    header_file->WriteLine(std::string(""));
    if (Size(this->includes)>0)
    {
        this->string_helper->WriteLines(header_file,this->includes);
        header_file->WriteLine(std::string(""));
    }
    header_file->WriteLine(std::string("#include <cstring>"));
    header_file->WriteLine(std::string("#include <list>"));
    header_file->WriteLine(std::string("#include <unordered_map>"));
    header_file->WriteLine(std::string("#include <memory>"));
    header_file->WriteLine(std::string("#include <string>"));
    header_file->WriteLine(std::string("#include <vector>"));
    header_file->WriteLine(std::string(""));
    this->WriteCommonFunctions(header_file);
    header_file->WriteLine(std::string(""));
    this->WriteBeginingNamespace(header_file);
    header_file->WriteLine(std::string(""));
    if (Size(this->interface_declarations)>0)
    {
        this->string_helper->WriteLines(header_file,this->interface_declarations);
        header_file->WriteLine(std::string(""));
    }
    if (Size(this->class_declarations)>0)
    {
        this->string_helper->WriteLines(header_file,this->class_declarations);
        header_file->WriteLine(std::string(""));
    }
    if (Size(this->interface_definitions)>0)
    {
        this->string_helper->WriteLines(header_file,this->interface_definitions);
    }
    this->string_helper->WriteLines(header_file,this->class_definitions);
    this->WriteEndingNamespace(header_file);
    header_file->WriteLine(std::string(""));
    this->WriteEndingGuard(header_file);
    source_file->WriteLine(Concat(Concat(std::string("#include \""),this->base_name),std::string(".hpp\"")));
    source_file->WriteLine(std::string(""));
    this->WriteBeginingNamespace(source_file);
    source_file->WriteLine(std::string(""));
    if (Size(this->function_definitions)>0)
    {
        this->string_helper->WriteLines(source_file,this->function_definitions);
        source_file->WriteLine(std::string(""));
    }
    this->WriteEndingNamespace(source_file);
}

std::string CPPTranspiler::GetDefault(std::string cpp_type)
{
    if (cpp_type==std::string("int"))
    {
        return std::string("0");
    }
    if (cpp_type==std::string("std::string"))
    {
        return std::string("\"\"");
    }
    if (cpp_type==std::string("bool"))
    {
        return std::string("false");
    }
    if (cpp_type==std::string("float"))
    {
        return std::string("0.0");
    }
    if (cpp_type==std::string("void"))
    {
        return std::string("NULL");
    }
    if (this->string_helper->BeginsWith(std::string("std::unordered_map<std::string, "),cpp_type))
    {
        return std::string("");
    }
    if (this->string_helper->BeginsWith(std::string("std::vector<"),cpp_type))
    {
        return std::string("");
    }
    return std::string("NULL");
}

std::string CPPTranspiler::MakeParametersString(std::vector<OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::ParameterDeclaration>> parameters)
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
        result = Concat(Concat(Concat(result,parameter->ReservedPrefixGetType()),std::string(" ")),parameter->GetName());
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
