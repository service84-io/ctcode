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

export class Python3Transpiler {
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
        return this.string_helper.SnakeCaseToCamelCase(name)
    }

    GetVariableName(name)
    {
        var value = this.string_helper.CamelCaseToSnakeCase(name)
        if (value=="myself")
        {
            return "self"
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
        return Concat(type,"()")
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
            return "True"
        }
        if (boolean=="false")
        {
            return "False"
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
            return Concat("not ",r_value)
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
            return Concat(Concat(r_value_l," or "),r_value_r)
        }
        if (op=="&&")
        {
            return Concat(Concat(r_value_l," and "),r_value_r)
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
            result = Concat(Concat("list[",result),"]")
            dimensions = dimensions-1
        }
        return result
    }

    GetMapType(singleton_type)
    {
        return Concat(Concat("dict[str, ",singleton_type),"]")
    }

    GetPrimativeType(c_t_type)
    {
        if (c_t_type=="int")
        {
            return "int"
        }
        if (c_t_type=="string")
        {
            return "str"
        }
        if (c_t_type=="bool")
        {
            return "bool"
        }
        if (c_t_type=="float")
        {
            return "float"
        }
        if (c_t_type=="void")
        {
            return "None"
        }
        return ""
    }

    GetQualifiedTypeName(name_parts)
    {
        var package_delimiter = "_"
        var package_name_delimiter = "."
        var name_parts_index = Size(name_parts)-1
        var last_package_index = Size(name_parts)-2
        var type_part = Element(name_parts,name_parts_index)
        var result = this.GetTypeName(type_part)
        if (name_parts_index>0)
        {
            result = Concat(package_name_delimiter,result)
            while (name_parts_index>0)
            {
                name_parts_index = name_parts_index-1
                var name_part = Element(name_parts,name_parts_index)
                if (name_parts_index!=last_package_index)
                {
                    result = Concat(package_delimiter,result)
                }
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
        ClearList(this.class_init)
        ClearList(this.class_functions)
    }

    ProcessExdef(exdef)
    {
        Append(this.imports,Concat("import ",this.string_helper.StripDot(exdef)))
    }

    ProcessUnmanagedType(unmanaged_type)
    {
        var noop = 0
    }

    BeginProcessingInterface(interface_name)
    {
        this.current_interface = interface_name
        Append(this.interface_definitions,Concat(Concat("class ",interface_name),":"))
    }

    ProcessInterfaceFunctionDeclaration(return_type, function_name, parameters)
    {
        Append(this.interface_definitions,Concat(Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(1),"def "),function_name),this.MakeParametersString(this.current_interface,parameters))," -> '"),return_type),"': pass"))
    }

    FinishProcessingInterface(interface_name)
    {
        Append(this.interface_definitions,"")
        this.current_interface = ""
    }

    BeginProcessingClass(class_name, implementing)
    {
        this.current_class = class_name
        if (implementing=="")
        {
            Append(this.class_definitions,Concat(Concat("class ",class_name),":"))
        }
        else
        {
            Append(this.class_definitions,Concat(Concat(Concat(Concat("class ",class_name),"("),implementing),"):"))
        }
        ClearList(this.class_init)
        ClearList(this.class_functions)
        Append(this.class_init,Concat(Concat(Concat(this.string_helper.Indentation(1),"def __init__(self: '"),class_name),"'):"))
    }

    BeginProcessingClassFunctionDefinition(return_type, function_name, parameters)
    {
        Append(this.class_functions,Concat(Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(1),"def "),function_name),this.MakeParametersString(this.current_class,parameters))," -> '"),return_type),"':"))
    }

    BeginProcessCodeBlock(indent)
    {
        var noop = 0
    }

    FinishProcessCodeBlock(indent)
    {
        var noop = 0
    }

    BeginProcessConditional(indent, r_value)
    {
        Append(this.class_functions,Concat(Concat(Concat(this.string_helper.Indentation(indent),"if "),r_value),":"))
    }

    ProcessElse(indent)
    {
        Append(this.class_functions,Concat(this.string_helper.Indentation(indent),"else:"))
    }

    FinishProcessConditional(indent, r_value)
    {
        var noop = 0
    }

    BeginProcessLoop(indent, r_value)
    {
        Append(this.class_functions,Concat(Concat(Concat(this.string_helper.Indentation(indent),"while "),r_value),":"))
    }

    FinishProcessLoop(indent, r_value)
    {
        var noop = 0
    }

    ProcessRtn(indent, r_value)
    {
        Append(this.class_functions,Concat(Concat(this.string_helper.Indentation(indent),"return "),r_value))
    }

    ProcessDeclaration(indent, type, l_value, r_value)
    {
        if (r_value=="")
        {
            r_value = this.GetDefault(type)
        }
        Append(this.class_functions,Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(indent),l_value),": '"),type),"' = "),r_value))
    }

    ProcessAssignment(indent, l_value, r_value)
    {
        Append(this.class_functions,Concat(Concat(Concat(this.string_helper.Indentation(indent),l_value)," = "),r_value))
    }

    ProcessCall(indent, call)
    {
        Append(this.class_functions,Concat(this.string_helper.Indentation(indent),call))
    }

    FinishProcessingClassFunctionDefinition(return_type, function_name, parameters)
    {
        Append(this.class_functions,"")
    }

    ProcessClassMemberDeclaration(member_type, member_name)
    {
        Append(this.class_init,Concat(Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(2),"self."),member_name),": "),member_type)," = "),this.GetDefault(member_type)))
    }

    FinishProcessingClass(class_name, implementing)
    {
        if (Size(this.class_init)==1)
        {
            Append(this.class_init,Concat(this.string_helper.Indentation(2),"pass"))
        }
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
        this.current_class = ""
    }

    WriteCommonFunctions(destination_file)
    {
        destination_file.WriteLine("def ClearList(input: list) -> None: input.clear()")
        destination_file.WriteLine("def Size(input: list) -> int: return len(input)")
        destination_file.WriteLine("def Element(input: list, element: int ) -> any: return input[element]")
        destination_file.WriteLine("def Append(input: list, element: any) -> None: input.append(element)")
        destination_file.WriteLine("def ClearMap(input: dict) -> None: input.clear()")
        destination_file.WriteLine("def SetKV(input: dict, key: str, element: any) -> None: input[key] = element")
        destination_file.WriteLine("def Keys(input: dict) -> list[str]:")
        destination_file.WriteLine("    result: list[str] = []")
        destination_file.WriteLine("    for key in input.keys():")
        destination_file.WriteLine("        result.append(key)")
        destination_file.WriteLine("    return result")
        destination_file.WriteLine("def HasKV(input: dict, key: str) -> bool: return key in input")
        destination_file.WriteLine("def GetKV(input: dict, key: str) -> any: return input[key]")
        destination_file.WriteLine("def Length(input: str) -> int: return len(input)")
        destination_file.WriteLine("def At(input: str, index: int) -> str: return input[index:index+1]")
        destination_file.WriteLine("def IntAt(input: str, index: int) -> int: return ord(input[index:index+1])")
        destination_file.WriteLine("def Concat(left: str, right: str) -> str: return left + right")
    }

    FinishProcessingCTCodeFile()
    {
        var destination_file_name = Concat(this.string_helper.StripDot(this.base_name),".py")
        var destination_file = this.system.OpenFileWriter(destination_file_name)
        if (Size(this.imports)>0)
        {
            this.string_helper.WriteLines(destination_file,this.imports)
            destination_file.WriteLine("")
        }
        this.WriteCommonFunctions(destination_file)
        destination_file.WriteLine("")
        this.string_helper.WriteLines(destination_file,this.interface_definitions)
        this.string_helper.WriteLines(destination_file,this.class_definitions)
    }

    GetDefault(python_type)
    {
        if (python_type=="int")
        {
            return "0"
        }
        if (python_type=="str")
        {
            return "\"\""
        }
        if (python_type=="bool")
        {
            return "False"
        }
        if (python_type=="float")
        {
            return "0.0"
        }
        if (python_type=="None")
        {
            return "None"
        }
        if (this.string_helper.BeginsWith("dict[str",python_type))
        {
            return "{}"
        }
        if (this.string_helper.BeginsWith("list[",python_type))
        {
            return "[]"
        }
        return "None"
    }

    MakeParametersString(self_type, parameters)
    {
        var result = Concat(Concat("(self: '",self_type),"'")
        var parameters_index = 0
        while (parameters_index<Size(parameters))
        {
            var parameter = Element(parameters,parameters_index)
            result = Concat(result,",")
            result = Concat(Concat(Concat(Concat(result,parameter.GetName()),": '"),parameter.GetType()),"'")
            parameters_index = parameters_index+1
        }
        result = Concat(result,")")
        return result
    }
}

