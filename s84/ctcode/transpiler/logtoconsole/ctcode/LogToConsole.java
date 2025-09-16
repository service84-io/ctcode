package s84.ctcode.transpiler.logtoconsole.ctcode;

import s84.ctcode.dbnf.ctcode.*;
import s84.ctcode.transpiler.standardstructure.ctcode.*;
import s84.ctcode.transpiler.stringhelper.ctcode.*;

public class LogToConsole implements s84.ctcode.transpiler.standardstructure.ctcode.TargetSpecificFunctions {
    public LogToConsole()
    {
        this.system = null;
        this.c_t_code_file = null;
        this.base_name = "";
        this.logger = null;
        this.string_helper = null;
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
        return 3;
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
            return "thyself";
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
        return Concat("new ", type);
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
        if (AsBoolean(!Equals(name,"")))
        {
            return this.string_helper.SnakeCaseToCamelCase(name);
        }
        else
        {
            return "";
        }
    }

    public java.lang.String GetDimensionalType(java.lang.String singleton_type, int dimensions)
    {
        java.lang.String result = singleton_type;
        while (AsBoolean((dimensions>0)))
        {
            result = Concat(result, "[]");
            dimensions = (dimensions-1);
        }
        return result;
    }

    public java.lang.String GetMapType(java.lang.String singleton_type)
    {
        return Concat(singleton_type, "{}");
    }

    public java.lang.String GetPrimativeType(java.lang.String c_t_type)
    {
        if (AsBoolean(Equals(c_t_type,"int")))
        {
            return "int";
        }
        if (AsBoolean(Equals(c_t_type,"string")))
        {
            return "string";
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

    public java.lang.String GetQualifiedTypeName(java.util.ArrayList<java.lang.String> name_parts)
    {
        java.lang.String delimiter = ".";
        java.lang.String first_name = Element(name_parts, 0);
        java.lang.String result = first_name;
        int name_parts_index = 1;
        while (AsBoolean((name_parts_index<Size(name_parts))))
        {
            java.lang.String name = Element(name_parts, name_parts_index);
            result = Concat(Concat(result, delimiter), name);
            name_parts_index = (name_parts_index+1);
        }
        return result;
    }

    public void BeginProcessingCTCodeFile()
    {
        this.logger.WriteLine("BeginProcessingCTCodeFile");
    }

    public void FinishProcessingCTCodeFile()
    {
        this.logger.WriteLine("FinishProcessingCTCodeFile");
    }

    public void ProcessExdef(java.lang.String exdef)
    {
        this.logger.WriteLine(Concat(Concat(this.string_helper.Indentation(1), "ProcessExdef: "), exdef));
    }

    public void ProcessUnmanagedType(java.lang.String unmanaged_type)
    {
        this.logger.WriteLine(Concat(Concat(this.string_helper.Indentation(1), "ProcessUnmanagedType: "), unmanaged_type));
    }

    public void BeginProcessingInterface(java.lang.String interface_name)
    {
        this.logger.WriteLine(Concat(Concat(this.string_helper.Indentation(1), "BeginProcessingInterface: "), interface_name));
    }

    public void ProcessInterfaceFunctionDeclaration(java.lang.String return_type, java.lang.String function_name, java.util.ArrayList<s84.ctcode.transpiler.standardstructure.ctcode.ParameterDeclaration> parameters)
    {
        this.logger.WriteLine(Concat(Concat(Concat(Concat(this.string_helper.Indentation(2), "ProcessInterfaceFunctionDeclaration: "), return_type), " "), function_name));
    }

    public void FinishProcessingInterface(java.lang.String interface_name)
    {
        this.logger.WriteLine(Concat(Concat(this.string_helper.Indentation(1), "FinishProcessingInterface: "), interface_name));
    }

    public void BeginProcessingClass(java.lang.String class_name, java.lang.String implementing)
    {
        this.logger.WriteLine(Concat(Concat(Concat(Concat(this.string_helper.Indentation(1), "BeginProcessingClass: "), class_name), " "), implementing));
    }

    public void BeginProcessingClassFunctionDefinition(java.lang.String return_type, java.lang.String function_name, java.util.ArrayList<s84.ctcode.transpiler.standardstructure.ctcode.ParameterDeclaration> parameters)
    {
        this.logger.WriteLine(Concat(Concat(Concat(Concat(this.string_helper.Indentation(2), "BeginProcessingClassFunctionDefinition: "), return_type), " "), function_name));
    }

    public void BeginProcessCodeBlock(int indent)
    {
        this.logger.WriteLine(Concat(this.string_helper.Indentation(indent), "BeginProcessCodeBlock"));
    }

    public void FinishProcessCodeBlock(int indent)
    {
        this.logger.WriteLine(Concat(this.string_helper.Indentation(indent), "FinishProcessCodeBlock"));
    }

    public void BeginProcessConditional(int indent, java.lang.String r_value)
    {
        this.logger.WriteLine(Concat(Concat(this.string_helper.Indentation(indent), "BeginProcessConditional: "), r_value));
    }

    public void ProcessElse(int indent)
    {
        this.logger.WriteLine(Concat(this.string_helper.Indentation(indent), "ProcessElse"));
    }

    public void FinishProcessConditional(int indent, java.lang.String r_value)
    {
        this.logger.WriteLine(Concat(Concat(this.string_helper.Indentation(indent), "FinishProcessConditional: "), r_value));
    }

    public void BeginProcessLoop(int indent, java.lang.String r_value)
    {
        this.logger.WriteLine(Concat(Concat(this.string_helper.Indentation(indent), "BeginProcessLoop: "), r_value));
    }

    public void FinishProcessLoop(int indent, java.lang.String r_value)
    {
        this.logger.WriteLine(Concat(Concat(this.string_helper.Indentation(indent), "FinishProcessLoop: "), r_value));
    }

    public void ProcessRtn(int indent, java.lang.String r_value)
    {
        this.logger.WriteLine(Concat(Concat(this.string_helper.Indentation(indent), "ProcessRtn: "), r_value));
    }

    public void ProcessDeclaration(int indent, java.lang.String type, java.lang.String l_value, java.lang.String r_value)
    {
        this.logger.WriteLine(Concat(Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(indent), "ProcessDeclaration: "), type), " "), l_value), " "), r_value));
    }

    public void ProcessAssignment(int indent, java.lang.String l_value, java.lang.String r_value)
    {
        this.logger.WriteLine(Concat(Concat(Concat(Concat(this.string_helper.Indentation(indent), "ProcessAssignment: "), l_value), " "), r_value));
    }

    public void ProcessCall(int indent, java.lang.String call)
    {
        this.logger.WriteLine(Concat(Concat(this.string_helper.Indentation(indent), "ProcessCall: "), call));
    }

    public void FinishProcessingClassFunctionDefinition(java.lang.String return_type, java.lang.String function_name, java.util.ArrayList<s84.ctcode.transpiler.standardstructure.ctcode.ParameterDeclaration> parameters)
    {
        this.logger.WriteLine(Concat(Concat(Concat(Concat(this.string_helper.Indentation(2), "FinishProcessingClassFunctionDefinition: "), return_type), " "), function_name));
    }

    public void ProcessClassMemberDeclaration(java.lang.String member_type, java.lang.String member_name)
    {
        this.logger.WriteLine(Concat(Concat(Concat(Concat(this.string_helper.Indentation(2), "ProcessClassMemberDeclaration: "), member_type), " "), member_name));
    }

    public void FinishProcessingClass(java.lang.String class_name, java.lang.String implementing)
    {
        this.logger.WriteLine(Concat(Concat(this.string_helper.Indentation(1), "FinishProcessingClass: "), class_name));
    }

    private s84.ctcode.system.ctcode.System system;
    private s84.ctcode.dbnf.ctcode.CTCodeFile c_t_code_file;
    private java.lang.String base_name;
    private s84.ctcode.system.ctcode.OutputStream logger;
    private s84.ctcode.transpiler.stringhelper.ctcode.StringHelper string_helper;

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
