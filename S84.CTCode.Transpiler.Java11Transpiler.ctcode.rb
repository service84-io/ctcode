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
module JAVA11TRANSPILER
module CTCODE

class Java11Transpiler < ::S84::CTCODE::TRANSPILER::STANDARDSTRUCTURE::CTCODE::TargetSpecificFunctions
    def initialize()
        @system = nil
        @c_t_code_file = nil
        @base_name = ""
        @logger = nil
        @string_helper = nil
        @imports = Array.new()
        @current_interface = ""
        @interface_definition = Array.new()
        @current_class = ""
        @class_definition = Array.new()
        @class_init = Array.new()
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
            return "this"
        end
        if (value=="nothing")
            return "null"
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
                result = Concat(result,", ")
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

    def ConvertString(literal)
        return Concat(Concat("\"",literal),"\"")
    end

    def UnaryOperator(op, r_value)
        if (op=="!")
            return Concat(Concat("(! AsBoolean(",r_value),"))")
        end
        return r_value
    end

    def BinaryOperator(op, r_value_l, r_value_r)
        if (op=="+")
            return Concat(Concat(Concat(Concat("(",r_value_l),"+"),r_value_r),")")
        end
        if (op=="-")
            return Concat(Concat(Concat(Concat("(",r_value_l),"-"),r_value_r),")")
        end
        if (op=="<=")
            return Concat(Concat(Concat(Concat("(",r_value_l),"<="),r_value_r),")")
        end
        if (op==">=")
            return Concat(Concat(Concat(Concat("(",r_value_l),">="),r_value_r),")")
        end
        if (op=="==")
            return Concat(Concat(Concat(Concat("Equals(",r_value_l),","),r_value_r),")")
        end
        if (op=="!=")
            return Concat(Concat(Concat(Concat("!Equals(",r_value_l),","),r_value_r),")")
        end
        if (op=="<")
            return Concat(Concat(Concat(Concat("(",r_value_l),"<"),r_value_r),")")
        end
        if (op==">")
            return Concat(Concat(Concat(Concat("(",r_value_l),">"),r_value_r),")")
        end
        if (op=="||")
            return Concat(Concat(Concat(Concat("(AsBoolean(",r_value_l),") || AsBoolean("),r_value_r),"))")
        end
        if (op=="&&")
            return Concat(Concat(Concat(Concat("(AsBoolean(",r_value_l),") && AsBoolean("),r_value_r),"))")
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
            result = Concat(Concat("java.util.ArrayList<",result),">")
            dimensions = dimensions-1
        end
        return result
    end

    def GetMapType(singleton_type)
        return Concat(Concat("java.util.HashMap<java.lang.String, ",singleton_type),">")
    end

    def GetPrimativeType(c_t_type)
        if (c_t_type=="int")
            return "int"
        end
        if (c_t_type=="string")
            return "java.lang.String"
        end
        if (c_t_type=="bool")
            return "boolean"
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
                result = Concat(@string_helper.ToLower(name_part),result)
            end
        end
        return result
    end

    def BeginProcessingCTCodeFile()
        ClearList(@imports)
        @current_interface = ""
        ClearList(@interface_definition)
        @current_class = ""
        ClearList(@class_definition)
        ClearList(@class_init)
        ClearList(@class_members)
    end

    def ProcessExdef(exdef)
        Append(@imports,Concat(Concat("import ",@string_helper.ToLower(exdef)),".*;"))
    end

    def ProcessUnmanagedType(unmanaged_type)
    end

    def BeginProcessingInterface(interface_name)
        ClearList(@interface_definition)
        @current_interface = interface_name
    end

    def ProcessInterfaceFunctionDeclaration(return_type, function_name, parameters)
        Append(@interface_definition,Concat(Concat(Concat(Concat(Concat(@string_helper.Indentation(1),return_type)," "),function_name),self.MakeParametersString(parameters)),";"))
    end

    def FinishProcessingInterface(interface_name)
        destination = @system.OpenFileWriter(Concat(Concat(Concat(@string_helper.DotToSlash(@string_helper.ToLower(@base_name)),"/"),@current_interface),".java"))
        destination.WriteLine(Concat(Concat("package ",@string_helper.ToLower(@base_name)),";"))
        destination.WriteLine("")
        if (Size(@imports)>0)
            @string_helper.WriteLines(destination,@imports)
            destination.WriteLine("")
        end
        destination.WriteLine(Concat(Concat("public interface ",interface_name)," {"))
        @string_helper.WriteLines(destination,@interface_definition)
        destination.WriteLine("}")
        @current_interface = ""
    end

    def BeginProcessingClass(class_name, implementing)
        ClearList(@class_definition)
        ClearList(@class_init)
        ClearList(@class_members)
        @current_class = class_name
        Append(@class_init,Concat(Concat(Concat(@string_helper.Indentation(1),"public "),class_name),"()"))
        Append(@class_init,Concat(@string_helper.Indentation(1),"{"))
    end

    def BeginProcessingClassFunctionDefinition(return_type, function_name, parameters)
        Append(@class_definition,Concat(Concat(Concat(Concat(Concat(@string_helper.Indentation(1),"public "),return_type)," "),function_name),self.MakeParametersString(parameters)))
    end

    def BeginProcessCodeBlock(indent)
        Append(@class_definition,Concat(@string_helper.Indentation(indent),"{"))
    end

    def FinishProcessCodeBlock(indent)
        Append(@class_definition,Concat(@string_helper.Indentation(indent),"}"))
    end

    def BeginProcessConditional(indent, r_value)
        Append(@class_definition,Concat(Concat(Concat(@string_helper.Indentation(indent),"if (AsBoolean("),r_value),"))"))
    end

    def ProcessElse(indent)
        Append(@class_definition,Concat(@string_helper.Indentation(indent),"else"))
    end

    def FinishProcessConditional(indent, r_value)
    end

    def BeginProcessLoop(indent, r_value)
        Append(@class_definition,Concat(Concat(Concat(@string_helper.Indentation(indent),"while (AsBoolean("),r_value),"))"))
    end

    def FinishProcessLoop(indent, r_value)
    end

    def ProcessRtn(indent, r_value)
        Append(@class_definition,Concat(Concat(Concat(@string_helper.Indentation(indent),"return "),r_value),";"))
    end

    def ProcessDeclaration(indent, type, l_value, r_value)
        if (r_value=="")
            r_value = self.GetDefault(type)
        end
        Append(@class_definition,Concat(Concat(Concat(Concat(Concat(Concat(@string_helper.Indentation(indent),type)," "),l_value)," = "),r_value),";"))
    end

    def ProcessAssignment(indent, l_value, r_value)
        Append(@class_definition,Concat(Concat(Concat(Concat(@string_helper.Indentation(indent),l_value)," = "),r_value),";"))
    end

    def ProcessCall(indent, call)
        Append(@class_definition,Concat(Concat(@string_helper.Indentation(indent),call),";"))
    end

    def FinishProcessingClassFunctionDefinition(return_type, function_name, parameters)
        Append(@class_definition,"")
    end

    def ProcessClassMemberDeclaration(member_type, member_name)
        Append(@class_init,Concat(Concat(Concat(Concat(Concat(@string_helper.Indentation(2),"this."),member_name)," = "),self.GetDefault(member_type)),";"))
        Append(@class_members,Concat(Concat(Concat(Concat(Concat(@string_helper.Indentation(1),"private "),member_type)," "),member_name),";"))
    end

    def FinishProcessingClass(class_name, implementing)
        destination = @system.OpenFileWriter(Concat(Concat(Concat(@string_helper.DotToSlash(@string_helper.ToLower(@base_name)),"/"),@current_class),".java"))
        destination.WriteLine(Concat(Concat("package ",@string_helper.ToLower(@base_name)),";"))
        destination.WriteLine("")
        if (Size(@imports)>0)
            @string_helper.WriteLines(destination,@imports)
            destination.WriteLine("")
        end
        if (implementing=="")
            destination.WriteLine(Concat(Concat("public class ",class_name)," {"))
        else
            destination.WriteLine(Concat(Concat(Concat(Concat("public class ",class_name)," implements "),implementing)," {"))
        end
        @string_helper.WriteLines(destination,@class_init)
        destination.WriteLine(Concat(@string_helper.Indentation(1),"}"))
        destination.WriteLine("")
        @string_helper.WriteLines(destination,@class_definition)
        if (Size(@class_members)>0)
            @string_helper.WriteLines(destination,@class_members)
            destination.WriteLine("")
        end
        self.WriteCommonFunctions(destination)
        destination.WriteLine("}")
        @current_class = ""
    end

    def WriteCommonFunctions(destination_file)
        destination_file.WriteLine(Concat(@string_helper.Indentation(1),"private static <T> void ClearList(java.util.ArrayList<T> input) { input.clear(); }"))
        destination_file.WriteLine(Concat(@string_helper.Indentation(1),"private static <T> int Size(java.util.ArrayList<T> input) { return input.size(); }"))
        destination_file.WriteLine(Concat(@string_helper.Indentation(1),"private static <T> T Element(java.util.ArrayList<T> input, int element) { return input.get(element); }"))
        destination_file.WriteLine(Concat(@string_helper.Indentation(1),"private static <T> void Append(java.util.ArrayList<T> input, T element) { input.add(element); }"))
        destination_file.WriteLine(Concat(@string_helper.Indentation(1),"private static <T> void ClearMap(java.util.HashMap<java.lang.String, T> input) { input.clear(); }"))
        destination_file.WriteLine(Concat(@string_helper.Indentation(1),"private static <T> void SetKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key, T element) { input.put(key, element); }"))
        destination_file.WriteLine(Concat(@string_helper.Indentation(1),"private static <T> java.util.ArrayList<java.lang.String> Keys(java.util.HashMap<java.lang.String, T> input) { return new java.util.ArrayList<>(input.keySet()); }"))
        destination_file.WriteLine(Concat(@string_helper.Indentation(1),"private static <T> boolean HasKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key) { return input.containsKey(key); }"))
        destination_file.WriteLine(Concat(@string_helper.Indentation(1),"private static <T> T GetKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key) { return input.get(key); }"))
        destination_file.WriteLine(Concat(@string_helper.Indentation(1),"private static int Length(java.lang.String input) { return input.length(); }"))
        destination_file.WriteLine(Concat(@string_helper.Indentation(1),"private static java.lang.String At(java.lang.String input, int index) { try { return input.substring(index, index + 1);} catch(Exception e) { return \"\"; }}"))
        destination_file.WriteLine(Concat(@string_helper.Indentation(1),"private static int IntAt(java.lang.String input, int index) { return (int)input.charAt(index); }"))
        destination_file.WriteLine(Concat(@string_helper.Indentation(1),"private static java.lang.String Concat(java.lang.String left, java.lang.String right) { return left + right; }"))
        destination_file.WriteLine(Concat(@string_helper.Indentation(1),"private static <T extends java.lang.Object> boolean AsBoolean(T value) { return value != null; }"))
        destination_file.WriteLine(Concat(@string_helper.Indentation(1),"private static boolean AsBoolean(boolean value) { return value; }"))
        destination_file.WriteLine(Concat(@string_helper.Indentation(1),"private static boolean Equals(java.lang.String left, java.lang.String right) { return left.equals(right); }"))
        destination_file.WriteLine(Concat(@string_helper.Indentation(1),"private static boolean Equals(boolean left, boolean right) { return left == right; }"))
        destination_file.WriteLine(Concat(@string_helper.Indentation(1),"private static boolean Equals(int left, int right) { return left == right; }"))
        destination_file.WriteLine(Concat(@string_helper.Indentation(1),"private static boolean Equals(float left, float right) { return left == right; }"))
    end

    def FinishProcessingCTCodeFile()
    end

    def GetDefault(java_type)
        if (java_type=="int")
            return "0"
        end
        if (java_type=="java.lang.String")
            return "\"\""
        end
        if (java_type=="boolean")
            return "false"
        end
        if (java_type=="float")
            return "0.0"
        end
        if (java_type=="void")
            return "null"
        end
        if (@string_helper.BeginsWith("java.util.HashMap<java.lang.String",java_type))
            return "new java.util.HashMap<>()"
        end
        if (@string_helper.BeginsWith("java.util.ArrayList<",java_type))
            return "new java.util.ArrayList<>()"
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
