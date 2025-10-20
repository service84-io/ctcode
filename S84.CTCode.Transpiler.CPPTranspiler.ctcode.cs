namespace S84.CTCode.Transpiler.CPPTranspiler.ctcode;

public class CPPTranspiler : S84.CTCode.Transpiler.StandardStructure.ctcode.TargetSpecificFunctions
{
    private S84.CTCode.System.ctcode.System? system;
    private S84.CTCode.dbnf.ctcode.CTCodeFile? c_t_code_file;
    private string? base_name;
    private S84.CTCode.System.ctcode.OutputStream? logger;
    private S84.CTCode.Transpiler.StringHelper.ctcode.StringHelper? string_helper;
    private List<string?>? includes;
    private List<string?>? interface_declarations;
    private List<string?>? class_declarations;
    private string? current_interface;
    private List<string?>? interface_definitions;
    private string? current_class;
    private List<string?>? class_definitions;
    private List<string?>? class_init;
    private List<string?>? class_functions;
    private List<string?>? class_members;
    private List<string?>? function_definitions;

    public CPPTranspiler()
    {
        this.system = null;
        this.c_t_code_file = null;
        this.base_name = "";
        this.logger = null;
        this.string_helper = null;
        this.includes = new List<string?>();
        this.interface_declarations = new List<string?>();
        this.class_declarations = new List<string?>();
        this.current_interface = "";
        this.interface_definitions = new List<string?>();
        this.current_class = "";
        this.class_definitions = new List<string?>();
        this.class_init = new List<string?>();
        this.class_functions = new List<string?>();
        this.class_members = new List<string?>();
        this.function_definitions = new List<string?>();
    }

    public void Initialize()
    {
        this.string_helper = new S84.CTCode.Transpiler.StringHelper.ctcode.StringHelper();
    }

    public void SetSystem(S84.CTCode.System.ctcode.System? system)
    {
        this.system = system;
    }

    public void SetCTCodeFile(S84.CTCode.dbnf.ctcode.CTCodeFile? c_t_code_file)
    {
        this.c_t_code_file = c_t_code_file;
    }

    public void SetBaseName(string? base_name)
    {
        this.base_name = base_name;
    }

    public void SetLogger(S84.CTCode.System.ctcode.OutputStream? logger)
    {
        this.logger = logger;
    }

    public int? GetBaseIndentation()
    {
        return 0;
    }

    public string? GetCallName(string? name)
    {
        string? value = this?.string_helper?.SnakeCaseToCamelCase(name);
        if (AsBoolean(this?.string_helper?.IsReserved(value)))
        {
            return Concat("ReservedPrefix",value);
        }
        return value;
    }

    public string? GetVariableName(string? name)
    {
        string? value = this?.string_helper?.CamelCaseToSnakeCase(name);
        if (AsBoolean(value=="myself"))
        {
            return "this";
        }
        if (AsBoolean(value=="nothing"))
        {
            return "NULL";
        }
        if (AsBoolean(this?.string_helper?.IsReserved(value)))
        {
            return Concat("reserved_prefix_",value);
        }
        return value;
    }

    public string? GetVariableChain(List<string?>? name_parts)
    {
        string? delimiter = "->";
        string? first_name = Element(name_parts,0);
        string? result = this?.GetVariableName(first_name);
        int? name_parts_index = 1;
        while (AsBoolean(name_parts_index<Size(name_parts)))
        {
            string? name = Element(name_parts,name_parts_index);
            result = Concat(Concat(result,delimiter),this?.GetVariableName(name));
            name_parts_index = name_parts_index+1;
        }
        return result;
    }

    public string? ConvertCall(List<string?>? name_chain,List<string?>? parameters)
    {
        string? result = Element(name_chain,0);
        int? name_chain_index = 1;
        while (AsBoolean(name_chain_index<Size(name_chain)))
        {
            string? name_part = Element(name_chain,name_chain_index);
            result = Concat(Concat(result,"->"),name_part);
            name_chain_index = name_chain_index+1;
        }
        result = Concat(result,"(");
        if (AsBoolean(Size(parameters)>0))
        {
            result = Concat(result,Element(parameters,0));
            int? parameters_index = 1;
            while (AsBoolean(parameters_index<Size(parameters)))
            {
                string? parameter = Element(parameters,parameters_index);
                result = Concat(result,",");
                result = Concat(result,parameter);
                parameters_index = parameters_index+1;
            }
        }
        result = Concat(result,")");
        return result;
    }

    public string? ConvertAllocate(string? type)
    {
        return Concat(Concat(Concat(Concat("std::shared_ptr<",type),">(new "),type),"())");
    }

    public string? ConvertByte(string? high,string? low)
    {
        return Concat(Concat("0x",high),low);
    }

    public string? ConvertDecimal(string? reserved_prefix_decimal)
    {
        return reserved_prefix_decimal;
    }

    public string? ConvertNumber(string? number)
    {
        return number;
    }

    public string? ConvertBoolean(string? reserved_prefix_boolean)
    {
        if (AsBoolean(reserved_prefix_boolean=="true"))
        {
            return "true";
        }
        if (AsBoolean(reserved_prefix_boolean=="false"))
        {
            return "false";
        }
        return "";
    }

    public string? ConvertVariable(string? variable)
    {
        return variable;
    }

    public string? ConvertString(string? literal)
    {
        return Concat(Concat("std::string(\"",literal),"\")");
    }

    public string? UnaryOperator(string? op,string? r_value)
    {
        if (AsBoolean(op=="!"))
        {
            return Concat("!",r_value);
        }
        return r_value;
    }

    public string? BinaryOperator(string? op,string? r_value_l,string? r_value_r)
    {
        if (AsBoolean(op=="+"))
        {
            return Concat(Concat(r_value_l,"+"),r_value_r);
        }
        if (AsBoolean(op=="-"))
        {
            return Concat(Concat(r_value_l,"-"),r_value_r);
        }
        if (AsBoolean(op=="<="))
        {
            return Concat(Concat(r_value_l,"<="),r_value_r);
        }
        if (AsBoolean(op==">="))
        {
            return Concat(Concat(r_value_l,">="),r_value_r);
        }
        if (AsBoolean(op=="=="))
        {
            return Concat(Concat(r_value_l,"=="),r_value_r);
        }
        if (AsBoolean(op=="!="))
        {
            return Concat(Concat(r_value_l,"!="),r_value_r);
        }
        if (AsBoolean(op=="<"))
        {
            return Concat(Concat(r_value_l,"<"),r_value_r);
        }
        if (AsBoolean(op==">"))
        {
            return Concat(Concat(r_value_l,">"),r_value_r);
        }
        if (AsBoolean(op=="||"))
        {
            return Concat(Concat(r_value_l,"||"),r_value_r);
        }
        if (AsBoolean(op=="&&"))
        {
            return Concat(Concat(r_value_l,"&&"),r_value_r);
        }
        return "";
    }

    public string? GetTypeName(string? name)
    {
        string? value = this?.string_helper?.SnakeCaseToCamelCase(name);
        if (AsBoolean(this?.string_helper?.IsReserved(value)))
        {
            return Concat("ReservedPrefix",value);
        }
        return value;
    }

    public string? GetDimensionalType(string? singleton_type,int? dimensions)
    {
        string? result = singleton_type;
        while (AsBoolean(dimensions>0))
        {
            result = Concat(Concat("std::vector<",result),">");
            dimensions = dimensions-1;
        }
        return result;
    }

    public string? GetMapType(string? singleton_type)
    {
        return Concat(Concat("std::unordered_map<std::string, ",singleton_type),">");
    }

    public string? GetPrimativeType(string? c_t_type)
    {
        if (AsBoolean(c_t_type=="int"))
        {
            return "int";
        }
        if (AsBoolean(c_t_type=="string"))
        {
            return "std::string";
        }
        if (AsBoolean(c_t_type=="bool"))
        {
            return "bool";
        }
        if (AsBoolean(c_t_type=="float"))
        {
            return "float";
        }
        if (AsBoolean(c_t_type=="void"))
        {
            return "void";
        }
        return "";
    }

    public string? GetDefinedType(string? c_t_type)
    {
        return Concat(Concat("OmniPointer<",c_t_type),">");
    }

    public string? GetQualifiedTypeName(List<string?>? name_parts)
    {
        string? delimiter = "::";
        int? name_parts_index = Size(name_parts)-1;
        string? type_part = Element(name_parts,name_parts_index);
        string? result = this?.GetTypeName(type_part);
        if (AsBoolean(name_parts_index>0))
        {
            while (AsBoolean(name_parts_index>0))
            {
                name_parts_index = name_parts_index-1;
                result = Concat(delimiter,result);
                string? name_part = Element(name_parts,name_parts_index);
                result = Concat(this?.string_helper?.ToLower(name_part),result);
            }
        }
        return result;
    }

    public void BeginProcessingCTCodeFile()
    {
        ClearList(this?.includes);
        ClearList(this?.interface_declarations);
        ClearList(this?.class_declarations);
        this.current_interface = "";
        ClearList(this?.interface_definitions);
        this.current_class = "";
        ClearList(this?.class_definitions);
        ClearList(this?.class_init);
        ClearList(this?.class_functions);
        ClearList(this?.class_members);
        ClearList(this?.function_definitions);
    }

    public void ProcessExdef(string? exdef)
    {
        Append(this?.includes,Concat("#include \"",Concat(exdef,".hpp\"")));
    }

    public void ProcessUnmanagedType(string? unmanaged_type)
    {
    }

    public void BeginProcessingInterface(string? interface_name)
    {
        this.current_interface = interface_name;
        Append(this?.interface_declarations,Concat(Concat("class ",interface_name),";"));
        Append(this?.interface_definitions,Concat(Concat("class ",interface_name)," {"));
        Append(this?.interface_definitions,"public:");
    }

    public void ProcessInterfaceFunctionDeclaration(string? return_type,string? function_name,List<S84.CTCode.Transpiler.StandardStructure.ctcode.ParameterDeclaration?>? parameters)
    {
        Append(this?.interface_definitions,Concat(Concat(Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(1),"virtual "),return_type)," "),function_name),this?.MakeParametersString(parameters))," = 0;"));
    }

    public void FinishProcessingInterface(string? interface_name)
    {
        Append(this?.interface_definitions,"};");
        Append(this?.interface_definitions,"");
        this.current_interface = "";
    }

    public void BeginProcessingClass(string? class_name,string? implementing)
    {
        this.current_class = class_name;
        Append(this?.class_declarations,Concat(Concat("class ",class_name),";"));
        if (AsBoolean(implementing==""))
        {
            Append(this?.class_definitions,Concat(Concat("class ",class_name)," {"));
        }
        else
        {
            Append(this?.class_definitions,Concat(Concat(Concat(Concat("class ",class_name)," : public "),implementing)," {"));
        }
        Append(this?.class_definitions,"public:");
        Append(this?.class_definitions,Concat(Concat(this?.string_helper?.Indentation(1),class_name),"();"));
        Append(this?.class_definitions,Concat(Concat(Concat(this?.string_helper?.Indentation(1),"inline ~"),class_name),"() {}"));
        Append(this?.class_definitions,"");
        ClearList(this?.class_init);
        ClearList(this?.class_functions);
        ClearList(this?.class_members);
        Append(this?.class_init,Concat(Concat(Concat(class_name,"::"),class_name),"()"));
        Append(this?.class_init,"{");
    }

    public void BeginProcessingClassFunctionDefinition(string? return_type,string? function_name,List<S84.CTCode.Transpiler.StandardStructure.ctcode.ParameterDeclaration?>? parameters)
    {
        Append(this?.class_definitions,Concat(Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(1),return_type)," "),function_name),this?.MakeParametersString(parameters)),";"));
        Append(this?.class_functions,Concat(Concat(Concat(Concat(Concat(return_type," "),this?.current_class),"::"),function_name),this?.MakeParametersString(parameters)));
    }

    public void BeginProcessCodeBlock(int? indent)
    {
        Append(this?.class_functions,Concat(this?.string_helper?.Indentation(indent),"{"));
    }

    public void FinishProcessCodeBlock(int? indent)
    {
        Append(this?.class_functions,Concat(this?.string_helper?.Indentation(indent),"}"));
    }

    public void BeginProcessConditional(int? indent,string? r_value)
    {
        Append(this?.class_functions,Concat(Concat(Concat(this?.string_helper?.Indentation(indent),"if ("),r_value),")"));
    }

    public void ProcessElse(int? indent)
    {
        Append(this?.class_functions,Concat(this?.string_helper?.Indentation(indent),"else"));
    }

    public void FinishProcessConditional(int? indent,string? r_value)
    {
    }

    public void BeginProcessLoop(int? indent,string? r_value)
    {
        Append(this?.class_functions,Concat(Concat(Concat(this?.string_helper?.Indentation(indent),"while ("),r_value),")"));
    }

    public void FinishProcessLoop(int? indent,string? r_value)
    {
    }

    public void ProcessRtn(int? indent,string? r_value)
    {
        Append(this?.class_functions,Concat(Concat(Concat(this?.string_helper?.Indentation(indent),"return "),r_value),";"));
    }

    public void ProcessDeclaration(int? indent,string? type,string? l_value,string? r_value)
    {
        if (AsBoolean(r_value==""))
        {
            r_value = this?.GetDefault(type);
        }
        if (AsBoolean(r_value==""))
        {
            Append(this?.class_functions,Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(indent),type)," "),l_value),";"));
        }
        else
        {
            Append(this?.class_functions,Concat(Concat(Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(indent),type)," "),l_value)," = "),r_value),";"));
        }
    }

    public void ProcessAssignment(int? indent,string? l_value,string? r_value)
    {
        Append(this?.class_functions,Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(indent),l_value)," = "),r_value),";"));
    }

    public void ProcessCall(int? indent,string? call)
    {
        Append(this?.class_functions,Concat(Concat(this?.string_helper?.Indentation(indent),call),";"));
    }

    public void FinishProcessingClassFunctionDefinition(string? return_type,string? function_name,List<S84.CTCode.Transpiler.StandardStructure.ctcode.ParameterDeclaration?>? parameters)
    {
        Append(this?.class_functions,"");
    }

    public void ProcessClassMemberDeclaration(string? member_type,string? member_name)
    {
        string? default_value = this?.GetDefault(member_type);
        if (AsBoolean(default_value!=""))
        {
            Append(this?.class_init,Concat(Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(1),"this->"),member_name)," = "),default_value),";"));
        }
        else
        {
            Append(this?.class_init,Concat(Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(1),"/*this->"),member_name)," = "),"NO_DEFAULT"),";*/"));
        }
        Append(this?.class_members,Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(1),member_type)," "),member_name),";"));
    }

    public void FinishProcessingClass(string? class_name,string? implementing)
    {
        if (AsBoolean(Size(this?.class_members)>0))
        {
            Append(this?.class_definitions,"");
            Append(this?.class_definitions,"private:");
            int? class_members_index = 0;
            while (AsBoolean(class_members_index<Size(this?.class_members)))
            {
                string? line = Element(this?.class_members,class_members_index);
                Append(this?.class_definitions,line);
                class_members_index = class_members_index+1;
            }
        }
        Append(this?.class_definitions,"};");
        Append(this?.class_definitions,"");
        Append(this?.class_init,"}");
        Append(this?.class_init,"");
        int? class_init_index = 0;
        while (AsBoolean(class_init_index<Size(this?.class_init)))
        {
            string? line = Element(this?.class_init,class_init_index);
            Append(this?.function_definitions,line);
            class_init_index = class_init_index+1;
        }
        int? class_functions_index = 0;
        while (AsBoolean(class_functions_index<Size(this?.class_functions)))
        {
            string? line = Element(this?.class_functions,class_functions_index);
            Append(this?.function_definitions,line);
            class_functions_index = class_functions_index+1;
        }
        this.current_class = "";
    }

    public void WriteCommonFunctions(S84.CTCode.System.ctcode.OutputStream? destination)
    {
        destination?.WriteLine("#ifndef CTCODE_COMMON_FUNCTIONS_VERSION_1");
        destination?.WriteLine("#define CTCODE_COMMON_FUNCTIONS_VERSION_1");
        destination?.WriteLine("template<typename T>");
        destination?.WriteLine("class OmniPointer");
        destination?.WriteLine("{");
        destination?.WriteLine("public:");
        destination?.WriteLine("    OmniPointer() { value_raw = NULL; }");
        destination?.WriteLine("    OmniPointer(T* value) { value_raw = value; }");
        destination?.WriteLine("    template<typename U>");
        destination?.WriteLine("    OmniPointer(U* value) { value_raw = value; }");
        destination?.WriteLine("    OmniPointer(std::shared_ptr<T> value) { value_raw = NULL; value_shared = value; }");
        destination?.WriteLine("    template<typename U>");
        destination?.WriteLine("    OmniPointer(std::shared_ptr<U> value) { value_raw = NULL; value_shared = value; }");
        destination?.WriteLine("    template<typename U>");
        destination?.WriteLine("    OmniPointer(OmniPointer<U> value) { value_raw = value.value_raw; value_shared = value.value_shared; }");
        destination?.WriteLine("");
        destination?.WriteLine("    operator bool()");
        destination?.WriteLine("    {");
        destination?.WriteLine("        if (value_raw) return true;");
        destination?.WriteLine("        return value_shared.get() != NULL;");
        destination?.WriteLine("    }");
        destination?.WriteLine("    T& operator*()");
        destination?.WriteLine("    {");
        destination?.WriteLine("        if (value_raw) return *value_raw;");
        destination?.WriteLine("        return *value_shared;");
        destination?.WriteLine("    }");
        destination?.WriteLine("    T* operator->()");
        destination?.WriteLine("    {");
        destination?.WriteLine("        if (value_raw) return value_raw;");
        destination?.WriteLine("        return value_shared.get();");
        destination?.WriteLine("    }");
        destination?.WriteLine("    T* raw()");
        destination?.WriteLine("    {");
        destination?.WriteLine("        if (value_raw) return value_raw;");
        destination?.WriteLine("        return value_shared.get();");
        destination?.WriteLine("    }");
        destination?.WriteLine("");
        destination?.WriteLine("    T* value_raw;");
        destination?.WriteLine("    std::shared_ptr<T> value_shared;");
        destination?.WriteLine("};");
        destination?.WriteLine("");
        destination?.WriteLine("template<typename T>");
        destination?.WriteLine("inline std::vector<T*> UnwrapOmniList(std::vector<OmniPointer<T>> input) {");
        destination?.WriteLine("	std::vector<T*> result;");
        destination?.WriteLine("	for (typename std::vector<OmniPointer<T>>::iterator index = input.begin();index != input.end();index++) {");
        destination?.WriteLine("		result.push_back(index->raw());");
        destination?.WriteLine("	}");
        destination?.WriteLine("	return result;");
        destination?.WriteLine("};");
        destination?.WriteLine("template<typename T>");
        destination?.WriteLine("inline void ClearList(std::vector<T>& input) { input.clear(); };");
        destination?.WriteLine("template<typename T>");
        destination?.WriteLine("inline int Size(const std::vector<T>& input) { return input.size(); };");
        destination?.WriteLine("template<typename T>");
        destination?.WriteLine("inline T Element(const std::vector<T>& input, int element) { return input.at(element); };");
        destination?.WriteLine("template<typename T>");
        destination?.WriteLine("inline void Append(std::vector<T>& input, T element) { input.push_back(element); };");
        destination?.WriteLine("template<typename T>");
        destination?.WriteLine("inline void ClearMap(std::unordered_map<std::string, T>& input) { input.clear(); };");
        destination?.WriteLine("template<typename T>");
        destination?.WriteLine("inline void SetKV(std::unordered_map<std::string, T>& input, const std::string& key, T element)");
        destination?.WriteLine("{");
        destination?.WriteLine("    input.erase(key);");
        destination?.WriteLine("    input.insert(std::pair<std::string, T>(key, element));");
        destination?.WriteLine("}");
        destination?.WriteLine("template<typename T>");
        destination?.WriteLine("inline std::vector<std::string> Keys(const std::unordered_map<std::string, T>& input)");
        destination?.WriteLine("{");
        destination?.WriteLine("    std::vector<std::string> result;");
        destination?.WriteLine("    for(typename std::unordered_map<std::string, T>::const_iterator index = input.begin();index != input.end();index++) {");
        destination?.WriteLine("        result.push_back(index->first);");
        destination?.WriteLine("    }");
        destination?.WriteLine("    return result;");
        destination?.WriteLine("}");
        destination?.WriteLine("template<typename T>");
        destination?.WriteLine("inline bool HasKV(const std::unordered_map<std::string, T>& input, const std::string& key)");
        destination?.WriteLine("{");
        destination?.WriteLine("    typename std::unordered_map<std::string, T>::const_iterator beginning = input.find(key);");
        destination?.WriteLine("    return beginning != input.end();");
        destination?.WriteLine("}");
        destination?.WriteLine("template<typename T>");
        destination?.WriteLine("inline T GetKV(const std::unordered_map<std::string, T>& input, const std::string& key) { return input.at(key); }");
        destination?.WriteLine("inline int Length(const std::string& input) { return (int)input.length(); };");
        destination?.WriteLine("inline std::string At(const std::string& input, int index) { return input.substr(index, 1); };");
        destination?.WriteLine("inline int IntAt(const std::string& input, int index) { return (input.at(index) + 256) % 256; };");
        destination?.WriteLine("inline std::string Concat(const std::string& left, const std::string& right) { return left + right; };");
        destination?.WriteLine("#endif");
    }

    public void WriteBeginingGuard(S84.CTCode.System.ctcode.OutputStream? file)
    {
        string? guard_name = this?.string_helper?.ToUpper(this?.string_helper?.StripDot(Concat(this?.base_name,"_H")));
        file?.WriteLine(Concat("#ifndef ",guard_name));
        file?.WriteLine(Concat("#define ",guard_name));
    }

    public List<string?>? TokenizeBaseName(string? name)
    {
        List<string?>? base_name_tokens = new List<string?>();
        string? current_token = "";
        int? index = 0;
        while (AsBoolean(index<Length(name)))
        {
            string? character = At(name,index);
            if (AsBoolean(character=="."))
            {
                Append(base_name_tokens,current_token);
                current_token = "";
            }
            else
            {
                current_token = Concat(current_token,character);
            }
            index = index+1;
        }
        Append(base_name_tokens,current_token);
        return base_name_tokens;
    }

    public void WriteBeginingNamespace(S84.CTCode.System.ctcode.OutputStream? file)
    {
        List<string?>? base_name_tokens = this?.TokenizeBaseName(this?.base_name);
        int? base_name_tokens_index = 0;
        while (AsBoolean(base_name_tokens_index<Size(base_name_tokens)))
        {
            string? base_name_token = Element(base_name_tokens,base_name_tokens_index);
            file?.WriteLine(Concat(Concat("namespace ",this?.string_helper?.ToLower(base_name_token))," {"));
            base_name_tokens_index = base_name_tokens_index+1;
        }
    }

    public void WriteEndingNamespace(S84.CTCode.System.ctcode.OutputStream? file)
    {
        List<string?>? base_name_tokens = this?.TokenizeBaseName(this?.base_name);
        int? base_name_tokens_index = 0;
        while (AsBoolean(base_name_tokens_index<Size(base_name_tokens)))
        {
            string? base_name_token = Element(base_name_tokens,base_name_tokens_index);
            file?.WriteLine("};");
            base_name_tokens_index = base_name_tokens_index+1;
        }
    }

    public void WriteEndingGuard(S84.CTCode.System.ctcode.OutputStream? file)
    {
        file?.WriteLine("#endif");
    }

    public void FinishProcessingCTCodeFile()
    {
        string? header_file_name = Concat(this?.base_name,".hpp");
        S84.CTCode.System.ctcode.OutputStream? header_file = this?.system?.OpenFileWriter(header_file_name);
        string? source_file_name = Concat(this?.base_name,".cpp");
        S84.CTCode.System.ctcode.OutputStream? source_file = this?.system?.OpenFileWriter(source_file_name);
        this?.WriteBeginingGuard(header_file);
        header_file?.WriteLine("");
        if (AsBoolean(Size(this?.includes)>0))
        {
            this?.string_helper?.WriteLines(header_file,this?.includes);
            header_file?.WriteLine("");
        }
        header_file?.WriteLine("#include <cstring>");
        header_file?.WriteLine("#include <list>");
        header_file?.WriteLine("#include <unordered_map>");
        header_file?.WriteLine("#include <memory>");
        header_file?.WriteLine("#include <string>");
        header_file?.WriteLine("#include <vector>");
        header_file?.WriteLine("");
        this?.WriteCommonFunctions(header_file);
        header_file?.WriteLine("");
        this?.WriteBeginingNamespace(header_file);
        header_file?.WriteLine("");
        if (AsBoolean(Size(this?.interface_declarations)>0))
        {
            this?.string_helper?.WriteLines(header_file,this?.interface_declarations);
            header_file?.WriteLine("");
        }
        if (AsBoolean(Size(this?.class_declarations)>0))
        {
            this?.string_helper?.WriteLines(header_file,this?.class_declarations);
            header_file?.WriteLine("");
        }
        if (AsBoolean(Size(this?.interface_definitions)>0))
        {
            this?.string_helper?.WriteLines(header_file,this?.interface_definitions);
        }
        this?.string_helper?.WriteLines(header_file,this?.class_definitions);
        this?.WriteEndingNamespace(header_file);
        header_file?.WriteLine("");
        this?.WriteEndingGuard(header_file);
        source_file?.WriteLine(Concat(Concat("#include \"",this?.base_name),".hpp\""));
        source_file?.WriteLine("");
        this?.WriteBeginingNamespace(source_file);
        source_file?.WriteLine("");
        if (AsBoolean(Size(this?.function_definitions)>0))
        {
            this?.string_helper?.WriteLines(source_file,this?.function_definitions);
            source_file?.WriteLine("");
        }
        this?.WriteEndingNamespace(source_file);
    }

    public string? GetDefault(string? cpp_type)
    {
        if (AsBoolean(cpp_type=="int"))
        {
            return "0";
        }
        if (AsBoolean(cpp_type=="std::string"))
        {
            return "\"\"";
        }
        if (AsBoolean(cpp_type=="bool"))
        {
            return "false";
        }
        if (AsBoolean(cpp_type=="float"))
        {
            return "0.0";
        }
        if (AsBoolean(cpp_type=="void"))
        {
            return "NULL";
        }
        if (AsBoolean(this?.string_helper?.BeginsWith("std::unordered_map<std::string, ",cpp_type)))
        {
            return "";
        }
        if (AsBoolean(this?.string_helper?.BeginsWith("std::vector<",cpp_type)))
        {
            return "";
        }
        return "NULL";
    }

    public string? MakeParametersString(List<S84.CTCode.Transpiler.StandardStructure.ctcode.ParameterDeclaration?>? parameters)
    {
        string? result = "(";
        int? parameters_index = 0;
        while (AsBoolean(parameters_index<Size(parameters)))
        {
            S84.CTCode.Transpiler.StandardStructure.ctcode.ParameterDeclaration? parameter = Element(parameters,parameters_index);
            if (AsBoolean(parameters_index!=0))
            {
                result = Concat(result,", ");
            }
            result = Concat(Concat(Concat(result,parameter?.ReservedPrefixGetType())," "),parameter?.GetName());
            parameters_index = parameters_index+1;
        }
        result = Concat(result,")");
        return result;
    }

    private static void ClearList<T>(List<T>? input) { input?.Clear(); }
    private static int? Size<T>(List<T>? input) { return input?.Count; }
    private static T? Element<T>(List<T>? input, int? element) { return input != null ? input[element??0] : default; }
    private static void Append<T>(List<T>? input, T element) { input?.Add(element); }
    private static void ClearMap<T>(Dictionary<string, T>? input) { input?.Clear();  }
    private static void SetKV<T>(Dictionary<string, T>? input, string? key, T element) { input?.Add(key??"", element); }
    private static List<string?>? Keys<T>(Dictionary<string, T>? input) { return new List<string?>(input?.Keys?.ToList()??new List<string>()); }
    private static bool? HasKV<T>(Dictionary<string, T>? input, string? key) { return input?.ContainsKey(key??""); }
    private static T? GetKV<T>(Dictionary<string, T>? input, string? key) { return input != null ? input[key??""] : default; }
    private static int? Length(string? input) { return input?.Length;  }
    private static string? At(string? input, int? index) { return input?.Length > index ? input?.Substring(index??0, 1) : "";  }
    private static int? IntAt(string? input, int? index) { return input?.Length > index ? (input[index??0] + 255 % 255) : 0;  }
    private static string? Concat(string? left, string? right) { return left + right; }
    private static bool AsBoolean(bool value) { return value; }
    private static bool AsBoolean<T>(T? value) { return value != null && !value.Equals(false); }
}
