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

export class LogToConsole {
    constructor() {
        this.system = null
        this.c_t_code_file = null
        this.base_name = ""
        this.logger = null
        this.string_helper = null
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
        return 3
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
            return "thyself"
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
        return Concat("new ",type)
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
            return Concat(Concat(r_value_l,"||"),r_value_r)
        }
        if (op=="&&")
        {
            return Concat(Concat(r_value_l,"&&"),r_value_r)
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
            result = Concat(result,"[]")
            dimensions = dimensions-1
        }
        return result
    }

    GetMapType(singleton_type)
    {
        return Concat(singleton_type,"{}")
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
        var delimiter = "."
        var first_name = Element(name_parts,0)
        var result = first_name
        var name_parts_index = 1
        while (name_parts_index<Size(name_parts))
        {
            var name = Element(name_parts,name_parts_index)
            result = Concat(Concat(result,delimiter),name)
            name_parts_index = name_parts_index+1
        }
        return result
    }

    BeginProcessingCTCodeFile()
    {
        this.logger.WriteLine("BeginProcessingCTCodeFile")
    }

    FinishProcessingCTCodeFile()
    {
        this.logger.WriteLine("FinishProcessingCTCodeFile")
    }

    ProcessExdef(exdef)
    {
        this.logger.WriteLine(Concat(Concat(this.string_helper.Indentation(1),"ProcessExdef: "),exdef))
    }

    ProcessUnmanagedType(unmanaged_type)
    {
        this.logger.WriteLine(Concat(Concat(this.string_helper.Indentation(1),"ProcessUnmanagedType: "),unmanaged_type))
    }

    BeginProcessingInterface(interface_name)
    {
        this.logger.WriteLine(Concat(Concat(this.string_helper.Indentation(1),"BeginProcessingInterface: "),interface_name))
    }

    ProcessInterfaceFunctionDeclaration(return_type, function_name, parameters)
    {
        this.logger.WriteLine(Concat(Concat(Concat(Concat(this.string_helper.Indentation(2),"ProcessInterfaceFunctionDeclaration: "),return_type)," "),function_name))
    }

    FinishProcessingInterface(interface_name)
    {
        this.logger.WriteLine(Concat(Concat(this.string_helper.Indentation(1),"FinishProcessingInterface: "),interface_name))
    }

    BeginProcessingClass(class_name, implementing)
    {
        this.logger.WriteLine(Concat(Concat(Concat(Concat(this.string_helper.Indentation(1),"BeginProcessingClass: "),class_name)," "),implementing))
    }

    BeginProcessingClassFunctionDefinition(return_type, function_name, parameters)
    {
        this.logger.WriteLine(Concat(Concat(Concat(Concat(this.string_helper.Indentation(2),"BeginProcessingClassFunctionDefinition: "),return_type)," "),function_name))
    }

    BeginProcessCodeBlock(indent)
    {
        this.logger.WriteLine(Concat(this.string_helper.Indentation(indent),"BeginProcessCodeBlock"))
    }

    FinishProcessCodeBlock(indent)
    {
        this.logger.WriteLine(Concat(this.string_helper.Indentation(indent),"FinishProcessCodeBlock"))
    }

    BeginProcessConditional(indent, r_value)
    {
        this.logger.WriteLine(Concat(Concat(this.string_helper.Indentation(indent),"BeginProcessConditional: "),r_value))
    }

    ProcessElse(indent)
    {
        this.logger.WriteLine(Concat(this.string_helper.Indentation(indent),"ProcessElse"))
    }

    FinishProcessConditional(indent, r_value)
    {
        this.logger.WriteLine(Concat(Concat(this.string_helper.Indentation(indent),"FinishProcessConditional: "),r_value))
    }

    BeginProcessLoop(indent, r_value)
    {
        this.logger.WriteLine(Concat(Concat(this.string_helper.Indentation(indent),"BeginProcessLoop: "),r_value))
    }

    FinishProcessLoop(indent, r_value)
    {
        this.logger.WriteLine(Concat(Concat(this.string_helper.Indentation(indent),"FinishProcessLoop: "),r_value))
    }

    ProcessRtn(indent, r_value)
    {
        this.logger.WriteLine(Concat(Concat(this.string_helper.Indentation(indent),"ProcessRtn: "),r_value))
    }

    ProcessDeclaration(indent, type, l_value, r_value)
    {
        this.logger.WriteLine(Concat(Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(indent),"ProcessDeclaration: "),type)," "),l_value)," "),r_value))
    }

    ProcessAssignment(indent, l_value, r_value)
    {
        this.logger.WriteLine(Concat(Concat(Concat(Concat(this.string_helper.Indentation(indent),"ProcessAssignment: "),l_value)," "),r_value))
    }

    ProcessCall(indent, call)
    {
        this.logger.WriteLine(Concat(Concat(this.string_helper.Indentation(indent),"ProcessCall: "),call))
    }

    FinishProcessingClassFunctionDefinition(return_type, function_name, parameters)
    {
        this.logger.WriteLine(Concat(Concat(Concat(Concat(this.string_helper.Indentation(2),"FinishProcessingClassFunctionDefinition: "),return_type)," "),function_name))
    }

    ProcessClassMemberDeclaration(member_type, member_name)
    {
        this.logger.WriteLine(Concat(Concat(Concat(Concat(this.string_helper.Indentation(2),"ProcessClassMemberDeclaration: "),member_type)," "),member_name))
    }

    FinishProcessingClass(class_name, implementing)
    {
        this.logger.WriteLine(Concat(Concat(this.string_helper.Indentation(1),"FinishProcessingClass: "),class_name))
    }
}

