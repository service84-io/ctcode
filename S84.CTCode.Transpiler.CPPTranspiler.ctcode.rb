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
module CPPTRANSPILER
module CTCODE

class CPPTranspiler < ::S84::CTCODE::TRANSPILER::STANDARDSTRUCTURE::CTCODE::TargetSpecificFunctions
    def initialize()
        @system = nil
        @c_t_code_file = nil
        @base_name = ""
        @logger = nil
        @string_helper = nil
        @includes = Array.new()
        @interface_declarations = Array.new()
        @class_declarations = Array.new()
        @current_interface = ""
        @interface_definitions = Array.new()
        @current_class = ""
        @class_definitions = Array.new()
        @class_init = Array.new()
        @class_functions = Array.new()
        @class_members = Array.new()
        @function_definitions = Array.new()
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
        return 0
    end

    def GetCallName(name)
        return @string_helper.SnakeCaseToCamelCase(name)
    end

    def GetVariableName(name)
        value = @string_helper.CamelCaseToSnakeCase(name)
        if (value=="myself")
            return "this"
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
        return result
    end

    def ConvertCall(name_chain, parameters)
        result = Element(name_chain,0)
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
        return Concat(Concat(Concat(Concat("std::shared_ptr<",type),">(new "),type),"())")
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
        return Concat(Concat("std::string(\"",literal),"\")")
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
            result = Concat(Concat("std::vector<",result),">")
            dimensions = dimensions-1
        end
        return result
    end

    def GetMapType(singleton_type)
        return Concat(Concat("std::unordered_map<std::string, ",singleton_type),">")
    end

    def GetPrimativeType(c_t_type)
        if (c_t_type=="int")
            return "int"
        end
        if (c_t_type=="string")
            return "std::string"
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
        return Concat(Concat("OmniPointer<",c_t_type),">")
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
                result = Concat(@string_helper.ToLower(name_part),result)
            end
        end
        return result
    end

    def BeginProcessingCTCodeFile()
        ClearList(@includes)
        ClearList(@interface_declarations)
        ClearList(@class_declarations)
        @current_interface = ""
        ClearList(@interface_definitions)
        @current_class = ""
        ClearList(@class_definitions)
        ClearList(@class_init)
        ClearList(@class_functions)
        ClearList(@class_members)
        ClearList(@function_definitions)
    end

    def ProcessExdef(exdef)
        Append(@includes,Concat("#include \"",Concat(exdef,".hpp\"")))
    end

    def ProcessUnmanagedType(unmanaged_type)
    end

    def BeginProcessingInterface(interface_name)
        @current_interface = interface_name
        Append(@interface_declarations,Concat(Concat("class ",interface_name),";"))
        Append(@interface_definitions,Concat(Concat("class ",interface_name)," {"))
        Append(@interface_definitions,"public:")
    end

    def ProcessInterfaceFunctionDeclaration(return_type, function_name, parameters)
        Append(@interface_definitions,Concat(Concat(Concat(Concat(Concat(Concat(@string_helper.Indentation(1),"virtual "),return_type)," "),function_name),self.MakeParametersString(parameters))," = 0;"))
    end

    def FinishProcessingInterface(interface_name)
        Append(@interface_definitions,"};")
        Append(@interface_definitions,"")
        @current_interface = ""
    end

    def BeginProcessingClass(class_name, implementing)
        @current_class = class_name
        Append(@class_declarations,Concat(Concat("class ",class_name),";"))
        if (implementing=="")
            Append(@class_definitions,Concat(Concat("class ",class_name)," {"))
        else
            Append(@class_definitions,Concat(Concat(Concat(Concat("class ",class_name)," : public "),implementing)," {"))
        end
        Append(@class_definitions,"public:")
        Append(@class_definitions,Concat(Concat(@string_helper.Indentation(1),class_name),"();"))
        Append(@class_definitions,Concat(Concat(Concat(@string_helper.Indentation(1),"inline ~"),class_name),"() {}"))
        Append(@class_definitions,"")
        ClearList(@class_init)
        ClearList(@class_functions)
        ClearList(@class_members)
        Append(@class_init,Concat(Concat(Concat(class_name,"::"),class_name),"()"))
        Append(@class_init,"{")
    end

    def BeginProcessingClassFunctionDefinition(return_type, function_name, parameters)
        Append(@class_definitions,Concat(Concat(Concat(Concat(Concat(@string_helper.Indentation(1),return_type)," "),function_name),self.MakeParametersString(parameters)),";"))
        Append(@class_functions,Concat(Concat(Concat(Concat(Concat(return_type," "),@current_class),"::"),function_name),self.MakeParametersString(parameters)))
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
        if (r_value=="")
            Append(@class_functions,Concat(Concat(Concat(Concat(@string_helper.Indentation(indent),type)," "),l_value),";"))
        else
            Append(@class_functions,Concat(Concat(Concat(Concat(Concat(Concat(@string_helper.Indentation(indent),type)," "),l_value)," = "),r_value),";"))
        end
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
        default_value = self.GetDefault(member_type)
        if (default_value!="")
            Append(@class_init,Concat(Concat(Concat(Concat(Concat(@string_helper.Indentation(1),"this->"),member_name)," = "),default_value),";"))
        else
            Append(@class_init,Concat(Concat(Concat(Concat(Concat(@string_helper.Indentation(1),"/*this->"),member_name)," = "),"NO_DEFAULT"),";*/"))
        end
        Append(@class_members,Concat(Concat(Concat(Concat(@string_helper.Indentation(1),member_type)," "),member_name),";"))
    end

    def FinishProcessingClass(class_name, implementing)
        if (Size(@class_members)>0)
            Append(@class_definitions,"")
            Append(@class_definitions,"private:")
            class_members_index = 0
            while (class_members_index<Size(@class_members))
                line = Element(@class_members,class_members_index)
                Append(@class_definitions,line)
                class_members_index = class_members_index+1
            end
        end
        Append(@class_definitions,"};")
        Append(@class_definitions,"")
        Append(@class_init,"}")
        Append(@class_init,"")
        class_init_index = 0
        while (class_init_index<Size(@class_init))
            line = Element(@class_init,class_init_index)
            Append(@function_definitions,line)
            class_init_index = class_init_index+1
        end
        class_functions_index = 0
        while (class_functions_index<Size(@class_functions))
            line = Element(@class_functions,class_functions_index)
            Append(@function_definitions,line)
            class_functions_index = class_functions_index+1
        end
        @current_class = ""
    end

    def WriteCommonFunctions(destination)
        destination.WriteLine("#ifndef CTCODE_COMMON_FUNCTIONS_VERSION_1")
        destination.WriteLine("#define CTCODE_COMMON_FUNCTIONS_VERSION_1")
        destination.WriteLine("template<typename T>")
        destination.WriteLine("class OmniPointer")
        destination.WriteLine("{")
        destination.WriteLine("public:")
        destination.WriteLine("    OmniPointer() { value_raw = NULL; }")
        destination.WriteLine("    OmniPointer(T* value) { value_raw = value; }")
        destination.WriteLine("    template<typename U>")
        destination.WriteLine("    OmniPointer(U* value) { value_raw = value; }")
        destination.WriteLine("    OmniPointer(std::shared_ptr<T> value) { value_raw = NULL; value_shared = value; }")
        destination.WriteLine("    template<typename U>")
        destination.WriteLine("    OmniPointer(std::shared_ptr<U> value) { value_raw = NULL; value_shared = value; }")
        destination.WriteLine("    template<typename U>")
        destination.WriteLine("    OmniPointer(OmniPointer<U> value) { value_raw = value.value_raw; value_shared = value.value_shared; }")
        destination.WriteLine("")
        destination.WriteLine("    operator bool()")
        destination.WriteLine("    {")
        destination.WriteLine("        if (value_raw) return true;")
        destination.WriteLine("        return value_shared.get() != NULL;")
        destination.WriteLine("    }")
        destination.WriteLine("    T& operator*()")
        destination.WriteLine("    {")
        destination.WriteLine("        if (value_raw) return *value_raw;")
        destination.WriteLine("        return *value_shared;")
        destination.WriteLine("    }")
        destination.WriteLine("    T* operator->()")
        destination.WriteLine("    {")
        destination.WriteLine("        if (value_raw) return value_raw;")
        destination.WriteLine("        return value_shared.get();")
        destination.WriteLine("    }")
        destination.WriteLine("    T* raw()")
        destination.WriteLine("    {")
        destination.WriteLine("        if (value_raw) return value_raw;")
        destination.WriteLine("        return value_shared.get();")
        destination.WriteLine("    }")
        destination.WriteLine("")
        destination.WriteLine("    T* value_raw;")
        destination.WriteLine("    std::shared_ptr<T> value_shared;")
        destination.WriteLine("};")
        destination.WriteLine("")
        destination.WriteLine("template<typename T>")
        destination.WriteLine("inline std::vector<T*> UnwrapOmniList(std::vector<OmniPointer<T>> input) {")
        destination.WriteLine("	std::vector<T*> result;")
        destination.WriteLine("	for (typename std::vector<OmniPointer<T>>::iterator index = input.begin();index != input.end();index++) {")
        destination.WriteLine("		result.push_back(index->raw());")
        destination.WriteLine("	}")
        destination.WriteLine("	return result;")
        destination.WriteLine("};")
        destination.WriteLine("template<typename T>")
        destination.WriteLine("inline void ClearList(std::vector<T>& input) { input.clear(); };")
        destination.WriteLine("template<typename T>")
        destination.WriteLine("inline int Size(const std::vector<T>& input) { return input.size(); };")
        destination.WriteLine("template<typename T>")
        destination.WriteLine("inline T Element(const std::vector<T>& input, int element) { return input.at(element); };")
        destination.WriteLine("template<typename T>")
        destination.WriteLine("inline void Append(std::vector<T>& input, T element) { input.push_back(element); };")
        destination.WriteLine("template<typename T>")
        destination.WriteLine("inline void ClearMap(std::unordered_map<std::string, T>& input) { input.clear(); };")
        destination.WriteLine("template<typename T>")
        destination.WriteLine("inline void SetKV(std::unordered_map<std::string, T>& input, const std::string& key, T element)")
        destination.WriteLine("{")
        destination.WriteLine("    input.erase(key);")
        destination.WriteLine("    input.insert(std::pair<std::string, T>(key, element));")
        destination.WriteLine("}")
        destination.WriteLine("template<typename T>")
        destination.WriteLine("inline std::vector<std::string> Keys(const std::unordered_map<std::string, T>& input)")
        destination.WriteLine("{")
        destination.WriteLine("    std::vector<std::string> result;")
        destination.WriteLine("    for(typename std::unordered_map<std::string, T>::const_iterator index = input.begin();index != input.end();index++) {")
        destination.WriteLine("        result.push_back(index->first);")
        destination.WriteLine("    }")
        destination.WriteLine("    return result;")
        destination.WriteLine("}")
        destination.WriteLine("template<typename T>")
        destination.WriteLine("inline bool HasKV(const std::unordered_map<std::string, T>& input, const std::string& key)")
        destination.WriteLine("{")
        destination.WriteLine("    typename std::unordered_map<std::string, T>::const_iterator beginning = input.find(key);")
        destination.WriteLine("    return beginning != input.end();")
        destination.WriteLine("}")
        destination.WriteLine("template<typename T>")
        destination.WriteLine("inline T GetKV(const std::unordered_map<std::string, T>& input, const std::string& key) { return input.at(key); }")
        destination.WriteLine("inline int Length(const std::string& input) { return (int)input.length(); };")
        destination.WriteLine("inline std::string At(const std::string& input, int index) { return input.substr(index, 1); };")
        destination.WriteLine("inline int IntAt(const std::string& input, int index) { return (input.at(index) + 256) % 256; };")
        destination.WriteLine("inline std::string Concat(const std::string& left, const std::string& right) { return left + right; };")
        destination.WriteLine("#endif")
    end

    def WriteBeginingGuard(file)
        guard_name = @string_helper.ToUpper(@string_helper.StripDot(Concat(@base_name,"_H")))
        file.WriteLine(Concat("#ifndef ",guard_name))
        file.WriteLine(Concat("#define ",guard_name))
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
            file.WriteLine(Concat(Concat("namespace ",@string_helper.ToLower(base_name_token))," {"))
            base_name_tokens_index = base_name_tokens_index+1
        end
    end

    def WriteEndingNamespace(file)
        base_name_tokens = self.TokenizeBaseName(@base_name)
        base_name_tokens_index = 0
        while (base_name_tokens_index<Size(base_name_tokens))
            base_name_token = Element(base_name_tokens,base_name_tokens_index)
            file.WriteLine("};")
            base_name_tokens_index = base_name_tokens_index+1
        end
    end

    def WriteEndingGuard(file)
        file.WriteLine("#endif")
    end

    def FinishProcessingCTCodeFile()
        header_file_name = Concat(@base_name,".hpp")
        header_file = @system.OpenFileWriter(header_file_name)
        source_file_name = Concat(@base_name,".cpp")
        source_file = @system.OpenFileWriter(source_file_name)
        self.WriteBeginingGuard(header_file)
        header_file.WriteLine("")
        if (Size(@includes)>0)
            @string_helper.WriteLines(header_file,@includes)
            header_file.WriteLine("")
        end
        header_file.WriteLine("#include <cstring>")
        header_file.WriteLine("#include <list>")
        header_file.WriteLine("#include <unordered_map>")
        header_file.WriteLine("#include <memory>")
        header_file.WriteLine("#include <string>")
        header_file.WriteLine("#include <vector>")
        header_file.WriteLine("")
        self.WriteCommonFunctions(header_file)
        header_file.WriteLine("")
        self.WriteBeginingNamespace(header_file)
        header_file.WriteLine("")
        if (Size(@interface_declarations)>0)
            @string_helper.WriteLines(header_file,@interface_declarations)
            header_file.WriteLine("")
        end
        if (Size(@class_declarations)>0)
            @string_helper.WriteLines(header_file,@class_declarations)
            header_file.WriteLine("")
        end
        if (Size(@interface_definitions)>0)
            @string_helper.WriteLines(header_file,@interface_definitions)
        end
        @string_helper.WriteLines(header_file,@class_definitions)
        self.WriteEndingNamespace(header_file)
        header_file.WriteLine("")
        self.WriteEndingGuard(header_file)
        source_file.WriteLine(Concat(Concat("#include \"",@base_name),".hpp\""))
        source_file.WriteLine("")
        self.WriteBeginingNamespace(source_file)
        source_file.WriteLine("")
        if (Size(@function_definitions)>0)
            @string_helper.WriteLines(source_file,@function_definitions)
            source_file.WriteLine("")
        end
        self.WriteEndingNamespace(source_file)
    end

    def GetDefault(cpp_type)
        if (cpp_type=="int")
            return "0"
        end
        if (cpp_type=="std::string")
            return "\"\""
        end
        if (cpp_type=="bool")
            return "false"
        end
        if (cpp_type=="float")
            return "0.0"
        end
        if (cpp_type=="void")
            return "NULL"
        end
        if (@string_helper.BeginsWith("std::unordered_map<std::string, ",cpp_type))
            return ""
        end
        if (@string_helper.BeginsWith("std::vector<",cpp_type))
            return ""
        end
        return "NULL"
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
