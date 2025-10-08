package s84.ctcode.transpiler.java11transpiler.ctcode;

import s84.ctcode.dbnf.ctcode.*;
import s84.ctcode.system.ctcode.*;
import s84.ctcode.transpiler.standardstructure.ctcode.*;
import s84.ctcode.transpiler.stringhelper.ctcode.*;

public class Java11Transpiler implements s84.ctcode.transpiler.standardstructure.ctcode.TargetSpecificFunctions {
    public Java11Transpiler()
    {
        this.system = null;
        this.c_t_code_file = null;
        this.base_name = "";
        this.logger = null;
        this.string_helper = null;
        this.imports = new java.util.ArrayList<>();
        this.current_interface = "";
        this.interface_definition = new java.util.ArrayList<>();
        this.current_class = "";
        this.class_definition = new java.util.ArrayList<>();
        this.class_init = new java.util.ArrayList<>();
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

    public java.lang.String GetCallName(java.lang.String name)
    {
        return this.string_helper.SnakeCaseToCamelCase(name);
    }

    public boolean IsReserved(java.lang.String name)
    {
        return (AsBoolean((AsBoolean((AsBoolean((AsBoolean(false) || AsBoolean(this.string_helper.BeginsWith("reserved_prefix_", name)))) || AsBoolean(Equals(name,"boolean")))) || AsBoolean(Equals(name,"char")))) || AsBoolean(Equals(name,"float")));
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
                result = Concat(result, ", ");
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

    public java.lang.String ConvertString(java.lang.String literal)
    {
        return Concat(Concat("\"", literal), "\"");
    }

    public java.lang.String UnaryOperator(java.lang.String op, java.lang.String r_value)
    {
        if (AsBoolean(Equals(op,"!")))
        {
            return Concat(Concat("(! AsBoolean(", r_value), "))");
        }
        return r_value;
    }

    public java.lang.String BinaryOperator(java.lang.String op, java.lang.String r_value_l, java.lang.String r_value_r)
    {
        if (AsBoolean(Equals(op,"+")))
        {
            return Concat(Concat(Concat(Concat("(", r_value_l), "+"), r_value_r), ")");
        }
        if (AsBoolean(Equals(op,"-")))
        {
            return Concat(Concat(Concat(Concat("(", r_value_l), "-"), r_value_r), ")");
        }
        if (AsBoolean(Equals(op,"<=")))
        {
            return Concat(Concat(Concat(Concat("(", r_value_l), "<="), r_value_r), ")");
        }
        if (AsBoolean(Equals(op,">=")))
        {
            return Concat(Concat(Concat(Concat("(", r_value_l), ">="), r_value_r), ")");
        }
        if (AsBoolean(Equals(op,"==")))
        {
            return Concat(Concat(Concat(Concat("Equals(", r_value_l), ","), r_value_r), ")");
        }
        if (AsBoolean(Equals(op,"!=")))
        {
            return Concat(Concat(Concat(Concat("!Equals(", r_value_l), ","), r_value_r), ")");
        }
        if (AsBoolean(Equals(op,"<")))
        {
            return Concat(Concat(Concat(Concat("(", r_value_l), "<"), r_value_r), ")");
        }
        if (AsBoolean(Equals(op,">")))
        {
            return Concat(Concat(Concat(Concat("(", r_value_l), ">"), r_value_r), ")");
        }
        if (AsBoolean(Equals(op,"||")))
        {
            return Concat(Concat(Concat(Concat("(AsBoolean(", r_value_l), ") || AsBoolean("), r_value_r), "))");
        }
        if (AsBoolean(Equals(op,"&&")))
        {
            return Concat(Concat(Concat(Concat("(AsBoolean(", r_value_l), ") && AsBoolean("), r_value_r), "))");
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
            result = Concat(Concat("java.util.ArrayList<", result), ">");
            dimensions = (dimensions-1);
        }
        return result;
    }

    public java.lang.String GetMapType(java.lang.String singleton_type)
    {
        return Concat(Concat("java.util.HashMap<java.lang.String, ", singleton_type), ">");
    }

    public java.lang.String GetPrimativeType(java.lang.String c_t_type)
    {
        if (AsBoolean(Equals(c_t_type,"int")))
        {
            return "int";
        }
        if (AsBoolean(Equals(c_t_type,"string")))
        {
            return "java.lang.String";
        }
        if (AsBoolean(Equals(c_t_type,"bool")))
        {
            return "boolean";
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
        return c_t_type;
    }

    public java.lang.String GetQualifiedTypeName(java.util.ArrayList<java.lang.String> name_parts)
    {
        java.lang.String delimiter = ".";
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
        ClearList(this.imports);
        this.current_interface = "";
        ClearList(this.interface_definition);
        this.current_class = "";
        ClearList(this.class_definition);
        ClearList(this.class_init);
        ClearList(this.class_members);
    }

    public void ProcessExdef(java.lang.String exdef)
    {
        Append(this.imports, Concat(Concat("import ", this.string_helper.ToLower(exdef)), ".*;"));
    }

    public void ProcessUnmanagedType(java.lang.String unmanaged_type)
    {
    }

    public void BeginProcessingInterface(java.lang.String interface_name)
    {
        ClearList(this.interface_definition);
        this.current_interface = interface_name;
    }

    public void ProcessInterfaceFunctionDeclaration(java.lang.String return_type, java.lang.String function_name, java.util.ArrayList<s84.ctcode.transpiler.standardstructure.ctcode.ParameterDeclaration> parameters)
    {
        Append(this.interface_definition, Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(1), return_type), " "), function_name), this.MakeParametersString(parameters)), ";"));
    }

    public void FinishProcessingInterface(java.lang.String interface_name)
    {
        s84.ctcode.system.ctcode.OutputStream destination = this.system.OpenFileWriter(Concat(Concat(Concat(this.string_helper.DotToSlash(this.string_helper.ToLower(this.base_name)), "/"), this.current_interface), ".java"));
        destination.WriteLine(Concat(Concat("package ", this.string_helper.ToLower(this.base_name)), ";"));
        destination.WriteLine("");
        if (AsBoolean((Size(this.imports)>0)))
        {
            this.string_helper.WriteLines(destination, this.imports);
            destination.WriteLine("");
        }
        destination.WriteLine(Concat(Concat("public interface ", interface_name), " {"));
        this.string_helper.WriteLines(destination, this.interface_definition);
        destination.WriteLine("}");
        this.current_interface = "";
    }

    public void BeginProcessingClass(java.lang.String class_name, java.lang.String implementing)
    {
        ClearList(this.class_definition);
        ClearList(this.class_init);
        ClearList(this.class_members);
        this.current_class = class_name;
        Append(this.class_init, Concat(Concat(Concat(this.string_helper.Indentation(1), "public "), class_name), "()"));
        Append(this.class_init, Concat(this.string_helper.Indentation(1), "{"));
    }

    public void BeginProcessingClassFunctionDefinition(java.lang.String return_type, java.lang.String function_name, java.util.ArrayList<s84.ctcode.transpiler.standardstructure.ctcode.ParameterDeclaration> parameters)
    {
        Append(this.class_definition, Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(1), "public "), return_type), " "), function_name), this.MakeParametersString(parameters)));
    }

    public void BeginProcessCodeBlock(int indent)
    {
        Append(this.class_definition, Concat(this.string_helper.Indentation(indent), "{"));
    }

    public void FinishProcessCodeBlock(int indent)
    {
        Append(this.class_definition, Concat(this.string_helper.Indentation(indent), "}"));
    }

    public void BeginProcessConditional(int indent, java.lang.String r_value)
    {
        Append(this.class_definition, Concat(Concat(Concat(this.string_helper.Indentation(indent), "if (AsBoolean("), r_value), "))"));
    }

    public void ProcessElse(int indent)
    {
        Append(this.class_definition, Concat(this.string_helper.Indentation(indent), "else"));
    }

    public void FinishProcessConditional(int indent, java.lang.String r_value)
    {
    }

    public void BeginProcessLoop(int indent, java.lang.String r_value)
    {
        Append(this.class_definition, Concat(Concat(Concat(this.string_helper.Indentation(indent), "while (AsBoolean("), r_value), "))"));
    }

    public void FinishProcessLoop(int indent, java.lang.String r_value)
    {
    }

    public void ProcessRtn(int indent, java.lang.String r_value)
    {
        Append(this.class_definition, Concat(Concat(Concat(this.string_helper.Indentation(indent), "return "), r_value), ";"));
    }

    public void ProcessDeclaration(int indent, java.lang.String type, java.lang.String l_value, java.lang.String r_value)
    {
        if (AsBoolean(Equals(r_value,"")))
        {
            r_value = this.GetDefault(type);
        }
        Append(this.class_definition, Concat(Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(indent), type), " "), l_value), " = "), r_value), ";"));
    }

    public void ProcessAssignment(int indent, java.lang.String l_value, java.lang.String r_value)
    {
        Append(this.class_definition, Concat(Concat(Concat(Concat(this.string_helper.Indentation(indent), l_value), " = "), r_value), ";"));
    }

    public void ProcessCall(int indent, java.lang.String call)
    {
        Append(this.class_definition, Concat(Concat(this.string_helper.Indentation(indent), call), ";"));
    }

    public void FinishProcessingClassFunctionDefinition(java.lang.String return_type, java.lang.String function_name, java.util.ArrayList<s84.ctcode.transpiler.standardstructure.ctcode.ParameterDeclaration> parameters)
    {
        Append(this.class_definition, "");
    }

    public void ProcessClassMemberDeclaration(java.lang.String member_type, java.lang.String member_name)
    {
        Append(this.class_init, Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(2), "this."), member_name), " = "), this.GetDefault(member_type)), ";"));
        Append(this.class_members, Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(1), "private "), member_type), " "), member_name), ";"));
    }

    public void FinishProcessingClass(java.lang.String class_name, java.lang.String implementing)
    {
        s84.ctcode.system.ctcode.OutputStream destination = this.system.OpenFileWriter(Concat(Concat(Concat(this.string_helper.DotToSlash(this.string_helper.ToLower(this.base_name)), "/"), this.current_class), ".java"));
        destination.WriteLine(Concat(Concat("package ", this.string_helper.ToLower(this.base_name)), ";"));
        destination.WriteLine("");
        if (AsBoolean((Size(this.imports)>0)))
        {
            this.string_helper.WriteLines(destination, this.imports);
            destination.WriteLine("");
        }
        if (AsBoolean(Equals(implementing,"")))
        {
            destination.WriteLine(Concat(Concat("public class ", class_name), " {"));
        }
        else
        {
            destination.WriteLine(Concat(Concat(Concat(Concat("public class ", class_name), " implements "), implementing), " {"));
        }
        this.string_helper.WriteLines(destination, this.class_init);
        destination.WriteLine(Concat(this.string_helper.Indentation(1), "}"));
        destination.WriteLine("");
        this.string_helper.WriteLines(destination, this.class_definition);
        if (AsBoolean((Size(this.class_members)>0)))
        {
            this.string_helper.WriteLines(destination, this.class_members);
            destination.WriteLine("");
        }
        this.WriteCommonFunctions(destination);
        destination.WriteLine("}");
        this.current_class = "";
    }

    public void WriteCommonFunctions(s84.ctcode.system.ctcode.OutputStream destination_file)
    {
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1), "private static <T> void ClearList(java.util.ArrayList<T> input) { input.clear(); }"));
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1), "private static <T> int Size(java.util.ArrayList<T> input) { return input.size(); }"));
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1), "private static <T> T Element(java.util.ArrayList<T> input, int element) { return input.get(element); }"));
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1), "private static <T> void Append(java.util.ArrayList<T> input, T element) { input.add(element); }"));
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1), "private static <T> void ClearMap(java.util.HashMap<java.lang.String, T> input) { input.clear(); }"));
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1), "private static <T> void SetKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key, T element) { input.put(key, element); }"));
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1), "private static <T> java.util.ArrayList<java.lang.String> Keys(java.util.HashMap<java.lang.String, T> input) { return new java.util.ArrayList<>(input.keySet()); }"));
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1), "private static <T> boolean HasKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key) { return input.containsKey(key); }"));
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1), "private static <T> T GetKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key) { return input.get(key); }"));
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1), "private static int Length(java.lang.String input) { return input.length(); }"));
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1), "private static java.lang.String At(java.lang.String input, int index) { try { return input.substring(index, index + 1);} catch(Exception e) { return \"\"; }}"));
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1), "private static int IntAt(java.lang.String input, int index) { return (int)input.charAt(index); }"));
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1), "private static java.lang.String Concat(java.lang.String left, java.lang.String right) { return left + right; }"));
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1), "private static <T extends Object> boolean AsBoolean(T value) { return value != null; }"));
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1), "private static boolean AsBoolean(boolean value) { return value; }"));
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1), "private static boolean Equals(java.lang.String left, java.lang.String right) { return left.equals(right); }"));
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1), "private static boolean Equals(boolean left, boolean right) { return left == right; }"));
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1), "private static boolean Equals(int left, int right) { return left == right; }"));
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1), "private static boolean Equals(float left, float right) { return left == right; }"));
    }

    public void FinishProcessingCTCodeFile()
    {
    }

    public java.lang.String GetDefault(java.lang.String java_type)
    {
        if (AsBoolean(Equals(java_type,"int")))
        {
            return "0";
        }
        if (AsBoolean(Equals(java_type,"java.lang.String")))
        {
            return "\"\"";
        }
        if (AsBoolean(Equals(java_type,"boolean")))
        {
            return "false";
        }
        if (AsBoolean(Equals(java_type,"float")))
        {
            return "0.0";
        }
        if (AsBoolean(Equals(java_type,"void")))
        {
            return "null";
        }
        if (AsBoolean(this.string_helper.BeginsWith("java.util.HashMap<java.lang.String", java_type)))
        {
            return "new java.util.HashMap<>()";
        }
        if (AsBoolean(this.string_helper.BeginsWith("java.util.ArrayList<", java_type)))
        {
            return "new java.util.ArrayList<>()";
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
    private java.util.ArrayList<java.lang.String> imports;
    private java.lang.String current_interface;
    private java.util.ArrayList<java.lang.String> interface_definition;
    private java.lang.String current_class;
    private java.util.ArrayList<java.lang.String> class_definition;
    private java.util.ArrayList<java.lang.String> class_init;
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
    private static <T extends Object> boolean AsBoolean(T value) { return value != null; }
    private static boolean AsBoolean(boolean value) { return value; }
    private static boolean Equals(java.lang.String left, java.lang.String right) { return left.equals(right); }
    private static boolean Equals(boolean left, boolean right) { return left == right; }
    private static boolean Equals(int left, int right) { return left == right; }
    private static boolean Equals(float left, float right) { return left == right; }
}
