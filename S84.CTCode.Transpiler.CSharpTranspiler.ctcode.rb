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
module CSHARPTRANSPILER
module CTCODE

class CSharpTranspiler < ::S84::CTCODE::TRANSPILER::STANDARDSTRUCTURE::CTCODE::TargetSpecificFunctions
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
        @class_members = Array.new()
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

    def IsReserved(name)
        return false || @string_helper.BeginsWith("ReservedPrefix",name) || @string_helper.BeginsWith("reserved_prefix_",name) || name=="GetType" || name=="boolean" || name=="float" || name=="decimal"
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
            result = Concat(Concat(result,"?."),name_part)
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
        result = ""
        variable_index = 0
        while (variable_index<Length(variable))
            character = At(variable,variable_index)
            if (character==".")
                result = Concat(result,"?")
            end
            result = Concat(result,character)
            variable_index = variable_index+1
        end
        return result
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
            return Concat(Concat(Concat(Concat("AsBoolean(",r_value_l),")||AsBoolean("),r_value_r),")")
        end
        if (op=="&&")
            return Concat(Concat(Concat(Concat("AsBoolean(",r_value_l),")&&AsBoolean("),r_value_r),")")
        end
        return ""
    end

    def GetTypeName(name)
        return @string_helper.SnakeCaseToCamelCase(name)
    end

    def GetDimensionalType(singleton_type, dimensions)
        result = singleton_type
        while (dimensions>0)
            result = Concat(Concat("List<",result),">?")
            dimensions = dimensions-1
        end
        return result
    end

    def GetMapType(singleton_type)
        return Concat(Concat("Dictionary<string,",singleton_type),">?")
    end

    def GetPrimativeType(c_t_type)
        if (c_t_type=="int")
            return "int?"
        end
        if (c_t_type=="string")
            return "string?"
        end
        if (c_t_type=="bool")
            return "bool?"
        end
        if (c_t_type=="float")
            return "float?"
        end
        if (c_t_type=="void")
            return "void"
        end
        return ""
    end

    def GetDefinedType(c_t_type)
        return Concat(c_t_type,"?")
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
        ClearList(@imports)
        @current_interface = ""
        ClearList(@interface_definitions)
        @current_class = ""
        ClearList(@class_definitions)
        ClearList(@class_members)
        ClearList(@class_init)
        ClearList(@class_functions)
    end

    def FinishProcessingCTCodeFile()
        destination_file_name = Concat(@base_name,".cs")
        destination_file = @system.OpenFileWriter(destination_file_name)
        destination_file.WriteLine(Concat(Concat("namespace ",@base_name),";"))
        destination_file.WriteLine("")
        @string_helper.WriteLines(destination_file,@interface_definitions)
        @string_helper.WriteLines(destination_file,@class_definitions)
    end

    def ProcessExdef(exdef)
        Append(@imports,Concat(Concat("using ",exdef),";"))
    end

    def ProcessUnmanagedType(unmanaged_type)
    end

    def BeginProcessingInterface(interface_name)
        @current_interface = interface_name
        Append(@interface_definitions,Concat("public interface ",interface_name))
        Append(@interface_definitions,"{")
    end

    def ProcessInterfaceFunctionDeclaration(return_type, function_name, parameters)
        Append(@interface_definitions,Concat(Concat(Concat(Concat(Concat(@string_helper.Indentation(1),return_type)," "),function_name),self.MakeParametersString(@current_interface,parameters)),";"))
    end

    def FinishProcessingInterface(interface_name)
        Append(@interface_definitions,"}")
        Append(@interface_definitions,"")
        @current_interface = ""
    end

    def BeginProcessingClass(class_name, implementing)
        @current_class = class_name
        if (implementing=="")
            Append(@class_definitions,Concat("public class ",class_name))
        else
            Append(@class_definitions,Concat(Concat(Concat("public class ",class_name)," : "),implementing))
        end
        Append(@class_definitions,"{")
        ClearList(@class_members)
        ClearList(@class_init)
        ClearList(@class_functions)
        Append(@class_init,Concat(Concat(Concat(@string_helper.Indentation(1),"public "),class_name),"()"))
        Append(@class_init,Concat(@string_helper.Indentation(1),"{"))
    end

    def BeginProcessingClassFunctionDefinition(return_type, function_name, parameters)
        Append(@class_functions,Concat(Concat(Concat(Concat(Concat(@string_helper.Indentation(1),"public "),return_type)," "),function_name),self.MakeParametersString(@current_class,parameters)))
    end

    def BeginProcessCodeBlock(indent)
        Append(@class_functions,Concat(@string_helper.Indentation(indent),"{"))
    end

    def FinishProcessCodeBlock(indent)
        Append(@class_functions,Concat(@string_helper.Indentation(indent),"}"))
    end

    def BeginProcessConditional(indent, r_value)
        Append(@class_functions,Concat(Concat(Concat(@string_helper.Indentation(indent),"if (AsBoolean("),r_value),"))"))
    end

    def ProcessElse(indent)
        Append(@class_functions,Concat(@string_helper.Indentation(indent),"else"))
    end

    def FinishProcessConditional(indent, r_value)
    end

    def BeginProcessLoop(indent, r_value)
        Append(@class_functions,Concat(Concat(Concat(@string_helper.Indentation(indent),"while (AsBoolean("),r_value),"))"))
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
        Append(@class_functions,Concat(Concat(Concat(Concat(Concat(Concat(@string_helper.Indentation(indent),type)," "),l_value)," = "),r_value),";"))
    end

    def ProcessAssignment(indent, l_value, r_value)
        Append(@class_functions,Concat(Concat(Concat(Concat(@string_helper.Indentation(indent),l_value)," = "),r_value),";"))
    end

    def ProcessCall(indent, call)
        Append(@class_functions,Concat(Concat(@string_helper.Indentation(indent),call),";"))
    end

    def FinishProcessingClassFunctionDefinition(return_type, function_name, parameters)
        Append(@class_functions,"")
    end

    def ProcessClassMemberDeclaration(member_type, member_name)
        Append(@class_init,Concat(Concat(Concat(Concat(Concat(@string_helper.Indentation(2),"this."),member_name)," = "),self.GetDefault(member_type)),";"))
        Append(@class_members,Concat(Concat(Concat(Concat(Concat(@string_helper.Indentation(1),"private "),member_type)," "),member_name),";"))
    end

    def FinishProcessingClass(class_name, implementing)
        if (Size(@class_members)>0)
            class_members_index = 0
            while (class_members_index<Size(@class_members))
                line = Element(@class_members,class_members_index)
                Append(@class_definitions,line)
                class_members_index = class_members_index+1
            end
            Append(@class_definitions,"")
        end
        Append(@class_init,Concat(@string_helper.Indentation(1),"}"))
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
        self.WriteCommonFunctions()
        Append(@class_definitions,"}")
        @current_class = ""
    end

    def WriteCommonFunctions()
        Append(@class_definitions,Concat(@string_helper.Indentation(1),"private static void ClearList<T>(List<T>? input) { input?.Clear(); }"))
        Append(@class_definitions,Concat(@string_helper.Indentation(1),"private static int? Size<T>(List<T>? input) { return input?.Count; }"))
        Append(@class_definitions,Concat(@string_helper.Indentation(1),"private static T? Element<T>(List<T>? input, int? element) { return input != null ? input[element??0] : default; }"))
        Append(@class_definitions,Concat(@string_helper.Indentation(1),"private static void Append<T>(List<T>? input, T element) { input?.Add(element); }"))
        Append(@class_definitions,Concat(@string_helper.Indentation(1),"private static void ClearMap<T>(Dictionary<string, T>? input) { input?.Clear();  }"))
        Append(@class_definitions,Concat(@string_helper.Indentation(1),"private static void SetKV<T>(Dictionary<string, T>? input, string? key, T element) { input?.Add(key??\"\", element); }"))
        Append(@class_definitions,Concat(@string_helper.Indentation(1),"private static List<string?>? Keys<T>(Dictionary<string, T>? input) { return new List<string?>(input?.Keys?.ToList()??new List<string>()); }"))
        Append(@class_definitions,Concat(@string_helper.Indentation(1),"private static bool? HasKV<T>(Dictionary<string, T>? input, string? key) { return input?.ContainsKey(key??\"\"); }"))
        Append(@class_definitions,Concat(@string_helper.Indentation(1),"private static T? GetKV<T>(Dictionary<string, T>? input, string? key) { return input != null ? input[key??\"\"] : default; }"))
        Append(@class_definitions,Concat(@string_helper.Indentation(1),"private static int? Length(string? input) { return input?.Length;  }"))
        Append(@class_definitions,Concat(@string_helper.Indentation(1),"private static string? At(string? input, int? index) { return input?.Length > index ? input?.Substring(index??0, 1) : \"\";  }"))
        Append(@class_definitions,Concat(@string_helper.Indentation(1),"private static int? IntAt(string? input, int? index) { return input?.Length > index ? (input[index??0] + 255 % 255) : 0;  }"))
        Append(@class_definitions,Concat(@string_helper.Indentation(1),"private static string? Concat(string? left, string? right) { return left + right; }"))
        Append(@class_definitions,Concat(@string_helper.Indentation(1),"private static bool AsBoolean(bool value) { return value; }"))
        Append(@class_definitions,Concat(@string_helper.Indentation(1),"private static bool AsBoolean<T>(T? value) { return value != null && !value.Equals(false); }"))
    end

    def StripLast(input)
        result = ""
        index = Length(input)-1
        while (index>0)
            index = index-1
            result = Concat(At(input,index),result)
        end
        return result
    end

    def GetDefault(csharp_type)
        if (csharp_type=="int?")
            return "0"
        end
        if (csharp_type=="string?")
            return "\"\""
        end
        if (csharp_type=="bool?")
            return "false"
        end
        if (csharp_type=="float?")
            return "0.0"
        end
        if (csharp_type=="void")
            return "void"
        end
        if (@string_helper.BeginsWith("Dictionary<string,",csharp_type))
            return Concat(Concat("new ",self.StripLast(csharp_type)),"()")
        end
        if (@string_helper.BeginsWith("List<",csharp_type))
            return Concat(Concat("new ",self.StripLast(csharp_type)),"()")
        end
        return "null"
    end

    def MakeParametersString(self_type, parameters)
        result = "("
        parameters_index = 0
        while (parameters_index<Size(parameters))
            parameter = Element(parameters,parameters_index)
            if (parameters_index!=0)
                result = Concat(result,",")
            end
            result = Concat(Concat(Concat(result,parameter.ReservedPrefixGetType())," "),parameter.GetName())
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
