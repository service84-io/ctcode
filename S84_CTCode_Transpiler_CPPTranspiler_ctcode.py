import S84_CTCode_dbnf_ctcode
import S84_CTCode_System_ctcode
import S84_CTCode_Transpiler_ctcode

def ClearList(input: list) -> None: input.clear()
def Size(input: list) -> int: return len(input)
def Element(input: list, element: int ) -> any: return input[element]
def Append(input: list, element: any) -> None: input.append(element)
def ClearMap(input: dict) -> None: input.clear()
def SetKV(input: dict, key: str, element: any) -> None: input[key] = element
def Keys(input: dict) -> list[str]:
    result: list[str] = []
    for key in input.keys():
        result.append(key)
    return result
def HasKV(input: dict, key: str) -> bool: return key in input
def GetKV(input: dict, key: str) -> any: return input[key]
def Length(input: str) -> int: return len(input)
def At(input: str, index: int) -> str: return input[index:index+1]
def IntAt(input: str, index: int) -> int: return ord(input[index:index+1])
def Concat(left: str, right: str) -> str: return left + right

class ParameterDeclaration:
    def __init__(self: 'ParameterDeclaration'):
        self.type: str = ""
        self.name: str = ""

    def GetType(self: 'ParameterDeclaration') -> 'str':
        return self.type

    def SetType(self: 'ParameterDeclaration',input: 'str') -> 'None':
        self.type = input

    def GetName(self: 'ParameterDeclaration') -> 'str':
        return self.name

    def SetName(self: 'ParameterDeclaration',input: 'str') -> 'None':
        self.name = input

class IntegerReference:
    def __init__(self: 'IntegerReference'):
        self.value: int = 0

    def GetValue(self: 'IntegerReference') -> 'int':
        return self.value

    def SetValue(self: 'IntegerReference',value: 'int') -> 'None':
        self.value = value

class CPPTranspiler(S84_CTCode_Transpiler_ctcode.Transpiler):
    def __init__(self: 'CPPTranspiler'):
        self.system: S84_CTCode_System_ctcode.System = None
        self.c_t_code_file: S84_CTCode_dbnf_ctcode.CTCodeFile = None
        self.base_name: str = ""
        self.operator_precedent: list[list[str]] = []
        self.logger: S84_CTCode_System_ctcode.OutputStream = None
        self.includes: list[str] = []
        self.interface_declarations: list[str] = []
        self.class_declarations: list[str] = []
        self.current_interface: str = ""
        self.interface_definitions: list[str] = []
        self.current_class: str = ""
        self.class_definitions: list[str] = []
        self.class_init: list[str] = []
        self.class_functions: list[str] = []
        self.class_members: list[str] = []
        self.function_definitions: list[str] = []

    def GetBaseIndentation(self: 'CPPTranspiler') -> 'int':
        return 0

    def GetCallName(self: 'CPPTranspiler',name: 'S84_CTCode_dbnf_ctcode.Name') -> 'str':
        if name:
            return self.SnakeCaseToCamelCase(name.UnParse())
        else:
            return ""

    def GetVariableName(self: 'CPPTranspiler',name: 'S84_CTCode_dbnf_ctcode.Name') -> 'str':
        if name:
            value: 'str' = self.CamelCaseToSnakeCase(name.UnParse())
            if value=="myself":
                return "this"
            return value
        else:
            return ""

    def GetVariableChainNameTail(self: 'CPPTranspiler',tail: 'S84_CTCode_dbnf_ctcode.NameTail') -> 'str':
        accessor: 'str' = "->"
        if tail:
            return Concat(Concat(accessor,self.GetVariableName(tail.GetName())),self.GetVariableChainNameTail(tail.GetTail()))
        else:
            return ""

    def GetVariableChain(self: 'CPPTranspiler',l_value: 'S84_CTCode_dbnf_ctcode.QualfiedName') -> 'str':
        if l_value:
            return Concat(self.GetVariableName(l_value.GetName()),self.GetVariableChainNameTail(l_value.GetTail()))
        else:
            return ""

    def ConvertCall(self: 'CPPTranspiler',name_chain: 'list[str]',parameters: 'list[str]') -> 'str':
        result: 'str' = Element(name_chain,0)
        name_chain_index: 'int' = 1
        while name_chain_index<Size(name_chain):
            name_part: 'str' = Element(name_chain,name_chain_index)
            result = Concat(Concat(result,"->"),name_part)
            name_chain_index = name_chain_index+1
        result = Concat(result,"(")
        if Size(parameters)>0:
            result = Concat(result,Element(parameters,0))
            parameters_index: 'int' = 1
            while parameters_index<Size(parameters):
                parameter: 'str' = Element(parameters,parameters_index)
                result = Concat(result,",")
                result = Concat(result,parameter)
                parameters_index = parameters_index+1
        result = Concat(result,")")
        return result

    def ConvertAllocate(self: 'CPPTranspiler',type: 'str') -> 'str':
        return Concat(Concat(Concat(Concat("std::shared_ptr<",type),">(new "),type),"())")

    def ConvertByte(self: 'CPPTranspiler',high: 'str',low: 'str') -> 'str':
        return Concat(Concat("0x",high),low)

    def ConvertDecimal(self: 'CPPTranspiler',decimal: 'str') -> 'str':
        return decimal

    def ConvertNumber(self: 'CPPTranspiler',number: 'str') -> 'str':
        return number

    def ConvertBoolean(self: 'CPPTranspiler',boolean: 'str') -> 'str':
        if boolean=="true":
            return "true"
        if boolean=="false":
            return "false"
        return ""

    def ConvertVariable(self: 'CPPTranspiler',variable: 'str') -> 'str':
        return variable

    def ConvertString(self: 'CPPTranspiler',literal: 'str') -> 'str':
        return Concat(Concat("std::string(\"",literal),"\")")

    def UnaryOperator(self: 'CPPTranspiler',op: 'str',r_value: 'str') -> 'str':
        if op=="!":
            return Concat("!",r_value)
        return r_value

    def BinaryOperator(self: 'CPPTranspiler',op: 'str',r_value_l: 'str',r_value_r: 'str') -> 'str':
        if op=="+":
            return Concat(Concat(r_value_l,"+"),r_value_r)
        if op=="-":
            return Concat(Concat(r_value_l,"-"),r_value_r)
        if op=="<=":
            return Concat(Concat(r_value_l,"<="),r_value_r)
        if op==">=":
            return Concat(Concat(r_value_l,">="),r_value_r)
        if op=="==":
            return Concat(Concat(r_value_l,"=="),r_value_r)
        if op=="!=":
            return Concat(Concat(r_value_l,"!="),r_value_r)
        if op=="<":
            return Concat(Concat(r_value_l,"<"),r_value_r)
        if op==">":
            return Concat(Concat(r_value_l,">"),r_value_r)
        if op=="||":
            return Concat(Concat(r_value_l,"||"),r_value_r)
        if op=="&&":
            return Concat(Concat(r_value_l,"&&"),r_value_r)
        return ""

    def GetTypeName(self: 'CPPTranspiler',name: 'S84_CTCode_dbnf_ctcode.Name') -> 'str':
        if name:
            return self.SnakeCaseToCamelCase(name.UnParse())
        else:
            return ""

    def GetDimensionalType(self: 'CPPTranspiler',singleton_type: 'str',dimensions: 'int') -> 'str':
        result: 'str' = singleton_type
        while dimensions>0:
            result = Concat(Concat("std::vector<",result),">")
            dimensions = dimensions-1
        return result

    def GetMapType(self: 'CPPTranspiler',singleton_type: 'str') -> 'str':
        return Concat(Concat("std::unordered_map<std::string, ",singleton_type),">")

    def GetPrimativeType(self: 'CPPTranspiler',c_t_type: 'str') -> 'str':
        if c_t_type=="int":
            return "int"
        if c_t_type=="string":
            return "std::string"
        if c_t_type=="bool":
            return "bool"
        if c_t_type=="float":
            return "float"
        if c_t_type=="void":
            return "void"
        return ""

    def GetQualifiedTypeName(self: 'CPPTranspiler',name_parts: 'list[S84_CTCode_dbnf_ctcode.Name]') -> 'str':
        delimiter: 'str' = "::"
        name_parts_index: 'int' = Size(name_parts)-1
        last_package_index: 'int' = Size(name_parts)-2
        type_part: 'S84_CTCode_dbnf_ctcode.Name' = Element(name_parts,name_parts_index)
        result: 'str' = self.GetTypeName(type_part)
        if name_parts_index>0:
            result = Concat(delimiter,result)
            while name_parts_index>0:
                name_parts_index = name_parts_index-1
                name_part: 'S84_CTCode_dbnf_ctcode.Name' = Element(name_parts,name_parts_index)
                if name_parts_index!=last_package_index:
                    result = Concat(delimiter,result)
                result = Concat(self.ToLower(name_part.UnParse()),result)
        return result

    def BeginProcessingCTCodeFile(self: 'CPPTranspiler') -> 'None':
        ClearList(self.includes)
        ClearList(self.interface_declarations)
        ClearList(self.class_declarations)
        self.current_interface = ""
        ClearList(self.interface_definitions)
        self.current_class = ""
        ClearList(self.class_definitions)
        ClearList(self.class_init)
        ClearList(self.class_functions)
        ClearList(self.class_members)
        ClearList(self.function_definitions)

    def ProcessExdef(self: 'CPPTranspiler',exdef: 'str') -> 'None':
        Append(self.includes,Concat("#include \"",Concat(exdef,".hpp\"")))

    def ProcessUnmanagedType(self: 'CPPTranspiler',unmanaged_type: 'str') -> 'None':
        noop: 'int' = 0

    def BeginProcessingInterface(self: 'CPPTranspiler',interface_name: 'str') -> 'None':
        self.current_interface = interface_name
        Append(self.interface_declarations,Concat(Concat("class ",interface_name),";"))
        Append(self.interface_definitions,Concat(Concat("class ",interface_name)," {"))
        Append(self.interface_definitions,"public:")

    def ProcessInterfaceFunctionDeclaration(self: 'CPPTranspiler',return_type: 'str',function_name: 'str',parameters: 'list[ParameterDeclaration]') -> 'None':
        Append(self.interface_definitions,Concat(Concat(Concat(Concat(Concat(Concat(self.Indentation(1),"virtual "),return_type)," "),function_name),self.MakeParametersString(parameters))," = 0;"))

    def FinishProcessingInterface(self: 'CPPTranspiler',interface_name: 'str') -> 'None':
        Append(self.interface_definitions,"};")
        Append(self.interface_definitions,"")
        self.current_interface = ""

    def BeginProcessingClass(self: 'CPPTranspiler',class_name: 'str',implementing: 'str') -> 'None':
        self.current_class = class_name
        Append(self.class_declarations,Concat(Concat("class ",class_name),";"))
        if implementing=="":
            Append(self.class_definitions,Concat(Concat("class ",class_name)," {"))
        else:
            Append(self.class_definitions,Concat(Concat(Concat(Concat("class ",class_name)," : public "),implementing)," {"))
        Append(self.class_definitions,"public:")
        Append(self.class_definitions,Concat(Concat(self.Indentation(1),class_name),"();"))
        Append(self.class_definitions,Concat(Concat(Concat(self.Indentation(1),"inline ~"),class_name),"() {}"))
        Append(self.class_definitions,"")
        ClearList(self.class_init)
        ClearList(self.class_functions)
        ClearList(self.class_members)
        Append(self.class_init,Concat(Concat(Concat(class_name,"::"),class_name),"()"))
        Append(self.class_init,"{")

    def BeginProcessingClassFunctionDefinition(self: 'CPPTranspiler',return_type: 'str',function_name: 'str',parameters: 'list[ParameterDeclaration]') -> 'None':
        Append(self.class_definitions,Concat(Concat(Concat(Concat(Concat(self.Indentation(1),return_type)," "),function_name),self.MakeParametersString(parameters)),";"))
        Append(self.class_functions,Concat(Concat(Concat(Concat(Concat(return_type," "),self.current_class),"::"),function_name),self.MakeParametersString(parameters)))

    def BeginProcessCodeBlock(self: 'CPPTranspiler',indent: 'int') -> 'None':
        Append(self.class_functions,Concat(self.Indentation(indent),"{"))

    def FinishProcessCodeBlock(self: 'CPPTranspiler',indent: 'int') -> 'None':
        Append(self.class_functions,Concat(self.Indentation(indent),"}"))

    def BeginProcessConditional(self: 'CPPTranspiler',indent: 'int',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(self.Indentation(indent),"if ("),r_value),")"))

    def ProcessElse(self: 'CPPTranspiler',indent: 'int') -> 'None':
        Append(self.class_functions,Concat(self.Indentation(indent),"else"))

    def FinishProcessConditional(self: 'CPPTranspiler',indent: 'int',r_value: 'str') -> 'None':
        noop: 'int' = 0

    def BeginProcessLoop(self: 'CPPTranspiler',indent: 'int',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(self.Indentation(indent),"while ("),r_value),")"))

    def FinishProcessLoop(self: 'CPPTranspiler',indent: 'int',r_value: 'str') -> 'None':
        noop: 'int' = 0

    def ProcessRtn(self: 'CPPTranspiler',indent: 'int',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(self.Indentation(indent),"return "),r_value),";"))

    def ProcessDeclaration(self: 'CPPTranspiler',indent: 'int',type: 'str',l_value: 'str',r_value: 'str') -> 'None':
        if r_value=="":
            r_value = self.GetDefault(type)
        if r_value=="":
            Append(self.class_functions,Concat(Concat(Concat(Concat(self.Indentation(indent),type)," "),l_value),";"))
        else:
            Append(self.class_functions,Concat(Concat(Concat(Concat(Concat(Concat(self.Indentation(indent),type)," "),l_value)," = "),r_value),";"))

    def ProcessAssignment(self: 'CPPTranspiler',indent: 'int',l_value: 'str',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(Concat(self.Indentation(indent),l_value)," = "),r_value),";"))

    def ProcessCall(self: 'CPPTranspiler',indent: 'int',call: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(self.Indentation(indent),call),";"))

    def FinishProcessingClassFunctionDefinition(self: 'CPPTranspiler',return_type: 'str',function_name: 'str',parameters: 'list[ParameterDeclaration]') -> 'None':
        Append(self.class_functions,"")

    def ProcessClassMemberDeclaration(self: 'CPPTranspiler',member_type: 'str',member_name: 'str') -> 'None':
        default_value: 'str' = self.GetDefault(member_type)
        if default_value!="":
            Append(self.class_init,Concat(Concat(Concat(Concat(Concat(self.Indentation(1),"this->"),member_name)," = "),default_value),";"))
        else:
            Append(self.class_init,Concat(Concat(Concat(Concat(Concat(self.Indentation(1),"/*this->"),member_name)," = "),"NO_DEFAULT"),";*/"))
        Append(self.class_members,Concat(Concat(Concat(Concat(self.Indentation(1),member_type)," "),member_name),";"))

    def FinishProcessingClass(self: 'CPPTranspiler',class_name: 'str',implementing: 'str') -> 'None':
        if Size(self.class_members)>0:
            Append(self.class_definitions,"")
            Append(self.class_definitions,"private:")
            class_members_index: 'int' = 0
            while class_members_index<Size(self.class_members):
                line: 'str' = Element(self.class_members,class_members_index)
                Append(self.class_definitions,line)
                class_members_index = class_members_index+1
        Append(self.class_definitions,"};")
        Append(self.class_definitions,"")
        Append(self.class_init,"}")
        Append(self.class_init,"")
        class_init_index: 'int' = 0
        while class_init_index<Size(self.class_init):
            line: 'str' = Element(self.class_init,class_init_index)
            Append(self.function_definitions,line)
            class_init_index = class_init_index+1
        class_functions_index: 'int' = 0
        while class_functions_index<Size(self.class_functions):
            line: 'str' = Element(self.class_functions,class_functions_index)
            Append(self.function_definitions,line)
            class_functions_index = class_functions_index+1
        self.current_class = ""

    def WriteCommonFunctions(self: 'CPPTranspiler',destination: 'S84_CTCode_System_ctcode.OutputStream') -> 'None':
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

    def WriteBeginingGuard(self: 'CPPTranspiler',file: 'S84_CTCode_System_ctcode.OutputStream') -> 'None':
        guard_name: 'str' = self.ToUpper(self.StripDot(Concat(self.base_name,"_H")))
        file.WriteLine(Concat("#ifndef ",guard_name))
        file.WriteLine(Concat("#define ",guard_name))

    def TokenizeBaseName(self: 'CPPTranspiler',name: 'str') -> 'list[str]':
        base_name_tokens: 'list[str]' = []
        current_token: 'str' = ""
        index: 'int' = 0
        while index<Length(name):
            character: 'str' = At(name,index)
            if character==".":
                Append(base_name_tokens,current_token)
                current_token = ""
            else:
                current_token = Concat(current_token,character)
            index = index+1
        Append(base_name_tokens,current_token)
        return base_name_tokens

    def WriteBeginingNamespace(self: 'CPPTranspiler',file: 'S84_CTCode_System_ctcode.OutputStream') -> 'None':
        base_name_tokens: 'list[str]' = self.TokenizeBaseName(self.base_name)
        base_name_tokens_index: 'int' = 0
        while base_name_tokens_index<Size(base_name_tokens):
            base_name_token: 'str' = Element(base_name_tokens,base_name_tokens_index)
            file.WriteLine(Concat(Concat("namespace ",self.ToLower(base_name_token))," {"))
            base_name_tokens_index = base_name_tokens_index+1

    def WriteEndingNamespace(self: 'CPPTranspiler',file: 'S84_CTCode_System_ctcode.OutputStream') -> 'None':
        base_name_tokens: 'list[str]' = self.TokenizeBaseName(self.base_name)
        base_name_tokens_index: 'int' = 0
        while base_name_tokens_index<Size(base_name_tokens):
            base_name_token: 'str' = Element(base_name_tokens,base_name_tokens_index)
            file.WriteLine("};")
            base_name_tokens_index = base_name_tokens_index+1

    def WriteEndingGuard(self: 'CPPTranspiler',file: 'S84_CTCode_System_ctcode.OutputStream') -> 'None':
        file.WriteLine("#endif")

    def FinishProcessingCTCodeFile(self: 'CPPTranspiler') -> 'None':
        header_file_name: 'str' = Concat(self.base_name,".hpp")
        header_file: 'S84_CTCode_System_ctcode.OutputStream' = self.system.OpenFileWriter(header_file_name)
        source_file_name: 'str' = Concat(self.base_name,".cpp")
        source_file: 'S84_CTCode_System_ctcode.OutputStream' = self.system.OpenFileWriter(source_file_name)
        self.WriteBeginingGuard(header_file)
        header_file.WriteLine("")
        if Size(self.includes)>0:
            self.WriteLines(header_file,self.includes)
            header_file.WriteLine("")
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
        if Size(self.interface_declarations)>0:
            self.WriteLines(header_file,self.interface_declarations)
            header_file.WriteLine("")
        if Size(self.class_declarations)>0:
            self.WriteLines(header_file,self.class_declarations)
            header_file.WriteLine("")
        if Size(self.interface_definitions)>0:
            self.WriteLines(header_file,self.interface_definitions)
        self.WriteLines(header_file,self.class_definitions)
        self.WriteEndingNamespace(header_file)
        header_file.WriteLine("")
        self.WriteEndingGuard(header_file)
        source_file.WriteLine(Concat(Concat("#include \"",self.base_name),".hpp\""))
        source_file.WriteLine("")
        self.WriteBeginingNamespace(source_file)
        source_file.WriteLine("")
        if Size(self.function_definitions)>0:
            self.WriteLines(source_file,self.function_definitions)
            source_file.WriteLine("")
        self.WriteEndingNamespace(source_file)

    def BeginsWith(self: 'CPPTranspiler',prefix: 'str',value: 'str') -> 'bool':
        if Length(prefix)>Length(value):
            return False
        prefix_index: 'int' = 0
        while prefix_index<Length(prefix):
            if At(prefix,prefix_index)!=At(value,prefix_index):
                return False
            prefix_index = prefix_index+1
        return True

    def GetDefault(self: 'CPPTranspiler',cpp_type: 'str') -> 'str':
        if cpp_type=="int":
            return "0"
        if cpp_type=="std::string":
            return "\"\""
        if cpp_type=="bool":
            return "false"
        if cpp_type=="float":
            return "0.0"
        if cpp_type=="void":
            return "NULL"
        if self.BeginsWith("std::unordered_map<std::string, ",cpp_type):
            return ""
        if self.BeginsWith("std::vector<",cpp_type):
            return ""
        return "NULL"

    def MakeParametersString(self: 'CPPTranspiler',parameters: 'list[ParameterDeclaration]') -> 'str':
        result: 'str' = "("
        parameters_index: 'int' = 0
        while parameters_index<Size(parameters):
            parameter: 'ParameterDeclaration' = Element(parameters,parameters_index)
            if parameters_index!=0:
                result = Concat(result,", ")
            result = Concat(Concat(Concat(result,parameter.GetType())," "),parameter.GetName())
            parameters_index = parameters_index+1
        result = Concat(result,")")
        return result

    def StripDot(self: 'CPPTranspiler',input: 'str') -> 'str':
        index: 'int' = 0
        index = 0
        result: 'str' = ""
        result = ""
        while index<Length(input):
            character: 'str' = ""
            character = At(input,index)
            if character==".":
                result = Concat(result,"_")
            else:
                result = Concat(result,character)
            index = index+1
        return result

    def WriteLines(self: 'CPPTranspiler',destination: 'S84_CTCode_System_ctcode.OutputStream',lines: 'list[str]') -> 'None':
        lines_index: 'int' = 0
        while lines_index<Size(lines):
            line: 'str' = Element(lines,lines_index)
            destination.WriteLine(line)
            lines_index = lines_index+1

    def Transpile(self: 'CPPTranspiler',system: 'S84_CTCode_System_ctcode.System',c_t_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile',base_name: 'str') -> 'int':
        ClearList(self.operator_precedent)
        self.PopulateOperatorPrecedent()
        self.system = system
        self.c_t_code_file = c_t_code_file
        self.base_name = base_name
        self.logger = system.GetLoggerDestination()
        self.ProcessCTCodeFile(c_t_code_file)
        return 0

    def ProcessCTCodeFile(self: 'CPPTranspiler',c_t_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile') -> 'None':
        self.BeginProcessingCTCodeFile()
        self.ProcessExdefs(c_t_code_file)
        self.ProcessUnmanagedTypes(c_t_code_file)
        self.ProcessDefinitions(c_t_code_file)
        self.FinishProcessingCTCodeFile()

    def ProcessExdefs(self: 'CPPTranspiler',c_t_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile') -> 'None':
        exdefs: 'list[S84_CTCode_dbnf_ctcode.ExternalDefinition]' = c_t_code_file.GetDeclarations()
        exdefs_index: 'int' = 0
        while exdefs_index<Size(exdefs):
            exdef: 'S84_CTCode_dbnf_ctcode.ExternalDefinition' = Element(exdefs,exdefs_index)
            exdef_name: 'S84_CTCode_dbnf_ctcode.QualfiedName' = exdef.GetExdef()
            self.ProcessExdef(exdef_name.UnParse())
            exdefs_index = exdefs_index+1

    def ProcessUnmanagedTypes(self: 'CPPTranspiler',c_t_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile') -> 'None':
        unmanaged_types: 'list[S84_CTCode_dbnf_ctcode.UnmanagedType]' = c_t_code_file.GetUnmanagedTypes()
        unmanaged_types_index: 'int' = 0
        while unmanaged_types_index<Size(unmanaged_types):
            unmanaged_type: 'S84_CTCode_dbnf_ctcode.UnmanagedType' = Element(unmanaged_types,unmanaged_types_index)
            self.ProcessUnmanagedType(self.GetQualifiedTypeNameInternal(unmanaged_type.GetUnmanagedType()))
            unmanaged_types_index = unmanaged_types_index+1

    def ProcessDefinitions(self: 'CPPTranspiler',c_t_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile') -> 'None':
        definitions: 'list[S84_CTCode_dbnf_ctcode.Definition]' = c_t_code_file.GetDefinitions()
        definitions_index: 'int' = 0
        while definitions_index<Size(definitions):
            definition: 'S84_CTCode_dbnf_ctcode.Definition' = None
            definition = Element(definitions,definitions_index)
            if definition.GetInterfaceDef():
                self.ProcessInterfaceDefinition(definition.GetInterfaceDef())
            if definition.GetClassDef():
                self.ProcessClassDefinition(definition.GetClassDef())
            definitions_index = definitions_index+1

    def GetParameters(self: 'CPPTranspiler',parameter_list_def: 'S84_CTCode_dbnf_ctcode.ParameterListDef') -> 'list[ParameterDeclaration]':
        result: 'list[ParameterDeclaration]' = []
        while parameter_list_def:
            parameter: 'ParameterDeclaration' = ParameterDeclaration()
            parameter.SetType(self.GetType(parameter_list_def.GetType()))
            parameter.SetName(self.GetVariableName(parameter_list_def.GetName()))
            Append(result,parameter)
            parameter_list_def = parameter_list_def.GetParameterTail()
        return result

    def ProcessInterfaceDefinition(self: 'CPPTranspiler',interface_definition: 'S84_CTCode_dbnf_ctcode.InterfaceDef') -> 'None':
        interface_name: 'str' = self.GetTypeName(interface_definition.GetName())
        self.BeginProcessingInterface(interface_name)
        declarations: 'list[S84_CTCode_dbnf_ctcode.ContentDeclaration]' = interface_definition.GetDeclarations()
        declarations_index: 'int' = 0
        while declarations_index<Size(declarations):
            declaration: 'S84_CTCode_dbnf_ctcode.ContentDeclaration' = Element(declarations,declarations_index)
            return_type: 'str' = self.GetType(declaration.GetType())
            function_name: 'str' = self.GetCallName(declaration.GetName())
            parameters: 'list[ParameterDeclaration]' = self.GetParameters(declaration.GetParameters())
            self.ProcessInterfaceFunctionDeclaration(return_type,function_name,parameters)
            declarations_index = declarations_index+1
        self.FinishProcessingInterface(interface_name)

    def ProcessClassDefinition(self: 'CPPTranspiler',class_definition: 'S84_CTCode_dbnf_ctcode.ClassDef') -> 'None':
        class_name: 'str' = self.GetTypeName(class_definition.GetName())
        implementing: 'str' = ""
        implementation_spec: 'S84_CTCode_dbnf_ctcode.ImplementationSpec' = class_definition.GetImplementing()
        if implementation_spec:
            implementing = self.GetQualifiedTypeNameInternal(implementation_spec.GetInterface())
        self.BeginProcessingClass(class_name,implementing)
        definitions: 'list[S84_CTCode_dbnf_ctcode.ContentDefinition]' = class_definition.GetDefinitions()
        definitions_index: 'int' = 0
        while definitions_index<Size(definitions):
            definition: 'S84_CTCode_dbnf_ctcode.ContentDefinition' = Element(definitions,definitions_index)
            if definition.GetFunctionBody():
                return_type: 'str' = self.GetType(definition.GetType())
                function_name: 'str' = self.GetCallName(definition.GetName())
                parameters: 'list[ParameterDeclaration]' = self.GetParameters(definition.GetParameters())
                self.BeginProcessingClassFunctionDefinition(return_type,function_name,parameters)
                self.ProcessCodeBlockInternal(self.GetBaseIndentation(),definition.GetFunctionBody())
                self.FinishProcessingClassFunctionDefinition(return_type,function_name,parameters)
            else:
                member_type: 'str' = self.GetType(definition.GetType())
                member_name: 'str' = self.GetVariableName(definition.GetName())
                self.ProcessClassMemberDeclaration(member_type,member_name)
            definitions_index = definitions_index+1
        self.FinishProcessingClass(class_name,implementing)

    def ProcessInstructionInternal(self: 'CPPTranspiler',indent: 'int',instruction: 'S84_CTCode_dbnf_ctcode.Instruction') -> 'None':
        if instruction.GetCodeBlock():
            self.ProcessCodeBlockInternal(indent,instruction.GetCodeBlock())
        if instruction.GetRtn():
            self.ProcessRtnInternal(indent,instruction.GetRtn())
        if instruction.GetDeclaration():
            self.ProcessDeclarationInternal(indent,instruction.GetDeclaration())
        if instruction.GetAssignment():
            self.ProcessAssignmentInternal(indent,instruction.GetAssignment())
        if instruction.GetCall():
            self.ProcessCallInternal(indent,instruction.GetCall())
        if instruction.GetConditional():
            self.ProcessConditionalInternal(indent,instruction.GetConditional())
        if instruction.GetLoop():
            self.ProcessLoopInternal(indent,instruction.GetLoop())

    def ProcessCodeBlockInternal(self: 'CPPTranspiler',indent: 'int',code_block: 'S84_CTCode_dbnf_ctcode.CodeBlock') -> 'None':
        self.BeginProcessCodeBlock(indent)
        instructions: 'list[S84_CTCode_dbnf_ctcode.Instruction]' = code_block.GetInstructions()
        instructions_index: 'int' = 0
        while instructions_index<Size(instructions):
            self.ProcessInstructionInternal(indent+1,Element(instructions,instructions_index))
            instructions_index = instructions_index+1
        self.FinishProcessCodeBlock(indent)

    def ProcessConditionalInternal(self: 'CPPTranspiler',indent: 'int',conditional: 'S84_CTCode_dbnf_ctcode.Conditional') -> 'None':
        r_value: 'str' = self.GetRValueInternal(conditional.GetRValue())
        self.BeginProcessConditional(indent,r_value)
        self.ProcessCodeBlockInternal(indent,conditional.GetCodeBlock())
        if conditional.GetElseTail():
            else_tail: 'S84_CTCode_dbnf_ctcode.ElseTail' = conditional.GetElseTail()
            self.ProcessElse(indent)
            self.ProcessCodeBlockInternal(indent,else_tail.GetCodeBlock())
        self.FinishProcessConditional(indent,r_value)

    def ProcessLoopInternal(self: 'CPPTranspiler',indent: 'int',loop: 'S84_CTCode_dbnf_ctcode.Loop') -> 'None':
        r_value: 'str' = self.GetRValueInternal(loop.GetRValue())
        self.BeginProcessLoop(indent,r_value)
        self.ProcessCodeBlockInternal(indent,loop.GetCodeBlock())
        self.FinishProcessLoop(indent,r_value)

    def ProcessRtnInternal(self: 'CPPTranspiler',indent: 'int',rtn: 'S84_CTCode_dbnf_ctcode.Return') -> 'None':
        r_value: 'str' = self.GetRValueInternal(rtn.GetRValue())
        self.ProcessRtn(indent,r_value)

    def ProcessDeclarationInternal(self: 'CPPTranspiler',indent: 'int',declaration: 'S84_CTCode_dbnf_ctcode.Declaration') -> 'None':
        type: 'str' = self.GetType(declaration.GetType())
        l_value: 'str' = self.GetVariableName(declaration.GetName())
        r_value: 'str' = ""
        declaration_assignment: 'S84_CTCode_dbnf_ctcode.DeclarationAssign' = declaration.GetAssignment()
        if declaration_assignment:
            r_value = self.GetRValueInternal(declaration_assignment.GetRValue())
        self.ProcessDeclaration(indent,type,l_value,r_value)

    def ProcessAssignmentInternal(self: 'CPPTranspiler',indent: 'int',assignment: 'S84_CTCode_dbnf_ctcode.Assignment') -> 'None':
        self.ProcessAssignment(indent,self.GetVariableChain(assignment.GetLValue()),self.GetRValueInternal(assignment.GetRValue()))

    def ProcessCallInternal(self: 'CPPTranspiler',indent: 'int',call: 'S84_CTCode_dbnf_ctcode.Call') -> 'None':
        self.ProcessCall(indent,self.ConvertCallInternal(call))

    def ConvertCallInternal(self: 'CPPTranspiler',call: 'S84_CTCode_dbnf_ctcode.Call') -> 'str':
        name_chain: 'list[str]' = []
        parameters: 'list[str]' = []
        if call.GetVariable():
            Append(name_chain,self.GetVariableName(call.GetVariable()))
        if call.GetFunction():
            Append(name_chain,self.GetCallName(call.GetFunction()))
        if call.GetFunctionChain():
            function_chain: 'S84_CTCode_dbnf_ctcode.QualfiedName' = call.GetFunctionChain()
            name_tail: 'S84_CTCode_dbnf_ctcode.NameTail' = function_chain.GetTail()
            if function_chain.GetTail():
                Append(name_chain,self.GetVariableName(function_chain.GetName()))
            else:
                Append(name_chain,self.GetCallName(function_chain.GetName()))
            while name_tail:
                if name_tail.GetTail():
                    Append(name_chain,self.GetVariableName(name_tail.GetName()))
                else:
                    Append(name_chain,self.GetCallName(name_tail.GetName()))
                name_tail = name_tail.GetTail()
        parameter_list: 'S84_CTCode_dbnf_ctcode.ParameterList' = call.GetParameters()
        while parameter_list:
            Append(parameters,self.GetRValueInternal(parameter_list.GetRValue()))
            parameter_list = parameter_list.GetParameterTail()
        return self.ConvertCall(name_chain,parameters)

    def GetSingletonType(self: 'CPPTranspiler',singleton_type: 'S84_CTCode_dbnf_ctcode.SingletonType') -> 'str':
        if singleton_type.GetPrimativeType():
            return self.GetPrimativeType(singleton_type.UnParse())
        if singleton_type.GetDefinedType():
            defined_type: 'S84_CTCode_dbnf_ctcode.DefinedType' = singleton_type.GetDefinedType()
            return Concat(Concat("OmniPointer<",self.GetQualifiedTypeNameInternal(defined_type.GetName())),">")
        return ""

    def GetRValueSingleBasisInternal(self: 'CPPTranspiler',r_value_single: 'S84_CTCode_dbnf_ctcode.RValueSingle') -> 'str':
        call: 'S84_CTCode_dbnf_ctcode.Call' = r_value_single.GetCall()
        if call:
            return self.ConvertCallInternal(call)
        allocate: 'S84_CTCode_dbnf_ctcode.Allocate' = r_value_single.GetAllocate()
        if allocate:
            return self.ConvertAllocate(self.GetQualifiedTypeNameInternal(allocate.GetManagedType()))
        byte_literal: 'S84_CTCode_dbnf_ctcode.Byte' = r_value_single.GetByteLiteral()
        if byte_literal:
            high: 'S84_CTCode_dbnf_ctcode.ByteDigit' = byte_literal.GetHigh()
            low: 'S84_CTCode_dbnf_ctcode.ByteDigit' = byte_literal.GetLow()
            return self.ConvertByte(high.UnParse(),low.UnParse())
        decimal_literal: 'S84_CTCode_dbnf_ctcode.Decimal' = r_value_single.GetDecimalLiteral()
        if decimal_literal:
            return self.ConvertDecimal(decimal_literal.UnParse())
        integer_literal: 'S84_CTCode_dbnf_ctcode.Number' = r_value_single.GetIntegerLiteral()
        if integer_literal:
            return self.ConvertNumber(integer_literal.UnParse())
        boolean_literal: 'S84_CTCode_dbnf_ctcode.Boolean' = r_value_single.GetBooleanLiteral()
        if boolean_literal:
            return self.ConvertBoolean(boolean_literal.UnParse())
        variable: 'S84_CTCode_dbnf_ctcode.QualfiedName' = r_value_single.GetVariable()
        if variable:
            return self.ConvertVariable(self.GetVariableChain(variable))
        string_literal: 'S84_CTCode_dbnf_ctcode.Literal' = r_value_single.GetStringLiteral()
        if string_literal:
            return self.ConvertString(string_literal.UnParse())
        return ""

    def GetRValueSingleInternal(self: 'CPPTranspiler',r_value_single: 'S84_CTCode_dbnf_ctcode.RValueSingle') -> 'str':
        unary_operator: 'S84_CTCode_dbnf_ctcode.UnaryOperator' = r_value_single.GetUnaryOperator()
        if unary_operator:
            return self.UnaryOperator(unary_operator.UnParse(),self.GetRValueSingleBasisInternal(r_value_single))
        return self.GetRValueSingleBasisInternal(r_value_single)

    def PopulateOperatorPrecedent(self: 'CPPTranspiler') -> 'None':
        precedent__0_operators: 'list[str]' = []
        Append(precedent__0_operators,"+")
        Append(precedent__0_operators,"-")
        Append(self.operator_precedent,precedent__0_operators)
        precedent__1_operators: 'list[str]' = []
        Append(precedent__1_operators,"<=")
        Append(precedent__1_operators,">=")
        Append(precedent__1_operators,"==")
        Append(precedent__1_operators,"!=")
        Append(precedent__1_operators,"<")
        Append(precedent__1_operators,">")
        Append(self.operator_precedent,precedent__1_operators)
        precedent__2_operators: 'list[str]' = []
        Append(precedent__2_operators,"&&")
        Append(self.operator_precedent,precedent__2_operators)
        precedent__3_operators: 'list[str]' = []
        Append(precedent__3_operators,"||")
        Append(self.operator_precedent,precedent__3_operators)
        precedent__4_operators: 'list[str]' = []
        Append(precedent__4_operators,"")
        Append(self.operator_precedent,precedent__4_operators)

    def OverPrecedent(self: 'CPPTranspiler',op: 'str',precedent: 'int') -> 'bool':
        precedent = precedent+1
        while precedent<Size(self.operator_precedent):
            precedent_operators: 'list[str]' = Element(self.operator_precedent,precedent)
            index: 'int' = 0
            while index<Size(precedent_operators):
                checking_op: 'str' = Element(precedent_operators,index)
                if checking_op==op:
                    return True
                index = index+1
            precedent = precedent+1
        return False

    def BinaryOperatorPrecedentMerge(self: 'CPPTranspiler',values: 'list[str]',operators: 'list[str]',index: 'IntegerReference',precedent: 'int') -> 'str':
        if precedent==-1:
            return Element(values,index.GetValue())
        r_value_l: 'str' = self.BinaryOperatorPrecedentMerge(values,operators,index,precedent-1)
        while index.GetValue()<Size(operators):
            op: 'str' = Element(operators,index.GetValue())
            if self.OverPrecedent(op,precedent):
                return r_value_l
            index.SetValue(index.GetValue()+1)
            r_value_r: 'str' = self.BinaryOperatorPrecedentMerge(values,operators,index,precedent-1)
            r_value_l = self.BinaryOperator(op,r_value_l,r_value_r)
        return r_value_l

    def GetRValueInternal(self: 'CPPTranspiler',r_value: 'S84_CTCode_dbnf_ctcode.RValue') -> 'str':
        values: 'list[str]' = []
        operators: 'list[str]' = []
        index: 'IntegerReference' = IntegerReference()
        index.SetValue(0)
        Append(values,self.GetRValueSingleInternal(r_value.GetValue()))
        r_value_tail: 'S84_CTCode_dbnf_ctcode.RValueTail' = r_value.GetTail()
        while r_value_tail:
            binary_operator: 'S84_CTCode_dbnf_ctcode.BinaryOperator' = r_value_tail.GetBinaryOperator()
            Append(values,self.GetRValueSingleInternal(r_value_tail.GetValue()))
            Append(operators,binary_operator.UnParse())
            r_value_tail = r_value_tail.GetTail()
        return self.BinaryOperatorPrecedentMerge(values,operators,index,Size(self.operator_precedent))

    def GetQualifiedTypeNameInternal(self: 'CPPTranspiler',qualified_name: 'S84_CTCode_dbnf_ctcode.QualfiedName') -> 'str':
        name_parts: 'list[S84_CTCode_dbnf_ctcode.Name]' = []
        Append(name_parts,qualified_name.GetName())
        tail: 'S84_CTCode_dbnf_ctcode.NameTail' = qualified_name.GetTail()
        while tail:
            Append(name_parts,tail.GetName())
            tail = tail.GetTail()
        return self.GetQualifiedTypeName(name_parts)

    def GetType(self: 'CPPTranspiler',type: 'S84_CTCode_dbnf_ctcode.ValueType') -> 'str':
        if type.GetDimensionalType():
            dimensional_type: 'S84_CTCode_dbnf_ctcode.DimensionalType' = type.GetDimensionalType()
            singleton_type: 'S84_CTCode_dbnf_ctcode.SingletonType' = dimensional_type.GetSingletonType()
            return self.GetDimensionalType(self.GetSingletonType(singleton_type),Size(dimensional_type.GetDimensionalNote()))
        if type.GetMapType():
            map_type: 'S84_CTCode_dbnf_ctcode.MapType' = type.GetMapType()
            singleton_type: 'S84_CTCode_dbnf_ctcode.SingletonType' = map_type.GetSingletonType()
            return self.GetMapType(self.GetSingletonType(singleton_type))
        if type.GetSingletonType():
            singleton_type: 'S84_CTCode_dbnf_ctcode.SingletonType' = type.GetSingletonType()
            return self.GetSingletonType(singleton_type)
        return ""

    def Indentation(self: 'CPPTranspiler',indent: 'int') -> 'str':
        result: 'str' = ""
        result = ""
        while indent>0:
            indent = indent-1
            result = Concat(result,"    ")
        return result

    def SnakeCaseToCamelCase(self: 'CPPTranspiler',snake_case: 'str') -> 'str':
        capitalize_this_letter: 'bool' = True
        camel_case: 'str' = ""
        index: 'int' = 0
        index = 0
        while index<Length(snake_case):
            source_character: 'str' = At(snake_case,index)
            if source_character=="_":
                capitalize_this_letter = True
            else:
                if capitalize_this_letter==True:
                    upper_character: 'str' = self.CharacterToUpper(source_character)
                    capitalize_this_letter = False
                    camel_case = Concat(camel_case,upper_character)
                else:
                    capitalize_this_letter = False
                    camel_case = Concat(camel_case,source_character)
            index = index+1
        return camel_case

    def CamelCaseToSnakeCase(self: 'CPPTranspiler',camel_case: 'str') -> 'str':
        delimiter: 'str' = "_"
        snake_case: 'str' = ""
        index: 'int' = 0
        while index<Length(camel_case):
            source_character: 'str' = At(camel_case,index)
            lower_character: 'str' = self.CharacterToLower(source_character)
            if self.IsUpper(source_character) or self.IsDigit(source_character):
                is_first_character: 'bool' = Length(snake_case)==0
                if not is_first_character:
                    snake_case = Concat(snake_case,delimiter)
            snake_case = Concat(snake_case,lower_character)
            index = index+1
        return snake_case

    def IsUpper(self: 'CPPTranspiler',character: 'str') -> 'bool':
        result: 'bool' = False
        result = False
        result = result or character=="A"
        result = result or character=="B"
        result = result or character=="C"
        result = result or character=="D"
        result = result or character=="E"
        result = result or character=="F"
        result = result or character=="G"
        result = result or character=="H"
        result = result or character=="I"
        result = result or character=="J"
        result = result or character=="K"
        result = result or character=="L"
        result = result or character=="M"
        result = result or character=="N"
        result = result or character=="O"
        result = result or character=="P"
        result = result or character=="Q"
        result = result or character=="R"
        result = result or character=="S"
        result = result or character=="T"
        result = result or character=="U"
        result = result or character=="V"
        result = result or character=="W"
        result = result or character=="X"
        result = result or character=="Y"
        result = result or character=="Z"
        return result

    def IsDigit(self: 'CPPTranspiler',character: 'str') -> 'bool':
        result: 'bool' = False
        result = False
        result = result or character=="0"
        result = result or character=="1"
        result = result or character=="2"
        result = result or character=="3"
        result = result or character=="4"
        result = result or character=="5"
        result = result or character=="6"
        result = result or character=="7"
        result = result or character=="8"
        result = result or character=="9"
        return result

    def ToLower(self: 'CPPTranspiler',input: 'str') -> 'str':
        index: 'int' = 0
        result: 'str' = ""
        while index<Length(input):
            character: 'str' = At(input,index)
            lower_character: 'str' = self.CharacterToLower(character)
            result = Concat(result,lower_character)
            index = index+1
        return result

    def CharacterToLower(self: 'CPPTranspiler',input: 'str') -> 'str':
        if input=="A":
            return "a"
        if input=="B":
            return "b"
        if input=="C":
            return "c"
        if input=="D":
            return "d"
        if input=="E":
            return "e"
        if input=="F":
            return "f"
        if input=="G":
            return "g"
        if input=="H":
            return "h"
        if input=="I":
            return "i"
        if input=="J":
            return "j"
        if input=="K":
            return "k"
        if input=="L":
            return "l"
        if input=="M":
            return "m"
        if input=="N":
            return "n"
        if input=="O":
            return "o"
        if input=="P":
            return "p"
        if input=="Q":
            return "q"
        if input=="R":
            return "r"
        if input=="S":
            return "s"
        if input=="T":
            return "t"
        if input=="U":
            return "u"
        if input=="V":
            return "v"
        if input=="W":
            return "w"
        if input=="X":
            return "x"
        if input=="Y":
            return "y"
        if input=="Z":
            return "z"
        return input

    def ToUpper(self: 'CPPTranspiler',input: 'str') -> 'str':
        index: 'int' = 0
        result: 'str' = ""
        while index<Length(input):
            character: 'str' = At(input,index)
            upper_character: 'str' = self.CharacterToUpper(character)
            result = Concat(result,upper_character)
            index = index+1
        return result

    def CharacterToUpper(self: 'CPPTranspiler',input: 'str') -> 'str':
        if input=="a":
            return "A"
        if input=="b":
            return "B"
        if input=="c":
            return "C"
        if input=="d":
            return "D"
        if input=="e":
            return "E"
        if input=="f":
            return "F"
        if input=="g":
            return "G"
        if input=="h":
            return "H"
        if input=="i":
            return "I"
        if input=="j":
            return "J"
        if input=="k":
            return "K"
        if input=="l":
            return "L"
        if input=="m":
            return "M"
        if input=="n":
            return "N"
        if input=="o":
            return "O"
        if input=="p":
            return "P"
        if input=="q":
            return "Q"
        if input=="r":
            return "R"
        if input=="s":
            return "S"
        if input=="t":
            return "T"
        if input=="u":
            return "U"
        if input=="v":
            return "V"
        if input=="w":
            return "W"
        if input=="x":
            return "X"
        if input=="y":
            return "Y"
        if input=="z":
            return "Z"
        return input

