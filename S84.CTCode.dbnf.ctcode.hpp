#ifndef S84_CTCODE_DBNF_CTCODE_H
#define S84_CTCODE_DBNF_CTCODE_H


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
inline void SetKV(std::unordered_map<std::string, T>& input, const std::string& key, T element)
{
    input.erase(key);
    input.insert(std::pair<std::string, T>(key, element));
}
template<typename T>
inline bool HasKV(const std::unordered_map<std::string, T>& input, const std::string& key)
{
    typename std::unordered_map<std::string, T>::iterator beginning = input.find(key);
    return beginning != input.end();
}
template<typename T>
inline T GetKV(const std::unordered_map<std::string, T>& input, const std::string& key) { return input.at(key); }
inline int Length(const std::string& input) { return (int)input.length(); };
inline std::string At(const std::string& input, int index) { return input.substr(index, 1); };
inline int IntAt(const std::string& input, int index) { return (input.at(index) + 256) % 256; };
inline std::string Concat(const std::string& left, const std::string& right) { return left + right; };
#endif

namespace s84
{
namespace ctcode
{
namespace dbnf
{
namespace ctcode
{
class StringParser;
class StringResult;
class StringListResult;
class String;
class CharacterParser;
class CharacterResult;
class CharacterListResult;
class Character;
class CharacterRangeParser;
class CharacterRangeResult;
class CharacterRangeListResult;
class CharacterRange;
class ParserNetwork;
class DBNFOmniType;
class DBNFOmniTypeResult;
class DBNFOmniTypeListResult;
class LargeString;
class LengthString;
class CTCodeFileParser;
class CTCodeFileResult;
class CTCodeFileListResult;
class CTCodeFile;
class ExternalDefinitionParser;
class ExternalDefinitionResult;
class ExternalDefinitionListResult;
class ExternalDefinition;
class UnmanagedTypeParser;
class UnmanagedTypeResult;
class UnmanagedTypeListResult;
class UnmanagedType;
class DefinitionParser;
class DefinitionResult;
class DefinitionListResult;
class Definition;
class InterfaceDefParser;
class InterfaceDefResult;
class InterfaceDefListResult;
class InterfaceDef;
class ClassDefParser;
class ClassDefResult;
class ClassDefListResult;
class ClassDef;
class ContentDeclarationParser;
class ContentDeclarationResult;
class ContentDeclarationListResult;
class ContentDeclaration;
class ContentDefinitionParser;
class ContentDefinitionResult;
class ContentDefinitionListResult;
class ContentDefinition;
class PrimativeTypeParser;
class PrimativeTypeResult;
class PrimativeTypeListResult;
class PrimativeType;
class DefinedTypeParser;
class DefinedTypeResult;
class DefinedTypeListResult;
class DefinedType;
class SingletonTypeParser;
class SingletonTypeResult;
class SingletonTypeListResult;
class SingletonType;
class DimensionalNoteParser;
class DimensionalNoteResult;
class DimensionalNoteListResult;
class DimensionalNote;
class DimensionalTypeParser;
class DimensionalTypeResult;
class DimensionalTypeListResult;
class DimensionalType;
class MapNoteParser;
class MapNoteResult;
class MapNoteListResult;
class MapNote;
class MapTypeParser;
class MapTypeResult;
class MapTypeListResult;
class MapType;
class ValueTypeParser;
class ValueTypeResult;
class ValueTypeListResult;
class ValueType;
class ParameterListDefParser;
class ParameterListDefResult;
class ParameterListDefListResult;
class ParameterListDef;
class ParameterListParser;
class ParameterListResult;
class ParameterListListResult;
class ParameterList;
class CodeBlockParser;
class CodeBlockResult;
class CodeBlockListResult;
class CodeBlock;
class DeclarationAssignParser;
class DeclarationAssignResult;
class DeclarationAssignListResult;
class DeclarationAssign;
class DeclarationParser;
class DeclarationResult;
class DeclarationListResult;
class Declaration;
class AssignmentParser;
class AssignmentResult;
class AssignmentListResult;
class Assignment;
class ReturnParser;
class ReturnResult;
class ReturnListResult;
class Return;
class ElseTailParser;
class ElseTailResult;
class ElseTailListResult;
class ElseTail;
class ConditionalParser;
class ConditionalResult;
class ConditionalListResult;
class Conditional;
class LoopParser;
class LoopResult;
class LoopListResult;
class Loop;
class CallParser;
class CallResult;
class CallListResult;
class Call;
class AllocateParser;
class AllocateResult;
class AllocateListResult;
class Allocate;
class InstructionParser;
class InstructionResult;
class InstructionListResult;
class Instruction;
class RValueSingleParser;
class RValueSingleResult;
class RValueSingleListResult;
class RValueSingle;
class RValueTailParser;
class RValueTailResult;
class RValueTailListResult;
class RValueTail;
class RValueParser;
class RValueResult;
class RValueListResult;
class RValue;
class BinaryOperatorParser;
class BinaryOperatorResult;
class BinaryOperatorListResult;
class BinaryOperator;
class UnaryOperatorParser;
class UnaryOperatorResult;
class UnaryOperatorListResult;
class UnaryOperator;
class CommentParser;
class CommentResult;
class CommentListResult;
class Comment;
class CommentCharacterParser;
class CommentCharacterResult;
class CommentCharacterListResult;
class CommentCharacter;
class QualfiedNameParser;
class QualfiedNameResult;
class QualfiedNameListResult;
class QualfiedName;
class NameTailParser;
class NameTailResult;
class NameTailListResult;
class NameTail;
class NameParser;
class NameResult;
class NameListResult;
class Name;
class NameCharacterParser;
class NameCharacterResult;
class NameCharacterListResult;
class NameCharacter;
class BooleanParser;
class BooleanResult;
class BooleanListResult;
class Boolean;
class ByteParser;
class ByteResult;
class ByteListResult;
class Byte;
class ByteDigitParser;
class ByteDigitResult;
class ByteDigitListResult;
class ByteDigit;
class NegativeParser;
class NegativeResult;
class NegativeListResult;
class Negative;
class DecimalParser;
class DecimalResult;
class DecimalListResult;
class Decimal;
class NumberParser;
class NumberResult;
class NumberListResult;
class Number;
class DigitParser;
class DigitResult;
class DigitListResult;
class Digit;
class LiteralParser;
class LiteralResult;
class LiteralListResult;
class Literal;
class LiteralCharacterParser;
class LiteralCharacterResult;
class LiteralCharacterListResult;
class LiteralCharacter;
class WhitespaceParser;
class WhitespaceResult;
class WhitespaceListResult;
class Whitespace;


class StringParser
{
public:
    inline StringParser() {};
    inline ~StringParser() {};

    bool ParseSingleSave(OmniPointer<LengthString> index, std::string value, OmniPointer<StringResult> result);
    bool ParseSingle(OmniPointer<LengthString> index, std::string value);
};

class StringResult
{
public:
    inline StringResult() {};
    inline ~StringResult() {};

    void SetValue(OmniPointer<String> new_value);
    OmniPointer<String> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<String> value;
    bool result;
};

class StringListResult
{
public:
    inline StringListResult() {};
    inline ~StringListResult() {};

    void SetValue(std::vector<OmniPointer<String>> new_value);
    std::vector<OmniPointer<String>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<String>> value;
    bool result;
};

class String
{
public:
    inline String() {};
    inline ~String() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();

private:
    OmniPointer<LengthString> length_string;
};

class CharacterParser
{
public:
    inline CharacterParser() {};
    inline ~CharacterParser() {};

    bool ParseSingle(OmniPointer<LengthString> index, int value);
};

class CharacterResult
{
public:
    inline CharacterResult() {};
    inline ~CharacterResult() {};

    void SetValue(OmniPointer<Character> new_value);
    OmniPointer<Character> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<Character> value;
    bool result;
};

class CharacterListResult
{
public:
    inline CharacterListResult() {};
    inline ~CharacterListResult() {};

    void SetValue(std::vector<OmniPointer<Character>> new_value);
    std::vector<OmniPointer<Character>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<Character>> value;
    bool result;
};

class Character
{
public:
    inline Character() {};
    inline ~Character() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();

private:
    OmniPointer<LengthString> length_string;
};

class CharacterRangeParser
{
public:
    inline CharacterRangeParser() {};
    inline ~CharacterRangeParser() {};

    bool ParseSingle(OmniPointer<LengthString> index, int low_value, int high_value);
};

class CharacterRangeResult
{
public:
    inline CharacterRangeResult() {};
    inline ~CharacterRangeResult() {};

    void SetValue(OmniPointer<CharacterRange> new_value);
    OmniPointer<CharacterRange> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<CharacterRange> value;
    bool result;
};

class CharacterRangeListResult
{
public:
    inline CharacterRangeListResult() {};
    inline ~CharacterRangeListResult() {};

    void SetValue(std::vector<OmniPointer<CharacterRange>> new_value);
    std::vector<OmniPointer<CharacterRange>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<CharacterRange>> value;
    bool result;
};

class CharacterRange
{
public:
    inline CharacterRange() {};
    inline ~CharacterRange() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();

private:
    OmniPointer<LengthString> length_string;
};

class ParserNetwork
{
public:
    inline ParserNetwork() {};
    inline ~ParserNetwork() {};

    OmniPointer<CTCodeFileParser> GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> GetDefinitionParser();
    OmniPointer<InterfaceDefParser> GetInterfaceDefParser();
    OmniPointer<ClassDefParser> GetClassDefParser();
    OmniPointer<ContentDeclarationParser> GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> GetMapNoteParser();
    OmniPointer<MapTypeParser> GetMapTypeParser();
    OmniPointer<ValueTypeParser> GetValueTypeParser();
    OmniPointer<ParameterListDefParser> GetParameterListDefParser();
    OmniPointer<ParameterListParser> GetParameterListParser();
    OmniPointer<CodeBlockParser> GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> GetDeclarationParser();
    OmniPointer<AssignmentParser> GetAssignmentParser();
    OmniPointer<ReturnParser> GetReturnParser();
    OmniPointer<ElseTailParser> GetElseTailParser();
    OmniPointer<ConditionalParser> GetConditionalParser();
    OmniPointer<LoopParser> GetLoopParser();
    OmniPointer<CallParser> GetCallParser();
    OmniPointer<AllocateParser> GetAllocateParser();
    OmniPointer<InstructionParser> GetInstructionParser();
    OmniPointer<RValueSingleParser> GetRValueSingleParser();
    OmniPointer<RValueTailParser> GetRValueTailParser();
    OmniPointer<RValueParser> GetRValueParser();
    OmniPointer<BinaryOperatorParser> GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> GetUnaryOperatorParser();
    OmniPointer<CommentParser> GetCommentParser();
    OmniPointer<CommentCharacterParser> GetCommentCharacterParser();
    OmniPointer<QualfiedNameParser> GetQualfiedNameParser();
    OmniPointer<NameTailParser> GetNameTailParser();
    OmniPointer<NameParser> GetNameParser();
    OmniPointer<NameCharacterParser> GetNameCharacterParser();
    OmniPointer<BooleanParser> GetBooleanParser();
    OmniPointer<ByteParser> GetByteParser();
    OmniPointer<ByteDigitParser> GetByteDigitParser();
    OmniPointer<NegativeParser> GetNegativeParser();
    OmniPointer<DecimalParser> GetDecimalParser();
    OmniPointer<NumberParser> GetNumberParser();
    OmniPointer<DigitParser> GetDigitParser();
    OmniPointer<LiteralParser> GetLiteralParser();
    OmniPointer<LiteralCharacterParser> GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> GetWhitespaceParser();
    OmniPointer<StringParser> GetStringParser();
    OmniPointer<CharacterParser> GetCharacterParser();
    OmniPointer<CharacterRangeParser> GetCharacterRangeParser();
    void Initialize();

private:
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_field;
    OmniPointer<ExternalDefinitionParser> external_definition_parser_field;
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_field;
    OmniPointer<DefinitionParser> definition_parser_field;
    OmniPointer<InterfaceDefParser> interface_def_parser_field;
    OmniPointer<ClassDefParser> class_def_parser_field;
    OmniPointer<ContentDeclarationParser> content_declaration_parser_field;
    OmniPointer<ContentDefinitionParser> content_definition_parser_field;
    OmniPointer<PrimativeTypeParser> primative_type_parser_field;
    OmniPointer<DefinedTypeParser> defined_type_parser_field;
    OmniPointer<SingletonTypeParser> singleton_type_parser_field;
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_field;
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_field;
    OmniPointer<MapNoteParser> map_note_parser_field;
    OmniPointer<MapTypeParser> map_type_parser_field;
    OmniPointer<ValueTypeParser> value_type_parser_field;
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_field;
    OmniPointer<ParameterListParser> parameter_list_parser_field;
    OmniPointer<CodeBlockParser> code_block_parser_field;
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_field;
    OmniPointer<DeclarationParser> declaration_parser_field;
    OmniPointer<AssignmentParser> assignment_parser_field;
    OmniPointer<ReturnParser> return_parser_field;
    OmniPointer<ElseTailParser> else_tail_parser_field;
    OmniPointer<ConditionalParser> conditional_parser_field;
    OmniPointer<LoopParser> loop_parser_field;
    OmniPointer<CallParser> call_parser_field;
    OmniPointer<AllocateParser> allocate_parser_field;
    OmniPointer<InstructionParser> instruction_parser_field;
    OmniPointer<RValueSingleParser> r_value_single_parser_field;
    OmniPointer<RValueTailParser> r_value_tail_parser_field;
    OmniPointer<RValueParser> r_value_parser_field;
    OmniPointer<BinaryOperatorParser> binary_operator_parser_field;
    OmniPointer<UnaryOperatorParser> unary_operator_parser_field;
    OmniPointer<CommentParser> comment_parser_field;
    OmniPointer<CommentCharacterParser> comment_character_parser_field;
    OmniPointer<QualfiedNameParser> qualfied_name_parser_field;
    OmniPointer<NameTailParser> name_tail_parser_field;
    OmniPointer<NameParser> name_parser_field;
    OmniPointer<NameCharacterParser> name_character_parser_field;
    OmniPointer<BooleanParser> boolean_parser_field;
    OmniPointer<ByteParser> byte_parser_field;
    OmniPointer<ByteDigitParser> byte_digit_parser_field;
    OmniPointer<NegativeParser> negative_parser_field;
    OmniPointer<DecimalParser> decimal_parser_field;
    OmniPointer<NumberParser> number_parser_field;
    OmniPointer<DigitParser> digit_parser_field;
    OmniPointer<LiteralParser> literal_parser_field;
    OmniPointer<LiteralCharacterParser> literal_character_parser_field;
    OmniPointer<WhitespaceParser> whitespace_parser_field;
    OmniPointer<StringParser> string_parser_field;
    OmniPointer<CharacterParser> character_parser_field;
    OmniPointer<CharacterRangeParser> character_range_parser_field;
};

class DBNFOmniType
{
public:
    inline DBNFOmniType() {};
    inline ~DBNFOmniType() {};

    void SetCTCodeFile(OmniPointer<CTCodeFile> input_value);
    OmniPointer<CTCodeFile> GetCTCodeFile();
    void SetExternalDefinition(OmniPointer<ExternalDefinition> input_value);
    OmniPointer<ExternalDefinition> GetExternalDefinition();
    void SetUnmanagedType(OmniPointer<UnmanagedType> input_value);
    OmniPointer<UnmanagedType> GetUnmanagedType();
    void SetDefinition(OmniPointer<Definition> input_value);
    OmniPointer<Definition> GetDefinition();
    void SetInterfaceDef(OmniPointer<InterfaceDef> input_value);
    OmniPointer<InterfaceDef> GetInterfaceDef();
    void SetClassDef(OmniPointer<ClassDef> input_value);
    OmniPointer<ClassDef> GetClassDef();
    void SetContentDeclaration(OmniPointer<ContentDeclaration> input_value);
    OmniPointer<ContentDeclaration> GetContentDeclaration();
    void SetContentDefinition(OmniPointer<ContentDefinition> input_value);
    OmniPointer<ContentDefinition> GetContentDefinition();
    void SetPrimativeType(OmniPointer<PrimativeType> input_value);
    OmniPointer<PrimativeType> GetPrimativeType();
    void SetDefinedType(OmniPointer<DefinedType> input_value);
    OmniPointer<DefinedType> GetDefinedType();
    void SetSingletonType(OmniPointer<SingletonType> input_value);
    OmniPointer<SingletonType> GetSingletonType();
    void SetDimensionalNote(OmniPointer<DimensionalNote> input_value);
    OmniPointer<DimensionalNote> GetDimensionalNote();
    void SetDimensionalType(OmniPointer<DimensionalType> input_value);
    OmniPointer<DimensionalType> GetDimensionalType();
    void SetMapNote(OmniPointer<MapNote> input_value);
    OmniPointer<MapNote> GetMapNote();
    void SetMapType(OmniPointer<MapType> input_value);
    OmniPointer<MapType> GetMapType();
    void SetValueType(OmniPointer<ValueType> input_value);
    OmniPointer<ValueType> GetValueType();
    void SetParameterListDef(OmniPointer<ParameterListDef> input_value);
    OmniPointer<ParameterListDef> GetParameterListDef();
    void SetParameterList(OmniPointer<ParameterList> input_value);
    OmniPointer<ParameterList> GetParameterList();
    void SetCodeBlock(OmniPointer<CodeBlock> input_value);
    OmniPointer<CodeBlock> GetCodeBlock();
    void SetDeclarationAssign(OmniPointer<DeclarationAssign> input_value);
    OmniPointer<DeclarationAssign> GetDeclarationAssign();
    void SetDeclaration(OmniPointer<Declaration> input_value);
    OmniPointer<Declaration> GetDeclaration();
    void SetAssignment(OmniPointer<Assignment> input_value);
    OmniPointer<Assignment> GetAssignment();
    void SetReturn(OmniPointer<Return> input_value);
    OmniPointer<Return> GetReturn();
    void SetElseTail(OmniPointer<ElseTail> input_value);
    OmniPointer<ElseTail> GetElseTail();
    void SetConditional(OmniPointer<Conditional> input_value);
    OmniPointer<Conditional> GetConditional();
    void SetLoop(OmniPointer<Loop> input_value);
    OmniPointer<Loop> GetLoop();
    void SetCall(OmniPointer<Call> input_value);
    OmniPointer<Call> GetCall();
    void SetAllocate(OmniPointer<Allocate> input_value);
    OmniPointer<Allocate> GetAllocate();
    void SetInstruction(OmniPointer<Instruction> input_value);
    OmniPointer<Instruction> GetInstruction();
    void SetRValueSingle(OmniPointer<RValueSingle> input_value);
    OmniPointer<RValueSingle> GetRValueSingle();
    void SetRValueTail(OmniPointer<RValueTail> input_value);
    OmniPointer<RValueTail> GetRValueTail();
    void SetRValue(OmniPointer<RValue> input_value);
    OmniPointer<RValue> GetRValue();
    void SetBinaryOperator(OmniPointer<BinaryOperator> input_value);
    OmniPointer<BinaryOperator> GetBinaryOperator();
    void SetUnaryOperator(OmniPointer<UnaryOperator> input_value);
    OmniPointer<UnaryOperator> GetUnaryOperator();
    void SetComment(OmniPointer<Comment> input_value);
    OmniPointer<Comment> GetComment();
    void SetCommentCharacter(OmniPointer<CommentCharacter> input_value);
    OmniPointer<CommentCharacter> GetCommentCharacter();
    void SetQualfiedName(OmniPointer<QualfiedName> input_value);
    OmniPointer<QualfiedName> GetQualfiedName();
    void SetNameTail(OmniPointer<NameTail> input_value);
    OmniPointer<NameTail> GetNameTail();
    void SetName(OmniPointer<Name> input_value);
    OmniPointer<Name> GetName();
    void SetNameCharacter(OmniPointer<NameCharacter> input_value);
    OmniPointer<NameCharacter> GetNameCharacter();
    void SetBoolean(OmniPointer<Boolean> input_value);
    OmniPointer<Boolean> GetBoolean();
    void SetByte(OmniPointer<Byte> input_value);
    OmniPointer<Byte> GetByte();
    void SetByteDigit(OmniPointer<ByteDigit> input_value);
    OmniPointer<ByteDigit> GetByteDigit();
    void SetNegative(OmniPointer<Negative> input_value);
    OmniPointer<Negative> GetNegative();
    void SetDecimal(OmniPointer<Decimal> input_value);
    OmniPointer<Decimal> GetDecimal();
    void SetNumber(OmniPointer<Number> input_value);
    OmniPointer<Number> GetNumber();
    void SetDigit(OmniPointer<Digit> input_value);
    OmniPointer<Digit> GetDigit();
    void SetLiteral(OmniPointer<Literal> input_value);
    OmniPointer<Literal> GetLiteral();
    void SetLiteralCharacter(OmniPointer<LiteralCharacter> input_value);
    OmniPointer<LiteralCharacter> GetLiteralCharacter();
    void SetWhitespace(OmniPointer<Whitespace> input_value);
    OmniPointer<Whitespace> GetWhitespace();

private:
    OmniPointer<CTCodeFile> c_t_code_file_field;
    OmniPointer<ExternalDefinition> external_definition_field;
    OmniPointer<UnmanagedType> unmanaged_type_field;
    OmniPointer<Definition> definition_field;
    OmniPointer<InterfaceDef> interface_def_field;
    OmniPointer<ClassDef> class_def_field;
    OmniPointer<ContentDeclaration> content_declaration_field;
    OmniPointer<ContentDefinition> content_definition_field;
    OmniPointer<PrimativeType> primative_type_field;
    OmniPointer<DefinedType> defined_type_field;
    OmniPointer<SingletonType> singleton_type_field;
    OmniPointer<DimensionalNote> dimensional_note_field;
    OmniPointer<DimensionalType> dimensional_type_field;
    OmniPointer<MapNote> map_note_field;
    OmniPointer<MapType> map_type_field;
    OmniPointer<ValueType> value_type_field;
    OmniPointer<ParameterListDef> parameter_list_def_field;
    OmniPointer<ParameterList> parameter_list_field;
    OmniPointer<CodeBlock> code_block_field;
    OmniPointer<DeclarationAssign> declaration_assign_field;
    OmniPointer<Declaration> declaration_field;
    OmniPointer<Assignment> assignment_field;
    OmniPointer<Return> return_field;
    OmniPointer<ElseTail> else_tail_field;
    OmniPointer<Conditional> conditional_field;
    OmniPointer<Loop> loop_field;
    OmniPointer<Call> call_field;
    OmniPointer<Allocate> allocate_field;
    OmniPointer<Instruction> instruction_field;
    OmniPointer<RValueSingle> r_value_single_field;
    OmniPointer<RValueTail> r_value_tail_field;
    OmniPointer<RValue> r_value_field;
    OmniPointer<BinaryOperator> binary_operator_field;
    OmniPointer<UnaryOperator> unary_operator_field;
    OmniPointer<Comment> comment_field;
    OmniPointer<CommentCharacter> comment_character_field;
    OmniPointer<QualfiedName> qualfied_name_field;
    OmniPointer<NameTail> name_tail_field;
    OmniPointer<Name> name_field;
    OmniPointer<NameCharacter> name_character_field;
    OmniPointer<Boolean> boolean_field;
    OmniPointer<Byte> byte_field;
    OmniPointer<ByteDigit> byte_digit_field;
    OmniPointer<Negative> negative_field;
    OmniPointer<Decimal> decimal_field;
    OmniPointer<Number> number_field;
    OmniPointer<Digit> digit_field;
    OmniPointer<Literal> literal_field;
    OmniPointer<LiteralCharacter> literal_character_field;
    OmniPointer<Whitespace> whitespace_field;
};

class DBNFOmniTypeResult
{
public:
    inline DBNFOmniTypeResult() {};
    inline ~DBNFOmniTypeResult() {};

    void SetValue(OmniPointer<DBNFOmniType> new_value);
    OmniPointer<DBNFOmniType> GetValue();
    void SetResult(bool new_result);
    bool GetResult();
    void SetCTCodeFile(OmniPointer<CTCodeFile> input_value);
    void SetExternalDefinition(OmniPointer<ExternalDefinition> input_value);
    void SetUnmanagedType(OmniPointer<UnmanagedType> input_value);
    void SetDefinition(OmniPointer<Definition> input_value);
    void SetInterfaceDef(OmniPointer<InterfaceDef> input_value);
    void SetClassDef(OmniPointer<ClassDef> input_value);
    void SetContentDeclaration(OmniPointer<ContentDeclaration> input_value);
    void SetContentDefinition(OmniPointer<ContentDefinition> input_value);
    void SetPrimativeType(OmniPointer<PrimativeType> input_value);
    void SetDefinedType(OmniPointer<DefinedType> input_value);
    void SetSingletonType(OmniPointer<SingletonType> input_value);
    void SetDimensionalNote(OmniPointer<DimensionalNote> input_value);
    void SetDimensionalType(OmniPointer<DimensionalType> input_value);
    void SetMapNote(OmniPointer<MapNote> input_value);
    void SetMapType(OmniPointer<MapType> input_value);
    void SetValueType(OmniPointer<ValueType> input_value);
    void SetParameterListDef(OmniPointer<ParameterListDef> input_value);
    void SetParameterList(OmniPointer<ParameterList> input_value);
    void SetCodeBlock(OmniPointer<CodeBlock> input_value);
    void SetDeclarationAssign(OmniPointer<DeclarationAssign> input_value);
    void SetDeclaration(OmniPointer<Declaration> input_value);
    void SetAssignment(OmniPointer<Assignment> input_value);
    void SetReturn(OmniPointer<Return> input_value);
    void SetElseTail(OmniPointer<ElseTail> input_value);
    void SetConditional(OmniPointer<Conditional> input_value);
    void SetLoop(OmniPointer<Loop> input_value);
    void SetCall(OmniPointer<Call> input_value);
    void SetAllocate(OmniPointer<Allocate> input_value);
    void SetInstruction(OmniPointer<Instruction> input_value);
    void SetRValueSingle(OmniPointer<RValueSingle> input_value);
    void SetRValueTail(OmniPointer<RValueTail> input_value);
    void SetRValue(OmniPointer<RValue> input_value);
    void SetBinaryOperator(OmniPointer<BinaryOperator> input_value);
    void SetUnaryOperator(OmniPointer<UnaryOperator> input_value);
    void SetComment(OmniPointer<Comment> input_value);
    void SetCommentCharacter(OmniPointer<CommentCharacter> input_value);
    void SetQualfiedName(OmniPointer<QualfiedName> input_value);
    void SetNameTail(OmniPointer<NameTail> input_value);
    void SetName(OmniPointer<Name> input_value);
    void SetNameCharacter(OmniPointer<NameCharacter> input_value);
    void SetBoolean(OmniPointer<Boolean> input_value);
    void SetByte(OmniPointer<Byte> input_value);
    void SetByteDigit(OmniPointer<ByteDigit> input_value);
    void SetNegative(OmniPointer<Negative> input_value);
    void SetDecimal(OmniPointer<Decimal> input_value);
    void SetNumber(OmniPointer<Number> input_value);
    void SetDigit(OmniPointer<Digit> input_value);
    void SetLiteral(OmniPointer<Literal> input_value);
    void SetLiteralCharacter(OmniPointer<LiteralCharacter> input_value);
    void SetWhitespace(OmniPointer<Whitespace> input_value);

private:
    OmniPointer<DBNFOmniType> value;
    bool result;
};

class DBNFOmniTypeListResult
{
public:
    inline DBNFOmniTypeListResult() {};
    inline ~DBNFOmniTypeListResult() {};

    void SetValue(std::vector<OmniPointer<DBNFOmniType>> new_value);
    std::vector<OmniPointer<DBNFOmniType>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();
    void SetCTCodeFile(std::vector<OmniPointer<CTCodeFile>> input_value);
    void SetExternalDefinition(std::vector<OmniPointer<ExternalDefinition>> input_value);
    void SetUnmanagedType(std::vector<OmniPointer<UnmanagedType>> input_value);
    void SetDefinition(std::vector<OmniPointer<Definition>> input_value);
    void SetInterfaceDef(std::vector<OmniPointer<InterfaceDef>> input_value);
    void SetClassDef(std::vector<OmniPointer<ClassDef>> input_value);
    void SetContentDeclaration(std::vector<OmniPointer<ContentDeclaration>> input_value);
    void SetContentDefinition(std::vector<OmniPointer<ContentDefinition>> input_value);
    void SetPrimativeType(std::vector<OmniPointer<PrimativeType>> input_value);
    void SetDefinedType(std::vector<OmniPointer<DefinedType>> input_value);
    void SetSingletonType(std::vector<OmniPointer<SingletonType>> input_value);
    void SetDimensionalNote(std::vector<OmniPointer<DimensionalNote>> input_value);
    void SetDimensionalType(std::vector<OmniPointer<DimensionalType>> input_value);
    void SetMapNote(std::vector<OmniPointer<MapNote>> input_value);
    void SetMapType(std::vector<OmniPointer<MapType>> input_value);
    void SetValueType(std::vector<OmniPointer<ValueType>> input_value);
    void SetParameterListDef(std::vector<OmniPointer<ParameterListDef>> input_value);
    void SetParameterList(std::vector<OmniPointer<ParameterList>> input_value);
    void SetCodeBlock(std::vector<OmniPointer<CodeBlock>> input_value);
    void SetDeclarationAssign(std::vector<OmniPointer<DeclarationAssign>> input_value);
    void SetDeclaration(std::vector<OmniPointer<Declaration>> input_value);
    void SetAssignment(std::vector<OmniPointer<Assignment>> input_value);
    void SetReturn(std::vector<OmniPointer<Return>> input_value);
    void SetElseTail(std::vector<OmniPointer<ElseTail>> input_value);
    void SetConditional(std::vector<OmniPointer<Conditional>> input_value);
    void SetLoop(std::vector<OmniPointer<Loop>> input_value);
    void SetCall(std::vector<OmniPointer<Call>> input_value);
    void SetAllocate(std::vector<OmniPointer<Allocate>> input_value);
    void SetInstruction(std::vector<OmniPointer<Instruction>> input_value);
    void SetRValueSingle(std::vector<OmniPointer<RValueSingle>> input_value);
    void SetRValueTail(std::vector<OmniPointer<RValueTail>> input_value);
    void SetRValue(std::vector<OmniPointer<RValue>> input_value);
    void SetBinaryOperator(std::vector<OmniPointer<BinaryOperator>> input_value);
    void SetUnaryOperator(std::vector<OmniPointer<UnaryOperator>> input_value);
    void SetComment(std::vector<OmniPointer<Comment>> input_value);
    void SetCommentCharacter(std::vector<OmniPointer<CommentCharacter>> input_value);
    void SetQualfiedName(std::vector<OmniPointer<QualfiedName>> input_value);
    void SetNameTail(std::vector<OmniPointer<NameTail>> input_value);
    void SetName(std::vector<OmniPointer<Name>> input_value);
    void SetNameCharacter(std::vector<OmniPointer<NameCharacter>> input_value);
    void SetBoolean(std::vector<OmniPointer<Boolean>> input_value);
    void SetByte(std::vector<OmniPointer<Byte>> input_value);
    void SetByteDigit(std::vector<OmniPointer<ByteDigit>> input_value);
    void SetNegative(std::vector<OmniPointer<Negative>> input_value);
    void SetDecimal(std::vector<OmniPointer<Decimal>> input_value);
    void SetNumber(std::vector<OmniPointer<Number>> input_value);
    void SetDigit(std::vector<OmniPointer<Digit>> input_value);
    void SetLiteral(std::vector<OmniPointer<Literal>> input_value);
    void SetLiteralCharacter(std::vector<OmniPointer<LiteralCharacter>> input_value);
    void SetWhitespace(std::vector<OmniPointer<Whitespace>> input_value);

private:
    std::vector<OmniPointer<DBNFOmniType>> value;
    bool result;
};

class LargeString
{
public:
    inline LargeString() {};
    inline ~LargeString() {};

    void SetData(std::string new_data);
    std::string GetData();
    int GetIntAt(int offset);
    std::string GetAt(int offset);

private:
    std::string data;
};

class LengthString
{
public:
    inline LengthString() {};
    inline ~LengthString() {};

    void SetData(OmniPointer<LargeString> new_data);
    OmniPointer<LargeString> GetData();
    void SetStart(int new_start);
    int GetStart();
    void SetLength(int new_length);
    int GetLength();
    std::string GetString();

private:
    OmniPointer<LargeString> data;
    int start;
    int length;
};

class CTCodeFileParser
{
public:
    inline CTCodeFileParser() {};
    inline ~CTCodeFileParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<CTCodeFileResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<CTCodeFileResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<CTCodeFileListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class CTCodeFileResult
{
public:
    inline CTCodeFileResult() {};
    inline ~CTCodeFileResult() {};

    void SetValue(OmniPointer<CTCodeFile> new_value);
    OmniPointer<CTCodeFile> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<CTCodeFile> value;
    bool result;
};

class CTCodeFileListResult
{
public:
    inline CTCodeFileListResult() {};
    inline ~CTCodeFileListResult() {};

    void SetValue(std::vector<OmniPointer<CTCodeFile>> new_value);
    std::vector<OmniPointer<CTCodeFile>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<CTCodeFile>> value;
    bool result;
};

class CTCodeFile
{
public:
    inline CTCodeFile() {};
    inline ~CTCodeFile() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetDeclarations(std::vector<OmniPointer<ExternalDefinition>> input_value);
    std::vector<OmniPointer<ExternalDefinition>> GetDeclarations();
    void SetDefinitions(std::vector<OmniPointer<Definition>> input_value);
    std::vector<OmniPointer<Definition>> GetDefinitions();
    void SetUnmanagedTypes(std::vector<OmniPointer<UnmanagedType>> input_value);
    std::vector<OmniPointer<UnmanagedType>> GetUnmanagedTypes();

private:
    OmniPointer<LengthString> length_string;
    std::vector<OmniPointer<ExternalDefinition>> declarations_field;
    std::vector<OmniPointer<Definition>> definitions_field;
    std::vector<OmniPointer<UnmanagedType>> unmanaged_types_field;
};

class ExternalDefinitionParser
{
public:
    inline ExternalDefinitionParser() {};
    inline ~ExternalDefinitionParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<ExternalDefinitionResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ExternalDefinitionResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<ExternalDefinitionListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class ExternalDefinitionResult
{
public:
    inline ExternalDefinitionResult() {};
    inline ~ExternalDefinitionResult() {};

    void SetValue(OmniPointer<ExternalDefinition> new_value);
    OmniPointer<ExternalDefinition> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<ExternalDefinition> value;
    bool result;
};

class ExternalDefinitionListResult
{
public:
    inline ExternalDefinitionListResult() {};
    inline ~ExternalDefinitionListResult() {};

    void SetValue(std::vector<OmniPointer<ExternalDefinition>> new_value);
    std::vector<OmniPointer<ExternalDefinition>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<ExternalDefinition>> value;
    bool result;
};

class ExternalDefinition
{
public:
    inline ExternalDefinition() {};
    inline ~ExternalDefinition() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetExdef(OmniPointer<QualfiedName> input_value);
    OmniPointer<QualfiedName> GetExdef();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<QualfiedName> exdef_field;
};

class UnmanagedTypeParser
{
public:
    inline UnmanagedTypeParser() {};
    inline ~UnmanagedTypeParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<UnmanagedTypeResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<UnmanagedTypeResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<UnmanagedTypeListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class UnmanagedTypeResult
{
public:
    inline UnmanagedTypeResult() {};
    inline ~UnmanagedTypeResult() {};

    void SetValue(OmniPointer<UnmanagedType> new_value);
    OmniPointer<UnmanagedType> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<UnmanagedType> value;
    bool result;
};

class UnmanagedTypeListResult
{
public:
    inline UnmanagedTypeListResult() {};
    inline ~UnmanagedTypeListResult() {};

    void SetValue(std::vector<OmniPointer<UnmanagedType>> new_value);
    std::vector<OmniPointer<UnmanagedType>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<UnmanagedType>> value;
    bool result;
};

class UnmanagedType
{
public:
    inline UnmanagedType() {};
    inline ~UnmanagedType() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetUnmanagedType(OmniPointer<QualfiedName> input_value);
    OmniPointer<QualfiedName> GetUnmanagedType();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<QualfiedName> unmanaged_type_field;
};

class DefinitionParser
{
public:
    inline DefinitionParser() {};
    inline ~DefinitionParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<DefinitionResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<DefinitionResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<DefinitionListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class DefinitionResult
{
public:
    inline DefinitionResult() {};
    inline ~DefinitionResult() {};

    void SetValue(OmniPointer<Definition> new_value);
    OmniPointer<Definition> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<Definition> value;
    bool result;
};

class DefinitionListResult
{
public:
    inline DefinitionListResult() {};
    inline ~DefinitionListResult() {};

    void SetValue(std::vector<OmniPointer<Definition>> new_value);
    std::vector<OmniPointer<Definition>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<Definition>> value;
    bool result;
};

class Definition
{
public:
    inline Definition() {};
    inline ~Definition() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetClassDef(OmniPointer<ClassDef> input_value);
    OmniPointer<ClassDef> GetClassDef();
    void SetInterfaceDef(OmniPointer<InterfaceDef> input_value);
    OmniPointer<InterfaceDef> GetInterfaceDef();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<ClassDef> class_def_field;
    OmniPointer<InterfaceDef> interface_def_field;
};

class InterfaceDefParser
{
public:
    inline InterfaceDefParser() {};
    inline ~InterfaceDefParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<InterfaceDefResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<InterfaceDefResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<InterfaceDefListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class InterfaceDefResult
{
public:
    inline InterfaceDefResult() {};
    inline ~InterfaceDefResult() {};

    void SetValue(OmniPointer<InterfaceDef> new_value);
    OmniPointer<InterfaceDef> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<InterfaceDef> value;
    bool result;
};

class InterfaceDefListResult
{
public:
    inline InterfaceDefListResult() {};
    inline ~InterfaceDefListResult() {};

    void SetValue(std::vector<OmniPointer<InterfaceDef>> new_value);
    std::vector<OmniPointer<InterfaceDef>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<InterfaceDef>> value;
    bool result;
};

class InterfaceDef
{
public:
    inline InterfaceDef() {};
    inline ~InterfaceDef() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetComment(OmniPointer<Comment> input_value);
    OmniPointer<Comment> GetComment();
    void SetDeclarations(std::vector<OmniPointer<ContentDeclaration>> input_value);
    std::vector<OmniPointer<ContentDeclaration>> GetDeclarations();
    void SetName(OmniPointer<Name> input_value);
    OmniPointer<Name> GetName();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<Comment> comment_field;
    std::vector<OmniPointer<ContentDeclaration>> declarations_field;
    OmniPointer<Name> name_field;
};

class ClassDefParser
{
public:
    inline ClassDefParser() {};
    inline ~ClassDefParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<ClassDefResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ClassDefResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<ClassDefListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class ClassDefResult
{
public:
    inline ClassDefResult() {};
    inline ~ClassDefResult() {};

    void SetValue(OmniPointer<ClassDef> new_value);
    OmniPointer<ClassDef> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<ClassDef> value;
    bool result;
};

class ClassDefListResult
{
public:
    inline ClassDefListResult() {};
    inline ~ClassDefListResult() {};

    void SetValue(std::vector<OmniPointer<ClassDef>> new_value);
    std::vector<OmniPointer<ClassDef>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<ClassDef>> value;
    bool result;
};

class ClassDef
{
public:
    inline ClassDef() {};
    inline ~ClassDef() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetComment(OmniPointer<Comment> input_value);
    OmniPointer<Comment> GetComment();
    void SetDefinitions(std::vector<OmniPointer<ContentDefinition>> input_value);
    std::vector<OmniPointer<ContentDefinition>> GetDefinitions();
    void SetName(OmniPointer<Name> input_value);
    OmniPointer<Name> GetName();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<Comment> comment_field;
    std::vector<OmniPointer<ContentDefinition>> definitions_field;
    OmniPointer<Name> name_field;
};

class ContentDeclarationParser
{
public:
    inline ContentDeclarationParser() {};
    inline ~ContentDeclarationParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<ContentDeclarationResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ContentDeclarationResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<ContentDeclarationListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class ContentDeclarationResult
{
public:
    inline ContentDeclarationResult() {};
    inline ~ContentDeclarationResult() {};

    void SetValue(OmniPointer<ContentDeclaration> new_value);
    OmniPointer<ContentDeclaration> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<ContentDeclaration> value;
    bool result;
};

class ContentDeclarationListResult
{
public:
    inline ContentDeclarationListResult() {};
    inline ~ContentDeclarationListResult() {};

    void SetValue(std::vector<OmniPointer<ContentDeclaration>> new_value);
    std::vector<OmniPointer<ContentDeclaration>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<ContentDeclaration>> value;
    bool result;
};

class ContentDeclaration
{
public:
    inline ContentDeclaration() {};
    inline ~ContentDeclaration() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetComment(OmniPointer<Comment> input_value);
    OmniPointer<Comment> GetComment();
    void SetName(OmniPointer<Name> input_value);
    OmniPointer<Name> GetName();
    void SetParameters(OmniPointer<ParameterListDef> input_value);
    OmniPointer<ParameterListDef> GetParameters();
    void SetType(OmniPointer<ValueType> input_value);
    OmniPointer<ValueType> GetType();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<Comment> comment_field;
    OmniPointer<Name> name_field;
    OmniPointer<ParameterListDef> parameters_field;
    OmniPointer<ValueType> type_field;
};

class ContentDefinitionParser
{
public:
    inline ContentDefinitionParser() {};
    inline ~ContentDefinitionParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<ContentDefinitionResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ContentDefinitionResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<ContentDefinitionListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class ContentDefinitionResult
{
public:
    inline ContentDefinitionResult() {};
    inline ~ContentDefinitionResult() {};

    void SetValue(OmniPointer<ContentDefinition> new_value);
    OmniPointer<ContentDefinition> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<ContentDefinition> value;
    bool result;
};

class ContentDefinitionListResult
{
public:
    inline ContentDefinitionListResult() {};
    inline ~ContentDefinitionListResult() {};

    void SetValue(std::vector<OmniPointer<ContentDefinition>> new_value);
    std::vector<OmniPointer<ContentDefinition>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<ContentDefinition>> value;
    bool result;
};

class ContentDefinition
{
public:
    inline ContentDefinition() {};
    inline ~ContentDefinition() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetComment(OmniPointer<Comment> input_value);
    OmniPointer<Comment> GetComment();
    void SetFunctionBody(OmniPointer<CodeBlock> input_value);
    OmniPointer<CodeBlock> GetFunctionBody();
    void SetName(OmniPointer<Name> input_value);
    OmniPointer<Name> GetName();
    void SetParameters(OmniPointer<ParameterListDef> input_value);
    OmniPointer<ParameterListDef> GetParameters();
    void SetType(OmniPointer<ValueType> input_value);
    OmniPointer<ValueType> GetType();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<Comment> comment_field;
    OmniPointer<CodeBlock> function_body_field;
    OmniPointer<Name> name_field;
    OmniPointer<ParameterListDef> parameters_field;
    OmniPointer<ValueType> type_field;
};

class PrimativeTypeParser
{
public:
    inline PrimativeTypeParser() {};
    inline ~PrimativeTypeParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<PrimativeTypeResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<PrimativeTypeResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<PrimativeTypeListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class PrimativeTypeResult
{
public:
    inline PrimativeTypeResult() {};
    inline ~PrimativeTypeResult() {};

    void SetValue(OmniPointer<PrimativeType> new_value);
    OmniPointer<PrimativeType> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<PrimativeType> value;
    bool result;
};

class PrimativeTypeListResult
{
public:
    inline PrimativeTypeListResult() {};
    inline ~PrimativeTypeListResult() {};

    void SetValue(std::vector<OmniPointer<PrimativeType>> new_value);
    std::vector<OmniPointer<PrimativeType>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<PrimativeType>> value;
    bool result;
};

class PrimativeType
{
public:
    inline PrimativeType() {};
    inline ~PrimativeType() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();

private:
    OmniPointer<LengthString> length_string;
};

class DefinedTypeParser
{
public:
    inline DefinedTypeParser() {};
    inline ~DefinedTypeParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<DefinedTypeResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<DefinedTypeResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<DefinedTypeListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class DefinedTypeResult
{
public:
    inline DefinedTypeResult() {};
    inline ~DefinedTypeResult() {};

    void SetValue(OmniPointer<DefinedType> new_value);
    OmniPointer<DefinedType> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<DefinedType> value;
    bool result;
};

class DefinedTypeListResult
{
public:
    inline DefinedTypeListResult() {};
    inline ~DefinedTypeListResult() {};

    void SetValue(std::vector<OmniPointer<DefinedType>> new_value);
    std::vector<OmniPointer<DefinedType>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<DefinedType>> value;
    bool result;
};

class DefinedType
{
public:
    inline DefinedType() {};
    inline ~DefinedType() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetName(OmniPointer<QualfiedName> input_value);
    OmniPointer<QualfiedName> GetName();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<QualfiedName> name_field;
};

class SingletonTypeParser
{
public:
    inline SingletonTypeParser() {};
    inline ~SingletonTypeParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<SingletonTypeResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<SingletonTypeResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<SingletonTypeListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class SingletonTypeResult
{
public:
    inline SingletonTypeResult() {};
    inline ~SingletonTypeResult() {};

    void SetValue(OmniPointer<SingletonType> new_value);
    OmniPointer<SingletonType> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<SingletonType> value;
    bool result;
};

class SingletonTypeListResult
{
public:
    inline SingletonTypeListResult() {};
    inline ~SingletonTypeListResult() {};

    void SetValue(std::vector<OmniPointer<SingletonType>> new_value);
    std::vector<OmniPointer<SingletonType>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<SingletonType>> value;
    bool result;
};

class SingletonType
{
public:
    inline SingletonType() {};
    inline ~SingletonType() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetDefinedType(OmniPointer<DefinedType> input_value);
    OmniPointer<DefinedType> GetDefinedType();
    void SetPrimativeType(OmniPointer<PrimativeType> input_value);
    OmniPointer<PrimativeType> GetPrimativeType();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<DefinedType> defined_type_field;
    OmniPointer<PrimativeType> primative_type_field;
};

class DimensionalNoteParser
{
public:
    inline DimensionalNoteParser() {};
    inline ~DimensionalNoteParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<DimensionalNoteResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<DimensionalNoteResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<DimensionalNoteListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class DimensionalNoteResult
{
public:
    inline DimensionalNoteResult() {};
    inline ~DimensionalNoteResult() {};

    void SetValue(OmniPointer<DimensionalNote> new_value);
    OmniPointer<DimensionalNote> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<DimensionalNote> value;
    bool result;
};

class DimensionalNoteListResult
{
public:
    inline DimensionalNoteListResult() {};
    inline ~DimensionalNoteListResult() {};

    void SetValue(std::vector<OmniPointer<DimensionalNote>> new_value);
    std::vector<OmniPointer<DimensionalNote>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<DimensionalNote>> value;
    bool result;
};

class DimensionalNote
{
public:
    inline DimensionalNote() {};
    inline ~DimensionalNote() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();

private:
    OmniPointer<LengthString> length_string;
};

class DimensionalTypeParser
{
public:
    inline DimensionalTypeParser() {};
    inline ~DimensionalTypeParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<DimensionalTypeResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<DimensionalTypeResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<DimensionalTypeListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class DimensionalTypeResult
{
public:
    inline DimensionalTypeResult() {};
    inline ~DimensionalTypeResult() {};

    void SetValue(OmniPointer<DimensionalType> new_value);
    OmniPointer<DimensionalType> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<DimensionalType> value;
    bool result;
};

class DimensionalTypeListResult
{
public:
    inline DimensionalTypeListResult() {};
    inline ~DimensionalTypeListResult() {};

    void SetValue(std::vector<OmniPointer<DimensionalType>> new_value);
    std::vector<OmniPointer<DimensionalType>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<DimensionalType>> value;
    bool result;
};

class DimensionalType
{
public:
    inline DimensionalType() {};
    inline ~DimensionalType() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetDimensionalNote(std::vector<OmniPointer<DimensionalNote>> input_value);
    std::vector<OmniPointer<DimensionalNote>> GetDimensionalNote();
    void SetSingletonType(OmniPointer<SingletonType> input_value);
    OmniPointer<SingletonType> GetSingletonType();

private:
    OmniPointer<LengthString> length_string;
    std::vector<OmniPointer<DimensionalNote>> dimensional_note_field;
    OmniPointer<SingletonType> singleton_type_field;
};

class MapNoteParser
{
public:
    inline MapNoteParser() {};
    inline ~MapNoteParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<MapNoteResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<MapNoteResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<MapNoteListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class MapNoteResult
{
public:
    inline MapNoteResult() {};
    inline ~MapNoteResult() {};

    void SetValue(OmniPointer<MapNote> new_value);
    OmniPointer<MapNote> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<MapNote> value;
    bool result;
};

class MapNoteListResult
{
public:
    inline MapNoteListResult() {};
    inline ~MapNoteListResult() {};

    void SetValue(std::vector<OmniPointer<MapNote>> new_value);
    std::vector<OmniPointer<MapNote>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<MapNote>> value;
    bool result;
};

class MapNote
{
public:
    inline MapNote() {};
    inline ~MapNote() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();

private:
    OmniPointer<LengthString> length_string;
};

class MapTypeParser
{
public:
    inline MapTypeParser() {};
    inline ~MapTypeParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<MapTypeResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<MapTypeResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<MapTypeListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class MapTypeResult
{
public:
    inline MapTypeResult() {};
    inline ~MapTypeResult() {};

    void SetValue(OmniPointer<MapType> new_value);
    OmniPointer<MapType> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<MapType> value;
    bool result;
};

class MapTypeListResult
{
public:
    inline MapTypeListResult() {};
    inline ~MapTypeListResult() {};

    void SetValue(std::vector<OmniPointer<MapType>> new_value);
    std::vector<OmniPointer<MapType>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<MapType>> value;
    bool result;
};

class MapType
{
public:
    inline MapType() {};
    inline ~MapType() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetMapNote(OmniPointer<MapNote> input_value);
    OmniPointer<MapNote> GetMapNote();
    void SetSingletonType(OmniPointer<SingletonType> input_value);
    OmniPointer<SingletonType> GetSingletonType();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<MapNote> map_note_field;
    OmniPointer<SingletonType> singleton_type_field;
};

class ValueTypeParser
{
public:
    inline ValueTypeParser() {};
    inline ~ValueTypeParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<ValueTypeResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ValueTypeResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<ValueTypeListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class ValueTypeResult
{
public:
    inline ValueTypeResult() {};
    inline ~ValueTypeResult() {};

    void SetValue(OmniPointer<ValueType> new_value);
    OmniPointer<ValueType> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<ValueType> value;
    bool result;
};

class ValueTypeListResult
{
public:
    inline ValueTypeListResult() {};
    inline ~ValueTypeListResult() {};

    void SetValue(std::vector<OmniPointer<ValueType>> new_value);
    std::vector<OmniPointer<ValueType>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<ValueType>> value;
    bool result;
};

class ValueType
{
public:
    inline ValueType() {};
    inline ~ValueType() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetDimensionalType(OmniPointer<DimensionalType> input_value);
    OmniPointer<DimensionalType> GetDimensionalType();
    void SetMapType(OmniPointer<MapType> input_value);
    OmniPointer<MapType> GetMapType();
    void SetSingletonType(OmniPointer<SingletonType> input_value);
    OmniPointer<SingletonType> GetSingletonType();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<DimensionalType> dimensional_type_field;
    OmniPointer<MapType> map_type_field;
    OmniPointer<SingletonType> singleton_type_field;
};

class ParameterListDefParser
{
public:
    inline ParameterListDefParser() {};
    inline ~ParameterListDefParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<ParameterListDefResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ParameterListDefResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<ParameterListDefListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class ParameterListDefResult
{
public:
    inline ParameterListDefResult() {};
    inline ~ParameterListDefResult() {};

    void SetValue(OmniPointer<ParameterListDef> new_value);
    OmniPointer<ParameterListDef> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<ParameterListDef> value;
    bool result;
};

class ParameterListDefListResult
{
public:
    inline ParameterListDefListResult() {};
    inline ~ParameterListDefListResult() {};

    void SetValue(std::vector<OmniPointer<ParameterListDef>> new_value);
    std::vector<OmniPointer<ParameterListDef>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<ParameterListDef>> value;
    bool result;
};

class ParameterListDef
{
public:
    inline ParameterListDef() {};
    inline ~ParameterListDef() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetName(OmniPointer<Name> input_value);
    OmniPointer<Name> GetName();
    void SetParameterTail(OmniPointer<ParameterListDef> input_value);
    OmniPointer<ParameterListDef> GetParameterTail();
    void SetType(OmniPointer<ValueType> input_value);
    OmniPointer<ValueType> GetType();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<Name> name_field;
    OmniPointer<ParameterListDef> parameter_tail_field;
    OmniPointer<ValueType> type_field;
};

class ParameterListParser
{
public:
    inline ParameterListParser() {};
    inline ~ParameterListParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<ParameterListResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ParameterListResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<ParameterListListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class ParameterListResult
{
public:
    inline ParameterListResult() {};
    inline ~ParameterListResult() {};

    void SetValue(OmniPointer<ParameterList> new_value);
    OmniPointer<ParameterList> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<ParameterList> value;
    bool result;
};

class ParameterListListResult
{
public:
    inline ParameterListListResult() {};
    inline ~ParameterListListResult() {};

    void SetValue(std::vector<OmniPointer<ParameterList>> new_value);
    std::vector<OmniPointer<ParameterList>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<ParameterList>> value;
    bool result;
};

class ParameterList
{
public:
    inline ParameterList() {};
    inline ~ParameterList() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetParameterTail(OmniPointer<ParameterList> input_value);
    OmniPointer<ParameterList> GetParameterTail();
    void SetRvalue(OmniPointer<RValue> input_value);
    OmniPointer<RValue> GetRvalue();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<ParameterList> parameter_tail_field;
    OmniPointer<RValue> rvalue_field;
};

class CodeBlockParser
{
public:
    inline CodeBlockParser() {};
    inline ~CodeBlockParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<CodeBlockResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<CodeBlockResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<CodeBlockListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class CodeBlockResult
{
public:
    inline CodeBlockResult() {};
    inline ~CodeBlockResult() {};

    void SetValue(OmniPointer<CodeBlock> new_value);
    OmniPointer<CodeBlock> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<CodeBlock> value;
    bool result;
};

class CodeBlockListResult
{
public:
    inline CodeBlockListResult() {};
    inline ~CodeBlockListResult() {};

    void SetValue(std::vector<OmniPointer<CodeBlock>> new_value);
    std::vector<OmniPointer<CodeBlock>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<CodeBlock>> value;
    bool result;
};

class CodeBlock
{
public:
    inline CodeBlock() {};
    inline ~CodeBlock() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetInstructions(std::vector<OmniPointer<Instruction>> input_value);
    std::vector<OmniPointer<Instruction>> GetInstructions();

private:
    OmniPointer<LengthString> length_string;
    std::vector<OmniPointer<Instruction>> instructions_field;
};

class DeclarationAssignParser
{
public:
    inline DeclarationAssignParser() {};
    inline ~DeclarationAssignParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<DeclarationAssignResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<DeclarationAssignResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<DeclarationAssignListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class DeclarationAssignResult
{
public:
    inline DeclarationAssignResult() {};
    inline ~DeclarationAssignResult() {};

    void SetValue(OmniPointer<DeclarationAssign> new_value);
    OmniPointer<DeclarationAssign> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<DeclarationAssign> value;
    bool result;
};

class DeclarationAssignListResult
{
public:
    inline DeclarationAssignListResult() {};
    inline ~DeclarationAssignListResult() {};

    void SetValue(std::vector<OmniPointer<DeclarationAssign>> new_value);
    std::vector<OmniPointer<DeclarationAssign>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<DeclarationAssign>> value;
    bool result;
};

class DeclarationAssign
{
public:
    inline DeclarationAssign() {};
    inline ~DeclarationAssign() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetRvalue(OmniPointer<RValue> input_value);
    OmniPointer<RValue> GetRvalue();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<RValue> rvalue_field;
};

class DeclarationParser
{
public:
    inline DeclarationParser() {};
    inline ~DeclarationParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<DeclarationResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<DeclarationResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<DeclarationListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class DeclarationResult
{
public:
    inline DeclarationResult() {};
    inline ~DeclarationResult() {};

    void SetValue(OmniPointer<Declaration> new_value);
    OmniPointer<Declaration> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<Declaration> value;
    bool result;
};

class DeclarationListResult
{
public:
    inline DeclarationListResult() {};
    inline ~DeclarationListResult() {};

    void SetValue(std::vector<OmniPointer<Declaration>> new_value);
    std::vector<OmniPointer<Declaration>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<Declaration>> value;
    bool result;
};

class Declaration
{
public:
    inline Declaration() {};
    inline ~Declaration() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetAssignment(OmniPointer<DeclarationAssign> input_value);
    OmniPointer<DeclarationAssign> GetAssignment();
    void SetName(OmniPointer<Name> input_value);
    OmniPointer<Name> GetName();
    void SetType(OmniPointer<ValueType> input_value);
    OmniPointer<ValueType> GetType();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<DeclarationAssign> assignment_field;
    OmniPointer<Name> name_field;
    OmniPointer<ValueType> type_field;
};

class AssignmentParser
{
public:
    inline AssignmentParser() {};
    inline ~AssignmentParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<AssignmentResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<AssignmentResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<AssignmentListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class AssignmentResult
{
public:
    inline AssignmentResult() {};
    inline ~AssignmentResult() {};

    void SetValue(OmniPointer<Assignment> new_value);
    OmniPointer<Assignment> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<Assignment> value;
    bool result;
};

class AssignmentListResult
{
public:
    inline AssignmentListResult() {};
    inline ~AssignmentListResult() {};

    void SetValue(std::vector<OmniPointer<Assignment>> new_value);
    std::vector<OmniPointer<Assignment>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<Assignment>> value;
    bool result;
};

class Assignment
{
public:
    inline Assignment() {};
    inline ~Assignment() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetLvalue(OmniPointer<Name> input_value);
    OmniPointer<Name> GetLvalue();
    void SetRvalue(OmniPointer<RValue> input_value);
    OmniPointer<RValue> GetRvalue();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<Name> lvalue_field;
    OmniPointer<RValue> rvalue_field;
};

class ReturnParser
{
public:
    inline ReturnParser() {};
    inline ~ReturnParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<ReturnResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ReturnResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<ReturnListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class ReturnResult
{
public:
    inline ReturnResult() {};
    inline ~ReturnResult() {};

    void SetValue(OmniPointer<Return> new_value);
    OmniPointer<Return> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<Return> value;
    bool result;
};

class ReturnListResult
{
public:
    inline ReturnListResult() {};
    inline ~ReturnListResult() {};

    void SetValue(std::vector<OmniPointer<Return>> new_value);
    std::vector<OmniPointer<Return>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<Return>> value;
    bool result;
};

class Return
{
public:
    inline Return() {};
    inline ~Return() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetRtn(OmniPointer<String> input_value);
    OmniPointer<String> GetRtn();
    void SetRvalue(OmniPointer<RValue> input_value);
    OmniPointer<RValue> GetRvalue();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<String> rtn_field;
    OmniPointer<RValue> rvalue_field;
};

class ElseTailParser
{
public:
    inline ElseTailParser() {};
    inline ~ElseTailParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<ElseTailResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ElseTailResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<ElseTailListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class ElseTailResult
{
public:
    inline ElseTailResult() {};
    inline ~ElseTailResult() {};

    void SetValue(OmniPointer<ElseTail> new_value);
    OmniPointer<ElseTail> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<ElseTail> value;
    bool result;
};

class ElseTailListResult
{
public:
    inline ElseTailListResult() {};
    inline ~ElseTailListResult() {};

    void SetValue(std::vector<OmniPointer<ElseTail>> new_value);
    std::vector<OmniPointer<ElseTail>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<ElseTail>> value;
    bool result;
};

class ElseTail
{
public:
    inline ElseTail() {};
    inline ~ElseTail() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetCodeBlock(OmniPointer<CodeBlock> input_value);
    OmniPointer<CodeBlock> GetCodeBlock();
    void SetElseKey(OmniPointer<String> input_value);
    OmniPointer<String> GetElseKey();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<CodeBlock> code_block_field;
    OmniPointer<String> else_key_field;
};

class ConditionalParser
{
public:
    inline ConditionalParser() {};
    inline ~ConditionalParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<ConditionalResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ConditionalResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<ConditionalListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class ConditionalResult
{
public:
    inline ConditionalResult() {};
    inline ~ConditionalResult() {};

    void SetValue(OmniPointer<Conditional> new_value);
    OmniPointer<Conditional> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<Conditional> value;
    bool result;
};

class ConditionalListResult
{
public:
    inline ConditionalListResult() {};
    inline ~ConditionalListResult() {};

    void SetValue(std::vector<OmniPointer<Conditional>> new_value);
    std::vector<OmniPointer<Conditional>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<Conditional>> value;
    bool result;
};

class Conditional
{
public:
    inline Conditional() {};
    inline ~Conditional() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetCodeBlock(OmniPointer<CodeBlock> input_value);
    OmniPointer<CodeBlock> GetCodeBlock();
    void SetConditionalKey(OmniPointer<String> input_value);
    OmniPointer<String> GetConditionalKey();
    void SetElseTail(OmniPointer<ElseTail> input_value);
    OmniPointer<ElseTail> GetElseTail();
    void SetRvalue(OmniPointer<RValue> input_value);
    OmniPointer<RValue> GetRvalue();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<CodeBlock> code_block_field;
    OmniPointer<String> conditional_key_field;
    OmniPointer<ElseTail> else_tail_field;
    OmniPointer<RValue> rvalue_field;
};

class LoopParser
{
public:
    inline LoopParser() {};
    inline ~LoopParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<LoopResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<LoopResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<LoopListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class LoopResult
{
public:
    inline LoopResult() {};
    inline ~LoopResult() {};

    void SetValue(OmniPointer<Loop> new_value);
    OmniPointer<Loop> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<Loop> value;
    bool result;
};

class LoopListResult
{
public:
    inline LoopListResult() {};
    inline ~LoopListResult() {};

    void SetValue(std::vector<OmniPointer<Loop>> new_value);
    std::vector<OmniPointer<Loop>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<Loop>> value;
    bool result;
};

class Loop
{
public:
    inline Loop() {};
    inline ~Loop() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetCodeBlock(OmniPointer<CodeBlock> input_value);
    OmniPointer<CodeBlock> GetCodeBlock();
    void SetLoopKey(OmniPointer<String> input_value);
    OmniPointer<String> GetLoopKey();
    void SetRvalue(OmniPointer<RValue> input_value);
    OmniPointer<RValue> GetRvalue();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<CodeBlock> code_block_field;
    OmniPointer<String> loop_key_field;
    OmniPointer<RValue> rvalue_field;
};

class CallParser
{
public:
    inline CallParser() {};
    inline ~CallParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<CallResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<CallResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<CallListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class CallResult
{
public:
    inline CallResult() {};
    inline ~CallResult() {};

    void SetValue(OmniPointer<Call> new_value);
    OmniPointer<Call> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<Call> value;
    bool result;
};

class CallListResult
{
public:
    inline CallListResult() {};
    inline ~CallListResult() {};

    void SetValue(std::vector<OmniPointer<Call>> new_value);
    std::vector<OmniPointer<Call>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<Call>> value;
    bool result;
};

class Call
{
public:
    inline Call() {};
    inline ~Call() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetFunction(OmniPointer<Name> input_value);
    OmniPointer<Name> GetFunction();
    void SetParameters(OmniPointer<ParameterList> input_value);
    OmniPointer<ParameterList> GetParameters();
    void SetVariable(OmniPointer<Name> input_value);
    OmniPointer<Name> GetVariable();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<Name> function_field;
    OmniPointer<ParameterList> parameters_field;
    OmniPointer<Name> variable_field;
};

class AllocateParser
{
public:
    inline AllocateParser() {};
    inline ~AllocateParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<AllocateResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<AllocateResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<AllocateListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class AllocateResult
{
public:
    inline AllocateResult() {};
    inline ~AllocateResult() {};

    void SetValue(OmniPointer<Allocate> new_value);
    OmniPointer<Allocate> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<Allocate> value;
    bool result;
};

class AllocateListResult
{
public:
    inline AllocateListResult() {};
    inline ~AllocateListResult() {};

    void SetValue(std::vector<OmniPointer<Allocate>> new_value);
    std::vector<OmniPointer<Allocate>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<Allocate>> value;
    bool result;
};

class Allocate
{
public:
    inline Allocate() {};
    inline ~Allocate() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetManagedType(OmniPointer<QualfiedName> input_value);
    OmniPointer<QualfiedName> GetManagedType();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<QualfiedName> managed_type_field;
};

class InstructionParser
{
public:
    inline InstructionParser() {};
    inline ~InstructionParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<InstructionResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<InstructionResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<InstructionListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class InstructionResult
{
public:
    inline InstructionResult() {};
    inline ~InstructionResult() {};

    void SetValue(OmniPointer<Instruction> new_value);
    OmniPointer<Instruction> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<Instruction> value;
    bool result;
};

class InstructionListResult
{
public:
    inline InstructionListResult() {};
    inline ~InstructionListResult() {};

    void SetValue(std::vector<OmniPointer<Instruction>> new_value);
    std::vector<OmniPointer<Instruction>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<Instruction>> value;
    bool result;
};

class Instruction
{
public:
    inline Instruction() {};
    inline ~Instruction() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetAssignment(OmniPointer<Assignment> input_value);
    OmniPointer<Assignment> GetAssignment();
    void SetCall(OmniPointer<Call> input_value);
    OmniPointer<Call> GetCall();
    void SetCodeBlock(OmniPointer<CodeBlock> input_value);
    OmniPointer<CodeBlock> GetCodeBlock();
    void SetComment(OmniPointer<Comment> input_value);
    OmniPointer<Comment> GetComment();
    void SetConditional(OmniPointer<Conditional> input_value);
    OmniPointer<Conditional> GetConditional();
    void SetDeclaration(OmniPointer<Declaration> input_value);
    OmniPointer<Declaration> GetDeclaration();
    void SetLoop(OmniPointer<Loop> input_value);
    OmniPointer<Loop> GetLoop();
    void SetRtn(OmniPointer<Return> input_value);
    OmniPointer<Return> GetRtn();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<Assignment> assignment_field;
    OmniPointer<Call> call_field;
    OmniPointer<CodeBlock> code_block_field;
    OmniPointer<Comment> comment_field;
    OmniPointer<Conditional> conditional_field;
    OmniPointer<Declaration> declaration_field;
    OmniPointer<Loop> loop_field;
    OmniPointer<Return> rtn_field;
};

class RValueSingleParser
{
public:
    inline RValueSingleParser() {};
    inline ~RValueSingleParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<RValueSingleResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<RValueSingleResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<RValueSingleListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class RValueSingleResult
{
public:
    inline RValueSingleResult() {};
    inline ~RValueSingleResult() {};

    void SetValue(OmniPointer<RValueSingle> new_value);
    OmniPointer<RValueSingle> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<RValueSingle> value;
    bool result;
};

class RValueSingleListResult
{
public:
    inline RValueSingleListResult() {};
    inline ~RValueSingleListResult() {};

    void SetValue(std::vector<OmniPointer<RValueSingle>> new_value);
    std::vector<OmniPointer<RValueSingle>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<RValueSingle>> value;
    bool result;
};

class RValueSingle
{
public:
    inline RValueSingle() {};
    inline ~RValueSingle() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetAllocate(OmniPointer<Allocate> input_value);
    OmniPointer<Allocate> GetAllocate();
    void SetBooleanLiteral(OmniPointer<Boolean> input_value);
    OmniPointer<Boolean> GetBooleanLiteral();
    void SetByteLiteral(OmniPointer<Byte> input_value);
    OmniPointer<Byte> GetByteLiteral();
    void SetCall(OmniPointer<Call> input_value);
    OmniPointer<Call> GetCall();
    void SetDecimalLiteral(OmniPointer<Decimal> input_value);
    OmniPointer<Decimal> GetDecimalLiteral();
    void SetIntegerLiteral(OmniPointer<Number> input_value);
    OmniPointer<Number> GetIntegerLiteral();
    void SetStringLiteral(OmniPointer<Literal> input_value);
    OmniPointer<Literal> GetStringLiteral();
    void SetUnaryOperator(OmniPointer<UnaryOperator> input_value);
    OmniPointer<UnaryOperator> GetUnaryOperator();
    void SetVariable(OmniPointer<Name> input_value);
    OmniPointer<Name> GetVariable();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<Allocate> allocate_field;
    OmniPointer<Boolean> boolean_literal_field;
    OmniPointer<Byte> byte_literal_field;
    OmniPointer<Call> call_field;
    OmniPointer<Decimal> decimal_literal_field;
    OmniPointer<Number> integer_literal_field;
    OmniPointer<Literal> string_literal_field;
    OmniPointer<UnaryOperator> unary_operator_field;
    OmniPointer<Name> variable_field;
};

class RValueTailParser
{
public:
    inline RValueTailParser() {};
    inline ~RValueTailParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<RValueTailResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<RValueTailResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<RValueTailListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class RValueTailResult
{
public:
    inline RValueTailResult() {};
    inline ~RValueTailResult() {};

    void SetValue(OmniPointer<RValueTail> new_value);
    OmniPointer<RValueTail> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<RValueTail> value;
    bool result;
};

class RValueTailListResult
{
public:
    inline RValueTailListResult() {};
    inline ~RValueTailListResult() {};

    void SetValue(std::vector<OmniPointer<RValueTail>> new_value);
    std::vector<OmniPointer<RValueTail>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<RValueTail>> value;
    bool result;
};

class RValueTail
{
public:
    inline RValueTail() {};
    inline ~RValueTail() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetBinaryOperator(OmniPointer<BinaryOperator> input_value);
    OmniPointer<BinaryOperator> GetBinaryOperator();
    void SetTail(OmniPointer<RValueTail> input_value);
    OmniPointer<RValueTail> GetTail();
    void SetValue(OmniPointer<RValueSingle> input_value);
    OmniPointer<RValueSingle> GetValue();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<BinaryOperator> binary_operator_field;
    OmniPointer<RValueTail> tail_field;
    OmniPointer<RValueSingle> value_field;
};

class RValueParser
{
public:
    inline RValueParser() {};
    inline ~RValueParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<RValueResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<RValueResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<RValueListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class RValueResult
{
public:
    inline RValueResult() {};
    inline ~RValueResult() {};

    void SetValue(OmniPointer<RValue> new_value);
    OmniPointer<RValue> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<RValue> value;
    bool result;
};

class RValueListResult
{
public:
    inline RValueListResult() {};
    inline ~RValueListResult() {};

    void SetValue(std::vector<OmniPointer<RValue>> new_value);
    std::vector<OmniPointer<RValue>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<RValue>> value;
    bool result;
};

class RValue
{
public:
    inline RValue() {};
    inline ~RValue() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetTail(OmniPointer<RValueTail> input_value);
    OmniPointer<RValueTail> GetTail();
    void SetValue(OmniPointer<RValueSingle> input_value);
    OmniPointer<RValueSingle> GetValue();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<RValueTail> tail_field;
    OmniPointer<RValueSingle> value_field;
};

class BinaryOperatorParser
{
public:
    inline BinaryOperatorParser() {};
    inline ~BinaryOperatorParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<BinaryOperatorResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<BinaryOperatorResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<BinaryOperatorListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class BinaryOperatorResult
{
public:
    inline BinaryOperatorResult() {};
    inline ~BinaryOperatorResult() {};

    void SetValue(OmniPointer<BinaryOperator> new_value);
    OmniPointer<BinaryOperator> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<BinaryOperator> value;
    bool result;
};

class BinaryOperatorListResult
{
public:
    inline BinaryOperatorListResult() {};
    inline ~BinaryOperatorListResult() {};

    void SetValue(std::vector<OmniPointer<BinaryOperator>> new_value);
    std::vector<OmniPointer<BinaryOperator>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<BinaryOperator>> value;
    bool result;
};

class BinaryOperator
{
public:
    inline BinaryOperator() {};
    inline ~BinaryOperator() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetAddition(OmniPointer<String> input_value);
    OmniPointer<String> GetAddition();
    void SetAndOp(OmniPointer<String> input_value);
    OmniPointer<String> GetAndOp();
    void SetEquality(OmniPointer<String> input_value);
    OmniPointer<String> GetEquality();
    void SetGreaterThanEq(OmniPointer<String> input_value);
    OmniPointer<String> GetGreaterThanEq();
    void SetGreaterThan(OmniPointer<String> input_value);
    OmniPointer<String> GetGreaterThan();
    void SetLessThanEq(OmniPointer<String> input_value);
    OmniPointer<String> GetLessThanEq();
    void SetLessThan(OmniPointer<String> input_value);
    OmniPointer<String> GetLessThan();
    void SetNotEquality(OmniPointer<String> input_value);
    OmniPointer<String> GetNotEquality();
    void SetOrOp(OmniPointer<String> input_value);
    OmniPointer<String> GetOrOp();
    void SetSubtraction(OmniPointer<String> input_value);
    OmniPointer<String> GetSubtraction();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<String> addition_field;
    OmniPointer<String> and_op_field;
    OmniPointer<String> equality_field;
    OmniPointer<String> greater_than_eq_field;
    OmniPointer<String> greater_than_field;
    OmniPointer<String> less_than_eq_field;
    OmniPointer<String> less_than_field;
    OmniPointer<String> not_equality_field;
    OmniPointer<String> or_op_field;
    OmniPointer<String> subtraction_field;
};

class UnaryOperatorParser
{
public:
    inline UnaryOperatorParser() {};
    inline ~UnaryOperatorParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<UnaryOperatorResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<UnaryOperatorResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<UnaryOperatorListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class UnaryOperatorResult
{
public:
    inline UnaryOperatorResult() {};
    inline ~UnaryOperatorResult() {};

    void SetValue(OmniPointer<UnaryOperator> new_value);
    OmniPointer<UnaryOperator> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<UnaryOperator> value;
    bool result;
};

class UnaryOperatorListResult
{
public:
    inline UnaryOperatorListResult() {};
    inline ~UnaryOperatorListResult() {};

    void SetValue(std::vector<OmniPointer<UnaryOperator>> new_value);
    std::vector<OmniPointer<UnaryOperator>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<UnaryOperator>> value;
    bool result;
};

class UnaryOperator
{
public:
    inline UnaryOperator() {};
    inline ~UnaryOperator() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetNegation(OmniPointer<String> input_value);
    OmniPointer<String> GetNegation();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<String> negation_field;
};

class CommentParser
{
public:
    inline CommentParser() {};
    inline ~CommentParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<CommentResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<CommentResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<CommentListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class CommentResult
{
public:
    inline CommentResult() {};
    inline ~CommentResult() {};

    void SetValue(OmniPointer<Comment> new_value);
    OmniPointer<Comment> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<Comment> value;
    bool result;
};

class CommentListResult
{
public:
    inline CommentListResult() {};
    inline ~CommentListResult() {};

    void SetValue(std::vector<OmniPointer<Comment>> new_value);
    std::vector<OmniPointer<Comment>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<Comment>> value;
    bool result;
};

class Comment
{
public:
    inline Comment() {};
    inline ~Comment() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetContent(std::vector<OmniPointer<CommentCharacter>> input_value);
    std::vector<OmniPointer<CommentCharacter>> GetContent();

private:
    OmniPointer<LengthString> length_string;
    std::vector<OmniPointer<CommentCharacter>> content_field;
};

class CommentCharacterParser
{
public:
    inline CommentCharacterParser() {};
    inline ~CommentCharacterParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<CommentCharacterResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<CommentCharacterResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<CommentCharacterListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class CommentCharacterResult
{
public:
    inline CommentCharacterResult() {};
    inline ~CommentCharacterResult() {};

    void SetValue(OmniPointer<CommentCharacter> new_value);
    OmniPointer<CommentCharacter> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<CommentCharacter> value;
    bool result;
};

class CommentCharacterListResult
{
public:
    inline CommentCharacterListResult() {};
    inline ~CommentCharacterListResult() {};

    void SetValue(std::vector<OmniPointer<CommentCharacter>> new_value);
    std::vector<OmniPointer<CommentCharacter>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<CommentCharacter>> value;
    bool result;
};

class CommentCharacter
{
public:
    inline CommentCharacter() {};
    inline ~CommentCharacter() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();

private:
    OmniPointer<LengthString> length_string;
};

class QualfiedNameParser
{
public:
    inline QualfiedNameParser() {};
    inline ~QualfiedNameParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<QualfiedNameResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<QualfiedNameResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<QualfiedNameListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class QualfiedNameResult
{
public:
    inline QualfiedNameResult() {};
    inline ~QualfiedNameResult() {};

    void SetValue(OmniPointer<QualfiedName> new_value);
    OmniPointer<QualfiedName> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<QualfiedName> value;
    bool result;
};

class QualfiedNameListResult
{
public:
    inline QualfiedNameListResult() {};
    inline ~QualfiedNameListResult() {};

    void SetValue(std::vector<OmniPointer<QualfiedName>> new_value);
    std::vector<OmniPointer<QualfiedName>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<QualfiedName>> value;
    bool result;
};

class QualfiedName
{
public:
    inline QualfiedName() {};
    inline ~QualfiedName() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetName(OmniPointer<Name> input_value);
    OmniPointer<Name> GetName();
    void SetTail(OmniPointer<NameTail> input_value);
    OmniPointer<NameTail> GetTail();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<Name> name_field;
    OmniPointer<NameTail> tail_field;
};

class NameTailParser
{
public:
    inline NameTailParser() {};
    inline ~NameTailParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<NameTailResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<NameTailResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<NameTailListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class NameTailResult
{
public:
    inline NameTailResult() {};
    inline ~NameTailResult() {};

    void SetValue(OmniPointer<NameTail> new_value);
    OmniPointer<NameTail> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<NameTail> value;
    bool result;
};

class NameTailListResult
{
public:
    inline NameTailListResult() {};
    inline ~NameTailListResult() {};

    void SetValue(std::vector<OmniPointer<NameTail>> new_value);
    std::vector<OmniPointer<NameTail>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<NameTail>> value;
    bool result;
};

class NameTail
{
public:
    inline NameTail() {};
    inline ~NameTail() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetName(OmniPointer<Name> input_value);
    OmniPointer<Name> GetName();
    void SetTail(OmniPointer<NameTail> input_value);
    OmniPointer<NameTail> GetTail();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<Name> name_field;
    OmniPointer<NameTail> tail_field;
};

class NameParser
{
public:
    inline NameParser() {};
    inline ~NameParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<NameResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<NameResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<NameListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class NameResult
{
public:
    inline NameResult() {};
    inline ~NameResult() {};

    void SetValue(OmniPointer<Name> new_value);
    OmniPointer<Name> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<Name> value;
    bool result;
};

class NameListResult
{
public:
    inline NameListResult() {};
    inline ~NameListResult() {};

    void SetValue(std::vector<OmniPointer<Name>> new_value);
    std::vector<OmniPointer<Name>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<Name>> value;
    bool result;
};

class Name
{
public:
    inline Name() {};
    inline ~Name() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();

private:
    OmniPointer<LengthString> length_string;
};

class NameCharacterParser
{
public:
    inline NameCharacterParser() {};
    inline ~NameCharacterParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<NameCharacterResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<NameCharacterResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<NameCharacterListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class NameCharacterResult
{
public:
    inline NameCharacterResult() {};
    inline ~NameCharacterResult() {};

    void SetValue(OmniPointer<NameCharacter> new_value);
    OmniPointer<NameCharacter> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<NameCharacter> value;
    bool result;
};

class NameCharacterListResult
{
public:
    inline NameCharacterListResult() {};
    inline ~NameCharacterListResult() {};

    void SetValue(std::vector<OmniPointer<NameCharacter>> new_value);
    std::vector<OmniPointer<NameCharacter>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<NameCharacter>> value;
    bool result;
};

class NameCharacter
{
public:
    inline NameCharacter() {};
    inline ~NameCharacter() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();

private:
    OmniPointer<LengthString> length_string;
};

class BooleanParser
{
public:
    inline BooleanParser() {};
    inline ~BooleanParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<BooleanResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<BooleanResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<BooleanListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class BooleanResult
{
public:
    inline BooleanResult() {};
    inline ~BooleanResult() {};

    void SetValue(OmniPointer<Boolean> new_value);
    OmniPointer<Boolean> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<Boolean> value;
    bool result;
};

class BooleanListResult
{
public:
    inline BooleanListResult() {};
    inline ~BooleanListResult() {};

    void SetValue(std::vector<OmniPointer<Boolean>> new_value);
    std::vector<OmniPointer<Boolean>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<Boolean>> value;
    bool result;
};

class Boolean
{
public:
    inline Boolean() {};
    inline ~Boolean() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();

private:
    OmniPointer<LengthString> length_string;
};

class ByteParser
{
public:
    inline ByteParser() {};
    inline ~ByteParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<ByteResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ByteResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<ByteListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class ByteResult
{
public:
    inline ByteResult() {};
    inline ~ByteResult() {};

    void SetValue(OmniPointer<Byte> new_value);
    OmniPointer<Byte> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<Byte> value;
    bool result;
};

class ByteListResult
{
public:
    inline ByteListResult() {};
    inline ~ByteListResult() {};

    void SetValue(std::vector<OmniPointer<Byte>> new_value);
    std::vector<OmniPointer<Byte>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<Byte>> value;
    bool result;
};

class Byte
{
public:
    inline Byte() {};
    inline ~Byte() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();
    void SetHigh(OmniPointer<ByteDigit> input_value);
    OmniPointer<ByteDigit> GetHigh();
    void SetLow(OmniPointer<ByteDigit> input_value);
    OmniPointer<ByteDigit> GetLow();

private:
    OmniPointer<LengthString> length_string;
    OmniPointer<ByteDigit> high_field;
    OmniPointer<ByteDigit> low_field;
};

class ByteDigitParser
{
public:
    inline ByteDigitParser() {};
    inline ~ByteDigitParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<ByteDigitResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ByteDigitResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<ByteDigitListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class ByteDigitResult
{
public:
    inline ByteDigitResult() {};
    inline ~ByteDigitResult() {};

    void SetValue(OmniPointer<ByteDigit> new_value);
    OmniPointer<ByteDigit> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<ByteDigit> value;
    bool result;
};

class ByteDigitListResult
{
public:
    inline ByteDigitListResult() {};
    inline ~ByteDigitListResult() {};

    void SetValue(std::vector<OmniPointer<ByteDigit>> new_value);
    std::vector<OmniPointer<ByteDigit>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<ByteDigit>> value;
    bool result;
};

class ByteDigit
{
public:
    inline ByteDigit() {};
    inline ~ByteDigit() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();

private:
    OmniPointer<LengthString> length_string;
};

class NegativeParser
{
public:
    inline NegativeParser() {};
    inline ~NegativeParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<NegativeResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<NegativeResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<NegativeListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class NegativeResult
{
public:
    inline NegativeResult() {};
    inline ~NegativeResult() {};

    void SetValue(OmniPointer<Negative> new_value);
    OmniPointer<Negative> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<Negative> value;
    bool result;
};

class NegativeListResult
{
public:
    inline NegativeListResult() {};
    inline ~NegativeListResult() {};

    void SetValue(std::vector<OmniPointer<Negative>> new_value);
    std::vector<OmniPointer<Negative>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<Negative>> value;
    bool result;
};

class Negative
{
public:
    inline Negative() {};
    inline ~Negative() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();

private:
    OmniPointer<LengthString> length_string;
};

class DecimalParser
{
public:
    inline DecimalParser() {};
    inline ~DecimalParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<DecimalResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<DecimalResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<DecimalListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class DecimalResult
{
public:
    inline DecimalResult() {};
    inline ~DecimalResult() {};

    void SetValue(OmniPointer<Decimal> new_value);
    OmniPointer<Decimal> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<Decimal> value;
    bool result;
};

class DecimalListResult
{
public:
    inline DecimalListResult() {};
    inline ~DecimalListResult() {};

    void SetValue(std::vector<OmniPointer<Decimal>> new_value);
    std::vector<OmniPointer<Decimal>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<Decimal>> value;
    bool result;
};

class Decimal
{
public:
    inline Decimal() {};
    inline ~Decimal() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();

private:
    OmniPointer<LengthString> length_string;
};

class NumberParser
{
public:
    inline NumberParser() {};
    inline ~NumberParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<NumberResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<NumberResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<NumberListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class NumberResult
{
public:
    inline NumberResult() {};
    inline ~NumberResult() {};

    void SetValue(OmniPointer<Number> new_value);
    OmniPointer<Number> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<Number> value;
    bool result;
};

class NumberListResult
{
public:
    inline NumberListResult() {};
    inline ~NumberListResult() {};

    void SetValue(std::vector<OmniPointer<Number>> new_value);
    std::vector<OmniPointer<Number>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<Number>> value;
    bool result;
};

class Number
{
public:
    inline Number() {};
    inline ~Number() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();

private:
    OmniPointer<LengthString> length_string;
};

class DigitParser
{
public:
    inline DigitParser() {};
    inline ~DigitParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<DigitResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<DigitResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<DigitListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class DigitResult
{
public:
    inline DigitResult() {};
    inline ~DigitResult() {};

    void SetValue(OmniPointer<Digit> new_value);
    OmniPointer<Digit> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<Digit> value;
    bool result;
};

class DigitListResult
{
public:
    inline DigitListResult() {};
    inline ~DigitListResult() {};

    void SetValue(std::vector<OmniPointer<Digit>> new_value);
    std::vector<OmniPointer<Digit>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<Digit>> value;
    bool result;
};

class Digit
{
public:
    inline Digit() {};
    inline ~Digit() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();

private:
    OmniPointer<LengthString> length_string;
};

class LiteralParser
{
public:
    inline LiteralParser() {};
    inline ~LiteralParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<LiteralResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<LiteralResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<LiteralListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class LiteralResult
{
public:
    inline LiteralResult() {};
    inline ~LiteralResult() {};

    void SetValue(OmniPointer<Literal> new_value);
    OmniPointer<Literal> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<Literal> value;
    bool result;
};

class LiteralListResult
{
public:
    inline LiteralListResult() {};
    inline ~LiteralListResult() {};

    void SetValue(std::vector<OmniPointer<Literal>> new_value);
    std::vector<OmniPointer<Literal>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<Literal>> value;
    bool result;
};

class Literal
{
public:
    inline Literal() {};
    inline ~Literal() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();

private:
    OmniPointer<LengthString> length_string;
};

class LiteralCharacterParser
{
public:
    inline LiteralCharacterParser() {};
    inline ~LiteralCharacterParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<LiteralCharacterResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<LiteralCharacterResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<LiteralCharacterListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class LiteralCharacterResult
{
public:
    inline LiteralCharacterResult() {};
    inline ~LiteralCharacterResult() {};

    void SetValue(OmniPointer<LiteralCharacter> new_value);
    OmniPointer<LiteralCharacter> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<LiteralCharacter> value;
    bool result;
};

class LiteralCharacterListResult
{
public:
    inline LiteralCharacterListResult() {};
    inline ~LiteralCharacterListResult() {};

    void SetValue(std::vector<OmniPointer<LiteralCharacter>> new_value);
    std::vector<OmniPointer<LiteralCharacter>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<LiteralCharacter>> value;
    bool result;
};

class LiteralCharacter
{
public:
    inline LiteralCharacter() {};
    inline ~LiteralCharacter() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();

private:
    OmniPointer<LengthString> length_string;
};

class WhitespaceParser
{
public:
    inline WhitespaceParser() {};
    inline ~WhitespaceParser() {};

    void SetParserNetwork(OmniPointer<ParserNetwork> input);
    bool ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<WhitespaceResult> result);
    bool ParseSingle(OmniPointer<LengthString> index);
    bool ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<WhitespaceResult> result);
    bool ParseOptional(OmniPointer<LengthString> index);
    bool ParseManySave(OmniPointer<LengthString> index, OmniPointer<WhitespaceListResult> list_result, int minimum, int maximum);
    bool ParseMany(OmniPointer<LengthString> index, int minimum, int maximum);

private:
    OmniPointer<ParserNetwork> parser_network;
};

class WhitespaceResult
{
public:
    inline WhitespaceResult() {};
    inline ~WhitespaceResult() {};

    void SetValue(OmniPointer<Whitespace> new_value);
    OmniPointer<Whitespace> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    OmniPointer<Whitespace> value;
    bool result;
};

class WhitespaceListResult
{
public:
    inline WhitespaceListResult() {};
    inline ~WhitespaceListResult() {};

    void SetValue(std::vector<OmniPointer<Whitespace>> new_value);
    std::vector<OmniPointer<Whitespace>> GetValue();
    void SetResult(bool new_result);
    bool GetResult();

private:
    std::vector<OmniPointer<Whitespace>> value;
    bool result;
};

class Whitespace
{
public:
    inline Whitespace() {};
    inline ~Whitespace() {};

    void SetLengthString(OmniPointer<LengthString> new_value);
    std::string UnParse();

private:
    OmniPointer<LengthString> length_string;
};
};
};
};
};

#endif
