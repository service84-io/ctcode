import S84_CTCode_System_ctcode

def ClearList(input: list) -> None: input.clear()
def Size(input: list) -> int: return len(input)
def Element(input: list, element: int ) -> any: return input[element]
def Append(input: list, element: any) -> None: input.append(element)
def ClearMap(input: dict) -> None: input.clear()
def SetKV(input: dict, key: str, element: any) -> None: input[key] = element
def Keys(input: dict) -> list[str]:
    result: list[str] = []
    for key in input.keys():
        result.append(key)
    return result
def HasKV(input: dict, key: str) -> bool: return key in input
def GetKV(input: dict, key: str) -> any: return input[key]
def Length(input: str) -> int: return len(input)
def At(input: str, index: int) -> str: return input[index:index+1]
def IntAt(input: str, index: int) -> int: return ord(input[index:index+1])
def Concat(left: str, right: str) -> str: return left + right

class StringHelper:
    def __init__(self: 'StringHelper'):
        pass

    def WriteLines(self: 'StringHelper',destination: 'S84_CTCode_System_ctcode.OutputStream',lines: 'list[str]') -> 'None':
        lines_index: 'int' = 0
        while lines_index<Size(lines):
            line: 'str' = Element(lines,lines_index)
            destination.WriteLine(line)
            lines_index = lines_index+1

    def Indentation(self: 'StringHelper',indent: 'int') -> 'str':
        result: 'str' = ""
        result = ""
        while indent>0:
            indent = indent-1
            result = Concat(result,"    ")
        return result

    def BeginsWith(self: 'StringHelper',prefix: 'str',value: 'str') -> 'bool':
        if Length(prefix)>Length(value):
            return False
        prefix_index: 'int' = 0
        while prefix_index<Length(prefix):
            if At(prefix,prefix_index)!=At(value,prefix_index):
                return False
            prefix_index = prefix_index+1
        return True

    def DotToSlash(self: 'StringHelper',input: 'str') -> 'str':
        result: 'str' = ""
        input_index: 'int' = 0
        while input_index<Length(input):
            character: 'str' = At(input,input_index)
            if character==".":
                result = Concat(result,"/")
            else:
                result = Concat(result,character)
            input_index = input_index+1
        return result

    def StripDot(self: 'StringHelper',input: 'str') -> 'str':
        index: 'int' = 0
        index = 0
        result: 'str' = ""
        result = ""
        while index<Length(input):
            character: 'str' = ""
            character = At(input,index)
            if character==".":
                result = Concat(result,"_")
            else:
                result = Concat(result,character)
            index = index+1
        return result

    def SnakeCaseToCamelCase(self: 'StringHelper',snake_case: 'str') -> 'str':
        capitalize_this_letter: 'bool' = True
        camel_case: 'str' = ""
        index: 'int' = 0
        index = 0
        while index<Length(snake_case):
            source_character: 'str' = At(snake_case,index)
            if source_character=="_":
                capitalize_this_letter = True
            else:
                if capitalize_this_letter==True:
                    upper_character: 'str' = self.CharacterToUpper(source_character)
                    capitalize_this_letter = False
                    camel_case = Concat(camel_case,upper_character)
                else:
                    capitalize_this_letter = False
                    camel_case = Concat(camel_case,source_character)
            index = index+1
        return camel_case

    def CamelCaseToSnakeCase(self: 'StringHelper',camel_case: 'str') -> 'str':
        delimiter: 'str' = "_"
        snake_case: 'str' = ""
        index: 'int' = 0
        while index<Length(camel_case):
            source_character: 'str' = At(camel_case,index)
            lower_character: 'str' = self.CharacterToLower(source_character)
            if self.IsUpper(source_character) or self.IsDigit(source_character):
                is_first_character: 'bool' = Length(snake_case)==0
                if not is_first_character:
                    snake_case = Concat(snake_case,delimiter)
            snake_case = Concat(snake_case,lower_character)
            index = index+1
        return snake_case

    def IsUpper(self: 'StringHelper',character: 'str') -> 'bool':
        result: 'bool' = False
        result = False
        result = result or character=="A"
        result = result or character=="B"
        result = result or character=="C"
        result = result or character=="D"
        result = result or character=="E"
        result = result or character=="F"
        result = result or character=="G"
        result = result or character=="H"
        result = result or character=="I"
        result = result or character=="J"
        result = result or character=="K"
        result = result or character=="L"
        result = result or character=="M"
        result = result or character=="N"
        result = result or character=="O"
        result = result or character=="P"
        result = result or character=="Q"
        result = result or character=="R"
        result = result or character=="S"
        result = result or character=="T"
        result = result or character=="U"
        result = result or character=="V"
        result = result or character=="W"
        result = result or character=="X"
        result = result or character=="Y"
        result = result or character=="Z"
        return result

    def IsDigit(self: 'StringHelper',character: 'str') -> 'bool':
        result: 'bool' = False
        result = False
        result = result or character=="0"
        result = result or character=="1"
        result = result or character=="2"
        result = result or character=="3"
        result = result or character=="4"
        result = result or character=="5"
        result = result or character=="6"
        result = result or character=="7"
        result = result or character=="8"
        result = result or character=="9"
        return result

    def ToLower(self: 'StringHelper',input: 'str') -> 'str':
        index: 'int' = 0
        result: 'str' = ""
        while index<Length(input):
            character: 'str' = At(input,index)
            lower_character: 'str' = self.CharacterToLower(character)
            result = Concat(result,lower_character)
            index = index+1
        return result

    def CharacterToLower(self: 'StringHelper',input: 'str') -> 'str':
        if input=="A":
            return "a"
        if input=="B":
            return "b"
        if input=="C":
            return "c"
        if input=="D":
            return "d"
        if input=="E":
            return "e"
        if input=="F":
            return "f"
        if input=="G":
            return "g"
        if input=="H":
            return "h"
        if input=="I":
            return "i"
        if input=="J":
            return "j"
        if input=="K":
            return "k"
        if input=="L":
            return "l"
        if input=="M":
            return "m"
        if input=="N":
            return "n"
        if input=="O":
            return "o"
        if input=="P":
            return "p"
        if input=="Q":
            return "q"
        if input=="R":
            return "r"
        if input=="S":
            return "s"
        if input=="T":
            return "t"
        if input=="U":
            return "u"
        if input=="V":
            return "v"
        if input=="W":
            return "w"
        if input=="X":
            return "x"
        if input=="Y":
            return "y"
        if input=="Z":
            return "z"
        return input

    def ToUpper(self: 'StringHelper',input: 'str') -> 'str':
        index: 'int' = 0
        result: 'str' = ""
        while index<Length(input):
            character: 'str' = At(input,index)
            upper_character: 'str' = self.CharacterToUpper(character)
            result = Concat(result,upper_character)
            index = index+1
        return result

    def CharacterToUpper(self: 'StringHelper',input: 'str') -> 'str':
        if input=="a":
            return "A"
        if input=="b":
            return "B"
        if input=="c":
            return "C"
        if input=="d":
            return "D"
        if input=="e":
            return "E"
        if input=="f":
            return "F"
        if input=="g":
            return "G"
        if input=="h":
            return "H"
        if input=="i":
            return "I"
        if input=="j":
            return "J"
        if input=="k":
            return "K"
        if input=="l":
            return "L"
        if input=="m":
            return "M"
        if input=="n":
            return "N"
        if input=="o":
            return "O"
        if input=="p":
            return "P"
        if input=="q":
            return "Q"
        if input=="r":
            return "R"
        if input=="s":
            return "S"
        if input=="t":
            return "T"
        if input=="u":
            return "U"
        if input=="v":
            return "V"
        if input=="w":
            return "W"
        if input=="x":
            return "X"
        if input=="y":
            return "Y"
        if input=="z":
            return "Z"
        return input

