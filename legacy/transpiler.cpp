#include "transpiler.hpp"

#include <map>
#include <string>

static std::map<std::string, s84::ctcode::Transpiler*>& GetTranspilerMap()
{
	static std::map<std::string, s84::ctcode::Transpiler*> g_transpiler_map;
	return g_transpiler_map;
}

static std::map<std::string, s84::ctcode::Transpiler*>& g_transpiler_map_initializer = GetTranspilerMap();

namespace s84
{
namespace ctcode
{
Transpiler::Transpiler()
{
}

Transpiler::~Transpiler()
{
}

void Transpiler::AddTranspiler(std::string name, s84::ctcode::Transpiler* transpiler)
{
	std::map<std::string, s84::ctcode::Transpiler*>& transpiler_map = GetTranspilerMap();
	transpiler_map[name] = transpiler;
}

s84::ctcode::Transpiler* Transpiler::GetTranspiler(std::string name)
{
	std::map<std::string, s84::ctcode::Transpiler*>& transpiler_map = GetTranspilerMap();
	std::map<std::string, s84::ctcode::Transpiler*>::iterator index = transpiler_map.find(name);
	
	if (index != transpiler_map.end())
	{
		return index->second;
	}
	
	return NULL;
}

std::list<std::string> Transpiler::GetTranspilerList()
{
	std::list<std::string> transpilers;
	std::map<std::string, s84::ctcode::Transpiler*>& transpiler_map = GetTranspilerMap();
	
	for (std::map<std::string, s84::ctcode::Transpiler*>::iterator index = transpiler_map.begin();index != transpiler_map.end();++index)
	{
		transpilers.push_back(index->first);
	}
	
	return transpilers;
}
};
};
