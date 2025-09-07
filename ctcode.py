import sys

import S84_CTCode_System_ctcode
import S84_CTCode_Main_ctcode

class FileWriter(S84_CTCode_System_ctcode.OutputStream):
    def __init__(self: 'FileWriter', file_name: str):
        self.target = open(file_name, 'w')

    def WriteLine(self: 'LoggerClass', line:  'str') -> None:
        self.target.write(line)
        self.target.write("\n")

class LoggerClass(S84_CTCode_System_ctcode.OutputStream):
    def WriteLine(self: 'LoggerClass', line:  'str') -> None:
        print(line)

class System(S84_CTCode_System_ctcode.System):
    def ReadFileToString(self: 'System', file_name: 'str') -> 'str':
        result:str = ""
        file = open(file_name)

        for line in file:
            result = result + line

        return result
    
    def OpenFileWriter(self: 'System', file_name: 'str') -> 'S84_CTCode_System_ctcode.OutputStream':
        return FileWriter(file_name)
    
    def GetLoggerDestination(self: 'System') -> 'S84_CTCode_System_ctcode.OutputStream':
        return LoggerClass()

if __name__ == "__main__":
    system: System = System()
    main: S84_CTCode_Main_ctcode.Main = S84_CTCode_Main_ctcode.Main()
    c_t_code_file_name: str = ""
    transpiler_name: str = ""

    if len(sys.argv) == 3:
        c_t_code_file_name = sys.argv[1]
        transpiler_name = sys.argv[2]
        
    sys.exit(main.RunMain(system, c_t_code_file_name, transpiler_name))
