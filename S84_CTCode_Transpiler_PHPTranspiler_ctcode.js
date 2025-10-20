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

export class PHPTranspiler {
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
        var delimiter = "->"
        var first_name = Element(name_parts,0)
        var result = this.GetVariableName(first_name)
        var name_parts_index = 1
        while (name_parts_index<Size(name_parts))
        {
            var name = Element(name_parts,name_parts_index)
            result = Concat(Concat(result,delimiter),this.GetVariableName(name))
            name_parts_index = name_parts_index+1
        }
        return Concat("$",result)
    }

    ConvertCall(name_chain, parameters)
    {
        var result = Element(name_chain,0)
        if (Size(name_chain)>1)
        {
            result = Concat("$",result)
        }
        var name_chain_index = 1
        while (name_chain_index<Size(name_chain))
        {
            var name_part = Element(name_chain,name_chain_index)
            result = Concat(Concat(result,"->"),name_part)
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
        return variable
    }

    Escape(input)
    {
        var result = ""
        var input_index = 0
        var in_escape = false
        while (input_index<Length(input))
        {
            var character = At(input,input_index)
            if (character=="'")
            {
                result = Concat(result,"\\")
            }
            if (! in_escape && character=="\\")
            {
                in_escape = true
            }
            else
            {
                in_escape = false
                if (character=="\\")
                {
                    result = Concat(result,"\\")
                }
                result = Concat(result,character)
            }
            input_index = input_index+1
        }
        return result
    }

    ConvertString(literal)
    {
        return Concat(Concat("'",this.Escape(literal)),"'")
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
        var value = this.string_helper.SnakeCaseToCamelCase(name)
        if (this.string_helper.IsReserved(value))
        {
            return Concat("ReservedPrefix",value)
        }
        return value
    }

    GetDimensionalType(singleton_type, dimensions)
    {
        return "?array"
    }

    GetMapType(singleton_type)
    {
        return "?array"
    }

    GetPrimativeType(c_t_type)
    {
        if (c_t_type=="int")
        {
            return "?int"
        }
        if (c_t_type=="string")
        {
            return "?string"
        }
        if (c_t_type=="bool")
        {
            return "?bool"
        }
        if (c_t_type=="float")
        {
            return "?float"
        }
        if (c_t_type=="void")
        {
            return "void"
        }
        return ""
    }

    GetDefinedType(c_t_type)
    {
        return Concat("?",c_t_type)
    }

    GetQualifiedTypeName(name_parts)
    {
        var delimiter = "\\"
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
        ClearList(this.class_members)
    }

    FinishProcessingCTCodeFile()
    {
        var destination_file_name = Concat(this.base_name,".php")
        var destination_file = this.system.OpenFileWriter(destination_file_name)
        destination_file.WriteLine("<?php")
        destination_file.WriteLine(Concat(Concat("namespace ",this.string_helper.DotToFwdSlash(this.base_name)),";"))
        destination_file.WriteLine("")
        if (Size(this.imports)>0)
        {
            this.string_helper.WriteLines(destination_file,this.imports)
            destination_file.WriteLine("")
        }
        this.WriteCommonFunctions(destination_file)
        destination_file.WriteLine("")
        this.string_helper.WriteLines(destination_file,this.interface_definitions)
        this.string_helper.WriteLines(destination_file,this.class_definitions)
        destination_file.WriteLine("?>")
    }

    ProcessExdef(exdef)
    {
        Append(this.imports,Concat(Concat("include_once \"",exdef),".php\";"))
    }

    ProcessUnmanagedType(unmanaged_type)
    {
    }

    BeginProcessingInterface(interface_name)
    {
        this.current_interface = interface_name
        Append(this.interface_definitions,Concat(Concat("interface ",interface_name)," {"))
    }

    ProcessInterfaceFunctionDeclaration(return_type, function_name, parameters)
    {
        Append(this.interface_definitions,Concat(Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(1),"public function "),function_name),this.MakeParametersString(parameters)),": "),return_type),";"))
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
            Append(this.class_definitions,Concat(Concat("class ",class_name)," {"))
        }
        else
        {
            Append(this.class_definitions,Concat(Concat(Concat(Concat("class ",class_name)," implements "),implementing)," {"))
        }
        ClearList(this.class_init)
        ClearList(this.class_functions)
        ClearList(this.class_members)
        Append(this.class_init,Concat(this.string_helper.Indentation(1),"public function __construct() {"))
    }

    BeginProcessingClassFunctionDefinition(return_type, function_name, parameters)
    {
        Append(this.class_functions,"")
        Append(this.class_functions,Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(1),"public function "),function_name),this.MakeParametersString(parameters)),": "),return_type))
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
        Append(this.class_functions,Concat(Concat(Concat(this.string_helper.Indentation(indent),"if ("),r_value),")"))
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
        Append(this.class_functions,Concat(Concat(Concat(this.string_helper.Indentation(indent),"while ("),r_value),")"))
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
        Append(this.class_functions,Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(indent),"$"),l_value)," = "),r_value),";"))
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
    }

    ProcessClassMemberDeclaration(member_type, member_name)
    {
        Append(this.class_init,Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(2),"$this->"),member_name)," = "),this.GetDefault(member_type)),";"))
        Append(this.class_members,Concat(Concat(Concat(this.string_helper.Indentation(1),"private $"),member_name),";"))
    }

    FinishProcessingClass(class_name, implementing)
    {
        Append(this.class_init,Concat(this.string_helper.Indentation(1),"}"))
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
        Append(this.class_definitions,"")
        var class_members_index = 0
        while (class_members_index<Size(this.class_members))
        {
            var line = Element(this.class_members,class_members_index)
            Append(this.class_definitions,line)
            class_members_index = class_members_index+1
        }
        Append(this.class_definitions,"}")
        Append(this.class_definitions,"")
        this.current_class = ""
    }

    WriteCommonFunctions(destination_file)
    {
        destination_file.WriteLine("function ClearList(array & $input): void { $input = array(); }")
        destination_file.WriteLine("function Size(array $input): int { return count($input); }")
        destination_file.WriteLine("function Element(array $input, int $element) { return $input[$element]; }")
        destination_file.WriteLine("function Append(array & $input, mixed $element): void { $input[] = $element; }")
        destination_file.WriteLine("function ClearMap(array & $input): void { reset($input); }")
        destination_file.WriteLine("function SetKV(array & $input, string $key, mixed $element): void { $input[$key] = $element; }")
        destination_file.WriteLine("function Keys(array $input): array { return array_keys($input); }")
        destination_file.WriteLine("function HasKV(array $input, string $key): bool { return array_key_exists($key, $input); }")
        destination_file.WriteLine("function GetKV(array $input, string $key) { return $input[$key]; }")
        destination_file.WriteLine("function Length(string $input): int { return strlen($input); }")
        destination_file.WriteLine("function At(string $input, int $index): string { return substr($input, $index, 1); }")
        destination_file.WriteLine("function IntAt(string $input, int $index): int { return ord(substr($input, $index, 1)); }")
        destination_file.WriteLine("function Concat(string $left, string $right): string { return $left . $right; }")
    }

    GetDefault(php_type)
    {
        if (php_type=="?int")
        {
            return "0"
        }
        if (php_type=="?string")
        {
            return "\"\""
        }
        if (php_type=="?bool")
        {
            return "false"
        }
        if (php_type=="?float")
        {
            return "0.0"
        }
        if (php_type=="void")
        {
            return "null"
        }
        if (php_type=="?array")
        {
            return "array()"
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
            result = Concat(Concat(Concat(result,parameter.ReservedPrefixGetType())," $"),parameter.GetName())
            parameters_index = parameters_index+1
        }
        result = Concat(result,")")
        return result
    }
}

