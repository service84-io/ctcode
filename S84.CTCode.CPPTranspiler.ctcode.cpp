#include "S84.CTCode.CPPTranspiler.ctcode.hpp"

#include "S84.CTCode.dbnf.hpp"

namespace s84
{
namespace ctcode
{
namespace cpptranspiler
{
namespace ctcode
{
    void CPPTranspilerCTCodeLogic::SetSavedUnmanagedTypes(std::vector<std::string> value)
    {
        saved_unmanaged_types = value;
    }

    bool CPPTranspilerCTCodeLogic::IsUnmanagedType(std::string type_name)
    {
        int index = 0;
        while (index < Size(saved_unmanaged_types))
        {
            if (type_name == Element(saved_unmanaged_types, index))
            {
                return true;
            }

            index = index + 1;
        }

        return false;
    }

    void CPPTranspilerCTCodeLogic::GenerateHeader(OmniPointer<s84::ctcode::dbnf::CTCodeFile> ctcode_file, OmniPointer<OutputStream> header, std::vector<std::string> base_name_tokens)
    {
        std::string guard_name = GenerateGuardName(base_name_tokens);
        header->WriteLine(Concat("#ifndef ", guard_name));
        header->WriteLine(Concat("#define ", guard_name));
        header->WriteLine("");
        OmniPointer<s84::ctcode::dbnf::ExternalDefinitionList> exdef_list;
        exdef_list = ctcode_file->GetDeclarations();
        std::vector<s84::ctcode::dbnf::ExternalDefinition*> exdefs;
        exdefs = exdef_list->GetVector();
        int index = 0;
        while (index < Size(exdefs))
        {
            s84::ctcode::dbnf::ExternalDefinition* exdef;
            exdef = Element(exdefs, index);
            OmniPointer<s84::ctcode::dbnf::QualfiedName> exdef_name;
            exdef_name = exdef->GetExdef();
            header->WriteLine(Concat("#include \"", Concat(GetExdefHeaderString(exdef_name), "\"")));
            index = index + 1;
        }

        header->WriteLine("");
        header->WriteLine("#include <cstring>");
        header->WriteLine("#include <list>");
        header->WriteLine("#include <memory>");
        header->WriteLine("#include <string>");
        header->WriteLine("#include <vector>");
        header->WriteLine("");
        index = 0;
        while (index < Size(base_name_tokens))
        {
            std::string base_name_token;
            base_name_token = Element(base_name_tokens, index);
            header->WriteLine(Concat("namespace ", ToLower(base_name_token)));
            header->WriteLine("{");
            index = index + 1;
        }

        header->WriteLine("namespace ctcode");
        header->WriteLine("{");
        WriteForwardDeclaration(ctcode_file, header);
        WriteClassDeclarations(ctcode_file, header);
        index = 0;
        while (index < Size(base_name_tokens))
        {
            header->WriteLine("};");
            index = index + 1;
        }

        header->WriteLine("};");
        header->WriteLine("");
        header->WriteLine("#endif");
    }

    void CPPTranspilerCTCodeLogic::WriteForwardDeclaration(OmniPointer<s84::ctcode::dbnf::CTCodeFile> ctcode_file, OmniPointer<OutputStream> header)
    {
        OmniPointer<s84::ctcode::dbnf::DefinitionList> definition_list = ctcode_file->GetDefinitions();
        std::vector<s84::ctcode::dbnf::Definition*> definitions = definition_list->GetVector();
        int index = 0;
        while (index < Size(definitions))
        {
            s84::ctcode::dbnf::Definition* definition;
            definition = Element(definitions, index);
            OmniPointer<s84::ctcode::dbnf::InterfaceDef> interface_definition = definition->GetInterfaceDef();
            s84::ctcode::dbnf::ClassDef* class_definition = definition->GetClassDef();
            if (interface_definition)
            {
                header->WriteLine(Concat("class ", Concat(GenerateClassName(interface_definition->GetName()), ";")));
            }

            if (class_definition)
            {
                header->WriteLine(Concat("class ", Concat(GenerateClassName(class_definition->GetName()), ";")));
            }

            index = index + 1;
        }
    }

    void CPPTranspilerCTCodeLogic::WriteClassDeclarations(OmniPointer<s84::ctcode::dbnf::CTCodeFile> ctcode_file, OmniPointer<OutputStream> header)
    {
        OmniPointer<s84::ctcode::dbnf::DefinitionList> definition_list = ctcode_file->GetDefinitions();
        std::vector<s84::ctcode::dbnf::Definition*> definitions = definition_list->GetVector();
        header->WriteLine("");
        header->WriteLine("template<typename T>");
        header->WriteLine("class OmniPointer");
        header->WriteLine("{");
        header->WriteLine("public:");
        header->WriteLine("    OmniPointer() { }");
        header->WriteLine("    OmniPointer(T* value) { value_raw = value; }");
        header->WriteLine("    OmniPointer(std::shared_ptr<T> value) { value_shared = value; }");
        header->WriteLine("");
        header->WriteLine("    operator bool()");
        header->WriteLine("    {");
        header->WriteLine("        if (value_raw) return true;");
        header->WriteLine("        return value_shared.get() != NULL;");
        header->WriteLine("    }");
        header->WriteLine("    T& operator*()");
        header->WriteLine("    {");
        header->WriteLine("        if (value_raw) return *value_raw;");
        header->WriteLine("        return *value_shared;");
        header->WriteLine("    }");
        header->WriteLine("    T* operator->()");
        header->WriteLine("    {");
        header->WriteLine("        if (value_raw) return value_raw;");
        header->WriteLine("        return value_shared.get();");
        header->WriteLine("    }");
        header->WriteLine("");
        header->WriteLine("private:");
        header->WriteLine("    T* value_raw;");
        header->WriteLine("    std::shared_ptr<T> value_shared;");
        header->WriteLine("};");
        header->WriteLine("");
        header->WriteLine("template<typename T>");
        header->WriteLine("inline int Size(std::vector<T> input) { return input.size(); };");
        header->WriteLine("template<typename T>");
        header->WriteLine("inline T Element(std::vector<T> input, int element) { return input.at(element); };");
        header->WriteLine("template<typename T>");
        header->WriteLine("inline std::vector<T> Append(std::vector<T> input, T element) { input.push_back(element); return input; };");
        header->WriteLine("inline int Length(std::string input) { return (int)input.length(); };");
        header->WriteLine("inline std::string At(std::string input, int index) { return input.substr(index, 1); };");
        header->WriteLine("inline std::string Concat(std::string left, std::string right) { return left + right; };");
        int index;
        index = 0;
        while (index < Size(definitions))
        {
            s84::ctcode::dbnf::Definition* definition;
            definition = Element(definitions, index);
            if (definition->GetInterfaceDef())
            {
                WriteInterfaceDeclaration(definition->GetInterfaceDef(), header);
            }

            if (definition->GetClassDef())
            {
                WriteClassDeclaration(definition->GetClassDef(), header);
            }

            index = index + 1;
        }
    }

    void CPPTranspilerCTCodeLogic::WriteInterfaceDeclaration(OmniPointer<s84::ctcode::dbnf::InterfaceDef> interface_definition, OmniPointer<OutputStream> header)
    {
        std::string class_name = "";
        class_name = GenerateClassName(interface_definition->GetName());
        header->WriteLine("");
        header->WriteLine(Concat("class ", class_name));
        header->WriteLine("{");
        header->WriteLine("public:");
        header->WriteLine(Concat("    inline ", Concat(class_name, "() {};")));
        header->WriteLine(Concat("    inline ~", Concat(class_name, "() {};")));
        OmniPointer<s84::ctcode::dbnf::ContentDeclarationList> declaration_list;
        declaration_list = interface_definition->GetDeclarations();
        std::vector<s84::ctcode::dbnf::ContentDeclaration*> declarations;
        declarations = declaration_list->GetVector();
        int index;
        index = 0;
        if (Size(declarations) > 0)
        {
            header->WriteLine("");
            while (index < Size(declarations))
            {
                s84::ctcode::dbnf::ContentDeclaration* declaration;
                declaration = Element(declarations, index);
                header->WriteLine(Concat("    virtual ", Concat(GetType(declaration->GetType()), Concat(" ", Concat(GenerateCallName(declaration->GetName()), Concat("(", Concat(GenerateParameterList(declaration->GetParameters()), ") = 0;")))))));
                index = index + 1;
            }
        }

        header->WriteLine("};");
    }

    void CPPTranspilerCTCodeLogic::WriteClassDeclaration(s84::ctcode::dbnf::ClassDef* class_definition, OmniPointer<OutputStream> header)
    {
        std::string class_name;
        class_name = GenerateClassName(class_definition->GetName());
        header->WriteLine("");
        header->WriteLine(Concat("class ", class_name));
        header->WriteLine("{");
        header->WriteLine("public:");
        header->WriteLine(Concat("    inline ", Concat(class_name, "() {};")));
        header->WriteLine(Concat("    inline ~", Concat(class_name, "() {};")));
        OmniPointer<s84::ctcode::dbnf::ContentDefinitionList> definition_list;
        definition_list = class_definition->GetDefinitions();
        std::vector<s84::ctcode::dbnf::ContentDefinition*> definitions;
        definitions = definition_list->GetVector();
        std::vector<s84::ctcode::dbnf::ContentDefinition*> function_definitions;
        std::vector<s84::ctcode::dbnf::ContentDefinition*> member_definitions;
        int index;
        index = 0;
        while (index < Size(definitions))
        {
            s84::ctcode::dbnf::ContentDefinition* definition;
            definition = Element(definitions, index);
            if (definition->GetFunctionBody())
            {
                function_definitions = Append(function_definitions, definition);
            }
            else
            {
                member_definitions = Append(member_definitions, definition);
            }

            index = index + 1;
        }

        if (Size(function_definitions) > 0)
        {
            header->WriteLine("");
            index = 0;
            while (index < Size(function_definitions))
            {
                s84::ctcode::dbnf::ContentDefinition* definition;
                definition = Element(function_definitions, index);
                header->WriteLine(Concat("    ", Concat(GetType(definition->GetType()), Concat(" ", Concat(GenerateCallName(definition->GetName()), Concat("(", Concat(GenerateParameterList(definition->GetParameters()), ");")))))));
                index = index + 1;
            }
        }

        if (Size(member_definitions) > 0)
        {
            header->WriteLine("");
            header->WriteLine("private:");
            index = 0;
            while (index < Size(member_definitions))
            {
                s84::ctcode::dbnf::ContentDefinition* definition;
                definition = Element(member_definitions, index);
                header->WriteLine(Concat("    ", Concat(GetType(definition->GetType()), Concat(" ", Concat(GenerateVariableName(definition->GetName()), ";")))));
                index = index + 1;
            }
        }

        header->WriteLine("};");
    }

    void CPPTranspilerCTCodeLogic::GenerateImplementation(OmniPointer<s84::ctcode::dbnf::CTCodeFile> ctcode_file, OmniPointer<OutputStream> implementation, std::string base_name, std::vector<std::string> base_name_tokens)
    {
        implementation->WriteLine(Concat("#include \"", Concat(base_name, ".hpp\"")));
        implementation->WriteLine("");
        OmniPointer<s84::ctcode::dbnf::ExternalDefinitionList> exdef_list;
        exdef_list = ctcode_file->GetDeclarations();
        std::vector<s84::ctcode::dbnf::ExternalDefinition*> exdefs;
        exdefs = exdef_list->GetVector();
        int index;
        index = 0;
        while (index < Size(exdefs))
        {
            s84::ctcode::dbnf::ExternalDefinition* exdef;
            exdef = Element(exdefs, index);
            OmniPointer<s84::ctcode::dbnf::QualfiedName> exdef_name;
            exdef_name = exdef->GetExdef();
            implementation->WriteLine(Concat("#include \"", Concat(GetExdefHeaderString(exdef_name), "\"")));
            index = index + 1;
        }

        implementation->WriteLine("");
        index = 0;
        while (index < Size(base_name_tokens))
        {
            std::string base_name_token;
            base_name_token = Element(base_name_tokens, index);
            implementation->WriteLine(Concat("namespace ", ToLower(base_name_token)));
            implementation->WriteLine("{");
            index = index + 1;
        }

        implementation->WriteLine("namespace ctcode");
        implementation->WriteLine("{");
        WriteFunctionDefinitions(ctcode_file, implementation);
        index = 0;
        while (index < Size(base_name_tokens))
        {
            implementation->WriteLine("};");
            index = index + 1;
        }

        implementation->WriteLine("};");
    }

    void CPPTranspilerCTCodeLogic::WriteFunctionDefinitions(OmniPointer<s84::ctcode::dbnf::CTCodeFile> ctcode_file, OmniPointer<OutputStream> implementation)
    {
        OmniPointer<s84::ctcode::dbnf::DefinitionList> definition_list;
        definition_list = ctcode_file->GetDefinitions();
        std::vector<s84::ctcode::dbnf::Definition*> definitions;
        definitions = definition_list->GetVector();
        std::vector<s84::ctcode::dbnf::ClassDef*> class_definitions;
        int index;
        index = 0;
        while (index < Size(definitions))
        {
            s84::ctcode::dbnf::Definition* definition;
            definition = Element(definitions, index);
            s84::ctcode::dbnf::ClassDef* class_definition;
            class_definition = definition->GetClassDef();
            if (class_definition)
            {
                class_definitions = Append(class_definitions, class_definition);
            }

            index = index + 1;
        }

        index = 0;
        while (index < Size(class_definitions))
        {
            s84::ctcode::dbnf::ClassDef* class_definition;
            class_definition = Element(class_definitions, index);
            WriteClassDefinition(class_definition, implementation);
            index = index + 1;
        }
    }

    void CPPTranspilerCTCodeLogic::WriteClassDefinition(s84::ctcode::dbnf::ClassDef* class_definition, OmniPointer<OutputStream> implementation)
    {
        std::string class_name;
        class_name = GenerateClassName(class_definition->GetName());
        OmniPointer<s84::ctcode::dbnf::ContentDefinitionList> definition_list;
        definition_list = class_definition->GetDefinitions();
        std::vector<s84::ctcode::dbnf::ContentDefinition*> definitions;
        definitions = definition_list->GetVector();
        std::vector<s84::ctcode::dbnf::ContentDefinition*> function_definitions;
        int index;
        index = 0;
        while (index < Size(definitions))
        {
            s84::ctcode::dbnf::ContentDefinition* definition;
            definition = Element(definitions, index);
            if (definition->GetFunctionBody())
            {
                function_definitions = Append(function_definitions, definition);
            }

            index = index + 1;
        }

        if (Size(function_definitions) > 0)
        {
            index = 0;
            while (index < Size(function_definitions))
            {
                s84::ctcode::dbnf::ContentDefinition* definition;
                definition = Element(function_definitions, index);
                implementation->WriteLine(Concat("    ", Concat(GetType(definition->GetType()), Concat(" ", Concat(class_name, Concat("::", Concat(GenerateCallName(definition->GetName()), Concat("(", Concat(GenerateParameterList(definition->GetParameters()), ")")))))))));
                WriteCodeBlock(1, implementation, definition->GetFunctionBody(), true);
                index = index + 1;
            }
        }
    }

    void CPPTranspilerCTCodeLogic::WriteInstruction(int indent, OmniPointer<OutputStream> implementation, s84::ctcode::dbnf::Instruction* instruction, bool add_newline_after_code_block)
    {
        if (instruction->GetCodeBlock())
        {
            WriteCodeBlock(indent, implementation, instruction->GetCodeBlock(), add_newline_after_code_block);
        }

        if (instruction->GetRtn())
        {
            WriteRtn(indent, implementation, instruction->GetRtn());
        }

        if (instruction->GetDeclaration())
        {
            WriteDeclaration(indent, implementation, instruction->GetDeclaration());
        }

        if (instruction->GetAssignment())
        {
            WriteAssignment(indent, implementation, instruction->GetAssignment());
        }

        if (instruction->GetCall())
        {
            WriteCall(indent, implementation, instruction->GetCall());
        }

        if (instruction->GetConditional())
        {
            WriteConditional(indent, implementation, instruction->GetConditional(), add_newline_after_code_block);
        }

        if (instruction->GetLoop())
        {
            WriteLoop(indent, implementation, instruction->GetLoop(), add_newline_after_code_block);
        }
    }

    void CPPTranspilerCTCodeLogic::WriteCodeBlock(int indent, OmniPointer<OutputStream> implementation, OmniPointer<s84::ctcode::dbnf::CodeBlock> code_block, bool add_newline_after_code_block)
    {
        implementation->WriteLine(Concat(Indentation(indent), "{"));
        OmniPointer<s84::ctcode::dbnf::InstructionList> instruction_list;
        instruction_list = code_block->GetInstructions();
        std::vector<s84::ctcode::dbnf::Instruction*> instructions;
        instructions = instruction_list->GetVector();
        int index;
        index = 0;
        int last;
        last = Size(instructions) - 1;
        while (index < Size(instructions))
        {
            WriteInstruction(indent + 1, implementation, Element(instructions, index), index != last);
            index = index + 1;
        }

        implementation->WriteLine(Concat(Indentation(indent), "}"));
        if (add_newline_after_code_block)
        {
            implementation->WriteLine("");
        }
    }

    void CPPTranspilerCTCodeLogic::WriteConditional(int indent, OmniPointer<OutputStream> implementation, OmniPointer<s84::ctcode::dbnf::Conditional> conditional, bool add_newline_after_code_block)
    {
        implementation->WriteLine(Concat(Indentation(indent), Concat("if (", Concat(GetRValueString(conditional->GetRvalue()), ")"))));
        if (conditional->GetElseTail())
        {
            OmniPointer<s84::ctcode::dbnf::ElseTail> else_tail;
            else_tail = conditional->GetElseTail();
            WriteCodeBlock(indent, implementation, conditional->GetCodeBlock(), false);
            implementation->WriteLine(Concat(Indentation(indent), "else"));
            WriteCodeBlock(indent, implementation, else_tail->GetCodeBlock(), add_newline_after_code_block);
        }
        else
        {
            WriteCodeBlock(indent, implementation, conditional->GetCodeBlock(), add_newline_after_code_block);
        }
    }

    void CPPTranspilerCTCodeLogic::WriteLoop(int indent, OmniPointer<OutputStream> implementation, OmniPointer<s84::ctcode::dbnf::Loop> loop, bool add_newline_after_code_block)
    {
        implementation->WriteLine(Concat(Indentation(indent), Concat("while (", Concat(GetRValueString(loop->GetRvalue()), ")"))));
        WriteCodeBlock(indent, implementation, loop->GetCodeBlock(), add_newline_after_code_block);
    }

    void CPPTranspilerCTCodeLogic::WriteRtn(int indent, OmniPointer<OutputStream> implementation, OmniPointer<s84::ctcode::dbnf::Return> rtn)
    {
        implementation->WriteLine(Concat(Indentation(indent), Concat("return ", Concat(GetRValueString(rtn->GetRvalue()), ";"))));
    }

    void CPPTranspilerCTCodeLogic::WriteDeclaration(int indent, OmniPointer<OutputStream> implementation, OmniPointer<s84::ctcode::dbnf::Declaration> declaration)
    {
        std::string assignment_suffix;
        assignment_suffix = "";
        if (declaration->GetAssignment())
        {
            OmniPointer<s84::ctcode::dbnf::DeclarationAssign> assignment;
            assignment = declaration->GetAssignment();
            assignment_suffix = Concat(" = ", GetRValueString(assignment->GetRvalue()));
        }

        implementation->WriteLine(Concat(Indentation(indent), Concat(GetVariableDefinition(declaration->GetType(), declaration->GetName()), Concat(assignment_suffix, ";"))));
    }

    void CPPTranspilerCTCodeLogic::WriteAssignment(int indent, OmniPointer<OutputStream> implementation, OmniPointer<s84::ctcode::dbnf::Assignment> assignment)
    {
        implementation->WriteLine(Concat(Indentation(indent), Concat(GenerateVariableName(assignment->GetLvalue()), Concat(" = ", Concat(GetRValueString(assignment->GetRvalue()), ";")))));
    }

    void CPPTranspilerCTCodeLogic::WriteCall(int indent, OmniPointer<OutputStream> implementation, OmniPointer<s84::ctcode::dbnf::Call> call)
    {
        implementation->WriteLine(Concat(Indentation(indent), Concat(GetCallString(call), ";")));
    }

    std::string CPPTranspilerCTCodeLogic::GetExdefHeaderString(OmniPointer<s84::ctcode::dbnf::QualfiedName> exdef_name)
    {
        return Concat(exdef_name->UnParse(), ".hpp");
    }

    std::vector<std::string> CPPTranspilerCTCodeLogic::GetUnmanagedTypes(std::vector<s84::ctcode::dbnf::UnmanagedType*> unmanaged_types)
    {
        std::vector<std::string> unmanaged_type_strings;
        int index;
        index = 0;
        while (index < Size(unmanaged_types))
        {
            s84::ctcode::dbnf::UnmanagedType* unmanaged_type = Element(unmanaged_types, index);
            unmanaged_type_strings = Append(unmanaged_type_strings, GetRawDefinedType(unmanaged_type->GetUnmanagedType()));
            index = index + 1;
        }

        return unmanaged_type_strings;
    }

    std::string CPPTranspilerCTCodeLogic::Indentation(int indent)
    {
        std::string result;
        result = "";
        while (indent > 0)
        {
            indent = indent - 1;
            result = Concat(result, "    ");
        }

        return result;
    }

    std::string CPPTranspilerCTCodeLogic::GetRValueSingleString(OmniPointer<s84::ctcode::dbnf::RValueSingle> r_value_single)
    {
        return Concat(GetRValueSingleUnaryString(r_value_single), GetRValueSingleCoreString(r_value_single));
    }

    std::string CPPTranspilerCTCodeLogic::GetRValueSingleUnaryString(OmniPointer<s84::ctcode::dbnf::RValueSingle> r_value_single)
    {
        if (r_value_single->GetUnaryOperator())
        {
            OmniPointer<s84::ctcode::dbnf::UnaryOperator> unary_operator;
            unary_operator = r_value_single->GetUnaryOperator();
            if (unary_operator->GetNegation())
            {
                return "!";
            }

            return "/*WARNING UnaryOperator FALL THROUGH*/";
        }
        else
        {
            return "";
        }
    }

    std::string CPPTranspilerCTCodeLogic::GetCallString(OmniPointer<s84::ctcode::dbnf::Call> call)
    {
        std::string result;
        result = "";
        if (call->GetVariable())
        {
            result = Concat(result, Concat(GenerateVariableName(call->GetVariable()), "->"));
        }

        result = Concat(result, Concat(GenerateCallName(call->GetFunction()), Concat("(", Concat(GenerateCallingParameterList(call->GetParameters()), ")"))));
        return result;
    }

    std::string CPPTranspilerCTCodeLogic::GetRValueSingleCoreString(OmniPointer<s84::ctcode::dbnf::RValueSingle> r_value_single)
    {
        if (r_value_single->GetCall())
        {
            return GetCallString(r_value_single->GetCall());
        }

        if (r_value_single->GetAllocate())
        {
            OmniPointer<s84::ctcode::dbnf::Allocate> allocate = r_value_single->GetAllocate();
            std::string raw_type = GetRawDefinedType(allocate->GetManagedType());
            return Concat("std::shared_ptr<", Concat(raw_type, Concat(">(new ", Concat(raw_type, "())"))));
        }

        if (r_value_single->GetDecimalLiteral())
        {
            return r_value_single->UnParse();
        }

        if (r_value_single->GetIntegerLiteral())
        {
            return r_value_single->UnParse();
        }

        if (r_value_single->GetBooleanLiteral())
        {
            return r_value_single->UnParse();
        }

        if (r_value_single->GetVariable())
        {
            return GenerateVariableName(r_value_single->GetVariable());
        }

        if (r_value_single->GetStringLiteral())
        {
            return r_value_single->UnParse();
        }

        return "/*WARNING RValueSingle FALL THROUGH*/";
    }

    std::string CPPTranspilerCTCodeLogic::GetOperator(OmniPointer<s84::ctcode::dbnf::BinaryOperator> op)
    {
        if (op->GetAddition())
        {
            return "+";
        }

        if (op->GetSubtraction())
        {
            return "-";
        }

        if (op->GetLessThan())
        {
            return "<";
        }

        if (op->GetLessThanEq())
        {
            return "<=";
        }

        if (op->GetEquality())
        {
            return "==";
        }

        if (op->GetNotEquality())
        {
            return "!=";
        }

        if (op->GetGreaterThanEq())
        {
            return ">=";
        }

        if (op->GetGreaterThan())
        {
            return ">";
        }

        if (op->GetOrOp())
        {
            return "||";
        }

        if (op->GetAndOp())
        {
            return "&&";
        }

        return "/*WARNING BinaryOperator FALL THROUGH*/";
    }

    std::string CPPTranspilerCTCodeLogic::GetRValueTail(OmniPointer<s84::ctcode::dbnf::RValueTail> r_value_tail)
    {
        if (r_value_tail)
        {
            OmniPointer<s84::ctcode::dbnf::BinaryOperator> op;
            op = r_value_tail->GetBinaryOperator();
            return Concat(" ", Concat(GetOperator(op), Concat(" ", Concat(GetRValueSingleString(r_value_tail->GetValue()), GetRValueTail(r_value_tail->GetTail())))));
        }

        return "";
    }

    std::string CPPTranspilerCTCodeLogic::GetRValueString(OmniPointer<s84::ctcode::dbnf::RValue> r_value)
    {
        return Concat(GetRValueSingleString(r_value->GetValue()), GetRValueTail(r_value->GetTail()));
    }

    std::string CPPTranspilerCTCodeLogic::GetVariableDefinition(OmniPointer<s84::ctcode::dbnf::ValueType> type, OmniPointer<s84::ctcode::dbnf::Name> name)
    {
        return Concat(GetType(type), Concat(" ", GenerateVariableName(name)));
    }

    std::string CPPTranspilerCTCodeLogic::GetParameterString(OmniPointer<s84::ctcode::dbnf::ParameterListDef> parameter)
    {
        return GetVariableDefinition(parameter->GetType(), parameter->GetName());
    }

    std::string CPPTranspilerCTCodeLogic::GenerateParameterListTail(OmniPointer<s84::ctcode::dbnf::ParameterListDef> parameters)
    {
        if (parameters)
        {
            return Concat(", ", Concat(GetParameterString(parameters), GenerateParameterListTail(parameters->GetParameterTail())));
        }

        return "";
    }

    std::string CPPTranspilerCTCodeLogic::GenerateParameterList(OmniPointer<s84::ctcode::dbnf::ParameterListDef> parameters)
    {
        if (parameters)
        {
            return Concat(GetParameterString(parameters), GenerateParameterListTail(parameters->GetParameterTail()));
        }
        else
        {
            return "";
        }
    }

    std::string CPPTranspilerCTCodeLogic::GenerateCallingParameterList(OmniPointer<s84::ctcode::dbnf::ParameterList> parameters)
    {
        if (parameters)
        {
            return Concat(GetCallingParameterString(parameters), GenerateCallingParameterListTail(parameters->GetParameterTail()));
        }
        else
        {
            return "";
        }
    }

    std::string CPPTranspilerCTCodeLogic::GetCallingParameterString(OmniPointer<s84::ctcode::dbnf::ParameterList> parameter)
    {
        if (parameter)
        {
            return GetRValueString(parameter->GetRvalue());
        }
        else
        {
            return "";
        }
    }

    std::string CPPTranspilerCTCodeLogic::GenerateCallingParameterListTail(OmniPointer<s84::ctcode::dbnf::ParameterList> parameters)
    {
        if (parameters)
        {
            return Concat(", ", Concat(GetCallingParameterString(parameters), GenerateCallingParameterListTail(parameters->GetParameterTail())));
        }

        return "";
    }

    std::string CPPTranspilerCTCodeLogic::GetType(OmniPointer<s84::ctcode::dbnf::ValueType> value_type)
    {
        if (value_type->GetDimensionalType())
        {
            return GetDimensionalType(value_type->GetDimensionalType());
        }

        if (value_type->GetSingletonType())
        {
            return GetSingletonType(value_type->GetSingletonType());
        }

        return "/*WARNING ValueType FALL THROUGH*/";
    }

    std::string CPPTranspilerCTCodeLogic::GetDimensionalType(OmniPointer<s84::ctcode::dbnf::DimensionalType> dimensional_type)
    {
        OmniPointer<s84::ctcode::dbnf::DimensionalNoteList> dimensional_note_list;
        dimensional_note_list = dimensional_type->GetDimensionalNote();
        int dimensional_notes;
        dimensional_notes = Size(dimensional_note_list->GetVector());
        return Concat(GetDimensionalPrefix(dimensional_notes), Concat(GetSingletonType(dimensional_type->GetSingletonType()), GetDimensionalSuffix(dimensional_notes)));
    }

    std::string CPPTranspilerCTCodeLogic::GetDimensionalPrefix(int dimensional_notes)
    {
        std::string dimensional_prefix;
        dimensional_prefix = "";
        while (dimensional_notes > 0)
        {
            dimensional_prefix = Concat(dimensional_prefix, "std::vector<");
            dimensional_notes = dimensional_notes - 1;
        }

        return dimensional_prefix;
    }

    std::string CPPTranspilerCTCodeLogic::GetDimensionalSuffix(int dimensional_notes)
    {
        std::string dimensional_suffix;
        dimensional_suffix = "";
        while (dimensional_notes > 0)
        {
            dimensional_suffix = Concat(dimensional_suffix, ">");
            dimensional_notes = dimensional_notes - 1;
        }

        return dimensional_suffix;
    }

    std::string CPPTranspilerCTCodeLogic::GetSingletonType(OmniPointer<s84::ctcode::dbnf::SingletonType> singleton_type)
    {
        if (singleton_type->GetDefinedType())
        {
            OmniPointer<s84::ctcode::dbnf::DefinedType> defined_type;
            defined_type = singleton_type->GetDefinedType();
            OmniPointer<s84::ctcode::dbnf::QualfiedName> defined_type_name;
            defined_type_name = defined_type->GetName();
            return GetDefinedType(defined_type_name);
        }

        if (singleton_type->GetPrimativeType())
        {
            OmniPointer<s84::ctcode::dbnf::PrimativeType> primative_type;
            primative_type = singleton_type->GetPrimativeType();
            std::string primative_type_string;
            primative_type_string = primative_type->UnParse();
            if (primative_type_string == "int")
            {
                return "int";
            }

            if (primative_type_string == "string")
            {
                return "std::string";
            }

            if (primative_type_string == "bool")
            {
                return "bool";
            }

            if (primative_type_string == "float")
            {
                return "float";
            }

            if (primative_type_string == "void")
            {
                return "void";
            }

            return "/*WARNING PrimativeType FALL THROUGH*/";
        }

        return "/*WARNING SingletonType FALL THROUGH*/";
    }

    std::string CPPTranspilerCTCodeLogic::GetDefinedType(OmniPointer<s84::ctcode::dbnf::QualfiedName> qualified_name)
    {
        std::string raw_type = GetRawDefinedType(qualified_name);
        if (IsUnmanagedType(raw_type))
        {
            return Concat(raw_type, "*");
        }
        else
        {
            return Concat("OmniPointer<", Concat(raw_type, ">"));
        }
    }

    std::string CPPTranspilerCTCodeLogic::GetRawDefinedType(OmniPointer<s84::ctcode::dbnf::QualfiedName> qualified_name)
    {
        OmniPointer<s84::ctcode::dbnf::NameTail> name_tail;
        name_tail = qualified_name->GetTail();
        OmniPointer<s84::ctcode::dbnf::Name> name;
        name = qualified_name->GetName();
        std::string result;
        result = "";
        if (name_tail)
        {
            std::string name_string;
            name_string = name->UnParse();
            std::string lower_name_string;
            lower_name_string = ToLower(name_string);
            std::string name_tail_string;
            name_tail_string = GetRawDefinedTypeTail(name_tail);
            result = Concat(result, lower_name_string);
            result = Concat(result, name_tail_string);
        }
        else
        {
            std::string class_name;
            class_name = GenerateClassName(name);
            result = Concat(result, class_name);
        }

        return result;
    }

    std::string CPPTranspilerCTCodeLogic::GetRawDefinedTypeTail(OmniPointer<s84::ctcode::dbnf::NameTail> name_tail)
    {
        OmniPointer<s84::ctcode::dbnf::NameTail> name_tail_tail;
        name_tail_tail = name_tail->GetTail();
        OmniPointer<s84::ctcode::dbnf::Name> name;
        name = name_tail->GetName();
        std::string result;
        result = "::";
        if (name_tail_tail)
        {
            std::string name_string;
            name_string = name->UnParse();
            std::string lower_name_string;
            lower_name_string = ToLower(name_string);
            std::string name_tail_tail_string;
            name_tail_tail_string = GetRawDefinedTypeTail(name_tail_tail);
            result = Concat(result, lower_name_string);
            result = Concat(result, name_tail_tail_string);
        }
        else
        {
            std::string class_name;
            class_name = GenerateClassName(name);
            result = Concat(result, class_name);
        }

        return result;
    }

    std::string CPPTranspilerCTCodeLogic::GenerateClassName(OmniPointer<s84::ctcode::dbnf::Name> name_node)
    {
        if (name_node)
        {
            std::string name_node_string;
            name_node_string = name_node->UnParse();
            return SnakeCaseToCamelCase(name_node_string);
        }
        else
        {
            return "";
        }
    }

    std::string CPPTranspilerCTCodeLogic::GenerateVariableName(OmniPointer<s84::ctcode::dbnf::Name> name_node)
    {
        if (name_node)
        {
            std::string name_node_string;
            name_node_string = name_node->UnParse();
            return CamelCaseToSnakeCase(name_node_string);
        }
        else
        {
            return "";
        }
    }

    std::string CPPTranspilerCTCodeLogic::GenerateCallName(OmniPointer<s84::ctcode::dbnf::Name> name_node)
    {
        if (name_node)
        {
            std::string name_node_string;
            name_node_string = name_node->UnParse();
            return SnakeCaseToCamelCase(name_node_string);
        }
        else
        {
            return "";
        }
    }

    std::vector<std::string> CPPTranspilerCTCodeLogic::TokenizeBaseName(std::string name)
    {
        std::vector<std::string> base_name_tokens;
        std::string current_token;
        current_token = "";
        int index;
        index = 0;
        while (index < Length(name))
        {
            std::string character;
            character = At(name, index);
            if (character == ".")
            {
                base_name_tokens = Append(base_name_tokens, current_token);
                current_token = "";
            }
            else
            {
                current_token = Concat(current_token, character);
            }

            index = index + 1;
        }

        return base_name_tokens;
    }

    std::string CPPTranspilerCTCodeLogic::GenerateGuardName(std::vector<std::string> base_name_tokens)
    {
        std::string guard_name;
        guard_name = "";
        std::string ctcode_guard;
        ctcode_guard = "CTCODE_H";
        std::string namespace_seperator;
        namespace_seperator = "_";
        int index;
        index = 0;
        while (index < Size(base_name_tokens))
        {
            std::string namespace_token;
            namespace_token = Element(base_name_tokens, index);
            std::string upper_namespace_token;
            upper_namespace_token = ToUpper(namespace_token);
            guard_name = Concat(guard_name, upper_namespace_token);
            guard_name = Concat(guard_name, namespace_seperator);
            index = index + 1;
        }

        guard_name = Concat(guard_name, ctcode_guard);
        return guard_name;
    }

    std::string CPPTranspilerCTCodeLogic::SnakeCaseToCamelCase(std::string snake_case)
    {
        bool capitalize_this_letter;
        capitalize_this_letter = true;
        std::string camel_case;
        camel_case = "";
        int index;
        index = 0;
        while (index < Length(snake_case))
        {
            std::string source_character;
            source_character = At(snake_case, index);
            if (source_character == "_")
            {
                capitalize_this_letter = true;
            }
            else
            {
                if (capitalize_this_letter == true)
                {
                    std::string upper_character;
                    upper_character = CharacterToUpper(source_character);
                    capitalize_this_letter = false;
                    camel_case = Concat(camel_case, upper_character);
                }
                else
                {
                    capitalize_this_letter = false;
                    camel_case = Concat(camel_case, source_character);
                }
            }

            index = index + 1;
        }

        return camel_case;
    }

    std::string CPPTranspilerCTCodeLogic::CamelCaseToSnakeCase(std::string camel_case)
    {
        std::string delimiter;
        delimiter = "_";
        bool in_abbreviation;
        in_abbreviation = true;
        std::string snake_case;
        snake_case = "";
        int index;
        index = 0;
        while (index < Length(camel_case))
        {
            std::string source_character;
            source_character = At(camel_case, index);
            std::string lower_character;
            lower_character = CharacterToLower(source_character);
            if (IsUpper(source_character) || IsDigit(source_character))
            {
                bool is_first_character;
                is_first_character = Length(snake_case) == 0;
                if (!in_abbreviation && !is_first_character)
                {
                    snake_case = Concat(snake_case, delimiter);
                }

                snake_case = Concat(snake_case, lower_character);
                in_abbreviation = true;
            }
            else
            {
                if (source_character == delimiter)
                {
                    snake_case = Concat(snake_case, delimiter);
                    in_abbreviation = true;
                }
                else
                {
                    snake_case = Concat(snake_case, lower_character);
                    in_abbreviation = false;
                }
            }

            index = index + 1;
        }

        return snake_case;
    }

    bool CPPTranspilerCTCodeLogic::IsUpper(std::string character)
    {
        bool result;
        result = false;
        result = result || character == "A";
        result = result || character == "B";
        result = result || character == "C";
        result = result || character == "D";
        result = result || character == "E";
        result = result || character == "F";
        result = result || character == "G";
        result = result || character == "H";
        result = result || character == "I";
        result = result || character == "J";
        result = result || character == "K";
        result = result || character == "L";
        result = result || character == "M";
        result = result || character == "N";
        result = result || character == "O";
        result = result || character == "P";
        result = result || character == "Q";
        result = result || character == "R";
        result = result || character == "S";
        result = result || character == "T";
        result = result || character == "U";
        result = result || character == "V";
        result = result || character == "W";
        result = result || character == "X";
        result = result || character == "Y";
        result = result || character == "Z";
        return result;
    }

    bool CPPTranspilerCTCodeLogic::IsDigit(std::string character)
    {
        bool result;
        result = false;
        result = result || character == "0";
        result = result || character == "1";
        result = result || character == "2";
        result = result || character == "3";
        result = result || character == "4";
        result = result || character == "5";
        result = result || character == "6";
        result = result || character == "7";
        result = result || character == "8";
        result = result || character == "9";
        return result;
    }

    std::string CPPTranspilerCTCodeLogic::ToLower(std::string input)
    {
        int index;
        index = 0;
        std::string result;
        result = "";
        while (index < Length(input))
        {
            std::string character;
            character = At(input, index);
            std::string lower_character;
            lower_character = CharacterToLower(character);
            result = Concat(result, lower_character);
            index = index + 1;
        }

        return result;
    }

    std::string CPPTranspilerCTCodeLogic::CharacterToLower(std::string input)
    {
        if (input == "A")
        {
            return "a";
        }

        if (input == "B")
        {
            return "b";
        }

        if (input == "C")
        {
            return "c";
        }

        if (input == "D")
        {
            return "d";
        }

        if (input == "E")
        {
            return "e";
        }

        if (input == "F")
        {
            return "f";
        }

        if (input == "G")
        {
            return "g";
        }

        if (input == "H")
        {
            return "h";
        }

        if (input == "I")
        {
            return "i";
        }

        if (input == "J")
        {
            return "j";
        }

        if (input == "K")
        {
            return "k";
        }

        if (input == "L")
        {
            return "l";
        }

        if (input == "M")
        {
            return "m";
        }

        if (input == "N")
        {
            return "n";
        }

        if (input == "O")
        {
            return "o";
        }

        if (input == "P")
        {
            return "p";
        }

        if (input == "Q")
        {
            return "q";
        }

        if (input == "R")
        {
            return "r";
        }

        if (input == "S")
        {
            return "s";
        }

        if (input == "T")
        {
            return "t";
        }

        if (input == "U")
        {
            return "u";
        }

        if (input == "V")
        {
            return "v";
        }

        if (input == "W")
        {
            return "w";
        }

        if (input == "X")
        {
            return "x";
        }

        if (input == "Y")
        {
            return "y";
        }

        if (input == "Z")
        {
            return "z";
        }

        return input;
    }

    std::string CPPTranspilerCTCodeLogic::ToUpper(std::string input)
    {
        int index;
        index = 0;
        std::string result;
        result = "";
        while (index < Length(input))
        {
            std::string character;
            character = At(input, index);
            std::string upper_character;
            upper_character = CharacterToUpper(character);
            result = Concat(result, upper_character);
            index = index + 1;
        }

        return result;
    }

    std::string CPPTranspilerCTCodeLogic::CharacterToUpper(std::string input)
    {
        if (input == "a")
        {
            return "A";
        }

        if (input == "b")
        {
            return "B";
        }

        if (input == "c")
        {
            return "C";
        }

        if (input == "d")
        {
            return "D";
        }

        if (input == "e")
        {
            return "E";
        }

        if (input == "f")
        {
            return "F";
        }

        if (input == "g")
        {
            return "G";
        }

        if (input == "h")
        {
            return "H";
        }

        if (input == "i")
        {
            return "I";
        }

        if (input == "j")
        {
            return "J";
        }

        if (input == "k")
        {
            return "K";
        }

        if (input == "l")
        {
            return "L";
        }

        if (input == "m")
        {
            return "M";
        }

        if (input == "n")
        {
            return "N";
        }

        if (input == "o")
        {
            return "O";
        }

        if (input == "p")
        {
            return "P";
        }

        if (input == "q")
        {
            return "Q";
        }

        if (input == "r")
        {
            return "R";
        }

        if (input == "s")
        {
            return "S";
        }

        if (input == "t")
        {
            return "T";
        }

        if (input == "u")
        {
            return "U";
        }

        if (input == "v")
        {
            return "V";
        }

        if (input == "w")
        {
            return "W";
        }

        if (input == "x")
        {
            return "X";
        }

        if (input == "y")
        {
            return "Y";
        }

        if (input == "z")
        {
            return "Z";
        }

        return input;
    }

};
};
};
};
