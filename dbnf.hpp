#ifndef S84_CTCODE_DBNF_H
#define S84_CTCODE_DBNF_H

#include <list>
#include <string>
#include <cstring>

namespace s84
{
namespace ctcode
{
namespace dbnf
{
class Node;
class String;
class CTCodeFile;
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
class ValueType;
class ParameterListDef;
class ParameterList;
class CodeBlock;
class Declaration;
class Assignment;
class Call;
class Instruction;
class RValue;
class Name;
class NameCharacter;
class Number;
class Digit;
class Literal;
class LiteralCharacter;
class HexDigit;
class Whitespace;

struct LengthString
{
    const char* data;
    int length;
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

protected:
    std::list<T*> list_;
};

class String : public s84::ctcode::dbnf::Node
{
public:
    String(s84::ctcode::dbnf::LengthString data);
    ~String();
};

class CTCodeFile : public s84::ctcode::dbnf::Node
{
public:
    CTCodeFile();
    ~CTCodeFile();

    static s84::ctcode::dbnf::CTCodeFile* Parse(const char*& index);
    static s84::ctcode::dbnf::CTCodeFile* Parse(s84::ctcode::dbnf::LengthString& index);

    List<s84::ctcode::dbnf::Definition>* GetDefinitions();

private:
    List<s84::ctcode::dbnf::Definition>* definitions_;
};

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

class InterfaceDef : public s84::ctcode::dbnf::Node
{
public:
    InterfaceDef();
    ~InterfaceDef();

    static s84::ctcode::dbnf::InterfaceDef* Parse(const char*& index);
    static s84::ctcode::dbnf::InterfaceDef* Parse(s84::ctcode::dbnf::LengthString& index);

    List<s84::ctcode::dbnf::ContentDeclaration>* GetDeclarations();
    s84::ctcode::dbnf::Name* GetName();

private:
    List<s84::ctcode::dbnf::ContentDeclaration>* declarations_;
    s84::ctcode::dbnf::Name* name_;
};

class ClassDef : public s84::ctcode::dbnf::Node
{
public:
    ClassDef();
    ~ClassDef();

    static s84::ctcode::dbnf::ClassDef* Parse(const char*& index);
    static s84::ctcode::dbnf::ClassDef* Parse(s84::ctcode::dbnf::LengthString& index);

    List<s84::ctcode::dbnf::ContentDefinition>* GetDefinitions();
    s84::ctcode::dbnf::Name* GetName();

private:
    List<s84::ctcode::dbnf::ContentDefinition>* definitions_;
    s84::ctcode::dbnf::Name* name_;
};

class ContentDeclaration : public s84::ctcode::dbnf::Node
{
public:
    ContentDeclaration();
    ~ContentDeclaration();

    static s84::ctcode::dbnf::ContentDeclaration* Parse(const char*& index);
    static s84::ctcode::dbnf::ContentDeclaration* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::Name* GetName();
    s84::ctcode::dbnf::ParameterListDef* GetParameters();
    s84::ctcode::dbnf::ValueType* GetType();

private:
    s84::ctcode::dbnf::Name* name_;
    s84::ctcode::dbnf::ParameterListDef* parameters_;
    s84::ctcode::dbnf::ValueType* type_;
};

class ContentDefinition : public s84::ctcode::dbnf::Node
{
public:
    ContentDefinition();
    ~ContentDefinition();

    static s84::ctcode::dbnf::ContentDefinition* Parse(const char*& index);
    static s84::ctcode::dbnf::ContentDefinition* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::CodeBlock* GetFunctionBody();
    s84::ctcode::dbnf::Name* GetName();
    s84::ctcode::dbnf::ParameterListDef* GetParameters();
    s84::ctcode::dbnf::ValueType* GetType();

private:
    s84::ctcode::dbnf::CodeBlock* functionBody_;
    s84::ctcode::dbnf::Name* name_;
    s84::ctcode::dbnf::ParameterListDef* parameters_;
    s84::ctcode::dbnf::ValueType* type_;
};

class PrimativeType : public s84::ctcode::dbnf::Node
{
public:
    PrimativeType();
    ~PrimativeType();

    static s84::ctcode::dbnf::PrimativeType* Parse(const char*& index);
    static s84::ctcode::dbnf::PrimativeType* Parse(s84::ctcode::dbnf::LengthString& index);
};

class DefinedType : public s84::ctcode::dbnf::Node
{
public:
    DefinedType();
    ~DefinedType();

    static s84::ctcode::dbnf::DefinedType* Parse(const char*& index);
    static s84::ctcode::dbnf::DefinedType* Parse(s84::ctcode::dbnf::LengthString& index);
};

class SingletonType : public s84::ctcode::dbnf::Node
{
public:
    SingletonType();
    ~SingletonType();

    static s84::ctcode::dbnf::SingletonType* Parse(const char*& index);
    static s84::ctcode::dbnf::SingletonType* Parse(s84::ctcode::dbnf::LengthString& index);
};

class DimensionalNote : public s84::ctcode::dbnf::Node
{
public:
    DimensionalNote();
    ~DimensionalNote();

    static s84::ctcode::dbnf::DimensionalNote* Parse(const char*& index);
    static s84::ctcode::dbnf::DimensionalNote* Parse(s84::ctcode::dbnf::LengthString& index);
};

class DimensionalType : public s84::ctcode::dbnf::Node
{
public:
    DimensionalType();
    ~DimensionalType();

    static s84::ctcode::dbnf::DimensionalType* Parse(const char*& index);
    static s84::ctcode::dbnf::DimensionalType* Parse(s84::ctcode::dbnf::LengthString& index);

    List<s84::ctcode::dbnf::DimensionalNote>* GetType();

private:
    List<s84::ctcode::dbnf::DimensionalNote>* type_;
};

class ValueType : public s84::ctcode::dbnf::Node
{
public:
    ValueType();
    ~ValueType();

    static s84::ctcode::dbnf::ValueType* Parse(const char*& index);
    static s84::ctcode::dbnf::ValueType* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::DimensionalType* GetDimensionalType();
    s84::ctcode::dbnf::SingletonType* GetSingletonType();

private:
    s84::ctcode::dbnf::DimensionalType* dimensionalType_;
    s84::ctcode::dbnf::SingletonType* singletonType_;
};

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

class ParameterList : public s84::ctcode::dbnf::Node
{
public:
    ParameterList();
    ~ParameterList();

    static s84::ctcode::dbnf::ParameterList* Parse(const char*& index);
    static s84::ctcode::dbnf::ParameterList* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::Name* GetName();
    s84::ctcode::dbnf::ParameterList* GetParameterTail();

private:
    s84::ctcode::dbnf::Name* name_;
    s84::ctcode::dbnf::ParameterList* parameterTail_;
};

class CodeBlock : public s84::ctcode::dbnf::Node
{
public:
    CodeBlock();
    ~CodeBlock();

    static s84::ctcode::dbnf::CodeBlock* Parse(const char*& index);
    static s84::ctcode::dbnf::CodeBlock* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::Instruction* GetInstructions();

private:
    s84::ctcode::dbnf::Instruction* instructions_;
};

class Declaration : public s84::ctcode::dbnf::Node
{
public:
    Declaration();
    ~Declaration();

    static s84::ctcode::dbnf::Declaration* Parse(const char*& index);
    static s84::ctcode::dbnf::Declaration* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::Name* GetName();
    s84::ctcode::dbnf::ValueType* GetType();

private:
    s84::ctcode::dbnf::Name* name_;
    s84::ctcode::dbnf::ValueType* type_;
};

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

class Call : public s84::ctcode::dbnf::Node
{
public:
    Call();
    ~Call();

    static s84::ctcode::dbnf::Call* Parse(const char*& index);
    static s84::ctcode::dbnf::Call* Parse(s84::ctcode::dbnf::LengthString& index);

    s84::ctcode::dbnf::ParameterList* GetParameters();

private:
    s84::ctcode::dbnf::ParameterList* parameters_;
};

class Instruction : public s84::ctcode::dbnf::Node
{
public:
    Instruction();
    ~Instruction();

    static s84::ctcode::dbnf::Instruction* Parse(const char*& index);
    static s84::ctcode::dbnf::Instruction* Parse(s84::ctcode::dbnf::LengthString& index);
};

class RValue : public s84::ctcode::dbnf::Node
{
public:
    RValue();
    ~RValue();

    static s84::ctcode::dbnf::RValue* Parse(const char*& index);
    static s84::ctcode::dbnf::RValue* Parse(s84::ctcode::dbnf::LengthString& index);
};

class Name : public s84::ctcode::dbnf::Node
{
public:
    Name();
    ~Name();

    static s84::ctcode::dbnf::Name* Parse(const char*& index);
    static s84::ctcode::dbnf::Name* Parse(s84::ctcode::dbnf::LengthString& index);
};

class NameCharacter : public s84::ctcode::dbnf::Node
{
public:
    NameCharacter();
    ~NameCharacter();

    static s84::ctcode::dbnf::NameCharacter* Parse(const char*& index);
    static s84::ctcode::dbnf::NameCharacter* Parse(s84::ctcode::dbnf::LengthString& index);
};

class Number : public s84::ctcode::dbnf::Node
{
public:
    Number();
    ~Number();

    static s84::ctcode::dbnf::Number* Parse(const char*& index);
    static s84::ctcode::dbnf::Number* Parse(s84::ctcode::dbnf::LengthString& index);
};

class Digit : public s84::ctcode::dbnf::Node
{
public:
    Digit();
    ~Digit();

    static s84::ctcode::dbnf::Digit* Parse(const char*& index);
    static s84::ctcode::dbnf::Digit* Parse(s84::ctcode::dbnf::LengthString& index);
};

class Literal : public s84::ctcode::dbnf::Node
{
public:
    Literal();
    ~Literal();

    static s84::ctcode::dbnf::Literal* Parse(const char*& index);
    static s84::ctcode::dbnf::Literal* Parse(s84::ctcode::dbnf::LengthString& index);
};

class LiteralCharacter : public s84::ctcode::dbnf::Node
{
public:
    LiteralCharacter();
    ~LiteralCharacter();

    static s84::ctcode::dbnf::LiteralCharacter* Parse(const char*& index);
    static s84::ctcode::dbnf::LiteralCharacter* Parse(s84::ctcode::dbnf::LengthString& index);
};

class HexDigit : public s84::ctcode::dbnf::Node
{
public:
    HexDigit();
    ~HexDigit();

    static s84::ctcode::dbnf::HexDigit* Parse(const char*& index);
    static s84::ctcode::dbnf::HexDigit* Parse(s84::ctcode::dbnf::LengthString& index);
};

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
