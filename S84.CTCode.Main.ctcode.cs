namespace S84.CTCode.Main.ctcode;

public class Main
{
    public Main()
    {
    }

    public S84.CTCode.Transpiler.ctcode.Transpiler? GetCPPTranspiler()
    {
        S84.CTCode.Transpiler.CPPTranspiler.ctcode.CPPTranspiler? specific = new S84.CTCode.Transpiler.CPPTranspiler.ctcode.CPPTranspiler();
        specific?.Initialize();
        S84.CTCode.Transpiler.StandardStructure.ctcode.StandardStructure? structue = new S84.CTCode.Transpiler.StandardStructure.ctcode.StandardStructure();
        structue?.SetTargetSpecificFunctions(specific);
        return structue;
    }

    public S84.CTCode.Transpiler.ctcode.Transpiler? GetCSharpTranspiler()
    {
        S84.CTCode.Transpiler.CSharpTranspiler.ctcode.CSharpTranspiler? specific = new S84.CTCode.Transpiler.CSharpTranspiler.ctcode.CSharpTranspiler();
        specific?.Initialize();
        S84.CTCode.Transpiler.StandardStructure.ctcode.StandardStructure? structue = new S84.CTCode.Transpiler.StandardStructure.ctcode.StandardStructure();
        structue?.SetTargetSpecificFunctions(specific);
        return structue;
    }

    public S84.CTCode.Transpiler.ctcode.Transpiler? GetJava11Transpiler()
    {
        S84.CTCode.Transpiler.Java11Transpiler.ctcode.Java11Transpiler? specific = new S84.CTCode.Transpiler.Java11Transpiler.ctcode.Java11Transpiler();
        specific?.Initialize();
        S84.CTCode.Transpiler.StandardStructure.ctcode.StandardStructure? structue = new S84.CTCode.Transpiler.StandardStructure.ctcode.StandardStructure();
        structue?.SetTargetSpecificFunctions(specific);
        return structue;
    }

    public S84.CTCode.Transpiler.ctcode.Transpiler? GetLogToConsole()
    {
        S84.CTCode.Transpiler.LogToConsole.ctcode.LogToConsole? specific = new S84.CTCode.Transpiler.LogToConsole.ctcode.LogToConsole();
        specific?.Initialize();
        S84.CTCode.Transpiler.StandardStructure.ctcode.StandardStructure? structue = new S84.CTCode.Transpiler.StandardStructure.ctcode.StandardStructure();
        structue?.SetTargetSpecificFunctions(specific);
        return structue;
    }

    public S84.CTCode.Transpiler.ctcode.Transpiler? GetNodeJSTranspiler()
    {
        S84.CTCode.Transpiler.NodeJSTranspiler.ctcode.NodeJSTranspiler? specific = new S84.CTCode.Transpiler.NodeJSTranspiler.ctcode.NodeJSTranspiler();
        specific?.Initialize();
        S84.CTCode.Transpiler.StandardStructure.ctcode.StandardStructure? structue = new S84.CTCode.Transpiler.StandardStructure.ctcode.StandardStructure();
        structue?.SetTargetSpecificFunctions(specific);
        return structue;
    }

    public S84.CTCode.Transpiler.ctcode.Transpiler? GetPHPTranspiler()
    {
        S84.CTCode.Transpiler.PHPTranspiler.ctcode.PHPTranspiler? specific = new S84.CTCode.Transpiler.PHPTranspiler.ctcode.PHPTranspiler();
        specific?.Initialize();
        S84.CTCode.Transpiler.StandardStructure.ctcode.StandardStructure? structue = new S84.CTCode.Transpiler.StandardStructure.ctcode.StandardStructure();
        structue?.SetTargetSpecificFunctions(specific);
        return structue;
    }

    public S84.CTCode.Transpiler.ctcode.Transpiler? GetPython3Transpiler()
    {
        S84.CTCode.Transpiler.Python3Transpiler.ctcode.Python3Transpiler? specific = new S84.CTCode.Transpiler.Python3Transpiler.ctcode.Python3Transpiler();
        specific?.Initialize();
        S84.CTCode.Transpiler.StandardStructure.ctcode.StandardStructure? structue = new S84.CTCode.Transpiler.StandardStructure.ctcode.StandardStructure();
        structue?.SetTargetSpecificFunctions(specific);
        return structue;
    }

    public S84.CTCode.Transpiler.ctcode.Transpiler? GetRubyTranspiler()
    {
        S84.CTCode.Transpiler.RubyTranspiler.ctcode.RubyTranspiler? specific = new S84.CTCode.Transpiler.RubyTranspiler.ctcode.RubyTranspiler();
        specific?.Initialize();
        S84.CTCode.Transpiler.StandardStructure.ctcode.StandardStructure? structue = new S84.CTCode.Transpiler.StandardStructure.ctcode.StandardStructure();
        structue?.SetTargetSpecificFunctions(specific);
        return structue;
    }

    public int? RunMain(S84.CTCode.System.ctcode.System? system,string? ctcode_file_name,string? transpiler)
    {
        S84.CTCode.System.ctcode.OutputStream? logger = system?.GetLoggerDestination();
        Dictionary<string,S84.CTCode.Transpiler.ctcode.Transpiler?>? transpilers = new Dictionary<string,S84.CTCode.Transpiler.ctcode.Transpiler?>();
        SetKV(transpilers,"CPPTranspiler",this?.GetCPPTranspiler());
        SetKV(transpilers,"CSharpTranspiler",this?.GetCSharpTranspiler());
        SetKV(transpilers,"Java11Transpiler",this?.GetJava11Transpiler());
        SetKV(transpilers,"LogToConsole",this?.GetLogToConsole());
        SetKV(transpilers,"NodeJSTranspiler",this?.GetNodeJSTranspiler());
        SetKV(transpilers,"PHPTranspiler",this?.GetPHPTranspiler());
        SetKV(transpilers,"Python3Transpiler",this?.GetPython3Transpiler());
        SetKV(transpilers,"RubyTranspiler",this?.GetRubyTranspiler());
        if (AsBoolean(AsBoolean(ctcode_file_name=="")||AsBoolean(! AsBoolean(HasKV(transpilers,transpiler)))))
        {
            logger?.WriteLine("ctcode <CTCodeFile> <Transpiler>");
            logger?.WriteLine("Known transpilers:");
            List<string?>? registered_transpilers = Keys(transpilers);
            int? registered_transpilers_index = 0;
            while (AsBoolean(registered_transpilers_index<Size(registered_transpilers)))
            {
                logger?.WriteLine(Concat("    ",Element(registered_transpilers,registered_transpilers_index)));
                registered_transpilers_index = registered_transpilers_index+1;
            }
            return 1;
        }
        string? ctcode = system?.ReadFileToString(ctcode_file_name);
        if (AsBoolean(ctcode==""))
        {
            logger?.WriteLine(Concat("The file ",Concat(ctcode_file_name," is empty or does not exist.")));
            return 1;
        }
        S84.CTCode.dbnf.ctcode.LargeString? ctcode_large_string = new S84.CTCode.dbnf.ctcode.LargeString();
        ctcode_large_string?.SetData(ctcode);
        S84.CTCode.dbnf.ctcode.LengthString? index = new S84.CTCode.dbnf.ctcode.LengthString();
        index?.SetData(ctcode_large_string);
        index?.SetStart(0);
        index?.SetLength(Length(ctcode));
        S84.CTCode.dbnf.ctcode.ParserNetwork? parser_network = new S84.CTCode.dbnf.ctcode.ParserNetwork();
        parser_network?.Initialize();
        S84.CTCode.dbnf.ctcode.CTCodeFileResult? ctcode_file_result = new S84.CTCode.dbnf.ctcode.CTCodeFileResult();
        S84.CTCode.dbnf.ctcode.CTCodeFileParser? ctcode_file_parser = parser_network?.GetCTCodeFileParser();
        logger?.WriteLine("Parsing CTCodeFile...");
        ctcode_file_parser?.ParseSingleSave(index,ctcode_file_result);
        if (AsBoolean(AsBoolean(ctcode_file_result?.GetResult())&&AsBoolean(index?.GetLength()==0)))
        {
            logger?.WriteLine("Done Parsing CTCodeFile!");
            S84.CTCode.Transpiler.ctcode.Transpiler? target_transpiler = GetKV(transpilers,transpiler);
            return target_transpiler?.Transpile(system,ctcode_file_result?.GetValue(),ctcode_file_name);
        }
        else
        {
            logger?.WriteLine(Concat("Failed to parse ",Concat(ctcode_file_name,".")));
            return 1;
        }
    }

    private static void ClearList<T>(List<T>? input) { input?.Clear(); }
    private static int? Size<T>(List<T>? input) { return input?.Count; }
    private static T? Element<T>(List<T>? input, int? element) { return input != null ? input[element??0] : default; }
    private static void Append<T>(List<T>? input, T element) { input?.Add(element); }
    private static void ClearMap<T>(Dictionary<string, T>? input) { input?.Clear();  }
    private static void SetKV<T>(Dictionary<string, T>? input, string? key, T element) { input?.Add(key??"", element); }
    private static List<string?>? Keys<T>(Dictionary<string, T>? input) { return new List<string?>(input?.Keys?.ToList()??new List<string>()); }
    private static bool? HasKV<T>(Dictionary<string, T>? input, string? key) { return input?.ContainsKey(key??""); }
    private static T? GetKV<T>(Dictionary<string, T>? input, string? key) { return input != null ? input[key??""] : default; }
    private static int? Length(string? input) { return input?.Length;  }
    private static string? At(string? input, int? index) { return input?.Length > index ? input?.Substring(index??0, 1) : "";  }
    private static int? IntAt(string? input, int? index) { return input?.Length > index ? (input[index??0] + 255 % 255) : 0;  }
    private static string? Concat(string? left, string? right) { return left + right; }
    private static bool AsBoolean(bool value) { return value; }
    private static bool AsBoolean<T>(T? value) { return value != null && !value.Equals(false); }
}
