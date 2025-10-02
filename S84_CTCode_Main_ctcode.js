import * as S84_CTCode_System_ctcode from "./S84_CTCode_System_ctcode.js"
import * as S84_CTCode_Transpiler_ctcode from "./S84_CTCode_Transpiler_ctcode.js"
import * as S84_CTCode_dbnf_ctcode from "./S84_CTCode_dbnf_ctcode.js"
import * as S84_CTCode_Transpiler_StandardStructure_ctcode from "./S84_CTCode_Transpiler_StandardStructure_ctcode.js"
import * as S84_CTCode_Transpiler_CPPTranspiler_ctcode from "./S84_CTCode_Transpiler_CPPTranspiler_ctcode.js"
import * as S84_CTCode_Transpiler_CSharpTranspiler_ctcode from "./S84_CTCode_Transpiler_CSharpTranspiler_ctcode.js"
import * as S84_CTCode_Transpiler_Java11Transpiler_ctcode from "./S84_CTCode_Transpiler_Java11Transpiler_ctcode.js"
import * as S84_CTCode_Transpiler_LogToConsole_ctcode from "./S84_CTCode_Transpiler_LogToConsole_ctcode.js"
import * as S84_CTCode_Transpiler_NodeJSTranspiler_ctcode from "./S84_CTCode_Transpiler_NodeJSTranspiler_ctcode.js"
import * as S84_CTCode_Transpiler_PHPTranspiler_ctcode from "./S84_CTCode_Transpiler_PHPTranspiler_ctcode.js"
import * as S84_CTCode_Transpiler_Python3Transpiler_ctcode from "./S84_CTCode_Transpiler_Python3Transpiler_ctcode.js"
import * as S84_CTCode_Transpiler_RubyTranspiler_ctcode from "./S84_CTCode_Transpiler_RubyTranspiler_ctcode.js"

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

export class Main {
    constructor() {
    }

    GetCPPTranspiler()
    {
        var specific = new S84_CTCode_Transpiler_CPPTranspiler_ctcode.CPPTranspiler()
        specific.Initialize()
        var structue = new S84_CTCode_Transpiler_StandardStructure_ctcode.StandardStructure()
        structue.SetTargetSpecificFunctions(specific)
        return structue
    }

    GetCSharpTranspiler()
    {
        var specific = new S84_CTCode_Transpiler_CSharpTranspiler_ctcode.CSharpTranspiler()
        specific.Initialize()
        var structue = new S84_CTCode_Transpiler_StandardStructure_ctcode.StandardStructure()
        structue.SetTargetSpecificFunctions(specific)
        return structue
    }

    GetJava11Transpiler()
    {
        var specific = new S84_CTCode_Transpiler_Java11Transpiler_ctcode.Java11Transpiler()
        specific.Initialize()
        var structue = new S84_CTCode_Transpiler_StandardStructure_ctcode.StandardStructure()
        structue.SetTargetSpecificFunctions(specific)
        return structue
    }

    GetLogToConsole()
    {
        var specific = new S84_CTCode_Transpiler_LogToConsole_ctcode.LogToConsole()
        specific.Initialize()
        var structue = new S84_CTCode_Transpiler_StandardStructure_ctcode.StandardStructure()
        structue.SetTargetSpecificFunctions(specific)
        return structue
    }

    GetNodeJSTranspiler()
    {
        var specific = new S84_CTCode_Transpiler_NodeJSTranspiler_ctcode.NodeJSTranspiler()
        specific.Initialize()
        var structue = new S84_CTCode_Transpiler_StandardStructure_ctcode.StandardStructure()
        structue.SetTargetSpecificFunctions(specific)
        return structue
    }

    GetPHPTranspiler()
    {
        var specific = new S84_CTCode_Transpiler_PHPTranspiler_ctcode.PHPTranspiler()
        specific.Initialize()
        var structue = new S84_CTCode_Transpiler_StandardStructure_ctcode.StandardStructure()
        structue.SetTargetSpecificFunctions(specific)
        return structue
    }

    GetPython3Transpiler()
    {
        var specific = new S84_CTCode_Transpiler_Python3Transpiler_ctcode.Python3Transpiler()
        specific.Initialize()
        var structue = new S84_CTCode_Transpiler_StandardStructure_ctcode.StandardStructure()
        structue.SetTargetSpecificFunctions(specific)
        return structue
    }

    GetRubyTranspiler()
    {
        var specific = new S84_CTCode_Transpiler_RubyTranspiler_ctcode.RubyTranspiler()
        specific.Initialize()
        var structue = new S84_CTCode_Transpiler_StandardStructure_ctcode.StandardStructure()
        structue.SetTargetSpecificFunctions(specific)
        return structue
    }

    RunMain(system, ctcode_file_name, transpiler)
    {
        var logger = system.GetLoggerDestination()
        var transpilers = new Map()
        SetKV(transpilers,"CPPTranspiler",this.GetCPPTranspiler())
        SetKV(transpilers,"CSharpTranspiler",this.GetCSharpTranspiler())
        SetKV(transpilers,"Java11Transpiler",this.GetJava11Transpiler())
        SetKV(transpilers,"LogToConsole",this.GetLogToConsole())
        SetKV(transpilers,"NodeJSTranspiler",this.GetNodeJSTranspiler())
        SetKV(transpilers,"PHPTranspiler",this.GetPHPTranspiler())
        SetKV(transpilers,"Python3Transpiler",this.GetPython3Transpiler())
        SetKV(transpilers,"RubyTranspiler",this.GetRubyTranspiler())
        if (ctcode_file_name=="" || ! HasKV(transpilers,transpiler))
        {
            logger.WriteLine("ctcode <CTCodeFile> <Transpiler>")
            logger.WriteLine("Known transpilers:")
            var registered_transpilers = Keys(transpilers)
            var registered_transpilers_index = 0
            while (registered_transpilers_index<Size(registered_transpilers))
            {
                logger.WriteLine(Concat("    ",Element(registered_transpilers,registered_transpilers_index)))
                registered_transpilers_index = registered_transpilers_index+1
            }
            return 1
        }
        var dbnf = system.ReadFileToString(ctcode_file_name)
        if (dbnf=="")
        {
            logger.WriteLine(Concat("The file ",Concat(ctcode_file_name," is empty or does not exist.")))
            return 1
        }
        var dbnf_large_string = new S84_CTCode_dbnf_ctcode.LargeString()
        dbnf_large_string.SetData(dbnf)
        var index = new S84_CTCode_dbnf_ctcode.LengthString()
        index.SetData(dbnf_large_string)
        index.SetStart(0)
        index.SetLength(Length(dbnf))
        var parser_network = new S84_CTCode_dbnf_ctcode.ParserNetwork()
        parser_network.Initialize()
        var ctcode_file_result = new S84_CTCode_dbnf_ctcode.CTCodeFileResult()
        var ctcode_file_parser = parser_network.GetCTCodeFileParser()
        logger.WriteLine("Parsing CTCodeFile...")
        ctcode_file_parser.ParseSingleSave(index,ctcode_file_result)
        if (ctcode_file_result.GetResult() && index.GetLength()==0)
        {
            logger.WriteLine("Done Parsing CTCodeFile!")
            var target_transpiler = GetKV(transpilers,transpiler)
            return target_transpiler.Transpile(system,ctcode_file_result.GetValue(),ctcode_file_name)
        }
        else
        {
            logger.WriteLine(Concat("Failed to parse ",Concat(ctcode_file_name,".")))
            return 1
        }
    }
}

