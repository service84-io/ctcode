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

class RubyTranspiler(S84_CTCode_Transpiler_StandardStructure_ctcode.TargetSpecificFunctions):
    def __init__(self: 'RubyTranspiler'):
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

    def Initialize(self: 'RubyTranspiler') -> 'None':
        self.string_helper = S84_CTCode_Transpiler_StringHelper_ctcode.StringHelper()

    def SetSystem(self: 'RubyTranspiler',system: 'S84_CTCode_System_ctcode.System') -> 'None':
        self.system = system

    def SetCTCodeFile(self: 'RubyTranspiler',c_t_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile') -> 'None':
        self.c_t_code_file = c_t_code_file

    def SetBaseName(self: 'RubyTranspiler',base_name: 'str') -> 'None':
        self.base_name = base_name

    def SetLogger(self: 'RubyTranspiler',logger: 'S84_CTCode_System_ctcode.OutputStream') -> 'None':
        self.logger = logger

    def GetBaseIndentation(self: 'RubyTranspiler') -> 'int':
        return 1

    def IsReserved(self: 'RubyTranspiler',name: 'str') -> 'bool':
        return False or self.string_helper.BeginsWith("ReservedPrefix",name) or self.string_helper.BeginsWith("reserved_prefix_",name) or name=="end" or name=="Return" or name=="String" or name=="GetType" or name=="string" or name=="boolean" or name=="char" or name=="float" or name=="decimal"

    def GetCallName(self: 'RubyTranspiler',name: 'str') -> 'str':
        value: 'str' = self.string_helper.SnakeCaseToCamelCase(name)
        if self.IsReserved(value):
            return Concat("ReservedPrefix",value)
        return value

    def GetVariableName(self: 'RubyTranspiler',name: 'str') -> 'str':
        value: 'str' = self.string_helper.CamelCaseToSnakeCase(name)
        if value=="myself":
            return "self"
        if self.IsReserved(value):
            return Concat("reserved_prefix_",value)
        return value

    def GetVariableChain(self: 'RubyTranspiler',name_parts: 'list[str]') -> 'str':
        delimiter: 'str' = "."
        first_name: 'str' = Element(name_parts,0)
        result: 'str' = self.GetVariableName(first_name)
        name_parts_index: 'int' = 1
        while name_parts_index<Size(name_parts):
            name: 'str' = Element(name_parts,name_parts_index)
            result = Concat(result,delimiter)
            if result=="self.":
                result = "@"
            result = Concat(result,self.GetVariableName(name))
            name_parts_index = name_parts_index+1
        return result

    def ConvertCall(self: 'RubyTranspiler',name_chain: 'list[str]',parameters: 'list[str]') -> 'str':
        result: 'str' = Element(name_chain,0)
        name_chain_index: 'int' = 1
        last_name_chain_index: 'int' = Size(name_chain)-1
        while name_chain_index<Size(name_chain):
            name_part: 'str' = Element(name_chain,name_chain_index)
            result = Concat(result,".")
            if name_chain_index!=last_name_chain_index:
                if result=="self.":
                    result = "@"
            result = Concat(result,name_part)
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

    def ConvertAllocate(self: 'RubyTranspiler',type: 'str') -> 'str':
        return Concat(type,".new()")

    def ConvertByte(self: 'RubyTranspiler',high: 'str',low: 'str') -> 'str':
        return Concat(Concat("0x",high),low)

    def ConvertDecimal(self: 'RubyTranspiler',decimal: 'str') -> 'str':
        return decimal

    def ConvertNumber(self: 'RubyTranspiler',number: 'str') -> 'str':
        return number

    def ConvertBoolean(self: 'RubyTranspiler',boolean: 'str') -> 'str':
        if boolean=="true":
            return "true"
        if boolean=="false":
            return "false"
        return ""

    def ConvertVariable(self: 'RubyTranspiler',variable: 'str') -> 'str':
        return variable

    def ConvertString(self: 'RubyTranspiler',literal: 'str') -> 'str':
        return Concat(Concat("\"",literal),"\"")

    def UnaryOperator(self: 'RubyTranspiler',op: 'str',r_value: 'str') -> 'str':
        if op=="!":
            return Concat("! ",r_value)
        return r_value

    def BinaryOperator(self: 'RubyTranspiler',op: 'str',r_value_l: 'str',r_value_r: 'str') -> 'str':
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

    def GetTypeName(self: 'RubyTranspiler',name: 'str') -> 'str':
        value: 'str' = self.string_helper.SnakeCaseToCamelCase(name)
        if self.IsReserved(value):
            return Concat("ReservedPrefix",value)
        return value

    def GetDimensionalType(self: 'RubyTranspiler',singleton_type: 'str',dimensions: 'int') -> 'str':
        result: 'str' = singleton_type
        while dimensions>0:
            result = Concat(Concat("list[",result),"]")
            dimensions = dimensions-1
        return result

    def GetMapType(self: 'RubyTranspiler',singleton_type: 'str') -> 'str':
        return Concat(Concat("dict[str, ",singleton_type),"]")

    def GetPrimativeType(self: 'RubyTranspiler',c_t_type: 'str') -> 'str':
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

    def GetDefinedType(self: 'RubyTranspiler',c_t_type: 'str') -> 'str':
        return c_t_type

    def GetQualifiedTypeName(self: 'RubyTranspiler',name_parts: 'list[str]') -> 'str':
        delimiter: 'str' = "::"
        name_parts_index: 'int' = Size(name_parts)-1
        type_part: 'str' = Element(name_parts,name_parts_index)
        result: 'str' = self.GetTypeName(type_part)
        if name_parts_index>0:
            while name_parts_index>0:
                name_parts_index = name_parts_index-1
                result = Concat(delimiter,result)
                name_part: 'str' = Element(name_parts,name_parts_index)
                result = Concat(self.string_helper.ToUpper(name_part),result)
            result = Concat(delimiter,result)
        return result

    def BeginProcessingCTCodeFile(self: 'RubyTranspiler') -> 'None':
        ClearList(self.imports)
        self.current_interface = ""
        ClearList(self.interface_definitions)
        self.current_class = ""
        ClearList(self.class_definitions)
        ClearList(self.class_init)
        ClearList(self.class_functions)

    def ProcessExdef(self: 'RubyTranspiler',exdef: 'str') -> 'None':
        Append(self.imports,Concat(Concat("require '",exdef),"'"))

    def ProcessUnmanagedType(self: 'RubyTranspiler',unmanaged_type: 'str') -> 'None':
        pass

    def BeginProcessingInterface(self: 'RubyTranspiler',interface_name: 'str') -> 'None':
        self.current_interface = interface_name
        Append(self.interface_definitions,Concat("class ",interface_name))

    def ProcessInterfaceFunctionDeclaration(self: 'RubyTranspiler',return_type: 'str',function_name: 'str',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'None':
        Append(self.interface_definitions,Concat(Concat(Concat(Concat(self.string_helper.Indentation(1),"def "),function_name),self.MakeParametersString(parameters)),"; end"))

    def FinishProcessingInterface(self: 'RubyTranspiler',interface_name: 'str') -> 'None':
        Append(self.interface_definitions,"end")
        Append(self.interface_definitions,"")
        self.current_interface = ""

    def BeginProcessingClass(self: 'RubyTranspiler',class_name: 'str',implementing: 'str') -> 'None':
        self.current_class = class_name
        if implementing=="":
            Append(self.class_definitions,Concat("class ",class_name))
        else:
            Append(self.class_definitions,Concat(Concat(Concat("class ",class_name)," < "),implementing))
        ClearList(self.class_init)
        ClearList(self.class_functions)
        Append(self.class_init,Concat(self.string_helper.Indentation(1),"def initialize()"))

    def BeginProcessingClassFunctionDefinition(self: 'RubyTranspiler',return_type: 'str',function_name: 'str',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'None':
        Append(self.class_functions,"")
        Append(self.class_functions,Concat(Concat(Concat(self.string_helper.Indentation(1),"def "),function_name),self.MakeParametersString(parameters)))

    def BeginProcessCodeBlock(self: 'RubyTranspiler',indent: 'int') -> 'None':
        pass

    def FinishProcessCodeBlock(self: 'RubyTranspiler',indent: 'int') -> 'None':
        pass

    def BeginProcessConditional(self: 'RubyTranspiler',indent: 'int',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(self.string_helper.Indentation(indent),"if ("),r_value),")"))

    def ProcessElse(self: 'RubyTranspiler',indent: 'int') -> 'None':
        Append(self.class_functions,Concat(self.string_helper.Indentation(indent),"else"))

    def FinishProcessConditional(self: 'RubyTranspiler',indent: 'int',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(self.string_helper.Indentation(indent),"end"))

    def BeginProcessLoop(self: 'RubyTranspiler',indent: 'int',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(self.string_helper.Indentation(indent),"while ("),r_value),")"))

    def FinishProcessLoop(self: 'RubyTranspiler',indent: 'int',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(self.string_helper.Indentation(indent),"end"))

    def ProcessRtn(self: 'RubyTranspiler',indent: 'int',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(self.string_helper.Indentation(indent),"return "),r_value))

    def ProcessDeclaration(self: 'RubyTranspiler',indent: 'int',type: 'str',l_value: 'str',r_value: 'str') -> 'None':
        if r_value=="":
            r_value = self.GetDefault(type)
        Append(self.class_functions,Concat(Concat(Concat(self.string_helper.Indentation(indent),l_value)," = "),r_value))

    def ProcessAssignment(self: 'RubyTranspiler',indent: 'int',l_value: 'str',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(self.string_helper.Indentation(indent),l_value)," = "),r_value))

    def ProcessCall(self: 'RubyTranspiler',indent: 'int',call: 'str') -> 'None':
        Append(self.class_functions,Concat(self.string_helper.Indentation(indent),call))

    def FinishProcessingClassFunctionDefinition(self: 'RubyTranspiler',return_type: 'str',function_name: 'str',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'None':
        Append(self.class_functions,Concat(self.string_helper.Indentation(1),"end"))

    def ProcessClassMemberDeclaration(self: 'RubyTranspiler',member_type: 'str',member_name: 'str') -> 'None':
        Append(self.class_init,Concat(Concat(Concat(Concat(self.string_helper.Indentation(2),"@"),member_name)," = "),self.GetDefault(member_type)))

    def FinishProcessingClass(self: 'RubyTranspiler',class_name: 'str',implementing: 'str') -> 'None':
        Append(self.class_init,Concat(self.string_helper.Indentation(1),"end"))
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
        Append(self.class_definitions,"end")
        Append(self.class_definitions,"")
        self.current_class = ""

    def WriteCommonFunctions(self: 'RubyTranspiler',destination_file: 'S84_CTCode_System_ctcode.OutputStream') -> 'None':
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

    def TokenizeBaseName(self: 'RubyTranspiler',name: 'str') -> 'list[str]':
        base_name_tokens: 'list[str]' = []
        current_token: 'str' = ""
        index: 'int' = 0
        while index<Length(name):
            character: 'str' = At(name,index)
            if character==".":
                Append(base_name_tokens,current_token)
                current_token = ""
            else:
                current_token = Concat(current_token,character)
            index = index+1
        Append(base_name_tokens,current_token)
        return base_name_tokens

    def WriteBeginingNamespace(self: 'RubyTranspiler',file: 'S84_CTCode_System_ctcode.OutputStream') -> 'None':
        base_name_tokens: 'list[str]' = self.TokenizeBaseName(self.base_name)
        base_name_tokens_index: 'int' = 0
        while base_name_tokens_index<Size(base_name_tokens):
            base_name_token: 'str' = Element(base_name_tokens,base_name_tokens_index)
            file.WriteLine(Concat("module ",self.string_helper.ToUpper(base_name_token)))
            base_name_tokens_index = base_name_tokens_index+1

    def WriteEndingNamespace(self: 'RubyTranspiler',file: 'S84_CTCode_System_ctcode.OutputStream') -> 'None':
        base_name_tokens: 'list[str]' = self.TokenizeBaseName(self.base_name)
        base_name_tokens_index: 'int' = 0
        while base_name_tokens_index<Size(base_name_tokens):
            base_name_token: 'str' = Element(base_name_tokens,base_name_tokens_index)
            file.WriteLine("end")
            base_name_tokens_index = base_name_tokens_index+1

    def FinishProcessingCTCodeFile(self: 'RubyTranspiler') -> 'None':
        destination_file_name: 'str' = Concat(self.base_name,".rb")
        destination_file: 'S84_CTCode_System_ctcode.OutputStream' = self.system.OpenFileWriter(destination_file_name)
        if Size(self.imports)>0:
            self.string_helper.WriteLines(destination_file,self.imports)
            destination_file.WriteLine("")
        self.WriteCommonFunctions(destination_file)
        destination_file.WriteLine("")
        self.WriteBeginingNamespace(destination_file)
        destination_file.WriteLine("")
        self.string_helper.WriteLines(destination_file,self.interface_definitions)
        self.string_helper.WriteLines(destination_file,self.class_definitions)
        self.WriteEndingNamespace(destination_file)

    def GetDefault(self: 'RubyTranspiler',javascript_type: 'str') -> 'str':
        if javascript_type=="int":
            return "0"
        if javascript_type=="string":
            return "\"\""
        if javascript_type=="bool":
            return "false"
        if javascript_type=="float":
            return "0.0"
        if javascript_type=="void":
            return "nil"
        if self.string_helper.BeginsWith("dict[str",javascript_type):
            return "Hash.new()"
        if self.string_helper.BeginsWith("list[",javascript_type):
            return "Array.new()"
        return "nil"

    def MakeParametersString(self: 'RubyTranspiler',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'str':
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

