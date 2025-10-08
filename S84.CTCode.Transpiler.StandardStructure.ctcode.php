<?php
namespace S84\CTCode\Transpiler\StandardStructure\ctcode;

include_once "S84.CTCode.dbnf.ctcode.php";
include_once "S84.CTCode.System.ctcode.php";
include_once "S84.CTCode.Transpiler.ctcode.php";

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

interface TargetSpecificFunctions {
    public function Initialize(): void;
    public function SetSystem(?\S84\CTCode\System\ctcode\System $system): void;
    public function SetCTCodeFile(?\S84\CTCode\dbnf\ctcode\CTCodeFile $c_t_code_file): void;
    public function SetBaseName(?string $base_name): void;
    public function SetLogger(?\S84\CTCode\System\ctcode\OutputStream $logger): void;
    public function GetBaseIndentation(): ?int;
    public function GetCallName(?string $name): ?string;
    public function GetVariableName(?string $name): ?string;
    public function GetVariableChain(?array $name_parts): ?string;
    public function ConvertCall(?array $name_chain, ?array $parameters): ?string;
    public function ConvertAllocate(?string $type): ?string;
    public function ConvertByte(?string $high, ?string $low): ?string;
    public function ConvertDecimal(?string $reserved_prefix_decimal): ?string;
    public function ConvertNumber(?string $number): ?string;
    public function ConvertBoolean(?string $reserved_prefix_boolean): ?string;
    public function ConvertVariable(?string $variable): ?string;
    public function ConvertString(?string $literal): ?string;
    public function UnaryOperator(?string $op, ?string $r_value): ?string;
    public function BinaryOperator(?string $op, ?string $r_value_l, ?string $r_value_r): ?string;
    public function GetTypeName(?string $name): ?string;
    public function GetDimensionalType(?string $singleton_type, ?int $dimensions): ?string;
    public function GetMapType(?string $singleton_type): ?string;
    public function GetPrimativeType(?string $c_t_type): ?string;
    public function GetDefinedType(?string $c_t_type): ?string;
    public function GetQualifiedTypeName(?array $name_parts): ?string;
    public function BeginProcessingCTCodeFile(): void;
    public function FinishProcessingCTCodeFile(): void;
    public function ProcessExdef(?string $exdef): void;
    public function ProcessUnmanagedType(?string $unmanaged_type): void;
    public function BeginProcessingInterface(?string $interface_name): void;
    public function ProcessInterfaceFunctionDeclaration(?string $return_type, ?string $function_name, ?array $parameters): void;
    public function FinishProcessingInterface(?string $interface_name): void;
    public function BeginProcessingClass(?string $class_name, ?string $implementing): void;
    public function BeginProcessingClassFunctionDefinition(?string $return_type, ?string $function_name, ?array $parameters): void;
    public function BeginProcessCodeBlock(?int $indent): void;
    public function FinishProcessCodeBlock(?int $indent): void;
    public function BeginProcessConditional(?int $indent, ?string $r_value): void;
    public function ProcessElse(?int $indent): void;
    public function FinishProcessConditional(?int $indent, ?string $r_value): void;
    public function BeginProcessLoop(?int $indent, ?string $r_value): void;
    public function FinishProcessLoop(?int $indent, ?string $r_value): void;
    public function ProcessRtn(?int $indent, ?string $r_value): void;
    public function ProcessDeclaration(?int $indent, ?string $type, ?string $l_value, ?string $r_value): void;
    public function ProcessAssignment(?int $indent, ?string $l_value, ?string $r_value): void;
    public function ProcessCall(?int $indent, ?string $call): void;
    public function FinishProcessingClassFunctionDefinition(?string $return_type, ?string $function_name, ?array $parameters): void;
    public function ProcessClassMemberDeclaration(?string $member_type, ?string $member_name): void;
    public function FinishProcessingClass(?string $class_name, ?string $implementing): void;
}

class ParameterDeclaration {
    public function __construct() {
        $this->type = "";
        $this->name = "";
    }

    public function ReservedPrefixGetType(): ?string
    {
        return $this->type;
    }

    public function SetType(?string $input): void
    {
        $this->type = $input;
    }

    public function GetName(): ?string
    {
        return $this->name;
    }

    public function SetName(?string $input): void
    {
        $this->name = $input;
    }

    private $type;
    private $name;
}

class IntegerReference {
    public function __construct() {
        $this->value = 0;
    }

    public function GetValue(): ?int
    {
        return $this->value;
    }

    public function SetValue(?int $value): void
    {
        $this->value = $value;
    }

    private $value;
}

class StandardStructure implements \S84\CTCode\Transpiler\ctcode\Transpiler {
    public function __construct() {
        $this->system = null;
        $this->c_t_code_file = null;
        $this->base_name = "";
        $this->operator_precedent = array();
        $this->logger = null;
        $this->target_specific_functions = null;
    }

    public function SetTargetSpecificFunctions(?TargetSpecificFunctions $target_specific_functions): void
    {
        $this->target_specific_functions = $target_specific_functions;
    }

    public function Transpile(?\S84\CTCode\System\ctcode\System $system, ?\S84\CTCode\dbnf\ctcode\CTCodeFile $c_t_code_file, ?string $base_name): ?int
    {
        ClearList($this->operator_precedent);
        $this->PopulateOperatorPrecedent();
        $this->system = $system;
        $this->c_t_code_file = $c_t_code_file;
        $this->base_name = $base_name;
        $this->logger = $system->GetLoggerDestination();
        $this->target_specific_functions->SetSystem($this->system);
        $this->target_specific_functions->SetCTCodeFile($this->c_t_code_file);
        $this->target_specific_functions->SetBaseName($this->base_name);
        $this->target_specific_functions->SetLogger($this->logger);
        $this->ProcessCTCodeFile($c_t_code_file);
        return 0;
    }

    public function ProcessCTCodeFile(?\S84\CTCode\dbnf\ctcode\CTCodeFile $c_t_code_file): void
    {
        $this->target_specific_functions->BeginProcessingCTCodeFile();
        $this->ProcessExdefs($c_t_code_file);
        $this->ProcessUnmanagedTypes($c_t_code_file);
        $this->ProcessDefinitions($c_t_code_file);
        $this->target_specific_functions->FinishProcessingCTCodeFile();
    }

    public function ProcessExdefs(?\S84\CTCode\dbnf\ctcode\CTCodeFile $c_t_code_file): void
    {
        $exdefs = $c_t_code_file->GetDeclarations();
        $exdefs_index = 0;
        while ($exdefs_index<Size($exdefs))
        {
            $exdef = Element($exdefs,$exdefs_index);
            $exdef_name = $exdef->GetExdef();
            $this->target_specific_functions->ProcessExdef($exdef_name->UnParse());
            $exdefs_index = $exdefs_index+1;
        }
    }

    public function ProcessUnmanagedTypes(?\S84\CTCode\dbnf\ctcode\CTCodeFile $c_t_code_file): void
    {
        $unmanaged_types = $c_t_code_file->GetUnmanagedTypes();
        $unmanaged_types_index = 0;
        while ($unmanaged_types_index<Size($unmanaged_types))
        {
            $unmanaged_type = Element($unmanaged_types,$unmanaged_types_index);
            $this->target_specific_functions->ProcessUnmanagedType($this->GetQualifiedTypeNameInternal($unmanaged_type->GetUnmanagedType()));
            $unmanaged_types_index = $unmanaged_types_index+1;
        }
    }

    public function ProcessDefinitions(?\S84\CTCode\dbnf\ctcode\CTCodeFile $c_t_code_file): void
    {
        $definitions = $c_t_code_file->GetDefinitions();
        $definitions_index = 0;
        while ($definitions_index<Size($definitions))
        {
            $definition = null;
            $definition = Element($definitions,$definitions_index);
            if ($definition->GetInterfaceDef())
            {
                $this->ProcessInterfaceDefinition($definition->GetInterfaceDef());
            }
            if ($definition->GetClassDef())
            {
                $this->ProcessClassDefinition($definition->GetClassDef());
            }
            $definitions_index = $definitions_index+1;
        }
    }

    public function GetParameters(?\S84\CTCode\dbnf\ctcode\ParameterListDef $parameter_list_def): ?array
    {
        $result = array();
        while ($parameter_list_def)
        {
            $parameter = new ParameterDeclaration();
            $parameter->SetType($this->ReservedPrefixGetType($parameter_list_def->ReservedPrefixGetType()));
            $parameter->SetName($this->target_specific_functions->GetVariableName($this->NameToString($parameter_list_def->GetName())));
            Append($result,$parameter);
            $parameter_list_def = $parameter_list_def->GetParameterTail();
        }
        return $result;
    }

    public function ProcessInterfaceDefinition(?\S84\CTCode\dbnf\ctcode\InterfaceDef $interface_definition): void
    {
        $interface_name = $this->target_specific_functions->GetTypeName($this->NameToString($interface_definition->GetName()));
        $this->target_specific_functions->BeginProcessingInterface($interface_name);
        $declarations = $interface_definition->GetDeclarations();
        $declarations_index = 0;
        while ($declarations_index<Size($declarations))
        {
            $declaration = Element($declarations,$declarations_index);
            $return_type = $this->ReservedPrefixGetType($declaration->ReservedPrefixGetType());
            $function_name = $this->target_specific_functions->GetCallName($this->NameToString($declaration->GetName()));
            $parameters = $this->GetParameters($declaration->GetParameters());
            $this->target_specific_functions->ProcessInterfaceFunctionDeclaration($return_type,$function_name,$parameters);
            $declarations_index = $declarations_index+1;
        }
        $this->target_specific_functions->FinishProcessingInterface($interface_name);
    }

    public function ProcessClassDefinition(?\S84\CTCode\dbnf\ctcode\ClassDef $class_definition): void
    {
        $class_name = $this->target_specific_functions->GetTypeName($this->NameToString($class_definition->GetName()));
        $implementing = '';
        $implementation_spec = $class_definition->GetImplementing();
        if ($implementation_spec)
        {
            $implementing = $this->GetQualifiedTypeNameInternal($implementation_spec->GetInterface());
        }
        $this->target_specific_functions->BeginProcessingClass($class_name,$implementing);
        $definitions = $class_definition->GetDefinitions();
        $definitions_index = 0;
        while ($definitions_index<Size($definitions))
        {
            $definition = Element($definitions,$definitions_index);
            if ($definition->GetFunctionBody())
            {
                $return_type = $this->ReservedPrefixGetType($definition->ReservedPrefixGetType());
                $function_name = $this->target_specific_functions->GetCallName($this->NameToString($definition->GetName()));
                $parameters = $this->GetParameters($definition->GetParameters());
                $this->target_specific_functions->BeginProcessingClassFunctionDefinition($return_type,$function_name,$parameters);
                $this->ProcessCodeBlockInternal($this->target_specific_functions->GetBaseIndentation(),$definition->GetFunctionBody());
                $this->target_specific_functions->FinishProcessingClassFunctionDefinition($return_type,$function_name,$parameters);
            }
            else
            {
                $member_type = $this->ReservedPrefixGetType($definition->ReservedPrefixGetType());
                $member_name = $this->target_specific_functions->GetVariableName($this->NameToString($definition->GetName()));
                $this->target_specific_functions->ProcessClassMemberDeclaration($member_type,$member_name);
            }
            $definitions_index = $definitions_index+1;
        }
        $this->target_specific_functions->FinishProcessingClass($class_name,$implementing);
    }

    public function ProcessInstructionInternal(?int $indent, ?\S84\CTCode\dbnf\ctcode\Instruction $instruction): void
    {
        if ($instruction->GetCodeBlock())
        {
            $this->ProcessCodeBlockInternal($indent,$instruction->GetCodeBlock());
        }
        if ($instruction->GetRtn())
        {
            $this->ProcessRtnInternal($indent,$instruction->GetRtn());
        }
        if ($instruction->GetDeclaration())
        {
            $this->ProcessDeclarationInternal($indent,$instruction->GetDeclaration());
        }
        if ($instruction->GetAssignment())
        {
            $this->ProcessAssignmentInternal($indent,$instruction->GetAssignment());
        }
        if ($instruction->GetCall())
        {
            $this->ProcessCallInternal($indent,$instruction->GetCall());
        }
        if ($instruction->GetConditional())
        {
            $this->ProcessConditionalInternal($indent,$instruction->GetConditional());
        }
        if ($instruction->GetLoop())
        {
            $this->ProcessLoopInternal($indent,$instruction->GetLoop());
        }
    }

    public function ProcessCodeBlockInternal(?int $indent, ?\S84\CTCode\dbnf\ctcode\CodeBlock $code_block): void
    {
        $this->target_specific_functions->BeginProcessCodeBlock($indent);
        $instructions = $code_block->GetInstructions();
        $instructions_index = 0;
        while ($instructions_index<Size($instructions))
        {
            $this->ProcessInstructionInternal($indent+1,Element($instructions,$instructions_index));
            $instructions_index = $instructions_index+1;
        }
        $this->target_specific_functions->FinishProcessCodeBlock($indent);
    }

    public function ProcessConditionalInternal(?int $indent, ?\S84\CTCode\dbnf\ctcode\Conditional $conditional): void
    {
        $r_value = $this->GetRValueInternal($conditional->GetRValue());
        $this->target_specific_functions->BeginProcessConditional($indent,$r_value);
        $this->ProcessCodeBlockInternal($indent,$conditional->GetCodeBlock());
        if ($conditional->GetElseTail())
        {
            $else_tail = $conditional->GetElseTail();
            $this->target_specific_functions->ProcessElse($indent);
            $this->ProcessCodeBlockInternal($indent,$else_tail->GetCodeBlock());
        }
        $this->target_specific_functions->FinishProcessConditional($indent,$r_value);
    }

    public function ProcessLoopInternal(?int $indent, ?\S84\CTCode\dbnf\ctcode\Loop $loop): void
    {
        $r_value = $this->GetRValueInternal($loop->GetRValue());
        $this->target_specific_functions->BeginProcessLoop($indent,$r_value);
        $this->ProcessCodeBlockInternal($indent,$loop->GetCodeBlock());
        $this->target_specific_functions->FinishProcessLoop($indent,$r_value);
    }

    public function ProcessRtnInternal(?int $indent, ?\S84\CTCode\dbnf\ctcode\ReservedPrefixReturn $rtn): void
    {
        $r_value = $this->GetRValueInternal($rtn->GetRValue());
        $this->target_specific_functions->ProcessRtn($indent,$r_value);
    }

    public function ProcessDeclarationInternal(?int $indent, ?\S84\CTCode\dbnf\ctcode\Declaration $declaration): void
    {
        $type = $this->ReservedPrefixGetType($declaration->ReservedPrefixGetType());
        $l_value = $this->target_specific_functions->GetVariableName($this->NameToString($declaration->GetName()));
        $r_value = '';
        $declaration_assignment = $declaration->GetAssignment();
        if ($declaration_assignment)
        {
            $r_value = $this->GetRValueInternal($declaration_assignment->GetRValue());
        }
        $this->target_specific_functions->ProcessDeclaration($indent,$type,$l_value,$r_value);
    }

    public function ProcessAssignmentInternal(?int $indent, ?\S84\CTCode\dbnf\ctcode\Assignment $assignment): void
    {
        $this->target_specific_functions->ProcessAssignment($indent,$this->GetVariableChainInternal($assignment->GetLValue()),$this->GetRValueInternal($assignment->GetRValue()));
    }

    public function ProcessCallInternal(?int $indent, ?\S84\CTCode\dbnf\ctcode\Call $call): void
    {
        $this->target_specific_functions->ProcessCall($indent,$this->ConvertCallInternal($call));
    }

    public function ConvertCallInternal(?\S84\CTCode\dbnf\ctcode\Call $call): ?string
    {
        $name_chain = array();
        $parameters = array();
        if ($call->GetVariable())
        {
            Append($name_chain,$this->target_specific_functions->GetVariableName($this->NameToString($call->GetVariable())));
        }
        if ($call->GetFunction())
        {
            Append($name_chain,$this->target_specific_functions->GetCallName($this->NameToString($call->GetFunction())));
        }
        if ($call->GetFunctionChain())
        {
            $function_chain = $call->GetFunctionChain();
            $name_tail = $function_chain->GetTail();
            if ($function_chain->GetTail())
            {
                Append($name_chain,$this->target_specific_functions->GetVariableName($this->NameToString($function_chain->GetName())));
            }
            else
            {
                Append($name_chain,$this->target_specific_functions->GetCallName($this->NameToString($function_chain->GetName())));
            }
            while ($name_tail)
            {
                if ($name_tail->GetTail())
                {
                    Append($name_chain,$this->target_specific_functions->GetVariableName($this->NameToString($name_tail->GetName())));
                }
                else
                {
                    Append($name_chain,$this->target_specific_functions->GetCallName($this->NameToString($name_tail->GetName())));
                }
                $name_tail = $name_tail->GetTail();
            }
        }
        $parameter_list = $call->GetParameters();
        while ($parameter_list)
        {
            Append($parameters,$this->GetRValueInternal($parameter_list->GetRValue()));
            $parameter_list = $parameter_list->GetParameterTail();
        }
        return $this->target_specific_functions->ConvertCall($name_chain,$parameters);
    }

    public function GetSingletonType(?\S84\CTCode\dbnf\ctcode\SingletonType $singleton_type): ?string
    {
        if ($singleton_type->GetPrimativeType())
        {
            return $this->target_specific_functions->GetPrimativeType($singleton_type->UnParse());
        }
        if ($singleton_type->GetDefinedType())
        {
            $defined_type = $singleton_type->GetDefinedType();
            return $this->target_specific_functions->GetDefinedType($this->GetQualifiedTypeNameInternal($defined_type->GetName()));
        }
        return '';
    }

    public function GetRValueSingleBasisInternal(?\S84\CTCode\dbnf\ctcode\RValueSingle $r_value_single): ?string
    {
        $call = $r_value_single->GetCall();
        if ($call)
        {
            return $this->ConvertCallInternal($call);
        }
        $allocate = $r_value_single->GetAllocate();
        if ($allocate)
        {
            return $this->target_specific_functions->ConvertAllocate($this->GetQualifiedTypeNameInternal($allocate->GetManagedType()));
        }
        $byte_literal = $r_value_single->GetByteLiteral();
        if ($byte_literal)
        {
            $high = $byte_literal->GetHigh();
            $low = $byte_literal->GetLow();
            return $this->target_specific_functions->ConvertByte($high->UnParse(),$low->UnParse());
        }
        $decimal_literal = $r_value_single->GetDecimalLiteral();
        if ($decimal_literal)
        {
            return $this->target_specific_functions->ConvertDecimal($decimal_literal->UnParse());
        }
        $integer_literal = $r_value_single->GetIntegerLiteral();
        if ($integer_literal)
        {
            return $this->target_specific_functions->ConvertNumber($integer_literal->UnParse());
        }
        $boolean_literal = $r_value_single->GetBooleanLiteral();
        if ($boolean_literal)
        {
            return $this->target_specific_functions->ConvertBoolean($boolean_literal->UnParse());
        }
        $variable = $r_value_single->GetVariable();
        if ($variable)
        {
            return $this->target_specific_functions->ConvertVariable($this->GetVariableChainInternal($variable));
        }
        $string_literal = $r_value_single->GetStringLiteral();
        if ($string_literal)
        {
            return $this->target_specific_functions->ConvertString($string_literal->UnParse());
        }
        return '';
    }

    public function GetRValueSingleInternal(?\S84\CTCode\dbnf\ctcode\RValueSingle $r_value_single): ?string
    {
        $unary_operator = $r_value_single->GetUnaryOperator();
        if ($unary_operator)
        {
            return $this->target_specific_functions->UnaryOperator($unary_operator->UnParse(),$this->GetRValueSingleBasisInternal($r_value_single));
        }
        return $this->GetRValueSingleBasisInternal($r_value_single);
    }

    public function PopulateOperatorPrecedent(): void
    {
        $precedent__0_operators = array();
        Append($precedent__0_operators,'+');
        Append($precedent__0_operators,'-');
        Append($this->operator_precedent,$precedent__0_operators);
        $precedent__1_operators = array();
        Append($precedent__1_operators,'<=');
        Append($precedent__1_operators,'>=');
        Append($precedent__1_operators,'==');
        Append($precedent__1_operators,'!=');
        Append($precedent__1_operators,'<');
        Append($precedent__1_operators,'>');
        Append($this->operator_precedent,$precedent__1_operators);
        $precedent__2_operators = array();
        Append($precedent__2_operators,'&&');
        Append($this->operator_precedent,$precedent__2_operators);
        $precedent__3_operators = array();
        Append($precedent__3_operators,'||');
        Append($this->operator_precedent,$precedent__3_operators);
        $precedent__4_operators = array();
        Append($precedent__4_operators,'');
        Append($this->operator_precedent,$precedent__4_operators);
    }

    public function OverPrecedent(?string $op, ?int $precedent): ?bool
    {
        $precedent = $precedent+1;
        while ($precedent<Size($this->operator_precedent))
        {
            $precedent_operators = Element($this->operator_precedent,$precedent);
            $index = 0;
            while ($index<Size($precedent_operators))
            {
                $checking_op = Element($precedent_operators,$index);
                if ($checking_op==$op)
                {
                    return true;
                }
                $index = $index+1;
            }
            $precedent = $precedent+1;
        }
        return false;
    }

    public function BinaryOperatorPrecedentMerge(?array $values, ?array $operators, ?IntegerReference $index, ?int $precedent): ?string
    {
        if ($precedent==-1)
        {
            return Element($values,$index->GetValue());
        }
        $r_value_l = $this->BinaryOperatorPrecedentMerge($values,$operators,$index,$precedent-1);
        while ($index->GetValue()<Size($operators))
        {
            $op = Element($operators,$index->GetValue());
            if ($this->OverPrecedent($op,$precedent))
            {
                return $r_value_l;
            }
            $index->SetValue($index->GetValue()+1);
            $r_value_r = $this->BinaryOperatorPrecedentMerge($values,$operators,$index,$precedent-1);
            $r_value_l = $this->target_specific_functions->BinaryOperator($op,$r_value_l,$r_value_r);
        }
        return $r_value_l;
    }

    public function GetRValueInternal(?\S84\CTCode\dbnf\ctcode\RValue $r_value): ?string
    {
        $values = array();
        $operators = array();
        $index = new IntegerReference();
        $index->SetValue(0);
        Append($values,$this->GetRValueSingleInternal($r_value->GetValue()));
        $r_value_tail = $r_value->GetTail();
        while ($r_value_tail)
        {
            $binary_operator = $r_value_tail->GetBinaryOperator();
            Append($values,$this->GetRValueSingleInternal($r_value_tail->GetValue()));
            Append($operators,$binary_operator->UnParse());
            $r_value_tail = $r_value_tail->GetTail();
        }
        return $this->BinaryOperatorPrecedentMerge($values,$operators,$index,Size($this->operator_precedent));
    }

    public function GetQualifiedTypeNameInternal(?\S84\CTCode\dbnf\ctcode\QualfiedName $qualified_name): ?string
    {
        $name_parts = array();
        Append($name_parts,$this->NameToString($qualified_name->GetName()));
        $tail = $qualified_name->GetTail();
        while ($tail)
        {
            Append($name_parts,$this->NameToString($tail->GetName()));
            $tail = $tail->GetTail();
        }
        return $this->target_specific_functions->GetQualifiedTypeName($name_parts);
    }

    public function GetVariableChainInternal(?\S84\CTCode\dbnf\ctcode\QualfiedName $qualified_name): ?string
    {
        $name_parts = array();
        Append($name_parts,$this->NameToString($qualified_name->GetName()));
        $tail = $qualified_name->GetTail();
        while ($tail)
        {
            Append($name_parts,$this->NameToString($tail->GetName()));
            $tail = $tail->GetTail();
        }
        return $this->target_specific_functions->GetVariableChain($name_parts);
    }

    public function ReservedPrefixGetType(?\S84\CTCode\dbnf\ctcode\ValueType $type): ?string
    {
        if ($type->GetDimensionalType())
        {
            $dimensional_type = $type->GetDimensionalType();
            $singleton_type = $dimensional_type->GetSingletonType();
            return $this->target_specific_functions->GetDimensionalType($this->GetSingletonType($singleton_type),Size($dimensional_type->GetDimensionalNote()));
        }
        if ($type->GetMapType())
        {
            $map_type = $type->GetMapType();
            $singleton_type = $map_type->GetSingletonType();
            return $this->target_specific_functions->GetMapType($this->GetSingletonType($singleton_type));
        }
        if ($type->GetSingletonType())
        {
            $singleton_type = $type->GetSingletonType();
            return $this->GetSingletonType($singleton_type);
        }
        return '';
    }

    public function NameToString(?\S84\CTCode\dbnf\ctcode\Name $name): ?string
    {
        if ($name)
        {
            return $name->UnParse();
        }
        else
        {
            return '';
        }
    }

    private $system;
    private $c_t_code_file;
    private $base_name;
    private $operator_precedent;
    private $logger;
    private $target_specific_functions;
}

?>
