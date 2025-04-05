#include <algorithm>
#include <fstream>
#include <iostream>
#include <locale>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>

#include "dbnf.hpp"
#include "generator.hpp"

namespace s84
{
namespace ctcode
{
class CPPGenerator : public s84::ctcode::Generator
{
public:
	CPPGenerator()
	{
	}
	virtual ~CPPGenerator()
	{
	}

	virtual int GenerateParser(const char* buffer, std::string base_name)
	{
		const char* index = buffer;
		s84::ctcode::dbnf::CTCodeFile* ctcodeFile = s84::ctcode::dbnf::CTCodeFile::Parse(index);

		if(ctcodeFile)
		{
			std::list<s84::ctcode::dbnf::Definition*> definitions = ctcodeFile->GetDefinitions()->GetList();
	
			for (std::list<s84::ctcode::dbnf::Definition*>::iterator definitionIndex = definitions.begin();definitionIndex != definitions.end();definitionIndex++){
				std::cout << "Checking definition " << (*definitionIndex) << std:: endl;
				s84::ctcode::dbnf::InterfaceDef* interfaceDefinition = (*definitionIndex)->GetInterfaceDef();
				s84::ctcode::dbnf::ClassDef* classDefinition = (*definitionIndex)->GetClassDef();
	
				if (interfaceDefinition) {
					std::cout << "interface: " << interfaceDefinition->GetName()->UnParse() << std::endl;
				}
	
				if (classDefinition) {
					std::cout << "class: " << classDefinition->GetName()->UnParse() << std::endl;
				}
			}

			std::ofstream header(base_name + ".hpp", std::ofstream::trunc | std::ofstream::out);
			std::ofstream implementation(base_name + ".cpp", std::ofstream::trunc | std::ofstream::out);
			std::list<std::string> base_name_tokens = TokenizeBaseName(base_name);
			GenerateHeader(ctcodeFile, header, base_name_tokens);
			GenerateImplementation(ctcodeFile, implementation, base_name, base_name_tokens);
			return 0;
		}
		else
		{
			return 1;
		}
	}

	void GenerateHeader(s84::ctcode::dbnf::CTCodeFile* ctcodeFile, std::ostream& header, std::list<std::string> base_name_tokens)
	{
		std::string guard_name = GenerateGuardName(base_name_tokens);
		header << "#ifndef " << guard_name << std::endl;
		header << "#define " << guard_name << std::endl;
		header << std::endl;
		header << "#include <list>" << std::endl;
		header << "#include <string>" << std::endl;
		header << "#include <cstring>" << std::endl;
		header << std::endl;

		for(std::list<std::string>::iterator base_name_token = base_name_tokens.begin();base_name_token != base_name_tokens.end();++base_name_token)
		{
			header << "namespace " << ToLower(*base_name_token) << std::endl;
			header << "{" << std::endl;
		}

		header << "namespace dbnf" << std::endl;
		header << "{" << std::endl;
		WriteForwardDeclaration(ctcodeFile, header);
		WriteClassDeclarations(ctcodeFile, header, GenerateFullNamespace(base_name_tokens));

		for(std::list<std::string>::iterator base_name_token = base_name_tokens.begin();base_name_token != base_name_tokens.end();++base_name_token)
		{
			header << "};" << std::endl;
		}
		
		header << "};" << std::endl;
		header << std::endl;
		header << "#endif" << std::endl;
	}

	void WriteForwardDeclaration(s84::ctcode::dbnf::CTCodeFile* ctcodeFile, std::ostream& header)
	{
		std::list<s84::ctcode::dbnf::Definition*> definitions = ctcodeFile->GetDefinitions()->GetList();

		for (std::list<s84::ctcode::dbnf::Definition*>::iterator definitionIndex = definitions.begin();definitionIndex != definitions.end();definitionIndex++){
			s84::ctcode::dbnf::InterfaceDef* interfaceDefinition = (*definitionIndex)->GetInterfaceDef();
			s84::ctcode::dbnf::ClassDef* classDefinition = (*definitionIndex)->GetClassDef();

			if (interfaceDefinition) {
				header << "class " << GenerateClassName(interfaceDefinition->GetName()) << ";" << std::endl;
			}

			if (classDefinition) {
				header << "class " << GenerateClassName(classDefinition->GetName()) << ";" << std::endl;
			}
		}
	}

	void WriteClassDeclarations(s84::ctcode::dbnf::CTCodeFile* ctcodeFile, std::ostream& header, std::string full_namespace)
	{
		std::list<s84::ctcode::dbnf::Definition*> definitions = ctcodeFile->GetDefinitions()->GetList();

		for (std::list<s84::ctcode::dbnf::Definition*>::iterator definitionIndex = definitions.begin();definitionIndex != definitions.end();definitionIndex++){
			s84::ctcode::dbnf::InterfaceDef* interfaceDefinition = (*definitionIndex)->GetInterfaceDef();
			s84::ctcode::dbnf::ClassDef* classDefinition = (*definitionIndex)->GetClassDef();

			if (interfaceDefinition) {
				WriteInterfaceDeclaration(interfaceDefinition, header, full_namespace);
			}

			if (classDefinition) {
				WriteClassDeclaration(classDefinition, header, full_namespace);
			}
		}
	}

	void WriteInterfaceDeclaration(s84::ctcode::dbnf::InterfaceDef* interfaceDefinition, std::ostream& header, std::string full_namespace)
	{
		std::string class_name = GenerateClassName(interfaceDefinition->GetName());
		std::map<std::string, std::string> members;
		header << std::endl;
		header << "class " << class_name << std::endl;
		header << "{" << std::endl;
		header << "public:" << std::endl;
		header << "    " << class_name << "();" << std::endl;
		header << "    ~" << class_name << "();" << std::endl;
		header << std::endl;

		if(members.size() > 0)
		{
			header << std::endl;

			for (std::map<std::string, std::string>::iterator index = members.begin(); index != members.end();++index)
			{
				header << "    " << index->second << " " << GenerateAccessorName(index->first) << "();" << std::endl;
			}

			header << std::endl;
			header << "private:" << std::endl;

			for (std::map<std::string, std::string>::iterator index = members.begin(); index != members.end();++index)
			{
				header << "    " << index->second << " " << index->first << ";" << std::endl;
			}
		}

		header << "};" << std::endl;
	}

	void WriteClassDeclaration(s84::ctcode::dbnf::ClassDef* classDefinition, std::ostream& header, std::string full_namespace)
	{
		std::string class_name = GenerateClassName(classDefinition->GetName());
		std::map<std::string, std::string> members;
		header << std::endl;
		header << "class " << class_name << std::endl;
		header << "{" << std::endl;
		header << "public:" << std::endl;
		header << "    " << class_name << "();" << std::endl;
		header << "    ~" << class_name << "();" << std::endl;
		header << std::endl;

		if(members.size() > 0)
		{
			header << std::endl;

			for (std::map<std::string, std::string>::iterator index = members.begin(); index != members.end();++index)
			{
				header << "    " << index->second << " " << GenerateAccessorName(index->first) << "();" << std::endl;
			}

			header << std::endl;
			header << "private:" << std::endl;

			for (std::map<std::string, std::string>::iterator index = members.begin(); index != members.end();++index)
			{
				header << "    " << index->second << " " << index->first << ";" << std::endl;
			}
		}

		header << "};" << std::endl;
	}

	void GenerateImplementation(s84::ctcode::dbnf::CTCodeFile* ctcodeFile, std::ostream& implementation, std::string base_name, std::list<std::string> base_name_tokens)
	{
		implementation << "#include \"" + base_name +".hpp\"" << std::endl;
		implementation << std::endl;

		for(std::list<std::string>::iterator base_name_token = base_name_tokens.begin();base_name_token != base_name_tokens.end();++base_name_token)
		{
			implementation << "namespace " << ToLower(*base_name_token) << std::endl;
			implementation << "{" << std::endl;
		}

		implementation << "namespace ctcode" << std::endl;
		implementation << "{" << std::endl;
		//WriteFunctionDefinitions(grammar, implementation, GenerateFullNamespace(base_name_tokens));
		implementation << std::endl;

		for(std::list<std::string>::iterator base_name_token = base_name_tokens.begin();base_name_token != base_name_tokens.end();++base_name_token)
		{
			implementation << "};" << std::endl;
		}
		
		implementation << "};" << std::endl;
	}

	std::string GenerateClassName(s84::ctcode::dbnf::Name* name_node)
	{
		if (name_node)
		{
			return SnakeCaseToCamelCase(name_node->UnParse());
		}
		else
		{
			return "";
		}
	}

	std::list<std::string> TokenizeBaseName(std::string name)
	{
		std::list<std::string> base_name_tokens;
		std::stringstream splitter(name);
		std::string item;
		
		while(std::getline(splitter, item, '.'))
		{
			base_name_tokens.push_back(item);
		}

		base_name_tokens.pop_back();
		return base_name_tokens;
	}

	std::string GenerateGuardName(std::list<std::string> base_name_tokens)
	{
		std::string guard_name;
		std::locale locale;

		for(std::list<std::string>::iterator base_name_token = base_name_tokens.begin();base_name_token != base_name_tokens.end();++base_name_token)
		{
			guard_name += ToUpper(*base_name_token) + "_";
		}

		guard_name += "CTCODE_H";
		return guard_name;
	}

	std::string GenerateAccessorName(std::string member)
	{
		return "Get" + SnakeCaseToCamelCase(member);
	}

	std::string GenerateFullNamespace(std::list<std::string> base_name_tokens)
	{
		std::string full_namespace;

		for(std::list<std::string>::iterator base_name_token = base_name_tokens.begin();base_name_token != base_name_tokens.end();++base_name_token)
		{
			full_namespace += ToLower(*base_name_token) + "::";
		}

		full_namespace += "dbnf::";
		return full_namespace;
	}

	std::string SnakeCaseToCamelCase(std::string snake_case)
	{
		bool capitalize_this_letter = true;
		std::string camel_case = "";

		for(std::string::iterator index = snake_case.begin();index != snake_case.end();++index)
		{
			if(*index == '_')
			{
				capitalize_this_letter = true;
			}
			else if(capitalize_this_letter)
			{
				capitalize_this_letter = false;
				camel_case += static_cast<char>(toupper(*index));
			}
			else
			{
				capitalize_this_letter = false;
				camel_case += *index;
			}
		}

		return camel_case;
	}

	std::string ToLower(std::string string)
	{
		std::transform(string.begin(), string.end(), string.begin(), tolower);
		return string;
	}

	std::string ToUpper(std::string string)
	{
		std::transform(string.begin(), string.end(), string.begin(), toupper);
		return string;
	}
};
};
};

static int AddCPPGenerator()
{
	static s84::ctcode::CPPGenerator g_cpp_generator;
	s84::ctcode::Generator::AddGenerator("s84::ctcode::CPPGenerator", &g_cpp_generator);
	return 0;
}

static int initializer = AddCPPGenerator();
