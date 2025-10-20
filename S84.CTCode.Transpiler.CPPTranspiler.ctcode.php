<?php
namespace S84\CTCode\Transpiler\CPPTranspiler\ctcode;

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

class CPPTranspiler implements \S84\CTCode\Transpiler\StandardStructure\ctcode\TargetSpecificFunctions {
    public function __construct() {
        $this->system = null;
        $this->c_t_code_file = null;
        $this->base_name = "";
        $this->logger = null;
        $this->string_helper = null;
        $this->includes = array();
        $this->interface_declarations = array();
        $this->class_declarations = array();
        $this->current_interface = "";
        $this->interface_definitions = array();
        $this->current_class = "";
        $this->class_definitions = array();
        $this->class_init = array();
        $this->class_functions = array();
        $this->class_members = array();
        $this->function_definitions = array();
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
        return 0;
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
            return 'NULL';
        }
        if ($this->string_helper->IsReserved($value))
        {
            return Concat('reserved_prefix_',$value);
        }
        return $value;
    }

    public function GetVariableChain(?array $name_parts): ?string
    {
        $delimiter = '->';
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
            $result = Concat(Concat($result,'->'),$name_part);
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
        return Concat(Concat(Concat(Concat('std::shared_ptr<',$type),'>(new '),$type),'())');
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
        return Concat(Concat('std::string("',$literal),'")');
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
            $result = Concat(Concat('std::vector<',$result),'>');
            $dimensions = $dimensions-1;
        }
        return $result;
    }

    public function GetMapType(?string $singleton_type): ?string
    {
        return Concat(Concat('std::unordered_map<std::string, ',$singleton_type),'>');
    }

    public function GetPrimativeType(?string $c_t_type): ?string
    {
        if ($c_t_type=='int')
        {
            return 'int';
        }
        if ($c_t_type=='string')
        {
            return 'std::string';
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
        return Concat(Concat('OmniPointer<',$c_t_type),'>');
    }

    public function GetQualifiedTypeName(?array $name_parts): ?string
    {
        $delimiter = '::';
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
        ClearList($this->includes);
        ClearList($this->interface_declarations);
        ClearList($this->class_declarations);
        $this->current_interface = '';
        ClearList($this->interface_definitions);
        $this->current_class = '';
        ClearList($this->class_definitions);
        ClearList($this->class_init);
        ClearList($this->class_functions);
        ClearList($this->class_members);
        ClearList($this->function_definitions);
    }

    public function ProcessExdef(?string $exdef): void
    {
        Append($this->includes,Concat('#include "',Concat($exdef,'.hpp"')));
    }

    public function ProcessUnmanagedType(?string $unmanaged_type): void
    {
    }

    public function BeginProcessingInterface(?string $interface_name): void
    {
        $this->current_interface = $interface_name;
        Append($this->interface_declarations,Concat(Concat('class ',$interface_name),';'));
        Append($this->interface_definitions,Concat(Concat('class ',$interface_name),' {'));
        Append($this->interface_definitions,'public:');
    }

    public function ProcessInterfaceFunctionDeclaration(?string $return_type, ?string $function_name, ?array $parameters): void
    {
        Append($this->interface_definitions,Concat(Concat(Concat(Concat(Concat(Concat($this->string_helper->Indentation(1),'virtual '),$return_type),' '),$function_name),$this->MakeParametersString($parameters)),' = 0;'));
    }

    public function FinishProcessingInterface(?string $interface_name): void
    {
        Append($this->interface_definitions,'};');
        Append($this->interface_definitions,'');
        $this->current_interface = '';
    }

    public function BeginProcessingClass(?string $class_name, ?string $implementing): void
    {
        $this->current_class = $class_name;
        Append($this->class_declarations,Concat(Concat('class ',$class_name),';'));
        if ($implementing=='')
        {
            Append($this->class_definitions,Concat(Concat('class ',$class_name),' {'));
        }
        else
        {
            Append($this->class_definitions,Concat(Concat(Concat(Concat('class ',$class_name),' : public '),$implementing),' {'));
        }
        Append($this->class_definitions,'public:');
        Append($this->class_definitions,Concat(Concat($this->string_helper->Indentation(1),$class_name),'();'));
        Append($this->class_definitions,Concat(Concat(Concat($this->string_helper->Indentation(1),'inline ~'),$class_name),'() {}'));
        Append($this->class_definitions,'');
        ClearList($this->class_init);
        ClearList($this->class_functions);
        ClearList($this->class_members);
        Append($this->class_init,Concat(Concat(Concat($class_name,'::'),$class_name),'()'));
        Append($this->class_init,'{');
    }

    public function BeginProcessingClassFunctionDefinition(?string $return_type, ?string $function_name, ?array $parameters): void
    {
        Append($this->class_definitions,Concat(Concat(Concat(Concat(Concat($this->string_helper->Indentation(1),$return_type),' '),$function_name),$this->MakeParametersString($parameters)),';'));
        Append($this->class_functions,Concat(Concat(Concat(Concat(Concat($return_type,' '),$this->current_class),'::'),$function_name),$this->MakeParametersString($parameters)));
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
        Append($this->class_functions,Concat(Concat(Concat($this->string_helper->Indentation($indent),'return '),$r_value),';'));
    }

    public function ProcessDeclaration(?int $indent, ?string $type, ?string $l_value, ?string $r_value): void
    {
        if ($r_value=='')
        {
            $r_value = $this->GetDefault($type);
        }
        if ($r_value=='')
        {
            Append($this->class_functions,Concat(Concat(Concat(Concat($this->string_helper->Indentation($indent),$type),' '),$l_value),';'));
        }
        else
        {
            Append($this->class_functions,Concat(Concat(Concat(Concat(Concat(Concat($this->string_helper->Indentation($indent),$type),' '),$l_value),' = '),$r_value),';'));
        }
    }

    public function ProcessAssignment(?int $indent, ?string $l_value, ?string $r_value): void
    {
        Append($this->class_functions,Concat(Concat(Concat(Concat($this->string_helper->Indentation($indent),$l_value),' = '),$r_value),';'));
    }

    public function ProcessCall(?int $indent, ?string $call): void
    {
        Append($this->class_functions,Concat(Concat($this->string_helper->Indentation($indent),$call),';'));
    }

    public function FinishProcessingClassFunctionDefinition(?string $return_type, ?string $function_name, ?array $parameters): void
    {
        Append($this->class_functions,'');
    }

    public function ProcessClassMemberDeclaration(?string $member_type, ?string $member_name): void
    {
        $default_value = $this->GetDefault($member_type);
        if ($default_value!='')
        {
            Append($this->class_init,Concat(Concat(Concat(Concat(Concat($this->string_helper->Indentation(1),'this->'),$member_name),' = '),$default_value),';'));
        }
        else
        {
            Append($this->class_init,Concat(Concat(Concat(Concat(Concat($this->string_helper->Indentation(1),'/*this->'),$member_name),' = '),'NO_DEFAULT'),';*/'));
        }
        Append($this->class_members,Concat(Concat(Concat(Concat($this->string_helper->Indentation(1),$member_type),' '),$member_name),';'));
    }

    public function FinishProcessingClass(?string $class_name, ?string $implementing): void
    {
        if (Size($this->class_members)>0)
        {
            Append($this->class_definitions,'');
            Append($this->class_definitions,'private:');
            $class_members_index = 0;
            while ($class_members_index<Size($this->class_members))
            {
                $line = Element($this->class_members,$class_members_index);
                Append($this->class_definitions,$line);
                $class_members_index = $class_members_index+1;
            }
        }
        Append($this->class_definitions,'};');
        Append($this->class_definitions,'');
        Append($this->class_init,'}');
        Append($this->class_init,'');
        $class_init_index = 0;
        while ($class_init_index<Size($this->class_init))
        {
            $line = Element($this->class_init,$class_init_index);
            Append($this->function_definitions,$line);
            $class_init_index = $class_init_index+1;
        }
        $class_functions_index = 0;
        while ($class_functions_index<Size($this->class_functions))
        {
            $line = Element($this->class_functions,$class_functions_index);
            Append($this->function_definitions,$line);
            $class_functions_index = $class_functions_index+1;
        }
        $this->current_class = '';
    }

    public function WriteCommonFunctions(?\S84\CTCode\System\ctcode\OutputStream $destination): void
    {
        $destination->WriteLine('#ifndef CTCODE_COMMON_FUNCTIONS_VERSION_1');
        $destination->WriteLine('#define CTCODE_COMMON_FUNCTIONS_VERSION_1');
        $destination->WriteLine('template<typename T>');
        $destination->WriteLine('class OmniPointer');
        $destination->WriteLine('{');
        $destination->WriteLine('public:');
        $destination->WriteLine('    OmniPointer() { value_raw = NULL; }');
        $destination->WriteLine('    OmniPointer(T* value) { value_raw = value; }');
        $destination->WriteLine('    template<typename U>');
        $destination->WriteLine('    OmniPointer(U* value) { value_raw = value; }');
        $destination->WriteLine('    OmniPointer(std::shared_ptr<T> value) { value_raw = NULL; value_shared = value; }');
        $destination->WriteLine('    template<typename U>');
        $destination->WriteLine('    OmniPointer(std::shared_ptr<U> value) { value_raw = NULL; value_shared = value; }');
        $destination->WriteLine('    template<typename U>');
        $destination->WriteLine('    OmniPointer(OmniPointer<U> value) { value_raw = value.value_raw; value_shared = value.value_shared; }');
        $destination->WriteLine('');
        $destination->WriteLine('    operator bool()');
        $destination->WriteLine('    {');
        $destination->WriteLine('        if (value_raw) return true;');
        $destination->WriteLine('        return value_shared.get() != NULL;');
        $destination->WriteLine('    }');
        $destination->WriteLine('    T& operator*()');
        $destination->WriteLine('    {');
        $destination->WriteLine('        if (value_raw) return *value_raw;');
        $destination->WriteLine('        return *value_shared;');
        $destination->WriteLine('    }');
        $destination->WriteLine('    T* operator->()');
        $destination->WriteLine('    {');
        $destination->WriteLine('        if (value_raw) return value_raw;');
        $destination->WriteLine('        return value_shared.get();');
        $destination->WriteLine('    }');
        $destination->WriteLine('    T* raw()');
        $destination->WriteLine('    {');
        $destination->WriteLine('        if (value_raw) return value_raw;');
        $destination->WriteLine('        return value_shared.get();');
        $destination->WriteLine('    }');
        $destination->WriteLine('');
        $destination->WriteLine('    T* value_raw;');
        $destination->WriteLine('    std::shared_ptr<T> value_shared;');
        $destination->WriteLine('};');
        $destination->WriteLine('');
        $destination->WriteLine('template<typename T>');
        $destination->WriteLine('inline std::vector<T*> UnwrapOmniList(std::vector<OmniPointer<T>> input) {');
        $destination->WriteLine('	std::vector<T*> result;');
        $destination->WriteLine('	for (typename std::vector<OmniPointer<T>>::iterator index = input.begin();index != input.end();index++) {');
        $destination->WriteLine('		result.push_back(index->raw());');
        $destination->WriteLine('	}');
        $destination->WriteLine('	return result;');
        $destination->WriteLine('};');
        $destination->WriteLine('template<typename T>');
        $destination->WriteLine('inline void ClearList(std::vector<T>& input) { input.clear(); };');
        $destination->WriteLine('template<typename T>');
        $destination->WriteLine('inline int Size(const std::vector<T>& input) { return input.size(); };');
        $destination->WriteLine('template<typename T>');
        $destination->WriteLine('inline T Element(const std::vector<T>& input, int element) { return input.at(element); };');
        $destination->WriteLine('template<typename T>');
        $destination->WriteLine('inline void Append(std::vector<T>& input, T element) { input.push_back(element); };');
        $destination->WriteLine('template<typename T>');
        $destination->WriteLine('inline void ClearMap(std::unordered_map<std::string, T>& input) { input.clear(); };');
        $destination->WriteLine('template<typename T>');
        $destination->WriteLine('inline void SetKV(std::unordered_map<std::string, T>& input, const std::string& key, T element)');
        $destination->WriteLine('{');
        $destination->WriteLine('    input.erase(key);');
        $destination->WriteLine('    input.insert(std::pair<std::string, T>(key, element));');
        $destination->WriteLine('}');
        $destination->WriteLine('template<typename T>');
        $destination->WriteLine('inline std::vector<std::string> Keys(const std::unordered_map<std::string, T>& input)');
        $destination->WriteLine('{');
        $destination->WriteLine('    std::vector<std::string> result;');
        $destination->WriteLine('    for(typename std::unordered_map<std::string, T>::const_iterator index = input.begin();index != input.end();index++) {');
        $destination->WriteLine('        result.push_back(index->first);');
        $destination->WriteLine('    }');
        $destination->WriteLine('    return result;');
        $destination->WriteLine('}');
        $destination->WriteLine('template<typename T>');
        $destination->WriteLine('inline bool HasKV(const std::unordered_map<std::string, T>& input, const std::string& key)');
        $destination->WriteLine('{');
        $destination->WriteLine('    typename std::unordered_map<std::string, T>::const_iterator beginning = input.find(key);');
        $destination->WriteLine('    return beginning != input.end();');
        $destination->WriteLine('}');
        $destination->WriteLine('template<typename T>');
        $destination->WriteLine('inline T GetKV(const std::unordered_map<std::string, T>& input, const std::string& key) { return input.at(key); }');
        $destination->WriteLine('inline int Length(const std::string& input) { return (int)input.length(); };');
        $destination->WriteLine('inline std::string At(const std::string& input, int index) { return input.substr(index, 1); };');
        $destination->WriteLine('inline int IntAt(const std::string& input, int index) { return (input.at(index) + 256) % 256; };');
        $destination->WriteLine('inline std::string Concat(const std::string& left, const std::string& right) { return left + right; };');
        $destination->WriteLine('#endif');
    }

    public function WriteBeginingGuard(?\S84\CTCode\System\ctcode\OutputStream $file): void
    {
        $guard_name = $this->string_helper->ToUpper($this->string_helper->StripDot(Concat($this->base_name,'_H')));
        $file->WriteLine(Concat('#ifndef ',$guard_name));
        $file->WriteLine(Concat('#define ',$guard_name));
    }

    public function TokenizeBaseName(?string $name): ?array
    {
        $base_name_tokens = array();
        $current_token = '';
        $index = 0;
        while ($index<Length($name))
        {
            $character = At($name,$index);
            if ($character=='.')
            {
                Append($base_name_tokens,$current_token);
                $current_token = '';
            }
            else
            {
                $current_token = Concat($current_token,$character);
            }
            $index = $index+1;
        }
        Append($base_name_tokens,$current_token);
        return $base_name_tokens;
    }

    public function WriteBeginingNamespace(?\S84\CTCode\System\ctcode\OutputStream $file): void
    {
        $base_name_tokens = $this->TokenizeBaseName($this->base_name);
        $base_name_tokens_index = 0;
        while ($base_name_tokens_index<Size($base_name_tokens))
        {
            $base_name_token = Element($base_name_tokens,$base_name_tokens_index);
            $file->WriteLine(Concat(Concat('namespace ',$this->string_helper->ToLower($base_name_token)),' {'));
            $base_name_tokens_index = $base_name_tokens_index+1;
        }
    }

    public function WriteEndingNamespace(?\S84\CTCode\System\ctcode\OutputStream $file): void
    {
        $base_name_tokens = $this->TokenizeBaseName($this->base_name);
        $base_name_tokens_index = 0;
        while ($base_name_tokens_index<Size($base_name_tokens))
        {
            $base_name_token = Element($base_name_tokens,$base_name_tokens_index);
            $file->WriteLine('};');
            $base_name_tokens_index = $base_name_tokens_index+1;
        }
    }

    public function WriteEndingGuard(?\S84\CTCode\System\ctcode\OutputStream $file): void
    {
        $file->WriteLine('#endif');
    }

    public function FinishProcessingCTCodeFile(): void
    {
        $header_file_name = Concat($this->base_name,'.hpp');
        $header_file = $this->system->OpenFileWriter($header_file_name);
        $source_file_name = Concat($this->base_name,'.cpp');
        $source_file = $this->system->OpenFileWriter($source_file_name);
        $this->WriteBeginingGuard($header_file);
        $header_file->WriteLine('');
        if (Size($this->includes)>0)
        {
            $this->string_helper->WriteLines($header_file,$this->includes);
            $header_file->WriteLine('');
        }
        $header_file->WriteLine('#include <cstring>');
        $header_file->WriteLine('#include <list>');
        $header_file->WriteLine('#include <unordered_map>');
        $header_file->WriteLine('#include <memory>');
        $header_file->WriteLine('#include <string>');
        $header_file->WriteLine('#include <vector>');
        $header_file->WriteLine('');
        $this->WriteCommonFunctions($header_file);
        $header_file->WriteLine('');
        $this->WriteBeginingNamespace($header_file);
        $header_file->WriteLine('');
        if (Size($this->interface_declarations)>0)
        {
            $this->string_helper->WriteLines($header_file,$this->interface_declarations);
            $header_file->WriteLine('');
        }
        if (Size($this->class_declarations)>0)
        {
            $this->string_helper->WriteLines($header_file,$this->class_declarations);
            $header_file->WriteLine('');
        }
        if (Size($this->interface_definitions)>0)
        {
            $this->string_helper->WriteLines($header_file,$this->interface_definitions);
        }
        $this->string_helper->WriteLines($header_file,$this->class_definitions);
        $this->WriteEndingNamespace($header_file);
        $header_file->WriteLine('');
        $this->WriteEndingGuard($header_file);
        $source_file->WriteLine(Concat(Concat('#include "',$this->base_name),'.hpp"'));
        $source_file->WriteLine('');
        $this->WriteBeginingNamespace($source_file);
        $source_file->WriteLine('');
        if (Size($this->function_definitions)>0)
        {
            $this->string_helper->WriteLines($source_file,$this->function_definitions);
            $source_file->WriteLine('');
        }
        $this->WriteEndingNamespace($source_file);
    }

    public function GetDefault(?string $cpp_type): ?string
    {
        if ($cpp_type=='int')
        {
            return '0';
        }
        if ($cpp_type=='std::string')
        {
            return '""';
        }
        if ($cpp_type=='bool')
        {
            return 'false';
        }
        if ($cpp_type=='float')
        {
            return '0.0';
        }
        if ($cpp_type=='void')
        {
            return 'NULL';
        }
        if ($this->string_helper->BeginsWith('std::unordered_map<std::string, ',$cpp_type))
        {
            return '';
        }
        if ($this->string_helper->BeginsWith('std::vector<',$cpp_type))
        {
            return '';
        }
        return 'NULL';
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
    private $includes;
    private $interface_declarations;
    private $class_declarations;
    private $current_interface;
    private $interface_definitions;
    private $current_class;
    private $class_definitions;
    private $class_init;
    private $class_functions;
    private $class_members;
    private $function_definitions;
}

?>
