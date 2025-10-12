require 'S84.CTCode.System.ctcode'

def ClearList(input); input.clear(); end
def Size(input); return input.length(); end
def Element(input, element); return input[element]; end
def Append(input, element); input.push(element); end
def ClearMap(input); input.clear(); end
def SetKV(input, key, element); input[key] = element; end
def Keys(input); return input.keys(); end
def HasKV(input, key); return input.has_key?(key); end
def GetKV(input, key); return input[key]; end
def Length(input); return input.length(); end
def At(input, index); return input[index]; end
def IntAt(input, index); return input[index].ord(); end
def Concat(left, right); return left + right; end

module S84
module CTCODE
module TRANSPILER
module STRINGHELPER
module CTCODE

class StringHelper
    def initialize()
    end

    def WriteLines(destination, lines)
        lines_index = 0
        while (lines_index<Size(lines))
            line = Element(lines,lines_index)
            destination.WriteLine(line)
            lines_index = lines_index+1
        end
    end

    def Indentation(indent)
        result = ""
        result = ""
        while (indent>0)
            indent = indent-1
            result = Concat(result,"    ")
        end
        return result
    end

    def BeginsWith(prefix, value)
        if (Length(prefix)>Length(value))
            return false
        end
        prefix_index = 0
        while (prefix_index<Length(prefix))
            if (At(prefix,prefix_index)!=At(value,prefix_index))
                return false
            end
            prefix_index = prefix_index+1
        end
        return true
    end

    def DotToSlash(input)
        result = ""
        input_index = 0
        while (input_index<Length(input))
            character = At(input,input_index)
            if (character==".")
                result = Concat(result,"/")
            else
                result = Concat(result,character)
            end
            input_index = input_index+1
        end
        return result
    end

    def DotToFwdSlash(input)
        result = ""
        input_index = 0
        while (input_index<Length(input))
            character = At(input,input_index)
            if (character==".")
                result = Concat(result,"\\")
            else
                result = Concat(result,character)
            end
            input_index = input_index+1
        end
        return result
    end

    def StripDot(input)
        index = 0
        index = 0
        result = ""
        result = ""
        while (index<Length(input))
            character = ""
            character = At(input,index)
            if (character==".")
                result = Concat(result,"_")
            else
                result = Concat(result,character)
            end
            index = index+1
        end
        return result
    end

    def SnakeCaseToCamelCase(snake_case)
        capitalize_this_letter = true
        camel_case = ""
        index = 0
        index = 0
        while (index<Length(snake_case))
            source_character = At(snake_case,index)
            if (source_character=="_")
                capitalize_this_letter = true
            else
                if (capitalize_this_letter==true)
                    upper_character = self.CharacterToUpper(source_character)
                    capitalize_this_letter = false
                    camel_case = Concat(camel_case,upper_character)
                else
                    capitalize_this_letter = false
                    camel_case = Concat(camel_case,source_character)
                end
            end
            index = index+1
        end
        return camel_case
    end

    def CamelCaseToSnakeCase(camel_case)
        delimiter = "_"
        snake_case = ""
        index = 0
        while (index<Length(camel_case))
            source_character = At(camel_case,index)
            lower_character = self.CharacterToLower(source_character)
            if (self.IsUpper(source_character) || self.IsDigit(source_character))
                is_first_character = Length(snake_case)==0
                if (! is_first_character)
                    snake_case = Concat(snake_case,delimiter)
                end
            end
            snake_case = Concat(snake_case,lower_character)
            index = index+1
        end
        return snake_case
    end

    def IsUpper(character)
        result = false
        result = false
        result = result || character=="A"
        result = result || character=="B"
        result = result || character=="C"
        result = result || character=="D"
        result = result || character=="E"
        result = result || character=="F"
        result = result || character=="G"
        result = result || character=="H"
        result = result || character=="I"
        result = result || character=="J"
        result = result || character=="K"
        result = result || character=="L"
        result = result || character=="M"
        result = result || character=="N"
        result = result || character=="O"
        result = result || character=="P"
        result = result || character=="Q"
        result = result || character=="R"
        result = result || character=="S"
        result = result || character=="T"
        result = result || character=="U"
        result = result || character=="V"
        result = result || character=="W"
        result = result || character=="X"
        result = result || character=="Y"
        result = result || character=="Z"
        return result
    end

    def IsDigit(character)
        result = false
        result = false
        result = result || character=="0"
        result = result || character=="1"
        result = result || character=="2"
        result = result || character=="3"
        result = result || character=="4"
        result = result || character=="5"
        result = result || character=="6"
        result = result || character=="7"
        result = result || character=="8"
        result = result || character=="9"
        return result
    end

    def ToLower(input)
        index = 0
        result = ""
        while (index<Length(input))
            character = At(input,index)
            lower_character = self.CharacterToLower(character)
            result = Concat(result,lower_character)
            index = index+1
        end
        return result
    end

    def CharacterToLower(input)
        if (input=="A")
            return "a"
        end
        if (input=="B")
            return "b"
        end
        if (input=="C")
            return "c"
        end
        if (input=="D")
            return "d"
        end
        if (input=="E")
            return "e"
        end
        if (input=="F")
            return "f"
        end
        if (input=="G")
            return "g"
        end
        if (input=="H")
            return "h"
        end
        if (input=="I")
            return "i"
        end
        if (input=="J")
            return "j"
        end
        if (input=="K")
            return "k"
        end
        if (input=="L")
            return "l"
        end
        if (input=="M")
            return "m"
        end
        if (input=="N")
            return "n"
        end
        if (input=="O")
            return "o"
        end
        if (input=="P")
            return "p"
        end
        if (input=="Q")
            return "q"
        end
        if (input=="R")
            return "r"
        end
        if (input=="S")
            return "s"
        end
        if (input=="T")
            return "t"
        end
        if (input=="U")
            return "u"
        end
        if (input=="V")
            return "v"
        end
        if (input=="W")
            return "w"
        end
        if (input=="X")
            return "x"
        end
        if (input=="Y")
            return "y"
        end
        if (input=="Z")
            return "z"
        end
        return input
    end

    def ToUpper(input)
        index = 0
        result = ""
        while (index<Length(input))
            character = At(input,index)
            upper_character = self.CharacterToUpper(character)
            result = Concat(result,upper_character)
            index = index+1
        end
        return result
    end

    def CharacterToUpper(input)
        if (input=="a")
            return "A"
        end
        if (input=="b")
            return "B"
        end
        if (input=="c")
            return "C"
        end
        if (input=="d")
            return "D"
        end
        if (input=="e")
            return "E"
        end
        if (input=="f")
            return "F"
        end
        if (input=="g")
            return "G"
        end
        if (input=="h")
            return "H"
        end
        if (input=="i")
            return "I"
        end
        if (input=="j")
            return "J"
        end
        if (input=="k")
            return "K"
        end
        if (input=="l")
            return "L"
        end
        if (input=="m")
            return "M"
        end
        if (input=="n")
            return "N"
        end
        if (input=="o")
            return "O"
        end
        if (input=="p")
            return "P"
        end
        if (input=="q")
            return "Q"
        end
        if (input=="r")
            return "R"
        end
        if (input=="s")
            return "S"
        end
        if (input=="t")
            return "T"
        end
        if (input=="u")
            return "U"
        end
        if (input=="v")
            return "V"
        end
        if (input=="w")
            return "W"
        end
        if (input=="x")
            return "X"
        end
        if (input=="y")
            return "Y"
        end
        if (input=="z")
            return "Z"
        end
        return input
    end
end

end
end
end
end
end
