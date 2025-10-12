require 'S84.CTCode.dbnf.ctcode'
require 'S84.CTCode.Transpiler.StandardStructure.ctcode'
require 'S84.CTCode.Transpiler.StringHelper.ctcode'

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
module LOGTOCONSOLE
module CTCODE

class LogToConsole < ::S84::CTCODE::TRANSPILER::STANDARDSTRUCTURE::CTCODE::TargetSpecificFunctions
    def initialize()
        @system = nil
        @c_t_code_file = nil
        @base_name = ""
        @logger = nil
        @string_helper = nil
    end

    def Initialize()
        @string_helper = ::S84::CTCODE::TRANSPILER::STRINGHELPER::CTCODE::StringHelper.new()
    end

    def SetSystem(system)
        @system = system
    end

    def SetCTCodeFile(c_t_code_file)
        @c_t_code_file = c_t_code_file
    end

    def SetBaseName(base_name)
        @base_name = base_name
    end

    def SetLogger(logger)
        @logger = logger
    end

    def GetBaseIndentation()
        return 3
    end

    def GetCallName(name)
        return @string_helper.SnakeCaseToCamelCase(name)
    end

    def GetVariableName(name)
        value = @string_helper.CamelCaseToSnakeCase(name)
        if (value=="myself")
            return "thyself"
        end
        return value
    end

    def GetVariableChain(name_parts)
        delimiter = "."
        first_name = Element(name_parts,0)
        result = self.GetVariableName(first_name)
        name_parts_index = 1
        while (name_parts_index<Size(name_parts))
            name = Element(name_parts,name_parts_index)
            result = Concat(Concat(result,delimiter),self.GetVariableName(name))
            name_parts_index = name_parts_index+1
        end
        return result
    end

    def ConvertCall(name_chain, parameters)
        result = Element(name_chain,0)
        name_chain_index = 1
        while (name_chain_index<Size(name_chain))
            name_part = Element(name_chain,name_chain_index)
            result = Concat(Concat(result,"."),name_part)
            name_chain_index = name_chain_index+1
        end
        result = Concat(result,"(")
        if (Size(parameters)>0)
            result = Concat(result,Element(parameters,0))
            parameters_index = 1
            while (parameters_index<Size(parameters))
                parameter = Element(parameters,parameters_index)
                result = Concat(result,",")
                result = Concat(result,parameter)
                parameters_index = parameters_index+1
            end
        end
        result = Concat(result,")")
        return result
    end

    def ConvertAllocate(type)
        return Concat("new ",type)
    end

    def ConvertByte(high, low)
        return Concat(Concat("0x",high),low)
    end

    def ConvertDecimal(reserved_prefix_decimal)
        return reserved_prefix_decimal
    end

    def ConvertNumber(number)
        return number
    end

    def ConvertBoolean(reserved_prefix_boolean)
        if (reserved_prefix_boolean=="true")
            return "true"
        end
        if (reserved_prefix_boolean=="false")
            return "false"
        end
        return ""
    end

    def ConvertVariable(variable)
        return variable
    end

    def ConvertString(literal)
        return Concat(Concat("\"",literal),"\"")
    end

    def UnaryOperator(op, r_value)
        if (op=="!")
            return Concat("!",r_value)
        end
        return r_value
    end

    def BinaryOperator(op, r_value_l, r_value_r)
        if (op=="+")
            return Concat(Concat(r_value_l,"+"),r_value_r)
        end
        if (op=="-")
            return Concat(Concat(r_value_l,"-"),r_value_r)
        end
        if (op=="<=")
            return Concat(Concat(r_value_l,"<="),r_value_r)
        end
        if (op==">=")
            return Concat(Concat(r_value_l,">="),r_value_r)
        end
        if (op=="==")
            return Concat(Concat(r_value_l,"=="),r_value_r)
        end
        if (op=="!=")
            return Concat(Concat(r_value_l,"!="),r_value_r)
        end
        if (op=="<")
            return Concat(Concat(r_value_l,"<"),r_value_r)
        end
        if (op==">")
            return Concat(Concat(r_value_l,">"),r_value_r)
        end
        if (op=="||")
            return Concat(Concat(r_value_l,"||"),r_value_r)
        end
        if (op=="&&")
            return Concat(Concat(r_value_l,"&&"),r_value_r)
        end
        return ""
    end

    def GetTypeName(name)
        return @string_helper.SnakeCaseToCamelCase(name)
    end

    def GetDimensionalType(singleton_type, dimensions)
        result = singleton_type
        while (dimensions>0)
            result = Concat(result,"[]")
            dimensions = dimensions-1
        end
        return result
    end

    def GetMapType(singleton_type)
        return Concat(singleton_type,"{}")
    end

    def GetPrimativeType(c_t_type)
        if (c_t_type=="int")
            return "int"
        end
        if (c_t_type=="string")
            return "string"
        end
        if (c_t_type=="bool")
            return "bool"
        end
        if (c_t_type=="float")
            return "float"
        end
        if (c_t_type=="void")
            return "void"
        end
        return ""
    end

    def GetDefinedType(c_t_type)
        return c_t_type
    end

    def GetQualifiedTypeName(name_parts)
        delimiter = "."
        name_parts_index = Size(name_parts)-1
        type_part = Element(name_parts,name_parts_index)
        result = self.GetTypeName(type_part)
        if (name_parts_index>0)
            while (name_parts_index>0)
                name_parts_index = name_parts_index-1
                result = Concat(delimiter,result)
                name_part = Element(name_parts,name_parts_index)
                result = Concat(name_part,result)
            end
        end
        return result
    end

    def BeginProcessingCTCodeFile()
        @logger.WriteLine("BeginProcessingCTCodeFile")
    end

    def FinishProcessingCTCodeFile()
        @logger.WriteLine("FinishProcessingCTCodeFile")
    end

    def ProcessExdef(exdef)
        @logger.WriteLine(Concat(Concat(@string_helper.Indentation(1),"ProcessExdef: "),exdef))
    end

    def ProcessUnmanagedType(unmanaged_type)
        @logger.WriteLine(Concat(Concat(@string_helper.Indentation(1),"ProcessUnmanagedType: "),unmanaged_type))
    end

    def BeginProcessingInterface(interface_name)
        @logger.WriteLine(Concat(Concat(@string_helper.Indentation(1),"BeginProcessingInterface: "),interface_name))
    end

    def ProcessInterfaceFunctionDeclaration(return_type, function_name, parameters)
        @logger.WriteLine(Concat(Concat(Concat(Concat(@string_helper.Indentation(2),"ProcessInterfaceFunctionDeclaration: "),return_type)," "),function_name))
    end

    def FinishProcessingInterface(interface_name)
        @logger.WriteLine(Concat(Concat(@string_helper.Indentation(1),"FinishProcessingInterface: "),interface_name))
    end

    def BeginProcessingClass(class_name, implementing)
        @logger.WriteLine(Concat(Concat(Concat(Concat(@string_helper.Indentation(1),"BeginProcessingClass: "),class_name)," "),implementing))
    end

    def BeginProcessingClassFunctionDefinition(return_type, function_name, parameters)
        @logger.WriteLine(Concat(Concat(Concat(Concat(@string_helper.Indentation(2),"BeginProcessingClassFunctionDefinition: "),return_type)," "),function_name))
    end

    def BeginProcessCodeBlock(indent)
        @logger.WriteLine(Concat(@string_helper.Indentation(indent),"BeginProcessCodeBlock"))
    end

    def FinishProcessCodeBlock(indent)
        @logger.WriteLine(Concat(@string_helper.Indentation(indent),"FinishProcessCodeBlock"))
    end

    def BeginProcessConditional(indent, r_value)
        @logger.WriteLine(Concat(Concat(@string_helper.Indentation(indent),"BeginProcessConditional: "),r_value))
    end

    def ProcessElse(indent)
        @logger.WriteLine(Concat(@string_helper.Indentation(indent),"ProcessElse"))
    end

    def FinishProcessConditional(indent, r_value)
        @logger.WriteLine(Concat(Concat(@string_helper.Indentation(indent),"FinishProcessConditional: "),r_value))
    end

    def BeginProcessLoop(indent, r_value)
        @logger.WriteLine(Concat(Concat(@string_helper.Indentation(indent),"BeginProcessLoop: "),r_value))
    end

    def FinishProcessLoop(indent, r_value)
        @logger.WriteLine(Concat(Concat(@string_helper.Indentation(indent),"FinishProcessLoop: "),r_value))
    end

    def ProcessRtn(indent, r_value)
        @logger.WriteLine(Concat(Concat(@string_helper.Indentation(indent),"ProcessRtn: "),r_value))
    end

    def ProcessDeclaration(indent, type, l_value, r_value)
        @logger.WriteLine(Concat(Concat(Concat(Concat(Concat(Concat(@string_helper.Indentation(indent),"ProcessDeclaration: "),type)," "),l_value)," "),r_value))
    end

    def ProcessAssignment(indent, l_value, r_value)
        @logger.WriteLine(Concat(Concat(Concat(Concat(@string_helper.Indentation(indent),"ProcessAssignment: "),l_value)," "),r_value))
    end

    def ProcessCall(indent, call)
        @logger.WriteLine(Concat(Concat(@string_helper.Indentation(indent),"ProcessCall: "),call))
    end

    def FinishProcessingClassFunctionDefinition(return_type, function_name, parameters)
        @logger.WriteLine(Concat(Concat(Concat(Concat(@string_helper.Indentation(2),"FinishProcessingClassFunctionDefinition: "),return_type)," "),function_name))
    end

    def ProcessClassMemberDeclaration(member_type, member_name)
        @logger.WriteLine(Concat(Concat(Concat(Concat(@string_helper.Indentation(2),"ProcessClassMemberDeclaration: "),member_type)," "),member_name))
    end

    def FinishProcessingClass(class_name, implementing)
        @logger.WriteLine(Concat(Concat(@string_helper.Indentation(1),"FinishProcessingClass: "),class_name))
    end
end

end
end
end
end
end
