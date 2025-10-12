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

export class RubyTranspiler {
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

    IsReserved(name)
    {
        return false || this.string_helper.BeginsWith("ReservedPrefix",name) || this.string_helper.BeginsWith("reserved_prefix_",name) || name=="end" || name=="Return" || name=="String" || name=="GetType" || name=="string" || name=="boolean" || name=="char" || name=="float" || name=="decimal"
    }

    GetCallName(name)
    {
        var value = this.string_helper.SnakeCaseToCamelCase(name)
        if (this.IsReserved(value))
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
            return "self"
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
            result = Concat(result,delimiter)
            if (result=="self.")
            {
                result = "@"
            }
            result = Concat(result,this.GetVariableName(name))
            name_parts_index = name_parts_index+1
        }
        return result
    }

    ConvertCall(name_chain, parameters)
    {
        var result = Element(name_chain,0)
        var name_chain_index = 1
        var last_name_chain_index = Size(name_chain)-1
        while (name_chain_index<Size(name_chain))
        {
            var name_part = Element(name_chain,name_chain_index)
            result = Concat(result,".")
            if (name_chain_index!=last_name_chain_index)
            {
                if (result=="self.")
                {
                    result = "@"
                }
            }
            result = Concat(result,name_part)
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
        return Concat(type,".new()")
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
            return Concat("! ",r_value)
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
            return Concat(Concat(r_value_l," || "),r_value_r)
        }
        if (op=="&&")
        {
            return Concat(Concat(r_value_l," && "),r_value_r)
        }
        return ""
    }

    GetTypeName(name)
    {
        var value = this.string_helper.SnakeCaseToCamelCase(name)
        if (this.IsReserved(value))
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
            return "string"
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
        var delimiter = "::"
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
                result = Concat(this.string_helper.ToUpper(name_part),result)
            }
            result = Concat(delimiter,result)
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
        Append(this.imports,Concat(Concat("require '",exdef),"'"))
    }

    ProcessUnmanagedType(unmanaged_type)
    {
    }

    BeginProcessingInterface(interface_name)
    {
        this.current_interface = interface_name
        Append(this.interface_definitions,Concat("class ",interface_name))
    }

    ProcessInterfaceFunctionDeclaration(return_type, function_name, parameters)
    {
        Append(this.interface_definitions,Concat(Concat(Concat(Concat(this.string_helper.Indentation(1),"def "),function_name),this.MakeParametersString(parameters)),"; end"))
    }

    FinishProcessingInterface(interface_name)
    {
        Append(this.interface_definitions,"end")
        Append(this.interface_definitions,"")
        this.current_interface = ""
    }

    BeginProcessingClass(class_name, implementing)
    {
        this.current_class = class_name
        if (implementing=="")
        {
            Append(this.class_definitions,Concat("class ",class_name))
        }
        else
        {
            Append(this.class_definitions,Concat(Concat(Concat("class ",class_name)," < "),implementing))
        }
        ClearList(this.class_init)
        ClearList(this.class_functions)
        Append(this.class_init,Concat(this.string_helper.Indentation(1),"def initialize()"))
    }

    BeginProcessingClassFunctionDefinition(return_type, function_name, parameters)
    {
        Append(this.class_functions,"")
        Append(this.class_functions,Concat(Concat(Concat(this.string_helper.Indentation(1),"def "),function_name),this.MakeParametersString(parameters)))
    }

    BeginProcessCodeBlock(indent)
    {
    }

    FinishProcessCodeBlock(indent)
    {
    }

    BeginProcessConditional(indent, r_value)
    {
        Append(this.class_functions,Concat(Concat(Concat(this.string_helper.Indentation(indent),"if ("),r_value),")"))
    }

    ProcessElse(indent)
    {
        Append(this.class_functions,Concat(this.string_helper.Indentation(indent),"else"))
    }

    FinishProcessConditional(indent, r_value)
    {
        Append(this.class_functions,Concat(this.string_helper.Indentation(indent),"end"))
    }

    BeginProcessLoop(indent, r_value)
    {
        Append(this.class_functions,Concat(Concat(Concat(this.string_helper.Indentation(indent),"while ("),r_value),")"))
    }

    FinishProcessLoop(indent, r_value)
    {
        Append(this.class_functions,Concat(this.string_helper.Indentation(indent),"end"))
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
        Append(this.class_functions,Concat(Concat(Concat(this.string_helper.Indentation(indent),l_value)," = "),r_value))
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
        Append(this.class_functions,Concat(this.string_helper.Indentation(1),"end"))
    }

    ProcessClassMemberDeclaration(member_type, member_name)
    {
        Append(this.class_init,Concat(Concat(Concat(Concat(this.string_helper.Indentation(2),"@"),member_name)," = "),this.GetDefault(member_type)))
    }

    FinishProcessingClass(class_name, implementing)
    {
        Append(this.class_init,Concat(this.string_helper.Indentation(1),"end"))
        var class_init_index = 0
        while (class_init_index<Size(this.class_init))
        {
            var line = Element(this.class_init,class_init_index)
            Append(this.class_definitions,line)
            class_init_index = class_init_index+1
        }
        var class_functions_index = 0
        while (class_functions_index<Size(this.class_functions))
        {
            var line = Element(this.class_functions,class_functions_index)
            Append(this.class_definitions,line)
            class_functions_index = class_functions_index+1
        }
        Append(this.class_definitions,"end")
        Append(this.class_definitions,"")
        this.current_class = ""
    }

    WriteCommonFunctions(destination_file)
    {
        destination_file.WriteLine("def ClearList(input); input.clear(); end")
        destination_file.WriteLine("def Size(input); return input.length(); end")
        destination_file.WriteLine("def Element(input, element); return input[element]; end")
        destination_file.WriteLine("def Append(input, element); input.push(element); end")
        destination_file.WriteLine("def ClearMap(input); input.clear(); end")
        destination_file.WriteLine("def SetKV(input, key, element); input[key] = element; end")
        destination_file.WriteLine("def Keys(input); return input.keys(); end")
        destination_file.WriteLine("def HasKV(input, key); return input.has_key?(key); end")
        destination_file.WriteLine("def GetKV(input, key); return input[key]; end")
        destination_file.WriteLine("def Length(input); return input.length(); end")
        destination_file.WriteLine("def At(input, index); return input[index]; end")
        destination_file.WriteLine("def IntAt(input, index); return input[index].ord(); end")
        destination_file.WriteLine("def Concat(left, right); return left + right; end")
    }

    TokenizeBaseName(name)
    {
        var base_name_tokens = []
        var current_token = ""
        var index = 0
        while (index<Length(name))
        {
            var character = At(name,index)
            if (character==".")
            {
                Append(base_name_tokens,current_token)
                current_token = ""
            }
            else
            {
                current_token = Concat(current_token,character)
            }
            index = index+1
        }
        Append(base_name_tokens,current_token)
        return base_name_tokens
    }

    WriteBeginingNamespace(file)
    {
        var base_name_tokens = this.TokenizeBaseName(this.base_name)
        var base_name_tokens_index = 0
        while (base_name_tokens_index<Size(base_name_tokens))
        {
            var base_name_token = Element(base_name_tokens,base_name_tokens_index)
            file.WriteLine(Concat("module ",this.string_helper.ToUpper(base_name_token)))
            base_name_tokens_index = base_name_tokens_index+1
        }
    }

    WriteEndingNamespace(file)
    {
        var base_name_tokens = this.TokenizeBaseName(this.base_name)
        var base_name_tokens_index = 0
        while (base_name_tokens_index<Size(base_name_tokens))
        {
            var base_name_token = Element(base_name_tokens,base_name_tokens_index)
            file.WriteLine("end")
            base_name_tokens_index = base_name_tokens_index+1
        }
    }

    FinishProcessingCTCodeFile()
    {
        var destination_file_name = Concat(this.base_name,".rb")
        var destination_file = this.system.OpenFileWriter(destination_file_name)
        if (Size(this.imports)>0)
        {
            this.string_helper.WriteLines(destination_file,this.imports)
            destination_file.WriteLine("")
        }
        this.WriteCommonFunctions(destination_file)
        destination_file.WriteLine("")
        this.WriteBeginingNamespace(destination_file)
        destination_file.WriteLine("")
        this.string_helper.WriteLines(destination_file,this.interface_definitions)
        this.string_helper.WriteLines(destination_file,this.class_definitions)
        this.WriteEndingNamespace(destination_file)
    }

    GetDefault(javascript_type)
    {
        if (javascript_type=="int")
        {
            return "0"
        }
        if (javascript_type=="string")
        {
            return "\"\""
        }
        if (javascript_type=="bool")
        {
            return "false"
        }
        if (javascript_type=="float")
        {
            return "0.0"
        }
        if (javascript_type=="void")
        {
            return "nil"
        }
        if (this.string_helper.BeginsWith("dict[str",javascript_type))
        {
            return "Hash.new()"
        }
        if (this.string_helper.BeginsWith("list[",javascript_type))
        {
            return "Array.new()"
        }
        return "nil"
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
            result = Concat(result,parameter.GetName())
            parameters_index = parameters_index+1
        }
        result = Concat(result,")")
        return result
    }
}

