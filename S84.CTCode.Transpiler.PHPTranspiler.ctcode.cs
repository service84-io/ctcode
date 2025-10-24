namespace S84.CTCode.Transpiler.PHPTranspiler.ctcode;

public class PHPTranspiler : S84.CTCode.Transpiler.StandardStructure.ctcode.TargetSpecificFunctions
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
    private List<string?>? class_members;

    public PHPTranspiler()
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
            return "null";
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
        return Concat("$",result);
    }

    public string? ConvertCall(List<string?>? name_chain,List<string?>? parameters)
    {
        string? result = Element(name_chain,0);
        if (AsBoolean(Size(name_chain)>1))
        {
            result = Concat("$",result);
        }
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

    public string? Escape(string? input)
    {
        string? result = "";
        int? input_index = 0;
        bool? in_escape = false;
        while (AsBoolean(input_index<Length(input)))
        {
            string? character = At(input,input_index);
            if (AsBoolean(character=="'"))
            {
                result = Concat(result,"\\");
            }
            if (AsBoolean(AsBoolean(! AsBoolean(in_escape))&&AsBoolean(character=="\\")))
            {
                in_escape = true;
            }
            else
            {
                in_escape = false;
                if (AsBoolean(character=="\\"))
                {
                    result = Concat(result,"\\");
                }
                result = Concat(result,character);
            }
            input_index = input_index+1;
        }
        return result;
    }

    public string? ConvertString(string? literal)
    {
        return Concat(Concat("'",this?.Escape(literal)),"'");
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
        return "?array";
    }

    public string? GetMapType(string? singleton_type)
    {
        return "?array";
    }

    public string? GetPrimativeType(string? c_t_type)
    {
        if (AsBoolean(c_t_type=="int"))
        {
            return "?int";
        }
        if (AsBoolean(c_t_type=="string"))
        {
            return "?string";
        }
        if (AsBoolean(c_t_type=="bool"))
        {
            return "?bool";
        }
        if (AsBoolean(c_t_type=="float"))
        {
            return "?float";
        }
        if (AsBoolean(c_t_type=="void"))
        {
            return "void";
        }
        return "";
    }

    public string? GetDefinedType(string? c_t_type)
    {
        return Concat("?",c_t_type);
    }

    public string? GetQualifiedTypeName(List<string?>? name_parts)
    {
        string? delimiter = "\\";
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
                result = Concat(name_part,result);
            }
            result = Concat(delimiter,result);
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
        ClearList(this?.class_members);
    }

    public void FinishProcessingCTCodeFile()
    {
        string? destination_file_name = Concat(this?.base_name,".php");
        S84.CTCode.System.ctcode.OutputStream? destination_file = this?.system?.OpenFileWriter(destination_file_name);
        destination_file?.WriteLine("<?php");
        destination_file?.WriteLine(Concat(Concat("namespace ",this?.string_helper?.DotToFwdSlash(this?.base_name)),";"));
        destination_file?.WriteLine("");
        if (AsBoolean(Size(this?.imports)>0))
        {
            this?.string_helper?.WriteLines(destination_file,this?.imports);
            destination_file?.WriteLine("");
        }
        this?.WriteCommonFunctions(destination_file);
        destination_file?.WriteLine("");
        this?.string_helper?.WriteLines(destination_file,this?.interface_definitions);
        this?.string_helper?.WriteLines(destination_file,this?.class_definitions);
        destination_file?.WriteLine("?>");
    }

    public void ProcessExdef(string? exdef)
    {
        Append(this?.imports,Concat(Concat("include_once \"",exdef),".php\";"));
    }

    public void ProcessUnmanagedType(string? unmanaged_type)
    {
    }

    public void BeginProcessingInterface(string? interface_name)
    {
        this.current_interface = interface_name;
        Append(this?.interface_definitions,Concat(Concat("interface ",interface_name)," {"));
    }

    public void ProcessInterfaceFunctionDeclaration(string? return_type,string? function_name,List<S84.CTCode.Transpiler.StandardStructure.ctcode.ParameterDeclaration?>? parameters)
    {
        Append(this?.interface_definitions,Concat(Concat(Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(1),"public function "),function_name),this?.MakeParametersString(parameters)),": "),return_type),";"));
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
        if (AsBoolean(implementing==""))
        {
            Append(this?.class_definitions,Concat(Concat("class ",class_name)," {"));
        }
        else
        {
            Append(this?.class_definitions,Concat(Concat(Concat(Concat("class ",class_name)," implements "),implementing)," {"));
        }
        ClearList(this?.class_init);
        ClearList(this?.class_functions);
        ClearList(this?.class_members);
        Append(this?.class_init,Concat(this?.string_helper?.Indentation(1),"public function __construct() {"));
    }

    public void BeginProcessingClassFunctionDefinition(string? return_type,string? function_name,List<S84.CTCode.Transpiler.StandardStructure.ctcode.ParameterDeclaration?>? parameters)
    {
        Append(this?.class_functions,"");
        Append(this?.class_functions,Concat(Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(1),"public function "),function_name),this?.MakeParametersString(parameters)),": "),return_type));
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
        Append(this?.class_functions,Concat(Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(indent),"$"),l_value)," = "),r_value),";"));
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
    }

    public void ProcessClassMemberDeclaration(string? member_type,string? member_name)
    {
        Append(this?.class_init,Concat(Concat(Concat(Concat(Concat(this?.string_helper?.Indentation(2),"$this->"),member_name)," = "),this?.GetDefault(member_type)),";"));
        Append(this?.class_members,Concat(Concat(Concat(this?.string_helper?.Indentation(1),"private $"),member_name),";"));
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
        Append(this?.class_definitions,"");
        int? class_members_index = 0;
        while (AsBoolean(class_members_index<Size(this?.class_members)))
        {
            string? line = Element(this?.class_members,class_members_index);
            Append(this?.class_definitions,line);
            class_members_index = class_members_index+1;
        }
        Append(this?.class_definitions,"}");
        Append(this?.class_definitions,"");
        this.current_class = "";
    }

    public void WriteCommonFunctions(S84.CTCode.System.ctcode.OutputStream? destination_file)
    {
        destination_file?.WriteLine("function ClearList(array & $input): void { $input = array(); }");
        destination_file?.WriteLine("function Size(array $input): int { return count($input); }");
        destination_file?.WriteLine("function Element(array $input, int $element) { return $input[$element]; }");
        destination_file?.WriteLine("function Append(array & $input, mixed $element): void { $input[] = $element; }");
        destination_file?.WriteLine("function ClearMap(array & $input): void { reset($input); }");
        destination_file?.WriteLine("function SetKV(array & $input, string $key, mixed $element): void { $input[$key] = $element; }");
        destination_file?.WriteLine("function Keys(array $input): array { return array_keys($input); }");
        destination_file?.WriteLine("function HasKV(array $input, string $key): bool { return array_key_exists($key, $input); }");
        destination_file?.WriteLine("function GetKV(array $input, string $key) { return $input[$key]; }");
        destination_file?.WriteLine("function Length(string $input): int { return strlen($input); }");
        destination_file?.WriteLine("function At(string $input, int $index): string { return substr($input, $index, 1); }");
        destination_file?.WriteLine("function IntAt(string $input, int $index): int { return ord(substr($input, $index, 1)); }");
        destination_file?.WriteLine("function Concat(string $left, string $right): string { return $left . $right; }");
    }

    public string? GetDefault(string? php_type)
    {
        if (AsBoolean(php_type=="?int"))
        {
            return "0";
        }
        if (AsBoolean(php_type=="?string"))
        {
            return "\"\"";
        }
        if (AsBoolean(php_type=="?bool"))
        {
            return "false";
        }
        if (AsBoolean(php_type=="?float"))
        {
            return "0.0";
        }
        if (AsBoolean(php_type=="void"))
        {
            return "null";
        }
        if (AsBoolean(php_type=="?array"))
        {
            return "array()";
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
            result = Concat(Concat(Concat(result,parameter?.ReservedPrefixGetType())," $"),parameter?.GetName());
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
