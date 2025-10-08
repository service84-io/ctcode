<?php
namespace S84\CTCode\dbnf\ctcode;

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

class StringParser {
    public function __construct() {
    }

    public function ParseSingleSave(?LengthString $index, ?string $value, ?StringResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $index_data = $index->GetData();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new ReservedPrefixString();
        $value_length = Length($value);
        if ($value_length>$index->GetLength())
        {
            $result->SetResult(false);
            return false;
        }
        $offset_index = 0;
        while ($offset_index<$value_length)
        {
            if ($index_data->GetAt($index->GetStart()+$offset_index)!=At($value,$offset_index))
            {
                $result->SetResult(false);
                return false;
            }
            $offset_index = $offset_index+1;
        }
        $index->SetStart($index->GetStart()+$value_length);
        $index->SetLength($index->GetLength()-$value_length);
        $consumed_string->SetLength($index->GetStart()-$index_start);
        $instance->SetLengthString($consumed_string);
        $result->SetValue($instance);
        $result->SetResult(true);
        return true;
    }

    public function ParseSingle(?LengthString $index, ?string $value): ?bool
    {
        $result = new StringResult();
        return $this->ParseSingleSave($index,$value,$result);
    }

}

class StringResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?ReservedPrefixString $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?ReservedPrefixString
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class StringListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class ReservedPrefixString {
    public function __construct() {
        $this->length_string = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    private $length_string;
}

class CharacterParser {
    public function __construct() {
    }

    public function ParseSingle(?LengthString $index, ?int $value): ?bool
    {
        if (0==$index->GetLength())
        {
            return false;
        }
        $index_data = $index->GetData();
        $current_character = $index_data->GetIntAt($index->GetStart());
        if ($current_character==$value)
        {
            $index->SetStart($index->GetStart()+1);
            $index->SetLength($index->GetLength()-1);
            return true;
        }
        return false;
    }

}

class CharacterResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?Character $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?Character
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class CharacterListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class Character {
    public function __construct() {
        $this->length_string = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    private $length_string;
}

class CharacterRangeParser {
    public function __construct() {
    }

    public function ParseSingle(?LengthString $index, ?int $low_value, ?int $high_value): ?bool
    {
        if (0==$index->GetLength())
        {
            return false;
        }
        $index_data = $index->GetData();
        $current_character = $index_data->GetIntAt($index->GetStart());
        if ($low_value<=$current_character&&$current_character<=$high_value)
        {
            $index->SetStart($index->GetStart()+1);
            $index->SetLength($index->GetLength()-1);
            return true;
        }
        return false;
    }

}

class CharacterRangeResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?CharacterRange $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?CharacterRange
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class CharacterRangeListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class CharacterRange {
    public function __construct() {
        $this->length_string = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    private $length_string;
}

class ParserNetwork {
    public function __construct() {
        $this->c_t_code_file_parser_field = null;
        $this->external_definition_parser_field = null;
        $this->unmanaged_type_parser_field = null;
        $this->definition_parser_field = null;
        $this->interface_def_parser_field = null;
        $this->class_def_parser_field = null;
        $this->implementation_spec_parser_field = null;
        $this->content_declaration_parser_field = null;
        $this->content_definition_parser_field = null;
        $this->primative_type_parser_field = null;
        $this->defined_type_parser_field = null;
        $this->singleton_type_parser_field = null;
        $this->dimensional_note_parser_field = null;
        $this->dimensional_type_parser_field = null;
        $this->map_note_parser_field = null;
        $this->map_type_parser_field = null;
        $this->value_type_parser_field = null;
        $this->parameter_list_def_parser_field = null;
        $this->parameter_list_parser_field = null;
        $this->code_block_parser_field = null;
        $this->declaration_assign_parser_field = null;
        $this->declaration_parser_field = null;
        $this->assignment_parser_field = null;
        $this->return_parser_field = null;
        $this->else_tail_parser_field = null;
        $this->conditional_parser_field = null;
        $this->loop_parser_field = null;
        $this->call_parser_field = null;
        $this->allocate_parser_field = null;
        $this->instruction_parser_field = null;
        $this->r_value_single_parser_field = null;
        $this->r_value_tail_parser_field = null;
        $this->r_value_parser_field = null;
        $this->binary_operator_parser_field = null;
        $this->unary_operator_parser_field = null;
        $this->comment_parser_field = null;
        $this->non_star_character_parser_field = null;
        $this->non_slash_character_parser_field = null;
        $this->comment_content_parser_field = null;
        $this->qualfied_name_parser_field = null;
        $this->name_tail_parser_field = null;
        $this->name_parser_field = null;
        $this->name_character_parser_field = null;
        $this->boolean_parser_field = null;
        $this->byte_parser_field = null;
        $this->byte_digit_parser_field = null;
        $this->negative_parser_field = null;
        $this->decimal_parser_field = null;
        $this->number_parser_field = null;
        $this->digit_parser_field = null;
        $this->literal_parser_field = null;
        $this->literal_character_parser_field = null;
        $this->whitespace_parser_field = null;
        $this->string_parser_field = null;
        $this->character_parser_field = null;
        $this->character_range_parser_field = null;
    }

    public function GetCTCodeFileParser(): ?CTCodeFileParser
    {
        return $this->c_t_code_file_parser_field;
    }

    public function GetExternalDefinitionParser(): ?ExternalDefinitionParser
    {
        return $this->external_definition_parser_field;
    }

    public function GetUnmanagedTypeParser(): ?UnmanagedTypeParser
    {
        return $this->unmanaged_type_parser_field;
    }

    public function GetDefinitionParser(): ?DefinitionParser
    {
        return $this->definition_parser_field;
    }

    public function GetInterfaceDefParser(): ?InterfaceDefParser
    {
        return $this->interface_def_parser_field;
    }

    public function GetClassDefParser(): ?ClassDefParser
    {
        return $this->class_def_parser_field;
    }

    public function GetImplementationSpecParser(): ?ImplementationSpecParser
    {
        return $this->implementation_spec_parser_field;
    }

    public function GetContentDeclarationParser(): ?ContentDeclarationParser
    {
        return $this->content_declaration_parser_field;
    }

    public function GetContentDefinitionParser(): ?ContentDefinitionParser
    {
        return $this->content_definition_parser_field;
    }

    public function GetPrimativeTypeParser(): ?PrimativeTypeParser
    {
        return $this->primative_type_parser_field;
    }

    public function GetDefinedTypeParser(): ?DefinedTypeParser
    {
        return $this->defined_type_parser_field;
    }

    public function GetSingletonTypeParser(): ?SingletonTypeParser
    {
        return $this->singleton_type_parser_field;
    }

    public function GetDimensionalNoteParser(): ?DimensionalNoteParser
    {
        return $this->dimensional_note_parser_field;
    }

    public function GetDimensionalTypeParser(): ?DimensionalTypeParser
    {
        return $this->dimensional_type_parser_field;
    }

    public function GetMapNoteParser(): ?MapNoteParser
    {
        return $this->map_note_parser_field;
    }

    public function GetMapTypeParser(): ?MapTypeParser
    {
        return $this->map_type_parser_field;
    }

    public function GetValueTypeParser(): ?ValueTypeParser
    {
        return $this->value_type_parser_field;
    }

    public function GetParameterListDefParser(): ?ParameterListDefParser
    {
        return $this->parameter_list_def_parser_field;
    }

    public function GetParameterListParser(): ?ParameterListParser
    {
        return $this->parameter_list_parser_field;
    }

    public function GetCodeBlockParser(): ?CodeBlockParser
    {
        return $this->code_block_parser_field;
    }

    public function GetDeclarationAssignParser(): ?DeclarationAssignParser
    {
        return $this->declaration_assign_parser_field;
    }

    public function GetDeclarationParser(): ?DeclarationParser
    {
        return $this->declaration_parser_field;
    }

    public function GetAssignmentParser(): ?AssignmentParser
    {
        return $this->assignment_parser_field;
    }

    public function GetReturnParser(): ?ReturnParser
    {
        return $this->return_parser_field;
    }

    public function GetElseTailParser(): ?ElseTailParser
    {
        return $this->else_tail_parser_field;
    }

    public function GetConditionalParser(): ?ConditionalParser
    {
        return $this->conditional_parser_field;
    }

    public function GetLoopParser(): ?LoopParser
    {
        return $this->loop_parser_field;
    }

    public function GetCallParser(): ?CallParser
    {
        return $this->call_parser_field;
    }

    public function GetAllocateParser(): ?AllocateParser
    {
        return $this->allocate_parser_field;
    }

    public function GetInstructionParser(): ?InstructionParser
    {
        return $this->instruction_parser_field;
    }

    public function GetRValueSingleParser(): ?RValueSingleParser
    {
        return $this->r_value_single_parser_field;
    }

    public function GetRValueTailParser(): ?RValueTailParser
    {
        return $this->r_value_tail_parser_field;
    }

    public function GetRValueParser(): ?RValueParser
    {
        return $this->r_value_parser_field;
    }

    public function GetBinaryOperatorParser(): ?BinaryOperatorParser
    {
        return $this->binary_operator_parser_field;
    }

    public function GetUnaryOperatorParser(): ?UnaryOperatorParser
    {
        return $this->unary_operator_parser_field;
    }

    public function GetCommentParser(): ?CommentParser
    {
        return $this->comment_parser_field;
    }

    public function GetNonStarCharacterParser(): ?NonStarCharacterParser
    {
        return $this->non_star_character_parser_field;
    }

    public function GetNonSlashCharacterParser(): ?NonSlashCharacterParser
    {
        return $this->non_slash_character_parser_field;
    }

    public function GetCommentContentParser(): ?CommentContentParser
    {
        return $this->comment_content_parser_field;
    }

    public function GetQualfiedNameParser(): ?QualfiedNameParser
    {
        return $this->qualfied_name_parser_field;
    }

    public function GetNameTailParser(): ?NameTailParser
    {
        return $this->name_tail_parser_field;
    }

    public function GetNameParser(): ?NameParser
    {
        return $this->name_parser_field;
    }

    public function GetNameCharacterParser(): ?NameCharacterParser
    {
        return $this->name_character_parser_field;
    }

    public function GetBooleanParser(): ?BooleanParser
    {
        return $this->boolean_parser_field;
    }

    public function GetByteParser(): ?ByteParser
    {
        return $this->byte_parser_field;
    }

    public function GetByteDigitParser(): ?ByteDigitParser
    {
        return $this->byte_digit_parser_field;
    }

    public function GetNegativeParser(): ?NegativeParser
    {
        return $this->negative_parser_field;
    }

    public function GetDecimalParser(): ?DecimalParser
    {
        return $this->decimal_parser_field;
    }

    public function GetNumberParser(): ?NumberParser
    {
        return $this->number_parser_field;
    }

    public function GetDigitParser(): ?DigitParser
    {
        return $this->digit_parser_field;
    }

    public function GetLiteralParser(): ?LiteralParser
    {
        return $this->literal_parser_field;
    }

    public function GetLiteralCharacterParser(): ?LiteralCharacterParser
    {
        return $this->literal_character_parser_field;
    }

    public function GetWhitespaceParser(): ?WhitespaceParser
    {
        return $this->whitespace_parser_field;
    }

    public function GetStringParser(): ?StringParser
    {
        return $this->string_parser_field;
    }

    public function GetCharacterParser(): ?CharacterParser
    {
        return $this->character_parser_field;
    }

    public function GetCharacterRangeParser(): ?CharacterRangeParser
    {
        return $this->character_range_parser_field;
    }

    public function Initialize(): void
    {
        $this->c_t_code_file_parser_field = new CTCodeFileParser();
        $this->c_t_code_file_parser_field->SetParserNetwork($this);
        $this->external_definition_parser_field = new ExternalDefinitionParser();
        $this->external_definition_parser_field->SetParserNetwork($this);
        $this->unmanaged_type_parser_field = new UnmanagedTypeParser();
        $this->unmanaged_type_parser_field->SetParserNetwork($this);
        $this->definition_parser_field = new DefinitionParser();
        $this->definition_parser_field->SetParserNetwork($this);
        $this->interface_def_parser_field = new InterfaceDefParser();
        $this->interface_def_parser_field->SetParserNetwork($this);
        $this->class_def_parser_field = new ClassDefParser();
        $this->class_def_parser_field->SetParserNetwork($this);
        $this->implementation_spec_parser_field = new ImplementationSpecParser();
        $this->implementation_spec_parser_field->SetParserNetwork($this);
        $this->content_declaration_parser_field = new ContentDeclarationParser();
        $this->content_declaration_parser_field->SetParserNetwork($this);
        $this->content_definition_parser_field = new ContentDefinitionParser();
        $this->content_definition_parser_field->SetParserNetwork($this);
        $this->primative_type_parser_field = new PrimativeTypeParser();
        $this->primative_type_parser_field->SetParserNetwork($this);
        $this->defined_type_parser_field = new DefinedTypeParser();
        $this->defined_type_parser_field->SetParserNetwork($this);
        $this->singleton_type_parser_field = new SingletonTypeParser();
        $this->singleton_type_parser_field->SetParserNetwork($this);
        $this->dimensional_note_parser_field = new DimensionalNoteParser();
        $this->dimensional_note_parser_field->SetParserNetwork($this);
        $this->dimensional_type_parser_field = new DimensionalTypeParser();
        $this->dimensional_type_parser_field->SetParserNetwork($this);
        $this->map_note_parser_field = new MapNoteParser();
        $this->map_note_parser_field->SetParserNetwork($this);
        $this->map_type_parser_field = new MapTypeParser();
        $this->map_type_parser_field->SetParserNetwork($this);
        $this->value_type_parser_field = new ValueTypeParser();
        $this->value_type_parser_field->SetParserNetwork($this);
        $this->parameter_list_def_parser_field = new ParameterListDefParser();
        $this->parameter_list_def_parser_field->SetParserNetwork($this);
        $this->parameter_list_parser_field = new ParameterListParser();
        $this->parameter_list_parser_field->SetParserNetwork($this);
        $this->code_block_parser_field = new CodeBlockParser();
        $this->code_block_parser_field->SetParserNetwork($this);
        $this->declaration_assign_parser_field = new DeclarationAssignParser();
        $this->declaration_assign_parser_field->SetParserNetwork($this);
        $this->declaration_parser_field = new DeclarationParser();
        $this->declaration_parser_field->SetParserNetwork($this);
        $this->assignment_parser_field = new AssignmentParser();
        $this->assignment_parser_field->SetParserNetwork($this);
        $this->return_parser_field = new ReturnParser();
        $this->return_parser_field->SetParserNetwork($this);
        $this->else_tail_parser_field = new ElseTailParser();
        $this->else_tail_parser_field->SetParserNetwork($this);
        $this->conditional_parser_field = new ConditionalParser();
        $this->conditional_parser_field->SetParserNetwork($this);
        $this->loop_parser_field = new LoopParser();
        $this->loop_parser_field->SetParserNetwork($this);
        $this->call_parser_field = new CallParser();
        $this->call_parser_field->SetParserNetwork($this);
        $this->allocate_parser_field = new AllocateParser();
        $this->allocate_parser_field->SetParserNetwork($this);
        $this->instruction_parser_field = new InstructionParser();
        $this->instruction_parser_field->SetParserNetwork($this);
        $this->r_value_single_parser_field = new RValueSingleParser();
        $this->r_value_single_parser_field->SetParserNetwork($this);
        $this->r_value_tail_parser_field = new RValueTailParser();
        $this->r_value_tail_parser_field->SetParserNetwork($this);
        $this->r_value_parser_field = new RValueParser();
        $this->r_value_parser_field->SetParserNetwork($this);
        $this->binary_operator_parser_field = new BinaryOperatorParser();
        $this->binary_operator_parser_field->SetParserNetwork($this);
        $this->unary_operator_parser_field = new UnaryOperatorParser();
        $this->unary_operator_parser_field->SetParserNetwork($this);
        $this->comment_parser_field = new CommentParser();
        $this->comment_parser_field->SetParserNetwork($this);
        $this->non_star_character_parser_field = new NonStarCharacterParser();
        $this->non_star_character_parser_field->SetParserNetwork($this);
        $this->non_slash_character_parser_field = new NonSlashCharacterParser();
        $this->non_slash_character_parser_field->SetParserNetwork($this);
        $this->comment_content_parser_field = new CommentContentParser();
        $this->comment_content_parser_field->SetParserNetwork($this);
        $this->qualfied_name_parser_field = new QualfiedNameParser();
        $this->qualfied_name_parser_field->SetParserNetwork($this);
        $this->name_tail_parser_field = new NameTailParser();
        $this->name_tail_parser_field->SetParserNetwork($this);
        $this->name_parser_field = new NameParser();
        $this->name_parser_field->SetParserNetwork($this);
        $this->name_character_parser_field = new NameCharacterParser();
        $this->name_character_parser_field->SetParserNetwork($this);
        $this->boolean_parser_field = new BooleanParser();
        $this->boolean_parser_field->SetParserNetwork($this);
        $this->byte_parser_field = new ByteParser();
        $this->byte_parser_field->SetParserNetwork($this);
        $this->byte_digit_parser_field = new ByteDigitParser();
        $this->byte_digit_parser_field->SetParserNetwork($this);
        $this->negative_parser_field = new NegativeParser();
        $this->negative_parser_field->SetParserNetwork($this);
        $this->decimal_parser_field = new DecimalParser();
        $this->decimal_parser_field->SetParserNetwork($this);
        $this->number_parser_field = new NumberParser();
        $this->number_parser_field->SetParserNetwork($this);
        $this->digit_parser_field = new DigitParser();
        $this->digit_parser_field->SetParserNetwork($this);
        $this->literal_parser_field = new LiteralParser();
        $this->literal_parser_field->SetParserNetwork($this);
        $this->literal_character_parser_field = new LiteralCharacterParser();
        $this->literal_character_parser_field->SetParserNetwork($this);
        $this->whitespace_parser_field = new WhitespaceParser();
        $this->whitespace_parser_field->SetParserNetwork($this);
        $this->string_parser_field = new StringParser();
        $this->character_parser_field = new CharacterParser();
        $this->character_range_parser_field = new CharacterRangeParser();
    }

    private $c_t_code_file_parser_field;
    private $external_definition_parser_field;
    private $unmanaged_type_parser_field;
    private $definition_parser_field;
    private $interface_def_parser_field;
    private $class_def_parser_field;
    private $implementation_spec_parser_field;
    private $content_declaration_parser_field;
    private $content_definition_parser_field;
    private $primative_type_parser_field;
    private $defined_type_parser_field;
    private $singleton_type_parser_field;
    private $dimensional_note_parser_field;
    private $dimensional_type_parser_field;
    private $map_note_parser_field;
    private $map_type_parser_field;
    private $value_type_parser_field;
    private $parameter_list_def_parser_field;
    private $parameter_list_parser_field;
    private $code_block_parser_field;
    private $declaration_assign_parser_field;
    private $declaration_parser_field;
    private $assignment_parser_field;
    private $return_parser_field;
    private $else_tail_parser_field;
    private $conditional_parser_field;
    private $loop_parser_field;
    private $call_parser_field;
    private $allocate_parser_field;
    private $instruction_parser_field;
    private $r_value_single_parser_field;
    private $r_value_tail_parser_field;
    private $r_value_parser_field;
    private $binary_operator_parser_field;
    private $unary_operator_parser_field;
    private $comment_parser_field;
    private $non_star_character_parser_field;
    private $non_slash_character_parser_field;
    private $comment_content_parser_field;
    private $qualfied_name_parser_field;
    private $name_tail_parser_field;
    private $name_parser_field;
    private $name_character_parser_field;
    private $boolean_parser_field;
    private $byte_parser_field;
    private $byte_digit_parser_field;
    private $negative_parser_field;
    private $decimal_parser_field;
    private $number_parser_field;
    private $digit_parser_field;
    private $literal_parser_field;
    private $literal_character_parser_field;
    private $whitespace_parser_field;
    private $string_parser_field;
    private $character_parser_field;
    private $character_range_parser_field;
}

class DBNFOmniType {
    public function __construct() {
        $this->c_t_code_file_field = null;
        $this->external_definition_field = null;
        $this->unmanaged_type_field = null;
        $this->definition_field = null;
        $this->interface_def_field = null;
        $this->class_def_field = null;
        $this->implementation_spec_field = null;
        $this->content_declaration_field = null;
        $this->content_definition_field = null;
        $this->primative_type_field = null;
        $this->defined_type_field = null;
        $this->singleton_type_field = null;
        $this->dimensional_note_field = null;
        $this->dimensional_type_field = null;
        $this->map_note_field = null;
        $this->map_type_field = null;
        $this->value_type_field = null;
        $this->parameter_list_def_field = null;
        $this->parameter_list_field = null;
        $this->code_block_field = null;
        $this->declaration_assign_field = null;
        $this->declaration_field = null;
        $this->assignment_field = null;
        $this->return_field = null;
        $this->else_tail_field = null;
        $this->conditional_field = null;
        $this->loop_field = null;
        $this->call_field = null;
        $this->allocate_field = null;
        $this->instruction_field = null;
        $this->r_value_single_field = null;
        $this->r_value_tail_field = null;
        $this->r_value_field = null;
        $this->binary_operator_field = null;
        $this->unary_operator_field = null;
        $this->comment_field = null;
        $this->non_star_character_field = null;
        $this->non_slash_character_field = null;
        $this->comment_content_field = null;
        $this->qualfied_name_field = null;
        $this->name_tail_field = null;
        $this->name_field = null;
        $this->name_character_field = null;
        $this->boolean_field = null;
        $this->byte_field = null;
        $this->byte_digit_field = null;
        $this->negative_field = null;
        $this->decimal_field = null;
        $this->number_field = null;
        $this->digit_field = null;
        $this->literal_field = null;
        $this->literal_character_field = null;
        $this->whitespace_field = null;
    }

    public function SetCTCodeFile(?CTCodeFile $input_value): void
    {
        $this->c_t_code_file_field = $input_value;
    }

    public function GetCTCodeFile(): ?CTCodeFile
    {
        return $this->c_t_code_file_field;
    }

    public function SetExternalDefinition(?ExternalDefinition $input_value): void
    {
        $this->external_definition_field = $input_value;
    }

    public function GetExternalDefinition(): ?ExternalDefinition
    {
        return $this->external_definition_field;
    }

    public function SetUnmanagedType(?UnmanagedType $input_value): void
    {
        $this->unmanaged_type_field = $input_value;
    }

    public function GetUnmanagedType(): ?UnmanagedType
    {
        return $this->unmanaged_type_field;
    }

    public function SetDefinition(?Definition $input_value): void
    {
        $this->definition_field = $input_value;
    }

    public function GetDefinition(): ?Definition
    {
        return $this->definition_field;
    }

    public function SetInterfaceDef(?InterfaceDef $input_value): void
    {
        $this->interface_def_field = $input_value;
    }

    public function GetInterfaceDef(): ?InterfaceDef
    {
        return $this->interface_def_field;
    }

    public function SetClassDef(?ClassDef $input_value): void
    {
        $this->class_def_field = $input_value;
    }

    public function GetClassDef(): ?ClassDef
    {
        return $this->class_def_field;
    }

    public function SetImplementationSpec(?ImplementationSpec $input_value): void
    {
        $this->implementation_spec_field = $input_value;
    }

    public function GetImplementationSpec(): ?ImplementationSpec
    {
        return $this->implementation_spec_field;
    }

    public function SetContentDeclaration(?ContentDeclaration $input_value): void
    {
        $this->content_declaration_field = $input_value;
    }

    public function GetContentDeclaration(): ?ContentDeclaration
    {
        return $this->content_declaration_field;
    }

    public function SetContentDefinition(?ContentDefinition $input_value): void
    {
        $this->content_definition_field = $input_value;
    }

    public function GetContentDefinition(): ?ContentDefinition
    {
        return $this->content_definition_field;
    }

    public function SetPrimativeType(?PrimativeType $input_value): void
    {
        $this->primative_type_field = $input_value;
    }

    public function GetPrimativeType(): ?PrimativeType
    {
        return $this->primative_type_field;
    }

    public function SetDefinedType(?DefinedType $input_value): void
    {
        $this->defined_type_field = $input_value;
    }

    public function GetDefinedType(): ?DefinedType
    {
        return $this->defined_type_field;
    }

    public function SetSingletonType(?SingletonType $input_value): void
    {
        $this->singleton_type_field = $input_value;
    }

    public function GetSingletonType(): ?SingletonType
    {
        return $this->singleton_type_field;
    }

    public function SetDimensionalNote(?DimensionalNote $input_value): void
    {
        $this->dimensional_note_field = $input_value;
    }

    public function GetDimensionalNote(): ?DimensionalNote
    {
        return $this->dimensional_note_field;
    }

    public function SetDimensionalType(?DimensionalType $input_value): void
    {
        $this->dimensional_type_field = $input_value;
    }

    public function GetDimensionalType(): ?DimensionalType
    {
        return $this->dimensional_type_field;
    }

    public function SetMapNote(?MapNote $input_value): void
    {
        $this->map_note_field = $input_value;
    }

    public function GetMapNote(): ?MapNote
    {
        return $this->map_note_field;
    }

    public function SetMapType(?MapType $input_value): void
    {
        $this->map_type_field = $input_value;
    }

    public function GetMapType(): ?MapType
    {
        return $this->map_type_field;
    }

    public function SetValueType(?ValueType $input_value): void
    {
        $this->value_type_field = $input_value;
    }

    public function GetValueType(): ?ValueType
    {
        return $this->value_type_field;
    }

    public function SetParameterListDef(?ParameterListDef $input_value): void
    {
        $this->parameter_list_def_field = $input_value;
    }

    public function GetParameterListDef(): ?ParameterListDef
    {
        return $this->parameter_list_def_field;
    }

    public function SetParameterList(?ParameterList $input_value): void
    {
        $this->parameter_list_field = $input_value;
    }

    public function GetParameterList(): ?ParameterList
    {
        return $this->parameter_list_field;
    }

    public function SetCodeBlock(?CodeBlock $input_value): void
    {
        $this->code_block_field = $input_value;
    }

    public function GetCodeBlock(): ?CodeBlock
    {
        return $this->code_block_field;
    }

    public function SetDeclarationAssign(?DeclarationAssign $input_value): void
    {
        $this->declaration_assign_field = $input_value;
    }

    public function GetDeclarationAssign(): ?DeclarationAssign
    {
        return $this->declaration_assign_field;
    }

    public function SetDeclaration(?Declaration $input_value): void
    {
        $this->declaration_field = $input_value;
    }

    public function GetDeclaration(): ?Declaration
    {
        return $this->declaration_field;
    }

    public function SetAssignment(?Assignment $input_value): void
    {
        $this->assignment_field = $input_value;
    }

    public function GetAssignment(): ?Assignment
    {
        return $this->assignment_field;
    }

    public function SetReturn(?ReservedPrefixReturn $input_value): void
    {
        $this->return_field = $input_value;
    }

    public function GetReturn(): ?ReservedPrefixReturn
    {
        return $this->return_field;
    }

    public function SetElseTail(?ElseTail $input_value): void
    {
        $this->else_tail_field = $input_value;
    }

    public function GetElseTail(): ?ElseTail
    {
        return $this->else_tail_field;
    }

    public function SetConditional(?Conditional $input_value): void
    {
        $this->conditional_field = $input_value;
    }

    public function GetConditional(): ?Conditional
    {
        return $this->conditional_field;
    }

    public function SetLoop(?Loop $input_value): void
    {
        $this->loop_field = $input_value;
    }

    public function GetLoop(): ?Loop
    {
        return $this->loop_field;
    }

    public function SetCall(?Call $input_value): void
    {
        $this->call_field = $input_value;
    }

    public function GetCall(): ?Call
    {
        return $this->call_field;
    }

    public function SetAllocate(?Allocate $input_value): void
    {
        $this->allocate_field = $input_value;
    }

    public function GetAllocate(): ?Allocate
    {
        return $this->allocate_field;
    }

    public function SetInstruction(?Instruction $input_value): void
    {
        $this->instruction_field = $input_value;
    }

    public function GetInstruction(): ?Instruction
    {
        return $this->instruction_field;
    }

    public function SetRValueSingle(?RValueSingle $input_value): void
    {
        $this->r_value_single_field = $input_value;
    }

    public function GetRValueSingle(): ?RValueSingle
    {
        return $this->r_value_single_field;
    }

    public function SetRValueTail(?RValueTail $input_value): void
    {
        $this->r_value_tail_field = $input_value;
    }

    public function GetRValueTail(): ?RValueTail
    {
        return $this->r_value_tail_field;
    }

    public function SetRValue(?RValue $input_value): void
    {
        $this->r_value_field = $input_value;
    }

    public function GetRValue(): ?RValue
    {
        return $this->r_value_field;
    }

    public function SetBinaryOperator(?BinaryOperator $input_value): void
    {
        $this->binary_operator_field = $input_value;
    }

    public function GetBinaryOperator(): ?BinaryOperator
    {
        return $this->binary_operator_field;
    }

    public function SetUnaryOperator(?UnaryOperator $input_value): void
    {
        $this->unary_operator_field = $input_value;
    }

    public function GetUnaryOperator(): ?UnaryOperator
    {
        return $this->unary_operator_field;
    }

    public function SetComment(?Comment $input_value): void
    {
        $this->comment_field = $input_value;
    }

    public function GetComment(): ?Comment
    {
        return $this->comment_field;
    }

    public function SetNonStarCharacter(?NonStarCharacter $input_value): void
    {
        $this->non_star_character_field = $input_value;
    }

    public function GetNonStarCharacter(): ?NonStarCharacter
    {
        return $this->non_star_character_field;
    }

    public function SetNonSlashCharacter(?NonSlashCharacter $input_value): void
    {
        $this->non_slash_character_field = $input_value;
    }

    public function GetNonSlashCharacter(): ?NonSlashCharacter
    {
        return $this->non_slash_character_field;
    }

    public function SetCommentContent(?CommentContent $input_value): void
    {
        $this->comment_content_field = $input_value;
    }

    public function GetCommentContent(): ?CommentContent
    {
        return $this->comment_content_field;
    }

    public function SetQualfiedName(?QualfiedName $input_value): void
    {
        $this->qualfied_name_field = $input_value;
    }

    public function GetQualfiedName(): ?QualfiedName
    {
        return $this->qualfied_name_field;
    }

    public function SetNameTail(?NameTail $input_value): void
    {
        $this->name_tail_field = $input_value;
    }

    public function GetNameTail(): ?NameTail
    {
        return $this->name_tail_field;
    }

    public function SetName(?Name $input_value): void
    {
        $this->name_field = $input_value;
    }

    public function GetName(): ?Name
    {
        return $this->name_field;
    }

    public function SetNameCharacter(?NameCharacter $input_value): void
    {
        $this->name_character_field = $input_value;
    }

    public function GetNameCharacter(): ?NameCharacter
    {
        return $this->name_character_field;
    }

    public function SetBoolean(?Boolean $input_value): void
    {
        $this->boolean_field = $input_value;
    }

    public function GetBoolean(): ?Boolean
    {
        return $this->boolean_field;
    }

    public function SetByte(?Byte $input_value): void
    {
        $this->byte_field = $input_value;
    }

    public function GetByte(): ?Byte
    {
        return $this->byte_field;
    }

    public function SetByteDigit(?ByteDigit $input_value): void
    {
        $this->byte_digit_field = $input_value;
    }

    public function GetByteDigit(): ?ByteDigit
    {
        return $this->byte_digit_field;
    }

    public function SetNegative(?Negative $input_value): void
    {
        $this->negative_field = $input_value;
    }

    public function GetNegative(): ?Negative
    {
        return $this->negative_field;
    }

    public function SetDecimal(?Decimal $input_value): void
    {
        $this->decimal_field = $input_value;
    }

    public function GetDecimal(): ?Decimal
    {
        return $this->decimal_field;
    }

    public function SetNumber(?Number $input_value): void
    {
        $this->number_field = $input_value;
    }

    public function GetNumber(): ?Number
    {
        return $this->number_field;
    }

    public function SetDigit(?Digit $input_value): void
    {
        $this->digit_field = $input_value;
    }

    public function GetDigit(): ?Digit
    {
        return $this->digit_field;
    }

    public function SetLiteral(?Literal $input_value): void
    {
        $this->literal_field = $input_value;
    }

    public function GetLiteral(): ?Literal
    {
        return $this->literal_field;
    }

    public function SetLiteralCharacter(?LiteralCharacter $input_value): void
    {
        $this->literal_character_field = $input_value;
    }

    public function GetLiteralCharacter(): ?LiteralCharacter
    {
        return $this->literal_character_field;
    }

    public function SetWhitespace(?Whitespace $input_value): void
    {
        $this->whitespace_field = $input_value;
    }

    public function GetWhitespace(): ?Whitespace
    {
        return $this->whitespace_field;
    }

    private $c_t_code_file_field;
    private $external_definition_field;
    private $unmanaged_type_field;
    private $definition_field;
    private $interface_def_field;
    private $class_def_field;
    private $implementation_spec_field;
    private $content_declaration_field;
    private $content_definition_field;
    private $primative_type_field;
    private $defined_type_field;
    private $singleton_type_field;
    private $dimensional_note_field;
    private $dimensional_type_field;
    private $map_note_field;
    private $map_type_field;
    private $value_type_field;
    private $parameter_list_def_field;
    private $parameter_list_field;
    private $code_block_field;
    private $declaration_assign_field;
    private $declaration_field;
    private $assignment_field;
    private $return_field;
    private $else_tail_field;
    private $conditional_field;
    private $loop_field;
    private $call_field;
    private $allocate_field;
    private $instruction_field;
    private $r_value_single_field;
    private $r_value_tail_field;
    private $r_value_field;
    private $binary_operator_field;
    private $unary_operator_field;
    private $comment_field;
    private $non_star_character_field;
    private $non_slash_character_field;
    private $comment_content_field;
    private $qualfied_name_field;
    private $name_tail_field;
    private $name_field;
    private $name_character_field;
    private $boolean_field;
    private $byte_field;
    private $byte_digit_field;
    private $negative_field;
    private $decimal_field;
    private $number_field;
    private $digit_field;
    private $literal_field;
    private $literal_character_field;
    private $whitespace_field;
}

class DBNFOmniTypeResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?DBNFOmniType $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?DBNFOmniType
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    public function SetCTCodeFile(?CTCodeFile $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetCTCodeFile($input_value);
    }

    public function SetExternalDefinition(?ExternalDefinition $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetExternalDefinition($input_value);
    }

    public function SetUnmanagedType(?UnmanagedType $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetUnmanagedType($input_value);
    }

    public function SetDefinition(?Definition $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetDefinition($input_value);
    }

    public function SetInterfaceDef(?InterfaceDef $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetInterfaceDef($input_value);
    }

    public function SetClassDef(?ClassDef $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetClassDef($input_value);
    }

    public function SetImplementationSpec(?ImplementationSpec $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetImplementationSpec($input_value);
    }

    public function SetContentDeclaration(?ContentDeclaration $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetContentDeclaration($input_value);
    }

    public function SetContentDefinition(?ContentDefinition $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetContentDefinition($input_value);
    }

    public function SetPrimativeType(?PrimativeType $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetPrimativeType($input_value);
    }

    public function SetDefinedType(?DefinedType $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetDefinedType($input_value);
    }

    public function SetSingletonType(?SingletonType $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetSingletonType($input_value);
    }

    public function SetDimensionalNote(?DimensionalNote $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetDimensionalNote($input_value);
    }

    public function SetDimensionalType(?DimensionalType $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetDimensionalType($input_value);
    }

    public function SetMapNote(?MapNote $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetMapNote($input_value);
    }

    public function SetMapType(?MapType $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetMapType($input_value);
    }

    public function SetValueType(?ValueType $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetValueType($input_value);
    }

    public function SetParameterListDef(?ParameterListDef $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetParameterListDef($input_value);
    }

    public function SetParameterList(?ParameterList $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetParameterList($input_value);
    }

    public function SetCodeBlock(?CodeBlock $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetCodeBlock($input_value);
    }

    public function SetDeclarationAssign(?DeclarationAssign $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetDeclarationAssign($input_value);
    }

    public function SetDeclaration(?Declaration $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetDeclaration($input_value);
    }

    public function SetAssignment(?Assignment $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetAssignment($input_value);
    }

    public function SetReturn(?ReservedPrefixReturn $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetReturn($input_value);
    }

    public function SetElseTail(?ElseTail $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetElseTail($input_value);
    }

    public function SetConditional(?Conditional $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetConditional($input_value);
    }

    public function SetLoop(?Loop $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetLoop($input_value);
    }

    public function SetCall(?Call $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetCall($input_value);
    }

    public function SetAllocate(?Allocate $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetAllocate($input_value);
    }

    public function SetInstruction(?Instruction $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetInstruction($input_value);
    }

    public function SetRValueSingle(?RValueSingle $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetRValueSingle($input_value);
    }

    public function SetRValueTail(?RValueTail $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetRValueTail($input_value);
    }

    public function SetRValue(?RValue $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetRValue($input_value);
    }

    public function SetBinaryOperator(?BinaryOperator $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetBinaryOperator($input_value);
    }

    public function SetUnaryOperator(?UnaryOperator $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetUnaryOperator($input_value);
    }

    public function SetComment(?Comment $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetComment($input_value);
    }

    public function SetNonStarCharacter(?NonStarCharacter $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetNonStarCharacter($input_value);
    }

    public function SetNonSlashCharacter(?NonSlashCharacter $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetNonSlashCharacter($input_value);
    }

    public function SetCommentContent(?CommentContent $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetCommentContent($input_value);
    }

    public function SetQualfiedName(?QualfiedName $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetQualfiedName($input_value);
    }

    public function SetNameTail(?NameTail $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetNameTail($input_value);
    }

    public function SetName(?Name $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetName($input_value);
    }

    public function SetNameCharacter(?NameCharacter $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetNameCharacter($input_value);
    }

    public function SetBoolean(?Boolean $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetBoolean($input_value);
    }

    public function SetByte(?Byte $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetByte($input_value);
    }

    public function SetByteDigit(?ByteDigit $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetByteDigit($input_value);
    }

    public function SetNegative(?Negative $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetNegative($input_value);
    }

    public function SetDecimal(?Decimal $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetDecimal($input_value);
    }

    public function SetNumber(?Number $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetNumber($input_value);
    }

    public function SetDigit(?Digit $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetDigit($input_value);
    }

    public function SetLiteral(?Literal $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetLiteral($input_value);
    }

    public function SetLiteralCharacter(?LiteralCharacter $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetLiteralCharacter($input_value);
    }

    public function SetWhitespace(?Whitespace $input_value): void
    {
        $this->value = new DBNFOmniType();
        $this->value->SetWhitespace($input_value);
    }

    private $value;
    private $result;
}

class DBNFOmniTypeListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    public function SetCTCodeFile(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetCTCodeFile(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetExternalDefinition(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetExternalDefinition(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetUnmanagedType(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetUnmanagedType(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetDefinition(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetDefinition(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetInterfaceDef(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetInterfaceDef(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetClassDef(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetClassDef(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetImplementationSpec(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetImplementationSpec(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetContentDeclaration(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetContentDeclaration(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetContentDefinition(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetContentDefinition(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetPrimativeType(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetPrimativeType(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetDefinedType(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetDefinedType(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetSingletonType(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetSingletonType(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetDimensionalNote(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetDimensionalNote(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetDimensionalType(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetDimensionalType(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetMapNote(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetMapNote(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetMapType(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetMapType(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetValueType(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetValueType(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetParameterListDef(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetParameterListDef(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetParameterList(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetParameterList(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetCodeBlock(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetCodeBlock(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetDeclarationAssign(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetDeclarationAssign(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetDeclaration(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetDeclaration(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetAssignment(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetAssignment(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetReturn(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetReturn(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetElseTail(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetElseTail(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetConditional(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetConditional(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetLoop(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetLoop(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetCall(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetCall(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetAllocate(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetAllocate(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetInstruction(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetInstruction(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetRValueSingle(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetRValueSingle(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetRValueTail(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetRValueTail(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetRValue(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetRValue(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetBinaryOperator(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetBinaryOperator(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetUnaryOperator(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetUnaryOperator(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetComment(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetComment(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetNonStarCharacter(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetNonStarCharacter(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetNonSlashCharacter(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetNonSlashCharacter(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetCommentContent(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetCommentContent(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetQualfiedName(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetQualfiedName(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetNameTail(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetNameTail(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetName(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetName(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetNameCharacter(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetNameCharacter(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetBoolean(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetBoolean(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetByte(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetByte(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetByteDigit(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetByteDigit(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetNegative(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetNegative(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetDecimal(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetDecimal(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetNumber(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetNumber(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetDigit(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetDigit(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetLiteral(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetLiteral(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetLiteralCharacter(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetLiteralCharacter(Element($input_value,$index));
            $index = $index+1;
        }
    }

    public function SetWhitespace(?array $input_value): void
    {
        $index = 0;
        while ($index<Size($input_value))
        {
            $value = new DBNFOmniType();
            $value->SetWhitespace(Element($input_value,$index));
            $index = $index+1;
        }
    }

    private $value;
    private $result;
}

class LargeString {
    public function __construct() {
        $this->data = "";
    }

    public function SetData(?string $new_data): void
    {
        $this->data = $new_data;
    }

    public function GetData(): ?string
    {
        return $this->data;
    }

    public function GetIntAt(?int $offset): ?int
    {
        return IntAt($this->data,$offset);
    }

    public function GetAt(?int $offset): ?string
    {
        return At($this->data,$offset);
    }

    private $data;
}

class LengthString {
    public function __construct() {
        $this->data = null;
        $this->start = 0;
        $this->length = 0;
    }

    public function SetData(?LargeString $new_data): void
    {
        $this->data = $new_data;
    }

    public function GetData(): ?LargeString
    {
        return $this->data;
    }

    public function SetStart(?int $new_start): void
    {
        $this->start = $new_start;
    }

    public function GetStart(): ?int
    {
        return $this->start;
    }

    public function SetLength(?int $new_length): void
    {
        $this->length = $new_length;
    }

    public function GetLength(): ?int
    {
        return $this->length;
    }

    public function GetString(): ?string
    {
        $deep_data = $this->data->GetData();
        $result = "";
        $index = $this->start;
        $end = $this->start+$this->length;
        while ($index<$end)
        {
            $result = Concat($result,At($deep_data,$index));
            $index = $index+1;
        }
        return $result;
    }

    private $data;
    private $start;
    private $length;
}

class CTCodeFileParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?CTCodeFileResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new CTCodeFile();
        $declarations_field = new ExternalDefinitionListResult();
        $definitions_field = new DefinitionListResult();
        $unmanaged_types_field = new UnmanagedTypeListResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$external_definition_parser_instance->ParseManySave($index,$declarations_field,0,-1)&&$unmanaged_type_parser_instance->ParseManySave($index,$unmanaged_types_field,0,-1)&&$definition_parser_instance->ParseManySave($index,$definitions_field,0,-1))
        {
            $instance->SetDeclarations($declarations_field->GetValue());
            $instance->SetDefinitions($definitions_field->GetValue());
            $instance->SetUnmanagedTypes($unmanaged_types_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $declarations_field = new ExternalDefinitionListResult();
            $definitions_field = new DefinitionListResult();
            $unmanaged_types_field = new UnmanagedTypeListResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new CTCodeFileResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?CTCodeFileResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new CTCodeFileResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?CTCodeFileListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new CTCodeFileResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new CTCodeFileListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class CTCodeFileResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?CTCodeFile $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?CTCodeFile
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class CTCodeFileListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class CTCodeFile {
    public function __construct() {
        $this->length_string = null;
        $this->declarations_field = array();
        $this->definitions_field = array();
        $this->unmanaged_types_field = array();
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetDeclarations(?array $input_value): void
    {
        $this->declarations_field = $input_value;
    }

    public function GetDeclarations(): ?array
    {
        return $this->declarations_field;
    }

    public function SetDefinitions(?array $input_value): void
    {
        $this->definitions_field = $input_value;
    }

    public function GetDefinitions(): ?array
    {
        return $this->definitions_field;
    }

    public function SetUnmanagedTypes(?array $input_value): void
    {
        $this->unmanaged_types_field = $input_value;
    }

    public function GetUnmanagedTypes(): ?array
    {
        return $this->unmanaged_types_field;
    }

    private $length_string;
    private $declarations_field;
    private $definitions_field;
    private $unmanaged_types_field;
}

class ExternalDefinitionParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?ExternalDefinitionResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new ExternalDefinition();
        $exdef_field = new QualfiedNameResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$string_parser_instance->ParseSingle($index,'exdef')&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$qualfied_name_parser_instance->ParseSingleSave($index,$exdef_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,';')&&$whitespace_parser_instance->ParseMany($index,0,-1))
        {
            $instance->SetExdef($exdef_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $exdef_field = new QualfiedNameResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new ExternalDefinitionResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?ExternalDefinitionResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new ExternalDefinitionResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?ExternalDefinitionListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new ExternalDefinitionResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new ExternalDefinitionListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class ExternalDefinitionResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?ExternalDefinition $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?ExternalDefinition
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class ExternalDefinitionListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class ExternalDefinition {
    public function __construct() {
        $this->length_string = null;
        $this->exdef_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetExdef(?QualfiedName $input_value): void
    {
        $this->exdef_field = $input_value;
    }

    public function GetExdef(): ?QualfiedName
    {
        return $this->exdef_field;
    }

    private $length_string;
    private $exdef_field;
}

class UnmanagedTypeParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?UnmanagedTypeResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new UnmanagedType();
        $unmanaged_type_field = new QualfiedNameResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$string_parser_instance->ParseSingle($index,'unmanaged')&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$qualfied_name_parser_instance->ParseSingleSave($index,$unmanaged_type_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,';')&&$whitespace_parser_instance->ParseMany($index,0,-1))
        {
            $instance->SetUnmanagedType($unmanaged_type_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $unmanaged_type_field = new QualfiedNameResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new UnmanagedTypeResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?UnmanagedTypeResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new UnmanagedTypeResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?UnmanagedTypeListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new UnmanagedTypeResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new UnmanagedTypeListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class UnmanagedTypeResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?UnmanagedType $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?UnmanagedType
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class UnmanagedTypeListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class UnmanagedType {
    public function __construct() {
        $this->length_string = null;
        $this->unmanaged_type_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetUnmanagedType(?QualfiedName $input_value): void
    {
        $this->unmanaged_type_field = $input_value;
    }

    public function GetUnmanagedType(): ?QualfiedName
    {
        return $this->unmanaged_type_field;
    }

    private $length_string;
    private $unmanaged_type_field;
}

class DefinitionParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?DefinitionResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new Definition();
        $class_def_field = new ClassDefResult();
        $interface_def_field = new InterfaceDefResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$interface_def_parser_instance->ParseSingleSave($index,$interface_def_field))
        {
            $instance->SetClassDef($class_def_field->GetValue());
            $instance->SetInterfaceDef($interface_def_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $class_def_field = new ClassDefResult();
            $interface_def_field = new InterfaceDefResult();
        }
        if (true&&$class_def_parser_instance->ParseSingleSave($index,$class_def_field))
        {
            $instance->SetClassDef($class_def_field->GetValue());
            $instance->SetInterfaceDef($interface_def_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $class_def_field = new ClassDefResult();
            $interface_def_field = new InterfaceDefResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new DefinitionResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?DefinitionResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new DefinitionResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?DefinitionListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new DefinitionResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new DefinitionListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class DefinitionResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?Definition $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?Definition
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class DefinitionListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class Definition {
    public function __construct() {
        $this->length_string = null;
        $this->class_def_field = null;
        $this->interface_def_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetClassDef(?ClassDef $input_value): void
    {
        $this->class_def_field = $input_value;
    }

    public function GetClassDef(): ?ClassDef
    {
        return $this->class_def_field;
    }

    public function SetInterfaceDef(?InterfaceDef $input_value): void
    {
        $this->interface_def_field = $input_value;
    }

    public function GetInterfaceDef(): ?InterfaceDef
    {
        return $this->interface_def_field;
    }

    private $length_string;
    private $class_def_field;
    private $interface_def_field;
}

class InterfaceDefParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?InterfaceDefResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new InterfaceDef();
        $comment_field = new CommentResult();
        $declarations_field = new ContentDeclarationListResult();
        $name_field = new NameResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$comment_parser_instance->ParseOptionalSave($index,$comment_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,'interface')&&$whitespace_parser_instance->ParseMany($index,1,-1)&&$name_parser_instance->ParseSingleSave($index,$name_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,'{')&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$content_declaration_parser_instance->ParseManySave($index,$declarations_field,0,-1)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,'}')&&$whitespace_parser_instance->ParseMany($index,0,-1))
        {
            $instance->SetComment($comment_field->GetValue());
            $instance->SetDeclarations($declarations_field->GetValue());
            $instance->SetName($name_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $comment_field = new CommentResult();
            $declarations_field = new ContentDeclarationListResult();
            $name_field = new NameResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new InterfaceDefResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?InterfaceDefResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new InterfaceDefResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?InterfaceDefListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new InterfaceDefResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new InterfaceDefListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class InterfaceDefResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?InterfaceDef $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?InterfaceDef
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class InterfaceDefListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class InterfaceDef {
    public function __construct() {
        $this->length_string = null;
        $this->comment_field = null;
        $this->declarations_field = array();
        $this->name_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetComment(?Comment $input_value): void
    {
        $this->comment_field = $input_value;
    }

    public function GetComment(): ?Comment
    {
        return $this->comment_field;
    }

    public function SetDeclarations(?array $input_value): void
    {
        $this->declarations_field = $input_value;
    }

    public function GetDeclarations(): ?array
    {
        return $this->declarations_field;
    }

    public function SetName(?Name $input_value): void
    {
        $this->name_field = $input_value;
    }

    public function GetName(): ?Name
    {
        return $this->name_field;
    }

    private $length_string;
    private $comment_field;
    private $declarations_field;
    private $name_field;
}

class ClassDefParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?ClassDefResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new ClassDef();
        $comment_field = new CommentResult();
        $definitions_field = new ContentDefinitionListResult();
        $implementing_field = new ImplementationSpecResult();
        $name_field = new NameResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$comment_parser_instance->ParseOptionalSave($index,$comment_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,'class')&&$whitespace_parser_instance->ParseMany($index,1,-1)&&$name_parser_instance->ParseSingleSave($index,$name_field)&&$implementation_spec_parser_instance->ParseOptionalSave($index,$implementing_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,'{')&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$content_definition_parser_instance->ParseManySave($index,$definitions_field,0,-1)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,'}')&&$whitespace_parser_instance->ParseMany($index,0,-1))
        {
            $instance->SetComment($comment_field->GetValue());
            $instance->SetDefinitions($definitions_field->GetValue());
            $instance->SetImplementing($implementing_field->GetValue());
            $instance->SetName($name_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $comment_field = new CommentResult();
            $definitions_field = new ContentDefinitionListResult();
            $implementing_field = new ImplementationSpecResult();
            $name_field = new NameResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new ClassDefResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?ClassDefResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new ClassDefResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?ClassDefListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new ClassDefResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new ClassDefListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class ClassDefResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?ClassDef $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?ClassDef
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class ClassDefListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class ClassDef {
    public function __construct() {
        $this->length_string = null;
        $this->comment_field = null;
        $this->definitions_field = array();
        $this->implementing_field = null;
        $this->name_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetComment(?Comment $input_value): void
    {
        $this->comment_field = $input_value;
    }

    public function GetComment(): ?Comment
    {
        return $this->comment_field;
    }

    public function SetDefinitions(?array $input_value): void
    {
        $this->definitions_field = $input_value;
    }

    public function GetDefinitions(): ?array
    {
        return $this->definitions_field;
    }

    public function SetImplementing(?ImplementationSpec $input_value): void
    {
        $this->implementing_field = $input_value;
    }

    public function GetImplementing(): ?ImplementationSpec
    {
        return $this->implementing_field;
    }

    public function SetName(?Name $input_value): void
    {
        $this->name_field = $input_value;
    }

    public function GetName(): ?Name
    {
        return $this->name_field;
    }

    private $length_string;
    private $comment_field;
    private $definitions_field;
    private $implementing_field;
    private $name_field;
}

class ImplementationSpecParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?ImplementationSpecResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new ImplementationSpec();
        $interface_field = new QualfiedNameResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$whitespace_parser_instance->ParseMany($index,1,-1)&&$string_parser_instance->ParseSingle($index,'implements')&&$whitespace_parser_instance->ParseMany($index,1,-1)&&$qualfied_name_parser_instance->ParseSingleSave($index,$interface_field)&&$whitespace_parser_instance->ParseMany($index,0,-1))
        {
            $instance->SetInterface($interface_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $interface_field = new QualfiedNameResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new ImplementationSpecResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?ImplementationSpecResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new ImplementationSpecResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?ImplementationSpecListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new ImplementationSpecResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new ImplementationSpecListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class ImplementationSpecResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?ImplementationSpec $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?ImplementationSpec
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class ImplementationSpecListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class ImplementationSpec {
    public function __construct() {
        $this->length_string = null;
        $this->interface_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetInterface(?QualfiedName $input_value): void
    {
        $this->interface_field = $input_value;
    }

    public function GetInterface(): ?QualfiedName
    {
        return $this->interface_field;
    }

    private $length_string;
    private $interface_field;
}

class ContentDeclarationParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?ContentDeclarationResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new ContentDeclaration();
        $comment_field = new CommentResult();
        $name_field = new NameResult();
        $parameters_field = new ParameterListDefResult();
        $type_field = new ValueTypeResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$comment_parser_instance->ParseOptionalSave($index,$comment_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,'function')&&$whitespace_parser_instance->ParseMany($index,1,-1)&&$value_type_parser_instance->ParseSingleSave($index,$type_field)&&$whitespace_parser_instance->ParseMany($index,1,-1)&&$name_parser_instance->ParseSingleSave($index,$name_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,'(')&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$parameter_list_def_parser_instance->ParseOptionalSave($index,$parameters_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,')')&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,';')&&$whitespace_parser_instance->ParseMany($index,0,-1))
        {
            $instance->SetComment($comment_field->GetValue());
            $instance->SetName($name_field->GetValue());
            $instance->SetParameters($parameters_field->GetValue());
            $instance->SetType($type_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $comment_field = new CommentResult();
            $name_field = new NameResult();
            $parameters_field = new ParameterListDefResult();
            $type_field = new ValueTypeResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new ContentDeclarationResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?ContentDeclarationResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new ContentDeclarationResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?ContentDeclarationListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new ContentDeclarationResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new ContentDeclarationListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class ContentDeclarationResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?ContentDeclaration $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?ContentDeclaration
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class ContentDeclarationListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class ContentDeclaration {
    public function __construct() {
        $this->length_string = null;
        $this->comment_field = null;
        $this->name_field = null;
        $this->parameters_field = null;
        $this->type_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetComment(?Comment $input_value): void
    {
        $this->comment_field = $input_value;
    }

    public function GetComment(): ?Comment
    {
        return $this->comment_field;
    }

    public function SetName(?Name $input_value): void
    {
        $this->name_field = $input_value;
    }

    public function GetName(): ?Name
    {
        return $this->name_field;
    }

    public function SetParameters(?ParameterListDef $input_value): void
    {
        $this->parameters_field = $input_value;
    }

    public function GetParameters(): ?ParameterListDef
    {
        return $this->parameters_field;
    }

    public function SetType(?ValueType $input_value): void
    {
        $this->type_field = $input_value;
    }

    public function ReservedPrefixGetType(): ?ValueType
    {
        return $this->type_field;
    }

    private $length_string;
    private $comment_field;
    private $name_field;
    private $parameters_field;
    private $type_field;
}

class ContentDefinitionParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?ContentDefinitionResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new ContentDefinition();
        $comment_field = new CommentResult();
        $function_body_field = new CodeBlockResult();
        $name_field = new NameResult();
        $parameters_field = new ParameterListDefResult();
        $type_field = new ValueTypeResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$comment_parser_instance->ParseOptionalSave($index,$comment_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,'function')&&$whitespace_parser_instance->ParseMany($index,1,-1)&&$value_type_parser_instance->ParseSingleSave($index,$type_field)&&$whitespace_parser_instance->ParseMany($index,1,-1)&&$name_parser_instance->ParseSingleSave($index,$name_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,'(')&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$parameter_list_def_parser_instance->ParseOptionalSave($index,$parameters_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,')')&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$code_block_parser_instance->ParseSingleSave($index,$function_body_field)&&$whitespace_parser_instance->ParseMany($index,0,-1))
        {
            $instance->SetComment($comment_field->GetValue());
            $instance->SetFunctionBody($function_body_field->GetValue());
            $instance->SetName($name_field->GetValue());
            $instance->SetParameters($parameters_field->GetValue());
            $instance->SetType($type_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $comment_field = new CommentResult();
            $function_body_field = new CodeBlockResult();
            $name_field = new NameResult();
            $parameters_field = new ParameterListDefResult();
            $type_field = new ValueTypeResult();
        }
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$comment_parser_instance->ParseOptionalSave($index,$comment_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$value_type_parser_instance->ParseSingleSave($index,$type_field)&&$whitespace_parser_instance->ParseMany($index,1,-1)&&$name_parser_instance->ParseSingleSave($index,$name_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,';')&&$whitespace_parser_instance->ParseMany($index,0,-1))
        {
            $instance->SetComment($comment_field->GetValue());
            $instance->SetFunctionBody($function_body_field->GetValue());
            $instance->SetName($name_field->GetValue());
            $instance->SetParameters($parameters_field->GetValue());
            $instance->SetType($type_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $comment_field = new CommentResult();
            $function_body_field = new CodeBlockResult();
            $name_field = new NameResult();
            $parameters_field = new ParameterListDefResult();
            $type_field = new ValueTypeResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new ContentDefinitionResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?ContentDefinitionResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new ContentDefinitionResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?ContentDefinitionListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new ContentDefinitionResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new ContentDefinitionListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class ContentDefinitionResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?ContentDefinition $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?ContentDefinition
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class ContentDefinitionListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class ContentDefinition {
    public function __construct() {
        $this->length_string = null;
        $this->comment_field = null;
        $this->function_body_field = null;
        $this->name_field = null;
        $this->parameters_field = null;
        $this->type_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetComment(?Comment $input_value): void
    {
        $this->comment_field = $input_value;
    }

    public function GetComment(): ?Comment
    {
        return $this->comment_field;
    }

    public function SetFunctionBody(?CodeBlock $input_value): void
    {
        $this->function_body_field = $input_value;
    }

    public function GetFunctionBody(): ?CodeBlock
    {
        return $this->function_body_field;
    }

    public function SetName(?Name $input_value): void
    {
        $this->name_field = $input_value;
    }

    public function GetName(): ?Name
    {
        return $this->name_field;
    }

    public function SetParameters(?ParameterListDef $input_value): void
    {
        $this->parameters_field = $input_value;
    }

    public function GetParameters(): ?ParameterListDef
    {
        return $this->parameters_field;
    }

    public function SetType(?ValueType $input_value): void
    {
        $this->type_field = $input_value;
    }

    public function ReservedPrefixGetType(): ?ValueType
    {
        return $this->type_field;
    }

    private $length_string;
    private $comment_field;
    private $function_body_field;
    private $name_field;
    private $parameters_field;
    private $type_field;
}

class PrimativeTypeParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?PrimativeTypeResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new PrimativeType();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$string_parser_instance->ParseSingle($index,'int'))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        if (true&&$string_parser_instance->ParseSingle($index,'string'))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        if (true&&$string_parser_instance->ParseSingle($index,'bool'))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        if (true&&$string_parser_instance->ParseSingle($index,'float'))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        if (true&&$string_parser_instance->ParseSingle($index,'void'))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new PrimativeTypeResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?PrimativeTypeResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new PrimativeTypeResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?PrimativeTypeListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new PrimativeTypeResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new PrimativeTypeListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class PrimativeTypeResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?PrimativeType $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?PrimativeType
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class PrimativeTypeListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class PrimativeType {
    public function __construct() {
        $this->length_string = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    private $length_string;
}

class DefinedTypeParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?DefinedTypeResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new DefinedType();
        $name_field = new QualfiedNameResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$qualfied_name_parser_instance->ParseSingleSave($index,$name_field))
        {
            $instance->SetName($name_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $name_field = new QualfiedNameResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new DefinedTypeResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?DefinedTypeResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new DefinedTypeResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?DefinedTypeListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new DefinedTypeResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new DefinedTypeListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class DefinedTypeResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?DefinedType $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?DefinedType
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class DefinedTypeListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class DefinedType {
    public function __construct() {
        $this->length_string = null;
        $this->name_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetName(?QualfiedName $input_value): void
    {
        $this->name_field = $input_value;
    }

    public function GetName(): ?QualfiedName
    {
        return $this->name_field;
    }

    private $length_string;
    private $name_field;
}

class SingletonTypeParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?SingletonTypeResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new SingletonType();
        $defined_type_field = new DefinedTypeResult();
        $primative_type_field = new PrimativeTypeResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$primative_type_parser_instance->ParseSingleSave($index,$primative_type_field))
        {
            $instance->SetDefinedType($defined_type_field->GetValue());
            $instance->SetPrimativeType($primative_type_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $defined_type_field = new DefinedTypeResult();
            $primative_type_field = new PrimativeTypeResult();
        }
        if (true&&$defined_type_parser_instance->ParseSingleSave($index,$defined_type_field))
        {
            $instance->SetDefinedType($defined_type_field->GetValue());
            $instance->SetPrimativeType($primative_type_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $defined_type_field = new DefinedTypeResult();
            $primative_type_field = new PrimativeTypeResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new SingletonTypeResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?SingletonTypeResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new SingletonTypeResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?SingletonTypeListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new SingletonTypeResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new SingletonTypeListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class SingletonTypeResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?SingletonType $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?SingletonType
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class SingletonTypeListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class SingletonType {
    public function __construct() {
        $this->length_string = null;
        $this->defined_type_field = null;
        $this->primative_type_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetDefinedType(?DefinedType $input_value): void
    {
        $this->defined_type_field = $input_value;
    }

    public function GetDefinedType(): ?DefinedType
    {
        return $this->defined_type_field;
    }

    public function SetPrimativeType(?PrimativeType $input_value): void
    {
        $this->primative_type_field = $input_value;
    }

    public function GetPrimativeType(): ?PrimativeType
    {
        return $this->primative_type_field;
    }

    private $length_string;
    private $defined_type_field;
    private $primative_type_field;
}

class DimensionalNoteParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?DimensionalNoteResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new DimensionalNote();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,'[')&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,']'))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new DimensionalNoteResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?DimensionalNoteResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new DimensionalNoteResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?DimensionalNoteListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new DimensionalNoteResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new DimensionalNoteListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class DimensionalNoteResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?DimensionalNote $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?DimensionalNote
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class DimensionalNoteListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class DimensionalNote {
    public function __construct() {
        $this->length_string = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    private $length_string;
}

class DimensionalTypeParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?DimensionalTypeResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new DimensionalType();
        $dimensional_note_field = new DimensionalNoteListResult();
        $singleton_type_field = new SingletonTypeResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$singleton_type_parser_instance->ParseSingleSave($index,$singleton_type_field)&&$dimensional_note_parser_instance->ParseManySave($index,$dimensional_note_field,1,-1))
        {
            $instance->SetDimensionalNote($dimensional_note_field->GetValue());
            $instance->SetSingletonType($singleton_type_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $dimensional_note_field = new DimensionalNoteListResult();
            $singleton_type_field = new SingletonTypeResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new DimensionalTypeResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?DimensionalTypeResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new DimensionalTypeResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?DimensionalTypeListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new DimensionalTypeResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new DimensionalTypeListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class DimensionalTypeResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?DimensionalType $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?DimensionalType
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class DimensionalTypeListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class DimensionalType {
    public function __construct() {
        $this->length_string = null;
        $this->dimensional_note_field = array();
        $this->singleton_type_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetDimensionalNote(?array $input_value): void
    {
        $this->dimensional_note_field = $input_value;
    }

    public function GetDimensionalNote(): ?array
    {
        return $this->dimensional_note_field;
    }

    public function SetSingletonType(?SingletonType $input_value): void
    {
        $this->singleton_type_field = $input_value;
    }

    public function GetSingletonType(): ?SingletonType
    {
        return $this->singleton_type_field;
    }

    private $length_string;
    private $dimensional_note_field;
    private $singleton_type_field;
}

class MapNoteParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?MapNoteResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new MapNote();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,'{')&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,'}'))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new MapNoteResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?MapNoteResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new MapNoteResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?MapNoteListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new MapNoteResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new MapNoteListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class MapNoteResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?MapNote $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?MapNote
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class MapNoteListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class MapNote {
    public function __construct() {
        $this->length_string = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    private $length_string;
}

class MapTypeParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?MapTypeResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new MapType();
        $map_note_field = new MapNoteResult();
        $singleton_type_field = new SingletonTypeResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$singleton_type_parser_instance->ParseSingleSave($index,$singleton_type_field)&&$map_note_parser_instance->ParseSingleSave($index,$map_note_field))
        {
            $instance->SetMapNote($map_note_field->GetValue());
            $instance->SetSingletonType($singleton_type_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $map_note_field = new MapNoteResult();
            $singleton_type_field = new SingletonTypeResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new MapTypeResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?MapTypeResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new MapTypeResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?MapTypeListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new MapTypeResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new MapTypeListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class MapTypeResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?MapType $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?MapType
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class MapTypeListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class MapType {
    public function __construct() {
        $this->length_string = null;
        $this->map_note_field = null;
        $this->singleton_type_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetMapNote(?MapNote $input_value): void
    {
        $this->map_note_field = $input_value;
    }

    public function GetMapNote(): ?MapNote
    {
        return $this->map_note_field;
    }

    public function SetSingletonType(?SingletonType $input_value): void
    {
        $this->singleton_type_field = $input_value;
    }

    public function GetSingletonType(): ?SingletonType
    {
        return $this->singleton_type_field;
    }

    private $length_string;
    private $map_note_field;
    private $singleton_type_field;
}

class ValueTypeParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?ValueTypeResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new ValueType();
        $dimensional_type_field = new DimensionalTypeResult();
        $map_type_field = new MapTypeResult();
        $singleton_type_field = new SingletonTypeResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$dimensional_type_parser_instance->ParseSingleSave($index,$dimensional_type_field))
        {
            $instance->SetDimensionalType($dimensional_type_field->GetValue());
            $instance->SetMapType($map_type_field->GetValue());
            $instance->SetSingletonType($singleton_type_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $dimensional_type_field = new DimensionalTypeResult();
            $map_type_field = new MapTypeResult();
            $singleton_type_field = new SingletonTypeResult();
        }
        if (true&&$map_type_parser_instance->ParseSingleSave($index,$map_type_field))
        {
            $instance->SetDimensionalType($dimensional_type_field->GetValue());
            $instance->SetMapType($map_type_field->GetValue());
            $instance->SetSingletonType($singleton_type_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $dimensional_type_field = new DimensionalTypeResult();
            $map_type_field = new MapTypeResult();
            $singleton_type_field = new SingletonTypeResult();
        }
        if (true&&$singleton_type_parser_instance->ParseSingleSave($index,$singleton_type_field))
        {
            $instance->SetDimensionalType($dimensional_type_field->GetValue());
            $instance->SetMapType($map_type_field->GetValue());
            $instance->SetSingletonType($singleton_type_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $dimensional_type_field = new DimensionalTypeResult();
            $map_type_field = new MapTypeResult();
            $singleton_type_field = new SingletonTypeResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new ValueTypeResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?ValueTypeResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new ValueTypeResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?ValueTypeListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new ValueTypeResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new ValueTypeListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class ValueTypeResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?ValueType $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?ValueType
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class ValueTypeListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class ValueType {
    public function __construct() {
        $this->length_string = null;
        $this->dimensional_type_field = null;
        $this->map_type_field = null;
        $this->singleton_type_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetDimensionalType(?DimensionalType $input_value): void
    {
        $this->dimensional_type_field = $input_value;
    }

    public function GetDimensionalType(): ?DimensionalType
    {
        return $this->dimensional_type_field;
    }

    public function SetMapType(?MapType $input_value): void
    {
        $this->map_type_field = $input_value;
    }

    public function GetMapType(): ?MapType
    {
        return $this->map_type_field;
    }

    public function SetSingletonType(?SingletonType $input_value): void
    {
        $this->singleton_type_field = $input_value;
    }

    public function GetSingletonType(): ?SingletonType
    {
        return $this->singleton_type_field;
    }

    private $length_string;
    private $dimensional_type_field;
    private $map_type_field;
    private $singleton_type_field;
}

class ParameterListDefParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?ParameterListDefResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new ParameterListDef();
        $name_field = new NameResult();
        $parameter_tail_field = new ParameterListDefResult();
        $type_field = new ValueTypeResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$value_type_parser_instance->ParseSingleSave($index,$type_field)&&$whitespace_parser_instance->ParseMany($index,1,-1)&&$name_parser_instance->ParseSingleSave($index,$name_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,',')&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$parameter_list_def_parser_instance->ParseSingleSave($index,$parameter_tail_field))
        {
            $instance->SetName($name_field->GetValue());
            $instance->SetParameterTail($parameter_tail_field->GetValue());
            $instance->SetType($type_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $name_field = new NameResult();
            $parameter_tail_field = new ParameterListDefResult();
            $type_field = new ValueTypeResult();
        }
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$value_type_parser_instance->ParseSingleSave($index,$type_field)&&$whitespace_parser_instance->ParseMany($index,1,-1)&&$name_parser_instance->ParseSingleSave($index,$name_field)&&$whitespace_parser_instance->ParseMany($index,0,-1))
        {
            $instance->SetName($name_field->GetValue());
            $instance->SetParameterTail($parameter_tail_field->GetValue());
            $instance->SetType($type_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $name_field = new NameResult();
            $parameter_tail_field = new ParameterListDefResult();
            $type_field = new ValueTypeResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new ParameterListDefResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?ParameterListDefResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new ParameterListDefResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?ParameterListDefListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new ParameterListDefResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new ParameterListDefListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class ParameterListDefResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?ParameterListDef $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?ParameterListDef
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class ParameterListDefListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class ParameterListDef {
    public function __construct() {
        $this->length_string = null;
        $this->name_field = null;
        $this->parameter_tail_field = null;
        $this->type_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetName(?Name $input_value): void
    {
        $this->name_field = $input_value;
    }

    public function GetName(): ?Name
    {
        return $this->name_field;
    }

    public function SetParameterTail(?ParameterListDef $input_value): void
    {
        $this->parameter_tail_field = $input_value;
    }

    public function GetParameterTail(): ?ParameterListDef
    {
        return $this->parameter_tail_field;
    }

    public function SetType(?ValueType $input_value): void
    {
        $this->type_field = $input_value;
    }

    public function ReservedPrefixGetType(): ?ValueType
    {
        return $this->type_field;
    }

    private $length_string;
    private $name_field;
    private $parameter_tail_field;
    private $type_field;
}

class ParameterListParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?ParameterListResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new ParameterList();
        $parameter_tail_field = new ParameterListResult();
        $r_value_field = new RValueResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$r_value_parser_instance->ParseSingleSave($index,$r_value_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,',')&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$parameter_list_parser_instance->ParseSingleSave($index,$parameter_tail_field))
        {
            $instance->SetParameterTail($parameter_tail_field->GetValue());
            $instance->SetRValue($r_value_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $parameter_tail_field = new ParameterListResult();
            $r_value_field = new RValueResult();
        }
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$r_value_parser_instance->ParseSingleSave($index,$r_value_field)&&$whitespace_parser_instance->ParseMany($index,0,-1))
        {
            $instance->SetParameterTail($parameter_tail_field->GetValue());
            $instance->SetRValue($r_value_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $parameter_tail_field = new ParameterListResult();
            $r_value_field = new RValueResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new ParameterListResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?ParameterListResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new ParameterListResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?ParameterListListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new ParameterListResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new ParameterListListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class ParameterListResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?ParameterList $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?ParameterList
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class ParameterListListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class ParameterList {
    public function __construct() {
        $this->length_string = null;
        $this->parameter_tail_field = null;
        $this->r_value_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetParameterTail(?ParameterList $input_value): void
    {
        $this->parameter_tail_field = $input_value;
    }

    public function GetParameterTail(): ?ParameterList
    {
        return $this->parameter_tail_field;
    }

    public function SetRValue(?RValue $input_value): void
    {
        $this->r_value_field = $input_value;
    }

    public function GetRValue(): ?RValue
    {
        return $this->r_value_field;
    }

    private $length_string;
    private $parameter_tail_field;
    private $r_value_field;
}

class CodeBlockParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?CodeBlockResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new CodeBlock();
        $instructions_field = new InstructionListResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,'{')&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$instruction_parser_instance->ParseManySave($index,$instructions_field,0,-1)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,'}')&&$whitespace_parser_instance->ParseMany($index,0,-1))
        {
            $instance->SetInstructions($instructions_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $instructions_field = new InstructionListResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new CodeBlockResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?CodeBlockResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new CodeBlockResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?CodeBlockListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new CodeBlockResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new CodeBlockListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class CodeBlockResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?CodeBlock $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?CodeBlock
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class CodeBlockListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class CodeBlock {
    public function __construct() {
        $this->length_string = null;
        $this->instructions_field = array();
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetInstructions(?array $input_value): void
    {
        $this->instructions_field = $input_value;
    }

    public function GetInstructions(): ?array
    {
        return $this->instructions_field;
    }

    private $length_string;
    private $instructions_field;
}

class DeclarationAssignParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?DeclarationAssignResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new DeclarationAssign();
        $r_value_field = new RValueResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,'=')&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$r_value_parser_instance->ParseSingleSave($index,$r_value_field)&&$whitespace_parser_instance->ParseMany($index,0,-1))
        {
            $instance->SetRValue($r_value_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $r_value_field = new RValueResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new DeclarationAssignResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?DeclarationAssignResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new DeclarationAssignResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?DeclarationAssignListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new DeclarationAssignResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new DeclarationAssignListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class DeclarationAssignResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?DeclarationAssign $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?DeclarationAssign
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class DeclarationAssignListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class DeclarationAssign {
    public function __construct() {
        $this->length_string = null;
        $this->r_value_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetRValue(?RValue $input_value): void
    {
        $this->r_value_field = $input_value;
    }

    public function GetRValue(): ?RValue
    {
        return $this->r_value_field;
    }

    private $length_string;
    private $r_value_field;
}

class DeclarationParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?DeclarationResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new Declaration();
        $assignment_field = new DeclarationAssignResult();
        $name_field = new NameResult();
        $type_field = new ValueTypeResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$value_type_parser_instance->ParseSingleSave($index,$type_field)&&$whitespace_parser_instance->ParseMany($index,1,-1)&&$name_parser_instance->ParseSingleSave($index,$name_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$declaration_assign_parser_instance->ParseOptionalSave($index,$assignment_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,';')&&$whitespace_parser_instance->ParseMany($index,0,-1))
        {
            $instance->SetAssignment($assignment_field->GetValue());
            $instance->SetName($name_field->GetValue());
            $instance->SetType($type_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $assignment_field = new DeclarationAssignResult();
            $name_field = new NameResult();
            $type_field = new ValueTypeResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new DeclarationResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?DeclarationResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new DeclarationResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?DeclarationListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new DeclarationResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new DeclarationListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class DeclarationResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?Declaration $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?Declaration
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class DeclarationListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class Declaration {
    public function __construct() {
        $this->length_string = null;
        $this->assignment_field = null;
        $this->name_field = null;
        $this->type_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetAssignment(?DeclarationAssign $input_value): void
    {
        $this->assignment_field = $input_value;
    }

    public function GetAssignment(): ?DeclarationAssign
    {
        return $this->assignment_field;
    }

    public function SetName(?Name $input_value): void
    {
        $this->name_field = $input_value;
    }

    public function GetName(): ?Name
    {
        return $this->name_field;
    }

    public function SetType(?ValueType $input_value): void
    {
        $this->type_field = $input_value;
    }

    public function ReservedPrefixGetType(): ?ValueType
    {
        return $this->type_field;
    }

    private $length_string;
    private $assignment_field;
    private $name_field;
    private $type_field;
}

class AssignmentParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?AssignmentResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new Assignment();
        $l_value_field = new QualfiedNameResult();
        $r_value_field = new RValueResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$qualfied_name_parser_instance->ParseSingleSave($index,$l_value_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,'=')&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$r_value_parser_instance->ParseSingleSave($index,$r_value_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,';')&&$whitespace_parser_instance->ParseMany($index,0,-1))
        {
            $instance->SetLValue($l_value_field->GetValue());
            $instance->SetRValue($r_value_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $l_value_field = new QualfiedNameResult();
            $r_value_field = new RValueResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new AssignmentResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?AssignmentResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new AssignmentResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?AssignmentListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new AssignmentResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new AssignmentListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class AssignmentResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?Assignment $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?Assignment
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class AssignmentListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class Assignment {
    public function __construct() {
        $this->length_string = null;
        $this->l_value_field = null;
        $this->r_value_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetLValue(?QualfiedName $input_value): void
    {
        $this->l_value_field = $input_value;
    }

    public function GetLValue(): ?QualfiedName
    {
        return $this->l_value_field;
    }

    public function SetRValue(?RValue $input_value): void
    {
        $this->r_value_field = $input_value;
    }

    public function GetRValue(): ?RValue
    {
        return $this->r_value_field;
    }

    private $length_string;
    private $l_value_field;
    private $r_value_field;
}

class ReturnParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?ReturnResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new ReservedPrefixReturn();
        $r_value_field = new RValueResult();
        $rtn_field = new StringResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingleSave($index,'return',$rtn_field)&&$whitespace_parser_instance->ParseMany($index,1,-1)&&$r_value_parser_instance->ParseSingleSave($index,$r_value_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,';')&&$whitespace_parser_instance->ParseMany($index,0,-1))
        {
            $instance->SetRValue($r_value_field->GetValue());
            $instance->SetRtn($rtn_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $r_value_field = new RValueResult();
            $rtn_field = new StringResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new ReturnResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?ReturnResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new ReturnResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?ReturnListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new ReturnResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new ReturnListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class ReturnResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?ReservedPrefixReturn $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?ReservedPrefixReturn
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class ReturnListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class ReservedPrefixReturn {
    public function __construct() {
        $this->length_string = null;
        $this->r_value_field = null;
        $this->rtn_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetRValue(?RValue $input_value): void
    {
        $this->r_value_field = $input_value;
    }

    public function GetRValue(): ?RValue
    {
        return $this->r_value_field;
    }

    public function SetRtn(?ReservedPrefixString $input_value): void
    {
        $this->rtn_field = $input_value;
    }

    public function GetRtn(): ?ReservedPrefixString
    {
        return $this->rtn_field;
    }

    private $length_string;
    private $r_value_field;
    private $rtn_field;
}

class ElseTailParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?ElseTailResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new ElseTail();
        $code_block_field = new CodeBlockResult();
        $else_key_field = new StringResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingleSave($index,'else',$else_key_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$code_block_parser_instance->ParseSingleSave($index,$code_block_field)&&$whitespace_parser_instance->ParseMany($index,0,-1))
        {
            $instance->SetCodeBlock($code_block_field->GetValue());
            $instance->SetElseKey($else_key_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $code_block_field = new CodeBlockResult();
            $else_key_field = new StringResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new ElseTailResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?ElseTailResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new ElseTailResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?ElseTailListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new ElseTailResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new ElseTailListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class ElseTailResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?ElseTail $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?ElseTail
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class ElseTailListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class ElseTail {
    public function __construct() {
        $this->length_string = null;
        $this->code_block_field = null;
        $this->else_key_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetCodeBlock(?CodeBlock $input_value): void
    {
        $this->code_block_field = $input_value;
    }

    public function GetCodeBlock(): ?CodeBlock
    {
        return $this->code_block_field;
    }

    public function SetElseKey(?ReservedPrefixString $input_value): void
    {
        $this->else_key_field = $input_value;
    }

    public function GetElseKey(): ?ReservedPrefixString
    {
        return $this->else_key_field;
    }

    private $length_string;
    private $code_block_field;
    private $else_key_field;
}

class ConditionalParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?ConditionalResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new Conditional();
        $code_block_field = new CodeBlockResult();
        $conditional_key_field = new StringResult();
        $else_tail_field = new ElseTailResult();
        $r_value_field = new RValueResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingleSave($index,'if',$conditional_key_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,'(')&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$r_value_parser_instance->ParseSingleSave($index,$r_value_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,')')&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$code_block_parser_instance->ParseSingleSave($index,$code_block_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$else_tail_parser_instance->ParseOptionalSave($index,$else_tail_field))
        {
            $instance->SetCodeBlock($code_block_field->GetValue());
            $instance->SetConditionalKey($conditional_key_field->GetValue());
            $instance->SetElseTail($else_tail_field->GetValue());
            $instance->SetRValue($r_value_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $code_block_field = new CodeBlockResult();
            $conditional_key_field = new StringResult();
            $else_tail_field = new ElseTailResult();
            $r_value_field = new RValueResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new ConditionalResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?ConditionalResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new ConditionalResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?ConditionalListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new ConditionalResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new ConditionalListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class ConditionalResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?Conditional $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?Conditional
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class ConditionalListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class Conditional {
    public function __construct() {
        $this->length_string = null;
        $this->code_block_field = null;
        $this->conditional_key_field = null;
        $this->else_tail_field = null;
        $this->r_value_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetCodeBlock(?CodeBlock $input_value): void
    {
        $this->code_block_field = $input_value;
    }

    public function GetCodeBlock(): ?CodeBlock
    {
        return $this->code_block_field;
    }

    public function SetConditionalKey(?ReservedPrefixString $input_value): void
    {
        $this->conditional_key_field = $input_value;
    }

    public function GetConditionalKey(): ?ReservedPrefixString
    {
        return $this->conditional_key_field;
    }

    public function SetElseTail(?ElseTail $input_value): void
    {
        $this->else_tail_field = $input_value;
    }

    public function GetElseTail(): ?ElseTail
    {
        return $this->else_tail_field;
    }

    public function SetRValue(?RValue $input_value): void
    {
        $this->r_value_field = $input_value;
    }

    public function GetRValue(): ?RValue
    {
        return $this->r_value_field;
    }

    private $length_string;
    private $code_block_field;
    private $conditional_key_field;
    private $else_tail_field;
    private $r_value_field;
}

class LoopParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?LoopResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new Loop();
        $code_block_field = new CodeBlockResult();
        $loop_key_field = new StringResult();
        $r_value_field = new RValueResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingleSave($index,'while',$loop_key_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,'(')&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$r_value_parser_instance->ParseSingleSave($index,$r_value_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,')')&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$code_block_parser_instance->ParseSingleSave($index,$code_block_field)&&$whitespace_parser_instance->ParseMany($index,0,-1))
        {
            $instance->SetCodeBlock($code_block_field->GetValue());
            $instance->SetLoopKey($loop_key_field->GetValue());
            $instance->SetRValue($r_value_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $code_block_field = new CodeBlockResult();
            $loop_key_field = new StringResult();
            $r_value_field = new RValueResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new LoopResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?LoopResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new LoopResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?LoopListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new LoopResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new LoopListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class LoopResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?Loop $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?Loop
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class LoopListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class Loop {
    public function __construct() {
        $this->length_string = null;
        $this->code_block_field = null;
        $this->loop_key_field = null;
        $this->r_value_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetCodeBlock(?CodeBlock $input_value): void
    {
        $this->code_block_field = $input_value;
    }

    public function GetCodeBlock(): ?CodeBlock
    {
        return $this->code_block_field;
    }

    public function SetLoopKey(?ReservedPrefixString $input_value): void
    {
        $this->loop_key_field = $input_value;
    }

    public function GetLoopKey(): ?ReservedPrefixString
    {
        return $this->loop_key_field;
    }

    public function SetRValue(?RValue $input_value): void
    {
        $this->r_value_field = $input_value;
    }

    public function GetRValue(): ?RValue
    {
        return $this->r_value_field;
    }

    private $length_string;
    private $code_block_field;
    private $loop_key_field;
    private $r_value_field;
}

class CallParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?CallResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new Call();
        $function_chain_field = new QualfiedNameResult();
        $function_field = new NameResult();
        $parameters_field = new ParameterListResult();
        $variable_field = new NameResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$name_parser_instance->ParseSingleSave($index,$variable_field)&&$string_parser_instance->ParseSingle($index,'.')&&$name_parser_instance->ParseSingleSave($index,$function_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,'(')&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$parameter_list_parser_instance->ParseOptionalSave($index,$parameters_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,')')&&$whitespace_parser_instance->ParseMany($index,0,-1))
        {
            $instance->SetFunctionChain($function_chain_field->GetValue());
            $instance->SetFunction($function_field->GetValue());
            $instance->SetParameters($parameters_field->GetValue());
            $instance->SetVariable($variable_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $function_chain_field = new QualfiedNameResult();
            $function_field = new NameResult();
            $parameters_field = new ParameterListResult();
            $variable_field = new NameResult();
        }
        if (true&&$name_parser_instance->ParseSingleSave($index,$function_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,'(')&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$parameter_list_parser_instance->ParseOptionalSave($index,$parameters_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,')')&&$whitespace_parser_instance->ParseMany($index,0,-1))
        {
            $instance->SetFunctionChain($function_chain_field->GetValue());
            $instance->SetFunction($function_field->GetValue());
            $instance->SetParameters($parameters_field->GetValue());
            $instance->SetVariable($variable_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $function_chain_field = new QualfiedNameResult();
            $function_field = new NameResult();
            $parameters_field = new ParameterListResult();
            $variable_field = new NameResult();
        }
        if (true&&$qualfied_name_parser_instance->ParseSingleSave($index,$function_chain_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,'(')&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$parameter_list_parser_instance->ParseOptionalSave($index,$parameters_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,')')&&$whitespace_parser_instance->ParseMany($index,0,-1))
        {
            $instance->SetFunctionChain($function_chain_field->GetValue());
            $instance->SetFunction($function_field->GetValue());
            $instance->SetParameters($parameters_field->GetValue());
            $instance->SetVariable($variable_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $function_chain_field = new QualfiedNameResult();
            $function_field = new NameResult();
            $parameters_field = new ParameterListResult();
            $variable_field = new NameResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new CallResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?CallResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new CallResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?CallListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new CallResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new CallListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class CallResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?Call $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?Call
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class CallListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class Call {
    public function __construct() {
        $this->length_string = null;
        $this->function_chain_field = null;
        $this->function_field = null;
        $this->parameters_field = null;
        $this->variable_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetFunctionChain(?QualfiedName $input_value): void
    {
        $this->function_chain_field = $input_value;
    }

    public function GetFunctionChain(): ?QualfiedName
    {
        return $this->function_chain_field;
    }

    public function SetFunction(?Name $input_value): void
    {
        $this->function_field = $input_value;
    }

    public function GetFunction(): ?Name
    {
        return $this->function_field;
    }

    public function SetParameters(?ParameterList $input_value): void
    {
        $this->parameters_field = $input_value;
    }

    public function GetParameters(): ?ParameterList
    {
        return $this->parameters_field;
    }

    public function SetVariable(?Name $input_value): void
    {
        $this->variable_field = $input_value;
    }

    public function GetVariable(): ?Name
    {
        return $this->variable_field;
    }

    private $length_string;
    private $function_chain_field;
    private $function_field;
    private $parameters_field;
    private $variable_field;
}

class AllocateParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?AllocateResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new Allocate();
        $managed_type_field = new QualfiedNameResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,'new')&&$whitespace_parser_instance->ParseMany($index,1,-1)&&$qualfied_name_parser_instance->ParseSingleSave($index,$managed_type_field)&&$whitespace_parser_instance->ParseMany($index,0,-1))
        {
            $instance->SetManagedType($managed_type_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $managed_type_field = new QualfiedNameResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new AllocateResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?AllocateResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new AllocateResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?AllocateListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new AllocateResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new AllocateListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class AllocateResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?Allocate $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?Allocate
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class AllocateListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class Allocate {
    public function __construct() {
        $this->length_string = null;
        $this->managed_type_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetManagedType(?QualfiedName $input_value): void
    {
        $this->managed_type_field = $input_value;
    }

    public function GetManagedType(): ?QualfiedName
    {
        return $this->managed_type_field;
    }

    private $length_string;
    private $managed_type_field;
}

class InstructionParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?InstructionResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new Instruction();
        $assignment_field = new AssignmentResult();
        $call_field = new CallResult();
        $code_block_field = new CodeBlockResult();
        $comment_field = new CommentResult();
        $conditional_field = new ConditionalResult();
        $declaration_field = new DeclarationResult();
        $loop_field = new LoopResult();
        $rtn_field = new ReturnResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$comment_parser_instance->ParseOptionalSave($index,$comment_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$code_block_parser_instance->ParseSingleSave($index,$code_block_field))
        {
            $instance->SetAssignment($assignment_field->GetValue());
            $instance->SetCall($call_field->GetValue());
            $instance->SetCodeBlock($code_block_field->GetValue());
            $instance->SetComment($comment_field->GetValue());
            $instance->SetConditional($conditional_field->GetValue());
            $instance->SetDeclaration($declaration_field->GetValue());
            $instance->SetLoop($loop_field->GetValue());
            $instance->SetRtn($rtn_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $assignment_field = new AssignmentResult();
            $call_field = new CallResult();
            $code_block_field = new CodeBlockResult();
            $comment_field = new CommentResult();
            $conditional_field = new ConditionalResult();
            $declaration_field = new DeclarationResult();
            $loop_field = new LoopResult();
            $rtn_field = new ReturnResult();
        }
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$comment_parser_instance->ParseOptionalSave($index,$comment_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$return_parser_instance->ParseSingleSave($index,$rtn_field))
        {
            $instance->SetAssignment($assignment_field->GetValue());
            $instance->SetCall($call_field->GetValue());
            $instance->SetCodeBlock($code_block_field->GetValue());
            $instance->SetComment($comment_field->GetValue());
            $instance->SetConditional($conditional_field->GetValue());
            $instance->SetDeclaration($declaration_field->GetValue());
            $instance->SetLoop($loop_field->GetValue());
            $instance->SetRtn($rtn_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $assignment_field = new AssignmentResult();
            $call_field = new CallResult();
            $code_block_field = new CodeBlockResult();
            $comment_field = new CommentResult();
            $conditional_field = new ConditionalResult();
            $declaration_field = new DeclarationResult();
            $loop_field = new LoopResult();
            $rtn_field = new ReturnResult();
        }
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$comment_parser_instance->ParseOptionalSave($index,$comment_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$declaration_parser_instance->ParseSingleSave($index,$declaration_field))
        {
            $instance->SetAssignment($assignment_field->GetValue());
            $instance->SetCall($call_field->GetValue());
            $instance->SetCodeBlock($code_block_field->GetValue());
            $instance->SetComment($comment_field->GetValue());
            $instance->SetConditional($conditional_field->GetValue());
            $instance->SetDeclaration($declaration_field->GetValue());
            $instance->SetLoop($loop_field->GetValue());
            $instance->SetRtn($rtn_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $assignment_field = new AssignmentResult();
            $call_field = new CallResult();
            $code_block_field = new CodeBlockResult();
            $comment_field = new CommentResult();
            $conditional_field = new ConditionalResult();
            $declaration_field = new DeclarationResult();
            $loop_field = new LoopResult();
            $rtn_field = new ReturnResult();
        }
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$comment_parser_instance->ParseOptionalSave($index,$comment_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$assignment_parser_instance->ParseSingleSave($index,$assignment_field))
        {
            $instance->SetAssignment($assignment_field->GetValue());
            $instance->SetCall($call_field->GetValue());
            $instance->SetCodeBlock($code_block_field->GetValue());
            $instance->SetComment($comment_field->GetValue());
            $instance->SetConditional($conditional_field->GetValue());
            $instance->SetDeclaration($declaration_field->GetValue());
            $instance->SetLoop($loop_field->GetValue());
            $instance->SetRtn($rtn_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $assignment_field = new AssignmentResult();
            $call_field = new CallResult();
            $code_block_field = new CodeBlockResult();
            $comment_field = new CommentResult();
            $conditional_field = new ConditionalResult();
            $declaration_field = new DeclarationResult();
            $loop_field = new LoopResult();
            $rtn_field = new ReturnResult();
        }
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$comment_parser_instance->ParseOptionalSave($index,$comment_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$call_parser_instance->ParseSingleSave($index,$call_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,';')&&$whitespace_parser_instance->ParseMany($index,0,-1))
        {
            $instance->SetAssignment($assignment_field->GetValue());
            $instance->SetCall($call_field->GetValue());
            $instance->SetCodeBlock($code_block_field->GetValue());
            $instance->SetComment($comment_field->GetValue());
            $instance->SetConditional($conditional_field->GetValue());
            $instance->SetDeclaration($declaration_field->GetValue());
            $instance->SetLoop($loop_field->GetValue());
            $instance->SetRtn($rtn_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $assignment_field = new AssignmentResult();
            $call_field = new CallResult();
            $code_block_field = new CodeBlockResult();
            $comment_field = new CommentResult();
            $conditional_field = new ConditionalResult();
            $declaration_field = new DeclarationResult();
            $loop_field = new LoopResult();
            $rtn_field = new ReturnResult();
        }
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$comment_parser_instance->ParseOptionalSave($index,$comment_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$conditional_parser_instance->ParseSingleSave($index,$conditional_field))
        {
            $instance->SetAssignment($assignment_field->GetValue());
            $instance->SetCall($call_field->GetValue());
            $instance->SetCodeBlock($code_block_field->GetValue());
            $instance->SetComment($comment_field->GetValue());
            $instance->SetConditional($conditional_field->GetValue());
            $instance->SetDeclaration($declaration_field->GetValue());
            $instance->SetLoop($loop_field->GetValue());
            $instance->SetRtn($rtn_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $assignment_field = new AssignmentResult();
            $call_field = new CallResult();
            $code_block_field = new CodeBlockResult();
            $comment_field = new CommentResult();
            $conditional_field = new ConditionalResult();
            $declaration_field = new DeclarationResult();
            $loop_field = new LoopResult();
            $rtn_field = new ReturnResult();
        }
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$comment_parser_instance->ParseOptionalSave($index,$comment_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$loop_parser_instance->ParseSingleSave($index,$loop_field))
        {
            $instance->SetAssignment($assignment_field->GetValue());
            $instance->SetCall($call_field->GetValue());
            $instance->SetCodeBlock($code_block_field->GetValue());
            $instance->SetComment($comment_field->GetValue());
            $instance->SetConditional($conditional_field->GetValue());
            $instance->SetDeclaration($declaration_field->GetValue());
            $instance->SetLoop($loop_field->GetValue());
            $instance->SetRtn($rtn_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $assignment_field = new AssignmentResult();
            $call_field = new CallResult();
            $code_block_field = new CodeBlockResult();
            $comment_field = new CommentResult();
            $conditional_field = new ConditionalResult();
            $declaration_field = new DeclarationResult();
            $loop_field = new LoopResult();
            $rtn_field = new ReturnResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new InstructionResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?InstructionResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new InstructionResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?InstructionListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new InstructionResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new InstructionListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class InstructionResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?Instruction $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?Instruction
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class InstructionListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class Instruction {
    public function __construct() {
        $this->length_string = null;
        $this->assignment_field = null;
        $this->call_field = null;
        $this->code_block_field = null;
        $this->comment_field = null;
        $this->conditional_field = null;
        $this->declaration_field = null;
        $this->loop_field = null;
        $this->rtn_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetAssignment(?Assignment $input_value): void
    {
        $this->assignment_field = $input_value;
    }

    public function GetAssignment(): ?Assignment
    {
        return $this->assignment_field;
    }

    public function SetCall(?Call $input_value): void
    {
        $this->call_field = $input_value;
    }

    public function GetCall(): ?Call
    {
        return $this->call_field;
    }

    public function SetCodeBlock(?CodeBlock $input_value): void
    {
        $this->code_block_field = $input_value;
    }

    public function GetCodeBlock(): ?CodeBlock
    {
        return $this->code_block_field;
    }

    public function SetComment(?Comment $input_value): void
    {
        $this->comment_field = $input_value;
    }

    public function GetComment(): ?Comment
    {
        return $this->comment_field;
    }

    public function SetConditional(?Conditional $input_value): void
    {
        $this->conditional_field = $input_value;
    }

    public function GetConditional(): ?Conditional
    {
        return $this->conditional_field;
    }

    public function SetDeclaration(?Declaration $input_value): void
    {
        $this->declaration_field = $input_value;
    }

    public function GetDeclaration(): ?Declaration
    {
        return $this->declaration_field;
    }

    public function SetLoop(?Loop $input_value): void
    {
        $this->loop_field = $input_value;
    }

    public function GetLoop(): ?Loop
    {
        return $this->loop_field;
    }

    public function SetRtn(?ReservedPrefixReturn $input_value): void
    {
        $this->rtn_field = $input_value;
    }

    public function GetRtn(): ?ReservedPrefixReturn
    {
        return $this->rtn_field;
    }

    private $length_string;
    private $assignment_field;
    private $call_field;
    private $code_block_field;
    private $comment_field;
    private $conditional_field;
    private $declaration_field;
    private $loop_field;
    private $rtn_field;
}

class RValueSingleParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?RValueSingleResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new RValueSingle();
        $allocate_field = new AllocateResult();
        $boolean_literal_field = new BooleanResult();
        $byte_literal_field = new ByteResult();
        $call_field = new CallResult();
        $decimal_literal_field = new DecimalResult();
        $integer_literal_field = new NumberResult();
        $string_literal_field = new LiteralResult();
        $unary_operator_field = new UnaryOperatorResult();
        $variable_field = new QualfiedNameResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$unary_operator_parser_instance->ParseOptionalSave($index,$unary_operator_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$call_parser_instance->ParseSingleSave($index,$call_field))
        {
            $instance->SetAllocate($allocate_field->GetValue());
            $instance->SetBooleanLiteral($boolean_literal_field->GetValue());
            $instance->SetByteLiteral($byte_literal_field->GetValue());
            $instance->SetCall($call_field->GetValue());
            $instance->SetDecimalLiteral($decimal_literal_field->GetValue());
            $instance->SetIntegerLiteral($integer_literal_field->GetValue());
            $instance->SetStringLiteral($string_literal_field->GetValue());
            $instance->SetUnaryOperator($unary_operator_field->GetValue());
            $instance->SetVariable($variable_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $allocate_field = new AllocateResult();
            $boolean_literal_field = new BooleanResult();
            $byte_literal_field = new ByteResult();
            $call_field = new CallResult();
            $decimal_literal_field = new DecimalResult();
            $integer_literal_field = new NumberResult();
            $string_literal_field = new LiteralResult();
            $unary_operator_field = new UnaryOperatorResult();
            $variable_field = new QualfiedNameResult();
        }
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$unary_operator_parser_instance->ParseOptionalSave($index,$unary_operator_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$allocate_parser_instance->ParseSingleSave($index,$allocate_field))
        {
            $instance->SetAllocate($allocate_field->GetValue());
            $instance->SetBooleanLiteral($boolean_literal_field->GetValue());
            $instance->SetByteLiteral($byte_literal_field->GetValue());
            $instance->SetCall($call_field->GetValue());
            $instance->SetDecimalLiteral($decimal_literal_field->GetValue());
            $instance->SetIntegerLiteral($integer_literal_field->GetValue());
            $instance->SetStringLiteral($string_literal_field->GetValue());
            $instance->SetUnaryOperator($unary_operator_field->GetValue());
            $instance->SetVariable($variable_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $allocate_field = new AllocateResult();
            $boolean_literal_field = new BooleanResult();
            $byte_literal_field = new ByteResult();
            $call_field = new CallResult();
            $decimal_literal_field = new DecimalResult();
            $integer_literal_field = new NumberResult();
            $string_literal_field = new LiteralResult();
            $unary_operator_field = new UnaryOperatorResult();
            $variable_field = new QualfiedNameResult();
        }
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$unary_operator_parser_instance->ParseOptionalSave($index,$unary_operator_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$byte_parser_instance->ParseSingleSave($index,$byte_literal_field))
        {
            $instance->SetAllocate($allocate_field->GetValue());
            $instance->SetBooleanLiteral($boolean_literal_field->GetValue());
            $instance->SetByteLiteral($byte_literal_field->GetValue());
            $instance->SetCall($call_field->GetValue());
            $instance->SetDecimalLiteral($decimal_literal_field->GetValue());
            $instance->SetIntegerLiteral($integer_literal_field->GetValue());
            $instance->SetStringLiteral($string_literal_field->GetValue());
            $instance->SetUnaryOperator($unary_operator_field->GetValue());
            $instance->SetVariable($variable_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $allocate_field = new AllocateResult();
            $boolean_literal_field = new BooleanResult();
            $byte_literal_field = new ByteResult();
            $call_field = new CallResult();
            $decimal_literal_field = new DecimalResult();
            $integer_literal_field = new NumberResult();
            $string_literal_field = new LiteralResult();
            $unary_operator_field = new UnaryOperatorResult();
            $variable_field = new QualfiedNameResult();
        }
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$unary_operator_parser_instance->ParseOptionalSave($index,$unary_operator_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$decimal_parser_instance->ParseSingleSave($index,$decimal_literal_field))
        {
            $instance->SetAllocate($allocate_field->GetValue());
            $instance->SetBooleanLiteral($boolean_literal_field->GetValue());
            $instance->SetByteLiteral($byte_literal_field->GetValue());
            $instance->SetCall($call_field->GetValue());
            $instance->SetDecimalLiteral($decimal_literal_field->GetValue());
            $instance->SetIntegerLiteral($integer_literal_field->GetValue());
            $instance->SetStringLiteral($string_literal_field->GetValue());
            $instance->SetUnaryOperator($unary_operator_field->GetValue());
            $instance->SetVariable($variable_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $allocate_field = new AllocateResult();
            $boolean_literal_field = new BooleanResult();
            $byte_literal_field = new ByteResult();
            $call_field = new CallResult();
            $decimal_literal_field = new DecimalResult();
            $integer_literal_field = new NumberResult();
            $string_literal_field = new LiteralResult();
            $unary_operator_field = new UnaryOperatorResult();
            $variable_field = new QualfiedNameResult();
        }
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$unary_operator_parser_instance->ParseOptionalSave($index,$unary_operator_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$number_parser_instance->ParseSingleSave($index,$integer_literal_field))
        {
            $instance->SetAllocate($allocate_field->GetValue());
            $instance->SetBooleanLiteral($boolean_literal_field->GetValue());
            $instance->SetByteLiteral($byte_literal_field->GetValue());
            $instance->SetCall($call_field->GetValue());
            $instance->SetDecimalLiteral($decimal_literal_field->GetValue());
            $instance->SetIntegerLiteral($integer_literal_field->GetValue());
            $instance->SetStringLiteral($string_literal_field->GetValue());
            $instance->SetUnaryOperator($unary_operator_field->GetValue());
            $instance->SetVariable($variable_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $allocate_field = new AllocateResult();
            $boolean_literal_field = new BooleanResult();
            $byte_literal_field = new ByteResult();
            $call_field = new CallResult();
            $decimal_literal_field = new DecimalResult();
            $integer_literal_field = new NumberResult();
            $string_literal_field = new LiteralResult();
            $unary_operator_field = new UnaryOperatorResult();
            $variable_field = new QualfiedNameResult();
        }
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$unary_operator_parser_instance->ParseOptionalSave($index,$unary_operator_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$boolean_parser_instance->ParseSingleSave($index,$boolean_literal_field))
        {
            $instance->SetAllocate($allocate_field->GetValue());
            $instance->SetBooleanLiteral($boolean_literal_field->GetValue());
            $instance->SetByteLiteral($byte_literal_field->GetValue());
            $instance->SetCall($call_field->GetValue());
            $instance->SetDecimalLiteral($decimal_literal_field->GetValue());
            $instance->SetIntegerLiteral($integer_literal_field->GetValue());
            $instance->SetStringLiteral($string_literal_field->GetValue());
            $instance->SetUnaryOperator($unary_operator_field->GetValue());
            $instance->SetVariable($variable_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $allocate_field = new AllocateResult();
            $boolean_literal_field = new BooleanResult();
            $byte_literal_field = new ByteResult();
            $call_field = new CallResult();
            $decimal_literal_field = new DecimalResult();
            $integer_literal_field = new NumberResult();
            $string_literal_field = new LiteralResult();
            $unary_operator_field = new UnaryOperatorResult();
            $variable_field = new QualfiedNameResult();
        }
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$unary_operator_parser_instance->ParseOptionalSave($index,$unary_operator_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$qualfied_name_parser_instance->ParseSingleSave($index,$variable_field))
        {
            $instance->SetAllocate($allocate_field->GetValue());
            $instance->SetBooleanLiteral($boolean_literal_field->GetValue());
            $instance->SetByteLiteral($byte_literal_field->GetValue());
            $instance->SetCall($call_field->GetValue());
            $instance->SetDecimalLiteral($decimal_literal_field->GetValue());
            $instance->SetIntegerLiteral($integer_literal_field->GetValue());
            $instance->SetStringLiteral($string_literal_field->GetValue());
            $instance->SetUnaryOperator($unary_operator_field->GetValue());
            $instance->SetVariable($variable_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $allocate_field = new AllocateResult();
            $boolean_literal_field = new BooleanResult();
            $byte_literal_field = new ByteResult();
            $call_field = new CallResult();
            $decimal_literal_field = new DecimalResult();
            $integer_literal_field = new NumberResult();
            $string_literal_field = new LiteralResult();
            $unary_operator_field = new UnaryOperatorResult();
            $variable_field = new QualfiedNameResult();
        }
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$unary_operator_parser_instance->ParseOptionalSave($index,$unary_operator_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$string_parser_instance->ParseSingle($index,'"')&&$literal_parser_instance->ParseSingleSave($index,$string_literal_field)&&$string_parser_instance->ParseSingle($index,'"'))
        {
            $instance->SetAllocate($allocate_field->GetValue());
            $instance->SetBooleanLiteral($boolean_literal_field->GetValue());
            $instance->SetByteLiteral($byte_literal_field->GetValue());
            $instance->SetCall($call_field->GetValue());
            $instance->SetDecimalLiteral($decimal_literal_field->GetValue());
            $instance->SetIntegerLiteral($integer_literal_field->GetValue());
            $instance->SetStringLiteral($string_literal_field->GetValue());
            $instance->SetUnaryOperator($unary_operator_field->GetValue());
            $instance->SetVariable($variable_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $allocate_field = new AllocateResult();
            $boolean_literal_field = new BooleanResult();
            $byte_literal_field = new ByteResult();
            $call_field = new CallResult();
            $decimal_literal_field = new DecimalResult();
            $integer_literal_field = new NumberResult();
            $string_literal_field = new LiteralResult();
            $unary_operator_field = new UnaryOperatorResult();
            $variable_field = new QualfiedNameResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new RValueSingleResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?RValueSingleResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new RValueSingleResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?RValueSingleListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new RValueSingleResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new RValueSingleListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class RValueSingleResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?RValueSingle $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?RValueSingle
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class RValueSingleListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class RValueSingle {
    public function __construct() {
        $this->length_string = null;
        $this->allocate_field = null;
        $this->boolean_literal_field = null;
        $this->byte_literal_field = null;
        $this->call_field = null;
        $this->decimal_literal_field = null;
        $this->integer_literal_field = null;
        $this->string_literal_field = null;
        $this->unary_operator_field = null;
        $this->variable_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetAllocate(?Allocate $input_value): void
    {
        $this->allocate_field = $input_value;
    }

    public function GetAllocate(): ?Allocate
    {
        return $this->allocate_field;
    }

    public function SetBooleanLiteral(?Boolean $input_value): void
    {
        $this->boolean_literal_field = $input_value;
    }

    public function GetBooleanLiteral(): ?Boolean
    {
        return $this->boolean_literal_field;
    }

    public function SetByteLiteral(?Byte $input_value): void
    {
        $this->byte_literal_field = $input_value;
    }

    public function GetByteLiteral(): ?Byte
    {
        return $this->byte_literal_field;
    }

    public function SetCall(?Call $input_value): void
    {
        $this->call_field = $input_value;
    }

    public function GetCall(): ?Call
    {
        return $this->call_field;
    }

    public function SetDecimalLiteral(?Decimal $input_value): void
    {
        $this->decimal_literal_field = $input_value;
    }

    public function GetDecimalLiteral(): ?Decimal
    {
        return $this->decimal_literal_field;
    }

    public function SetIntegerLiteral(?Number $input_value): void
    {
        $this->integer_literal_field = $input_value;
    }

    public function GetIntegerLiteral(): ?Number
    {
        return $this->integer_literal_field;
    }

    public function SetStringLiteral(?Literal $input_value): void
    {
        $this->string_literal_field = $input_value;
    }

    public function GetStringLiteral(): ?Literal
    {
        return $this->string_literal_field;
    }

    public function SetUnaryOperator(?UnaryOperator $input_value): void
    {
        $this->unary_operator_field = $input_value;
    }

    public function GetUnaryOperator(): ?UnaryOperator
    {
        return $this->unary_operator_field;
    }

    public function SetVariable(?QualfiedName $input_value): void
    {
        $this->variable_field = $input_value;
    }

    public function GetVariable(): ?QualfiedName
    {
        return $this->variable_field;
    }

    private $length_string;
    private $allocate_field;
    private $boolean_literal_field;
    private $byte_literal_field;
    private $call_field;
    private $decimal_literal_field;
    private $integer_literal_field;
    private $string_literal_field;
    private $unary_operator_field;
    private $variable_field;
}

class RValueTailParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?RValueTailResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new RValueTail();
        $binary_operator_field = new BinaryOperatorResult();
        $tail_field = new RValueTailResult();
        $value_field = new RValueSingleResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$binary_operator_parser_instance->ParseSingleSave($index,$binary_operator_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$r_value_single_parser_instance->ParseSingleSave($index,$value_field)&&$whitespace_parser_instance->ParseMany($index,0,-1)&&$r_value_tail_parser_instance->ParseOptionalSave($index,$tail_field))
        {
            $instance->SetBinaryOperator($binary_operator_field->GetValue());
            $instance->SetTail($tail_field->GetValue());
            $instance->SetValue($value_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $binary_operator_field = new BinaryOperatorResult();
            $tail_field = new RValueTailResult();
            $value_field = new RValueSingleResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new RValueTailResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?RValueTailResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new RValueTailResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?RValueTailListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new RValueTailResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new RValueTailListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class RValueTailResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?RValueTail $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?RValueTail
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class RValueTailListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class RValueTail {
    public function __construct() {
        $this->length_string = null;
        $this->binary_operator_field = null;
        $this->tail_field = null;
        $this->value_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetBinaryOperator(?BinaryOperator $input_value): void
    {
        $this->binary_operator_field = $input_value;
    }

    public function GetBinaryOperator(): ?BinaryOperator
    {
        return $this->binary_operator_field;
    }

    public function SetTail(?RValueTail $input_value): void
    {
        $this->tail_field = $input_value;
    }

    public function GetTail(): ?RValueTail
    {
        return $this->tail_field;
    }

    public function SetValue(?RValueSingle $input_value): void
    {
        $this->value_field = $input_value;
    }

    public function GetValue(): ?RValueSingle
    {
        return $this->value_field;
    }

    private $length_string;
    private $binary_operator_field;
    private $tail_field;
    private $value_field;
}

class RValueParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?RValueResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new RValue();
        $tail_field = new RValueTailResult();
        $value_field = new RValueSingleResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$r_value_single_parser_instance->ParseSingleSave($index,$value_field)&&$r_value_tail_parser_instance->ParseOptionalSave($index,$tail_field))
        {
            $instance->SetTail($tail_field->GetValue());
            $instance->SetValue($value_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $tail_field = new RValueTailResult();
            $value_field = new RValueSingleResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new RValueResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?RValueResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new RValueResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?RValueListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new RValueResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new RValueListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class RValueResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?RValue $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?RValue
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class RValueListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class RValue {
    public function __construct() {
        $this->length_string = null;
        $this->tail_field = null;
        $this->value_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetTail(?RValueTail $input_value): void
    {
        $this->tail_field = $input_value;
    }

    public function GetTail(): ?RValueTail
    {
        return $this->tail_field;
    }

    public function SetValue(?RValueSingle $input_value): void
    {
        $this->value_field = $input_value;
    }

    public function GetValue(): ?RValueSingle
    {
        return $this->value_field;
    }

    private $length_string;
    private $tail_field;
    private $value_field;
}

class BinaryOperatorParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?BinaryOperatorResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new BinaryOperator();
        $addition_field = new StringResult();
        $and_op_field = new StringResult();
        $equality_field = new StringResult();
        $greater_than_eq_field = new StringResult();
        $greater_than_field = new StringResult();
        $less_than_eq_field = new StringResult();
        $less_than_field = new StringResult();
        $not_equality_field = new StringResult();
        $or_op_field = new StringResult();
        $subtraction_field = new StringResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$string_parser_instance->ParseSingleSave($index,'+',$addition_field))
        {
            $instance->SetAddition($addition_field->GetValue());
            $instance->SetAndOp($and_op_field->GetValue());
            $instance->SetEquality($equality_field->GetValue());
            $instance->SetGreaterThanEq($greater_than_eq_field->GetValue());
            $instance->SetGreaterThan($greater_than_field->GetValue());
            $instance->SetLessThanEq($less_than_eq_field->GetValue());
            $instance->SetLessThan($less_than_field->GetValue());
            $instance->SetNotEquality($not_equality_field->GetValue());
            $instance->SetOrOp($or_op_field->GetValue());
            $instance->SetSubtraction($subtraction_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $addition_field = new StringResult();
            $and_op_field = new StringResult();
            $equality_field = new StringResult();
            $greater_than_eq_field = new StringResult();
            $greater_than_field = new StringResult();
            $less_than_eq_field = new StringResult();
            $less_than_field = new StringResult();
            $not_equality_field = new StringResult();
            $or_op_field = new StringResult();
            $subtraction_field = new StringResult();
        }
        if (true&&$string_parser_instance->ParseSingleSave($index,'-',$subtraction_field))
        {
            $instance->SetAddition($addition_field->GetValue());
            $instance->SetAndOp($and_op_field->GetValue());
            $instance->SetEquality($equality_field->GetValue());
            $instance->SetGreaterThanEq($greater_than_eq_field->GetValue());
            $instance->SetGreaterThan($greater_than_field->GetValue());
            $instance->SetLessThanEq($less_than_eq_field->GetValue());
            $instance->SetLessThan($less_than_field->GetValue());
            $instance->SetNotEquality($not_equality_field->GetValue());
            $instance->SetOrOp($or_op_field->GetValue());
            $instance->SetSubtraction($subtraction_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $addition_field = new StringResult();
            $and_op_field = new StringResult();
            $equality_field = new StringResult();
            $greater_than_eq_field = new StringResult();
            $greater_than_field = new StringResult();
            $less_than_eq_field = new StringResult();
            $less_than_field = new StringResult();
            $not_equality_field = new StringResult();
            $or_op_field = new StringResult();
            $subtraction_field = new StringResult();
        }
        if (true&&$string_parser_instance->ParseSingleSave($index,'<=',$less_than_eq_field))
        {
            $instance->SetAddition($addition_field->GetValue());
            $instance->SetAndOp($and_op_field->GetValue());
            $instance->SetEquality($equality_field->GetValue());
            $instance->SetGreaterThanEq($greater_than_eq_field->GetValue());
            $instance->SetGreaterThan($greater_than_field->GetValue());
            $instance->SetLessThanEq($less_than_eq_field->GetValue());
            $instance->SetLessThan($less_than_field->GetValue());
            $instance->SetNotEquality($not_equality_field->GetValue());
            $instance->SetOrOp($or_op_field->GetValue());
            $instance->SetSubtraction($subtraction_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $addition_field = new StringResult();
            $and_op_field = new StringResult();
            $equality_field = new StringResult();
            $greater_than_eq_field = new StringResult();
            $greater_than_field = new StringResult();
            $less_than_eq_field = new StringResult();
            $less_than_field = new StringResult();
            $not_equality_field = new StringResult();
            $or_op_field = new StringResult();
            $subtraction_field = new StringResult();
        }
        if (true&&$string_parser_instance->ParseSingleSave($index,'>=',$greater_than_eq_field))
        {
            $instance->SetAddition($addition_field->GetValue());
            $instance->SetAndOp($and_op_field->GetValue());
            $instance->SetEquality($equality_field->GetValue());
            $instance->SetGreaterThanEq($greater_than_eq_field->GetValue());
            $instance->SetGreaterThan($greater_than_field->GetValue());
            $instance->SetLessThanEq($less_than_eq_field->GetValue());
            $instance->SetLessThan($less_than_field->GetValue());
            $instance->SetNotEquality($not_equality_field->GetValue());
            $instance->SetOrOp($or_op_field->GetValue());
            $instance->SetSubtraction($subtraction_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $addition_field = new StringResult();
            $and_op_field = new StringResult();
            $equality_field = new StringResult();
            $greater_than_eq_field = new StringResult();
            $greater_than_field = new StringResult();
            $less_than_eq_field = new StringResult();
            $less_than_field = new StringResult();
            $not_equality_field = new StringResult();
            $or_op_field = new StringResult();
            $subtraction_field = new StringResult();
        }
        if (true&&$string_parser_instance->ParseSingleSave($index,'==',$equality_field))
        {
            $instance->SetAddition($addition_field->GetValue());
            $instance->SetAndOp($and_op_field->GetValue());
            $instance->SetEquality($equality_field->GetValue());
            $instance->SetGreaterThanEq($greater_than_eq_field->GetValue());
            $instance->SetGreaterThan($greater_than_field->GetValue());
            $instance->SetLessThanEq($less_than_eq_field->GetValue());
            $instance->SetLessThan($less_than_field->GetValue());
            $instance->SetNotEquality($not_equality_field->GetValue());
            $instance->SetOrOp($or_op_field->GetValue());
            $instance->SetSubtraction($subtraction_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $addition_field = new StringResult();
            $and_op_field = new StringResult();
            $equality_field = new StringResult();
            $greater_than_eq_field = new StringResult();
            $greater_than_field = new StringResult();
            $less_than_eq_field = new StringResult();
            $less_than_field = new StringResult();
            $not_equality_field = new StringResult();
            $or_op_field = new StringResult();
            $subtraction_field = new StringResult();
        }
        if (true&&$string_parser_instance->ParseSingleSave($index,'!=',$not_equality_field))
        {
            $instance->SetAddition($addition_field->GetValue());
            $instance->SetAndOp($and_op_field->GetValue());
            $instance->SetEquality($equality_field->GetValue());
            $instance->SetGreaterThanEq($greater_than_eq_field->GetValue());
            $instance->SetGreaterThan($greater_than_field->GetValue());
            $instance->SetLessThanEq($less_than_eq_field->GetValue());
            $instance->SetLessThan($less_than_field->GetValue());
            $instance->SetNotEquality($not_equality_field->GetValue());
            $instance->SetOrOp($or_op_field->GetValue());
            $instance->SetSubtraction($subtraction_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $addition_field = new StringResult();
            $and_op_field = new StringResult();
            $equality_field = new StringResult();
            $greater_than_eq_field = new StringResult();
            $greater_than_field = new StringResult();
            $less_than_eq_field = new StringResult();
            $less_than_field = new StringResult();
            $not_equality_field = new StringResult();
            $or_op_field = new StringResult();
            $subtraction_field = new StringResult();
        }
        if (true&&$string_parser_instance->ParseSingleSave($index,'<',$less_than_field))
        {
            $instance->SetAddition($addition_field->GetValue());
            $instance->SetAndOp($and_op_field->GetValue());
            $instance->SetEquality($equality_field->GetValue());
            $instance->SetGreaterThanEq($greater_than_eq_field->GetValue());
            $instance->SetGreaterThan($greater_than_field->GetValue());
            $instance->SetLessThanEq($less_than_eq_field->GetValue());
            $instance->SetLessThan($less_than_field->GetValue());
            $instance->SetNotEquality($not_equality_field->GetValue());
            $instance->SetOrOp($or_op_field->GetValue());
            $instance->SetSubtraction($subtraction_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $addition_field = new StringResult();
            $and_op_field = new StringResult();
            $equality_field = new StringResult();
            $greater_than_eq_field = new StringResult();
            $greater_than_field = new StringResult();
            $less_than_eq_field = new StringResult();
            $less_than_field = new StringResult();
            $not_equality_field = new StringResult();
            $or_op_field = new StringResult();
            $subtraction_field = new StringResult();
        }
        if (true&&$string_parser_instance->ParseSingleSave($index,'>',$greater_than_field))
        {
            $instance->SetAddition($addition_field->GetValue());
            $instance->SetAndOp($and_op_field->GetValue());
            $instance->SetEquality($equality_field->GetValue());
            $instance->SetGreaterThanEq($greater_than_eq_field->GetValue());
            $instance->SetGreaterThan($greater_than_field->GetValue());
            $instance->SetLessThanEq($less_than_eq_field->GetValue());
            $instance->SetLessThan($less_than_field->GetValue());
            $instance->SetNotEquality($not_equality_field->GetValue());
            $instance->SetOrOp($or_op_field->GetValue());
            $instance->SetSubtraction($subtraction_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $addition_field = new StringResult();
            $and_op_field = new StringResult();
            $equality_field = new StringResult();
            $greater_than_eq_field = new StringResult();
            $greater_than_field = new StringResult();
            $less_than_eq_field = new StringResult();
            $less_than_field = new StringResult();
            $not_equality_field = new StringResult();
            $or_op_field = new StringResult();
            $subtraction_field = new StringResult();
        }
        if (true&&$string_parser_instance->ParseSingleSave($index,'||',$or_op_field))
        {
            $instance->SetAddition($addition_field->GetValue());
            $instance->SetAndOp($and_op_field->GetValue());
            $instance->SetEquality($equality_field->GetValue());
            $instance->SetGreaterThanEq($greater_than_eq_field->GetValue());
            $instance->SetGreaterThan($greater_than_field->GetValue());
            $instance->SetLessThanEq($less_than_eq_field->GetValue());
            $instance->SetLessThan($less_than_field->GetValue());
            $instance->SetNotEquality($not_equality_field->GetValue());
            $instance->SetOrOp($or_op_field->GetValue());
            $instance->SetSubtraction($subtraction_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $addition_field = new StringResult();
            $and_op_field = new StringResult();
            $equality_field = new StringResult();
            $greater_than_eq_field = new StringResult();
            $greater_than_field = new StringResult();
            $less_than_eq_field = new StringResult();
            $less_than_field = new StringResult();
            $not_equality_field = new StringResult();
            $or_op_field = new StringResult();
            $subtraction_field = new StringResult();
        }
        if (true&&$string_parser_instance->ParseSingleSave($index,'&&',$and_op_field))
        {
            $instance->SetAddition($addition_field->GetValue());
            $instance->SetAndOp($and_op_field->GetValue());
            $instance->SetEquality($equality_field->GetValue());
            $instance->SetGreaterThanEq($greater_than_eq_field->GetValue());
            $instance->SetGreaterThan($greater_than_field->GetValue());
            $instance->SetLessThanEq($less_than_eq_field->GetValue());
            $instance->SetLessThan($less_than_field->GetValue());
            $instance->SetNotEquality($not_equality_field->GetValue());
            $instance->SetOrOp($or_op_field->GetValue());
            $instance->SetSubtraction($subtraction_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $addition_field = new StringResult();
            $and_op_field = new StringResult();
            $equality_field = new StringResult();
            $greater_than_eq_field = new StringResult();
            $greater_than_field = new StringResult();
            $less_than_eq_field = new StringResult();
            $less_than_field = new StringResult();
            $not_equality_field = new StringResult();
            $or_op_field = new StringResult();
            $subtraction_field = new StringResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new BinaryOperatorResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?BinaryOperatorResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new BinaryOperatorResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?BinaryOperatorListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new BinaryOperatorResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new BinaryOperatorListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class BinaryOperatorResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?BinaryOperator $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?BinaryOperator
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class BinaryOperatorListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class BinaryOperator {
    public function __construct() {
        $this->length_string = null;
        $this->addition_field = null;
        $this->and_op_field = null;
        $this->equality_field = null;
        $this->greater_than_eq_field = null;
        $this->greater_than_field = null;
        $this->less_than_eq_field = null;
        $this->less_than_field = null;
        $this->not_equality_field = null;
        $this->or_op_field = null;
        $this->subtraction_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetAddition(?ReservedPrefixString $input_value): void
    {
        $this->addition_field = $input_value;
    }

    public function GetAddition(): ?ReservedPrefixString
    {
        return $this->addition_field;
    }

    public function SetAndOp(?ReservedPrefixString $input_value): void
    {
        $this->and_op_field = $input_value;
    }

    public function GetAndOp(): ?ReservedPrefixString
    {
        return $this->and_op_field;
    }

    public function SetEquality(?ReservedPrefixString $input_value): void
    {
        $this->equality_field = $input_value;
    }

    public function GetEquality(): ?ReservedPrefixString
    {
        return $this->equality_field;
    }

    public function SetGreaterThanEq(?ReservedPrefixString $input_value): void
    {
        $this->greater_than_eq_field = $input_value;
    }

    public function GetGreaterThanEq(): ?ReservedPrefixString
    {
        return $this->greater_than_eq_field;
    }

    public function SetGreaterThan(?ReservedPrefixString $input_value): void
    {
        $this->greater_than_field = $input_value;
    }

    public function GetGreaterThan(): ?ReservedPrefixString
    {
        return $this->greater_than_field;
    }

    public function SetLessThanEq(?ReservedPrefixString $input_value): void
    {
        $this->less_than_eq_field = $input_value;
    }

    public function GetLessThanEq(): ?ReservedPrefixString
    {
        return $this->less_than_eq_field;
    }

    public function SetLessThan(?ReservedPrefixString $input_value): void
    {
        $this->less_than_field = $input_value;
    }

    public function GetLessThan(): ?ReservedPrefixString
    {
        return $this->less_than_field;
    }

    public function SetNotEquality(?ReservedPrefixString $input_value): void
    {
        $this->not_equality_field = $input_value;
    }

    public function GetNotEquality(): ?ReservedPrefixString
    {
        return $this->not_equality_field;
    }

    public function SetOrOp(?ReservedPrefixString $input_value): void
    {
        $this->or_op_field = $input_value;
    }

    public function GetOrOp(): ?ReservedPrefixString
    {
        return $this->or_op_field;
    }

    public function SetSubtraction(?ReservedPrefixString $input_value): void
    {
        $this->subtraction_field = $input_value;
    }

    public function GetSubtraction(): ?ReservedPrefixString
    {
        return $this->subtraction_field;
    }

    private $length_string;
    private $addition_field;
    private $and_op_field;
    private $equality_field;
    private $greater_than_eq_field;
    private $greater_than_field;
    private $less_than_eq_field;
    private $less_than_field;
    private $not_equality_field;
    private $or_op_field;
    private $subtraction_field;
}

class UnaryOperatorParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?UnaryOperatorResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new UnaryOperator();
        $negation_field = new StringResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$string_parser_instance->ParseSingleSave($index,'!',$negation_field))
        {
            $instance->SetNegation($negation_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $negation_field = new StringResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new UnaryOperatorResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?UnaryOperatorResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new UnaryOperatorResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?UnaryOperatorListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new UnaryOperatorResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new UnaryOperatorListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class UnaryOperatorResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?UnaryOperator $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?UnaryOperator
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class UnaryOperatorListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class UnaryOperator {
    public function __construct() {
        $this->length_string = null;
        $this->negation_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetNegation(?ReservedPrefixString $input_value): void
    {
        $this->negation_field = $input_value;
    }

    public function GetNegation(): ?ReservedPrefixString
    {
        return $this->negation_field;
    }

    private $length_string;
    private $negation_field;
}

class CommentParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?CommentResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new Comment();
        $content_field = new CommentContentListResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$string_parser_instance->ParseSingle($index,'/*')&&$comment_content_parser_instance->ParseManySave($index,$content_field,0,-1)&&$string_parser_instance->ParseSingle($index,'*/'))
        {
            $instance->SetContent($content_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $content_field = new CommentContentListResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new CommentResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?CommentResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new CommentResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?CommentListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new CommentResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new CommentListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class CommentResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?Comment $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?Comment
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class CommentListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class Comment {
    public function __construct() {
        $this->length_string = null;
        $this->content_field = array();
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetContent(?array $input_value): void
    {
        $this->content_field = $input_value;
    }

    public function GetContent(): ?array
    {
        return $this->content_field;
    }

    private $length_string;
    private $content_field;
}

class NonStarCharacterParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?NonStarCharacterResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new NonStarCharacter();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$character_range_parser_instance->ParseSingle($index,0x00,0x29))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        if (true&&$character_range_parser_instance->ParseSingle($index,0x2B,0xFF))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new NonStarCharacterResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?NonStarCharacterResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new NonStarCharacterResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?NonStarCharacterListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new NonStarCharacterResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new NonStarCharacterListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class NonStarCharacterResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?NonStarCharacter $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?NonStarCharacter
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class NonStarCharacterListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class NonStarCharacter {
    public function __construct() {
        $this->length_string = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    private $length_string;
}

class NonSlashCharacterParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?NonSlashCharacterResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new NonSlashCharacter();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$character_range_parser_instance->ParseSingle($index,0x00,0x2E))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        if (true&&$character_range_parser_instance->ParseSingle($index,0x30,0xFF))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new NonSlashCharacterResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?NonSlashCharacterResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new NonSlashCharacterResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?NonSlashCharacterListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new NonSlashCharacterResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new NonSlashCharacterListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class NonSlashCharacterResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?NonSlashCharacter $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?NonSlashCharacter
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class NonSlashCharacterListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class NonSlashCharacter {
    public function __construct() {
        $this->length_string = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    private $length_string;
}

class CommentContentParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?CommentContentResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new CommentContent();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$non_star_character_parser_instance->ParseSingle($index))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        if (true&&$string_parser_instance->ParseSingle($index,'*')&&$non_slash_character_parser_instance->ParseSingle($index))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new CommentContentResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?CommentContentResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new CommentContentResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?CommentContentListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new CommentContentResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new CommentContentListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class CommentContentResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?CommentContent $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?CommentContent
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class CommentContentListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class CommentContent {
    public function __construct() {
        $this->length_string = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    private $length_string;
}

class QualfiedNameParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?QualfiedNameResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new QualfiedName();
        $name_field = new NameResult();
        $tail_field = new NameTailResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$name_parser_instance->ParseSingleSave($index,$name_field)&&$name_tail_parser_instance->ParseOptionalSave($index,$tail_field))
        {
            $instance->SetName($name_field->GetValue());
            $instance->SetTail($tail_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $name_field = new NameResult();
            $tail_field = new NameTailResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new QualfiedNameResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?QualfiedNameResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new QualfiedNameResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?QualfiedNameListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new QualfiedNameResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new QualfiedNameListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class QualfiedNameResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?QualfiedName $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?QualfiedName
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class QualfiedNameListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class QualfiedName {
    public function __construct() {
        $this->length_string = null;
        $this->name_field = null;
        $this->tail_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetName(?Name $input_value): void
    {
        $this->name_field = $input_value;
    }

    public function GetName(): ?Name
    {
        return $this->name_field;
    }

    public function SetTail(?NameTail $input_value): void
    {
        $this->tail_field = $input_value;
    }

    public function GetTail(): ?NameTail
    {
        return $this->tail_field;
    }

    private $length_string;
    private $name_field;
    private $tail_field;
}

class NameTailParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?NameTailResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new NameTail();
        $name_field = new NameResult();
        $tail_field = new NameTailResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$string_parser_instance->ParseSingle($index,'.')&&$name_parser_instance->ParseSingleSave($index,$name_field)&&$name_tail_parser_instance->ParseOptionalSave($index,$tail_field))
        {
            $instance->SetName($name_field->GetValue());
            $instance->SetTail($tail_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $name_field = new NameResult();
            $tail_field = new NameTailResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new NameTailResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?NameTailResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new NameTailResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?NameTailListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new NameTailResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new NameTailListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class NameTailResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?NameTail $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?NameTail
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class NameTailListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class NameTail {
    public function __construct() {
        $this->length_string = null;
        $this->name_field = null;
        $this->tail_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetName(?Name $input_value): void
    {
        $this->name_field = $input_value;
    }

    public function GetName(): ?Name
    {
        return $this->name_field;
    }

    public function SetTail(?NameTail $input_value): void
    {
        $this->tail_field = $input_value;
    }

    public function GetTail(): ?NameTail
    {
        return $this->tail_field;
    }

    private $length_string;
    private $name_field;
    private $tail_field;
}

class NameParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?NameResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new Name();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$name_character_parser_instance->ParseMany($index,1,-1))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new NameResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?NameResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new NameResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?NameListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new NameResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new NameListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class NameResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?Name $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?Name
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class NameListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class Name {
    public function __construct() {
        $this->length_string = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    private $length_string;
}

class NameCharacterParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?NameCharacterResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new NameCharacter();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$character_range_parser_instance->ParseSingle($index,0x30,0x39))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        if (true&&$character_range_parser_instance->ParseSingle($index,0x41,0x5A))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        if (true&&$string_parser_instance->ParseSingle($index,'_'))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        if (true&&$character_range_parser_instance->ParseSingle($index,0x61,0x7A))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new NameCharacterResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?NameCharacterResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new NameCharacterResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?NameCharacterListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new NameCharacterResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new NameCharacterListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class NameCharacterResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?NameCharacter $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?NameCharacter
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class NameCharacterListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class NameCharacter {
    public function __construct() {
        $this->length_string = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    private $length_string;
}

class BooleanParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?BooleanResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new Boolean();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$string_parser_instance->ParseSingle($index,'true'))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        if (true&&$string_parser_instance->ParseSingle($index,'false'))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new BooleanResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?BooleanResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new BooleanResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?BooleanListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new BooleanResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new BooleanListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class BooleanResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?Boolean $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?Boolean
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class BooleanListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class Boolean {
    public function __construct() {
        $this->length_string = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    private $length_string;
}

class ByteParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?ByteResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new Byte();
        $high_field = new ByteDigitResult();
        $low_field = new ByteDigitResult();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$string_parser_instance->ParseSingle($index,'0x')&&$byte_digit_parser_instance->ParseSingleSave($index,$high_field)&&$byte_digit_parser_instance->ParseSingleSave($index,$low_field))
        {
            $instance->SetHigh($high_field->GetValue());
            $instance->SetLow($low_field->GetValue());
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $high_field = new ByteDigitResult();
            $low_field = new ByteDigitResult();
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new ByteResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?ByteResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new ByteResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?ByteListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new ByteResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new ByteListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class ByteResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?Byte $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?Byte
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class ByteListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class Byte {
    public function __construct() {
        $this->length_string = null;
        $this->high_field = null;
        $this->low_field = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    public function SetHigh(?ByteDigit $input_value): void
    {
        $this->high_field = $input_value;
    }

    public function GetHigh(): ?ByteDigit
    {
        return $this->high_field;
    }

    public function SetLow(?ByteDigit $input_value): void
    {
        $this->low_field = $input_value;
    }

    public function GetLow(): ?ByteDigit
    {
        return $this->low_field;
    }

    private $length_string;
    private $high_field;
    private $low_field;
}

class ByteDigitParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?ByteDigitResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new ByteDigit();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$character_range_parser_instance->ParseSingle($index,0x30,0x39))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        if (true&&$character_range_parser_instance->ParseSingle($index,0x41,0x46))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new ByteDigitResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?ByteDigitResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new ByteDigitResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?ByteDigitListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new ByteDigitResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new ByteDigitListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class ByteDigitResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?ByteDigit $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?ByteDigit
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class ByteDigitListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class ByteDigit {
    public function __construct() {
        $this->length_string = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    private $length_string;
}

class NegativeParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?NegativeResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new Negative();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$string_parser_instance->ParseSingle($index,'-'))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new NegativeResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?NegativeResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new NegativeResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?NegativeListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new NegativeResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new NegativeListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class NegativeResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?Negative $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?Negative
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class NegativeListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class Negative {
    public function __construct() {
        $this->length_string = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    private $length_string;
}

class DecimalParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?DecimalResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new Decimal();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$negative_parser_instance->ParseOptional($index)&&$number_parser_instance->ParseSingle($index)&&$string_parser_instance->ParseSingle($index,'.')&&$number_parser_instance->ParseSingle($index))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new DecimalResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?DecimalResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new DecimalResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?DecimalListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new DecimalResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new DecimalListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class DecimalResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?Decimal $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?Decimal
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class DecimalListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class Decimal {
    public function __construct() {
        $this->length_string = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    private $length_string;
}

class NumberParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?NumberResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new Number();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$negative_parser_instance->ParseOptional($index)&&$digit_parser_instance->ParseMany($index,1,-1))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new NumberResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?NumberResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new NumberResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?NumberListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new NumberResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new NumberListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class NumberResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?Number $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?Number
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class NumberListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class Number {
    public function __construct() {
        $this->length_string = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    private $length_string;
}

class DigitParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?DigitResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new Digit();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$character_range_parser_instance->ParseSingle($index,0x30,0x39))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new DigitResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?DigitResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new DigitResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?DigitListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new DigitResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new DigitListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class DigitResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?Digit $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?Digit
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class DigitListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class Digit {
    public function __construct() {
        $this->length_string = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    private $length_string;
}

class LiteralParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?LiteralResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new Literal();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$literal_character_parser_instance->ParseMany($index,0,-1))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new LiteralResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?LiteralResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new LiteralResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?LiteralListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new LiteralResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new LiteralListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class LiteralResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?Literal $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?Literal
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class LiteralListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class Literal {
    public function __construct() {
        $this->length_string = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    private $length_string;
}

class LiteralCharacterParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?LiteralCharacterResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new LiteralCharacter();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$character_range_parser_instance->ParseSingle($index,0x00,0x21))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        if (true&&$string_parser_instance->ParseSingle($index,'\\"'))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        if (true&&$character_range_parser_instance->ParseSingle($index,0x23,0x5B))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        if (true&&$string_parser_instance->ParseSingle($index,'\\\\'))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        if (true&&$character_range_parser_instance->ParseSingle($index,0x5D,0xFF))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new LiteralCharacterResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?LiteralCharacterResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new LiteralCharacterResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?LiteralCharacterListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new LiteralCharacterResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new LiteralCharacterListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class LiteralCharacterResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?LiteralCharacter $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?LiteralCharacter
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class LiteralCharacterListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class LiteralCharacter {
    public function __construct() {
        $this->length_string = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    private $length_string;
}

class WhitespaceParser {
    public function __construct() {
        $this->parser_network = null;
    }

    public function SetParserNetwork(?ParserNetwork $input): void
    {
        $this->parser_network = $input;
    }

    public function ParseSingleSave(?LengthString $index, ?WhitespaceResult $result): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $consumed_string = new LengthString();
        $consumed_string->SetData($index->GetData());
        $consumed_string->SetStart($index->GetStart());
        $consumed_string->SetLength(0);
        $instance = new Whitespace();
        $c_t_code_file_parser_instance = $this->parser_network->GetCTCodeFileParser();
        $external_definition_parser_instance = $this->parser_network->GetExternalDefinitionParser();
        $unmanaged_type_parser_instance = $this->parser_network->GetUnmanagedTypeParser();
        $definition_parser_instance = $this->parser_network->GetDefinitionParser();
        $interface_def_parser_instance = $this->parser_network->GetInterfaceDefParser();
        $class_def_parser_instance = $this->parser_network->GetClassDefParser();
        $implementation_spec_parser_instance = $this->parser_network->GetImplementationSpecParser();
        $content_declaration_parser_instance = $this->parser_network->GetContentDeclarationParser();
        $content_definition_parser_instance = $this->parser_network->GetContentDefinitionParser();
        $primative_type_parser_instance = $this->parser_network->GetPrimativeTypeParser();
        $defined_type_parser_instance = $this->parser_network->GetDefinedTypeParser();
        $singleton_type_parser_instance = $this->parser_network->GetSingletonTypeParser();
        $dimensional_note_parser_instance = $this->parser_network->GetDimensionalNoteParser();
        $dimensional_type_parser_instance = $this->parser_network->GetDimensionalTypeParser();
        $map_note_parser_instance = $this->parser_network->GetMapNoteParser();
        $map_type_parser_instance = $this->parser_network->GetMapTypeParser();
        $value_type_parser_instance = $this->parser_network->GetValueTypeParser();
        $parameter_list_def_parser_instance = $this->parser_network->GetParameterListDefParser();
        $parameter_list_parser_instance = $this->parser_network->GetParameterListParser();
        $code_block_parser_instance = $this->parser_network->GetCodeBlockParser();
        $declaration_assign_parser_instance = $this->parser_network->GetDeclarationAssignParser();
        $declaration_parser_instance = $this->parser_network->GetDeclarationParser();
        $assignment_parser_instance = $this->parser_network->GetAssignmentParser();
        $return_parser_instance = $this->parser_network->GetReturnParser();
        $else_tail_parser_instance = $this->parser_network->GetElseTailParser();
        $conditional_parser_instance = $this->parser_network->GetConditionalParser();
        $loop_parser_instance = $this->parser_network->GetLoopParser();
        $call_parser_instance = $this->parser_network->GetCallParser();
        $allocate_parser_instance = $this->parser_network->GetAllocateParser();
        $instruction_parser_instance = $this->parser_network->GetInstructionParser();
        $r_value_single_parser_instance = $this->parser_network->GetRValueSingleParser();
        $r_value_tail_parser_instance = $this->parser_network->GetRValueTailParser();
        $r_value_parser_instance = $this->parser_network->GetRValueParser();
        $binary_operator_parser_instance = $this->parser_network->GetBinaryOperatorParser();
        $unary_operator_parser_instance = $this->parser_network->GetUnaryOperatorParser();
        $comment_parser_instance = $this->parser_network->GetCommentParser();
        $non_star_character_parser_instance = $this->parser_network->GetNonStarCharacterParser();
        $non_slash_character_parser_instance = $this->parser_network->GetNonSlashCharacterParser();
        $comment_content_parser_instance = $this->parser_network->GetCommentContentParser();
        $qualfied_name_parser_instance = $this->parser_network->GetQualfiedNameParser();
        $name_tail_parser_instance = $this->parser_network->GetNameTailParser();
        $name_parser_instance = $this->parser_network->GetNameParser();
        $name_character_parser_instance = $this->parser_network->GetNameCharacterParser();
        $boolean_parser_instance = $this->parser_network->GetBooleanParser();
        $byte_parser_instance = $this->parser_network->GetByteParser();
        $byte_digit_parser_instance = $this->parser_network->GetByteDigitParser();
        $negative_parser_instance = $this->parser_network->GetNegativeParser();
        $decimal_parser_instance = $this->parser_network->GetDecimalParser();
        $number_parser_instance = $this->parser_network->GetNumberParser();
        $digit_parser_instance = $this->parser_network->GetDigitParser();
        $literal_parser_instance = $this->parser_network->GetLiteralParser();
        $literal_character_parser_instance = $this->parser_network->GetLiteralCharacterParser();
        $whitespace_parser_instance = $this->parser_network->GetWhitespaceParser();
        $string_parser_instance = $this->parser_network->GetStringParser();
        $character_parser_instance = $this->parser_network->GetCharacterParser();
        $character_range_parser_instance = $this->parser_network->GetCharacterRangeParser();
        if (true&&$character_range_parser_instance->ParseSingle($index,0x00,0x20))
        {
            $consumed_string->SetLength($index->GetStart()-$index_start);
            $instance->SetLengthString($consumed_string);
            $result->SetValue($instance);
            $result->SetResult(true);
            return $result->GetResult();
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
        }
        $result->SetResult(false);
        return $result->GetResult();
    }

    public function ParseSingle(?LengthString $index): ?bool
    {
        $result = new WhitespaceResult();
        return $this->ParseSingleSave($index,$result);
    }

    public function ParseOptionalSave(?LengthString $index, ?WhitespaceResult $result): ?bool
    {
        $this->ParseSingleSave($index,$result);
        $result->SetResult(true);
        return true;
    }

    public function ParseOptional(?LengthString $index): ?bool
    {
        $result = new WhitespaceResult();
        return $this->ParseOptionalSave($index,$result);
    }

    public function ParseManySave(?LengthString $index, ?WhitespaceListResult $list_result, ?int $minimum, ?int $maximum): ?bool
    {
        $index_start = $index->GetStart();
        $index_length = $index->GetLength();
        $results = array();
        $count = 0;
        $max_check = $maximum;
        $check_next = true;
        if ($maximum<0)
        {
            $max_check = $count+1;
        }
        while ($check_next&&$count<$max_check)
        {
            $result = new WhitespaceResult();
            $this->ParseSingleSave($index,$result);
            $check_next = $result->GetResult();
            if ($result->GetResult())
            {
                $count = $count+1;
                Append($results,$result->GetValue());
            }
            if ($maximum<0)
            {
                $max_check = $count+1;
            }
        }
        if ($count>=$minimum&&$count<=$max_check)
        {
            $list_result->SetValue($results);
            $list_result->SetResult(true);
        }
        else
        {
            $index->SetStart($index_start);
            $index->SetLength($index_length);
            $list_result->SetResult(false);
        }
        return $list_result->GetResult();
    }

    public function ParseMany(?LengthString $index, ?int $minimum, ?int $maximum): ?bool
    {
        $result = new WhitespaceListResult();
        return $this->ParseManySave($index,$result,$minimum,$maximum);
    }

    private $parser_network;
}

class WhitespaceResult {
    public function __construct() {
        $this->value = null;
        $this->result = false;
    }

    public function SetValue(?Whitespace $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?Whitespace
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class WhitespaceListResult {
    public function __construct() {
        $this->value = array();
        $this->result = false;
    }

    public function SetValue(?array $new_value): void
    {
        $this->value = $new_value;
    }

    public function GetValue(): ?array
    {
        return $this->value;
    }

    public function SetResult(?bool $new_result): void
    {
        $this->result = $new_result;
    }

    public function GetResult(): ?bool
    {
        return $this->result;
    }

    private $value;
    private $result;
}

class Whitespace {
    public function __construct() {
        $this->length_string = null;
    }

    public function SetLengthString(?LengthString $new_value): void
    {
        $this->length_string = new LengthString();
        $this->length_string->SetData($new_value->GetData());
        $this->length_string->SetStart($new_value->GetStart());
        $this->length_string->SetLength($new_value->GetLength());
    }

    public function UnParse(): ?string
    {
        return $this->length_string->GetString();
    }

    private $length_string;
}

?>
