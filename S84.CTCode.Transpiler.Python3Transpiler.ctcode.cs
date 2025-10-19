namespace S84.CTCode.Transpiler.Python3Transpiler.ctcode;

public class Python3Transpiler : S84.CTCode.Transpiler.StandardStructure.ctcode.TargetSpecificFunctions
{
    private S84.CTCode.System.ctcode.System? system;
    private S84.CTCode.dbnf.ctcode.CTCodeFile? c_t_code_file;
    private string? base_name;
    private S84.CTCode.System.ctcode.OutputStream? logger;
    private S84.CTCode.Transpiler.StringHelper.ctcode.StringHelper? string_helper;
    private List<string?>? imports;
    private string? current_interface;
    private List<string?>? interface_definitions;
    private string? current_class;
    private List<string?>? class_definitions;
    private List<string?>? class_init;
    private List<string?>? class_functions;
    private bool? current_class_function_has_operation;

    public Python3Transpiler()
    {
        this.system = null;
        this.c_t_code_file = null;
        this.base_name = "";
        this.logger = null;
        this.string_helper = null;
        this.imports = new List<string?>();
        this.current_interface = "";
        this.interface_definitions = new List<string?>();
        this.current_class = "";
        this.class_definitions = new List<string?>();
        this.class_init = new List<string?>();
        this.class_functions = new List<string?>();
        this.current_class_function_has_operation = false;
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
            return "self";
        }
        if (AsBoolean(this?.string_helper?.IsReserved(value)))
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
        return Concat(type,"()");
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
            return "True";
        }
        if (AsBoolean(reserved_prefix_boolean=="false"))
        {
            return "False";
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
            return Concat("not ",r_value);
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
            return Concat(Concat(r_value_l," or "),r_value_r);
        }
        if (AsBoolean(op=="&&"))
        {
            return Concat(Concat(r_value_l," and "),r_value_r);
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
            result = Concat(Concat("list[",result),"]");
            dimensions = dimensions-1;
        }
        return result;
    }

    public string? GetMapType(string? singleton_type)
    {
        return Concat(Concat("dict[str, ",singleton_type),"]");
    }

    public string? GetPrimativeType(string? c_t_type)
    {
        if (AsBoolean(c_t_type=="int"))
        {
            return "int";
        }
        if (AsBoolean(c_t_type=="string"))
        {
            return "str";
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
            return "None";
        }
        return "";
    }

    public string? GetDefinedType(string? c_t_type)
    {
        return c_t_type;
    }

    public string? GetQualifiedTypeName(List<string?>? name_parts)
    {
        string? package_delimiter = "_";
        string? package_name_delimiter = ".";
        int? name_parts_index = Size(name_parts)-1;
        int? last_package_index = Size(name_parts)-2;
        string? type_part = Element(name_parts,name_parts_index);
        string? result = this?.GetTypeName(type_part);
        if (AsBoolean(name_parts_index>0))
        {
            result = Concat(package_name_delimiter,result);
            while (AsBoolean(name_parts_index>0))
            {
                name_parts_index = name_parts_index-1;
                string? name_part = Element(name_parts,name_parts_index);
                if (AsBoolean(name_parts_index!=last_package_index))
                {
                    result = Concat(package_delimiter,result);
                }
                result = Concat(name_part,result);
            }
        }
        return result;
    }

    public void BeginProcessingCTCodeFile()
    {
        ClearList(this?.imports);
        this.current_interface = "";
        ClearList(this?.interface_definitions);
        this.current_class = "";
        ClearList(this?.class_definitions);
        ClearList(this?.class_init);
        ClearList(this?.class_functions);
        this.current_class_function_has_operation = false;
    }

    public void ProcessExdef(string? exdef)
    {
        Append(this?.imports,Concat("import ",this?.string_helper?.StripDot(exdef)));
    }

    public void ProcessUnmanagedType(string? unmanaged_type)
    {
    }

    public void BeginProcessingInterface(string? interface_name)
    {
        this.current_interface = interface_name;
        Append(this?.interface_definitions,Concat(Concat("class ",interface_name),":"));
    }

    public void ProcessInterfaceFunctionDeclaration(string? return_type,string? function_name,List<S84.CTCode.Transpiler.StandardStructure.ctcode.ParameterDeclaration?>? parameters)
    {
        Append(this?.interface_definitions,Concat(Concat(Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(1),"def "),function_name),this?.MakeParametersString(this?.current_interface,parameters))," -> '"),return_type),"': pass"));
    }

    public void FinishProcessingInterface(string? interface_name)
    {
        Append(this?.interface_definitions,"");
        this.current_interface = "";
    }

    public void BeginProcessingClass(string? class_name,string? implementing)
    {
        this.current_class = class_name;
        if (AsBoolean(implementing==""))
        {
            Append(this?.class_definitions,Concat(Concat("class ",class_name),":"));
        }
        else
        {
            Append(this?.class_definitions,Concat(Concat(Concat(Concat("class ",class_name),"("),implementing),"):"));
        }
        ClearList(this?.class_init);
        ClearList(this?.class_functions);
        this.current_class_function_has_operation = false;
        Append(this?.class_init,Concat(Concat(Concat(this?.string_helper?.Indentation(1),"def __init__(self: '"),class_name),"'):"));
    }

    public void BeginProcessingClassFunctionDefinition(string? return_type,string? function_name,List<S84.CTCode.Transpiler.StandardStructure.ctcode.ParameterDeclaration?>? parameters)
    {
        Append(this?.class_functions,Concat(Concat(Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(1),"def "),function_name),this?.MakeParametersString(this?.current_class,parameters))," -> '"),return_type),"':"));
        this.current_class_function_has_operation = false;
    }

    public void BeginProcessCodeBlock(int? indent)
    {
    }

    public void FinishProcessCodeBlock(int? indent)
    {
    }

    public void BeginProcessConditional(int? indent,string? r_value)
    {
        this.current_class_function_has_operation = true;
        Append(this?.class_functions,Concat(Concat(Concat(this?.string_helper?.Indentation(indent),"if "),r_value),":"));
    }

    public void ProcessElse(int? indent)
    {
        this.current_class_function_has_operation = true;
        Append(this?.class_functions,Concat(this?.string_helper?.Indentation(indent),"else:"));
    }

    public void FinishProcessConditional(int? indent,string? r_value)
    {
        this.current_class_function_has_operation = true;
    }

    public void BeginProcessLoop(int? indent,string? r_value)
    {
        this.current_class_function_has_operation = true;
        Append(this?.class_functions,Concat(Concat(Concat(this?.string_helper?.Indentation(indent),"while "),r_value),":"));
    }

    public void FinishProcessLoop(int? indent,string? r_value)
    {
        this.current_class_function_has_operation = true;
    }

    public void ProcessRtn(int? indent,string? r_value)
    {
        this.current_class_function_has_operation = true;
        Append(this?.class_functions,Concat(Concat(this?.string_helper?.Indentation(indent),"return "),r_value));
    }

    public void ProcessDeclaration(int? indent,string? type,string? l_value,string? r_value)
    {
        this.current_class_function_has_operation = true;
        if (AsBoolean(r_value==""))
        {
            r_value = this?.GetDefault(type);
        }
        Append(this?.class_functions,Concat(Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(indent),l_value),": '"),type),"' = "),r_value));
    }

    public void ProcessAssignment(int? indent,string? l_value,string? r_value)
    {
        this.current_class_function_has_operation = true;
        Append(this?.class_functions,Concat(Concat(Concat(this?.string_helper?.Indentation(indent),l_value)," = "),r_value));
    }

    public void ProcessCall(int? indent,string? call)
    {
        this.current_class_function_has_operation = true;
        Append(this?.class_functions,Concat(this?.string_helper?.Indentation(indent),call));
    }

    public void FinishProcessingClassFunctionDefinition(string? return_type,string? function_name,List<S84.CTCode.Transpiler.StandardStructure.ctcode.ParameterDeclaration?>? parameters)
    {
        if (AsBoolean(!this?.current_class_function_has_operation))
        {
            Append(this?.class_functions,Concat(this?.string_helper?.Indentation(2),"pass"));
        }
        Append(this?.class_functions,"");
    }

    public void ProcessClassMemberDeclaration(string? member_type,string? member_name)
    {
        Append(this?.class_init,Concat(Concat(Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(2),"self."),member_name),": "),member_type)," = "),this?.GetDefault(member_type)));
    }

    public void FinishProcessingClass(string? class_name,string? implementing)
    {
        if (AsBoolean(Size(this?.class_init)==1))
        {
            Append(this?.class_init,Concat(this?.string_helper?.Indentation(2),"pass"));
        }
        int? class_init_index = 0;
        while (AsBoolean(class_init_index<Size(this?.class_init)))
        {
            string? line = Element(this?.class_init,class_init_index);
            Append(this?.class_definitions,line);
            class_init_index = class_init_index+1;
        }
        Append(this?.class_definitions,"");
        int? class_functions_index = 0;
        while (AsBoolean(class_functions_index<Size(this?.class_functions)))
        {
            string? line = Element(this?.class_functions,class_functions_index);
            Append(this?.class_definitions,line);
            class_functions_index = class_functions_index+1;
        }
        this.current_class = "";
    }

    public void WriteCommonFunctions(S84.CTCode.System.ctcode.OutputStream? destination_file)
    {
        destination_file?.WriteLine("def ClearList(input: list) -> None: input.clear()");
        destination_file?.WriteLine("def Size(input: list) -> int: return len(input)");
        destination_file?.WriteLine("def Element(input: list, element: int ) -> any: return input[element]");
        destination_file?.WriteLine("def Append(input: list, element: any) -> None: input.append(element)");
        destination_file?.WriteLine("def ClearMap(input: dict) -> None: input.clear()");
        destination_file?.WriteLine("def SetKV(input: dict, key: str, element: any) -> None: input[key] = element");
        destination_file?.WriteLine("def Keys(input: dict) -> list[str]:");
        destination_file?.WriteLine("    result: list[str] = []");
        destination_file?.WriteLine("    for key in input.keys():");
        destination_file?.WriteLine("        result.append(key)");
        destination_file?.WriteLine("    return result");
        destination_file?.WriteLine("def HasKV(input: dict, key: str) -> bool: return key in input");
        destination_file?.WriteLine("def GetKV(input: dict, key: str) -> any: return input[key]");
        destination_file?.WriteLine("def Length(input: str) -> int: return len(input)");
        destination_file?.WriteLine("def At(input: str, index: int) -> str: return input[index:index+1]");
        destination_file?.WriteLine("def IntAt(input: str, index: int) -> int: return ord(input[index:index+1])");
        destination_file?.WriteLine("def Concat(left: str, right: str) -> str: return left + right");
    }

    public void FinishProcessingCTCodeFile()
    {
        string? destination_file_name = Concat(this?.string_helper?.StripDot(this?.base_name),".py");
        S84.CTCode.System.ctcode.OutputStream? destination_file = this?.system?.OpenFileWriter(destination_file_name);
        if (AsBoolean(Size(this?.imports)>0))
        {
            this?.string_helper?.WriteLines(destination_file,this?.imports);
            destination_file?.WriteLine("");
        }
        this?.WriteCommonFunctions(destination_file);
        destination_file?.WriteLine("");
        this?.string_helper?.WriteLines(destination_file,this?.interface_definitions);
        this?.string_helper?.WriteLines(destination_file,this?.class_definitions);
    }

    public string? GetDefault(string? python_type)
    {
        if (AsBoolean(python_type=="int"))
        {
            return "0";
        }
        if (AsBoolean(python_type=="str"))
        {
            return "\"\"";
        }
        if (AsBoolean(python_type=="bool"))
        {
            return "False";
        }
        if (AsBoolean(python_type=="float"))
        {
            return "0.0";
        }
        if (AsBoolean(python_type=="None"))
        {
            return "None";
        }
        if (AsBoolean(this?.string_helper?.BeginsWith("dict[str",python_type)))
        {
            return "{}";
        }
        if (AsBoolean(this?.string_helper?.BeginsWith("list[",python_type)))
        {
            return "[]";
        }
        return "None";
    }

    public string? MakeParametersString(string? self_type,List<S84.CTCode.Transpiler.StandardStructure.ctcode.ParameterDeclaration?>? parameters)
    {
        string? result = Concat(Concat("(self: '",self_type),"'");
        int? parameters_index = 0;
        while (AsBoolean(parameters_index<Size(parameters)))
        {
            S84.CTCode.Transpiler.StandardStructure.ctcode.ParameterDeclaration? parameter = Element(parameters,parameters_index);
            result = Concat(result,",");
            result = Concat(Concat(Concat(Concat(result,parameter?.GetName()),": '"),parameter?.ReservedPrefixGetType()),"'");
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
