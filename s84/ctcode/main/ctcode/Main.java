package s84.ctcode.main.ctcode;

import s84.ctcode.system.ctcode.*;
import s84.ctcode.transpiler.ctcode.*;
import s84.ctcode.transpiler.standardstructure.ctcode.*;
import s84.ctcode.transpiler.cpptranspiler.ctcode.*;
import s84.ctcode.transpiler.python3transpiler.ctcode.*;
import s84.ctcode.transpiler.nodejstranspiler.ctcode.*;
import s84.ctcode.transpiler.java11transpiler.ctcode.*;
import s84.ctcode.transpiler.logtoconsole.ctcode.*;
import s84.ctcode.dbnf.ctcode.*;

public class Main {
    public Main()
    {
    }

    public s84.ctcode.transpiler.ctcode.Transpiler GetCPPTranspiler()
    {
        s84.ctcode.transpiler.cpptranspiler.ctcode.CPPTranspiler specific = new s84.ctcode.transpiler.cpptranspiler.ctcode.CPPTranspiler();
        specific.Initialize();
        s84.ctcode.transpiler.standardstructure.ctcode.StandardStructure structue = new s84.ctcode.transpiler.standardstructure.ctcode.StandardStructure();
        structue.SetTargetSpecificFunctions(specific);
        return structue;
    }

    public s84.ctcode.transpiler.ctcode.Transpiler GetPython3Transpiler()
    {
        s84.ctcode.transpiler.python3transpiler.ctcode.Python3Transpiler specific = new s84.ctcode.transpiler.python3transpiler.ctcode.Python3Transpiler();
        specific.Initialize();
        s84.ctcode.transpiler.standardstructure.ctcode.StandardStructure structue = new s84.ctcode.transpiler.standardstructure.ctcode.StandardStructure();
        structue.SetTargetSpecificFunctions(specific);
        return structue;
    }

    public s84.ctcode.transpiler.ctcode.Transpiler GetNodeJSTranspiler()
    {
        s84.ctcode.transpiler.nodejstranspiler.ctcode.NodeJSTranspiler specific = new s84.ctcode.transpiler.nodejstranspiler.ctcode.NodeJSTranspiler();
        specific.Initialize();
        s84.ctcode.transpiler.standardstructure.ctcode.StandardStructure structue = new s84.ctcode.transpiler.standardstructure.ctcode.StandardStructure();
        structue.SetTargetSpecificFunctions(specific);
        return structue;
    }

    public s84.ctcode.transpiler.ctcode.Transpiler GetJava11Transpiler()
    {
        return new s84.ctcode.transpiler.java11transpiler.ctcode.Java11Transpiler();
    }

    public s84.ctcode.transpiler.ctcode.Transpiler GetLogToConsole()
    {
        s84.ctcode.transpiler.logtoconsole.ctcode.LogToConsole specific = new s84.ctcode.transpiler.logtoconsole.ctcode.LogToConsole();
        specific.Initialize();
        s84.ctcode.transpiler.standardstructure.ctcode.StandardStructure structue = new s84.ctcode.transpiler.standardstructure.ctcode.StandardStructure();
        structue.SetTargetSpecificFunctions(specific);
        return structue;
    }

    public int RunMain(s84.ctcode.system.ctcode.System system, java.lang.String ctcode_file_name, java.lang.String transpiler)
    {
        s84.ctcode.system.ctcode.OutputStream logger = system.GetLoggerDestination();
        java.util.HashMap<java.lang.String, s84.ctcode.transpiler.ctcode.Transpiler> transpilers = new java.util.HashMap<>();
        SetKV(transpilers, "CPPTranspiler", this.GetCPPTranspiler());
        SetKV(transpilers, "Python3Transpiler", this.GetPython3Transpiler());
        SetKV(transpilers, "NodeJSTranspiler", this.GetNodeJSTranspiler());
        SetKV(transpilers, "Java11Transpiler", this.GetJava11Transpiler());
        SetKV(transpilers, "LogToConsole", this.GetLogToConsole());
        if (AsBoolean((AsBoolean(Equals(ctcode_file_name,"")) || AsBoolean((! AsBoolean(HasKV(transpilers, transpiler)))))))
        {
            logger.WriteLine("ctcode <CTCodeFile> <Transpiler>");
            logger.WriteLine("Known transpilers:");
            java.util.ArrayList<java.lang.String> registered_transpilers = Keys(transpilers);
            int index = 0;
            while (AsBoolean((index<Size(registered_transpilers))))
            {
                logger.WriteLine(Concat("    ", Element(registered_transpilers, index)));
                index = (index+1);
            }
            return 1;
        }
        java.lang.String dbnf = system.ReadFileToString(ctcode_file_name);
        if (AsBoolean(Equals(dbnf,"")))
        {
            logger.WriteLine(Concat("The file ", Concat(ctcode_file_name, " is empty or does not exist.")));
            return 1;
        }
        s84.ctcode.dbnf.ctcode.LargeString dbnf_large_string = new s84.ctcode.dbnf.ctcode.LargeString();
        dbnf_large_string.SetData(dbnf);
        s84.ctcode.dbnf.ctcode.LengthString index = new s84.ctcode.dbnf.ctcode.LengthString();
        index.SetData(dbnf_large_string);
        index.SetStart(0);
        index.SetLength(Length(dbnf));
        s84.ctcode.dbnf.ctcode.ParserNetwork parser_network = new s84.ctcode.dbnf.ctcode.ParserNetwork();
        parser_network.Initialize();
        s84.ctcode.dbnf.ctcode.CTCodeFileResult ctcode_file_result = new s84.ctcode.dbnf.ctcode.CTCodeFileResult();
        s84.ctcode.dbnf.ctcode.CTCodeFileParser ctcode_file_parser = parser_network.GetCTCodeFileParser();
        logger.WriteLine("Parsing CTCodeFile...");
        ctcode_file_parser.ParseSingleSave(index, ctcode_file_result);
        if (AsBoolean((AsBoolean(ctcode_file_result.GetResult()) && AsBoolean(Equals(index.GetLength(),0)))))
        {
            logger.WriteLine("Done Parsing CTCodeFile!");
            s84.ctcode.transpiler.ctcode.Transpiler target_transpiler = GetKV(transpilers, transpiler);
            return target_transpiler.Transpile(system, ctcode_file_result.GetValue(), ctcode_file_name);
        }
        else
        {
            logger.WriteLine(Concat("Failed to parse ", Concat(ctcode_file_name, ".")));
            return 1;
        }
    }

    private static <T> void ClearList(java.util.ArrayList<T> input) { input.clear(); }
    private static <T> int Size(java.util.ArrayList<T> input) { return input.size(); }
    private static <T> T Element(java.util.ArrayList<T> input, int element) { return input.get(element); }
    private static <T> void Append(java.util.ArrayList<T> input, T element) { input.add(element); }
    private static <T> void ClearMap(java.util.HashMap<java.lang.String, T> input) { input.clear(); }
    private static <T> void SetKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key, T element) { input.put(key, element); }
    private static <T> java.util.ArrayList<java.lang.String> Keys(java.util.HashMap<java.lang.String, T> input) { return new java.util.ArrayList<>(input.keySet()); }
    private static <T> boolean HasKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key) { return input.containsKey(key); }
    private static <T> T GetKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key) { return input.get(key); }
    private static int Length(java.lang.String input) { return input.length(); }
    private static java.lang.String At(java.lang.String input, int index) { try { return input.substring(index, index + 1);} catch(Exception e) { return ""; }}
    private static int IntAt(java.lang.String input, int index) { return (int)input.charAt(index); }
    private static java.lang.String Concat(java.lang.String left, java.lang.String right) { return left + right; }
    private static <T extends Object> boolean AsBoolean(T value) { return value != null; }
    private static boolean AsBoolean(boolean value) { return value; }
    private static boolean Equals(java.lang.String left, java.lang.String right) { return left.equals(right); }
    private static boolean Equals(boolean left, boolean right) { return left == right; }
    private static boolean Equals(int left, int right) { return left == right; }
    private static boolean Equals(float left, float right) { return left == right; }
}
