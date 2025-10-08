namespace S84.CTCode.Transpiler.Java11Transpiler.ctcode;

public class Java11Transpiler : S84.CTCode.Transpiler.StandardStructure.ctcode.TargetSpecificFunctions
{
    private S84.CTCode.System.ctcode.System? system;
    private S84.CTCode.dbnf.ctcode.CTCodeFile? c_t_code_file;
    private string? base_name;
    private S84.CTCode.System.ctcode.OutputStream? logger;
    private S84.CTCode.Transpiler.StringHelper.ctcode.StringHelper? string_helper;
    private List<string?>? imports;
    private string? current_interface;
    private List<string?>? interface_definition;
    private string? current_class;
    private List<string?>? class_definition;
    private List<string?>? class_init;
    private List<string?>? class_members;

    public Java11Transpiler()
    {
        this.system = null;
        this.c_t_code_file = null;
        this.base_name = "";
        this.logger = null;
        this.string_helper = null;
        this.imports = new List<string?>();
        this.current_interface = "";
        this.interface_definition = new List<string?>();
        this.current_class = "";
        this.class_definition = new List<string?>();
        this.class_init = new List<string?>();
        this.class_members = new List<string?>();
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
        return 1;
    }

    public string? GetCallName(string? name)
    {
        return this?.string_helper?.SnakeCaseToCamelCase(name);
    }

    public bool? IsReserved(string? name)
    {
        return AsBoolean(AsBoolean(AsBoolean(AsBoolean(false)||AsBoolean(this?.string_helper?.BeginsWith("reserved_prefix_",name)))||AsBoolean(name=="boolean"))||AsBoolean(name=="char"))||AsBoolean(name=="float");
    }

    public string? GetVariableName(string? name)
    {
        string? value = this?.string_helper?.CamelCaseToSnakeCase(name);
        if (AsBoolean(value=="myself"))
        {
            return "this";
        }
        if (AsBoolean(this?.IsReserved(value)))
        {
            return Concat("reserved_prefix_",value);
        }
        return value;
    }

    public string? GetVariableChain(List<string?>? name_parts)
    {
        string? delimiter = ".";
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
            result = Concat(Concat(result,"."),name_part);
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
                result = Concat(result,", ");
                result = Concat(result,parameter);
                parameters_index = parameters_index+1;
            }
        }
        result = Concat(result,")");
        return result;
    }

    public string? ConvertAllocate(string? type)
    {
        return Concat(Concat("new ",type),"()");
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
        return Concat(Concat("\"",literal),"\"");
    }

    public string? UnaryOperator(string? op,string? r_value)
    {
        if (AsBoolean(op=="!"))
        {
            return Concat(Concat("(! AsBoolean(",r_value),"))");
        }
        return r_value;
    }

    public string? BinaryOperator(string? op,string? r_value_l,string? r_value_r)
    {
        if (AsBoolean(op=="+"))
        {
            return Concat(Concat(Concat(Concat("(",r_value_l),"+"),r_value_r),")");
        }
        if (AsBoolean(op=="-"))
        {
            return Concat(Concat(Concat(Concat("(",r_value_l),"-"),r_value_r),")");
        }
        if (AsBoolean(op=="<="))
        {
            return Concat(Concat(Concat(Concat("(",r_value_l),"<="),r_value_r),")");
        }
        if (AsBoolean(op==">="))
        {
            return Concat(Concat(Concat(Concat("(",r_value_l),">="),r_value_r),")");
        }
        if (AsBoolean(op=="=="))
        {
            return Concat(Concat(Concat(Concat("Equals(",r_value_l),","),r_value_r),")");
        }
        if (AsBoolean(op=="!="))
        {
            return Concat(Concat(Concat(Concat("!Equals(",r_value_l),","),r_value_r),")");
        }
        if (AsBoolean(op=="<"))
        {
            return Concat(Concat(Concat(Concat("(",r_value_l),"<"),r_value_r),")");
        }
        if (AsBoolean(op==">"))
        {
            return Concat(Concat(Concat(Concat("(",r_value_l),">"),r_value_r),")");
        }
        if (AsBoolean(op=="||"))
        {
            return Concat(Concat(Concat(Concat("(AsBoolean(",r_value_l),") || AsBoolean("),r_value_r),"))");
        }
        if (AsBoolean(op=="&&"))
        {
            return Concat(Concat(Concat(Concat("(AsBoolean(",r_value_l),") && AsBoolean("),r_value_r),"))");
        }
        return "";
    }

    public string? GetTypeName(string? name)
    {
        return this?.string_helper?.SnakeCaseToCamelCase(name);
    }

    public string? GetDimensionalType(string? singleton_type,int? dimensions)
    {
        string? result = singleton_type;
        while (AsBoolean(dimensions>0))
        {
            result = Concat(Concat("java.util.ArrayList<",result),">");
            dimensions = dimensions-1;
        }
        return result;
    }

    public string? GetMapType(string? singleton_type)
    {
        return Concat(Concat("java.util.HashMap<java.lang.String, ",singleton_type),">");
    }

    public string? GetPrimativeType(string? c_t_type)
    {
        if (AsBoolean(c_t_type=="int"))
        {
            return "int";
        }
        if (AsBoolean(c_t_type=="string"))
        {
            return "java.lang.String";
        }
        if (AsBoolean(c_t_type=="bool"))
        {
            return "boolean";
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
        return c_t_type;
    }

    public string? GetQualifiedTypeName(List<string?>? name_parts)
    {
        string? delimiter = ".";
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
        ClearList(this?.imports);
        this.current_interface = "";
        ClearList(this?.interface_definition);
        this.current_class = "";
        ClearList(this?.class_definition);
        ClearList(this?.class_init);
        ClearList(this?.class_members);
    }

    public void ProcessExdef(string? exdef)
    {
        Append(this?.imports,Concat(Concat("import ",this?.string_helper?.ToLower(exdef)),".*;"));
    }

    public void ProcessUnmanagedType(string? unmanaged_type)
    {
    }

    public void BeginProcessingInterface(string? interface_name)
    {
        ClearList(this?.interface_definition);
        this.current_interface = interface_name;
    }

    public void ProcessInterfaceFunctionDeclaration(string? return_type,string? function_name,List<S84.CTCode.Transpiler.StandardStructure.ctcode.ParameterDeclaration?>? parameters)
    {
        Append(this?.interface_definition,Concat(Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(1),return_type)," "),function_name),this?.MakeParametersString(parameters)),";"));
    }

    public void FinishProcessingInterface(string? interface_name)
    {
        S84.CTCode.System.ctcode.OutputStream? destination = this?.system?.OpenFileWriter(Concat(Concat(Concat(this?.string_helper?.DotToSlash(this?.string_helper?.ToLower(this?.base_name)),"/"),this?.current_interface),".java"));
        destination?.WriteLine(Concat(Concat("package ",this?.string_helper?.ToLower(this?.base_name)),";"));
        destination?.WriteLine("");
        if (AsBoolean(Size(this?.imports)>0))
        {
            this?.string_helper?.WriteLines(destination,this?.imports);
            destination?.WriteLine("");
        }
        destination?.WriteLine(Concat(Concat("public interface ",interface_name)," {"));
        this?.string_helper?.WriteLines(destination,this?.interface_definition);
        destination?.WriteLine("}");
        this.current_interface = "";
    }

    public void BeginProcessingClass(string? class_name,string? implementing)
    {
        ClearList(this?.class_definition);
        ClearList(this?.class_init);
        ClearList(this?.class_members);
        this.current_class = class_name;
        Append(this?.class_init,Concat(Concat(Concat(this?.string_helper?.Indentation(1),"public "),class_name),"()"));
        Append(this?.class_init,Concat(this?.string_helper?.Indentation(1),"{"));
    }

    public void BeginProcessingClassFunctionDefinition(string? return_type,string? function_name,List<S84.CTCode.Transpiler.StandardStructure.ctcode.ParameterDeclaration?>? parameters)
    {
        Append(this?.class_definition,Concat(Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(1),"public "),return_type)," "),function_name),this?.MakeParametersString(parameters)));
    }

    public void BeginProcessCodeBlock(int? indent)
    {
        Append(this?.class_definition,Concat(this?.string_helper?.Indentation(indent),"{"));
    }

    public void FinishProcessCodeBlock(int? indent)
    {
        Append(this?.class_definition,Concat(this?.string_helper?.Indentation(indent),"}"));
    }

    public void BeginProcessConditional(int? indent,string? r_value)
    {
        Append(this?.class_definition,Concat(Concat(Concat(this?.string_helper?.Indentation(indent),"if (AsBoolean("),r_value),"))"));
    }

    public void ProcessElse(int? indent)
    {
        Append(this?.class_definition,Concat(this?.string_helper?.Indentation(indent),"else"));
    }

    public void FinishProcessConditional(int? indent,string? r_value)
    {
    }

    public void BeginProcessLoop(int? indent,string? r_value)
    {
        Append(this?.class_definition,Concat(Concat(Concat(this?.string_helper?.Indentation(indent),"while (AsBoolean("),r_value),"))"));
    }

    public void FinishProcessLoop(int? indent,string? r_value)
    {
    }

    public void ProcessRtn(int? indent,string? r_value)
    {
        Append(this?.class_definition,Concat(Concat(Concat(this?.string_helper?.Indentation(indent),"return "),r_value),";"));
    }

    public void ProcessDeclaration(int? indent,string? type,string? l_value,string? r_value)
    {
        if (AsBoolean(r_value==""))
        {
            r_value = this?.GetDefault(type);
        }
        Append(this?.class_definition,Concat(Concat(Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(indent),type)," "),l_value)," = "),r_value),";"));
    }

    public void ProcessAssignment(int? indent,string? l_value,string? r_value)
    {
        Append(this?.class_definition,Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(indent),l_value)," = "),r_value),";"));
    }

    public void ProcessCall(int? indent,string? call)
    {
        Append(this?.class_definition,Concat(Concat(this?.string_helper?.Indentation(indent),call),";"));
    }

    public void FinishProcessingClassFunctionDefinition(string? return_type,string? function_name,List<S84.CTCode.Transpiler.StandardStructure.ctcode.ParameterDeclaration?>? parameters)
    {
        Append(this?.class_definition,"");
    }

    public void ProcessClassMemberDeclaration(string? member_type,string? member_name)
    {
        Append(this?.class_init,Concat(Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(2),"this."),member_name)," = "),this?.GetDefault(member_type)),";"));
        Append(this?.class_members,Concat(Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(1),"private "),member_type)," "),member_name),";"));
    }

    public void FinishProcessingClass(string? class_name,string? implementing)
    {
        S84.CTCode.System.ctcode.OutputStream? destination = this?.system?.OpenFileWriter(Concat(Concat(Concat(this?.string_helper?.DotToSlash(this?.string_helper?.ToLower(this?.base_name)),"/"),this?.current_class),".java"));
        destination?.WriteLine(Concat(Concat("package ",this?.string_helper?.ToLower(this?.base_name)),";"));
        destination?.WriteLine("");
        if (AsBoolean(Size(this?.imports)>0))
        {
            this?.string_helper?.WriteLines(destination,this?.imports);
            destination?.WriteLine("");
        }
        if (AsBoolean(implementing==""))
        {
            destination?.WriteLine(Concat(Concat("public class ",class_name)," {"));
        }
        else
        {
            destination?.WriteLine(Concat(Concat(Concat(Concat("public class ",class_name)," implements "),implementing)," {"));
        }
        this?.string_helper?.WriteLines(destination,this?.class_init);
        destination?.WriteLine(Concat(this?.string_helper?.Indentation(1),"}"));
        destination?.WriteLine("");
        this?.string_helper?.WriteLines(destination,this?.class_definition);
        if (AsBoolean(Size(this?.class_members)>0))
        {
            this?.string_helper?.WriteLines(destination,this?.class_members);
            destination?.WriteLine("");
        }
        this?.WriteCommonFunctions(destination);
        destination?.WriteLine("}");
        this.current_class = "";
    }

    public void WriteCommonFunctions(S84.CTCode.System.ctcode.OutputStream? destination_file)
    {
        destination_file?.WriteLine(Concat(this?.string_helper?.Indentation(1),"private static <T> void ClearList(java.util.ArrayList<T> input) { input.clear(); }"));
        destination_file?.WriteLine(Concat(this?.string_helper?.Indentation(1),"private static <T> int Size(java.util.ArrayList<T> input) { return input.size(); }"));
        destination_file?.WriteLine(Concat(this?.string_helper?.Indentation(1),"private static <T> T Element(java.util.ArrayList<T> input, int element) { return input.get(element); }"));
        destination_file?.WriteLine(Concat(this?.string_helper?.Indentation(1),"private static <T> void Append(java.util.ArrayList<T> input, T element) { input.add(element); }"));
        destination_file?.WriteLine(Concat(this?.string_helper?.Indentation(1),"private static <T> void ClearMap(java.util.HashMap<java.lang.String, T> input) { input.clear(); }"));
        destination_file?.WriteLine(Concat(this?.string_helper?.Indentation(1),"private static <T> void SetKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key, T element) { input.put(key, element); }"));
        destination_file?.WriteLine(Concat(this?.string_helper?.Indentation(1),"private static <T> java.util.ArrayList<java.lang.String> Keys(java.util.HashMap<java.lang.String, T> input) { return new java.util.ArrayList<>(input.keySet()); }"));
        destination_file?.WriteLine(Concat(this?.string_helper?.Indentation(1),"private static <T> boolean HasKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key) { return input.containsKey(key); }"));
        destination_file?.WriteLine(Concat(this?.string_helper?.Indentation(1),"private static <T> T GetKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key) { return input.get(key); }"));
        destination_file?.WriteLine(Concat(this?.string_helper?.Indentation(1),"private static int Length(java.lang.String input) { return input.length(); }"));
        destination_file?.WriteLine(Concat(this?.string_helper?.Indentation(1),"private static java.lang.String At(java.lang.String input, int index) { try { return input.substring(index, index + 1);} catch(Exception e) { return \"\"; }}"));
        destination_file?.WriteLine(Concat(this?.string_helper?.Indentation(1),"private static int IntAt(java.lang.String input, int index) { return (int)input.charAt(index); }"));
        destination_file?.WriteLine(Concat(this?.string_helper?.Indentation(1),"private static java.lang.String Concat(java.lang.String left, java.lang.String right) { return left + right; }"));
        destination_file?.WriteLine(Concat(this?.string_helper?.Indentation(1),"private static <T extends Object> boolean AsBoolean(T value) { return value != null; }"));
        destination_file?.WriteLine(Concat(this?.string_helper?.Indentation(1),"private static boolean AsBoolean(boolean value) { return value; }"));
        destination_file?.WriteLine(Concat(this?.string_helper?.Indentation(1),"private static boolean Equals(java.lang.String left, java.lang.String right) { return left.equals(right); }"));
        destination_file?.WriteLine(Concat(this?.string_helper?.Indentation(1),"private static boolean Equals(boolean left, boolean right) { return left == right; }"));
        destination_file?.WriteLine(Concat(this?.string_helper?.Indentation(1),"private static boolean Equals(int left, int right) { return left == right; }"));
        destination_file?.WriteLine(Concat(this?.string_helper?.Indentation(1),"private static boolean Equals(float left, float right) { return left == right; }"));
    }

    public void FinishProcessingCTCodeFile()
    {
    }

    public string? GetDefault(string? java_type)
    {
        if (AsBoolean(java_type=="int"))
        {
            return "0";
        }
        if (AsBoolean(java_type=="java.lang.String"))
        {
            return "\"\"";
        }
        if (AsBoolean(java_type=="boolean"))
        {
            return "false";
        }
        if (AsBoolean(java_type=="float"))
        {
            return "0.0";
        }
        if (AsBoolean(java_type=="void"))
        {
            return "null";
        }
        if (AsBoolean(this?.string_helper?.BeginsWith("java.util.HashMap<java.lang.String",java_type)))
        {
            return "new java.util.HashMap<>()";
        }
        if (AsBoolean(this?.string_helper?.BeginsWith("java.util.ArrayList<",java_type)))
        {
            return "new java.util.ArrayList<>()";
        }
        return "null";
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
