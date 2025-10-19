import S84_CTCode_dbnf_ctcode
import S84_CTCode_Transpiler_StandardStructure_ctcode
import S84_CTCode_Transpiler_StringHelper_ctcode

def ClearList(input: list) -> None: input.clear()
def Size(input: list) -> int: return len(input)
def Element(input: list, element: int ) -> any: return input[element]
def Append(input: list, element: any) -> None: input.append(element)
def ClearMap(input: dict) -> None: input.clear()
def SetKV(input: dict, key: str, element: any) -> None: input[key] = element
def Keys(input: dict) -> list[str]:
    result: list[str] = []
    for key in input.keys():
        result.append(key)
    return result
def HasKV(input: dict, key: str) -> bool: return key in input
def GetKV(input: dict, key: str) -> any: return input[key]
def Length(input: str) -> int: return len(input)
def At(input: str, index: int) -> str: return input[index:index+1]
def IntAt(input: str, index: int) -> int: return ord(input[index:index+1])
def Concat(left: str, right: str) -> str: return left + right

class PHPTranspiler(S84_CTCode_Transpiler_StandardStructure_ctcode.TargetSpecificFunctions):
    def __init__(self: 'PHPTranspiler'):
        self.system: S84_CTCode_System_ctcode.System = None
        self.c_t_code_file: S84_CTCode_dbnf_ctcode.CTCodeFile = None
        self.base_name: str = ""
        self.logger: S84_CTCode_System_ctcode.OutputStream = None
        self.string_helper: S84_CTCode_Transpiler_StringHelper_ctcode.StringHelper = None
        self.imports: list[str] = []
        self.current_interface: str = ""
        self.interface_definitions: list[str] = []
        self.current_class: str = ""
        self.class_definitions: list[str] = []
        self.class_init: list[str] = []
        self.class_functions: list[str] = []
        self.class_members: list[str] = []

    def Initialize(self: 'PHPTranspiler') -> 'None':
        self.string_helper = S84_CTCode_Transpiler_StringHelper_ctcode.StringHelper()

    def SetSystem(self: 'PHPTranspiler',system: 'S84_CTCode_System_ctcode.System') -> 'None':
        self.system = system

    def SetCTCodeFile(self: 'PHPTranspiler',c_t_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile') -> 'None':
        self.c_t_code_file = c_t_code_file

    def SetBaseName(self: 'PHPTranspiler',base_name: 'str') -> 'None':
        self.base_name = base_name

    def SetLogger(self: 'PHPTranspiler',logger: 'S84_CTCode_System_ctcode.OutputStream') -> 'None':
        self.logger = logger

    def GetBaseIndentation(self: 'PHPTranspiler') -> 'int':
        return 1

    def GetCallName(self: 'PHPTranspiler',name: 'str') -> 'str':
        value: 'str' = self.string_helper.SnakeCaseToCamelCase(name)
        if self.string_helper.IsReserved(value):
            return Concat("ReservedPrefix",value)
        return value

    def GetVariableName(self: 'PHPTranspiler',name: 'str') -> 'str':
        value: 'str' = self.string_helper.CamelCaseToSnakeCase(name)
        if value=="myself":
            return "this"
        if self.string_helper.IsReserved(value):
            return Concat("reserved_prefix_",value)
        return value

    def GetVariableChain(self: 'PHPTranspiler',name_parts: 'list[str]') -> 'str':
        delimiter: 'str' = "->"
        first_name: 'str' = Element(name_parts,0)
        result: 'str' = self.GetVariableName(first_name)
        name_parts_index: 'int' = 1
        while name_parts_index<Size(name_parts):
            name: 'str' = Element(name_parts,name_parts_index)
            result = Concat(Concat(result,delimiter),self.GetVariableName(name))
            name_parts_index = name_parts_index+1
        return Concat("$",result)

    def ConvertCall(self: 'PHPTranspiler',name_chain: 'list[str]',parameters: 'list[str]') -> 'str':
        result: 'str' = Element(name_chain,0)
        if Size(name_chain)>1:
            result = Concat("$",result)
        name_chain_index: 'int' = 1
        while name_chain_index<Size(name_chain):
            name_part: 'str' = Element(name_chain,name_chain_index)
            result = Concat(Concat(result,"->"),name_part)
            name_chain_index = name_chain_index+1
        result = Concat(result,"(")
        if Size(parameters)>0:
            result = Concat(result,Element(parameters,0))
            parameters_index: 'int' = 1
            while parameters_index<Size(parameters):
                parameter: 'str' = Element(parameters,parameters_index)
                result = Concat(result,",")
                result = Concat(result,parameter)
                parameters_index = parameters_index+1
        result = Concat(result,")")
        return result

    def ConvertAllocate(self: 'PHPTranspiler',type: 'str') -> 'str':
        return Concat(Concat("new ",type),"()")

    def ConvertByte(self: 'PHPTranspiler',high: 'str',low: 'str') -> 'str':
        return Concat(Concat("0x",high),low)

    def ConvertDecimal(self: 'PHPTranspiler',reserved_prefix_decimal: 'str') -> 'str':
        return reserved_prefix_decimal

    def ConvertNumber(self: 'PHPTranspiler',number: 'str') -> 'str':
        return number

    def ConvertBoolean(self: 'PHPTranspiler',reserved_prefix_boolean: 'str') -> 'str':
        if reserved_prefix_boolean=="true":
            return "true"
        if reserved_prefix_boolean=="false":
            return "false"
        return ""

    def ConvertVariable(self: 'PHPTranspiler',variable: 'str') -> 'str':
        return variable

    def Escape(self: 'PHPTranspiler',input: 'str') -> 'str':
        result: 'str' = ""
        input_index: 'int' = 0
        in_escape: 'bool' = False
        while input_index<Length(input):
            character: 'str' = At(input,input_index)
            if character=="'":
                result = Concat(result,"\\")
            if not in_escape and character=="\\":
                in_escape = True
            else:
                in_escape = False
                if character=="\\":
                    result = Concat(result,"\\")
                result = Concat(result,character)
            input_index = input_index+1
        return result

    def ConvertString(self: 'PHPTranspiler',literal: 'str') -> 'str':
        return Concat(Concat("'",self.Escape(literal)),"'")

    def UnaryOperator(self: 'PHPTranspiler',op: 'str',r_value: 'str') -> 'str':
        if op=="!":
            return Concat("!",r_value)
        return r_value

    def BinaryOperator(self: 'PHPTranspiler',op: 'str',r_value_l: 'str',r_value_r: 'str') -> 'str':
        if op=="+":
            return Concat(Concat(r_value_l,"+"),r_value_r)
        if op=="-":
            return Concat(Concat(r_value_l,"-"),r_value_r)
        if op=="<=":
            return Concat(Concat(r_value_l,"<="),r_value_r)
        if op==">=":
            return Concat(Concat(r_value_l,">="),r_value_r)
        if op=="==":
            return Concat(Concat(r_value_l,"=="),r_value_r)
        if op=="!=":
            return Concat(Concat(r_value_l,"!="),r_value_r)
        if op=="<":
            return Concat(Concat(r_value_l,"<"),r_value_r)
        if op==">":
            return Concat(Concat(r_value_l,">"),r_value_r)
        if op=="||":
            return Concat(Concat(r_value_l,"||"),r_value_r)
        if op=="&&":
            return Concat(Concat(r_value_l,"&&"),r_value_r)
        return ""

    def GetTypeName(self: 'PHPTranspiler',name: 'str') -> 'str':
        value: 'str' = self.string_helper.SnakeCaseToCamelCase(name)
        if self.string_helper.IsReserved(value):
            return Concat("ReservedPrefix",value)
        return value

    def GetDimensionalType(self: 'PHPTranspiler',singleton_type: 'str',dimensions: 'int') -> 'str':
        return "?array"

    def GetMapType(self: 'PHPTranspiler',singleton_type: 'str') -> 'str':
        return "?array"

    def GetPrimativeType(self: 'PHPTranspiler',c_t_type: 'str') -> 'str':
        if c_t_type=="int":
            return "?int"
        if c_t_type=="string":
            return "?string"
        if c_t_type=="bool":
            return "?bool"
        if c_t_type=="float":
            return "?float"
        if c_t_type=="void":
            return "void"
        return ""

    def GetDefinedType(self: 'PHPTranspiler',c_t_type: 'str') -> 'str':
        return Concat("?",c_t_type)

    def GetQualifiedTypeName(self: 'PHPTranspiler',name_parts: 'list[str]') -> 'str':
        delimiter: 'str' = "\\"
        name_parts_index: 'int' = Size(name_parts)-1
        type_part: 'str' = Element(name_parts,name_parts_index)
        result: 'str' = self.GetTypeName(type_part)
        if name_parts_index>0:
            while name_parts_index>0:
                name_parts_index = name_parts_index-1
                result = Concat(delimiter,result)
                name_part: 'str' = Element(name_parts,name_parts_index)
                result = Concat(name_part,result)
            result = Concat(delimiter,result)
        return result

    def BeginProcessingCTCodeFile(self: 'PHPTranspiler') -> 'None':
        ClearList(self.imports)
        self.current_interface = ""
        ClearList(self.interface_definitions)
        self.current_class = ""
        ClearList(self.class_definitions)
        ClearList(self.class_init)
        ClearList(self.class_functions)
        ClearList(self.class_members)

    def FinishProcessingCTCodeFile(self: 'PHPTranspiler') -> 'None':
        destination_file_name: 'str' = Concat(self.base_name,".php")
        destination_file: 'S84_CTCode_System_ctcode.OutputStream' = self.system.OpenFileWriter(destination_file_name)
        destination_file.WriteLine("<?php")
        destination_file.WriteLine(Concat(Concat("namespace ",self.string_helper.DotToFwdSlash(self.base_name)),";"))
        destination_file.WriteLine("")
        if Size(self.imports)>0:
            self.string_helper.WriteLines(destination_file,self.imports)
            destination_file.WriteLine("")
        self.WriteCommonFunctions(destination_file)
        destination_file.WriteLine("")
        self.string_helper.WriteLines(destination_file,self.interface_definitions)
        self.string_helper.WriteLines(destination_file,self.class_definitions)
        destination_file.WriteLine("?>")

    def ProcessExdef(self: 'PHPTranspiler',exdef: 'str') -> 'None':
        Append(self.imports,Concat(Concat("include_once \"",exdef),".php\";"))

    def ProcessUnmanagedType(self: 'PHPTranspiler',unmanaged_type: 'str') -> 'None':
        pass

    def BeginProcessingInterface(self: 'PHPTranspiler',interface_name: 'str') -> 'None':
        self.current_interface = interface_name
        Append(self.interface_definitions,Concat(Concat("interface ",interface_name)," {"))

    def ProcessInterfaceFunctionDeclaration(self: 'PHPTranspiler',return_type: 'str',function_name: 'str',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'None':
        Append(self.interface_definitions,Concat(Concat(Concat(Concat(Concat(Concat(self.string_helper.Indentation(1),"public function "),function_name),self.MakeParametersString(parameters)),": "),return_type),";"))

    def FinishProcessingInterface(self: 'PHPTranspiler',interface_name: 'str') -> 'None':
        Append(self.interface_definitions,"}")
        Append(self.interface_definitions,"")
        self.current_interface = ""

    def BeginProcessingClass(self: 'PHPTranspiler',class_name: 'str',implementing: 'str') -> 'None':
        self.current_class = class_name
        if implementing=="":
            Append(self.class_definitions,Concat(Concat("class ",class_name)," {"))
        else:
            Append(self.class_definitions,Concat(Concat(Concat(Concat("class ",class_name)," implements "),implementing)," {"))
        ClearList(self.class_init)
        ClearList(self.class_functions)
        ClearList(self.class_members)
        Append(self.class_init,Concat(self.string_helper.Indentation(1),"public function __construct() {"))

    def BeginProcessingClassFunctionDefinition(self: 'PHPTranspiler',return_type: 'str',function_name: 'str',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'None':
        Append(self.class_functions,"")
        Append(self.class_functions,Concat(Concat(Concat(Concat(Concat(self.string_helper.Indentation(1),"public function "),function_name),self.MakeParametersString(parameters)),": "),return_type))

    def BeginProcessCodeBlock(self: 'PHPTranspiler',indent: 'int') -> 'None':
        Append(self.class_functions,Concat(self.string_helper.Indentation(indent),"{"))

    def FinishProcessCodeBlock(self: 'PHPTranspiler',indent: 'int') -> 'None':
        Append(self.class_functions,Concat(self.string_helper.Indentation(indent),"}"))

    def BeginProcessConditional(self: 'PHPTranspiler',indent: 'int',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(self.string_helper.Indentation(indent),"if ("),r_value),")"))

    def ProcessElse(self: 'PHPTranspiler',indent: 'int') -> 'None':
        Append(self.class_functions,Concat(self.string_helper.Indentation(indent),"else"))

    def FinishProcessConditional(self: 'PHPTranspiler',indent: 'int',r_value: 'str') -> 'None':
        pass

    def BeginProcessLoop(self: 'PHPTranspiler',indent: 'int',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(self.string_helper.Indentation(indent),"while ("),r_value),")"))

    def FinishProcessLoop(self: 'PHPTranspiler',indent: 'int',r_value: 'str') -> 'None':
        pass

    def ProcessRtn(self: 'PHPTranspiler',indent: 'int',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(self.string_helper.Indentation(indent),"return "),r_value),";"))

    def ProcessDeclaration(self: 'PHPTranspiler',indent: 'int',type: 'str',l_value: 'str',r_value: 'str') -> 'None':
        if r_value=="":
            r_value = self.GetDefault(type)
        Append(self.class_functions,Concat(Concat(Concat(Concat(Concat(self.string_helper.Indentation(indent),"$"),l_value)," = "),r_value),";"))

    def ProcessAssignment(self: 'PHPTranspiler',indent: 'int',l_value: 'str',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(Concat(self.string_helper.Indentation(indent),l_value)," = "),r_value),";"))

    def ProcessCall(self: 'PHPTranspiler',indent: 'int',call: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(self.string_helper.Indentation(indent),call),";"))

    def FinishProcessingClassFunctionDefinition(self: 'PHPTranspiler',return_type: 'str',function_name: 'str',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'None':
        pass

    def ProcessClassMemberDeclaration(self: 'PHPTranspiler',member_type: 'str',member_name: 'str') -> 'None':
        Append(self.class_init,Concat(Concat(Concat(Concat(Concat(self.string_helper.Indentation(2),"$this->"),member_name)," = "),self.GetDefault(member_type)),";"))
        Append(self.class_members,Concat(Concat(Concat(self.string_helper.Indentation(1),"private $"),member_name),";"))

    def FinishProcessingClass(self: 'PHPTranspiler',class_name: 'str',implementing: 'str') -> 'None':
        Append(self.class_init,Concat(self.string_helper.Indentation(1),"}"))
        class_init_index: 'int' = 0
        while class_init_index<Size(self.class_init):
            line: 'str' = Element(self.class_init,class_init_index)
            Append(self.class_definitions,line)
            class_init_index = class_init_index+1
        class_functions_index: 'int' = 0
        while class_functions_index<Size(self.class_functions):
            line: 'str' = Element(self.class_functions,class_functions_index)
            Append(self.class_definitions,line)
            class_functions_index = class_functions_index+1
        Append(self.class_definitions,"")
        class_members_index: 'int' = 0
        while class_members_index<Size(self.class_members):
            line: 'str' = Element(self.class_members,class_members_index)
            Append(self.class_definitions,line)
            class_members_index = class_members_index+1
        Append(self.class_definitions,"}")
        Append(self.class_definitions,"")
        self.current_class = ""

    def WriteCommonFunctions(self: 'PHPTranspiler',destination_file: 'S84_CTCode_System_ctcode.OutputStream') -> 'None':
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

    def GetDefault(self: 'PHPTranspiler',php_type: 'str') -> 'str':
        if php_type=="?int":
            return "0"
        if php_type=="?string":
            return "\"\""
        if php_type=="?bool":
            return "false"
        if php_type=="?float":
            return "0.0"
        if php_type=="void":
            return "null"
        if php_type=="?array":
            return "array()"
        return "null"

    def MakeParametersString(self: 'PHPTranspiler',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'str':
        result: 'str' = "("
        parameters_index: 'int' = 0
        while parameters_index<Size(parameters):
            parameter: 'S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration' = Element(parameters,parameters_index)
            if parameters_index!=0:
                result = Concat(result,", ")
            result = Concat(Concat(Concat(result,parameter.ReservedPrefixGetType())," $"),parameter.GetName())
            parameters_index = parameters_index+1
        result = Concat(result,")")
        return result

