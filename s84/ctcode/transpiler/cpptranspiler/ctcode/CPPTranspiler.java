package s84.ctcode.transpiler.cpptranspiler.ctcode;

import s84.ctcode.dbnf.ctcode.*;
import s84.ctcode.system.ctcode.*;
import s84.ctcode.transpiler.standardstructure.ctcode.*;
import s84.ctcode.transpiler.stringhelper.ctcode.*;

public class CPPTranspiler implements s84.ctcode.transpiler.standardstructure.ctcode.TargetSpecificFunctions {
    public CPPTranspiler()
    {
        this.system = null;
        this.c_t_code_file = null;
        this.base_name = "";
        this.logger = null;
        this.string_helper = null;
        this.includes = new java.util.ArrayList<>();
        this.interface_declarations = new java.util.ArrayList<>();
        this.class_declarations = new java.util.ArrayList<>();
        this.current_interface = "";
        this.interface_definitions = new java.util.ArrayList<>();
        this.current_class = "";
        this.class_definitions = new java.util.ArrayList<>();
        this.class_init = new java.util.ArrayList<>();
        this.class_functions = new java.util.ArrayList<>();
        this.class_members = new java.util.ArrayList<>();
        this.function_definitions = new java.util.ArrayList<>();
    }

    public void Initialize()
    {
        this.string_helper = new s84.ctcode.transpiler.stringhelper.ctcode.StringHelper();
    }

    public void SetSystem(s84.ctcode.system.ctcode.System system)
    {
        this.system = system;
    }

    public void SetCTCodeFile(s84.ctcode.dbnf.ctcode.CTCodeFile c_t_code_file)
    {
        this.c_t_code_file = c_t_code_file;
    }

    public void SetBaseName(java.lang.String base_name)
    {
        this.base_name = base_name;
    }

    public void SetLogger(s84.ctcode.system.ctcode.OutputStream logger)
    {
        this.logger = logger;
    }

    public int GetBaseIndentation()
    {
        return 0;
    }

    public java.lang.String GetCallName(java.lang.String name)
    {
        return this.string_helper.SnakeCaseToCamelCase(name);
    }

    public java.lang.String GetVariableName(java.lang.String name)
    {
        java.lang.String value = this.string_helper.CamelCaseToSnakeCase(name);
        if (AsBoolean(Equals(value,"myself")))
        {
            return "this";
        }
        return value;
    }

    public java.lang.String GetVariableChain(java.util.ArrayList<java.lang.String> name_parts)
    {
        java.lang.String delimiter = "->";
        java.lang.String first_name = Element(name_parts, 0);
        java.lang.String result = this.GetVariableName(first_name);
        int name_parts_index = 1;
        while (AsBoolean((name_parts_index<Size(name_parts))))
        {
            java.lang.String name = Element(name_parts, name_parts_index);
            result = Concat(Concat(result, delimiter), this.GetVariableName(name));
            name_parts_index = (name_parts_index+1);
        }
        return result;
    }

    public java.lang.String ConvertCall(java.util.ArrayList<java.lang.String> name_chain, java.util.ArrayList<java.lang.String> parameters)
    {
        java.lang.String result = Element(name_chain, 0);
        int name_chain_index = 1;
        while (AsBoolean((name_chain_index<Size(name_chain))))
        {
            java.lang.String name_part = Element(name_chain, name_chain_index);
            result = Concat(Concat(result, "->"), name_part);
            name_chain_index = (name_chain_index+1);
        }
        result = Concat(result, "(");
        if (AsBoolean((Size(parameters)>0)))
        {
            result = Concat(result, Element(parameters, 0));
            int parameters_index = 1;
            while (AsBoolean((parameters_index<Size(parameters))))
            {
                java.lang.String parameter = Element(parameters, parameters_index);
                result = Concat(result, ",");
                result = Concat(result, parameter);
                parameters_index = (parameters_index+1);
            }
        }
        result = Concat(result, ")");
        return result;
    }

    public java.lang.String ConvertAllocate(java.lang.String type)
    {
        return Concat(Concat(Concat(Concat("std::shared_ptr<", type), ">(new "), type), "())");
    }

    public java.lang.String ConvertByte(java.lang.String high, java.lang.String low)
    {
        return Concat(Concat("0x", high), low);
    }

    public java.lang.String ConvertDecimal(java.lang.String decimal)
    {
        return decimal;
    }

    public java.lang.String ConvertNumber(java.lang.String number)
    {
        return number;
    }

    public java.lang.String ConvertBoolean(java.lang.String reserved_prefix_boolean)
    {
        if (AsBoolean(Equals(reserved_prefix_boolean,"true")))
        {
            return "true";
        }
        if (AsBoolean(Equals(reserved_prefix_boolean,"false")))
        {
            return "false";
        }
        return "";
    }

    public java.lang.String ConvertVariable(java.lang.String variable)
    {
        return variable;
    }

    public java.lang.String ConvertString(java.lang.String literal)
    {
        return Concat(Concat("std::string(\"", literal), "\")");
    }

    public java.lang.String UnaryOperator(java.lang.String op, java.lang.String r_value)
    {
        if (AsBoolean(Equals(op,"!")))
        {
            return Concat("!", r_value);
        }
        return r_value;
    }

    public java.lang.String BinaryOperator(java.lang.String op, java.lang.String r_value_l, java.lang.String r_value_r)
    {
        if (AsBoolean(Equals(op,"+")))
        {
            return Concat(Concat(r_value_l, "+"), r_value_r);
        }
        if (AsBoolean(Equals(op,"-")))
        {
            return Concat(Concat(r_value_l, "-"), r_value_r);
        }
        if (AsBoolean(Equals(op,"<=")))
        {
            return Concat(Concat(r_value_l, "<="), r_value_r);
        }
        if (AsBoolean(Equals(op,">=")))
        {
            return Concat(Concat(r_value_l, ">="), r_value_r);
        }
        if (AsBoolean(Equals(op,"==")))
        {
            return Concat(Concat(r_value_l, "=="), r_value_r);
        }
        if (AsBoolean(Equals(op,"!=")))
        {
            return Concat(Concat(r_value_l, "!="), r_value_r);
        }
        if (AsBoolean(Equals(op,"<")))
        {
            return Concat(Concat(r_value_l, "<"), r_value_r);
        }
        if (AsBoolean(Equals(op,">")))
        {
            return Concat(Concat(r_value_l, ">"), r_value_r);
        }
        if (AsBoolean(Equals(op,"||")))
        {
            return Concat(Concat(r_value_l, "||"), r_value_r);
        }
        if (AsBoolean(Equals(op,"&&")))
        {
            return Concat(Concat(r_value_l, "&&"), r_value_r);
        }
        return "";
    }

    public java.lang.String GetTypeName(java.lang.String name)
    {
        return this.string_helper.SnakeCaseToCamelCase(name);
    }

    public java.lang.String GetDimensionalType(java.lang.String singleton_type, int dimensions)
    {
        java.lang.String result = singleton_type;
        while (AsBoolean((dimensions>0)))
        {
            result = Concat(Concat("std::vector<", result), ">");
            dimensions = (dimensions-1);
        }
        return result;
    }

    public java.lang.String GetMapType(java.lang.String singleton_type)
    {
        return Concat(Concat("std::unordered_map<std::string, ", singleton_type), ">");
    }

    public java.lang.String GetPrimativeType(java.lang.String c_t_type)
    {
        if (AsBoolean(Equals(c_t_type,"int")))
        {
            return "int";
        }
        if (AsBoolean(Equals(c_t_type,"string")))
        {
            return "std::string";
        }
        if (AsBoolean(Equals(c_t_type,"bool")))
        {
            return "bool";
        }
        if (AsBoolean(Equals(c_t_type,"float")))
        {
            return "float";
        }
        if (AsBoolean(Equals(c_t_type,"void")))
        {
            return "void";
        }
        return "";
    }

    public java.lang.String GetDefinedType(java.lang.String c_t_type)
    {
        return Concat(Concat("OmniPointer<", c_t_type), ">");
    }

    public java.lang.String GetQualifiedTypeName(java.util.ArrayList<java.lang.String> name_parts)
    {
        java.lang.String delimiter = "::";
        int name_parts_index = (Size(name_parts)-1);
        java.lang.String type_part = Element(name_parts, name_parts_index);
        java.lang.String result = this.GetTypeName(type_part);
        if (AsBoolean((name_parts_index>0)))
        {
            while (AsBoolean((name_parts_index>0)))
            {
                name_parts_index = (name_parts_index-1);
                result = Concat(delimiter, result);
                java.lang.String name_part = Element(name_parts, name_parts_index);
                result = Concat(this.string_helper.ToLower(name_part), result);
            }
        }
        return result;
    }

    public void BeginProcessingCTCodeFile()
    {
        ClearList(this.includes);
        ClearList(this.interface_declarations);
        ClearList(this.class_declarations);
        this.current_interface = "";
        ClearList(this.interface_definitions);
        this.current_class = "";
        ClearList(this.class_definitions);
        ClearList(this.class_init);
        ClearList(this.class_functions);
        ClearList(this.class_members);
        ClearList(this.function_definitions);
    }

    public void ProcessExdef(java.lang.String exdef)
    {
        Append(this.includes, Concat("#include \"", Concat(exdef, ".hpp\"")));
    }

    public void ProcessUnmanagedType(java.lang.String unmanaged_type)
    {
    }

    public void BeginProcessingInterface(java.lang.String interface_name)
    {
        this.current_interface = interface_name;
        Append(this.interface_declarations, Concat(Concat("class ", interface_name), ";"));
        Append(this.interface_definitions, Concat(Concat("class ", interface_name), " {"));
        Append(this.interface_definitions, "public:");
    }

    public void ProcessInterfaceFunctionDeclaration(java.lang.String return_type, java.lang.String function_name, java.util.ArrayList<s84.ctcode.transpiler.standardstructure.ctcode.ParameterDeclaration> parameters)
    {
        Append(this.interface_definitions, Concat(Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(1), "virtual "), return_type), " "), function_name), this.MakeParametersString(parameters)), " = 0;"));
    }

    public void FinishProcessingInterface(java.lang.String interface_name)
    {
        Append(this.interface_definitions, "};");
        Append(this.interface_definitions, "");
        this.current_interface = "";
    }

    public void BeginProcessingClass(java.lang.String class_name, java.lang.String implementing)
    {
        this.current_class = class_name;
        Append(this.class_declarations, Concat(Concat("class ", class_name), ";"));
        if (AsBoolean(Equals(implementing,"")))
        {
            Append(this.class_definitions, Concat(Concat("class ", class_name), " {"));
        }
        else
        {
            Append(this.class_definitions, Concat(Concat(Concat(Concat("class ", class_name), " : public "), implementing), " {"));
        }
        Append(this.class_definitions, "public:");
        Append(this.class_definitions, Concat(Concat(this.string_helper.Indentation(1), class_name), "();"));
        Append(this.class_definitions, Concat(Concat(Concat(this.string_helper.Indentation(1), "inline ~"), class_name), "() {}"));
        Append(this.class_definitions, "");
        ClearList(this.class_init);
        ClearList(this.class_functions);
        ClearList(this.class_members);
        Append(this.class_init, Concat(Concat(Concat(class_name, "::"), class_name), "()"));
        Append(this.class_init, "{");
    }

    public void BeginProcessingClassFunctionDefinition(java.lang.String return_type, java.lang.String function_name, java.util.ArrayList<s84.ctcode.transpiler.standardstructure.ctcode.ParameterDeclaration> parameters)
    {
        Append(this.class_definitions, Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(1), return_type), " "), function_name), this.MakeParametersString(parameters)), ";"));
        Append(this.class_functions, Concat(Concat(Concat(Concat(Concat(return_type, " "), this.current_class), "::"), function_name), this.MakeParametersString(parameters)));
    }

    public void BeginProcessCodeBlock(int indent)
    {
        Append(this.class_functions, Concat(this.string_helper.Indentation(indent), "{"));
    }

    public void FinishProcessCodeBlock(int indent)
    {
        Append(this.class_functions, Concat(this.string_helper.Indentation(indent), "}"));
    }

    public void BeginProcessConditional(int indent, java.lang.String r_value)
    {
        Append(this.class_functions, Concat(Concat(Concat(this.string_helper.Indentation(indent), "if ("), r_value), ")"));
    }

    public void ProcessElse(int indent)
    {
        Append(this.class_functions, Concat(this.string_helper.Indentation(indent), "else"));
    }

    public void FinishProcessConditional(int indent, java.lang.String r_value)
    {
    }

    public void BeginProcessLoop(int indent, java.lang.String r_value)
    {
        Append(this.class_functions, Concat(Concat(Concat(this.string_helper.Indentation(indent), "while ("), r_value), ")"));
    }

    public void FinishProcessLoop(int indent, java.lang.String r_value)
    {
    }

    public void ProcessRtn(int indent, java.lang.String r_value)
    {
        Append(this.class_functions, Concat(Concat(Concat(this.string_helper.Indentation(indent), "return "), r_value), ";"));
    }

    public void ProcessDeclaration(int indent, java.lang.String type, java.lang.String l_value, java.lang.String r_value)
    {
        if (AsBoolean(Equals(r_value,"")))
        {
            r_value = this.GetDefault(type);
        }
        if (AsBoolean(Equals(r_value,"")))
        {
            Append(this.class_functions, Concat(Concat(Concat(Concat(this.string_helper.Indentation(indent), type), " "), l_value), ";"));
        }
        else
        {
            Append(this.class_functions, Concat(Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(indent), type), " "), l_value), " = "), r_value), ";"));
        }
    }

    public void ProcessAssignment(int indent, java.lang.String l_value, java.lang.String r_value)
    {
        Append(this.class_functions, Concat(Concat(Concat(Concat(this.string_helper.Indentation(indent), l_value), " = "), r_value), ";"));
    }

    public void ProcessCall(int indent, java.lang.String call)
    {
        Append(this.class_functions, Concat(Concat(this.string_helper.Indentation(indent), call), ";"));
    }

    public void FinishProcessingClassFunctionDefinition(java.lang.String return_type, java.lang.String function_name, java.util.ArrayList<s84.ctcode.transpiler.standardstructure.ctcode.ParameterDeclaration> parameters)
    {
        Append(this.class_functions, "");
    }

    public void ProcessClassMemberDeclaration(java.lang.String member_type, java.lang.String member_name)
    {
        java.lang.String default_value = this.GetDefault(member_type);
        if (AsBoolean(!Equals(default_value,"")))
        {
            Append(this.class_init, Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(1), "this->"), member_name), " = "), default_value), ";"));
        }
        else
        {
            Append(this.class_init, Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(1), "/*this->"), member_name), " = "), "NO_DEFAULT"), ";*/"));
        }
        Append(this.class_members, Concat(Concat(Concat(Concat(this.string_helper.Indentation(1), member_type), " "), member_name), ";"));
    }

    public void FinishProcessingClass(java.lang.String class_name, java.lang.String implementing)
    {
        if (AsBoolean((Size(this.class_members)>0)))
        {
            Append(this.class_definitions, "");
            Append(this.class_definitions, "private:");
            int class_members_index = 0;
            while (AsBoolean((class_members_index<Size(this.class_members))))
            {
                java.lang.String line = Element(this.class_members, class_members_index);
                Append(this.class_definitions, line);
                class_members_index = (class_members_index+1);
            }
        }
        Append(this.class_definitions, "};");
        Append(this.class_definitions, "");
        Append(this.class_init, "}");
        Append(this.class_init, "");
        int class_init_index = 0;
        while (AsBoolean((class_init_index<Size(this.class_init))))
        {
            java.lang.String line = Element(this.class_init, class_init_index);
            Append(this.function_definitions, line);
            class_init_index = (class_init_index+1);
        }
        int class_functions_index = 0;
        while (AsBoolean((class_functions_index<Size(this.class_functions))))
        {
            java.lang.String line = Element(this.class_functions, class_functions_index);
            Append(this.function_definitions, line);
            class_functions_index = (class_functions_index+1);
        }
        this.current_class = "";
    }

    public void WriteCommonFunctions(s84.ctcode.system.ctcode.OutputStream destination)
    {
        destination.WriteLine("#ifndef CTCODE_COMMON_FUNCTIONS_VERSION_1");
        destination.WriteLine("#define CTCODE_COMMON_FUNCTIONS_VERSION_1");
        destination.WriteLine("template<typename T>");
        destination.WriteLine("class OmniPointer");
        destination.WriteLine("{");
        destination.WriteLine("public:");
        destination.WriteLine("    OmniPointer() { value_raw = NULL; }");
        destination.WriteLine("    OmniPointer(T* value) { value_raw = value; }");
        destination.WriteLine("    template<typename U>");
        destination.WriteLine("    OmniPointer(U* value) { value_raw = value; }");
        destination.WriteLine("    OmniPointer(std::shared_ptr<T> value) { value_raw = NULL; value_shared = value; }");
        destination.WriteLine("    template<typename U>");
        destination.WriteLine("    OmniPointer(std::shared_ptr<U> value) { value_raw = NULL; value_shared = value; }");
        destination.WriteLine("    template<typename U>");
        destination.WriteLine("    OmniPointer(OmniPointer<U> value) { value_raw = value.value_raw; value_shared = value.value_shared; }");
        destination.WriteLine("");
        destination.WriteLine("    operator bool()");
        destination.WriteLine("    {");
        destination.WriteLine("        if (value_raw) return true;");
        destination.WriteLine("        return value_shared.get() != NULL;");
        destination.WriteLine("    }");
        destination.WriteLine("    T& operator*()");
        destination.WriteLine("    {");
        destination.WriteLine("        if (value_raw) return *value_raw;");
        destination.WriteLine("        return *value_shared;");
        destination.WriteLine("    }");
        destination.WriteLine("    T* operator->()");
        destination.WriteLine("    {");
        destination.WriteLine("        if (value_raw) return value_raw;");
        destination.WriteLine("        return value_shared.get();");
        destination.WriteLine("    }");
        destination.WriteLine("    T* raw()");
        destination.WriteLine("    {");
        destination.WriteLine("        if (value_raw) return value_raw;");
        destination.WriteLine("        return value_shared.get();");
        destination.WriteLine("    }");
        destination.WriteLine("");
        destination.WriteLine("    T* value_raw;");
        destination.WriteLine("    std::shared_ptr<T> value_shared;");
        destination.WriteLine("};");
        destination.WriteLine("");
        destination.WriteLine("template<typename T>");
        destination.WriteLine("inline std::vector<T*> UnwrapOmniList(std::vector<OmniPointer<T>> input) {");
        destination.WriteLine("	std::vector<T*> result;");
        destination.WriteLine("	for (typename std::vector<OmniPointer<T>>::iterator index = input.begin();index != input.end();index++) {");
        destination.WriteLine("		result.push_back(index->raw());");
        destination.WriteLine("	}");
        destination.WriteLine("	return result;");
        destination.WriteLine("};");
        destination.WriteLine("template<typename T>");
        destination.WriteLine("inline void ClearList(std::vector<T>& input) { input.clear(); };");
        destination.WriteLine("template<typename T>");
        destination.WriteLine("inline int Size(const std::vector<T>& input) { return input.size(); };");
        destination.WriteLine("template<typename T>");
        destination.WriteLine("inline T Element(const std::vector<T>& input, int element) { return input.at(element); };");
        destination.WriteLine("template<typename T>");
        destination.WriteLine("inline void Append(std::vector<T>& input, T element) { input.push_back(element); };");
        destination.WriteLine("template<typename T>");
        destination.WriteLine("inline void ClearMap(std::unordered_map<std::string, T>& input) { input.clear(); };");
        destination.WriteLine("template<typename T>");
        destination.WriteLine("inline void SetKV(std::unordered_map<std::string, T>& input, const std::string& key, T element)");
        destination.WriteLine("{");
        destination.WriteLine("    input.erase(key);");
        destination.WriteLine("    input.insert(std::pair<std::string, T>(key, element));");
        destination.WriteLine("}");
        destination.WriteLine("template<typename T>");
        destination.WriteLine("inline std::vector<std::string> Keys(const std::unordered_map<std::string, T>& input)");
        destination.WriteLine("{");
        destination.WriteLine("    std::vector<std::string> result;");
        destination.WriteLine("    for(typename std::unordered_map<std::string, T>::const_iterator index = input.begin();index != input.end();index++) {");
        destination.WriteLine("        result.push_back(index->first);");
        destination.WriteLine("    }");
        destination.WriteLine("    return result;");
        destination.WriteLine("}");
        destination.WriteLine("template<typename T>");
        destination.WriteLine("inline bool HasKV(const std::unordered_map<std::string, T>& input, const std::string& key)");
        destination.WriteLine("{");
        destination.WriteLine("    typename std::unordered_map<std::string, T>::const_iterator beginning = input.find(key);");
        destination.WriteLine("    return beginning != input.end();");
        destination.WriteLine("}");
        destination.WriteLine("template<typename T>");
        destination.WriteLine("inline T GetKV(const std::unordered_map<std::string, T>& input, const std::string& key) { return input.at(key); }");
        destination.WriteLine("inline int Length(const std::string& input) { return (int)input.length(); };");
        destination.WriteLine("inline std::string At(const std::string& input, int index) { return input.substr(index, 1); };");
        destination.WriteLine("inline int IntAt(const std::string& input, int index) { return (input.at(index) + 256) % 256; };");
        destination.WriteLine("inline std::string Concat(const std::string& left, const std::string& right) { return left + right; };");
        destination.WriteLine("#endif");
    }

    public void WriteBeginingGuard(s84.ctcode.system.ctcode.OutputStream file)
    {
        java.lang.String guard_name = this.string_helper.ToUpper(this.string_helper.StripDot(Concat(this.base_name, "_H")));
        file.WriteLine(Concat("#ifndef ", guard_name));
        file.WriteLine(Concat("#define ", guard_name));
    }

    public java.util.ArrayList<java.lang.String> TokenizeBaseName(java.lang.String name)
    {
        java.util.ArrayList<java.lang.String> base_name_tokens = new java.util.ArrayList<>();
        java.lang.String current_token = "";
        int index = 0;
        while (AsBoolean((index<Length(name))))
        {
            java.lang.String character = At(name, index);
            if (AsBoolean(Equals(character,".")))
            {
                Append(base_name_tokens, current_token);
                current_token = "";
            }
            else
            {
                current_token = Concat(current_token, character);
            }
            index = (index+1);
        }
        Append(base_name_tokens, current_token);
        return base_name_tokens;
    }

    public void WriteBeginingNamespace(s84.ctcode.system.ctcode.OutputStream file)
    {
        java.util.ArrayList<java.lang.String> base_name_tokens = this.TokenizeBaseName(this.base_name);
        int base_name_tokens_index = 0;
        while (AsBoolean((base_name_tokens_index<Size(base_name_tokens))))
        {
            java.lang.String base_name_token = Element(base_name_tokens, base_name_tokens_index);
            file.WriteLine(Concat(Concat("namespace ", this.string_helper.ToLower(base_name_token)), " {"));
            base_name_tokens_index = (base_name_tokens_index+1);
        }
    }

    public void WriteEndingNamespace(s84.ctcode.system.ctcode.OutputStream file)
    {
        java.util.ArrayList<java.lang.String> base_name_tokens = this.TokenizeBaseName(this.base_name);
        int base_name_tokens_index = 0;
        while (AsBoolean((base_name_tokens_index<Size(base_name_tokens))))
        {
            java.lang.String base_name_token = Element(base_name_tokens, base_name_tokens_index);
            file.WriteLine("};");
            base_name_tokens_index = (base_name_tokens_index+1);
        }
    }

    public void WriteEndingGuard(s84.ctcode.system.ctcode.OutputStream file)
    {
        file.WriteLine("#endif");
    }

    public void FinishProcessingCTCodeFile()
    {
        java.lang.String header_file_name = Concat(this.base_name, ".hpp");
        s84.ctcode.system.ctcode.OutputStream header_file = this.system.OpenFileWriter(header_file_name);
        java.lang.String source_file_name = Concat(this.base_name, ".cpp");
        s84.ctcode.system.ctcode.OutputStream source_file = this.system.OpenFileWriter(source_file_name);
        this.WriteBeginingGuard(header_file);
        header_file.WriteLine("");
        if (AsBoolean((Size(this.includes)>0)))
        {
            this.string_helper.WriteLines(header_file, this.includes);
            header_file.WriteLine("");
        }
        header_file.WriteLine("#include <cstring>");
        header_file.WriteLine("#include <list>");
        header_file.WriteLine("#include <unordered_map>");
        header_file.WriteLine("#include <memory>");
        header_file.WriteLine("#include <string>");
        header_file.WriteLine("#include <vector>");
        header_file.WriteLine("");
        this.WriteCommonFunctions(header_file);
        header_file.WriteLine("");
        this.WriteBeginingNamespace(header_file);
        header_file.WriteLine("");
        if (AsBoolean((Size(this.interface_declarations)>0)))
        {
            this.string_helper.WriteLines(header_file, this.interface_declarations);
            header_file.WriteLine("");
        }
        if (AsBoolean((Size(this.class_declarations)>0)))
        {
            this.string_helper.WriteLines(header_file, this.class_declarations);
            header_file.WriteLine("");
        }
        if (AsBoolean((Size(this.interface_definitions)>0)))
        {
            this.string_helper.WriteLines(header_file, this.interface_definitions);
        }
        this.string_helper.WriteLines(header_file, this.class_definitions);
        this.WriteEndingNamespace(header_file);
        header_file.WriteLine("");
        this.WriteEndingGuard(header_file);
        source_file.WriteLine(Concat(Concat("#include \"", this.base_name), ".hpp\""));
        source_file.WriteLine("");
        this.WriteBeginingNamespace(source_file);
        source_file.WriteLine("");
        if (AsBoolean((Size(this.function_definitions)>0)))
        {
            this.string_helper.WriteLines(source_file, this.function_definitions);
            source_file.WriteLine("");
        }
        this.WriteEndingNamespace(source_file);
    }

    public java.lang.String GetDefault(java.lang.String cpp_type)
    {
        if (AsBoolean(Equals(cpp_type,"int")))
        {
            return "0";
        }
        if (AsBoolean(Equals(cpp_type,"std::string")))
        {
            return "\"\"";
        }
        if (AsBoolean(Equals(cpp_type,"bool")))
        {
            return "false";
        }
        if (AsBoolean(Equals(cpp_type,"float")))
        {
            return "0.0";
        }
        if (AsBoolean(Equals(cpp_type,"void")))
        {
            return "NULL";
        }
        if (AsBoolean(this.string_helper.BeginsWith("std::unordered_map<std::string, ", cpp_type)))
        {
            return "";
        }
        if (AsBoolean(this.string_helper.BeginsWith("std::vector<", cpp_type)))
        {
            return "";
        }
        return "NULL";
    }

    public java.lang.String MakeParametersString(java.util.ArrayList<s84.ctcode.transpiler.standardstructure.ctcode.ParameterDeclaration> parameters)
    {
        java.lang.String result = "(";
        int parameters_index = 0;
        while (AsBoolean((parameters_index<Size(parameters))))
        {
            s84.ctcode.transpiler.standardstructure.ctcode.ParameterDeclaration parameter = Element(parameters, parameters_index);
            if (AsBoolean(!Equals(parameters_index,0)))
            {
                result = Concat(result, ", ");
            }
            result = Concat(Concat(Concat(result, parameter.GetType()), " "), parameter.GetName());
            parameters_index = (parameters_index+1);
        }
        result = Concat(result, ")");
        return result;
    }

    private s84.ctcode.system.ctcode.System system;
    private s84.ctcode.dbnf.ctcode.CTCodeFile c_t_code_file;
    private java.lang.String base_name;
    private s84.ctcode.system.ctcode.OutputStream logger;
    private s84.ctcode.transpiler.stringhelper.ctcode.StringHelper string_helper;
    private java.util.ArrayList<java.lang.String> includes;
    private java.util.ArrayList<java.lang.String> interface_declarations;
    private java.util.ArrayList<java.lang.String> class_declarations;
    private java.lang.String current_interface;
    private java.util.ArrayList<java.lang.String> interface_definitions;
    private java.lang.String current_class;
    private java.util.ArrayList<java.lang.String> class_definitions;
    private java.util.ArrayList<java.lang.String> class_init;
    private java.util.ArrayList<java.lang.String> class_functions;
    private java.util.ArrayList<java.lang.String> class_members;
    private java.util.ArrayList<java.lang.String> function_definitions;

    private static <T> void ClearList(java.util.ArrayList<T> input) { input.clear(); }
    private static <T> int Size(java.util.ArrayList<T> input) { return input.size(); }
    private static <T> T Element(java.util.ArrayList<T> input, int element) { return input.get(element); }
    private static <T> void Append(java.util.ArrayList<T> input, T element) { input.add(element); }
    private static <T> void ClearMap(java.util.HashMap<java.lang.String, T> input) { input.clear(); }
    private static <T> void SetKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key, T element) { input.put(key, element); }
    private static <T> java.util.ArrayList<java.lang.String> Keys(java.util.HashMap<java.lang.String, T> input) { return new java.util.ArrayList<>(input.keySet()); }
    private static <T> boolean HasKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key) { return input.containsKey(key); }
    private static <T> T GetKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key) { return input.get(key); }
    private static int Length(java.lang.String input) { return input.length(); }
    private static java.lang.String At(java.lang.String input, int index) { try { return input.substring(index, index + 1);} catch(Exception e) { return ""; }}
    private static int IntAt(java.lang.String input, int index) { return (int)input.charAt(index); }
    private static java.lang.String Concat(java.lang.String left, java.lang.String right) { return left + right; }
    private static <T extends Object> boolean AsBoolean(T value) { return value != null; }
    private static boolean AsBoolean(boolean value) { return value; }
    private static boolean Equals(java.lang.String left, java.lang.String right) { return left.equals(right); }
    private static boolean Equals(boolean left, boolean right) { return left == right; }
    private static boolean Equals(int left, int right) { return left == right; }
    private static boolean Equals(float left, float right) { return left == right; }
}
