namespace S84.CTCode.Transpiler.PHPTranspiler.ctcode;

public class PHPTranspiler : S84.CTCode.Transpiler.StandardStructure.ctcode.TargetSpecificFunctions
{
    private S84.CTCode.System.ctcode.System? system;
    private S84.CTCode.dbnf.ctcode.CTCodeFile? c_t_code_file;
    private string? base_name;
    private S84.CTCode.System.ctcode.OutputStream? logger;
    private S84.CTCode.Transpiler.StringHelper.ctcode.StringHelper? string_helper;

    public PHPTranspiler()
    {
        this.system = null;
        this.c_t_code_file = null;
        this.base_name = "";
        this.logger = null;
        this.string_helper = null;
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

    public string? GetVariableName(string? name)
    {
        string? value = this?.string_helper?.CamelCaseToSnakeCase(name);
        if (AsBoolean(value=="myself"))
        {
            return "this";
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
        return Concat("new ",type);
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
        return this?.string_helper?.SnakeCaseToCamelCase(name);
    }

    public string? GetDimensionalType(string? singleton_type,int? dimensions)
    {
        string? result = singleton_type;
        while (AsBoolean(dimensions>0))
        {
            result = Concat(result,"[]");
            dimensions = dimensions-1;
        }
        return result;
    }

    public string? GetMapType(string? singleton_type)
    {
        return Concat(singleton_type,"{}");
    }

    public string? GetPrimativeType(string? c_t_type)
    {
        if (AsBoolean(c_t_type=="int"))
        {
            return "int";
        }
        if (AsBoolean(c_t_type=="string"))
        {
            return "string";
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
        return c_t_type;
    }

    public string? GetQualifiedTypeName(List<string?>? name_parts)
    {
        string? delimiter = ".";
        string? first_name = Element(name_parts,0);
        string? result = first_name;
        int? name_parts_index = 1;
        while (AsBoolean(name_parts_index<Size(name_parts)))
        {
            string? name = Element(name_parts,name_parts_index);
            result = Concat(Concat(result,delimiter),name);
            name_parts_index = name_parts_index+1;
        }
        return result;
    }

    public void BeginProcessingCTCodeFile()
    {
        this?.logger?.WriteLine("BeginProcessingCTCodeFile");
    }

    public void FinishProcessingCTCodeFile()
    {
        this?.logger?.WriteLine("FinishProcessingCTCodeFile");
    }

    public void ProcessExdef(string? exdef)
    {
        this?.logger?.WriteLine(Concat(Concat(this?.string_helper?.Indentation(1),"ProcessExdef: "),exdef));
    }

    public void ProcessUnmanagedType(string? unmanaged_type)
    {
        this?.logger?.WriteLine(Concat(Concat(this?.string_helper?.Indentation(1),"ProcessUnmanagedType: "),unmanaged_type));
    }

    public void BeginProcessingInterface(string? interface_name)
    {
        this?.logger?.WriteLine(Concat(Concat(this?.string_helper?.Indentation(1),"BeginProcessingInterface: "),interface_name));
    }

    public void ProcessInterfaceFunctionDeclaration(string? return_type,string? function_name,List<S84.CTCode.Transpiler.StandardStructure.ctcode.ParameterDeclaration?>? parameters)
    {
        this?.logger?.WriteLine(Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(2),"ProcessInterfaceFunctionDeclaration: "),return_type)," "),function_name));
    }

    public void FinishProcessingInterface(string? interface_name)
    {
        this?.logger?.WriteLine(Concat(Concat(this?.string_helper?.Indentation(1),"FinishProcessingInterface: "),interface_name));
    }

    public void BeginProcessingClass(string? class_name,string? implementing)
    {
        this?.logger?.WriteLine(Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(1),"BeginProcessingClass: "),class_name)," "),implementing));
    }

    public void BeginProcessingClassFunctionDefinition(string? return_type,string? function_name,List<S84.CTCode.Transpiler.StandardStructure.ctcode.ParameterDeclaration?>? parameters)
    {
        this?.logger?.WriteLine(Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(2),"BeginProcessingClassFunctionDefinition: "),return_type)," "),function_name));
    }

    public void BeginProcessCodeBlock(int? indent)
    {
        this?.logger?.WriteLine(Concat(this?.string_helper?.Indentation(indent),"BeginProcessCodeBlock"));
    }

    public void FinishProcessCodeBlock(int? indent)
    {
        this?.logger?.WriteLine(Concat(this?.string_helper?.Indentation(indent),"FinishProcessCodeBlock"));
    }

    public void BeginProcessConditional(int? indent,string? r_value)
    {
        this?.logger?.WriteLine(Concat(Concat(this?.string_helper?.Indentation(indent),"BeginProcessConditional: "),r_value));
    }

    public void ProcessElse(int? indent)
    {
        this?.logger?.WriteLine(Concat(this?.string_helper?.Indentation(indent),"ProcessElse"));
    }

    public void FinishProcessConditional(int? indent,string? r_value)
    {
        this?.logger?.WriteLine(Concat(Concat(this?.string_helper?.Indentation(indent),"FinishProcessConditional: "),r_value));
    }

    public void BeginProcessLoop(int? indent,string? r_value)
    {
        this?.logger?.WriteLine(Concat(Concat(this?.string_helper?.Indentation(indent),"BeginProcessLoop: "),r_value));
    }

    public void FinishProcessLoop(int? indent,string? r_value)
    {
        this?.logger?.WriteLine(Concat(Concat(this?.string_helper?.Indentation(indent),"FinishProcessLoop: "),r_value));
    }

    public void ProcessRtn(int? indent,string? r_value)
    {
        this?.logger?.WriteLine(Concat(Concat(this?.string_helper?.Indentation(indent),"ProcessRtn: "),r_value));
    }

    public void ProcessDeclaration(int? indent,string? type,string? l_value,string? r_value)
    {
        this?.logger?.WriteLine(Concat(Concat(Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(indent),"ProcessDeclaration: "),type)," "),l_value)," "),r_value));
    }

    public void ProcessAssignment(int? indent,string? l_value,string? r_value)
    {
        this?.logger?.WriteLine(Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(indent),"ProcessAssignment: "),l_value)," "),r_value));
    }

    public void ProcessCall(int? indent,string? call)
    {
        this?.logger?.WriteLine(Concat(Concat(this?.string_helper?.Indentation(indent),"ProcessCall: "),call));
    }

    public void FinishProcessingClassFunctionDefinition(string? return_type,string? function_name,List<S84.CTCode.Transpiler.StandardStructure.ctcode.ParameterDeclaration?>? parameters)
    {
        this?.logger?.WriteLine(Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(2),"FinishProcessingClassFunctionDefinition: "),return_type)," "),function_name));
    }

    public void ProcessClassMemberDeclaration(string? member_type,string? member_name)
    {
        this?.logger?.WriteLine(Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(2),"ProcessClassMemberDeclaration: "),member_type)," "),member_name));
    }

    public void FinishProcessingClass(string? class_name,string? implementing)
    {
        this?.logger?.WriteLine(Concat(Concat(this?.string_helper?.Indentation(1),"FinishProcessingClass: "),class_name));
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
