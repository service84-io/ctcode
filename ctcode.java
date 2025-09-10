import s84.ctcode.system.ctcode.System;
import s84.ctcode.system.ctcode.OutputStream;
import s84.ctcode.main.ctcode.Main;
import java.nio.file.Files;
import java.nio.file.Path;
import java.io.FileWriter;
import java.io.BufferedWriter;

public class ctcode {
    private static class SystemImplementation implements s84.ctcode.system.ctcode.System {
        public java.lang.String ReadFileToString(java.lang.String file_name) {
            try {
                return java.nio.file.Files.readString(java.nio.file.Path.of(file_name));
            } catch(Exception e) {
                return "";
            }
        }
        public OutputStream OpenFileWriter(java.lang.String file_name) {
            return new FileWriter(file_name);
        }
        public OutputStream GetLoggerDestination() {
            return new Logger();
        }
    }
    private static class FileWriter implements s84.ctcode.system.ctcode.OutputStream {
        public FileWriter(java.lang.String file_name) {
            try {
                this.destination = new java.io.BufferedWriter(new java.io.FileWriter(file_name, false));
            } catch(Exception e) {
                java.lang.System.out.println(e);
            }
        }
        public void WriteLine(java.lang.String line) {
            try {
                destination.write(line);
                destination.newLine();
                destination.flush();
            } catch(Exception e) {
                java.lang.System.out.println(e);
            }
        }

        private java.io.BufferedWriter destination;
    }
    private static class Logger implements s84.ctcode.system.ctcode.OutputStream {
        public void WriteLine(java.lang.String line) {
            java.lang.System.out.println(line);
        }
    }
    public static void main(java.lang.String[] args) {
        s84.ctcode.system.ctcode.System system = new SystemImplementation();
        s84.ctcode.main.ctcode.Main main = new s84.ctcode.main.ctcode.Main();
        java.lang.String c_t_code_file_name = "";
        java.lang.String transpiler_name = "";

        if (args.length == 2) {
            c_t_code_file_name = args[0];
            transpiler_name = args[1];
        }

        java.lang.System.exit(main.RunMain(system, c_t_code_file_name, transpiler_name));
    }
}
