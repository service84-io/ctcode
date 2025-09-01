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
def At(input: str, index: int) -> str: return input[index]
def IntAt(input: str, index: int) -> int: return ord(input[index])
def Concat(left: str, right: str) -> str: return left + right

class OutputStream:
    def WriteLine(self: 'OutputStream',line: 'str') -> 'None': pass

class System:
    def ReadFileToString(self: 'System',file_name: 'str') -> 'str': pass
    def OpenFileWriter(self: 'System',file_name: 'str') -> 'OutputStream': pass
    def GetLoggerDestination(self: 'System') -> 'OutputStream': pass

