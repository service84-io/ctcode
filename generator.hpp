#ifndef DSA_VENT_TOWER_GENERATOR_H
#define DSA_VENT_TOWER_GENERATOR_H

#include <list>
#include <string>

#include "S84.CTCode.dbnf.hpp"

namespace s84
{
namespace ctcode
{
class Generator
{
public:
	Generator();
	virtual ~Generator();

	static void AddGenerator(std::string name, s84::ctcode::Generator* generator);
	static s84::ctcode::Generator* GetGenerator(std::string name);
	static std::list<std::string> GetGeneratorList();

	virtual int GenerateParser(const char* buffer, std::string base_name) = 0;
};
};
};

#endif

