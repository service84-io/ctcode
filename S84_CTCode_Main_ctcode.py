import S84_CTCode_System_ctcode
import S84_CTCode_Transpiler_ctcode
import S84_CTCode_dbnf_ctcode
import S84_CTCode_Transpiler_StandardStructure_ctcode
import S84_CTCode_Transpiler_CPPTranspiler_ctcode
import S84_CTCode_Transpiler_CSharpTranspiler_ctcode
import S84_CTCode_Transpiler_Java11Transpiler_ctcode
import S84_CTCode_Transpiler_LogToConsole_ctcode
import S84_CTCode_Transpiler_NodeJSTranspiler_ctcode
import S84_CTCode_Transpiler_PHPTranspiler_ctcode
import S84_CTCode_Transpiler_Python3Transpiler_ctcode
import S84_CTCode_Transpiler_RubyTranspiler_ctcode

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

class Main:
    def __init__(self: 'Main'):
        pass

    def GetCPPTranspiler(self: 'Main') -> 'S84_CTCode_Transpiler_ctcode.Transpiler':
        specific: 'S84_CTCode_Transpiler_CPPTranspiler_ctcode.CPPTranspiler' = S84_CTCode_Transpiler_CPPTranspiler_ctcode.CPPTranspiler()
        specific.Initialize()
        structue: 'S84_CTCode_Transpiler_StandardStructure_ctcode.StandardStructure' = S84_CTCode_Transpiler_StandardStructure_ctcode.StandardStructure()
        structue.SetTargetSpecificFunctions(specific)
        return structue

    def GetCSharpTranspiler(self: 'Main') -> 'S84_CTCode_Transpiler_ctcode.Transpiler':
        specific: 'S84_CTCode_Transpiler_CSharpTranspiler_ctcode.CSharpTranspiler' = S84_CTCode_Transpiler_CSharpTranspiler_ctcode.CSharpTranspiler()
        specific.Initialize()
        structue: 'S84_CTCode_Transpiler_StandardStructure_ctcode.StandardStructure' = S84_CTCode_Transpiler_StandardStructure_ctcode.StandardStructure()
        structue.SetTargetSpecificFunctions(specific)
        return structue

    def GetJava11Transpiler(self: 'Main') -> 'S84_CTCode_Transpiler_ctcode.Transpiler':
        specific: 'S84_CTCode_Transpiler_Java11Transpiler_ctcode.Java11Transpiler' = S84_CTCode_Transpiler_Java11Transpiler_ctcode.Java11Transpiler()
        specific.Initialize()
        structue: 'S84_CTCode_Transpiler_StandardStructure_ctcode.StandardStructure' = S84_CTCode_Transpiler_StandardStructure_ctcode.StandardStructure()
        structue.SetTargetSpecificFunctions(specific)
        return structue

    def GetLogToConsole(self: 'Main') -> 'S84_CTCode_Transpiler_ctcode.Transpiler':
        specific: 'S84_CTCode_Transpiler_LogToConsole_ctcode.LogToConsole' = S84_CTCode_Transpiler_LogToConsole_ctcode.LogToConsole()
        specific.Initialize()
        structue: 'S84_CTCode_Transpiler_StandardStructure_ctcode.StandardStructure' = S84_CTCode_Transpiler_StandardStructure_ctcode.StandardStructure()
        structue.SetTargetSpecificFunctions(specific)
        return structue

    def GetNodeJSTranspiler(self: 'Main') -> 'S84_CTCode_Transpiler_ctcode.Transpiler':
        specific: 'S84_CTCode_Transpiler_NodeJSTranspiler_ctcode.NodeJSTranspiler' = S84_CTCode_Transpiler_NodeJSTranspiler_ctcode.NodeJSTranspiler()
        specific.Initialize()
        structue: 'S84_CTCode_Transpiler_StandardStructure_ctcode.StandardStructure' = S84_CTCode_Transpiler_StandardStructure_ctcode.StandardStructure()
        structue.SetTargetSpecificFunctions(specific)
        return structue

    def GetPHPTranspiler(self: 'Main') -> 'S84_CTCode_Transpiler_ctcode.Transpiler':
        specific: 'S84_CTCode_Transpiler_PHPTranspiler_ctcode.PHPTranspiler' = S84_CTCode_Transpiler_PHPTranspiler_ctcode.PHPTranspiler()
        specific.Initialize()
        structue: 'S84_CTCode_Transpiler_StandardStructure_ctcode.StandardStructure' = S84_CTCode_Transpiler_StandardStructure_ctcode.StandardStructure()
        structue.SetTargetSpecificFunctions(specific)
        return structue

    def GetPython3Transpiler(self: 'Main') -> 'S84_CTCode_Transpiler_ctcode.Transpiler':
        specific: 'S84_CTCode_Transpiler_Python3Transpiler_ctcode.Python3Transpiler' = S84_CTCode_Transpiler_Python3Transpiler_ctcode.Python3Transpiler()
        specific.Initialize()
        structue: 'S84_CTCode_Transpiler_StandardStructure_ctcode.StandardStructure' = S84_CTCode_Transpiler_StandardStructure_ctcode.StandardStructure()
        structue.SetTargetSpecificFunctions(specific)
        return structue

    def GetRubyTranspiler(self: 'Main') -> 'S84_CTCode_Transpiler_ctcode.Transpiler':
        specific: 'S84_CTCode_Transpiler_RubyTranspiler_ctcode.RubyTranspiler' = S84_CTCode_Transpiler_RubyTranspiler_ctcode.RubyTranspiler()
        specific.Initialize()
        structue: 'S84_CTCode_Transpiler_StandardStructure_ctcode.StandardStructure' = S84_CTCode_Transpiler_StandardStructure_ctcode.StandardStructure()
        structue.SetTargetSpecificFunctions(specific)
        return structue

    def RunMain(self: 'Main',system: 'S84_CTCode_System_ctcode.System',ctcode_file_name: 'str',transpiler: 'str') -> 'int':
        logger: 'S84_CTCode_System_ctcode.OutputStream' = system.GetLoggerDestination()
        transpilers: 'dict[str, S84_CTCode_Transpiler_ctcode.Transpiler]' = {}
        SetKV(transpilers,"CPPTranspiler",self.GetCPPTranspiler())
        SetKV(transpilers,"CSharpTranspiler",self.GetCSharpTranspiler())
        SetKV(transpilers,"Java11Transpiler",self.GetJava11Transpiler())
        SetKV(transpilers,"LogToConsole",self.GetLogToConsole())
        SetKV(transpilers,"NodeJSTranspiler",self.GetNodeJSTranspiler())
        SetKV(transpilers,"PHPTranspiler",self.GetPHPTranspiler())
        SetKV(transpilers,"Python3Transpiler",self.GetPython3Transpiler())
        SetKV(transpilers,"RubyTranspiler",self.GetRubyTranspiler())
        if ctcode_file_name=="" or not HasKV(transpilers,transpiler):
            logger.WriteLine("ctcode <CTCodeFile> <Transpiler>")
            logger.WriteLine("Known transpilers:")
            registered_transpilers: 'list[str]' = Keys(transpilers)
            registered_transpilers_index: 'int' = 0
            while registered_transpilers_index<Size(registered_transpilers):
                logger.WriteLine(Concat("    ",Element(registered_transpilers,registered_transpilers_index)))
                registered_transpilers_index = registered_transpilers_index+1
            return 1
        dbnf: 'str' = system.ReadFileToString(ctcode_file_name)
        if dbnf=="":
            logger.WriteLine(Concat("The file ",Concat(ctcode_file_name," is empty or does not exist.")))
            return 1
        dbnf_large_string: 'S84_CTCode_dbnf_ctcode.LargeString' = S84_CTCode_dbnf_ctcode.LargeString()
        dbnf_large_string.SetData(dbnf)
        index: 'S84_CTCode_dbnf_ctcode.LengthString' = S84_CTCode_dbnf_ctcode.LengthString()
        index.SetData(dbnf_large_string)
        index.SetStart(0)
        index.SetLength(Length(dbnf))
        parser_network: 'S84_CTCode_dbnf_ctcode.ParserNetwork' = S84_CTCode_dbnf_ctcode.ParserNetwork()
        parser_network.Initialize()
        ctcode_file_result: 'S84_CTCode_dbnf_ctcode.CTCodeFileResult' = S84_CTCode_dbnf_ctcode.CTCodeFileResult()
        ctcode_file_parser: 'S84_CTCode_dbnf_ctcode.CTCodeFileParser' = parser_network.GetCTCodeFileParser()
        logger.WriteLine("Parsing CTCodeFile...")
        ctcode_file_parser.ParseSingleSave(index,ctcode_file_result)
        if ctcode_file_result.GetResult() and index.GetLength()==0:
            logger.WriteLine("Done Parsing CTCodeFile!")
            target_transpiler: 'S84_CTCode_Transpiler_ctcode.Transpiler' = GetKV(transpilers,transpiler)
            return target_transpiler.Transpile(system,ctcode_file_result.GetValue(),ctcode_file_name)
        else:
            logger.WriteLine(Concat("Failed to parse ",Concat(ctcode_file_name,".")))
            return 1

