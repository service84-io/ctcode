<?php
namespace S84\CTCode\Main\ctcode;

include_once "S84.CTCode.System.ctcode.php";
include_once "S84.CTCode.Transpiler.ctcode.php";
include_once "S84.CTCode.dbnf.ctcode.php";
include_once "S84.CTCode.Transpiler.StandardStructure.ctcode.php";
include_once "S84.CTCode.Transpiler.CPPTranspiler.ctcode.php";
include_once "S84.CTCode.Transpiler.CSharpTranspiler.ctcode.php";
include_once "S84.CTCode.Transpiler.Java11Transpiler.ctcode.php";
include_once "S84.CTCode.Transpiler.LogToConsole.ctcode.php";
include_once "S84.CTCode.Transpiler.NodeJSTranspiler.ctcode.php";
include_once "S84.CTCode.Transpiler.PHPTranspiler.ctcode.php";
include_once "S84.CTCode.Transpiler.Python3Transpiler.ctcode.php";
include_once "S84.CTCode.Transpiler.RubyTranspiler.ctcode.php";

function ClearList(array & $input): void { $input = array(); }
function Size(array $input): int { return count($input); }
function Element(array $input, int $element) { return $input[$element]; }
function Append(array & $input, mixed $element): void { $input[] = $element; }
function ClearMap(array & $input): void { reset($input); }
function SetKV(array & $input, string $key, mixed $element): void { $input[$key] = $element; }
function Keys(array $input): array { return array_keys($input); }
function HasKV(array $input, string $key): bool { return array_key_exists($key, $input); }
function GetKV(array $input, string $key) { return $input[$key]; }
function Length(string $input): int { return strlen($input); }
function At(string $input, int $index): string { return substr($input, $index, 1); }
function IntAt(string $input, int $index): int { return ord(substr($input, $index, 1)); }
function Concat(string $left, string $right): string { return $left . $right; }

class Main {
    public function __construct() {
    }

    public function GetCPPTranspiler(): ?\S84\CTCode\Transpiler\ctcode\Transpiler
    {
        $specific = new \S84\CTCode\Transpiler\CPPTranspiler\ctcode\CPPTranspiler();
        $specific->Initialize();
        $structue = new \S84\CTCode\Transpiler\StandardStructure\ctcode\StandardStructure();
        $structue->SetTargetSpecificFunctions($specific);
        return $structue;
    }

    public function GetCSharpTranspiler(): ?\S84\CTCode\Transpiler\ctcode\Transpiler
    {
        $specific = new \S84\CTCode\Transpiler\CSharpTranspiler\ctcode\CSharpTranspiler();
        $specific->Initialize();
        $structue = new \S84\CTCode\Transpiler\StandardStructure\ctcode\StandardStructure();
        $structue->SetTargetSpecificFunctions($specific);
        return $structue;
    }

    public function GetJava11Transpiler(): ?\S84\CTCode\Transpiler\ctcode\Transpiler
    {
        $specific = new \S84\CTCode\Transpiler\Java11Transpiler\ctcode\Java11Transpiler();
        $specific->Initialize();
        $structue = new \S84\CTCode\Transpiler\StandardStructure\ctcode\StandardStructure();
        $structue->SetTargetSpecificFunctions($specific);
        return $structue;
    }

    public function GetLogToConsole(): ?\S84\CTCode\Transpiler\ctcode\Transpiler
    {
        $specific = new \S84\CTCode\Transpiler\LogToConsole\ctcode\LogToConsole();
        $specific->Initialize();
        $structue = new \S84\CTCode\Transpiler\StandardStructure\ctcode\StandardStructure();
        $structue->SetTargetSpecificFunctions($specific);
        return $structue;
    }

    public function GetNodeJSTranspiler(): ?\S84\CTCode\Transpiler\ctcode\Transpiler
    {
        $specific = new \S84\CTCode\Transpiler\NodeJSTranspiler\ctcode\NodeJSTranspiler();
        $specific->Initialize();
        $structue = new \S84\CTCode\Transpiler\StandardStructure\ctcode\StandardStructure();
        $structue->SetTargetSpecificFunctions($specific);
        return $structue;
    }

    public function GetPHPTranspiler(): ?\S84\CTCode\Transpiler\ctcode\Transpiler
    {
        $specific = new \S84\CTCode\Transpiler\PHPTranspiler\ctcode\PHPTranspiler();
        $specific->Initialize();
        $structue = new \S84\CTCode\Transpiler\StandardStructure\ctcode\StandardStructure();
        $structue->SetTargetSpecificFunctions($specific);
        return $structue;
    }

    public function GetPython3Transpiler(): ?\S84\CTCode\Transpiler\ctcode\Transpiler
    {
        $specific = new \S84\CTCode\Transpiler\Python3Transpiler\ctcode\Python3Transpiler();
        $specific->Initialize();
        $structue = new \S84\CTCode\Transpiler\StandardStructure\ctcode\StandardStructure();
        $structue->SetTargetSpecificFunctions($specific);
        return $structue;
    }

    public function GetRubyTranspiler(): ?\S84\CTCode\Transpiler\ctcode\Transpiler
    {
        $specific = new \S84\CTCode\Transpiler\RubyTranspiler\ctcode\RubyTranspiler();
        $specific->Initialize();
        $structue = new \S84\CTCode\Transpiler\StandardStructure\ctcode\StandardStructure();
        $structue->SetTargetSpecificFunctions($specific);
        return $structue;
    }

    public function RunMain(?\S84\CTCode\System\ctcode\System $system, ?string $ctcode_file_name, ?string $transpiler): ?int
    {
        $logger = $system->GetLoggerDestination();
        $transpilers = array();
        SetKV($transpilers,'CPPTranspiler',$this->GetCPPTranspiler());
        SetKV($transpilers,'CSharpTranspiler',$this->GetCSharpTranspiler());
        SetKV($transpilers,'Java11Transpiler',$this->GetJava11Transpiler());
        SetKV($transpilers,'LogToConsole',$this->GetLogToConsole());
        SetKV($transpilers,'NodeJSTranspiler',$this->GetNodeJSTranspiler());
        SetKV($transpilers,'PHPTranspiler',$this->GetPHPTranspiler());
        SetKV($transpilers,'Python3Transpiler',$this->GetPython3Transpiler());
        SetKV($transpilers,'RubyTranspiler',$this->GetRubyTranspiler());
        if ($ctcode_file_name==''||!HasKV($transpilers,$transpiler))
        {
            $logger->WriteLine('ctcode <CTCodeFile> <Transpiler>');
            $logger->WriteLine('Known transpilers:');
            $registered_transpilers = Keys($transpilers);
            $registered_transpilers_index = 0;
            while ($registered_transpilers_index<Size($registered_transpilers))
            {
                $logger->WriteLine(Concat('    ',Element($registered_transpilers,$registered_transpilers_index)));
                $registered_transpilers_index = $registered_transpilers_index+1;
            }
            return 1;
        }
        $ctcode = $system->ReadFileToString($ctcode_file_name);
        if ($ctcode=='')
        {
            $logger->WriteLine(Concat('The file ',Concat($ctcode_file_name,' is empty or does not exist.')));
            return 1;
        }
        $ctcode_large_string = new \S84\CTCode\dbnf\ctcode\LargeString();
        $ctcode_large_string->SetData($ctcode);
        $index = new \S84\CTCode\dbnf\ctcode\LengthString();
        $index->SetData($ctcode_large_string);
        $index->SetStart(0);
        $index->SetLength(Length($ctcode));
        $parser_network = new \S84\CTCode\dbnf\ctcode\ParserNetwork();
        $parser_network->Initialize();
        $ctcode_file_result = new \S84\CTCode\dbnf\ctcode\CTCodeFileResult();
        $ctcode_file_parser = $parser_network->GetCTCodeFileParser();
        $logger->WriteLine('Parsing CTCodeFile...');
        $ctcode_file_parser->ParseSingleSave($index,$ctcode_file_result);
        if ($ctcode_file_result->GetResult()&&$index->GetLength()==0)
        {
            $logger->WriteLine('Done Parsing CTCodeFile!');
            $target_transpiler = GetKV($transpilers,$transpiler);
            return $target_transpiler->Transpile($system,$ctcode_file_result->GetValue(),$ctcode_file_name);
        }
        else
        {
            $logger->WriteLine(Concat('Failed to parse ',Concat($ctcode_file_name,'.')));
            return 1;
        }
    }

}

?>
