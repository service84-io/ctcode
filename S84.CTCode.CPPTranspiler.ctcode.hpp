#ifndef S84_CTCODE_CPPTRANSPILER_CTCODE_H
#define S84_CTCODE_CPPTRANSPILER_CTCODE_H

#include "S84.CTCode.dbnf.hpp"

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
    OmniPointer(std::shared_ptr<T> value) { value_raw = NULL; value_shared = value; }

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

private:
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
inline void SetKV(std::unordered_map<std::string, T>& input, std::string key, T element)
{
    input.erase(key);
    input.insert(std::pair<std::string, T>(key, element));
}
template<typename T>
inline bool HasKV(const std::unordered_map<std::string, T>& input, std::string key)
{
    typename std::unordered_map<std::string, T>::iterator beginning = input.find(key);
    return beginning != input.end();
}
template<typename T>
inline T GetKV(const std::unordered_map<std::string, T>& input, std::string key) { return input.at(key); }
inline int Length(std::string input) { return (int)input.length(); };
inline std::string At(std::string input, int index) { return input.substr(index, 1); };
inline int IntAt(std::string input, int index) { return (input.at(index) + 256) % 256; };
inline std::string Concat(std::string left, std::string right) { return left + right; };
#endif

namespace s84
{
namespace ctcode
{
namespace cpptranspiler
{
namespace ctcode
{
class OutputStream;
class CPPTranspilerCTCodeLogic;


class OutputStream
{
public:
    inline OutputStream() {};
    inline ~OutputStream() {};

    virtual void WriteLine(std::string line) = 0;
};

class CPPTranspilerCTCodeLogic
{
public:
    inline CPPTranspilerCTCodeLogic() {};
    inline ~CPPTranspilerCTCodeLogic() {};

    void SetSavedUnmanagedTypes(std::vector<std::string> value);
    bool IsUnmanagedType(std::string type_name);
    void GenerateHeader(OmniPointer<s84::ctcode::dbnf::CTCodeFile> ctcode_file, OmniPointer<OutputStream> header, std::vector<std::string> base_name_tokens);
    void WriteCTCodeCommonFunctions(OmniPointer<OutputStream> header);
    void WriteForwardDeclaration(OmniPointer<s84::ctcode::dbnf::CTCodeFile> ctcode_file, OmniPointer<OutputStream> header);
    void WriteClassDeclarations(OmniPointer<s84::ctcode::dbnf::CTCodeFile> ctcode_file, OmniPointer<OutputStream> header);
    void WriteInterfaceDeclaration(OmniPointer<s84::ctcode::dbnf::InterfaceDef> interface_definition, OmniPointer<OutputStream> header);
    void WriteClassDeclaration(s84::ctcode::dbnf::ClassDef* class_definition, OmniPointer<OutputStream> header);
    void GenerateImplementation(OmniPointer<s84::ctcode::dbnf::CTCodeFile> ctcode_file, OmniPointer<OutputStream> implementation, std::string base_name, std::vector<std::string> base_name_tokens);
    void WriteFunctionDefinitions(OmniPointer<s84::ctcode::dbnf::CTCodeFile> ctcode_file, OmniPointer<OutputStream> implementation);
    void WriteClassDefinition(s84::ctcode::dbnf::ClassDef* class_definition, OmniPointer<OutputStream> implementation);
    void WriteInstruction(int indent, OmniPointer<OutputStream> implementation, s84::ctcode::dbnf::Instruction* instruction, bool add_newline_after_code_block);
    void WriteCodeBlock(int indent, OmniPointer<OutputStream> implementation, OmniPointer<s84::ctcode::dbnf::CodeBlock> code_block, bool add_newline_after_code_block);
    void WriteConditional(int indent, OmniPointer<OutputStream> implementation, OmniPointer<s84::ctcode::dbnf::Conditional> conditional, bool add_newline_after_code_block);
    void WriteLoop(int indent, OmniPointer<OutputStream> implementation, OmniPointer<s84::ctcode::dbnf::Loop> loop, bool add_newline_after_code_block);
    void WriteRtn(int indent, OmniPointer<OutputStream> implementation, OmniPointer<s84::ctcode::dbnf::Return> rtn);
    void WriteDeclaration(int indent, OmniPointer<OutputStream> implementation, OmniPointer<s84::ctcode::dbnf::Declaration> declaration);
    void WriteAssignment(int indent, OmniPointer<OutputStream> implementation, OmniPointer<s84::ctcode::dbnf::Assignment> assignment);
    void WriteCall(int indent, OmniPointer<OutputStream> implementation, OmniPointer<s84::ctcode::dbnf::Call> call);
    std::string GetExdefHeaderString(OmniPointer<s84::ctcode::dbnf::QualfiedName> exdef_name);
    std::vector<std::string> GetUnmanagedTypes(std::vector<s84::ctcode::dbnf::UnmanagedType*> unmanaged_types);
    std::string Indentation(int indent);
    std::string GetRValueSingleString(OmniPointer<s84::ctcode::dbnf::RValueSingle> r_value_single);
    std::string GetRValueSingleUnaryString(OmniPointer<s84::ctcode::dbnf::RValueSingle> r_value_single);
    std::string GetCallString(OmniPointer<s84::ctcode::dbnf::Call> call);
    std::string GetRValueSingleCoreString(OmniPointer<s84::ctcode::dbnf::RValueSingle> r_value_single);
    std::string GetOperator(OmniPointer<s84::ctcode::dbnf::BinaryOperator> op);
    std::string GetRValueTail(OmniPointer<s84::ctcode::dbnf::RValueTail> r_value_tail);
    std::string GetRValueString(OmniPointer<s84::ctcode::dbnf::RValue> r_value);
    std::string GetVariableDefinition(OmniPointer<s84::ctcode::dbnf::ValueType> type, OmniPointer<s84::ctcode::dbnf::Name> name);
    std::string GetParameterString(OmniPointer<s84::ctcode::dbnf::ParameterListDef> parameter);
    std::string GenerateParameterListTail(OmniPointer<s84::ctcode::dbnf::ParameterListDef> parameters);
    std::string GenerateParameterList(OmniPointer<s84::ctcode::dbnf::ParameterListDef> parameters);
    std::string GenerateCallingParameterList(OmniPointer<s84::ctcode::dbnf::ParameterList> parameters);
    std::string GetCallingParameterString(OmniPointer<s84::ctcode::dbnf::ParameterList> parameter);
    std::string GenerateCallingParameterListTail(OmniPointer<s84::ctcode::dbnf::ParameterList> parameters);
    std::string GetType(OmniPointer<s84::ctcode::dbnf::ValueType> value_type);
    std::string GetDimensionalType(OmniPointer<s84::ctcode::dbnf::DimensionalType> dimensional_type);
    std::string GetDimensionalPrefix(int dimensional_notes);
    std::string GetDimensionalSuffix(int dimensional_notes);
    std::string GetMapType(OmniPointer<s84::ctcode::dbnf::MapType> map_type);
    std::string GetSingletonType(OmniPointer<s84::ctcode::dbnf::SingletonType> singleton_type);
    std::string GetDefinedType(OmniPointer<s84::ctcode::dbnf::QualfiedName> qualified_name);
    std::string GetRawDefinedType(OmniPointer<s84::ctcode::dbnf::QualfiedName> qualified_name);
    std::string GetRawDefinedTypeTail(OmniPointer<s84::ctcode::dbnf::NameTail> name_tail);
    std::string GenerateClassName(OmniPointer<s84::ctcode::dbnf::Name> name_node);
    std::string GenerateVariableName(OmniPointer<s84::ctcode::dbnf::Name> name_node);
    std::string GenerateCallName(OmniPointer<s84::ctcode::dbnf::Name> name_node);
    std::vector<std::string> TokenizeBaseName(std::string name);
    std::string GenerateGuardName(std::vector<std::string> base_name_tokens);
    std::string SnakeCaseToCamelCase(std::string snake_case);
    std::string CamelCaseToSnakeCase(std::string camel_case);
    bool IsUpper(std::string character);
    bool IsDigit(std::string character);
    std::string ToLower(std::string input);
    std::string CharacterToLower(std::string input);
    std::string ToUpper(std::string input);
    std::string CharacterToUpper(std::string input);

private:
    std::vector<std::string> saved_unmanaged_types;
};
};
};
};
};

#endif
