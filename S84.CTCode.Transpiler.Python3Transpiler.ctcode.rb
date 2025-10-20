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
module PYTHON3TRANSPILER
module CTCODE

class Python3Transpiler < ::S84::CTCODE::TRANSPILER::STANDARDSTRUCTURE::CTCODE::TargetSpecificFunctions
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
        @current_class_function_has_operation = false
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
            return "None"
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
        return Concat(type,"()")
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
            return "True"
        end
        if (reserved_prefix_boolean=="false")
            return "False"
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
            return Concat("not ",r_value)
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
            return Concat(Concat(r_value_l," or "),r_value_r)
        end
        if (op=="&&")
            return Concat(Concat(r_value_l," and "),r_value_r)
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
            return "str"
        end
        if (c_t_type=="bool")
            return "bool"
        end
        if (c_t_type=="float")
            return "float"
        end
        if (c_t_type=="void")
            return "None"
        end
        return ""
    end

    def GetDefinedType(c_t_type)
        return c_t_type
    end

    def GetQualifiedTypeName(name_parts)
        package_delimiter = "_"
        package_name_delimiter = "."
        name_parts_index = Size(name_parts)-1
        last_package_index = Size(name_parts)-2
        type_part = Element(name_parts,name_parts_index)
        result = self.GetTypeName(type_part)
        if (name_parts_index>0)
            result = Concat(package_name_delimiter,result)
            while (name_parts_index>0)
                name_parts_index = name_parts_index-1
                name_part = Element(name_parts,name_parts_index)
                if (name_parts_index!=last_package_index)
                    result = Concat(package_delimiter,result)
                end
                result = Concat(name_part,result)
            end
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
        @current_class_function_has_operation = false
    end

    def ProcessExdef(exdef)
        Append(@imports,Concat("import ",@string_helper.StripDot(exdef)))
    end

    def ProcessUnmanagedType(unmanaged_type)
    end

    def BeginProcessingInterface(interface_name)
        @current_interface = interface_name
        Append(@interface_definitions,Concat(Concat("class ",interface_name),":"))
    end

    def ProcessInterfaceFunctionDeclaration(return_type, function_name, parameters)
        Append(@interface_definitions,Concat(Concat(Concat(Concat(Concat(Concat(@string_helper.Indentation(1),"def "),function_name),self.MakeParametersString(@current_interface,parameters))," -> '"),return_type),"': pass"))
    end

    def FinishProcessingInterface(interface_name)
        Append(@interface_definitions,"")
        @current_interface = ""
    end

    def BeginProcessingClass(class_name, implementing)
        @current_class = class_name
        if (implementing=="")
            Append(@class_definitions,Concat(Concat("class ",class_name),":"))
        else
            Append(@class_definitions,Concat(Concat(Concat(Concat("class ",class_name),"("),implementing),"):"))
        end
        ClearList(@class_init)
        ClearList(@class_functions)
        @current_class_function_has_operation = false
        Append(@class_init,Concat(Concat(Concat(@string_helper.Indentation(1),"def __init__(self: '"),class_name),"'):"))
    end

    def BeginProcessingClassFunctionDefinition(return_type, function_name, parameters)
        Append(@class_functions,Concat(Concat(Concat(Concat(Concat(Concat(@string_helper.Indentation(1),"def "),function_name),self.MakeParametersString(@current_class,parameters))," -> '"),return_type),"':"))
        @current_class_function_has_operation = false
    end

    def BeginProcessCodeBlock(indent)
    end

    def FinishProcessCodeBlock(indent)
    end

    def BeginProcessConditional(indent, r_value)
        @current_class_function_has_operation = true
        Append(@class_functions,Concat(Concat(Concat(@string_helper.Indentation(indent),"if "),r_value),":"))
    end

    def ProcessElse(indent)
        @current_class_function_has_operation = true
        Append(@class_functions,Concat(@string_helper.Indentation(indent),"else:"))
    end

    def FinishProcessConditional(indent, r_value)
        @current_class_function_has_operation = true
    end

    def BeginProcessLoop(indent, r_value)
        @current_class_function_has_operation = true
        Append(@class_functions,Concat(Concat(Concat(@string_helper.Indentation(indent),"while "),r_value),":"))
    end

    def FinishProcessLoop(indent, r_value)
        @current_class_function_has_operation = true
    end

    def ProcessRtn(indent, r_value)
        @current_class_function_has_operation = true
        Append(@class_functions,Concat(Concat(@string_helper.Indentation(indent),"return "),r_value))
    end

    def ProcessDeclaration(indent, type, l_value, r_value)
        @current_class_function_has_operation = true
        if (r_value=="")
            r_value = self.GetDefault(type)
        end
        Append(@class_functions,Concat(Concat(Concat(Concat(Concat(@string_helper.Indentation(indent),l_value),": '"),type),"' = "),r_value))
    end

    def ProcessAssignment(indent, l_value, r_value)
        @current_class_function_has_operation = true
        Append(@class_functions,Concat(Concat(Concat(@string_helper.Indentation(indent),l_value)," = "),r_value))
    end

    def ProcessCall(indent, call)
        @current_class_function_has_operation = true
        Append(@class_functions,Concat(@string_helper.Indentation(indent),call))
    end

    def FinishProcessingClassFunctionDefinition(return_type, function_name, parameters)
        if (! @current_class_function_has_operation)
            Append(@class_functions,Concat(@string_helper.Indentation(2),"pass"))
        end
        Append(@class_functions,"")
    end

    def ProcessClassMemberDeclaration(member_type, member_name)
        Append(@class_init,Concat(Concat(Concat(Concat(Concat(Concat(@string_helper.Indentation(2),"self."),member_name),": "),member_type)," = "),self.GetDefault(member_type)))
    end

    def FinishProcessingClass(class_name, implementing)
        if (Size(@class_init)==1)
            Append(@class_init,Concat(@string_helper.Indentation(2),"pass"))
        end
        class_init_index = 0
        while (class_init_index<Size(@class_init))
            line = Element(@class_init,class_init_index)
            Append(@class_definitions,line)
            class_init_index = class_init_index+1
        end
        Append(@class_definitions,"")
        class_functions_index = 0
        while (class_functions_index<Size(@class_functions))
            line = Element(@class_functions,class_functions_index)
            Append(@class_definitions,line)
            class_functions_index = class_functions_index+1
        end
        @current_class = ""
    end

    def WriteCommonFunctions(destination_file)
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
    end

    def FinishProcessingCTCodeFile()
        destination_file_name = Concat(@string_helper.StripDot(@base_name),".py")
        destination_file = @system.OpenFileWriter(destination_file_name)
        if (Size(@imports)>0)
            @string_helper.WriteLines(destination_file,@imports)
            destination_file.WriteLine("")
        end
        self.WriteCommonFunctions(destination_file)
        destination_file.WriteLine("")
        @string_helper.WriteLines(destination_file,@interface_definitions)
        @string_helper.WriteLines(destination_file,@class_definitions)
    end

    def GetDefault(python_type)
        if (python_type=="int")
            return "0"
        end
        if (python_type=="str")
            return "\"\""
        end
        if (python_type=="bool")
            return "False"
        end
        if (python_type=="float")
            return "0.0"
        end
        if (python_type=="None")
            return "None"
        end
        if (@string_helper.BeginsWith("dict[str",python_type))
            return "{}"
        end
        if (@string_helper.BeginsWith("list[",python_type))
            return "[]"
        end
        return "None"
    end

    def MakeParametersString(self_type, parameters)
        result = Concat(Concat("(self: '",self_type),"'")
        parameters_index = 0
        while (parameters_index<Size(parameters))
            parameter = Element(parameters,parameters_index)
            result = Concat(result,",")
            result = Concat(Concat(Concat(Concat(result,parameter.GetName()),": '"),parameter.ReservedPrefixGetType()),"'")
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
