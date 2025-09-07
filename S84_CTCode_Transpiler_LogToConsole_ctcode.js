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

export class ParameterDeclaration {
    constructor() {
        this.type = ""
        this.name = ""
    }

    GetType()
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

export class LogToConsole {
    constructor() {
        this.system = null
        this.c_t_code_file = null
        this.base_name = ""
        this.logger = null
    }

    GetBaseIndentation()
    {
        return 3
    }

    GetCallName(name)
    {
        if (name)
        {
            return this.SnakeCaseToCamelCase(name.UnParse())
        }
        else
        {
            return ""
        }
    }

    GetVariableName(name)
    {
        if (name)
        {
            var value = this.CamelCaseToSnakeCase(name.UnParse())
            if (value=="myself")
            {
                return "self"
            }
            return value
        }
        else
        {
            return ""
        }
    }

    GetVariableChainNameTail(tail)
    {
        var accessor = "."
        if (tail)
        {
            return Concat(Concat(accessor,this.GetVariableName(tail.GetName())),this.GetVariableChainNameTail(tail.GetTail()))
        }
        else
        {
            return ""
        }
    }

    GetVariableChain(l_value)
    {
        if (l_value)
        {
            return Concat(this.GetVariableName(l_value.GetName()),this.GetVariableChainNameTail(l_value.GetTail()))
        }
        else
        {
            return ""
        }
    }

    ConvertCall(name_chain, parameters)
    {
        var result = Element(name_chain,0)
        var name_chain_index = 1
        while (name_chain_index<Size(name_chain))
        {
            var name_part = Element(name_chain,name_chain_index)
            result = Concat(Concat(result,"."),name_part)
            name_chain_index = name_chain_index+1
        }
        result = Concat(result,"(")
        if (Size(parameters)>0)
        {
            result = Concat(result,Element(parameters,0))
            var parameters_index = 1
            while (parameters_index<Size(parameters))
            {
                var parameter = Element(parameters,parameters_index)
                result = Concat(result,",")
                result = Concat(result,parameter)
                parameters_index = parameters_index+1
            }
        }
        result = Concat(result,")")
        return result
    }

    ConvertAllocate(type)
    {
        return Concat("new ",type)
    }

    ConvertByte(high, low)
    {
        return Concat(Concat("0x",high),low)
    }

    ConvertDecimal(decimal)
    {
        return decimal
    }

    ConvertNumber(number)
    {
        return number
    }

    ConvertBoolean(boolean)
    {
        if (boolean=="true")
        {
            return "true"
        }
        if (boolean=="false")
        {
            return "false"
        }
        return ""
    }

    ConvertVariable(variable)
    {
        return variable
    }

    ConvertString(literal)
    {
        return Concat(Concat("\"",literal),"\"")
    }

    UnaryOperator(op, r_value)
    {
        if (op=="!")
        {
            return Concat("!",r_value)
        }
        return r_value
    }

    BinaryOperator(op, r_value_l, r_value_r)
    {
        if (op=="+")
        {
            return Concat(Concat(r_value_l,"+"),r_value_r)
        }
        if (op=="-")
        {
            return Concat(Concat(r_value_l,"-"),r_value_r)
        }
        if (op=="<=")
        {
            return Concat(Concat(r_value_l,"<="),r_value_r)
        }
        if (op==">=")
        {
            return Concat(Concat(r_value_l,">="),r_value_r)
        }
        if (op=="==")
        {
            return Concat(Concat(r_value_l,"=="),r_value_r)
        }
        if (op=="!=")
        {
            return Concat(Concat(r_value_l,"!="),r_value_r)
        }
        if (op=="<")
        {
            return Concat(Concat(r_value_l,"<"),r_value_r)
        }
        if (op==">")
        {
            return Concat(Concat(r_value_l,">"),r_value_r)
        }
        if (op=="||")
        {
            return Concat(Concat(r_value_l,"||"),r_value_r)
        }
        if (op=="&&")
        {
            return Concat(Concat(r_value_l,"&&"),r_value_r)
        }
        return ""
    }

    GetTypeName(name)
    {
        if (name)
        {
            return this.SnakeCaseToCamelCase(name.UnParse())
        }
        else
        {
            return ""
        }
    }

    GetDimensionalType(singleton_type, dimensions)
    {
        var result = singleton_type
        while (dimensions>0)
        {
            result = Concat(result,"[]")
            dimensions = dimensions-1
        }
        return result
    }

    GetMapType(singleton_type)
    {
        return Concat(singleton_type,"{}")
    }

    GetPrimativeType(c_t_type)
    {
        if (c_t_type=="int")
        {
            return "int"
        }
        if (c_t_type=="string")
        {
            return "string"
        }
        if (c_t_type=="bool")
        {
            return "bool"
        }
        if (c_t_type=="float")
        {
            return "float"
        }
        if (c_t_type=="void")
        {
            return "void"
        }
        return ""
    }

    GetQualifiedTypeName(name_parts)
    {
        var delimiter = "."
        var first_name = Element(name_parts,0)
        var result = first_name.UnParse()
        var name_parts_index = 1
        while (name_parts_index<Size(name_parts))
        {
            var name = Element(name_parts,name_parts_index)
            result = Concat(Concat(result,delimiter),name.UnParse())
            name_parts_index = name_parts_index+1
        }
        return result
    }

    BeginProcessingCTCodeFile()
    {
        this.logger.WriteLine("BeginProcessingCTCodeFile")
    }

    ProcessExdef(exdef)
    {
        this.logger.WriteLine(Concat(Concat(this.Indentation(1),"ProcessExdef: "),exdef))
    }

    ProcessUnmanagedType(unmanaged_type)
    {
        this.logger.WriteLine(Concat(Concat(this.Indentation(1),"ProcessUnmanagedType: "),unmanaged_type))
    }

    BeginProcessingInterface(interface_name)
    {
        this.logger.WriteLine(Concat(Concat(this.Indentation(1),"BeginProcessingInterface: "),interface_name))
    }

    ProcessInterfaceFunctionDeclaration(return_type, function_name, parameters)
    {
        this.logger.WriteLine(Concat(Concat(Concat(Concat(this.Indentation(2),"ProcessInterfaceFunctionDeclaration: "),return_type)," "),function_name))
    }

    FinishProcessingInterface(interface_name)
    {
        this.logger.WriteLine(Concat(Concat(this.Indentation(1),"FinishProcessingInterface: "),interface_name))
    }

    BeginProcessingClass(class_name, implementing)
    {
        this.logger.WriteLine(Concat(Concat(Concat(Concat(this.Indentation(1),"BeginProcessingClass: "),class_name)," "),implementing))
    }

    BeginProcessingClassFunctionDefinition(return_type, function_name, parameters)
    {
        this.logger.WriteLine(Concat(Concat(Concat(Concat(this.Indentation(2),"BeginProcessingClassFunctionDefinition: "),return_type)," "),function_name))
    }

    BeginProcessCodeBlock(indent)
    {
        this.logger.WriteLine(Concat(this.Indentation(indent),"BeginProcessCodeBlock"))
    }

    FinishProcessCodeBlock(indent)
    {
        this.logger.WriteLine(Concat(this.Indentation(indent),"FinishProcessCodeBlock"))
    }

    BeginProcessConditional(indent, r_value)
    {
        this.logger.WriteLine(Concat(Concat(this.Indentation(indent),"BeginProcessConditional: "),r_value))
    }

    ProcessElse(indent)
    {
        this.logger.WriteLine(Concat(this.Indentation(indent),"ProcessElse"))
    }

    FinishProcessConditional(indent, r_value)
    {
        this.logger.WriteLine(Concat(Concat(this.Indentation(indent),"FinishProcessConditional: "),r_value))
    }

    BeginProcessLoop(indent, r_value)
    {
        this.logger.WriteLine(Concat(Concat(this.Indentation(indent),"BeginProcessLoop: "),r_value))
    }

    FinishProcessLoop(indent, r_value)
    {
        this.logger.WriteLine(Concat(Concat(this.Indentation(indent),"FinishProcessLoop: "),r_value))
    }

    ProcessRtn(indent, r_value)
    {
        this.logger.WriteLine(Concat(Concat(this.Indentation(indent),"ProcessRtn: "),r_value))
    }

    ProcessDeclaration(indent, type, l_value, r_value)
    {
        this.logger.WriteLine(Concat(Concat(Concat(Concat(Concat(Concat(this.Indentation(indent),"ProcessDeclaration: "),type)," "),l_value)," "),r_value))
    }

    ProcessAssignment(indent, l_value, r_value)
    {
        this.logger.WriteLine(Concat(Concat(Concat(Concat(this.Indentation(indent),"ProcessAssignment: "),l_value)," "),r_value))
    }

    ProcessCall(indent, call)
    {
        this.logger.WriteLine(Concat(Concat(this.Indentation(indent),"ProcessCall: "),call))
    }

    FinishProcessingClassFunctionDefinition(return_type, function_name, parameters)
    {
        this.logger.WriteLine(Concat(Concat(Concat(Concat(this.Indentation(2),"FinishProcessingClassFunctionDefinition: "),return_type)," "),function_name))
    }

    ProcessClassMemberDeclaration(member_type, member_name)
    {
        this.logger.WriteLine(Concat(Concat(Concat(Concat(this.Indentation(2),"ProcessClassMemberDeclaration: "),member_type)," "),member_name))
    }

    FinishProcessingClass(class_name, implementing)
    {
        this.logger.WriteLine(Concat(Concat(this.Indentation(1),"FinishProcessingClass: "),class_name))
    }

    FinishProcessingCTCodeFile()
    {
        this.logger.WriteLine("FinishProcessingCTCodeFile")
    }

    Transpile(system, c_t_code_file, base_name)
    {
        this.system = system
        this.c_t_code_file = c_t_code_file
        this.base_name = base_name
        this.logger = system.GetLoggerDestination()
        this.ProcessCTCodeFile(c_t_code_file)
        return 0
    }

    ProcessCTCodeFile(c_t_code_file)
    {
        this.BeginProcessingCTCodeFile()
        this.ProcessExdefs(c_t_code_file)
        this.ProcessUnmanagedTypes(c_t_code_file)
        this.ProcessDefinitions(c_t_code_file)
        this.FinishProcessingCTCodeFile()
    }

    ProcessExdefs(c_t_code_file)
    {
        var exdefs = c_t_code_file.GetDeclarations()
        var exdefs_index = 0
        while (exdefs_index<Size(exdefs))
        {
            var exdef = Element(exdefs,exdefs_index)
            var exdef_name = exdef.GetExdef()
            this.ProcessExdef(exdef_name.UnParse())
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
            this.ProcessUnmanagedType(this.GetQualifiedTypeNameInternal(unmanaged_type.GetUnmanagedType()))
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
            parameter.SetType(this.GetType(parameter_list_def.GetType()))
            parameter.SetName(this.GetVariableName(parameter_list_def.GetName()))
            Append(result,parameter)
            parameter_list_def = parameter_list_def.GetParameterTail()
        }
        return result
    }

    ProcessInterfaceDefinition(interface_definition)
    {
        var interface_name = this.GetTypeName(interface_definition.GetName())
        this.BeginProcessingInterface(interface_name)
        var declarations = interface_definition.GetDeclarations()
        var declarations_index = 0
        while (declarations_index<Size(declarations))
        {
            var declaration = Element(declarations,declarations_index)
            var return_type = this.GetType(declaration.GetType())
            var function_name = this.GetCallName(declaration.GetName())
            var parameters = this.GetParameters(declaration.GetParameters())
            this.ProcessInterfaceFunctionDeclaration(return_type,function_name,parameters)
            declarations_index = declarations_index+1
        }
        this.FinishProcessingInterface(interface_name)
    }

    ProcessClassDefinition(class_definition)
    {
        var class_name = this.GetTypeName(class_definition.GetName())
        var implementing = ""
        var implementation_spec = class_definition.GetImplementing()
        if (implementation_spec)
        {
            implementing = this.GetQualifiedTypeNameInternal(implementation_spec.GetInterface())
        }
        this.BeginProcessingClass(class_name,implementing)
        var definitions = class_definition.GetDefinitions()
        var definitions_index = 0
        while (definitions_index<Size(definitions))
        {
            var definition = Element(definitions,definitions_index)
            if (definition.GetFunctionBody())
            {
                var return_type = this.GetType(definition.GetType())
                var function_name = this.GetCallName(definition.GetName())
                var parameters = this.GetParameters(definition.GetParameters())
                this.BeginProcessingClassFunctionDefinition(return_type,function_name,parameters)
                this.ProcessCodeBlockInternal(this.GetBaseIndentation(),definition.GetFunctionBody())
                this.FinishProcessingClassFunctionDefinition(return_type,function_name,parameters)
            }
            else
            {
                var member_type = this.GetType(definition.GetType())
                var member_name = this.GetVariableName(definition.GetName())
                this.ProcessClassMemberDeclaration(member_type,member_name)
            }
            definitions_index = definitions_index+1
        }
        this.FinishProcessingClass(class_name,implementing)
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
        this.BeginProcessCodeBlock(indent)
        var instructions = code_block.GetInstructions()
        var instructions_index = 0
        while (instructions_index<Size(instructions))
        {
            this.ProcessInstructionInternal(indent+1,Element(instructions,instructions_index))
            instructions_index = instructions_index+1
        }
        this.FinishProcessCodeBlock(indent)
    }

    ProcessConditionalInternal(indent, conditional)
    {
        var r_value = this.GetRValueInternal(conditional.GetRValue())
        this.BeginProcessConditional(indent,r_value)
        this.ProcessCodeBlockInternal(indent,conditional.GetCodeBlock())
        if (conditional.GetElseTail())
        {
            var else_tail = conditional.GetElseTail()
            this.ProcessElse(indent)
            this.ProcessCodeBlockInternal(indent,else_tail.GetCodeBlock())
        }
        this.FinishProcessConditional(indent,r_value)
    }

    ProcessLoopInternal(indent, loop)
    {
        var r_value = this.GetRValueInternal(loop.GetRValue())
        this.BeginProcessLoop(indent,r_value)
        this.ProcessCodeBlockInternal(indent,loop.GetCodeBlock())
        this.FinishProcessLoop(indent,r_value)
    }

    ProcessRtnInternal(indent, rtn)
    {
        var r_value = this.GetRValueInternal(rtn.GetRValue())
        this.ProcessRtn(indent,r_value)
    }

    ProcessDeclarationInternal(indent, declaration)
    {
        var type = this.GetType(declaration.GetType())
        var l_value = this.GetVariableName(declaration.GetName())
        var r_value = ""
        var declaration_assignment = declaration.GetAssignment()
        if (declaration_assignment)
        {
            r_value = this.GetRValueInternal(declaration_assignment.GetRValue())
        }
        this.ProcessDeclaration(indent,type,l_value,r_value)
    }

    ProcessAssignmentInternal(indent, assignment)
    {
        this.ProcessAssignment(indent,this.GetVariableChain(assignment.GetLValue()),this.GetRValueInternal(assignment.GetRValue()))
    }

    ProcessCallInternal(indent, call)
    {
        this.ProcessCall(indent,this.ConvertCallInternal(call))
    }

    ConvertCallInternal(call)
    {
        var name_chain = []
        var parameters = []
        if (call.GetVariable())
        {
            Append(name_chain,this.GetVariableName(call.GetVariable()))
        }
        if (call.GetFunction())
        {
            Append(name_chain,this.GetCallName(call.GetFunction()))
        }
        if (call.GetFunctionChain())
        {
            var function_chain = call.GetFunctionChain()
            var name_tail = function_chain.GetTail()
            if (function_chain.GetTail())
            {
                Append(name_chain,this.GetVariableName(function_chain.GetName()))
            }
            else
            {
                Append(name_chain,this.GetCallName(function_chain.GetName()))
            }
            while (name_tail)
            {
                if (name_tail.GetTail())
                {
                    Append(name_chain,this.GetVariableName(name_tail.GetName()))
                }
                else
                {
                    Append(name_chain,this.GetCallName(name_tail.GetName()))
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
        return this.ConvertCall(name_chain,parameters)
    }

    GetSingletonType(singleton_type)
    {
        if (singleton_type.GetPrimativeType())
        {
            return this.GetPrimativeType(singleton_type.UnParse())
        }
        if (singleton_type.GetDefinedType())
        {
            var defined_type = singleton_type.GetDefinedType()
            return this.GetQualifiedTypeNameInternal(defined_type.GetName())
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
            return this.ConvertAllocate(this.GetQualifiedTypeNameInternal(allocate.GetManagedType()))
        }
        var byte_literal = r_value_single.GetByteLiteral()
        if (byte_literal)
        {
            var high = byte_literal.GetHigh()
            var low = byte_literal.GetLow()
            return this.ConvertByte(high.UnParse(),low.UnParse())
        }
        var decimal_literal = r_value_single.GetDecimalLiteral()
        if (decimal_literal)
        {
            return this.ConvertDecimal(decimal_literal.UnParse())
        }
        var integer_literal = r_value_single.GetIntegerLiteral()
        if (integer_literal)
        {
            return this.ConvertNumber(integer_literal.UnParse())
        }
        var boolean_literal = r_value_single.GetBooleanLiteral()
        if (boolean_literal)
        {
            return this.ConvertBoolean(boolean_literal.UnParse())
        }
        var variable = r_value_single.GetVariable()
        if (variable)
        {
            return this.ConvertVariable(this.GetVariableChain(variable))
        }
        var string_literal = r_value_single.GetStringLiteral()
        if (string_literal)
        {
            return this.ConvertString(string_literal.UnParse())
        }
        return ""
    }

    GetRValueSingleInternal(r_value_single)
    {
        var unary_operator = r_value_single.GetUnaryOperator()
        if (unary_operator)
        {
            return this.UnaryOperator(unary_operator.UnParse(),this.GetRValueSingleBasisInternal(r_value_single))
        }
        return this.GetRValueSingleBasisInternal(r_value_single)
    }

    GetRValueBinaryInternal(r_value_l, r_value_tail)
    {
        var r_value_r = this.GetRValueSingleInternal(r_value_tail.GetValue())
        var binary_operator = r_value_tail.GetBinaryOperator()
        r_value_l = this.BinaryOperator(binary_operator.UnParse(),r_value_l,r_value_r)
        if (r_value_tail.GetTail())
        {
            return this.GetRValueBinaryInternal(r_value_l,r_value_tail.GetTail())
        }
        return r_value_l
    }

    GetRValueInternal(r_value)
    {
        var r_value_l = this.GetRValueSingleInternal(r_value.GetValue())
        if (r_value.GetTail())
        {
            return this.GetRValueBinaryInternal(r_value_l,r_value.GetTail())
        }
        return r_value_l
    }

    GetQualifiedTypeNameInternal(qualified_name)
    {
        var name_parts = []
        Append(name_parts,qualified_name.GetName())
        var tail = qualified_name.GetTail()
        while (tail)
        {
            Append(name_parts,tail.GetName())
            tail = tail.GetTail()
        }
        return this.GetQualifiedTypeName(name_parts)
    }

    GetType(type)
    {
        if (type.GetDimensionalType())
        {
            var dimensional_type = type.GetDimensionalType()
            var singleton_type = dimensional_type.GetSingletonType()
            return this.GetDimensionalType(this.GetSingletonType(singleton_type),Size(dimensional_type.GetDimensionalNote()))
        }
        if (type.GetMapType())
        {
            var map_type = type.GetMapType()
            var singleton_type = map_type.GetSingletonType()
            return this.GetMapType(this.GetSingletonType(singleton_type))
        }
        if (type.GetSingletonType())
        {
            var singleton_type = type.GetSingletonType()
            return this.GetSingletonType(singleton_type)
        }
        return ""
    }

    Indentation(indent)
    {
        var result = ""
        result = ""
        while (indent>0)
        {
            indent = indent-1
            result = Concat(result,"    ")
        }
        return result
    }

    SnakeCaseToCamelCase(snake_case)
    {
        var capitalize_this_letter = true
        var camel_case = ""
        var index = 0
        index = 0
        while (index<Length(snake_case))
        {
            var source_character = At(snake_case,index)
            if (source_character=="_")
            {
                capitalize_this_letter = true
            }
            else
            {
                if (capitalize_this_letter==true)
                {
                    var upper_character = this.CharacterToUpper(source_character)
                    capitalize_this_letter = false
                    camel_case = Concat(camel_case,upper_character)
                }
                else
                {
                    capitalize_this_letter = false
                    camel_case = Concat(camel_case,source_character)
                }
            }
            index = index+1
        }
        return camel_case
    }

    CamelCaseToSnakeCase(camel_case)
    {
        var delimiter = "_"
        var snake_case = ""
        var index = 0
        while (index<Length(camel_case))
        {
            var source_character = At(camel_case,index)
            var lower_character = this.CharacterToLower(source_character)
            if (this.IsUpper(source_character) || this.IsDigit(source_character))
            {
                var is_first_character = Length(snake_case)==0
                if (! is_first_character)
                {
                    snake_case = Concat(snake_case,delimiter)
                }
            }
            snake_case = Concat(snake_case,lower_character)
            index = index+1
        }
        return snake_case
    }

    IsUpper(character)
    {
        var result = false
        result = false
        result = result || character=="A"
        result = result || character=="B"
        result = result || character=="C"
        result = result || character=="D"
        result = result || character=="E"
        result = result || character=="F"
        result = result || character=="G"
        result = result || character=="H"
        result = result || character=="I"
        result = result || character=="J"
        result = result || character=="K"
        result = result || character=="L"
        result = result || character=="M"
        result = result || character=="N"
        result = result || character=="O"
        result = result || character=="P"
        result = result || character=="Q"
        result = result || character=="R"
        result = result || character=="S"
        result = result || character=="T"
        result = result || character=="U"
        result = result || character=="V"
        result = result || character=="W"
        result = result || character=="X"
        result = result || character=="Y"
        result = result || character=="Z"
        return result
    }

    IsDigit(character)
    {
        var result = false
        result = false
        result = result || character=="0"
        result = result || character=="1"
        result = result || character=="2"
        result = result || character=="3"
        result = result || character=="4"
        result = result || character=="5"
        result = result || character=="6"
        result = result || character=="7"
        result = result || character=="8"
        result = result || character=="9"
        return result
    }

    ToLower(input)
    {
        var index = 0
        var result = ""
        while (index<Length(input))
        {
            var character = At(input,index)
            var lower_character = this.CharacterToLower(character)
            result = Concat(result,lower_character)
            index = index+1
        }
        return result
    }

    CharacterToLower(input)
    {
        if (input=="A")
        {
            return "a"
        }
        if (input=="B")
        {
            return "b"
        }
        if (input=="C")
        {
            return "c"
        }
        if (input=="D")
        {
            return "d"
        }
        if (input=="E")
        {
            return "e"
        }
        if (input=="F")
        {
            return "f"
        }
        if (input=="G")
        {
            return "g"
        }
        if (input=="H")
        {
            return "h"
        }
        if (input=="I")
        {
            return "i"
        }
        if (input=="J")
        {
            return "j"
        }
        if (input=="K")
        {
            return "k"
        }
        if (input=="L")
        {
            return "l"
        }
        if (input=="M")
        {
            return "m"
        }
        if (input=="N")
        {
            return "n"
        }
        if (input=="O")
        {
            return "o"
        }
        if (input=="P")
        {
            return "p"
        }
        if (input=="Q")
        {
            return "q"
        }
        if (input=="R")
        {
            return "r"
        }
        if (input=="S")
        {
            return "s"
        }
        if (input=="T")
        {
            return "t"
        }
        if (input=="U")
        {
            return "u"
        }
        if (input=="V")
        {
            return "v"
        }
        if (input=="W")
        {
            return "w"
        }
        if (input=="X")
        {
            return "x"
        }
        if (input=="Y")
        {
            return "y"
        }
        if (input=="Z")
        {
            return "z"
        }
        return input
    }

    ToUpper(input)
    {
        var index = 0
        var result = ""
        while (index<Length(input))
        {
            var character = At(input,index)
            var upper_character = this.CharacterToUpper(character)
            result = Concat(result,upper_character)
            index = index+1
        }
        return result
    }

    CharacterToUpper(input)
    {
        if (input=="a")
        {
            return "A"
        }
        if (input=="b")
        {
            return "B"
        }
        if (input=="c")
        {
            return "C"
        }
        if (input=="d")
        {
            return "D"
        }
        if (input=="e")
        {
            return "E"
        }
        if (input=="f")
        {
            return "F"
        }
        if (input=="g")
        {
            return "G"
        }
        if (input=="h")
        {
            return "H"
        }
        if (input=="i")
        {
            return "I"
        }
        if (input=="j")
        {
            return "J"
        }
        if (input=="k")
        {
            return "K"
        }
        if (input=="l")
        {
            return "L"
        }
        if (input=="m")
        {
            return "M"
        }
        if (input=="n")
        {
            return "N"
        }
        if (input=="o")
        {
            return "O"
        }
        if (input=="p")
        {
            return "P"
        }
        if (input=="q")
        {
            return "Q"
        }
        if (input=="r")
        {
            return "R"
        }
        if (input=="s")
        {
            return "S"
        }
        if (input=="t")
        {
            return "T"
        }
        if (input=="u")
        {
            return "U"
        }
        if (input=="v")
        {
            return "V"
        }
        if (input=="w")
        {
            return "W"
        }
        if (input=="x")
        {
            return "X"
        }
        if (input=="y")
        {
            return "Y"
        }
        if (input=="z")
        {
            return "Z"
        }
        return input
    }
}

