import * as S84_CTCode_dbnf_ctcode from "./S84_CTCode_dbnf_ctcode.js"
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

export class CSharpTranspiler {
    constructor() {
        this.system = null
        this.c_t_code_file = null
        this.base_name = ""
        this.logger = null
        this.string_helper = null
        this.imports = []
        this.current_interface = ""
        this.interface_definitions = []
        this.current_class = ""
        this.class_definitions = []
        this.class_members = []
        this.class_init = []
        this.class_functions = []
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
        var value = this.string_helper.SnakeCaseToCamelCase(name)
        if (this.string_helper.IsReserved(value))
        {
            return Concat("ReservedPrefix",value)
        }
        return value
    }

    GetVariableName(name)
    {
        var value = this.string_helper.CamelCaseToSnakeCase(name)
        if (value=="myself")
        {
            return "this"
        }
        if (value=="nothing")
        {
            return "null"
        }
        if (this.string_helper.IsReserved(value))
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
            result = Concat(Concat(result,"?."),name_part)
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
                result = Concat(result,",")
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

    ConvertDecimal(reserved_prefix_decimal)
    {
        return reserved_prefix_decimal
    }

    ConvertNumber(number)
    {
        return number
    }

    ConvertBoolean(reserved_prefix_boolean)
    {
        if (reserved_prefix_boolean=="true")
        {
            return "true"
        }
        if (reserved_prefix_boolean=="false")
        {
            return "false"
        }
        return ""
    }

    ConvertVariable(variable)
    {
        var result = ""
        var variable_index = 0
        while (variable_index<Length(variable))
        {
            var character = At(variable,variable_index)
            if (character==".")
            {
                result = Concat(result,"?")
            }
            result = Concat(result,character)
            variable_index = variable_index+1
        }
        return result
    }

    ConvertString(literal)
    {
        return Concat(Concat("\"",literal),"\"")
    }

    UnaryOperator(op, r_value)
    {
        if (op=="!")
        {
            return Concat("!",r_value)
        }
        return r_value
    }

    BinaryOperator(op, r_value_l, r_value_r)
    {
        if (op=="+")
        {
            return Concat(Concat(r_value_l,"+"),r_value_r)
        }
        if (op=="-")
        {
            return Concat(Concat(r_value_l,"-"),r_value_r)
        }
        if (op=="<=")
        {
            return Concat(Concat(r_value_l,"<="),r_value_r)
        }
        if (op==">=")
        {
            return Concat(Concat(r_value_l,">="),r_value_r)
        }
        if (op=="==")
        {
            return Concat(Concat(r_value_l,"=="),r_value_r)
        }
        if (op=="!=")
        {
            return Concat(Concat(r_value_l,"!="),r_value_r)
        }
        if (op=="<")
        {
            return Concat(Concat(r_value_l,"<"),r_value_r)
        }
        if (op==">")
        {
            return Concat(Concat(r_value_l,">"),r_value_r)
        }
        if (op=="||")
        {
            return Concat(Concat(Concat(Concat("AsBoolean(",r_value_l),")||AsBoolean("),r_value_r),")")
        }
        if (op=="&&")
        {
            return Concat(Concat(Concat(Concat("AsBoolean(",r_value_l),")&&AsBoolean("),r_value_r),")")
        }
        return ""
    }

    GetTypeName(name)
    {
        var value = this.string_helper.SnakeCaseToCamelCase(name)
        if (this.string_helper.IsReserved(value))
        {
            return Concat("ReservedPrefix",value)
        }
        return value
    }

    GetDimensionalType(singleton_type, dimensions)
    {
        var result = singleton_type
        while (dimensions>0)
        {
            result = Concat(Concat("List<",result),">?")
            dimensions = dimensions-1
        }
        return result
    }

    GetMapType(singleton_type)
    {
        return Concat(Concat("Dictionary<string,",singleton_type),">?")
    }

    GetPrimativeType(c_t_type)
    {
        if (c_t_type=="int")
        {
            return "int?"
        }
        if (c_t_type=="string")
        {
            return "string?"
        }
        if (c_t_type=="bool")
        {
            return "bool?"
        }
        if (c_t_type=="float")
        {
            return "float?"
        }
        if (c_t_type=="void")
        {
            return "void"
        }
        return ""
    }

    GetDefinedType(c_t_type)
    {
        return Concat(c_t_type,"?")
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
                result = Concat(name_part,result)
            }
        }
        return result
    }

    BeginProcessingCTCodeFile()
    {
        ClearList(this.imports)
        this.current_interface = ""
        ClearList(this.interface_definitions)
        this.current_class = ""
        ClearList(this.class_definitions)
        ClearList(this.class_members)
        ClearList(this.class_init)
        ClearList(this.class_functions)
    }

    FinishProcessingCTCodeFile()
    {
        var destination_file_name = Concat(this.base_name,".cs")
        var destination_file = this.system.OpenFileWriter(destination_file_name)
        destination_file.WriteLine(Concat(Concat("namespace ",this.base_name),";"))
        destination_file.WriteLine("")
        this.string_helper.WriteLines(destination_file,this.interface_definitions)
        this.string_helper.WriteLines(destination_file,this.class_definitions)
    }

    ProcessExdef(exdef)
    {
        Append(this.imports,Concat(Concat("using ",exdef),";"))
    }

    ProcessUnmanagedType(unmanaged_type)
    {
    }

    BeginProcessingInterface(interface_name)
    {
        this.current_interface = interface_name
        Append(this.interface_definitions,Concat("public interface ",interface_name))
        Append(this.interface_definitions,"{")
    }

    ProcessInterfaceFunctionDeclaration(return_type, function_name, parameters)
    {
        Append(this.interface_definitions,Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(1),return_type)," "),function_name),this.MakeParametersString(this.current_interface,parameters)),";"))
    }

    FinishProcessingInterface(interface_name)
    {
        Append(this.interface_definitions,"}")
        Append(this.interface_definitions,"")
        this.current_interface = ""
    }

    BeginProcessingClass(class_name, implementing)
    {
        this.current_class = class_name
        if (implementing=="")
        {
            Append(this.class_definitions,Concat("public class ",class_name))
        }
        else
        {
            Append(this.class_definitions,Concat(Concat(Concat("public class ",class_name)," : "),implementing))
        }
        Append(this.class_definitions,"{")
        ClearList(this.class_members)
        ClearList(this.class_init)
        ClearList(this.class_functions)
        Append(this.class_init,Concat(Concat(Concat(this.string_helper.Indentation(1),"public "),class_name),"()"))
        Append(this.class_init,Concat(this.string_helper.Indentation(1),"{"))
    }

    BeginProcessingClassFunctionDefinition(return_type, function_name, parameters)
    {
        Append(this.class_functions,Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(1),"public "),return_type)," "),function_name),this.MakeParametersString(this.current_class,parameters)))
    }

    BeginProcessCodeBlock(indent)
    {
        Append(this.class_functions,Concat(this.string_helper.Indentation(indent),"{"))
    }

    FinishProcessCodeBlock(indent)
    {
        Append(this.class_functions,Concat(this.string_helper.Indentation(indent),"}"))
    }

    BeginProcessConditional(indent, r_value)
    {
        Append(this.class_functions,Concat(Concat(Concat(this.string_helper.Indentation(indent),"if (AsBoolean("),r_value),"))"))
    }

    ProcessElse(indent)
    {
        Append(this.class_functions,Concat(this.string_helper.Indentation(indent),"else"))
    }

    FinishProcessConditional(indent, r_value)
    {
    }

    BeginProcessLoop(indent, r_value)
    {
        Append(this.class_functions,Concat(Concat(Concat(this.string_helper.Indentation(indent),"while (AsBoolean("),r_value),"))"))
    }

    FinishProcessLoop(indent, r_value)
    {
    }

    ProcessRtn(indent, r_value)
    {
        Append(this.class_functions,Concat(Concat(Concat(this.string_helper.Indentation(indent),"return "),r_value),";"))
    }

    ProcessDeclaration(indent, type, l_value, r_value)
    {
        if (r_value=="")
        {
            r_value = this.GetDefault(type)
        }
        Append(this.class_functions,Concat(Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(indent),type)," "),l_value)," = "),r_value),";"))
    }

    ProcessAssignment(indent, l_value, r_value)
    {
        Append(this.class_functions,Concat(Concat(Concat(Concat(this.string_helper.Indentation(indent),l_value)," = "),r_value),";"))
    }

    ProcessCall(indent, call)
    {
        Append(this.class_functions,Concat(Concat(this.string_helper.Indentation(indent),call),";"))
    }

    FinishProcessingClassFunctionDefinition(return_type, function_name, parameters)
    {
        Append(this.class_functions,"")
    }

    ProcessClassMemberDeclaration(member_type, member_name)
    {
        Append(this.class_init,Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(2),"this."),member_name)," = "),this.GetDefault(member_type)),";"))
        Append(this.class_members,Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(1),"private "),member_type)," "),member_name),";"))
    }

    FinishProcessingClass(class_name, implementing)
    {
        if (Size(this.class_members)>0)
        {
            var class_members_index = 0
            while (class_members_index<Size(this.class_members))
            {
                var line = Element(this.class_members,class_members_index)
                Append(this.class_definitions,line)
                class_members_index = class_members_index+1
            }
            Append(this.class_definitions,"")
        }
        Append(this.class_init,Concat(this.string_helper.Indentation(1),"}"))
        var class_init_index = 0
        while (class_init_index<Size(this.class_init))
        {
            var line = Element(this.class_init,class_init_index)
            Append(this.class_definitions,line)
            class_init_index = class_init_index+1
        }
        Append(this.class_definitions,"")
        var class_functions_index = 0
        while (class_functions_index<Size(this.class_functions))
        {
            var line = Element(this.class_functions,class_functions_index)
            Append(this.class_definitions,line)
            class_functions_index = class_functions_index+1
        }
        this.WriteCommonFunctions()
        Append(this.class_definitions,"}")
        this.current_class = ""
    }

    WriteCommonFunctions()
    {
        Append(this.class_definitions,Concat(this.string_helper.Indentation(1),"private static void ClearList<T>(List<T>? input) { input?.Clear(); }"))
        Append(this.class_definitions,Concat(this.string_helper.Indentation(1),"private static int? Size<T>(List<T>? input) { return input?.Count; }"))
        Append(this.class_definitions,Concat(this.string_helper.Indentation(1),"private static T? Element<T>(List<T>? input, int? element) { return input != null ? input[element??0] : default; }"))
        Append(this.class_definitions,Concat(this.string_helper.Indentation(1),"private static void Append<T>(List<T>? input, T element) { input?.Add(element); }"))
        Append(this.class_definitions,Concat(this.string_helper.Indentation(1),"private static void ClearMap<T>(Dictionary<string, T>? input) { input?.Clear();  }"))
        Append(this.class_definitions,Concat(this.string_helper.Indentation(1),"private static void SetKV<T>(Dictionary<string, T>? input, string? key, T element) { input?.Add(key??\"\", element); }"))
        Append(this.class_definitions,Concat(this.string_helper.Indentation(1),"private static List<string?>? Keys<T>(Dictionary<string, T>? input) { return new List<string?>(input?.Keys?.ToList()??new List<string>()); }"))
        Append(this.class_definitions,Concat(this.string_helper.Indentation(1),"private static bool? HasKV<T>(Dictionary<string, T>? input, string? key) { return input?.ContainsKey(key??\"\"); }"))
        Append(this.class_definitions,Concat(this.string_helper.Indentation(1),"private static T? GetKV<T>(Dictionary<string, T>? input, string? key) { return input != null ? input[key??\"\"] : default; }"))
        Append(this.class_definitions,Concat(this.string_helper.Indentation(1),"private static int? Length(string? input) { return input?.Length;  }"))
        Append(this.class_definitions,Concat(this.string_helper.Indentation(1),"private static string? At(string? input, int? index) { return input?.Length > index ? input?.Substring(index??0, 1) : \"\";  }"))
        Append(this.class_definitions,Concat(this.string_helper.Indentation(1),"private static int? IntAt(string? input, int? index) { return input?.Length > index ? (input[index??0] + 255 % 255) : 0;  }"))
        Append(this.class_definitions,Concat(this.string_helper.Indentation(1),"private static string? Concat(string? left, string? right) { return left + right; }"))
        Append(this.class_definitions,Concat(this.string_helper.Indentation(1),"private static bool AsBoolean(bool value) { return value; }"))
        Append(this.class_definitions,Concat(this.string_helper.Indentation(1),"private static bool AsBoolean<T>(T? value) { return value != null && !value.Equals(false); }"))
    }

    StripLast(input)
    {
        var result = ""
        var index = Length(input)-1
        while (index>0)
        {
            index = index-1
            result = Concat(At(input,index),result)
        }
        return result
    }

    GetDefault(csharp_type)
    {
        if (csharp_type=="int?")
        {
            return "0"
        }
        if (csharp_type=="string?")
        {
            return "\"\""
        }
        if (csharp_type=="bool?")
        {
            return "false"
        }
        if (csharp_type=="float?")
        {
            return "0.0"
        }
        if (csharp_type=="void")
        {
            return "void"
        }
        if (this.string_helper.BeginsWith("Dictionary<string,",csharp_type))
        {
            return Concat(Concat("new ",this.StripLast(csharp_type)),"()")
        }
        if (this.string_helper.BeginsWith("List<",csharp_type))
        {
            return Concat(Concat("new ",this.StripLast(csharp_type)),"()")
        }
        return "null"
    }

    MakeParametersString(self_type, parameters)
    {
        var result = "("
        var parameters_index = 0
        while (parameters_index<Size(parameters))
        {
            var parameter = Element(parameters,parameters_index)
            if (parameters_index!=0)
            {
                result = Concat(result,",")
            }
            result = Concat(Concat(Concat(result,parameter.ReservedPrefixGetType())," "),parameter.GetName())
            parameters_index = parameters_index+1
        }
        result = Concat(result,")")
        return result
    }
}

