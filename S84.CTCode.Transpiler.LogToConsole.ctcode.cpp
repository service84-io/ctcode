#include "S84.CTCode.Transpiler.LogToConsole.ctcode.hpp"

#include "S84.CTCode.System.ctcode.hpp"
#include "S84.CTCode.Transpiler.ctcode.hpp"
#include "S84.CTCode.dbnf.ctcode.hpp"

namespace s84
{
namespace ctcode
{
namespace transpiler
{
namespace logtoconsole
{
namespace ctcode
{
    int LogToConsole::Transpile(OmniPointer<s84::ctcode::system::ctcode::System> system, OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> ct_code_file, std::string base_name)
    {
        OmniPointer<s84::ctcode::system::ctcode::OutputStream> logger = system->GetLoggerDestination();
        logger->WriteLine(ct_code_file->UnParse());
        return 0;
    }

};
};
};
};
};
