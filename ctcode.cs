public class LoggerImplementation : S84.CTCode.System.ctcode.OutputStream
{
    public void WriteLine(string? line)
    {
        Console.WriteLine(line ?? "");
    }
}
public class FileImplementation : S84.CTCode.System.ctcode.OutputStream
{
    public FileImplementation(string? file_name)
    {
        try
        {
            Directory.GetParent(file_name ?? "").Create();
        }
        catch { }
        this.destination = new System.IO.StreamWriter(file_name??"");
    }
    public void WriteLine(string? line)
    {
        this.destination.WriteLine(line ?? "");
        this.destination.Flush();
    }

    private System.IO.StreamWriter destination;
}
public class SystemImplementation : S84.CTCode.System.ctcode.System
{
    public string? ReadFileToString(string? file_name)
    {
        return System.IO.File.ReadAllText(file_name ?? "");
    }
    public S84.CTCode.System.ctcode.OutputStream? OpenFileWriter(string? file_name)
    {
        return new FileImplementation(file_name);
    }
    public S84.CTCode.System.ctcode.OutputStream? GetLoggerDestination()
    {
        return new LoggerImplementation();
    }
}
public class CTCodeMain
{
    public static int Main(string[] args)
    {
        S84.CTCode.Main.ctcode.Main main = new S84.CTCode.Main.ctcode.Main();
        SystemImplementation system = new SystemImplementation();
        string c_t_code_file_name = "";
        string transpiler_name = "";

        if (args.Length == 2) {
            c_t_code_file_name = args[0];
            transpiler_name = args[1];
        }

        return main.RunMain(system, c_t_code_file_name, transpiler_name) ?? 0;
    }
}