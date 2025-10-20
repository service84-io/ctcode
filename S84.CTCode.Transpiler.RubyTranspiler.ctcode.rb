require 'S84.CTCode.dbnf.ctcode'
require 'S84.CTCode.System.ctcode'
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
module RUBYTRANSPILER
module CTCODE

class RubyTranspiler < ::S84::CTCODE::TRANSPILER::STANDARDSTRUCTURE::CTCODE::TargetSpecificFunctions
    def initialize()
        @system = nil
        @c_t_code_file = nil
        @base_name = ""
        @logger = nil
        @string_helper = nil
        @imports = Array.new()
        @current_interface = ""
        @interface_definitions = Array.new()
        @current_class = ""
        @class_definitions = Array.new()
        @class_init = Array.new()
        @class_functions = Array.new()
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
        return 1
    end

    def GetCallName(name)
        value = @string_helper.SnakeCaseToCamelCase(name)
        if (@string_helper.IsReserved(value))
            return Concat("ReservedPrefix",value)
        end
        return value
    end

    def GetVariableName(name)
        value = @string_helper.CamelCaseToSnakeCase(name)
        if (value=="myself")
            return "self"
        end
        if (value=="nothing")
            return "nil"
        end
        if (@string_helper.IsReserved(value))
            return Concat("reserved_prefix_",value)
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
            result = Concat(result,delimiter)
            if (result=="self.")
                result = "@"
            end
            result = Concat(result,self.GetVariableName(name))
            name_parts_index = name_parts_index+1
        end
        return result
    end

    def ConvertCall(name_chain, parameters)
        result = Element(name_chain,0)
        name_chain_index = 1
        last_name_chain_index = Size(name_chain)-1
        while (name_chain_index<Size(name_chain))
            name_part = Element(name_chain,name_chain_index)
            result = Concat(result,".")
            if (name_chain_index!=last_name_chain_index)
                if (result=="self.")
                    result = "@"
                end
            end
            result = Concat(result,name_part)
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
        return Concat(type,".new()")
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
            return Concat("! ",r_value)
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
            return Concat(Concat(r_value_l," || "),r_value_r)
        end
        if (op=="&&")
            return Concat(Concat(r_value_l," && "),r_value_r)
        end
        return ""
    end

    def GetTypeName(name)
        value = @string_helper.SnakeCaseToCamelCase(name)
        if (@string_helper.IsReserved(value))
            return Concat("ReservedPrefix",value)
        end
        return value
    end

    def GetDimensionalType(singleton_type, dimensions)
        result = singleton_type
        while (dimensions>0)
            result = Concat(Concat("list[",result),"]")
            dimensions = dimensions-1
        end
        return result
    end

    def GetMapType(singleton_type)
        return Concat(Concat("dict[str, ",singleton_type),"]")
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
        delimiter = "::"
        name_parts_index = Size(name_parts)-1
        type_part = Element(name_parts,name_parts_index)
        result = self.GetTypeName(type_part)
        if (name_parts_index>0)
            while (name_parts_index>0)
                name_parts_index = name_parts_index-1
                result = Concat(delimiter,result)
                name_part = Element(name_parts,name_parts_index)
                result = Concat(@string_helper.ToUpper(name_part),result)
            end
            result = Concat(delimiter,result)
        end
        return result
    end

    def BeginProcessingCTCodeFile()
        ClearList(@imports)
        @current_interface = ""
        ClearList(@interface_definitions)
        @current_class = ""
        ClearList(@class_definitions)
        ClearList(@class_init)
        ClearList(@class_functions)
    end

    def ProcessExdef(exdef)
        Append(@imports,Concat(Concat("require '",exdef),"'"))
    end

    def ProcessUnmanagedType(unmanaged_type)
    end

    def BeginProcessingInterface(interface_name)
        @current_interface = interface_name
        Append(@interface_definitions,Concat("class ",interface_name))
    end

    def ProcessInterfaceFunctionDeclaration(return_type, function_name, parameters)
        Append(@interface_definitions,Concat(Concat(Concat(Concat(@string_helper.Indentation(1),"def "),function_name),self.MakeParametersString(parameters)),"; end"))
    end

    def FinishProcessingInterface(interface_name)
        Append(@interface_definitions,"end")
        Append(@interface_definitions,"")
        @current_interface = ""
    end

    def BeginProcessingClass(class_name, implementing)
        @current_class = class_name
        if (implementing=="")
            Append(@class_definitions,Concat("class ",class_name))
        else
            Append(@class_definitions,Concat(Concat(Concat("class ",class_name)," < "),implementing))
        end
        ClearList(@class_init)
        ClearList(@class_functions)
        Append(@class_init,Concat(@string_helper.Indentation(1),"def initialize()"))
    end

    def BeginProcessingClassFunctionDefinition(return_type, function_name, parameters)
        Append(@class_functions,"")
        Append(@class_functions,Concat(Concat(Concat(@string_helper.Indentation(1),"def "),function_name),self.MakeParametersString(parameters)))
    end

    def BeginProcessCodeBlock(indent)
    end

    def FinishProcessCodeBlock(indent)
    end

    def BeginProcessConditional(indent, r_value)
        Append(@class_functions,Concat(Concat(Concat(@string_helper.Indentation(indent),"if ("),r_value),")"))
    end

    def ProcessElse(indent)
        Append(@class_functions,Concat(@string_helper.Indentation(indent),"else"))
    end

    def FinishProcessConditional(indent, r_value)
        Append(@class_functions,Concat(@string_helper.Indentation(indent),"end"))
    end

    def BeginProcessLoop(indent, r_value)
        Append(@class_functions,Concat(Concat(Concat(@string_helper.Indentation(indent),"while ("),r_value),")"))
    end

    def FinishProcessLoop(indent, r_value)
        Append(@class_functions,Concat(@string_helper.Indentation(indent),"end"))
    end

    def ProcessRtn(indent, r_value)
        Append(@class_functions,Concat(Concat(@string_helper.Indentation(indent),"return "),r_value))
    end

    def ProcessDeclaration(indent, type, l_value, r_value)
        if (r_value=="")
            r_value = self.GetDefault(type)
        end
        Append(@class_functions,Concat(Concat(Concat(@string_helper.Indentation(indent),l_value)," = "),r_value))
    end

    def ProcessAssignment(indent, l_value, r_value)
        Append(@class_functions,Concat(Concat(Concat(@string_helper.Indentation(indent),l_value)," = "),r_value))
    end

    def ProcessCall(indent, call)
        Append(@class_functions,Concat(@string_helper.Indentation(indent),call))
    end

    def FinishProcessingClassFunctionDefinition(return_type, function_name, parameters)
        Append(@class_functions,Concat(@string_helper.Indentation(1),"end"))
    end

    def ProcessClassMemberDeclaration(member_type, member_name)
        Append(@class_init,Concat(Concat(Concat(Concat(@string_helper.Indentation(2),"@"),member_name)," = "),self.GetDefault(member_type)))
    end

    def FinishProcessingClass(class_name, implementing)
        Append(@class_init,Concat(@string_helper.Indentation(1),"end"))
        class_init_index = 0
        while (class_init_index<Size(@class_init))
            line = Element(@class_init,class_init_index)
            Append(@class_definitions,line)
            class_init_index = class_init_index+1
        end
        class_functions_index = 0
        while (class_functions_index<Size(@class_functions))
            line = Element(@class_functions,class_functions_index)
            Append(@class_definitions,line)
            class_functions_index = class_functions_index+1
        end
        Append(@class_definitions,"end")
        Append(@class_definitions,"")
        @current_class = ""
    end

    def WriteCommonFunctions(destination_file)
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
    end

    def TokenizeBaseName(name)
        base_name_tokens = Array.new()
        current_token = ""
        index = 0
        while (index<Length(name))
            character = At(name,index)
            if (character==".")
                Append(base_name_tokens,current_token)
                current_token = ""
            else
                current_token = Concat(current_token,character)
            end
            index = index+1
        end
        Append(base_name_tokens,current_token)
        return base_name_tokens
    end

    def WriteBeginingNamespace(file)
        base_name_tokens = self.TokenizeBaseName(@base_name)
        base_name_tokens_index = 0
        while (base_name_tokens_index<Size(base_name_tokens))
            base_name_token = Element(base_name_tokens,base_name_tokens_index)
            file.WriteLine(Concat("module ",@string_helper.ToUpper(base_name_token)))
            base_name_tokens_index = base_name_tokens_index+1
        end
    end

    def WriteEndingNamespace(file)
        base_name_tokens = self.TokenizeBaseName(@base_name)
        base_name_tokens_index = 0
        while (base_name_tokens_index<Size(base_name_tokens))
            base_name_token = Element(base_name_tokens,base_name_tokens_index)
            file.WriteLine("end")
            base_name_tokens_index = base_name_tokens_index+1
        end
    end

    def FinishProcessingCTCodeFile()
        destination_file_name = Concat(@base_name,".rb")
        destination_file = @system.OpenFileWriter(destination_file_name)
        if (Size(@imports)>0)
            @string_helper.WriteLines(destination_file,@imports)
            destination_file.WriteLine("")
        end
        self.WriteCommonFunctions(destination_file)
        destination_file.WriteLine("")
        self.WriteBeginingNamespace(destination_file)
        destination_file.WriteLine("")
        @string_helper.WriteLines(destination_file,@interface_definitions)
        @string_helper.WriteLines(destination_file,@class_definitions)
        self.WriteEndingNamespace(destination_file)
    end

    def GetDefault(javascript_type)
        if (javascript_type=="int")
            return "0"
        end
        if (javascript_type=="string")
            return "\"\""
        end
        if (javascript_type=="bool")
            return "false"
        end
        if (javascript_type=="float")
            return "0.0"
        end
        if (javascript_type=="void")
            return "nil"
        end
        if (@string_helper.BeginsWith("dict[str",javascript_type))
            return "Hash.new()"
        end
        if (@string_helper.BeginsWith("list[",javascript_type))
            return "Array.new()"
        end
        return "nil"
    end

    def MakeParametersString(parameters)
        result = "("
        parameters_index = 0
        while (parameters_index<Size(parameters))
            parameter = Element(parameters,parameters_index)
            if (parameters_index!=0)
                result = Concat(result,", ")
            end
            result = Concat(result,parameter.GetName())
            parameters_index = parameters_index+1
        end
        result = Concat(result,")")
        return result
    end
end

end
end
end
end
end
