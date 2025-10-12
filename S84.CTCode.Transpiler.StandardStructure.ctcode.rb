require 'S84.CTCode.dbnf.ctcode'
require 'S84.CTCode.System.ctcode'
require 'S84.CTCode.Transpiler.ctcode'

def ClearList(input); input.clear(); end
def Size(input); return input.length(); end
def Element(input, element); return input[element]; end
def Append(input, element); input.push(element); end
def ClearMap(input); input.clear(); end
def SetKV(input, key, element); input[key] = element; end
def Keys(input); return input.keys(); end
def HasKV(input, key); return input.has_key?(key); end
def GetKV(input, key); return input[key]; end
def Length(input); return input.length(); end
def At(input, index); return input[index]; end
def IntAt(input, index); return input[index].ord(); end
def Concat(left, right); return left + right; end

module S84
module CTCODE
module TRANSPILER
module STANDARDSTRUCTURE
module CTCODE

class TargetSpecificFunctions
    def Initialize(); end
    def SetSystem(system); end
    def SetCTCodeFile(c_t_code_file); end
    def SetBaseName(base_name); end
    def SetLogger(logger); end
    def GetBaseIndentation(); end
    def GetCallName(name); end
    def GetVariableName(name); end
    def GetVariableChain(name_parts); end
    def ConvertCall(name_chain, parameters); end
    def ConvertAllocate(type); end
    def ConvertByte(high, low); end
    def ConvertDecimal(reserved_prefix_decimal); end
    def ConvertNumber(number); end
    def ConvertBoolean(reserved_prefix_boolean); end
    def ConvertVariable(variable); end
    def ConvertString(literal); end
    def UnaryOperator(op, r_value); end
    def BinaryOperator(op, r_value_l, r_value_r); end
    def GetTypeName(name); end
    def GetDimensionalType(singleton_type, dimensions); end
    def GetMapType(singleton_type); end
    def GetPrimativeType(c_t_type); end
    def GetDefinedType(c_t_type); end
    def GetQualifiedTypeName(name_parts); end
    def BeginProcessingCTCodeFile(); end
    def FinishProcessingCTCodeFile(); end
    def ProcessExdef(exdef); end
    def ProcessUnmanagedType(unmanaged_type); end
    def BeginProcessingInterface(interface_name); end
    def ProcessInterfaceFunctionDeclaration(return_type, function_name, parameters); end
    def FinishProcessingInterface(interface_name); end
    def BeginProcessingClass(class_name, implementing); end
    def BeginProcessingClassFunctionDefinition(return_type, function_name, parameters); end
    def BeginProcessCodeBlock(indent); end
    def FinishProcessCodeBlock(indent); end
    def BeginProcessConditional(indent, r_value); end
    def ProcessElse(indent); end
    def FinishProcessConditional(indent, r_value); end
    def BeginProcessLoop(indent, r_value); end
    def FinishProcessLoop(indent, r_value); end
    def ProcessRtn(indent, r_value); end
    def ProcessDeclaration(indent, type, l_value, r_value); end
    def ProcessAssignment(indent, l_value, r_value); end
    def ProcessCall(indent, call); end
    def FinishProcessingClassFunctionDefinition(return_type, function_name, parameters); end
    def ProcessClassMemberDeclaration(member_type, member_name); end
    def FinishProcessingClass(class_name, implementing); end
end

class ParameterDeclaration
    def initialize()
        @type = ""
        @name = ""
    end

    def ReservedPrefixGetType()
        return @type
    end

    def SetType(input)
        @type = input
    end

    def GetName()
        return @name
    end

    def SetName(input)
        @name = input
    end
end

class IntegerReference
    def initialize()
        @value = 0
    end

    def GetValue()
        return @value
    end

    def SetValue(value)
        @value = value
    end
end

class StandardStructure < ::S84::CTCODE::TRANSPILER::CTCODE::Transpiler
    def initialize()
        @system = nil
        @c_t_code_file = nil
        @base_name = ""
        @operator_precedent = Array.new()
        @logger = nil
        @target_specific_functions = nil
    end

    def SetTargetSpecificFunctions(target_specific_functions)
        @target_specific_functions = target_specific_functions
    end

    def Transpile(system, c_t_code_file, base_name)
        ClearList(@operator_precedent)
        self.PopulateOperatorPrecedent()
        @system = system
        @c_t_code_file = c_t_code_file
        @base_name = base_name
        @logger = system.GetLoggerDestination()
        @target_specific_functions.SetSystem(@system)
        @target_specific_functions.SetCTCodeFile(@c_t_code_file)
        @target_specific_functions.SetBaseName(@base_name)
        @target_specific_functions.SetLogger(@logger)
        self.ProcessCTCodeFile(c_t_code_file)
        return 0
    end

    def ProcessCTCodeFile(c_t_code_file)
        @target_specific_functions.BeginProcessingCTCodeFile()
        self.ProcessExdefs(c_t_code_file)
        self.ProcessUnmanagedTypes(c_t_code_file)
        self.ProcessDefinitions(c_t_code_file)
        @target_specific_functions.FinishProcessingCTCodeFile()
    end

    def ProcessExdefs(c_t_code_file)
        exdefs = c_t_code_file.GetDeclarations()
        exdefs_index = 0
        while (exdefs_index<Size(exdefs))
            exdef = Element(exdefs,exdefs_index)
            exdef_name = exdef.GetExdef()
            @target_specific_functions.ProcessExdef(exdef_name.UnParse())
            exdefs_index = exdefs_index+1
        end
    end

    def ProcessUnmanagedTypes(c_t_code_file)
        unmanaged_types = c_t_code_file.GetUnmanagedTypes()
        unmanaged_types_index = 0
        while (unmanaged_types_index<Size(unmanaged_types))
            unmanaged_type = Element(unmanaged_types,unmanaged_types_index)
            @target_specific_functions.ProcessUnmanagedType(self.GetQualifiedTypeNameInternal(unmanaged_type.GetUnmanagedType()))
            unmanaged_types_index = unmanaged_types_index+1
        end
    end

    def ProcessDefinitions(c_t_code_file)
        definitions = c_t_code_file.GetDefinitions()
        definitions_index = 0
        while (definitions_index<Size(definitions))
            definition = nil
            definition = Element(definitions,definitions_index)
            if (definition.GetInterfaceDef())
                self.ProcessInterfaceDefinition(definition.GetInterfaceDef())
            end
            if (definition.GetClassDef())
                self.ProcessClassDefinition(definition.GetClassDef())
            end
            definitions_index = definitions_index+1
        end
    end

    def GetParameters(parameter_list_def)
        result = Array.new()
        while (parameter_list_def)
            parameter = ParameterDeclaration.new()
            parameter.SetType(self.ReservedPrefixGetType(parameter_list_def.ReservedPrefixGetType()))
            parameter.SetName(@target_specific_functions.GetVariableName(self.NameToString(parameter_list_def.GetName())))
            Append(result,parameter)
            parameter_list_def = parameter_list_def.GetParameterTail()
        end
        return result
    end

    def ProcessInterfaceDefinition(interface_definition)
        interface_name = @target_specific_functions.GetTypeName(self.NameToString(interface_definition.GetName()))
        @target_specific_functions.BeginProcessingInterface(interface_name)
        declarations = interface_definition.GetDeclarations()
        declarations_index = 0
        while (declarations_index<Size(declarations))
            declaration = Element(declarations,declarations_index)
            return_type = self.ReservedPrefixGetType(declaration.ReservedPrefixGetType())
            function_name = @target_specific_functions.GetCallName(self.NameToString(declaration.GetName()))
            parameters = self.GetParameters(declaration.GetParameters())
            @target_specific_functions.ProcessInterfaceFunctionDeclaration(return_type,function_name,parameters)
            declarations_index = declarations_index+1
        end
        @target_specific_functions.FinishProcessingInterface(interface_name)
    end

    def ProcessClassDefinition(class_definition)
        class_name = @target_specific_functions.GetTypeName(self.NameToString(class_definition.GetName()))
        implementing = ""
        implementation_spec = class_definition.GetImplementing()
        if (implementation_spec)
            implementing = self.GetQualifiedTypeNameInternal(implementation_spec.GetInterface())
        end
        @target_specific_functions.BeginProcessingClass(class_name,implementing)
        definitions = class_definition.GetDefinitions()
        definitions_index = 0
        while (definitions_index<Size(definitions))
            definition = Element(definitions,definitions_index)
            if (definition.GetFunctionBody())
                return_type = self.ReservedPrefixGetType(definition.ReservedPrefixGetType())
                function_name = @target_specific_functions.GetCallName(self.NameToString(definition.GetName()))
                parameters = self.GetParameters(definition.GetParameters())
                @target_specific_functions.BeginProcessingClassFunctionDefinition(return_type,function_name,parameters)
                self.ProcessCodeBlockInternal(@target_specific_functions.GetBaseIndentation(),definition.GetFunctionBody())
                @target_specific_functions.FinishProcessingClassFunctionDefinition(return_type,function_name,parameters)
            else
                member_type = self.ReservedPrefixGetType(definition.ReservedPrefixGetType())
                member_name = @target_specific_functions.GetVariableName(self.NameToString(definition.GetName()))
                @target_specific_functions.ProcessClassMemberDeclaration(member_type,member_name)
            end
            definitions_index = definitions_index+1
        end
        @target_specific_functions.FinishProcessingClass(class_name,implementing)
    end

    def ProcessInstructionInternal(indent, instruction)
        if (instruction.GetCodeBlock())
            self.ProcessCodeBlockInternal(indent,instruction.GetCodeBlock())
        end
        if (instruction.GetRtn())
            self.ProcessRtnInternal(indent,instruction.GetRtn())
        end
        if (instruction.GetDeclaration())
            self.ProcessDeclarationInternal(indent,instruction.GetDeclaration())
        end
        if (instruction.GetAssignment())
            self.ProcessAssignmentInternal(indent,instruction.GetAssignment())
        end
        if (instruction.GetCall())
            self.ProcessCallInternal(indent,instruction.GetCall())
        end
        if (instruction.GetConditional())
            self.ProcessConditionalInternal(indent,instruction.GetConditional())
        end
        if (instruction.GetLoop())
            self.ProcessLoopInternal(indent,instruction.GetLoop())
        end
    end

    def ProcessCodeBlockInternal(indent, code_block)
        @target_specific_functions.BeginProcessCodeBlock(indent)
        instructions = code_block.GetInstructions()
        instructions_index = 0
        while (instructions_index<Size(instructions))
            self.ProcessInstructionInternal(indent+1,Element(instructions,instructions_index))
            instructions_index = instructions_index+1
        end
        @target_specific_functions.FinishProcessCodeBlock(indent)
    end

    def ProcessConditionalInternal(indent, conditional)
        r_value = self.GetRValueInternal(conditional.GetRValue())
        @target_specific_functions.BeginProcessConditional(indent,r_value)
        self.ProcessCodeBlockInternal(indent,conditional.GetCodeBlock())
        if (conditional.GetElseTail())
            else_tail = conditional.GetElseTail()
            @target_specific_functions.ProcessElse(indent)
            self.ProcessCodeBlockInternal(indent,else_tail.GetCodeBlock())
        end
        @target_specific_functions.FinishProcessConditional(indent,r_value)
    end

    def ProcessLoopInternal(indent, loop)
        r_value = self.GetRValueInternal(loop.GetRValue())
        @target_specific_functions.BeginProcessLoop(indent,r_value)
        self.ProcessCodeBlockInternal(indent,loop.GetCodeBlock())
        @target_specific_functions.FinishProcessLoop(indent,r_value)
    end

    def ProcessRtnInternal(indent, rtn)
        r_value = self.GetRValueInternal(rtn.GetRValue())
        @target_specific_functions.ProcessRtn(indent,r_value)
    end

    def ProcessDeclarationInternal(indent, declaration)
        type = self.ReservedPrefixGetType(declaration.ReservedPrefixGetType())
        l_value = @target_specific_functions.GetVariableName(self.NameToString(declaration.GetName()))
        r_value = ""
        declaration_assignment = declaration.GetAssignment()
        if (declaration_assignment)
            r_value = self.GetRValueInternal(declaration_assignment.GetRValue())
        end
        @target_specific_functions.ProcessDeclaration(indent,type,l_value,r_value)
    end

    def ProcessAssignmentInternal(indent, assignment)
        @target_specific_functions.ProcessAssignment(indent,self.GetVariableChainInternal(assignment.GetLValue()),self.GetRValueInternal(assignment.GetRValue()))
    end

    def ProcessCallInternal(indent, call)
        @target_specific_functions.ProcessCall(indent,self.ConvertCallInternal(call))
    end

    def ConvertCallInternal(call)
        name_chain = Array.new()
        parameters = Array.new()
        if (call.GetVariable())
            Append(name_chain,@target_specific_functions.GetVariableName(self.NameToString(call.GetVariable())))
        end
        if (call.GetFunction())
            Append(name_chain,@target_specific_functions.GetCallName(self.NameToString(call.GetFunction())))
        end
        if (call.GetFunctionChain())
            function_chain = call.GetFunctionChain()
            name_tail = function_chain.GetTail()
            if (function_chain.GetTail())
                Append(name_chain,@target_specific_functions.GetVariableName(self.NameToString(function_chain.GetName())))
            else
                Append(name_chain,@target_specific_functions.GetCallName(self.NameToString(function_chain.GetName())))
            end
            while (name_tail)
                if (name_tail.GetTail())
                    Append(name_chain,@target_specific_functions.GetVariableName(self.NameToString(name_tail.GetName())))
                else
                    Append(name_chain,@target_specific_functions.GetCallName(self.NameToString(name_tail.GetName())))
                end
                name_tail = name_tail.GetTail()
            end
        end
        parameter_list = call.GetParameters()
        while (parameter_list)
            Append(parameters,self.GetRValueInternal(parameter_list.GetRValue()))
            parameter_list = parameter_list.GetParameterTail()
        end
        return @target_specific_functions.ConvertCall(name_chain,parameters)
    end

    def GetSingletonType(singleton_type)
        if (singleton_type.GetPrimativeType())
            return @target_specific_functions.GetPrimativeType(singleton_type.UnParse())
        end
        if (singleton_type.GetDefinedType())
            defined_type = singleton_type.GetDefinedType()
            return @target_specific_functions.GetDefinedType(self.GetQualifiedTypeNameInternal(defined_type.GetName()))
        end
        return ""
    end

    def GetRValueSingleBasisInternal(r_value_single)
        call = r_value_single.GetCall()
        if (call)
            return self.ConvertCallInternal(call)
        end
        allocate = r_value_single.GetAllocate()
        if (allocate)
            return @target_specific_functions.ConvertAllocate(self.GetQualifiedTypeNameInternal(allocate.GetManagedType()))
        end
        byte_literal = r_value_single.GetByteLiteral()
        if (byte_literal)
            high = byte_literal.GetHigh()
            low = byte_literal.GetLow()
            return @target_specific_functions.ConvertByte(high.UnParse(),low.UnParse())
        end
        decimal_literal = r_value_single.GetDecimalLiteral()
        if (decimal_literal)
            return @target_specific_functions.ConvertDecimal(decimal_literal.UnParse())
        end
        integer_literal = r_value_single.GetIntegerLiteral()
        if (integer_literal)
            return @target_specific_functions.ConvertNumber(integer_literal.UnParse())
        end
        boolean_literal = r_value_single.GetBooleanLiteral()
        if (boolean_literal)
            return @target_specific_functions.ConvertBoolean(boolean_literal.UnParse())
        end
        variable = r_value_single.GetVariable()
        if (variable)
            return @target_specific_functions.ConvertVariable(self.GetVariableChainInternal(variable))
        end
        string_literal = r_value_single.GetStringLiteral()
        if (string_literal)
            return @target_specific_functions.ConvertString(string_literal.UnParse())
        end
        return ""
    end

    def GetRValueSingleInternal(r_value_single)
        unary_operator = r_value_single.GetUnaryOperator()
        if (unary_operator)
            return @target_specific_functions.UnaryOperator(unary_operator.UnParse(),self.GetRValueSingleBasisInternal(r_value_single))
        end
        return self.GetRValueSingleBasisInternal(r_value_single)
    end

    def PopulateOperatorPrecedent()
        precedent__0_operators = Array.new()
        Append(precedent__0_operators,"+")
        Append(precedent__0_operators,"-")
        Append(@operator_precedent,precedent__0_operators)
        precedent__1_operators = Array.new()
        Append(precedent__1_operators,"<=")
        Append(precedent__1_operators,">=")
        Append(precedent__1_operators,"==")
        Append(precedent__1_operators,"!=")
        Append(precedent__1_operators,"<")
        Append(precedent__1_operators,">")
        Append(@operator_precedent,precedent__1_operators)
        precedent__2_operators = Array.new()
        Append(precedent__2_operators,"&&")
        Append(@operator_precedent,precedent__2_operators)
        precedent__3_operators = Array.new()
        Append(precedent__3_operators,"||")
        Append(@operator_precedent,precedent__3_operators)
        precedent__4_operators = Array.new()
        Append(precedent__4_operators,"")
        Append(@operator_precedent,precedent__4_operators)
    end

    def OverPrecedent(op, precedent)
        precedent = precedent+1
        while (precedent<Size(@operator_precedent))
            precedent_operators = Element(@operator_precedent,precedent)
            index = 0
            while (index<Size(precedent_operators))
                checking_op = Element(precedent_operators,index)
                if (checking_op==op)
                    return true
                end
                index = index+1
            end
            precedent = precedent+1
        end
        return false
    end

    def BinaryOperatorPrecedentMerge(values, operators, index, precedent)
        if (precedent==-1)
            return Element(values,index.GetValue())
        end
        r_value_l = self.BinaryOperatorPrecedentMerge(values,operators,index,precedent-1)
        while (index.GetValue()<Size(operators))
            op = Element(operators,index.GetValue())
            if (self.OverPrecedent(op,precedent))
                return r_value_l
            end
            index.SetValue(index.GetValue()+1)
            r_value_r = self.BinaryOperatorPrecedentMerge(values,operators,index,precedent-1)
            r_value_l = @target_specific_functions.BinaryOperator(op,r_value_l,r_value_r)
        end
        return r_value_l
    end

    def GetRValueInternal(r_value)
        values = Array.new()
        operators = Array.new()
        index = IntegerReference.new()
        index.SetValue(0)
        Append(values,self.GetRValueSingleInternal(r_value.GetValue()))
        r_value_tail = r_value.GetTail()
        while (r_value_tail)
            binary_operator = r_value_tail.GetBinaryOperator()
            Append(values,self.GetRValueSingleInternal(r_value_tail.GetValue()))
            Append(operators,binary_operator.UnParse())
            r_value_tail = r_value_tail.GetTail()
        end
        return self.BinaryOperatorPrecedentMerge(values,operators,index,Size(@operator_precedent))
    end

    def GetQualifiedTypeNameInternal(qualified_name)
        name_parts = Array.new()
        Append(name_parts,self.NameToString(qualified_name.GetName()))
        tail = qualified_name.GetTail()
        while (tail)
            Append(name_parts,self.NameToString(tail.GetName()))
            tail = tail.GetTail()
        end
        return @target_specific_functions.GetQualifiedTypeName(name_parts)
    end

    def GetVariableChainInternal(qualified_name)
        name_parts = Array.new()
        Append(name_parts,self.NameToString(qualified_name.GetName()))
        tail = qualified_name.GetTail()
        while (tail)
            Append(name_parts,self.NameToString(tail.GetName()))
            tail = tail.GetTail()
        end
        return @target_specific_functions.GetVariableChain(name_parts)
    end

    def ReservedPrefixGetType(type)
        if (type.GetDimensionalType())
            dimensional_type = type.GetDimensionalType()
            singleton_type = dimensional_type.GetSingletonType()
            return @target_specific_functions.GetDimensionalType(self.GetSingletonType(singleton_type),Size(dimensional_type.GetDimensionalNote()))
        end
        if (type.GetMapType())
            map_type = type.GetMapType()
            singleton_type = map_type.GetSingletonType()
            return @target_specific_functions.GetMapType(self.GetSingletonType(singleton_type))
        end
        if (type.GetSingletonType())
            singleton_type = type.GetSingletonType()
            return self.GetSingletonType(singleton_type)
        end
        return ""
    end

    def NameToString(name)
        if (name)
            return name.UnParse()
        else
            return ""
        end
    end
end

end
end
end
end
end
