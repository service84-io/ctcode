import S84_CTCode_dbnf_ctcode
import S84_CTCode_System_ctcode
import S84_CTCode_Transpiler_StandardStructure_ctcode
import S84_CTCode_Transpiler_StringHelper_ctcode

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

class CPPTranspiler(S84_CTCode_Transpiler_StandardStructure_ctcode.TargetSpecificFunctions):
    def __init__(self: 'CPPTranspiler'):
        self.system: S84_CTCode_System_ctcode.System = None
        self.c_t_code_file: S84_CTCode_dbnf_ctcode.CTCodeFile = None
        self.base_name: str = ""
        self.logger: S84_CTCode_System_ctcode.OutputStream = None
        self.string_helper: S84_CTCode_Transpiler_StringHelper_ctcode.StringHelper = None
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

    def Initialize(self: 'CPPTranspiler') -> 'None':
        self.string_helper = S84_CTCode_Transpiler_StringHelper_ctcode.StringHelper()

    def SetSystem(self: 'CPPTranspiler',system: 'S84_CTCode_System_ctcode.System') -> 'None':
        self.system = system

    def SetCTCodeFile(self: 'CPPTranspiler',c_t_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile') -> 'None':
        self.c_t_code_file = c_t_code_file

    def SetBaseName(self: 'CPPTranspiler',base_name: 'str') -> 'None':
        self.base_name = base_name

    def SetLogger(self: 'CPPTranspiler',logger: 'S84_CTCode_System_ctcode.OutputStream') -> 'None':
        self.logger = logger

    def GetBaseIndentation(self: 'CPPTranspiler') -> 'int':
        return 0

    def GetCallName(self: 'CPPTranspiler',name: 'str') -> 'str':
        return self.string_helper.SnakeCaseToCamelCase(name)

    def GetVariableName(self: 'CPPTranspiler',name: 'str') -> 'str':
        value: 'str' = self.string_helper.CamelCaseToSnakeCase(name)
        if value=="myself":
            return "this"
        return value

    def GetVariableChain(self: 'CPPTranspiler',name_parts: 'list[str]') -> 'str':
        delimiter: 'str' = "->"
        first_name: 'str' = Element(name_parts,0)
        result: 'str' = self.GetVariableName(first_name)
        name_parts_index: 'int' = 1
        while name_parts_index<Size(name_parts):
            name: 'str' = Element(name_parts,name_parts_index)
            result = Concat(Concat(result,delimiter),self.GetVariableName(name))
            name_parts_index = name_parts_index+1
        return result

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

    def GetTypeName(self: 'CPPTranspiler',name: 'str') -> 'str':
        return self.string_helper.SnakeCaseToCamelCase(name)

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

    def GetDefinedType(self: 'CPPTranspiler',c_t_type: 'str') -> 'str':
        return Concat(Concat("OmniPointer<",c_t_type),">")

    def GetQualifiedTypeName(self: 'CPPTranspiler',name_parts: 'list[str]') -> 'str':
        delimiter: 'str' = "::"
        name_parts_index: 'int' = Size(name_parts)-1
        type_part: 'str' = Element(name_parts,name_parts_index)
        result: 'str' = self.GetTypeName(type_part)
        if name_parts_index>0:
            while name_parts_index>0:
                name_parts_index = name_parts_index-1
                result = Concat(delimiter,result)
                name_part: 'str' = Element(name_parts,name_parts_index)
                result = Concat(self.string_helper.ToLower(name_part),result)
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
        pass

    def BeginProcessingInterface(self: 'CPPTranspiler',interface_name: 'str') -> 'None':
        self.current_interface = interface_name
        Append(self.interface_declarations,Concat(Concat("class ",interface_name),";"))
        Append(self.interface_definitions,Concat(Concat("class ",interface_name)," {"))
        Append(self.interface_definitions,"public:")

    def ProcessInterfaceFunctionDeclaration(self: 'CPPTranspiler',return_type: 'str',function_name: 'str',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'None':
        Append(self.interface_definitions,Concat(Concat(Concat(Concat(Concat(Concat(self.string_helper.Indentation(1),"virtual "),return_type)," "),function_name),self.MakeParametersString(parameters))," = 0;"))

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
        Append(self.class_definitions,Concat(Concat(self.string_helper.Indentation(1),class_name),"();"))
        Append(self.class_definitions,Concat(Concat(Concat(self.string_helper.Indentation(1),"inline ~"),class_name),"() {}"))
        Append(self.class_definitions,"")
        ClearList(self.class_init)
        ClearList(self.class_functions)
        ClearList(self.class_members)
        Append(self.class_init,Concat(Concat(Concat(class_name,"::"),class_name),"()"))
        Append(self.class_init,"{")

    def BeginProcessingClassFunctionDefinition(self: 'CPPTranspiler',return_type: 'str',function_name: 'str',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'None':
        Append(self.class_definitions,Concat(Concat(Concat(Concat(Concat(self.string_helper.Indentation(1),return_type)," "),function_name),self.MakeParametersString(parameters)),";"))
        Append(self.class_functions,Concat(Concat(Concat(Concat(Concat(return_type," "),self.current_class),"::"),function_name),self.MakeParametersString(parameters)))

    def BeginProcessCodeBlock(self: 'CPPTranspiler',indent: 'int') -> 'None':
        Append(self.class_functions,Concat(self.string_helper.Indentation(indent),"{"))

    def FinishProcessCodeBlock(self: 'CPPTranspiler',indent: 'int') -> 'None':
        Append(self.class_functions,Concat(self.string_helper.Indentation(indent),"}"))

    def BeginProcessConditional(self: 'CPPTranspiler',indent: 'int',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(self.string_helper.Indentation(indent),"if ("),r_value),")"))

    def ProcessElse(self: 'CPPTranspiler',indent: 'int') -> 'None':
        Append(self.class_functions,Concat(self.string_helper.Indentation(indent),"else"))

    def FinishProcessConditional(self: 'CPPTranspiler',indent: 'int',r_value: 'str') -> 'None':
        pass

    def BeginProcessLoop(self: 'CPPTranspiler',indent: 'int',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(self.string_helper.Indentation(indent),"while ("),r_value),")"))

    def FinishProcessLoop(self: 'CPPTranspiler',indent: 'int',r_value: 'str') -> 'None':
        pass

    def ProcessRtn(self: 'CPPTranspiler',indent: 'int',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(self.string_helper.Indentation(indent),"return "),r_value),";"))

    def ProcessDeclaration(self: 'CPPTranspiler',indent: 'int',type: 'str',l_value: 'str',r_value: 'str') -> 'None':
        if r_value=="":
            r_value = self.GetDefault(type)
        if r_value=="":
            Append(self.class_functions,Concat(Concat(Concat(Concat(self.string_helper.Indentation(indent),type)," "),l_value),";"))
        else:
            Append(self.class_functions,Concat(Concat(Concat(Concat(Concat(Concat(self.string_helper.Indentation(indent),type)," "),l_value)," = "),r_value),";"))

    def ProcessAssignment(self: 'CPPTranspiler',indent: 'int',l_value: 'str',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(Concat(self.string_helper.Indentation(indent),l_value)," = "),r_value),";"))

    def ProcessCall(self: 'CPPTranspiler',indent: 'int',call: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(self.string_helper.Indentation(indent),call),";"))

    def FinishProcessingClassFunctionDefinition(self: 'CPPTranspiler',return_type: 'str',function_name: 'str',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'None':
        Append(self.class_functions,"")

    def ProcessClassMemberDeclaration(self: 'CPPTranspiler',member_type: 'str',member_name: 'str') -> 'None':
        default_value: 'str' = self.GetDefault(member_type)
        if default_value!="":
            Append(self.class_init,Concat(Concat(Concat(Concat(Concat(self.string_helper.Indentation(1),"this->"),member_name)," = "),default_value),";"))
        else:
            Append(self.class_init,Concat(Concat(Concat(Concat(Concat(self.string_helper.Indentation(1),"/*this->"),member_name)," = "),"NO_DEFAULT"),";*/"))
        Append(self.class_members,Concat(Concat(Concat(Concat(self.string_helper.Indentation(1),member_type)," "),member_name),";"))

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
        guard_name: 'str' = self.string_helper.ToUpper(self.string_helper.StripDot(Concat(self.base_name,"_H")))
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
            file.WriteLine(Concat(Concat("namespace ",self.string_helper.ToLower(base_name_token))," {"))
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
            self.string_helper.WriteLines(header_file,self.includes)
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
            self.string_helper.WriteLines(header_file,self.interface_declarations)
            header_file.WriteLine("")
        if Size(self.class_declarations)>0:
            self.string_helper.WriteLines(header_file,self.class_declarations)
            header_file.WriteLine("")
        if Size(self.interface_definitions)>0:
            self.string_helper.WriteLines(header_file,self.interface_definitions)
        self.string_helper.WriteLines(header_file,self.class_definitions)
        self.WriteEndingNamespace(header_file)
        header_file.WriteLine("")
        self.WriteEndingGuard(header_file)
        source_file.WriteLine(Concat(Concat("#include \"",self.base_name),".hpp\""))
        source_file.WriteLine("")
        self.WriteBeginingNamespace(source_file)
        source_file.WriteLine("")
        if Size(self.function_definitions)>0:
            self.string_helper.WriteLines(source_file,self.function_definitions)
            source_file.WriteLine("")
        self.WriteEndingNamespace(source_file)

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
        if self.string_helper.BeginsWith("std::unordered_map<std::string, ",cpp_type):
            return ""
        if self.string_helper.BeginsWith("std::vector<",cpp_type):
            return ""
        return "NULL"

    def MakeParametersString(self: 'CPPTranspiler',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'str':
        result: 'str' = "("
        parameters_index: 'int' = 0
        while parameters_index<Size(parameters):
            parameter: 'S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration' = Element(parameters,parameters_index)
            if parameters_index!=0:
                result = Concat(result,", ")
            result = Concat(Concat(Concat(result,parameter.GetType())," "),parameter.GetName())
            parameters_index = parameters_index+1
        result = Concat(result,")")
        return result

