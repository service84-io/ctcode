package s84.ctcode.system.ctcode;

public interface System {
    java.lang.String ReadFileToString(java.lang.String file_name);
    OutputStream OpenFileWriter(java.lang.String file_name);
    OutputStream GetLoggerDestination();
}
