<?php
namespace S84\CTCode\Transpiler\StringHelper\ctcode;

include_once "S84.CTCode.System.ctcode.php";

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

class StringHelper {
    public function __construct() {
    }

    public function WriteLines(?\S84\CTCode\System\ctcode\OutputStream $destination, ?array $lines): void
    {
        $lines_index = 0;
        while ($lines_index<Size($lines))
        {
            $line = Element($lines,$lines_index);
            $destination->WriteLine($line);
            $lines_index = $lines_index+1;
        }
    }

    public function IsReserved(?string $name): ?bool
    {
        return false||$this->BeginsWith('ReservedPrefix',$name)||$this->BeginsWith('reserved_prefix_',$name)||$name=='GetType'||$name=='Object'||$name=='Return'||$name=='String'||$name=='boolean'||$name=='char'||$name=='decimal'||$name=='end'||$name=='float'||$name=='string'||false;
    }

    public function Indentation(?int $indent): ?string
    {
        $result = "";
        $result = '';
        while ($indent>0)
        {
            $indent = $indent-1;
            $result = Concat($result,'    ');
        }
        return $result;
    }

    public function BeginsWith(?string $prefix, ?string $value): ?bool
    {
        if (Length($prefix)>Length($value))
        {
            return false;
        }
        $prefix_index = 0;
        while ($prefix_index<Length($prefix))
        {
            if (At($prefix,$prefix_index)!=At($value,$prefix_index))
            {
                return false;
            }
            $prefix_index = $prefix_index+1;
        }
        return true;
    }

    public function DotToSlash(?string $input): ?string
    {
        $result = '';
        $input_index = 0;
        while ($input_index<Length($input))
        {
            $character = At($input,$input_index);
            if ($character=='.')
            {
                $result = Concat($result,'/');
            }
            else
            {
                $result = Concat($result,$character);
            }
            $input_index = $input_index+1;
        }
        return $result;
    }

    public function DotToFwdSlash(?string $input): ?string
    {
        $result = '';
        $input_index = 0;
        while ($input_index<Length($input))
        {
            $character = At($input,$input_index);
            if ($character=='.')
            {
                $result = Concat($result,'\\');
            }
            else
            {
                $result = Concat($result,$character);
            }
            $input_index = $input_index+1;
        }
        return $result;
    }

    public function StripDot(?string $input): ?string
    {
        $index = 0;
        $index = 0;
        $result = "";
        $result = '';
        while ($index<Length($input))
        {
            $character = "";
            $character = At($input,$index);
            if ($character=='.')
            {
                $result = Concat($result,'_');
            }
            else
            {
                $result = Concat($result,$character);
            }
            $index = $index+1;
        }
        return $result;
    }

    public function SnakeCaseToCamelCase(?string $snake_case): ?string
    {
        $capitalize_this_letter = true;
        $camel_case = '';
        $index = 0;
        $index = 0;
        while ($index<Length($snake_case))
        {
            $source_character = At($snake_case,$index);
            if ($source_character=='_')
            {
                $capitalize_this_letter = true;
            }
            else
            {
                if ($capitalize_this_letter==true)
                {
                    $upper_character = $this->CharacterToUpper($source_character);
                    $capitalize_this_letter = false;
                    $camel_case = Concat($camel_case,$upper_character);
                }
                else
                {
                    $capitalize_this_letter = false;
                    $camel_case = Concat($camel_case,$source_character);
                }
            }
            $index = $index+1;
        }
        return $camel_case;
    }

    public function CamelCaseToSnakeCase(?string $camel_case): ?string
    {
        $delimiter = '_';
        $snake_case = '';
        $index = 0;
        while ($index<Length($camel_case))
        {
            $source_character = At($camel_case,$index);
            $lower_character = $this->CharacterToLower($source_character);
            if ($this->IsUpper($source_character)||$this->IsDigit($source_character))
            {
                $is_first_character = Length($snake_case)==0;
                if (!$is_first_character)
                {
                    $snake_case = Concat($snake_case,$delimiter);
                }
            }
            $snake_case = Concat($snake_case,$lower_character);
            $index = $index+1;
        }
        return $snake_case;
    }

    public function IsUpper(?string $character): ?bool
    {
        $result = false;
        $result = false;
        $result = $result||$character=='A';
        $result = $result||$character=='B';
        $result = $result||$character=='C';
        $result = $result||$character=='D';
        $result = $result||$character=='E';
        $result = $result||$character=='F';
        $result = $result||$character=='G';
        $result = $result||$character=='H';
        $result = $result||$character=='I';
        $result = $result||$character=='J';
        $result = $result||$character=='K';
        $result = $result||$character=='L';
        $result = $result||$character=='M';
        $result = $result||$character=='N';
        $result = $result||$character=='O';
        $result = $result||$character=='P';
        $result = $result||$character=='Q';
        $result = $result||$character=='R';
        $result = $result||$character=='S';
        $result = $result||$character=='T';
        $result = $result||$character=='U';
        $result = $result||$character=='V';
        $result = $result||$character=='W';
        $result = $result||$character=='X';
        $result = $result||$character=='Y';
        $result = $result||$character=='Z';
        return $result;
    }

    public function IsDigit(?string $character): ?bool
    {
        $result = false;
        $result = false;
        $result = $result||$character=='0';
        $result = $result||$character=='1';
        $result = $result||$character=='2';
        $result = $result||$character=='3';
        $result = $result||$character=='4';
        $result = $result||$character=='5';
        $result = $result||$character=='6';
        $result = $result||$character=='7';
        $result = $result||$character=='8';
        $result = $result||$character=='9';
        return $result;
    }

    public function ToLower(?string $input): ?string
    {
        $index = 0;
        $result = '';
        while ($index<Length($input))
        {
            $character = At($input,$index);
            $lower_character = $this->CharacterToLower($character);
            $result = Concat($result,$lower_character);
            $index = $index+1;
        }
        return $result;
    }

    public function CharacterToLower(?string $input): ?string
    {
        if ($input=='A')
        {
            return 'a';
        }
        if ($input=='B')
        {
            return 'b';
        }
        if ($input=='C')
        {
            return 'c';
        }
        if ($input=='D')
        {
            return 'd';
        }
        if ($input=='E')
        {
            return 'e';
        }
        if ($input=='F')
        {
            return 'f';
        }
        if ($input=='G')
        {
            return 'g';
        }
        if ($input=='H')
        {
            return 'h';
        }
        if ($input=='I')
        {
            return 'i';
        }
        if ($input=='J')
        {
            return 'j';
        }
        if ($input=='K')
        {
            return 'k';
        }
        if ($input=='L')
        {
            return 'l';
        }
        if ($input=='M')
        {
            return 'm';
        }
        if ($input=='N')
        {
            return 'n';
        }
        if ($input=='O')
        {
            return 'o';
        }
        if ($input=='P')
        {
            return 'p';
        }
        if ($input=='Q')
        {
            return 'q';
        }
        if ($input=='R')
        {
            return 'r';
        }
        if ($input=='S')
        {
            return 's';
        }
        if ($input=='T')
        {
            return 't';
        }
        if ($input=='U')
        {
            return 'u';
        }
        if ($input=='V')
        {
            return 'v';
        }
        if ($input=='W')
        {
            return 'w';
        }
        if ($input=='X')
        {
            return 'x';
        }
        if ($input=='Y')
        {
            return 'y';
        }
        if ($input=='Z')
        {
            return 'z';
        }
        return $input;
    }

    public function ToUpper(?string $input): ?string
    {
        $index = 0;
        $result = '';
        while ($index<Length($input))
        {
            $character = At($input,$index);
            $upper_character = $this->CharacterToUpper($character);
            $result = Concat($result,$upper_character);
            $index = $index+1;
        }
        return $result;
    }

    public function CharacterToUpper(?string $input): ?string
    {
        if ($input=='a')
        {
            return 'A';
        }
        if ($input=='b')
        {
            return 'B';
        }
        if ($input=='c')
        {
            return 'C';
        }
        if ($input=='d')
        {
            return 'D';
        }
        if ($input=='e')
        {
            return 'E';
        }
        if ($input=='f')
        {
            return 'F';
        }
        if ($input=='g')
        {
            return 'G';
        }
        if ($input=='h')
        {
            return 'H';
        }
        if ($input=='i')
        {
            return 'I';
        }
        if ($input=='j')
        {
            return 'J';
        }
        if ($input=='k')
        {
            return 'K';
        }
        if ($input=='l')
        {
            return 'L';
        }
        if ($input=='m')
        {
            return 'M';
        }
        if ($input=='n')
        {
            return 'N';
        }
        if ($input=='o')
        {
            return 'O';
        }
        if ($input=='p')
        {
            return 'P';
        }
        if ($input=='q')
        {
            return 'Q';
        }
        if ($input=='r')
        {
            return 'R';
        }
        if ($input=='s')
        {
            return 'S';
        }
        if ($input=='t')
        {
            return 'T';
        }
        if ($input=='u')
        {
            return 'U';
        }
        if ($input=='v')
        {
            return 'V';
        }
        if ($input=='w')
        {
            return 'W';
        }
        if ($input=='x')
        {
            return 'X';
        }
        if ($input=='y')
        {
            return 'Y';
        }
        if ($input=='z')
        {
            return 'Z';
        }
        return $input;
    }

}

?>
