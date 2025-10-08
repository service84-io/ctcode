import * as S84_CTCode_dbnf_ctcode from "./S84_CTCode_dbnf_ctcode.js"
import * as S84_CTCode_System_ctcode from "./S84_CTCode_System_ctcode.js"
import * as S84_CTCode_Transpiler_StandardStructure_ctcode from "./S84_CTCode_Transpiler_StandardStructure_ctcode.js"
import * as S84_CTCode_Transpiler_StringHelper_ctcode from "./S84_CTCode_Transpiler_StringHelper_ctcode.js"

function ClearList(input) { input.length = 0; }
function Size(input) { return input.length; }
function Element(input, element) { return input[element]; }
function Append(input, element) { input.push(element); }
function ClearMap(input) { input.clear(); }
function SetKV(input, key, element) { input.set(key, element); }
function Keys(input) { return Array.from(input.keys()); }
function HasKV(input, key) { return input.has(key); }
function GetKV(input, key) { return input.get(key); }
function Length(input) { return input.length; }
function At(input, index) { return input[index]; }
function IntAt(input, index) { return input.charCodeAt(index); }
function Concat(left, right) { return left + right; }

export class Java11Transpiler {
    constructor() {
        this.system = null
        this.c_t_code_file = null
        this.base_name = ""
        this.logger = null
        this.string_helper = null
        this.imports = []
        this.current_interface = ""
        this.interface_definition = []
        this.current_class = ""
        this.class_definition = []
        this.class_init = []
        this.class_members = []
    }

    Initialize()
    {
        this.string_helper = new S84_CTCode_Transpiler_StringHelper_ctcode.StringHelper()
    }

    SetSystem(system)
    {
        this.system = system
    }

    SetCTCodeFile(c_t_code_file)
    {
        this.c_t_code_file = c_t_code_file
    }

    SetBaseName(base_name)
    {
        this.base_name = base_name
    }

    SetLogger(logger)
    {
        this.logger = logger
    }

    GetBaseIndentation()
    {
        return 1
    }

    GetCallName(name)
    {
        return this.string_helper.SnakeCaseToCamelCase(name)
    }

    IsReserved(name)
    {
        return false || this.string_helper.BeginsWith("reserved_prefix_",name) || name=="boolean" || name=="char" || name=="float"
    }

    GetVariableName(name)
    {
        var value = this.string_helper.CamelCaseToSnakeCase(name)
        if (value=="myself")
        {
            return "this"
        }
        if (this.IsReserved(value))
        {
            return Concat("reserved_prefix_",value)
        }
        return value
    }

    GetVariableChain(name_parts)
    {
        var delimiter = "."
        var first_name = Element(name_parts,0)
        var result = this.GetVariableName(first_name)
        var name_parts_index = 1
        while (name_parts_index<Size(name_parts))
        {
            var name = Element(name_parts,name_parts_index)
            result = Concat(Concat(result,delimiter),this.GetVariableName(name))
            name_parts_index = name_parts_index+1
        }
        return result
    }

    ConvertCall(name_chain, parameters)
    {
        var result = Element(name_chain,0)
        var name_chain_index = 1
        while (name_chain_index<Size(name_chain))
        {
            var name_part = Element(name_chain,name_chain_index)
            result = Concat(Concat(result,"."),name_part)
            name_chain_index = name_chain_index+1
        }
        result = Concat(result,"(")
        if (Size(parameters)>0)
        {
            result = Concat(result,Element(parameters,0))
            var parameters_index = 1
            while (parameters_index<Size(parameters))
            {
                var parameter = Element(parameters,parameters_index)
                result = Concat(result,", ")
                result = Concat(result,parameter)
                parameters_index = parameters_index+1
            }
        }
        result = Concat(result,")")
        return result
    }

    ConvertAllocate(type)
    {
        return Concat(Concat("new ",type),"()")
    }

    ConvertByte(high, low)
    {
        return Concat(Concat("0x",high),low)
    }

    ConvertDecimal(decimal)
    {
        return decimal
    }

    ConvertNumber(number)
    {
        return number
    }

    ConvertBoolean(boolean)
    {
        if (boolean=="true")
        {
            return "true"
        }
        if (boolean=="false")
        {
            return "false"
        }
        return ""
    }

    ConvertVariable(variable)
    {
        return variable
    }

    ConvertString(literal)
    {
        return Concat(Concat("\"",literal),"\"")
    }

    UnaryOperator(op, r_value)
    {
        if (op=="!")
        {
            return Concat(Concat("(! AsBoolean(",r_value),"))")
        }
        return r_value
    }

    BinaryOperator(op, r_value_l, r_value_r)
    {
        if (op=="+")
        {
            return Concat(Concat(Concat(Concat("(",r_value_l),"+"),r_value_r),")")
        }
        if (op=="-")
        {
            return Concat(Concat(Concat(Concat("(",r_value_l),"-"),r_value_r),")")
        }
        if (op=="<=")
        {
            return Concat(Concat(Concat(Concat("(",r_value_l),"<="),r_value_r),")")
        }
        if (op==">=")
        {
            return Concat(Concat(Concat(Concat("(",r_value_l),">="),r_value_r),")")
        }
        if (op=="==")
        {
            return Concat(Concat(Concat(Concat("Equals(",r_value_l),","),r_value_r),")")
        }
        if (op=="!=")
        {
            return Concat(Concat(Concat(Concat("!Equals(",r_value_l),","),r_value_r),")")
        }
        if (op=="<")
        {
            return Concat(Concat(Concat(Concat("(",r_value_l),"<"),r_value_r),")")
        }
        if (op==">")
        {
            return Concat(Concat(Concat(Concat("(",r_value_l),">"),r_value_r),")")
        }
        if (op=="||")
        {
            return Concat(Concat(Concat(Concat("(AsBoolean(",r_value_l),") || AsBoolean("),r_value_r),"))")
        }
        if (op=="&&")
        {
            return Concat(Concat(Concat(Concat("(AsBoolean(",r_value_l),") && AsBoolean("),r_value_r),"))")
        }
        return ""
    }

    GetTypeName(name)
    {
        return this.string_helper.SnakeCaseToCamelCase(name)
    }

    GetDimensionalType(singleton_type, dimensions)
    {
        var result = singleton_type
        while (dimensions>0)
        {
            result = Concat(Concat("java.util.ArrayList<",result),">")
            dimensions = dimensions-1
        }
        return result
    }

    GetMapType(singleton_type)
    {
        return Concat(Concat("java.util.HashMap<java.lang.String, ",singleton_type),">")
    }

    GetPrimativeType(c_t_type)
    {
        if (c_t_type=="int")
        {
            return "int"
        }
        if (c_t_type=="string")
        {
            return "java.lang.String"
        }
        if (c_t_type=="bool")
        {
            return "boolean"
        }
        if (c_t_type=="float")
        {
            return "float"
        }
        if (c_t_type=="void")
        {
            return "void"
        }
        return ""
    }

    GetDefinedType(c_t_type)
    {
        return c_t_type
    }

    GetQualifiedTypeName(name_parts)
    {
        var delimiter = "."
        var name_parts_index = Size(name_parts)-1
        var type_part = Element(name_parts,name_parts_index)
        var result = this.GetTypeName(type_part)
        if (name_parts_index>0)
        {
            while (name_parts_index>0)
            {
                name_parts_index = name_parts_index-1
                result = Concat(delimiter,result)
                var name_part = Element(name_parts,name_parts_index)
                result = Concat(this.string_helper.ToLower(name_part),result)
            }
        }
        return result
    }

    BeginProcessingCTCodeFile()
    {
        ClearList(this.imports)
        this.current_interface = ""
        ClearList(this.interface_definition)
        this.current_class = ""
        ClearList(this.class_definition)
        ClearList(this.class_init)
        ClearList(this.class_members)
    }

    ProcessExdef(exdef)
    {
        Append(this.imports,Concat(Concat("import ",this.string_helper.ToLower(exdef)),".*;"))
    }

    ProcessUnmanagedType(unmanaged_type)
    {
    }

    BeginProcessingInterface(interface_name)
    {
        ClearList(this.interface_definition)
        this.current_interface = interface_name
    }

    ProcessInterfaceFunctionDeclaration(return_type, function_name, parameters)
    {
        Append(this.interface_definition,Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(1),return_type)," "),function_name),this.MakeParametersString(parameters)),";"))
    }

    FinishProcessingInterface(interface_name)
    {
        var destination = this.system.OpenFileWriter(Concat(Concat(Concat(this.string_helper.DotToSlash(this.string_helper.ToLower(this.base_name)),"/"),this.current_interface),".java"))
        destination.WriteLine(Concat(Concat("package ",this.string_helper.ToLower(this.base_name)),";"))
        destination.WriteLine("")
        if (Size(this.imports)>0)
        {
            this.string_helper.WriteLines(destination,this.imports)
            destination.WriteLine("")
        }
        destination.WriteLine(Concat(Concat("public interface ",interface_name)," {"))
        this.string_helper.WriteLines(destination,this.interface_definition)
        destination.WriteLine("}")
        this.current_interface = ""
    }

    BeginProcessingClass(class_name, implementing)
    {
        ClearList(this.class_definition)
        ClearList(this.class_init)
        ClearList(this.class_members)
        this.current_class = class_name
        Append(this.class_init,Concat(Concat(Concat(this.string_helper.Indentation(1),"public "),class_name),"()"))
        Append(this.class_init,Concat(this.string_helper.Indentation(1),"{"))
    }

    BeginProcessingClassFunctionDefinition(return_type, function_name, parameters)
    {
        Append(this.class_definition,Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(1),"public "),return_type)," "),function_name),this.MakeParametersString(parameters)))
    }

    BeginProcessCodeBlock(indent)
    {
        Append(this.class_definition,Concat(this.string_helper.Indentation(indent),"{"))
    }

    FinishProcessCodeBlock(indent)
    {
        Append(this.class_definition,Concat(this.string_helper.Indentation(indent),"}"))
    }

    BeginProcessConditional(indent, r_value)
    {
        Append(this.class_definition,Concat(Concat(Concat(this.string_helper.Indentation(indent),"if (AsBoolean("),r_value),"))"))
    }

    ProcessElse(indent)
    {
        Append(this.class_definition,Concat(this.string_helper.Indentation(indent),"else"))
    }

    FinishProcessConditional(indent, r_value)
    {
    }

    BeginProcessLoop(indent, r_value)
    {
        Append(this.class_definition,Concat(Concat(Concat(this.string_helper.Indentation(indent),"while (AsBoolean("),r_value),"))"))
    }

    FinishProcessLoop(indent, r_value)
    {
    }

    ProcessRtn(indent, r_value)
    {
        Append(this.class_definition,Concat(Concat(Concat(this.string_helper.Indentation(indent),"return "),r_value),";"))
    }

    ProcessDeclaration(indent, type, l_value, r_value)
    {
        if (r_value=="")
        {
            r_value = this.GetDefault(type)
        }
        Append(this.class_definition,Concat(Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(indent),type)," "),l_value)," = "),r_value),";"))
    }

    ProcessAssignment(indent, l_value, r_value)
    {
        Append(this.class_definition,Concat(Concat(Concat(Concat(this.string_helper.Indentation(indent),l_value)," = "),r_value),";"))
    }

    ProcessCall(indent, call)
    {
        Append(this.class_definition,Concat(Concat(this.string_helper.Indentation(indent),call),";"))
    }

    FinishProcessingClassFunctionDefinition(return_type, function_name, parameters)
    {
        Append(this.class_definition,"")
    }

    ProcessClassMemberDeclaration(member_type, member_name)
    {
        Append(this.class_init,Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(2),"this."),member_name)," = "),this.GetDefault(member_type)),";"))
        Append(this.class_members,Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(1),"private "),member_type)," "),member_name),";"))
    }

    FinishProcessingClass(class_name, implementing)
    {
        var destination = this.system.OpenFileWriter(Concat(Concat(Concat(this.string_helper.DotToSlash(this.string_helper.ToLower(this.base_name)),"/"),this.current_class),".java"))
        destination.WriteLine(Concat(Concat("package ",this.string_helper.ToLower(this.base_name)),";"))
        destination.WriteLine("")
        if (Size(this.imports)>0)
        {
            this.string_helper.WriteLines(destination,this.imports)
            destination.WriteLine("")
        }
        if (implementing=="")
        {
            destination.WriteLine(Concat(Concat("public class ",class_name)," {"))
        }
        else
        {
            destination.WriteLine(Concat(Concat(Concat(Concat("public class ",class_name)," implements "),implementing)," {"))
        }
        this.string_helper.WriteLines(destination,this.class_init)
        destination.WriteLine(Concat(this.string_helper.Indentation(1),"}"))
        destination.WriteLine("")
        this.string_helper.WriteLines(destination,this.class_definition)
        if (Size(this.class_members)>0)
        {
            this.string_helper.WriteLines(destination,this.class_members)
            destination.WriteLine("")
        }
        this.WriteCommonFunctions(destination)
        destination.WriteLine("}")
        this.current_class = ""
    }

    WriteCommonFunctions(destination_file)
    {
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1),"private static <T> void ClearList(java.util.ArrayList<T> input) { input.clear(); }"))
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1),"private static <T> int Size(java.util.ArrayList<T> input) { return input.size(); }"))
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1),"private static <T> T Element(java.util.ArrayList<T> input, int element) { return input.get(element); }"))
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1),"private static <T> void Append(java.util.ArrayList<T> input, T element) { input.add(element); }"))
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1),"private static <T> void ClearMap(java.util.HashMap<java.lang.String, T> input) { input.clear(); }"))
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1),"private static <T> void SetKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key, T element) { input.put(key, element); }"))
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1),"private static <T> java.util.ArrayList<java.lang.String> Keys(java.util.HashMap<java.lang.String, T> input) { return new java.util.ArrayList<>(input.keySet()); }"))
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1),"private static <T> boolean HasKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key) { return input.containsKey(key); }"))
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1),"private static <T> T GetKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key) { return input.get(key); }"))
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1),"private static int Length(java.lang.String input) { return input.length(); }"))
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1),"private static java.lang.String At(java.lang.String input, int index) { try { return input.substring(index, index + 1);} catch(Exception e) { return \"\"; }}"))
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1),"private static int IntAt(java.lang.String input, int index) { return (int)input.charAt(index); }"))
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1),"private static java.lang.String Concat(java.lang.String left, java.lang.String right) { return left + right; }"))
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1),"private static <T extends Object> boolean AsBoolean(T value) { return value != null; }"))
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1),"private static boolean AsBoolean(boolean value) { return value; }"))
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1),"private static boolean Equals(java.lang.String left, java.lang.String right) { return left.equals(right); }"))
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1),"private static boolean Equals(boolean left, boolean right) { return left == right; }"))
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1),"private static boolean Equals(int left, int right) { return left == right; }"))
        destination_file.WriteLine(Concat(this.string_helper.Indentation(1),"private static boolean Equals(float left, float right) { return left == right; }"))
    }

    FinishProcessingCTCodeFile()
    {
    }

    GetDefault(java_type)
    {
        if (java_type=="int")
        {
            return "0"
        }
        if (java_type=="java.lang.String")
        {
            return "\"\""
        }
        if (java_type=="boolean")
        {
            return "false"
        }
        if (java_type=="float")
        {
            return "0.0"
        }
        if (java_type=="void")
        {
            return "null"
        }
        if (this.string_helper.BeginsWith("java.util.HashMap<java.lang.String",java_type))
        {
            return "new java.util.HashMap<>()"
        }
        if (this.string_helper.BeginsWith("java.util.ArrayList<",java_type))
        {
            return "new java.util.ArrayList<>()"
        }
        return "null"
    }

    MakeParametersString(parameters)
    {
        var result = "("
        var parameters_index = 0
        while (parameters_index<Size(parameters))
        {
            var parameter = Element(parameters,parameters_index)
            if (parameters_index!=0)
            {
                result = Concat(result,", ")
            }
            result = Concat(Concat(Concat(result,parameter.GetType())," "),parameter.GetName())
            parameters_index = parameters_index+1
        }
        result = Concat(result,")")
        return result
    }
}

