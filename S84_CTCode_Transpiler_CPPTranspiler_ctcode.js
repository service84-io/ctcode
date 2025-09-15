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

export class CPPTranspiler {
    constructor() {
        this.system = null
        this.c_t_code_file = null
        this.base_name = ""
        this.operator_precedent = []
        this.logger = null
        this.includes = []
        this.interface_declarations = []
        this.class_declarations = []
        this.current_interface = ""
        this.interface_definitions = []
        this.current_class = ""
        this.class_definitions = []
        this.class_init = []
        this.class_functions = []
        this.class_members = []
        this.function_definitions = []
    }

    GetBaseIndentation()
    {
        return 0
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
                return "this"
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
        var accessor = "->"
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
            result = Concat(Concat(result,"->"),name_part)
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
        return Concat(Concat(Concat(Concat("std::shared_ptr<",type),">(new "),type),"())")
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
        return Concat(Concat("std::string(\"",literal),"\")")
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
            result = Concat(Concat("std::vector<",result),">")
            dimensions = dimensions-1
        }
        return result
    }

    GetMapType(singleton_type)
    {
        return Concat(Concat("std::unordered_map<std::string, ",singleton_type),">")
    }

    GetPrimativeType(c_t_type)
    {
        if (c_t_type=="int")
        {
            return "int"
        }
        if (c_t_type=="string")
        {
            return "std::string"
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
        var delimiter = "::"
        var name_parts_index = Size(name_parts)-1
        var last_package_index = Size(name_parts)-2
        var type_part = Element(name_parts,name_parts_index)
        var result = this.GetTypeName(type_part)
        if (name_parts_index>0)
        {
            result = Concat(delimiter,result)
            while (name_parts_index>0)
            {
                name_parts_index = name_parts_index-1
                var name_part = Element(name_parts,name_parts_index)
                if (name_parts_index!=last_package_index)
                {
                    result = Concat(delimiter,result)
                }
                result = Concat(this.ToLower(name_part.UnParse()),result)
            }
        }
        return result
    }

    BeginProcessingCTCodeFile()
    {
        ClearList(this.includes)
        ClearList(this.interface_declarations)
        ClearList(this.class_declarations)
        this.current_interface = ""
        ClearList(this.interface_definitions)
        this.current_class = ""
        ClearList(this.class_definitions)
        ClearList(this.class_init)
        ClearList(this.class_functions)
        ClearList(this.class_members)
        ClearList(this.function_definitions)
    }

    ProcessExdef(exdef)
    {
        Append(this.includes,Concat("#include \"",Concat(exdef,".hpp\"")))
    }

    ProcessUnmanagedType(unmanaged_type)
    {
        var noop = 0
    }

    BeginProcessingInterface(interface_name)
    {
        this.current_interface = interface_name
        Append(this.interface_declarations,Concat(Concat("class ",interface_name),";"))
        Append(this.interface_definitions,Concat(Concat("class ",interface_name)," {"))
        Append(this.interface_definitions,"public:")
    }

    ProcessInterfaceFunctionDeclaration(return_type, function_name, parameters)
    {
        Append(this.interface_definitions,Concat(Concat(Concat(Concat(Concat(Concat(this.Indentation(1),"virtual "),return_type)," "),function_name),this.MakeParametersString(parameters))," = 0;"))
    }

    FinishProcessingInterface(interface_name)
    {
        Append(this.interface_definitions,"};")
        Append(this.interface_definitions,"")
        this.current_interface = ""
    }

    BeginProcessingClass(class_name, implementing)
    {
        this.current_class = class_name
        Append(this.class_declarations,Concat(Concat("class ",class_name),";"))
        if (implementing=="")
        {
            Append(this.class_definitions,Concat(Concat("class ",class_name)," {"))
        }
        else
        {
            Append(this.class_definitions,Concat(Concat(Concat(Concat("class ",class_name)," : public "),implementing)," {"))
        }
        Append(this.class_definitions,"public:")
        Append(this.class_definitions,Concat(Concat(this.Indentation(1),class_name),"();"))
        Append(this.class_definitions,Concat(Concat(Concat(this.Indentation(1),"inline ~"),class_name),"() {}"))
        Append(this.class_definitions,"")
        ClearList(this.class_init)
        ClearList(this.class_functions)
        ClearList(this.class_members)
        Append(this.class_init,Concat(Concat(Concat(class_name,"::"),class_name),"()"))
        Append(this.class_init,"{")
    }

    BeginProcessingClassFunctionDefinition(return_type, function_name, parameters)
    {
        Append(this.class_definitions,Concat(Concat(Concat(Concat(Concat(this.Indentation(1),return_type)," "),function_name),this.MakeParametersString(parameters)),";"))
        Append(this.class_functions,Concat(Concat(Concat(Concat(Concat(return_type," "),this.current_class),"::"),function_name),this.MakeParametersString(parameters)))
    }

    BeginProcessCodeBlock(indent)
    {
        Append(this.class_functions,Concat(this.Indentation(indent),"{"))
    }

    FinishProcessCodeBlock(indent)
    {
        Append(this.class_functions,Concat(this.Indentation(indent),"}"))
    }

    BeginProcessConditional(indent, r_value)
    {
        Append(this.class_functions,Concat(Concat(Concat(this.Indentation(indent),"if ("),r_value),")"))
    }

    ProcessElse(indent)
    {
        Append(this.class_functions,Concat(this.Indentation(indent),"else"))
    }

    FinishProcessConditional(indent, r_value)
    {
        var noop = 0
    }

    BeginProcessLoop(indent, r_value)
    {
        Append(this.class_functions,Concat(Concat(Concat(this.Indentation(indent),"while ("),r_value),")"))
    }

    FinishProcessLoop(indent, r_value)
    {
        var noop = 0
    }

    ProcessRtn(indent, r_value)
    {
        Append(this.class_functions,Concat(Concat(Concat(this.Indentation(indent),"return "),r_value),";"))
    }

    ProcessDeclaration(indent, type, l_value, r_value)
    {
        if (r_value=="")
        {
            r_value = this.GetDefault(type)
        }
        if (r_value=="")
        {
            Append(this.class_functions,Concat(Concat(Concat(Concat(this.Indentation(indent),type)," "),l_value),";"))
        }
        else
        {
            Append(this.class_functions,Concat(Concat(Concat(Concat(Concat(Concat(this.Indentation(indent),type)," "),l_value)," = "),r_value),";"))
        }
    }

    ProcessAssignment(indent, l_value, r_value)
    {
        Append(this.class_functions,Concat(Concat(Concat(Concat(this.Indentation(indent),l_value)," = "),r_value),";"))
    }

    ProcessCall(indent, call)
    {
        Append(this.class_functions,Concat(Concat(this.Indentation(indent),call),";"))
    }

    FinishProcessingClassFunctionDefinition(return_type, function_name, parameters)
    {
        Append(this.class_functions,"")
    }

    ProcessClassMemberDeclaration(member_type, member_name)
    {
        var default_value = this.GetDefault(member_type)
        if (default_value!="")
        {
            Append(this.class_init,Concat(Concat(Concat(Concat(Concat(this.Indentation(1),"this->"),member_name)," = "),default_value),";"))
        }
        else
        {
            Append(this.class_init,Concat(Concat(Concat(Concat(Concat(this.Indentation(1),"/*this->"),member_name)," = "),"NO_DEFAULT"),";*/"))
        }
        Append(this.class_members,Concat(Concat(Concat(Concat(this.Indentation(1),member_type)," "),member_name),";"))
    }

    FinishProcessingClass(class_name, implementing)
    {
        if (Size(this.class_members)>0)
        {
            Append(this.class_definitions,"")
            Append(this.class_definitions,"private:")
            var class_members_index = 0
            while (class_members_index<Size(this.class_members))
            {
                var line = Element(this.class_members,class_members_index)
                Append(this.class_definitions,line)
                class_members_index = class_members_index+1
            }
        }
        Append(this.class_definitions,"};")
        Append(this.class_definitions,"")
        Append(this.class_init,"}")
        Append(this.class_init,"")
        var class_init_index = 0
        while (class_init_index<Size(this.class_init))
        {
            var line = Element(this.class_init,class_init_index)
            Append(this.function_definitions,line)
            class_init_index = class_init_index+1
        }
        var class_functions_index = 0
        while (class_functions_index<Size(this.class_functions))
        {
            var line = Element(this.class_functions,class_functions_index)
            Append(this.function_definitions,line)
            class_functions_index = class_functions_index+1
        }
        this.current_class = ""
    }

    WriteCommonFunctions(destination)
    {
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
    }

    WriteBeginingGuard(file)
    {
        var guard_name = this.ToUpper(this.StripDot(Concat(this.base_name,"_H")))
        file.WriteLine(Concat("#ifndef ",guard_name))
        file.WriteLine(Concat("#define ",guard_name))
    }

    TokenizeBaseName(name)
    {
        var base_name_tokens = []
        var current_token = ""
        var index = 0
        while (index<Length(name))
        {
            var character = At(name,index)
            if (character==".")
            {
                Append(base_name_tokens,current_token)
                current_token = ""
            }
            else
            {
                current_token = Concat(current_token,character)
            }
            index = index+1
        }
        Append(base_name_tokens,current_token)
        return base_name_tokens
    }

    WriteBeginingNamespace(file)
    {
        var base_name_tokens = this.TokenizeBaseName(this.base_name)
        var base_name_tokens_index = 0
        while (base_name_tokens_index<Size(base_name_tokens))
        {
            var base_name_token = Element(base_name_tokens,base_name_tokens_index)
            file.WriteLine(Concat(Concat("namespace ",this.ToLower(base_name_token))," {"))
            base_name_tokens_index = base_name_tokens_index+1
        }
    }

    WriteEndingNamespace(file)
    {
        var base_name_tokens = this.TokenizeBaseName(this.base_name)
        var base_name_tokens_index = 0
        while (base_name_tokens_index<Size(base_name_tokens))
        {
            var base_name_token = Element(base_name_tokens,base_name_tokens_index)
            file.WriteLine("};")
            base_name_tokens_index = base_name_tokens_index+1
        }
    }

    WriteEndingGuard(file)
    {
        file.WriteLine("#endif")
    }

    FinishProcessingCTCodeFile()
    {
        var header_file_name = Concat(this.base_name,".hpp")
        var header_file = this.system.OpenFileWriter(header_file_name)
        var source_file_name = Concat(this.base_name,".cpp")
        var source_file = this.system.OpenFileWriter(source_file_name)
        this.WriteBeginingGuard(header_file)
        header_file.WriteLine("")
        if (Size(this.includes)>0)
        {
            this.WriteLines(header_file,this.includes)
            header_file.WriteLine("")
        }
        header_file.WriteLine("#include <cstring>")
        header_file.WriteLine("#include <list>")
        header_file.WriteLine("#include <unordered_map>")
        header_file.WriteLine("#include <memory>")
        header_file.WriteLine("#include <string>")
        header_file.WriteLine("#include <vector>")
        header_file.WriteLine("")
        this.WriteCommonFunctions(header_file)
        header_file.WriteLine("")
        this.WriteBeginingNamespace(header_file)
        header_file.WriteLine("")
        if (Size(this.interface_declarations)>0)
        {
            this.WriteLines(header_file,this.interface_declarations)
            header_file.WriteLine("")
        }
        if (Size(this.class_declarations)>0)
        {
            this.WriteLines(header_file,this.class_declarations)
            header_file.WriteLine("")
        }
        if (Size(this.interface_definitions)>0)
        {
            this.WriteLines(header_file,this.interface_definitions)
        }
        this.WriteLines(header_file,this.class_definitions)
        this.WriteEndingNamespace(header_file)
        header_file.WriteLine("")
        this.WriteEndingGuard(header_file)
        source_file.WriteLine(Concat(Concat("#include \"",this.base_name),".hpp\""))
        source_file.WriteLine("")
        this.WriteBeginingNamespace(source_file)
        source_file.WriteLine("")
        if (Size(this.function_definitions)>0)
        {
            this.WriteLines(source_file,this.function_definitions)
            source_file.WriteLine("")
        }
        this.WriteEndingNamespace(source_file)
    }

    BeginsWith(prefix, value)
    {
        if (Length(prefix)>Length(value))
        {
            return false
        }
        var prefix_index = 0
        while (prefix_index<Length(prefix))
        {
            if (At(prefix,prefix_index)!=At(value,prefix_index))
            {
                return false
            }
            prefix_index = prefix_index+1
        }
        return true
    }

    GetDefault(cpp_type)
    {
        if (cpp_type=="int")
        {
            return "0"
        }
        if (cpp_type=="std::string")
        {
            return "\"\""
        }
        if (cpp_type=="bool")
        {
            return "false"
        }
        if (cpp_type=="float")
        {
            return "0.0"
        }
        if (cpp_type=="void")
        {
            return "NULL"
        }
        if (this.BeginsWith("std::unordered_map<std::string, ",cpp_type))
        {
            return ""
        }
        if (this.BeginsWith("std::vector<",cpp_type))
        {
            return ""
        }
        return "NULL"
    }

    MakeParametersString(parameters)
    {
        var result = "("
        var parameters_index = 0
        while (parameters_index<Size(parameters))
        {
            var parameter = Element(parameters,parameters_index)
            if (parameters_index!=0)
            {
                result = Concat(result,", ")
            }
            result = Concat(Concat(Concat(result,parameter.GetType())," "),parameter.GetName())
            parameters_index = parameters_index+1
        }
        result = Concat(result,")")
        return result
    }

    StripDot(input)
    {
        var index = 0
        index = 0
        var result = ""
        result = ""
        while (index<Length(input))
        {
            var character = ""
            character = At(input,index)
            if (character==".")
            {
                result = Concat(result,"_")
            }
            else
            {
                result = Concat(result,character)
            }
            index = index+1
        }
        return result
    }

    WriteLines(destination, lines)
    {
        var lines_index = 0
        while (lines_index<Size(lines))
        {
            var line = Element(lines,lines_index)
            destination.WriteLine(line)
            lines_index = lines_index+1
        }
    }

    Transpile(system, c_t_code_file, base_name)
    {
        ClearList(this.operator_precedent)
        this.PopulateOperatorPrecedent()
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
            return Concat(Concat("OmniPointer<",this.GetQualifiedTypeNameInternal(defined_type.GetName())),">")
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
            r_value_l = this.BinaryOperator(op,r_value_l,r_value_r)
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

