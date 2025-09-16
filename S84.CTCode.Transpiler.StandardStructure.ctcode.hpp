#ifndef S84_CTCODE_TRANSPILER_STANDARDSTRUCTURE_CTCODE_H
#define S84_CTCODE_TRANSPILER_STANDARDSTRUCTURE_CTCODE_H

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
namespace standardstructure {
namespace ctcode {

class TargetSpecificFunctions;

class ParameterDeclaration;
class IntegerReference;
class StandardStructure;

class TargetSpecificFunctions {
public:
    virtual void Initialize() = 0;
    virtual void SetSystem(OmniPointer<s84::ctcode::system::ctcode::System> system) = 0;
    virtual void SetCTCodeFile(OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file) = 0;
    virtual void SetBaseName(std::string base_name) = 0;
    virtual void SetLogger(OmniPointer<s84::ctcode::system::ctcode::OutputStream> logger) = 0;
    virtual int GetBaseIndentation() = 0;
    virtual std::string GetCallName(std::string name) = 0;
    virtual std::string GetVariableName(std::string name) = 0;
    virtual std::string GetVariableChain(std::vector<std::string> name_parts) = 0;
    virtual std::string ConvertCall(std::vector<std::string> name_chain, std::vector<std::string> parameters) = 0;
    virtual std::string ConvertAllocate(std::string type) = 0;
    virtual std::string ConvertByte(std::string high, std::string low) = 0;
    virtual std::string ConvertDecimal(std::string decimal) = 0;
    virtual std::string ConvertNumber(std::string number) = 0;
    virtual std::string ConvertBoolean(std::string boolean) = 0;
    virtual std::string ConvertVariable(std::string variable) = 0;
    virtual std::string ConvertString(std::string literal) = 0;
    virtual std::string UnaryOperator(std::string op, std::string r_value) = 0;
    virtual std::string BinaryOperator(std::string op, std::string r_value_l, std::string r_value_r) = 0;
    virtual std::string GetTypeName(std::string name) = 0;
    virtual std::string GetDimensionalType(std::string singleton_type, int dimensions) = 0;
    virtual std::string GetMapType(std::string singleton_type) = 0;
    virtual std::string GetPrimativeType(std::string c_t_type) = 0;
    virtual std::string GetDefinedType(std::string c_t_type) = 0;
    virtual std::string GetQualifiedTypeName(std::vector<std::string> name_parts) = 0;
    virtual void BeginProcessingCTCodeFile() = 0;
    virtual void FinishProcessingCTCodeFile() = 0;
    virtual void ProcessExdef(std::string exdef) = 0;
    virtual void ProcessUnmanagedType(std::string unmanaged_type) = 0;
    virtual void BeginProcessingInterface(std::string interface_name) = 0;
    virtual void ProcessInterfaceFunctionDeclaration(std::string return_type, std::string function_name, std::vector<OmniPointer<ParameterDeclaration>> parameters) = 0;
    virtual void FinishProcessingInterface(std::string interface_name) = 0;
    virtual void BeginProcessingClass(std::string class_name, std::string implementing) = 0;
    virtual void BeginProcessingClassFunctionDefinition(std::string return_type, std::string function_name, std::vector<OmniPointer<ParameterDeclaration>> parameters) = 0;
    virtual void BeginProcessCodeBlock(int indent) = 0;
    virtual void FinishProcessCodeBlock(int indent) = 0;
    virtual void BeginProcessConditional(int indent, std::string r_value) = 0;
    virtual void ProcessElse(int indent) = 0;
    virtual void FinishProcessConditional(int indent, std::string r_value) = 0;
    virtual void BeginProcessLoop(int indent, std::string r_value) = 0;
    virtual void FinishProcessLoop(int indent, std::string r_value) = 0;
    virtual void ProcessRtn(int indent, std::string r_value) = 0;
    virtual void ProcessDeclaration(int indent, std::string type, std::string l_value, std::string r_value) = 0;
    virtual void ProcessAssignment(int indent, std::string l_value, std::string r_value) = 0;
    virtual void ProcessCall(int indent, std::string call) = 0;
    virtual void FinishProcessingClassFunctionDefinition(std::string return_type, std::string function_name, std::vector<OmniPointer<ParameterDeclaration>> parameters) = 0;
    virtual void ProcessClassMemberDeclaration(std::string member_type, std::string member_name) = 0;
    virtual void FinishProcessingClass(std::string class_name, std::string implementing) = 0;
};

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

class StandardStructure : public s84::ctcode::transpiler::ctcode::Transpiler {
public:
    StandardStructure();
    inline ~StandardStructure() {}

    void SetTargetSpecificFunctions(OmniPointer<TargetSpecificFunctions> target_specific_functions);
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
    std::string GetVariableChainInternal(OmniPointer<s84::ctcode::dbnf::ctcode::QualfiedName> qualified_name);
    std::string GetType(OmniPointer<s84::ctcode::dbnf::ctcode::ValueType> type);
    std::string NameToString(OmniPointer<s84::ctcode::dbnf::ctcode::Name> name);

private:
    OmniPointer<s84::ctcode::system::ctcode::System> system;
    OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file;
    std::string base_name;
    std::vector<std::vector<std::string>> operator_precedent;
    OmniPointer<s84::ctcode::system::ctcode::OutputStream> logger;
    OmniPointer<TargetSpecificFunctions> target_specific_functions;
};

};
};
};
};
};

#endif
