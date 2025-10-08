<?php

include_once "S84.CTCode.System.ctcode.php";
include_once "S84.CTCode.Main.ctcode.php";

class FileImplementation implements \S84\CTCode\System\ctcode\OutputStream {
    public function __construct(?string $file_name) {
        $path = dirname($file_name);

        if (!is_dir($path)) {
            $permissions = 0755;
            mkdir($path, $permissions, true);
        }

        $this->file_handle = fopen($file_name, 'w');
    }

    public function WriteLine(?string $line): void {
        fwrite($this->file_handle, $line);
        fwrite($this->file_handle, "\n");
        fflush($this->file_handle);
    }
}

class LoggerImplementation implements \S84\CTCode\System\ctcode\OutputStream {
    public function WriteLine(?string $line): void {
        echo $line;
        echo "\n";
    }
}

class SystemImplementation implements \S84\CTCode\System\ctcode\System {
    public function ReadFileToString(?string $file_name): ?string {
        return file_get_contents($file_name);
    }
    public function OpenFileWriter(?string $file_name): ?\S84\CTCode\System\ctcode\OutputStream {
        return new FileImplementation($file_name);
    }
    public function GetLoggerDestination(): ?\S84\CTCode\System\ctcode\OutputStream {
        return new LoggerImplementation();
    }
}

function main($argv, $argc): int {
    $system = new SystemImplementation();
    $main = new \S84\CTCode\Main\ctcode\Main();
    $c_t_code_file_name = "";
    $transpiler_name = "";

    if ($argc == 3) {
        $c_t_code_file_name = $argv[1];
        $transpiler_name = $argv[2];
    }
    $logger = $system->GetLoggerDestination();
    return $main->RunMain($system, $c_t_code_file_name, $transpiler_name);
}

exit(main($argv, $argc));
?>