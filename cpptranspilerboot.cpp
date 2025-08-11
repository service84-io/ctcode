#include <algorithm>
#include <fstream>
#include <iostream>
#include <locale>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>

#include "S84.CTCode.dbnf.ctcode.hpp"
#include "S84.CTCode.CPPTranspilerBoot.ctcode.hpp"
#include "transpiler.hpp"
#include <vector>

namespace s84
{
namespace ctcode
{
class OStreamWriterBoot : public s84::ctcode::cpptranspilerboot::ctcode::OutputStream {
public:
	OStreamWriterBoot(std::ostream& stream) : destination(stream) {}

    virtual void WriteLine(std::string line) {
		destination << line << std::endl;
	}

private:
	std::ostream& destination;
};
class CPPTranspilerBoot : public s84::ctcode::Transpiler
{
public:
	CPPTranspilerBoot()
	{
	}
	virtual ~CPPTranspilerBoot()
	{
	}

	virtual int Transpile(const char* buffer, std::string base_name)
	{
		s84::ctcode::dbnf::ctcode::LengthString index;
		std::string data(buffer);
		index.SetData(data);
		index.SetStart(0);
		index.SetLength(data.length());
		s84::ctcode::dbnf::ctcode::ParserNetwork parser_network;
		parser_network.Initialize();
		s84::ctcode::dbnf::ctcode::CTCodeFileResult ctcodeFile_result;
		std::cout << "Parsing CTCode File..." << std::endl;
		parser_network.GetCTCodeFileParser()->ParseSingleSave(&index, &ctcodeFile_result);
		s84::ctcode::dbnf::ctcode::CTCodeFile* ctcodeFile = ctcodeFile_result.GetValue().raw();

		if (index.GetLength() > 0) {
			std::cout << "Failed to parse input" << std::endl;
			std::cout << index.GetString().substr(0,200) << std::endl;

			return 1;
		}

		if(ctcodeFile)
		{
			std::cout << "CTCode File Parsed!" << std::endl;
			s84::ctcode::cpptranspilerboot::ctcode::CPPTranspilerCTCodeLogic ctcodeLogic;
			std::ofstream header(base_name + ".hpp", std::ofstream::trunc | std::ofstream::out);
			std::ofstream implementation(base_name + ".cpp", std::ofstream::trunc | std::ofstream::out);
			OStreamWriterBoot header_stream(header);
			OStreamWriterBoot implementation_stream(implementation);
			std::vector<std::string> base_name_tokens = ctcodeLogic.TokenizeBaseName(base_name);
			ctcodeLogic.SetSavedUnmanagedTypes(ctcodeLogic.GetUnmanagedTypes(ctcodeFile->GetUnmanagedTypes()));
			ctcodeLogic.GenerateHeader(ctcodeFile, &header_stream, base_name_tokens);
			ctcodeLogic.GenerateImplementation(ctcodeFile, &implementation_stream, base_name, base_name_tokens);
			return 0;
		}
		else
		{
			std::cout << "Failed to parse CTCode file." << std::endl;
			return 1;
		}
	}
};
};
};

static int AddCPPTranspiler()
{
	static s84::ctcode::CPPTranspilerBoot g_cpp_transpiler_boot;
	s84::ctcode::Transpiler::AddTranspiler("s84::ctcode::CPPTranspilerBoot", &g_cpp_transpiler_boot);
	return 0;
}

static int initializer = AddCPPTranspiler();
