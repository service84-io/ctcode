<?php
namespace S84\CTCode\Transpiler\Java11Transpiler\ctcode;

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

class Java11Transpiler implements \S84\CTCode\Transpiler\StandardStructure\ctcode\TargetSpecificFunctions {
    public function __construct() {
        $this->system = null;
        $this->c_t_code_file = null;
        $this->base_name = "";
        $this->logger = null;
        $this->string_helper = null;
        $this->imports = array();
        $this->current_interface = "";
        $this->interface_definition = array();
        $this->current_class = "";
        $this->class_definition = array();
        $this->class_init = array();
        $this->class_members = array();
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
        return $this->string_helper->SnakeCaseToCamelCase($name);
    }

    public function IsReserved(?string $name): ?bool
    {
        return false||$this->string_helper->BeginsWith('reserved_prefix_',$name)||$name=='boolean'||$name=='char'||$name=='float';
    }

    public function GetVariableName(?string $name): ?string
    {
        $value = $this->string_helper->CamelCaseToSnakeCase($name);
        if ($value=='myself')
        {
            return 'this';
        }
        if ($this->IsReserved($value))
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
                $result = Concat($result,', ');
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
            return Concat(Concat('(! AsBoolean(',$r_value),'))');
        }
        return $r_value;
    }

    public function BinaryOperator(?string $op, ?string $r_value_l, ?string $r_value_r): ?string
    {
        if ($op=='+')
        {
            return Concat(Concat(Concat(Concat('(',$r_value_l),'+'),$r_value_r),')');
        }
        if ($op=='-')
        {
            return Concat(Concat(Concat(Concat('(',$r_value_l),'-'),$r_value_r),')');
        }
        if ($op=='<=')
        {
            return Concat(Concat(Concat(Concat('(',$r_value_l),'<='),$r_value_r),')');
        }
        if ($op=='>=')
        {
            return Concat(Concat(Concat(Concat('(',$r_value_l),'>='),$r_value_r),')');
        }
        if ($op=='==')
        {
            return Concat(Concat(Concat(Concat('Equals(',$r_value_l),','),$r_value_r),')');
        }
        if ($op=='!=')
        {
            return Concat(Concat(Concat(Concat('!Equals(',$r_value_l),','),$r_value_r),')');
        }
        if ($op=='<')
        {
            return Concat(Concat(Concat(Concat('(',$r_value_l),'<'),$r_value_r),')');
        }
        if ($op=='>')
        {
            return Concat(Concat(Concat(Concat('(',$r_value_l),'>'),$r_value_r),')');
        }
        if ($op=='||')
        {
            return Concat(Concat(Concat(Concat('(AsBoolean(',$r_value_l),') || AsBoolean('),$r_value_r),'))');
        }
        if ($op=='&&')
        {
            return Concat(Concat(Concat(Concat('(AsBoolean(',$r_value_l),') && AsBoolean('),$r_value_r),'))');
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
            $result = Concat(Concat('java.util.ArrayList<',$result),'>');
            $dimensions = $dimensions-1;
        }
        return $result;
    }

    public function GetMapType(?string $singleton_type): ?string
    {
        return Concat(Concat('java.util.HashMap<java.lang.String, ',$singleton_type),'>');
    }

    public function GetPrimativeType(?string $c_t_type): ?string
    {
        if ($c_t_type=='int')
        {
            return 'int';
        }
        if ($c_t_type=='string')
        {
            return 'java.lang.String';
        }
        if ($c_t_type=='bool')
        {
            return 'boolean';
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
                $result = Concat($this->string_helper->ToLower($name_part),$result);
            }
        }
        return $result;
    }

    public function BeginProcessingCTCodeFile(): void
    {
        ClearList($this->imports);
        $this->current_interface = '';
        ClearList($this->interface_definition);
        $this->current_class = '';
        ClearList($this->class_definition);
        ClearList($this->class_init);
        ClearList($this->class_members);
    }

    public function ProcessExdef(?string $exdef): void
    {
        Append($this->imports,Concat(Concat('import ',$this->string_helper->ToLower($exdef)),'.*;'));
    }

    public function ProcessUnmanagedType(?string $unmanaged_type): void
    {
    }

    public function BeginProcessingInterface(?string $interface_name): void
    {
        ClearList($this->interface_definition);
        $this->current_interface = $interface_name;
    }

    public function ProcessInterfaceFunctionDeclaration(?string $return_type, ?string $function_name, ?array $parameters): void
    {
        Append($this->interface_definition,Concat(Concat(Concat(Concat(Concat($this->string_helper->Indentation(1),$return_type),' '),$function_name),$this->MakeParametersString($parameters)),';'));
    }

    public function FinishProcessingInterface(?string $interface_name): void
    {
        $destination = $this->system->OpenFileWriter(Concat(Concat(Concat($this->string_helper->DotToSlash($this->string_helper->ToLower($this->base_name)),'/'),$this->current_interface),'.java'));
        $destination->WriteLine(Concat(Concat('package ',$this->string_helper->ToLower($this->base_name)),';'));
        $destination->WriteLine('');
        if (Size($this->imports)>0)
        {
            $this->string_helper->WriteLines($destination,$this->imports);
            $destination->WriteLine('');
        }
        $destination->WriteLine(Concat(Concat('public interface ',$interface_name),' {'));
        $this->string_helper->WriteLines($destination,$this->interface_definition);
        $destination->WriteLine('}');
        $this->current_interface = '';
    }

    public function BeginProcessingClass(?string $class_name, ?string $implementing): void
    {
        ClearList($this->class_definition);
        ClearList($this->class_init);
        ClearList($this->class_members);
        $this->current_class = $class_name;
        Append($this->class_init,Concat(Concat(Concat($this->string_helper->Indentation(1),'public '),$class_name),'()'));
        Append($this->class_init,Concat($this->string_helper->Indentation(1),'{'));
    }

    public function BeginProcessingClassFunctionDefinition(?string $return_type, ?string $function_name, ?array $parameters): void
    {
        Append($this->class_definition,Concat(Concat(Concat(Concat(Concat($this->string_helper->Indentation(1),'public '),$return_type),' '),$function_name),$this->MakeParametersString($parameters)));
    }

    public function BeginProcessCodeBlock(?int $indent): void
    {
        Append($this->class_definition,Concat($this->string_helper->Indentation($indent),'{'));
    }

    public function FinishProcessCodeBlock(?int $indent): void
    {
        Append($this->class_definition,Concat($this->string_helper->Indentation($indent),'}'));
    }

    public function BeginProcessConditional(?int $indent, ?string $r_value): void
    {
        Append($this->class_definition,Concat(Concat(Concat($this->string_helper->Indentation($indent),'if (AsBoolean('),$r_value),'))'));
    }

    public function ProcessElse(?int $indent): void
    {
        Append($this->class_definition,Concat($this->string_helper->Indentation($indent),'else'));
    }

    public function FinishProcessConditional(?int $indent, ?string $r_value): void
    {
    }

    public function BeginProcessLoop(?int $indent, ?string $r_value): void
    {
        Append($this->class_definition,Concat(Concat(Concat($this->string_helper->Indentation($indent),'while (AsBoolean('),$r_value),'))'));
    }

    public function FinishProcessLoop(?int $indent, ?string $r_value): void
    {
    }

    public function ProcessRtn(?int $indent, ?string $r_value): void
    {
        Append($this->class_definition,Concat(Concat(Concat($this->string_helper->Indentation($indent),'return '),$r_value),';'));
    }

    public function ProcessDeclaration(?int $indent, ?string $type, ?string $l_value, ?string $r_value): void
    {
        if ($r_value=='')
        {
            $r_value = $this->GetDefault($type);
        }
        Append($this->class_definition,Concat(Concat(Concat(Concat(Concat(Concat($this->string_helper->Indentation($indent),$type),' '),$l_value),' = '),$r_value),';'));
    }

    public function ProcessAssignment(?int $indent, ?string $l_value, ?string $r_value): void
    {
        Append($this->class_definition,Concat(Concat(Concat(Concat($this->string_helper->Indentation($indent),$l_value),' = '),$r_value),';'));
    }

    public function ProcessCall(?int $indent, ?string $call): void
    {
        Append($this->class_definition,Concat(Concat($this->string_helper->Indentation($indent),$call),';'));
    }

    public function FinishProcessingClassFunctionDefinition(?string $return_type, ?string $function_name, ?array $parameters): void
    {
        Append($this->class_definition,'');
    }

    public function ProcessClassMemberDeclaration(?string $member_type, ?string $member_name): void
    {
        Append($this->class_init,Concat(Concat(Concat(Concat(Concat($this->string_helper->Indentation(2),'this.'),$member_name),' = '),$this->GetDefault($member_type)),';'));
        Append($this->class_members,Concat(Concat(Concat(Concat(Concat($this->string_helper->Indentation(1),'private '),$member_type),' '),$member_name),';'));
    }

    public function FinishProcessingClass(?string $class_name, ?string $implementing): void
    {
        $destination = $this->system->OpenFileWriter(Concat(Concat(Concat($this->string_helper->DotToSlash($this->string_helper->ToLower($this->base_name)),'/'),$this->current_class),'.java'));
        $destination->WriteLine(Concat(Concat('package ',$this->string_helper->ToLower($this->base_name)),';'));
        $destination->WriteLine('');
        if (Size($this->imports)>0)
        {
            $this->string_helper->WriteLines($destination,$this->imports);
            $destination->WriteLine('');
        }
        if ($implementing=='')
        {
            $destination->WriteLine(Concat(Concat('public class ',$class_name),' {'));
        }
        else
        {
            $destination->WriteLine(Concat(Concat(Concat(Concat('public class ',$class_name),' implements '),$implementing),' {'));
        }
        $this->string_helper->WriteLines($destination,$this->class_init);
        $destination->WriteLine(Concat($this->string_helper->Indentation(1),'}'));
        $destination->WriteLine('');
        $this->string_helper->WriteLines($destination,$this->class_definition);
        if (Size($this->class_members)>0)
        {
            $this->string_helper->WriteLines($destination,$this->class_members);
            $destination->WriteLine('');
        }
        $this->WriteCommonFunctions($destination);
        $destination->WriteLine('}');
        $this->current_class = '';
    }

    public function WriteCommonFunctions(?\S84\CTCode\System\ctcode\OutputStream $destination_file): void
    {
        $destination_file->WriteLine(Concat($this->string_helper->Indentation(1),'private static <T> void ClearList(java.util.ArrayList<T> input) { input.clear(); }'));
        $destination_file->WriteLine(Concat($this->string_helper->Indentation(1),'private static <T> int Size(java.util.ArrayList<T> input) { return input.size(); }'));
        $destination_file->WriteLine(Concat($this->string_helper->Indentation(1),'private static <T> T Element(java.util.ArrayList<T> input, int element) { return input.get(element); }'));
        $destination_file->WriteLine(Concat($this->string_helper->Indentation(1),'private static <T> void Append(java.util.ArrayList<T> input, T element) { input.add(element); }'));
        $destination_file->WriteLine(Concat($this->string_helper->Indentation(1),'private static <T> void ClearMap(java.util.HashMap<java.lang.String, T> input) { input.clear(); }'));
        $destination_file->WriteLine(Concat($this->string_helper->Indentation(1),'private static <T> void SetKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key, T element) { input.put(key, element); }'));
        $destination_file->WriteLine(Concat($this->string_helper->Indentation(1),'private static <T> java.util.ArrayList<java.lang.String> Keys(java.util.HashMap<java.lang.String, T> input) { return new java.util.ArrayList<>(input.keySet()); }'));
        $destination_file->WriteLine(Concat($this->string_helper->Indentation(1),'private static <T> boolean HasKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key) { return input.containsKey(key); }'));
        $destination_file->WriteLine(Concat($this->string_helper->Indentation(1),'private static <T> T GetKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key) { return input.get(key); }'));
        $destination_file->WriteLine(Concat($this->string_helper->Indentation(1),'private static int Length(java.lang.String input) { return input.length(); }'));
        $destination_file->WriteLine(Concat($this->string_helper->Indentation(1),'private static java.lang.String At(java.lang.String input, int index) { try { return input.substring(index, index + 1);} catch(Exception e) { return ""; }}'));
        $destination_file->WriteLine(Concat($this->string_helper->Indentation(1),'private static int IntAt(java.lang.String input, int index) { return (int)input.charAt(index); }'));
        $destination_file->WriteLine(Concat($this->string_helper->Indentation(1),'private static java.lang.String Concat(java.lang.String left, java.lang.String right) { return left + right; }'));
        $destination_file->WriteLine(Concat($this->string_helper->Indentation(1),'private static <T extends java.lang.Object> boolean AsBoolean(T value) { return value != null; }'));
        $destination_file->WriteLine(Concat($this->string_helper->Indentation(1),'private static boolean AsBoolean(boolean value) { return value; }'));
        $destination_file->WriteLine(Concat($this->string_helper->Indentation(1),'private static boolean Equals(java.lang.String left, java.lang.String right) { return left.equals(right); }'));
        $destination_file->WriteLine(Concat($this->string_helper->Indentation(1),'private static boolean Equals(boolean left, boolean right) { return left == right; }'));
        $destination_file->WriteLine(Concat($this->string_helper->Indentation(1),'private static boolean Equals(int left, int right) { return left == right; }'));
        $destination_file->WriteLine(Concat($this->string_helper->Indentation(1),'private static boolean Equals(float left, float right) { return left == right; }'));
    }

    public function FinishProcessingCTCodeFile(): void
    {
    }

    public function GetDefault(?string $java_type): ?string
    {
        if ($java_type=='int')
        {
            return '0';
        }
        if ($java_type=='java.lang.String')
        {
            return '""';
        }
        if ($java_type=='boolean')
        {
            return 'false';
        }
        if ($java_type=='float')
        {
            return '0.0';
        }
        if ($java_type=='void')
        {
            return 'null';
        }
        if ($this->string_helper->BeginsWith('java.util.HashMap<java.lang.String',$java_type))
        {
            return 'new java.util.HashMap<>()';
        }
        if ($this->string_helper->BeginsWith('java.util.ArrayList<',$java_type))
        {
            return 'new java.util.ArrayList<>()';
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
            $result = Concat(Concat(Concat($result,$parameter->ReservedPrefixGetType()),' '),$parameter->GetName());
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
    private $interface_definition;
    private $current_class;
    private $class_definition;
    private $class_init;
    private $class_members;
}

?>
