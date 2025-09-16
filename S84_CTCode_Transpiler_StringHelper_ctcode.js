import * as S84_CTCode_System_ctcode from "./S84_CTCode_System_ctcode.js"

function ClearList(input) { input.length = 0; }
function Size(input) { return input.length; }
function Element(input, element) { return input[element]; }
function Append(input, element) { input.push(element); }
function ClearMap(input) { input.clear(); }
function SetKV(input, key, element) { input.set(key, element); }
function Keys(input) { return Array.from(input.keys()); }
function HasKV(input, key) { return input.has(key); }
function GetKV(input, key) { return input.get(key); }
function Length(input) { return input.length; }
function At(input, index) { return input[index]; }
function IntAt(input, index) { return input.charCodeAt(index); }
function Concat(left, right) { return left + right; }

export class StringHelper {
    constructor() {
    }

    WriteLines(destination, lines)
    {
        var lines_index = 0
        while (lines_index<Size(lines))
        {
            var line = Element(lines,lines_index)
            destination.WriteLine(line)
            lines_index = lines_index+1
        }
    }

    Indentation(indent)
    {
        var result = ""
        result = ""
        while (indent>0)
        {
            indent = indent-1
            result = Concat(result,"    ")
        }
        return result
    }

    BeginsWith(prefix, value)
    {
        if (Length(prefix)>Length(value))
        {
            return false
        }
        var prefix_index = 0
        while (prefix_index<Length(prefix))
        {
            if (At(prefix,prefix_index)!=At(value,prefix_index))
            {
                return false
            }
            prefix_index = prefix_index+1
        }
        return true
    }

    StripDot(input)
    {
        var index = 0
        index = 0
        var result = ""
        result = ""
        while (index<Length(input))
        {
            var character = ""
            character = At(input,index)
            if (character==".")
            {
                result = Concat(result,"_")
            }
            else
            {
                result = Concat(result,character)
            }
            index = index+1
        }
        return result
    }

    SnakeCaseToCamelCase(snake_case)
    {
        var capitalize_this_letter = true
        var camel_case = ""
        var index = 0
        index = 0
        while (index<Length(snake_case))
        {
            var source_character = At(snake_case,index)
            if (source_character=="_")
            {
                capitalize_this_letter = true
            }
            else
            {
                if (capitalize_this_letter==true)
                {
                    var upper_character = this.CharacterToUpper(source_character)
                    capitalize_this_letter = false
                    camel_case = Concat(camel_case,upper_character)
                }
                else
                {
                    capitalize_this_letter = false
                    camel_case = Concat(camel_case,source_character)
                }
            }
            index = index+1
        }
        return camel_case
    }

    CamelCaseToSnakeCase(camel_case)
    {
        var delimiter = "_"
        var snake_case = ""
        var index = 0
        while (index<Length(camel_case))
        {
            var source_character = At(camel_case,index)
            var lower_character = this.CharacterToLower(source_character)
            if (this.IsUpper(source_character) || this.IsDigit(source_character))
            {
                var is_first_character = Length(snake_case)==0
                if (! is_first_character)
                {
                    snake_case = Concat(snake_case,delimiter)
                }
            }
            snake_case = Concat(snake_case,lower_character)
            index = index+1
        }
        return snake_case
    }

    IsUpper(character)
    {
        var result = false
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
    }

    IsDigit(character)
    {
        var result = false
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
    }

    ToLower(input)
    {
        var index = 0
        var result = ""
        while (index<Length(input))
        {
            var character = At(input,index)
            var lower_character = this.CharacterToLower(character)
            result = Concat(result,lower_character)
            index = index+1
        }
        return result
    }

    CharacterToLower(input)
    {
        if (input=="A")
        {
            return "a"
        }
        if (input=="B")
        {
            return "b"
        }
        if (input=="C")
        {
            return "c"
        }
        if (input=="D")
        {
            return "d"
        }
        if (input=="E")
        {
            return "e"
        }
        if (input=="F")
        {
            return "f"
        }
        if (input=="G")
        {
            return "g"
        }
        if (input=="H")
        {
            return "h"
        }
        if (input=="I")
        {
            return "i"
        }
        if (input=="J")
        {
            return "j"
        }
        if (input=="K")
        {
            return "k"
        }
        if (input=="L")
        {
            return "l"
        }
        if (input=="M")
        {
            return "m"
        }
        if (input=="N")
        {
            return "n"
        }
        if (input=="O")
        {
            return "o"
        }
        if (input=="P")
        {
            return "p"
        }
        if (input=="Q")
        {
            return "q"
        }
        if (input=="R")
        {
            return "r"
        }
        if (input=="S")
        {
            return "s"
        }
        if (input=="T")
        {
            return "t"
        }
        if (input=="U")
        {
            return "u"
        }
        if (input=="V")
        {
            return "v"
        }
        if (input=="W")
        {
            return "w"
        }
        if (input=="X")
        {
            return "x"
        }
        if (input=="Y")
        {
            return "y"
        }
        if (input=="Z")
        {
            return "z"
        }
        return input
    }

    ToUpper(input)
    {
        var index = 0
        var result = ""
        while (index<Length(input))
        {
            var character = At(input,index)
            var upper_character = this.CharacterToUpper(character)
            result = Concat(result,upper_character)
            index = index+1
        }
        return result
    }

    CharacterToUpper(input)
    {
        if (input=="a")
        {
            return "A"
        }
        if (input=="b")
        {
            return "B"
        }
        if (input=="c")
        {
            return "C"
        }
        if (input=="d")
        {
            return "D"
        }
        if (input=="e")
        {
            return "E"
        }
        if (input=="f")
        {
            return "F"
        }
        if (input=="g")
        {
            return "G"
        }
        if (input=="h")
        {
            return "H"
        }
        if (input=="i")
        {
            return "I"
        }
        if (input=="j")
        {
            return "J"
        }
        if (input=="k")
        {
            return "K"
        }
        if (input=="l")
        {
            return "L"
        }
        if (input=="m")
        {
            return "M"
        }
        if (input=="n")
        {
            return "N"
        }
        if (input=="o")
        {
            return "O"
        }
        if (input=="p")
        {
            return "P"
        }
        if (input=="q")
        {
            return "Q"
        }
        if (input=="r")
        {
            return "R"
        }
        if (input=="s")
        {
            return "S"
        }
        if (input=="t")
        {
            return "T"
        }
        if (input=="u")
        {
            return "U"
        }
        if (input=="v")
        {
            return "V"
        }
        if (input=="w")
        {
            return "W"
        }
        if (input=="x")
        {
            return "X"
        }
        if (input=="y")
        {
            return "Y"
        }
        if (input=="z")
        {
            return "Z"
        }
        return input
    }
}

