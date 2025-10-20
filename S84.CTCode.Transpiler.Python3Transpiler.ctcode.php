<?php
namespace S84\CTCode\Transpiler\Python3Transpiler\ctcode;

include_once "S84.CTCode.dbnf.ctcode.php";
include_once "S84.CTCode.System.ctcode.php";
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

class Python3Transpiler implements \S84\CTCode\Transpiler\StandardStructure\ctcode\TargetSpecificFunctions {
    public function __construct() {
        $this->system = null;
        $this->c_t_code_file = null;
        $this->base_name = "";
        $this->logger = null;
        $this->string_helper = null;
        $this->imports = array();
        $this->current_interface = "";
        $this->interface_definitions = array();
        $this->current_class = "";
        $this->class_definitions = array();
        $this->class_init = array();
        $this->class_functions = array();
        $this->current_class_function_has_operation = false;
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
        return 1;
    }

    public function GetCallName(?string $name): ?string
    {
        $value = $this->string_helper->SnakeCaseToCamelCase($name);
        if ($this->string_helper->IsReserved($value))
        {
            return Concat('ReservedPrefix',$value);
        }
        return $value;
    }

    public function GetVariableName(?string $name): ?string
    {
        $value = $this->string_helper->CamelCaseToSnakeCase($name);
        if ($value=='myself')
        {
            return 'self';
        }
        if ($value=='nothing')
        {
            return 'None';
        }
        if ($this->string_helper->IsReserved($value))
        {
            return Concat('reserved_prefix_',$value);
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
        return Concat($type,'()');
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
            return 'True';
        }
        if ($reserved_prefix_boolean=='false')
        {
            return 'False';
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
            return Concat('not ',$r_value);
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
            return Concat(Concat($r_value_l,' or '),$r_value_r);
        }
        if ($op=='&&')
        {
            return Concat(Concat($r_value_l,' and '),$r_value_r);
        }
        return '';
    }

    public function GetTypeName(?string $name): ?string
    {
        $value = $this->string_helper->SnakeCaseToCamelCase($name);
        if ($this->string_helper->IsReserved($value))
        {
            return Concat('ReservedPrefix',$value);
        }
        return $value;
    }

    public function GetDimensionalType(?string $singleton_type, ?int $dimensions): ?string
    {
        $result = $singleton_type;
        while ($dimensions>0)
        {
            $result = Concat(Concat('list[',$result),']');
            $dimensions = $dimensions-1;
        }
        return $result;
    }

    public function GetMapType(?string $singleton_type): ?string
    {
        return Concat(Concat('dict[str, ',$singleton_type),']');
    }

    public function GetPrimativeType(?string $c_t_type): ?string
    {
        if ($c_t_type=='int')
        {
            return 'int';
        }
        if ($c_t_type=='string')
        {
            return 'str';
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
            return 'None';
        }
        return '';
    }

    public function GetDefinedType(?string $c_t_type): ?string
    {
        return $c_t_type;
    }

    public function GetQualifiedTypeName(?array $name_parts): ?string
    {
        $package_delimiter = '_';
        $package_name_delimiter = '.';
        $name_parts_index = Size($name_parts)-1;
        $last_package_index = Size($name_parts)-2;
        $type_part = Element($name_parts,$name_parts_index);
        $result = $this->GetTypeName($type_part);
        if ($name_parts_index>0)
        {
            $result = Concat($package_name_delimiter,$result);
            while ($name_parts_index>0)
            {
                $name_parts_index = $name_parts_index-1;
                $name_part = Element($name_parts,$name_parts_index);
                if ($name_parts_index!=$last_package_index)
                {
                    $result = Concat($package_delimiter,$result);
                }
                $result = Concat($name_part,$result);
            }
        }
        return $result;
    }

    public function BeginProcessingCTCodeFile(): void
    {
        ClearList($this->imports);
        $this->current_interface = '';
        ClearList($this->interface_definitions);
        $this->current_class = '';
        ClearList($this->class_definitions);
        ClearList($this->class_init);
        ClearList($this->class_functions);
        $this->current_class_function_has_operation = false;
    }

    public function ProcessExdef(?string $exdef): void
    {
        Append($this->imports,Concat('import ',$this->string_helper->StripDot($exdef)));
    }

    public function ProcessUnmanagedType(?string $unmanaged_type): void
    {
    }

    public function BeginProcessingInterface(?string $interface_name): void
    {
        $this->current_interface = $interface_name;
        Append($this->interface_definitions,Concat(Concat('class ',$interface_name),':'));
    }

    public function ProcessInterfaceFunctionDeclaration(?string $return_type, ?string $function_name, ?array $parameters): void
    {
        Append($this->interface_definitions,Concat(Concat(Concat(Concat(Concat(Concat($this->string_helper->Indentation(1),'def '),$function_name),$this->MakeParametersString($this->current_interface,$parameters)),' -> \''),$return_type),'\': pass'));
    }

    public function FinishProcessingInterface(?string $interface_name): void
    {
        Append($this->interface_definitions,'');
        $this->current_interface = '';
    }

    public function BeginProcessingClass(?string $class_name, ?string $implementing): void
    {
        $this->current_class = $class_name;
        if ($implementing=='')
        {
            Append($this->class_definitions,Concat(Concat('class ',$class_name),':'));
        }
        else
        {
            Append($this->class_definitions,Concat(Concat(Concat(Concat('class ',$class_name),'('),$implementing),'):'));
        }
        ClearList($this->class_init);
        ClearList($this->class_functions);
        $this->current_class_function_has_operation = false;
        Append($this->class_init,Concat(Concat(Concat($this->string_helper->Indentation(1),'def __init__(self: \''),$class_name),'\'):'));
    }

    public function BeginProcessingClassFunctionDefinition(?string $return_type, ?string $function_name, ?array $parameters): void
    {
        Append($this->class_functions,Concat(Concat(Concat(Concat(Concat(Concat($this->string_helper->Indentation(1),'def '),$function_name),$this->MakeParametersString($this->current_class,$parameters)),' -> \''),$return_type),'\':'));
        $this->current_class_function_has_operation = false;
    }

    public function BeginProcessCodeBlock(?int $indent): void
    {
    }

    public function FinishProcessCodeBlock(?int $indent): void
    {
    }

    public function BeginProcessConditional(?int $indent, ?string $r_value): void
    {
        $this->current_class_function_has_operation = true;
        Append($this->class_functions,Concat(Concat(Concat($this->string_helper->Indentation($indent),'if '),$r_value),':'));
    }

    public function ProcessElse(?int $indent): void
    {
        $this->current_class_function_has_operation = true;
        Append($this->class_functions,Concat($this->string_helper->Indentation($indent),'else:'));
    }

    public function FinishProcessConditional(?int $indent, ?string $r_value): void
    {
        $this->current_class_function_has_operation = true;
    }

    public function BeginProcessLoop(?int $indent, ?string $r_value): void
    {
        $this->current_class_function_has_operation = true;
        Append($this->class_functions,Concat(Concat(Concat($this->string_helper->Indentation($indent),'while '),$r_value),':'));
    }

    public function FinishProcessLoop(?int $indent, ?string $r_value): void
    {
        $this->current_class_function_has_operation = true;
    }

    public function ProcessRtn(?int $indent, ?string $r_value): void
    {
        $this->current_class_function_has_operation = true;
        Append($this->class_functions,Concat(Concat($this->string_helper->Indentation($indent),'return '),$r_value));
    }

    public function ProcessDeclaration(?int $indent, ?string $type, ?string $l_value, ?string $r_value): void
    {
        $this->current_class_function_has_operation = true;
        if ($r_value=='')
        {
            $r_value = $this->GetDefault($type);
        }
        Append($this->class_functions,Concat(Concat(Concat(Concat(Concat($this->string_helper->Indentation($indent),$l_value),': \''),$type),'\' = '),$r_value));
    }

    public function ProcessAssignment(?int $indent, ?string $l_value, ?string $r_value): void
    {
        $this->current_class_function_has_operation = true;
        Append($this->class_functions,Concat(Concat(Concat($this->string_helper->Indentation($indent),$l_value),' = '),$r_value));
    }

    public function ProcessCall(?int $indent, ?string $call): void
    {
        $this->current_class_function_has_operation = true;
        Append($this->class_functions,Concat($this->string_helper->Indentation($indent),$call));
    }

    public function FinishProcessingClassFunctionDefinition(?string $return_type, ?string $function_name, ?array $parameters): void
    {
        if (!$this->current_class_function_has_operation)
        {
            Append($this->class_functions,Concat($this->string_helper->Indentation(2),'pass'));
        }
        Append($this->class_functions,'');
    }

    public function ProcessClassMemberDeclaration(?string $member_type, ?string $member_name): void
    {
        Append($this->class_init,Concat(Concat(Concat(Concat(Concat(Concat($this->string_helper->Indentation(2),'self.'),$member_name),': '),$member_type),' = '),$this->GetDefault($member_type)));
    }

    public function FinishProcessingClass(?string $class_name, ?string $implementing): void
    {
        if (Size($this->class_init)==1)
        {
            Append($this->class_init,Concat($this->string_helper->Indentation(2),'pass'));
        }
        $class_init_index = 0;
        while ($class_init_index<Size($this->class_init))
        {
            $line = Element($this->class_init,$class_init_index);
            Append($this->class_definitions,$line);
            $class_init_index = $class_init_index+1;
        }
        Append($this->class_definitions,'');
        $class_functions_index = 0;
        while ($class_functions_index<Size($this->class_functions))
        {
            $line = Element($this->class_functions,$class_functions_index);
            Append($this->class_definitions,$line);
            $class_functions_index = $class_functions_index+1;
        }
        $this->current_class = '';
    }

    public function WriteCommonFunctions(?\S84\CTCode\System\ctcode\OutputStream $destination_file): void
    {
        $destination_file->WriteLine('def ClearList(input: list) -> None: input.clear()');
        $destination_file->WriteLine('def Size(input: list) -> int: return len(input)');
        $destination_file->WriteLine('def Element(input: list, element: int ) -> any: return input[element]');
        $destination_file->WriteLine('def Append(input: list, element: any) -> None: input.append(element)');
        $destination_file->WriteLine('def ClearMap(input: dict) -> None: input.clear()');
        $destination_file->WriteLine('def SetKV(input: dict, key: str, element: any) -> None: input[key] = element');
        $destination_file->WriteLine('def Keys(input: dict) -> list[str]:');
        $destination_file->WriteLine('    result: list[str] = []');
        $destination_file->WriteLine('    for key in input.keys():');
        $destination_file->WriteLine('        result.append(key)');
        $destination_file->WriteLine('    return result');
        $destination_file->WriteLine('def HasKV(input: dict, key: str) -> bool: return key in input');
        $destination_file->WriteLine('def GetKV(input: dict, key: str) -> any: return input[key]');
        $destination_file->WriteLine('def Length(input: str) -> int: return len(input)');
        $destination_file->WriteLine('def At(input: str, index: int) -> str: return input[index:index+1]');
        $destination_file->WriteLine('def IntAt(input: str, index: int) -> int: return ord(input[index:index+1])');
        $destination_file->WriteLine('def Concat(left: str, right: str) -> str: return left + right');
    }

    public function FinishProcessingCTCodeFile(): void
    {
        $destination_file_name = Concat($this->string_helper->StripDot($this->base_name),'.py');
        $destination_file = $this->system->OpenFileWriter($destination_file_name);
        if (Size($this->imports)>0)
        {
            $this->string_helper->WriteLines($destination_file,$this->imports);
            $destination_file->WriteLine('');
        }
        $this->WriteCommonFunctions($destination_file);
        $destination_file->WriteLine('');
        $this->string_helper->WriteLines($destination_file,$this->interface_definitions);
        $this->string_helper->WriteLines($destination_file,$this->class_definitions);
    }

    public function GetDefault(?string $python_type): ?string
    {
        if ($python_type=='int')
        {
            return '0';
        }
        if ($python_type=='str')
        {
            return '""';
        }
        if ($python_type=='bool')
        {
            return 'False';
        }
        if ($python_type=='float')
        {
            return '0.0';
        }
        if ($python_type=='None')
        {
            return 'None';
        }
        if ($this->string_helper->BeginsWith('dict[str',$python_type))
        {
            return '{}';
        }
        if ($this->string_helper->BeginsWith('list[',$python_type))
        {
            return '[]';
        }
        return 'None';
    }

    public function MakeParametersString(?string $self_type, ?array $parameters): ?string
    {
        $result = Concat(Concat('(self: \'',$self_type),'\'');
        $parameters_index = 0;
        while ($parameters_index<Size($parameters))
        {
            $parameter = Element($parameters,$parameters_index);
            $result = Concat($result,',');
            $result = Concat(Concat(Concat(Concat($result,$parameter->GetName()),': \''),$parameter->ReservedPrefixGetType()),'\'');
            $parameters_index = $parameters_index+1;
        }
        $result = Concat($result,')');
        return $result;
    }

    private $system;
    private $c_t_code_file;
    private $base_name;
    private $logger;
    private $string_helper;
    private $imports;
    private $current_interface;
    private $interface_definitions;
    private $current_class;
    private $class_definitions;
    private $class_init;
    private $class_functions;
    private $current_class_function_has_operation;
}

?>
