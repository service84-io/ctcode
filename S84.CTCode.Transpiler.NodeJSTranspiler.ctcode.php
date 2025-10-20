<?php
namespace S84\CTCode\Transpiler\NodeJSTranspiler\ctcode;

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

class NodeJSTranspiler implements \S84\CTCode\Transpiler\StandardStructure\ctcode\TargetSpecificFunctions {
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
            return 'this';
        }
        if ($value=='nothing')
        {
            return 'null';
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
        return Concat(Concat('new ',$type),'()');
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
            return Concat('! ',$r_value);
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
            return Concat(Concat($r_value_l,' || '),$r_value_r);
        }
        if ($op=='&&')
        {
            return Concat(Concat($r_value_l,' && '),$r_value_r);
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
    }

    public function ProcessExdef(?string $exdef): void
    {
        Append($this->imports,Concat(Concat(Concat(Concat('import * as ',$this->string_helper->StripDot($exdef)),' from "./'),$this->string_helper->StripDot($exdef)),'.js"'));
    }

    public function ProcessUnmanagedType(?string $unmanaged_type): void
    {
    }

    public function BeginProcessingInterface(?string $interface_name): void
    {
        $this->current_interface = $interface_name;
        Append($this->interface_definitions,Concat(Concat('export class ',$interface_name),' {'));
    }

    public function ProcessInterfaceFunctionDeclaration(?string $return_type, ?string $function_name, ?array $parameters): void
    {
        Append($this->interface_definitions,Concat(Concat(Concat($this->string_helper->Indentation(1),$function_name),$this->MakeParametersString($parameters)),' {}'));
    }

    public function FinishProcessingInterface(?string $interface_name): void
    {
        Append($this->interface_definitions,'}');
        Append($this->interface_definitions,'');
        $this->current_interface = '';
    }

    public function BeginProcessingClass(?string $class_name, ?string $implementing): void
    {
        $this->current_class = $class_name;
        Append($this->class_definitions,Concat(Concat('export class ',$class_name),' {'));
        ClearList($this->class_init);
        ClearList($this->class_functions);
        Append($this->class_init,Concat($this->string_helper->Indentation(1),'constructor() {'));
    }

    public function BeginProcessingClassFunctionDefinition(?string $return_type, ?string $function_name, ?array $parameters): void
    {
        Append($this->class_functions,'');
        Append($this->class_functions,Concat(Concat($this->string_helper->Indentation(1),$function_name),$this->MakeParametersString($parameters)));
    }

    public function BeginProcessCodeBlock(?int $indent): void
    {
        Append($this->class_functions,Concat($this->string_helper->Indentation($indent),'{'));
    }

    public function FinishProcessCodeBlock(?int $indent): void
    {
        Append($this->class_functions,Concat($this->string_helper->Indentation($indent),'}'));
    }

    public function BeginProcessConditional(?int $indent, ?string $r_value): void
    {
        Append($this->class_functions,Concat(Concat(Concat($this->string_helper->Indentation($indent),'if ('),$r_value),')'));
    }

    public function ProcessElse(?int $indent): void
    {
        Append($this->class_functions,Concat($this->string_helper->Indentation($indent),'else'));
    }

    public function FinishProcessConditional(?int $indent, ?string $r_value): void
    {
    }

    public function BeginProcessLoop(?int $indent, ?string $r_value): void
    {
        Append($this->class_functions,Concat(Concat(Concat($this->string_helper->Indentation($indent),'while ('),$r_value),')'));
    }

    public function FinishProcessLoop(?int $indent, ?string $r_value): void
    {
    }

    public function ProcessRtn(?int $indent, ?string $r_value): void
    {
        Append($this->class_functions,Concat(Concat($this->string_helper->Indentation($indent),'return '),$r_value));
    }

    public function ProcessDeclaration(?int $indent, ?string $type, ?string $l_value, ?string $r_value): void
    {
        if ($r_value=='')
        {
            $r_value = $this->GetDefault($type);
        }
        Append($this->class_functions,Concat(Concat(Concat(Concat($this->string_helper->Indentation($indent),'var '),$l_value),' = '),$r_value));
    }

    public function ProcessAssignment(?int $indent, ?string $l_value, ?string $r_value): void
    {
        Append($this->class_functions,Concat(Concat(Concat($this->string_helper->Indentation($indent),$l_value),' = '),$r_value));
    }

    public function ProcessCall(?int $indent, ?string $call): void
    {
        Append($this->class_functions,Concat($this->string_helper->Indentation($indent),$call));
    }

    public function FinishProcessingClassFunctionDefinition(?string $return_type, ?string $function_name, ?array $parameters): void
    {
    }

    public function ProcessClassMemberDeclaration(?string $member_type, ?string $member_name): void
    {
        Append($this->class_init,Concat(Concat(Concat(Concat($this->string_helper->Indentation(2),'this.'),$member_name),' = '),$this->GetDefault($member_type)));
    }

    public function FinishProcessingClass(?string $class_name, ?string $implementing): void
    {
        Append($this->class_init,Concat($this->string_helper->Indentation(1),'}'));
        $class_init_index = 0;
        while ($class_init_index<Size($this->class_init))
        {
            $line = Element($this->class_init,$class_init_index);
            Append($this->class_definitions,$line);
            $class_init_index = $class_init_index+1;
        }
        $class_functions_index = 0;
        while ($class_functions_index<Size($this->class_functions))
        {
            $line = Element($this->class_functions,$class_functions_index);
            Append($this->class_definitions,$line);
            $class_functions_index = $class_functions_index+1;
        }
        Append($this->class_definitions,'}');
        Append($this->class_definitions,'');
        $this->current_class = '';
    }

    public function WriteCommonFunctions(?\S84\CTCode\System\ctcode\OutputStream $destination_file): void
    {
        $destination_file->WriteLine('function ClearList(input) { input.length = 0; }');
        $destination_file->WriteLine('function Size(input) { return input.length; }');
        $destination_file->WriteLine('function Element(input, element) { return input[element]; }');
        $destination_file->WriteLine('function Append(input, element) { input.push(element); }');
        $destination_file->WriteLine('function ClearMap(input) { input.clear(); }');
        $destination_file->WriteLine('function SetKV(input, key, element) { input.set(key, element); }');
        $destination_file->WriteLine('function Keys(input) { return Array.from(input.keys()); }');
        $destination_file->WriteLine('function HasKV(input, key) { return input.has(key); }');
        $destination_file->WriteLine('function GetKV(input, key) { return input.get(key); }');
        $destination_file->WriteLine('function Length(input) { return input.length; }');
        $destination_file->WriteLine('function At(input, index) { return input[index]; }');
        $destination_file->WriteLine('function IntAt(input, index) { return input.charCodeAt(index); }');
        $destination_file->WriteLine('function Concat(left, right) { return left + right; }');
    }

    public function FinishProcessingCTCodeFile(): void
    {
        $destination_file_name = Concat($this->string_helper->StripDot($this->base_name),'.js');
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

    public function GetDefault(?string $javascript_type): ?string
    {
        if ($javascript_type=='int')
        {
            return '0';
        }
        if ($javascript_type=='string')
        {
            return '""';
        }
        if ($javascript_type=='bool')
        {
            return 'false';
        }
        if ($javascript_type=='float')
        {
            return '0.0';
        }
        if ($javascript_type=='void')
        {
            return 'null';
        }
        if ($this->string_helper->BeginsWith('dict[str',$javascript_type))
        {
            return 'new Map()';
        }
        if ($this->string_helper->BeginsWith('list[',$javascript_type))
        {
            return '[]';
        }
        return 'null';
    }

    public function MakeParametersString(?array $parameters): ?string
    {
        $result = '(';
        $parameters_index = 0;
        while ($parameters_index<Size($parameters))
        {
            $parameter = Element($parameters,$parameters_index);
            if ($parameters_index!=0)
            {
                $result = Concat($result,', ');
            }
            $result = Concat($result,$parameter->GetName());
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
}

?>
