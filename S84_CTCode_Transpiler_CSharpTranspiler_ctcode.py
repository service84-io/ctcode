import S84_CTCode_dbnf_ctcode
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

class CSharpTranspiler(S84_CTCode_Transpiler_StandardStructure_ctcode.TargetSpecificFunctions):
    def __init__(self: 'CSharpTranspiler'):
        self.system: S84_CTCode_System_ctcode.System = None
        self.c_t_code_file: S84_CTCode_dbnf_ctcode.CTCodeFile = None
        self.base_name: str = ""
        self.logger: S84_CTCode_System_ctcode.OutputStream = None
        self.string_helper: S84_CTCode_Transpiler_StringHelper_ctcode.StringHelper = None
        self.imports: list[str] = []
        self.current_interface: str = ""
        self.interface_definitions: list[str] = []
        self.current_class: str = ""
        self.class_definitions: list[str] = []
        self.class_members: list[str] = []
        self.class_init: list[str] = []
        self.class_functions: list[str] = []

    def Initialize(self: 'CSharpTranspiler') -> 'None':
        self.string_helper = S84_CTCode_Transpiler_StringHelper_ctcode.StringHelper()

    def SetSystem(self: 'CSharpTranspiler',system: 'S84_CTCode_System_ctcode.System') -> 'None':
        self.system = system

    def SetCTCodeFile(self: 'CSharpTranspiler',c_t_code_file: 'S84_CTCode_dbnf_ctcode.CTCodeFile') -> 'None':
        self.c_t_code_file = c_t_code_file

    def SetBaseName(self: 'CSharpTranspiler',base_name: 'str') -> 'None':
        self.base_name = base_name

    def SetLogger(self: 'CSharpTranspiler',logger: 'S84_CTCode_System_ctcode.OutputStream') -> 'None':
        self.logger = logger

    def GetBaseIndentation(self: 'CSharpTranspiler') -> 'int':
        return 1

    def GetCallName(self: 'CSharpTranspiler',name: 'str') -> 'str':
        value: 'str' = self.string_helper.SnakeCaseToCamelCase(name)
        if self.string_helper.IsReserved(value):
            return Concat("ReservedPrefix",value)
        return value

    def GetVariableName(self: 'CSharpTranspiler',name: 'str') -> 'str':
        value: 'str' = self.string_helper.CamelCaseToSnakeCase(name)
        if value=="myself":
            return "this"
        if self.string_helper.IsReserved(value):
            return Concat("reserved_prefix_",value)
        return value

    def GetVariableChain(self: 'CSharpTranspiler',name_parts: 'list[str]') -> 'str':
        delimiter: 'str' = "."
        first_name: 'str' = Element(name_parts,0)
        result: 'str' = self.GetVariableName(first_name)
        name_parts_index: 'int' = 1
        while name_parts_index<Size(name_parts):
            name: 'str' = Element(name_parts,name_parts_index)
            result = Concat(Concat(result,delimiter),self.GetVariableName(name))
            name_parts_index = name_parts_index+1
        return result

    def ConvertCall(self: 'CSharpTranspiler',name_chain: 'list[str]',parameters: 'list[str]') -> 'str':
        result: 'str' = Element(name_chain,0)
        name_chain_index: 'int' = 1
        while name_chain_index<Size(name_chain):
            name_part: 'str' = Element(name_chain,name_chain_index)
            result = Concat(Concat(result,"?."),name_part)
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

    def ConvertAllocate(self: 'CSharpTranspiler',type: 'str') -> 'str':
        return Concat(Concat("new ",type),"()")

    def ConvertByte(self: 'CSharpTranspiler',high: 'str',low: 'str') -> 'str':
        return Concat(Concat("0x",high),low)

    def ConvertDecimal(self: 'CSharpTranspiler',reserved_prefix_decimal: 'str') -> 'str':
        return reserved_prefix_decimal

    def ConvertNumber(self: 'CSharpTranspiler',number: 'str') -> 'str':
        return number

    def ConvertBoolean(self: 'CSharpTranspiler',reserved_prefix_boolean: 'str') -> 'str':
        if reserved_prefix_boolean=="true":
            return "true"
        if reserved_prefix_boolean=="false":
            return "false"
        return ""

    def ConvertVariable(self: 'CSharpTranspiler',variable: 'str') -> 'str':
        result: 'str' = ""
        variable_index: 'int' = 0
        while variable_index<Length(variable):
            character: 'str' = At(variable,variable_index)
            if character==".":
                result = Concat(result,"?")
            result = Concat(result,character)
            variable_index = variable_index+1
        return result

    def ConvertString(self: 'CSharpTranspiler',literal: 'str') -> 'str':
        return Concat(Concat("\"",literal),"\"")

    def UnaryOperator(self: 'CSharpTranspiler',op: 'str',r_value: 'str') -> 'str':
        if op=="!":
            return Concat("!",r_value)
        return r_value

    def BinaryOperator(self: 'CSharpTranspiler',op: 'str',r_value_l: 'str',r_value_r: 'str') -> 'str':
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
            return Concat(Concat(Concat(Concat("AsBoolean(",r_value_l),")||AsBoolean("),r_value_r),")")
        if op=="&&":
            return Concat(Concat(Concat(Concat("AsBoolean(",r_value_l),")&&AsBoolean("),r_value_r),")")
        return ""

    def GetTypeName(self: 'CSharpTranspiler',name: 'str') -> 'str':
        value: 'str' = self.string_helper.SnakeCaseToCamelCase(name)
        if self.string_helper.IsReserved(value):
            return Concat("ReservedPrefix",value)
        return value

    def GetDimensionalType(self: 'CSharpTranspiler',singleton_type: 'str',dimensions: 'int') -> 'str':
        result: 'str' = singleton_type
        while dimensions>0:
            result = Concat(Concat("List<",result),">?")
            dimensions = dimensions-1
        return result

    def GetMapType(self: 'CSharpTranspiler',singleton_type: 'str') -> 'str':
        return Concat(Concat("Dictionary<string,",singleton_type),">?")

    def GetPrimativeType(self: 'CSharpTranspiler',c_t_type: 'str') -> 'str':
        if c_t_type=="int":
            return "int?"
        if c_t_type=="string":
            return "string?"
        if c_t_type=="bool":
            return "bool?"
        if c_t_type=="float":
            return "float?"
        if c_t_type=="void":
            return "void"
        return ""

    def GetDefinedType(self: 'CSharpTranspiler',c_t_type: 'str') -> 'str':
        return Concat(c_t_type,"?")

    def GetQualifiedTypeName(self: 'CSharpTranspiler',name_parts: 'list[str]') -> 'str':
        delimiter: 'str' = "."
        name_parts_index: 'int' = Size(name_parts)-1
        type_part: 'str' = Element(name_parts,name_parts_index)
        result: 'str' = self.GetTypeName(type_part)
        if name_parts_index>0:
            while name_parts_index>0:
                name_parts_index = name_parts_index-1
                result = Concat(delimiter,result)
                name_part: 'str' = Element(name_parts,name_parts_index)
                result = Concat(name_part,result)
        return result

    def BeginProcessingCTCodeFile(self: 'CSharpTranspiler') -> 'None':
        ClearList(self.imports)
        self.current_interface = ""
        ClearList(self.interface_definitions)
        self.current_class = ""
        ClearList(self.class_definitions)
        ClearList(self.class_members)
        ClearList(self.class_init)
        ClearList(self.class_functions)

    def FinishProcessingCTCodeFile(self: 'CSharpTranspiler') -> 'None':
        destination_file_name: 'str' = Concat(self.base_name,".cs")
        destination_file: 'S84_CTCode_System_ctcode.OutputStream' = self.system.OpenFileWriter(destination_file_name)
        destination_file.WriteLine(Concat(Concat("namespace ",self.base_name),";"))
        destination_file.WriteLine("")
        self.string_helper.WriteLines(destination_file,self.interface_definitions)
        self.string_helper.WriteLines(destination_file,self.class_definitions)

    def ProcessExdef(self: 'CSharpTranspiler',exdef: 'str') -> 'None':
        Append(self.imports,Concat(Concat("using ",exdef),";"))

    def ProcessUnmanagedType(self: 'CSharpTranspiler',unmanaged_type: 'str') -> 'None':
        pass

    def BeginProcessingInterface(self: 'CSharpTranspiler',interface_name: 'str') -> 'None':
        self.current_interface = interface_name
        Append(self.interface_definitions,Concat("public interface ",interface_name))
        Append(self.interface_definitions,"{")

    def ProcessInterfaceFunctionDeclaration(self: 'CSharpTranspiler',return_type: 'str',function_name: 'str',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'None':
        Append(self.interface_definitions,Concat(Concat(Concat(Concat(Concat(self.string_helper.Indentation(1),return_type)," "),function_name),self.MakeParametersString(self.current_interface,parameters)),";"))

    def FinishProcessingInterface(self: 'CSharpTranspiler',interface_name: 'str') -> 'None':
        Append(self.interface_definitions,"}")
        Append(self.interface_definitions,"")
        self.current_interface = ""

    def BeginProcessingClass(self: 'CSharpTranspiler',class_name: 'str',implementing: 'str') -> 'None':
        self.current_class = class_name
        if implementing=="":
            Append(self.class_definitions,Concat("public class ",class_name))
        else:
            Append(self.class_definitions,Concat(Concat(Concat("public class ",class_name)," : "),implementing))
        Append(self.class_definitions,"{")
        ClearList(self.class_members)
        ClearList(self.class_init)
        ClearList(self.class_functions)
        Append(self.class_init,Concat(Concat(Concat(self.string_helper.Indentation(1),"public "),class_name),"()"))
        Append(self.class_init,Concat(self.string_helper.Indentation(1),"{"))

    def BeginProcessingClassFunctionDefinition(self: 'CSharpTranspiler',return_type: 'str',function_name: 'str',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(Concat(Concat(self.string_helper.Indentation(1),"public "),return_type)," "),function_name),self.MakeParametersString(self.current_class,parameters)))

    def BeginProcessCodeBlock(self: 'CSharpTranspiler',indent: 'int') -> 'None':
        Append(self.class_functions,Concat(self.string_helper.Indentation(indent),"{"))

    def FinishProcessCodeBlock(self: 'CSharpTranspiler',indent: 'int') -> 'None':
        Append(self.class_functions,Concat(self.string_helper.Indentation(indent),"}"))

    def BeginProcessConditional(self: 'CSharpTranspiler',indent: 'int',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(self.string_helper.Indentation(indent),"if (AsBoolean("),r_value),"))"))

    def ProcessElse(self: 'CSharpTranspiler',indent: 'int') -> 'None':
        Append(self.class_functions,Concat(self.string_helper.Indentation(indent),"else"))

    def FinishProcessConditional(self: 'CSharpTranspiler',indent: 'int',r_value: 'str') -> 'None':
        pass

    def BeginProcessLoop(self: 'CSharpTranspiler',indent: 'int',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(self.string_helper.Indentation(indent),"while (AsBoolean("),r_value),"))"))

    def FinishProcessLoop(self: 'CSharpTranspiler',indent: 'int',r_value: 'str') -> 'None':
        pass

    def ProcessRtn(self: 'CSharpTranspiler',indent: 'int',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(self.string_helper.Indentation(indent),"return "),r_value),";"))

    def ProcessDeclaration(self: 'CSharpTranspiler',indent: 'int',type: 'str',l_value: 'str',r_value: 'str') -> 'None':
        if r_value=="":
            r_value = self.GetDefault(type)
        Append(self.class_functions,Concat(Concat(Concat(Concat(Concat(Concat(self.string_helper.Indentation(indent),type)," "),l_value)," = "),r_value),";"))

    def ProcessAssignment(self: 'CSharpTranspiler',indent: 'int',l_value: 'str',r_value: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(Concat(Concat(self.string_helper.Indentation(indent),l_value)," = "),r_value),";"))

    def ProcessCall(self: 'CSharpTranspiler',indent: 'int',call: 'str') -> 'None':
        Append(self.class_functions,Concat(Concat(self.string_helper.Indentation(indent),call),";"))

    def FinishProcessingClassFunctionDefinition(self: 'CSharpTranspiler',return_type: 'str',function_name: 'str',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'None':
        Append(self.class_functions,"")

    def ProcessClassMemberDeclaration(self: 'CSharpTranspiler',member_type: 'str',member_name: 'str') -> 'None':
        Append(self.class_init,Concat(Concat(Concat(Concat(Concat(self.string_helper.Indentation(2),"this."),member_name)," = "),self.GetDefault(member_type)),";"))
        Append(self.class_members,Concat(Concat(Concat(Concat(Concat(self.string_helper.Indentation(1),"private "),member_type)," "),member_name),";"))

    def FinishProcessingClass(self: 'CSharpTranspiler',class_name: 'str',implementing: 'str') -> 'None':
        if Size(self.class_members)>0:
            class_members_index: 'int' = 0
            while class_members_index<Size(self.class_members):
                line: 'str' = Element(self.class_members,class_members_index)
                Append(self.class_definitions,line)
                class_members_index = class_members_index+1
            Append(self.class_definitions,"")
        Append(self.class_init,Concat(self.string_helper.Indentation(1),"}"))
        class_init_index: 'int' = 0
        while class_init_index<Size(self.class_init):
            line: 'str' = Element(self.class_init,class_init_index)
            Append(self.class_definitions,line)
            class_init_index = class_init_index+1
        Append(self.class_definitions,"")
        class_functions_index: 'int' = 0
        while class_functions_index<Size(self.class_functions):
            line: 'str' = Element(self.class_functions,class_functions_index)
            Append(self.class_definitions,line)
            class_functions_index = class_functions_index+1
        self.WriteCommonFunctions()
        Append(self.class_definitions,"}")
        self.current_class = ""

    def WriteCommonFunctions(self: 'CSharpTranspiler') -> 'None':
        Append(self.class_definitions,Concat(self.string_helper.Indentation(1),"private static void ClearList<T>(List<T>? input) { input?.Clear(); }"))
        Append(self.class_definitions,Concat(self.string_helper.Indentation(1),"private static int? Size<T>(List<T>? input) { return input?.Count; }"))
        Append(self.class_definitions,Concat(self.string_helper.Indentation(1),"private static T? Element<T>(List<T>? input, int? element) { return input != null ? input[element??0] : default; }"))
        Append(self.class_definitions,Concat(self.string_helper.Indentation(1),"private static void Append<T>(List<T>? input, T element) { input?.Add(element); }"))
        Append(self.class_definitions,Concat(self.string_helper.Indentation(1),"private static void ClearMap<T>(Dictionary<string, T>? input) { input?.Clear();  }"))
        Append(self.class_definitions,Concat(self.string_helper.Indentation(1),"private static void SetKV<T>(Dictionary<string, T>? input, string? key, T element) { input?.Add(key??\"\", element); }"))
        Append(self.class_definitions,Concat(self.string_helper.Indentation(1),"private static List<string?>? Keys<T>(Dictionary<string, T>? input) { return new List<string?>(input?.Keys?.ToList()??new List<string>()); }"))
        Append(self.class_definitions,Concat(self.string_helper.Indentation(1),"private static bool? HasKV<T>(Dictionary<string, T>? input, string? key) { return input?.ContainsKey(key??\"\"); }"))
        Append(self.class_definitions,Concat(self.string_helper.Indentation(1),"private static T? GetKV<T>(Dictionary<string, T>? input, string? key) { return input != null ? input[key??\"\"] : default; }"))
        Append(self.class_definitions,Concat(self.string_helper.Indentation(1),"private static int? Length(string? input) { return input?.Length;  }"))
        Append(self.class_definitions,Concat(self.string_helper.Indentation(1),"private static string? At(string? input, int? index) { return input?.Length > index ? input?.Substring(index??0, 1) : \"\";  }"))
        Append(self.class_definitions,Concat(self.string_helper.Indentation(1),"private static int? IntAt(string? input, int? index) { return input?.Length > index ? (input[index??0] + 255 % 255) : 0;  }"))
        Append(self.class_definitions,Concat(self.string_helper.Indentation(1),"private static string? Concat(string? left, string? right) { return left + right; }"))
        Append(self.class_definitions,Concat(self.string_helper.Indentation(1),"private static bool AsBoolean(bool value) { return value; }"))
        Append(self.class_definitions,Concat(self.string_helper.Indentation(1),"private static bool AsBoolean<T>(T? value) { return value != null && !value.Equals(false); }"))

    def StripLast(self: 'CSharpTranspiler',input: 'str') -> 'str':
        result: 'str' = ""
        index: 'int' = Length(input)-1
        while index>0:
            index = index-1
            result = Concat(At(input,index),result)
        return result

    def GetDefault(self: 'CSharpTranspiler',csharp_type: 'str') -> 'str':
        if csharp_type=="int?":
            return "0"
        if csharp_type=="string?":
            return "\"\""
        if csharp_type=="bool?":
            return "false"
        if csharp_type=="float?":
            return "0.0"
        if csharp_type=="void":
            return "void"
        if self.string_helper.BeginsWith("Dictionary<string,",csharp_type):
            return Concat(Concat("new ",self.StripLast(csharp_type)),"()")
        if self.string_helper.BeginsWith("List<",csharp_type):
            return Concat(Concat("new ",self.StripLast(csharp_type)),"()")
        return "null"

    def MakeParametersString(self: 'CSharpTranspiler',self_type: 'str',parameters: 'list[S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration]') -> 'str':
        result: 'str' = "("
        parameters_index: 'int' = 0
        while parameters_index<Size(parameters):
            parameter: 'S84_CTCode_Transpiler_StandardStructure_ctcode.ParameterDeclaration' = Element(parameters,parameters_index)
            if parameters_index!=0:
                result = Concat(result,",")
            result = Concat(Concat(Concat(result,parameter.ReservedPrefixGetType())," "),parameter.GetName())
            parameters_index = parameters_index+1
        result = Concat(result,")")
        return result

