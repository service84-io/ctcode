#include "S84.CTCode.Transpiler.CPPTranspiler.ctcode.hpp"

#include "S84.CTCode.dbnf.ctcode.hpp"
#include "S84.CTCode.System.ctcode.hpp"
#include "S84.CTCode.Transpiler.ctcode.hpp"

namespace s84
{
namespace ctcode
{
namespace transpiler
{
namespace cpptranspiler
{
namespace ctcode
{
    int CPPTranspiler::Transpile(OmniPointer<s84::ctcode::system::ctcode::System> system, OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> ct_code_file, std::string base_name)
    {
        OmniPointer<s84::ctcode::system::ctcode::OutputStream> logger = system->GetLoggerDestination();
        OmniPointer<s84::ctcode::system::ctcode::OutputStream> header = system->OpenFileWriter(Concat(base_name, std::string(".hpp")));
        OmniPointer<s84::ctcode::system::ctcode::OutputStream> implementation = system->OpenFileWriter(Concat(base_name, std::string(".cpp")));
        std::vector<std::string> base_name_tokens = this->TokenizeBaseName(base_name);
        this->SetSavedUnmanagedTypes(this->GetUnmanagedTypes(ct_code_file->GetUnmanagedTypes()));
        this->GenerateHeader(ct_code_file, header, base_name_tokens);
        this->GenerateImplementation(ct_code_file, implementation, base_name, base_name_tokens);
        return 0;
    }

    void CPPTranspiler::SetSavedUnmanagedTypes(std::vector<std::string> value)
    {
        this->saved_unmanaged_types = value;
    }

    bool CPPTranspiler::IsUnmanagedType(std::string type_name)
    {
        int index = 0;
        while (index < Size(this->saved_unmanaged_types))
        {
            if (type_name == Element(this->saved_unmanaged_types, index))
            {
                return true;
            }

            index = index + 1;
        }

        return false;
    }

    void CPPTranspiler::GenerateHeader(OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> ctcode_file, OmniPointer<s84::ctcode::system::ctcode::OutputStream> header, std::vector<std::string> base_name_tokens)
    {
        std::string guard_name = this->GenerateGuardName(base_name_tokens);
        header->WriteLine(Concat(std::string("#ifndef "), guard_name));
        header->WriteLine(Concat(std::string("#define "), guard_name));
        header->WriteLine(std::string(""));
        std::vector<OmniPointer<s84::ctcode::dbnf::ctcode::ExternalDefinition>> exdefs = ctcode_file->GetDeclarations();
        int index = 0;
        while (index < Size(exdefs))
        {
            OmniPointer<s84::ctcode::dbnf::ctcode::ExternalDefinition> exdef;
            exdef = Element(exdefs, index);
            OmniPointer<s84::ctcode::dbnf::ctcode::QualfiedName> exdef_name;
            exdef_name = exdef->GetExdef();
            header->WriteLine(Concat(std::string("#include \""), Concat(this->GetExdefHeaderString(exdef_name), std::string("\""))));
            index = index + 1;
        }

        header->WriteLine(std::string(""));
        header->WriteLine(std::string("#include <cstring>"));
        header->WriteLine(std::string("#include <list>"));
        header->WriteLine(std::string("#include <unordered_map>"));
        header->WriteLine(std::string("#include <memory>"));
        header->WriteLine(std::string("#include <string>"));
        header->WriteLine(std::string("#include <vector>"));
        this->WriteCTCodeCommonFunctions(header);
        header->WriteLine(std::string(""));
        index = 0;
        while (index < Size(base_name_tokens))
        {
            std::string base_name_token;
            base_name_token = Element(base_name_tokens, index);
            header->WriteLine(Concat(std::string("namespace "), this->ToLower(base_name_token)));
            header->WriteLine(std::string("{"));
            index = index + 1;
        }

        header->WriteLine(std::string("namespace ctcode"));
        header->WriteLine(std::string("{"));
        this->WriteForwardDeclaration(ctcode_file, header);
        this->WriteClassDeclarations(ctcode_file, header);
        index = 0;
        while (index < Size(base_name_tokens))
        {
            header->WriteLine(std::string("};"));
            index = index + 1;
        }

        header->WriteLine(std::string("};"));
        header->WriteLine(std::string(""));
        header->WriteLine(std::string("#endif"));
    }

    void CPPTranspiler::WriteCTCodeCommonFunctions(OmniPointer<s84::ctcode::system::ctcode::OutputStream> header)
    {
        header->WriteLine(std::string(""));
        header->WriteLine(std::string("#ifndef CTCODE_COMMON_FUNCTIONS_VERSION_1"));
        header->WriteLine(std::string("#define CTCODE_COMMON_FUNCTIONS_VERSION_1"));
        header->WriteLine(std::string("template<typename T>"));
        header->WriteLine(std::string("class OmniPointer"));
        header->WriteLine(std::string("{"));
        header->WriteLine(std::string("public:"));
        header->WriteLine(std::string("    OmniPointer() { value_raw = NULL; }"));
        header->WriteLine(std::string("    OmniPointer(T* value) { value_raw = value; }"));
        header->WriteLine(std::string("    template<typename U>"));
        header->WriteLine(std::string("    OmniPointer(U* value) { value_raw = value; }"));
        header->WriteLine(std::string("    OmniPointer(std::shared_ptr<T> value) { value_raw = NULL; value_shared = value; }"));
        header->WriteLine(std::string("    template<typename U>"));
        header->WriteLine(std::string("    OmniPointer(std::shared_ptr<U> value) { value_raw = NULL; value_shared = value; }"));
        header->WriteLine(std::string(""));
        header->WriteLine(std::string("    operator bool()"));
        header->WriteLine(std::string("    {"));
        header->WriteLine(std::string("        if (value_raw) return true;"));
        header->WriteLine(std::string("        return value_shared.get() != NULL;"));
        header->WriteLine(std::string("    }"));
        header->WriteLine(std::string("    T& operator*()"));
        header->WriteLine(std::string("    {"));
        header->WriteLine(std::string("        if (value_raw) return *value_raw;"));
        header->WriteLine(std::string("        return *value_shared;"));
        header->WriteLine(std::string("    }"));
        header->WriteLine(std::string("    T* operator->()"));
        header->WriteLine(std::string("    {"));
        header->WriteLine(std::string("        if (value_raw) return value_raw;"));
        header->WriteLine(std::string("        return value_shared.get();"));
        header->WriteLine(std::string("    }"));
        header->WriteLine(std::string("    T* raw()"));
        header->WriteLine(std::string("    {"));
        header->WriteLine(std::string("        if (value_raw) return value_raw;"));
        header->WriteLine(std::string("        return value_shared.get();"));
        header->WriteLine(std::string("    }"));
        header->WriteLine(std::string(""));
        header->WriteLine(std::string("private:"));
        header->WriteLine(std::string("    T* value_raw;"));
        header->WriteLine(std::string("    std::shared_ptr<T> value_shared;"));
        header->WriteLine(std::string("};"));
        header->WriteLine(std::string(""));
        header->WriteLine(std::string("template<typename T>"));
        header->WriteLine(std::string("inline std::vector<T*> UnwrapOmniList(std::vector<OmniPointer<T>> input) {"));
        header->WriteLine(std::string("	std::vector<T*> result;"));
        header->WriteLine(std::string("	for (typename std::vector<OmniPointer<T>>::iterator index = input.begin();index != input.end();index++) {"));
        header->WriteLine(std::string("		result.push_back(index->raw());"));
        header->WriteLine(std::string("	}"));
        header->WriteLine(std::string("	return result;"));
        header->WriteLine(std::string("};"));
        header->WriteLine(std::string("template<typename T>"));
        header->WriteLine(std::string("inline void ClearList(std::vector<T>& input) { input.clear(); };"));
        header->WriteLine(std::string("template<typename T>"));
        header->WriteLine(std::string("inline int Size(const std::vector<T>& input) { return input.size(); };"));
        header->WriteLine(std::string("template<typename T>"));
        header->WriteLine(std::string("inline T Element(const std::vector<T>& input, int element) { return input.at(element); };"));
        header->WriteLine(std::string("template<typename T>"));
        header->WriteLine(std::string("inline void Append(std::vector<T>& input, T element) { input.push_back(element); };"));
        header->WriteLine(std::string("template<typename T>"));
        header->WriteLine(std::string("inline void ClearMap(std::unordered_map<std::string, T>& input) { input.clear(); };"));
        header->WriteLine(std::string("template<typename T>"));
        header->WriteLine(std::string("inline void SetKV(std::unordered_map<std::string, T>& input, const std::string& key, T element)"));
        header->WriteLine(std::string("{"));
        header->WriteLine(std::string("    input.erase(key);"));
        header->WriteLine(std::string("    input.insert(std::pair<std::string, T>(key, element));"));
        header->WriteLine(std::string("}"));
        header->WriteLine(std::string("template<typename T>"));
        header->WriteLine(std::string("inline std::vector<std::string> Keys(const std::unordered_map<std::string, T>& input)"));
        header->WriteLine(std::string("{"));
        header->WriteLine(std::string("    std::vector<std::string> result;"));
        header->WriteLine(std::string("    for(typename std::unordered_map<std::string, T>::const_iterator index = input.begin();index != input.end();index++) {"));
        header->WriteLine(std::string("        result.push_back(index->first);"));
        header->WriteLine(std::string("    }"));
        header->WriteLine(std::string("    return result;"));
        header->WriteLine(std::string("}"));
        header->WriteLine(std::string("template<typename T>"));
        header->WriteLine(std::string("inline bool HasKV(const std::unordered_map<std::string, T>& input, const std::string& key)"));
        header->WriteLine(std::string("{"));
        header->WriteLine(std::string("    typename std::unordered_map<std::string, T>::const_iterator beginning = input.find(key);"));
        header->WriteLine(std::string("    return beginning != input.end();"));
        header->WriteLine(std::string("}"));
        header->WriteLine(std::string("template<typename T>"));
        header->WriteLine(std::string("inline T GetKV(const std::unordered_map<std::string, T>& input, const std::string& key) { return input.at(key); }"));
        header->WriteLine(std::string("inline int Length(const std::string& input) { return (int)input.length(); };"));
        header->WriteLine(std::string("inline std::string At(const std::string& input, int index) { return input.substr(index, 1); };"));
        header->WriteLine(std::string("inline int IntAt(const std::string& input, int index) { return (input.at(index) + 256) % 256; };"));
        header->WriteLine(std::string("inline std::string Concat(const std::string& left, const std::string& right) { return left + right; };"));
        header->WriteLine(std::string("#endif"));
    }

    void CPPTranspiler::WriteForwardDeclaration(OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> ctcode_file, OmniPointer<s84::ctcode::system::ctcode::OutputStream> header)
    {
        std::vector<OmniPointer<s84::ctcode::dbnf::ctcode::Definition>> definitions = ctcode_file->GetDefinitions();
        int index = 0;
        while (index < Size(definitions))
        {
            OmniPointer<s84::ctcode::dbnf::ctcode::Definition> definition;
            definition = Element(definitions, index);
            OmniPointer<s84::ctcode::dbnf::ctcode::InterfaceDef> interface_definition = definition->GetInterfaceDef();
            OmniPointer<s84::ctcode::dbnf::ctcode::ClassDef> class_definition = definition->GetClassDef();
            if (interface_definition)
            {
                header->WriteLine(Concat(std::string("class "), Concat(this->GenerateClassName(interface_definition->GetName()), std::string(";"))));
            }

            if (class_definition)
            {
                header->WriteLine(Concat(std::string("class "), Concat(this->GenerateClassName(class_definition->GetName()), std::string(";"))));
            }

            index = index + 1;
        }
    }

    void CPPTranspiler::WriteClassDeclarations(OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> ctcode_file, OmniPointer<s84::ctcode::system::ctcode::OutputStream> header)
    {
        std::vector<OmniPointer<s84::ctcode::dbnf::ctcode::Definition>> definitions = ctcode_file->GetDefinitions();
        header->WriteLine(std::string(""));
        int index;
        index = 0;
        while (index < Size(definitions))
        {
            OmniPointer<s84::ctcode::dbnf::ctcode::Definition> definition;
            definition = Element(definitions, index);
            if (definition->GetInterfaceDef())
            {
                this->WriteInterfaceDeclaration(definition->GetInterfaceDef(), header);
            }

            if (definition->GetClassDef())
            {
                this->WriteClassDeclaration(definition->GetClassDef(), header);
            }

            index = index + 1;
        }
    }

    void CPPTranspiler::WriteInterfaceDeclaration(OmniPointer<s84::ctcode::dbnf::ctcode::InterfaceDef> interface_definition, OmniPointer<s84::ctcode::system::ctcode::OutputStream> header)
    {
        std::string class_name = std::string("");
        class_name = this->GenerateClassName(interface_definition->GetName());
        header->WriteLine(std::string(""));
        header->WriteLine(Concat(std::string("class "), class_name));
        header->WriteLine(std::string("{"));
        header->WriteLine(std::string("public:"));
        header->WriteLine(Concat(std::string("    inline "), Concat(class_name, std::string("() {};"))));
        header->WriteLine(Concat(std::string("    inline ~"), Concat(class_name, std::string("() {};"))));
        std::vector<OmniPointer<s84::ctcode::dbnf::ctcode::ContentDeclaration>> declarations = interface_definition->GetDeclarations();
        int index;
        index = 0;
        if (Size(declarations) > 0)
        {
            header->WriteLine(std::string(""));
            while (index < Size(declarations))
            {
                OmniPointer<s84::ctcode::dbnf::ctcode::ContentDeclaration> declaration;
                declaration = Element(declarations, index);
                header->WriteLine(Concat(std::string("    virtual "), Concat(this->GetType(declaration->GetType()), Concat(std::string(" "), Concat(this->GenerateCallName(declaration->GetName()), Concat(std::string("("), Concat(this->GenerateParameterList(declaration->GetParameters()), std::string(") = 0;"))))))));
                index = index + 1;
            }
        }

        header->WriteLine(std::string("};"));
    }

    void CPPTranspiler::WriteClassDeclaration(OmniPointer<s84::ctcode::dbnf::ctcode::ClassDef> class_definition, OmniPointer<s84::ctcode::system::ctcode::OutputStream> header)
    {
        std::string class_name;
        class_name = this->GenerateClassName(class_definition->GetName());
        header->WriteLine(std::string(""));
        header->WriteLine(Concat(std::string("class "), class_name));
        this->WriteImplementationSpec(class_definition->GetImplementing(), header);
        header->WriteLine(std::string("{"));
        header->WriteLine(std::string("public:"));
        header->WriteLine(Concat(std::string("    inline "), Concat(class_name, std::string("() {};"))));
        header->WriteLine(Concat(std::string("    inline ~"), Concat(class_name, std::string("() {};"))));
        std::vector<OmniPointer<s84::ctcode::dbnf::ctcode::ContentDefinition>> definitions = class_definition->GetDefinitions();
        std::vector<OmniPointer<s84::ctcode::dbnf::ctcode::ContentDefinition>> function_definitions;
        std::vector<OmniPointer<s84::ctcode::dbnf::ctcode::ContentDefinition>> member_definitions;
        int index;
        index = 0;
        while (index < Size(definitions))
        {
            OmniPointer<s84::ctcode::dbnf::ctcode::ContentDefinition> definition;
            definition = Element(definitions, index);
            if (definition->GetFunctionBody())
            {
                Append(function_definitions, definition);
            }
            else
            {
                Append(member_definitions, definition);
            }

            index = index + 1;
        }

        if (Size(function_definitions) > 0)
        {
            header->WriteLine(std::string(""));
            index = 0;
            while (index < Size(function_definitions))
            {
                OmniPointer<s84::ctcode::dbnf::ctcode::ContentDefinition> definition;
                definition = Element(function_definitions, index);
                header->WriteLine(Concat(std::string("    "), Concat(this->GetType(definition->GetType()), Concat(std::string(" "), Concat(this->GenerateCallName(definition->GetName()), Concat(std::string("("), Concat(this->GenerateParameterList(definition->GetParameters()), std::string(");"))))))));
                index = index + 1;
            }
        }

        if (Size(member_definitions) > 0)
        {
            header->WriteLine(std::string(""));
            header->WriteLine(std::string("private:"));
            index = 0;
            while (index < Size(member_definitions))
            {
                OmniPointer<s84::ctcode::dbnf::ctcode::ContentDefinition> definition;
                definition = Element(member_definitions, index);
                header->WriteLine(Concat(std::string("    "), Concat(this->GetType(definition->GetType()), Concat(std::string(" "), Concat(this->GenerateVariableName(definition->GetName()), std::string(";"))))));
                index = index + 1;
            }
        }

        header->WriteLine(std::string("};"));
    }

    void CPPTranspiler::WriteImplementationSpec(OmniPointer<s84::ctcode::dbnf::ctcode::ImplementationSpec> implementation_spec, OmniPointer<s84::ctcode::system::ctcode::OutputStream> header)
    {
        if (implementation_spec)
        {
            OmniPointer<s84::ctcode::dbnf::ctcode::QualfiedName> qualified_name = implementation_spec->GetInterface();
            header->WriteLine(Concat(std::string(": public "), this->GetRawDefinedType(qualified_name)));
        }
    }

    void CPPTranspiler::GenerateImplementation(OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> ctcode_file, OmniPointer<s84::ctcode::system::ctcode::OutputStream> implementation, std::string base_name, std::vector<std::string> base_name_tokens)
    {
        implementation->WriteLine(Concat(std::string("#include \""), Concat(base_name, std::string(".hpp\""))));
        implementation->WriteLine(std::string(""));
        std::vector<OmniPointer<s84::ctcode::dbnf::ctcode::ExternalDefinition>> exdefs = ctcode_file->GetDeclarations();
        int index;
        index = 0;
        while (index < Size(exdefs))
        {
            OmniPointer<s84::ctcode::dbnf::ctcode::ExternalDefinition> exdef;
            exdef = Element(exdefs, index);
            OmniPointer<s84::ctcode::dbnf::ctcode::QualfiedName> exdef_name;
            exdef_name = exdef->GetExdef();
            implementation->WriteLine(Concat(std::string("#include \""), Concat(this->GetExdefHeaderString(exdef_name), std::string("\""))));
            index = index + 1;
        }

        implementation->WriteLine(std::string(""));
        index = 0;
        while (index < Size(base_name_tokens))
        {
            std::string base_name_token;
            base_name_token = Element(base_name_tokens, index);
            implementation->WriteLine(Concat(std::string("namespace "), this->ToLower(base_name_token)));
            implementation->WriteLine(std::string("{"));
            index = index + 1;
        }

        implementation->WriteLine(std::string("namespace ctcode"));
        implementation->WriteLine(std::string("{"));
        this->WriteFunctionDefinitions(ctcode_file, implementation);
        index = 0;
        while (index < Size(base_name_tokens))
        {
            implementation->WriteLine(std::string("};"));
            index = index + 1;
        }

        implementation->WriteLine(std::string("};"));
    }

    void CPPTranspiler::WriteFunctionDefinitions(OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> ctcode_file, OmniPointer<s84::ctcode::system::ctcode::OutputStream> implementation)
    {
        std::vector<OmniPointer<s84::ctcode::dbnf::ctcode::Definition>> definitions = ctcode_file->GetDefinitions();
        std::vector<OmniPointer<s84::ctcode::dbnf::ctcode::ClassDef>> class_definitions;
        int index;
        index = 0;
        while (index < Size(definitions))
        {
            OmniPointer<s84::ctcode::dbnf::ctcode::Definition> definition;
            definition = Element(definitions, index);
            OmniPointer<s84::ctcode::dbnf::ctcode::ClassDef> class_definition;
            class_definition = definition->GetClassDef();
            if (class_definition)
            {
                Append(class_definitions, class_definition);
            }

            index = index + 1;
        }

        index = 0;
        while (index < Size(class_definitions))
        {
            OmniPointer<s84::ctcode::dbnf::ctcode::ClassDef> class_definition;
            class_definition = Element(class_definitions, index);
            this->WriteClassDefinition(class_definition, implementation);
            index = index + 1;
        }
    }

    void CPPTranspiler::WriteClassDefinition(OmniPointer<s84::ctcode::dbnf::ctcode::ClassDef> class_definition, OmniPointer<s84::ctcode::system::ctcode::OutputStream> implementation)
    {
        std::string class_name;
        class_name = this->GenerateClassName(class_definition->GetName());
        std::vector<OmniPointer<s84::ctcode::dbnf::ctcode::ContentDefinition>> definitions = class_definition->GetDefinitions();
        std::vector<OmniPointer<s84::ctcode::dbnf::ctcode::ContentDefinition>> function_definitions;
        int index;
        index = 0;
        while (index < Size(definitions))
        {
            OmniPointer<s84::ctcode::dbnf::ctcode::ContentDefinition> definition;
            definition = Element(definitions, index);
            if (definition->GetFunctionBody())
            {
                Append(function_definitions, definition);
            }

            index = index + 1;
        }

        if (Size(function_definitions) > 0)
        {
            index = 0;
            while (index < Size(function_definitions))
            {
                OmniPointer<s84::ctcode::dbnf::ctcode::ContentDefinition> definition;
                definition = Element(function_definitions, index);
                implementation->WriteLine(Concat(std::string("    "), Concat(this->GetType(definition->GetType()), Concat(std::string(" "), Concat(class_name, Concat(std::string("::"), Concat(this->GenerateCallName(definition->GetName()), Concat(std::string("("), Concat(this->GenerateParameterList(definition->GetParameters()), std::string(")"))))))))));
                this->WriteCodeBlock(1, implementation, definition->GetFunctionBody(), true);
                index = index + 1;
            }
        }
    }

    void CPPTranspiler::WriteInstruction(int indent, OmniPointer<s84::ctcode::system::ctcode::OutputStream> implementation, OmniPointer<s84::ctcode::dbnf::ctcode::Instruction> instruction, bool add_newline_after_code_block)
    {
        if (instruction->GetCodeBlock())
        {
            this->WriteCodeBlock(indent, implementation, instruction->GetCodeBlock(), add_newline_after_code_block);
        }

        if (instruction->GetRtn())
        {
            this->WriteRtn(indent, implementation, instruction->GetRtn());
        }

        if (instruction->GetDeclaration())
        {
            this->WriteDeclaration(indent, implementation, instruction->GetDeclaration());
        }

        if (instruction->GetAssignment())
        {
            this->WriteAssignment(indent, implementation, instruction->GetAssignment());
        }

        if (instruction->GetCall())
        {
            this->WriteCall(indent, implementation, instruction->GetCall());
        }

        if (instruction->GetConditional())
        {
            this->WriteConditional(indent, implementation, instruction->GetConditional(), add_newline_after_code_block);
        }

        if (instruction->GetLoop())
        {
            this->WriteLoop(indent, implementation, instruction->GetLoop(), add_newline_after_code_block);
        }
    }

    void CPPTranspiler::WriteCodeBlock(int indent, OmniPointer<s84::ctcode::system::ctcode::OutputStream> implementation, OmniPointer<s84::ctcode::dbnf::ctcode::CodeBlock> code_block, bool add_newline_after_code_block)
    {
        implementation->WriteLine(Concat(this->Indentation(indent), std::string("{")));
        std::vector<OmniPointer<s84::ctcode::dbnf::ctcode::Instruction>> instructions = code_block->GetInstructions();
        int index;
        index = 0;
        int last;
        last = Size(instructions) - 1;
        while (index < Size(instructions))
        {
            this->WriteInstruction(indent + 1, implementation, Element(instructions, index), index != last);
            index = index + 1;
        }

        implementation->WriteLine(Concat(this->Indentation(indent), std::string("}")));
        if (add_newline_after_code_block)
        {
            implementation->WriteLine(std::string(""));
        }
    }

    void CPPTranspiler::WriteConditional(int indent, OmniPointer<s84::ctcode::system::ctcode::OutputStream> implementation, OmniPointer<s84::ctcode::dbnf::ctcode::Conditional> conditional, bool add_newline_after_code_block)
    {
        implementation->WriteLine(Concat(this->Indentation(indent), Concat(std::string("if ("), Concat(this->GetRValueString(conditional->GetRValue()), std::string(")")))));
        if (conditional->GetElseTail())
        {
            OmniPointer<s84::ctcode::dbnf::ctcode::ElseTail> else_tail;
            else_tail = conditional->GetElseTail();
            this->WriteCodeBlock(indent, implementation, conditional->GetCodeBlock(), false);
            implementation->WriteLine(Concat(this->Indentation(indent), std::string("else")));
            this->WriteCodeBlock(indent, implementation, else_tail->GetCodeBlock(), add_newline_after_code_block);
        }
        else
        {
            this->WriteCodeBlock(indent, implementation, conditional->GetCodeBlock(), add_newline_after_code_block);
        }
    }

    void CPPTranspiler::WriteLoop(int indent, OmniPointer<s84::ctcode::system::ctcode::OutputStream> implementation, OmniPointer<s84::ctcode::dbnf::ctcode::Loop> loop, bool add_newline_after_code_block)
    {
        implementation->WriteLine(Concat(this->Indentation(indent), Concat(std::string("while ("), Concat(this->GetRValueString(loop->GetRValue()), std::string(")")))));
        this->WriteCodeBlock(indent, implementation, loop->GetCodeBlock(), add_newline_after_code_block);
    }

    void CPPTranspiler::WriteRtn(int indent, OmniPointer<s84::ctcode::system::ctcode::OutputStream> implementation, OmniPointer<s84::ctcode::dbnf::ctcode::Return> rtn)
    {
        implementation->WriteLine(Concat(this->Indentation(indent), Concat(std::string("return "), Concat(this->GetRValueString(rtn->GetRValue()), std::string(";")))));
    }

    void CPPTranspiler::WriteDeclaration(int indent, OmniPointer<s84::ctcode::system::ctcode::OutputStream> implementation, OmniPointer<s84::ctcode::dbnf::ctcode::Declaration> declaration)
    {
        std::string assignment_suffix;
        assignment_suffix = std::string("");
        if (declaration->GetAssignment())
        {
            OmniPointer<s84::ctcode::dbnf::ctcode::DeclarationAssign> assignment;
            assignment = declaration->GetAssignment();
            assignment_suffix = Concat(std::string(" = "), this->GetRValueString(assignment->GetRValue()));
        }

        implementation->WriteLine(Concat(this->Indentation(indent), Concat(this->GetVariableDefinition(declaration->GetType(), declaration->GetName()), Concat(assignment_suffix, std::string(";")))));
    }

    void CPPTranspiler::WriteAssignment(int indent, OmniPointer<s84::ctcode::system::ctcode::OutputStream> implementation, OmniPointer<s84::ctcode::dbnf::ctcode::Assignment> assignment)
    {
        implementation->WriteLine(Concat(this->Indentation(indent), Concat(this->GenerateVariableChain(assignment->GetLValue()), Concat(std::string(" = "), Concat(this->GetRValueString(assignment->GetRValue()), std::string(";"))))));
    }

    void CPPTranspiler::WriteCall(int indent, OmniPointer<s84::ctcode::system::ctcode::OutputStream> implementation, OmniPointer<s84::ctcode::dbnf::ctcode::Call> call)
    {
        implementation->WriteLine(Concat(this->Indentation(indent), Concat(this->GetCallString(call), std::string(";"))));
    }

    std::string CPPTranspiler::GetExdefHeaderString(OmniPointer<s84::ctcode::dbnf::ctcode::QualfiedName> exdef_name)
    {
        return Concat(exdef_name->UnParse(), std::string(".hpp"));
    }

    std::vector<std::string> CPPTranspiler::GetUnmanagedTypes(std::vector<OmniPointer<s84::ctcode::dbnf::ctcode::UnmanagedType>> unmanaged_types)
    {
        std::vector<std::string> unmanaged_type_strings;
        int index;
        index = 0;
        while (index < Size(unmanaged_types))
        {
            OmniPointer<s84::ctcode::dbnf::ctcode::UnmanagedType> unmanaged_type = Element(unmanaged_types, index);
            Append(unmanaged_type_strings, this->GetRawDefinedType(unmanaged_type->GetUnmanagedType()));
            index = index + 1;
        }

        return unmanaged_type_strings;
    }

    std::string CPPTranspiler::Indentation(int indent)
    {
        std::string result;
        result = std::string("");
        while (indent > 0)
        {
            indent = indent - 1;
            result = Concat(result, std::string("    "));
        }

        return result;
    }

    std::string CPPTranspiler::GetRValueSingleString(OmniPointer<s84::ctcode::dbnf::ctcode::RValueSingle> r_value_single)
    {
        return Concat(this->GetRValueSingleUnaryString(r_value_single), this->GetRValueSingleCoreString(r_value_single));
    }

    std::string CPPTranspiler::GetRValueSingleUnaryString(OmniPointer<s84::ctcode::dbnf::ctcode::RValueSingle> r_value_single)
    {
        if (r_value_single->GetUnaryOperator())
        {
            OmniPointer<s84::ctcode::dbnf::ctcode::UnaryOperator> unary_operator;
            unary_operator = r_value_single->GetUnaryOperator();
            if (unary_operator->GetNegation())
            {
                return std::string("!");
            }

            return std::string("/*WARNING UnaryOperator FALL THROUGH*/");
        }
        else
        {
            return std::string("");
        }
    }

    std::string CPPTranspiler::GetCallString(OmniPointer<s84::ctcode::dbnf::ctcode::Call> call)
    {
        std::string result;
        result = std::string("");
        if (call->GetVariable())
        {
            result = Concat(result, Concat(this->GenerateVariableName(call->GetVariable()), std::string("->")));
        }

        if (call->GetFunction())
        {
            result = Concat(result, this->GenerateCallName(call->GetFunction()));
        }

        if (call->GetFunctionChain())
        {
            OmniPointer<s84::ctcode::dbnf::ctcode::QualfiedName> function_chain = call->GetFunctionChain();
            OmniPointer<s84::ctcode::dbnf::ctcode::NameTail> name_tail = function_chain->GetTail();
            if (function_chain->GetTail())
            {
                result = Concat(Concat(result, this->GenerateVariableName(function_chain->GetName())), std::string("->"));
            }
            else
            {
                result = Concat(result, this->GenerateCallName(function_chain->GetName()));
            }

            while (name_tail)
            {
                if (name_tail->GetTail())
                {
                    result = Concat(Concat(result, this->GenerateVariableName(name_tail->GetName())), std::string("->"));
                }
                else
                {
                    result = Concat(result, this->GenerateCallName(name_tail->GetName()));
                }

                name_tail = name_tail->GetTail();
            }
        }

        result = Concat(Concat(Concat(result, std::string("(")), this->GenerateCallingParameterList(call->GetParameters())), std::string(")"));
        return result;
    }

    std::string CPPTranspiler::GetRValueSingleCoreString(OmniPointer<s84::ctcode::dbnf::ctcode::RValueSingle> r_value_single)
    {
        if (r_value_single->GetCall())
        {
            return this->GetCallString(r_value_single->GetCall());
        }

        if (r_value_single->GetAllocate())
        {
            OmniPointer<s84::ctcode::dbnf::ctcode::Allocate> allocate = r_value_single->GetAllocate();
            std::string raw_type = this->GetRawDefinedType(allocate->GetManagedType());
            return Concat(std::string("std::shared_ptr<"), Concat(raw_type, Concat(std::string(">(new "), Concat(raw_type, std::string("())")))));
        }

        if (r_value_single->GetByteLiteral())
        {
            return r_value_single->UnParse();
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
            return this->GenerateVariableChain(r_value_single->GetVariable());
        }

        if (r_value_single->GetStringLiteral())
        {
            return Concat(Concat(std::string("std::string("), r_value_single->UnParse()), std::string(")"));
        }

        return std::string("/*WARNING RValueSingle FALL THROUGH*/");
    }

    std::string CPPTranspiler::GetOperator(OmniPointer<s84::ctcode::dbnf::ctcode::BinaryOperator> op)
    {
        if (op->GetAddition())
        {
            return std::string("+");
        }

        if (op->GetSubtraction())
        {
            return std::string("-");
        }

        if (op->GetLessThan())
        {
            return std::string("<");
        }

        if (op->GetLessThanEq())
        {
            return std::string("<=");
        }

        if (op->GetEquality())
        {
            return std::string("==");
        }

        if (op->GetNotEquality())
        {
            return std::string("!=");
        }

        if (op->GetGreaterThanEq())
        {
            return std::string(">=");
        }

        if (op->GetGreaterThan())
        {
            return std::string(">");
        }

        if (op->GetOrOp())
        {
            return std::string("||");
        }

        if (op->GetAndOp())
        {
            return std::string("&&");
        }

        return std::string("/*WARNING BinaryOperator FALL THROUGH*/");
    }

    std::string CPPTranspiler::GetRValueTail(OmniPointer<s84::ctcode::dbnf::ctcode::RValueTail> r_value_tail)
    {
        if (r_value_tail)
        {
            OmniPointer<s84::ctcode::dbnf::ctcode::BinaryOperator> op;
            op = r_value_tail->GetBinaryOperator();
            return Concat(std::string(" "), Concat(this->GetOperator(op), Concat(std::string(" "), Concat(this->GetRValueSingleString(r_value_tail->GetValue()), this->GetRValueTail(r_value_tail->GetTail())))));
        }

        return std::string("");
    }

    std::string CPPTranspiler::GetRValueString(OmniPointer<s84::ctcode::dbnf::ctcode::RValue> r_value)
    {
        return Concat(this->GetRValueSingleString(r_value->GetValue()), this->GetRValueTail(r_value->GetTail()));
    }

    std::string CPPTranspiler::GetVariableDefinition(OmniPointer<s84::ctcode::dbnf::ctcode::ValueType> type, OmniPointer<s84::ctcode::dbnf::ctcode::Name> name)
    {
        return Concat(this->GetType(type), Concat(std::string(" "), this->GenerateVariableName(name)));
    }

    std::string CPPTranspiler::GetParameterString(OmniPointer<s84::ctcode::dbnf::ctcode::ParameterListDef> parameter)
    {
        return this->GetVariableDefinition(parameter->GetType(), parameter->GetName());
    }

    std::string CPPTranspiler::GenerateParameterListTail(OmniPointer<s84::ctcode::dbnf::ctcode::ParameterListDef> parameters)
    {
        if (parameters)
        {
            return Concat(std::string(", "), Concat(this->GetParameterString(parameters), this->GenerateParameterListTail(parameters->GetParameterTail())));
        }

        return std::string("");
    }

    std::string CPPTranspiler::GenerateParameterList(OmniPointer<s84::ctcode::dbnf::ctcode::ParameterListDef> parameters)
    {
        if (parameters)
        {
            return Concat(this->GetParameterString(parameters), this->GenerateParameterListTail(parameters->GetParameterTail()));
        }
        else
        {
            return std::string("");
        }
    }

    std::string CPPTranspiler::GenerateCallingParameterList(OmniPointer<s84::ctcode::dbnf::ctcode::ParameterList> parameters)
    {
        if (parameters)
        {
            return Concat(this->GetCallingParameterString(parameters), this->GenerateCallingParameterListTail(parameters->GetParameterTail()));
        }
        else
        {
            return std::string("");
        }
    }

    std::string CPPTranspiler::GetCallingParameterString(OmniPointer<s84::ctcode::dbnf::ctcode::ParameterList> parameter)
    {
        if (parameter)
        {
            return this->GetRValueString(parameter->GetRValue());
        }
        else
        {
            return std::string("");
        }
    }

    std::string CPPTranspiler::GenerateCallingParameterListTail(OmniPointer<s84::ctcode::dbnf::ctcode::ParameterList> parameters)
    {
        if (parameters)
        {
            return Concat(std::string(", "), Concat(this->GetCallingParameterString(parameters), this->GenerateCallingParameterListTail(parameters->GetParameterTail())));
        }

        return std::string("");
    }

    std::string CPPTranspiler::GetType(OmniPointer<s84::ctcode::dbnf::ctcode::ValueType> value_type)
    {
        if (value_type->GetDimensionalType())
        {
            return this->GetDimensionalType(value_type->GetDimensionalType());
        }

        if (value_type->GetMapType())
        {
            return this->GetMapType(value_type->GetMapType());
        }

        if (value_type->GetSingletonType())
        {
            return this->GetSingletonType(value_type->GetSingletonType());
        }

        return std::string("/*WARNING ValueType FALL THROUGH*/");
    }

    std::string CPPTranspiler::GetDimensionalType(OmniPointer<s84::ctcode::dbnf::ctcode::DimensionalType> dimensional_type)
    {
        std::vector<OmniPointer<s84::ctcode::dbnf::ctcode::DimensionalNote>> dimensional_note_list;
        dimensional_note_list = dimensional_type->GetDimensionalNote();
        int dimensional_notes;
        dimensional_notes = Size(dimensional_note_list);
        return Concat(this->GetDimensionalPrefix(dimensional_notes), Concat(this->GetSingletonType(dimensional_type->GetSingletonType()), this->GetDimensionalSuffix(dimensional_notes)));
    }

    std::string CPPTranspiler::GetDimensionalPrefix(int dimensional_notes)
    {
        std::string dimensional_prefix;
        dimensional_prefix = std::string("");
        while (dimensional_notes > 0)
        {
            dimensional_prefix = Concat(dimensional_prefix, std::string("std::vector<"));
            dimensional_notes = dimensional_notes - 1;
        }

        return dimensional_prefix;
    }

    std::string CPPTranspiler::GetDimensionalSuffix(int dimensional_notes)
    {
        std::string dimensional_suffix;
        dimensional_suffix = std::string("");
        while (dimensional_notes > 0)
        {
            dimensional_suffix = Concat(dimensional_suffix, std::string(">"));
            dimensional_notes = dimensional_notes - 1;
        }

        return dimensional_suffix;
    }

    std::string CPPTranspiler::GetMapType(OmniPointer<s84::ctcode::dbnf::ctcode::MapType> map_type)
    {
        return Concat(std::string("std::unordered_map<std::string, "), Concat(this->GetSingletonType(map_type->GetSingletonType()), std::string(">")));
    }

    std::string CPPTranspiler::GetSingletonType(OmniPointer<s84::ctcode::dbnf::ctcode::SingletonType> singleton_type)
    {
        if (singleton_type->GetDefinedType())
        {
            OmniPointer<s84::ctcode::dbnf::ctcode::DefinedType> defined_type;
            defined_type = singleton_type->GetDefinedType();
            OmniPointer<s84::ctcode::dbnf::ctcode::QualfiedName> defined_type_name;
            defined_type_name = defined_type->GetName();
            return this->GetDefinedType(defined_type_name);
        }

        if (singleton_type->GetPrimativeType())
        {
            OmniPointer<s84::ctcode::dbnf::ctcode::PrimativeType> primative_type;
            primative_type = singleton_type->GetPrimativeType();
            std::string primative_type_string;
            primative_type_string = primative_type->UnParse();
            if (primative_type_string == std::string("int"))
            {
                return std::string("int");
            }

            if (primative_type_string == std::string("string"))
            {
                return std::string("std::string");
            }

            if (primative_type_string == std::string("bool"))
            {
                return std::string("bool");
            }

            if (primative_type_string == std::string("float"))
            {
                return std::string("float");
            }

            if (primative_type_string == std::string("void"))
            {
                return std::string("void");
            }

            return std::string("/*WARNING PrimativeType FALL THROUGH*/");
        }

        return std::string("/*WARNING SingletonType FALL THROUGH*/");
    }

    std::string CPPTranspiler::GetDefinedType(OmniPointer<s84::ctcode::dbnf::ctcode::QualfiedName> qualified_name)
    {
        std::string raw_type = this->GetRawDefinedType(qualified_name);
        if (this->IsUnmanagedType(raw_type))
        {
            return Concat(raw_type, std::string("*"));
        }
        else
        {
            return Concat(std::string("OmniPointer<"), Concat(raw_type, std::string(">")));
        }
    }

    std::string CPPTranspiler::GetRawDefinedType(OmniPointer<s84::ctcode::dbnf::ctcode::QualfiedName> qualified_name)
    {
        OmniPointer<s84::ctcode::dbnf::ctcode::NameTail> name_tail;
        name_tail = qualified_name->GetTail();
        OmniPointer<s84::ctcode::dbnf::ctcode::Name> name;
        name = qualified_name->GetName();
        std::string result;
        result = std::string("");
        if (name_tail)
        {
            std::string name_string;
            name_string = name->UnParse();
            std::string lower_name_string;
            lower_name_string = this->ToLower(name_string);
            std::string name_tail_string;
            name_tail_string = this->GetRawDefinedTypeTail(name_tail);
            result = Concat(result, lower_name_string);
            result = Concat(result, name_tail_string);
        }
        else
        {
            std::string class_name;
            class_name = this->GenerateClassName(name);
            result = Concat(result, class_name);
        }

        return result;
    }

    std::string CPPTranspiler::GetRawDefinedTypeTail(OmniPointer<s84::ctcode::dbnf::ctcode::NameTail> name_tail)
    {
        OmniPointer<s84::ctcode::dbnf::ctcode::NameTail> name_tail_tail;
        name_tail_tail = name_tail->GetTail();
        OmniPointer<s84::ctcode::dbnf::ctcode::Name> name;
        name = name_tail->GetName();
        std::string result;
        result = std::string("::");
        if (name_tail_tail)
        {
            std::string name_string;
            name_string = name->UnParse();
            std::string lower_name_string;
            lower_name_string = this->ToLower(name_string);
            std::string name_tail_tail_string;
            name_tail_tail_string = this->GetRawDefinedTypeTail(name_tail_tail);
            result = Concat(result, lower_name_string);
            result = Concat(result, name_tail_tail_string);
        }
        else
        {
            std::string class_name;
            class_name = this->GenerateClassName(name);
            result = Concat(result, class_name);
        }

        return result;
    }

    std::string CPPTranspiler::GenerateClassName(OmniPointer<s84::ctcode::dbnf::ctcode::Name> name_node)
    {
        if (name_node)
        {
            std::string name_node_string = name_node->UnParse();
            return this->SnakeCaseToCamelCase(name_node_string);
        }
        else
        {
            return std::string("");
        }
    }

    std::string CPPTranspiler::GenerateVariableChainNameTail(OmniPointer<s84::ctcode::dbnf::ctcode::NameTail> name_tail)
    {
        if (name_tail->GetTail())
        {
            return Concat(Concat(this->GenerateVariableName(name_tail->GetName()), std::string("->")), this->GenerateVariableChainNameTail(name_tail->GetTail()));
        }
        else
        {
            return this->GenerateVariableName(name_tail->GetName());
        }
    }

    std::string CPPTranspiler::GenerateVariableChain(OmniPointer<s84::ctcode::dbnf::ctcode::QualfiedName> qualified_name_node)
    {
        if (qualified_name_node->GetTail())
        {
            return Concat(Concat(this->GenerateVariableName(qualified_name_node->GetName()), std::string("->")), this->GenerateVariableChainNameTail(qualified_name_node->GetTail()));
        }
        else
        {
            return this->GenerateVariableName(qualified_name_node->GetName());
        }
    }

    std::string CPPTranspiler::GenerateVariableName(OmniPointer<s84::ctcode::dbnf::ctcode::Name> name_node)
    {
        if (name_node)
        {
            std::string name_node_string = name_node->UnParse();
            if (name_node_string == std::string("myself"))
            {
                return std::string("this");
            }

            return this->CamelCaseToSnakeCase(name_node_string);
        }
        else
        {
            return std::string("");
        }
    }

    std::string CPPTranspiler::GenerateCallName(OmniPointer<s84::ctcode::dbnf::ctcode::Name> name_node)
    {
        if (name_node)
        {
            std::string name_node_string = name_node->UnParse();
            return this->SnakeCaseToCamelCase(name_node_string);
        }
        else
        {
            return std::string("");
        }
    }

    std::vector<std::string> CPPTranspiler::TokenizeBaseName(std::string name)
    {
        std::vector<std::string> base_name_tokens;
        std::string current_token;
        current_token = std::string("");
        int index;
        index = 0;
        while (index < Length(name))
        {
            std::string character;
            character = At(name, index);
            if (character == std::string("."))
            {
                Append(base_name_tokens, current_token);
                current_token = std::string("");
            }
            else
            {
                current_token = Concat(current_token, character);
            }

            index = index + 1;
        }

        return base_name_tokens;
    }

    std::string CPPTranspiler::GenerateGuardName(std::vector<std::string> base_name_tokens)
    {
        std::string guard_name;
        guard_name = std::string("");
        std::string ctcode_guard;
        ctcode_guard = std::string("CTCODE_H");
        std::string namespace_seperator;
        namespace_seperator = std::string("_");
        int index;
        index = 0;
        while (index < Size(base_name_tokens))
        {
            std::string namespace_token;
            namespace_token = Element(base_name_tokens, index);
            std::string upper_namespace_token;
            upper_namespace_token = this->ToUpper(namespace_token);
            guard_name = Concat(guard_name, upper_namespace_token);
            guard_name = Concat(guard_name, namespace_seperator);
            index = index + 1;
        }

        guard_name = Concat(guard_name, ctcode_guard);
        return guard_name;
    }

    std::string CPPTranspiler::SnakeCaseToCamelCase(std::string snake_case)
    {
        bool capitalize_this_letter;
        capitalize_this_letter = true;
        std::string camel_case;
        camel_case = std::string("");
        int index;
        index = 0;
        while (index < Length(snake_case))
        {
            std::string source_character;
            source_character = At(snake_case, index);
            if (source_character == std::string("_"))
            {
                capitalize_this_letter = true;
            }
            else
            {
                if (capitalize_this_letter == true)
                {
                    std::string upper_character;
                    upper_character = this->CharacterToUpper(source_character);
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

    std::string CPPTranspiler::CamelCaseToSnakeCase(std::string camel_case)
    {
        std::string delimiter;
        delimiter = std::string("_");
        bool in_abbreviation;
        in_abbreviation = true;
        std::string snake_case;
        snake_case = std::string("");
        int index;
        index = 0;
        while (index < Length(camel_case))
        {
            std::string source_character;
            source_character = At(camel_case, index);
            std::string lower_character;
            lower_character = this->CharacterToLower(source_character);
            if (this->IsUpper(source_character) || this->IsDigit(source_character))
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

    bool CPPTranspiler::IsUpper(std::string character)
    {
        bool result;
        result = false;
        result = result || character == std::string("A");
        result = result || character == std::string("B");
        result = result || character == std::string("C");
        result = result || character == std::string("D");
        result = result || character == std::string("E");
        result = result || character == std::string("F");
        result = result || character == std::string("G");
        result = result || character == std::string("H");
        result = result || character == std::string("I");
        result = result || character == std::string("J");
        result = result || character == std::string("K");
        result = result || character == std::string("L");
        result = result || character == std::string("M");
        result = result || character == std::string("N");
        result = result || character == std::string("O");
        result = result || character == std::string("P");
        result = result || character == std::string("Q");
        result = result || character == std::string("R");
        result = result || character == std::string("S");
        result = result || character == std::string("T");
        result = result || character == std::string("U");
        result = result || character == std::string("V");
        result = result || character == std::string("W");
        result = result || character == std::string("X");
        result = result || character == std::string("Y");
        result = result || character == std::string("Z");
        return result;
    }

    bool CPPTranspiler::IsDigit(std::string character)
    {
        bool result;
        result = false;
        result = result || character == std::string("0");
        result = result || character == std::string("1");
        result = result || character == std::string("2");
        result = result || character == std::string("3");
        result = result || character == std::string("4");
        result = result || character == std::string("5");
        result = result || character == std::string("6");
        result = result || character == std::string("7");
        result = result || character == std::string("8");
        result = result || character == std::string("9");
        return result;
    }

    std::string CPPTranspiler::ToLower(std::string input)
    {
        int index;
        index = 0;
        std::string result;
        result = std::string("");
        while (index < Length(input))
        {
            std::string character;
            character = At(input, index);
            std::string lower_character;
            lower_character = this->CharacterToLower(character);
            result = Concat(result, lower_character);
            index = index + 1;
        }

        return result;
    }

    std::string CPPTranspiler::CharacterToLower(std::string input)
    {
        if (input == std::string("A"))
        {
            return std::string("a");
        }

        if (input == std::string("B"))
        {
            return std::string("b");
        }

        if (input == std::string("C"))
        {
            return std::string("c");
        }

        if (input == std::string("D"))
        {
            return std::string("d");
        }

        if (input == std::string("E"))
        {
            return std::string("e");
        }

        if (input == std::string("F"))
        {
            return std::string("f");
        }

        if (input == std::string("G"))
        {
            return std::string("g");
        }

        if (input == std::string("H"))
        {
            return std::string("h");
        }

        if (input == std::string("I"))
        {
            return std::string("i");
        }

        if (input == std::string("J"))
        {
            return std::string("j");
        }

        if (input == std::string("K"))
        {
            return std::string("k");
        }

        if (input == std::string("L"))
        {
            return std::string("l");
        }

        if (input == std::string("M"))
        {
            return std::string("m");
        }

        if (input == std::string("N"))
        {
            return std::string("n");
        }

        if (input == std::string("O"))
        {
            return std::string("o");
        }

        if (input == std::string("P"))
        {
            return std::string("p");
        }

        if (input == std::string("Q"))
        {
            return std::string("q");
        }

        if (input == std::string("R"))
        {
            return std::string("r");
        }

        if (input == std::string("S"))
        {
            return std::string("s");
        }

        if (input == std::string("T"))
        {
            return std::string("t");
        }

        if (input == std::string("U"))
        {
            return std::string("u");
        }

        if (input == std::string("V"))
        {
            return std::string("v");
        }

        if (input == std::string("W"))
        {
            return std::string("w");
        }

        if (input == std::string("X"))
        {
            return std::string("x");
        }

        if (input == std::string("Y"))
        {
            return std::string("y");
        }

        if (input == std::string("Z"))
        {
            return std::string("z");
        }

        return input;
    }

    std::string CPPTranspiler::ToUpper(std::string input)
    {
        int index;
        index = 0;
        std::string result;
        result = std::string("");
        while (index < Length(input))
        {
            std::string character;
            character = At(input, index);
            std::string upper_character;
            upper_character = this->CharacterToUpper(character);
            result = Concat(result, upper_character);
            index = index + 1;
        }

        return result;
    }

    std::string CPPTranspiler::CharacterToUpper(std::string input)
    {
        if (input == std::string("a"))
        {
            return std::string("A");
        }

        if (input == std::string("b"))
        {
            return std::string("B");
        }

        if (input == std::string("c"))
        {
            return std::string("C");
        }

        if (input == std::string("d"))
        {
            return std::string("D");
        }

        if (input == std::string("e"))
        {
            return std::string("E");
        }

        if (input == std::string("f"))
        {
            return std::string("F");
        }

        if (input == std::string("g"))
        {
            return std::string("G");
        }

        if (input == std::string("h"))
        {
            return std::string("H");
        }

        if (input == std::string("i"))
        {
            return std::string("I");
        }

        if (input == std::string("j"))
        {
            return std::string("J");
        }

        if (input == std::string("k"))
        {
            return std::string("K");
        }

        if (input == std::string("l"))
        {
            return std::string("L");
        }

        if (input == std::string("m"))
        {
            return std::string("M");
        }

        if (input == std::string("n"))
        {
            return std::string("N");
        }

        if (input == std::string("o"))
        {
            return std::string("O");
        }

        if (input == std::string("p"))
        {
            return std::string("P");
        }

        if (input == std::string("q"))
        {
            return std::string("Q");
        }

        if (input == std::string("r"))
        {
            return std::string("R");
        }

        if (input == std::string("s"))
        {
            return std::string("S");
        }

        if (input == std::string("t"))
        {
            return std::string("T");
        }

        if (input == std::string("u"))
        {
            return std::string("U");
        }

        if (input == std::string("v"))
        {
            return std::string("V");
        }

        if (input == std::string("w"))
        {
            return std::string("W");
        }

        if (input == std::string("x"))
        {
            return std::string("X");
        }

        if (input == std::string("y"))
        {
            return std::string("Y");
        }

        if (input == std::string("z"))
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
