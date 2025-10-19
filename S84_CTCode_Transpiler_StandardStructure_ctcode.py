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

class TargetSpecificFunctions:
    def Initialize(self: 'TargetSpecificFunctions') -> 'None': pass
    def SetSystem(self: 'TargetSpecificFunctions',system: 'S84_CTCode_System_ctcode.System') -> 'None': pass
    def SetCTCodeFile(self: 'TargetSpecificFunctions',c_t_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile') -> 'None': pass
    def SetBaseName(self: 'TargetSpecificFunctions',base_name: 'str') -> 'None': pass
    def SetLogger(self: 'TargetSpecificFunctions',logger: 'S84_CTCode_System_ctcode.OutputStream') -> 'None': pass
    def GetBaseIndentation(self: 'TargetSpecificFunctions') -> 'int': pass
    def GetCallName(self: 'TargetSpecificFunctions',name: 'str') -> 'str': pass
    def GetVariableName(self: 'TargetSpecificFunctions',name: 'str') -> 'str': pass
    def GetVariableChain(self: 'TargetSpecificFunctions',name_parts: 'list[str]') -> 'str': pass
    def ConvertCall(self: 'TargetSpecificFunctions',name_chain: 'list[str]',parameters: 'list[str]') -> 'str': pass
    def ConvertAllocate(self: 'TargetSpecificFunctions',type: 'str') -> 'str': pass
    def ConvertByte(self: 'TargetSpecificFunctions',high: 'str',low: 'str') -> 'str': pass
    def ConvertDecimal(self: 'TargetSpecificFunctions',reserved_prefix_decimal: 'str') -> 'str': pass
    def ConvertNumber(self: 'TargetSpecificFunctions',number: 'str') -> 'str': pass
    def ConvertBoolean(self: 'TargetSpecificFunctions',reserved_prefix_boolean: 'str') -> 'str': pass
    def ConvertVariable(self: 'TargetSpecificFunctions',variable: 'str') -> 'str': pass
    def ConvertString(self: 'TargetSpecificFunctions',literal: 'str') -> 'str': pass
    def UnaryOperator(self: 'TargetSpecificFunctions',op: 'str',r_value: 'str') -> 'str': pass
    def BinaryOperator(self: 'TargetSpecificFunctions',op: 'str',r_value_l: 'str',r_value_r: 'str') -> 'str': pass
    def GetTypeName(self: 'TargetSpecificFunctions',name: 'str') -> 'str': pass
    def GetDimensionalType(self: 'TargetSpecificFunctions',singleton_type: 'str',dimensions: 'int') -> 'str': pass
    def GetMapType(self: 'TargetSpecificFunctions',singleton_type: 'str') -> 'str': pass
    def GetPrimativeType(self: 'TargetSpecificFunctions',c_t_type: 'str') -> 'str': pass
    def GetDefinedType(self: 'TargetSpecificFunctions',c_t_type: 'str') -> 'str': pass
    def GetQualifiedTypeName(self: 'TargetSpecificFunctions',name_parts: 'list[str]') -> 'str': pass
    def BeginProcessingCTCodeFile(self: 'TargetSpecificFunctions') -> 'None': pass
    def FinishProcessingCTCodeFile(self: 'TargetSpecificFunctions') -> 'None': pass
    def ProcessExdef(self: 'TargetSpecificFunctions',exdef: 'str') -> 'None': pass
    def ProcessUnmanagedType(self: 'TargetSpecificFunctions',unmanaged_type: 'str') -> 'None': pass
    def BeginProcessingInterface(self: 'TargetSpecificFunctions',interface_name: 'str') -> 'None': pass
    def ProcessInterfaceFunctionDeclaration(self: 'TargetSpecificFunctions',return_type: 'str',function_name: 'str',parameters: 'list[ParameterDeclaration]') -> 'None': pass
    def FinishProcessingInterface(self: 'TargetSpecificFunctions',interface_name: 'str') -> 'None': pass
    def BeginProcessingClass(self: 'TargetSpecificFunctions',class_name: 'str',implementing: 'str') -> 'None': pass
    def BeginProcessingClassFunctionDefinition(self: 'TargetSpecificFunctions',return_type: 'str',function_name: 'str',parameters: 'list[ParameterDeclaration]') -> 'None': pass
    def BeginProcessCodeBlock(self: 'TargetSpecificFunctions',indent: 'int') -> 'None': pass
    def FinishProcessCodeBlock(self: 'TargetSpecificFunctions',indent: 'int') -> 'None': pass
    def BeginProcessConditional(self: 'TargetSpecificFunctions',indent: 'int',r_value: 'str') -> 'None': pass
    def ProcessElse(self: 'TargetSpecificFunctions',indent: 'int') -> 'None': pass
    def FinishProcessConditional(self: 'TargetSpecificFunctions',indent: 'int',r_value: 'str') -> 'None': pass
    def BeginProcessLoop(self: 'TargetSpecificFunctions',indent: 'int',r_value: 'str') -> 'None': pass
    def FinishProcessLoop(self: 'TargetSpecificFunctions',indent: 'int',r_value: 'str') -> 'None': pass
    def ProcessRtn(self: 'TargetSpecificFunctions',indent: 'int',r_value: 'str') -> 'None': pass
    def ProcessDeclaration(self: 'TargetSpecificFunctions',indent: 'int',type: 'str',l_value: 'str',r_value: 'str') -> 'None': pass
    def ProcessAssignment(self: 'TargetSpecificFunctions',indent: 'int',l_value: 'str',r_value: 'str') -> 'None': pass
    def ProcessCall(self: 'TargetSpecificFunctions',indent: 'int',call: 'str') -> 'None': pass
    def FinishProcessingClassFunctionDefinition(self: 'TargetSpecificFunctions',return_type: 'str',function_name: 'str',parameters: 'list[ParameterDeclaration]') -> 'None': pass
    def ProcessClassMemberDeclaration(self: 'TargetSpecificFunctions',member_type: 'str',member_name: 'str') -> 'None': pass
    def FinishProcessingClass(self: 'TargetSpecificFunctions',class_name: 'str',implementing: 'str') -> 'None': pass

class ParameterDeclaration:
    def __init__(self: 'ParameterDeclaration'):
        self.type: str = ""
        self.name: str = ""

    def ReservedPrefixGetType(self: 'ParameterDeclaration') -> 'str':
        return self.type

    def SetType(self: 'ParameterDeclaration',input: 'str') -> 'None':
        self.type = input

    def GetName(self: 'ParameterDeclaration') -> 'str':
        return self.name

    def SetName(self: 'ParameterDeclaration',input: 'str') -> 'None':
        self.name = input

class IntegerReference:
    def __init__(self: 'IntegerReference'):
        self.value: int = 0

    def GetValue(self: 'IntegerReference') -> 'int':
        return self.value

    def SetValue(self: 'IntegerReference',value: 'int') -> 'None':
        self.value = value

class StandardStructure(S84_CTCode_Transpiler_ctcode.Transpiler):
    def __init__(self: 'StandardStructure'):
        self.system: S84_CTCode_System_ctcode.System = None
        self.c_t_code_file: S84_CTCode_dbnf_ctcode.CTCodeFile = None
        self.base_name: str = ""
        self.operator_precedent: list[list[str]] = []
        self.logger: S84_CTCode_System_ctcode.OutputStream = None
        self.target_specific_functions: TargetSpecificFunctions = None

    def SetTargetSpecificFunctions(self: 'StandardStructure',target_specific_functions: 'TargetSpecificFunctions') -> 'None':
        self.target_specific_functions = target_specific_functions

    def Transpile(self: 'StandardStructure',system: 'S84_CTCode_System_ctcode.System',c_t_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile',base_name: 'str') -> 'int':
        ClearList(self.operator_precedent)
        self.PopulateOperatorPrecedent()
        self.system = system
        self.c_t_code_file = c_t_code_file
        self.base_name = base_name
        self.logger = system.GetLoggerDestination()
        self.target_specific_functions.SetSystem(self.system)
        self.target_specific_functions.SetCTCodeFile(self.c_t_code_file)
        self.target_specific_functions.SetBaseName(self.base_name)
        self.target_specific_functions.SetLogger(self.logger)
        self.ProcessCTCodeFile(c_t_code_file)
        return 0

    def ProcessCTCodeFile(self: 'StandardStructure',c_t_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile') -> 'None':
        self.target_specific_functions.BeginProcessingCTCodeFile()
        self.ProcessExdefs(c_t_code_file)
        self.ProcessUnmanagedTypes(c_t_code_file)
        self.ProcessDefinitions(c_t_code_file)
        self.target_specific_functions.FinishProcessingCTCodeFile()

    def ProcessExdefs(self: 'StandardStructure',c_t_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile') -> 'None':
        exdefs: 'list[S84_CTCode_dbnf_ctcode.ExternalDefinition]' = c_t_code_file.GetDeclarations()
        exdefs_index: 'int' = 0
        while exdefs_index<Size(exdefs):
            exdef: 'S84_CTCode_dbnf_ctcode.ExternalDefinition' = Element(exdefs,exdefs_index)
            exdef_name: 'S84_CTCode_dbnf_ctcode.QualfiedName' = exdef.GetExdef()
            self.target_specific_functions.ProcessExdef(exdef_name.UnParse())
            exdefs_index = exdefs_index+1

    def ProcessUnmanagedTypes(self: 'StandardStructure',c_t_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile') -> 'None':
        unmanaged_types: 'list[S84_CTCode_dbnf_ctcode.UnmanagedType]' = c_t_code_file.GetUnmanagedTypes()
        unmanaged_types_index: 'int' = 0
        while unmanaged_types_index<Size(unmanaged_types):
            unmanaged_type: 'S84_CTCode_dbnf_ctcode.UnmanagedType' = Element(unmanaged_types,unmanaged_types_index)
            self.target_specific_functions.ProcessUnmanagedType(self.GetQualifiedTypeNameInternal(unmanaged_type.GetUnmanagedType()))
            unmanaged_types_index = unmanaged_types_index+1

    def ProcessDefinitions(self: 'StandardStructure',c_t_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile') -> 'None':
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

    def GetParameters(self: 'StandardStructure',parameter_list_def: 'S84_CTCode_dbnf_ctcode.ParameterListDef') -> 'list[ParameterDeclaration]':
        result: 'list[ParameterDeclaration]' = []
        while parameter_list_def:
            parameter: 'ParameterDeclaration' = ParameterDeclaration()
            parameter.SetType(self.ReservedPrefixGetType(parameter_list_def.ReservedPrefixGetType()))
            parameter.SetName(self.target_specific_functions.GetVariableName(self.NameToString(parameter_list_def.GetName())))
            Append(result,parameter)
            parameter_list_def = parameter_list_def.GetParameterTail()
        return result

    def ProcessInterfaceDefinition(self: 'StandardStructure',interface_definition: 'S84_CTCode_dbnf_ctcode.InterfaceDef') -> 'None':
        interface_name: 'str' = self.target_specific_functions.GetTypeName(self.NameToString(interface_definition.GetName()))
        self.target_specific_functions.BeginProcessingInterface(interface_name)
        declarations: 'list[S84_CTCode_dbnf_ctcode.ContentDeclaration]' = interface_definition.GetDeclarations()
        declarations_index: 'int' = 0
        while declarations_index<Size(declarations):
            declaration: 'S84_CTCode_dbnf_ctcode.ContentDeclaration' = Element(declarations,declarations_index)
            return_type: 'str' = self.ReservedPrefixGetType(declaration.ReservedPrefixGetType())
            function_name: 'str' = self.target_specific_functions.GetCallName(self.NameToString(declaration.GetName()))
            parameters: 'list[ParameterDeclaration]' = self.GetParameters(declaration.GetParameters())
            self.target_specific_functions.ProcessInterfaceFunctionDeclaration(return_type,function_name,parameters)
            declarations_index = declarations_index+1
        self.target_specific_functions.FinishProcessingInterface(interface_name)

    def ProcessClassDefinition(self: 'StandardStructure',class_definition: 'S84_CTCode_dbnf_ctcode.ClassDef') -> 'None':
        class_name: 'str' = self.target_specific_functions.GetTypeName(self.NameToString(class_definition.GetName()))
        implementing: 'str' = ""
        implementation_spec: 'S84_CTCode_dbnf_ctcode.ImplementationSpec' = class_definition.GetImplementing()
        if implementation_spec:
            implementing = self.GetQualifiedTypeNameInternal(implementation_spec.GetInterface())
        self.target_specific_functions.BeginProcessingClass(class_name,implementing)
        definitions: 'list[S84_CTCode_dbnf_ctcode.ContentDefinition]' = class_definition.GetDefinitions()
        definitions_index: 'int' = 0
        while definitions_index<Size(definitions):
            definition: 'S84_CTCode_dbnf_ctcode.ContentDefinition' = Element(definitions,definitions_index)
            if definition.GetFunctionBody():
                return_type: 'str' = self.ReservedPrefixGetType(definition.ReservedPrefixGetType())
                function_name: 'str' = self.target_specific_functions.GetCallName(self.NameToString(definition.GetName()))
                parameters: 'list[ParameterDeclaration]' = self.GetParameters(definition.GetParameters())
                self.target_specific_functions.BeginProcessingClassFunctionDefinition(return_type,function_name,parameters)
                self.ProcessCodeBlockInternal(self.target_specific_functions.GetBaseIndentation(),definition.GetFunctionBody())
                self.target_specific_functions.FinishProcessingClassFunctionDefinition(return_type,function_name,parameters)
            else:
                member_type: 'str' = self.ReservedPrefixGetType(definition.ReservedPrefixGetType())
                member_name: 'str' = self.target_specific_functions.GetVariableName(self.NameToString(definition.GetName()))
                self.target_specific_functions.ProcessClassMemberDeclaration(member_type,member_name)
            definitions_index = definitions_index+1
        self.target_specific_functions.FinishProcessingClass(class_name,implementing)

    def ProcessInstructionInternal(self: 'StandardStructure',indent: 'int',instruction: 'S84_CTCode_dbnf_ctcode.Instruction') -> 'None':
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

    def ProcessCodeBlockInternal(self: 'StandardStructure',indent: 'int',code_block: 'S84_CTCode_dbnf_ctcode.CodeBlock') -> 'None':
        self.target_specific_functions.BeginProcessCodeBlock(indent)
        instructions: 'list[S84_CTCode_dbnf_ctcode.Instruction]' = code_block.GetInstructions()
        instructions_index: 'int' = 0
        while instructions_index<Size(instructions):
            self.ProcessInstructionInternal(indent+1,Element(instructions,instructions_index))
            instructions_index = instructions_index+1
        self.target_specific_functions.FinishProcessCodeBlock(indent)

    def ProcessConditionalInternal(self: 'StandardStructure',indent: 'int',conditional: 'S84_CTCode_dbnf_ctcode.Conditional') -> 'None':
        r_value: 'str' = self.GetRValueInternal(conditional.GetRValue())
        self.target_specific_functions.BeginProcessConditional(indent,r_value)
        self.ProcessCodeBlockInternal(indent,conditional.GetCodeBlock())
        if conditional.GetElseTail():
            else_tail: 'S84_CTCode_dbnf_ctcode.ElseTail' = conditional.GetElseTail()
            self.target_specific_functions.ProcessElse(indent)
            self.ProcessCodeBlockInternal(indent,else_tail.GetCodeBlock())
        self.target_specific_functions.FinishProcessConditional(indent,r_value)

    def ProcessLoopInternal(self: 'StandardStructure',indent: 'int',loop: 'S84_CTCode_dbnf_ctcode.Loop') -> 'None':
        r_value: 'str' = self.GetRValueInternal(loop.GetRValue())
        self.target_specific_functions.BeginProcessLoop(indent,r_value)
        self.ProcessCodeBlockInternal(indent,loop.GetCodeBlock())
        self.target_specific_functions.FinishProcessLoop(indent,r_value)

    def ProcessRtnInternal(self: 'StandardStructure',indent: 'int',rtn: 'S84_CTCode_dbnf_ctcode.ReservedPrefixReturn') -> 'None':
        r_value: 'str' = self.GetRValueInternal(rtn.GetRValue())
        self.target_specific_functions.ProcessRtn(indent,r_value)

    def ProcessDeclarationInternal(self: 'StandardStructure',indent: 'int',declaration: 'S84_CTCode_dbnf_ctcode.Declaration') -> 'None':
        type: 'str' = self.ReservedPrefixGetType(declaration.ReservedPrefixGetType())
        l_value: 'str' = self.target_specific_functions.GetVariableName(self.NameToString(declaration.GetName()))
        r_value: 'str' = ""
        declaration_assignment: 'S84_CTCode_dbnf_ctcode.DeclarationAssign' = declaration.GetAssignment()
        if declaration_assignment:
            r_value = self.GetRValueInternal(declaration_assignment.GetRValue())
        self.target_specific_functions.ProcessDeclaration(indent,type,l_value,r_value)

    def ProcessAssignmentInternal(self: 'StandardStructure',indent: 'int',assignment: 'S84_CTCode_dbnf_ctcode.Assignment') -> 'None':
        self.target_specific_functions.ProcessAssignment(indent,self.GetVariableChainInternal(assignment.GetLValue()),self.GetRValueInternal(assignment.GetRValue()))

    def ProcessCallInternal(self: 'StandardStructure',indent: 'int',call: 'S84_CTCode_dbnf_ctcode.Call') -> 'None':
        self.target_specific_functions.ProcessCall(indent,self.ConvertCallInternal(call))

    def ConvertCallInternal(self: 'StandardStructure',call: 'S84_CTCode_dbnf_ctcode.Call') -> 'str':
        name_chain: 'list[str]' = []
        parameters: 'list[str]' = []
        if call.GetVariable():
            Append(name_chain,self.target_specific_functions.GetVariableName(self.NameToString(call.GetVariable())))
        if call.GetFunction():
            Append(name_chain,self.target_specific_functions.GetCallName(self.NameToString(call.GetFunction())))
        if call.GetFunctionChain():
            function_chain: 'S84_CTCode_dbnf_ctcode.QualfiedName' = call.GetFunctionChain()
            name_tail: 'S84_CTCode_dbnf_ctcode.NameTail' = function_chain.GetTail()
            if function_chain.GetTail():
                Append(name_chain,self.target_specific_functions.GetVariableName(self.NameToString(function_chain.GetName())))
            else:
                Append(name_chain,self.target_specific_functions.GetCallName(self.NameToString(function_chain.GetName())))
            while name_tail:
                if name_tail.GetTail():
                    Append(name_chain,self.target_specific_functions.GetVariableName(self.NameToString(name_tail.GetName())))
                else:
                    Append(name_chain,self.target_specific_functions.GetCallName(self.NameToString(name_tail.GetName())))
                name_tail = name_tail.GetTail()
        parameter_list: 'S84_CTCode_dbnf_ctcode.ParameterList' = call.GetParameters()
        while parameter_list:
            Append(parameters,self.GetRValueInternal(parameter_list.GetRValue()))
            parameter_list = parameter_list.GetParameterTail()
        return self.target_specific_functions.ConvertCall(name_chain,parameters)

    def GetSingletonType(self: 'StandardStructure',singleton_type: 'S84_CTCode_dbnf_ctcode.SingletonType') -> 'str':
        if singleton_type.GetPrimativeType():
            return self.target_specific_functions.GetPrimativeType(singleton_type.UnParse())
        if singleton_type.GetDefinedType():
            defined_type: 'S84_CTCode_dbnf_ctcode.DefinedType' = singleton_type.GetDefinedType()
            return self.target_specific_functions.GetDefinedType(self.GetQualifiedTypeNameInternal(defined_type.GetName()))
        return ""

    def GetRValueSingleBasisInternal(self: 'StandardStructure',r_value_single: 'S84_CTCode_dbnf_ctcode.RValueSingle') -> 'str':
        call: 'S84_CTCode_dbnf_ctcode.Call' = r_value_single.GetCall()
        if call:
            return self.ConvertCallInternal(call)
        allocate: 'S84_CTCode_dbnf_ctcode.Allocate' = r_value_single.GetAllocate()
        if allocate:
            return self.target_specific_functions.ConvertAllocate(self.GetQualifiedTypeNameInternal(allocate.GetManagedType()))
        byte_literal: 'S84_CTCode_dbnf_ctcode.Byte' = r_value_single.GetByteLiteral()
        if byte_literal:
            high: 'S84_CTCode_dbnf_ctcode.ByteDigit' = byte_literal.GetHigh()
            low: 'S84_CTCode_dbnf_ctcode.ByteDigit' = byte_literal.GetLow()
            return self.target_specific_functions.ConvertByte(high.UnParse(),low.UnParse())
        decimal_literal: 'S84_CTCode_dbnf_ctcode.Decimal' = r_value_single.GetDecimalLiteral()
        if decimal_literal:
            return self.target_specific_functions.ConvertDecimal(decimal_literal.UnParse())
        integer_literal: 'S84_CTCode_dbnf_ctcode.Number' = r_value_single.GetIntegerLiteral()
        if integer_literal:
            return self.target_specific_functions.ConvertNumber(integer_literal.UnParse())
        boolean_literal: 'S84_CTCode_dbnf_ctcode.Boolean' = r_value_single.GetBooleanLiteral()
        if boolean_literal:
            return self.target_specific_functions.ConvertBoolean(boolean_literal.UnParse())
        variable: 'S84_CTCode_dbnf_ctcode.QualfiedName' = r_value_single.GetVariable()
        if variable:
            return self.target_specific_functions.ConvertVariable(self.GetVariableChainInternal(variable))
        string_literal: 'S84_CTCode_dbnf_ctcode.Literal' = r_value_single.GetStringLiteral()
        if string_literal:
            return self.target_specific_functions.ConvertString(string_literal.UnParse())
        return ""

    def GetRValueSingleInternal(self: 'StandardStructure',r_value_single: 'S84_CTCode_dbnf_ctcode.RValueSingle') -> 'str':
        unary_operator: 'S84_CTCode_dbnf_ctcode.UnaryOperator' = r_value_single.GetUnaryOperator()
        if unary_operator:
            return self.target_specific_functions.UnaryOperator(unary_operator.UnParse(),self.GetRValueSingleBasisInternal(r_value_single))
        return self.GetRValueSingleBasisInternal(r_value_single)

    def PopulateOperatorPrecedent(self: 'StandardStructure') -> 'None':
        precedent__0_operators: 'list[str]' = []
        Append(precedent__0_operators,"+")
        Append(precedent__0_operators,"-")
        Append(self.operator_precedent,precedent__0_operators)
        precedent__1_operators: 'list[str]' = []
        Append(precedent__1_operators,"<=")
        Append(precedent__1_operators,">=")
        Append(precedent__1_operators,"==")
        Append(precedent__1_operators,"!=")
        Append(precedent__1_operators,"<")
        Append(precedent__1_operators,">")
        Append(self.operator_precedent,precedent__1_operators)
        precedent__2_operators: 'list[str]' = []
        Append(precedent__2_operators,"&&")
        Append(self.operator_precedent,precedent__2_operators)
        precedent__3_operators: 'list[str]' = []
        Append(precedent__3_operators,"||")
        Append(self.operator_precedent,precedent__3_operators)
        precedent__4_operators: 'list[str]' = []
        Append(precedent__4_operators,"")
        Append(self.operator_precedent,precedent__4_operators)

    def OverPrecedent(self: 'StandardStructure',op: 'str',precedent: 'int') -> 'bool':
        precedent = precedent+1
        while precedent<Size(self.operator_precedent):
            precedent_operators: 'list[str]' = Element(self.operator_precedent,precedent)
            index: 'int' = 0
            while index<Size(precedent_operators):
                checking_op: 'str' = Element(precedent_operators,index)
                if checking_op==op:
                    return True
                index = index+1
            precedent = precedent+1
        return False

    def BinaryOperatorPrecedentMerge(self: 'StandardStructure',values: 'list[str]',operators: 'list[str]',index: 'IntegerReference',precedent: 'int') -> 'str':
        if precedent==-1:
            return Element(values,index.GetValue())
        r_value_l: 'str' = self.BinaryOperatorPrecedentMerge(values,operators,index,precedent-1)
        while index.GetValue()<Size(operators):
            op: 'str' = Element(operators,index.GetValue())
            if self.OverPrecedent(op,precedent):
                return r_value_l
            index.SetValue(index.GetValue()+1)
            r_value_r: 'str' = self.BinaryOperatorPrecedentMerge(values,operators,index,precedent-1)
            r_value_l = self.target_specific_functions.BinaryOperator(op,r_value_l,r_value_r)
        return r_value_l

    def GetRValueInternal(self: 'StandardStructure',r_value: 'S84_CTCode_dbnf_ctcode.RValue') -> 'str':
        values: 'list[str]' = []
        operators: 'list[str]' = []
        index: 'IntegerReference' = IntegerReference()
        index.SetValue(0)
        Append(values,self.GetRValueSingleInternal(r_value.GetValue()))
        r_value_tail: 'S84_CTCode_dbnf_ctcode.RValueTail' = r_value.GetTail()
        while r_value_tail:
            binary_operator: 'S84_CTCode_dbnf_ctcode.BinaryOperator' = r_value_tail.GetBinaryOperator()
            Append(values,self.GetRValueSingleInternal(r_value_tail.GetValue()))
            Append(operators,binary_operator.UnParse())
            r_value_tail = r_value_tail.GetTail()
        return self.BinaryOperatorPrecedentMerge(values,operators,index,Size(self.operator_precedent))

    def GetQualifiedTypeNameInternal(self: 'StandardStructure',qualified_name: 'S84_CTCode_dbnf_ctcode.QualfiedName') -> 'str':
        name_parts: 'list[str]' = []
        Append(name_parts,self.NameToString(qualified_name.GetName()))
        tail: 'S84_CTCode_dbnf_ctcode.NameTail' = qualified_name.GetTail()
        while tail:
            Append(name_parts,self.NameToString(tail.GetName()))
            tail = tail.GetTail()
        return self.target_specific_functions.GetQualifiedTypeName(name_parts)

    def GetVariableChainInternal(self: 'StandardStructure',qualified_name: 'S84_CTCode_dbnf_ctcode.QualfiedName') -> 'str':
        name_parts: 'list[str]' = []
        Append(name_parts,self.NameToString(qualified_name.GetName()))
        tail: 'S84_CTCode_dbnf_ctcode.NameTail' = qualified_name.GetTail()
        while tail:
            Append(name_parts,self.NameToString(tail.GetName()))
            tail = tail.GetTail()
        return self.target_specific_functions.GetVariableChain(name_parts)

    def ReservedPrefixGetType(self: 'StandardStructure',type: 'S84_CTCode_dbnf_ctcode.ValueType') -> 'str':
        if type.GetDimensionalType():
            dimensional_type: 'S84_CTCode_dbnf_ctcode.DimensionalType' = type.GetDimensionalType()
            singleton_type: 'S84_CTCode_dbnf_ctcode.SingletonType' = dimensional_type.GetSingletonType()
            return self.target_specific_functions.GetDimensionalType(self.GetSingletonType(singleton_type),Size(dimensional_type.GetDimensionalNote()))
        if type.GetMapType():
            map_type: 'S84_CTCode_dbnf_ctcode.MapType' = type.GetMapType()
            singleton_type: 'S84_CTCode_dbnf_ctcode.SingletonType' = map_type.GetSingletonType()
            return self.target_specific_functions.GetMapType(self.GetSingletonType(singleton_type))
        if type.GetSingletonType():
            singleton_type: 'S84_CTCode_dbnf_ctcode.SingletonType' = type.GetSingletonType()
            return self.GetSingletonType(singleton_type)
        return ""

    def NameToString(self: 'StandardStructure',name: 'S84_CTCode_dbnf_ctcode.Name') -> 'str':
        if name:
            return name.UnParse()
        else:
            return ""

