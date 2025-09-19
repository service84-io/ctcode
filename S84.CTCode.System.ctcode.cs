namespace S84.CTCode.System.ctcode;

public interface OutputStream
{
    void WriteLine(string? line);
}

public interface System
{
    string? ReadFileToString(string? file_name);
    OutputStream? OpenFileWriter(string? file_name);
    OutputStream? GetLoggerDestination();
}

