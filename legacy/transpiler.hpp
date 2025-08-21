#ifndef DSA_VENT_TOWER_GENERATOR_H
#define DSA_VENT_TOWER_GENERATOR_H

#include <list>
#include <string>

namespace s84
{
namespace ctcode
{
class Transpiler
{
public:
	Transpiler();
	virtual ~Transpiler();

	static void AddTranspiler(std::string name, s84::ctcode::Transpiler* transpiler);
	static s84::ctcode::Transpiler* GetTranspiler(std::string name);
	static std::list<std::string> GetTranspilerList();

	virtual int Transpile(const char* buffer, std::string base_name) = 0;
};
};
};

#endif

