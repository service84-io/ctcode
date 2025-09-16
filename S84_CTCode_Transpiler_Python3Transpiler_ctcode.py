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

class Python3Transpiler(S84_CTCode_Transpiler_StandardStructure_ctcode.TargetSpecificFunctions):
    def __init__(self: 'Python3Transpiler'):
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

    def Initialize(self: 'Python3Transpiler') -> 'None':
        self.string_helper = S84_CTCode_Transpiler_StringHelper_ctcode.StringHelper()

    def SetSystem(self: 'Python3Transpiler',system: 'S84_CTCode_System_ctcode.System') -> 'None':
        self.system = system

    def SetCTCodeFile(self: 'Python3Transpiler',c_t_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile') -> 'None':
        self.c_t_code_file = c_t_code_file

    def SetBaseName(self: 'Python3Transpiler',base_name: 'str') -> 'None':
        self.base_name = base_name

    def SetLogger(self: 'Python3Transpiler',logger: 'S84_CTCode_System_ctcode.OutputStream') -> 'None':
        self.logger = logger

    def GetBaseIndentation(self: 'Python3Transpiler') -> 'int':
        return 1

    def GetCallName(self: 'Python3Transpiler',name: 'str') -> 'str':
        return self.string_helper.SnakeCaseToCamelCase(name)

    def GetVariableName(self: 'Python3Transpiler',name: 'str') -> 'str':
        value: 'str' = self.string_helper.CamelCaseToSnakeCase(name)
        if value=="myself":
            return "self"
        return value

    def GetVariableChain(self: 'Python3Transpiler',name_parts: 'list[str]') -> 'str':
        delimiter: 'str' = "."
        first_name: 'str' = Element(name_parts,0)
        result: 'str' = self.GetVariableName(first_name)
        name_parts_index: 'int' = 1
        while name_parts_index<Size(name_parts):
            name: 'str' = Element(name_parts,name_parts_index)
            result = Concat(Concat(result,delimiter),self.GetVariableName(name))
            name_parts_index = name_parts_index+1
        return result

    def ConvertCall(self: 'Python3Transpiler',name_chain: 'list[str]',parameters: 'list[str]') -> 'str':
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

    def ConvertAllocate(self: 'Python3Transpiler',type: 'str') -> 'str':
        return Concat(type,"()")

    def ConvertByte(self: 'Python3Transpiler',high: 'str',low: 'str') -> 'str':
        return Concat(Concat("0x",high),low)

    def ConvertDecimal(self: 'Python3Transpiler',decimal: 'str') -> 'str':
        return decimal

    def ConvertNumber(self: 'Python3Transpiler',number: 'str') -> 'str':
        return number

    def ConvertBoolean(self: 'Python3Transpiler',boolean: 'str') -> 'str':
        if boolean=="true":
            return "True"
        if boolean=="false":
            return "False"
        return ""

    def ConvertVariable(self: 'Python3Transpiler',variable: 'str') -> 'str':
        return variable

    def ConvertString(self: 'Python3Transpiler',literal: 'str') -> 'str':
        return Concat(Concat("\"",literal),"\"")

    def UnaryOperator(self: 'Python3Transpiler',op: 'str',r_value: 'str') -> 'str':
        if op=="!":
            return Concat("not ",r_value)
        return r_value

    def BinaryOperator(self: 'Python3Transpiler',op: 'str',r_value_l: 'str',r_value_r: 'str') -> 'str':
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
            return Concat(Concat(r_value_l," or "),r_value_r)
        if op=="&&":
            return Concat(Concat(r_value_l," and "),r_value_r)
        return ""

    def GetTypeName(self: 'Python3Transpiler',name: 'str') -> 'str':
        return self.string_helper.SnakeCaseToCamelCase(name)

    def GetDimensionalType(self: 'Python3Transpiler',singleton_type: 'str',dimensions: 'int') -> 'str':
        result: 'str' = singleton_type
        while dimensions>0:
            result = Concat(Concat("list[",result),"]")
            dimensions = dimensions-1
        return result

    def GetMapType(self: 'Python3Transpiler',singleton_type: 'str') -> 'str':
        return Concat(Concat("dict[str, ",singleton_type),"]")

    def GetPrimativeType(self: 'Python3Transpiler',c_t_type: 'str') -> 'str':
        if c_t_type=="int":
            return "int"
        if c_t_type=="string":
            return "str"
        if c_t_type=="bool":
            return "bool"
        if c_t_type=="float":
            return "float"
        if c_t_type=="void":
            return "None"
        return ""

    def GetDefinedType(self: 'Python3Transpiler',c_t_type: 'str') -> 'str':
        return c_t_type

    def GetQualifiedTypeName(self: 'Python3Transpiler',name_parts: 'list[str]') -> 'str':
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

    def BeginProcessingCTCodeFile(self: 'Python3Transpiler') -> 'None':
        ClearList(self.imports)
        self.current_interface = ""
        ClearList(self.interface_definitions)
        self.current_class = ""
        ClearList(self.class_definitions)
        ClearList(self.class_init)
        ClearList(self.class_functions)

    def ProcessExdef(self: 'Python3Transpiler',exdef: 'str') -> 'None':
        Append(self.imports,Concat("import ",self.string_helper.StripDot(exdef)))

    def ProcessUnmanagedType(self: 'Python3Transpiler',unmanaged_type: 'str') -> 'None':
        noop: 'int' = 0

    def BeginProcessingInterface(self: 'Python3Transpiler',interface_name: 'str') -> 'None':
        self.current_interface = interface_name
        Append(self.interface_definitions,Concat(Concat("class ",interface_name),":"))

    def ProcessInterfaceFunctionDeclaration(self: 'Python3Transpiler',return_type: 'str',function_name: 'str',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'None':
        Append(self.interface_definitions,Concat(Concat(Concat(Concat(Concat(Concat(self.string_helper.Indentation(1),"def "),function_name),self.MakeParametersString(self.current_interface,parameters))," -> '"),return_type),"': pass"))

    def FinishProcessingInterface(self: 'Python3Transpiler',interface_name: 'str') -> 'None':
        Append(self.interface_definitions,"")
        self.current_interface = ""

    def BeginProcessingClass(self: 'Python3Transpiler',class_name: 'str',implementing: 'str') -> 'None':
        self.current_class = class_name
        if implementing=="":
            Append(self.class_definitions,Concat(Concat("class ",class_name),":"))
        else:
            Append(self.class_definitions,Concat(Concat(Concat(Concat("class ",class_name),"("),implementing),"):"))
        ClearList(self.class_init)
        ClearList(self.class_functions)
        Append(self.class_init,Concat(Concat(Concat(self.string_helper.Indentation(1),"def __init__(self: '"),class_name),"'):"))

    def BeginProcessingClassFunctionDefinition(self: 'Python3Transpiler',return_type: 'str',function_name: 'str',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(Concat(Concat(Concat(self.string_helper.Indentation(1),"def "),function_name),self.MakeParametersString(self.current_class,parameters))," -> '"),return_type),"':"))

    def BeginProcessCodeBlock(self: 'Python3Transpiler',indent: 'int') -> 'None':
        noop: 'int' = 0

    def FinishProcessCodeBlock(self: 'Python3Transpiler',indent: 'int') -> 'None':
        noop: 'int' = 0

    def BeginProcessConditional(self: 'Python3Transpiler',indent: 'int',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(self.string_helper.Indentation(indent),"if "),r_value),":"))

    def ProcessElse(self: 'Python3Transpiler',indent: 'int') -> 'None':
        Append(self.class_functions,Concat(self.string_helper.Indentation(indent),"else:"))

    def FinishProcessConditional(self: 'Python3Transpiler',indent: 'int',r_value: 'str') -> 'None':
        noop: 'int' = 0

    def BeginProcessLoop(self: 'Python3Transpiler',indent: 'int',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(self.string_helper.Indentation(indent),"while "),r_value),":"))

    def FinishProcessLoop(self: 'Python3Transpiler',indent: 'int',r_value: 'str') -> 'None':
        noop: 'int' = 0

    def ProcessRtn(self: 'Python3Transpiler',indent: 'int',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(self.string_helper.Indentation(indent),"return "),r_value))

    def ProcessDeclaration(self: 'Python3Transpiler',indent: 'int',type: 'str',l_value: 'str',r_value: 'str') -> 'None':
        if r_value=="":
            r_value = self.GetDefault(type)
        Append(self.class_functions,Concat(Concat(Concat(Concat(Concat(self.string_helper.Indentation(indent),l_value),": '"),type),"' = "),r_value))

    def ProcessAssignment(self: 'Python3Transpiler',indent: 'int',l_value: 'str',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(self.string_helper.Indentation(indent),l_value)," = "),r_value))

    def ProcessCall(self: 'Python3Transpiler',indent: 'int',call: 'str') -> 'None':
        Append(self.class_functions,Concat(self.string_helper.Indentation(indent),call))

    def FinishProcessingClassFunctionDefinition(self: 'Python3Transpiler',return_type: 'str',function_name: 'str',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'None':
        Append(self.class_functions,"")

    def ProcessClassMemberDeclaration(self: 'Python3Transpiler',member_type: 'str',member_name: 'str') -> 'None':
        Append(self.class_init,Concat(Concat(Concat(Concat(Concat(Concat(self.string_helper.Indentation(2),"self."),member_name),": "),member_type)," = "),self.GetDefault(member_type)))

    def FinishProcessingClass(self: 'Python3Transpiler',class_name: 'str',implementing: 'str') -> 'None':
        if Size(self.class_init)==1:
            Append(self.class_init,Concat(self.string_helper.Indentation(2),"pass"))
        class_init_index: 'int' = 0
        while class_init_index<Size(self.class_init):
            line: 'str' = Element(self.class_init,class_init_index)
            Append(self.class_definitions,line)
            class_init_index = class_init_index+1
        Append(self.class_definitions,"")
        class_functions_index: 'int' = 0
        while class_functions_index<Size(self.class_functions):
            line: 'str' = Element(self.class_functions,class_functions_index)
            Append(self.class_definitions,line)
            class_functions_index = class_functions_index+1
        self.current_class = ""

    def WriteCommonFunctions(self: 'Python3Transpiler',destination_file: 'S84_CTCode_System_ctcode.OutputStream') -> 'None':
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

    def FinishProcessingCTCodeFile(self: 'Python3Transpiler') -> 'None':
        destination_file_name: 'str' = Concat(self.string_helper.StripDot(self.base_name),".py")
        destination_file: 'S84_CTCode_System_ctcode.OutputStream' = self.system.OpenFileWriter(destination_file_name)
        if Size(self.imports)>0:
            self.string_helper.WriteLines(destination_file,self.imports)
            destination_file.WriteLine("")
        self.WriteCommonFunctions(destination_file)
        destination_file.WriteLine("")
        self.string_helper.WriteLines(destination_file,self.interface_definitions)
        self.string_helper.WriteLines(destination_file,self.class_definitions)

    def GetDefault(self: 'Python3Transpiler',python_type: 'str') -> 'str':
        if python_type=="int":
            return "0"
        if python_type=="str":
            return "\"\""
        if python_type=="bool":
            return "False"
        if python_type=="float":
            return "0.0"
        if python_type=="None":
            return "None"
        if self.string_helper.BeginsWith("dict[str",python_type):
            return "{}"
        if self.string_helper.BeginsWith("list[",python_type):
            return "[]"
        return "None"

    def MakeParametersString(self: 'Python3Transpiler',self_type: 'str',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'str':
        result: 'str' = Concat(Concat("(self: '",self_type),"'")
        parameters_index: 'int' = 0
        while parameters_index<Size(parameters):
            parameter: 'S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration' = Element(parameters,parameters_index)
            result = Concat(result,",")
            result = Concat(Concat(Concat(Concat(result,parameter.GetName()),": '"),parameter.GetType()),"'")
            parameters_index = parameters_index+1
        result = Concat(result,")")
        return result

