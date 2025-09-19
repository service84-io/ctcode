import S84_CTCode_dbnf_ctcode
import S84_CTCode_System_ctcode
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

class NodeJSTranspiler(S84_CTCode_Transpiler_StandardStructure_ctcode.TargetSpecificFunctions):
    def __init__(self: 'NodeJSTranspiler'):
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

    def Initialize(self: 'NodeJSTranspiler') -> 'None':
        self.string_helper = S84_CTCode_Transpiler_StringHelper_ctcode.StringHelper()

    def SetSystem(self: 'NodeJSTranspiler',system: 'S84_CTCode_System_ctcode.System') -> 'None':
        self.system = system

    def SetCTCodeFile(self: 'NodeJSTranspiler',c_t_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile') -> 'None':
        self.c_t_code_file = c_t_code_file

    def SetBaseName(self: 'NodeJSTranspiler',base_name: 'str') -> 'None':
        self.base_name = base_name

    def SetLogger(self: 'NodeJSTranspiler',logger: 'S84_CTCode_System_ctcode.OutputStream') -> 'None':
        self.logger = logger

    def GetBaseIndentation(self: 'NodeJSTranspiler') -> 'int':
        return 1

    def GetCallName(self: 'NodeJSTranspiler',name: 'str') -> 'str':
        return self.string_helper.SnakeCaseToCamelCase(name)

    def GetVariableName(self: 'NodeJSTranspiler',name: 'str') -> 'str':
        value: 'str' = self.string_helper.CamelCaseToSnakeCase(name)
        if value=="myself":
            return "this"
        return value

    def GetVariableChain(self: 'NodeJSTranspiler',name_parts: 'list[str]') -> 'str':
        delimiter: 'str' = "."
        first_name: 'str' = Element(name_parts,0)
        result: 'str' = self.GetVariableName(first_name)
        name_parts_index: 'int' = 1
        while name_parts_index<Size(name_parts):
            name: 'str' = Element(name_parts,name_parts_index)
            result = Concat(Concat(result,delimiter),self.GetVariableName(name))
            name_parts_index = name_parts_index+1
        return result

    def ConvertCall(self: 'NodeJSTranspiler',name_chain: 'list[str]',parameters: 'list[str]') -> 'str':
        result: 'str' = Element(name_chain,0)
        name_chain_index: 'int' = 1
        while name_chain_index<Size(name_chain):
            name_part: 'str' = Element(name_chain,name_chain_index)
            result = Concat(Concat(result,"."),name_part)
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

    def ConvertAllocate(self: 'NodeJSTranspiler',type: 'str') -> 'str':
        return Concat(Concat("new ",type),"()")

    def ConvertByte(self: 'NodeJSTranspiler',high: 'str',low: 'str') -> 'str':
        return Concat(Concat("0x",high),low)

    def ConvertDecimal(self: 'NodeJSTranspiler',decimal: 'str') -> 'str':
        return decimal

    def ConvertNumber(self: 'NodeJSTranspiler',number: 'str') -> 'str':
        return number

    def ConvertBoolean(self: 'NodeJSTranspiler',boolean: 'str') -> 'str':
        if boolean=="true":
            return "true"
        if boolean=="false":
            return "false"
        return ""

    def ConvertVariable(self: 'NodeJSTranspiler',variable: 'str') -> 'str':
        return variable

    def ConvertString(self: 'NodeJSTranspiler',literal: 'str') -> 'str':
        return Concat(Concat("\"",literal),"\"")

    def UnaryOperator(self: 'NodeJSTranspiler',op: 'str',r_value: 'str') -> 'str':
        if op=="!":
            return Concat("! ",r_value)
        return r_value

    def BinaryOperator(self: 'NodeJSTranspiler',op: 'str',r_value_l: 'str',r_value_r: 'str') -> 'str':
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
            return Concat(Concat(r_value_l," || "),r_value_r)
        if op=="&&":
            return Concat(Concat(r_value_l," && "),r_value_r)
        return ""

    def GetTypeName(self: 'NodeJSTranspiler',name: 'str') -> 'str':
        return self.string_helper.SnakeCaseToCamelCase(name)

    def GetDimensionalType(self: 'NodeJSTranspiler',singleton_type: 'str',dimensions: 'int') -> 'str':
        result: 'str' = singleton_type
        while dimensions>0:
            result = Concat(Concat("list[",result),"]")
            dimensions = dimensions-1
        return result

    def GetMapType(self: 'NodeJSTranspiler',singleton_type: 'str') -> 'str':
        return Concat(Concat("dict[str, ",singleton_type),"]")

    def GetPrimativeType(self: 'NodeJSTranspiler',c_t_type: 'str') -> 'str':
        if c_t_type=="int":
            return "int"
        if c_t_type=="string":
            return "string"
        if c_t_type=="bool":
            return "bool"
        if c_t_type=="float":
            return "float"
        if c_t_type=="void":
            return "void"
        return ""

    def GetDefinedType(self: 'NodeJSTranspiler',c_t_type: 'str') -> 'str':
        return c_t_type

    def GetQualifiedTypeName(self: 'NodeJSTranspiler',name_parts: 'list[str]') -> 'str':
        package_delimiter: 'str' = "_"
        package_name_delimiter: 'str' = "."
        name_parts_index: 'int' = Size(name_parts)-1
        last_package_index: 'int' = Size(name_parts)-2
        type_part: 'str' = Element(name_parts,name_parts_index)
        result: 'str' = self.GetTypeName(type_part)
        if name_parts_index>0:
            result = Concat(package_name_delimiter,result)
            while name_parts_index>0:
                name_parts_index = name_parts_index-1
                name_part: 'str' = Element(name_parts,name_parts_index)
                if name_parts_index!=last_package_index:
                    result = Concat(package_delimiter,result)
                result = Concat(name_part,result)
        return result

    def BeginProcessingCTCodeFile(self: 'NodeJSTranspiler') -> 'None':
        ClearList(self.imports)
        self.current_interface = ""
        ClearList(self.interface_definitions)
        self.current_class = ""
        ClearList(self.class_definitions)
        ClearList(self.class_init)
        ClearList(self.class_functions)

    def ProcessExdef(self: 'NodeJSTranspiler',exdef: 'str') -> 'None':
        Append(self.imports,Concat(Concat(Concat(Concat("import * as ",self.string_helper.StripDot(exdef))," from \"./"),self.string_helper.StripDot(exdef)),".js\""))

    def ProcessUnmanagedType(self: 'NodeJSTranspiler',unmanaged_type: 'str') -> 'None':
        pass

    def BeginProcessingInterface(self: 'NodeJSTranspiler',interface_name: 'str') -> 'None':
        self.current_interface = interface_name
        Append(self.interface_definitions,Concat(Concat("export class ",interface_name)," {"))

    def ProcessInterfaceFunctionDeclaration(self: 'NodeJSTranspiler',return_type: 'str',function_name: 'str',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'None':
        Append(self.interface_definitions,Concat(Concat(Concat(self.string_helper.Indentation(1),function_name),self.MakeParametersString(parameters))," {}"))

    def FinishProcessingInterface(self: 'NodeJSTranspiler',interface_name: 'str') -> 'None':
        Append(self.interface_definitions,"}")
        Append(self.interface_definitions,"")
        self.current_interface = ""

    def BeginProcessingClass(self: 'NodeJSTranspiler',class_name: 'str',implementing: 'str') -> 'None':
        self.current_class = class_name
        Append(self.class_definitions,Concat(Concat("export class ",class_name)," {"))
        ClearList(self.class_init)
        ClearList(self.class_functions)
        Append(self.class_init,Concat(self.string_helper.Indentation(1),"constructor() {"))

    def BeginProcessingClassFunctionDefinition(self: 'NodeJSTranspiler',return_type: 'str',function_name: 'str',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'None':
        Append(self.class_functions,"")
        Append(self.class_functions,Concat(Concat(self.string_helper.Indentation(1),function_name),self.MakeParametersString(parameters)))

    def BeginProcessCodeBlock(self: 'NodeJSTranspiler',indent: 'int') -> 'None':
        Append(self.class_functions,Concat(self.string_helper.Indentation(indent),"{"))

    def FinishProcessCodeBlock(self: 'NodeJSTranspiler',indent: 'int') -> 'None':
        Append(self.class_functions,Concat(self.string_helper.Indentation(indent),"}"))

    def BeginProcessConditional(self: 'NodeJSTranspiler',indent: 'int',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(self.string_helper.Indentation(indent),"if ("),r_value),")"))

    def ProcessElse(self: 'NodeJSTranspiler',indent: 'int') -> 'None':
        Append(self.class_functions,Concat(self.string_helper.Indentation(indent),"else"))

    def FinishProcessConditional(self: 'NodeJSTranspiler',indent: 'int',r_value: 'str') -> 'None':
        pass

    def BeginProcessLoop(self: 'NodeJSTranspiler',indent: 'int',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(self.string_helper.Indentation(indent),"while ("),r_value),")"))

    def FinishProcessLoop(self: 'NodeJSTranspiler',indent: 'int',r_value: 'str') -> 'None':
        pass

    def ProcessRtn(self: 'NodeJSTranspiler',indent: 'int',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(self.string_helper.Indentation(indent),"return "),r_value))

    def ProcessDeclaration(self: 'NodeJSTranspiler',indent: 'int',type: 'str',l_value: 'str',r_value: 'str') -> 'None':
        if r_value=="":
            r_value = self.GetDefault(type)
        Append(self.class_functions,Concat(Concat(Concat(Concat(self.string_helper.Indentation(indent),"var "),l_value)," = "),r_value))

    def ProcessAssignment(self: 'NodeJSTranspiler',indent: 'int',l_value: 'str',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(self.string_helper.Indentation(indent),l_value)," = "),r_value))

    def ProcessCall(self: 'NodeJSTranspiler',indent: 'int',call: 'str') -> 'None':
        Append(self.class_functions,Concat(self.string_helper.Indentation(indent),call))

    def FinishProcessingClassFunctionDefinition(self: 'NodeJSTranspiler',return_type: 'str',function_name: 'str',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'None':
        pass

    def ProcessClassMemberDeclaration(self: 'NodeJSTranspiler',member_type: 'str',member_name: 'str') -> 'None':
        Append(self.class_init,Concat(Concat(Concat(Concat(self.string_helper.Indentation(2),"this."),member_name)," = "),self.GetDefault(member_type)))

    def FinishProcessingClass(self: 'NodeJSTranspiler',class_name: 'str',implementing: 'str') -> 'None':
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
        Append(self.class_definitions,"}")
        Append(self.class_definitions,"")
        self.current_class = ""

    def WriteCommonFunctions(self: 'NodeJSTranspiler',destination_file: 'S84_CTCode_System_ctcode.OutputStream') -> 'None':
        destination_file.WriteLine("function ClearList(input) { input.length = 0; }")
        destination_file.WriteLine("function Size(input) { return input.length; }")
        destination_file.WriteLine("function Element(input, element) { return input[element]; }")
        destination_file.WriteLine("function Append(input, element) { input.push(element); }")
        destination_file.WriteLine("function ClearMap(input) { input.clear(); }")
        destination_file.WriteLine("function SetKV(input, key, element) { input.set(key, element); }")
        destination_file.WriteLine("function Keys(input) { return Array.from(input.keys()); }")
        destination_file.WriteLine("function HasKV(input, key) { return input.has(key); }")
        destination_file.WriteLine("function GetKV(input, key) { return input.get(key); }")
        destination_file.WriteLine("function Length(input) { return input.length; }")
        destination_file.WriteLine("function At(input, index) { return input[index]; }")
        destination_file.WriteLine("function IntAt(input, index) { return input.charCodeAt(index); }")
        destination_file.WriteLine("function Concat(left, right) { return left + right; }")

    def FinishProcessingCTCodeFile(self: 'NodeJSTranspiler') -> 'None':
        destination_file_name: 'str' = Concat(self.string_helper.StripDot(self.base_name),".js")
        destination_file: 'S84_CTCode_System_ctcode.OutputStream' = self.system.OpenFileWriter(destination_file_name)
        if Size(self.imports)>0:
            self.string_helper.WriteLines(destination_file,self.imports)
            destination_file.WriteLine("")
        self.WriteCommonFunctions(destination_file)
        destination_file.WriteLine("")
        self.string_helper.WriteLines(destination_file,self.interface_definitions)
        self.string_helper.WriteLines(destination_file,self.class_definitions)

    def GetDefault(self: 'NodeJSTranspiler',javascript_type: 'str') -> 'str':
        if javascript_type=="int":
            return "0"
        if javascript_type=="string":
            return "\"\""
        if javascript_type=="bool":
            return "false"
        if javascript_type=="float":
            return "0.0"
        if javascript_type=="void":
            return "null"
        if self.string_helper.BeginsWith("dict[str",javascript_type):
            return "new Map()"
        if self.string_helper.BeginsWith("list[",javascript_type):
            return "[]"
        return "null"

    def MakeParametersString(self: 'NodeJSTranspiler',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'str':
        result: 'str' = "("
        parameters_index: 'int' = 0
        while parameters_index<Size(parameters):
            parameter: 'S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration' = Element(parameters,parameters_index)
            if parameters_index!=0:
                result = Concat(result,", ")
            result = Concat(result,parameter.GetName())
            parameters_index = parameters_index+1
        result = Concat(result,")")
        return result

