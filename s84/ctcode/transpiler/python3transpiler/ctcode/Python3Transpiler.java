package s84.ctcode.transpiler.python3transpiler.ctcode;

import s84.ctcode.dbnf.ctcode.*;
import s84.ctcode.system.ctcode.*;
import s84.ctcode.transpiler.standardstructure.ctcode.*;
import s84.ctcode.transpiler.stringhelper.ctcode.*;

public class Python3Transpiler implements s84.ctcode.transpiler.standardstructure.ctcode.TargetSpecificFunctions {
    public Python3Transpiler()
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
        this.current_class_function_has_operation = false;
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

    public java.lang.String GetCallName(java.lang.String name)
    {
        return this.string_helper.SnakeCaseToCamelCase(name);
    }

    public java.lang.String GetVariableName(java.lang.String name)
    {
        java.lang.String value = this.string_helper.CamelCaseToSnakeCase(name);
        if (AsBoolean(Equals(value,"myself")))
        {
            return "self";
        }
        return value;
    }

    public java.lang.String GetVariableChain(java.util.ArrayList<java.lang.String> name_parts)
    {
        java.lang.String delimiter = ".";
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
            result = Concat(Concat(result, "."), name_part);
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
        return Concat(type, "()");
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
            return "True";
        }
        if (AsBoolean(Equals(reserved_prefix_boolean,"false")))
        {
            return "False";
        }
        return "";
    }

    public java.lang.String ConvertVariable(java.lang.String variable)
    {
        return variable;
    }

    public java.lang.String ConvertString(java.lang.String literal)
    {
        return Concat(Concat("\"", literal), "\"");
    }

    public java.lang.String UnaryOperator(java.lang.String op, java.lang.String r_value)
    {
        if (AsBoolean(Equals(op,"!")))
        {
            return Concat("not ", r_value);
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
            return Concat(Concat(r_value_l, " or "), r_value_r);
        }
        if (AsBoolean(Equals(op,"&&")))
        {
            return Concat(Concat(r_value_l, " and "), r_value_r);
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
            result = Concat(Concat("list[", result), "]");
            dimensions = (dimensions-1);
        }
        return result;
    }

    public java.lang.String GetMapType(java.lang.String singleton_type)
    {
        return Concat(Concat("dict[str, ", singleton_type), "]");
    }

    public java.lang.String GetPrimativeType(java.lang.String c_t_type)
    {
        if (AsBoolean(Equals(c_t_type,"int")))
        {
            return "int";
        }
        if (AsBoolean(Equals(c_t_type,"string")))
        {
            return "str";
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
            return "None";
        }
        return "";
    }

    public java.lang.String GetDefinedType(java.lang.String c_t_type)
    {
        return c_t_type;
    }

    public java.lang.String GetQualifiedTypeName(java.util.ArrayList<java.lang.String> name_parts)
    {
        java.lang.String package_delimiter = "_";
        java.lang.String package_name_delimiter = ".";
        int name_parts_index = (Size(name_parts)-1);
        int last_package_index = (Size(name_parts)-2);
        java.lang.String type_part = Element(name_parts, name_parts_index);
        java.lang.String result = this.GetTypeName(type_part);
        if (AsBoolean((name_parts_index>0)))
        {
            result = Concat(package_name_delimiter, result);
            while (AsBoolean((name_parts_index>0)))
            {
                name_parts_index = (name_parts_index-1);
                java.lang.String name_part = Element(name_parts, name_parts_index);
                if (AsBoolean(!Equals(name_parts_index,last_package_index)))
                {
                    result = Concat(package_delimiter, result);
                }
                result = Concat(name_part, result);
            }
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
        this.current_class_function_has_operation = false;
    }

    public void ProcessExdef(java.lang.String exdef)
    {
        Append(this.imports, Concat("import ", this.string_helper.StripDot(exdef)));
    }

    public void ProcessUnmanagedType(java.lang.String unmanaged_type)
    {
    }

    public void BeginProcessingInterface(java.lang.String interface_name)
    {
        this.current_interface = interface_name;
        Append(this.interface_definitions, Concat(Concat("class ", interface_name), ":"));
    }

    public void ProcessInterfaceFunctionDeclaration(java.lang.String return_type, java.lang.String function_name, java.util.ArrayList<s84.ctcode.transpiler.standardstructure.ctcode.ParameterDeclaration> parameters)
    {
        Append(this.interface_definitions, Concat(Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(1), "def "), function_name), this.MakeParametersString(this.current_interface, parameters)), " -> '"), return_type), "': pass"));
    }

    public void FinishProcessingInterface(java.lang.String interface_name)
    {
        Append(this.interface_definitions, "");
        this.current_interface = "";
    }

    public void BeginProcessingClass(java.lang.String class_name, java.lang.String implementing)
    {
        this.current_class = class_name;
        if (AsBoolean(Equals(implementing,"")))
        {
            Append(this.class_definitions, Concat(Concat("class ", class_name), ":"));
        }
        else
        {
            Append(this.class_definitions, Concat(Concat(Concat(Concat("class ", class_name), "("), implementing), "):"));
        }
        ClearList(this.class_init);
        ClearList(this.class_functions);
        this.current_class_function_has_operation = false;
        Append(this.class_init, Concat(Concat(Concat(this.string_helper.Indentation(1), "def __init__(self: '"), class_name), "'):"));
    }

    public void BeginProcessingClassFunctionDefinition(java.lang.String return_type, java.lang.String function_name, java.util.ArrayList<s84.ctcode.transpiler.standardstructure.ctcode.ParameterDeclaration> parameters)
    {
        Append(this.class_functions, Concat(Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(1), "def "), function_name), this.MakeParametersString(this.current_class, parameters)), " -> '"), return_type), "':"));
        this.current_class_function_has_operation = false;
    }

    public void BeginProcessCodeBlock(int indent)
    {
    }

    public void FinishProcessCodeBlock(int indent)
    {
    }

    public void BeginProcessConditional(int indent, java.lang.String r_value)
    {
        this.current_class_function_has_operation = true;
        Append(this.class_functions, Concat(Concat(Concat(this.string_helper.Indentation(indent), "if "), r_value), ":"));
    }

    public void ProcessElse(int indent)
    {
        this.current_class_function_has_operation = true;
        Append(this.class_functions, Concat(this.string_helper.Indentation(indent), "else:"));
    }

    public void FinishProcessConditional(int indent, java.lang.String r_value)
    {
        this.current_class_function_has_operation = true;
    }

    public void BeginProcessLoop(int indent, java.lang.String r_value)
    {
        this.current_class_function_has_operation = true;
        Append(this.class_functions, Concat(Concat(Concat(this.string_helper.Indentation(indent), "while "), r_value), ":"));
    }

    public void FinishProcessLoop(int indent, java.lang.String r_value)
    {
        this.current_class_function_has_operation = true;
    }

    public void ProcessRtn(int indent, java.lang.String r_value)
    {
        this.current_class_function_has_operation = true;
        Append(this.class_functions, Concat(Concat(this.string_helper.Indentation(indent), "return "), r_value));
    }

    public void ProcessDeclaration(int indent, java.lang.String type, java.lang.String l_value, java.lang.String r_value)
    {
        this.current_class_function_has_operation = true;
        if (AsBoolean(Equals(r_value,"")))
        {
            r_value = this.GetDefault(type);
        }
        Append(this.class_functions, Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(indent), l_value), ": '"), type), "' = "), r_value));
    }

    public void ProcessAssignment(int indent, java.lang.String l_value, java.lang.String r_value)
    {
        this.current_class_function_has_operation = true;
        Append(this.class_functions, Concat(Concat(Concat(this.string_helper.Indentation(indent), l_value), " = "), r_value));
    }

    public void ProcessCall(int indent, java.lang.String call)
    {
        this.current_class_function_has_operation = true;
        Append(this.class_functions, Concat(this.string_helper.Indentation(indent), call));
    }

    public void FinishProcessingClassFunctionDefinition(java.lang.String return_type, java.lang.String function_name, java.util.ArrayList<s84.ctcode.transpiler.standardstructure.ctcode.ParameterDeclaration> parameters)
    {
        if (AsBoolean((! AsBoolean(this.current_class_function_has_operation))))
        {
            Append(this.class_functions, Concat(this.string_helper.Indentation(2), "pass"));
        }
        Append(this.class_functions, "");
    }

    public void ProcessClassMemberDeclaration(java.lang.String member_type, java.lang.String member_name)
    {
        Append(this.class_init, Concat(Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(2), "self."), member_name), ": "), member_type), " = "), this.GetDefault(member_type)));
    }

    public void FinishProcessingClass(java.lang.String class_name, java.lang.String implementing)
    {
        if (AsBoolean(Equals(Size(this.class_init),1)))
        {
            Append(this.class_init, Concat(this.string_helper.Indentation(2), "pass"));
        }
        int class_init_index = 0;
        while (AsBoolean((class_init_index<Size(this.class_init))))
        {
            java.lang.String line = Element(this.class_init, class_init_index);
            Append(this.class_definitions, line);
            class_init_index = (class_init_index+1);
        }
        Append(this.class_definitions, "");
        int class_functions_index = 0;
        while (AsBoolean((class_functions_index<Size(this.class_functions))))
        {
            java.lang.String line = Element(this.class_functions, class_functions_index);
            Append(this.class_definitions, line);
            class_functions_index = (class_functions_index+1);
        }
        this.current_class = "";
    }

    public void WriteCommonFunctions(s84.ctcode.system.ctcode.OutputStream destination_file)
    {
        destination_file.WriteLine("def ClearList(input: list) -> None: input.clear()");
        destination_file.WriteLine("def Size(input: list) -> int: return len(input)");
        destination_file.WriteLine("def Element(input: list, element: int ) -> any: return input[element]");
        destination_file.WriteLine("def Append(input: list, element: any) -> None: input.append(element)");
        destination_file.WriteLine("def ClearMap(input: dict) -> None: input.clear()");
        destination_file.WriteLine("def SetKV(input: dict, key: str, element: any) -> None: input[key] = element");
        destination_file.WriteLine("def Keys(input: dict) -> list[str]:");
        destination_file.WriteLine("    result: list[str] = []");
        destination_file.WriteLine("    for key in input.keys():");
        destination_file.WriteLine("        result.append(key)");
        destination_file.WriteLine("    return result");
        destination_file.WriteLine("def HasKV(input: dict, key: str) -> bool: return key in input");
        destination_file.WriteLine("def GetKV(input: dict, key: str) -> any: return input[key]");
        destination_file.WriteLine("def Length(input: str) -> int: return len(input)");
        destination_file.WriteLine("def At(input: str, index: int) -> str: return input[index:index+1]");
        destination_file.WriteLine("def IntAt(input: str, index: int) -> int: return ord(input[index:index+1])");
        destination_file.WriteLine("def Concat(left: str, right: str) -> str: return left + right");
    }

    public void FinishProcessingCTCodeFile()
    {
        java.lang.String destination_file_name = Concat(this.string_helper.StripDot(this.base_name), ".py");
        s84.ctcode.system.ctcode.OutputStream destination_file = this.system.OpenFileWriter(destination_file_name);
        if (AsBoolean((Size(this.imports)>0)))
        {
            this.string_helper.WriteLines(destination_file, this.imports);
            destination_file.WriteLine("");
        }
        this.WriteCommonFunctions(destination_file);
        destination_file.WriteLine("");
        this.string_helper.WriteLines(destination_file, this.interface_definitions);
        this.string_helper.WriteLines(destination_file, this.class_definitions);
    }

    public java.lang.String GetDefault(java.lang.String python_type)
    {
        if (AsBoolean(Equals(python_type,"int")))
        {
            return "0";
        }
        if (AsBoolean(Equals(python_type,"str")))
        {
            return "\"\"";
        }
        if (AsBoolean(Equals(python_type,"bool")))
        {
            return "False";
        }
        if (AsBoolean(Equals(python_type,"float")))
        {
            return "0.0";
        }
        if (AsBoolean(Equals(python_type,"None")))
        {
            return "None";
        }
        if (AsBoolean(this.string_helper.BeginsWith("dict[str", python_type)))
        {
            return "{}";
        }
        if (AsBoolean(this.string_helper.BeginsWith("list[", python_type)))
        {
            return "[]";
        }
        return "None";
    }

    public java.lang.String MakeParametersString(java.lang.String self_type, java.util.ArrayList<s84.ctcode.transpiler.standardstructure.ctcode.ParameterDeclaration> parameters)
    {
        java.lang.String result = Concat(Concat("(self: '", self_type), "'");
        int parameters_index = 0;
        while (AsBoolean((parameters_index<Size(parameters))))
        {
            s84.ctcode.transpiler.standardstructure.ctcode.ParameterDeclaration parameter = Element(parameters, parameters_index);
            result = Concat(result, ",");
            result = Concat(Concat(Concat(Concat(result, parameter.GetName()), ": '"), parameter.GetType()), "'");
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
    private boolean current_class_function_has_operation;

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
