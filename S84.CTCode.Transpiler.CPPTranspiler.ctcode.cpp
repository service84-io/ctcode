#include "S84.CTCode.Transpiler.CPPTranspiler.ctcode.hpp"

namespace s84 {
namespace ctcode {
namespace transpiler {
namespace cpptranspiler {
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

CPPTranspiler::CPPTranspiler()
{
    this->system = NULL;
    this->c_t_code_file = NULL;
    this->base_name = "";
    this->logger = NULL;
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

int CPPTranspiler::GetBaseIndentation()
{
    return 0;
}

std::string CPPTranspiler::GetCallName(OmniPointer<s84::ctcode::dbnf::ctcode::Name> name)
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

std::string CPPTranspiler::GetVariableName(OmniPointer<s84::ctcode::dbnf::ctcode::Name> name)
{
    if (name)
    {
        std::string value = this->CamelCaseToSnakeCase(name->UnParse());
        if (value==std::string("myself"))
        {
            return std::string("this");
        }
        return value;
    }
    else
    {
        return std::string("");
    }
}

std::string CPPTranspiler::GetVariableChainNameTail(OmniPointer<s84::ctcode::dbnf::ctcode::NameTail> tail)
{
    std::string accessor = std::string("->");
    if (tail)
    {
        return Concat(Concat(accessor,this->GetVariableName(tail->GetName())),this->GetVariableChainNameTail(tail->GetTail()));
    }
    else
    {
        return std::string("");
    }
}

std::string CPPTranspiler::GetVariableChain(OmniPointer<s84::ctcode::dbnf::ctcode::QualfiedName> l_value)
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

std::string CPPTranspiler::ConvertDecimal(std::string decimal)
{
    return decimal;
}

std::string CPPTranspiler::ConvertNumber(std::string number)
{
    return number;
}

std::string CPPTranspiler::ConvertBoolean(std::string boolean)
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

std::string CPPTranspiler::GetTypeName(OmniPointer<s84::ctcode::dbnf::ctcode::Name> name)
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

std::string CPPTranspiler::GetQualifiedTypeName(std::vector<OmniPointer<s84::ctcode::dbnf::ctcode::Name>> name_parts)
{
    std::string delimiter = std::string("::");
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
            result = Concat(ToLower(name_part->UnParse()),result);
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
    int noop = 0;
}

void CPPTranspiler::BeginProcessingInterface(std::string interface_name)
{
    this->current_interface = interface_name;
    Append(this->interface_declarations,Concat(Concat(std::string("class "),interface_name),std::string(";")));
    Append(this->interface_definitions,Concat(Concat(std::string("class "),interface_name),std::string(" {")));
    Append(this->interface_definitions,std::string("public:"));
}

void CPPTranspiler::ProcessInterfaceFunctionDeclaration(std::string return_type, std::string function_name, std::vector<OmniPointer<ParameterDeclaration>> parameters)
{
    Append(this->interface_definitions,Concat(Concat(Concat(Concat(Concat(Concat(this->Indentation(1),std::string("virtual ")),return_type),std::string(" ")),function_name),this->MakeParametersString(parameters)),std::string(" = 0;")));
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
    Append(this->class_definitions,Concat(Concat(this->Indentation(1),class_name),std::string("();")));
    Append(this->class_definitions,Concat(Concat(Concat(this->Indentation(1),std::string("inline ~")),class_name),std::string("() {}")));
    Append(this->class_definitions,std::string(""));
    ClearList(this->class_init);
    ClearList(this->class_functions);
    ClearList(this->class_members);
    Append(this->class_init,Concat(Concat(Concat(class_name,std::string("::")),class_name),std::string("()")));
    Append(this->class_init,std::string("{"));
}

void CPPTranspiler::BeginProcessingClassFunctionDefinition(std::string return_type, std::string function_name, std::vector<OmniPointer<ParameterDeclaration>> parameters)
{
    Append(this->class_definitions,Concat(Concat(Concat(Concat(Concat(this->Indentation(1),return_type),std::string(" ")),function_name),this->MakeParametersString(parameters)),std::string(";")));
    Append(this->class_functions,Concat(Concat(Concat(Concat(Concat(return_type,std::string(" ")),this->current_class),std::string("::")),function_name),this->MakeParametersString(parameters)));
}

void CPPTranspiler::BeginProcessCodeBlock(int indent)
{
    Append(this->class_functions,Concat(this->Indentation(indent),std::string("{")));
}

void CPPTranspiler::FinishProcessCodeBlock(int indent)
{
    Append(this->class_functions,Concat(this->Indentation(indent),std::string("}")));
}

void CPPTranspiler::BeginProcessConditional(int indent, std::string r_value)
{
    Append(this->class_functions,Concat(Concat(Concat(this->Indentation(indent),std::string("if (")),r_value),std::string(")")));
}

void CPPTranspiler::ProcessElse(int indent)
{
    Append(this->class_functions,Concat(this->Indentation(indent),std::string("else")));
}

void CPPTranspiler::FinishProcessConditional(int indent, std::string r_value)
{
    int noop = 0;
}

void CPPTranspiler::BeginProcessLoop(int indent, std::string r_value)
{
    Append(this->class_functions,Concat(Concat(Concat(this->Indentation(indent),std::string("while (")),r_value),std::string(")")));
}

void CPPTranspiler::FinishProcessLoop(int indent, std::string r_value)
{
    int noop = 0;
}

void CPPTranspiler::ProcessRtn(int indent, std::string r_value)
{
    Append(this->class_functions,Concat(Concat(Concat(this->Indentation(indent),std::string("return ")),r_value),std::string(";")));
}

void CPPTranspiler::ProcessDeclaration(int indent, std::string type, std::string l_value, std::string r_value)
{
    if (r_value==std::string(""))
    {
        r_value = this->GetDefault(type);
    }
    if (r_value==std::string(""))
    {
        Append(this->class_functions,Concat(Concat(Concat(Concat(this->Indentation(indent),type),std::string(" ")),l_value),std::string(";")));
    }
    else
    {
        Append(this->class_functions,Concat(Concat(Concat(Concat(Concat(Concat(this->Indentation(indent),type),std::string(" ")),l_value),std::string(" = ")),r_value),std::string(";")));
    }
}

void CPPTranspiler::ProcessAssignment(int indent, std::string l_value, std::string r_value)
{
    Append(this->class_functions,Concat(Concat(Concat(Concat(this->Indentation(indent),l_value),std::string(" = ")),r_value),std::string(";")));
}

void CPPTranspiler::ProcessCall(int indent, std::string call)
{
    Append(this->class_functions,Concat(Concat(this->Indentation(indent),call),std::string(";")));
}

void CPPTranspiler::FinishProcessingClassFunctionDefinition(std::string return_type, std::string function_name, std::vector<OmniPointer<ParameterDeclaration>> parameters)
{
    Append(this->class_functions,std::string(""));
}

void CPPTranspiler::ProcessClassMemberDeclaration(std::string member_type, std::string member_name)
{
    std::string default_value = this->GetDefault(member_type);
    if (default_value!=std::string(""))
    {
        Append(this->class_init,Concat(Concat(Concat(Concat(Concat(this->Indentation(1),std::string("this->")),member_name),std::string(" = ")),default_value),std::string(";")));
    }
    else
    {
        Append(this->class_init,Concat(Concat(Concat(Concat(Concat(this->Indentation(1),std::string("/*this->")),member_name),std::string(" = ")),std::string("NO_DEFAULT")),std::string(";*/")));
    }
    Append(this->class_members,Concat(Concat(Concat(Concat(this->Indentation(1),member_type),std::string(" ")),member_name),std::string(";")));
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
    destination->WriteLine(std::string("private:"));
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
    std::string guard_name = this->ToUpper(this->StripDot(Concat(this->base_name,std::string("_H"))));
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
        file->WriteLine(Concat(Concat(std::string("namespace "),ToLower(base_name_token)),std::string(" {")));
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
        this->WriteLines(header_file,this->includes);
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
        this->WriteLines(header_file,this->interface_declarations);
        header_file->WriteLine(std::string(""));
    }
    if (Size(this->class_declarations)>0)
    {
        this->WriteLines(header_file,this->class_declarations);
        header_file->WriteLine(std::string(""));
    }
    if (Size(this->interface_definitions)>0)
    {
        this->WriteLines(header_file,this->interface_definitions);
    }
    this->WriteLines(header_file,this->class_definitions);
    this->WriteEndingNamespace(header_file);
    header_file->WriteLine(std::string(""));
    this->WriteEndingGuard(header_file);
    source_file->WriteLine(Concat(Concat(std::string("#include \""),base_name),std::string(".hpp\"")));
    source_file->WriteLine(std::string(""));
    this->WriteBeginingNamespace(source_file);
    source_file->WriteLine(std::string(""));
    if (Size(this->function_definitions)>0)
    {
        this->WriteLines(source_file,this->function_definitions);
        source_file->WriteLine(std::string(""));
    }
    this->WriteEndingNamespace(source_file);
}

bool CPPTranspiler::BeginsWith(std::string prefix, std::string value)
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
    if (this->BeginsWith(std::string("std::unordered_map<std::string, "),cpp_type))
    {
        return std::string("");
    }
    if (this->BeginsWith(std::string("std::vector<"),cpp_type))
    {
        return std::string("");
    }
    return std::string("NULL");
}

std::string CPPTranspiler::MakeParametersString(std::vector<OmniPointer<ParameterDeclaration>> parameters)
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

std::string CPPTranspiler::StripDot(std::string input)
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

void CPPTranspiler::WriteLines(OmniPointer<s84::ctcode::system::ctcode::OutputStream> destination, std::vector<std::string> lines)
{
    int lines_index = 0;
    while (lines_index<Size(lines))
    {
        std::string line = Element(lines,lines_index);
        destination->WriteLine(line);
        lines_index = lines_index+1;
    }
}

int CPPTranspiler::Transpile(OmniPointer<s84::ctcode::system::ctcode::System> system, OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file, std::string base_name)
{
    this->system = system;
    this->c_t_code_file = c_t_code_file;
    this->base_name = base_name;
    this->logger = system->GetLoggerDestination();
    this->ProcessCTCodeFile(c_t_code_file);
    return 0;
}

void CPPTranspiler::ProcessCTCodeFile(OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file)
{
    this->BeginProcessingCTCodeFile();
    this->ProcessExdefs(c_t_code_file);
    this->ProcessUnmanagedTypes(c_t_code_file);
    this->ProcessDefinitions(c_t_code_file);
    this->FinishProcessingCTCodeFile();
}

void CPPTranspiler::ProcessExdefs(OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file)
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

void CPPTranspiler::ProcessUnmanagedTypes(OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file)
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

void CPPTranspiler::ProcessDefinitions(OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file)
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

std::vector<OmniPointer<ParameterDeclaration>> CPPTranspiler::GetParameters(OmniPointer<s84::ctcode::dbnf::ctcode::ParameterListDef> parameter_list_def)
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

void CPPTranspiler::ProcessInterfaceDefinition(OmniPointer<s84::ctcode::dbnf::ctcode::InterfaceDef> interface_definition)
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

void CPPTranspiler::ProcessClassDefinition(OmniPointer<s84::ctcode::dbnf::ctcode::ClassDef> class_definition)
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

void CPPTranspiler::ProcessInstructionInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::Instruction> instruction)
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

void CPPTranspiler::ProcessCodeBlockInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::CodeBlock> code_block)
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

void CPPTranspiler::ProcessConditionalInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::Conditional> conditional)
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

void CPPTranspiler::ProcessLoopInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::Loop> loop)
{
    std::string r_value = this->GetRValueInternal(loop->GetRValue());
    this->BeginProcessLoop(indent,r_value);
    this->ProcessCodeBlockInternal(indent,loop->GetCodeBlock());
    this->FinishProcessLoop(indent,r_value);
}

void CPPTranspiler::ProcessRtnInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::Return> rtn)
{
    std::string r_value = this->GetRValueInternal(rtn->GetRValue());
    this->ProcessRtn(indent,r_value);
}

void CPPTranspiler::ProcessDeclarationInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::Declaration> declaration)
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

void CPPTranspiler::ProcessAssignmentInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::Assignment> assignment)
{
    this->ProcessAssignment(indent,this->GetVariableChain(assignment->GetLValue()),this->GetRValueInternal(assignment->GetRValue()));
}

void CPPTranspiler::ProcessCallInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::Call> call)
{
    this->ProcessCall(indent,this->ConvertCallInternal(call));
}

std::string CPPTranspiler::ConvertCallInternal(OmniPointer<s84::ctcode::dbnf::ctcode::Call> call)
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

std::string CPPTranspiler::GetSingletonType(OmniPointer<s84::ctcode::dbnf::ctcode::SingletonType> singleton_type)
{
    if (singleton_type->GetPrimativeType())
    {
        return this->GetPrimativeType(singleton_type->UnParse());
    }
    if (singleton_type->GetDefinedType())
    {
        OmniPointer<s84::ctcode::dbnf::ctcode::DefinedType> defined_type = singleton_type->GetDefinedType();
        return Concat(Concat(std::string("OmniPointer<"),this->GetQualifiedTypeNameInternal(defined_type->GetName())),std::string(">"));
    }
    return std::string("");
}

std::string CPPTranspiler::GetRValueSingleBasisInternal(OmniPointer<s84::ctcode::dbnf::ctcode::RValueSingle> r_value_single)
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

std::string CPPTranspiler::GetRValueSingleInternal(OmniPointer<s84::ctcode::dbnf::ctcode::RValueSingle> r_value_single)
{
    OmniPointer<s84::ctcode::dbnf::ctcode::UnaryOperator> unary_operator = r_value_single->GetUnaryOperator();
    if (unary_operator)
    {
        return this->UnaryOperator(unary_operator->UnParse(),this->GetRValueSingleBasisInternal(r_value_single));
    }
    return this->GetRValueSingleBasisInternal(r_value_single);
}

std::string CPPTranspiler::GetRValueBinaryInternal(std::string r_value_l, OmniPointer<s84::ctcode::dbnf::ctcode::RValueTail> r_value_tail)
{
    std::string r_value_r = this->GetRValueSingleInternal(r_value_tail->GetValue());
    OmniPointer<s84::ctcode::dbnf::ctcode::BinaryOperator> binary_operator = r_value_tail->GetBinaryOperator();
    r_value_l = this->BinaryOperator(binary_operator->UnParse(),r_value_l,r_value_r);
    if (r_value_tail->GetTail())
    {
        return this->GetRValueBinaryInternal(r_value_l,r_value_tail->GetTail());
    }
    return r_value_l;
}

std::string CPPTranspiler::GetRValueInternal(OmniPointer<s84::ctcode::dbnf::ctcode::RValue> r_value)
{
    std::string r_value_l = this->GetRValueSingleInternal(r_value->GetValue());
    if (r_value->GetTail())
    {
        return this->GetRValueBinaryInternal(r_value_l,r_value->GetTail());
    }
    return r_value_l;
}

std::string CPPTranspiler::GetQualifiedTypeNameInternal(OmniPointer<s84::ctcode::dbnf::ctcode::QualfiedName> qualified_name)
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

std::string CPPTranspiler::GetType(OmniPointer<s84::ctcode::dbnf::ctcode::ValueType> type)
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

std::string CPPTranspiler::Indentation(int indent)
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

std::string CPPTranspiler::SnakeCaseToCamelCase(std::string snake_case)
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

std::string CPPTranspiler::CamelCaseToSnakeCase(std::string camel_case)
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

bool CPPTranspiler::IsUpper(std::string character)
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

bool CPPTranspiler::IsDigit(std::string character)
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

std::string CPPTranspiler::ToLower(std::string input)
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

std::string CPPTranspiler::CharacterToLower(std::string input)
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

std::string CPPTranspiler::ToUpper(std::string input)
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

std::string CPPTranspiler::CharacterToUpper(std::string input)
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
