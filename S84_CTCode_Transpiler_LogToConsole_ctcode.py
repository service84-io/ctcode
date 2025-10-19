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

class LogToConsole(S84_CTCode_Transpiler_StandardStructure_ctcode.TargetSpecificFunctions):
    def __init__(self: 'LogToConsole'):
        self.system: S84_CTCode_System_ctcode.System = None
        self.c_t_code_file: S84_CTCode_dbnf_ctcode.CTCodeFile = None
        self.base_name: str = ""
        self.logger: S84_CTCode_System_ctcode.OutputStream = None
        self.string_helper: S84_CTCode_Transpiler_StringHelper_ctcode.StringHelper = None

    def Initialize(self: 'LogToConsole') -> 'None':
        self.string_helper = S84_CTCode_Transpiler_StringHelper_ctcode.StringHelper()

    def SetSystem(self: 'LogToConsole',system: 'S84_CTCode_System_ctcode.System') -> 'None':
        self.system = system

    def SetCTCodeFile(self: 'LogToConsole',c_t_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile') -> 'None':
        self.c_t_code_file = c_t_code_file

    def SetBaseName(self: 'LogToConsole',base_name: 'str') -> 'None':
        self.base_name = base_name

    def SetLogger(self: 'LogToConsole',logger: 'S84_CTCode_System_ctcode.OutputStream') -> 'None':
        self.logger = logger

    def GetBaseIndentation(self: 'LogToConsole') -> 'int':
        return 3

    def GetCallName(self: 'LogToConsole',name: 'str') -> 'str':
        value: 'str' = self.string_helper.SnakeCaseToCamelCase(name)
        if self.string_helper.IsReserved(value):
            return Concat("ReservedPrefix",value)
        return value

    def GetVariableName(self: 'LogToConsole',name: 'str') -> 'str':
        value: 'str' = self.string_helper.CamelCaseToSnakeCase(name)
        if value=="myself":
            return "thyself"
        if self.string_helper.IsReserved(value):
            return Concat("reserved_prefix_",value)
        return value

    def GetVariableChain(self: 'LogToConsole',name_parts: 'list[str]') -> 'str':
        delimiter: 'str' = "."
        first_name: 'str' = Element(name_parts,0)
        result: 'str' = self.GetVariableName(first_name)
        name_parts_index: 'int' = 1
        while name_parts_index<Size(name_parts):
            name: 'str' = Element(name_parts,name_parts_index)
            result = Concat(Concat(result,delimiter),self.GetVariableName(name))
            name_parts_index = name_parts_index+1
        return result

    def ConvertCall(self: 'LogToConsole',name_chain: 'list[str]',parameters: 'list[str]') -> 'str':
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

    def ConvertAllocate(self: 'LogToConsole',type: 'str') -> 'str':
        return Concat("new ",type)

    def ConvertByte(self: 'LogToConsole',high: 'str',low: 'str') -> 'str':
        return Concat(Concat("0x",high),low)

    def ConvertDecimal(self: 'LogToConsole',reserved_prefix_decimal: 'str') -> 'str':
        return reserved_prefix_decimal

    def ConvertNumber(self: 'LogToConsole',number: 'str') -> 'str':
        return number

    def ConvertBoolean(self: 'LogToConsole',reserved_prefix_boolean: 'str') -> 'str':
        if reserved_prefix_boolean=="true":
            return "true"
        if reserved_prefix_boolean=="false":
            return "false"
        return ""

    def ConvertVariable(self: 'LogToConsole',variable: 'str') -> 'str':
        return variable

    def ConvertString(self: 'LogToConsole',literal: 'str') -> 'str':
        return Concat(Concat("\"",literal),"\"")

    def UnaryOperator(self: 'LogToConsole',op: 'str',r_value: 'str') -> 'str':
        if op=="!":
            return Concat("!",r_value)
        return r_value

    def BinaryOperator(self: 'LogToConsole',op: 'str',r_value_l: 'str',r_value_r: 'str') -> 'str':
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

    def GetTypeName(self: 'LogToConsole',name: 'str') -> 'str':
        value: 'str' = self.string_helper.SnakeCaseToCamelCase(name)
        if self.string_helper.IsReserved(value):
            return Concat("ReservedPrefix",value)
        return value

    def GetDimensionalType(self: 'LogToConsole',singleton_type: 'str',dimensions: 'int') -> 'str':
        result: 'str' = singleton_type
        while dimensions>0:
            result = Concat(result,"[]")
            dimensions = dimensions-1
        return result

    def GetMapType(self: 'LogToConsole',singleton_type: 'str') -> 'str':
        return Concat(singleton_type,"{}")

    def GetPrimativeType(self: 'LogToConsole',c_t_type: 'str') -> 'str':
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

    def GetDefinedType(self: 'LogToConsole',c_t_type: 'str') -> 'str':
        return c_t_type

    def GetQualifiedTypeName(self: 'LogToConsole',name_parts: 'list[str]') -> 'str':
        delimiter: 'str' = "."
        name_parts_index: 'int' = Size(name_parts)-1
        type_part: 'str' = Element(name_parts,name_parts_index)
        result: 'str' = self.GetTypeName(type_part)
        if name_parts_index>0:
            while name_parts_index>0:
                name_parts_index = name_parts_index-1
                result = Concat(delimiter,result)
                name_part: 'str' = Element(name_parts,name_parts_index)
                result = Concat(name_part,result)
        return result

    def BeginProcessingCTCodeFile(self: 'LogToConsole') -> 'None':
        self.logger.WriteLine("BeginProcessingCTCodeFile")

    def FinishProcessingCTCodeFile(self: 'LogToConsole') -> 'None':
        self.logger.WriteLine("FinishProcessingCTCodeFile")

    def ProcessExdef(self: 'LogToConsole',exdef: 'str') -> 'None':
        self.logger.WriteLine(Concat(Concat(self.string_helper.Indentation(1),"ProcessExdef: "),exdef))

    def ProcessUnmanagedType(self: 'LogToConsole',unmanaged_type: 'str') -> 'None':
        self.logger.WriteLine(Concat(Concat(self.string_helper.Indentation(1),"ProcessUnmanagedType: "),unmanaged_type))

    def BeginProcessingInterface(self: 'LogToConsole',interface_name: 'str') -> 'None':
        self.logger.WriteLine(Concat(Concat(self.string_helper.Indentation(1),"BeginProcessingInterface: "),interface_name))

    def ProcessInterfaceFunctionDeclaration(self: 'LogToConsole',return_type: 'str',function_name: 'str',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'None':
        self.logger.WriteLine(Concat(Concat(Concat(Concat(self.string_helper.Indentation(2),"ProcessInterfaceFunctionDeclaration: "),return_type)," "),function_name))

    def FinishProcessingInterface(self: 'LogToConsole',interface_name: 'str') -> 'None':
        self.logger.WriteLine(Concat(Concat(self.string_helper.Indentation(1),"FinishProcessingInterface: "),interface_name))

    def BeginProcessingClass(self: 'LogToConsole',class_name: 'str',implementing: 'str') -> 'None':
        self.logger.WriteLine(Concat(Concat(Concat(Concat(self.string_helper.Indentation(1),"BeginProcessingClass: "),class_name)," "),implementing))

    def BeginProcessingClassFunctionDefinition(self: 'LogToConsole',return_type: 'str',function_name: 'str',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'None':
        self.logger.WriteLine(Concat(Concat(Concat(Concat(self.string_helper.Indentation(2),"BeginProcessingClassFunctionDefinition: "),return_type)," "),function_name))

    def BeginProcessCodeBlock(self: 'LogToConsole',indent: 'int') -> 'None':
        self.logger.WriteLine(Concat(self.string_helper.Indentation(indent),"BeginProcessCodeBlock"))

    def FinishProcessCodeBlock(self: 'LogToConsole',indent: 'int') -> 'None':
        self.logger.WriteLine(Concat(self.string_helper.Indentation(indent),"FinishProcessCodeBlock"))

    def BeginProcessConditional(self: 'LogToConsole',indent: 'int',r_value: 'str') -> 'None':
        self.logger.WriteLine(Concat(Concat(self.string_helper.Indentation(indent),"BeginProcessConditional: "),r_value))

    def ProcessElse(self: 'LogToConsole',indent: 'int') -> 'None':
        self.logger.WriteLine(Concat(self.string_helper.Indentation(indent),"ProcessElse"))

    def FinishProcessConditional(self: 'LogToConsole',indent: 'int',r_value: 'str') -> 'None':
        self.logger.WriteLine(Concat(Concat(self.string_helper.Indentation(indent),"FinishProcessConditional: "),r_value))

    def BeginProcessLoop(self: 'LogToConsole',indent: 'int',r_value: 'str') -> 'None':
        self.logger.WriteLine(Concat(Concat(self.string_helper.Indentation(indent),"BeginProcessLoop: "),r_value))

    def FinishProcessLoop(self: 'LogToConsole',indent: 'int',r_value: 'str') -> 'None':
        self.logger.WriteLine(Concat(Concat(self.string_helper.Indentation(indent),"FinishProcessLoop: "),r_value))

    def ProcessRtn(self: 'LogToConsole',indent: 'int',r_value: 'str') -> 'None':
        self.logger.WriteLine(Concat(Concat(self.string_helper.Indentation(indent),"ProcessRtn: "),r_value))

    def ProcessDeclaration(self: 'LogToConsole',indent: 'int',type: 'str',l_value: 'str',r_value: 'str') -> 'None':
        self.logger.WriteLine(Concat(Concat(Concat(Concat(Concat(Concat(self.string_helper.Indentation(indent),"ProcessDeclaration: "),type)," "),l_value)," "),r_value))

    def ProcessAssignment(self: 'LogToConsole',indent: 'int',l_value: 'str',r_value: 'str') -> 'None':
        self.logger.WriteLine(Concat(Concat(Concat(Concat(self.string_helper.Indentation(indent),"ProcessAssignment: "),l_value)," "),r_value))

    def ProcessCall(self: 'LogToConsole',indent: 'int',call: 'str') -> 'None':
        self.logger.WriteLine(Concat(Concat(self.string_helper.Indentation(indent),"ProcessCall: "),call))

    def FinishProcessingClassFunctionDefinition(self: 'LogToConsole',return_type: 'str',function_name: 'str',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'None':
        self.logger.WriteLine(Concat(Concat(Concat(Concat(self.string_helper.Indentation(2),"FinishProcessingClassFunctionDefinition: "),return_type)," "),function_name))

    def ProcessClassMemberDeclaration(self: 'LogToConsole',member_type: 'str',member_name: 'str') -> 'None':
        self.logger.WriteLine(Concat(Concat(Concat(Concat(self.string_helper.Indentation(2),"ProcessClassMemberDeclaration: "),member_type)," "),member_name))

    def FinishProcessingClass(self: 'LogToConsole',class_name: 'str',implementing: 'str') -> 'None':
        self.logger.WriteLine(Concat(Concat(self.string_helper.Indentation(1),"FinishProcessingClass: "),class_name))

