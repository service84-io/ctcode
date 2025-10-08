<?php
namespace S84\CTCode\Transpiler\LogToConsole\ctcode;

include_once "S84.CTCode.dbnf.ctcode.php";
include_once "S84.CTCode.Transpiler.StandardStructure.ctcode.php";
include_once "S84.CTCode.Transpiler.StringHelper.ctcode.php";

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

class LogToConsole implements \S84\CTCode\Transpiler\StandardStructure\ctcode\TargetSpecificFunctions {
    public function __construct() {
        $this->system = null;
        $this->c_t_code_file = null;
        $this->base_name = "";
        $this->logger = null;
        $this->string_helper = null;
    }

    public function Initialize(): void
    {
        $this->string_helper = new \S84\CTCode\Transpiler\StringHelper\ctcode\StringHelper();
    }

    public function SetSystem(?\S84\CTCode\System\ctcode\System $system): void
    {
        $this->system = $system;
    }

    public function SetCTCodeFile(?\S84\CTCode\dbnf\ctcode\CTCodeFile $c_t_code_file): void
    {
        $this->c_t_code_file = $c_t_code_file;
    }

    public function SetBaseName(?string $base_name): void
    {
        $this->base_name = $base_name;
    }

    public function SetLogger(?\S84\CTCode\System\ctcode\OutputStream $logger): void
    {
        $this->logger = $logger;
    }

    public function GetBaseIndentation(): ?int
    {
        return 3;
    }

    public function GetCallName(?string $name): ?string
    {
        return $this->string_helper->SnakeCaseToCamelCase($name);
    }

    public function GetVariableName(?string $name): ?string
    {
        $value = $this->string_helper->CamelCaseToSnakeCase($name);
        if ($value=='myself')
        {
            return 'thyself';
        }
        return $value;
    }

    public function GetVariableChain(?array $name_parts): ?string
    {
        $delimiter = '.';
        $first_name = Element($name_parts,0);
        $result = $this->GetVariableName($first_name);
        $name_parts_index = 1;
        while ($name_parts_index<Size($name_parts))
        {
            $name = Element($name_parts,$name_parts_index);
            $result = Concat(Concat($result,$delimiter),$this->GetVariableName($name));
            $name_parts_index = $name_parts_index+1;
        }
        return $result;
    }

    public function ConvertCall(?array $name_chain, ?array $parameters): ?string
    {
        $result = Element($name_chain,0);
        $name_chain_index = 1;
        while ($name_chain_index<Size($name_chain))
        {
            $name_part = Element($name_chain,$name_chain_index);
            $result = Concat(Concat($result,'.'),$name_part);
            $name_chain_index = $name_chain_index+1;
        }
        $result = Concat($result,'(');
        if (Size($parameters)>0)
        {
            $result = Concat($result,Element($parameters,0));
            $parameters_index = 1;
            while ($parameters_index<Size($parameters))
            {
                $parameter = Element($parameters,$parameters_index);
                $result = Concat($result,',');
                $result = Concat($result,$parameter);
                $parameters_index = $parameters_index+1;
            }
        }
        $result = Concat($result,')');
        return $result;
    }

    public function ConvertAllocate(?string $type): ?string
    {
        return Concat('new ',$type);
    }

    public function ConvertByte(?string $high, ?string $low): ?string
    {
        return Concat(Concat('0x',$high),$low);
    }

    public function ConvertDecimal(?string $reserved_prefix_decimal): ?string
    {
        return $reserved_prefix_decimal;
    }

    public function ConvertNumber(?string $number): ?string
    {
        return $number;
    }

    public function ConvertBoolean(?string $reserved_prefix_boolean): ?string
    {
        if ($reserved_prefix_boolean=='true')
        {
            return 'true';
        }
        if ($reserved_prefix_boolean=='false')
        {
            return 'false';
        }
        return '';
    }

    public function ConvertVariable(?string $variable): ?string
    {
        return $variable;
    }

    public function ConvertString(?string $literal): ?string
    {
        return Concat(Concat('"',$literal),'"');
    }

    public function UnaryOperator(?string $op, ?string $r_value): ?string
    {
        if ($op=='!')
        {
            return Concat('!',$r_value);
        }
        return $r_value;
    }

    public function BinaryOperator(?string $op, ?string $r_value_l, ?string $r_value_r): ?string
    {
        if ($op=='+')
        {
            return Concat(Concat($r_value_l,'+'),$r_value_r);
        }
        if ($op=='-')
        {
            return Concat(Concat($r_value_l,'-'),$r_value_r);
        }
        if ($op=='<=')
        {
            return Concat(Concat($r_value_l,'<='),$r_value_r);
        }
        if ($op=='>=')
        {
            return Concat(Concat($r_value_l,'>='),$r_value_r);
        }
        if ($op=='==')
        {
            return Concat(Concat($r_value_l,'=='),$r_value_r);
        }
        if ($op=='!=')
        {
            return Concat(Concat($r_value_l,'!='),$r_value_r);
        }
        if ($op=='<')
        {
            return Concat(Concat($r_value_l,'<'),$r_value_r);
        }
        if ($op=='>')
        {
            return Concat(Concat($r_value_l,'>'),$r_value_r);
        }
        if ($op=='||')
        {
            return Concat(Concat($r_value_l,'||'),$r_value_r);
        }
        if ($op=='&&')
        {
            return Concat(Concat($r_value_l,'&&'),$r_value_r);
        }
        return '';
    }

    public function GetTypeName(?string $name): ?string
    {
        return $this->string_helper->SnakeCaseToCamelCase($name);
    }

    public function GetDimensionalType(?string $singleton_type, ?int $dimensions): ?string
    {
        $result = $singleton_type;
        while ($dimensions>0)
        {
            $result = Concat($result,'[]');
            $dimensions = $dimensions-1;
        }
        return $result;
    }

    public function GetMapType(?string $singleton_type): ?string
    {
        return Concat($singleton_type,'{}');
    }

    public function GetPrimativeType(?string $c_t_type): ?string
    {
        if ($c_t_type=='int')
        {
            return 'int';
        }
        if ($c_t_type=='string')
        {
            return 'string';
        }
        if ($c_t_type=='bool')
        {
            return 'bool';
        }
        if ($c_t_type=='float')
        {
            return 'float';
        }
        if ($c_t_type=='void')
        {
            return 'void';
        }
        return '';
    }

    public function GetDefinedType(?string $c_t_type): ?string
    {
        return $c_t_type;
    }

    public function GetQualifiedTypeName(?array $name_parts): ?string
    {
        $delimiter = '.';
        $name_parts_index = Size($name_parts)-1;
        $type_part = Element($name_parts,$name_parts_index);
        $result = $this->GetTypeName($type_part);
        if ($name_parts_index>0)
        {
            while ($name_parts_index>0)
            {
                $name_parts_index = $name_parts_index-1;
                $result = Concat($delimiter,$result);
                $name_part = Element($name_parts,$name_parts_index);
                $result = Concat($name_part,$result);
            }
        }
        return $result;
    }

    public function BeginProcessingCTCodeFile(): void
    {
        $this->logger->WriteLine('BeginProcessingCTCodeFile');
    }

    public function FinishProcessingCTCodeFile(): void
    {
        $this->logger->WriteLine('FinishProcessingCTCodeFile');
    }

    public function ProcessExdef(?string $exdef): void
    {
        $this->logger->WriteLine(Concat(Concat($this->string_helper->Indentation(1),'ProcessExdef: '),$exdef));
    }

    public function ProcessUnmanagedType(?string $unmanaged_type): void
    {
        $this->logger->WriteLine(Concat(Concat($this->string_helper->Indentation(1),'ProcessUnmanagedType: '),$unmanaged_type));
    }

    public function BeginProcessingInterface(?string $interface_name): void
    {
        $this->logger->WriteLine(Concat(Concat($this->string_helper->Indentation(1),'BeginProcessingInterface: '),$interface_name));
    }

    public function ProcessInterfaceFunctionDeclaration(?string $return_type, ?string $function_name, ?array $parameters): void
    {
        $this->logger->WriteLine(Concat(Concat(Concat(Concat($this->string_helper->Indentation(2),'ProcessInterfaceFunctionDeclaration: '),$return_type),' '),$function_name));
    }

    public function FinishProcessingInterface(?string $interface_name): void
    {
        $this->logger->WriteLine(Concat(Concat($this->string_helper->Indentation(1),'FinishProcessingInterface: '),$interface_name));
    }

    public function BeginProcessingClass(?string $class_name, ?string $implementing): void
    {
        $this->logger->WriteLine(Concat(Concat(Concat(Concat($this->string_helper->Indentation(1),'BeginProcessingClass: '),$class_name),' '),$implementing));
    }

    public function BeginProcessingClassFunctionDefinition(?string $return_type, ?string $function_name, ?array $parameters): void
    {
        $this->logger->WriteLine(Concat(Concat(Concat(Concat($this->string_helper->Indentation(2),'BeginProcessingClassFunctionDefinition: '),$return_type),' '),$function_name));
    }

    public function BeginProcessCodeBlock(?int $indent): void
    {
        $this->logger->WriteLine(Concat($this->string_helper->Indentation($indent),'BeginProcessCodeBlock'));
    }

    public function FinishProcessCodeBlock(?int $indent): void
    {
        $this->logger->WriteLine(Concat($this->string_helper->Indentation($indent),'FinishProcessCodeBlock'));
    }

    public function BeginProcessConditional(?int $indent, ?string $r_value): void
    {
        $this->logger->WriteLine(Concat(Concat($this->string_helper->Indentation($indent),'BeginProcessConditional: '),$r_value));
    }

    public function ProcessElse(?int $indent): void
    {
        $this->logger->WriteLine(Concat($this->string_helper->Indentation($indent),'ProcessElse'));
    }

    public function FinishProcessConditional(?int $indent, ?string $r_value): void
    {
        $this->logger->WriteLine(Concat(Concat($this->string_helper->Indentation($indent),'FinishProcessConditional: '),$r_value));
    }

    public function BeginProcessLoop(?int $indent, ?string $r_value): void
    {
        $this->logger->WriteLine(Concat(Concat($this->string_helper->Indentation($indent),'BeginProcessLoop: '),$r_value));
    }

    public function FinishProcessLoop(?int $indent, ?string $r_value): void
    {
        $this->logger->WriteLine(Concat(Concat($this->string_helper->Indentation($indent),'FinishProcessLoop: '),$r_value));
    }

    public function ProcessRtn(?int $indent, ?string $r_value): void
    {
        $this->logger->WriteLine(Concat(Concat($this->string_helper->Indentation($indent),'ProcessRtn: '),$r_value));
    }

    public function ProcessDeclaration(?int $indent, ?string $type, ?string $l_value, ?string $r_value): void
    {
        $this->logger->WriteLine(Concat(Concat(Concat(Concat(Concat(Concat($this->string_helper->Indentation($indent),'ProcessDeclaration: '),$type),' '),$l_value),' '),$r_value));
    }

    public function ProcessAssignment(?int $indent, ?string $l_value, ?string $r_value): void
    {
        $this->logger->WriteLine(Concat(Concat(Concat(Concat($this->string_helper->Indentation($indent),'ProcessAssignment: '),$l_value),' '),$r_value));
    }

    public function ProcessCall(?int $indent, ?string $call): void
    {
        $this->logger->WriteLine(Concat(Concat($this->string_helper->Indentation($indent),'ProcessCall: '),$call));
    }

    public function FinishProcessingClassFunctionDefinition(?string $return_type, ?string $function_name, ?array $parameters): void
    {
        $this->logger->WriteLine(Concat(Concat(Concat(Concat($this->string_helper->Indentation(2),'FinishProcessingClassFunctionDefinition: '),$return_type),' '),$function_name));
    }

    public function ProcessClassMemberDeclaration(?string $member_type, ?string $member_name): void
    {
        $this->logger->WriteLine(Concat(Concat(Concat(Concat($this->string_helper->Indentation(2),'ProcessClassMemberDeclaration: '),$member_type),' '),$member_name));
    }

    public function FinishProcessingClass(?string $class_name, ?string $implementing): void
    {
        $this->logger->WriteLine(Concat(Concat($this->string_helper->Indentation(1),'FinishProcessingClass: '),$class_name));
    }

    private $system;
    private $c_t_code_file;
    private $base_name;
    private $logger;
    private $string_helper;
}

?>
