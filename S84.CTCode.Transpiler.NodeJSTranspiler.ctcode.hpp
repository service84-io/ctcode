#ifndef S84_CTCODE_TRANSPILER_NODEJSTRANSPILER_CTCODE_H
#define S84_CTCODE_TRANSPILER_NODEJSTRANSPILER_CTCODE_H

#include "S84.CTCode.dbnf.ctcode.hpp"
#include "S84.CTCode.System.ctcode.hpp"
#include "S84.CTCode.Transpiler.ctcode.hpp"

#include <cstring>
#include <list>
#include <unordered_map>
#include <memory>
#include <string>
#include <vector>

#ifndef CTCODE_COMMON_FUNCTIONS_VERSION_1
#define CTCODE_COMMON_FUNCTIONS_VERSION_1
template<typename T>
class OmniPointer
{
public:
    OmniPointer() { value_raw = NULL; }
    OmniPointer(T* value) { value_raw = value; }
    template<typename U>
    OmniPointer(U* value) { value_raw = value; }
    OmniPointer(std::shared_ptr<T> value) { value_raw = NULL; value_shared = value; }
    template<typename U>
    OmniPointer(std::shared_ptr<U> value) { value_raw = NULL; value_shared = value; }
    template<typename U>
    OmniPointer(OmniPointer<U> value) { value_raw = value.value_raw; value_shared = value.value_shared; }

    operator bool()
    {
        if (value_raw) return true;
        return value_shared.get() != NULL;
    }
    T& operator*()
    {
        if (value_raw) return *value_raw;
        return *value_shared;
    }
    T* operator->()
    {
        if (value_raw) return value_raw;
        return value_shared.get();
    }
    T* raw()
    {
        if (value_raw) return value_raw;
        return value_shared.get();
    }

    T* value_raw;
    std::shared_ptr<T> value_shared;
};

template<typename T>
inline std::vector<T*> UnwrapOmniList(std::vector<OmniPointer<T>> input) {
	std::vector<T*> result;
	for (typename std::vector<OmniPointer<T>>::iterator index = input.begin();index != input.end();index++) {
		result.push_back(index->raw());
	}
	return result;
};
template<typename T>
inline void ClearList(std::vector<T>& input) { input.clear(); };
template<typename T>
inline int Size(const std::vector<T>& input) { return input.size(); };
template<typename T>
inline T Element(const std::vector<T>& input, int element) { return input.at(element); };
template<typename T>
inline void Append(std::vector<T>& input, T element) { input.push_back(element); };
template<typename T>
inline void ClearMap(std::unordered_map<std::string, T>& input) { input.clear(); };
template<typename T>
inline void SetKV(std::unordered_map<std::string, T>& input, const std::string& key, T element)
{
    input.erase(key);
    input.insert(std::pair<std::string, T>(key, element));
}
template<typename T>
inline std::vector<std::string> Keys(const std::unordered_map<std::string, T>& input)
{
    std::vector<std::string> result;
    for(typename std::unordered_map<std::string, T>::const_iterator index = input.begin();index != input.end();index++) {
        result.push_back(index->first);
    }
    return result;
}
template<typename T>
inline bool HasKV(const std::unordered_map<std::string, T>& input, const std::string& key)
{
    typename std::unordered_map<std::string, T>::const_iterator beginning = input.find(key);
    return beginning != input.end();
}
template<typename T>
inline T GetKV(const std::unordered_map<std::string, T>& input, const std::string& key) { return input.at(key); }
inline int Length(const std::string& input) { return (int)input.length(); };
inline std::string At(const std::string& input, int index) { return input.substr(index, 1); };
inline int IntAt(const std::string& input, int index) { return (input.at(index) + 256) % 256; };
inline std::string Concat(const std::string& left, const std::string& right) { return left + right; };
#endif

namespace s84 {
namespace ctcode {
namespace transpiler {
namespace nodejstranspiler {
namespace ctcode {

class ParameterDeclaration;
class IntegerReference;
class NodeJSTranspiler;

class ParameterDeclaration {
public:
    ParameterDeclaration();
    inline ~ParameterDeclaration() {}

    std::string GetType();
    void SetType(std::string input);
    std::string GetName();
    void SetName(std::string input);

private:
    std::string type;
    std::string name;
};

class IntegerReference {
public:
    IntegerReference();
    inline ~IntegerReference() {}

    int GetValue();
    void SetValue(int value);

private:
    int value;
};

class NodeJSTranspiler : public s84::ctcode::transpiler::ctcode::Transpiler {
public:
    NodeJSTranspiler();
    inline ~NodeJSTranspiler() {}

    int GetBaseIndentation();
    std::string GetCallName(OmniPointer<s84::ctcode::dbnf::ctcode::Name> name);
    std::string GetVariableName(OmniPointer<s84::ctcode::dbnf::ctcode::Name> name);
    std::string GetVariableChainNameTail(OmniPointer<s84::ctcode::dbnf::ctcode::NameTail> tail);
    std::string GetVariableChain(OmniPointer<s84::ctcode::dbnf::ctcode::QualfiedName> l_value);
    std::string ConvertCall(std::vector<std::string> name_chain, std::vector<std::string> parameters);
    std::string ConvertAllocate(std::string type);
    std::string ConvertByte(std::string high, std::string low);
    std::string ConvertDecimal(std::string decimal);
    std::string ConvertNumber(std::string number);
    std::string ConvertBoolean(std::string boolean);
    std::string ConvertVariable(std::string variable);
    std::string ConvertString(std::string literal);
    std::string UnaryOperator(std::string op, std::string r_value);
    std::string BinaryOperator(std::string op, std::string r_value_l, std::string r_value_r);
    std::string GetTypeName(OmniPointer<s84::ctcode::dbnf::ctcode::Name> name);
    std::string GetDimensionalType(std::string singleton_type, int dimensions);
    std::string GetMapType(std::string singleton_type);
    std::string GetPrimativeType(std::string c_t_type);
    std::string GetQualifiedTypeName(std::vector<OmniPointer<s84::ctcode::dbnf::ctcode::Name>> name_parts);
    void BeginProcessingCTCodeFile();
    void ProcessExdef(std::string exdef);
    void ProcessUnmanagedType(std::string unmanaged_type);
    void BeginProcessingInterface(std::string interface_name);
    void ProcessInterfaceFunctionDeclaration(std::string return_type, std::string function_name, std::vector<OmniPointer<ParameterDeclaration>> parameters);
    void FinishProcessingInterface(std::string interface_name);
    void BeginProcessingClass(std::string class_name, std::string implementing);
    void BeginProcessingClassFunctionDefinition(std::string return_type, std::string function_name, std::vector<OmniPointer<ParameterDeclaration>> parameters);
    void BeginProcessCodeBlock(int indent);
    void FinishProcessCodeBlock(int indent);
    void BeginProcessConditional(int indent, std::string r_value);
    void ProcessElse(int indent);
    void FinishProcessConditional(int indent, std::string r_value);
    void BeginProcessLoop(int indent, std::string r_value);
    void FinishProcessLoop(int indent, std::string r_value);
    void ProcessRtn(int indent, std::string r_value);
    void ProcessDeclaration(int indent, std::string type, std::string l_value, std::string r_value);
    void ProcessAssignment(int indent, std::string l_value, std::string r_value);
    void ProcessCall(int indent, std::string call);
    void FinishProcessingClassFunctionDefinition(std::string return_type, std::string function_name, std::vector<OmniPointer<ParameterDeclaration>> parameters);
    void ProcessClassMemberDeclaration(std::string member_type, std::string member_name);
    void FinishProcessingClass(std::string class_name, std::string implementing);
    void WriteCommonFunctions(OmniPointer<s84::ctcode::system::ctcode::OutputStream> destination_file);
    void FinishProcessingCTCodeFile();
    bool BeginsWith(std::string prefix, std::string value);
    std::string GetDefault(std::string javascript_type);
    std::string MakeParametersString(std::vector<OmniPointer<ParameterDeclaration>> parameters);
    std::string StripDot(std::string input);
    void WriteLines(OmniPointer<s84::ctcode::system::ctcode::OutputStream> destination, std::vector<std::string> lines);
    int Transpile(OmniPointer<s84::ctcode::system::ctcode::System> system, OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file, std::string base_name);
    void ProcessCTCodeFile(OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file);
    void ProcessExdefs(OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file);
    void ProcessUnmanagedTypes(OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file);
    void ProcessDefinitions(OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file);
    std::vector<OmniPointer<ParameterDeclaration>> GetParameters(OmniPointer<s84::ctcode::dbnf::ctcode::ParameterListDef> parameter_list_def);
    void ProcessInterfaceDefinition(OmniPointer<s84::ctcode::dbnf::ctcode::InterfaceDef> interface_definition);
    void ProcessClassDefinition(OmniPointer<s84::ctcode::dbnf::ctcode::ClassDef> class_definition);
    void ProcessInstructionInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::Instruction> instruction);
    void ProcessCodeBlockInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::CodeBlock> code_block);
    void ProcessConditionalInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::Conditional> conditional);
    void ProcessLoopInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::Loop> loop);
    void ProcessRtnInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::Return> rtn);
    void ProcessDeclarationInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::Declaration> declaration);
    void ProcessAssignmentInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::Assignment> assignment);
    void ProcessCallInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::Call> call);
    std::string ConvertCallInternal(OmniPointer<s84::ctcode::dbnf::ctcode::Call> call);
    std::string GetSingletonType(OmniPointer<s84::ctcode::dbnf::ctcode::SingletonType> singleton_type);
    std::string GetRValueSingleBasisInternal(OmniPointer<s84::ctcode::dbnf::ctcode::RValueSingle> r_value_single);
    std::string GetRValueSingleInternal(OmniPointer<s84::ctcode::dbnf::ctcode::RValueSingle> r_value_single);
    void PopulateOperatorPrecedent();
    bool OverPrecedent(std::string op, int precedent);
    std::string BinaryOperatorPrecedentMerge(std::vector<std::string> values, std::vector<std::string> operators, OmniPointer<IntegerReference> index, int precedent);
    std::string GetRValueInternal(OmniPointer<s84::ctcode::dbnf::ctcode::RValue> r_value);
    std::string GetQualifiedTypeNameInternal(OmniPointer<s84::ctcode::dbnf::ctcode::QualfiedName> qualified_name);
    std::string GetType(OmniPointer<s84::ctcode::dbnf::ctcode::ValueType> type);
    std::string Indentation(int indent);
    std::string SnakeCaseToCamelCase(std::string snake_case);
    std::string CamelCaseToSnakeCase(std::string camel_case);
    bool IsUpper(std::string character);
    bool IsDigit(std::string character);
    std::string ToLower(std::string input);
    std::string CharacterToLower(std::string input);
    std::string ToUpper(std::string input);
    std::string CharacterToUpper(std::string input);

private:
    OmniPointer<s84::ctcode::system::ctcode::System> system;
    OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file;
    std::string base_name;
    std::vector<std::vector<std::string>> operator_precedent;
    OmniPointer<s84::ctcode::system::ctcode::OutputStream> logger;
    std::vector<std::string> imports;
    std::string current_interface;
    std::vector<std::string> interface_definitions;
    std::string current_class;
    std::vector<std::string> class_definitions;
    std::vector<std::string> class_init;
    std::vector<std::string> class_functions;
};

};
};
};
};
};

#endif
