#ifndef S84_CTCODE_DBNF_H
#define S84_CTCODE_DBNF_H

#include <cstring>
#include <list>
#include <string>
#include <vector>

namespace s84
{
namespace ctcode
{
namespace dbnf
{
class Node;
class String;
class CTCodeFile;
class ExternalDefinition;
class UnmanagedType;
class Definition;
class InterfaceDef;
class ClassDef;
class ContentDeclaration;
class ContentDefinition;
class PrimativeType;
class DefinedType;
class SingletonType;
class DimensionalNote;
class DimensionalType;
class MapNote;
class MapType;
class ValueType;
class ParameterListDef;
class ParameterList;
class CodeBlock;
class DeclarationAssign;
class Declaration;
class Assignment;
class Return;
class ElseTail;
class Conditional;
class Loop;
class Call;
class Allocate;
class Instruction;
class RValueSingle;
class RValueTail;
class RValue;
class BinaryOperator;
class UnaryOperator;
class Comment;
class CommentCharacter;
class QualfiedName;
class NameTail;
class Name;
class NameCharacter;
class Boolean;
class Byte;
class ByteDigit;
class Negative;
class Decimal;
class Number;
class Digit;
class Literal;
class LiteralCharacter;
class HexDigit;
class Whitespace;

struct LengthString
{
    const char* data;
    size_t length;
};

class Node
{
public:
    Node();
    virtual ~Node();

    std::string UnParse();
    s84::ctcode::dbnf::LengthString UnParseLString();
    std::list<s84::ctcode::dbnf::Node*> GetChildren();

protected:
    void SetString(s84::ctcode::dbnf::LengthString data);
    void SetChildren(std::list<s84::ctcode::dbnf::Node*> children);

private:
    s84::ctcode::dbnf::LengthString data_;
    std::list<s84::ctcode::dbnf::Node*> children_;
};

template<class T>
class List : public s84::ctcode::dbnf::Node
{
public:
    List()
    {
    }
    virtual ~List()
    {
    }

    virtual std::list<T*> GetList()
    {
        return list_;
    }

    virtual std::vector<T*> GetVector()
    {
        return {list_.begin(), list_.end()};
    }

protected:
    std::list<T*> list_;
};

class String : public s84::ctcode::dbnf::Node
{
public:
    String(s84::ctcode::dbnf::LengthString data);
    ~String();
};

typedef List<CTCodeFile> CTCodeFileList;

class CTCodeFile : public s84::ctcode::dbnf::Node
{
public:
    CTCodeFile();
    ~CTCodeFile();

    static s84::ctcode::dbnf::CTCodeFile* Parse(const char*& index);
    static s84::ctcode::dbnf::CTCodeFile* Parse(s84::ctcode::dbnf::LengthString& index);

    List<s84::ctcode::dbnf::ExternalDefinition>* GetDeclarations();
    List<s84::ctcode::dbnf::Definition>* GetDefinitions();
    List<s84::ctcode::dbnf::UnmanagedType>* GetUnmanagedTypes();

private:
    List<s84::ctcode::dbnf::ExternalDefinition>* declarations_;
    List<s84::ctcode::dbnf::Definition>* definitions_;
    List<s84::ctcode::dbnf::UnmanagedType>* unmanaged_types_;
};

typedef List<ExternalDefinition> ExternalDefinitionList;

class ExternalDefinition : public s84::ctcode::dbnf::Node
{
public:
    ExternalDefinition();
    ~ExternalDefinition();

    static s84::ctcode::dbnf::ExternalDefinition* Parse(const char*& index);
    static s84::ctcode::dbnf::ExternalDefinition* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::QualfiedName* GetExdef();

private:
    s84::ctcode::dbnf::QualfiedName* exdef_;
};

typedef List<UnmanagedType> UnmanagedTypeList;

class UnmanagedType : public s84::ctcode::dbnf::Node
{
public:
    UnmanagedType();
    ~UnmanagedType();

    static s84::ctcode::dbnf::UnmanagedType* Parse(const char*& index);
    static s84::ctcode::dbnf::UnmanagedType* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::QualfiedName* GetUnmanagedType();

private:
    s84::ctcode::dbnf::QualfiedName* unmanaged_type_;
};

typedef List<Definition> DefinitionList;

class Definition : public s84::ctcode::dbnf::Node
{
public:
    Definition();
    ~Definition();

    static s84::ctcode::dbnf::Definition* Parse(const char*& index);
    static s84::ctcode::dbnf::Definition* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::ClassDef* GetClassDef();
    s84::ctcode::dbnf::InterfaceDef* GetInterfaceDef();

private:
    s84::ctcode::dbnf::ClassDef* classDef_;
    s84::ctcode::dbnf::InterfaceDef* interfaceDef_;
};

typedef List<InterfaceDef> InterfaceDefList;

class InterfaceDef : public s84::ctcode::dbnf::Node
{
public:
    InterfaceDef();
    ~InterfaceDef();

    static s84::ctcode::dbnf::InterfaceDef* Parse(const char*& index);
    static s84::ctcode::dbnf::InterfaceDef* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::Comment* GetComment();
    List<s84::ctcode::dbnf::ContentDeclaration>* GetDeclarations();
    s84::ctcode::dbnf::Name* GetName();

private:
    s84::ctcode::dbnf::Comment* comment_;
    List<s84::ctcode::dbnf::ContentDeclaration>* declarations_;
    s84::ctcode::dbnf::Name* name_;
};

typedef List<ClassDef> ClassDefList;

class ClassDef : public s84::ctcode::dbnf::Node
{
public:
    ClassDef();
    ~ClassDef();

    static s84::ctcode::dbnf::ClassDef* Parse(const char*& index);
    static s84::ctcode::dbnf::ClassDef* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::Comment* GetComment();
    List<s84::ctcode::dbnf::ContentDefinition>* GetDefinitions();
    s84::ctcode::dbnf::Name* GetName();

private:
    s84::ctcode::dbnf::Comment* comment_;
    List<s84::ctcode::dbnf::ContentDefinition>* definitions_;
    s84::ctcode::dbnf::Name* name_;
};

typedef List<ContentDeclaration> ContentDeclarationList;

class ContentDeclaration : public s84::ctcode::dbnf::Node
{
public:
    ContentDeclaration();
    ~ContentDeclaration();

    static s84::ctcode::dbnf::ContentDeclaration* Parse(const char*& index);
    static s84::ctcode::dbnf::ContentDeclaration* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::Comment* GetComment();
    s84::ctcode::dbnf::Name* GetName();
    s84::ctcode::dbnf::ParameterListDef* GetParameters();
    s84::ctcode::dbnf::ValueType* GetType();

private:
    s84::ctcode::dbnf::Comment* comment_;
    s84::ctcode::dbnf::Name* name_;
    s84::ctcode::dbnf::ParameterListDef* parameters_;
    s84::ctcode::dbnf::ValueType* type_;
};

typedef List<ContentDefinition> ContentDefinitionList;

class ContentDefinition : public s84::ctcode::dbnf::Node
{
public:
    ContentDefinition();
    ~ContentDefinition();

    static s84::ctcode::dbnf::ContentDefinition* Parse(const char*& index);
    static s84::ctcode::dbnf::ContentDefinition* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::Comment* GetComment();
    s84::ctcode::dbnf::CodeBlock* GetFunctionBody();
    s84::ctcode::dbnf::Name* GetName();
    s84::ctcode::dbnf::ParameterListDef* GetParameters();
    s84::ctcode::dbnf::ValueType* GetType();

private:
    s84::ctcode::dbnf::Comment* comment_;
    s84::ctcode::dbnf::CodeBlock* functionBody_;
    s84::ctcode::dbnf::Name* name_;
    s84::ctcode::dbnf::ParameterListDef* parameters_;
    s84::ctcode::dbnf::ValueType* type_;
};

typedef List<PrimativeType> PrimativeTypeList;

class PrimativeType : public s84::ctcode::dbnf::Node
{
public:
    PrimativeType();
    ~PrimativeType();

    static s84::ctcode::dbnf::PrimativeType* Parse(const char*& index);
    static s84::ctcode::dbnf::PrimativeType* Parse(s84::ctcode::dbnf::LengthString& index);
};

typedef List<DefinedType> DefinedTypeList;

class DefinedType : public s84::ctcode::dbnf::Node
{
public:
    DefinedType();
    ~DefinedType();

    static s84::ctcode::dbnf::DefinedType* Parse(const char*& index);
    static s84::ctcode::dbnf::DefinedType* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::QualfiedName* GetName();

private:
    s84::ctcode::dbnf::QualfiedName* name_;
};

typedef List<SingletonType> SingletonTypeList;

class SingletonType : public s84::ctcode::dbnf::Node
{
public:
    SingletonType();
    ~SingletonType();

    static s84::ctcode::dbnf::SingletonType* Parse(const char*& index);
    static s84::ctcode::dbnf::SingletonType* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::DefinedType* GetDefinedType();
    s84::ctcode::dbnf::PrimativeType* GetPrimativeType();

private:
    s84::ctcode::dbnf::DefinedType* definedType_;
    s84::ctcode::dbnf::PrimativeType* primativeType_;
};

typedef List<DimensionalNote> DimensionalNoteList;

class DimensionalNote : public s84::ctcode::dbnf::Node
{
public:
    DimensionalNote();
    ~DimensionalNote();

    static s84::ctcode::dbnf::DimensionalNote* Parse(const char*& index);
    static s84::ctcode::dbnf::DimensionalNote* Parse(s84::ctcode::dbnf::LengthString& index);
};

typedef List<DimensionalType> DimensionalTypeList;

class DimensionalType : public s84::ctcode::dbnf::Node
{
public:
    DimensionalType();
    ~DimensionalType();

    static s84::ctcode::dbnf::DimensionalType* Parse(const char*& index);
    static s84::ctcode::dbnf::DimensionalType* Parse(s84::ctcode::dbnf::LengthString& index);

    List<s84::ctcode::dbnf::DimensionalNote>* GetDimensionalNote();
    s84::ctcode::dbnf::SingletonType* GetSingletonType();

private:
    List<s84::ctcode::dbnf::DimensionalNote>* dimensionalNote_;
    s84::ctcode::dbnf::SingletonType* singletonType_;
};

typedef List<MapNote> MapNoteList;

class MapNote : public s84::ctcode::dbnf::Node
{
public:
    MapNote();
    ~MapNote();

    static s84::ctcode::dbnf::MapNote* Parse(const char*& index);
    static s84::ctcode::dbnf::MapNote* Parse(s84::ctcode::dbnf::LengthString& index);
};

typedef List<MapType> MapTypeList;

class MapType : public s84::ctcode::dbnf::Node
{
public:
    MapType();
    ~MapType();

    static s84::ctcode::dbnf::MapType* Parse(const char*& index);
    static s84::ctcode::dbnf::MapType* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::MapNote* GetMapNote();
    s84::ctcode::dbnf::SingletonType* GetSingletonType();

private:
    s84::ctcode::dbnf::MapNote* mapNote_;
    s84::ctcode::dbnf::SingletonType* singletonType_;
};

typedef List<ValueType> ValueTypeList;

class ValueType : public s84::ctcode::dbnf::Node
{
public:
    ValueType();
    ~ValueType();

    static s84::ctcode::dbnf::ValueType* Parse(const char*& index);
    static s84::ctcode::dbnf::ValueType* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::DimensionalType* GetDimensionalType();
    s84::ctcode::dbnf::MapType* GetMapType();
    s84::ctcode::dbnf::SingletonType* GetSingletonType();

private:
    s84::ctcode::dbnf::DimensionalType* dimensionalType_;
    s84::ctcode::dbnf::MapType* mapType_;
    s84::ctcode::dbnf::SingletonType* singletonType_;
};

typedef List<ParameterListDef> ParameterListDefList;

class ParameterListDef : public s84::ctcode::dbnf::Node
{
public:
    ParameterListDef();
    ~ParameterListDef();

    static s84::ctcode::dbnf::ParameterListDef* Parse(const char*& index);
    static s84::ctcode::dbnf::ParameterListDef* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::Name* GetName();
    s84::ctcode::dbnf::ParameterListDef* GetParameterTail();
    s84::ctcode::dbnf::ValueType* GetType();

private:
    s84::ctcode::dbnf::Name* name_;
    s84::ctcode::dbnf::ParameterListDef* parameterTail_;
    s84::ctcode::dbnf::ValueType* type_;
};

typedef List<ParameterList> ParameterListList;

class ParameterList : public s84::ctcode::dbnf::Node
{
public:
    ParameterList();
    ~ParameterList();

    static s84::ctcode::dbnf::ParameterList* Parse(const char*& index);
    static s84::ctcode::dbnf::ParameterList* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::ParameterList* GetParameterTail();
    s84::ctcode::dbnf::RValue* GetRvalue();

private:
    s84::ctcode::dbnf::ParameterList* parameterTail_;
    s84::ctcode::dbnf::RValue* rvalue_;
};

typedef List<CodeBlock> CodeBlockList;

class CodeBlock : public s84::ctcode::dbnf::Node
{
public:
    CodeBlock();
    ~CodeBlock();

    static s84::ctcode::dbnf::CodeBlock* Parse(const char*& index);
    static s84::ctcode::dbnf::CodeBlock* Parse(s84::ctcode::dbnf::LengthString& index);

    List<s84::ctcode::dbnf::Instruction>* GetInstructions();

private:
    List<s84::ctcode::dbnf::Instruction>* instructions_;
};

typedef List<DeclarationAssign> DeclarationAssignList;

class DeclarationAssign : public s84::ctcode::dbnf::Node
{
public:
    DeclarationAssign();
    ~DeclarationAssign();

    static s84::ctcode::dbnf::DeclarationAssign* Parse(const char*& index);
    static s84::ctcode::dbnf::DeclarationAssign* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::RValue* GetRvalue();

private:
    s84::ctcode::dbnf::RValue* rvalue_;
};

typedef List<Declaration> DeclarationList;

class Declaration : public s84::ctcode::dbnf::Node
{
public:
    Declaration();
    ~Declaration();

    static s84::ctcode::dbnf::Declaration* Parse(const char*& index);
    static s84::ctcode::dbnf::Declaration* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::DeclarationAssign* GetAssignment();
    s84::ctcode::dbnf::Name* GetName();
    s84::ctcode::dbnf::ValueType* GetType();

private:
    s84::ctcode::dbnf::DeclarationAssign* assignment_;
    s84::ctcode::dbnf::Name* name_;
    s84::ctcode::dbnf::ValueType* type_;
};

typedef List<Assignment> AssignmentList;

class Assignment : public s84::ctcode::dbnf::Node
{
public:
    Assignment();
    ~Assignment();

    static s84::ctcode::dbnf::Assignment* Parse(const char*& index);
    static s84::ctcode::dbnf::Assignment* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::Name* GetLvalue();
    s84::ctcode::dbnf::RValue* GetRvalue();

private:
    s84::ctcode::dbnf::Name* lvalue_;
    s84::ctcode::dbnf::RValue* rvalue_;
};

typedef List<Return> ReturnList;

class Return : public s84::ctcode::dbnf::Node
{
public:
    Return();
    ~Return();

    static s84::ctcode::dbnf::Return* Parse(const char*& index);
    static s84::ctcode::dbnf::Return* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::String* GetRtn();
    s84::ctcode::dbnf::RValue* GetRvalue();

private:
    s84::ctcode::dbnf::String* rtn_;
    s84::ctcode::dbnf::RValue* rvalue_;
};

typedef List<ElseTail> ElseTailList;

class ElseTail : public s84::ctcode::dbnf::Node
{
public:
    ElseTail();
    ~ElseTail();

    static s84::ctcode::dbnf::ElseTail* Parse(const char*& index);
    static s84::ctcode::dbnf::ElseTail* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::CodeBlock* GetCodeBlock();
    s84::ctcode::dbnf::String* GetElseKey();

private:
    s84::ctcode::dbnf::CodeBlock* codeBlock_;
    s84::ctcode::dbnf::String* elseKey_;
};

typedef List<Conditional> ConditionalList;

class Conditional : public s84::ctcode::dbnf::Node
{
public:
    Conditional();
    ~Conditional();

    static s84::ctcode::dbnf::Conditional* Parse(const char*& index);
    static s84::ctcode::dbnf::Conditional* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::CodeBlock* GetCodeBlock();
    s84::ctcode::dbnf::String* GetConditionalKey();
    s84::ctcode::dbnf::ElseTail* GetElseTail();
    s84::ctcode::dbnf::RValue* GetRvalue();

private:
    s84::ctcode::dbnf::CodeBlock* codeBlock_;
    s84::ctcode::dbnf::String* conditionalKey_;
    s84::ctcode::dbnf::ElseTail* elseTail_;
    s84::ctcode::dbnf::RValue* rvalue_;
};

typedef List<Loop> LoopList;

class Loop : public s84::ctcode::dbnf::Node
{
public:
    Loop();
    ~Loop();

    static s84::ctcode::dbnf::Loop* Parse(const char*& index);
    static s84::ctcode::dbnf::Loop* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::CodeBlock* GetCodeBlock();
    s84::ctcode::dbnf::String* GetLoopKey();
    s84::ctcode::dbnf::RValue* GetRvalue();

private:
    s84::ctcode::dbnf::CodeBlock* codeBlock_;
    s84::ctcode::dbnf::String* loopKey_;
    s84::ctcode::dbnf::RValue* rvalue_;
};

typedef List<Call> CallList;

class Call : public s84::ctcode::dbnf::Node
{
public:
    Call();
    ~Call();

    static s84::ctcode::dbnf::Call* Parse(const char*& index);
    static s84::ctcode::dbnf::Call* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::Name* GetFunction();
    s84::ctcode::dbnf::ParameterList* GetParameters();
    s84::ctcode::dbnf::Name* GetVariable();

private:
    s84::ctcode::dbnf::Name* function_;
    s84::ctcode::dbnf::ParameterList* parameters_;
    s84::ctcode::dbnf::Name* variable_;
};

typedef List<Allocate> AllocateList;

class Allocate : public s84::ctcode::dbnf::Node
{
public:
    Allocate();
    ~Allocate();

    static s84::ctcode::dbnf::Allocate* Parse(const char*& index);
    static s84::ctcode::dbnf::Allocate* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::QualfiedName* GetManagedType();

private:
    s84::ctcode::dbnf::QualfiedName* managed_type_;
};

typedef List<Instruction> InstructionList;

class Instruction : public s84::ctcode::dbnf::Node
{
public:
    Instruction();
    ~Instruction();

    static s84::ctcode::dbnf::Instruction* Parse(const char*& index);
    static s84::ctcode::dbnf::Instruction* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::Assignment* GetAssignment();
    s84::ctcode::dbnf::Call* GetCall();
    s84::ctcode::dbnf::CodeBlock* GetCodeBlock();
    s84::ctcode::dbnf::Comment* GetComment();
    s84::ctcode::dbnf::Conditional* GetConditional();
    s84::ctcode::dbnf::Declaration* GetDeclaration();
    s84::ctcode::dbnf::Loop* GetLoop();
    s84::ctcode::dbnf::Return* GetRtn();

private:
    s84::ctcode::dbnf::Assignment* assignment_;
    s84::ctcode::dbnf::Call* call_;
    s84::ctcode::dbnf::CodeBlock* codeBlock_;
    s84::ctcode::dbnf::Comment* comment_;
    s84::ctcode::dbnf::Conditional* conditional_;
    s84::ctcode::dbnf::Declaration* declaration_;
    s84::ctcode::dbnf::Loop* loop_;
    s84::ctcode::dbnf::Return* rtn_;
};

typedef List<RValueSingle> RValueSingleList;

class RValueSingle : public s84::ctcode::dbnf::Node
{
public:
    RValueSingle();
    ~RValueSingle();

    static s84::ctcode::dbnf::RValueSingle* Parse(const char*& index);
    static s84::ctcode::dbnf::RValueSingle* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::Allocate* GetAllocate();
    s84::ctcode::dbnf::Boolean* GetBooleanLiteral();
    s84::ctcode::dbnf::Byte* GetByteLiteral();
    s84::ctcode::dbnf::Call* GetCall();
    s84::ctcode::dbnf::Decimal* GetDecimalLiteral();
    s84::ctcode::dbnf::Number* GetIntegerLiteral();
    s84::ctcode::dbnf::Literal* GetStringLiteral();
    s84::ctcode::dbnf::UnaryOperator* GetUnaryOperator();
    s84::ctcode::dbnf::Name* GetVariable();

private:
    s84::ctcode::dbnf::Allocate* allocate_;
    s84::ctcode::dbnf::Boolean* booleanLiteral_;
    s84::ctcode::dbnf::Byte* byteLiteral_;
    s84::ctcode::dbnf::Call* call_;
    s84::ctcode::dbnf::Decimal* decimalLiteral_;
    s84::ctcode::dbnf::Number* integerLiteral_;
    s84::ctcode::dbnf::Literal* stringLiteral_;
    s84::ctcode::dbnf::UnaryOperator* unary_operator_;
    s84::ctcode::dbnf::Name* variable_;
};

typedef List<RValueTail> RValueTailList;

class RValueTail : public s84::ctcode::dbnf::Node
{
public:
    RValueTail();
    ~RValueTail();

    static s84::ctcode::dbnf::RValueTail* Parse(const char*& index);
    static s84::ctcode::dbnf::RValueTail* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::BinaryOperator* GetBinaryOperator();
    s84::ctcode::dbnf::RValueTail* GetTail();
    s84::ctcode::dbnf::RValueSingle* GetValue();

private:
    s84::ctcode::dbnf::BinaryOperator* binary_operator_;
    s84::ctcode::dbnf::RValueTail* tail_;
    s84::ctcode::dbnf::RValueSingle* value_;
};

typedef List<RValue> RValueList;

class RValue : public s84::ctcode::dbnf::Node
{
public:
    RValue();
    ~RValue();

    static s84::ctcode::dbnf::RValue* Parse(const char*& index);
    static s84::ctcode::dbnf::RValue* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::RValueTail* GetTail();
    s84::ctcode::dbnf::RValueSingle* GetValue();

private:
    s84::ctcode::dbnf::RValueTail* tail_;
    s84::ctcode::dbnf::RValueSingle* value_;
};

typedef List<BinaryOperator> BinaryOperatorList;

class BinaryOperator : public s84::ctcode::dbnf::Node
{
public:
    BinaryOperator();
    ~BinaryOperator();

    static s84::ctcode::dbnf::BinaryOperator* Parse(const char*& index);
    static s84::ctcode::dbnf::BinaryOperator* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::String* GetAddition();
    s84::ctcode::dbnf::String* GetAndOp();
    s84::ctcode::dbnf::String* GetEquality();
    s84::ctcode::dbnf::String* GetGreaterThanEq();
    s84::ctcode::dbnf::String* GetGreaterThan();
    s84::ctcode::dbnf::String* GetLessThanEq();
    s84::ctcode::dbnf::String* GetLessThan();
    s84::ctcode::dbnf::String* GetNotEquality();
    s84::ctcode::dbnf::String* GetOrOp();
    s84::ctcode::dbnf::String* GetSubtraction();

private:
    s84::ctcode::dbnf::String* addition_;
    s84::ctcode::dbnf::String* andOp_;
    s84::ctcode::dbnf::String* equality_;
    s84::ctcode::dbnf::String* greaterThanEq_;
    s84::ctcode::dbnf::String* greaterThan_;
    s84::ctcode::dbnf::String* lessThanEq_;
    s84::ctcode::dbnf::String* lessThan_;
    s84::ctcode::dbnf::String* notEquality_;
    s84::ctcode::dbnf::String* orOp_;
    s84::ctcode::dbnf::String* subtraction_;
};

typedef List<UnaryOperator> UnaryOperatorList;

class UnaryOperator : public s84::ctcode::dbnf::Node
{
public:
    UnaryOperator();
    ~UnaryOperator();

    static s84::ctcode::dbnf::UnaryOperator* Parse(const char*& index);
    static s84::ctcode::dbnf::UnaryOperator* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::String* GetNegation();

private:
    s84::ctcode::dbnf::String* negation_;
};

typedef List<Comment> CommentList;

class Comment : public s84::ctcode::dbnf::Node
{
public:
    Comment();
    ~Comment();

    static s84::ctcode::dbnf::Comment* Parse(const char*& index);
    static s84::ctcode::dbnf::Comment* Parse(s84::ctcode::dbnf::LengthString& index);

    List<s84::ctcode::dbnf::CommentCharacter>* GetContent();

private:
    List<s84::ctcode::dbnf::CommentCharacter>* content_;
};

typedef List<CommentCharacter> CommentCharacterList;

class CommentCharacter : public s84::ctcode::dbnf::Node
{
public:
    CommentCharacter();
    ~CommentCharacter();

    static s84::ctcode::dbnf::CommentCharacter* Parse(const char*& index);
    static s84::ctcode::dbnf::CommentCharacter* Parse(s84::ctcode::dbnf::LengthString& index);
};

typedef List<QualfiedName> QualfiedNameList;

class QualfiedName : public s84::ctcode::dbnf::Node
{
public:
    QualfiedName();
    ~QualfiedName();

    static s84::ctcode::dbnf::QualfiedName* Parse(const char*& index);
    static s84::ctcode::dbnf::QualfiedName* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::Name* GetName();
    s84::ctcode::dbnf::NameTail* GetTail();

private:
    s84::ctcode::dbnf::Name* name_;
    s84::ctcode::dbnf::NameTail* tail_;
};

typedef List<NameTail> NameTailList;

class NameTail : public s84::ctcode::dbnf::Node
{
public:
    NameTail();
    ~NameTail();

    static s84::ctcode::dbnf::NameTail* Parse(const char*& index);
    static s84::ctcode::dbnf::NameTail* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::Name* GetName();
    s84::ctcode::dbnf::NameTail* GetTail();

private:
    s84::ctcode::dbnf::Name* name_;
    s84::ctcode::dbnf::NameTail* tail_;
};

typedef List<Name> NameList;

class Name : public s84::ctcode::dbnf::Node
{
public:
    Name();
    ~Name();

    static s84::ctcode::dbnf::Name* Parse(const char*& index);
    static s84::ctcode::dbnf::Name* Parse(s84::ctcode::dbnf::LengthString& index);
};

typedef List<NameCharacter> NameCharacterList;

class NameCharacter : public s84::ctcode::dbnf::Node
{
public:
    NameCharacter();
    ~NameCharacter();

    static s84::ctcode::dbnf::NameCharacter* Parse(const char*& index);
    static s84::ctcode::dbnf::NameCharacter* Parse(s84::ctcode::dbnf::LengthString& index);
};

typedef List<Boolean> BooleanList;

class Boolean : public s84::ctcode::dbnf::Node
{
public:
    Boolean();
    ~Boolean();

    static s84::ctcode::dbnf::Boolean* Parse(const char*& index);
    static s84::ctcode::dbnf::Boolean* Parse(s84::ctcode::dbnf::LengthString& index);
};

typedef List<Byte> ByteList;

class Byte : public s84::ctcode::dbnf::Node
{
public:
    Byte();
    ~Byte();

    static s84::ctcode::dbnf::Byte* Parse(const char*& index);
    static s84::ctcode::dbnf::Byte* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::ByteDigit* GetHigh();
    s84::ctcode::dbnf::ByteDigit* GetLow();

private:
    s84::ctcode::dbnf::ByteDigit* high_;
    s84::ctcode::dbnf::ByteDigit* low_;
};

typedef List<ByteDigit> ByteDigitList;

class ByteDigit : public s84::ctcode::dbnf::Node
{
public:
    ByteDigit();
    ~ByteDigit();

    static s84::ctcode::dbnf::ByteDigit* Parse(const char*& index);
    static s84::ctcode::dbnf::ByteDigit* Parse(s84::ctcode::dbnf::LengthString& index);
};

typedef List<Negative> NegativeList;

class Negative : public s84::ctcode::dbnf::Node
{
public:
    Negative();
    ~Negative();

    static s84::ctcode::dbnf::Negative* Parse(const char*& index);
    static s84::ctcode::dbnf::Negative* Parse(s84::ctcode::dbnf::LengthString& index);
};

typedef List<Decimal> DecimalList;

class Decimal : public s84::ctcode::dbnf::Node
{
public:
    Decimal();
    ~Decimal();

    static s84::ctcode::dbnf::Decimal* Parse(const char*& index);
    static s84::ctcode::dbnf::Decimal* Parse(s84::ctcode::dbnf::LengthString& index);
};

typedef List<Number> NumberList;

class Number : public s84::ctcode::dbnf::Node
{
public:
    Number();
    ~Number();

    static s84::ctcode::dbnf::Number* Parse(const char*& index);
    static s84::ctcode::dbnf::Number* Parse(s84::ctcode::dbnf::LengthString& index);
};

typedef List<Digit> DigitList;

class Digit : public s84::ctcode::dbnf::Node
{
public:
    Digit();
    ~Digit();

    static s84::ctcode::dbnf::Digit* Parse(const char*& index);
    static s84::ctcode::dbnf::Digit* Parse(s84::ctcode::dbnf::LengthString& index);
};

typedef List<Literal> LiteralList;

class Literal : public s84::ctcode::dbnf::Node
{
public:
    Literal();
    ~Literal();

    static s84::ctcode::dbnf::Literal* Parse(const char*& index);
    static s84::ctcode::dbnf::Literal* Parse(s84::ctcode::dbnf::LengthString& index);
};

typedef List<LiteralCharacter> LiteralCharacterList;

class LiteralCharacter : public s84::ctcode::dbnf::Node
{
public:
    LiteralCharacter();
    ~LiteralCharacter();

    static s84::ctcode::dbnf::LiteralCharacter* Parse(const char*& index);
    static s84::ctcode::dbnf::LiteralCharacter* Parse(s84::ctcode::dbnf::LengthString& index);
};

typedef List<HexDigit> HexDigitList;

class HexDigit : public s84::ctcode::dbnf::Node
{
public:
    HexDigit();
    ~HexDigit();

    static s84::ctcode::dbnf::HexDigit* Parse(const char*& index);
    static s84::ctcode::dbnf::HexDigit* Parse(s84::ctcode::dbnf::LengthString& index);
};

typedef List<Whitespace> WhitespaceList;

class Whitespace : public s84::ctcode::dbnf::Node
{
public:
    Whitespace();
    ~Whitespace();

    static s84::ctcode::dbnf::Whitespace* Parse(const char*& index);
    static s84::ctcode::dbnf::Whitespace* Parse(s84::ctcode::dbnf::LengthString& index);
};

};
};
};

#endif
