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
def At(input: str, index: int) -> str: return input[index:index+1]
def IntAt(input: str, index: int) -> int: return ord(input[index:index+1])
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

class LogToConsole(S84_CTCode_Transpiler_ctcode.Transpiler):
    def __init__(self: 'LogToConsole'):
        self.system: S84_CTCode_System_ctcode.System = None
        self.c_t_code_file: S84_CTCode_dbnf_ctcode.CTCodeFile = None
        self.base_name: str = ""
        self.logger: S84_CTCode_System_ctcode.OutputStream = None

    def LogLine(self: 'LogToConsole',line: 'str') -> 'None':
        local_logger: 'S84_CTCode_System_ctcode.OutputStream' = self.logger
        local_logger.WriteLine(line)

    def GetBaseIndentation(self: 'LogToConsole') -> 'int':
        return 3

    def GetCallName(self: 'LogToConsole',name: 'S84_CTCode_dbnf_ctcode.Name') -> 'str':
        if name:
            return self.SnakeCaseToCamelCase(name.UnParse())
        else:
            return ""

    def GetVariableName(self: 'LogToConsole',name: 'S84_CTCode_dbnf_ctcode.Name') -> 'str':
        if name:
            value: 'str' = self.CamelCaseToSnakeCase(name.UnParse())
            if value=="myself":
                return "self"
            return value
        else:
            return ""

    def GetVariableChainNameTail(self: 'LogToConsole',tail: 'S84_CTCode_dbnf_ctcode.NameTail') -> 'str':
        accessor: 'str' = "."
        if tail:
            return Concat(Concat(accessor,self.GetVariableName(tail.GetName())),self.GetVariableChainNameTail(tail.GetTail()))
        else:
            return ""

    def GetVariableChain(self: 'LogToConsole',l_value: 'S84_CTCode_dbnf_ctcode.QualfiedName') -> 'str':
        if l_value:
            return Concat(self.GetVariableName(l_value.GetName()),self.GetVariableChainNameTail(l_value.GetTail()))
        else:
            return ""

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

    def ConvertDecimal(self: 'LogToConsole',decimal: 'str') -> 'str':
        return decimal

    def ConvertNumber(self: 'LogToConsole',number: 'str') -> 'str':
        return number

    def ConvertBoolean(self: 'LogToConsole',boolean: 'str') -> 'str':
        if boolean=="true":
            return "true"
        if boolean=="false":
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

    def GetTypeName(self: 'LogToConsole',name: 'S84_CTCode_dbnf_ctcode.Name') -> 'str':
        if name:
            return self.SnakeCaseToCamelCase(name.UnParse())
        else:
            return ""

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

    def GetQualifiedTypeName(self: 'LogToConsole',name_parts: 'list[S84_CTCode_dbnf_ctcode.Name]') -> 'str':
        delimiter: 'str' = "."
        first_name: 'S84_CTCode_dbnf_ctcode.Name' = Element(name_parts,0)
        result: 'str' = first_name.UnParse()
        name_parts_index: 'int' = 1
        while name_parts_index<Size(name_parts):
            name: 'S84_CTCode_dbnf_ctcode.Name' = Element(name_parts,name_parts_index)
            result = Concat(Concat(result,delimiter),name.UnParse())
            name_parts_index = name_parts_index+1
        return result

    def BeginProcessingCTCodeFile(self: 'LogToConsole') -> 'None':
        self.LogLine("BeginProcessingCTCodeFile")

    def ProcessExdef(self: 'LogToConsole',exdef: 'str') -> 'None':
        self.LogLine(Concat(Concat(self.Indentation(1),"ProcessExdef: "),exdef))

    def ProcessUnmanagedType(self: 'LogToConsole',unmanaged_type: 'str') -> 'None':
        self.LogLine(Concat(Concat(self.Indentation(1),"ProcessUnmanagedType: "),unmanaged_type))

    def BeginProcessingInterface(self: 'LogToConsole',interface_name: 'str') -> 'None':
        self.LogLine(Concat(Concat(self.Indentation(1),"BeginProcessingInterface: "),interface_name))

    def ProcessInterfaceFunctionDeclaration(self: 'LogToConsole',return_type: 'str',function_name: 'str',parameters: 'list[ParameterDeclaration]') -> 'None':
        self.LogLine(Concat(Concat(Concat(Concat(self.Indentation(2),"ProcessInterfaceFunctionDeclaration: "),return_type)," "),function_name))

    def FinishProcessingInterface(self: 'LogToConsole',interface_name: 'str') -> 'None':
        self.LogLine(Concat(Concat(self.Indentation(1),"FinishProcessingInterface: "),interface_name))

    def BeginProcessingClass(self: 'LogToConsole',class_name: 'str',implementing: 'str') -> 'None':
        self.LogLine(Concat(Concat(Concat(Concat(self.Indentation(1),"BeginProcessingClass: "),class_name)," "),implementing))

    def BeginProcessingClassFunctionDefinition(self: 'LogToConsole',return_type: 'str',function_name: 'str',parameters: 'list[ParameterDeclaration]') -> 'None':
        self.LogLine(Concat(Concat(Concat(Concat(self.Indentation(2),"BeginProcessingClassFunctionDefinition: "),return_type)," "),function_name))

    def BeginProcessCodeBlock(self: 'LogToConsole',indent: 'int') -> 'None':
        self.LogLine(Concat(self.Indentation(indent),"BeginProcessCodeBlock"))

    def FinishProcessCodeBlock(self: 'LogToConsole',indent: 'int') -> 'None':
        self.LogLine(Concat(self.Indentation(indent),"FinishProcessCodeBlock"))

    def BeginProcessConditional(self: 'LogToConsole',indent: 'int',r_value: 'str') -> 'None':
        self.LogLine(Concat(Concat(self.Indentation(indent),"BeginProcessConditional: "),r_value))

    def ProcessElse(self: 'LogToConsole',indent: 'int') -> 'None':
        self.LogLine(Concat(self.Indentation(indent),"ProcessElse"))

    def FinishProcessConditional(self: 'LogToConsole',indent: 'int',r_value: 'str') -> 'None':
        self.LogLine(Concat(Concat(self.Indentation(indent),"FinishProcessConditional: "),r_value))

    def BeginProcessLoop(self: 'LogToConsole',indent: 'int',r_value: 'str') -> 'None':
        self.LogLine(Concat(Concat(self.Indentation(indent),"BeginProcessLoop: "),r_value))

    def FinishProcessLoop(self: 'LogToConsole',indent: 'int',r_value: 'str') -> 'None':
        self.LogLine(Concat(Concat(self.Indentation(indent),"FinishProcessLoop: "),r_value))

    def ProcessRtn(self: 'LogToConsole',indent: 'int',r_value: 'str') -> 'None':
        self.LogLine(Concat(Concat(self.Indentation(indent),"ProcessRtn: "),r_value))

    def ProcessDeclaration(self: 'LogToConsole',indent: 'int',type: 'str',l_value: 'str',r_value: 'str') -> 'None':
        self.LogLine(Concat(Concat(Concat(Concat(Concat(Concat(self.Indentation(indent),"ProcessDeclaration: "),type)," "),l_value)," "),r_value))

    def ProcessAssignment(self: 'LogToConsole',indent: 'int',l_value: 'str',r_value: 'str') -> 'None':
        self.LogLine(Concat(Concat(Concat(Concat(self.Indentation(indent),"ProcessAssignment: "),l_value)," "),r_value))

    def ProcessCall(self: 'LogToConsole',indent: 'int',call: 'str') -> 'None':
        self.LogLine(Concat(Concat(self.Indentation(indent),"ProcessCall: "),call))

    def FinishProcessingClassFunctionDefinition(self: 'LogToConsole',return_type: 'str',function_name: 'str',parameters: 'list[ParameterDeclaration]') -> 'None':
        self.LogLine(Concat(Concat(Concat(Concat(self.Indentation(2),"FinishProcessingClassFunctionDefinition: "),return_type)," "),function_name))

    def ProcessClassMemberDeclaration(self: 'LogToConsole',member_type: 'str',member_name: 'str') -> 'None':
        self.LogLine(Concat(Concat(Concat(Concat(self.Indentation(2),"ProcessClassMemberDeclaration: "),member_type)," "),member_name))

    def FinishProcessingClass(self: 'LogToConsole',class_name: 'str',implementing: 'str') -> 'None':
        self.LogLine(Concat(Concat(self.Indentation(1),"FinishProcessingClass: "),class_name))

    def FinishProcessingCTCodeFile(self: 'LogToConsole') -> 'None':
        self.LogLine("FinishProcessingCTCodeFile")

    def Transpile(self: 'LogToConsole',system: 'S84_CTCode_System_ctcode.System',c_t_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile',base_name: 'str') -> 'int':
        self.system = system
        self.c_t_code_file = c_t_code_file
        self.base_name = base_name
        self.logger = system.GetLoggerDestination()
        self.ProcessCTCodeFile(c_t_code_file)
        return 0

    def ProcessCTCodeFile(self: 'LogToConsole',c_t_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile') -> 'None':
        self.BeginProcessingCTCodeFile()
        self.ProcessExdefs(c_t_code_file)
        self.ProcessUnmanagedTypes(c_t_code_file)
        self.ProcessDefinitions(c_t_code_file)
        self.FinishProcessingCTCodeFile()

    def ProcessExdefs(self: 'LogToConsole',c_t_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile') -> 'None':
        exdefs: 'list[S84_CTCode_dbnf_ctcode.ExternalDefinition]' = c_t_code_file.GetDeclarations()
        exdefs_index: 'int' = 0
        while exdefs_index<Size(exdefs):
            exdef: 'S84_CTCode_dbnf_ctcode.ExternalDefinition' = Element(exdefs,exdefs_index)
            exdef_name: 'S84_CTCode_dbnf_ctcode.QualfiedName' = exdef.GetExdef()
            self.ProcessExdef(exdef_name.UnParse())
            exdefs_index = exdefs_index+1

    def ProcessUnmanagedTypes(self: 'LogToConsole',c_t_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile') -> 'None':
        unmanaged_types: 'list[S84_CTCode_dbnf_ctcode.UnmanagedType]' = c_t_code_file.GetUnmanagedTypes()
        unmanaged_types_index: 'int' = 0
        while unmanaged_types_index<Size(unmanaged_types):
            unmanaged_type: 'S84_CTCode_dbnf_ctcode.UnmanagedType' = Element(unmanaged_types,unmanaged_types_index)
            self.ProcessUnmanagedType(self.GetQualifiedTypeNameInternal(unmanaged_type.GetUnmanagedType()))
            unmanaged_types_index = unmanaged_types_index+1

    def ProcessDefinitions(self: 'LogToConsole',c_t_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile') -> 'None':
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

    def GetParameters(self: 'LogToConsole',parameter_list_def: 'S84_CTCode_dbnf_ctcode.ParameterListDef') -> 'list[ParameterDeclaration]':
        result: 'list[ParameterDeclaration]' = []
        while parameter_list_def:
            parameter: 'ParameterDeclaration' = ParameterDeclaration()
            parameter.SetType(self.GetType(parameter_list_def.GetType()))
            parameter.SetName(self.GetVariableName(parameter_list_def.GetName()))
            Append(result,parameter)
            parameter_list_def = parameter_list_def.GetParameterTail()
        return result

    def ProcessInterfaceDefinition(self: 'LogToConsole',interface_definition: 'S84_CTCode_dbnf_ctcode.InterfaceDef') -> 'None':
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

    def ProcessClassDefinition(self: 'LogToConsole',class_definition: 'S84_CTCode_dbnf_ctcode.ClassDef') -> 'None':
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

    def ProcessInstructionInternal(self: 'LogToConsole',indent: 'int',instruction: 'S84_CTCode_dbnf_ctcode.Instruction') -> 'None':
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

    def ProcessCodeBlockInternal(self: 'LogToConsole',indent: 'int',code_block: 'S84_CTCode_dbnf_ctcode.CodeBlock') -> 'None':
        self.BeginProcessCodeBlock(indent)
        instructions: 'list[S84_CTCode_dbnf_ctcode.Instruction]' = code_block.GetInstructions()
        instructions_index: 'int' = 0
        while instructions_index<Size(instructions):
            self.ProcessInstructionInternal(indent+1,Element(instructions,instructions_index))
            instructions_index = instructions_index+1
        self.FinishProcessCodeBlock(indent)

    def ProcessConditionalInternal(self: 'LogToConsole',indent: 'int',conditional: 'S84_CTCode_dbnf_ctcode.Conditional') -> 'None':
        r_value: 'str' = self.GetRValueInternal(conditional.GetRValue())
        self.BeginProcessConditional(indent,r_value)
        self.ProcessCodeBlockInternal(indent,conditional.GetCodeBlock())
        if conditional.GetElseTail():
            else_tail: 'S84_CTCode_dbnf_ctcode.ElseTail' = conditional.GetElseTail()
            self.ProcessElse(indent)
            self.ProcessCodeBlockInternal(indent,else_tail.GetCodeBlock())
        self.FinishProcessConditional(indent,r_value)

    def ProcessLoopInternal(self: 'LogToConsole',indent: 'int',loop: 'S84_CTCode_dbnf_ctcode.Loop') -> 'None':
        r_value: 'str' = self.GetRValueInternal(loop.GetRValue())
        self.BeginProcessLoop(indent,r_value)
        self.ProcessCodeBlockInternal(indent,loop.GetCodeBlock())
        self.FinishProcessLoop(indent,r_value)

    def ProcessRtnInternal(self: 'LogToConsole',indent: 'int',rtn: 'S84_CTCode_dbnf_ctcode.Return') -> 'None':
        r_value: 'str' = self.GetRValueInternal(rtn.GetRValue())
        self.ProcessRtn(indent,r_value)

    def ProcessDeclarationInternal(self: 'LogToConsole',indent: 'int',declaration: 'S84_CTCode_dbnf_ctcode.Declaration') -> 'None':
        type: 'str' = self.GetType(declaration.GetType())
        l_value: 'str' = self.GetVariableName(declaration.GetName())
        r_value: 'str' = ""
        declaration_assignment: 'S84_CTCode_dbnf_ctcode.DeclarationAssign' = declaration.GetAssignment()
        if declaration_assignment:
            r_value = self.GetRValueInternal(declaration_assignment.GetRValue())
        self.ProcessDeclaration(indent,type,l_value,r_value)

    def ProcessAssignmentInternal(self: 'LogToConsole',indent: 'int',assignment: 'S84_CTCode_dbnf_ctcode.Assignment') -> 'None':
        self.ProcessAssignment(indent,self.GetVariableChain(assignment.GetLValue()),self.GetRValueInternal(assignment.GetRValue()))

    def ProcessCallInternal(self: 'LogToConsole',indent: 'int',call: 'S84_CTCode_dbnf_ctcode.Call') -> 'None':
        self.ProcessCall(indent,self.ConvertCallInternal(call))

    def ConvertCallInternal(self: 'LogToConsole',call: 'S84_CTCode_dbnf_ctcode.Call') -> 'str':
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

    def GetSingletonType(self: 'LogToConsole',singleton_type: 'S84_CTCode_dbnf_ctcode.SingletonType') -> 'str':
        if singleton_type.GetPrimativeType():
            return self.GetPrimativeType(singleton_type.UnParse())
        if singleton_type.GetDefinedType():
            defined_type: 'S84_CTCode_dbnf_ctcode.DefinedType' = singleton_type.GetDefinedType()
            return self.GetQualifiedTypeNameInternal(defined_type.GetName())
        return ""

    def GetRValueSingleBasisInternal(self: 'LogToConsole',r_value_single: 'S84_CTCode_dbnf_ctcode.RValueSingle') -> 'str':
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

    def GetRValueSingleInternal(self: 'LogToConsole',r_value_single: 'S84_CTCode_dbnf_ctcode.RValueSingle') -> 'str':
        unary_operator: 'S84_CTCode_dbnf_ctcode.UnaryOperator' = r_value_single.GetUnaryOperator()
        if unary_operator:
            return self.UnaryOperator(unary_operator.UnParse(),self.GetRValueSingleBasisInternal(r_value_single))
        return self.GetRValueSingleBasisInternal(r_value_single)

    def GetRValueBinaryInternal(self: 'LogToConsole',r_value_l: 'str',r_value_tail: 'S84_CTCode_dbnf_ctcode.RValueTail') -> 'str':
        r_value_r: 'str' = self.GetRValueSingleInternal(r_value_tail.GetValue())
        binary_operator: 'S84_CTCode_dbnf_ctcode.BinaryOperator' = r_value_tail.GetBinaryOperator()
        r_value_l = self.BinaryOperator(binary_operator.UnParse(),r_value_l,r_value_r)
        if r_value_tail.GetTail():
            return self.GetRValueBinaryInternal(r_value_l,r_value_tail.GetTail())
        return r_value_l

    def GetRValueInternal(self: 'LogToConsole',r_value: 'S84_CTCode_dbnf_ctcode.RValue') -> 'str':
        r_value_l: 'str' = self.GetRValueSingleInternal(r_value.GetValue())
        if r_value.GetTail():
            return self.GetRValueBinaryInternal(r_value_l,r_value.GetTail())
        return r_value_l

    def GetQualifiedTypeNameInternal(self: 'LogToConsole',qualified_name: 'S84_CTCode_dbnf_ctcode.QualfiedName') -> 'str':
        name_parts: 'list[S84_CTCode_dbnf_ctcode.Name]' = []
        Append(name_parts,qualified_name.GetName())
        tail: 'S84_CTCode_dbnf_ctcode.NameTail' = qualified_name.GetTail()
        while tail:
            Append(name_parts,tail.GetName())
            tail = tail.GetTail()
        return self.GetQualifiedTypeName(name_parts)

    def GetType(self: 'LogToConsole',type: 'S84_CTCode_dbnf_ctcode.ValueType') -> 'str':
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

    def Indentation(self: 'LogToConsole',indent: 'int') -> 'str':
        result: 'str' = ""
        result = ""
        while indent>0:
            indent = indent-1
            result = Concat(result,"    ")
        return result

    def SnakeCaseToCamelCase(self: 'LogToConsole',snake_case: 'str') -> 'str':
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

    def CamelCaseToSnakeCase(self: 'LogToConsole',camel_case: 'str') -> 'str':
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

    def IsUpper(self: 'LogToConsole',character: 'str') -> 'bool':
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

    def IsDigit(self: 'LogToConsole',character: 'str') -> 'bool':
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

    def ToLower(self: 'LogToConsole',input: 'str') -> 'str':
        index: 'int' = 0
        result: 'str' = ""
        while index<Length(input):
            character: 'str' = At(input,index)
            lower_character: 'str' = self.CharacterToLower(character)
            result = Concat(result,lower_character)
            index = index+1
        return result

    def CharacterToLower(self: 'LogToConsole',input: 'str') -> 'str':
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

    def ToUpper(self: 'LogToConsole',input: 'str') -> 'str':
        index: 'int' = 0
        result: 'str' = ""
        while index<Length(input):
            character: 'str' = At(input,index)
            upper_character: 'str' = self.CharacterToUpper(character)
            result = Concat(result,upper_character)
            index = index+1
        return result

    def CharacterToUpper(self: 'LogToConsole',input: 'str') -> 'str':
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

