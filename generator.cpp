#include "generator.hpp"

#include <map>
#include <string>

static std::map<std::string, s84::ctcode::Generator*>& GetGeneratorMap()
{
	static std::map<std::string, s84::ctcode::Generator*> g_generator_map;
	return g_generator_map;
}

static std::map<std::string, s84::ctcode::Generator*>& g_generator_map_initializer = GetGeneratorMap();

namespace s84
{
namespace ctcode
{
Generator::Generator()
{
}

Generator::~Generator()
{
}

void Generator::AddGenerator(std::string name, s84::ctcode::Generator* generator)
{
	std::map<std::string, s84::ctcode::Generator*>& generator_map = GetGeneratorMap();
	generator_map[name] = generator;
}

s84::ctcode::Generator* Generator::GetGenerator(std::string name)
{
	std::map<std::string, s84::ctcode::Generator*>& generator_map = GetGeneratorMap();
	std::map<std::string, s84::ctcode::Generator*>::iterator index = generator_map.find(name);
	
	if (index != generator_map.end())
	{
		return index->second;
	}
	
	return NULL;
}

std::list<std::string> Generator::GetGeneratorList()
{
	std::list<std::string> generators;
	std::map<std::string, s84::ctcode::Generator*>& generator_map = GetGeneratorMap();
	
	for (std::map<std::string, s84::ctcode::Generator*>::iterator index = generator_map.begin();index != generator_map.end();++index)
	{
		generators.push_back(index->first);
	}
	
	return generators;
}
};
};
