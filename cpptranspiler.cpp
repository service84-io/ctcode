#include <algorithm>
#include <fstream>
#include <iostream>
#include <locale>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>

#include "S84.CTCode.dbnf.hpp"
#include "S84.CTCode.CPPTranspiler.ctcode.hpp"
#include "transpiler.hpp"
#include <vector>

namespace s84
{
namespace ctcode
{
class OStreamWriter : public s84::ctcode::cpptranspiler::ctcode::OutputStream {
public:
	OStreamWriter(std::ostream& stream) : destination(stream) {}

    virtual void WriteLine(std::string line) {
		destination << line << std::endl;
	}

private:
	std::ostream& destination;
};
class CPPTranspiler : public s84::ctcode::Transpiler
{
public:
	CPPTranspiler()
	{
	}
	virtual ~CPPTranspiler()
	{
	}

	virtual int Transpile(const char* buffer, std::string base_name)
	{
		const char* index = buffer;
		s84::ctcode::dbnf::CTCodeFile* ctcodeFile = s84::ctcode::dbnf::CTCodeFile::Parse(index);

		if (*index) {
			std::cout << "Failed to parse input" << std::endl;

			for (int count = 0;count < 200;count++) {
				if (index[count]) {
					std::cout << index[count];
				} else {
					break;
				}
			}

			std::cout << std::endl;

			return 1;
		}

		if(ctcodeFile)
		{
			s84::ctcode::cpptranspiler::ctcode::CPPTranspilerCTCodeLogic ctcodeLogic;
			std::ofstream header(base_name + ".hpp", std::ofstream::trunc | std::ofstream::out);
			std::ofstream implementation(base_name + ".cpp", std::ofstream::trunc | std::ofstream::out);
			OStreamWriter header_stream(header);
			OStreamWriter implementation_stream(implementation);
			std::vector<std::string> base_name_tokens = ctcodeLogic.TokenizeBaseName(base_name);
			ctcodeLogic.SetSavedUnmanagedTypes(ctcodeLogic.GetUnmanagedTypes(ctcodeFile->GetUnmanagedTypes()->GetVector()));
			ctcodeLogic.GenerateHeader(ctcodeFile, &header_stream, base_name_tokens);
			ctcodeLogic.GenerateImplementation(ctcodeFile, &implementation_stream, base_name, base_name_tokens);
			return 0;
		}
		else
		{
			return 1;
		}
	}
};
};
};

static int AddCPPTranspiler()
{
	static s84::ctcode::CPPTranspiler g_cpp_transpiler;
	s84::ctcode::Transpiler::AddTranspiler("s84::ctcode::CPPTranspiler", &g_cpp_transpiler);
	return 0;
}

static int initializer = AddCPPTranspiler();
