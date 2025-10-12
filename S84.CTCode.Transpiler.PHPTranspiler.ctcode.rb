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
module PHPTRANSPILER
module CTCODE

class PHPTranspiler < ::S84::CTCODE::TRANSPILER::STANDARDSTRUCTURE::CTCODE::TargetSpecificFunctions
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
        @class_members = Array.new()
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

    def IsReserved(name)
        return false || @string_helper.BeginsWith("ReservedPrefix",name) || @string_helper.BeginsWith("reserved_prefix_",name) || name=="Return" || name=="String" || name=="GetType" || name=="string" || name=="boolean" || name=="char" || name=="float" || name=="decimal"
    end

    def GetCallName(name)
        value = @string_helper.SnakeCaseToCamelCase(name)
        if (self.IsReserved(value))
            return Concat("ReservedPrefix",value)
        end
        return value
    end

    def GetVariableName(name)
        value = @string_helper.CamelCaseToSnakeCase(name)
        if (value=="myself")
            return "this"
        end
        if (self.IsReserved(value))
            return Concat("reserved_prefix_",value)
        end
        return value
    end

    def GetVariableChain(name_parts)
        delimiter = "->"
        first_name = Element(name_parts,0)
        result = self.GetVariableName(first_name)
        name_parts_index = 1
        while (name_parts_index<Size(name_parts))
            name = Element(name_parts,name_parts_index)
            result = Concat(Concat(result,delimiter),self.GetVariableName(name))
            name_parts_index = name_parts_index+1
        end
        return Concat("$",result)
    end

    def ConvertCall(name_chain, parameters)
        result = Element(name_chain,0)
        if (Size(name_chain)>1)
            result = Concat("$",result)
        end
        name_chain_index = 1
        while (name_chain_index<Size(name_chain))
            name_part = Element(name_chain,name_chain_index)
            result = Concat(Concat(result,"->"),name_part)
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
        return Concat(Concat("new ",type),"()")
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

    def Escape(input)
        result = ""
        input_index = 0
        in_escape = false
        while (input_index<Length(input))
            character = At(input,input_index)
            if (character=="'")
                result = Concat(result,"\\")
            end
            if (! in_escape && character=="\\")
                in_escape = true
            else
                in_escape = false
                if (character=="\\")
                    result = Concat(result,"\\")
                end
                result = Concat(result,character)
            end
            input_index = input_index+1
        end
        return result
    end

    def ConvertString(literal)
        return Concat(Concat("'",self.Escape(literal)),"'")
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
        value = @string_helper.SnakeCaseToCamelCase(name)
        if (self.IsReserved(value))
            return Concat("ReservedPrefix",value)
        end
        return value
    end

    def GetDimensionalType(singleton_type, dimensions)
        return "?array"
    end

    def GetMapType(singleton_type)
        return "?array"
    end

    def GetPrimativeType(c_t_type)
        if (c_t_type=="int")
            return "?int"
        end
        if (c_t_type=="string")
            return "?string"
        end
        if (c_t_type=="bool")
            return "?bool"
        end
        if (c_t_type=="float")
            return "?float"
        end
        if (c_t_type=="void")
            return "void"
        end
        return ""
    end

    def GetDefinedType(c_t_type)
        return Concat("?",c_t_type)
    end

    def GetQualifiedTypeName(name_parts)
        delimiter = "\\"
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
        ClearList(@class_members)
    end

    def FinishProcessingCTCodeFile()
        destination_file_name = Concat(@base_name,".php")
        destination_file = @system.OpenFileWriter(destination_file_name)
        destination_file.WriteLine("<?php")
        destination_file.WriteLine(Concat(Concat("namespace ",@string_helper.DotToFwdSlash(@base_name)),";"))
        destination_file.WriteLine("")
        if (Size(@imports)>0)
            @string_helper.WriteLines(destination_file,@imports)
            destination_file.WriteLine("")
        end
        self.WriteCommonFunctions(destination_file)
        destination_file.WriteLine("")
        @string_helper.WriteLines(destination_file,@interface_definitions)
        @string_helper.WriteLines(destination_file,@class_definitions)
        destination_file.WriteLine("?>")
    end

    def ProcessExdef(exdef)
        Append(@imports,Concat(Concat("include_once \"",exdef),".php\";"))
    end

    def ProcessUnmanagedType(unmanaged_type)
    end

    def BeginProcessingInterface(interface_name)
        @current_interface = interface_name
        Append(@interface_definitions,Concat(Concat("interface ",interface_name)," {"))
    end

    def ProcessInterfaceFunctionDeclaration(return_type, function_name, parameters)
        Append(@interface_definitions,Concat(Concat(Concat(Concat(Concat(Concat(@string_helper.Indentation(1),"public function "),function_name),self.MakeParametersString(parameters)),": "),return_type),";"))
    end

    def FinishProcessingInterface(interface_name)
        Append(@interface_definitions,"}")
        Append(@interface_definitions,"")
        @current_interface = ""
    end

    def BeginProcessingClass(class_name, implementing)
        @current_class = class_name
        if (implementing=="")
            Append(@class_definitions,Concat(Concat("class ",class_name)," {"))
        else
            Append(@class_definitions,Concat(Concat(Concat(Concat("class ",class_name)," implements "),implementing)," {"))
        end
        ClearList(@class_init)
        ClearList(@class_functions)
        ClearList(@class_members)
        Append(@class_init,Concat(@string_helper.Indentation(1),"public function __construct() {"))
    end

    def BeginProcessingClassFunctionDefinition(return_type, function_name, parameters)
        Append(@class_functions,"")
        Append(@class_functions,Concat(Concat(Concat(Concat(Concat(@string_helper.Indentation(1),"public function "),function_name),self.MakeParametersString(parameters)),": "),return_type))
    end

    def BeginProcessCodeBlock(indent)
        Append(@class_functions,Concat(@string_helper.Indentation(indent),"{"))
    end

    def FinishProcessCodeBlock(indent)
        Append(@class_functions,Concat(@string_helper.Indentation(indent),"}"))
    end

    def BeginProcessConditional(indent, r_value)
        Append(@class_functions,Concat(Concat(Concat(@string_helper.Indentation(indent),"if ("),r_value),")"))
    end

    def ProcessElse(indent)
        Append(@class_functions,Concat(@string_helper.Indentation(indent),"else"))
    end

    def FinishProcessConditional(indent, r_value)
    end

    def BeginProcessLoop(indent, r_value)
        Append(@class_functions,Concat(Concat(Concat(@string_helper.Indentation(indent),"while ("),r_value),")"))
    end

    def FinishProcessLoop(indent, r_value)
    end

    def ProcessRtn(indent, r_value)
        Append(@class_functions,Concat(Concat(Concat(@string_helper.Indentation(indent),"return "),r_value),";"))
    end

    def ProcessDeclaration(indent, type, l_value, r_value)
        if (r_value=="")
            r_value = self.GetDefault(type)
        end
        Append(@class_functions,Concat(Concat(Concat(Concat(Concat(@string_helper.Indentation(indent),"$"),l_value)," = "),r_value),";"))
    end

    def ProcessAssignment(indent, l_value, r_value)
        Append(@class_functions,Concat(Concat(Concat(Concat(@string_helper.Indentation(indent),l_value)," = "),r_value),";"))
    end

    def ProcessCall(indent, call)
        Append(@class_functions,Concat(Concat(@string_helper.Indentation(indent),call),";"))
    end

    def FinishProcessingClassFunctionDefinition(return_type, function_name, parameters)
    end

    def ProcessClassMemberDeclaration(member_type, member_name)
        Append(@class_init,Concat(Concat(Concat(Concat(Concat(@string_helper.Indentation(2),"$this->"),member_name)," = "),self.GetDefault(member_type)),";"))
        Append(@class_members,Concat(Concat(Concat(@string_helper.Indentation(1),"private $"),member_name),";"))
    end

    def FinishProcessingClass(class_name, implementing)
        Append(@class_init,Concat(@string_helper.Indentation(1),"}"))
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
        Append(@class_definitions,"")
        class_members_index = 0
        while (class_members_index<Size(@class_members))
            line = Element(@class_members,class_members_index)
            Append(@class_definitions,line)
            class_members_index = class_members_index+1
        end
        Append(@class_definitions,"}")
        Append(@class_definitions,"")
        @current_class = ""
    end

    def WriteCommonFunctions(destination_file)
        destination_file.WriteLine("function ClearList(array & $input): void { $input = array(); }")
        destination_file.WriteLine("function Size(array $input): int { return count($input); }")
        destination_file.WriteLine("function Element(array $input, int $element) { return $input[$element]; }")
        destination_file.WriteLine("function Append(array & $input, mixed $element): void { $input[] = $element; }")
        destination_file.WriteLine("function ClearMap(array & $input): void { reset($input); }")
        destination_file.WriteLine("function SetKV(array & $input, string $key, mixed $element): void { $input[$key] = $element; }")
        destination_file.WriteLine("function Keys(array $input): array { return array_keys($input); }")
        destination_file.WriteLine("function HasKV(array $input, string $key): bool { return array_key_exists($key, $input); }")
        destination_file.WriteLine("function GetKV(array $input, string $key) { return $input[$key]; }")
        destination_file.WriteLine("function Length(string $input): int { return strlen($input); }")
        destination_file.WriteLine("function At(string $input, int $index): string { return substr($input, $index, 1); }")
        destination_file.WriteLine("function IntAt(string $input, int $index): int { return ord(substr($input, $index, 1)); }")
        destination_file.WriteLine("function Concat(string $left, string $right): string { return $left . $right; }")
    end

    def GetDefault(php_type)
        if (php_type=="?int")
            return "0"
        end
        if (php_type=="?string")
            return "\"\""
        end
        if (php_type=="?bool")
            return "false"
        end
        if (php_type=="?float")
            return "0.0"
        end
        if (php_type=="void")
            return "null"
        end
        if (php_type=="?array")
            return "array()"
        end
        return "null"
    end

    def MakeParametersString(parameters)
        result = "("
        parameters_index = 0
        while (parameters_index<Size(parameters))
            parameter = Element(parameters,parameters_index)
            if (parameters_index!=0)
                result = Concat(result,", ")
            end
            result = Concat(Concat(Concat(result,parameter.ReservedPrefixGetType())," $"),parameter.GetName())
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
