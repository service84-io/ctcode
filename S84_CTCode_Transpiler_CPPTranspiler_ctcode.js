import * as S84_CTCode_dbnf_ctcode from "./S84_CTCode_dbnf_ctcode.js"
import * as S84_CTCode_System_ctcode from "./S84_CTCode_System_ctcode.js"
import * as S84_CTCode_Transpiler_StandardStructure_ctcode from "./S84_CTCode_Transpiler_StandardStructure_ctcode.js"
import * as S84_CTCode_Transpiler_StringHelper_ctcode from "./S84_CTCode_Transpiler_StringHelper_ctcode.js"

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

export class CPPTranspiler {
    constructor() {
        this.system = null
        this.c_t_code_file = null
        this.base_name = ""
        this.logger = null
        this.string_helper = null
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

    Initialize()
    {
        this.string_helper = new S84_CTCode_Transpiler_StringHelper_ctcode.StringHelper()
    }

    SetSystem(system)
    {
        this.system = system
    }

    SetCTCodeFile(c_t_code_file)
    {
        this.c_t_code_file = c_t_code_file
    }

    SetBaseName(base_name)
    {
        this.base_name = base_name
    }

    SetLogger(logger)
    {
        this.logger = logger
    }

    GetBaseIndentation()
    {
        return 0
    }

    GetCallName(name)
    {
        return this.string_helper.SnakeCaseToCamelCase(name)
    }

    GetVariableName(name)
    {
        var value = this.string_helper.CamelCaseToSnakeCase(name)
        if (value=="myself")
        {
            return "this"
        }
        return value
    }

    GetVariableChain(name_parts)
    {
        var delimiter = "->"
        var first_name = Element(name_parts,0)
        var result = this.GetVariableName(first_name)
        var name_parts_index = 1
        while (name_parts_index<Size(name_parts))
        {
            var name = Element(name_parts,name_parts_index)
            result = Concat(Concat(result,delimiter),this.GetVariableName(name))
            name_parts_index = name_parts_index+1
        }
        return result
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
        return this.string_helper.SnakeCaseToCamelCase(name)
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

    GetDefinedType(c_t_type)
    {
        return Concat(Concat("OmniPointer<",c_t_type),">")
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
                result = Concat(this.string_helper.ToLower(name_part),result)
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
        Append(this.interface_definitions,Concat(Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(1),"virtual "),return_type)," "),function_name),this.MakeParametersString(parameters))," = 0;"))
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
        Append(this.class_definitions,Concat(Concat(this.string_helper.Indentation(1),class_name),"();"))
        Append(this.class_definitions,Concat(Concat(Concat(this.string_helper.Indentation(1),"inline ~"),class_name),"() {}"))
        Append(this.class_definitions,"")
        ClearList(this.class_init)
        ClearList(this.class_functions)
        ClearList(this.class_members)
        Append(this.class_init,Concat(Concat(Concat(class_name,"::"),class_name),"()"))
        Append(this.class_init,"{")
    }

    BeginProcessingClassFunctionDefinition(return_type, function_name, parameters)
    {
        Append(this.class_definitions,Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(1),return_type)," "),function_name),this.MakeParametersString(parameters)),";"))
        Append(this.class_functions,Concat(Concat(Concat(Concat(Concat(return_type," "),this.current_class),"::"),function_name),this.MakeParametersString(parameters)))
    }

    BeginProcessCodeBlock(indent)
    {
        Append(this.class_functions,Concat(this.string_helper.Indentation(indent),"{"))
    }

    FinishProcessCodeBlock(indent)
    {
        Append(this.class_functions,Concat(this.string_helper.Indentation(indent),"}"))
    }

    BeginProcessConditional(indent, r_value)
    {
        Append(this.class_functions,Concat(Concat(Concat(this.string_helper.Indentation(indent),"if ("),r_value),")"))
    }

    ProcessElse(indent)
    {
        Append(this.class_functions,Concat(this.string_helper.Indentation(indent),"else"))
    }

    FinishProcessConditional(indent, r_value)
    {
    }

    BeginProcessLoop(indent, r_value)
    {
        Append(this.class_functions,Concat(Concat(Concat(this.string_helper.Indentation(indent),"while ("),r_value),")"))
    }

    FinishProcessLoop(indent, r_value)
    {
    }

    ProcessRtn(indent, r_value)
    {
        Append(this.class_functions,Concat(Concat(Concat(this.string_helper.Indentation(indent),"return "),r_value),";"))
    }

    ProcessDeclaration(indent, type, l_value, r_value)
    {
        if (r_value=="")
        {
            r_value = this.GetDefault(type)
        }
        if (r_value=="")
        {
            Append(this.class_functions,Concat(Concat(Concat(Concat(this.string_helper.Indentation(indent),type)," "),l_value),";"))
        }
        else
        {
            Append(this.class_functions,Concat(Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(indent),type)," "),l_value)," = "),r_value),";"))
        }
    }

    ProcessAssignment(indent, l_value, r_value)
    {
        Append(this.class_functions,Concat(Concat(Concat(Concat(this.string_helper.Indentation(indent),l_value)," = "),r_value),";"))
    }

    ProcessCall(indent, call)
    {
        Append(this.class_functions,Concat(Concat(this.string_helper.Indentation(indent),call),";"))
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
            Append(this.class_init,Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(1),"this->"),member_name)," = "),default_value),";"))
        }
        else
        {
            Append(this.class_init,Concat(Concat(Concat(Concat(Concat(this.string_helper.Indentation(1),"/*this->"),member_name)," = "),"NO_DEFAULT"),";*/"))
        }
        Append(this.class_members,Concat(Concat(Concat(Concat(this.string_helper.Indentation(1),member_type)," "),member_name),";"))
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
        var guard_name = this.string_helper.ToUpper(this.string_helper.StripDot(Concat(this.base_name,"_H")))
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
            file.WriteLine(Concat(Concat("namespace ",this.string_helper.ToLower(base_name_token))," {"))
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
            this.string_helper.WriteLines(header_file,this.includes)
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
            this.string_helper.WriteLines(header_file,this.interface_declarations)
            header_file.WriteLine("")
        }
        if (Size(this.class_declarations)>0)
        {
            this.string_helper.WriteLines(header_file,this.class_declarations)
            header_file.WriteLine("")
        }
        if (Size(this.interface_definitions)>0)
        {
            this.string_helper.WriteLines(header_file,this.interface_definitions)
        }
        this.string_helper.WriteLines(header_file,this.class_definitions)
        this.WriteEndingNamespace(header_file)
        header_file.WriteLine("")
        this.WriteEndingGuard(header_file)
        source_file.WriteLine(Concat(Concat("#include \"",this.base_name),".hpp\""))
        source_file.WriteLine("")
        this.WriteBeginingNamespace(source_file)
        source_file.WriteLine("")
        if (Size(this.function_definitions)>0)
        {
            this.string_helper.WriteLines(source_file,this.function_definitions)
            source_file.WriteLine("")
        }
        this.WriteEndingNamespace(source_file)
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
        if (this.string_helper.BeginsWith("std::unordered_map<std::string, ",cpp_type))
        {
            return ""
        }
        if (this.string_helper.BeginsWith("std::vector<",cpp_type))
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
}

