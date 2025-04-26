#ifndef S84_CTCODE_CPPTRANSPILER_CTCODE_H
#define S84_CTCODE_CPPTRANSPILER_CTCODE_H

#include "S84.CTCode.dbnf.hpp"

#include <cstring>
#include <list>
#include <string>
#include <vector>

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

template<typename T>
inline int Size(std::vector<T> input) { return input.size(); };
template<typename T>
inline T Element(std::vector<T> input, int element) { return input.at(element); };
template<typename T>
inline std::vector<T> Append(std::vector<T> input, T element) { input.push_back(element); return input; };
inline int Length(std::string input) { return (int)input.length(); };
inline std::string At(std::string input, int index) { return input.substr(index, 1); };
inline std::string Concat(std::string left, std::string right) { return left + right; };

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

    void GenerateHeader(s84::ctcode::dbnf::CTCodeFile* ctcode_file, OutputStream* header, std::vector<std::string> base_name_tokens);
    void WriteForwardDeclaration(s84::ctcode::dbnf::CTCodeFile* ctcode_file, OutputStream* header);
    void WriteClassDeclarations(s84::ctcode::dbnf::CTCodeFile* ctcode_file, OutputStream* header);
    void WriteInterfaceDeclaration(s84::ctcode::dbnf::InterfaceDef* interface_definition, OutputStream* header);
    void WriteClassDeclaration(s84::ctcode::dbnf::ClassDef* class_definition, OutputStream* header);
    void GenerateImplementation(s84::ctcode::dbnf::CTCodeFile* ctcode_file, OutputStream* implementation, std::string base_name, std::vector<std::string> base_name_tokens);
    void WriteFunctionDefinitions(s84::ctcode::dbnf::CTCodeFile* ctcode_file, OutputStream* implementation);
    void WriteClassDefinition(s84::ctcode::dbnf::ClassDef* class_definition, OutputStream* implementation, bool first_class_definition);
    void WriteInstruction(int indent, OutputStream* implementation, s84::ctcode::dbnf::Instruction* instruction, bool add_newline_after_code_block);
    void WriteCodeBlock(int indent, OutputStream* implementation, s84::ctcode::dbnf::CodeBlock* code_block, bool add_newline_after_code_block);
    void WriteConditional(int indent, OutputStream* implementation, s84::ctcode::dbnf::Conditional* conditional, bool add_newline_after_code_block);
    void WriteLoop(int indent, OutputStream* implementation, s84::ctcode::dbnf::Loop* loop, bool add_newline_after_code_block);
    void WriteRtn(int indent, OutputStream* implementation, s84::ctcode::dbnf::Return* rtn);
    void WriteDeclaration(int indent, OutputStream* implementation, s84::ctcode::dbnf::Declaration* declaration);
    void WriteAssignment(int indent, OutputStream* implementation, s84::ctcode::dbnf::Assignment* assignment);
    void WriteCall(int indent, OutputStream* implementation, s84::ctcode::dbnf::Call* call);
    std::string GetExdefHeaderString(s84::ctcode::dbnf::QualfiedName* exdef_name);
    std::string Indentation(int indent);
    std::string GetRValueSingleString(s84::ctcode::dbnf::RValueSingle* r_value_single);
    std::string GetRValueSingleUnaryString(s84::ctcode::dbnf::RValueSingle* r_value_single);
    std::string GetCallString(s84::ctcode::dbnf::Call* call);
    std::string GetRValueSingleCoreString(s84::ctcode::dbnf::RValueSingle* r_value_single);
    std::string GetOperator(s84::ctcode::dbnf::BinaryOperator* op);
    std::string GetRValueTail(s84::ctcode::dbnf::RValueTail* r_value_tail);
    std::string GetRValueString(s84::ctcode::dbnf::RValue* r_value);
    std::string GetVariableDefinition(s84::ctcode::dbnf::ValueType* type, s84::ctcode::dbnf::Name* name);
    std::string GetParameterString(s84::ctcode::dbnf::ParameterListDef* parameter);
    std::string GenerateParameterListTail(s84::ctcode::dbnf::ParameterListDef* parameters);
    std::string GenerateParameterList(s84::ctcode::dbnf::ParameterListDef* parameters);
    std::string GenerateCallingParameterList(s84::ctcode::dbnf::ParameterList* parameters);
    std::string GetCallingParameterString(s84::ctcode::dbnf::ParameterList* parameter);
    std::string GenerateCallingParameterListTail(s84::ctcode::dbnf::ParameterList* parameters);
    std::string GetType(s84::ctcode::dbnf::ValueType* value_type);
    std::string GetDimensionalType(s84::ctcode::dbnf::DimensionalType* dimensional_type);
    std::string GetDimensionalPrefix(int dimensional_notes);
    std::string GetDimensionalSuffix(int dimensional_notes);
    std::string GetSingletonType(s84::ctcode::dbnf::SingletonType* singleton_type);
    std::string GetDefinedType(s84::ctcode::dbnf::QualfiedName* qualified_name);
    std::string GetDefinedTypeTail(s84::ctcode::dbnf::NameTail* name_tail);
    std::string GenerateClassName(s84::ctcode::dbnf::Name* name_node);
    std::string GenerateVariableName(s84::ctcode::dbnf::Name* name_node);
    std::string GenerateCallName(s84::ctcode::dbnf::Name* name_node);
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
};
};
};
};
};

#endif
