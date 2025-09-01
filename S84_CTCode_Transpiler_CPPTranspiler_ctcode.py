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

class CPPTranspiler(S84_CTCode_Transpiler_ctcode.Transpiler):
    def __init__(self: 'CPPTranspiler'):
        self.saved_unmanaged_types: list[str] = []

    def Transpile(self: 'CPPTranspiler',system: 'S84_CTCode_System_ctcode.System',ct_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile',base_name: 'str') -> 'int':
        logger: 'S84_CTCode_System_ctcode.OutputStream' = system.GetLoggerDestination()
        header: 'S84_CTCode_System_ctcode.OutputStream' = system.OpenFileWriter(Concat(base_name,".hpp"))
        implementation: 'S84_CTCode_System_ctcode.OutputStream' = system.OpenFileWriter(Concat(base_name,".cpp"))
        base_name_tokens: 'list[str]' = self.TokenizeBaseName(base_name)
        self.SetSavedUnmanagedTypes(self.GetUnmanagedTypes(ct_code_file.GetUnmanagedTypes()))
        self.GenerateHeader(ct_code_file,header,base_name_tokens)
        self.GenerateImplementation(ct_code_file,implementation,base_name,base_name_tokens)
        return 0

    def SetSavedUnmanagedTypes(self: 'CPPTranspiler',value: 'list[str]') -> 'None':
        self.saved_unmanaged_types = value

    def IsUnmanagedType(self: 'CPPTranspiler',type_name: 'str') -> 'bool':
        index: 'int' = 0
        while index<Size(self.saved_unmanaged_types):
            if type_name==Element(self.saved_unmanaged_types,index):
                return True
            index = index+1
        return False

    def GenerateHeader(self: 'CPPTranspiler',ctcode_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile',header: 'S84_CTCode_System_ctcode.OutputStream',base_name_tokens: 'list[str]') -> 'None':
        guard_name: 'str' = self.GenerateGuardName(base_name_tokens)
        header.WriteLine(Concat("#ifndef ",guard_name))
        header.WriteLine(Concat("#define ",guard_name))
        header.WriteLine("")
        exdefs: 'list[S84_CTCode_dbnf_ctcode.ExternalDefinition]' = ctcode_file.GetDeclarations()
        index: 'int' = 0
        while index<Size(exdefs):
            exdef: 'S84_CTCode_dbnf_ctcode.ExternalDefinition' = None
            exdef = Element(exdefs,index)
            exdef_name: 'S84_CTCode_dbnf_ctcode.QualfiedName' = None
            exdef_name = exdef.GetExdef()
            header.WriteLine(Concat("#include \"",Concat(self.GetExdefHeaderString(exdef_name),"\"")))
            index = index+1
        header.WriteLine("")
        header.WriteLine("#include <cstring>")
        header.WriteLine("#include <list>")
        header.WriteLine("#include <unordered_map>")
        header.WriteLine("#include <memory>")
        header.WriteLine("#include <string>")
        header.WriteLine("#include <vector>")
        self.WriteCTCodeCommonFunctions(header)
        header.WriteLine("")
        index = 0
        while index<Size(base_name_tokens):
            base_name_token: 'str' = ""
            base_name_token = Element(base_name_tokens,index)
            header.WriteLine(Concat("namespace ",self.ToLower(base_name_token)))
            header.WriteLine("{")
            index = index+1
        header.WriteLine("namespace ctcode")
        header.WriteLine("{")
        self.WriteForwardDeclaration(ctcode_file,header)
        self.WriteClassDeclarations(ctcode_file,header)
        index = 0
        while index<Size(base_name_tokens):
            header.WriteLine("};")
            index = index+1
        header.WriteLine("};")
        header.WriteLine("")
        header.WriteLine("#endif")

    def WriteCTCodeCommonFunctions(self: 'CPPTranspiler',header: 'S84_CTCode_System_ctcode.OutputStream') -> 'None':
        header.WriteLine("")
        header.WriteLine("#ifndef CTCODE_COMMON_FUNCTIONS_VERSION_1")
        header.WriteLine("#define CTCODE_COMMON_FUNCTIONS_VERSION_1")
        header.WriteLine("template<typename T>")
        header.WriteLine("class OmniPointer")
        header.WriteLine("{")
        header.WriteLine("public:")
        header.WriteLine("    OmniPointer() { value_raw = NULL; }")
        header.WriteLine("    OmniPointer(T* value) { value_raw = value; }")
        header.WriteLine("    template<typename U>")
        header.WriteLine("    OmniPointer(U* value) { value_raw = value; }")
        header.WriteLine("    OmniPointer(std::shared_ptr<T> value) { value_raw = NULL; value_shared = value; }")
        header.WriteLine("    template<typename U>")
        header.WriteLine("    OmniPointer(std::shared_ptr<U> value) { value_raw = NULL; value_shared = value; }")
        header.WriteLine("")
        header.WriteLine("    operator bool()")
        header.WriteLine("    {")
        header.WriteLine("        if (value_raw) return true;")
        header.WriteLine("        return value_shared.get() != NULL;")
        header.WriteLine("    }")
        header.WriteLine("    T& operator*()")
        header.WriteLine("    {")
        header.WriteLine("        if (value_raw) return *value_raw;")
        header.WriteLine("        return *value_shared;")
        header.WriteLine("    }")
        header.WriteLine("    T* operator->()")
        header.WriteLine("    {")
        header.WriteLine("        if (value_raw) return value_raw;")
        header.WriteLine("        return value_shared.get();")
        header.WriteLine("    }")
        header.WriteLine("    T* raw()")
        header.WriteLine("    {")
        header.WriteLine("        if (value_raw) return value_raw;")
        header.WriteLine("        return value_shared.get();")
        header.WriteLine("    }")
        header.WriteLine("")
        header.WriteLine("private:")
        header.WriteLine("    T* value_raw;")
        header.WriteLine("    std::shared_ptr<T> value_shared;")
        header.WriteLine("};")
        header.WriteLine("")
        header.WriteLine("template<typename T>")
        header.WriteLine("inline std::vector<T*> UnwrapOmniList(std::vector<OmniPointer<T>> input) {")
        header.WriteLine("	std::vector<T*> result;")
        header.WriteLine("	for (typename std::vector<OmniPointer<T>>::iterator index = input.begin();index != input.end();index++) {")
        header.WriteLine("		result.push_back(index->raw());")
        header.WriteLine("	}")
        header.WriteLine("	return result;")
        header.WriteLine("};")
        header.WriteLine("template<typename T>")
        header.WriteLine("inline void ClearList(std::vector<T>& input) { input.clear(); };")
        header.WriteLine("template<typename T>")
        header.WriteLine("inline int Size(const std::vector<T>& input) { return input.size(); };")
        header.WriteLine("template<typename T>")
        header.WriteLine("inline T Element(const std::vector<T>& input, int element) { return input.at(element); };")
        header.WriteLine("template<typename T>")
        header.WriteLine("inline void Append(std::vector<T>& input, T element) { input.push_back(element); };")
        header.WriteLine("template<typename T>")
        header.WriteLine("inline void ClearMap(std::unordered_map<std::string, T>& input) { input.clear(); };")
        header.WriteLine("template<typename T>")
        header.WriteLine("inline void SetKV(std::unordered_map<std::string, T>& input, const std::string& key, T element)")
        header.WriteLine("{")
        header.WriteLine("    input.erase(key);")
        header.WriteLine("    input.insert(std::pair<std::string, T>(key, element));")
        header.WriteLine("}")
        header.WriteLine("template<typename T>")
        header.WriteLine("inline std::vector<std::string> Keys(const std::unordered_map<std::string, T>& input)")
        header.WriteLine("{")
        header.WriteLine("    std::vector<std::string> result;")
        header.WriteLine("    for(typename std::unordered_map<std::string, T>::const_iterator index = input.begin();index != input.end();index++) {")
        header.WriteLine("        result.push_back(index->first);")
        header.WriteLine("    }")
        header.WriteLine("    return result;")
        header.WriteLine("}")
        header.WriteLine("template<typename T>")
        header.WriteLine("inline bool HasKV(const std::unordered_map<std::string, T>& input, const std::string& key)")
        header.WriteLine("{")
        header.WriteLine("    typename std::unordered_map<std::string, T>::const_iterator beginning = input.find(key);")
        header.WriteLine("    return beginning != input.end();")
        header.WriteLine("}")
        header.WriteLine("template<typename T>")
        header.WriteLine("inline T GetKV(const std::unordered_map<std::string, T>& input, const std::string& key) { return input.at(key); }")
        header.WriteLine("inline int Length(const std::string& input) { return (int)input.length(); };")
        header.WriteLine("inline std::string At(const std::string& input, int index) { return input.substr(index, 1); };")
        header.WriteLine("inline int IntAt(const std::string& input, int index) { return (input.at(index) + 256) % 256; };")
        header.WriteLine("inline std::string Concat(const std::string& left, const std::string& right) { return left + right; };")
        header.WriteLine("#endif")

    def WriteForwardDeclaration(self: 'CPPTranspiler',ctcode_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile',header: 'S84_CTCode_System_ctcode.OutputStream') -> 'None':
        definitions: 'list[S84_CTCode_dbnf_ctcode.Definition]' = ctcode_file.GetDefinitions()
        index: 'int' = 0
        while index<Size(definitions):
            definition: 'S84_CTCode_dbnf_ctcode.Definition' = None
            definition = Element(definitions,index)
            interface_definition: 'S84_CTCode_dbnf_ctcode.InterfaceDef' = definition.GetInterfaceDef()
            class_definition: 'S84_CTCode_dbnf_ctcode.ClassDef' = definition.GetClassDef()
            if interface_definition:
                header.WriteLine(Concat("class ",Concat(self.GenerateClassName(interface_definition.GetName()),";")))
            if class_definition:
                header.WriteLine(Concat("class ",Concat(self.GenerateClassName(class_definition.GetName()),";")))
            index = index+1

    def WriteClassDeclarations(self: 'CPPTranspiler',ctcode_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile',header: 'S84_CTCode_System_ctcode.OutputStream') -> 'None':
        definitions: 'list[S84_CTCode_dbnf_ctcode.Definition]' = ctcode_file.GetDefinitions()
        header.WriteLine("")
        index: 'int' = 0
        index = 0
        while index<Size(definitions):
            definition: 'S84_CTCode_dbnf_ctcode.Definition' = None
            definition = Element(definitions,index)
            if definition.GetInterfaceDef():
                self.WriteInterfaceDeclaration(definition.GetInterfaceDef(),header)
            if definition.GetClassDef():
                self.WriteClassDeclaration(definition.GetClassDef(),header)
            index = index+1

    def WriteInterfaceDeclaration(self: 'CPPTranspiler',interface_definition: 'S84_CTCode_dbnf_ctcode.InterfaceDef',header: 'S84_CTCode_System_ctcode.OutputStream') -> 'None':
        class_name: 'str' = ""
        class_name = self.GenerateClassName(interface_definition.GetName())
        header.WriteLine("")
        header.WriteLine(Concat("class ",class_name))
        header.WriteLine("{")
        header.WriteLine("public:")
        header.WriteLine(Concat("    inline ",Concat(class_name,"() {};")))
        header.WriteLine(Concat("    inline ~",Concat(class_name,"() {};")))
        declarations: 'list[S84_CTCode_dbnf_ctcode.ContentDeclaration]' = interface_definition.GetDeclarations()
        index: 'int' = 0
        index = 0
        if Size(declarations)>0:
            header.WriteLine("")
            while index<Size(declarations):
                declaration: 'S84_CTCode_dbnf_ctcode.ContentDeclaration' = None
                declaration = Element(declarations,index)
                header.WriteLine(Concat("    virtual ",Concat(self.GetType(declaration.GetType()),Concat(" ",Concat(self.GenerateCallName(declaration.GetName()),Concat("(",Concat(self.GenerateParameterList(declaration.GetParameters()),") = 0;")))))))
                index = index+1
        header.WriteLine("};")

    def WriteClassDeclaration(self: 'CPPTranspiler',class_definition: 'S84_CTCode_dbnf_ctcode.ClassDef',header: 'S84_CTCode_System_ctcode.OutputStream') -> 'None':
        class_name: 'str' = ""
        class_name = self.GenerateClassName(class_definition.GetName())
        header.WriteLine("")
        header.WriteLine(Concat("class ",class_name))
        self.WriteImplementationSpec(class_definition.GetImplementing(),header)
        header.WriteLine("{")
        header.WriteLine("public:")
        header.WriteLine(Concat("    inline ",Concat(class_name,"() {};")))
        header.WriteLine(Concat("    inline ~",Concat(class_name,"() {};")))
        definitions: 'list[S84_CTCode_dbnf_ctcode.ContentDefinition]' = class_definition.GetDefinitions()
        function_definitions: 'list[S84_CTCode_dbnf_ctcode.ContentDefinition]' = []
        member_definitions: 'list[S84_CTCode_dbnf_ctcode.ContentDefinition]' = []
        index: 'int' = 0
        index = 0
        while index<Size(definitions):
            definition: 'S84_CTCode_dbnf_ctcode.ContentDefinition' = None
            definition = Element(definitions,index)
            if definition.GetFunctionBody():
                Append(function_definitions,definition)
            else:
                Append(member_definitions,definition)
            index = index+1
        if Size(function_definitions)>0:
            header.WriteLine("")
            index = 0
            while index<Size(function_definitions):
                definition: 'S84_CTCode_dbnf_ctcode.ContentDefinition' = None
                definition = Element(function_definitions,index)
                header.WriteLine(Concat("    ",Concat(self.GetType(definition.GetType()),Concat(" ",Concat(self.GenerateCallName(definition.GetName()),Concat("(",Concat(self.GenerateParameterList(definition.GetParameters()),");")))))))
                index = index+1
        if Size(member_definitions)>0:
            header.WriteLine("")
            header.WriteLine("private:")
            index = 0
            while index<Size(member_definitions):
                definition: 'S84_CTCode_dbnf_ctcode.ContentDefinition' = None
                definition = Element(member_definitions,index)
                header.WriteLine(Concat("    ",Concat(self.GetType(definition.GetType()),Concat(" ",Concat(self.GenerateVariableName(definition.GetName()),";")))))
                index = index+1
        header.WriteLine("};")

    def WriteImplementationSpec(self: 'CPPTranspiler',implementation_spec: 'S84_CTCode_dbnf_ctcode.ImplementationSpec',header: 'S84_CTCode_System_ctcode.OutputStream') -> 'None':
        if implementation_spec:
            qualified_name: 'S84_CTCode_dbnf_ctcode.QualfiedName' = implementation_spec.GetInterface()
            header.WriteLine(Concat(": public ",self.GetRawDefinedType(qualified_name)))

    def GenerateImplementation(self: 'CPPTranspiler',ctcode_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile',implementation: 'S84_CTCode_System_ctcode.OutputStream',base_name: 'str',base_name_tokens: 'list[str]') -> 'None':
        implementation.WriteLine(Concat("#include \"",Concat(base_name,".hpp\"")))
        implementation.WriteLine("")
        exdefs: 'list[S84_CTCode_dbnf_ctcode.ExternalDefinition]' = ctcode_file.GetDeclarations()
        index: 'int' = 0
        index = 0
        while index<Size(exdefs):
            exdef: 'S84_CTCode_dbnf_ctcode.ExternalDefinition' = None
            exdef = Element(exdefs,index)
            exdef_name: 'S84_CTCode_dbnf_ctcode.QualfiedName' = None
            exdef_name = exdef.GetExdef()
            implementation.WriteLine(Concat("#include \"",Concat(self.GetExdefHeaderString(exdef_name),"\"")))
            index = index+1
        implementation.WriteLine("")
        index = 0
        while index<Size(base_name_tokens):
            base_name_token: 'str' = ""
            base_name_token = Element(base_name_tokens,index)
            implementation.WriteLine(Concat("namespace ",self.ToLower(base_name_token)))
            implementation.WriteLine("{")
            index = index+1
        implementation.WriteLine("namespace ctcode")
        implementation.WriteLine("{")
        self.WriteFunctionDefinitions(ctcode_file,implementation)
        index = 0
        while index<Size(base_name_tokens):
            implementation.WriteLine("};")
            index = index+1
        implementation.WriteLine("};")

    def WriteFunctionDefinitions(self: 'CPPTranspiler',ctcode_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile',implementation: 'S84_CTCode_System_ctcode.OutputStream') -> 'None':
        definitions: 'list[S84_CTCode_dbnf_ctcode.Definition]' = ctcode_file.GetDefinitions()
        class_definitions: 'list[S84_CTCode_dbnf_ctcode.ClassDef]' = []
        index: 'int' = 0
        index = 0
        while index<Size(definitions):
            definition: 'S84_CTCode_dbnf_ctcode.Definition' = None
            definition = Element(definitions,index)
            class_definition: 'S84_CTCode_dbnf_ctcode.ClassDef' = None
            class_definition = definition.GetClassDef()
            if class_definition:
                Append(class_definitions,class_definition)
            index = index+1
        index = 0
        while index<Size(class_definitions):
            class_definition: 'S84_CTCode_dbnf_ctcode.ClassDef' = None
            class_definition = Element(class_definitions,index)
            self.WriteClassDefinition(class_definition,implementation)
            index = index+1

    def WriteClassDefinition(self: 'CPPTranspiler',class_definition: 'S84_CTCode_dbnf_ctcode.ClassDef',implementation: 'S84_CTCode_System_ctcode.OutputStream') -> 'None':
        class_name: 'str' = ""
        class_name = self.GenerateClassName(class_definition.GetName())
        definitions: 'list[S84_CTCode_dbnf_ctcode.ContentDefinition]' = class_definition.GetDefinitions()
        function_definitions: 'list[S84_CTCode_dbnf_ctcode.ContentDefinition]' = []
        index: 'int' = 0
        index = 0
        while index<Size(definitions):
            definition: 'S84_CTCode_dbnf_ctcode.ContentDefinition' = None
            definition = Element(definitions,index)
            if definition.GetFunctionBody():
                Append(function_definitions,definition)
            index = index+1
        if Size(function_definitions)>0:
            index = 0
            while index<Size(function_definitions):
                definition: 'S84_CTCode_dbnf_ctcode.ContentDefinition' = None
                definition = Element(function_definitions,index)
                implementation.WriteLine(Concat("    ",Concat(self.GetType(definition.GetType()),Concat(" ",Concat(class_name,Concat("::",Concat(self.GenerateCallName(definition.GetName()),Concat("(",Concat(self.GenerateParameterList(definition.GetParameters()),")")))))))))
                self.WriteCodeBlock(1,implementation,definition.GetFunctionBody(),True)
                index = index+1

    def WriteInstruction(self: 'CPPTranspiler',indent: 'int',implementation: 'S84_CTCode_System_ctcode.OutputStream',instruction: 'S84_CTCode_dbnf_ctcode.Instruction',add_newline_after_code_block: 'bool') -> 'None':
        if instruction.GetCodeBlock():
            self.WriteCodeBlock(indent,implementation,instruction.GetCodeBlock(),add_newline_after_code_block)
        if instruction.GetRtn():
            self.WriteRtn(indent,implementation,instruction.GetRtn())
        if instruction.GetDeclaration():
            self.WriteDeclaration(indent,implementation,instruction.GetDeclaration())
        if instruction.GetAssignment():
            self.WriteAssignment(indent,implementation,instruction.GetAssignment())
        if instruction.GetCall():
            self.WriteCall(indent,implementation,instruction.GetCall())
        if instruction.GetConditional():
            self.WriteConditional(indent,implementation,instruction.GetConditional(),add_newline_after_code_block)
        if instruction.GetLoop():
            self.WriteLoop(indent,implementation,instruction.GetLoop(),add_newline_after_code_block)

    def WriteCodeBlock(self: 'CPPTranspiler',indent: 'int',implementation: 'S84_CTCode_System_ctcode.OutputStream',code_block: 'S84_CTCode_dbnf_ctcode.CodeBlock',add_newline_after_code_block: 'bool') -> 'None':
        implementation.WriteLine(Concat(self.Indentation(indent),"{"))
        instructions: 'list[S84_CTCode_dbnf_ctcode.Instruction]' = code_block.GetInstructions()
        index: 'int' = 0
        index = 0
        last: 'int' = 0
        last = Size(instructions)-1
        while index<Size(instructions):
            self.WriteInstruction(indent+1,implementation,Element(instructions,index),index!=last)
            index = index+1
        implementation.WriteLine(Concat(self.Indentation(indent),"}"))
        if add_newline_after_code_block:
            implementation.WriteLine("")

    def WriteConditional(self: 'CPPTranspiler',indent: 'int',implementation: 'S84_CTCode_System_ctcode.OutputStream',conditional: 'S84_CTCode_dbnf_ctcode.Conditional',add_newline_after_code_block: 'bool') -> 'None':
        implementation.WriteLine(Concat(self.Indentation(indent),Concat("if (",Concat(self.GetRValueString(conditional.GetRValue()),")"))))
        if conditional.GetElseTail():
            else_tail: 'S84_CTCode_dbnf_ctcode.ElseTail' = None
            else_tail = conditional.GetElseTail()
            self.WriteCodeBlock(indent,implementation,conditional.GetCodeBlock(),False)
            implementation.WriteLine(Concat(self.Indentation(indent),"else"))
            self.WriteCodeBlock(indent,implementation,else_tail.GetCodeBlock(),add_newline_after_code_block)
        else:
            self.WriteCodeBlock(indent,implementation,conditional.GetCodeBlock(),add_newline_after_code_block)

    def WriteLoop(self: 'CPPTranspiler',indent: 'int',implementation: 'S84_CTCode_System_ctcode.OutputStream',loop: 'S84_CTCode_dbnf_ctcode.Loop',add_newline_after_code_block: 'bool') -> 'None':
        implementation.WriteLine(Concat(self.Indentation(indent),Concat("while (",Concat(self.GetRValueString(loop.GetRValue()),")"))))
        self.WriteCodeBlock(indent,implementation,loop.GetCodeBlock(),add_newline_after_code_block)

    def WriteRtn(self: 'CPPTranspiler',indent: 'int',implementation: 'S84_CTCode_System_ctcode.OutputStream',rtn: 'S84_CTCode_dbnf_ctcode.Return') -> 'None':
        implementation.WriteLine(Concat(self.Indentation(indent),Concat("return ",Concat(self.GetRValueString(rtn.GetRValue()),";"))))

    def WriteDeclaration(self: 'CPPTranspiler',indent: 'int',implementation: 'S84_CTCode_System_ctcode.OutputStream',declaration: 'S84_CTCode_dbnf_ctcode.Declaration') -> 'None':
        assignment_suffix: 'str' = ""
        assignment_suffix = ""
        if declaration.GetAssignment():
            assignment: 'S84_CTCode_dbnf_ctcode.DeclarationAssign' = None
            assignment = declaration.GetAssignment()
            assignment_suffix = Concat(" = ",self.GetRValueString(assignment.GetRValue()))
        implementation.WriteLine(Concat(self.Indentation(indent),Concat(self.GetVariableDefinition(declaration.GetType(),declaration.GetName()),Concat(assignment_suffix,";"))))

    def WriteAssignment(self: 'CPPTranspiler',indent: 'int',implementation: 'S84_CTCode_System_ctcode.OutputStream',assignment: 'S84_CTCode_dbnf_ctcode.Assignment') -> 'None':
        implementation.WriteLine(Concat(self.Indentation(indent),Concat(self.GenerateVariableChain(assignment.GetLValue()),Concat(" = ",Concat(self.GetRValueString(assignment.GetRValue()),";")))))

    def WriteCall(self: 'CPPTranspiler',indent: 'int',implementation: 'S84_CTCode_System_ctcode.OutputStream',call: 'S84_CTCode_dbnf_ctcode.Call') -> 'None':
        implementation.WriteLine(Concat(self.Indentation(indent),Concat(self.GetCallString(call),";")))

    def GetExdefHeaderString(self: 'CPPTranspiler',exdef_name: 'S84_CTCode_dbnf_ctcode.QualfiedName') -> 'str':
        return Concat(exdef_name.UnParse(),".hpp")

    def GetUnmanagedTypes(self: 'CPPTranspiler',unmanaged_types: 'list[S84_CTCode_dbnf_ctcode.UnmanagedType]') -> 'list[str]':
        unmanaged_type_strings: 'list[str]' = []
        index: 'int' = 0
        index = 0
        while index<Size(unmanaged_types):
            unmanaged_type: 'S84_CTCode_dbnf_ctcode.UnmanagedType' = Element(unmanaged_types,index)
            Append(unmanaged_type_strings,self.GetRawDefinedType(unmanaged_type.GetUnmanagedType()))
            index = index+1
        return unmanaged_type_strings

    def Indentation(self: 'CPPTranspiler',indent: 'int') -> 'str':
        result: 'str' = ""
        result = ""
        while indent>0:
            indent = indent-1
            result = Concat(result,"    ")
        return result

    def GetRValueSingleString(self: 'CPPTranspiler',r_value_single: 'S84_CTCode_dbnf_ctcode.RValueSingle') -> 'str':
        return Concat(self.GetRValueSingleUnaryString(r_value_single),self.GetRValueSingleCoreString(r_value_single))

    def GetRValueSingleUnaryString(self: 'CPPTranspiler',r_value_single: 'S84_CTCode_dbnf_ctcode.RValueSingle') -> 'str':
        if r_value_single.GetUnaryOperator():
            unary_operator: 'S84_CTCode_dbnf_ctcode.UnaryOperator' = None
            unary_operator = r_value_single.GetUnaryOperator()
            if unary_operator.GetNegation():
                return "!"
            return "/*WARNING UnaryOperator FALL THROUGH*/"
        else:
            return ""

    def GetCallString(self: 'CPPTranspiler',call: 'S84_CTCode_dbnf_ctcode.Call') -> 'str':
        result: 'str' = ""
        result = ""
        if call.GetVariable():
            result = Concat(result,Concat(self.GenerateVariableName(call.GetVariable()),"->"))
        if call.GetFunction():
            result = Concat(result,self.GenerateCallName(call.GetFunction()))
        if call.GetFunctionChain():
            function_chain: 'S84_CTCode_dbnf_ctcode.QualfiedName' = call.GetFunctionChain()
            name_tail: 'S84_CTCode_dbnf_ctcode.NameTail' = function_chain.GetTail()
            if function_chain.GetTail():
                result = Concat(Concat(result,self.GenerateVariableName(function_chain.GetName())),"->")
            else:
                result = Concat(result,self.GenerateCallName(function_chain.GetName()))
            while name_tail:
                if name_tail.GetTail():
                    result = Concat(Concat(result,self.GenerateVariableName(name_tail.GetName())),"->")
                else:
                    result = Concat(result,self.GenerateCallName(name_tail.GetName()))
                name_tail = name_tail.GetTail()
        result = Concat(Concat(Concat(result,"("),self.GenerateCallingParameterList(call.GetParameters())),")")
        return result

    def GetRValueSingleCoreString(self: 'CPPTranspiler',r_value_single: 'S84_CTCode_dbnf_ctcode.RValueSingle') -> 'str':
        if r_value_single.GetCall():
            return self.GetCallString(r_value_single.GetCall())
        if r_value_single.GetAllocate():
            allocate: 'S84_CTCode_dbnf_ctcode.Allocate' = r_value_single.GetAllocate()
            raw_type: 'str' = self.GetRawDefinedType(allocate.GetManagedType())
            return Concat("std::shared_ptr<",Concat(raw_type,Concat(">(new ",Concat(raw_type,"())"))))
        if r_value_single.GetByteLiteral():
            return r_value_single.UnParse()
        if r_value_single.GetDecimalLiteral():
            return r_value_single.UnParse()
        if r_value_single.GetIntegerLiteral():
            return r_value_single.UnParse()
        if r_value_single.GetBooleanLiteral():
            return r_value_single.UnParse()
        if r_value_single.GetVariable():
            return self.GenerateVariableChain(r_value_single.GetVariable())
        if r_value_single.GetStringLiteral():
            return Concat(Concat("std::string(",r_value_single.UnParse()),")")
        return "/*WARNING RValueSingle FALL THROUGH*/"

    def GetOperator(self: 'CPPTranspiler',op: 'S84_CTCode_dbnf_ctcode.BinaryOperator') -> 'str':
        if op.GetAddition():
            return "+"
        if op.GetSubtraction():
            return "-"
        if op.GetLessThan():
            return "<"
        if op.GetLessThanEq():
            return "<="
        if op.GetEquality():
            return "=="
        if op.GetNotEquality():
            return "!="
        if op.GetGreaterThanEq():
            return ">="
        if op.GetGreaterThan():
            return ">"
        if op.GetOrOp():
            return "||"
        if op.GetAndOp():
            return "&&"
        return "/*WARNING BinaryOperator FALL THROUGH*/"

    def GetRValueTail(self: 'CPPTranspiler',r_value_tail: 'S84_CTCode_dbnf_ctcode.RValueTail') -> 'str':
        if r_value_tail:
            op: 'S84_CTCode_dbnf_ctcode.BinaryOperator' = None
            op = r_value_tail.GetBinaryOperator()
            return Concat(" ",Concat(self.GetOperator(op),Concat(" ",Concat(self.GetRValueSingleString(r_value_tail.GetValue()),self.GetRValueTail(r_value_tail.GetTail())))))
        return ""

    def GetRValueString(self: 'CPPTranspiler',r_value: 'S84_CTCode_dbnf_ctcode.RValue') -> 'str':
        return Concat(self.GetRValueSingleString(r_value.GetValue()),self.GetRValueTail(r_value.GetTail()))

    def GetVariableDefinition(self: 'CPPTranspiler',type: 'S84_CTCode_dbnf_ctcode.ValueType',name: 'S84_CTCode_dbnf_ctcode.Name') -> 'str':
        return Concat(self.GetType(type),Concat(" ",self.GenerateVariableName(name)))

    def GetParameterString(self: 'CPPTranspiler',parameter: 'S84_CTCode_dbnf_ctcode.ParameterListDef') -> 'str':
        return self.GetVariableDefinition(parameter.GetType(),parameter.GetName())

    def GenerateParameterListTail(self: 'CPPTranspiler',parameters: 'S84_CTCode_dbnf_ctcode.ParameterListDef') -> 'str':
        if parameters:
            return Concat(", ",Concat(self.GetParameterString(parameters),self.GenerateParameterListTail(parameters.GetParameterTail())))
        return ""

    def GenerateParameterList(self: 'CPPTranspiler',parameters: 'S84_CTCode_dbnf_ctcode.ParameterListDef') -> 'str':
        if parameters:
            return Concat(self.GetParameterString(parameters),self.GenerateParameterListTail(parameters.GetParameterTail()))
        else:
            return ""

    def GenerateCallingParameterList(self: 'CPPTranspiler',parameters: 'S84_CTCode_dbnf_ctcode.ParameterList') -> 'str':
        if parameters:
            return Concat(self.GetCallingParameterString(parameters),self.GenerateCallingParameterListTail(parameters.GetParameterTail()))
        else:
            return ""

    def GetCallingParameterString(self: 'CPPTranspiler',parameter: 'S84_CTCode_dbnf_ctcode.ParameterList') -> 'str':
        if parameter:
            return self.GetRValueString(parameter.GetRValue())
        else:
            return ""

    def GenerateCallingParameterListTail(self: 'CPPTranspiler',parameters: 'S84_CTCode_dbnf_ctcode.ParameterList') -> 'str':
        if parameters:
            return Concat(", ",Concat(self.GetCallingParameterString(parameters),self.GenerateCallingParameterListTail(parameters.GetParameterTail())))
        return ""

    def GetType(self: 'CPPTranspiler',value_type: 'S84_CTCode_dbnf_ctcode.ValueType') -> 'str':
        if value_type.GetDimensionalType():
            return self.GetDimensionalType(value_type.GetDimensionalType())
        if value_type.GetMapType():
            return self.GetMapType(value_type.GetMapType())
        if value_type.GetSingletonType():
            return self.GetSingletonType(value_type.GetSingletonType())
        return "/*WARNING ValueType FALL THROUGH*/"

    def GetDimensionalType(self: 'CPPTranspiler',dimensional_type: 'S84_CTCode_dbnf_ctcode.DimensionalType') -> 'str':
        dimensional_note_list: 'list[S84_CTCode_dbnf_ctcode.DimensionalNote]' = []
        dimensional_note_list = dimensional_type.GetDimensionalNote()
        dimensional_notes: 'int' = 0
        dimensional_notes = Size(dimensional_note_list)
        return Concat(self.GetDimensionalPrefix(dimensional_notes),Concat(self.GetSingletonType(dimensional_type.GetSingletonType()),self.GetDimensionalSuffix(dimensional_notes)))

    def GetDimensionalPrefix(self: 'CPPTranspiler',dimensional_notes: 'int') -> 'str':
        dimensional_prefix: 'str' = ""
        dimensional_prefix = ""
        while dimensional_notes>0:
            dimensional_prefix = Concat(dimensional_prefix,"std::vector<")
            dimensional_notes = dimensional_notes-1
        return dimensional_prefix

    def GetDimensionalSuffix(self: 'CPPTranspiler',dimensional_notes: 'int') -> 'str':
        dimensional_suffix: 'str' = ""
        dimensional_suffix = ""
        while dimensional_notes>0:
            dimensional_suffix = Concat(dimensional_suffix,">")
            dimensional_notes = dimensional_notes-1
        return dimensional_suffix

    def GetMapType(self: 'CPPTranspiler',map_type: 'S84_CTCode_dbnf_ctcode.MapType') -> 'str':
        return Concat("std::unordered_map<std::string, ",Concat(self.GetSingletonType(map_type.GetSingletonType()),">"))

    def GetSingletonType(self: 'CPPTranspiler',singleton_type: 'S84_CTCode_dbnf_ctcode.SingletonType') -> 'str':
        if singleton_type.GetDefinedType():
            defined_type: 'S84_CTCode_dbnf_ctcode.DefinedType' = None
            defined_type = singleton_type.GetDefinedType()
            defined_type_name: 'S84_CTCode_dbnf_ctcode.QualfiedName' = None
            defined_type_name = defined_type.GetName()
            return self.GetDefinedType(defined_type_name)
        if singleton_type.GetPrimativeType():
            primative_type: 'S84_CTCode_dbnf_ctcode.PrimativeType' = None
            primative_type = singleton_type.GetPrimativeType()
            primative_type_string: 'str' = ""
            primative_type_string = primative_type.UnParse()
            if primative_type_string=="int":
                return "int"
            if primative_type_string=="string":
                return "std::string"
            if primative_type_string=="bool":
                return "bool"
            if primative_type_string=="float":
                return "float"
            if primative_type_string=="void":
                return "void"
            return "/*WARNING PrimativeType FALL THROUGH*/"
        return "/*WARNING SingletonType FALL THROUGH*/"

    def GetDefinedType(self: 'CPPTranspiler',qualified_name: 'S84_CTCode_dbnf_ctcode.QualfiedName') -> 'str':
        raw_type: 'str' = self.GetRawDefinedType(qualified_name)
        if self.IsUnmanagedType(raw_type):
            return Concat(raw_type,"*")
        else:
            return Concat("OmniPointer<",Concat(raw_type,">"))

    def GetRawDefinedType(self: 'CPPTranspiler',qualified_name: 'S84_CTCode_dbnf_ctcode.QualfiedName') -> 'str':
        name_tail: 'S84_CTCode_dbnf_ctcode.NameTail' = None
        name_tail = qualified_name.GetTail()
        name: 'S84_CTCode_dbnf_ctcode.Name' = None
        name = qualified_name.GetName()
        result: 'str' = ""
        result = ""
        if name_tail:
            name_string: 'str' = ""
            name_string = name.UnParse()
            lower_name_string: 'str' = ""
            lower_name_string = self.ToLower(name_string)
            name_tail_string: 'str' = ""
            name_tail_string = self.GetRawDefinedTypeTail(name_tail)
            result = Concat(result,lower_name_string)
            result = Concat(result,name_tail_string)
        else:
            class_name: 'str' = ""
            class_name = self.GenerateClassName(name)
            result = Concat(result,class_name)
        return result

    def GetRawDefinedTypeTail(self: 'CPPTranspiler',name_tail: 'S84_CTCode_dbnf_ctcode.NameTail') -> 'str':
        name_tail_tail: 'S84_CTCode_dbnf_ctcode.NameTail' = None
        name_tail_tail = name_tail.GetTail()
        name: 'S84_CTCode_dbnf_ctcode.Name' = None
        name = name_tail.GetName()
        result: 'str' = ""
        result = "::"
        if name_tail_tail:
            name_string: 'str' = ""
            name_string = name.UnParse()
            lower_name_string: 'str' = ""
            lower_name_string = self.ToLower(name_string)
            name_tail_tail_string: 'str' = ""
            name_tail_tail_string = self.GetRawDefinedTypeTail(name_tail_tail)
            result = Concat(result,lower_name_string)
            result = Concat(result,name_tail_tail_string)
        else:
            class_name: 'str' = ""
            class_name = self.GenerateClassName(name)
            result = Concat(result,class_name)
        return result

    def GenerateClassName(self: 'CPPTranspiler',name_node: 'S84_CTCode_dbnf_ctcode.Name') -> 'str':
        if name_node:
            name_node_string: 'str' = name_node.UnParse()
            return self.SnakeCaseToCamelCase(name_node_string)
        else:
            return ""

    def GenerateVariableChainNameTail(self: 'CPPTranspiler',name_tail: 'S84_CTCode_dbnf_ctcode.NameTail') -> 'str':
        if name_tail.GetTail():
            return Concat(Concat(self.GenerateVariableName(name_tail.GetName()),"->"),self.GenerateVariableChainNameTail(name_tail.GetTail()))
        else:
            return self.GenerateVariableName(name_tail.GetName())

    def GenerateVariableChain(self: 'CPPTranspiler',qualified_name_node: 'S84_CTCode_dbnf_ctcode.QualfiedName') -> 'str':
        if qualified_name_node.GetTail():
            return Concat(Concat(self.GenerateVariableName(qualified_name_node.GetName()),"->"),self.GenerateVariableChainNameTail(qualified_name_node.GetTail()))
        else:
            return self.GenerateVariableName(qualified_name_node.GetName())

    def GenerateVariableName(self: 'CPPTranspiler',name_node: 'S84_CTCode_dbnf_ctcode.Name') -> 'str':
        if name_node:
            name_node_string: 'str' = name_node.UnParse()
            if name_node_string=="myself":
                return "this"
            return self.CamelCaseToSnakeCase(name_node_string)
        else:
            return ""

    def GenerateCallName(self: 'CPPTranspiler',name_node: 'S84_CTCode_dbnf_ctcode.Name') -> 'str':
        if name_node:
            name_node_string: 'str' = name_node.UnParse()
            return self.SnakeCaseToCamelCase(name_node_string)
        else:
            return ""

    def TokenizeBaseName(self: 'CPPTranspiler',name: 'str') -> 'list[str]':
        base_name_tokens: 'list[str]' = []
        current_token: 'str' = ""
        current_token = ""
        index: 'int' = 0
        index = 0
        while index<Length(name):
            character: 'str' = ""
            character = At(name,index)
            if character==".":
                Append(base_name_tokens,current_token)
                current_token = ""
            else:
                current_token = Concat(current_token,character)
            index = index+1
        return base_name_tokens

    def GenerateGuardName(self: 'CPPTranspiler',base_name_tokens: 'list[str]') -> 'str':
        guard_name: 'str' = ""
        guard_name = ""
        ctcode_guard: 'str' = ""
        ctcode_guard = "CTCODE_H"
        namespace_seperator: 'str' = ""
        namespace_seperator = "_"
        index: 'int' = 0
        index = 0
        while index<Size(base_name_tokens):
            namespace_token: 'str' = ""
            namespace_token = Element(base_name_tokens,index)
            upper_namespace_token: 'str' = ""
            upper_namespace_token = self.ToUpper(namespace_token)
            guard_name = Concat(guard_name,upper_namespace_token)
            guard_name = Concat(guard_name,namespace_seperator)
            index = index+1
        guard_name = Concat(guard_name,ctcode_guard)
        return guard_name

    def SnakeCaseToCamelCase(self: 'CPPTranspiler',snake_case: 'str') -> 'str':
        capitalize_this_letter: 'bool' = False
        capitalize_this_letter = True
        camel_case: 'str' = ""
        camel_case = ""
        index: 'int' = 0
        index = 0
        while index<Length(snake_case):
            source_character: 'str' = ""
            source_character = At(snake_case,index)
            if source_character=="_":
                capitalize_this_letter = True
            else:
                if capitalize_this_letter==True:
                    upper_character: 'str' = ""
                    upper_character = self.CharacterToUpper(source_character)
                    capitalize_this_letter = False
                    camel_case = Concat(camel_case,upper_character)
                else:
                    capitalize_this_letter = False
                    camel_case = Concat(camel_case,source_character)
            index = index+1
        return camel_case

    def CamelCaseToSnakeCase(self: 'CPPTranspiler',camel_case: 'str') -> 'str':
        delimiter: 'str' = ""
        delimiter = "_"
        in_abbreviation: 'bool' = False
        in_abbreviation = True
        snake_case: 'str' = ""
        snake_case = ""
        index: 'int' = 0
        index = 0
        while index<Length(camel_case):
            source_character: 'str' = ""
            source_character = At(camel_case,index)
            lower_character: 'str' = ""
            lower_character = self.CharacterToLower(source_character)
            if self.IsUpper(source_character) or self.IsDigit(source_character):
                is_first_character: 'bool' = False
                is_first_character = Length(snake_case)==0
                if not in_abbreviation and not is_first_character:
                    snake_case = Concat(snake_case,delimiter)
                snake_case = Concat(snake_case,lower_character)
                in_abbreviation = True
            else:
                if source_character==delimiter:
                    snake_case = Concat(snake_case,delimiter)
                    in_abbreviation = True
                else:
                    snake_case = Concat(snake_case,lower_character)
                    in_abbreviation = False
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
        index = 0
        result: 'str' = ""
        result = ""
        while index<Length(input):
            character: 'str' = ""
            character = At(input,index)
            lower_character: 'str' = ""
            lower_character = self.CharacterToLower(character)
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
        index = 0
        result: 'str' = ""
        result = ""
        while index<Length(input):
            character: 'str' = ""
            character = At(input,index)
            upper_character: 'str' = ""
            upper_character = self.CharacterToUpper(character)
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

