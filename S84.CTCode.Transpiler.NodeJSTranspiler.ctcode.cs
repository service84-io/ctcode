namespace S84.CTCode.Transpiler.NodeJSTranspiler.ctcode;

public class NodeJSTranspiler : S84.CTCode.Transpiler.StandardStructure.ctcode.TargetSpecificFunctions
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

    public NodeJSTranspiler()
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
            return Concat("! ",r_value);
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
            return Concat(Concat(r_value_l," || "),r_value_r);
        }
        if (AsBoolean(op=="&&"))
        {
            return Concat(Concat(r_value_l," && "),r_value_r);
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
    }

    public void ProcessExdef(string? exdef)
    {
        Append(this?.imports,Concat(Concat(Concat(Concat("import * as ",this?.string_helper?.StripDot(exdef))," from \"./"),this?.string_helper?.StripDot(exdef)),".js\""));
    }

    public void ProcessUnmanagedType(string? unmanaged_type)
    {
    }

    public void BeginProcessingInterface(string? interface_name)
    {
        this.current_interface = interface_name;
        Append(this?.interface_definitions,Concat(Concat("export class ",interface_name)," {"));
    }

    public void ProcessInterfaceFunctionDeclaration(string? return_type,string? function_name,List<S84.CTCode.Transpiler.StandardStructure.ctcode.ParameterDeclaration?>? parameters)
    {
        Append(this?.interface_definitions,Concat(Concat(Concat(this?.string_helper?.Indentation(1),function_name),this?.MakeParametersString(parameters))," {}"));
    }

    public void FinishProcessingInterface(string? interface_name)
    {
        Append(this?.interface_definitions,"}");
        Append(this?.interface_definitions,"");
        this.current_interface = "";
    }

    public void BeginProcessingClass(string? class_name,string? implementing)
    {
        this.current_class = class_name;
        Append(this?.class_definitions,Concat(Concat("export class ",class_name)," {"));
        ClearList(this?.class_init);
        ClearList(this?.class_functions);
        Append(this?.class_init,Concat(this?.string_helper?.Indentation(1),"constructor() {"));
    }

    public void BeginProcessingClassFunctionDefinition(string? return_type,string? function_name,List<S84.CTCode.Transpiler.StandardStructure.ctcode.ParameterDeclaration?>? parameters)
    {
        Append(this?.class_functions,"");
        Append(this?.class_functions,Concat(Concat(this?.string_helper?.Indentation(1),function_name),this?.MakeParametersString(parameters)));
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
        Append(this?.class_functions,Concat(Concat(this?.string_helper?.Indentation(indent),"return "),r_value));
    }

    public void ProcessDeclaration(int? indent,string? type,string? l_value,string? r_value)
    {
        if (AsBoolean(r_value==""))
        {
            r_value = this?.GetDefault(type);
        }
        Append(this?.class_functions,Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(indent),"var "),l_value)," = "),r_value));
    }

    public void ProcessAssignment(int? indent,string? l_value,string? r_value)
    {
        Append(this?.class_functions,Concat(Concat(Concat(this?.string_helper?.Indentation(indent),l_value)," = "),r_value));
    }

    public void ProcessCall(int? indent,string? call)
    {
        Append(this?.class_functions,Concat(this?.string_helper?.Indentation(indent),call));
    }

    public void FinishProcessingClassFunctionDefinition(string? return_type,string? function_name,List<S84.CTCode.Transpiler.StandardStructure.ctcode.ParameterDeclaration?>? parameters)
    {
    }

    public void ProcessClassMemberDeclaration(string? member_type,string? member_name)
    {
        Append(this?.class_init,Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(2),"this."),member_name)," = "),this?.GetDefault(member_type)));
    }

    public void FinishProcessingClass(string? class_name,string? implementing)
    {
        Append(this?.class_init,Concat(this?.string_helper?.Indentation(1),"}"));
        int? class_init_index = 0;
        while (AsBoolean(class_init_index<Size(this?.class_init)))
        {
            string? line = Element(this?.class_init,class_init_index);
            Append(this?.class_definitions,line);
            class_init_index = class_init_index+1;
        }
        int? class_functions_index = 0;
        while (AsBoolean(class_functions_index<Size(this?.class_functions)))
        {
            string? line = Element(this?.class_functions,class_functions_index);
            Append(this?.class_definitions,line);
            class_functions_index = class_functions_index+1;
        }
        Append(this?.class_definitions,"}");
        Append(this?.class_definitions,"");
        this.current_class = "";
    }

    public void WriteCommonFunctions(S84.CTCode.System.ctcode.OutputStream? destination_file)
    {
        destination_file?.WriteLine("function ClearList(input) { input.length = 0; }");
        destination_file?.WriteLine("function Size(input) { return input.length; }");
        destination_file?.WriteLine("function Element(input, element) { return input[element]; }");
        destination_file?.WriteLine("function Append(input, element) { input.push(element); }");
        destination_file?.WriteLine("function ClearMap(input) { input.clear(); }");
        destination_file?.WriteLine("function SetKV(input, key, element) { input.set(key, element); }");
        destination_file?.WriteLine("function Keys(input) { return Array.from(input.keys()); }");
        destination_file?.WriteLine("function HasKV(input, key) { return input.has(key); }");
        destination_file?.WriteLine("function GetKV(input, key) { return input.get(key); }");
        destination_file?.WriteLine("function Length(input) { return input.length; }");
        destination_file?.WriteLine("function At(input, index) { return input[index]; }");
        destination_file?.WriteLine("function IntAt(input, index) { return input.charCodeAt(index); }");
        destination_file?.WriteLine("function Concat(left, right) { return left + right; }");
    }

    public void FinishProcessingCTCodeFile()
    {
        string? destination_file_name = Concat(this?.string_helper?.StripDot(this?.base_name),".js");
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

    public string? GetDefault(string? javascript_type)
    {
        if (AsBoolean(javascript_type=="int"))
        {
            return "0";
        }
        if (AsBoolean(javascript_type=="string"))
        {
            return "\"\"";
        }
        if (AsBoolean(javascript_type=="bool"))
        {
            return "false";
        }
        if (AsBoolean(javascript_type=="float"))
        {
            return "0.0";
        }
        if (AsBoolean(javascript_type=="void"))
        {
            return "null";
        }
        if (AsBoolean(this?.string_helper?.BeginsWith("dict[str",javascript_type)))
        {
            return "new Map()";
        }
        if (AsBoolean(this?.string_helper?.BeginsWith("list[",javascript_type)))
        {
            return "[]";
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
            result = Concat(result,parameter?.GetName());
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
