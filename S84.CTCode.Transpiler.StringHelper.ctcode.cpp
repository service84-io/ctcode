#include "S84.CTCode.Transpiler.StringHelper.ctcode.hpp"

namespace s84 {
namespace ctcode {
namespace transpiler {
namespace stringhelper {
namespace ctcode {

StringHelper::StringHelper()
{
}

void StringHelper::WriteLines(OmniPointer<s84::ctcode::system::ctcode::OutputStream> destination, std::vector<std::string> lines)
{
    int lines_index = 0;
    while (lines_index<Size(lines))
    {
        std::string line = Element(lines,lines_index);
        destination->WriteLine(line);
        lines_index = lines_index+1;
    }
}

std::string StringHelper::Indentation(int indent)
{
    std::string result = "";
    result = std::string("");
    while (indent>0)
    {
        indent = indent-1;
        result = Concat(result,std::string("    "));
    }
    return result;
}

bool StringHelper::BeginsWith(std::string prefix, std::string value)
{
    if (Length(prefix)>Length(value))
    {
        return false;
    }
    int prefix_index = 0;
    while (prefix_index<Length(prefix))
    {
        if (At(prefix,prefix_index)!=At(value,prefix_index))
        {
            return false;
        }
        prefix_index = prefix_index+1;
    }
    return true;
}

std::string StringHelper::StripDot(std::string input)
{
    int index = 0;
    index = 0;
    std::string result = "";
    result = std::string("");
    while (index<Length(input))
    {
        std::string character = "";
        character = At(input,index);
        if (character==std::string("."))
        {
            result = Concat(result,std::string("_"));
        }
        else
        {
            result = Concat(result,character);
        }
        index = index+1;
    }
    return result;
}

std::string StringHelper::SnakeCaseToCamelCase(std::string snake_case)
{
    bool capitalize_this_letter = true;
    std::string camel_case = std::string("");
    int index = 0;
    index = 0;
    while (index<Length(snake_case))
    {
        std::string source_character = At(snake_case,index);
        if (source_character==std::string("_"))
        {
            capitalize_this_letter = true;
        }
        else
        {
            if (capitalize_this_letter==true)
            {
                std::string upper_character = this->CharacterToUpper(source_character);
                capitalize_this_letter = false;
                camel_case = Concat(camel_case,upper_character);
            }
            else
            {
                capitalize_this_letter = false;
                camel_case = Concat(camel_case,source_character);
            }
        }
        index = index+1;
    }
    return camel_case;
}

std::string StringHelper::CamelCaseToSnakeCase(std::string camel_case)
{
    std::string delimiter = std::string("_");
    std::string snake_case = std::string("");
    int index = 0;
    while (index<Length(camel_case))
    {
        std::string source_character = At(camel_case,index);
        std::string lower_character = this->CharacterToLower(source_character);
        if (this->IsUpper(source_character)||this->IsDigit(source_character))
        {
            bool is_first_character = Length(snake_case)==0;
            if (!is_first_character)
            {
                snake_case = Concat(snake_case,delimiter);
            }
        }
        snake_case = Concat(snake_case,lower_character);
        index = index+1;
    }
    return snake_case;
}

bool StringHelper::IsUpper(std::string character)
{
    bool result = false;
    result = false;
    result = result||character==std::string("A");
    result = result||character==std::string("B");
    result = result||character==std::string("C");
    result = result||character==std::string("D");
    result = result||character==std::string("E");
    result = result||character==std::string("F");
    result = result||character==std::string("G");
    result = result||character==std::string("H");
    result = result||character==std::string("I");
    result = result||character==std::string("J");
    result = result||character==std::string("K");
    result = result||character==std::string("L");
    result = result||character==std::string("M");
    result = result||character==std::string("N");
    result = result||character==std::string("O");
    result = result||character==std::string("P");
    result = result||character==std::string("Q");
    result = result||character==std::string("R");
    result = result||character==std::string("S");
    result = result||character==std::string("T");
    result = result||character==std::string("U");
    result = result||character==std::string("V");
    result = result||character==std::string("W");
    result = result||character==std::string("X");
    result = result||character==std::string("Y");
    result = result||character==std::string("Z");
    return result;
}

bool StringHelper::IsDigit(std::string character)
{
    bool result = false;
    result = false;
    result = result||character==std::string("0");
    result = result||character==std::string("1");
    result = result||character==std::string("2");
    result = result||character==std::string("3");
    result = result||character==std::string("4");
    result = result||character==std::string("5");
    result = result||character==std::string("6");
    result = result||character==std::string("7");
    result = result||character==std::string("8");
    result = result||character==std::string("9");
    return result;
}

std::string StringHelper::ToLower(std::string input)
{
    int index = 0;
    std::string result = std::string("");
    while (index<Length(input))
    {
        std::string character = At(input,index);
        std::string lower_character = this->CharacterToLower(character);
        result = Concat(result,lower_character);
        index = index+1;
    }
    return result;
}

std::string StringHelper::CharacterToLower(std::string input)
{
    if (input==std::string("A"))
    {
        return std::string("a");
    }
    if (input==std::string("B"))
    {
        return std::string("b");
    }
    if (input==std::string("C"))
    {
        return std::string("c");
    }
    if (input==std::string("D"))
    {
        return std::string("d");
    }
    if (input==std::string("E"))
    {
        return std::string("e");
    }
    if (input==std::string("F"))
    {
        return std::string("f");
    }
    if (input==std::string("G"))
    {
        return std::string("g");
    }
    if (input==std::string("H"))
    {
        return std::string("h");
    }
    if (input==std::string("I"))
    {
        return std::string("i");
    }
    if (input==std::string("J"))
    {
        return std::string("j");
    }
    if (input==std::string("K"))
    {
        return std::string("k");
    }
    if (input==std::string("L"))
    {
        return std::string("l");
    }
    if (input==std::string("M"))
    {
        return std::string("m");
    }
    if (input==std::string("N"))
    {
        return std::string("n");
    }
    if (input==std::string("O"))
    {
        return std::string("o");
    }
    if (input==std::string("P"))
    {
        return std::string("p");
    }
    if (input==std::string("Q"))
    {
        return std::string("q");
    }
    if (input==std::string("R"))
    {
        return std::string("r");
    }
    if (input==std::string("S"))
    {
        return std::string("s");
    }
    if (input==std::string("T"))
    {
        return std::string("t");
    }
    if (input==std::string("U"))
    {
        return std::string("u");
    }
    if (input==std::string("V"))
    {
        return std::string("v");
    }
    if (input==std::string("W"))
    {
        return std::string("w");
    }
    if (input==std::string("X"))
    {
        return std::string("x");
    }
    if (input==std::string("Y"))
    {
        return std::string("y");
    }
    if (input==std::string("Z"))
    {
        return std::string("z");
    }
    return input;
}

std::string StringHelper::ToUpper(std::string input)
{
    int index = 0;
    std::string result = std::string("");
    while (index<Length(input))
    {
        std::string character = At(input,index);
        std::string upper_character = this->CharacterToUpper(character);
        result = Concat(result,upper_character);
        index = index+1;
    }
    return result;
}

std::string StringHelper::CharacterToUpper(std::string input)
{
    if (input==std::string("a"))
    {
        return std::string("A");
    }
    if (input==std::string("b"))
    {
        return std::string("B");
    }
    if (input==std::string("c"))
    {
        return std::string("C");
    }
    if (input==std::string("d"))
    {
        return std::string("D");
    }
    if (input==std::string("e"))
    {
        return std::string("E");
    }
    if (input==std::string("f"))
    {
        return std::string("F");
    }
    if (input==std::string("g"))
    {
        return std::string("G");
    }
    if (input==std::string("h"))
    {
        return std::string("H");
    }
    if (input==std::string("i"))
    {
        return std::string("I");
    }
    if (input==std::string("j"))
    {
        return std::string("J");
    }
    if (input==std::string("k"))
    {
        return std::string("K");
    }
    if (input==std::string("l"))
    {
        return std::string("L");
    }
    if (input==std::string("m"))
    {
        return std::string("M");
    }
    if (input==std::string("n"))
    {
        return std::string("N");
    }
    if (input==std::string("o"))
    {
        return std::string("O");
    }
    if (input==std::string("p"))
    {
        return std::string("P");
    }
    if (input==std::string("q"))
    {
        return std::string("Q");
    }
    if (input==std::string("r"))
    {
        return std::string("R");
    }
    if (input==std::string("s"))
    {
        return std::string("S");
    }
    if (input==std::string("t"))
    {
        return std::string("T");
    }
    if (input==std::string("u"))
    {
        return std::string("U");
    }
    if (input==std::string("v"))
    {
        return std::string("V");
    }
    if (input==std::string("w"))
    {
        return std::string("W");
    }
    if (input==std::string("x"))
    {
        return std::string("X");
    }
    if (input==std::string("y"))
    {
        return std::string("Y");
    }
    if (input==std::string("z"))
    {
        return std::string("Z");
    }
    return input;
}


};
};
};
};
};
