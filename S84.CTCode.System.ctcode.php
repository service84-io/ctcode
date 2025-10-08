<?php
namespace S84\CTCode\System\ctcode;

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

interface OutputStream {
    public function WriteLine(?string $line): void;
}

interface System {
    public function ReadFileToString(?string $file_name): ?string;
    public function OpenFileWriter(?string $file_name): ?OutputStream;
    public function GetLoggerDestination(): ?OutputStream;
}

?>
