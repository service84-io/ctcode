#include "S84.CTCode.Transpiler.StandardStructure.ctcode.hpp"

namespace s84 {
namespace ctcode {
namespace transpiler {
namespace standardstructure {
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

StandardStructure::StandardStructure()
{
    this->system = NULL;
    this->c_t_code_file = NULL;
    this->base_name = "";
    /*this->operator_precedent = NO_DEFAULT;*/
    this->logger = NULL;
    this->target_specific_functions = NULL;
}

void StandardStructure::SetTargetSpecificFunctions(OmniPointer<TargetSpecificFunctions> target_specific_functions)
{
    this->target_specific_functions = target_specific_functions;
}

int StandardStructure::Transpile(OmniPointer<s84::ctcode::system::ctcode::System> system, OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file, std::string base_name)
{
    ClearList(this->operator_precedent);
    this->PopulateOperatorPrecedent();
    this->system = system;
    this->c_t_code_file = c_t_code_file;
    this->base_name = base_name;
    this->logger = system->GetLoggerDestination();
    this->target_specific_functions->SetSystem(this->system);
    this->target_specific_functions->SetCTCodeFile(this->c_t_code_file);
    this->target_specific_functions->SetBaseName(this->base_name);
    this->target_specific_functions->SetLogger(this->logger);
    this->ProcessCTCodeFile(c_t_code_file);
    return 0;
}

void StandardStructure::ProcessCTCodeFile(OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file)
{
    this->target_specific_functions->BeginProcessingCTCodeFile();
    this->ProcessExdefs(c_t_code_file);
    this->ProcessUnmanagedTypes(c_t_code_file);
    this->ProcessDefinitions(c_t_code_file);
    this->target_specific_functions->FinishProcessingCTCodeFile();
}

void StandardStructure::ProcessExdefs(OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file)
{
    std::vector<OmniPointer<s84::ctcode::dbnf::ctcode::ExternalDefinition>> exdefs = c_t_code_file->GetDeclarations();
    int exdefs_index = 0;
    while (exdefs_index<Size(exdefs))
    {
        OmniPointer<s84::ctcode::dbnf::ctcode::ExternalDefinition> exdef = Element(exdefs,exdefs_index);
        OmniPointer<s84::ctcode::dbnf::ctcode::QualfiedName> exdef_name = exdef->GetExdef();
        this->target_specific_functions->ProcessExdef(exdef_name->UnParse());
        exdefs_index = exdefs_index+1;
    }
}

void StandardStructure::ProcessUnmanagedTypes(OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file)
{
    std::vector<OmniPointer<s84::ctcode::dbnf::ctcode::UnmanagedType>> unmanaged_types = c_t_code_file->GetUnmanagedTypes();
    int unmanaged_types_index = 0;
    while (unmanaged_types_index<Size(unmanaged_types))
    {
        OmniPointer<s84::ctcode::dbnf::ctcode::UnmanagedType> unmanaged_type = Element(unmanaged_types,unmanaged_types_index);
        this->target_specific_functions->ProcessUnmanagedType(this->GetQualifiedTypeNameInternal(unmanaged_type->GetUnmanagedType()));
        unmanaged_types_index = unmanaged_types_index+1;
    }
}

void StandardStructure::ProcessDefinitions(OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> c_t_code_file)
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

std::vector<OmniPointer<ParameterDeclaration>> StandardStructure::GetParameters(OmniPointer<s84::ctcode::dbnf::ctcode::ParameterListDef> parameter_list_def)
{
    std::vector<OmniPointer<ParameterDeclaration>> result;
    while (parameter_list_def)
    {
        OmniPointer<ParameterDeclaration> parameter = std::shared_ptr<ParameterDeclaration>(new ParameterDeclaration());
        parameter->SetType(this->GetType(parameter_list_def->GetType()));
        parameter->SetName(this->target_specific_functions->GetVariableName(this->NameToString(parameter_list_def->GetName())));
        Append(result,parameter);
        parameter_list_def = parameter_list_def->GetParameterTail();
    }
    return result;
}

void StandardStructure::ProcessInterfaceDefinition(OmniPointer<s84::ctcode::dbnf::ctcode::InterfaceDef> interface_definition)
{
    std::string interface_name = this->target_specific_functions->GetTypeName(this->NameToString(interface_definition->GetName()));
    this->target_specific_functions->BeginProcessingInterface(interface_name);
    std::vector<OmniPointer<s84::ctcode::dbnf::ctcode::ContentDeclaration>> declarations = interface_definition->GetDeclarations();
    int declarations_index = 0;
    while (declarations_index<Size(declarations))
    {
        OmniPointer<s84::ctcode::dbnf::ctcode::ContentDeclaration> declaration = Element(declarations,declarations_index);
        std::string return_type = this->GetType(declaration->GetType());
        std::string function_name = this->target_specific_functions->GetCallName(this->NameToString(declaration->GetName()));
        std::vector<OmniPointer<ParameterDeclaration>> parameters = this->GetParameters(declaration->GetParameters());
        this->target_specific_functions->ProcessInterfaceFunctionDeclaration(return_type,function_name,parameters);
        declarations_index = declarations_index+1;
    }
    this->target_specific_functions->FinishProcessingInterface(interface_name);
}

void StandardStructure::ProcessClassDefinition(OmniPointer<s84::ctcode::dbnf::ctcode::ClassDef> class_definition)
{
    std::string class_name = this->target_specific_functions->GetTypeName(this->NameToString(class_definition->GetName()));
    std::string implementing = std::string("");
    OmniPointer<s84::ctcode::dbnf::ctcode::ImplementationSpec> implementation_spec = class_definition->GetImplementing();
    if (implementation_spec)
    {
        implementing = this->GetQualifiedTypeNameInternal(implementation_spec->GetInterface());
    }
    this->target_specific_functions->BeginProcessingClass(class_name,implementing);
    std::vector<OmniPointer<s84::ctcode::dbnf::ctcode::ContentDefinition>> definitions = class_definition->GetDefinitions();
    int definitions_index = 0;
    while (definitions_index<Size(definitions))
    {
        OmniPointer<s84::ctcode::dbnf::ctcode::ContentDefinition> definition = Element(definitions,definitions_index);
        if (definition->GetFunctionBody())
        {
            std::string return_type = this->GetType(definition->GetType());
            std::string function_name = this->target_specific_functions->GetCallName(this->NameToString(definition->GetName()));
            std::vector<OmniPointer<ParameterDeclaration>> parameters = this->GetParameters(definition->GetParameters());
            this->target_specific_functions->BeginProcessingClassFunctionDefinition(return_type,function_name,parameters);
            this->ProcessCodeBlockInternal(this->target_specific_functions->GetBaseIndentation(),definition->GetFunctionBody());
            this->target_specific_functions->FinishProcessingClassFunctionDefinition(return_type,function_name,parameters);
        }
        else
        {
            std::string member_type = this->GetType(definition->GetType());
            std::string member_name = this->target_specific_functions->GetVariableName(this->NameToString(definition->GetName()));
            this->target_specific_functions->ProcessClassMemberDeclaration(member_type,member_name);
        }
        definitions_index = definitions_index+1;
    }
    this->target_specific_functions->FinishProcessingClass(class_name,implementing);
}

void StandardStructure::ProcessInstructionInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::Instruction> instruction)
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

void StandardStructure::ProcessCodeBlockInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::CodeBlock> code_block)
{
    this->target_specific_functions->BeginProcessCodeBlock(indent);
    std::vector<OmniPointer<s84::ctcode::dbnf::ctcode::Instruction>> instructions = code_block->GetInstructions();
    int instructions_index = 0;
    while (instructions_index<Size(instructions))
    {
        this->ProcessInstructionInternal(indent+1,Element(instructions,instructions_index));
        instructions_index = instructions_index+1;
    }
    this->target_specific_functions->FinishProcessCodeBlock(indent);
}

void StandardStructure::ProcessConditionalInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::Conditional> conditional)
{
    std::string r_value = this->GetRValueInternal(conditional->GetRValue());
    this->target_specific_functions->BeginProcessConditional(indent,r_value);
    this->ProcessCodeBlockInternal(indent,conditional->GetCodeBlock());
    if (conditional->GetElseTail())
    {
        OmniPointer<s84::ctcode::dbnf::ctcode::ElseTail> else_tail = conditional->GetElseTail();
        this->target_specific_functions->ProcessElse(indent);
        this->ProcessCodeBlockInternal(indent,else_tail->GetCodeBlock());
    }
    this->target_specific_functions->FinishProcessConditional(indent,r_value);
}

void StandardStructure::ProcessLoopInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::Loop> loop)
{
    std::string r_value = this->GetRValueInternal(loop->GetRValue());
    this->target_specific_functions->BeginProcessLoop(indent,r_value);
    this->ProcessCodeBlockInternal(indent,loop->GetCodeBlock());
    this->target_specific_functions->FinishProcessLoop(indent,r_value);
}

void StandardStructure::ProcessRtnInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::Return> rtn)
{
    std::string r_value = this->GetRValueInternal(rtn->GetRValue());
    this->target_specific_functions->ProcessRtn(indent,r_value);
}

void StandardStructure::ProcessDeclarationInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::Declaration> declaration)
{
    std::string type = this->GetType(declaration->GetType());
    std::string l_value = this->target_specific_functions->GetVariableName(this->NameToString(declaration->GetName()));
    std::string r_value = std::string("");
    OmniPointer<s84::ctcode::dbnf::ctcode::DeclarationAssign> declaration_assignment = declaration->GetAssignment();
    if (declaration_assignment)
    {
        r_value = this->GetRValueInternal(declaration_assignment->GetRValue());
    }
    this->target_specific_functions->ProcessDeclaration(indent,type,l_value,r_value);
}

void StandardStructure::ProcessAssignmentInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::Assignment> assignment)
{
    this->target_specific_functions->ProcessAssignment(indent,this->GetVariableChainInternal(assignment->GetLValue()),this->GetRValueInternal(assignment->GetRValue()));
}

void StandardStructure::ProcessCallInternal(int indent, OmniPointer<s84::ctcode::dbnf::ctcode::Call> call)
{
    this->target_specific_functions->ProcessCall(indent,this->ConvertCallInternal(call));
}

std::string StandardStructure::ConvertCallInternal(OmniPointer<s84::ctcode::dbnf::ctcode::Call> call)
{
    std::vector<std::string> name_chain;
    std::vector<std::string> parameters;
    if (call->GetVariable())
    {
        Append(name_chain,this->target_specific_functions->GetVariableName(this->NameToString(call->GetVariable())));
    }
    if (call->GetFunction())
    {
        Append(name_chain,this->target_specific_functions->GetCallName(this->NameToString(call->GetFunction())));
    }
    if (call->GetFunctionChain())
    {
        OmniPointer<s84::ctcode::dbnf::ctcode::QualfiedName> function_chain = call->GetFunctionChain();
        OmniPointer<s84::ctcode::dbnf::ctcode::NameTail> name_tail = function_chain->GetTail();
        if (function_chain->GetTail())
        {
            Append(name_chain,this->target_specific_functions->GetVariableName(this->NameToString(function_chain->GetName())));
        }
        else
        {
            Append(name_chain,this->target_specific_functions->GetCallName(this->NameToString(function_chain->GetName())));
        }
        while (name_tail)
        {
            if (name_tail->GetTail())
            {
                Append(name_chain,this->target_specific_functions->GetVariableName(this->NameToString(name_tail->GetName())));
            }
            else
            {
                Append(name_chain,this->target_specific_functions->GetCallName(this->NameToString(name_tail->GetName())));
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
    return this->target_specific_functions->ConvertCall(name_chain,parameters);
}

std::string StandardStructure::GetSingletonType(OmniPointer<s84::ctcode::dbnf::ctcode::SingletonType> singleton_type)
{
    if (singleton_type->GetPrimativeType())
    {
        return this->target_specific_functions->GetPrimativeType(singleton_type->UnParse());
    }
    if (singleton_type->GetDefinedType())
    {
        OmniPointer<s84::ctcode::dbnf::ctcode::DefinedType> defined_type = singleton_type->GetDefinedType();
        return this->GetQualifiedTypeNameInternal(defined_type->GetName());
    }
    return std::string("");
}

std::string StandardStructure::GetRValueSingleBasisInternal(OmniPointer<s84::ctcode::dbnf::ctcode::RValueSingle> r_value_single)
{
    OmniPointer<s84::ctcode::dbnf::ctcode::Call> call = r_value_single->GetCall();
    if (call)
    {
        return this->ConvertCallInternal(call);
    }
    OmniPointer<s84::ctcode::dbnf::ctcode::Allocate> allocate = r_value_single->GetAllocate();
    if (allocate)
    {
        return this->target_specific_functions->ConvertAllocate(this->GetQualifiedTypeNameInternal(allocate->GetManagedType()));
    }
    OmniPointer<s84::ctcode::dbnf::ctcode::Byte> byte_literal = r_value_single->GetByteLiteral();
    if (byte_literal)
    {
        OmniPointer<s84::ctcode::dbnf::ctcode::ByteDigit> high = byte_literal->GetHigh();
        OmniPointer<s84::ctcode::dbnf::ctcode::ByteDigit> low = byte_literal->GetLow();
        return this->target_specific_functions->ConvertByte(high->UnParse(),low->UnParse());
    }
    OmniPointer<s84::ctcode::dbnf::ctcode::Decimal> decimal_literal = r_value_single->GetDecimalLiteral();
    if (decimal_literal)
    {
        return this->target_specific_functions->ConvertDecimal(decimal_literal->UnParse());
    }
    OmniPointer<s84::ctcode::dbnf::ctcode::Number> integer_literal = r_value_single->GetIntegerLiteral();
    if (integer_literal)
    {
        return this->target_specific_functions->ConvertNumber(integer_literal->UnParse());
    }
    OmniPointer<s84::ctcode::dbnf::ctcode::Boolean> boolean_literal = r_value_single->GetBooleanLiteral();
    if (boolean_literal)
    {
        return this->target_specific_functions->ConvertBoolean(boolean_literal->UnParse());
    }
    OmniPointer<s84::ctcode::dbnf::ctcode::QualfiedName> variable = r_value_single->GetVariable();
    if (variable)
    {
        return this->target_specific_functions->ConvertVariable(this->GetVariableChainInternal(variable));
    }
    OmniPointer<s84::ctcode::dbnf::ctcode::Literal> string_literal = r_value_single->GetStringLiteral();
    if (string_literal)
    {
        return this->target_specific_functions->ConvertString(string_literal->UnParse());
    }
    return std::string("");
}

std::string StandardStructure::GetRValueSingleInternal(OmniPointer<s84::ctcode::dbnf::ctcode::RValueSingle> r_value_single)
{
    OmniPointer<s84::ctcode::dbnf::ctcode::UnaryOperator> unary_operator = r_value_single->GetUnaryOperator();
    if (unary_operator)
    {
        return this->target_specific_functions->UnaryOperator(unary_operator->UnParse(),this->GetRValueSingleBasisInternal(r_value_single));
    }
    return this->GetRValueSingleBasisInternal(r_value_single);
}

void StandardStructure::PopulateOperatorPrecedent()
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

bool StandardStructure::OverPrecedent(std::string op, int precedent)
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

std::string StandardStructure::BinaryOperatorPrecedentMerge(std::vector<std::string> values, std::vector<std::string> operators, OmniPointer<IntegerReference> index, int precedent)
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
        r_value_l = this->target_specific_functions->BinaryOperator(op,r_value_l,r_value_r);
    }
    return r_value_l;
}

std::string StandardStructure::GetRValueInternal(OmniPointer<s84::ctcode::dbnf::ctcode::RValue> r_value)
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

std::string StandardStructure::GetQualifiedTypeNameInternal(OmniPointer<s84::ctcode::dbnf::ctcode::QualfiedName> qualified_name)
{
    std::vector<std::string> name_parts;
    Append(name_parts,this->NameToString(qualified_name->GetName()));
    OmniPointer<s84::ctcode::dbnf::ctcode::NameTail> tail = qualified_name->GetTail();
    while (tail)
    {
        Append(name_parts,this->NameToString(tail->GetName()));
        tail = tail->GetTail();
    }
    return this->target_specific_functions->GetQualifiedTypeName(name_parts);
}

std::string StandardStructure::GetVariableChainInternal(OmniPointer<s84::ctcode::dbnf::ctcode::QualfiedName> qualified_name)
{
    std::vector<std::string> name_parts;
    Append(name_parts,this->NameToString(qualified_name->GetName()));
    OmniPointer<s84::ctcode::dbnf::ctcode::NameTail> tail = qualified_name->GetTail();
    while (tail)
    {
        Append(name_parts,this->NameToString(tail->GetName()));
        tail = tail->GetTail();
    }
    return this->target_specific_functions->GetVariableChain(name_parts);
}

std::string StandardStructure::GetType(OmniPointer<s84::ctcode::dbnf::ctcode::ValueType> type)
{
    if (type->GetDimensionalType())
    {
        OmniPointer<s84::ctcode::dbnf::ctcode::DimensionalType> dimensional_type = type->GetDimensionalType();
        OmniPointer<s84::ctcode::dbnf::ctcode::SingletonType> singleton_type = dimensional_type->GetSingletonType();
        return this->target_specific_functions->GetDimensionalType(this->GetSingletonType(singleton_type),Size(dimensional_type->GetDimensionalNote()));
    }
    if (type->GetMapType())
    {
        OmniPointer<s84::ctcode::dbnf::ctcode::MapType> map_type = type->GetMapType();
        OmniPointer<s84::ctcode::dbnf::ctcode::SingletonType> singleton_type = map_type->GetSingletonType();
        return this->target_specific_functions->GetMapType(this->GetSingletonType(singleton_type));
    }
    if (type->GetSingletonType())
    {
        OmniPointer<s84::ctcode::dbnf::ctcode::SingletonType> singleton_type = type->GetSingletonType();
        return this->GetSingletonType(singleton_type);
    }
    return std::string("");
}

std::string StandardStructure::NameToString(OmniPointer<s84::ctcode::dbnf::ctcode::Name> name)
{
    if (name)
    {
        return name->UnParse();
    }
    else
    {
        return std::string("");
    }
}


};
};
};
};
};
