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

class Java11Transpiler(S84_CTCode_Transpiler_StandardStructure_ctcode.TargetSpecificFunctions):
    def __init__(self: 'Java11Transpiler'):
        self.system: S84_CTCode_System_ctcode.System = None
        self.c_t_code_file: S84_CTCode_dbnf_ctcode.CTCodeFile = None
        self.base_name: str = ""
        self.logger: S84_CTCode_System_ctcode.OutputStream = None
        self.string_helper: S84_CTCode_Transpiler_StringHelper_ctcode.StringHelper = None
        self.imports: list[str] = []
        self.current_interface: str = ""
        self.interface_definition: list[str] = []
        self.current_class: str = ""
        self.class_definition: list[str] = []
        self.class_init: list[str] = []
        self.class_members: list[str] = []

    def Initialize(self: 'Java11Transpiler') -> 'None':
        self.string_helper = S84_CTCode_Transpiler_StringHelper_ctcode.StringHelper()

    def SetSystem(self: 'Java11Transpiler',system: 'S84_CTCode_System_ctcode.System') -> 'None':
        self.system = system

    def SetCTCodeFile(self: 'Java11Transpiler',c_t_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile') -> 'None':
        self.c_t_code_file = c_t_code_file

    def SetBaseName(self: 'Java11Transpiler',base_name: 'str') -> 'None':
        self.base_name = base_name

    def SetLogger(self: 'Java11Transpiler',logger: 'S84_CTCode_System_ctcode.OutputStream') -> 'None':
        self.logger = logger

    def GetBaseIndentation(self: 'Java11Transpiler') -> 'int':
        return 1

    def GetCallName(self: 'Java11Transpiler',name: 'str') -> 'str':
        return self.string_helper.SnakeCaseToCamelCase(name)

    def IsReserved(self: 'Java11Transpiler',name: 'str') -> 'bool':
        return False or self.string_helper.BeginsWith("reserved_prefix_",name) or name=="boolean" or name=="float"

    def GetVariableName(self: 'Java11Transpiler',name: 'str') -> 'str':
        value: 'str' = self.string_helper.CamelCaseToSnakeCase(name)
        if value=="myself":
            return "this"
        if self.IsReserved(value):
            return Concat("reserved_prefix_",value)
        return value

    def GetVariableChain(self: 'Java11Transpiler',name_parts: 'list[str]') -> 'str':
        delimiter: 'str' = "."
        first_name: 'str' = Element(name_parts,0)
        result: 'str' = self.GetVariableName(first_name)
        name_parts_index: 'int' = 1
        while name_parts_index<Size(name_parts):
            name: 'str' = Element(name_parts,name_parts_index)
            result = Concat(Concat(result,delimiter),self.GetVariableName(name))
            name_parts_index = name_parts_index+1
        return result

    def ConvertCall(self: 'Java11Transpiler',name_chain: 'list[str]',parameters: 'list[str]') -> 'str':
        result: 'str' = Element(name_chain,0)
        name_chain_index: 'int' = 1
        while name_chain_index<Size(name_chain):
            name_part: 'str' = Element(name_chain,name_chain_index)
            result = Concat(Concat(result,"."),name_part)
            name_chain_index = name_chain_index+1
        result = Concat(result,"(")
        if Size(parameters)>0:
            result = Concat(result,Element(parameters,0))
            parameters_index: 'int' = 1
            while parameters_index<Size(parameters):
                parameter: 'str' = Element(parameters,parameters_index)
                result = Concat(result,", ")
                result = Concat(result,parameter)
                parameters_index = parameters_index+1
        result = Concat(result,")")
        return result

    def ConvertAllocate(self: 'Java11Transpiler',type: 'str') -> 'str':
        return Concat(Concat("new ",type),"()")

    def ConvertByte(self: 'Java11Transpiler',high: 'str',low: 'str') -> 'str':
        return Concat(Concat("0x",high),low)

    def ConvertDecimal(self: 'Java11Transpiler',decimal: 'str') -> 'str':
        return decimal

    def ConvertNumber(self: 'Java11Transpiler',number: 'str') -> 'str':
        return number

    def ConvertBoolean(self: 'Java11Transpiler',boolean: 'str') -> 'str':
        if boolean=="true":
            return "true"
        if boolean=="false":
            return "false"
        return ""

    def ConvertVariable(self: 'Java11Transpiler',variable: 'str') -> 'str':
        return variable

    def ConvertString(self: 'Java11Transpiler',literal: 'str') -> 'str':
        return Concat(Concat("\"",literal),"\"")

    def UnaryOperator(self: 'Java11Transpiler',op: 'str',r_value: 'str') -> 'str':
        if op=="!":
            return Concat(Concat("(! AsBoolean(",r_value),"))")
        return r_value

    def BinaryOperator(self: 'Java11Transpiler',op: 'str',r_value_l: 'str',r_value_r: 'str') -> 'str':
        if op=="+":
            return Concat(Concat(Concat(Concat("(",r_value_l),"+"),r_value_r),")")
        if op=="-":
            return Concat(Concat(Concat(Concat("(",r_value_l),"-"),r_value_r),")")
        if op=="<=":
            return Concat(Concat(Concat(Concat("(",r_value_l),"<="),r_value_r),")")
        if op==">=":
            return Concat(Concat(Concat(Concat("(",r_value_l),">="),r_value_r),")")
        if op=="==":
            return Concat(Concat(Concat(Concat("Equals(",r_value_l),","),r_value_r),")")
        if op=="!=":
            return Concat(Concat(Concat(Concat("!Equals(",r_value_l),","),r_value_r),")")
        if op=="<":
            return Concat(Concat(Concat(Concat("(",r_value_l),"<"),r_value_r),")")
        if op==">":
            return Concat(Concat(Concat(Concat("(",r_value_l),">"),r_value_r),")")
        if op=="||":
            return Concat(Concat(Concat(Concat("(AsBoolean(",r_value_l),") || AsBoolean("),r_value_r),"))")
        if op=="&&":
            return Concat(Concat(Concat(Concat("(AsBoolean(",r_value_l),") && AsBoolean("),r_value_r),"))")
        return ""

    def GetTypeName(self: 'Java11Transpiler',name: 'str') -> 'str':
        return self.string_helper.SnakeCaseToCamelCase(name)

    def GetDimensionalType(self: 'Java11Transpiler',singleton_type: 'str',dimensions: 'int') -> 'str':
        result: 'str' = singleton_type
        while dimensions>0:
            result = Concat(Concat("java.util.ArrayList<",result),">")
            dimensions = dimensions-1
        return result

    def GetMapType(self: 'Java11Transpiler',singleton_type: 'str') -> 'str':
        return Concat(Concat("java.util.HashMap<java.lang.String, ",singleton_type),">")

    def GetPrimativeType(self: 'Java11Transpiler',c_t_type: 'str') -> 'str':
        if c_t_type=="int":
            return "int"
        if c_t_type=="string":
            return "java.lang.String"
        if c_t_type=="bool":
            return "boolean"
        if c_t_type=="float":
            return "float"
        if c_t_type=="void":
            return "void"
        return ""

    def GetDefinedType(self: 'Java11Transpiler',c_t_type: 'str') -> 'str':
        return c_t_type

    def GetQualifiedTypeName(self: 'Java11Transpiler',name_parts: 'list[str]') -> 'str':
        delimiter: 'str' = "."
        name_parts_index: 'int' = Size(name_parts)-1
        last_package_index: 'int' = Size(name_parts)-2
        type_part: 'str' = Element(name_parts,name_parts_index)
        result: 'str' = self.GetTypeName(type_part)
        if name_parts_index>0:
            result = Concat(delimiter,result)
            while name_parts_index>0:
                name_parts_index = name_parts_index-1
                name_part: 'str' = Element(name_parts,name_parts_index)
                if name_parts_index!=last_package_index:
                    result = Concat(delimiter,result)
                result = Concat(self.string_helper.ToLower(name_part),result)
        return result

    def BeginProcessingCTCodeFile(self: 'Java11Transpiler') -> 'None':
        ClearList(self.imports)
        self.current_interface = ""
        ClearList(self.interface_definition)
        self.current_class = ""
        ClearList(self.class_definition)
        ClearList(self.class_init)
        ClearList(self.class_members)

    def ProcessExdef(self: 'Java11Transpiler',exdef: 'str') -> 'None':
        Append(self.imports,Concat(Concat("import ",self.string_helper.ToLower(exdef)),".*;"))

    def ProcessUnmanagedType(self: 'Java11Transpiler',unmanaged_type: 'str') -> 'None':
        pass

    def BeginProcessingInterface(self: 'Java11Transpiler',interface_name: 'str') -> 'None':
        ClearList(self.interface_definition)
        self.current_interface = interface_name

    def ProcessInterfaceFunctionDeclaration(self: 'Java11Transpiler',return_type: 'str',function_name: 'str',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'None':
        Append(self.interface_definition,Concat(Concat(Concat(Concat(Concat(self.string_helper.Indentation(1),return_type)," "),function_name),self.MakeParametersString(parameters)),";"))

    def FinishProcessingInterface(self: 'Java11Transpiler',interface_name: 'str') -> 'None':
        destination: 'S84_CTCode_System_ctcode.OutputStream' = self.system.OpenFileWriter(Concat(Concat(Concat(self.string_helper.DotToSlash(self.string_helper.ToLower(self.base_name)),"/"),self.current_interface),".java"))
        destination.WriteLine(Concat(Concat("package ",self.string_helper.ToLower(self.base_name)),";"))
        destination.WriteLine("")
        if Size(self.imports)>0:
            self.string_helper.WriteLines(destination,self.imports)
            destination.WriteLine("")
        destination.WriteLine(Concat(Concat("public interface ",interface_name)," {"))
        self.string_helper.WriteLines(destination,self.interface_definition)
        destination.WriteLine("}")
        self.current_interface = ""

    def BeginProcessingClass(self: 'Java11Transpiler',class_name: 'str',implementing: 'str') -> 'None':
        ClearList(self.class_definition)
        ClearList(self.class_init)
        ClearList(self.class_members)
        self.current_class = class_name
        Append(self.class_init,Concat(Concat(Concat(self.string_helper.Indentation(1),"public "),class_name),"()"))
        Append(self.class_init,Concat(self.string_helper.Indentation(1),"{"))

    def BeginProcessingClassFunctionDefinition(self: 'Java11Transpiler',return_type: 'str',function_name: 'str',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'None':
        Append(self.class_definition,Concat(Concat(Concat(Concat(Concat(self.string_helper.Indentation(1),"public "),return_type)," "),function_name),self.MakeParametersString(parameters)))

    def BeginProcessCodeBlock(self: 'Java11Transpiler',indent: 'int') -> 'None':
        Append(self.class_definition,Concat(self.string_helper.Indentation(indent),"{"))

    def FinishProcessCodeBlock(self: 'Java11Transpiler',indent: 'int') -> 'None':
        Append(self.class_definition,Concat(self.string_helper.Indentation(indent),"}"))

    def BeginProcessConditional(self: 'Java11Transpiler',indent: 'int',r_value: 'str') -> 'None':
        Append(self.class_definition,Concat(Concat(Concat(self.string_helper.Indentation(indent),"if (AsBoolean("),r_value),"))"))

    def ProcessElse(self: 'Java11Transpiler',indent: 'int') -> 'None':
        Append(self.class_definition,Concat(self.string_helper.Indentation(indent),"else"))

    def FinishProcessConditional(self: 'Java11Transpiler',indent: 'int',r_value: 'str') -> 'None':
        pass

    def BeginProcessLoop(self: 'Java11Transpiler',indent: 'int',r_value: 'str') -> 'None':
        Append(self.class_definition,Concat(Concat(Concat(self.string_helper.Indentation(indent),"while (AsBoolean("),r_value),"))"))

    def FinishProcessLoop(self: 'Java11Transpiler',indent: 'int',r_value: 'str') -> 'None':
        pass

    def ProcessRtn(self: 'Java11Transpiler',indent: 'int',r_value: 'str') -> 'None':
        Append(self.class_definition,Concat(Concat(Concat(self.string_helper.Indentation(indent),"return "),r_value),";"))

    def ProcessDeclaration(self: 'Java11Transpiler',indent: 'int',type: 'str',l_value: 'str',r_value: 'str') -> 'None':
        if r_value=="":
            r_value = self.GetDefault(type)
        Append(self.class_definition,Concat(Concat(Concat(Concat(Concat(Concat(self.string_helper.Indentation(indent),type)," "),l_value)," = "),r_value),";"))

    def ProcessAssignment(self: 'Java11Transpiler',indent: 'int',l_value: 'str',r_value: 'str') -> 'None':
        Append(self.class_definition,Concat(Concat(Concat(Concat(self.string_helper.Indentation(indent),l_value)," = "),r_value),";"))

    def ProcessCall(self: 'Java11Transpiler',indent: 'int',call: 'str') -> 'None':
        Append(self.class_definition,Concat(Concat(self.string_helper.Indentation(indent),call),";"))

    def FinishProcessingClassFunctionDefinition(self: 'Java11Transpiler',return_type: 'str',function_name: 'str',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'None':
        Append(self.class_definition,"")

    def ProcessClassMemberDeclaration(self: 'Java11Transpiler',member_type: 'str',member_name: 'str') -> 'None':
        Append(self.class_init,Concat(Concat(Concat(Concat(Concat(self.string_helper.Indentation(2),"this."),member_name)," = "),self.GetDefault(member_type)),";"))
        Append(self.class_members,Concat(Concat(Concat(Concat(Concat(self.string_helper.Indentation(1),"private "),member_type)," "),member_name),";"))

    def FinishProcessingClass(self: 'Java11Transpiler',class_name: 'str',implementing: 'str') -> 'None':
        destination: 'S84_CTCode_System_ctcode.OutputStream' = self.system.OpenFileWriter(Concat(Concat(Concat(self.string_helper.DotToSlash(self.string_helper.ToLower(self.base_name)),"/"),self.current_class),".java"))
        destination.WriteLine(Concat(Concat("package ",self.string_helper.ToLower(self.base_name)),";"))
        destination.WriteLine("")
        if Size(self.imports)>0:
            self.string_helper.WriteLines(destination,self.imports)
            destination.WriteLine("")
        if implementing=="":
            destination.WriteLine(Concat(Concat("public class ",class_name)," {"))
        else:
            destination.WriteLine(Concat(Concat(Concat(Concat("public class ",class_name)," implements "),implementing)," {"))
        self.string_helper.WriteLines(destination,self.class_init)
        destination.WriteLine(Concat(self.string_helper.Indentation(1),"}"))
        destination.WriteLine("")
        self.string_helper.WriteLines(destination,self.class_definition)
        if Size(self.class_members)>0:
            self.string_helper.WriteLines(destination,self.class_members)
            destination.WriteLine("")
        self.WriteCommonFunctions(destination)
        destination.WriteLine("}")
        self.current_class = ""

    def WriteCommonFunctions(self: 'Java11Transpiler',destination_file: 'S84_CTCode_System_ctcode.OutputStream') -> 'None':
        destination_file.WriteLine(Concat(self.string_helper.Indentation(1),"private static <T> void ClearList(java.util.ArrayList<T> input) { input.clear(); }"))
        destination_file.WriteLine(Concat(self.string_helper.Indentation(1),"private static <T> int Size(java.util.ArrayList<T> input) { return input.size(); }"))
        destination_file.WriteLine(Concat(self.string_helper.Indentation(1),"private static <T> T Element(java.util.ArrayList<T> input, int element) { return input.get(element); }"))
        destination_file.WriteLine(Concat(self.string_helper.Indentation(1),"private static <T> void Append(java.util.ArrayList<T> input, T element) { input.add(element); }"))
        destination_file.WriteLine(Concat(self.string_helper.Indentation(1),"private static <T> void ClearMap(java.util.HashMap<java.lang.String, T> input) { input.clear(); }"))
        destination_file.WriteLine(Concat(self.string_helper.Indentation(1),"private static <T> void SetKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key, T element) { input.put(key, element); }"))
        destination_file.WriteLine(Concat(self.string_helper.Indentation(1),"private static <T> java.util.ArrayList<java.lang.String> Keys(java.util.HashMap<java.lang.String, T> input) { return new java.util.ArrayList<>(input.keySet()); }"))
        destination_file.WriteLine(Concat(self.string_helper.Indentation(1),"private static <T> boolean HasKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key) { return input.containsKey(key); }"))
        destination_file.WriteLine(Concat(self.string_helper.Indentation(1),"private static <T> T GetKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key) { return input.get(key); }"))
        destination_file.WriteLine(Concat(self.string_helper.Indentation(1),"private static int Length(java.lang.String input) { return input.length(); }"))
        destination_file.WriteLine(Concat(self.string_helper.Indentation(1),"private static java.lang.String At(java.lang.String input, int index) { try { return input.substring(index, index + 1);} catch(Exception e) { return \"\"; }}"))
        destination_file.WriteLine(Concat(self.string_helper.Indentation(1),"private static int IntAt(java.lang.String input, int index) { return (int)input.charAt(index); }"))
        destination_file.WriteLine(Concat(self.string_helper.Indentation(1),"private static java.lang.String Concat(java.lang.String left, java.lang.String right) { return left + right; }"))
        destination_file.WriteLine(Concat(self.string_helper.Indentation(1),"private static <T extends Object> boolean AsBoolean(T value) { return value != null; }"))
        destination_file.WriteLine(Concat(self.string_helper.Indentation(1),"private static boolean AsBoolean(boolean value) { return value; }"))
        destination_file.WriteLine(Concat(self.string_helper.Indentation(1),"private static boolean Equals(java.lang.String left, java.lang.String right) { return left.equals(right); }"))
        destination_file.WriteLine(Concat(self.string_helper.Indentation(1),"private static boolean Equals(boolean left, boolean right) { return left == right; }"))
        destination_file.WriteLine(Concat(self.string_helper.Indentation(1),"private static boolean Equals(int left, int right) { return left == right; }"))
        destination_file.WriteLine(Concat(self.string_helper.Indentation(1),"private static boolean Equals(float left, float right) { return left == right; }"))

    def FinishProcessingCTCodeFile(self: 'Java11Transpiler') -> 'None':
        pass

    def GetDefault(self: 'Java11Transpiler',java_type: 'str') -> 'str':
        if java_type=="int":
            return "0"
        if java_type=="java.lang.String":
            return "\"\""
        if java_type=="boolean":
            return "false"
        if java_type=="float":
            return "0.0"
        if java_type=="void":
            return "null"
        if self.string_helper.BeginsWith("java.util.HashMap<java.lang.String",java_type):
            return "new java.util.HashMap<>()"
        if self.string_helper.BeginsWith("java.util.ArrayList<",java_type):
            return "new java.util.ArrayList<>()"
        return "null"

    def MakeParametersString(self: 'Java11Transpiler',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'str':
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

