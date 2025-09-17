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

class CSharpTranspiler(S84_CTCode_Transpiler_StandardStructure_ctcode.TargetSpecificFunctions):
    def __init__(self: 'CSharpTranspiler'):
        self.system: S84_CTCode_System_ctcode.System = None
        self.c_t_code_file: S84_CTCode_dbnf_ctcode.CTCodeFile = None
        self.base_name: str = ""
        self.logger: S84_CTCode_System_ctcode.OutputStream = None
        self.string_helper: S84_CTCode_Transpiler_StringHelper_ctcode.StringHelper = None

    def Initialize(self: 'CSharpTranspiler') -> 'None':
        self.string_helper = S84_CTCode_Transpiler_StringHelper_ctcode.StringHelper()

    def SetSystem(self: 'CSharpTranspiler',system: 'S84_CTCode_System_ctcode.System') -> 'None':
        self.system = system

    def SetCTCodeFile(self: 'CSharpTranspiler',c_t_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile') -> 'None':
        self.c_t_code_file = c_t_code_file

    def SetBaseName(self: 'CSharpTranspiler',base_name: 'str') -> 'None':
        self.base_name = base_name

    def SetLogger(self: 'CSharpTranspiler',logger: 'S84_CTCode_System_ctcode.OutputStream') -> 'None':
        self.logger = logger

    def GetBaseIndentation(self: 'CSharpTranspiler') -> 'int':
        return 3

    def GetCallName(self: 'CSharpTranspiler',name: 'str') -> 'str':
        return self.string_helper.SnakeCaseToCamelCase(name)

    def GetVariableName(self: 'CSharpTranspiler',name: 'str') -> 'str':
        value: 'str' = self.string_helper.CamelCaseToSnakeCase(name)
        if value=="myself":
            return "thyself"
        return value

    def GetVariableChain(self: 'CSharpTranspiler',name_parts: 'list[str]') -> 'str':
        delimiter: 'str' = "."
        first_name: 'str' = Element(name_parts,0)
        result: 'str' = self.GetVariableName(first_name)
        name_parts_index: 'int' = 1
        while name_parts_index<Size(name_parts):
            name: 'str' = Element(name_parts,name_parts_index)
            result = Concat(Concat(result,delimiter),self.GetVariableName(name))
            name_parts_index = name_parts_index+1
        return result

    def ConvertCall(self: 'CSharpTranspiler',name_chain: 'list[str]',parameters: 'list[str]') -> 'str':
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

    def ConvertAllocate(self: 'CSharpTranspiler',type: 'str') -> 'str':
        return Concat("new ",type)

    def ConvertByte(self: 'CSharpTranspiler',high: 'str',low: 'str') -> 'str':
        return Concat(Concat("0x",high),low)

    def ConvertDecimal(self: 'CSharpTranspiler',decimal: 'str') -> 'str':
        return decimal

    def ConvertNumber(self: 'CSharpTranspiler',number: 'str') -> 'str':
        return number

    def ConvertBoolean(self: 'CSharpTranspiler',boolean: 'str') -> 'str':
        if boolean=="true":
            return "true"
        if boolean=="false":
            return "false"
        return ""

    def ConvertVariable(self: 'CSharpTranspiler',variable: 'str') -> 'str':
        return variable

    def ConvertString(self: 'CSharpTranspiler',literal: 'str') -> 'str':
        return Concat(Concat("\"",literal),"\"")

    def UnaryOperator(self: 'CSharpTranspiler',op: 'str',r_value: 'str') -> 'str':
        if op=="!":
            return Concat("!",r_value)
        return r_value

    def BinaryOperator(self: 'CSharpTranspiler',op: 'str',r_value_l: 'str',r_value_r: 'str') -> 'str':
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

    def GetTypeName(self: 'CSharpTranspiler',name: 'str') -> 'str':
        if name!="":
            return self.string_helper.SnakeCaseToCamelCase(name)
        else:
            return ""

    def GetDimensionalType(self: 'CSharpTranspiler',singleton_type: 'str',dimensions: 'int') -> 'str':
        result: 'str' = singleton_type
        while dimensions>0:
            result = Concat(result,"[]")
            dimensions = dimensions-1
        return result

    def GetMapType(self: 'CSharpTranspiler',singleton_type: 'str') -> 'str':
        return Concat(singleton_type,"{}")

    def GetPrimativeType(self: 'CSharpTranspiler',c_t_type: 'str') -> 'str':
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

    def GetDefinedType(self: 'CSharpTranspiler',c_t_type: 'str') -> 'str':
        return c_t_type

    def GetQualifiedTypeName(self: 'CSharpTranspiler',name_parts: 'list[str]') -> 'str':
        delimiter: 'str' = "."
        first_name: 'str' = Element(name_parts,0)
        result: 'str' = first_name
        name_parts_index: 'int' = 1
        while name_parts_index<Size(name_parts):
            name: 'str' = Element(name_parts,name_parts_index)
            result = Concat(Concat(result,delimiter),name)
            name_parts_index = name_parts_index+1
        return result

    def BeginProcessingCTCodeFile(self: 'CSharpTranspiler') -> 'None':
        self.logger.WriteLine("BeginProcessingCTCodeFile")

    def FinishProcessingCTCodeFile(self: 'CSharpTranspiler') -> 'None':
        self.logger.WriteLine("FinishProcessingCTCodeFile")

    def ProcessExdef(self: 'CSharpTranspiler',exdef: 'str') -> 'None':
        self.logger.WriteLine(Concat(Concat(self.string_helper.Indentation(1),"ProcessExdef: "),exdef))

    def ProcessUnmanagedType(self: 'CSharpTranspiler',unmanaged_type: 'str') -> 'None':
        self.logger.WriteLine(Concat(Concat(self.string_helper.Indentation(1),"ProcessUnmanagedType: "),unmanaged_type))

    def BeginProcessingInterface(self: 'CSharpTranspiler',interface_name: 'str') -> 'None':
        self.logger.WriteLine(Concat(Concat(self.string_helper.Indentation(1),"BeginProcessingInterface: "),interface_name))

    def ProcessInterfaceFunctionDeclaration(self: 'CSharpTranspiler',return_type: 'str',function_name: 'str',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'None':
        self.logger.WriteLine(Concat(Concat(Concat(Concat(self.string_helper.Indentation(2),"ProcessInterfaceFunctionDeclaration: "),return_type)," "),function_name))

    def FinishProcessingInterface(self: 'CSharpTranspiler',interface_name: 'str') -> 'None':
        self.logger.WriteLine(Concat(Concat(self.string_helper.Indentation(1),"FinishProcessingInterface: "),interface_name))

    def BeginProcessingClass(self: 'CSharpTranspiler',class_name: 'str',implementing: 'str') -> 'None':
        self.logger.WriteLine(Concat(Concat(Concat(Concat(self.string_helper.Indentation(1),"BeginProcessingClass: "),class_name)," "),implementing))

    def BeginProcessingClassFunctionDefinition(self: 'CSharpTranspiler',return_type: 'str',function_name: 'str',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'None':
        self.logger.WriteLine(Concat(Concat(Concat(Concat(self.string_helper.Indentation(2),"BeginProcessingClassFunctionDefinition: "),return_type)," "),function_name))

    def BeginProcessCodeBlock(self: 'CSharpTranspiler',indent: 'int') -> 'None':
        self.logger.WriteLine(Concat(self.string_helper.Indentation(indent),"BeginProcessCodeBlock"))

    def FinishProcessCodeBlock(self: 'CSharpTranspiler',indent: 'int') -> 'None':
        self.logger.WriteLine(Concat(self.string_helper.Indentation(indent),"FinishProcessCodeBlock"))

    def BeginProcessConditional(self: 'CSharpTranspiler',indent: 'int',r_value: 'str') -> 'None':
        self.logger.WriteLine(Concat(Concat(self.string_helper.Indentation(indent),"BeginProcessConditional: "),r_value))

    def ProcessElse(self: 'CSharpTranspiler',indent: 'int') -> 'None':
        self.logger.WriteLine(Concat(self.string_helper.Indentation(indent),"ProcessElse"))

    def FinishProcessConditional(self: 'CSharpTranspiler',indent: 'int',r_value: 'str') -> 'None':
        self.logger.WriteLine(Concat(Concat(self.string_helper.Indentation(indent),"FinishProcessConditional: "),r_value))

    def BeginProcessLoop(self: 'CSharpTranspiler',indent: 'int',r_value: 'str') -> 'None':
        self.logger.WriteLine(Concat(Concat(self.string_helper.Indentation(indent),"BeginProcessLoop: "),r_value))

    def FinishProcessLoop(self: 'CSharpTranspiler',indent: 'int',r_value: 'str') -> 'None':
        self.logger.WriteLine(Concat(Concat(self.string_helper.Indentation(indent),"FinishProcessLoop: "),r_value))

    def ProcessRtn(self: 'CSharpTranspiler',indent: 'int',r_value: 'str') -> 'None':
        self.logger.WriteLine(Concat(Concat(self.string_helper.Indentation(indent),"ProcessRtn: "),r_value))

    def ProcessDeclaration(self: 'CSharpTranspiler',indent: 'int',type: 'str',l_value: 'str',r_value: 'str') -> 'None':
        self.logger.WriteLine(Concat(Concat(Concat(Concat(Concat(Concat(self.string_helper.Indentation(indent),"ProcessDeclaration: "),type)," "),l_value)," "),r_value))

    def ProcessAssignment(self: 'CSharpTranspiler',indent: 'int',l_value: 'str',r_value: 'str') -> 'None':
        self.logger.WriteLine(Concat(Concat(Concat(Concat(self.string_helper.Indentation(indent),"ProcessAssignment: "),l_value)," "),r_value))

    def ProcessCall(self: 'CSharpTranspiler',indent: 'int',call: 'str') -> 'None':
        self.logger.WriteLine(Concat(Concat(self.string_helper.Indentation(indent),"ProcessCall: "),call))

    def FinishProcessingClassFunctionDefinition(self: 'CSharpTranspiler',return_type: 'str',function_name: 'str',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'None':
        self.logger.WriteLine(Concat(Concat(Concat(Concat(self.string_helper.Indentation(2),"FinishProcessingClassFunctionDefinition: "),return_type)," "),function_name))

    def ProcessClassMemberDeclaration(self: 'CSharpTranspiler',member_type: 'str',member_name: 'str') -> 'None':
        self.logger.WriteLine(Concat(Concat(Concat(Concat(self.string_helper.Indentation(2),"ProcessClassMemberDeclaration: "),member_type)," "),member_name))

    def FinishProcessingClass(self: 'CSharpTranspiler',class_name: 'str',implementing: 'str') -> 'None':
        self.logger.WriteLine(Concat(Concat(self.string_helper.Indentation(1),"FinishProcessingClass: "),class_name))

