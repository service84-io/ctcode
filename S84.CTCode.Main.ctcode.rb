require 'S84.CTCode.System.ctcode'
require 'S84.CTCode.Transpiler.ctcode'
require 'S84.CTCode.dbnf.ctcode'
require 'S84.CTCode.Transpiler.StandardStructure.ctcode'
require 'S84.CTCode.Transpiler.CPPTranspiler.ctcode'
require 'S84.CTCode.Transpiler.CSharpTranspiler.ctcode'
require 'S84.CTCode.Transpiler.Java11Transpiler.ctcode'
require 'S84.CTCode.Transpiler.LogToConsole.ctcode'
require 'S84.CTCode.Transpiler.NodeJSTranspiler.ctcode'
require 'S84.CTCode.Transpiler.PHPTranspiler.ctcode'
require 'S84.CTCode.Transpiler.Python3Transpiler.ctcode'
require 'S84.CTCode.Transpiler.RubyTranspiler.ctcode'

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
module MAIN
module CTCODE

class Main
    def initialize()
    end

    def GetCPPTranspiler()
        specific = ::S84::CTCODE::TRANSPILER::CPPTRANSPILER::CTCODE::CPPTranspiler.new()
        specific.Initialize()
        structue = ::S84::CTCODE::TRANSPILER::STANDARDSTRUCTURE::CTCODE::StandardStructure.new()
        structue.SetTargetSpecificFunctions(specific)
        return structue
    end

    def GetCSharpTranspiler()
        specific = ::S84::CTCODE::TRANSPILER::CSHARPTRANSPILER::CTCODE::CSharpTranspiler.new()
        specific.Initialize()
        structue = ::S84::CTCODE::TRANSPILER::STANDARDSTRUCTURE::CTCODE::StandardStructure.new()
        structue.SetTargetSpecificFunctions(specific)
        return structue
    end

    def GetJava11Transpiler()
        specific = ::S84::CTCODE::TRANSPILER::JAVA11TRANSPILER::CTCODE::Java11Transpiler.new()
        specific.Initialize()
        structue = ::S84::CTCODE::TRANSPILER::STANDARDSTRUCTURE::CTCODE::StandardStructure.new()
        structue.SetTargetSpecificFunctions(specific)
        return structue
    end

    def GetLogToConsole()
        specific = ::S84::CTCODE::TRANSPILER::LOGTOCONSOLE::CTCODE::LogToConsole.new()
        specific.Initialize()
        structue = ::S84::CTCODE::TRANSPILER::STANDARDSTRUCTURE::CTCODE::StandardStructure.new()
        structue.SetTargetSpecificFunctions(specific)
        return structue
    end

    def GetNodeJSTranspiler()
        specific = ::S84::CTCODE::TRANSPILER::NODEJSTRANSPILER::CTCODE::NodeJSTranspiler.new()
        specific.Initialize()
        structue = ::S84::CTCODE::TRANSPILER::STANDARDSTRUCTURE::CTCODE::StandardStructure.new()
        structue.SetTargetSpecificFunctions(specific)
        return structue
    end

    def GetPHPTranspiler()
        specific = ::S84::CTCODE::TRANSPILER::PHPTRANSPILER::CTCODE::PHPTranspiler.new()
        specific.Initialize()
        structue = ::S84::CTCODE::TRANSPILER::STANDARDSTRUCTURE::CTCODE::StandardStructure.new()
        structue.SetTargetSpecificFunctions(specific)
        return structue
    end

    def GetPython3Transpiler()
        specific = ::S84::CTCODE::TRANSPILER::PYTHON3TRANSPILER::CTCODE::Python3Transpiler.new()
        specific.Initialize()
        structue = ::S84::CTCODE::TRANSPILER::STANDARDSTRUCTURE::CTCODE::StandardStructure.new()
        structue.SetTargetSpecificFunctions(specific)
        return structue
    end

    def GetRubyTranspiler()
        specific = ::S84::CTCODE::TRANSPILER::RUBYTRANSPILER::CTCODE::RubyTranspiler.new()
        specific.Initialize()
        structue = ::S84::CTCODE::TRANSPILER::STANDARDSTRUCTURE::CTCODE::StandardStructure.new()
        structue.SetTargetSpecificFunctions(specific)
        return structue
    end

    def RunMain(system, ctcode_file_name, transpiler)
        logger = system.GetLoggerDestination()
        transpilers = Hash.new()
        SetKV(transpilers,"CPPTranspiler",self.GetCPPTranspiler())
        SetKV(transpilers,"CSharpTranspiler",self.GetCSharpTranspiler())
        SetKV(transpilers,"Java11Transpiler",self.GetJava11Transpiler())
        SetKV(transpilers,"LogToConsole",self.GetLogToConsole())
        SetKV(transpilers,"NodeJSTranspiler",self.GetNodeJSTranspiler())
        SetKV(transpilers,"PHPTranspiler",self.GetPHPTranspiler())
        SetKV(transpilers,"Python3Transpiler",self.GetPython3Transpiler())
        SetKV(transpilers,"RubyTranspiler",self.GetRubyTranspiler())
        if (ctcode_file_name=="" || ! HasKV(transpilers,transpiler))
            logger.WriteLine("ctcode <CTCodeFile> <Transpiler>")
            logger.WriteLine("Known transpilers:")
            registered_transpilers = Keys(transpilers)
            registered_transpilers_index = 0
            while (registered_transpilers_index<Size(registered_transpilers))
                logger.WriteLine(Concat("    ",Element(registered_transpilers,registered_transpilers_index)))
                registered_transpilers_index = registered_transpilers_index+1
            end
            return 1
        end
        ctcode = system.ReadFileToString(ctcode_file_name)
        if (ctcode=="")
            logger.WriteLine(Concat("The file ",Concat(ctcode_file_name," is empty or does not exist.")))
            return 1
        end
        ctcode_large_string = ::S84::CTCODE::DBNF::CTCODE::LargeString.new()
        ctcode_large_string.SetData(ctcode)
        index = ::S84::CTCODE::DBNF::CTCODE::LengthString.new()
        index.SetData(ctcode_large_string)
        index.SetStart(0)
        index.SetLength(Length(ctcode))
        parser_network = ::S84::CTCODE::DBNF::CTCODE::ParserNetwork.new()
        parser_network.Initialize()
        ctcode_file_result = ::S84::CTCODE::DBNF::CTCODE::CTCodeFileResult.new()
        ctcode_file_parser = parser_network.GetCTCodeFileParser()
        logger.WriteLine("Parsing CTCodeFile...")
        ctcode_file_parser.ParseSingleSave(index,ctcode_file_result)
        if (ctcode_file_result.GetResult() && index.GetLength()==0)
            logger.WriteLine("Done Parsing CTCodeFile!")
            target_transpiler = GetKV(transpilers,transpiler)
            return target_transpiler.Transpile(system,ctcode_file_result.GetValue(),ctcode_file_name)
        else
            logger.WriteLine(Concat("Failed to parse ",Concat(ctcode_file_name,".")))
            return 1
        end
    end
end

end
end
end
end
