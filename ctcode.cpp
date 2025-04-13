#include <fstream>
#include <iostream>
#include <string>

#include "S84.CTCode.dbnf.hpp"
#include "generator.hpp"

char* ReadFileIntoBuffer(std::string file)
{
	std::ifstream file_stream(file.c_str(), std::ifstream::in | std::ifstream::binary);

	if (file_stream.bad())
	{
		return NULL;
	}

	file_stream.seekg(0, file_stream.end);
	int length = file_stream.tellg();

	if(length <= 0)
	{
		return NULL;
	}

	file_stream.seekg(0, file_stream.beg);
    char* buffer = new char[length + 1];
	const char* index = buffer;
    file_stream.read(buffer, length);
	buffer[length] = 0;
	return buffer;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << argv[0] << " <CTCodeFile> <Generator>" << std::endl;
		std::cout << "Known generators:" << std::endl;
		std::list<std::string> generators = s84::ctcode::Generator::GetGeneratorList();
		
		for(std::list<std::string>::iterator index = generators.begin();index != generators.end();++index)
		{
			std::cout<< "    " << (*index) << std::endl;
		}
		
		return 1;
	}
	
	std::string ctcode_file_name = argv[1];
	std::string generator_name = argv[2];
	s84::ctcode::Generator* generator = s84::ctcode::Generator::GetGenerator(generator_name);
    char* buffer = ReadFileIntoBuffer(ctcode_file_name);

	if(buffer)
	{
		if(generator)
		{
			int value = generator->GenerateParser(buffer, ctcode_file_name);
			delete[] buffer;
			return value;
		}
		else
		{
			std::cout << "The generator " << generator_name << " is unknown." << std::endl;
			std::cout << "Known generators:" << std::endl;
			std::list<std::string> generators = s84::ctcode::Generator::GetGeneratorList();
			
			for(std::list<std::string>::iterator index = generators.begin();index != generators.end();++index)
			{
				std::cout<< "    " << (*index) << std::endl;
			}
			
			return 1;
		}
	}
	else
	{
		std::cout << "The file " << ctcode_file_name << " is empty or does not exist." << std::endl;
		return 1;
	}
}

