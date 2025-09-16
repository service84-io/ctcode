#include "S84.CTCode.Main.ctcode.hpp"

namespace s84 {
namespace ctcode {
namespace main {
namespace ctcode {

Main::Main()
{
}

OmniPointer<s84::ctcode::transpiler::ctcode::Transpiler> Main::GetCPPTranspiler()
{
    OmniPointer<s84::ctcode::transpiler::cpptranspiler::ctcode::CPPTranspiler> specific = std::shared_ptr<s84::ctcode::transpiler::cpptranspiler::ctcode::CPPTranspiler>(new s84::ctcode::transpiler::cpptranspiler::ctcode::CPPTranspiler());
    specific->Initialize();
    OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::StandardStructure> structue = std::shared_ptr<s84::ctcode::transpiler::standardstructure::ctcode::StandardStructure>(new s84::ctcode::transpiler::standardstructure::ctcode::StandardStructure());
    structue->SetTargetSpecificFunctions(specific);
    return structue;
}

OmniPointer<s84::ctcode::transpiler::ctcode::Transpiler> Main::GetPython3Transpiler()
{
    OmniPointer<s84::ctcode::transpiler::python3transpiler::ctcode::Python3Transpiler> specific = std::shared_ptr<s84::ctcode::transpiler::python3transpiler::ctcode::Python3Transpiler>(new s84::ctcode::transpiler::python3transpiler::ctcode::Python3Transpiler());
    specific->Initialize();
    OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::StandardStructure> structue = std::shared_ptr<s84::ctcode::transpiler::standardstructure::ctcode::StandardStructure>(new s84::ctcode::transpiler::standardstructure::ctcode::StandardStructure());
    structue->SetTargetSpecificFunctions(specific);
    return structue;
}

OmniPointer<s84::ctcode::transpiler::ctcode::Transpiler> Main::GetNodeJSTranspiler()
{
    OmniPointer<s84::ctcode::transpiler::nodejstranspiler::ctcode::NodeJSTranspiler> specific = std::shared_ptr<s84::ctcode::transpiler::nodejstranspiler::ctcode::NodeJSTranspiler>(new s84::ctcode::transpiler::nodejstranspiler::ctcode::NodeJSTranspiler());
    specific->Initialize();
    OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::StandardStructure> structue = std::shared_ptr<s84::ctcode::transpiler::standardstructure::ctcode::StandardStructure>(new s84::ctcode::transpiler::standardstructure::ctcode::StandardStructure());
    structue->SetTargetSpecificFunctions(specific);
    return structue;
}

OmniPointer<s84::ctcode::transpiler::ctcode::Transpiler> Main::GetJava11Transpiler()
{
    return std::shared_ptr<s84::ctcode::transpiler::java11transpiler::ctcode::Java11Transpiler>(new s84::ctcode::transpiler::java11transpiler::ctcode::Java11Transpiler());
}

OmniPointer<s84::ctcode::transpiler::ctcode::Transpiler> Main::GetLogToConsole()
{
    OmniPointer<s84::ctcode::transpiler::logtoconsole::ctcode::LogToConsole> specific = std::shared_ptr<s84::ctcode::transpiler::logtoconsole::ctcode::LogToConsole>(new s84::ctcode::transpiler::logtoconsole::ctcode::LogToConsole());
    specific->Initialize();
    OmniPointer<s84::ctcode::transpiler::standardstructure::ctcode::StandardStructure> structue = std::shared_ptr<s84::ctcode::transpiler::standardstructure::ctcode::StandardStructure>(new s84::ctcode::transpiler::standardstructure::ctcode::StandardStructure());
    structue->SetTargetSpecificFunctions(specific);
    return structue;
}

int Main::RunMain(OmniPointer<s84::ctcode::system::ctcode::System> system, std::string ctcode_file_name, std::string transpiler)
{
    OmniPointer<s84::ctcode::system::ctcode::OutputStream> logger = system->GetLoggerDestination();
    std::unordered_map<std::string, OmniPointer<s84::ctcode::transpiler::ctcode::Transpiler>> transpilers;
    SetKV(transpilers,std::string("CPPTranspiler"),this->GetCPPTranspiler());
    SetKV(transpilers,std::string("Python3Transpiler"),this->GetPython3Transpiler());
    SetKV(transpilers,std::string("NodeJSTranspiler"),this->GetNodeJSTranspiler());
    SetKV(transpilers,std::string("Java11Transpiler"),this->GetJava11Transpiler());
    SetKV(transpilers,std::string("LogToConsole"),this->GetLogToConsole());
    if (ctcode_file_name==std::string("")||!HasKV(transpilers,transpiler))
    {
        logger->WriteLine(std::string("ctcode <CTCodeFile> <Transpiler>"));
        logger->WriteLine(std::string("Known transpilers:"));
        std::vector<std::string> registered_transpilers = Keys(transpilers);
        int index = 0;
        while (index<Size(registered_transpilers))
        {
            logger->WriteLine(Concat(std::string("    "),Element(registered_transpilers,index)));
            index = index+1;
        }
        return 1;
    }
    std::string dbnf = system->ReadFileToString(ctcode_file_name);
    if (dbnf==std::string(""))
    {
        logger->WriteLine(Concat(std::string("The file "),Concat(ctcode_file_name,std::string(" is empty or does not exist."))));
        return 1;
    }
    OmniPointer<s84::ctcode::dbnf::ctcode::LargeString> dbnf_large_string = std::shared_ptr<s84::ctcode::dbnf::ctcode::LargeString>(new s84::ctcode::dbnf::ctcode::LargeString());
    dbnf_large_string->SetData(dbnf);
    OmniPointer<s84::ctcode::dbnf::ctcode::LengthString> index = std::shared_ptr<s84::ctcode::dbnf::ctcode::LengthString>(new s84::ctcode::dbnf::ctcode::LengthString());
    index->SetData(dbnf_large_string);
    index->SetStart(0);
    index->SetLength(Length(dbnf));
    OmniPointer<s84::ctcode::dbnf::ctcode::ParserNetwork> parser_network = std::shared_ptr<s84::ctcode::dbnf::ctcode::ParserNetwork>(new s84::ctcode::dbnf::ctcode::ParserNetwork());
    parser_network->Initialize();
    OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFileResult> ctcode_file_result = std::shared_ptr<s84::ctcode::dbnf::ctcode::CTCodeFileResult>(new s84::ctcode::dbnf::ctcode::CTCodeFileResult());
    OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFileParser> ctcode_file_parser = parser_network->GetCTCodeFileParser();
    logger->WriteLine(std::string("Parsing CTCodeFile..."));
    ctcode_file_parser->ParseSingleSave(index,ctcode_file_result);
    if (ctcode_file_result->GetResult()&&index->GetLength()==0)
    {
        logger->WriteLine(std::string("Done Parsing CTCodeFile!"));
        OmniPointer<s84::ctcode::transpiler::ctcode::Transpiler> target_transpiler = GetKV(transpilers,transpiler);
        return target_transpiler->Transpile(system,ctcode_file_result->GetValue(),ctcode_file_name);
    }
    else
    {
        logger->WriteLine(Concat(std::string("Failed to parse "),Concat(ctcode_file_name,std::string("."))));
        return 1;
    }
}


};
};
};
};
