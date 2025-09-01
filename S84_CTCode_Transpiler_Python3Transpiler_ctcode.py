import S84_CTCode_dbnf_ctcode
import S84_CTCode_System_ctcode
import S84_CTCode_Transpiler_ctcode

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
def At(input: str, index: int) -> str: return input[index]
def IntAt(input: str, index: int) -> int: return ord(input[index])
def Concat(left: str, right: str) -> str: return left + right

class ParameterDeclaration:
    def __init__(self: 'ParameterDeclaration'):
        self.type: str = ""
        self.name: str = ""

    def GetType(self: 'ParameterDeclaration') -> 'str':
        return self.type

    def SetType(self: 'ParameterDeclaration',input: 'str') -> 'None':
        self.type = input

    def GetName(self: 'ParameterDeclaration') -> 'str':
        return self.name

    def SetName(self: 'ParameterDeclaration',input: 'str') -> 'None':
        self.name = input

class Python3Transpiler(S84_CTCode_Transpiler_ctcode.Transpiler):
    def __init__(self: 'Python3Transpiler'):
        self.system: S84_CTCode_System_ctcode.System = None
        self.c_t_code_file: S84_CTCode_dbnf_ctcode.CTCodeFile = None
        self.base_name: str = ""
        self.logger: S84_CTCode_System_ctcode.OutputStream = None
        self.imports: list[str] = []
        self.current_interface: str = ""
        self.interface_definitions: list[str] = []
        self.current_class: str = ""
        self.class_definitions: list[str] = []
        self.class_init: list[str] = []
        self.class_functions: list[str] = []

    def LogLine(self: 'Python3Transpiler',line: 'str') -> 'None':
        local_logger: 'S84_CTCode_System_ctcode.OutputStream' = self.logger
        local_logger.WriteLine(line)

    def GetBaseIndentation(self: 'Python3Transpiler') -> 'int':
        return 1

    def GetCallName(self: 'Python3Transpiler',name: 'S84_CTCode_dbnf_ctcode.Name') -> 'str':
        if name:
            return self.SnakeCaseToCamelCase(name.UnParse())
        else:
            return ""

    def GetVariableName(self: 'Python3Transpiler',name: 'S84_CTCode_dbnf_ctcode.Name') -> 'str':
        if name:
            value: 'str' = self.CamelCaseToSnakeCase(name.UnParse())
            if value=="myself":
                return "self"
            return value
        else:
            return ""

    def GetVariableChainNameTail(self: 'Python3Transpiler',tail: 'S84_CTCode_dbnf_ctcode.NameTail') -> 'str':
        accessor: 'str' = "."
        if tail:
            return Concat(Concat(accessor,self.GetVariableName(tail.GetName())),self.GetVariableChainNameTail(tail.GetTail()))
        else:
            return ""

    def GetVariableChain(self: 'Python3Transpiler',l_value: 'S84_CTCode_dbnf_ctcode.QualfiedName') -> 'str':
        if l_value:
            return Concat(self.GetVariableName(l_value.GetName()),self.GetVariableChainNameTail(l_value.GetTail()))
        else:
            return ""

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

    def GetTypeName(self: 'Python3Transpiler',name: 'S84_CTCode_dbnf_ctcode.Name') -> 'str':
        if name:
            return self.SnakeCaseToCamelCase(name.UnParse())
        else:
            return ""

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

    def GetQualifiedTypeName(self: 'Python3Transpiler',name_parts: 'list[S84_CTCode_dbnf_ctcode.Name]') -> 'str':
        package_delimiter: 'str' = "_"
        package_name_delimiter: 'str' = "."
        name_parts_index: 'int' = Size(name_parts)-1
        last_package_index: 'int' = Size(name_parts)-2
        type_part: 'S84_CTCode_dbnf_ctcode.Name' = Element(name_parts,name_parts_index)
        result: 'str' = self.GetTypeName(type_part)
        if name_parts_index>0:
            result = Concat(package_name_delimiter,result)
            while name_parts_index>0:
                name_parts_index = name_parts_index-1
                name_part: 'S84_CTCode_dbnf_ctcode.Name' = Element(name_parts,name_parts_index)
                if name_parts_index!=last_package_index:
                    result = Concat(package_delimiter,result)
                result = Concat(name_part.UnParse(),result)
        return result

    def BeginProcessingCTCodeFile(self: 'Python3Transpiler') -> 'None':
        ClearList(self.imports)
        self.current_interface = ""
        ClearList(self.interface_definitions)
        self.current_class = ""
        ClearList(self.class_definitions)
        ClearList(self.class_init)
        ClearList(self.class_functions)
        ClearList(self.imports)
        ClearList(self.interface_definitions)
        ClearList(self.class_definitions)

    def ProcessExdef(self: 'Python3Transpiler',exdef: 'str') -> 'None':
        Append(self.imports,Concat("import ",self.StripDot(exdef)))

    def ProcessUnmanagedType(self: 'Python3Transpiler',unmanaged_type: 'str') -> 'None':
        noop: 'int' = 0

    def BeginProcessingInterface(self: 'Python3Transpiler',interface_name: 'str') -> 'None':
        self.current_interface = interface_name
        Append(self.interface_definitions,Concat(Concat("class ",interface_name),":"))

    def ProcessInterfaceFunctionDeclaration(self: 'Python3Transpiler',return_type: 'str',function_name: 'str',parameters: 'list[ParameterDeclaration]') -> 'None':
        Append(self.interface_definitions,Concat(Concat(Concat(Concat(Concat(Concat(self.Indentation(1),"def "),function_name),self.MakeParametersString(self.current_interface,parameters))," -> '"),return_type),"': pass"))

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
        Append(self.class_init,Concat(Concat(Concat(self.Indentation(1),"def __init__(self: '"),class_name),"'):"))

    def BeginProcessingClassFunctionDefinition(self: 'Python3Transpiler',return_type: 'str',function_name: 'str',parameters: 'list[ParameterDeclaration]') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(Concat(Concat(Concat(self.Indentation(1),"def "),function_name),self.MakeParametersString(self.current_class,parameters))," -> '"),return_type),"':"))

    def BeginProcessCodeBlock(self: 'Python3Transpiler',indent: 'int') -> 'None':
        noop: 'int' = 0

    def FinishProcessCodeBlock(self: 'Python3Transpiler',indent: 'int') -> 'None':
        noop: 'int' = 0

    def BeginProcessConditional(self: 'Python3Transpiler',indent: 'int',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(self.Indentation(indent),"if "),r_value),":"))

    def ProcessElse(self: 'Python3Transpiler',indent: 'int') -> 'None':
        Append(self.class_functions,Concat(self.Indentation(indent),"else:"))

    def FinishProcessConditional(self: 'Python3Transpiler',indent: 'int',r_value: 'str') -> 'None':
        noop: 'int' = 0

    def BeginProcessLoop(self: 'Python3Transpiler',indent: 'int',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(self.Indentation(indent),"while "),r_value),":"))

    def FinishProcessLoop(self: 'Python3Transpiler',indent: 'int',r_value: 'str') -> 'None':
        noop: 'int' = 0

    def ProcessRtn(self: 'Python3Transpiler',indent: 'int',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(self.Indentation(indent),"return "),r_value))

    def ProcessDeclaration(self: 'Python3Transpiler',indent: 'int',type: 'str',l_value: 'str',r_value: 'str') -> 'None':
        if r_value=="":
            r_value = self.GetDefault(type)
        Append(self.class_functions,Concat(Concat(Concat(Concat(Concat(self.Indentation(indent),l_value),": '"),type),"' = "),r_value))

    def ProcessAssignment(self: 'Python3Transpiler',indent: 'int',l_value: 'str',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(self.Indentation(indent),l_value)," = "),r_value))

    def ProcessCall(self: 'Python3Transpiler',indent: 'int',call: 'str') -> 'None':
        Append(self.class_functions,Concat(self.Indentation(indent),call))

    def FinishProcessingClassFunctionDefinition(self: 'Python3Transpiler',return_type: 'str',function_name: 'str',parameters: 'list[ParameterDeclaration]') -> 'None':
        Append(self.class_functions,"")

    def ProcessClassMemberDeclaration(self: 'Python3Transpiler',member_type: 'str',member_name: 'str') -> 'None':
        Append(self.class_init,Concat(Concat(Concat(Concat(Concat(Concat(self.Indentation(2),"self."),member_name),": "),member_type)," = "),self.GetDefault(member_type)))

    def FinishProcessingClass(self: 'Python3Transpiler',class_name: 'str',implementing: 'str') -> 'None':
        if Size(self.class_init)==1:
            Append(self.class_init,Concat(self.Indentation(2),"pass"))
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
        destination_file.WriteLine("def At(input: str, index: int) -> str: return input[index]")
        destination_file.WriteLine("def IntAt(input: str, index: int) -> int: return ord(input[index])")
        destination_file.WriteLine("def Concat(left: str, right: str) -> str: return left + right")

    def FinishProcessingCTCodeFile(self: 'Python3Transpiler') -> 'None':
        destination_file_name: 'str' = Concat(self.StripDot(self.base_name),".py")
        system: 'S84_CTCode_System_ctcode.System' = self.system
        destination_file: 'S84_CTCode_System_ctcode.OutputStream' = system.OpenFileWriter(destination_file_name)
        if Size(self.imports)>0:
            self.WriteLines(destination_file,self.imports)
            destination_file.WriteLine("")
        self.WriteCommonFunctions(destination_file)
        destination_file.WriteLine("")
        self.WriteLines(destination_file,self.interface_definitions)
        self.WriteLines(destination_file,self.class_definitions)

    def BeginsWith(self: 'Python3Transpiler',prefix: 'str',value: 'str') -> 'bool':
        if Length(prefix)>Length(value):
            return False
        prefix_index: 'int' = 0
        while prefix_index<Length(prefix):
            if At(prefix,prefix_index)!=At(value,prefix_index):
                return False
            prefix_index = prefix_index+1
        return True

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
        if self.BeginsWith("dict[str",python_type):
            return "{}"
        if self.BeginsWith("list[",python_type):
            return "[]"
        return "None"

    def MakeParametersString(self: 'Python3Transpiler',self_type: 'str',parameters: 'list[ParameterDeclaration]') -> 'str':
        result: 'str' = Concat(Concat("(self: '",self_type),"'")
        parameters_index: 'int' = 0
        while parameters_index<Size(parameters):
            parameter: 'ParameterDeclaration' = Element(parameters,parameters_index)
            result = Concat(result,",")
            result = Concat(Concat(Concat(Concat(result,parameter.GetName()),": '"),parameter.GetType()),"'")
            parameters_index = parameters_index+1
        result = Concat(result,")")
        return result

    def StripDot(self: 'Python3Transpiler',input: 'str') -> 'str':
        index: 'int' = 0
        index = 0
        result: 'str' = ""
        result = ""
        while index<Length(input):
            character: 'str' = ""
            character = At(input,index)
            if character==".":
                result = Concat(result,"_")
            else:
                result = Concat(result,character)
            index = index+1
        return result

    def WriteLines(self: 'Python3Transpiler',destination: 'S84_CTCode_System_ctcode.OutputStream',lines: 'list[str]') -> 'None':
        lines_index: 'int' = 0
        while lines_index<Size(lines):
            line: 'str' = Element(lines,lines_index)
            destination.WriteLine(line)
            lines_index = lines_index+1

    def Transpile(self: 'Python3Transpiler',system: 'S84_CTCode_System_ctcode.System',c_t_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile',base_name: 'str') -> 'int':
        self.system = system
        self.c_t_code_file = c_t_code_file
        self.base_name = base_name
        self.logger = system.GetLoggerDestination()
        self.ProcessCTCodeFile(c_t_code_file)
        return 0

    def ProcessCTCodeFile(self: 'Python3Transpiler',c_t_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile') -> 'None':
        self.BeginProcessingCTCodeFile()
        self.ProcessExdefs(c_t_code_file)
        self.ProcessUnmanagedTypes(c_t_code_file)
        self.ProcessDefinitions(c_t_code_file)
        self.FinishProcessingCTCodeFile()

    def ProcessExdefs(self: 'Python3Transpiler',c_t_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile') -> 'None':
        exdefs: 'list[S84_CTCode_dbnf_ctcode.ExternalDefinition]' = c_t_code_file.GetDeclarations()
        exdefs_index: 'int' = 0
        while exdefs_index<Size(exdefs):
            exdef: 'S84_CTCode_dbnf_ctcode.ExternalDefinition' = Element(exdefs,exdefs_index)
            exdef_name: 'S84_CTCode_dbnf_ctcode.QualfiedName' = exdef.GetExdef()
            self.ProcessExdef(exdef_name.UnParse())
            exdefs_index = exdefs_index+1

    def ProcessUnmanagedTypes(self: 'Python3Transpiler',c_t_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile') -> 'None':
        unmanaged_types: 'list[S84_CTCode_dbnf_ctcode.UnmanagedType]' = c_t_code_file.GetUnmanagedTypes()
        unmanaged_types_index: 'int' = 0
        while unmanaged_types_index<Size(unmanaged_types):
            unmanaged_type: 'S84_CTCode_dbnf_ctcode.UnmanagedType' = Element(unmanaged_types,unmanaged_types_index)
            self.ProcessUnmanagedType(self.GetQualifiedTypeNameInternal(unmanaged_type.GetUnmanagedType()))
            unmanaged_types_index = unmanaged_types_index+1

    def ProcessDefinitions(self: 'Python3Transpiler',c_t_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile') -> 'None':
        definitions: 'list[S84_CTCode_dbnf_ctcode.Definition]' = c_t_code_file.GetDefinitions()
        definitions_index: 'int' = 0
        while definitions_index<Size(definitions):
            definition: 'S84_CTCode_dbnf_ctcode.Definition' = None
            definition = Element(definitions,definitions_index)
            if definition.GetInterfaceDef():
                self.ProcessInterfaceDefinition(definition.GetInterfaceDef())
            if definition.GetClassDef():
                self.ProcessClassDefinition(definition.GetClassDef())
            definitions_index = definitions_index+1

    def GetParameters(self: 'Python3Transpiler',parameter_list_def: 'S84_CTCode_dbnf_ctcode.ParameterListDef') -> 'list[ParameterDeclaration]':
        result: 'list[ParameterDeclaration]' = []
        while parameter_list_def:
            parameter: 'ParameterDeclaration' = ParameterDeclaration()
            parameter.SetType(self.GetType(parameter_list_def.GetType()))
            parameter.SetName(self.GetVariableName(parameter_list_def.GetName()))
            Append(result,parameter)
            parameter_list_def = parameter_list_def.GetParameterTail()
        return result

    def ProcessInterfaceDefinition(self: 'Python3Transpiler',interface_definition: 'S84_CTCode_dbnf_ctcode.InterfaceDef') -> 'None':
        interface_name: 'str' = self.GetTypeName(interface_definition.GetName())
        self.BeginProcessingInterface(interface_name)
        declarations: 'list[S84_CTCode_dbnf_ctcode.ContentDeclaration]' = interface_definition.GetDeclarations()
        declarations_index: 'int' = 0
        while declarations_index<Size(declarations):
            declaration: 'S84_CTCode_dbnf_ctcode.ContentDeclaration' = Element(declarations,declarations_index)
            return_type: 'str' = self.GetType(declaration.GetType())
            function_name: 'str' = self.GetCallName(declaration.GetName())
            parameters: 'list[ParameterDeclaration]' = self.GetParameters(declaration.GetParameters())
            self.ProcessInterfaceFunctionDeclaration(return_type,function_name,parameters)
            declarations_index = declarations_index+1
        self.FinishProcessingInterface(interface_name)

    def ProcessClassDefinition(self: 'Python3Transpiler',class_definition: 'S84_CTCode_dbnf_ctcode.ClassDef') -> 'None':
        class_name: 'str' = self.GetTypeName(class_definition.GetName())
        implementing: 'str' = ""
        implementation_spec: 'S84_CTCode_dbnf_ctcode.ImplementationSpec' = class_definition.GetImplementing()
        if implementation_spec:
            implementing = self.GetQualifiedTypeNameInternal(implementation_spec.GetInterface())
        self.BeginProcessingClass(class_name,implementing)
        definitions: 'list[S84_CTCode_dbnf_ctcode.ContentDefinition]' = class_definition.GetDefinitions()
        definitions_index: 'int' = 0
        while definitions_index<Size(definitions):
            definition: 'S84_CTCode_dbnf_ctcode.ContentDefinition' = Element(definitions,definitions_index)
            if definition.GetFunctionBody():
                return_type: 'str' = self.GetType(definition.GetType())
                function_name: 'str' = self.GetCallName(definition.GetName())
                parameters: 'list[ParameterDeclaration]' = self.GetParameters(definition.GetParameters())
                self.BeginProcessingClassFunctionDefinition(return_type,function_name,parameters)
                self.ProcessCodeBlockInternal(self.GetBaseIndentation(),definition.GetFunctionBody())
                self.FinishProcessingClassFunctionDefinition(return_type,function_name,parameters)
            else:
                member_type: 'str' = self.GetType(definition.GetType())
                member_name: 'str' = self.GetVariableName(definition.GetName())
                self.ProcessClassMemberDeclaration(member_type,member_name)
            definitions_index = definitions_index+1
        self.FinishProcessingClass(class_name,implementing)

    def ProcessInstructionInternal(self: 'Python3Transpiler',indent: 'int',instruction: 'S84_CTCode_dbnf_ctcode.Instruction') -> 'None':
        if instruction.GetCodeBlock():
            self.ProcessCodeBlockInternal(indent,instruction.GetCodeBlock())
        if instruction.GetRtn():
            self.ProcessRtnInternal(indent,instruction.GetRtn())
        if instruction.GetDeclaration():
            self.ProcessDeclarationInternal(indent,instruction.GetDeclaration())
        if instruction.GetAssignment():
            self.ProcessAssignmentInternal(indent,instruction.GetAssignment())
        if instruction.GetCall():
            self.ProcessCallInternal(indent,instruction.GetCall())
        if instruction.GetConditional():
            self.ProcessConditionalInternal(indent,instruction.GetConditional())
        if instruction.GetLoop():
            self.ProcessLoopInternal(indent,instruction.GetLoop())

    def ProcessCodeBlockInternal(self: 'Python3Transpiler',indent: 'int',code_block: 'S84_CTCode_dbnf_ctcode.CodeBlock') -> 'None':
        self.BeginProcessCodeBlock(indent)
        instructions: 'list[S84_CTCode_dbnf_ctcode.Instruction]' = code_block.GetInstructions()
        instructions_index: 'int' = 0
        while instructions_index<Size(instructions):
            self.ProcessInstructionInternal(indent+1,Element(instructions,instructions_index))
            instructions_index = instructions_index+1
        self.FinishProcessCodeBlock(indent)

    def ProcessConditionalInternal(self: 'Python3Transpiler',indent: 'int',conditional: 'S84_CTCode_dbnf_ctcode.Conditional') -> 'None':
        r_value: 'str' = self.GetRValueInternal(conditional.GetRValue())
        self.BeginProcessConditional(indent,r_value)
        self.ProcessCodeBlockInternal(indent,conditional.GetCodeBlock())
        if conditional.GetElseTail():
            else_tail: 'S84_CTCode_dbnf_ctcode.ElseTail' = conditional.GetElseTail()
            self.ProcessElse(indent)
            self.ProcessCodeBlockInternal(indent,else_tail.GetCodeBlock())
        self.FinishProcessConditional(indent,r_value)

    def ProcessLoopInternal(self: 'Python3Transpiler',indent: 'int',loop: 'S84_CTCode_dbnf_ctcode.Loop') -> 'None':
        r_value: 'str' = self.GetRValueInternal(loop.GetRValue())
        self.BeginProcessLoop(indent,r_value)
        self.ProcessCodeBlockInternal(indent,loop.GetCodeBlock())
        self.FinishProcessLoop(indent,r_value)

    def ProcessRtnInternal(self: 'Python3Transpiler',indent: 'int',rtn: 'S84_CTCode_dbnf_ctcode.Return') -> 'None':
        r_value: 'str' = self.GetRValueInternal(rtn.GetRValue())
        self.ProcessRtn(indent,r_value)

    def ProcessDeclarationInternal(self: 'Python3Transpiler',indent: 'int',declaration: 'S84_CTCode_dbnf_ctcode.Declaration') -> 'None':
        type: 'str' = self.GetType(declaration.GetType())
        l_value: 'str' = self.GetVariableName(declaration.GetName())
        r_value: 'str' = ""
        declaration_assignment: 'S84_CTCode_dbnf_ctcode.DeclarationAssign' = declaration.GetAssignment()
        if declaration_assignment:
            r_value = self.GetRValueInternal(declaration_assignment.GetRValue())
        self.ProcessDeclaration(indent,type,l_value,r_value)

    def ProcessAssignmentInternal(self: 'Python3Transpiler',indent: 'int',assignment: 'S84_CTCode_dbnf_ctcode.Assignment') -> 'None':
        self.ProcessAssignment(indent,self.GetVariableChain(assignment.GetLValue()),self.GetRValueInternal(assignment.GetRValue()))

    def ProcessCallInternal(self: 'Python3Transpiler',indent: 'int',call: 'S84_CTCode_dbnf_ctcode.Call') -> 'None':
        self.ProcessCall(indent,self.ConvertCallInternal(call))

    def ConvertCallInternal(self: 'Python3Transpiler',call: 'S84_CTCode_dbnf_ctcode.Call') -> 'str':
        name_chain: 'list[str]' = []
        parameters: 'list[str]' = []
        if call.GetVariable():
            Append(name_chain,self.GetVariableName(call.GetVariable()))
        if call.GetFunction():
            Append(name_chain,self.GetCallName(call.GetFunction()))
        if call.GetFunctionChain():
            function_chain: 'S84_CTCode_dbnf_ctcode.QualfiedName' = call.GetFunctionChain()
            name_tail: 'S84_CTCode_dbnf_ctcode.NameTail' = function_chain.GetTail()
            if function_chain.GetTail():
                Append(name_chain,self.GetVariableName(function_chain.GetName()))
            else:
                Append(name_chain,self.GetCallName(function_chain.GetName()))
            while name_tail:
                if name_tail.GetTail():
                    Append(name_chain,self.GetVariableName(name_tail.GetName()))
                else:
                    Append(name_chain,self.GetCallName(name_tail.GetName()))
                name_tail = name_tail.GetTail()
        parameter_list: 'S84_CTCode_dbnf_ctcode.ParameterList' = call.GetParameters()
        while parameter_list:
            Append(parameters,self.GetRValueInternal(parameter_list.GetRValue()))
            parameter_list = parameter_list.GetParameterTail()
        return self.ConvertCall(name_chain,parameters)

    def GetSingletonType(self: 'Python3Transpiler',singleton_type: 'S84_CTCode_dbnf_ctcode.SingletonType') -> 'str':
        if singleton_type.GetPrimativeType():
            return self.GetPrimativeType(singleton_type.UnParse())
        if singleton_type.GetDefinedType():
            defined_type: 'S84_CTCode_dbnf_ctcode.DefinedType' = singleton_type.GetDefinedType()
            return self.GetQualifiedTypeNameInternal(defined_type.GetName())
        return ""

    def GetRValueSingleBasisInternal(self: 'Python3Transpiler',r_value_single: 'S84_CTCode_dbnf_ctcode.RValueSingle') -> 'str':
        call: 'S84_CTCode_dbnf_ctcode.Call' = r_value_single.GetCall()
        if call:
            return self.ConvertCallInternal(call)
        allocate: 'S84_CTCode_dbnf_ctcode.Allocate' = r_value_single.GetAllocate()
        if allocate:
            return self.ConvertAllocate(self.GetQualifiedTypeNameInternal(allocate.GetManagedType()))
        byte_literal: 'S84_CTCode_dbnf_ctcode.Byte' = r_value_single.GetByteLiteral()
        if byte_literal:
            high: 'S84_CTCode_dbnf_ctcode.ByteDigit' = byte_literal.GetHigh()
            low: 'S84_CTCode_dbnf_ctcode.ByteDigit' = byte_literal.GetLow()
            return self.ConvertByte(high.UnParse(),low.UnParse())
        decimal_literal: 'S84_CTCode_dbnf_ctcode.Decimal' = r_value_single.GetDecimalLiteral()
        if decimal_literal:
            return self.ConvertDecimal(decimal_literal.UnParse())
        integer_literal: 'S84_CTCode_dbnf_ctcode.Number' = r_value_single.GetIntegerLiteral()
        if integer_literal:
            return self.ConvertNumber(integer_literal.UnParse())
        boolean_literal: 'S84_CTCode_dbnf_ctcode.Boolean' = r_value_single.GetBooleanLiteral()
        if boolean_literal:
            return self.ConvertBoolean(boolean_literal.UnParse())
        variable: 'S84_CTCode_dbnf_ctcode.QualfiedName' = r_value_single.GetVariable()
        if variable:
            return self.ConvertVariable(self.GetVariableChain(variable))
        string_literal: 'S84_CTCode_dbnf_ctcode.Literal' = r_value_single.GetStringLiteral()
        if string_literal:
            return self.ConvertString(string_literal.UnParse())
        return ""

    def GetRValueSingleInternal(self: 'Python3Transpiler',r_value_single: 'S84_CTCode_dbnf_ctcode.RValueSingle') -> 'str':
        unary_operator: 'S84_CTCode_dbnf_ctcode.UnaryOperator' = r_value_single.GetUnaryOperator()
        if unary_operator:
            return self.UnaryOperator(unary_operator.UnParse(),self.GetRValueSingleBasisInternal(r_value_single))
        return self.GetRValueSingleBasisInternal(r_value_single)

    def GetRValueBinaryInternal(self: 'Python3Transpiler',r_value_l: 'str',r_value_tail: 'S84_CTCode_dbnf_ctcode.RValueTail') -> 'str':
        r_value_r: 'str' = self.GetRValueSingleInternal(r_value_tail.GetValue())
        binary_operator: 'S84_CTCode_dbnf_ctcode.BinaryOperator' = r_value_tail.GetBinaryOperator()
        r_value_l = self.BinaryOperator(binary_operator.UnParse(),r_value_l,r_value_r)
        if r_value_tail.GetTail():
            return self.GetRValueBinaryInternal(r_value_l,r_value_tail.GetTail())
        return r_value_l

    def GetRValueInternal(self: 'Python3Transpiler',r_value: 'S84_CTCode_dbnf_ctcode.RValue') -> 'str':
        r_value_l: 'str' = self.GetRValueSingleInternal(r_value.GetValue())
        if r_value.GetTail():
            return self.GetRValueBinaryInternal(r_value_l,r_value.GetTail())
        return r_value_l

    def GetQualifiedTypeNameInternal(self: 'Python3Transpiler',qualified_name: 'S84_CTCode_dbnf_ctcode.QualfiedName') -> 'str':
        name_parts: 'list[S84_CTCode_dbnf_ctcode.Name]' = []
        Append(name_parts,qualified_name.GetName())
        tail: 'S84_CTCode_dbnf_ctcode.NameTail' = qualified_name.GetTail()
        while tail:
            Append(name_parts,tail.GetName())
            tail = tail.GetTail()
        return self.GetQualifiedTypeName(name_parts)

    def GetType(self: 'Python3Transpiler',type: 'S84_CTCode_dbnf_ctcode.ValueType') -> 'str':
        if type.GetDimensionalType():
            dimensional_type: 'S84_CTCode_dbnf_ctcode.DimensionalType' = type.GetDimensionalType()
            singleton_type: 'S84_CTCode_dbnf_ctcode.SingletonType' = dimensional_type.GetSingletonType()
            return self.GetDimensionalType(self.GetSingletonType(singleton_type),Size(dimensional_type.GetDimensionalNote()))
        if type.GetMapType():
            map_type: 'S84_CTCode_dbnf_ctcode.MapType' = type.GetMapType()
            singleton_type: 'S84_CTCode_dbnf_ctcode.SingletonType' = map_type.GetSingletonType()
            return self.GetMapType(self.GetSingletonType(singleton_type))
        if type.GetSingletonType():
            singleton_type: 'S84_CTCode_dbnf_ctcode.SingletonType' = type.GetSingletonType()
            return self.GetSingletonType(singleton_type)
        return ""

    def Indentation(self: 'Python3Transpiler',indent: 'int') -> 'str':
        result: 'str' = ""
        result = ""
        while indent>0:
            indent = indent-1
            result = Concat(result,"    ")
        return result

    def SnakeCaseToCamelCase(self: 'Python3Transpiler',snake_case: 'str') -> 'str':
        capitalize_this_letter: 'bool' = True
        camel_case: 'str' = ""
        index: 'int' = 0
        index = 0
        while index<Length(snake_case):
            source_character: 'str' = At(snake_case,index)
            if source_character=="_":
                capitalize_this_letter = True
            else:
                if capitalize_this_letter==True:
                    upper_character: 'str' = self.CharacterToUpper(source_character)
                    capitalize_this_letter = False
                    camel_case = Concat(camel_case,upper_character)
                else:
                    capitalize_this_letter = False
                    camel_case = Concat(camel_case,source_character)
            index = index+1
        return camel_case

    def CamelCaseToSnakeCase(self: 'Python3Transpiler',camel_case: 'str') -> 'str':
        delimiter: 'str' = "_"
        snake_case: 'str' = ""
        index: 'int' = 0
        while index<Length(camel_case):
            source_character: 'str' = At(camel_case,index)
            lower_character: 'str' = self.CharacterToLower(source_character)
            if self.IsUpper(source_character) or self.IsDigit(source_character):
                is_first_character: 'bool' = Length(snake_case)==0
                if not is_first_character:
                    snake_case = Concat(snake_case,delimiter)
            snake_case = Concat(snake_case,lower_character)
            index = index+1
        return snake_case

    def IsUpper(self: 'Python3Transpiler',character: 'str') -> 'bool':
        result: 'bool' = False
        result = False
        result = result or character=="A"
        result = result or character=="B"
        result = result or character=="C"
        result = result or character=="D"
        result = result or character=="E"
        result = result or character=="F"
        result = result or character=="G"
        result = result or character=="H"
        result = result or character=="I"
        result = result or character=="J"
        result = result or character=="K"
        result = result or character=="L"
        result = result or character=="M"
        result = result or character=="N"
        result = result or character=="O"
        result = result or character=="P"
        result = result or character=="Q"
        result = result or character=="R"
        result = result or character=="S"
        result = result or character=="T"
        result = result or character=="U"
        result = result or character=="V"
        result = result or character=="W"
        result = result or character=="X"
        result = result or character=="Y"
        result = result or character=="Z"
        return result

    def IsDigit(self: 'Python3Transpiler',character: 'str') -> 'bool':
        result: 'bool' = False
        result = False
        result = result or character=="0"
        result = result or character=="1"
        result = result or character=="2"
        result = result or character=="3"
        result = result or character=="4"
        result = result or character=="5"
        result = result or character=="6"
        result = result or character=="7"
        result = result or character=="8"
        result = result or character=="9"
        return result

    def ToLower(self: 'Python3Transpiler',input: 'str') -> 'str':
        index: 'int' = 0
        result: 'str' = ""
        while index<Length(input):
            character: 'str' = At(input,index)
            lower_character: 'str' = self.CharacterToLower(character)
            result = Concat(result,lower_character)
            index = index+1
        return result

    def CharacterToLower(self: 'Python3Transpiler',input: 'str') -> 'str':
        if input=="A":
            return "a"
        if input=="B":
            return "b"
        if input=="C":
            return "c"
        if input=="D":
            return "d"
        if input=="E":
            return "e"
        if input=="F":
            return "f"
        if input=="G":
            return "g"
        if input=="H":
            return "h"
        if input=="I":
            return "i"
        if input=="J":
            return "j"
        if input=="K":
            return "k"
        if input=="L":
            return "l"
        if input=="M":
            return "m"
        if input=="N":
            return "n"
        if input=="O":
            return "o"
        if input=="P":
            return "p"
        if input=="Q":
            return "q"
        if input=="R":
            return "r"
        if input=="S":
            return "s"
        if input=="T":
            return "t"
        if input=="U":
            return "u"
        if input=="V":
            return "v"
        if input=="W":
            return "w"
        if input=="X":
            return "x"
        if input=="Y":
            return "y"
        if input=="Z":
            return "z"
        return input

    def ToUpper(self: 'Python3Transpiler',input: 'str') -> 'str':
        index: 'int' = 0
        result: 'str' = ""
        while index<Length(input):
            character: 'str' = At(input,index)
            upper_character: 'str' = self.CharacterToUpper(character)
            result = Concat(result,upper_character)
            index = index+1
        return result

    def CharacterToUpper(self: 'Python3Transpiler',input: 'str') -> 'str':
        if input=="a":
            return "A"
        if input=="b":
            return "B"
        if input=="c":
            return "C"
        if input=="d":
            return "D"
        if input=="e":
            return "E"
        if input=="f":
            return "F"
        if input=="g":
            return "G"
        if input=="h":
            return "H"
        if input=="i":
            return "I"
        if input=="j":
            return "J"
        if input=="k":
            return "K"
        if input=="l":
            return "L"
        if input=="m":
            return "M"
        if input=="n":
            return "N"
        if input=="o":
            return "O"
        if input=="p":
            return "P"
        if input=="q":
            return "Q"
        if input=="r":
            return "R"
        if input=="s":
            return "S"
        if input=="t":
            return "T"
        if input=="u":
            return "U"
        if input=="v":
            return "V"
        if input=="w":
            return "W"
        if input=="x":
            return "X"
        if input=="y":
            return "Y"
        if input=="z":
            return "Z"
        return input

