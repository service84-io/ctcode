namespace S84.CTCode.Transpiler.ctcode;

public interface OutputStream
{
    void WriteLine(string? line);
}

public interface Transpiler
{
    int? Transpile(S84.CTCode.System.ctcode.System? system,S84.CTCode.dbnf.ctcode.CTCodeFile? ct_code_file,string? base_name);
}

