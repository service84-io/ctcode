import * as S84_CTCode_dbnf_ctcode from "./S84_CTCode_dbnf_ctcode.js"
import * as S84_CTCode_System_ctcode from "./S84_CTCode_System_ctcode.js"
import * as S84_CTCode_Transpiler_ctcode from "./S84_CTCode_Transpiler_ctcode.js"

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

export class TargetSpecificFunctions {
    Initialize() {}
    SetSystem(system) {}
    SetCTCodeFile(c_t_code_file) {}
    SetBaseName(base_name) {}
    SetLogger(logger) {}
    GetBaseIndentation() {}
    GetCallName(name) {}
    GetVariableName(name) {}
    GetVariableChain(name_parts) {}
    ConvertCall(name_chain, parameters) {}
    ConvertAllocate(type) {}
    ConvertByte(high, low) {}
    ConvertDecimal(reserved_prefix_decimal) {}
    ConvertNumber(number) {}
    ConvertBoolean(reserved_prefix_boolean) {}
    ConvertVariable(variable) {}
    ConvertString(literal) {}
    UnaryOperator(op, r_value) {}
    BinaryOperator(op, r_value_l, r_value_r) {}
    GetTypeName(name) {}
    GetDimensionalType(singleton_type, dimensions) {}
    GetMapType(singleton_type) {}
    GetPrimativeType(c_t_type) {}
    GetDefinedType(c_t_type) {}
    GetQualifiedTypeName(name_parts) {}
    BeginProcessingCTCodeFile() {}
    FinishProcessingCTCodeFile() {}
    ProcessExdef(exdef) {}
    ProcessUnmanagedType(unmanaged_type) {}
    BeginProcessingInterface(interface_name) {}
    ProcessInterfaceFunctionDeclaration(return_type, function_name, parameters) {}
    FinishProcessingInterface(interface_name) {}
    BeginProcessingClass(class_name, implementing) {}
    BeginProcessingClassFunctionDefinition(return_type, function_name, parameters) {}
    BeginProcessCodeBlock(indent) {}
    FinishProcessCodeBlock(indent) {}
    BeginProcessConditional(indent, r_value) {}
    ProcessElse(indent) {}
    FinishProcessConditional(indent, r_value) {}
    BeginProcessLoop(indent, r_value) {}
    FinishProcessLoop(indent, r_value) {}
    ProcessRtn(indent, r_value) {}
    ProcessDeclaration(indent, type, l_value, r_value) {}
    ProcessAssignment(indent, l_value, r_value) {}
    ProcessCall(indent, call) {}
    FinishProcessingClassFunctionDefinition(return_type, function_name, parameters) {}
    ProcessClassMemberDeclaration(member_type, member_name) {}
    FinishProcessingClass(class_name, implementing) {}
}

export class ParameterDeclaration {
    constructor() {
        this.type = ""
        this.name = ""
    }

    ReservedPrefixGetType()
    {
        return this.type
    }

    SetType(input)
    {
        this.type = input
    }

    GetName()
    {
        return this.name
    }

    SetName(input)
    {
        this.name = input
    }
}

export class IntegerReference {
    constructor() {
        this.value = 0
    }

    GetValue()
    {
        return this.value
    }

    SetValue(value)
    {
        this.value = value
    }
}

export class StandardStructure {
    constructor() {
        this.system = null
        this.c_t_code_file = null
        this.base_name = ""
        this.operator_precedent = []
        this.logger = null
        this.target_specific_functions = null
    }

    SetTargetSpecificFunctions(target_specific_functions)
    {
        this.target_specific_functions = target_specific_functions
    }

    Transpile(system, c_t_code_file, base_name)
    {
        ClearList(this.operator_precedent)
        this.PopulateOperatorPrecedent()
        this.system = system
        this.c_t_code_file = c_t_code_file
        this.base_name = base_name
        this.logger = system.GetLoggerDestination()
        this.target_specific_functions.SetSystem(this.system)
        this.target_specific_functions.SetCTCodeFile(this.c_t_code_file)
        this.target_specific_functions.SetBaseName(this.base_name)
        this.target_specific_functions.SetLogger(this.logger)
        this.ProcessCTCodeFile(c_t_code_file)
        return 0
    }

    ProcessCTCodeFile(c_t_code_file)
    {
        this.target_specific_functions.BeginProcessingCTCodeFile()
        this.ProcessExdefs(c_t_code_file)
        this.ProcessUnmanagedTypes(c_t_code_file)
        this.ProcessDefinitions(c_t_code_file)
        this.target_specific_functions.FinishProcessingCTCodeFile()
    }

    ProcessExdefs(c_t_code_file)
    {
        var exdefs = c_t_code_file.GetDeclarations()
        var exdefs_index = 0
        while (exdefs_index<Size(exdefs))
        {
            var exdef = Element(exdefs,exdefs_index)
            var exdef_name = exdef.GetExdef()
            this.target_specific_functions.ProcessExdef(exdef_name.UnParse())
            exdefs_index = exdefs_index+1
        }
    }

    ProcessUnmanagedTypes(c_t_code_file)
    {
        var unmanaged_types = c_t_code_file.GetUnmanagedTypes()
        var unmanaged_types_index = 0
        while (unmanaged_types_index<Size(unmanaged_types))
        {
            var unmanaged_type = Element(unmanaged_types,unmanaged_types_index)
            this.target_specific_functions.ProcessUnmanagedType(this.GetQualifiedTypeNameInternal(unmanaged_type.GetUnmanagedType()))
            unmanaged_types_index = unmanaged_types_index+1
        }
    }

    ProcessDefinitions(c_t_code_file)
    {
        var definitions = c_t_code_file.GetDefinitions()
        var definitions_index = 0
        while (definitions_index<Size(definitions))
        {
            var definition = null
            definition = Element(definitions,definitions_index)
            if (definition.GetInterfaceDef())
            {
                this.ProcessInterfaceDefinition(definition.GetInterfaceDef())
            }
            if (definition.GetClassDef())
            {
                this.ProcessClassDefinition(definition.GetClassDef())
            }
            definitions_index = definitions_index+1
        }
    }

    GetParameters(parameter_list_def)
    {
        var result = []
        while (parameter_list_def)
        {
            var parameter = new ParameterDeclaration()
            parameter.SetType(this.ReservedPrefixGetType(parameter_list_def.ReservedPrefixGetType()))
            parameter.SetName(this.target_specific_functions.GetVariableName(this.NameToString(parameter_list_def.GetName())))
            Append(result,parameter)
            parameter_list_def = parameter_list_def.GetParameterTail()
        }
        return result
    }

    ProcessInterfaceDefinition(interface_definition)
    {
        var interface_name = this.target_specific_functions.GetTypeName(this.NameToString(interface_definition.GetName()))
        this.target_specific_functions.BeginProcessingInterface(interface_name)
        var declarations = interface_definition.GetDeclarations()
        var declarations_index = 0
        while (declarations_index<Size(declarations))
        {
            var declaration = Element(declarations,declarations_index)
            var return_type = this.ReservedPrefixGetType(declaration.ReservedPrefixGetType())
            var function_name = this.target_specific_functions.GetCallName(this.NameToString(declaration.GetName()))
            var parameters = this.GetParameters(declaration.GetParameters())
            this.target_specific_functions.ProcessInterfaceFunctionDeclaration(return_type,function_name,parameters)
            declarations_index = declarations_index+1
        }
        this.target_specific_functions.FinishProcessingInterface(interface_name)
    }

    ProcessClassDefinition(class_definition)
    {
        var class_name = this.target_specific_functions.GetTypeName(this.NameToString(class_definition.GetName()))
        var implementing = ""
        var implementation_spec = class_definition.GetImplementing()
        if (implementation_spec)
        {
            implementing = this.GetQualifiedTypeNameInternal(implementation_spec.GetInterface())
        }
        this.target_specific_functions.BeginProcessingClass(class_name,implementing)
        var definitions = class_definition.GetDefinitions()
        var definitions_index = 0
        while (definitions_index<Size(definitions))
        {
            var definition = Element(definitions,definitions_index)
            if (definition.GetFunctionBody())
            {
                var return_type = this.ReservedPrefixGetType(definition.ReservedPrefixGetType())
                var function_name = this.target_specific_functions.GetCallName(this.NameToString(definition.GetName()))
                var parameters = this.GetParameters(definition.GetParameters())
                this.target_specific_functions.BeginProcessingClassFunctionDefinition(return_type,function_name,parameters)
                this.ProcessCodeBlockInternal(this.target_specific_functions.GetBaseIndentation(),definition.GetFunctionBody())
                this.target_specific_functions.FinishProcessingClassFunctionDefinition(return_type,function_name,parameters)
            }
            else
            {
                var member_type = this.ReservedPrefixGetType(definition.ReservedPrefixGetType())
                var member_name = this.target_specific_functions.GetVariableName(this.NameToString(definition.GetName()))
                this.target_specific_functions.ProcessClassMemberDeclaration(member_type,member_name)
            }
            definitions_index = definitions_index+1
        }
        this.target_specific_functions.FinishProcessingClass(class_name,implementing)
    }

    ProcessInstructionInternal(indent, instruction)
    {
        if (instruction.GetCodeBlock())
        {
            this.ProcessCodeBlockInternal(indent,instruction.GetCodeBlock())
        }
        if (instruction.GetRtn())
        {
            this.ProcessRtnInternal(indent,instruction.GetRtn())
        }
        if (instruction.GetDeclaration())
        {
            this.ProcessDeclarationInternal(indent,instruction.GetDeclaration())
        }
        if (instruction.GetAssignment())
        {
            this.ProcessAssignmentInternal(indent,instruction.GetAssignment())
        }
        if (instruction.GetCall())
        {
            this.ProcessCallInternal(indent,instruction.GetCall())
        }
        if (instruction.GetConditional())
        {
            this.ProcessConditionalInternal(indent,instruction.GetConditional())
        }
        if (instruction.GetLoop())
        {
            this.ProcessLoopInternal(indent,instruction.GetLoop())
        }
    }

    ProcessCodeBlockInternal(indent, code_block)
    {
        this.target_specific_functions.BeginProcessCodeBlock(indent)
        var instructions = code_block.GetInstructions()
        var instructions_index = 0
        while (instructions_index<Size(instructions))
        {
            this.ProcessInstructionInternal(indent+1,Element(instructions,instructions_index))
            instructions_index = instructions_index+1
        }
        this.target_specific_functions.FinishProcessCodeBlock(indent)
    }

    ProcessConditionalInternal(indent, conditional)
    {
        var r_value = this.GetRValueInternal(conditional.GetRValue())
        this.target_specific_functions.BeginProcessConditional(indent,r_value)
        this.ProcessCodeBlockInternal(indent,conditional.GetCodeBlock())
        if (conditional.GetElseTail())
        {
            var else_tail = conditional.GetElseTail()
            this.target_specific_functions.ProcessElse(indent)
            this.ProcessCodeBlockInternal(indent,else_tail.GetCodeBlock())
        }
        this.target_specific_functions.FinishProcessConditional(indent,r_value)
    }

    ProcessLoopInternal(indent, loop)
    {
        var r_value = this.GetRValueInternal(loop.GetRValue())
        this.target_specific_functions.BeginProcessLoop(indent,r_value)
        this.ProcessCodeBlockInternal(indent,loop.GetCodeBlock())
        this.target_specific_functions.FinishProcessLoop(indent,r_value)
    }

    ProcessRtnInternal(indent, rtn)
    {
        var r_value = this.GetRValueInternal(rtn.GetRValue())
        this.target_specific_functions.ProcessRtn(indent,r_value)
    }

    ProcessDeclarationInternal(indent, declaration)
    {
        var type = this.ReservedPrefixGetType(declaration.ReservedPrefixGetType())
        var l_value = this.target_specific_functions.GetVariableName(this.NameToString(declaration.GetName()))
        var r_value = ""
        var declaration_assignment = declaration.GetAssignment()
        if (declaration_assignment)
        {
            r_value = this.GetRValueInternal(declaration_assignment.GetRValue())
        }
        this.target_specific_functions.ProcessDeclaration(indent,type,l_value,r_value)
    }

    ProcessAssignmentInternal(indent, assignment)
    {
        this.target_specific_functions.ProcessAssignment(indent,this.GetVariableChainInternal(assignment.GetLValue()),this.GetRValueInternal(assignment.GetRValue()))
    }

    ProcessCallInternal(indent, call)
    {
        this.target_specific_functions.ProcessCall(indent,this.ConvertCallInternal(call))
    }

    ConvertCallInternal(call)
    {
        var name_chain = []
        var parameters = []
        if (call.GetVariable())
        {
            Append(name_chain,this.target_specific_functions.GetVariableName(this.NameToString(call.GetVariable())))
        }
        if (call.GetFunction())
        {
            Append(name_chain,this.target_specific_functions.GetCallName(this.NameToString(call.GetFunction())))
        }
        if (call.GetFunctionChain())
        {
            var function_chain = call.GetFunctionChain()
            var name_tail = function_chain.GetTail()
            if (function_chain.GetTail())
            {
                Append(name_chain,this.target_specific_functions.GetVariableName(this.NameToString(function_chain.GetName())))
            }
            else
            {
                Append(name_chain,this.target_specific_functions.GetCallName(this.NameToString(function_chain.GetName())))
            }
            while (name_tail)
            {
                if (name_tail.GetTail())
                {
                    Append(name_chain,this.target_specific_functions.GetVariableName(this.NameToString(name_tail.GetName())))
                }
                else
                {
                    Append(name_chain,this.target_specific_functions.GetCallName(this.NameToString(name_tail.GetName())))
                }
                name_tail = name_tail.GetTail()
            }
        }
        var parameter_list = call.GetParameters()
        while (parameter_list)
        {
            Append(parameters,this.GetRValueInternal(parameter_list.GetRValue()))
            parameter_list = parameter_list.GetParameterTail()
        }
        return this.target_specific_functions.ConvertCall(name_chain,parameters)
    }

    GetSingletonType(singleton_type)
    {
        if (singleton_type.GetPrimativeType())
        {
            return this.target_specific_functions.GetPrimativeType(singleton_type.UnParse())
        }
        if (singleton_type.GetDefinedType())
        {
            var defined_type = singleton_type.GetDefinedType()
            return this.target_specific_functions.GetDefinedType(this.GetQualifiedTypeNameInternal(defined_type.GetName()))
        }
        return ""
    }

    GetRValueSingleBasisInternal(r_value_single)
    {
        var call = r_value_single.GetCall()
        if (call)
        {
            return this.ConvertCallInternal(call)
        }
        var allocate = r_value_single.GetAllocate()
        if (allocate)
        {
            return this.target_specific_functions.ConvertAllocate(this.GetQualifiedTypeNameInternal(allocate.GetManagedType()))
        }
        var byte_literal = r_value_single.GetByteLiteral()
        if (byte_literal)
        {
            var high = byte_literal.GetHigh()
            var low = byte_literal.GetLow()
            return this.target_specific_functions.ConvertByte(high.UnParse(),low.UnParse())
        }
        var decimal_literal = r_value_single.GetDecimalLiteral()
        if (decimal_literal)
        {
            return this.target_specific_functions.ConvertDecimal(decimal_literal.UnParse())
        }
        var integer_literal = r_value_single.GetIntegerLiteral()
        if (integer_literal)
        {
            return this.target_specific_functions.ConvertNumber(integer_literal.UnParse())
        }
        var boolean_literal = r_value_single.GetBooleanLiteral()
        if (boolean_literal)
        {
            return this.target_specific_functions.ConvertBoolean(boolean_literal.UnParse())
        }
        var variable = r_value_single.GetVariable()
        if (variable)
        {
            return this.target_specific_functions.ConvertVariable(this.GetVariableChainInternal(variable))
        }
        var string_literal = r_value_single.GetStringLiteral()
        if (string_literal)
        {
            return this.target_specific_functions.ConvertString(string_literal.UnParse())
        }
        return ""
    }

    GetRValueSingleInternal(r_value_single)
    {
        var unary_operator = r_value_single.GetUnaryOperator()
        if (unary_operator)
        {
            return this.target_specific_functions.UnaryOperator(unary_operator.UnParse(),this.GetRValueSingleBasisInternal(r_value_single))
        }
        return this.GetRValueSingleBasisInternal(r_value_single)
    }

    PopulateOperatorPrecedent()
    {
        var precedent__0_operators = []
        Append(precedent__0_operators,"+")
        Append(precedent__0_operators,"-")
        Append(this.operator_precedent,precedent__0_operators)
        var precedent__1_operators = []
        Append(precedent__1_operators,"<=")
        Append(precedent__1_operators,">=")
        Append(precedent__1_operators,"==")
        Append(precedent__1_operators,"!=")
        Append(precedent__1_operators,"<")
        Append(precedent__1_operators,">")
        Append(this.operator_precedent,precedent__1_operators)
        var precedent__2_operators = []
        Append(precedent__2_operators,"&&")
        Append(this.operator_precedent,precedent__2_operators)
        var precedent__3_operators = []
        Append(precedent__3_operators,"||")
        Append(this.operator_precedent,precedent__3_operators)
        var precedent__4_operators = []
        Append(precedent__4_operators,"")
        Append(this.operator_precedent,precedent__4_operators)
    }

    OverPrecedent(op, precedent)
    {
        precedent = precedent+1
        while (precedent<Size(this.operator_precedent))
        {
            var precedent_operators = Element(this.operator_precedent,precedent)
            var index = 0
            while (index<Size(precedent_operators))
            {
                var checking_op = Element(precedent_operators,index)
                if (checking_op==op)
                {
                    return true
                }
                index = index+1
            }
            precedent = precedent+1
        }
        return false
    }

    BinaryOperatorPrecedentMerge(values, operators, index, precedent)
    {
        if (precedent==-1)
        {
            return Element(values,index.GetValue())
        }
        var r_value_l = this.BinaryOperatorPrecedentMerge(values,operators,index,precedent-1)
        while (index.GetValue()<Size(operators))
        {
            var op = Element(operators,index.GetValue())
            if (this.OverPrecedent(op,precedent))
            {
                return r_value_l
            }
            index.SetValue(index.GetValue()+1)
            var r_value_r = this.BinaryOperatorPrecedentMerge(values,operators,index,precedent-1)
            r_value_l = this.target_specific_functions.BinaryOperator(op,r_value_l,r_value_r)
        }
        return r_value_l
    }

    GetRValueInternal(r_value)
    {
        var values = []
        var operators = []
        var index = new IntegerReference()
        index.SetValue(0)
        Append(values,this.GetRValueSingleInternal(r_value.GetValue()))
        var r_value_tail = r_value.GetTail()
        while (r_value_tail)
        {
            var binary_operator = r_value_tail.GetBinaryOperator()
            Append(values,this.GetRValueSingleInternal(r_value_tail.GetValue()))
            Append(operators,binary_operator.UnParse())
            r_value_tail = r_value_tail.GetTail()
        }
        return this.BinaryOperatorPrecedentMerge(values,operators,index,Size(this.operator_precedent))
    }

    GetQualifiedTypeNameInternal(qualified_name)
    {
        var name_parts = []
        Append(name_parts,this.NameToString(qualified_name.GetName()))
        var tail = qualified_name.GetTail()
        while (tail)
        {
            Append(name_parts,this.NameToString(tail.GetName()))
            tail = tail.GetTail()
        }
        return this.target_specific_functions.GetQualifiedTypeName(name_parts)
    }

    GetVariableChainInternal(qualified_name)
    {
        var name_parts = []
        Append(name_parts,this.NameToString(qualified_name.GetName()))
        var tail = qualified_name.GetTail()
        while (tail)
        {
            Append(name_parts,this.NameToString(tail.GetName()))
            tail = tail.GetTail()
        }
        return this.target_specific_functions.GetVariableChain(name_parts)
    }

    ReservedPrefixGetType(type)
    {
        if (type.GetDimensionalType())
        {
            var dimensional_type = type.GetDimensionalType()
            var singleton_type = dimensional_type.GetSingletonType()
            return this.target_specific_functions.GetDimensionalType(this.GetSingletonType(singleton_type),Size(dimensional_type.GetDimensionalNote()))
        }
        if (type.GetMapType())
        {
            var map_type = type.GetMapType()
            var singleton_type = map_type.GetSingletonType()
            return this.target_specific_functions.GetMapType(this.GetSingletonType(singleton_type))
        }
        if (type.GetSingletonType())
        {
            var singleton_type = type.GetSingletonType()
            return this.GetSingletonType(singleton_type)
        }
        return ""
    }

    NameToString(name)
    {
        if (name)
        {
            return name.UnParse()
        }
        else
        {
            return ""
        }
    }
}

