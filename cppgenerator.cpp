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

		header << "namespace ctcode" << std::endl;
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
		header << std::endl;
		header << "class " << class_name << std::endl;
		header << "{" << std::endl;
		header << "public:" << std::endl;
		header << "    inline " << class_name << "() {};" << std::endl;
		header << "    inline ~" << class_name << "() {};" << std::endl;

		std::list<s84::ctcode::dbnf::ContentDeclaration*> declarations = interfaceDefinition->GetDeclarations()->GetList();

		if(declarations.size() > 0)
		{
			header << std::endl;

			for (std::list<s84::ctcode::dbnf::ContentDeclaration*>::iterator index = declarations.begin(); index != declarations.end();++index)
			{
				header << "    virtual " << GetType((*index)->GetType()) << " " << GenerateCallName((*index)->GetName()) << "(" <<  GenerateParameterList((*index)->GetParameters()) << ") = 0;" << std::endl;
			}
		}

		header << "};" << std::endl;
	}

	void WriteClassDeclaration(s84::ctcode::dbnf::ClassDef* classDefinition, std::ostream& header, std::string full_namespace)
	{
		std::string class_name = GenerateClassName(classDefinition->GetName());
		header << std::endl;
		header << "class " << class_name << std::endl;
		header << "{" << std::endl;
		header << "public:" << std::endl;
		header << "    inline " << class_name << "() {};" << std::endl;
		header << "    inline ~" << class_name << "() {};" << std::endl;

		std::list<s84::ctcode::dbnf::ContentDefinition*> definitions = classDefinition->GetDefinitions()->GetList();
		std::list<s84::ctcode::dbnf::ContentDefinition*> functionDefinitions;
		std::list<s84::ctcode::dbnf::ContentDefinition*> memberDefinitions;

		for (std::list<s84::ctcode::dbnf::ContentDefinition*>::iterator index = definitions.begin(); index != definitions.end();++index)
		{
			if ((*index)->GetFunctionBody() == NULL) {
				memberDefinitions.push_back((*index));
			} else {
				functionDefinitions.push_back((*index));
			}
		}

		if(functionDefinitions.size() > 0)
		{
			header << std::endl;

			for (std::list<s84::ctcode::dbnf::ContentDefinition*>::iterator index = functionDefinitions.begin(); index != functionDefinitions.end();++index)
			{
				if ((*index)->GetFunctionBody() != NULL) {
					header << "    " << GetType((*index)->GetType()) << " " << GenerateCallName((*index)->GetName()) << "(" <<  GenerateParameterList((*index)->GetParameters()) << ");" << std::endl;
				}
			}
		}

		if(memberDefinitions.size() > 0)
		{
			header << std::endl;
			header << "private:" << std::endl;

			for (std::list<s84::ctcode::dbnf::ContentDefinition*>::iterator index = memberDefinitions.begin(); index != memberDefinitions.end();++index)
			{
				if ((*index)->GetFunctionBody() == NULL) {
					header << "    " << GetType((*index)->GetType()) << " " << GenerateVariableName((*index)->GetName()) << ";" << std::endl;
				}
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
		WriteFunctionDefinitions(ctcodeFile, implementation, GenerateFullNamespace(base_name_tokens));

		for(std::list<std::string>::iterator base_name_token = base_name_tokens.begin();base_name_token != base_name_tokens.end();++base_name_token)
		{
			implementation << "};" << std::endl;
		}
		
		implementation << "};" << std::endl;
	}

	void WriteFunctionDefinitions(s84::ctcode::dbnf::CTCodeFile* ctcodeFile, std::ostream& implementation, std::string full_namespace)
	{
		std::list<s84::ctcode::dbnf::Definition*> definitions = ctcodeFile->GetDefinitions()->GetList();
		std::list<s84::ctcode::dbnf::ClassDef*> classDefinitions;

		for (std::list<s84::ctcode::dbnf::Definition*>::iterator definitionIndex = definitions.begin();definitionIndex != definitions.end();definitionIndex++){
			s84::ctcode::dbnf::ClassDef* classDefinition = (*definitionIndex)->GetClassDef();

			if (classDefinition) {
				classDefinitions.push_back(classDefinition);
			}
		}

		for (std::list<s84::ctcode::dbnf::ClassDef*>::iterator definitionIndex = classDefinitions.begin();definitionIndex != classDefinitions.end();definitionIndex++){
			WriteClassDefinition(*definitionIndex, implementation, full_namespace, definitionIndex == classDefinitions.begin());
		}
	}

	void WriteInterfaceDefinition(s84::ctcode::dbnf::InterfaceDef* interfaceDefinition, std::ostream& implementation, std::string full_namespace)
	{
		// There is nothing to write to the devinition file for interfaces
	}

	void WriteClassDefinition(s84::ctcode::dbnf::ClassDef* classDefinition, std::ostream& implementation, std::string full_namespace, bool first_class_definition)
	{
		std::string class_name = GenerateClassName(classDefinition->GetName());

		std::list<s84::ctcode::dbnf::ContentDefinition*> definitions = classDefinition->GetDefinitions()->GetList();
		std::list<s84::ctcode::dbnf::ContentDefinition*> functionDefinitions;

		for (std::list<s84::ctcode::dbnf::ContentDefinition*>::iterator index = definitions.begin(); index != definitions.end();++index)
		{
			if ((*index)->GetFunctionBody() != NULL) {
				functionDefinitions.push_back((*index));
			}
		}

		if(functionDefinitions.size() > 0)
		{
			for (std::list<s84::ctcode::dbnf::ContentDefinition*>::iterator index = functionDefinitions.begin(); index != functionDefinitions.end();++index)
			{
				if ((!first_class_definition) || index != functionDefinitions.begin()) {
					implementation << std::endl;
				}

				if ((*index)->GetFunctionBody() != NULL) {
					implementation << "    " << GetType((*index)->GetType()) << " " << GenerateCallName((*index)->GetName()) << "(" <<  GenerateParameterList((*index)->GetParameters()) << ")" << std::endl;
					implementation << "    {" << std::endl;
					implementation << "    }" << std::endl;
				}
			}
		}
	}

	std::string GetParameterString(s84::ctcode::dbnf::ParameterListDef* parameter) {
		return GetType(parameter->GetType()) + " " + GenerateVariableName(parameter->GetName());
	}

	std::string GenerateParameterListTail(s84::ctcode::dbnf::ParameterListDef* parameters) {
		if (parameters) {
			return ", " + GetParameterString(parameters) + GenerateParameterListTail(parameters->GetParameterTail());
		}

		return "";
	}

	std::string GenerateParameterList(s84::ctcode::dbnf::ParameterListDef* parameters) {
		return GetParameterString(parameters) + GenerateParameterListTail(parameters->GetParameterTail());
	}

	std::string GetType(s84::ctcode::dbnf::ValueType* value_type) {
		return "int";
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

	std::string GenerateVariableName(s84::ctcode::dbnf::Name* name_node)
	{
		if(name_node)
		{
			return CamelCaseToSnakeCase(name_node->UnParse());
		}
		else
		{
			return "";
		}
	}

	std::string GenerateCallName(s84::ctcode::dbnf::Name* name_node)
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

	std::string CamelCaseToSnakeCase(std::string camel_case)
	{
		bool in_abbreviation = true;
		std::string snake_case = "";

		for(std::string::iterator index = camel_case.begin();index != camel_case.end();++index)
		{
			if(isupper(*index))
			{
				if (!in_abbreviation || snake_case.empty()) {
					snake_case += '_';
				}

				snake_case += static_cast<char>(tolower(*index));
				in_abbreviation = true;
			}
			else
			{
				snake_case += *index;
				in_abbreviation = false;
			}
		}

		return snake_case;
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
