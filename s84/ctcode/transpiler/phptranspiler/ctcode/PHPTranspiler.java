package s84.ctcode.transpiler.phptranspiler.ctcode;

import s84.ctcode.dbnf.ctcode.*;
import s84.ctcode.transpiler.standardstructure.ctcode.*;
import s84.ctcode.transpiler.stringhelper.ctcode.*;

public class PHPTranspiler implements s84.ctcode.transpiler.standardstructure.ctcode.TargetSpecificFunctions {
    public PHPTranspiler()
    {
        this.system = null;
        this.c_t_code_file = null;
        this.base_name = "";
        this.logger = null;
        this.string_helper = null;
        this.imports = new java.util.ArrayList<>();
        this.current_interface = "";
        this.interface_definitions = new java.util.ArrayList<>();
        this.current_class = "";
        this.class_definitions = new java.util.ArrayList<>();
        this.class_init = new java.util.ArrayList<>();
        this.class_functions = new java.util.ArrayList<>();
        this.class_members = new java.util.ArrayList<>();
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
        return 1;
    }

    public boolean IsReserved(java.lang.String name)
    {
        return (AsBoolean((AsBoolean((AsBoolean((AsBoolean((AsBoolean((AsBoolean((AsBoolean((AsBoolean((AsBoolean((AsBoolean(false) || AsBoolean(this.string_helper.BeginsWith("ReservedPrefix", name)))) || AsBoolean(this.string_helper.BeginsWith("reserved_prefix_", name)))) || AsBoolean(Equals(name,"Return")))) || AsBoolean(Equals(name,"String")))) || AsBoolean(Equals(name,"GetType")))) || AsBoolean(Equals(name,"string")))) || AsBoolean(Equals(name,"boolean")))) || AsBoolean(Equals(name,"char")))) || AsBoolean(Equals(name,"float")))) || AsBoolean(Equals(name,"decimal")));
    }

    public java.lang.String GetCallName(java.lang.String name)
    {
        java.lang.String value = this.string_helper.SnakeCaseToCamelCase(name);
        if (AsBoolean(this.IsReserved(value)))
        {
            return Concat("ReservedPrefix", value);
        }
        return value;
    }

    public java.lang.String GetVariableName(java.lang.String name)
    {
        java.lang.String value = this.string_helper.CamelCaseToSnakeCase(name);
        if (AsBoolean(Equals(value,"myself")))
        {
            return "this";
        }
        if (AsBoolean(this.IsReserved(value)))
        {
            return Concat("reserved_prefix_", value);
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
        return Concat("$", result);
    }

    public java.lang.String ConvertCall(java.util.ArrayList<java.lang.String> name_chain, java.util.ArrayList<java.lang.String> parameters)
    {
        java.lang.String result = Element(name_chain, 0);
        if (AsBoolean((Size(name_chain)>1)))
        {
            result = Concat("$", result);
        }
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
        return Concat(Concat("new ", type), "()");
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

    public java.lang.String Escape(java.lang.String input)
    {
        java.lang.String result = "";
        int input_index = 0;
        boolean in_escape = false;
        while (AsBoolean((input_index<Length(input))))
        {
            java.lang.String character = At(input, input_index);
            if (AsBoolean(Equals(character,"'")))
            {
                result = Concat(result, "\\");
            }
            if (AsBoolean((AsBoolean((! AsBoolean(in_escape))) && AsBoolean(Equals(character,"\\")))))
            {
                in_escape = true;
            }
            else
            {
                in_escape = false;
                if (AsBoolean(Equals(character,"\\")))
                {
                    result = Concat(result, "\\");
                }
                result = Concat(result, character);
            }
            input_index = (input_index+1);
        }
        return result;
    }

    public java.lang.String ConvertString(java.lang.String literal)
    {
        return Concat(Concat("'", this.Escape(literal)), "'");
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
        java.lang.String value = this.string_helper.SnakeCaseToCamelCase(name);
        if (AsBoolean(this.IsReserved(value)))
        {
            return Concat("ReservedPrefix", value);
        }
        return value;
    }

    public java.lang.String GetDimensionalType(java.lang.String singleton_type, int dimensions)
    {
        return "?array";
    }

    public java.lang.String GetMapType(java.lang.String singleton_type)
    {
        return "?array";
    }

    public java.lang.String GetPrimativeType(java.lang.String c_t_type)
    {
        if (AsBoolean(Equals(c_t_type,"int")))
        {
            return "?int";
        }
        if (AsBoolean(Equals(c_t_type,"string")))
        {
            return "?string";
        }
        if (AsBoolean(Equals(c_t_type,"bool")))
        {
            return "?bool";
        }
        if (AsBoolean(Equals(c_t_type,"float")))
        {
            return "?float";
        }
        if (AsBoolean(Equals(c_t_type,"void")))
        {
            return "void";
        }
        return "";
    }

    public java.lang.String GetDefinedType(java.lang.String c_t_type)
    {
        return Concat("?", c_t_type);
    }

    public java.lang.String GetQualifiedTypeName(java.util.ArrayList<java.lang.String> name_parts)
    {
        java.lang.String delimiter = "\\";
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
                result = Concat(name_part, result);
            }
            result = Concat(delimiter, result);
        }
        return result;
    }

    public void BeginProcessingCTCodeFile()
    {
        ClearList(this.imports);
        this.current_interface = "";
        ClearList(this.interface_definitions);
        this.current_class = "";
        ClearList(this.class_definitions);
        ClearList(this.class_init);
        ClearList(this.class_functions);
        ClearList(this.class_members);
    }

    public void FinishProcessingCTCodeFile()
    {
        java.lang.String destination_file_name = Concat(this.base_name, ".php");
        s84.ctcode.system.ctcode.OutputStream destination_file = this.system.OpenFileWriter(destination_file_name);
        destination_file.WriteLine("<?php");
        destination_file.WriteLine(Concat(Concat("namespace ", this.string_helper.DotToFwdSlash(this.base_name)), ";"));
        destination_file.WriteLine("");
        if (AsBoolean((Size(this.imports)>0)))
        {
            this.string_helper.WriteLines(destination_file, this.imports);
            destination_file.WriteLine("");
        }
        this.WriteCommonFunctions(destination_file);
        destination_file.WriteLine("");
        this.string_helper.WriteLines(destination_file, this.interface_definitions);
        this.string_helper.WriteLines(destination_file, this.class_definitions);
        destination_file.WriteLine("?>");
    }

    public void ProcessExdef(java.lang.String exdef)
    {
        Append(this.imports, Concat(Concat("include_once \"", exdef), ".php\";"));
    }

    public void ProcessUnmanagedType(java.lang.String unmanaged_type)
    {
    }

    public void BeginProcessingInterface(java.lang.String interface_name)
    {
        this.current_interface = interface_name;
        Append(this.interface_definitions, Concat(Concat("interface ", interface_name), " {"));
    }

    public void ProcessInterfaceFunctionDeclaration(java.lang.String return_type, java.lang.String function_name, java.util.ArrayList<s84.ctcode.transpiler.standardstructure.ctcode.ParameterDeclaration> parameters)
    {
        Append(this.interface_definitions, Concat(Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(1), "public function "), function_name), this.MakeParametersString(parameters)), ": "), return_type), ";"));
    }

    public void FinishProcessingInterface(java.lang.String interface_name)
    {
        Append(this.interface_definitions, "}");
        Append(this.interface_definitions, "");
        this.current_interface = "";
    }

    public void BeginProcessingClass(java.lang.String class_name, java.lang.String implementing)
    {
        this.current_class = class_name;
        if (AsBoolean(Equals(implementing,"")))
        {
            Append(this.class_definitions, Concat(Concat("class ", class_name), " {"));
        }
        else
        {
            Append(this.class_definitions, Concat(Concat(Concat(Concat("class ", class_name), " implements "), implementing), " {"));
        }
        ClearList(this.class_init);
        ClearList(this.class_functions);
        ClearList(this.class_members);
        Append(this.class_init, Concat(this.string_helper.Indentation(1), "public function __construct() {"));
    }

    public void BeginProcessingClassFunctionDefinition(java.lang.String return_type, java.lang.String function_name, java.util.ArrayList<s84.ctcode.transpiler.standardstructure.ctcode.ParameterDeclaration> parameters)
    {
        Append(this.class_functions, "");
        Append(this.class_functions, Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(1), "public function "), function_name), this.MakeParametersString(parameters)), ": "), return_type));
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
        Append(this.class_functions, Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(indent), "$"), l_value), " = "), r_value), ";"));
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
    }

    public void ProcessClassMemberDeclaration(java.lang.String member_type, java.lang.String member_name)
    {
        Append(this.class_init, Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(2), "$this->"), member_name), " = "), this.GetDefault(member_type)), ";"));
        Append(this.class_members, Concat(Concat(Concat(this.string_helper.Indentation(1), "private $"), member_name), ";"));
    }

    public void FinishProcessingClass(java.lang.String class_name, java.lang.String implementing)
    {
        Append(this.class_init, Concat(this.string_helper.Indentation(1), "}"));
        int class_init_index = 0;
        while (AsBoolean((class_init_index<Size(this.class_init))))
        {
            java.lang.String line = Element(this.class_init, class_init_index);
            Append(this.class_definitions, line);
            class_init_index = (class_init_index+1);
        }
        int class_functions_index = 0;
        while (AsBoolean((class_functions_index<Size(this.class_functions))))
        {
            java.lang.String line = Element(this.class_functions, class_functions_index);
            Append(this.class_definitions, line);
            class_functions_index = (class_functions_index+1);
        }
        Append(this.class_definitions, "");
        int class_members_index = 0;
        while (AsBoolean((class_members_index<Size(this.class_members))))
        {
            java.lang.String line = Element(this.class_members, class_members_index);
            Append(this.class_definitions, line);
            class_members_index = (class_members_index+1);
        }
        Append(this.class_definitions, "}");
        Append(this.class_definitions, "");
        this.current_class = "";
    }

    public void WriteCommonFunctions(s84.ctcode.system.ctcode.OutputStream destination_file)
    {
        destination_file.WriteLine("function ClearList(array & $input): void { $input = array(); }");
        destination_file.WriteLine("function Size(array $input): int { return count($input); }");
        destination_file.WriteLine("function Element(array $input, int $element) { return $input[$element]; }");
        destination_file.WriteLine("function Append(array & $input, mixed $element): void { $input[] = $element; }");
        destination_file.WriteLine("function ClearMap(array & $input): void { reset($input); }");
        destination_file.WriteLine("function SetKV(array & $input, string $key, mixed $element): void { $input[$key] = $element; }");
        destination_file.WriteLine("function Keys(array $input): array { return array_keys($input); }");
        destination_file.WriteLine("function HasKV(array $input, string $key): bool { return array_key_exists($key, $input); }");
        destination_file.WriteLine("function GetKV(array $input, string $key) { return $input[$key]; }");
        destination_file.WriteLine("function Length(string $input): int { return strlen($input); }");
        destination_file.WriteLine("function At(string $input, int $index): string { return substr($input, $index, 1); }");
        destination_file.WriteLine("function IntAt(string $input, int $index): int { return ord(substr($input, $index, 1)); }");
        destination_file.WriteLine("function Concat(string $left, string $right): string { return $left . $right; }");
    }

    public java.lang.String GetDefault(java.lang.String php_type)
    {
        if (AsBoolean(Equals(php_type,"?int")))
        {
            return "0";
        }
        if (AsBoolean(Equals(php_type,"?string")))
        {
            return "\"\"";
        }
        if (AsBoolean(Equals(php_type,"?bool")))
        {
            return "false";
        }
        if (AsBoolean(Equals(php_type,"?float")))
        {
            return "0.0";
        }
        if (AsBoolean(Equals(php_type,"void")))
        {
            return "null";
        }
        if (AsBoolean(Equals(php_type,"?array")))
        {
            return "array()";
        }
        return "null";
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
            result = Concat(Concat(Concat(result, parameter.GetType()), " $"), parameter.GetName());
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
    private java.util.ArrayList<java.lang.String> imports;
    private java.lang.String current_interface;
    private java.util.ArrayList<java.lang.String> interface_definitions;
    private java.lang.String current_class;
    private java.util.ArrayList<java.lang.String> class_definitions;
    private java.util.ArrayList<java.lang.String> class_init;
    private java.util.ArrayList<java.lang.String> class_functions;
    private java.util.ArrayList<java.lang.String> class_members;

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
    private static <T extends java.lang.Object> boolean AsBoolean(T value) { return value != null; }
    private static boolean AsBoolean(boolean value) { return value; }
    private static boolean Equals(java.lang.String left, java.lang.String right) { return left.equals(right); }
    private static boolean Equals(boolean left, boolean right) { return left == right; }
    private static boolean Equals(int left, int right) { return left == right; }
    private static boolean Equals(float left, float right) { return left == right; }
}
