require 'S84.CTCode.System.ctcode'
require 'S84.CTCode.Main.ctcode'

require 'fileutils'

class FileImplementation < ::S84::CTCODE::SYSTEM::CTCODE::OutputStream
    def initialize(file_name)
        directory = File.dirname(file_name)
        FileUtils.mkdir_p(directory)
        @file = File.open(file_name, 'w')
    end

    def WriteLine(line)
        @file.puts line
        @file.flush
    end
end

class LoggerImplementation < ::S84::CTCODE::SYSTEM::CTCODE::OutputStream
    def initialize()
    end

    def WriteLine(line)
        puts line
    end
end

class SystemImplementation < ::S84::CTCODE::SYSTEM::CTCODE::System
    def initialize()
    end

    def ReadFileToString(file_name)
        return File.read(file_name);
    end

    def OpenFileWriter(file_name)
        return FileImplementation.new(file_name)
    end

    def GetLoggerDestination()
        return LoggerImplementation.new()
    end
end

def main(argv)
    system = SystemImplementation.new()
    main = ::S84::CTCODE::MAIN::CTCODE::Main.new()
    c_t_code_file_name = "";
    transpiler_name = "";

    if (argv.length == 2)
        c_t_code_file_name = argv[0];
        transpiler_name = argv[1];
    end

    logger = system.GetLoggerDestination();
    return main.RunMain(system, c_t_code_file_name, transpiler_name);
end

exit(main(ARGV))