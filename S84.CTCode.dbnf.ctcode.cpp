#include "S84.CTCode.dbnf.ctcode.hpp"

namespace s84 {
namespace ctcode {
namespace dbnf {
namespace ctcode {

StringParser::StringParser()
{
}

bool StringParser::ParseSingleSave(OmniPointer<LengthString> index, std::string value, OmniPointer<StringResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LargeString> index_data = index->GetData();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<String> instance = std::shared_ptr<String>(new String());
    int value_length = Length(value);
    if (value_length>index->GetLength())
    {
        result->SetResult(false);
        return false;
    }
    int offset_index = 0;
    while (offset_index<value_length)
    {
        if (index_data->GetAt(index->GetStart()+offset_index)!=At(value,offset_index))
        {
            result->SetResult(false);
            return false;
        }
        offset_index = offset_index+1;
    }
    index->SetStart(index->GetStart()+value_length);
    index->SetLength(index->GetLength()-value_length);
    consumed_string->SetLength(index->GetStart()-index_start);
    instance->SetLengthString(consumed_string);
    result->SetValue(instance);
    result->SetResult(true);
    return true;
}

bool StringParser::ParseSingle(OmniPointer<LengthString> index, std::string value)
{
    OmniPointer<StringResult> result = std::shared_ptr<StringResult>(new StringResult());
    return this->ParseSingleSave(index,value,result);
}

StringResult::StringResult()
{
    this->value = NULL;
    this->result = false;
}

void StringResult::SetValue(OmniPointer<String> new_value)
{
    this->value = new_value;
}

OmniPointer<String> StringResult::GetValue()
{
    return this->value;
}

void StringResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool StringResult::GetResult()
{
    return this->result;
}

StringListResult::StringListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void StringListResult::SetValue(std::vector<OmniPointer<String>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<String>> StringListResult::GetValue()
{
    return this->value;
}

void StringListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool StringListResult::GetResult()
{
    return this->result;
}

String::String()
{
    this->length_string = NULL;
}

void String::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string String::UnParse()
{
    return this->length_string->GetString();
}

CharacterParser::CharacterParser()
{
}

bool CharacterParser::ParseSingle(OmniPointer<LengthString> index, int value)
{
    if (0==index->GetLength())
    {
        return false;
    }
    OmniPointer<LargeString> index_data = index->GetData();
    int current_character = index_data->GetIntAt(index->GetStart());
    if (current_character==value)
    {
        index->SetStart(index->GetStart()+1);
        index->SetLength(index->GetLength()-1);
        return true;
    }
    return false;
}

CharacterResult::CharacterResult()
{
    this->value = NULL;
    this->result = false;
}

void CharacterResult::SetValue(OmniPointer<Character> new_value)
{
    this->value = new_value;
}

OmniPointer<Character> CharacterResult::GetValue()
{
    return this->value;
}

void CharacterResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool CharacterResult::GetResult()
{
    return this->result;
}

CharacterListResult::CharacterListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void CharacterListResult::SetValue(std::vector<OmniPointer<Character>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<Character>> CharacterListResult::GetValue()
{
    return this->value;
}

void CharacterListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool CharacterListResult::GetResult()
{
    return this->result;
}

Character::Character()
{
    this->length_string = NULL;
}

void Character::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string Character::UnParse()
{
    return this->length_string->GetString();
}

CharacterRangeParser::CharacterRangeParser()
{
}

bool CharacterRangeParser::ParseSingle(OmniPointer<LengthString> index, int low_value, int high_value)
{
    if (0==index->GetLength())
    {
        return false;
    }
    OmniPointer<LargeString> index_data = index->GetData();
    int current_character = index_data->GetIntAt(index->GetStart());
    if (low_value<=current_character&&current_character<=high_value)
    {
        index->SetStart(index->GetStart()+1);
        index->SetLength(index->GetLength()-1);
        return true;
    }
    return false;
}

CharacterRangeResult::CharacterRangeResult()
{
    this->value = NULL;
    this->result = false;
}

void CharacterRangeResult::SetValue(OmniPointer<CharacterRange> new_value)
{
    this->value = new_value;
}

OmniPointer<CharacterRange> CharacterRangeResult::GetValue()
{
    return this->value;
}

void CharacterRangeResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool CharacterRangeResult::GetResult()
{
    return this->result;
}

CharacterRangeListResult::CharacterRangeListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void CharacterRangeListResult::SetValue(std::vector<OmniPointer<CharacterRange>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<CharacterRange>> CharacterRangeListResult::GetValue()
{
    return this->value;
}

void CharacterRangeListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool CharacterRangeListResult::GetResult()
{
    return this->result;
}

CharacterRange::CharacterRange()
{
    this->length_string = NULL;
}

void CharacterRange::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string CharacterRange::UnParse()
{
    return this->length_string->GetString();
}

ParserNetwork::ParserNetwork()
{
    this->c_t_code_file_parser_field = NULL;
    this->external_definition_parser_field = NULL;
    this->unmanaged_type_parser_field = NULL;
    this->definition_parser_field = NULL;
    this->interface_def_parser_field = NULL;
    this->class_def_parser_field = NULL;
    this->implementation_spec_parser_field = NULL;
    this->content_declaration_parser_field = NULL;
    this->content_definition_parser_field = NULL;
    this->primative_type_parser_field = NULL;
    this->defined_type_parser_field = NULL;
    this->singleton_type_parser_field = NULL;
    this->dimensional_note_parser_field = NULL;
    this->dimensional_type_parser_field = NULL;
    this->map_note_parser_field = NULL;
    this->map_type_parser_field = NULL;
    this->value_type_parser_field = NULL;
    this->parameter_list_def_parser_field = NULL;
    this->parameter_list_parser_field = NULL;
    this->code_block_parser_field = NULL;
    this->declaration_assign_parser_field = NULL;
    this->declaration_parser_field = NULL;
    this->assignment_parser_field = NULL;
    this->return_parser_field = NULL;
    this->else_tail_parser_field = NULL;
    this->conditional_parser_field = NULL;
    this->loop_parser_field = NULL;
    this->call_parser_field = NULL;
    this->allocate_parser_field = NULL;
    this->instruction_parser_field = NULL;
    this->r_value_single_parser_field = NULL;
    this->r_value_tail_parser_field = NULL;
    this->r_value_parser_field = NULL;
    this->binary_operator_parser_field = NULL;
    this->unary_operator_parser_field = NULL;
    this->comment_parser_field = NULL;
    this->non_star_character_parser_field = NULL;
    this->non_slash_character_parser_field = NULL;
    this->comment_content_parser_field = NULL;
    this->qualfied_name_parser_field = NULL;
    this->name_tail_parser_field = NULL;
    this->name_parser_field = NULL;
    this->name_character_parser_field = NULL;
    this->boolean_parser_field = NULL;
    this->byte_parser_field = NULL;
    this->byte_digit_parser_field = NULL;
    this->negative_parser_field = NULL;
    this->decimal_parser_field = NULL;
    this->number_parser_field = NULL;
    this->digit_parser_field = NULL;
    this->literal_parser_field = NULL;
    this->literal_character_parser_field = NULL;
    this->whitespace_parser_field = NULL;
    this->string_parser_field = NULL;
    this->character_parser_field = NULL;
    this->character_range_parser_field = NULL;
}

OmniPointer<CTCodeFileParser> ParserNetwork::GetCTCodeFileParser()
{
    return this->c_t_code_file_parser_field;
}

OmniPointer<ExternalDefinitionParser> ParserNetwork::GetExternalDefinitionParser()
{
    return this->external_definition_parser_field;
}

OmniPointer<UnmanagedTypeParser> ParserNetwork::GetUnmanagedTypeParser()
{
    return this->unmanaged_type_parser_field;
}

OmniPointer<DefinitionParser> ParserNetwork::GetDefinitionParser()
{
    return this->definition_parser_field;
}

OmniPointer<InterfaceDefParser> ParserNetwork::GetInterfaceDefParser()
{
    return this->interface_def_parser_field;
}

OmniPointer<ClassDefParser> ParserNetwork::GetClassDefParser()
{
    return this->class_def_parser_field;
}

OmniPointer<ImplementationSpecParser> ParserNetwork::GetImplementationSpecParser()
{
    return this->implementation_spec_parser_field;
}

OmniPointer<ContentDeclarationParser> ParserNetwork::GetContentDeclarationParser()
{
    return this->content_declaration_parser_field;
}

OmniPointer<ContentDefinitionParser> ParserNetwork::GetContentDefinitionParser()
{
    return this->content_definition_parser_field;
}

OmniPointer<PrimativeTypeParser> ParserNetwork::GetPrimativeTypeParser()
{
    return this->primative_type_parser_field;
}

OmniPointer<DefinedTypeParser> ParserNetwork::GetDefinedTypeParser()
{
    return this->defined_type_parser_field;
}

OmniPointer<SingletonTypeParser> ParserNetwork::GetSingletonTypeParser()
{
    return this->singleton_type_parser_field;
}

OmniPointer<DimensionalNoteParser> ParserNetwork::GetDimensionalNoteParser()
{
    return this->dimensional_note_parser_field;
}

OmniPointer<DimensionalTypeParser> ParserNetwork::GetDimensionalTypeParser()
{
    return this->dimensional_type_parser_field;
}

OmniPointer<MapNoteParser> ParserNetwork::GetMapNoteParser()
{
    return this->map_note_parser_field;
}

OmniPointer<MapTypeParser> ParserNetwork::GetMapTypeParser()
{
    return this->map_type_parser_field;
}

OmniPointer<ValueTypeParser> ParserNetwork::GetValueTypeParser()
{
    return this->value_type_parser_field;
}

OmniPointer<ParameterListDefParser> ParserNetwork::GetParameterListDefParser()
{
    return this->parameter_list_def_parser_field;
}

OmniPointer<ParameterListParser> ParserNetwork::GetParameterListParser()
{
    return this->parameter_list_parser_field;
}

OmniPointer<CodeBlockParser> ParserNetwork::GetCodeBlockParser()
{
    return this->code_block_parser_field;
}

OmniPointer<DeclarationAssignParser> ParserNetwork::GetDeclarationAssignParser()
{
    return this->declaration_assign_parser_field;
}

OmniPointer<DeclarationParser> ParserNetwork::GetDeclarationParser()
{
    return this->declaration_parser_field;
}

OmniPointer<AssignmentParser> ParserNetwork::GetAssignmentParser()
{
    return this->assignment_parser_field;
}

OmniPointer<ReturnParser> ParserNetwork::GetReturnParser()
{
    return this->return_parser_field;
}

OmniPointer<ElseTailParser> ParserNetwork::GetElseTailParser()
{
    return this->else_tail_parser_field;
}

OmniPointer<ConditionalParser> ParserNetwork::GetConditionalParser()
{
    return this->conditional_parser_field;
}

OmniPointer<LoopParser> ParserNetwork::GetLoopParser()
{
    return this->loop_parser_field;
}

OmniPointer<CallParser> ParserNetwork::GetCallParser()
{
    return this->call_parser_field;
}

OmniPointer<AllocateParser> ParserNetwork::GetAllocateParser()
{
    return this->allocate_parser_field;
}

OmniPointer<InstructionParser> ParserNetwork::GetInstructionParser()
{
    return this->instruction_parser_field;
}

OmniPointer<RValueSingleParser> ParserNetwork::GetRValueSingleParser()
{
    return this->r_value_single_parser_field;
}

OmniPointer<RValueTailParser> ParserNetwork::GetRValueTailParser()
{
    return this->r_value_tail_parser_field;
}

OmniPointer<RValueParser> ParserNetwork::GetRValueParser()
{
    return this->r_value_parser_field;
}

OmniPointer<BinaryOperatorParser> ParserNetwork::GetBinaryOperatorParser()
{
    return this->binary_operator_parser_field;
}

OmniPointer<UnaryOperatorParser> ParserNetwork::GetUnaryOperatorParser()
{
    return this->unary_operator_parser_field;
}

OmniPointer<CommentParser> ParserNetwork::GetCommentParser()
{
    return this->comment_parser_field;
}

OmniPointer<NonStarCharacterParser> ParserNetwork::GetNonStarCharacterParser()
{
    return this->non_star_character_parser_field;
}

OmniPointer<NonSlashCharacterParser> ParserNetwork::GetNonSlashCharacterParser()
{
    return this->non_slash_character_parser_field;
}

OmniPointer<CommentContentParser> ParserNetwork::GetCommentContentParser()
{
    return this->comment_content_parser_field;
}

OmniPointer<QualfiedNameParser> ParserNetwork::GetQualfiedNameParser()
{
    return this->qualfied_name_parser_field;
}

OmniPointer<NameTailParser> ParserNetwork::GetNameTailParser()
{
    return this->name_tail_parser_field;
}

OmniPointer<NameParser> ParserNetwork::GetNameParser()
{
    return this->name_parser_field;
}

OmniPointer<NameCharacterParser> ParserNetwork::GetNameCharacterParser()
{
    return this->name_character_parser_field;
}

OmniPointer<BooleanParser> ParserNetwork::GetBooleanParser()
{
    return this->boolean_parser_field;
}

OmniPointer<ByteParser> ParserNetwork::GetByteParser()
{
    return this->byte_parser_field;
}

OmniPointer<ByteDigitParser> ParserNetwork::GetByteDigitParser()
{
    return this->byte_digit_parser_field;
}

OmniPointer<NegativeParser> ParserNetwork::GetNegativeParser()
{
    return this->negative_parser_field;
}

OmniPointer<DecimalParser> ParserNetwork::GetDecimalParser()
{
    return this->decimal_parser_field;
}

OmniPointer<NumberParser> ParserNetwork::GetNumberParser()
{
    return this->number_parser_field;
}

OmniPointer<DigitParser> ParserNetwork::GetDigitParser()
{
    return this->digit_parser_field;
}

OmniPointer<LiteralParser> ParserNetwork::GetLiteralParser()
{
    return this->literal_parser_field;
}

OmniPointer<LiteralCharacterParser> ParserNetwork::GetLiteralCharacterParser()
{
    return this->literal_character_parser_field;
}

OmniPointer<WhitespaceParser> ParserNetwork::GetWhitespaceParser()
{
    return this->whitespace_parser_field;
}

OmniPointer<StringParser> ParserNetwork::GetStringParser()
{
    return this->string_parser_field;
}

OmniPointer<CharacterParser> ParserNetwork::GetCharacterParser()
{
    return this->character_parser_field;
}

OmniPointer<CharacterRangeParser> ParserNetwork::GetCharacterRangeParser()
{
    return this->character_range_parser_field;
}

void ParserNetwork::Initialize()
{
    this->c_t_code_file_parser_field = std::shared_ptr<CTCodeFileParser>(new CTCodeFileParser());
    this->c_t_code_file_parser_field->SetParserNetwork(this);
    this->external_definition_parser_field = std::shared_ptr<ExternalDefinitionParser>(new ExternalDefinitionParser());
    this->external_definition_parser_field->SetParserNetwork(this);
    this->unmanaged_type_parser_field = std::shared_ptr<UnmanagedTypeParser>(new UnmanagedTypeParser());
    this->unmanaged_type_parser_field->SetParserNetwork(this);
    this->definition_parser_field = std::shared_ptr<DefinitionParser>(new DefinitionParser());
    this->definition_parser_field->SetParserNetwork(this);
    this->interface_def_parser_field = std::shared_ptr<InterfaceDefParser>(new InterfaceDefParser());
    this->interface_def_parser_field->SetParserNetwork(this);
    this->class_def_parser_field = std::shared_ptr<ClassDefParser>(new ClassDefParser());
    this->class_def_parser_field->SetParserNetwork(this);
    this->implementation_spec_parser_field = std::shared_ptr<ImplementationSpecParser>(new ImplementationSpecParser());
    this->implementation_spec_parser_field->SetParserNetwork(this);
    this->content_declaration_parser_field = std::shared_ptr<ContentDeclarationParser>(new ContentDeclarationParser());
    this->content_declaration_parser_field->SetParserNetwork(this);
    this->content_definition_parser_field = std::shared_ptr<ContentDefinitionParser>(new ContentDefinitionParser());
    this->content_definition_parser_field->SetParserNetwork(this);
    this->primative_type_parser_field = std::shared_ptr<PrimativeTypeParser>(new PrimativeTypeParser());
    this->primative_type_parser_field->SetParserNetwork(this);
    this->defined_type_parser_field = std::shared_ptr<DefinedTypeParser>(new DefinedTypeParser());
    this->defined_type_parser_field->SetParserNetwork(this);
    this->singleton_type_parser_field = std::shared_ptr<SingletonTypeParser>(new SingletonTypeParser());
    this->singleton_type_parser_field->SetParserNetwork(this);
    this->dimensional_note_parser_field = std::shared_ptr<DimensionalNoteParser>(new DimensionalNoteParser());
    this->dimensional_note_parser_field->SetParserNetwork(this);
    this->dimensional_type_parser_field = std::shared_ptr<DimensionalTypeParser>(new DimensionalTypeParser());
    this->dimensional_type_parser_field->SetParserNetwork(this);
    this->map_note_parser_field = std::shared_ptr<MapNoteParser>(new MapNoteParser());
    this->map_note_parser_field->SetParserNetwork(this);
    this->map_type_parser_field = std::shared_ptr<MapTypeParser>(new MapTypeParser());
    this->map_type_parser_field->SetParserNetwork(this);
    this->value_type_parser_field = std::shared_ptr<ValueTypeParser>(new ValueTypeParser());
    this->value_type_parser_field->SetParserNetwork(this);
    this->parameter_list_def_parser_field = std::shared_ptr<ParameterListDefParser>(new ParameterListDefParser());
    this->parameter_list_def_parser_field->SetParserNetwork(this);
    this->parameter_list_parser_field = std::shared_ptr<ParameterListParser>(new ParameterListParser());
    this->parameter_list_parser_field->SetParserNetwork(this);
    this->code_block_parser_field = std::shared_ptr<CodeBlockParser>(new CodeBlockParser());
    this->code_block_parser_field->SetParserNetwork(this);
    this->declaration_assign_parser_field = std::shared_ptr<DeclarationAssignParser>(new DeclarationAssignParser());
    this->declaration_assign_parser_field->SetParserNetwork(this);
    this->declaration_parser_field = std::shared_ptr<DeclarationParser>(new DeclarationParser());
    this->declaration_parser_field->SetParserNetwork(this);
    this->assignment_parser_field = std::shared_ptr<AssignmentParser>(new AssignmentParser());
    this->assignment_parser_field->SetParserNetwork(this);
    this->return_parser_field = std::shared_ptr<ReturnParser>(new ReturnParser());
    this->return_parser_field->SetParserNetwork(this);
    this->else_tail_parser_field = std::shared_ptr<ElseTailParser>(new ElseTailParser());
    this->else_tail_parser_field->SetParserNetwork(this);
    this->conditional_parser_field = std::shared_ptr<ConditionalParser>(new ConditionalParser());
    this->conditional_parser_field->SetParserNetwork(this);
    this->loop_parser_field = std::shared_ptr<LoopParser>(new LoopParser());
    this->loop_parser_field->SetParserNetwork(this);
    this->call_parser_field = std::shared_ptr<CallParser>(new CallParser());
    this->call_parser_field->SetParserNetwork(this);
    this->allocate_parser_field = std::shared_ptr<AllocateParser>(new AllocateParser());
    this->allocate_parser_field->SetParserNetwork(this);
    this->instruction_parser_field = std::shared_ptr<InstructionParser>(new InstructionParser());
    this->instruction_parser_field->SetParserNetwork(this);
    this->r_value_single_parser_field = std::shared_ptr<RValueSingleParser>(new RValueSingleParser());
    this->r_value_single_parser_field->SetParserNetwork(this);
    this->r_value_tail_parser_field = std::shared_ptr<RValueTailParser>(new RValueTailParser());
    this->r_value_tail_parser_field->SetParserNetwork(this);
    this->r_value_parser_field = std::shared_ptr<RValueParser>(new RValueParser());
    this->r_value_parser_field->SetParserNetwork(this);
    this->binary_operator_parser_field = std::shared_ptr<BinaryOperatorParser>(new BinaryOperatorParser());
    this->binary_operator_parser_field->SetParserNetwork(this);
    this->unary_operator_parser_field = std::shared_ptr<UnaryOperatorParser>(new UnaryOperatorParser());
    this->unary_operator_parser_field->SetParserNetwork(this);
    this->comment_parser_field = std::shared_ptr<CommentParser>(new CommentParser());
    this->comment_parser_field->SetParserNetwork(this);
    this->non_star_character_parser_field = std::shared_ptr<NonStarCharacterParser>(new NonStarCharacterParser());
    this->non_star_character_parser_field->SetParserNetwork(this);
    this->non_slash_character_parser_field = std::shared_ptr<NonSlashCharacterParser>(new NonSlashCharacterParser());
    this->non_slash_character_parser_field->SetParserNetwork(this);
    this->comment_content_parser_field = std::shared_ptr<CommentContentParser>(new CommentContentParser());
    this->comment_content_parser_field->SetParserNetwork(this);
    this->qualfied_name_parser_field = std::shared_ptr<QualfiedNameParser>(new QualfiedNameParser());
    this->qualfied_name_parser_field->SetParserNetwork(this);
    this->name_tail_parser_field = std::shared_ptr<NameTailParser>(new NameTailParser());
    this->name_tail_parser_field->SetParserNetwork(this);
    this->name_parser_field = std::shared_ptr<NameParser>(new NameParser());
    this->name_parser_field->SetParserNetwork(this);
    this->name_character_parser_field = std::shared_ptr<NameCharacterParser>(new NameCharacterParser());
    this->name_character_parser_field->SetParserNetwork(this);
    this->boolean_parser_field = std::shared_ptr<BooleanParser>(new BooleanParser());
    this->boolean_parser_field->SetParserNetwork(this);
    this->byte_parser_field = std::shared_ptr<ByteParser>(new ByteParser());
    this->byte_parser_field->SetParserNetwork(this);
    this->byte_digit_parser_field = std::shared_ptr<ByteDigitParser>(new ByteDigitParser());
    this->byte_digit_parser_field->SetParserNetwork(this);
    this->negative_parser_field = std::shared_ptr<NegativeParser>(new NegativeParser());
    this->negative_parser_field->SetParserNetwork(this);
    this->decimal_parser_field = std::shared_ptr<DecimalParser>(new DecimalParser());
    this->decimal_parser_field->SetParserNetwork(this);
    this->number_parser_field = std::shared_ptr<NumberParser>(new NumberParser());
    this->number_parser_field->SetParserNetwork(this);
    this->digit_parser_field = std::shared_ptr<DigitParser>(new DigitParser());
    this->digit_parser_field->SetParserNetwork(this);
    this->literal_parser_field = std::shared_ptr<LiteralParser>(new LiteralParser());
    this->literal_parser_field->SetParserNetwork(this);
    this->literal_character_parser_field = std::shared_ptr<LiteralCharacterParser>(new LiteralCharacterParser());
    this->literal_character_parser_field->SetParserNetwork(this);
    this->whitespace_parser_field = std::shared_ptr<WhitespaceParser>(new WhitespaceParser());
    this->whitespace_parser_field->SetParserNetwork(this);
    this->string_parser_field = std::shared_ptr<StringParser>(new StringParser());
    this->character_parser_field = std::shared_ptr<CharacterParser>(new CharacterParser());
    this->character_range_parser_field = std::shared_ptr<CharacterRangeParser>(new CharacterRangeParser());
}

DBNFOmniType::DBNFOmniType()
{
    this->c_t_code_file_field = NULL;
    this->external_definition_field = NULL;
    this->unmanaged_type_field = NULL;
    this->definition_field = NULL;
    this->interface_def_field = NULL;
    this->class_def_field = NULL;
    this->implementation_spec_field = NULL;
    this->content_declaration_field = NULL;
    this->content_definition_field = NULL;
    this->primative_type_field = NULL;
    this->defined_type_field = NULL;
    this->singleton_type_field = NULL;
    this->dimensional_note_field = NULL;
    this->dimensional_type_field = NULL;
    this->map_note_field = NULL;
    this->map_type_field = NULL;
    this->value_type_field = NULL;
    this->parameter_list_def_field = NULL;
    this->parameter_list_field = NULL;
    this->code_block_field = NULL;
    this->declaration_assign_field = NULL;
    this->declaration_field = NULL;
    this->assignment_field = NULL;
    this->return_field = NULL;
    this->else_tail_field = NULL;
    this->conditional_field = NULL;
    this->loop_field = NULL;
    this->call_field = NULL;
    this->allocate_field = NULL;
    this->instruction_field = NULL;
    this->r_value_single_field = NULL;
    this->r_value_tail_field = NULL;
    this->r_value_field = NULL;
    this->binary_operator_field = NULL;
    this->unary_operator_field = NULL;
    this->comment_field = NULL;
    this->non_star_character_field = NULL;
    this->non_slash_character_field = NULL;
    this->comment_content_field = NULL;
    this->qualfied_name_field = NULL;
    this->name_tail_field = NULL;
    this->name_field = NULL;
    this->name_character_field = NULL;
    this->boolean_field = NULL;
    this->byte_field = NULL;
    this->byte_digit_field = NULL;
    this->negative_field = NULL;
    this->decimal_field = NULL;
    this->number_field = NULL;
    this->digit_field = NULL;
    this->literal_field = NULL;
    this->literal_character_field = NULL;
    this->whitespace_field = NULL;
}

void DBNFOmniType::SetCTCodeFile(OmniPointer<CTCodeFile> input_value)
{
    this->c_t_code_file_field = input_value;
}

OmniPointer<CTCodeFile> DBNFOmniType::GetCTCodeFile()
{
    return this->c_t_code_file_field;
}

void DBNFOmniType::SetExternalDefinition(OmniPointer<ExternalDefinition> input_value)
{
    this->external_definition_field = input_value;
}

OmniPointer<ExternalDefinition> DBNFOmniType::GetExternalDefinition()
{
    return this->external_definition_field;
}

void DBNFOmniType::SetUnmanagedType(OmniPointer<UnmanagedType> input_value)
{
    this->unmanaged_type_field = input_value;
}

OmniPointer<UnmanagedType> DBNFOmniType::GetUnmanagedType()
{
    return this->unmanaged_type_field;
}

void DBNFOmniType::SetDefinition(OmniPointer<Definition> input_value)
{
    this->definition_field = input_value;
}

OmniPointer<Definition> DBNFOmniType::GetDefinition()
{
    return this->definition_field;
}

void DBNFOmniType::SetInterfaceDef(OmniPointer<InterfaceDef> input_value)
{
    this->interface_def_field = input_value;
}

OmniPointer<InterfaceDef> DBNFOmniType::GetInterfaceDef()
{
    return this->interface_def_field;
}

void DBNFOmniType::SetClassDef(OmniPointer<ClassDef> input_value)
{
    this->class_def_field = input_value;
}

OmniPointer<ClassDef> DBNFOmniType::GetClassDef()
{
    return this->class_def_field;
}

void DBNFOmniType::SetImplementationSpec(OmniPointer<ImplementationSpec> input_value)
{
    this->implementation_spec_field = input_value;
}

OmniPointer<ImplementationSpec> DBNFOmniType::GetImplementationSpec()
{
    return this->implementation_spec_field;
}

void DBNFOmniType::SetContentDeclaration(OmniPointer<ContentDeclaration> input_value)
{
    this->content_declaration_field = input_value;
}

OmniPointer<ContentDeclaration> DBNFOmniType::GetContentDeclaration()
{
    return this->content_declaration_field;
}

void DBNFOmniType::SetContentDefinition(OmniPointer<ContentDefinition> input_value)
{
    this->content_definition_field = input_value;
}

OmniPointer<ContentDefinition> DBNFOmniType::GetContentDefinition()
{
    return this->content_definition_field;
}

void DBNFOmniType::SetPrimativeType(OmniPointer<PrimativeType> input_value)
{
    this->primative_type_field = input_value;
}

OmniPointer<PrimativeType> DBNFOmniType::GetPrimativeType()
{
    return this->primative_type_field;
}

void DBNFOmniType::SetDefinedType(OmniPointer<DefinedType> input_value)
{
    this->defined_type_field = input_value;
}

OmniPointer<DefinedType> DBNFOmniType::GetDefinedType()
{
    return this->defined_type_field;
}

void DBNFOmniType::SetSingletonType(OmniPointer<SingletonType> input_value)
{
    this->singleton_type_field = input_value;
}

OmniPointer<SingletonType> DBNFOmniType::GetSingletonType()
{
    return this->singleton_type_field;
}

void DBNFOmniType::SetDimensionalNote(OmniPointer<DimensionalNote> input_value)
{
    this->dimensional_note_field = input_value;
}

OmniPointer<DimensionalNote> DBNFOmniType::GetDimensionalNote()
{
    return this->dimensional_note_field;
}

void DBNFOmniType::SetDimensionalType(OmniPointer<DimensionalType> input_value)
{
    this->dimensional_type_field = input_value;
}

OmniPointer<DimensionalType> DBNFOmniType::GetDimensionalType()
{
    return this->dimensional_type_field;
}

void DBNFOmniType::SetMapNote(OmniPointer<MapNote> input_value)
{
    this->map_note_field = input_value;
}

OmniPointer<MapNote> DBNFOmniType::GetMapNote()
{
    return this->map_note_field;
}

void DBNFOmniType::SetMapType(OmniPointer<MapType> input_value)
{
    this->map_type_field = input_value;
}

OmniPointer<MapType> DBNFOmniType::GetMapType()
{
    return this->map_type_field;
}

void DBNFOmniType::SetValueType(OmniPointer<ValueType> input_value)
{
    this->value_type_field = input_value;
}

OmniPointer<ValueType> DBNFOmniType::GetValueType()
{
    return this->value_type_field;
}

void DBNFOmniType::SetParameterListDef(OmniPointer<ParameterListDef> input_value)
{
    this->parameter_list_def_field = input_value;
}

OmniPointer<ParameterListDef> DBNFOmniType::GetParameterListDef()
{
    return this->parameter_list_def_field;
}

void DBNFOmniType::SetParameterList(OmniPointer<ParameterList> input_value)
{
    this->parameter_list_field = input_value;
}

OmniPointer<ParameterList> DBNFOmniType::GetParameterList()
{
    return this->parameter_list_field;
}

void DBNFOmniType::SetCodeBlock(OmniPointer<CodeBlock> input_value)
{
    this->code_block_field = input_value;
}

OmniPointer<CodeBlock> DBNFOmniType::GetCodeBlock()
{
    return this->code_block_field;
}

void DBNFOmniType::SetDeclarationAssign(OmniPointer<DeclarationAssign> input_value)
{
    this->declaration_assign_field = input_value;
}

OmniPointer<DeclarationAssign> DBNFOmniType::GetDeclarationAssign()
{
    return this->declaration_assign_field;
}

void DBNFOmniType::SetDeclaration(OmniPointer<Declaration> input_value)
{
    this->declaration_field = input_value;
}

OmniPointer<Declaration> DBNFOmniType::GetDeclaration()
{
    return this->declaration_field;
}

void DBNFOmniType::SetAssignment(OmniPointer<Assignment> input_value)
{
    this->assignment_field = input_value;
}

OmniPointer<Assignment> DBNFOmniType::GetAssignment()
{
    return this->assignment_field;
}

void DBNFOmniType::SetReturn(OmniPointer<Return> input_value)
{
    this->return_field = input_value;
}

OmniPointer<Return> DBNFOmniType::GetReturn()
{
    return this->return_field;
}

void DBNFOmniType::SetElseTail(OmniPointer<ElseTail> input_value)
{
    this->else_tail_field = input_value;
}

OmniPointer<ElseTail> DBNFOmniType::GetElseTail()
{
    return this->else_tail_field;
}

void DBNFOmniType::SetConditional(OmniPointer<Conditional> input_value)
{
    this->conditional_field = input_value;
}

OmniPointer<Conditional> DBNFOmniType::GetConditional()
{
    return this->conditional_field;
}

void DBNFOmniType::SetLoop(OmniPointer<Loop> input_value)
{
    this->loop_field = input_value;
}

OmniPointer<Loop> DBNFOmniType::GetLoop()
{
    return this->loop_field;
}

void DBNFOmniType::SetCall(OmniPointer<Call> input_value)
{
    this->call_field = input_value;
}

OmniPointer<Call> DBNFOmniType::GetCall()
{
    return this->call_field;
}

void DBNFOmniType::SetAllocate(OmniPointer<Allocate> input_value)
{
    this->allocate_field = input_value;
}

OmniPointer<Allocate> DBNFOmniType::GetAllocate()
{
    return this->allocate_field;
}

void DBNFOmniType::SetInstruction(OmniPointer<Instruction> input_value)
{
    this->instruction_field = input_value;
}

OmniPointer<Instruction> DBNFOmniType::GetInstruction()
{
    return this->instruction_field;
}

void DBNFOmniType::SetRValueSingle(OmniPointer<RValueSingle> input_value)
{
    this->r_value_single_field = input_value;
}

OmniPointer<RValueSingle> DBNFOmniType::GetRValueSingle()
{
    return this->r_value_single_field;
}

void DBNFOmniType::SetRValueTail(OmniPointer<RValueTail> input_value)
{
    this->r_value_tail_field = input_value;
}

OmniPointer<RValueTail> DBNFOmniType::GetRValueTail()
{
    return this->r_value_tail_field;
}

void DBNFOmniType::SetRValue(OmniPointer<RValue> input_value)
{
    this->r_value_field = input_value;
}

OmniPointer<RValue> DBNFOmniType::GetRValue()
{
    return this->r_value_field;
}

void DBNFOmniType::SetBinaryOperator(OmniPointer<BinaryOperator> input_value)
{
    this->binary_operator_field = input_value;
}

OmniPointer<BinaryOperator> DBNFOmniType::GetBinaryOperator()
{
    return this->binary_operator_field;
}

void DBNFOmniType::SetUnaryOperator(OmniPointer<UnaryOperator> input_value)
{
    this->unary_operator_field = input_value;
}

OmniPointer<UnaryOperator> DBNFOmniType::GetUnaryOperator()
{
    return this->unary_operator_field;
}

void DBNFOmniType::SetComment(OmniPointer<Comment> input_value)
{
    this->comment_field = input_value;
}

OmniPointer<Comment> DBNFOmniType::GetComment()
{
    return this->comment_field;
}

void DBNFOmniType::SetNonStarCharacter(OmniPointer<NonStarCharacter> input_value)
{
    this->non_star_character_field = input_value;
}

OmniPointer<NonStarCharacter> DBNFOmniType::GetNonStarCharacter()
{
    return this->non_star_character_field;
}

void DBNFOmniType::SetNonSlashCharacter(OmniPointer<NonSlashCharacter> input_value)
{
    this->non_slash_character_field = input_value;
}

OmniPointer<NonSlashCharacter> DBNFOmniType::GetNonSlashCharacter()
{
    return this->non_slash_character_field;
}

void DBNFOmniType::SetCommentContent(OmniPointer<CommentContent> input_value)
{
    this->comment_content_field = input_value;
}

OmniPointer<CommentContent> DBNFOmniType::GetCommentContent()
{
    return this->comment_content_field;
}

void DBNFOmniType::SetQualfiedName(OmniPointer<QualfiedName> input_value)
{
    this->qualfied_name_field = input_value;
}

OmniPointer<QualfiedName> DBNFOmniType::GetQualfiedName()
{
    return this->qualfied_name_field;
}

void DBNFOmniType::SetNameTail(OmniPointer<NameTail> input_value)
{
    this->name_tail_field = input_value;
}

OmniPointer<NameTail> DBNFOmniType::GetNameTail()
{
    return this->name_tail_field;
}

void DBNFOmniType::SetName(OmniPointer<Name> input_value)
{
    this->name_field = input_value;
}

OmniPointer<Name> DBNFOmniType::GetName()
{
    return this->name_field;
}

void DBNFOmniType::SetNameCharacter(OmniPointer<NameCharacter> input_value)
{
    this->name_character_field = input_value;
}

OmniPointer<NameCharacter> DBNFOmniType::GetNameCharacter()
{
    return this->name_character_field;
}

void DBNFOmniType::SetBoolean(OmniPointer<Boolean> input_value)
{
    this->boolean_field = input_value;
}

OmniPointer<Boolean> DBNFOmniType::GetBoolean()
{
    return this->boolean_field;
}

void DBNFOmniType::SetByte(OmniPointer<Byte> input_value)
{
    this->byte_field = input_value;
}

OmniPointer<Byte> DBNFOmniType::GetByte()
{
    return this->byte_field;
}

void DBNFOmniType::SetByteDigit(OmniPointer<ByteDigit> input_value)
{
    this->byte_digit_field = input_value;
}

OmniPointer<ByteDigit> DBNFOmniType::GetByteDigit()
{
    return this->byte_digit_field;
}

void DBNFOmniType::SetNegative(OmniPointer<Negative> input_value)
{
    this->negative_field = input_value;
}

OmniPointer<Negative> DBNFOmniType::GetNegative()
{
    return this->negative_field;
}

void DBNFOmniType::SetDecimal(OmniPointer<Decimal> input_value)
{
    this->decimal_field = input_value;
}

OmniPointer<Decimal> DBNFOmniType::GetDecimal()
{
    return this->decimal_field;
}

void DBNFOmniType::SetNumber(OmniPointer<Number> input_value)
{
    this->number_field = input_value;
}

OmniPointer<Number> DBNFOmniType::GetNumber()
{
    return this->number_field;
}

void DBNFOmniType::SetDigit(OmniPointer<Digit> input_value)
{
    this->digit_field = input_value;
}

OmniPointer<Digit> DBNFOmniType::GetDigit()
{
    return this->digit_field;
}

void DBNFOmniType::SetLiteral(OmniPointer<Literal> input_value)
{
    this->literal_field = input_value;
}

OmniPointer<Literal> DBNFOmniType::GetLiteral()
{
    return this->literal_field;
}

void DBNFOmniType::SetLiteralCharacter(OmniPointer<LiteralCharacter> input_value)
{
    this->literal_character_field = input_value;
}

OmniPointer<LiteralCharacter> DBNFOmniType::GetLiteralCharacter()
{
    return this->literal_character_field;
}

void DBNFOmniType::SetWhitespace(OmniPointer<Whitespace> input_value)
{
    this->whitespace_field = input_value;
}

OmniPointer<Whitespace> DBNFOmniType::GetWhitespace()
{
    return this->whitespace_field;
}

DBNFOmniTypeResult::DBNFOmniTypeResult()
{
    this->value = NULL;
    this->result = false;
}

void DBNFOmniTypeResult::SetValue(OmniPointer<DBNFOmniType> new_value)
{
    this->value = new_value;
}

OmniPointer<DBNFOmniType> DBNFOmniTypeResult::GetValue()
{
    return this->value;
}

void DBNFOmniTypeResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool DBNFOmniTypeResult::GetResult()
{
    return this->result;
}

void DBNFOmniTypeResult::SetCTCodeFile(OmniPointer<CTCodeFile> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetCTCodeFile(input_value);
}

void DBNFOmniTypeResult::SetExternalDefinition(OmniPointer<ExternalDefinition> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetExternalDefinition(input_value);
}

void DBNFOmniTypeResult::SetUnmanagedType(OmniPointer<UnmanagedType> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetUnmanagedType(input_value);
}

void DBNFOmniTypeResult::SetDefinition(OmniPointer<Definition> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetDefinition(input_value);
}

void DBNFOmniTypeResult::SetInterfaceDef(OmniPointer<InterfaceDef> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetInterfaceDef(input_value);
}

void DBNFOmniTypeResult::SetClassDef(OmniPointer<ClassDef> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetClassDef(input_value);
}

void DBNFOmniTypeResult::SetImplementationSpec(OmniPointer<ImplementationSpec> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetImplementationSpec(input_value);
}

void DBNFOmniTypeResult::SetContentDeclaration(OmniPointer<ContentDeclaration> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetContentDeclaration(input_value);
}

void DBNFOmniTypeResult::SetContentDefinition(OmniPointer<ContentDefinition> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetContentDefinition(input_value);
}

void DBNFOmniTypeResult::SetPrimativeType(OmniPointer<PrimativeType> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetPrimativeType(input_value);
}

void DBNFOmniTypeResult::SetDefinedType(OmniPointer<DefinedType> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetDefinedType(input_value);
}

void DBNFOmniTypeResult::SetSingletonType(OmniPointer<SingletonType> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetSingletonType(input_value);
}

void DBNFOmniTypeResult::SetDimensionalNote(OmniPointer<DimensionalNote> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetDimensionalNote(input_value);
}

void DBNFOmniTypeResult::SetDimensionalType(OmniPointer<DimensionalType> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetDimensionalType(input_value);
}

void DBNFOmniTypeResult::SetMapNote(OmniPointer<MapNote> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetMapNote(input_value);
}

void DBNFOmniTypeResult::SetMapType(OmniPointer<MapType> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetMapType(input_value);
}

void DBNFOmniTypeResult::SetValueType(OmniPointer<ValueType> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetValueType(input_value);
}

void DBNFOmniTypeResult::SetParameterListDef(OmniPointer<ParameterListDef> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetParameterListDef(input_value);
}

void DBNFOmniTypeResult::SetParameterList(OmniPointer<ParameterList> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetParameterList(input_value);
}

void DBNFOmniTypeResult::SetCodeBlock(OmniPointer<CodeBlock> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetCodeBlock(input_value);
}

void DBNFOmniTypeResult::SetDeclarationAssign(OmniPointer<DeclarationAssign> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetDeclarationAssign(input_value);
}

void DBNFOmniTypeResult::SetDeclaration(OmniPointer<Declaration> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetDeclaration(input_value);
}

void DBNFOmniTypeResult::SetAssignment(OmniPointer<Assignment> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetAssignment(input_value);
}

void DBNFOmniTypeResult::SetReturn(OmniPointer<Return> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetReturn(input_value);
}

void DBNFOmniTypeResult::SetElseTail(OmniPointer<ElseTail> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetElseTail(input_value);
}

void DBNFOmniTypeResult::SetConditional(OmniPointer<Conditional> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetConditional(input_value);
}

void DBNFOmniTypeResult::SetLoop(OmniPointer<Loop> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetLoop(input_value);
}

void DBNFOmniTypeResult::SetCall(OmniPointer<Call> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetCall(input_value);
}

void DBNFOmniTypeResult::SetAllocate(OmniPointer<Allocate> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetAllocate(input_value);
}

void DBNFOmniTypeResult::SetInstruction(OmniPointer<Instruction> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetInstruction(input_value);
}

void DBNFOmniTypeResult::SetRValueSingle(OmniPointer<RValueSingle> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetRValueSingle(input_value);
}

void DBNFOmniTypeResult::SetRValueTail(OmniPointer<RValueTail> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetRValueTail(input_value);
}

void DBNFOmniTypeResult::SetRValue(OmniPointer<RValue> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetRValue(input_value);
}

void DBNFOmniTypeResult::SetBinaryOperator(OmniPointer<BinaryOperator> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetBinaryOperator(input_value);
}

void DBNFOmniTypeResult::SetUnaryOperator(OmniPointer<UnaryOperator> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetUnaryOperator(input_value);
}

void DBNFOmniTypeResult::SetComment(OmniPointer<Comment> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetComment(input_value);
}

void DBNFOmniTypeResult::SetNonStarCharacter(OmniPointer<NonStarCharacter> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetNonStarCharacter(input_value);
}

void DBNFOmniTypeResult::SetNonSlashCharacter(OmniPointer<NonSlashCharacter> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetNonSlashCharacter(input_value);
}

void DBNFOmniTypeResult::SetCommentContent(OmniPointer<CommentContent> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetCommentContent(input_value);
}

void DBNFOmniTypeResult::SetQualfiedName(OmniPointer<QualfiedName> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetQualfiedName(input_value);
}

void DBNFOmniTypeResult::SetNameTail(OmniPointer<NameTail> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetNameTail(input_value);
}

void DBNFOmniTypeResult::SetName(OmniPointer<Name> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetName(input_value);
}

void DBNFOmniTypeResult::SetNameCharacter(OmniPointer<NameCharacter> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetNameCharacter(input_value);
}

void DBNFOmniTypeResult::SetBoolean(OmniPointer<Boolean> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetBoolean(input_value);
}

void DBNFOmniTypeResult::SetByte(OmniPointer<Byte> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetByte(input_value);
}

void DBNFOmniTypeResult::SetByteDigit(OmniPointer<ByteDigit> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetByteDigit(input_value);
}

void DBNFOmniTypeResult::SetNegative(OmniPointer<Negative> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetNegative(input_value);
}

void DBNFOmniTypeResult::SetDecimal(OmniPointer<Decimal> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetDecimal(input_value);
}

void DBNFOmniTypeResult::SetNumber(OmniPointer<Number> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetNumber(input_value);
}

void DBNFOmniTypeResult::SetDigit(OmniPointer<Digit> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetDigit(input_value);
}

void DBNFOmniTypeResult::SetLiteral(OmniPointer<Literal> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetLiteral(input_value);
}

void DBNFOmniTypeResult::SetLiteralCharacter(OmniPointer<LiteralCharacter> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetLiteralCharacter(input_value);
}

void DBNFOmniTypeResult::SetWhitespace(OmniPointer<Whitespace> input_value)
{
    this->value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
    this->value->SetWhitespace(input_value);
}

DBNFOmniTypeListResult::DBNFOmniTypeListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void DBNFOmniTypeListResult::SetValue(std::vector<OmniPointer<DBNFOmniType>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<DBNFOmniType>> DBNFOmniTypeListResult::GetValue()
{
    return this->value;
}

void DBNFOmniTypeListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool DBNFOmniTypeListResult::GetResult()
{
    return this->result;
}

void DBNFOmniTypeListResult::SetCTCodeFile(std::vector<OmniPointer<CTCodeFile>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetCTCodeFile(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetExternalDefinition(std::vector<OmniPointer<ExternalDefinition>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetExternalDefinition(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetUnmanagedType(std::vector<OmniPointer<UnmanagedType>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetUnmanagedType(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetDefinition(std::vector<OmniPointer<Definition>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetDefinition(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetInterfaceDef(std::vector<OmniPointer<InterfaceDef>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetInterfaceDef(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetClassDef(std::vector<OmniPointer<ClassDef>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetClassDef(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetImplementationSpec(std::vector<OmniPointer<ImplementationSpec>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetImplementationSpec(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetContentDeclaration(std::vector<OmniPointer<ContentDeclaration>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetContentDeclaration(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetContentDefinition(std::vector<OmniPointer<ContentDefinition>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetContentDefinition(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetPrimativeType(std::vector<OmniPointer<PrimativeType>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetPrimativeType(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetDefinedType(std::vector<OmniPointer<DefinedType>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetDefinedType(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetSingletonType(std::vector<OmniPointer<SingletonType>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetSingletonType(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetDimensionalNote(std::vector<OmniPointer<DimensionalNote>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetDimensionalNote(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetDimensionalType(std::vector<OmniPointer<DimensionalType>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetDimensionalType(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetMapNote(std::vector<OmniPointer<MapNote>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetMapNote(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetMapType(std::vector<OmniPointer<MapType>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetMapType(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetValueType(std::vector<OmniPointer<ValueType>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetValueType(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetParameterListDef(std::vector<OmniPointer<ParameterListDef>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetParameterListDef(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetParameterList(std::vector<OmniPointer<ParameterList>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetParameterList(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetCodeBlock(std::vector<OmniPointer<CodeBlock>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetCodeBlock(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetDeclarationAssign(std::vector<OmniPointer<DeclarationAssign>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetDeclarationAssign(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetDeclaration(std::vector<OmniPointer<Declaration>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetDeclaration(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetAssignment(std::vector<OmniPointer<Assignment>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetAssignment(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetReturn(std::vector<OmniPointer<Return>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetReturn(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetElseTail(std::vector<OmniPointer<ElseTail>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetElseTail(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetConditional(std::vector<OmniPointer<Conditional>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetConditional(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetLoop(std::vector<OmniPointer<Loop>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetLoop(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetCall(std::vector<OmniPointer<Call>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetCall(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetAllocate(std::vector<OmniPointer<Allocate>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetAllocate(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetInstruction(std::vector<OmniPointer<Instruction>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetInstruction(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetRValueSingle(std::vector<OmniPointer<RValueSingle>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetRValueSingle(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetRValueTail(std::vector<OmniPointer<RValueTail>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetRValueTail(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetRValue(std::vector<OmniPointer<RValue>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetRValue(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetBinaryOperator(std::vector<OmniPointer<BinaryOperator>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetBinaryOperator(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetUnaryOperator(std::vector<OmniPointer<UnaryOperator>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetUnaryOperator(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetComment(std::vector<OmniPointer<Comment>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetComment(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetNonStarCharacter(std::vector<OmniPointer<NonStarCharacter>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetNonStarCharacter(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetNonSlashCharacter(std::vector<OmniPointer<NonSlashCharacter>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetNonSlashCharacter(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetCommentContent(std::vector<OmniPointer<CommentContent>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetCommentContent(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetQualfiedName(std::vector<OmniPointer<QualfiedName>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetQualfiedName(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetNameTail(std::vector<OmniPointer<NameTail>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetNameTail(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetName(std::vector<OmniPointer<Name>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetName(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetNameCharacter(std::vector<OmniPointer<NameCharacter>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetNameCharacter(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetBoolean(std::vector<OmniPointer<Boolean>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetBoolean(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetByte(std::vector<OmniPointer<Byte>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetByte(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetByteDigit(std::vector<OmniPointer<ByteDigit>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetByteDigit(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetNegative(std::vector<OmniPointer<Negative>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetNegative(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetDecimal(std::vector<OmniPointer<Decimal>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetDecimal(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetNumber(std::vector<OmniPointer<Number>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetNumber(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetDigit(std::vector<OmniPointer<Digit>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetDigit(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetLiteral(std::vector<OmniPointer<Literal>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetLiteral(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetLiteralCharacter(std::vector<OmniPointer<LiteralCharacter>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetLiteralCharacter(Element(input_value,index));
        index = index+1;
    }
}

void DBNFOmniTypeListResult::SetWhitespace(std::vector<OmniPointer<Whitespace>> input_value)
{
    int index = 0;
    while (index<Size(input_value))
    {
        OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetWhitespace(Element(input_value,index));
        index = index+1;
    }
}

LargeString::LargeString()
{
    this->data = "";
}

void LargeString::SetData(std::string new_data)
{
    this->data = new_data;
}

std::string LargeString::GetData()
{
    return this->data;
}

int LargeString::GetIntAt(int offset)
{
    return IntAt(this->data,offset);
}

std::string LargeString::GetAt(int offset)
{
    return At(this->data,offset);
}

LengthString::LengthString()
{
    this->data = NULL;
    this->start = 0;
    this->length = 0;
}

void LengthString::SetData(OmniPointer<LargeString> new_data)
{
    this->data = new_data;
}

OmniPointer<LargeString> LengthString::GetData()
{
    return this->data;
}

void LengthString::SetStart(int new_start)
{
    this->start = new_start;
}

int LengthString::GetStart()
{
    return this->start;
}

void LengthString::SetLength(int new_length)
{
    this->length = new_length;
}

int LengthString::GetLength()
{
    return this->length;
}

std::string LengthString::GetString()
{
    std::string deep_data = this->data->GetData();
    std::string result = "";
    int index = this->start;
    int end = this->start+this->length;
    while (index<end)
    {
        result = Concat(result,At(deep_data,index));
        index = index+1;
    }
    return result;
}

CTCodeFileParser::CTCodeFileParser()
{
    this->parser_network = NULL;
}

void CTCodeFileParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool CTCodeFileParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<CTCodeFileResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<CTCodeFile> instance = std::shared_ptr<CTCodeFile>(new CTCodeFile());
    OmniPointer<DefinitionListResult> definitions_field = std::shared_ptr<DefinitionListResult>(new DefinitionListResult());
    OmniPointer<UnmanagedTypeListResult> unmanaged_types_field = std::shared_ptr<UnmanagedTypeListResult>(new UnmanagedTypeListResult());
    OmniPointer<ExternalDefinitionListResult> declarations_field = std::shared_ptr<ExternalDefinitionListResult>(new ExternalDefinitionListResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&external_definition_parser_instance->ParseManySave(index,declarations_field,0,-1)&&unmanaged_type_parser_instance->ParseManySave(index,unmanaged_types_field,0,-1)&&definition_parser_instance->ParseManySave(index,definitions_field,0,-1))
    {
        instance->SetDefinitions(definitions_field->GetValue());
        instance->SetUnmanagedTypes(unmanaged_types_field->GetValue());
        instance->SetDeclarations(declarations_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        definitions_field = std::shared_ptr<DefinitionListResult>(new DefinitionListResult());
        unmanaged_types_field = std::shared_ptr<UnmanagedTypeListResult>(new UnmanagedTypeListResult());
        declarations_field = std::shared_ptr<ExternalDefinitionListResult>(new ExternalDefinitionListResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool CTCodeFileParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<CTCodeFileResult> result = std::shared_ptr<CTCodeFileResult>(new CTCodeFileResult());
    return this->ParseSingleSave(index,result);
}

bool CTCodeFileParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<CTCodeFileResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool CTCodeFileParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<CTCodeFileResult> result = std::shared_ptr<CTCodeFileResult>(new CTCodeFileResult());
    return this->ParseOptionalSave(index,result);
}

bool CTCodeFileParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<CTCodeFileListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<CTCodeFile>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<CTCodeFileResult> result = std::shared_ptr<CTCodeFileResult>(new CTCodeFileResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool CTCodeFileParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<CTCodeFileListResult> result = std::shared_ptr<CTCodeFileListResult>(new CTCodeFileListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

CTCodeFileResult::CTCodeFileResult()
{
    this->value = NULL;
    this->result = false;
}

void CTCodeFileResult::SetValue(OmniPointer<CTCodeFile> new_value)
{
    this->value = new_value;
}

OmniPointer<CTCodeFile> CTCodeFileResult::GetValue()
{
    return this->value;
}

void CTCodeFileResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool CTCodeFileResult::GetResult()
{
    return this->result;
}

CTCodeFileListResult::CTCodeFileListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void CTCodeFileListResult::SetValue(std::vector<OmniPointer<CTCodeFile>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<CTCodeFile>> CTCodeFileListResult::GetValue()
{
    return this->value;
}

void CTCodeFileListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool CTCodeFileListResult::GetResult()
{
    return this->result;
}

CTCodeFile::CTCodeFile()
{
    this->length_string = NULL;
    /*this->definitions_field = NO_DEFAULT;*/
    /*this->unmanaged_types_field = NO_DEFAULT;*/
    /*this->declarations_field = NO_DEFAULT;*/
}

void CTCodeFile::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string CTCodeFile::UnParse()
{
    return this->length_string->GetString();
}

void CTCodeFile::SetDefinitions(std::vector<OmniPointer<Definition>> input_value)
{
    this->definitions_field = input_value;
}

std::vector<OmniPointer<Definition>> CTCodeFile::GetDefinitions()
{
    return this->definitions_field;
}

void CTCodeFile::SetUnmanagedTypes(std::vector<OmniPointer<UnmanagedType>> input_value)
{
    this->unmanaged_types_field = input_value;
}

std::vector<OmniPointer<UnmanagedType>> CTCodeFile::GetUnmanagedTypes()
{
    return this->unmanaged_types_field;
}

void CTCodeFile::SetDeclarations(std::vector<OmniPointer<ExternalDefinition>> input_value)
{
    this->declarations_field = input_value;
}

std::vector<OmniPointer<ExternalDefinition>> CTCodeFile::GetDeclarations()
{
    return this->declarations_field;
}

ExternalDefinitionParser::ExternalDefinitionParser()
{
    this->parser_network = NULL;
}

void ExternalDefinitionParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool ExternalDefinitionParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<ExternalDefinitionResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<ExternalDefinition> instance = std::shared_ptr<ExternalDefinition>(new ExternalDefinition());
    OmniPointer<QualfiedNameResult> exdef_field = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&string_parser_instance->ParseSingle(index,std::string("exdef"))&&whitespace_parser_instance->ParseMany(index,0,-1)&&qualfied_name_parser_instance->ParseSingleSave(index,exdef_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string(";"))&&whitespace_parser_instance->ParseMany(index,0,-1))
    {
        instance->SetExdef(exdef_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        exdef_field = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool ExternalDefinitionParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<ExternalDefinitionResult> result = std::shared_ptr<ExternalDefinitionResult>(new ExternalDefinitionResult());
    return this->ParseSingleSave(index,result);
}

bool ExternalDefinitionParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ExternalDefinitionResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool ExternalDefinitionParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<ExternalDefinitionResult> result = std::shared_ptr<ExternalDefinitionResult>(new ExternalDefinitionResult());
    return this->ParseOptionalSave(index,result);
}

bool ExternalDefinitionParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<ExternalDefinitionListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<ExternalDefinition>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<ExternalDefinitionResult> result = std::shared_ptr<ExternalDefinitionResult>(new ExternalDefinitionResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool ExternalDefinitionParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<ExternalDefinitionListResult> result = std::shared_ptr<ExternalDefinitionListResult>(new ExternalDefinitionListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

ExternalDefinitionResult::ExternalDefinitionResult()
{
    this->value = NULL;
    this->result = false;
}

void ExternalDefinitionResult::SetValue(OmniPointer<ExternalDefinition> new_value)
{
    this->value = new_value;
}

OmniPointer<ExternalDefinition> ExternalDefinitionResult::GetValue()
{
    return this->value;
}

void ExternalDefinitionResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool ExternalDefinitionResult::GetResult()
{
    return this->result;
}

ExternalDefinitionListResult::ExternalDefinitionListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void ExternalDefinitionListResult::SetValue(std::vector<OmniPointer<ExternalDefinition>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<ExternalDefinition>> ExternalDefinitionListResult::GetValue()
{
    return this->value;
}

void ExternalDefinitionListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool ExternalDefinitionListResult::GetResult()
{
    return this->result;
}

ExternalDefinition::ExternalDefinition()
{
    this->length_string = NULL;
    this->exdef_field = NULL;
}

void ExternalDefinition::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string ExternalDefinition::UnParse()
{
    return this->length_string->GetString();
}

void ExternalDefinition::SetExdef(OmniPointer<QualfiedName> input_value)
{
    this->exdef_field = input_value;
}

OmniPointer<QualfiedName> ExternalDefinition::GetExdef()
{
    return this->exdef_field;
}

UnmanagedTypeParser::UnmanagedTypeParser()
{
    this->parser_network = NULL;
}

void UnmanagedTypeParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool UnmanagedTypeParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<UnmanagedTypeResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<UnmanagedType> instance = std::shared_ptr<UnmanagedType>(new UnmanagedType());
    OmniPointer<QualfiedNameResult> unmanaged_type_field = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&string_parser_instance->ParseSingle(index,std::string("unmanaged"))&&whitespace_parser_instance->ParseMany(index,0,-1)&&qualfied_name_parser_instance->ParseSingleSave(index,unmanaged_type_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string(";"))&&whitespace_parser_instance->ParseMany(index,0,-1))
    {
        instance->SetUnmanagedType(unmanaged_type_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        unmanaged_type_field = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool UnmanagedTypeParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<UnmanagedTypeResult> result = std::shared_ptr<UnmanagedTypeResult>(new UnmanagedTypeResult());
    return this->ParseSingleSave(index,result);
}

bool UnmanagedTypeParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<UnmanagedTypeResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool UnmanagedTypeParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<UnmanagedTypeResult> result = std::shared_ptr<UnmanagedTypeResult>(new UnmanagedTypeResult());
    return this->ParseOptionalSave(index,result);
}

bool UnmanagedTypeParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<UnmanagedTypeListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<UnmanagedType>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<UnmanagedTypeResult> result = std::shared_ptr<UnmanagedTypeResult>(new UnmanagedTypeResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool UnmanagedTypeParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<UnmanagedTypeListResult> result = std::shared_ptr<UnmanagedTypeListResult>(new UnmanagedTypeListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

UnmanagedTypeResult::UnmanagedTypeResult()
{
    this->value = NULL;
    this->result = false;
}

void UnmanagedTypeResult::SetValue(OmniPointer<UnmanagedType> new_value)
{
    this->value = new_value;
}

OmniPointer<UnmanagedType> UnmanagedTypeResult::GetValue()
{
    return this->value;
}

void UnmanagedTypeResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool UnmanagedTypeResult::GetResult()
{
    return this->result;
}

UnmanagedTypeListResult::UnmanagedTypeListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void UnmanagedTypeListResult::SetValue(std::vector<OmniPointer<UnmanagedType>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<UnmanagedType>> UnmanagedTypeListResult::GetValue()
{
    return this->value;
}

void UnmanagedTypeListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool UnmanagedTypeListResult::GetResult()
{
    return this->result;
}

UnmanagedType::UnmanagedType()
{
    this->length_string = NULL;
    this->unmanaged_type_field = NULL;
}

void UnmanagedType::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string UnmanagedType::UnParse()
{
    return this->length_string->GetString();
}

void UnmanagedType::SetUnmanagedType(OmniPointer<QualfiedName> input_value)
{
    this->unmanaged_type_field = input_value;
}

OmniPointer<QualfiedName> UnmanagedType::GetUnmanagedType()
{
    return this->unmanaged_type_field;
}

DefinitionParser::DefinitionParser()
{
    this->parser_network = NULL;
}

void DefinitionParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool DefinitionParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<DefinitionResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<Definition> instance = std::shared_ptr<Definition>(new Definition());
    OmniPointer<ClassDefResult> class_def_field = std::shared_ptr<ClassDefResult>(new ClassDefResult());
    OmniPointer<InterfaceDefResult> interface_def_field = std::shared_ptr<InterfaceDefResult>(new InterfaceDefResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&interface_def_parser_instance->ParseSingleSave(index,interface_def_field))
    {
        instance->SetClassDef(class_def_field->GetValue());
        instance->SetInterfaceDef(interface_def_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        class_def_field = std::shared_ptr<ClassDefResult>(new ClassDefResult());
        interface_def_field = std::shared_ptr<InterfaceDefResult>(new InterfaceDefResult());
    }
    if (true&&class_def_parser_instance->ParseSingleSave(index,class_def_field))
    {
        instance->SetClassDef(class_def_field->GetValue());
        instance->SetInterfaceDef(interface_def_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        class_def_field = std::shared_ptr<ClassDefResult>(new ClassDefResult());
        interface_def_field = std::shared_ptr<InterfaceDefResult>(new InterfaceDefResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool DefinitionParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<DefinitionResult> result = std::shared_ptr<DefinitionResult>(new DefinitionResult());
    return this->ParseSingleSave(index,result);
}

bool DefinitionParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<DefinitionResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool DefinitionParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<DefinitionResult> result = std::shared_ptr<DefinitionResult>(new DefinitionResult());
    return this->ParseOptionalSave(index,result);
}

bool DefinitionParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<DefinitionListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<Definition>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<DefinitionResult> result = std::shared_ptr<DefinitionResult>(new DefinitionResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool DefinitionParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<DefinitionListResult> result = std::shared_ptr<DefinitionListResult>(new DefinitionListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

DefinitionResult::DefinitionResult()
{
    this->value = NULL;
    this->result = false;
}

void DefinitionResult::SetValue(OmniPointer<Definition> new_value)
{
    this->value = new_value;
}

OmniPointer<Definition> DefinitionResult::GetValue()
{
    return this->value;
}

void DefinitionResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool DefinitionResult::GetResult()
{
    return this->result;
}

DefinitionListResult::DefinitionListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void DefinitionListResult::SetValue(std::vector<OmniPointer<Definition>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<Definition>> DefinitionListResult::GetValue()
{
    return this->value;
}

void DefinitionListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool DefinitionListResult::GetResult()
{
    return this->result;
}

Definition::Definition()
{
    this->length_string = NULL;
    this->class_def_field = NULL;
    this->interface_def_field = NULL;
}

void Definition::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string Definition::UnParse()
{
    return this->length_string->GetString();
}

void Definition::SetClassDef(OmniPointer<ClassDef> input_value)
{
    this->class_def_field = input_value;
}

OmniPointer<ClassDef> Definition::GetClassDef()
{
    return this->class_def_field;
}

void Definition::SetInterfaceDef(OmniPointer<InterfaceDef> input_value)
{
    this->interface_def_field = input_value;
}

OmniPointer<InterfaceDef> Definition::GetInterfaceDef()
{
    return this->interface_def_field;
}

InterfaceDefParser::InterfaceDefParser()
{
    this->parser_network = NULL;
}

void InterfaceDefParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool InterfaceDefParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<InterfaceDefResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<InterfaceDef> instance = std::shared_ptr<InterfaceDef>(new InterfaceDef());
    OmniPointer<ContentDeclarationListResult> declarations_field = std::shared_ptr<ContentDeclarationListResult>(new ContentDeclarationListResult());
    OmniPointer<NameResult> name_field = std::shared_ptr<NameResult>(new NameResult());
    OmniPointer<CommentResult> comment_field = std::shared_ptr<CommentResult>(new CommentResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&comment_parser_instance->ParseOptionalSave(index,comment_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string("interface"))&&whitespace_parser_instance->ParseMany(index,1,-1)&&name_parser_instance->ParseSingleSave(index,name_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string("{"))&&whitespace_parser_instance->ParseMany(index,0,-1)&&content_declaration_parser_instance->ParseManySave(index,declarations_field,0,-1)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string("}"))&&whitespace_parser_instance->ParseMany(index,0,-1))
    {
        instance->SetDeclarations(declarations_field->GetValue());
        instance->SetName(name_field->GetValue());
        instance->SetComment(comment_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        declarations_field = std::shared_ptr<ContentDeclarationListResult>(new ContentDeclarationListResult());
        name_field = std::shared_ptr<NameResult>(new NameResult());
        comment_field = std::shared_ptr<CommentResult>(new CommentResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool InterfaceDefParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<InterfaceDefResult> result = std::shared_ptr<InterfaceDefResult>(new InterfaceDefResult());
    return this->ParseSingleSave(index,result);
}

bool InterfaceDefParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<InterfaceDefResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool InterfaceDefParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<InterfaceDefResult> result = std::shared_ptr<InterfaceDefResult>(new InterfaceDefResult());
    return this->ParseOptionalSave(index,result);
}

bool InterfaceDefParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<InterfaceDefListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<InterfaceDef>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<InterfaceDefResult> result = std::shared_ptr<InterfaceDefResult>(new InterfaceDefResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool InterfaceDefParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<InterfaceDefListResult> result = std::shared_ptr<InterfaceDefListResult>(new InterfaceDefListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

InterfaceDefResult::InterfaceDefResult()
{
    this->value = NULL;
    this->result = false;
}

void InterfaceDefResult::SetValue(OmniPointer<InterfaceDef> new_value)
{
    this->value = new_value;
}

OmniPointer<InterfaceDef> InterfaceDefResult::GetValue()
{
    return this->value;
}

void InterfaceDefResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool InterfaceDefResult::GetResult()
{
    return this->result;
}

InterfaceDefListResult::InterfaceDefListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void InterfaceDefListResult::SetValue(std::vector<OmniPointer<InterfaceDef>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<InterfaceDef>> InterfaceDefListResult::GetValue()
{
    return this->value;
}

void InterfaceDefListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool InterfaceDefListResult::GetResult()
{
    return this->result;
}

InterfaceDef::InterfaceDef()
{
    this->length_string = NULL;
    /*this->declarations_field = NO_DEFAULT;*/
    this->name_field = NULL;
    this->comment_field = NULL;
}

void InterfaceDef::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string InterfaceDef::UnParse()
{
    return this->length_string->GetString();
}

void InterfaceDef::SetDeclarations(std::vector<OmniPointer<ContentDeclaration>> input_value)
{
    this->declarations_field = input_value;
}

std::vector<OmniPointer<ContentDeclaration>> InterfaceDef::GetDeclarations()
{
    return this->declarations_field;
}

void InterfaceDef::SetName(OmniPointer<Name> input_value)
{
    this->name_field = input_value;
}

OmniPointer<Name> InterfaceDef::GetName()
{
    return this->name_field;
}

void InterfaceDef::SetComment(OmniPointer<Comment> input_value)
{
    this->comment_field = input_value;
}

OmniPointer<Comment> InterfaceDef::GetComment()
{
    return this->comment_field;
}

ClassDefParser::ClassDefParser()
{
    this->parser_network = NULL;
}

void ClassDefParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool ClassDefParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<ClassDefResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<ClassDef> instance = std::shared_ptr<ClassDef>(new ClassDef());
    OmniPointer<ImplementationSpecResult> implementing_field = std::shared_ptr<ImplementationSpecResult>(new ImplementationSpecResult());
    OmniPointer<NameResult> name_field = std::shared_ptr<NameResult>(new NameResult());
    OmniPointer<ContentDefinitionListResult> definitions_field = std::shared_ptr<ContentDefinitionListResult>(new ContentDefinitionListResult());
    OmniPointer<CommentResult> comment_field = std::shared_ptr<CommentResult>(new CommentResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&comment_parser_instance->ParseOptionalSave(index,comment_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string("class"))&&whitespace_parser_instance->ParseMany(index,1,-1)&&name_parser_instance->ParseSingleSave(index,name_field)&&implementation_spec_parser_instance->ParseOptionalSave(index,implementing_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string("{"))&&whitespace_parser_instance->ParseMany(index,0,-1)&&content_definition_parser_instance->ParseManySave(index,definitions_field,0,-1)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string("}"))&&whitespace_parser_instance->ParseMany(index,0,-1))
    {
        instance->SetImplementing(implementing_field->GetValue());
        instance->SetName(name_field->GetValue());
        instance->SetDefinitions(definitions_field->GetValue());
        instance->SetComment(comment_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        implementing_field = std::shared_ptr<ImplementationSpecResult>(new ImplementationSpecResult());
        name_field = std::shared_ptr<NameResult>(new NameResult());
        definitions_field = std::shared_ptr<ContentDefinitionListResult>(new ContentDefinitionListResult());
        comment_field = std::shared_ptr<CommentResult>(new CommentResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool ClassDefParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<ClassDefResult> result = std::shared_ptr<ClassDefResult>(new ClassDefResult());
    return this->ParseSingleSave(index,result);
}

bool ClassDefParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ClassDefResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool ClassDefParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<ClassDefResult> result = std::shared_ptr<ClassDefResult>(new ClassDefResult());
    return this->ParseOptionalSave(index,result);
}

bool ClassDefParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<ClassDefListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<ClassDef>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<ClassDefResult> result = std::shared_ptr<ClassDefResult>(new ClassDefResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool ClassDefParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<ClassDefListResult> result = std::shared_ptr<ClassDefListResult>(new ClassDefListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

ClassDefResult::ClassDefResult()
{
    this->value = NULL;
    this->result = false;
}

void ClassDefResult::SetValue(OmniPointer<ClassDef> new_value)
{
    this->value = new_value;
}

OmniPointer<ClassDef> ClassDefResult::GetValue()
{
    return this->value;
}

void ClassDefResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool ClassDefResult::GetResult()
{
    return this->result;
}

ClassDefListResult::ClassDefListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void ClassDefListResult::SetValue(std::vector<OmniPointer<ClassDef>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<ClassDef>> ClassDefListResult::GetValue()
{
    return this->value;
}

void ClassDefListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool ClassDefListResult::GetResult()
{
    return this->result;
}

ClassDef::ClassDef()
{
    this->length_string = NULL;
    this->implementing_field = NULL;
    this->name_field = NULL;
    /*this->definitions_field = NO_DEFAULT;*/
    this->comment_field = NULL;
}

void ClassDef::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string ClassDef::UnParse()
{
    return this->length_string->GetString();
}

void ClassDef::SetImplementing(OmniPointer<ImplementationSpec> input_value)
{
    this->implementing_field = input_value;
}

OmniPointer<ImplementationSpec> ClassDef::GetImplementing()
{
    return this->implementing_field;
}

void ClassDef::SetName(OmniPointer<Name> input_value)
{
    this->name_field = input_value;
}

OmniPointer<Name> ClassDef::GetName()
{
    return this->name_field;
}

void ClassDef::SetDefinitions(std::vector<OmniPointer<ContentDefinition>> input_value)
{
    this->definitions_field = input_value;
}

std::vector<OmniPointer<ContentDefinition>> ClassDef::GetDefinitions()
{
    return this->definitions_field;
}

void ClassDef::SetComment(OmniPointer<Comment> input_value)
{
    this->comment_field = input_value;
}

OmniPointer<Comment> ClassDef::GetComment()
{
    return this->comment_field;
}

ImplementationSpecParser::ImplementationSpecParser()
{
    this->parser_network = NULL;
}

void ImplementationSpecParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool ImplementationSpecParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<ImplementationSpecResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<ImplementationSpec> instance = std::shared_ptr<ImplementationSpec>(new ImplementationSpec());
    OmniPointer<QualfiedNameResult> interface_field = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&whitespace_parser_instance->ParseMany(index,1,-1)&&string_parser_instance->ParseSingle(index,std::string("implements"))&&whitespace_parser_instance->ParseMany(index,1,-1)&&qualfied_name_parser_instance->ParseSingleSave(index,interface_field)&&whitespace_parser_instance->ParseMany(index,0,-1))
    {
        instance->SetInterface(interface_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        interface_field = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool ImplementationSpecParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<ImplementationSpecResult> result = std::shared_ptr<ImplementationSpecResult>(new ImplementationSpecResult());
    return this->ParseSingleSave(index,result);
}

bool ImplementationSpecParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ImplementationSpecResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool ImplementationSpecParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<ImplementationSpecResult> result = std::shared_ptr<ImplementationSpecResult>(new ImplementationSpecResult());
    return this->ParseOptionalSave(index,result);
}

bool ImplementationSpecParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<ImplementationSpecListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<ImplementationSpec>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<ImplementationSpecResult> result = std::shared_ptr<ImplementationSpecResult>(new ImplementationSpecResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool ImplementationSpecParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<ImplementationSpecListResult> result = std::shared_ptr<ImplementationSpecListResult>(new ImplementationSpecListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

ImplementationSpecResult::ImplementationSpecResult()
{
    this->value = NULL;
    this->result = false;
}

void ImplementationSpecResult::SetValue(OmniPointer<ImplementationSpec> new_value)
{
    this->value = new_value;
}

OmniPointer<ImplementationSpec> ImplementationSpecResult::GetValue()
{
    return this->value;
}

void ImplementationSpecResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool ImplementationSpecResult::GetResult()
{
    return this->result;
}

ImplementationSpecListResult::ImplementationSpecListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void ImplementationSpecListResult::SetValue(std::vector<OmniPointer<ImplementationSpec>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<ImplementationSpec>> ImplementationSpecListResult::GetValue()
{
    return this->value;
}

void ImplementationSpecListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool ImplementationSpecListResult::GetResult()
{
    return this->result;
}

ImplementationSpec::ImplementationSpec()
{
    this->length_string = NULL;
    this->interface_field = NULL;
}

void ImplementationSpec::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string ImplementationSpec::UnParse()
{
    return this->length_string->GetString();
}

void ImplementationSpec::SetInterface(OmniPointer<QualfiedName> input_value)
{
    this->interface_field = input_value;
}

OmniPointer<QualfiedName> ImplementationSpec::GetInterface()
{
    return this->interface_field;
}

ContentDeclarationParser::ContentDeclarationParser()
{
    this->parser_network = NULL;
}

void ContentDeclarationParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool ContentDeclarationParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<ContentDeclarationResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<ContentDeclaration> instance = std::shared_ptr<ContentDeclaration>(new ContentDeclaration());
    OmniPointer<ParameterListDefResult> parameters_field = std::shared_ptr<ParameterListDefResult>(new ParameterListDefResult());
    OmniPointer<NameResult> name_field = std::shared_ptr<NameResult>(new NameResult());
    OmniPointer<ValueTypeResult> type_field = std::shared_ptr<ValueTypeResult>(new ValueTypeResult());
    OmniPointer<CommentResult> comment_field = std::shared_ptr<CommentResult>(new CommentResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&comment_parser_instance->ParseOptionalSave(index,comment_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string("function"))&&whitespace_parser_instance->ParseMany(index,1,-1)&&value_type_parser_instance->ParseSingleSave(index,type_field)&&whitespace_parser_instance->ParseMany(index,1,-1)&&name_parser_instance->ParseSingleSave(index,name_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string("("))&&whitespace_parser_instance->ParseMany(index,0,-1)&&parameter_list_def_parser_instance->ParseOptionalSave(index,parameters_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string(")"))&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string(";"))&&whitespace_parser_instance->ParseMany(index,0,-1))
    {
        instance->SetParameters(parameters_field->GetValue());
        instance->SetName(name_field->GetValue());
        instance->SetType(type_field->GetValue());
        instance->SetComment(comment_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        parameters_field = std::shared_ptr<ParameterListDefResult>(new ParameterListDefResult());
        name_field = std::shared_ptr<NameResult>(new NameResult());
        type_field = std::shared_ptr<ValueTypeResult>(new ValueTypeResult());
        comment_field = std::shared_ptr<CommentResult>(new CommentResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool ContentDeclarationParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<ContentDeclarationResult> result = std::shared_ptr<ContentDeclarationResult>(new ContentDeclarationResult());
    return this->ParseSingleSave(index,result);
}

bool ContentDeclarationParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ContentDeclarationResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool ContentDeclarationParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<ContentDeclarationResult> result = std::shared_ptr<ContentDeclarationResult>(new ContentDeclarationResult());
    return this->ParseOptionalSave(index,result);
}

bool ContentDeclarationParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<ContentDeclarationListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<ContentDeclaration>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<ContentDeclarationResult> result = std::shared_ptr<ContentDeclarationResult>(new ContentDeclarationResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool ContentDeclarationParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<ContentDeclarationListResult> result = std::shared_ptr<ContentDeclarationListResult>(new ContentDeclarationListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

ContentDeclarationResult::ContentDeclarationResult()
{
    this->value = NULL;
    this->result = false;
}

void ContentDeclarationResult::SetValue(OmniPointer<ContentDeclaration> new_value)
{
    this->value = new_value;
}

OmniPointer<ContentDeclaration> ContentDeclarationResult::GetValue()
{
    return this->value;
}

void ContentDeclarationResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool ContentDeclarationResult::GetResult()
{
    return this->result;
}

ContentDeclarationListResult::ContentDeclarationListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void ContentDeclarationListResult::SetValue(std::vector<OmniPointer<ContentDeclaration>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<ContentDeclaration>> ContentDeclarationListResult::GetValue()
{
    return this->value;
}

void ContentDeclarationListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool ContentDeclarationListResult::GetResult()
{
    return this->result;
}

ContentDeclaration::ContentDeclaration()
{
    this->length_string = NULL;
    this->parameters_field = NULL;
    this->name_field = NULL;
    this->type_field = NULL;
    this->comment_field = NULL;
}

void ContentDeclaration::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string ContentDeclaration::UnParse()
{
    return this->length_string->GetString();
}

void ContentDeclaration::SetParameters(OmniPointer<ParameterListDef> input_value)
{
    this->parameters_field = input_value;
}

OmniPointer<ParameterListDef> ContentDeclaration::GetParameters()
{
    return this->parameters_field;
}

void ContentDeclaration::SetName(OmniPointer<Name> input_value)
{
    this->name_field = input_value;
}

OmniPointer<Name> ContentDeclaration::GetName()
{
    return this->name_field;
}

void ContentDeclaration::SetType(OmniPointer<ValueType> input_value)
{
    this->type_field = input_value;
}

OmniPointer<ValueType> ContentDeclaration::GetType()
{
    return this->type_field;
}

void ContentDeclaration::SetComment(OmniPointer<Comment> input_value)
{
    this->comment_field = input_value;
}

OmniPointer<Comment> ContentDeclaration::GetComment()
{
    return this->comment_field;
}

ContentDefinitionParser::ContentDefinitionParser()
{
    this->parser_network = NULL;
}

void ContentDefinitionParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool ContentDefinitionParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<ContentDefinitionResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<ContentDefinition> instance = std::shared_ptr<ContentDefinition>(new ContentDefinition());
    OmniPointer<CodeBlockResult> function_body_field = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
    OmniPointer<ParameterListDefResult> parameters_field = std::shared_ptr<ParameterListDefResult>(new ParameterListDefResult());
    OmniPointer<NameResult> name_field = std::shared_ptr<NameResult>(new NameResult());
    OmniPointer<ValueTypeResult> type_field = std::shared_ptr<ValueTypeResult>(new ValueTypeResult());
    OmniPointer<CommentResult> comment_field = std::shared_ptr<CommentResult>(new CommentResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&comment_parser_instance->ParseOptionalSave(index,comment_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string("function"))&&whitespace_parser_instance->ParseMany(index,1,-1)&&value_type_parser_instance->ParseSingleSave(index,type_field)&&whitespace_parser_instance->ParseMany(index,1,-1)&&name_parser_instance->ParseSingleSave(index,name_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string("("))&&whitespace_parser_instance->ParseMany(index,0,-1)&&parameter_list_def_parser_instance->ParseOptionalSave(index,parameters_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string(")"))&&whitespace_parser_instance->ParseMany(index,0,-1)&&code_block_parser_instance->ParseSingleSave(index,function_body_field)&&whitespace_parser_instance->ParseMany(index,0,-1))
    {
        instance->SetFunctionBody(function_body_field->GetValue());
        instance->SetParameters(parameters_field->GetValue());
        instance->SetName(name_field->GetValue());
        instance->SetType(type_field->GetValue());
        instance->SetComment(comment_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        function_body_field = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
        parameters_field = std::shared_ptr<ParameterListDefResult>(new ParameterListDefResult());
        name_field = std::shared_ptr<NameResult>(new NameResult());
        type_field = std::shared_ptr<ValueTypeResult>(new ValueTypeResult());
        comment_field = std::shared_ptr<CommentResult>(new CommentResult());
    }
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&comment_parser_instance->ParseOptionalSave(index,comment_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&value_type_parser_instance->ParseSingleSave(index,type_field)&&whitespace_parser_instance->ParseMany(index,1,-1)&&name_parser_instance->ParseSingleSave(index,name_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string(";"))&&whitespace_parser_instance->ParseMany(index,0,-1))
    {
        instance->SetFunctionBody(function_body_field->GetValue());
        instance->SetParameters(parameters_field->GetValue());
        instance->SetName(name_field->GetValue());
        instance->SetType(type_field->GetValue());
        instance->SetComment(comment_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        function_body_field = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
        parameters_field = std::shared_ptr<ParameterListDefResult>(new ParameterListDefResult());
        name_field = std::shared_ptr<NameResult>(new NameResult());
        type_field = std::shared_ptr<ValueTypeResult>(new ValueTypeResult());
        comment_field = std::shared_ptr<CommentResult>(new CommentResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool ContentDefinitionParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<ContentDefinitionResult> result = std::shared_ptr<ContentDefinitionResult>(new ContentDefinitionResult());
    return this->ParseSingleSave(index,result);
}

bool ContentDefinitionParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ContentDefinitionResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool ContentDefinitionParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<ContentDefinitionResult> result = std::shared_ptr<ContentDefinitionResult>(new ContentDefinitionResult());
    return this->ParseOptionalSave(index,result);
}

bool ContentDefinitionParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<ContentDefinitionListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<ContentDefinition>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<ContentDefinitionResult> result = std::shared_ptr<ContentDefinitionResult>(new ContentDefinitionResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool ContentDefinitionParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<ContentDefinitionListResult> result = std::shared_ptr<ContentDefinitionListResult>(new ContentDefinitionListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

ContentDefinitionResult::ContentDefinitionResult()
{
    this->value = NULL;
    this->result = false;
}

void ContentDefinitionResult::SetValue(OmniPointer<ContentDefinition> new_value)
{
    this->value = new_value;
}

OmniPointer<ContentDefinition> ContentDefinitionResult::GetValue()
{
    return this->value;
}

void ContentDefinitionResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool ContentDefinitionResult::GetResult()
{
    return this->result;
}

ContentDefinitionListResult::ContentDefinitionListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void ContentDefinitionListResult::SetValue(std::vector<OmniPointer<ContentDefinition>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<ContentDefinition>> ContentDefinitionListResult::GetValue()
{
    return this->value;
}

void ContentDefinitionListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool ContentDefinitionListResult::GetResult()
{
    return this->result;
}

ContentDefinition::ContentDefinition()
{
    this->length_string = NULL;
    this->function_body_field = NULL;
    this->parameters_field = NULL;
    this->name_field = NULL;
    this->type_field = NULL;
    this->comment_field = NULL;
}

void ContentDefinition::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string ContentDefinition::UnParse()
{
    return this->length_string->GetString();
}

void ContentDefinition::SetFunctionBody(OmniPointer<CodeBlock> input_value)
{
    this->function_body_field = input_value;
}

OmniPointer<CodeBlock> ContentDefinition::GetFunctionBody()
{
    return this->function_body_field;
}

void ContentDefinition::SetParameters(OmniPointer<ParameterListDef> input_value)
{
    this->parameters_field = input_value;
}

OmniPointer<ParameterListDef> ContentDefinition::GetParameters()
{
    return this->parameters_field;
}

void ContentDefinition::SetName(OmniPointer<Name> input_value)
{
    this->name_field = input_value;
}

OmniPointer<Name> ContentDefinition::GetName()
{
    return this->name_field;
}

void ContentDefinition::SetType(OmniPointer<ValueType> input_value)
{
    this->type_field = input_value;
}

OmniPointer<ValueType> ContentDefinition::GetType()
{
    return this->type_field;
}

void ContentDefinition::SetComment(OmniPointer<Comment> input_value)
{
    this->comment_field = input_value;
}

OmniPointer<Comment> ContentDefinition::GetComment()
{
    return this->comment_field;
}

PrimativeTypeParser::PrimativeTypeParser()
{
    this->parser_network = NULL;
}

void PrimativeTypeParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool PrimativeTypeParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<PrimativeTypeResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<PrimativeType> instance = std::shared_ptr<PrimativeType>(new PrimativeType());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&string_parser_instance->ParseSingle(index,std::string("int")))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    if (true&&string_parser_instance->ParseSingle(index,std::string("string")))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    if (true&&string_parser_instance->ParseSingle(index,std::string("bool")))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    if (true&&string_parser_instance->ParseSingle(index,std::string("float")))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    if (true&&string_parser_instance->ParseSingle(index,std::string("void")))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    result->SetResult(false);
    return result->GetResult();
}

bool PrimativeTypeParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<PrimativeTypeResult> result = std::shared_ptr<PrimativeTypeResult>(new PrimativeTypeResult());
    return this->ParseSingleSave(index,result);
}

bool PrimativeTypeParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<PrimativeTypeResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool PrimativeTypeParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<PrimativeTypeResult> result = std::shared_ptr<PrimativeTypeResult>(new PrimativeTypeResult());
    return this->ParseOptionalSave(index,result);
}

bool PrimativeTypeParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<PrimativeTypeListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<PrimativeType>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<PrimativeTypeResult> result = std::shared_ptr<PrimativeTypeResult>(new PrimativeTypeResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool PrimativeTypeParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<PrimativeTypeListResult> result = std::shared_ptr<PrimativeTypeListResult>(new PrimativeTypeListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

PrimativeTypeResult::PrimativeTypeResult()
{
    this->value = NULL;
    this->result = false;
}

void PrimativeTypeResult::SetValue(OmniPointer<PrimativeType> new_value)
{
    this->value = new_value;
}

OmniPointer<PrimativeType> PrimativeTypeResult::GetValue()
{
    return this->value;
}

void PrimativeTypeResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool PrimativeTypeResult::GetResult()
{
    return this->result;
}

PrimativeTypeListResult::PrimativeTypeListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void PrimativeTypeListResult::SetValue(std::vector<OmniPointer<PrimativeType>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<PrimativeType>> PrimativeTypeListResult::GetValue()
{
    return this->value;
}

void PrimativeTypeListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool PrimativeTypeListResult::GetResult()
{
    return this->result;
}

PrimativeType::PrimativeType()
{
    this->length_string = NULL;
}

void PrimativeType::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string PrimativeType::UnParse()
{
    return this->length_string->GetString();
}

DefinedTypeParser::DefinedTypeParser()
{
    this->parser_network = NULL;
}

void DefinedTypeParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool DefinedTypeParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<DefinedTypeResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<DefinedType> instance = std::shared_ptr<DefinedType>(new DefinedType());
    OmniPointer<QualfiedNameResult> name_field = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&qualfied_name_parser_instance->ParseSingleSave(index,name_field))
    {
        instance->SetName(name_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        name_field = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool DefinedTypeParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<DefinedTypeResult> result = std::shared_ptr<DefinedTypeResult>(new DefinedTypeResult());
    return this->ParseSingleSave(index,result);
}

bool DefinedTypeParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<DefinedTypeResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool DefinedTypeParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<DefinedTypeResult> result = std::shared_ptr<DefinedTypeResult>(new DefinedTypeResult());
    return this->ParseOptionalSave(index,result);
}

bool DefinedTypeParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<DefinedTypeListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<DefinedType>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<DefinedTypeResult> result = std::shared_ptr<DefinedTypeResult>(new DefinedTypeResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool DefinedTypeParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<DefinedTypeListResult> result = std::shared_ptr<DefinedTypeListResult>(new DefinedTypeListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

DefinedTypeResult::DefinedTypeResult()
{
    this->value = NULL;
    this->result = false;
}

void DefinedTypeResult::SetValue(OmniPointer<DefinedType> new_value)
{
    this->value = new_value;
}

OmniPointer<DefinedType> DefinedTypeResult::GetValue()
{
    return this->value;
}

void DefinedTypeResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool DefinedTypeResult::GetResult()
{
    return this->result;
}

DefinedTypeListResult::DefinedTypeListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void DefinedTypeListResult::SetValue(std::vector<OmniPointer<DefinedType>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<DefinedType>> DefinedTypeListResult::GetValue()
{
    return this->value;
}

void DefinedTypeListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool DefinedTypeListResult::GetResult()
{
    return this->result;
}

DefinedType::DefinedType()
{
    this->length_string = NULL;
    this->name_field = NULL;
}

void DefinedType::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string DefinedType::UnParse()
{
    return this->length_string->GetString();
}

void DefinedType::SetName(OmniPointer<QualfiedName> input_value)
{
    this->name_field = input_value;
}

OmniPointer<QualfiedName> DefinedType::GetName()
{
    return this->name_field;
}

SingletonTypeParser::SingletonTypeParser()
{
    this->parser_network = NULL;
}

void SingletonTypeParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool SingletonTypeParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<SingletonTypeResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<SingletonType> instance = std::shared_ptr<SingletonType>(new SingletonType());
    OmniPointer<DefinedTypeResult> defined_type_field = std::shared_ptr<DefinedTypeResult>(new DefinedTypeResult());
    OmniPointer<PrimativeTypeResult> primative_type_field = std::shared_ptr<PrimativeTypeResult>(new PrimativeTypeResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&primative_type_parser_instance->ParseSingleSave(index,primative_type_field))
    {
        instance->SetDefinedType(defined_type_field->GetValue());
        instance->SetPrimativeType(primative_type_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        defined_type_field = std::shared_ptr<DefinedTypeResult>(new DefinedTypeResult());
        primative_type_field = std::shared_ptr<PrimativeTypeResult>(new PrimativeTypeResult());
    }
    if (true&&defined_type_parser_instance->ParseSingleSave(index,defined_type_field))
    {
        instance->SetDefinedType(defined_type_field->GetValue());
        instance->SetPrimativeType(primative_type_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        defined_type_field = std::shared_ptr<DefinedTypeResult>(new DefinedTypeResult());
        primative_type_field = std::shared_ptr<PrimativeTypeResult>(new PrimativeTypeResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool SingletonTypeParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<SingletonTypeResult> result = std::shared_ptr<SingletonTypeResult>(new SingletonTypeResult());
    return this->ParseSingleSave(index,result);
}

bool SingletonTypeParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<SingletonTypeResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool SingletonTypeParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<SingletonTypeResult> result = std::shared_ptr<SingletonTypeResult>(new SingletonTypeResult());
    return this->ParseOptionalSave(index,result);
}

bool SingletonTypeParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<SingletonTypeListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<SingletonType>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<SingletonTypeResult> result = std::shared_ptr<SingletonTypeResult>(new SingletonTypeResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool SingletonTypeParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<SingletonTypeListResult> result = std::shared_ptr<SingletonTypeListResult>(new SingletonTypeListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

SingletonTypeResult::SingletonTypeResult()
{
    this->value = NULL;
    this->result = false;
}

void SingletonTypeResult::SetValue(OmniPointer<SingletonType> new_value)
{
    this->value = new_value;
}

OmniPointer<SingletonType> SingletonTypeResult::GetValue()
{
    return this->value;
}

void SingletonTypeResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool SingletonTypeResult::GetResult()
{
    return this->result;
}

SingletonTypeListResult::SingletonTypeListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void SingletonTypeListResult::SetValue(std::vector<OmniPointer<SingletonType>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<SingletonType>> SingletonTypeListResult::GetValue()
{
    return this->value;
}

void SingletonTypeListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool SingletonTypeListResult::GetResult()
{
    return this->result;
}

SingletonType::SingletonType()
{
    this->length_string = NULL;
    this->defined_type_field = NULL;
    this->primative_type_field = NULL;
}

void SingletonType::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string SingletonType::UnParse()
{
    return this->length_string->GetString();
}

void SingletonType::SetDefinedType(OmniPointer<DefinedType> input_value)
{
    this->defined_type_field = input_value;
}

OmniPointer<DefinedType> SingletonType::GetDefinedType()
{
    return this->defined_type_field;
}

void SingletonType::SetPrimativeType(OmniPointer<PrimativeType> input_value)
{
    this->primative_type_field = input_value;
}

OmniPointer<PrimativeType> SingletonType::GetPrimativeType()
{
    return this->primative_type_field;
}

DimensionalNoteParser::DimensionalNoteParser()
{
    this->parser_network = NULL;
}

void DimensionalNoteParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool DimensionalNoteParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<DimensionalNoteResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<DimensionalNote> instance = std::shared_ptr<DimensionalNote>(new DimensionalNote());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string("["))&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string("]")))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    result->SetResult(false);
    return result->GetResult();
}

bool DimensionalNoteParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<DimensionalNoteResult> result = std::shared_ptr<DimensionalNoteResult>(new DimensionalNoteResult());
    return this->ParseSingleSave(index,result);
}

bool DimensionalNoteParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<DimensionalNoteResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool DimensionalNoteParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<DimensionalNoteResult> result = std::shared_ptr<DimensionalNoteResult>(new DimensionalNoteResult());
    return this->ParseOptionalSave(index,result);
}

bool DimensionalNoteParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<DimensionalNoteListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<DimensionalNote>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<DimensionalNoteResult> result = std::shared_ptr<DimensionalNoteResult>(new DimensionalNoteResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool DimensionalNoteParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<DimensionalNoteListResult> result = std::shared_ptr<DimensionalNoteListResult>(new DimensionalNoteListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

DimensionalNoteResult::DimensionalNoteResult()
{
    this->value = NULL;
    this->result = false;
}

void DimensionalNoteResult::SetValue(OmniPointer<DimensionalNote> new_value)
{
    this->value = new_value;
}

OmniPointer<DimensionalNote> DimensionalNoteResult::GetValue()
{
    return this->value;
}

void DimensionalNoteResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool DimensionalNoteResult::GetResult()
{
    return this->result;
}

DimensionalNoteListResult::DimensionalNoteListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void DimensionalNoteListResult::SetValue(std::vector<OmniPointer<DimensionalNote>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<DimensionalNote>> DimensionalNoteListResult::GetValue()
{
    return this->value;
}

void DimensionalNoteListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool DimensionalNoteListResult::GetResult()
{
    return this->result;
}

DimensionalNote::DimensionalNote()
{
    this->length_string = NULL;
}

void DimensionalNote::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string DimensionalNote::UnParse()
{
    return this->length_string->GetString();
}

DimensionalTypeParser::DimensionalTypeParser()
{
    this->parser_network = NULL;
}

void DimensionalTypeParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool DimensionalTypeParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<DimensionalTypeResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<DimensionalType> instance = std::shared_ptr<DimensionalType>(new DimensionalType());
    OmniPointer<DimensionalNoteListResult> dimensional_note_field = std::shared_ptr<DimensionalNoteListResult>(new DimensionalNoteListResult());
    OmniPointer<SingletonTypeResult> singleton_type_field = std::shared_ptr<SingletonTypeResult>(new SingletonTypeResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&singleton_type_parser_instance->ParseSingleSave(index,singleton_type_field)&&dimensional_note_parser_instance->ParseManySave(index,dimensional_note_field,1,-1))
    {
        instance->SetDimensionalNote(dimensional_note_field->GetValue());
        instance->SetSingletonType(singleton_type_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        dimensional_note_field = std::shared_ptr<DimensionalNoteListResult>(new DimensionalNoteListResult());
        singleton_type_field = std::shared_ptr<SingletonTypeResult>(new SingletonTypeResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool DimensionalTypeParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<DimensionalTypeResult> result = std::shared_ptr<DimensionalTypeResult>(new DimensionalTypeResult());
    return this->ParseSingleSave(index,result);
}

bool DimensionalTypeParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<DimensionalTypeResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool DimensionalTypeParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<DimensionalTypeResult> result = std::shared_ptr<DimensionalTypeResult>(new DimensionalTypeResult());
    return this->ParseOptionalSave(index,result);
}

bool DimensionalTypeParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<DimensionalTypeListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<DimensionalType>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<DimensionalTypeResult> result = std::shared_ptr<DimensionalTypeResult>(new DimensionalTypeResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool DimensionalTypeParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<DimensionalTypeListResult> result = std::shared_ptr<DimensionalTypeListResult>(new DimensionalTypeListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

DimensionalTypeResult::DimensionalTypeResult()
{
    this->value = NULL;
    this->result = false;
}

void DimensionalTypeResult::SetValue(OmniPointer<DimensionalType> new_value)
{
    this->value = new_value;
}

OmniPointer<DimensionalType> DimensionalTypeResult::GetValue()
{
    return this->value;
}

void DimensionalTypeResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool DimensionalTypeResult::GetResult()
{
    return this->result;
}

DimensionalTypeListResult::DimensionalTypeListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void DimensionalTypeListResult::SetValue(std::vector<OmniPointer<DimensionalType>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<DimensionalType>> DimensionalTypeListResult::GetValue()
{
    return this->value;
}

void DimensionalTypeListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool DimensionalTypeListResult::GetResult()
{
    return this->result;
}

DimensionalType::DimensionalType()
{
    this->length_string = NULL;
    /*this->dimensional_note_field = NO_DEFAULT;*/
    this->singleton_type_field = NULL;
}

void DimensionalType::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string DimensionalType::UnParse()
{
    return this->length_string->GetString();
}

void DimensionalType::SetDimensionalNote(std::vector<OmniPointer<DimensionalNote>> input_value)
{
    this->dimensional_note_field = input_value;
}

std::vector<OmniPointer<DimensionalNote>> DimensionalType::GetDimensionalNote()
{
    return this->dimensional_note_field;
}

void DimensionalType::SetSingletonType(OmniPointer<SingletonType> input_value)
{
    this->singleton_type_field = input_value;
}

OmniPointer<SingletonType> DimensionalType::GetSingletonType()
{
    return this->singleton_type_field;
}

MapNoteParser::MapNoteParser()
{
    this->parser_network = NULL;
}

void MapNoteParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool MapNoteParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<MapNoteResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<MapNote> instance = std::shared_ptr<MapNote>(new MapNote());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string("{"))&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string("}")))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    result->SetResult(false);
    return result->GetResult();
}

bool MapNoteParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<MapNoteResult> result = std::shared_ptr<MapNoteResult>(new MapNoteResult());
    return this->ParseSingleSave(index,result);
}

bool MapNoteParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<MapNoteResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool MapNoteParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<MapNoteResult> result = std::shared_ptr<MapNoteResult>(new MapNoteResult());
    return this->ParseOptionalSave(index,result);
}

bool MapNoteParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<MapNoteListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<MapNote>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<MapNoteResult> result = std::shared_ptr<MapNoteResult>(new MapNoteResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool MapNoteParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<MapNoteListResult> result = std::shared_ptr<MapNoteListResult>(new MapNoteListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

MapNoteResult::MapNoteResult()
{
    this->value = NULL;
    this->result = false;
}

void MapNoteResult::SetValue(OmniPointer<MapNote> new_value)
{
    this->value = new_value;
}

OmniPointer<MapNote> MapNoteResult::GetValue()
{
    return this->value;
}

void MapNoteResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool MapNoteResult::GetResult()
{
    return this->result;
}

MapNoteListResult::MapNoteListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void MapNoteListResult::SetValue(std::vector<OmniPointer<MapNote>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<MapNote>> MapNoteListResult::GetValue()
{
    return this->value;
}

void MapNoteListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool MapNoteListResult::GetResult()
{
    return this->result;
}

MapNote::MapNote()
{
    this->length_string = NULL;
}

void MapNote::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string MapNote::UnParse()
{
    return this->length_string->GetString();
}

MapTypeParser::MapTypeParser()
{
    this->parser_network = NULL;
}

void MapTypeParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool MapTypeParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<MapTypeResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<MapType> instance = std::shared_ptr<MapType>(new MapType());
    OmniPointer<MapNoteResult> map_note_field = std::shared_ptr<MapNoteResult>(new MapNoteResult());
    OmniPointer<SingletonTypeResult> singleton_type_field = std::shared_ptr<SingletonTypeResult>(new SingletonTypeResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&singleton_type_parser_instance->ParseSingleSave(index,singleton_type_field)&&map_note_parser_instance->ParseSingleSave(index,map_note_field))
    {
        instance->SetMapNote(map_note_field->GetValue());
        instance->SetSingletonType(singleton_type_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        map_note_field = std::shared_ptr<MapNoteResult>(new MapNoteResult());
        singleton_type_field = std::shared_ptr<SingletonTypeResult>(new SingletonTypeResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool MapTypeParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<MapTypeResult> result = std::shared_ptr<MapTypeResult>(new MapTypeResult());
    return this->ParseSingleSave(index,result);
}

bool MapTypeParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<MapTypeResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool MapTypeParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<MapTypeResult> result = std::shared_ptr<MapTypeResult>(new MapTypeResult());
    return this->ParseOptionalSave(index,result);
}

bool MapTypeParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<MapTypeListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<MapType>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<MapTypeResult> result = std::shared_ptr<MapTypeResult>(new MapTypeResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool MapTypeParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<MapTypeListResult> result = std::shared_ptr<MapTypeListResult>(new MapTypeListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

MapTypeResult::MapTypeResult()
{
    this->value = NULL;
    this->result = false;
}

void MapTypeResult::SetValue(OmniPointer<MapType> new_value)
{
    this->value = new_value;
}

OmniPointer<MapType> MapTypeResult::GetValue()
{
    return this->value;
}

void MapTypeResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool MapTypeResult::GetResult()
{
    return this->result;
}

MapTypeListResult::MapTypeListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void MapTypeListResult::SetValue(std::vector<OmniPointer<MapType>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<MapType>> MapTypeListResult::GetValue()
{
    return this->value;
}

void MapTypeListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool MapTypeListResult::GetResult()
{
    return this->result;
}

MapType::MapType()
{
    this->length_string = NULL;
    this->map_note_field = NULL;
    this->singleton_type_field = NULL;
}

void MapType::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string MapType::UnParse()
{
    return this->length_string->GetString();
}

void MapType::SetMapNote(OmniPointer<MapNote> input_value)
{
    this->map_note_field = input_value;
}

OmniPointer<MapNote> MapType::GetMapNote()
{
    return this->map_note_field;
}

void MapType::SetSingletonType(OmniPointer<SingletonType> input_value)
{
    this->singleton_type_field = input_value;
}

OmniPointer<SingletonType> MapType::GetSingletonType()
{
    return this->singleton_type_field;
}

ValueTypeParser::ValueTypeParser()
{
    this->parser_network = NULL;
}

void ValueTypeParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool ValueTypeParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<ValueTypeResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<ValueType> instance = std::shared_ptr<ValueType>(new ValueType());
    OmniPointer<MapTypeResult> map_type_field = std::shared_ptr<MapTypeResult>(new MapTypeResult());
    OmniPointer<SingletonTypeResult> singleton_type_field = std::shared_ptr<SingletonTypeResult>(new SingletonTypeResult());
    OmniPointer<DimensionalTypeResult> dimensional_type_field = std::shared_ptr<DimensionalTypeResult>(new DimensionalTypeResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&dimensional_type_parser_instance->ParseSingleSave(index,dimensional_type_field))
    {
        instance->SetMapType(map_type_field->GetValue());
        instance->SetSingletonType(singleton_type_field->GetValue());
        instance->SetDimensionalType(dimensional_type_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        map_type_field = std::shared_ptr<MapTypeResult>(new MapTypeResult());
        singleton_type_field = std::shared_ptr<SingletonTypeResult>(new SingletonTypeResult());
        dimensional_type_field = std::shared_ptr<DimensionalTypeResult>(new DimensionalTypeResult());
    }
    if (true&&map_type_parser_instance->ParseSingleSave(index,map_type_field))
    {
        instance->SetMapType(map_type_field->GetValue());
        instance->SetSingletonType(singleton_type_field->GetValue());
        instance->SetDimensionalType(dimensional_type_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        map_type_field = std::shared_ptr<MapTypeResult>(new MapTypeResult());
        singleton_type_field = std::shared_ptr<SingletonTypeResult>(new SingletonTypeResult());
        dimensional_type_field = std::shared_ptr<DimensionalTypeResult>(new DimensionalTypeResult());
    }
    if (true&&singleton_type_parser_instance->ParseSingleSave(index,singleton_type_field))
    {
        instance->SetMapType(map_type_field->GetValue());
        instance->SetSingletonType(singleton_type_field->GetValue());
        instance->SetDimensionalType(dimensional_type_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        map_type_field = std::shared_ptr<MapTypeResult>(new MapTypeResult());
        singleton_type_field = std::shared_ptr<SingletonTypeResult>(new SingletonTypeResult());
        dimensional_type_field = std::shared_ptr<DimensionalTypeResult>(new DimensionalTypeResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool ValueTypeParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<ValueTypeResult> result = std::shared_ptr<ValueTypeResult>(new ValueTypeResult());
    return this->ParseSingleSave(index,result);
}

bool ValueTypeParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ValueTypeResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool ValueTypeParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<ValueTypeResult> result = std::shared_ptr<ValueTypeResult>(new ValueTypeResult());
    return this->ParseOptionalSave(index,result);
}

bool ValueTypeParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<ValueTypeListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<ValueType>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<ValueTypeResult> result = std::shared_ptr<ValueTypeResult>(new ValueTypeResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool ValueTypeParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<ValueTypeListResult> result = std::shared_ptr<ValueTypeListResult>(new ValueTypeListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

ValueTypeResult::ValueTypeResult()
{
    this->value = NULL;
    this->result = false;
}

void ValueTypeResult::SetValue(OmniPointer<ValueType> new_value)
{
    this->value = new_value;
}

OmniPointer<ValueType> ValueTypeResult::GetValue()
{
    return this->value;
}

void ValueTypeResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool ValueTypeResult::GetResult()
{
    return this->result;
}

ValueTypeListResult::ValueTypeListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void ValueTypeListResult::SetValue(std::vector<OmniPointer<ValueType>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<ValueType>> ValueTypeListResult::GetValue()
{
    return this->value;
}

void ValueTypeListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool ValueTypeListResult::GetResult()
{
    return this->result;
}

ValueType::ValueType()
{
    this->length_string = NULL;
    this->map_type_field = NULL;
    this->singleton_type_field = NULL;
    this->dimensional_type_field = NULL;
}

void ValueType::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string ValueType::UnParse()
{
    return this->length_string->GetString();
}

void ValueType::SetMapType(OmniPointer<MapType> input_value)
{
    this->map_type_field = input_value;
}

OmniPointer<MapType> ValueType::GetMapType()
{
    return this->map_type_field;
}

void ValueType::SetSingletonType(OmniPointer<SingletonType> input_value)
{
    this->singleton_type_field = input_value;
}

OmniPointer<SingletonType> ValueType::GetSingletonType()
{
    return this->singleton_type_field;
}

void ValueType::SetDimensionalType(OmniPointer<DimensionalType> input_value)
{
    this->dimensional_type_field = input_value;
}

OmniPointer<DimensionalType> ValueType::GetDimensionalType()
{
    return this->dimensional_type_field;
}

ParameterListDefParser::ParameterListDefParser()
{
    this->parser_network = NULL;
}

void ParameterListDefParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool ParameterListDefParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<ParameterListDefResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<ParameterListDef> instance = std::shared_ptr<ParameterListDef>(new ParameterListDef());
    OmniPointer<ParameterListDefResult> parameter_tail_field = std::shared_ptr<ParameterListDefResult>(new ParameterListDefResult());
    OmniPointer<NameResult> name_field = std::shared_ptr<NameResult>(new NameResult());
    OmniPointer<ValueTypeResult> type_field = std::shared_ptr<ValueTypeResult>(new ValueTypeResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&value_type_parser_instance->ParseSingleSave(index,type_field)&&whitespace_parser_instance->ParseMany(index,1,-1)&&name_parser_instance->ParseSingleSave(index,name_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string(","))&&whitespace_parser_instance->ParseMany(index,0,-1)&&parameter_list_def_parser_instance->ParseSingleSave(index,parameter_tail_field))
    {
        instance->SetParameterTail(parameter_tail_field->GetValue());
        instance->SetName(name_field->GetValue());
        instance->SetType(type_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        parameter_tail_field = std::shared_ptr<ParameterListDefResult>(new ParameterListDefResult());
        name_field = std::shared_ptr<NameResult>(new NameResult());
        type_field = std::shared_ptr<ValueTypeResult>(new ValueTypeResult());
    }
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&value_type_parser_instance->ParseSingleSave(index,type_field)&&whitespace_parser_instance->ParseMany(index,1,-1)&&name_parser_instance->ParseSingleSave(index,name_field)&&whitespace_parser_instance->ParseMany(index,0,-1))
    {
        instance->SetParameterTail(parameter_tail_field->GetValue());
        instance->SetName(name_field->GetValue());
        instance->SetType(type_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        parameter_tail_field = std::shared_ptr<ParameterListDefResult>(new ParameterListDefResult());
        name_field = std::shared_ptr<NameResult>(new NameResult());
        type_field = std::shared_ptr<ValueTypeResult>(new ValueTypeResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool ParameterListDefParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<ParameterListDefResult> result = std::shared_ptr<ParameterListDefResult>(new ParameterListDefResult());
    return this->ParseSingleSave(index,result);
}

bool ParameterListDefParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ParameterListDefResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool ParameterListDefParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<ParameterListDefResult> result = std::shared_ptr<ParameterListDefResult>(new ParameterListDefResult());
    return this->ParseOptionalSave(index,result);
}

bool ParameterListDefParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<ParameterListDefListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<ParameterListDef>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<ParameterListDefResult> result = std::shared_ptr<ParameterListDefResult>(new ParameterListDefResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool ParameterListDefParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<ParameterListDefListResult> result = std::shared_ptr<ParameterListDefListResult>(new ParameterListDefListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

ParameterListDefResult::ParameterListDefResult()
{
    this->value = NULL;
    this->result = false;
}

void ParameterListDefResult::SetValue(OmniPointer<ParameterListDef> new_value)
{
    this->value = new_value;
}

OmniPointer<ParameterListDef> ParameterListDefResult::GetValue()
{
    return this->value;
}

void ParameterListDefResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool ParameterListDefResult::GetResult()
{
    return this->result;
}

ParameterListDefListResult::ParameterListDefListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void ParameterListDefListResult::SetValue(std::vector<OmniPointer<ParameterListDef>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<ParameterListDef>> ParameterListDefListResult::GetValue()
{
    return this->value;
}

void ParameterListDefListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool ParameterListDefListResult::GetResult()
{
    return this->result;
}

ParameterListDef::ParameterListDef()
{
    this->length_string = NULL;
    this->parameter_tail_field = NULL;
    this->name_field = NULL;
    this->type_field = NULL;
}

void ParameterListDef::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string ParameterListDef::UnParse()
{
    return this->length_string->GetString();
}

void ParameterListDef::SetParameterTail(OmniPointer<ParameterListDef> input_value)
{
    this->parameter_tail_field = input_value;
}

OmniPointer<ParameterListDef> ParameterListDef::GetParameterTail()
{
    return this->parameter_tail_field;
}

void ParameterListDef::SetName(OmniPointer<Name> input_value)
{
    this->name_field = input_value;
}

OmniPointer<Name> ParameterListDef::GetName()
{
    return this->name_field;
}

void ParameterListDef::SetType(OmniPointer<ValueType> input_value)
{
    this->type_field = input_value;
}

OmniPointer<ValueType> ParameterListDef::GetType()
{
    return this->type_field;
}

ParameterListParser::ParameterListParser()
{
    this->parser_network = NULL;
}

void ParameterListParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool ParameterListParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<ParameterListResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<ParameterList> instance = std::shared_ptr<ParameterList>(new ParameterList());
    OmniPointer<ParameterListResult> parameter_tail_field = std::shared_ptr<ParameterListResult>(new ParameterListResult());
    OmniPointer<RValueResult> r_value_field = std::shared_ptr<RValueResult>(new RValueResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&r_value_parser_instance->ParseSingleSave(index,r_value_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string(","))&&whitespace_parser_instance->ParseMany(index,0,-1)&&parameter_list_parser_instance->ParseSingleSave(index,parameter_tail_field))
    {
        instance->SetParameterTail(parameter_tail_field->GetValue());
        instance->SetRValue(r_value_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        parameter_tail_field = std::shared_ptr<ParameterListResult>(new ParameterListResult());
        r_value_field = std::shared_ptr<RValueResult>(new RValueResult());
    }
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&r_value_parser_instance->ParseSingleSave(index,r_value_field)&&whitespace_parser_instance->ParseMany(index,0,-1))
    {
        instance->SetParameterTail(parameter_tail_field->GetValue());
        instance->SetRValue(r_value_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        parameter_tail_field = std::shared_ptr<ParameterListResult>(new ParameterListResult());
        r_value_field = std::shared_ptr<RValueResult>(new RValueResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool ParameterListParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<ParameterListResult> result = std::shared_ptr<ParameterListResult>(new ParameterListResult());
    return this->ParseSingleSave(index,result);
}

bool ParameterListParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ParameterListResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool ParameterListParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<ParameterListResult> result = std::shared_ptr<ParameterListResult>(new ParameterListResult());
    return this->ParseOptionalSave(index,result);
}

bool ParameterListParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<ParameterListListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<ParameterList>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<ParameterListResult> result = std::shared_ptr<ParameterListResult>(new ParameterListResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool ParameterListParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<ParameterListListResult> result = std::shared_ptr<ParameterListListResult>(new ParameterListListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

ParameterListResult::ParameterListResult()
{
    this->value = NULL;
    this->result = false;
}

void ParameterListResult::SetValue(OmniPointer<ParameterList> new_value)
{
    this->value = new_value;
}

OmniPointer<ParameterList> ParameterListResult::GetValue()
{
    return this->value;
}

void ParameterListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool ParameterListResult::GetResult()
{
    return this->result;
}

ParameterListListResult::ParameterListListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void ParameterListListResult::SetValue(std::vector<OmniPointer<ParameterList>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<ParameterList>> ParameterListListResult::GetValue()
{
    return this->value;
}

void ParameterListListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool ParameterListListResult::GetResult()
{
    return this->result;
}

ParameterList::ParameterList()
{
    this->length_string = NULL;
    this->parameter_tail_field = NULL;
    this->r_value_field = NULL;
}

void ParameterList::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string ParameterList::UnParse()
{
    return this->length_string->GetString();
}

void ParameterList::SetParameterTail(OmniPointer<ParameterList> input_value)
{
    this->parameter_tail_field = input_value;
}

OmniPointer<ParameterList> ParameterList::GetParameterTail()
{
    return this->parameter_tail_field;
}

void ParameterList::SetRValue(OmniPointer<RValue> input_value)
{
    this->r_value_field = input_value;
}

OmniPointer<RValue> ParameterList::GetRValue()
{
    return this->r_value_field;
}

CodeBlockParser::CodeBlockParser()
{
    this->parser_network = NULL;
}

void CodeBlockParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool CodeBlockParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<CodeBlockResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<CodeBlock> instance = std::shared_ptr<CodeBlock>(new CodeBlock());
    OmniPointer<InstructionListResult> instructions_field = std::shared_ptr<InstructionListResult>(new InstructionListResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string("{"))&&whitespace_parser_instance->ParseMany(index,0,-1)&&instruction_parser_instance->ParseManySave(index,instructions_field,0,-1)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string("}"))&&whitespace_parser_instance->ParseMany(index,0,-1))
    {
        instance->SetInstructions(instructions_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        instructions_field = std::shared_ptr<InstructionListResult>(new InstructionListResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool CodeBlockParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<CodeBlockResult> result = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
    return this->ParseSingleSave(index,result);
}

bool CodeBlockParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<CodeBlockResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool CodeBlockParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<CodeBlockResult> result = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
    return this->ParseOptionalSave(index,result);
}

bool CodeBlockParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<CodeBlockListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<CodeBlock>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<CodeBlockResult> result = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool CodeBlockParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<CodeBlockListResult> result = std::shared_ptr<CodeBlockListResult>(new CodeBlockListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

CodeBlockResult::CodeBlockResult()
{
    this->value = NULL;
    this->result = false;
}

void CodeBlockResult::SetValue(OmniPointer<CodeBlock> new_value)
{
    this->value = new_value;
}

OmniPointer<CodeBlock> CodeBlockResult::GetValue()
{
    return this->value;
}

void CodeBlockResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool CodeBlockResult::GetResult()
{
    return this->result;
}

CodeBlockListResult::CodeBlockListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void CodeBlockListResult::SetValue(std::vector<OmniPointer<CodeBlock>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<CodeBlock>> CodeBlockListResult::GetValue()
{
    return this->value;
}

void CodeBlockListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool CodeBlockListResult::GetResult()
{
    return this->result;
}

CodeBlock::CodeBlock()
{
    this->length_string = NULL;
    /*this->instructions_field = NO_DEFAULT;*/
}

void CodeBlock::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string CodeBlock::UnParse()
{
    return this->length_string->GetString();
}

void CodeBlock::SetInstructions(std::vector<OmniPointer<Instruction>> input_value)
{
    this->instructions_field = input_value;
}

std::vector<OmniPointer<Instruction>> CodeBlock::GetInstructions()
{
    return this->instructions_field;
}

DeclarationAssignParser::DeclarationAssignParser()
{
    this->parser_network = NULL;
}

void DeclarationAssignParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool DeclarationAssignParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<DeclarationAssignResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<DeclarationAssign> instance = std::shared_ptr<DeclarationAssign>(new DeclarationAssign());
    OmniPointer<RValueResult> r_value_field = std::shared_ptr<RValueResult>(new RValueResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string("="))&&whitespace_parser_instance->ParseMany(index,0,-1)&&r_value_parser_instance->ParseSingleSave(index,r_value_field)&&whitespace_parser_instance->ParseMany(index,0,-1))
    {
        instance->SetRValue(r_value_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        r_value_field = std::shared_ptr<RValueResult>(new RValueResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool DeclarationAssignParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<DeclarationAssignResult> result = std::shared_ptr<DeclarationAssignResult>(new DeclarationAssignResult());
    return this->ParseSingleSave(index,result);
}

bool DeclarationAssignParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<DeclarationAssignResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool DeclarationAssignParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<DeclarationAssignResult> result = std::shared_ptr<DeclarationAssignResult>(new DeclarationAssignResult());
    return this->ParseOptionalSave(index,result);
}

bool DeclarationAssignParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<DeclarationAssignListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<DeclarationAssign>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<DeclarationAssignResult> result = std::shared_ptr<DeclarationAssignResult>(new DeclarationAssignResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool DeclarationAssignParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<DeclarationAssignListResult> result = std::shared_ptr<DeclarationAssignListResult>(new DeclarationAssignListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

DeclarationAssignResult::DeclarationAssignResult()
{
    this->value = NULL;
    this->result = false;
}

void DeclarationAssignResult::SetValue(OmniPointer<DeclarationAssign> new_value)
{
    this->value = new_value;
}

OmniPointer<DeclarationAssign> DeclarationAssignResult::GetValue()
{
    return this->value;
}

void DeclarationAssignResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool DeclarationAssignResult::GetResult()
{
    return this->result;
}

DeclarationAssignListResult::DeclarationAssignListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void DeclarationAssignListResult::SetValue(std::vector<OmniPointer<DeclarationAssign>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<DeclarationAssign>> DeclarationAssignListResult::GetValue()
{
    return this->value;
}

void DeclarationAssignListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool DeclarationAssignListResult::GetResult()
{
    return this->result;
}

DeclarationAssign::DeclarationAssign()
{
    this->length_string = NULL;
    this->r_value_field = NULL;
}

void DeclarationAssign::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string DeclarationAssign::UnParse()
{
    return this->length_string->GetString();
}

void DeclarationAssign::SetRValue(OmniPointer<RValue> input_value)
{
    this->r_value_field = input_value;
}

OmniPointer<RValue> DeclarationAssign::GetRValue()
{
    return this->r_value_field;
}

DeclarationParser::DeclarationParser()
{
    this->parser_network = NULL;
}

void DeclarationParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool DeclarationParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<DeclarationResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<Declaration> instance = std::shared_ptr<Declaration>(new Declaration());
    OmniPointer<NameResult> name_field = std::shared_ptr<NameResult>(new NameResult());
    OmniPointer<DeclarationAssignResult> assignment_field = std::shared_ptr<DeclarationAssignResult>(new DeclarationAssignResult());
    OmniPointer<ValueTypeResult> type_field = std::shared_ptr<ValueTypeResult>(new ValueTypeResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&value_type_parser_instance->ParseSingleSave(index,type_field)&&whitespace_parser_instance->ParseMany(index,1,-1)&&name_parser_instance->ParseSingleSave(index,name_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&declaration_assign_parser_instance->ParseOptionalSave(index,assignment_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string(";"))&&whitespace_parser_instance->ParseMany(index,0,-1))
    {
        instance->SetName(name_field->GetValue());
        instance->SetAssignment(assignment_field->GetValue());
        instance->SetType(type_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        name_field = std::shared_ptr<NameResult>(new NameResult());
        assignment_field = std::shared_ptr<DeclarationAssignResult>(new DeclarationAssignResult());
        type_field = std::shared_ptr<ValueTypeResult>(new ValueTypeResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool DeclarationParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<DeclarationResult> result = std::shared_ptr<DeclarationResult>(new DeclarationResult());
    return this->ParseSingleSave(index,result);
}

bool DeclarationParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<DeclarationResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool DeclarationParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<DeclarationResult> result = std::shared_ptr<DeclarationResult>(new DeclarationResult());
    return this->ParseOptionalSave(index,result);
}

bool DeclarationParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<DeclarationListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<Declaration>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<DeclarationResult> result = std::shared_ptr<DeclarationResult>(new DeclarationResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool DeclarationParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<DeclarationListResult> result = std::shared_ptr<DeclarationListResult>(new DeclarationListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

DeclarationResult::DeclarationResult()
{
    this->value = NULL;
    this->result = false;
}

void DeclarationResult::SetValue(OmniPointer<Declaration> new_value)
{
    this->value = new_value;
}

OmniPointer<Declaration> DeclarationResult::GetValue()
{
    return this->value;
}

void DeclarationResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool DeclarationResult::GetResult()
{
    return this->result;
}

DeclarationListResult::DeclarationListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void DeclarationListResult::SetValue(std::vector<OmniPointer<Declaration>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<Declaration>> DeclarationListResult::GetValue()
{
    return this->value;
}

void DeclarationListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool DeclarationListResult::GetResult()
{
    return this->result;
}

Declaration::Declaration()
{
    this->length_string = NULL;
    this->name_field = NULL;
    this->assignment_field = NULL;
    this->type_field = NULL;
}

void Declaration::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string Declaration::UnParse()
{
    return this->length_string->GetString();
}

void Declaration::SetName(OmniPointer<Name> input_value)
{
    this->name_field = input_value;
}

OmniPointer<Name> Declaration::GetName()
{
    return this->name_field;
}

void Declaration::SetAssignment(OmniPointer<DeclarationAssign> input_value)
{
    this->assignment_field = input_value;
}

OmniPointer<DeclarationAssign> Declaration::GetAssignment()
{
    return this->assignment_field;
}

void Declaration::SetType(OmniPointer<ValueType> input_value)
{
    this->type_field = input_value;
}

OmniPointer<ValueType> Declaration::GetType()
{
    return this->type_field;
}

AssignmentParser::AssignmentParser()
{
    this->parser_network = NULL;
}

void AssignmentParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool AssignmentParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<AssignmentResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<Assignment> instance = std::shared_ptr<Assignment>(new Assignment());
    OmniPointer<RValueResult> r_value_field = std::shared_ptr<RValueResult>(new RValueResult());
    OmniPointer<QualfiedNameResult> l_value_field = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&qualfied_name_parser_instance->ParseSingleSave(index,l_value_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string("="))&&whitespace_parser_instance->ParseMany(index,0,-1)&&r_value_parser_instance->ParseSingleSave(index,r_value_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string(";"))&&whitespace_parser_instance->ParseMany(index,0,-1))
    {
        instance->SetRValue(r_value_field->GetValue());
        instance->SetLValue(l_value_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        r_value_field = std::shared_ptr<RValueResult>(new RValueResult());
        l_value_field = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool AssignmentParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<AssignmentResult> result = std::shared_ptr<AssignmentResult>(new AssignmentResult());
    return this->ParseSingleSave(index,result);
}

bool AssignmentParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<AssignmentResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool AssignmentParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<AssignmentResult> result = std::shared_ptr<AssignmentResult>(new AssignmentResult());
    return this->ParseOptionalSave(index,result);
}

bool AssignmentParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<AssignmentListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<Assignment>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<AssignmentResult> result = std::shared_ptr<AssignmentResult>(new AssignmentResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool AssignmentParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<AssignmentListResult> result = std::shared_ptr<AssignmentListResult>(new AssignmentListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

AssignmentResult::AssignmentResult()
{
    this->value = NULL;
    this->result = false;
}

void AssignmentResult::SetValue(OmniPointer<Assignment> new_value)
{
    this->value = new_value;
}

OmniPointer<Assignment> AssignmentResult::GetValue()
{
    return this->value;
}

void AssignmentResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool AssignmentResult::GetResult()
{
    return this->result;
}

AssignmentListResult::AssignmentListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void AssignmentListResult::SetValue(std::vector<OmniPointer<Assignment>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<Assignment>> AssignmentListResult::GetValue()
{
    return this->value;
}

void AssignmentListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool AssignmentListResult::GetResult()
{
    return this->result;
}

Assignment::Assignment()
{
    this->length_string = NULL;
    this->r_value_field = NULL;
    this->l_value_field = NULL;
}

void Assignment::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string Assignment::UnParse()
{
    return this->length_string->GetString();
}

void Assignment::SetRValue(OmniPointer<RValue> input_value)
{
    this->r_value_field = input_value;
}

OmniPointer<RValue> Assignment::GetRValue()
{
    return this->r_value_field;
}

void Assignment::SetLValue(OmniPointer<QualfiedName> input_value)
{
    this->l_value_field = input_value;
}

OmniPointer<QualfiedName> Assignment::GetLValue()
{
    return this->l_value_field;
}

ReturnParser::ReturnParser()
{
    this->parser_network = NULL;
}

void ReturnParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool ReturnParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<ReturnResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<Return> instance = std::shared_ptr<Return>(new Return());
    OmniPointer<RValueResult> r_value_field = std::shared_ptr<RValueResult>(new RValueResult());
    OmniPointer<StringResult> rtn_field = std::shared_ptr<StringResult>(new StringResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingleSave(index,std::string("return"),rtn_field)&&whitespace_parser_instance->ParseMany(index,1,-1)&&r_value_parser_instance->ParseSingleSave(index,r_value_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string(";"))&&whitespace_parser_instance->ParseMany(index,0,-1))
    {
        instance->SetRValue(r_value_field->GetValue());
        instance->SetRtn(rtn_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        r_value_field = std::shared_ptr<RValueResult>(new RValueResult());
        rtn_field = std::shared_ptr<StringResult>(new StringResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool ReturnParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<ReturnResult> result = std::shared_ptr<ReturnResult>(new ReturnResult());
    return this->ParseSingleSave(index,result);
}

bool ReturnParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ReturnResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool ReturnParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<ReturnResult> result = std::shared_ptr<ReturnResult>(new ReturnResult());
    return this->ParseOptionalSave(index,result);
}

bool ReturnParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<ReturnListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<Return>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<ReturnResult> result = std::shared_ptr<ReturnResult>(new ReturnResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool ReturnParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<ReturnListResult> result = std::shared_ptr<ReturnListResult>(new ReturnListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

ReturnResult::ReturnResult()
{
    this->value = NULL;
    this->result = false;
}

void ReturnResult::SetValue(OmniPointer<Return> new_value)
{
    this->value = new_value;
}

OmniPointer<Return> ReturnResult::GetValue()
{
    return this->value;
}

void ReturnResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool ReturnResult::GetResult()
{
    return this->result;
}

ReturnListResult::ReturnListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void ReturnListResult::SetValue(std::vector<OmniPointer<Return>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<Return>> ReturnListResult::GetValue()
{
    return this->value;
}

void ReturnListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool ReturnListResult::GetResult()
{
    return this->result;
}

Return::Return()
{
    this->length_string = NULL;
    this->r_value_field = NULL;
    this->rtn_field = NULL;
}

void Return::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string Return::UnParse()
{
    return this->length_string->GetString();
}

void Return::SetRValue(OmniPointer<RValue> input_value)
{
    this->r_value_field = input_value;
}

OmniPointer<RValue> Return::GetRValue()
{
    return this->r_value_field;
}

void Return::SetRtn(OmniPointer<String> input_value)
{
    this->rtn_field = input_value;
}

OmniPointer<String> Return::GetRtn()
{
    return this->rtn_field;
}

ElseTailParser::ElseTailParser()
{
    this->parser_network = NULL;
}

void ElseTailParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool ElseTailParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<ElseTailResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<ElseTail> instance = std::shared_ptr<ElseTail>(new ElseTail());
    OmniPointer<CodeBlockResult> code_block_field = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
    OmniPointer<StringResult> else_key_field = std::shared_ptr<StringResult>(new StringResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingleSave(index,std::string("else"),else_key_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&code_block_parser_instance->ParseSingleSave(index,code_block_field)&&whitespace_parser_instance->ParseMany(index,0,-1))
    {
        instance->SetCodeBlock(code_block_field->GetValue());
        instance->SetElseKey(else_key_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        code_block_field = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
        else_key_field = std::shared_ptr<StringResult>(new StringResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool ElseTailParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<ElseTailResult> result = std::shared_ptr<ElseTailResult>(new ElseTailResult());
    return this->ParseSingleSave(index,result);
}

bool ElseTailParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ElseTailResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool ElseTailParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<ElseTailResult> result = std::shared_ptr<ElseTailResult>(new ElseTailResult());
    return this->ParseOptionalSave(index,result);
}

bool ElseTailParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<ElseTailListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<ElseTail>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<ElseTailResult> result = std::shared_ptr<ElseTailResult>(new ElseTailResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool ElseTailParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<ElseTailListResult> result = std::shared_ptr<ElseTailListResult>(new ElseTailListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

ElseTailResult::ElseTailResult()
{
    this->value = NULL;
    this->result = false;
}

void ElseTailResult::SetValue(OmniPointer<ElseTail> new_value)
{
    this->value = new_value;
}

OmniPointer<ElseTail> ElseTailResult::GetValue()
{
    return this->value;
}

void ElseTailResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool ElseTailResult::GetResult()
{
    return this->result;
}

ElseTailListResult::ElseTailListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void ElseTailListResult::SetValue(std::vector<OmniPointer<ElseTail>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<ElseTail>> ElseTailListResult::GetValue()
{
    return this->value;
}

void ElseTailListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool ElseTailListResult::GetResult()
{
    return this->result;
}

ElseTail::ElseTail()
{
    this->length_string = NULL;
    this->code_block_field = NULL;
    this->else_key_field = NULL;
}

void ElseTail::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string ElseTail::UnParse()
{
    return this->length_string->GetString();
}

void ElseTail::SetCodeBlock(OmniPointer<CodeBlock> input_value)
{
    this->code_block_field = input_value;
}

OmniPointer<CodeBlock> ElseTail::GetCodeBlock()
{
    return this->code_block_field;
}

void ElseTail::SetElseKey(OmniPointer<String> input_value)
{
    this->else_key_field = input_value;
}

OmniPointer<String> ElseTail::GetElseKey()
{
    return this->else_key_field;
}

ConditionalParser::ConditionalParser()
{
    this->parser_network = NULL;
}

void ConditionalParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool ConditionalParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<ConditionalResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<Conditional> instance = std::shared_ptr<Conditional>(new Conditional());
    OmniPointer<ElseTailResult> else_tail_field = std::shared_ptr<ElseTailResult>(new ElseTailResult());
    OmniPointer<CodeBlockResult> code_block_field = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
    OmniPointer<RValueResult> r_value_field = std::shared_ptr<RValueResult>(new RValueResult());
    OmniPointer<StringResult> conditional_key_field = std::shared_ptr<StringResult>(new StringResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingleSave(index,std::string("if"),conditional_key_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string("("))&&whitespace_parser_instance->ParseMany(index,0,-1)&&r_value_parser_instance->ParseSingleSave(index,r_value_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string(")"))&&whitespace_parser_instance->ParseMany(index,0,-1)&&code_block_parser_instance->ParseSingleSave(index,code_block_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&else_tail_parser_instance->ParseOptionalSave(index,else_tail_field))
    {
        instance->SetElseTail(else_tail_field->GetValue());
        instance->SetCodeBlock(code_block_field->GetValue());
        instance->SetRValue(r_value_field->GetValue());
        instance->SetConditionalKey(conditional_key_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        else_tail_field = std::shared_ptr<ElseTailResult>(new ElseTailResult());
        code_block_field = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
        r_value_field = std::shared_ptr<RValueResult>(new RValueResult());
        conditional_key_field = std::shared_ptr<StringResult>(new StringResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool ConditionalParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<ConditionalResult> result = std::shared_ptr<ConditionalResult>(new ConditionalResult());
    return this->ParseSingleSave(index,result);
}

bool ConditionalParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ConditionalResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool ConditionalParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<ConditionalResult> result = std::shared_ptr<ConditionalResult>(new ConditionalResult());
    return this->ParseOptionalSave(index,result);
}

bool ConditionalParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<ConditionalListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<Conditional>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<ConditionalResult> result = std::shared_ptr<ConditionalResult>(new ConditionalResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool ConditionalParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<ConditionalListResult> result = std::shared_ptr<ConditionalListResult>(new ConditionalListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

ConditionalResult::ConditionalResult()
{
    this->value = NULL;
    this->result = false;
}

void ConditionalResult::SetValue(OmniPointer<Conditional> new_value)
{
    this->value = new_value;
}

OmniPointer<Conditional> ConditionalResult::GetValue()
{
    return this->value;
}

void ConditionalResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool ConditionalResult::GetResult()
{
    return this->result;
}

ConditionalListResult::ConditionalListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void ConditionalListResult::SetValue(std::vector<OmniPointer<Conditional>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<Conditional>> ConditionalListResult::GetValue()
{
    return this->value;
}

void ConditionalListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool ConditionalListResult::GetResult()
{
    return this->result;
}

Conditional::Conditional()
{
    this->length_string = NULL;
    this->else_tail_field = NULL;
    this->code_block_field = NULL;
    this->r_value_field = NULL;
    this->conditional_key_field = NULL;
}

void Conditional::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string Conditional::UnParse()
{
    return this->length_string->GetString();
}

void Conditional::SetElseTail(OmniPointer<ElseTail> input_value)
{
    this->else_tail_field = input_value;
}

OmniPointer<ElseTail> Conditional::GetElseTail()
{
    return this->else_tail_field;
}

void Conditional::SetCodeBlock(OmniPointer<CodeBlock> input_value)
{
    this->code_block_field = input_value;
}

OmniPointer<CodeBlock> Conditional::GetCodeBlock()
{
    return this->code_block_field;
}

void Conditional::SetRValue(OmniPointer<RValue> input_value)
{
    this->r_value_field = input_value;
}

OmniPointer<RValue> Conditional::GetRValue()
{
    return this->r_value_field;
}

void Conditional::SetConditionalKey(OmniPointer<String> input_value)
{
    this->conditional_key_field = input_value;
}

OmniPointer<String> Conditional::GetConditionalKey()
{
    return this->conditional_key_field;
}

LoopParser::LoopParser()
{
    this->parser_network = NULL;
}

void LoopParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool LoopParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<LoopResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<Loop> instance = std::shared_ptr<Loop>(new Loop());
    OmniPointer<CodeBlockResult> code_block_field = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
    OmniPointer<RValueResult> r_value_field = std::shared_ptr<RValueResult>(new RValueResult());
    OmniPointer<StringResult> loop_key_field = std::shared_ptr<StringResult>(new StringResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingleSave(index,std::string("while"),loop_key_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string("("))&&whitespace_parser_instance->ParseMany(index,0,-1)&&r_value_parser_instance->ParseSingleSave(index,r_value_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string(")"))&&whitespace_parser_instance->ParseMany(index,0,-1)&&code_block_parser_instance->ParseSingleSave(index,code_block_field)&&whitespace_parser_instance->ParseMany(index,0,-1))
    {
        instance->SetCodeBlock(code_block_field->GetValue());
        instance->SetRValue(r_value_field->GetValue());
        instance->SetLoopKey(loop_key_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        code_block_field = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
        r_value_field = std::shared_ptr<RValueResult>(new RValueResult());
        loop_key_field = std::shared_ptr<StringResult>(new StringResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool LoopParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<LoopResult> result = std::shared_ptr<LoopResult>(new LoopResult());
    return this->ParseSingleSave(index,result);
}

bool LoopParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<LoopResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool LoopParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<LoopResult> result = std::shared_ptr<LoopResult>(new LoopResult());
    return this->ParseOptionalSave(index,result);
}

bool LoopParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<LoopListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<Loop>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<LoopResult> result = std::shared_ptr<LoopResult>(new LoopResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool LoopParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<LoopListResult> result = std::shared_ptr<LoopListResult>(new LoopListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

LoopResult::LoopResult()
{
    this->value = NULL;
    this->result = false;
}

void LoopResult::SetValue(OmniPointer<Loop> new_value)
{
    this->value = new_value;
}

OmniPointer<Loop> LoopResult::GetValue()
{
    return this->value;
}

void LoopResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool LoopResult::GetResult()
{
    return this->result;
}

LoopListResult::LoopListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void LoopListResult::SetValue(std::vector<OmniPointer<Loop>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<Loop>> LoopListResult::GetValue()
{
    return this->value;
}

void LoopListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool LoopListResult::GetResult()
{
    return this->result;
}

Loop::Loop()
{
    this->length_string = NULL;
    this->code_block_field = NULL;
    this->r_value_field = NULL;
    this->loop_key_field = NULL;
}

void Loop::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string Loop::UnParse()
{
    return this->length_string->GetString();
}

void Loop::SetCodeBlock(OmniPointer<CodeBlock> input_value)
{
    this->code_block_field = input_value;
}

OmniPointer<CodeBlock> Loop::GetCodeBlock()
{
    return this->code_block_field;
}

void Loop::SetRValue(OmniPointer<RValue> input_value)
{
    this->r_value_field = input_value;
}

OmniPointer<RValue> Loop::GetRValue()
{
    return this->r_value_field;
}

void Loop::SetLoopKey(OmniPointer<String> input_value)
{
    this->loop_key_field = input_value;
}

OmniPointer<String> Loop::GetLoopKey()
{
    return this->loop_key_field;
}

CallParser::CallParser()
{
    this->parser_network = NULL;
}

void CallParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool CallParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<CallResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<Call> instance = std::shared_ptr<Call>(new Call());
    OmniPointer<QualfiedNameResult> function_chain_field = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
    OmniPointer<ParameterListResult> parameters_field = std::shared_ptr<ParameterListResult>(new ParameterListResult());
    OmniPointer<NameResult> function_field = std::shared_ptr<NameResult>(new NameResult());
    OmniPointer<NameResult> variable_field = std::shared_ptr<NameResult>(new NameResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&name_parser_instance->ParseSingleSave(index,variable_field)&&string_parser_instance->ParseSingle(index,std::string("."))&&name_parser_instance->ParseSingleSave(index,function_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string("("))&&whitespace_parser_instance->ParseMany(index,0,-1)&&parameter_list_parser_instance->ParseOptionalSave(index,parameters_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string(")"))&&whitespace_parser_instance->ParseMany(index,0,-1))
    {
        instance->SetFunctionChain(function_chain_field->GetValue());
        instance->SetParameters(parameters_field->GetValue());
        instance->SetFunction(function_field->GetValue());
        instance->SetVariable(variable_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        function_chain_field = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
        parameters_field = std::shared_ptr<ParameterListResult>(new ParameterListResult());
        function_field = std::shared_ptr<NameResult>(new NameResult());
        variable_field = std::shared_ptr<NameResult>(new NameResult());
    }
    if (true&&name_parser_instance->ParseSingleSave(index,function_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string("("))&&whitespace_parser_instance->ParseMany(index,0,-1)&&parameter_list_parser_instance->ParseOptionalSave(index,parameters_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string(")"))&&whitespace_parser_instance->ParseMany(index,0,-1))
    {
        instance->SetFunctionChain(function_chain_field->GetValue());
        instance->SetParameters(parameters_field->GetValue());
        instance->SetFunction(function_field->GetValue());
        instance->SetVariable(variable_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        function_chain_field = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
        parameters_field = std::shared_ptr<ParameterListResult>(new ParameterListResult());
        function_field = std::shared_ptr<NameResult>(new NameResult());
        variable_field = std::shared_ptr<NameResult>(new NameResult());
    }
    if (true&&qualfied_name_parser_instance->ParseSingleSave(index,function_chain_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string("("))&&whitespace_parser_instance->ParseMany(index,0,-1)&&parameter_list_parser_instance->ParseOptionalSave(index,parameters_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string(")"))&&whitespace_parser_instance->ParseMany(index,0,-1))
    {
        instance->SetFunctionChain(function_chain_field->GetValue());
        instance->SetParameters(parameters_field->GetValue());
        instance->SetFunction(function_field->GetValue());
        instance->SetVariable(variable_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        function_chain_field = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
        parameters_field = std::shared_ptr<ParameterListResult>(new ParameterListResult());
        function_field = std::shared_ptr<NameResult>(new NameResult());
        variable_field = std::shared_ptr<NameResult>(new NameResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool CallParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<CallResult> result = std::shared_ptr<CallResult>(new CallResult());
    return this->ParseSingleSave(index,result);
}

bool CallParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<CallResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool CallParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<CallResult> result = std::shared_ptr<CallResult>(new CallResult());
    return this->ParseOptionalSave(index,result);
}

bool CallParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<CallListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<Call>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<CallResult> result = std::shared_ptr<CallResult>(new CallResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool CallParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<CallListResult> result = std::shared_ptr<CallListResult>(new CallListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

CallResult::CallResult()
{
    this->value = NULL;
    this->result = false;
}

void CallResult::SetValue(OmniPointer<Call> new_value)
{
    this->value = new_value;
}

OmniPointer<Call> CallResult::GetValue()
{
    return this->value;
}

void CallResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool CallResult::GetResult()
{
    return this->result;
}

CallListResult::CallListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void CallListResult::SetValue(std::vector<OmniPointer<Call>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<Call>> CallListResult::GetValue()
{
    return this->value;
}

void CallListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool CallListResult::GetResult()
{
    return this->result;
}

Call::Call()
{
    this->length_string = NULL;
    this->function_chain_field = NULL;
    this->parameters_field = NULL;
    this->function_field = NULL;
    this->variable_field = NULL;
}

void Call::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string Call::UnParse()
{
    return this->length_string->GetString();
}

void Call::SetFunctionChain(OmniPointer<QualfiedName> input_value)
{
    this->function_chain_field = input_value;
}

OmniPointer<QualfiedName> Call::GetFunctionChain()
{
    return this->function_chain_field;
}

void Call::SetParameters(OmniPointer<ParameterList> input_value)
{
    this->parameters_field = input_value;
}

OmniPointer<ParameterList> Call::GetParameters()
{
    return this->parameters_field;
}

void Call::SetFunction(OmniPointer<Name> input_value)
{
    this->function_field = input_value;
}

OmniPointer<Name> Call::GetFunction()
{
    return this->function_field;
}

void Call::SetVariable(OmniPointer<Name> input_value)
{
    this->variable_field = input_value;
}

OmniPointer<Name> Call::GetVariable()
{
    return this->variable_field;
}

AllocateParser::AllocateParser()
{
    this->parser_network = NULL;
}

void AllocateParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool AllocateParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<AllocateResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<Allocate> instance = std::shared_ptr<Allocate>(new Allocate());
    OmniPointer<QualfiedNameResult> managed_type_field = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string("new"))&&whitespace_parser_instance->ParseMany(index,1,-1)&&qualfied_name_parser_instance->ParseSingleSave(index,managed_type_field)&&whitespace_parser_instance->ParseMany(index,0,-1))
    {
        instance->SetManagedType(managed_type_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        managed_type_field = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool AllocateParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<AllocateResult> result = std::shared_ptr<AllocateResult>(new AllocateResult());
    return this->ParseSingleSave(index,result);
}

bool AllocateParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<AllocateResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool AllocateParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<AllocateResult> result = std::shared_ptr<AllocateResult>(new AllocateResult());
    return this->ParseOptionalSave(index,result);
}

bool AllocateParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<AllocateListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<Allocate>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<AllocateResult> result = std::shared_ptr<AllocateResult>(new AllocateResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool AllocateParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<AllocateListResult> result = std::shared_ptr<AllocateListResult>(new AllocateListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

AllocateResult::AllocateResult()
{
    this->value = NULL;
    this->result = false;
}

void AllocateResult::SetValue(OmniPointer<Allocate> new_value)
{
    this->value = new_value;
}

OmniPointer<Allocate> AllocateResult::GetValue()
{
    return this->value;
}

void AllocateResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool AllocateResult::GetResult()
{
    return this->result;
}

AllocateListResult::AllocateListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void AllocateListResult::SetValue(std::vector<OmniPointer<Allocate>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<Allocate>> AllocateListResult::GetValue()
{
    return this->value;
}

void AllocateListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool AllocateListResult::GetResult()
{
    return this->result;
}

Allocate::Allocate()
{
    this->length_string = NULL;
    this->managed_type_field = NULL;
}

void Allocate::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string Allocate::UnParse()
{
    return this->length_string->GetString();
}

void Allocate::SetManagedType(OmniPointer<QualfiedName> input_value)
{
    this->managed_type_field = input_value;
}

OmniPointer<QualfiedName> Allocate::GetManagedType()
{
    return this->managed_type_field;
}

InstructionParser::InstructionParser()
{
    this->parser_network = NULL;
}

void InstructionParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool InstructionParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<InstructionResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<Instruction> instance = std::shared_ptr<Instruction>(new Instruction());
    OmniPointer<LoopResult> loop_field = std::shared_ptr<LoopResult>(new LoopResult());
    OmniPointer<ConditionalResult> conditional_field = std::shared_ptr<ConditionalResult>(new ConditionalResult());
    OmniPointer<CallResult> call_field = std::shared_ptr<CallResult>(new CallResult());
    OmniPointer<ReturnResult> rtn_field = std::shared_ptr<ReturnResult>(new ReturnResult());
    OmniPointer<CodeBlockResult> code_block_field = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
    OmniPointer<AssignmentResult> assignment_field = std::shared_ptr<AssignmentResult>(new AssignmentResult());
    OmniPointer<DeclarationResult> declaration_field = std::shared_ptr<DeclarationResult>(new DeclarationResult());
    OmniPointer<CommentResult> comment_field = std::shared_ptr<CommentResult>(new CommentResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&comment_parser_instance->ParseOptionalSave(index,comment_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&code_block_parser_instance->ParseSingleSave(index,code_block_field))
    {
        instance->SetLoop(loop_field->GetValue());
        instance->SetConditional(conditional_field->GetValue());
        instance->SetCall(call_field->GetValue());
        instance->SetRtn(rtn_field->GetValue());
        instance->SetCodeBlock(code_block_field->GetValue());
        instance->SetAssignment(assignment_field->GetValue());
        instance->SetDeclaration(declaration_field->GetValue());
        instance->SetComment(comment_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        loop_field = std::shared_ptr<LoopResult>(new LoopResult());
        conditional_field = std::shared_ptr<ConditionalResult>(new ConditionalResult());
        call_field = std::shared_ptr<CallResult>(new CallResult());
        rtn_field = std::shared_ptr<ReturnResult>(new ReturnResult());
        code_block_field = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
        assignment_field = std::shared_ptr<AssignmentResult>(new AssignmentResult());
        declaration_field = std::shared_ptr<DeclarationResult>(new DeclarationResult());
        comment_field = std::shared_ptr<CommentResult>(new CommentResult());
    }
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&comment_parser_instance->ParseOptionalSave(index,comment_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&return_parser_instance->ParseSingleSave(index,rtn_field))
    {
        instance->SetLoop(loop_field->GetValue());
        instance->SetConditional(conditional_field->GetValue());
        instance->SetCall(call_field->GetValue());
        instance->SetRtn(rtn_field->GetValue());
        instance->SetCodeBlock(code_block_field->GetValue());
        instance->SetAssignment(assignment_field->GetValue());
        instance->SetDeclaration(declaration_field->GetValue());
        instance->SetComment(comment_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        loop_field = std::shared_ptr<LoopResult>(new LoopResult());
        conditional_field = std::shared_ptr<ConditionalResult>(new ConditionalResult());
        call_field = std::shared_ptr<CallResult>(new CallResult());
        rtn_field = std::shared_ptr<ReturnResult>(new ReturnResult());
        code_block_field = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
        assignment_field = std::shared_ptr<AssignmentResult>(new AssignmentResult());
        declaration_field = std::shared_ptr<DeclarationResult>(new DeclarationResult());
        comment_field = std::shared_ptr<CommentResult>(new CommentResult());
    }
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&comment_parser_instance->ParseOptionalSave(index,comment_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&declaration_parser_instance->ParseSingleSave(index,declaration_field))
    {
        instance->SetLoop(loop_field->GetValue());
        instance->SetConditional(conditional_field->GetValue());
        instance->SetCall(call_field->GetValue());
        instance->SetRtn(rtn_field->GetValue());
        instance->SetCodeBlock(code_block_field->GetValue());
        instance->SetAssignment(assignment_field->GetValue());
        instance->SetDeclaration(declaration_field->GetValue());
        instance->SetComment(comment_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        loop_field = std::shared_ptr<LoopResult>(new LoopResult());
        conditional_field = std::shared_ptr<ConditionalResult>(new ConditionalResult());
        call_field = std::shared_ptr<CallResult>(new CallResult());
        rtn_field = std::shared_ptr<ReturnResult>(new ReturnResult());
        code_block_field = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
        assignment_field = std::shared_ptr<AssignmentResult>(new AssignmentResult());
        declaration_field = std::shared_ptr<DeclarationResult>(new DeclarationResult());
        comment_field = std::shared_ptr<CommentResult>(new CommentResult());
    }
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&comment_parser_instance->ParseOptionalSave(index,comment_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&assignment_parser_instance->ParseSingleSave(index,assignment_field))
    {
        instance->SetLoop(loop_field->GetValue());
        instance->SetConditional(conditional_field->GetValue());
        instance->SetCall(call_field->GetValue());
        instance->SetRtn(rtn_field->GetValue());
        instance->SetCodeBlock(code_block_field->GetValue());
        instance->SetAssignment(assignment_field->GetValue());
        instance->SetDeclaration(declaration_field->GetValue());
        instance->SetComment(comment_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        loop_field = std::shared_ptr<LoopResult>(new LoopResult());
        conditional_field = std::shared_ptr<ConditionalResult>(new ConditionalResult());
        call_field = std::shared_ptr<CallResult>(new CallResult());
        rtn_field = std::shared_ptr<ReturnResult>(new ReturnResult());
        code_block_field = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
        assignment_field = std::shared_ptr<AssignmentResult>(new AssignmentResult());
        declaration_field = std::shared_ptr<DeclarationResult>(new DeclarationResult());
        comment_field = std::shared_ptr<CommentResult>(new CommentResult());
    }
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&comment_parser_instance->ParseOptionalSave(index,comment_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&call_parser_instance->ParseSingleSave(index,call_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string(";"))&&whitespace_parser_instance->ParseMany(index,0,-1))
    {
        instance->SetLoop(loop_field->GetValue());
        instance->SetConditional(conditional_field->GetValue());
        instance->SetCall(call_field->GetValue());
        instance->SetRtn(rtn_field->GetValue());
        instance->SetCodeBlock(code_block_field->GetValue());
        instance->SetAssignment(assignment_field->GetValue());
        instance->SetDeclaration(declaration_field->GetValue());
        instance->SetComment(comment_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        loop_field = std::shared_ptr<LoopResult>(new LoopResult());
        conditional_field = std::shared_ptr<ConditionalResult>(new ConditionalResult());
        call_field = std::shared_ptr<CallResult>(new CallResult());
        rtn_field = std::shared_ptr<ReturnResult>(new ReturnResult());
        code_block_field = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
        assignment_field = std::shared_ptr<AssignmentResult>(new AssignmentResult());
        declaration_field = std::shared_ptr<DeclarationResult>(new DeclarationResult());
        comment_field = std::shared_ptr<CommentResult>(new CommentResult());
    }
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&comment_parser_instance->ParseOptionalSave(index,comment_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&conditional_parser_instance->ParseSingleSave(index,conditional_field))
    {
        instance->SetLoop(loop_field->GetValue());
        instance->SetConditional(conditional_field->GetValue());
        instance->SetCall(call_field->GetValue());
        instance->SetRtn(rtn_field->GetValue());
        instance->SetCodeBlock(code_block_field->GetValue());
        instance->SetAssignment(assignment_field->GetValue());
        instance->SetDeclaration(declaration_field->GetValue());
        instance->SetComment(comment_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        loop_field = std::shared_ptr<LoopResult>(new LoopResult());
        conditional_field = std::shared_ptr<ConditionalResult>(new ConditionalResult());
        call_field = std::shared_ptr<CallResult>(new CallResult());
        rtn_field = std::shared_ptr<ReturnResult>(new ReturnResult());
        code_block_field = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
        assignment_field = std::shared_ptr<AssignmentResult>(new AssignmentResult());
        declaration_field = std::shared_ptr<DeclarationResult>(new DeclarationResult());
        comment_field = std::shared_ptr<CommentResult>(new CommentResult());
    }
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&comment_parser_instance->ParseOptionalSave(index,comment_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&loop_parser_instance->ParseSingleSave(index,loop_field))
    {
        instance->SetLoop(loop_field->GetValue());
        instance->SetConditional(conditional_field->GetValue());
        instance->SetCall(call_field->GetValue());
        instance->SetRtn(rtn_field->GetValue());
        instance->SetCodeBlock(code_block_field->GetValue());
        instance->SetAssignment(assignment_field->GetValue());
        instance->SetDeclaration(declaration_field->GetValue());
        instance->SetComment(comment_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        loop_field = std::shared_ptr<LoopResult>(new LoopResult());
        conditional_field = std::shared_ptr<ConditionalResult>(new ConditionalResult());
        call_field = std::shared_ptr<CallResult>(new CallResult());
        rtn_field = std::shared_ptr<ReturnResult>(new ReturnResult());
        code_block_field = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
        assignment_field = std::shared_ptr<AssignmentResult>(new AssignmentResult());
        declaration_field = std::shared_ptr<DeclarationResult>(new DeclarationResult());
        comment_field = std::shared_ptr<CommentResult>(new CommentResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool InstructionParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<InstructionResult> result = std::shared_ptr<InstructionResult>(new InstructionResult());
    return this->ParseSingleSave(index,result);
}

bool InstructionParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<InstructionResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool InstructionParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<InstructionResult> result = std::shared_ptr<InstructionResult>(new InstructionResult());
    return this->ParseOptionalSave(index,result);
}

bool InstructionParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<InstructionListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<Instruction>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<InstructionResult> result = std::shared_ptr<InstructionResult>(new InstructionResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool InstructionParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<InstructionListResult> result = std::shared_ptr<InstructionListResult>(new InstructionListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

InstructionResult::InstructionResult()
{
    this->value = NULL;
    this->result = false;
}

void InstructionResult::SetValue(OmniPointer<Instruction> new_value)
{
    this->value = new_value;
}

OmniPointer<Instruction> InstructionResult::GetValue()
{
    return this->value;
}

void InstructionResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool InstructionResult::GetResult()
{
    return this->result;
}

InstructionListResult::InstructionListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void InstructionListResult::SetValue(std::vector<OmniPointer<Instruction>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<Instruction>> InstructionListResult::GetValue()
{
    return this->value;
}

void InstructionListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool InstructionListResult::GetResult()
{
    return this->result;
}

Instruction::Instruction()
{
    this->length_string = NULL;
    this->loop_field = NULL;
    this->conditional_field = NULL;
    this->call_field = NULL;
    this->rtn_field = NULL;
    this->code_block_field = NULL;
    this->assignment_field = NULL;
    this->declaration_field = NULL;
    this->comment_field = NULL;
}

void Instruction::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string Instruction::UnParse()
{
    return this->length_string->GetString();
}

void Instruction::SetLoop(OmniPointer<Loop> input_value)
{
    this->loop_field = input_value;
}

OmniPointer<Loop> Instruction::GetLoop()
{
    return this->loop_field;
}

void Instruction::SetConditional(OmniPointer<Conditional> input_value)
{
    this->conditional_field = input_value;
}

OmniPointer<Conditional> Instruction::GetConditional()
{
    return this->conditional_field;
}

void Instruction::SetCall(OmniPointer<Call> input_value)
{
    this->call_field = input_value;
}

OmniPointer<Call> Instruction::GetCall()
{
    return this->call_field;
}

void Instruction::SetRtn(OmniPointer<Return> input_value)
{
    this->rtn_field = input_value;
}

OmniPointer<Return> Instruction::GetRtn()
{
    return this->rtn_field;
}

void Instruction::SetCodeBlock(OmniPointer<CodeBlock> input_value)
{
    this->code_block_field = input_value;
}

OmniPointer<CodeBlock> Instruction::GetCodeBlock()
{
    return this->code_block_field;
}

void Instruction::SetAssignment(OmniPointer<Assignment> input_value)
{
    this->assignment_field = input_value;
}

OmniPointer<Assignment> Instruction::GetAssignment()
{
    return this->assignment_field;
}

void Instruction::SetDeclaration(OmniPointer<Declaration> input_value)
{
    this->declaration_field = input_value;
}

OmniPointer<Declaration> Instruction::GetDeclaration()
{
    return this->declaration_field;
}

void Instruction::SetComment(OmniPointer<Comment> input_value)
{
    this->comment_field = input_value;
}

OmniPointer<Comment> Instruction::GetComment()
{
    return this->comment_field;
}

RValueSingleParser::RValueSingleParser()
{
    this->parser_network = NULL;
}

void RValueSingleParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool RValueSingleParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<RValueSingleResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<RValueSingle> instance = std::shared_ptr<RValueSingle>(new RValueSingle());
    OmniPointer<QualfiedNameResult> variable_field = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
    OmniPointer<LiteralResult> string_literal_field = std::shared_ptr<LiteralResult>(new LiteralResult());
    OmniPointer<NumberResult> integer_literal_field = std::shared_ptr<NumberResult>(new NumberResult());
    OmniPointer<DecimalResult> decimal_literal_field = std::shared_ptr<DecimalResult>(new DecimalResult());
    OmniPointer<ByteResult> byte_literal_field = std::shared_ptr<ByteResult>(new ByteResult());
    OmniPointer<AllocateResult> allocate_field = std::shared_ptr<AllocateResult>(new AllocateResult());
    OmniPointer<BooleanResult> boolean_literal_field = std::shared_ptr<BooleanResult>(new BooleanResult());
    OmniPointer<CallResult> call_field = std::shared_ptr<CallResult>(new CallResult());
    OmniPointer<UnaryOperatorResult> unary_operator_field = std::shared_ptr<UnaryOperatorResult>(new UnaryOperatorResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&unary_operator_parser_instance->ParseOptionalSave(index,unary_operator_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&call_parser_instance->ParseSingleSave(index,call_field))
    {
        instance->SetVariable(variable_field->GetValue());
        instance->SetStringLiteral(string_literal_field->GetValue());
        instance->SetIntegerLiteral(integer_literal_field->GetValue());
        instance->SetDecimalLiteral(decimal_literal_field->GetValue());
        instance->SetByteLiteral(byte_literal_field->GetValue());
        instance->SetAllocate(allocate_field->GetValue());
        instance->SetBooleanLiteral(boolean_literal_field->GetValue());
        instance->SetCall(call_field->GetValue());
        instance->SetUnaryOperator(unary_operator_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        variable_field = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
        string_literal_field = std::shared_ptr<LiteralResult>(new LiteralResult());
        integer_literal_field = std::shared_ptr<NumberResult>(new NumberResult());
        decimal_literal_field = std::shared_ptr<DecimalResult>(new DecimalResult());
        byte_literal_field = std::shared_ptr<ByteResult>(new ByteResult());
        allocate_field = std::shared_ptr<AllocateResult>(new AllocateResult());
        boolean_literal_field = std::shared_ptr<BooleanResult>(new BooleanResult());
        call_field = std::shared_ptr<CallResult>(new CallResult());
        unary_operator_field = std::shared_ptr<UnaryOperatorResult>(new UnaryOperatorResult());
    }
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&unary_operator_parser_instance->ParseOptionalSave(index,unary_operator_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&allocate_parser_instance->ParseSingleSave(index,allocate_field))
    {
        instance->SetVariable(variable_field->GetValue());
        instance->SetStringLiteral(string_literal_field->GetValue());
        instance->SetIntegerLiteral(integer_literal_field->GetValue());
        instance->SetDecimalLiteral(decimal_literal_field->GetValue());
        instance->SetByteLiteral(byte_literal_field->GetValue());
        instance->SetAllocate(allocate_field->GetValue());
        instance->SetBooleanLiteral(boolean_literal_field->GetValue());
        instance->SetCall(call_field->GetValue());
        instance->SetUnaryOperator(unary_operator_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        variable_field = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
        string_literal_field = std::shared_ptr<LiteralResult>(new LiteralResult());
        integer_literal_field = std::shared_ptr<NumberResult>(new NumberResult());
        decimal_literal_field = std::shared_ptr<DecimalResult>(new DecimalResult());
        byte_literal_field = std::shared_ptr<ByteResult>(new ByteResult());
        allocate_field = std::shared_ptr<AllocateResult>(new AllocateResult());
        boolean_literal_field = std::shared_ptr<BooleanResult>(new BooleanResult());
        call_field = std::shared_ptr<CallResult>(new CallResult());
        unary_operator_field = std::shared_ptr<UnaryOperatorResult>(new UnaryOperatorResult());
    }
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&unary_operator_parser_instance->ParseOptionalSave(index,unary_operator_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&byte_parser_instance->ParseSingleSave(index,byte_literal_field))
    {
        instance->SetVariable(variable_field->GetValue());
        instance->SetStringLiteral(string_literal_field->GetValue());
        instance->SetIntegerLiteral(integer_literal_field->GetValue());
        instance->SetDecimalLiteral(decimal_literal_field->GetValue());
        instance->SetByteLiteral(byte_literal_field->GetValue());
        instance->SetAllocate(allocate_field->GetValue());
        instance->SetBooleanLiteral(boolean_literal_field->GetValue());
        instance->SetCall(call_field->GetValue());
        instance->SetUnaryOperator(unary_operator_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        variable_field = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
        string_literal_field = std::shared_ptr<LiteralResult>(new LiteralResult());
        integer_literal_field = std::shared_ptr<NumberResult>(new NumberResult());
        decimal_literal_field = std::shared_ptr<DecimalResult>(new DecimalResult());
        byte_literal_field = std::shared_ptr<ByteResult>(new ByteResult());
        allocate_field = std::shared_ptr<AllocateResult>(new AllocateResult());
        boolean_literal_field = std::shared_ptr<BooleanResult>(new BooleanResult());
        call_field = std::shared_ptr<CallResult>(new CallResult());
        unary_operator_field = std::shared_ptr<UnaryOperatorResult>(new UnaryOperatorResult());
    }
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&unary_operator_parser_instance->ParseOptionalSave(index,unary_operator_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&decimal_parser_instance->ParseSingleSave(index,decimal_literal_field))
    {
        instance->SetVariable(variable_field->GetValue());
        instance->SetStringLiteral(string_literal_field->GetValue());
        instance->SetIntegerLiteral(integer_literal_field->GetValue());
        instance->SetDecimalLiteral(decimal_literal_field->GetValue());
        instance->SetByteLiteral(byte_literal_field->GetValue());
        instance->SetAllocate(allocate_field->GetValue());
        instance->SetBooleanLiteral(boolean_literal_field->GetValue());
        instance->SetCall(call_field->GetValue());
        instance->SetUnaryOperator(unary_operator_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        variable_field = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
        string_literal_field = std::shared_ptr<LiteralResult>(new LiteralResult());
        integer_literal_field = std::shared_ptr<NumberResult>(new NumberResult());
        decimal_literal_field = std::shared_ptr<DecimalResult>(new DecimalResult());
        byte_literal_field = std::shared_ptr<ByteResult>(new ByteResult());
        allocate_field = std::shared_ptr<AllocateResult>(new AllocateResult());
        boolean_literal_field = std::shared_ptr<BooleanResult>(new BooleanResult());
        call_field = std::shared_ptr<CallResult>(new CallResult());
        unary_operator_field = std::shared_ptr<UnaryOperatorResult>(new UnaryOperatorResult());
    }
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&unary_operator_parser_instance->ParseOptionalSave(index,unary_operator_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&number_parser_instance->ParseSingleSave(index,integer_literal_field))
    {
        instance->SetVariable(variable_field->GetValue());
        instance->SetStringLiteral(string_literal_field->GetValue());
        instance->SetIntegerLiteral(integer_literal_field->GetValue());
        instance->SetDecimalLiteral(decimal_literal_field->GetValue());
        instance->SetByteLiteral(byte_literal_field->GetValue());
        instance->SetAllocate(allocate_field->GetValue());
        instance->SetBooleanLiteral(boolean_literal_field->GetValue());
        instance->SetCall(call_field->GetValue());
        instance->SetUnaryOperator(unary_operator_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        variable_field = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
        string_literal_field = std::shared_ptr<LiteralResult>(new LiteralResult());
        integer_literal_field = std::shared_ptr<NumberResult>(new NumberResult());
        decimal_literal_field = std::shared_ptr<DecimalResult>(new DecimalResult());
        byte_literal_field = std::shared_ptr<ByteResult>(new ByteResult());
        allocate_field = std::shared_ptr<AllocateResult>(new AllocateResult());
        boolean_literal_field = std::shared_ptr<BooleanResult>(new BooleanResult());
        call_field = std::shared_ptr<CallResult>(new CallResult());
        unary_operator_field = std::shared_ptr<UnaryOperatorResult>(new UnaryOperatorResult());
    }
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&unary_operator_parser_instance->ParseOptionalSave(index,unary_operator_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&boolean_parser_instance->ParseSingleSave(index,boolean_literal_field))
    {
        instance->SetVariable(variable_field->GetValue());
        instance->SetStringLiteral(string_literal_field->GetValue());
        instance->SetIntegerLiteral(integer_literal_field->GetValue());
        instance->SetDecimalLiteral(decimal_literal_field->GetValue());
        instance->SetByteLiteral(byte_literal_field->GetValue());
        instance->SetAllocate(allocate_field->GetValue());
        instance->SetBooleanLiteral(boolean_literal_field->GetValue());
        instance->SetCall(call_field->GetValue());
        instance->SetUnaryOperator(unary_operator_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        variable_field = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
        string_literal_field = std::shared_ptr<LiteralResult>(new LiteralResult());
        integer_literal_field = std::shared_ptr<NumberResult>(new NumberResult());
        decimal_literal_field = std::shared_ptr<DecimalResult>(new DecimalResult());
        byte_literal_field = std::shared_ptr<ByteResult>(new ByteResult());
        allocate_field = std::shared_ptr<AllocateResult>(new AllocateResult());
        boolean_literal_field = std::shared_ptr<BooleanResult>(new BooleanResult());
        call_field = std::shared_ptr<CallResult>(new CallResult());
        unary_operator_field = std::shared_ptr<UnaryOperatorResult>(new UnaryOperatorResult());
    }
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&unary_operator_parser_instance->ParseOptionalSave(index,unary_operator_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&qualfied_name_parser_instance->ParseSingleSave(index,variable_field))
    {
        instance->SetVariable(variable_field->GetValue());
        instance->SetStringLiteral(string_literal_field->GetValue());
        instance->SetIntegerLiteral(integer_literal_field->GetValue());
        instance->SetDecimalLiteral(decimal_literal_field->GetValue());
        instance->SetByteLiteral(byte_literal_field->GetValue());
        instance->SetAllocate(allocate_field->GetValue());
        instance->SetBooleanLiteral(boolean_literal_field->GetValue());
        instance->SetCall(call_field->GetValue());
        instance->SetUnaryOperator(unary_operator_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        variable_field = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
        string_literal_field = std::shared_ptr<LiteralResult>(new LiteralResult());
        integer_literal_field = std::shared_ptr<NumberResult>(new NumberResult());
        decimal_literal_field = std::shared_ptr<DecimalResult>(new DecimalResult());
        byte_literal_field = std::shared_ptr<ByteResult>(new ByteResult());
        allocate_field = std::shared_ptr<AllocateResult>(new AllocateResult());
        boolean_literal_field = std::shared_ptr<BooleanResult>(new BooleanResult());
        call_field = std::shared_ptr<CallResult>(new CallResult());
        unary_operator_field = std::shared_ptr<UnaryOperatorResult>(new UnaryOperatorResult());
    }
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&unary_operator_parser_instance->ParseOptionalSave(index,unary_operator_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&string_parser_instance->ParseSingle(index,std::string("\""))&&literal_parser_instance->ParseSingleSave(index,string_literal_field)&&string_parser_instance->ParseSingle(index,std::string("\"")))
    {
        instance->SetVariable(variable_field->GetValue());
        instance->SetStringLiteral(string_literal_field->GetValue());
        instance->SetIntegerLiteral(integer_literal_field->GetValue());
        instance->SetDecimalLiteral(decimal_literal_field->GetValue());
        instance->SetByteLiteral(byte_literal_field->GetValue());
        instance->SetAllocate(allocate_field->GetValue());
        instance->SetBooleanLiteral(boolean_literal_field->GetValue());
        instance->SetCall(call_field->GetValue());
        instance->SetUnaryOperator(unary_operator_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        variable_field = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
        string_literal_field = std::shared_ptr<LiteralResult>(new LiteralResult());
        integer_literal_field = std::shared_ptr<NumberResult>(new NumberResult());
        decimal_literal_field = std::shared_ptr<DecimalResult>(new DecimalResult());
        byte_literal_field = std::shared_ptr<ByteResult>(new ByteResult());
        allocate_field = std::shared_ptr<AllocateResult>(new AllocateResult());
        boolean_literal_field = std::shared_ptr<BooleanResult>(new BooleanResult());
        call_field = std::shared_ptr<CallResult>(new CallResult());
        unary_operator_field = std::shared_ptr<UnaryOperatorResult>(new UnaryOperatorResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool RValueSingleParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<RValueSingleResult> result = std::shared_ptr<RValueSingleResult>(new RValueSingleResult());
    return this->ParseSingleSave(index,result);
}

bool RValueSingleParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<RValueSingleResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool RValueSingleParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<RValueSingleResult> result = std::shared_ptr<RValueSingleResult>(new RValueSingleResult());
    return this->ParseOptionalSave(index,result);
}

bool RValueSingleParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<RValueSingleListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<RValueSingle>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<RValueSingleResult> result = std::shared_ptr<RValueSingleResult>(new RValueSingleResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool RValueSingleParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<RValueSingleListResult> result = std::shared_ptr<RValueSingleListResult>(new RValueSingleListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

RValueSingleResult::RValueSingleResult()
{
    this->value = NULL;
    this->result = false;
}

void RValueSingleResult::SetValue(OmniPointer<RValueSingle> new_value)
{
    this->value = new_value;
}

OmniPointer<RValueSingle> RValueSingleResult::GetValue()
{
    return this->value;
}

void RValueSingleResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool RValueSingleResult::GetResult()
{
    return this->result;
}

RValueSingleListResult::RValueSingleListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void RValueSingleListResult::SetValue(std::vector<OmniPointer<RValueSingle>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<RValueSingle>> RValueSingleListResult::GetValue()
{
    return this->value;
}

void RValueSingleListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool RValueSingleListResult::GetResult()
{
    return this->result;
}

RValueSingle::RValueSingle()
{
    this->length_string = NULL;
    this->variable_field = NULL;
    this->string_literal_field = NULL;
    this->integer_literal_field = NULL;
    this->decimal_literal_field = NULL;
    this->byte_literal_field = NULL;
    this->allocate_field = NULL;
    this->boolean_literal_field = NULL;
    this->call_field = NULL;
    this->unary_operator_field = NULL;
}

void RValueSingle::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string RValueSingle::UnParse()
{
    return this->length_string->GetString();
}

void RValueSingle::SetVariable(OmniPointer<QualfiedName> input_value)
{
    this->variable_field = input_value;
}

OmniPointer<QualfiedName> RValueSingle::GetVariable()
{
    return this->variable_field;
}

void RValueSingle::SetStringLiteral(OmniPointer<Literal> input_value)
{
    this->string_literal_field = input_value;
}

OmniPointer<Literal> RValueSingle::GetStringLiteral()
{
    return this->string_literal_field;
}

void RValueSingle::SetIntegerLiteral(OmniPointer<Number> input_value)
{
    this->integer_literal_field = input_value;
}

OmniPointer<Number> RValueSingle::GetIntegerLiteral()
{
    return this->integer_literal_field;
}

void RValueSingle::SetDecimalLiteral(OmniPointer<Decimal> input_value)
{
    this->decimal_literal_field = input_value;
}

OmniPointer<Decimal> RValueSingle::GetDecimalLiteral()
{
    return this->decimal_literal_field;
}

void RValueSingle::SetByteLiteral(OmniPointer<Byte> input_value)
{
    this->byte_literal_field = input_value;
}

OmniPointer<Byte> RValueSingle::GetByteLiteral()
{
    return this->byte_literal_field;
}

void RValueSingle::SetAllocate(OmniPointer<Allocate> input_value)
{
    this->allocate_field = input_value;
}

OmniPointer<Allocate> RValueSingle::GetAllocate()
{
    return this->allocate_field;
}

void RValueSingle::SetBooleanLiteral(OmniPointer<Boolean> input_value)
{
    this->boolean_literal_field = input_value;
}

OmniPointer<Boolean> RValueSingle::GetBooleanLiteral()
{
    return this->boolean_literal_field;
}

void RValueSingle::SetCall(OmniPointer<Call> input_value)
{
    this->call_field = input_value;
}

OmniPointer<Call> RValueSingle::GetCall()
{
    return this->call_field;
}

void RValueSingle::SetUnaryOperator(OmniPointer<UnaryOperator> input_value)
{
    this->unary_operator_field = input_value;
}

OmniPointer<UnaryOperator> RValueSingle::GetUnaryOperator()
{
    return this->unary_operator_field;
}

RValueTailParser::RValueTailParser()
{
    this->parser_network = NULL;
}

void RValueTailParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool RValueTailParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<RValueTailResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<RValueTail> instance = std::shared_ptr<RValueTail>(new RValueTail());
    OmniPointer<RValueTailResult> tail_field = std::shared_ptr<RValueTailResult>(new RValueTailResult());
    OmniPointer<RValueSingleResult> value_field = std::shared_ptr<RValueSingleResult>(new RValueSingleResult());
    OmniPointer<BinaryOperatorResult> binary_operator_field = std::shared_ptr<BinaryOperatorResult>(new BinaryOperatorResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&whitespace_parser_instance->ParseMany(index,0,-1)&&binary_operator_parser_instance->ParseSingleSave(index,binary_operator_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&r_value_single_parser_instance->ParseSingleSave(index,value_field)&&whitespace_parser_instance->ParseMany(index,0,-1)&&r_value_tail_parser_instance->ParseOptionalSave(index,tail_field))
    {
        instance->SetTail(tail_field->GetValue());
        instance->SetValue(value_field->GetValue());
        instance->SetBinaryOperator(binary_operator_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        tail_field = std::shared_ptr<RValueTailResult>(new RValueTailResult());
        value_field = std::shared_ptr<RValueSingleResult>(new RValueSingleResult());
        binary_operator_field = std::shared_ptr<BinaryOperatorResult>(new BinaryOperatorResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool RValueTailParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<RValueTailResult> result = std::shared_ptr<RValueTailResult>(new RValueTailResult());
    return this->ParseSingleSave(index,result);
}

bool RValueTailParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<RValueTailResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool RValueTailParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<RValueTailResult> result = std::shared_ptr<RValueTailResult>(new RValueTailResult());
    return this->ParseOptionalSave(index,result);
}

bool RValueTailParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<RValueTailListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<RValueTail>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<RValueTailResult> result = std::shared_ptr<RValueTailResult>(new RValueTailResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool RValueTailParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<RValueTailListResult> result = std::shared_ptr<RValueTailListResult>(new RValueTailListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

RValueTailResult::RValueTailResult()
{
    this->value = NULL;
    this->result = false;
}

void RValueTailResult::SetValue(OmniPointer<RValueTail> new_value)
{
    this->value = new_value;
}

OmniPointer<RValueTail> RValueTailResult::GetValue()
{
    return this->value;
}

void RValueTailResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool RValueTailResult::GetResult()
{
    return this->result;
}

RValueTailListResult::RValueTailListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void RValueTailListResult::SetValue(std::vector<OmniPointer<RValueTail>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<RValueTail>> RValueTailListResult::GetValue()
{
    return this->value;
}

void RValueTailListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool RValueTailListResult::GetResult()
{
    return this->result;
}

RValueTail::RValueTail()
{
    this->length_string = NULL;
    this->tail_field = NULL;
    this->value_field = NULL;
    this->binary_operator_field = NULL;
}

void RValueTail::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string RValueTail::UnParse()
{
    return this->length_string->GetString();
}

void RValueTail::SetTail(OmniPointer<RValueTail> input_value)
{
    this->tail_field = input_value;
}

OmniPointer<RValueTail> RValueTail::GetTail()
{
    return this->tail_field;
}

void RValueTail::SetValue(OmniPointer<RValueSingle> input_value)
{
    this->value_field = input_value;
}

OmniPointer<RValueSingle> RValueTail::GetValue()
{
    return this->value_field;
}

void RValueTail::SetBinaryOperator(OmniPointer<BinaryOperator> input_value)
{
    this->binary_operator_field = input_value;
}

OmniPointer<BinaryOperator> RValueTail::GetBinaryOperator()
{
    return this->binary_operator_field;
}

RValueParser::RValueParser()
{
    this->parser_network = NULL;
}

void RValueParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool RValueParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<RValueResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<RValue> instance = std::shared_ptr<RValue>(new RValue());
    OmniPointer<RValueTailResult> tail_field = std::shared_ptr<RValueTailResult>(new RValueTailResult());
    OmniPointer<RValueSingleResult> value_field = std::shared_ptr<RValueSingleResult>(new RValueSingleResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&r_value_single_parser_instance->ParseSingleSave(index,value_field)&&r_value_tail_parser_instance->ParseOptionalSave(index,tail_field))
    {
        instance->SetTail(tail_field->GetValue());
        instance->SetValue(value_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        tail_field = std::shared_ptr<RValueTailResult>(new RValueTailResult());
        value_field = std::shared_ptr<RValueSingleResult>(new RValueSingleResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool RValueParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<RValueResult> result = std::shared_ptr<RValueResult>(new RValueResult());
    return this->ParseSingleSave(index,result);
}

bool RValueParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<RValueResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool RValueParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<RValueResult> result = std::shared_ptr<RValueResult>(new RValueResult());
    return this->ParseOptionalSave(index,result);
}

bool RValueParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<RValueListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<RValue>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<RValueResult> result = std::shared_ptr<RValueResult>(new RValueResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool RValueParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<RValueListResult> result = std::shared_ptr<RValueListResult>(new RValueListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

RValueResult::RValueResult()
{
    this->value = NULL;
    this->result = false;
}

void RValueResult::SetValue(OmniPointer<RValue> new_value)
{
    this->value = new_value;
}

OmniPointer<RValue> RValueResult::GetValue()
{
    return this->value;
}

void RValueResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool RValueResult::GetResult()
{
    return this->result;
}

RValueListResult::RValueListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void RValueListResult::SetValue(std::vector<OmniPointer<RValue>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<RValue>> RValueListResult::GetValue()
{
    return this->value;
}

void RValueListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool RValueListResult::GetResult()
{
    return this->result;
}

RValue::RValue()
{
    this->length_string = NULL;
    this->tail_field = NULL;
    this->value_field = NULL;
}

void RValue::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string RValue::UnParse()
{
    return this->length_string->GetString();
}

void RValue::SetTail(OmniPointer<RValueTail> input_value)
{
    this->tail_field = input_value;
}

OmniPointer<RValueTail> RValue::GetTail()
{
    return this->tail_field;
}

void RValue::SetValue(OmniPointer<RValueSingle> input_value)
{
    this->value_field = input_value;
}

OmniPointer<RValueSingle> RValue::GetValue()
{
    return this->value_field;
}

BinaryOperatorParser::BinaryOperatorParser()
{
    this->parser_network = NULL;
}

void BinaryOperatorParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool BinaryOperatorParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<BinaryOperatorResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<BinaryOperator> instance = std::shared_ptr<BinaryOperator>(new BinaryOperator());
    OmniPointer<StringResult> and_op_field = std::shared_ptr<StringResult>(new StringResult());
    OmniPointer<StringResult> not_equality_field = std::shared_ptr<StringResult>(new StringResult());
    OmniPointer<StringResult> or_op_field = std::shared_ptr<StringResult>(new StringResult());
    OmniPointer<StringResult> greater_than_field = std::shared_ptr<StringResult>(new StringResult());
    OmniPointer<StringResult> less_than_field = std::shared_ptr<StringResult>(new StringResult());
    OmniPointer<StringResult> equality_field = std::shared_ptr<StringResult>(new StringResult());
    OmniPointer<StringResult> greater_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
    OmniPointer<StringResult> less_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
    OmniPointer<StringResult> subtraction_field = std::shared_ptr<StringResult>(new StringResult());
    OmniPointer<StringResult> addition_field = std::shared_ptr<StringResult>(new StringResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&string_parser_instance->ParseSingleSave(index,std::string("+"),addition_field))
    {
        instance->SetAndOp(and_op_field->GetValue());
        instance->SetNotEquality(not_equality_field->GetValue());
        instance->SetOrOp(or_op_field->GetValue());
        instance->SetGreaterThan(greater_than_field->GetValue());
        instance->SetLessThan(less_than_field->GetValue());
        instance->SetEquality(equality_field->GetValue());
        instance->SetGreaterThanEq(greater_than_eq_field->GetValue());
        instance->SetLessThanEq(less_than_eq_field->GetValue());
        instance->SetSubtraction(subtraction_field->GetValue());
        instance->SetAddition(addition_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        and_op_field = std::shared_ptr<StringResult>(new StringResult());
        not_equality_field = std::shared_ptr<StringResult>(new StringResult());
        or_op_field = std::shared_ptr<StringResult>(new StringResult());
        greater_than_field = std::shared_ptr<StringResult>(new StringResult());
        less_than_field = std::shared_ptr<StringResult>(new StringResult());
        equality_field = std::shared_ptr<StringResult>(new StringResult());
        greater_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
        less_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
        subtraction_field = std::shared_ptr<StringResult>(new StringResult());
        addition_field = std::shared_ptr<StringResult>(new StringResult());
    }
    if (true&&string_parser_instance->ParseSingleSave(index,std::string("-"),subtraction_field))
    {
        instance->SetAndOp(and_op_field->GetValue());
        instance->SetNotEquality(not_equality_field->GetValue());
        instance->SetOrOp(or_op_field->GetValue());
        instance->SetGreaterThan(greater_than_field->GetValue());
        instance->SetLessThan(less_than_field->GetValue());
        instance->SetEquality(equality_field->GetValue());
        instance->SetGreaterThanEq(greater_than_eq_field->GetValue());
        instance->SetLessThanEq(less_than_eq_field->GetValue());
        instance->SetSubtraction(subtraction_field->GetValue());
        instance->SetAddition(addition_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        and_op_field = std::shared_ptr<StringResult>(new StringResult());
        not_equality_field = std::shared_ptr<StringResult>(new StringResult());
        or_op_field = std::shared_ptr<StringResult>(new StringResult());
        greater_than_field = std::shared_ptr<StringResult>(new StringResult());
        less_than_field = std::shared_ptr<StringResult>(new StringResult());
        equality_field = std::shared_ptr<StringResult>(new StringResult());
        greater_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
        less_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
        subtraction_field = std::shared_ptr<StringResult>(new StringResult());
        addition_field = std::shared_ptr<StringResult>(new StringResult());
    }
    if (true&&string_parser_instance->ParseSingleSave(index,std::string("<="),less_than_eq_field))
    {
        instance->SetAndOp(and_op_field->GetValue());
        instance->SetNotEquality(not_equality_field->GetValue());
        instance->SetOrOp(or_op_field->GetValue());
        instance->SetGreaterThan(greater_than_field->GetValue());
        instance->SetLessThan(less_than_field->GetValue());
        instance->SetEquality(equality_field->GetValue());
        instance->SetGreaterThanEq(greater_than_eq_field->GetValue());
        instance->SetLessThanEq(less_than_eq_field->GetValue());
        instance->SetSubtraction(subtraction_field->GetValue());
        instance->SetAddition(addition_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        and_op_field = std::shared_ptr<StringResult>(new StringResult());
        not_equality_field = std::shared_ptr<StringResult>(new StringResult());
        or_op_field = std::shared_ptr<StringResult>(new StringResult());
        greater_than_field = std::shared_ptr<StringResult>(new StringResult());
        less_than_field = std::shared_ptr<StringResult>(new StringResult());
        equality_field = std::shared_ptr<StringResult>(new StringResult());
        greater_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
        less_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
        subtraction_field = std::shared_ptr<StringResult>(new StringResult());
        addition_field = std::shared_ptr<StringResult>(new StringResult());
    }
    if (true&&string_parser_instance->ParseSingleSave(index,std::string(">="),greater_than_eq_field))
    {
        instance->SetAndOp(and_op_field->GetValue());
        instance->SetNotEquality(not_equality_field->GetValue());
        instance->SetOrOp(or_op_field->GetValue());
        instance->SetGreaterThan(greater_than_field->GetValue());
        instance->SetLessThan(less_than_field->GetValue());
        instance->SetEquality(equality_field->GetValue());
        instance->SetGreaterThanEq(greater_than_eq_field->GetValue());
        instance->SetLessThanEq(less_than_eq_field->GetValue());
        instance->SetSubtraction(subtraction_field->GetValue());
        instance->SetAddition(addition_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        and_op_field = std::shared_ptr<StringResult>(new StringResult());
        not_equality_field = std::shared_ptr<StringResult>(new StringResult());
        or_op_field = std::shared_ptr<StringResult>(new StringResult());
        greater_than_field = std::shared_ptr<StringResult>(new StringResult());
        less_than_field = std::shared_ptr<StringResult>(new StringResult());
        equality_field = std::shared_ptr<StringResult>(new StringResult());
        greater_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
        less_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
        subtraction_field = std::shared_ptr<StringResult>(new StringResult());
        addition_field = std::shared_ptr<StringResult>(new StringResult());
    }
    if (true&&string_parser_instance->ParseSingleSave(index,std::string("=="),equality_field))
    {
        instance->SetAndOp(and_op_field->GetValue());
        instance->SetNotEquality(not_equality_field->GetValue());
        instance->SetOrOp(or_op_field->GetValue());
        instance->SetGreaterThan(greater_than_field->GetValue());
        instance->SetLessThan(less_than_field->GetValue());
        instance->SetEquality(equality_field->GetValue());
        instance->SetGreaterThanEq(greater_than_eq_field->GetValue());
        instance->SetLessThanEq(less_than_eq_field->GetValue());
        instance->SetSubtraction(subtraction_field->GetValue());
        instance->SetAddition(addition_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        and_op_field = std::shared_ptr<StringResult>(new StringResult());
        not_equality_field = std::shared_ptr<StringResult>(new StringResult());
        or_op_field = std::shared_ptr<StringResult>(new StringResult());
        greater_than_field = std::shared_ptr<StringResult>(new StringResult());
        less_than_field = std::shared_ptr<StringResult>(new StringResult());
        equality_field = std::shared_ptr<StringResult>(new StringResult());
        greater_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
        less_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
        subtraction_field = std::shared_ptr<StringResult>(new StringResult());
        addition_field = std::shared_ptr<StringResult>(new StringResult());
    }
    if (true&&string_parser_instance->ParseSingleSave(index,std::string("!="),not_equality_field))
    {
        instance->SetAndOp(and_op_field->GetValue());
        instance->SetNotEquality(not_equality_field->GetValue());
        instance->SetOrOp(or_op_field->GetValue());
        instance->SetGreaterThan(greater_than_field->GetValue());
        instance->SetLessThan(less_than_field->GetValue());
        instance->SetEquality(equality_field->GetValue());
        instance->SetGreaterThanEq(greater_than_eq_field->GetValue());
        instance->SetLessThanEq(less_than_eq_field->GetValue());
        instance->SetSubtraction(subtraction_field->GetValue());
        instance->SetAddition(addition_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        and_op_field = std::shared_ptr<StringResult>(new StringResult());
        not_equality_field = std::shared_ptr<StringResult>(new StringResult());
        or_op_field = std::shared_ptr<StringResult>(new StringResult());
        greater_than_field = std::shared_ptr<StringResult>(new StringResult());
        less_than_field = std::shared_ptr<StringResult>(new StringResult());
        equality_field = std::shared_ptr<StringResult>(new StringResult());
        greater_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
        less_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
        subtraction_field = std::shared_ptr<StringResult>(new StringResult());
        addition_field = std::shared_ptr<StringResult>(new StringResult());
    }
    if (true&&string_parser_instance->ParseSingleSave(index,std::string("<"),less_than_field))
    {
        instance->SetAndOp(and_op_field->GetValue());
        instance->SetNotEquality(not_equality_field->GetValue());
        instance->SetOrOp(or_op_field->GetValue());
        instance->SetGreaterThan(greater_than_field->GetValue());
        instance->SetLessThan(less_than_field->GetValue());
        instance->SetEquality(equality_field->GetValue());
        instance->SetGreaterThanEq(greater_than_eq_field->GetValue());
        instance->SetLessThanEq(less_than_eq_field->GetValue());
        instance->SetSubtraction(subtraction_field->GetValue());
        instance->SetAddition(addition_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        and_op_field = std::shared_ptr<StringResult>(new StringResult());
        not_equality_field = std::shared_ptr<StringResult>(new StringResult());
        or_op_field = std::shared_ptr<StringResult>(new StringResult());
        greater_than_field = std::shared_ptr<StringResult>(new StringResult());
        less_than_field = std::shared_ptr<StringResult>(new StringResult());
        equality_field = std::shared_ptr<StringResult>(new StringResult());
        greater_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
        less_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
        subtraction_field = std::shared_ptr<StringResult>(new StringResult());
        addition_field = std::shared_ptr<StringResult>(new StringResult());
    }
    if (true&&string_parser_instance->ParseSingleSave(index,std::string(">"),greater_than_field))
    {
        instance->SetAndOp(and_op_field->GetValue());
        instance->SetNotEquality(not_equality_field->GetValue());
        instance->SetOrOp(or_op_field->GetValue());
        instance->SetGreaterThan(greater_than_field->GetValue());
        instance->SetLessThan(less_than_field->GetValue());
        instance->SetEquality(equality_field->GetValue());
        instance->SetGreaterThanEq(greater_than_eq_field->GetValue());
        instance->SetLessThanEq(less_than_eq_field->GetValue());
        instance->SetSubtraction(subtraction_field->GetValue());
        instance->SetAddition(addition_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        and_op_field = std::shared_ptr<StringResult>(new StringResult());
        not_equality_field = std::shared_ptr<StringResult>(new StringResult());
        or_op_field = std::shared_ptr<StringResult>(new StringResult());
        greater_than_field = std::shared_ptr<StringResult>(new StringResult());
        less_than_field = std::shared_ptr<StringResult>(new StringResult());
        equality_field = std::shared_ptr<StringResult>(new StringResult());
        greater_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
        less_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
        subtraction_field = std::shared_ptr<StringResult>(new StringResult());
        addition_field = std::shared_ptr<StringResult>(new StringResult());
    }
    if (true&&string_parser_instance->ParseSingleSave(index,std::string("||"),or_op_field))
    {
        instance->SetAndOp(and_op_field->GetValue());
        instance->SetNotEquality(not_equality_field->GetValue());
        instance->SetOrOp(or_op_field->GetValue());
        instance->SetGreaterThan(greater_than_field->GetValue());
        instance->SetLessThan(less_than_field->GetValue());
        instance->SetEquality(equality_field->GetValue());
        instance->SetGreaterThanEq(greater_than_eq_field->GetValue());
        instance->SetLessThanEq(less_than_eq_field->GetValue());
        instance->SetSubtraction(subtraction_field->GetValue());
        instance->SetAddition(addition_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        and_op_field = std::shared_ptr<StringResult>(new StringResult());
        not_equality_field = std::shared_ptr<StringResult>(new StringResult());
        or_op_field = std::shared_ptr<StringResult>(new StringResult());
        greater_than_field = std::shared_ptr<StringResult>(new StringResult());
        less_than_field = std::shared_ptr<StringResult>(new StringResult());
        equality_field = std::shared_ptr<StringResult>(new StringResult());
        greater_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
        less_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
        subtraction_field = std::shared_ptr<StringResult>(new StringResult());
        addition_field = std::shared_ptr<StringResult>(new StringResult());
    }
    if (true&&string_parser_instance->ParseSingleSave(index,std::string("&&"),and_op_field))
    {
        instance->SetAndOp(and_op_field->GetValue());
        instance->SetNotEquality(not_equality_field->GetValue());
        instance->SetOrOp(or_op_field->GetValue());
        instance->SetGreaterThan(greater_than_field->GetValue());
        instance->SetLessThan(less_than_field->GetValue());
        instance->SetEquality(equality_field->GetValue());
        instance->SetGreaterThanEq(greater_than_eq_field->GetValue());
        instance->SetLessThanEq(less_than_eq_field->GetValue());
        instance->SetSubtraction(subtraction_field->GetValue());
        instance->SetAddition(addition_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        and_op_field = std::shared_ptr<StringResult>(new StringResult());
        not_equality_field = std::shared_ptr<StringResult>(new StringResult());
        or_op_field = std::shared_ptr<StringResult>(new StringResult());
        greater_than_field = std::shared_ptr<StringResult>(new StringResult());
        less_than_field = std::shared_ptr<StringResult>(new StringResult());
        equality_field = std::shared_ptr<StringResult>(new StringResult());
        greater_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
        less_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
        subtraction_field = std::shared_ptr<StringResult>(new StringResult());
        addition_field = std::shared_ptr<StringResult>(new StringResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool BinaryOperatorParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<BinaryOperatorResult> result = std::shared_ptr<BinaryOperatorResult>(new BinaryOperatorResult());
    return this->ParseSingleSave(index,result);
}

bool BinaryOperatorParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<BinaryOperatorResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool BinaryOperatorParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<BinaryOperatorResult> result = std::shared_ptr<BinaryOperatorResult>(new BinaryOperatorResult());
    return this->ParseOptionalSave(index,result);
}

bool BinaryOperatorParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<BinaryOperatorListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<BinaryOperator>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<BinaryOperatorResult> result = std::shared_ptr<BinaryOperatorResult>(new BinaryOperatorResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool BinaryOperatorParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<BinaryOperatorListResult> result = std::shared_ptr<BinaryOperatorListResult>(new BinaryOperatorListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

BinaryOperatorResult::BinaryOperatorResult()
{
    this->value = NULL;
    this->result = false;
}

void BinaryOperatorResult::SetValue(OmniPointer<BinaryOperator> new_value)
{
    this->value = new_value;
}

OmniPointer<BinaryOperator> BinaryOperatorResult::GetValue()
{
    return this->value;
}

void BinaryOperatorResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool BinaryOperatorResult::GetResult()
{
    return this->result;
}

BinaryOperatorListResult::BinaryOperatorListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void BinaryOperatorListResult::SetValue(std::vector<OmniPointer<BinaryOperator>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<BinaryOperator>> BinaryOperatorListResult::GetValue()
{
    return this->value;
}

void BinaryOperatorListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool BinaryOperatorListResult::GetResult()
{
    return this->result;
}

BinaryOperator::BinaryOperator()
{
    this->length_string = NULL;
    this->and_op_field = NULL;
    this->not_equality_field = NULL;
    this->or_op_field = NULL;
    this->greater_than_field = NULL;
    this->less_than_field = NULL;
    this->equality_field = NULL;
    this->greater_than_eq_field = NULL;
    this->less_than_eq_field = NULL;
    this->subtraction_field = NULL;
    this->addition_field = NULL;
}

void BinaryOperator::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string BinaryOperator::UnParse()
{
    return this->length_string->GetString();
}

void BinaryOperator::SetAndOp(OmniPointer<String> input_value)
{
    this->and_op_field = input_value;
}

OmniPointer<String> BinaryOperator::GetAndOp()
{
    return this->and_op_field;
}

void BinaryOperator::SetNotEquality(OmniPointer<String> input_value)
{
    this->not_equality_field = input_value;
}

OmniPointer<String> BinaryOperator::GetNotEquality()
{
    return this->not_equality_field;
}

void BinaryOperator::SetOrOp(OmniPointer<String> input_value)
{
    this->or_op_field = input_value;
}

OmniPointer<String> BinaryOperator::GetOrOp()
{
    return this->or_op_field;
}

void BinaryOperator::SetGreaterThan(OmniPointer<String> input_value)
{
    this->greater_than_field = input_value;
}

OmniPointer<String> BinaryOperator::GetGreaterThan()
{
    return this->greater_than_field;
}

void BinaryOperator::SetLessThan(OmniPointer<String> input_value)
{
    this->less_than_field = input_value;
}

OmniPointer<String> BinaryOperator::GetLessThan()
{
    return this->less_than_field;
}

void BinaryOperator::SetEquality(OmniPointer<String> input_value)
{
    this->equality_field = input_value;
}

OmniPointer<String> BinaryOperator::GetEquality()
{
    return this->equality_field;
}

void BinaryOperator::SetGreaterThanEq(OmniPointer<String> input_value)
{
    this->greater_than_eq_field = input_value;
}

OmniPointer<String> BinaryOperator::GetGreaterThanEq()
{
    return this->greater_than_eq_field;
}

void BinaryOperator::SetLessThanEq(OmniPointer<String> input_value)
{
    this->less_than_eq_field = input_value;
}

OmniPointer<String> BinaryOperator::GetLessThanEq()
{
    return this->less_than_eq_field;
}

void BinaryOperator::SetSubtraction(OmniPointer<String> input_value)
{
    this->subtraction_field = input_value;
}

OmniPointer<String> BinaryOperator::GetSubtraction()
{
    return this->subtraction_field;
}

void BinaryOperator::SetAddition(OmniPointer<String> input_value)
{
    this->addition_field = input_value;
}

OmniPointer<String> BinaryOperator::GetAddition()
{
    return this->addition_field;
}

UnaryOperatorParser::UnaryOperatorParser()
{
    this->parser_network = NULL;
}

void UnaryOperatorParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool UnaryOperatorParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<UnaryOperatorResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<UnaryOperator> instance = std::shared_ptr<UnaryOperator>(new UnaryOperator());
    OmniPointer<StringResult> negation_field = std::shared_ptr<StringResult>(new StringResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&string_parser_instance->ParseSingleSave(index,std::string("!"),negation_field))
    {
        instance->SetNegation(negation_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        negation_field = std::shared_ptr<StringResult>(new StringResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool UnaryOperatorParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<UnaryOperatorResult> result = std::shared_ptr<UnaryOperatorResult>(new UnaryOperatorResult());
    return this->ParseSingleSave(index,result);
}

bool UnaryOperatorParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<UnaryOperatorResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool UnaryOperatorParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<UnaryOperatorResult> result = std::shared_ptr<UnaryOperatorResult>(new UnaryOperatorResult());
    return this->ParseOptionalSave(index,result);
}

bool UnaryOperatorParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<UnaryOperatorListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<UnaryOperator>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<UnaryOperatorResult> result = std::shared_ptr<UnaryOperatorResult>(new UnaryOperatorResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool UnaryOperatorParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<UnaryOperatorListResult> result = std::shared_ptr<UnaryOperatorListResult>(new UnaryOperatorListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

UnaryOperatorResult::UnaryOperatorResult()
{
    this->value = NULL;
    this->result = false;
}

void UnaryOperatorResult::SetValue(OmniPointer<UnaryOperator> new_value)
{
    this->value = new_value;
}

OmniPointer<UnaryOperator> UnaryOperatorResult::GetValue()
{
    return this->value;
}

void UnaryOperatorResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool UnaryOperatorResult::GetResult()
{
    return this->result;
}

UnaryOperatorListResult::UnaryOperatorListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void UnaryOperatorListResult::SetValue(std::vector<OmniPointer<UnaryOperator>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<UnaryOperator>> UnaryOperatorListResult::GetValue()
{
    return this->value;
}

void UnaryOperatorListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool UnaryOperatorListResult::GetResult()
{
    return this->result;
}

UnaryOperator::UnaryOperator()
{
    this->length_string = NULL;
    this->negation_field = NULL;
}

void UnaryOperator::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string UnaryOperator::UnParse()
{
    return this->length_string->GetString();
}

void UnaryOperator::SetNegation(OmniPointer<String> input_value)
{
    this->negation_field = input_value;
}

OmniPointer<String> UnaryOperator::GetNegation()
{
    return this->negation_field;
}

CommentParser::CommentParser()
{
    this->parser_network = NULL;
}

void CommentParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool CommentParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<CommentResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<Comment> instance = std::shared_ptr<Comment>(new Comment());
    OmniPointer<CommentContentListResult> content_field = std::shared_ptr<CommentContentListResult>(new CommentContentListResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&string_parser_instance->ParseSingle(index,std::string("/*"))&&comment_content_parser_instance->ParseManySave(index,content_field,0,-1)&&string_parser_instance->ParseSingle(index,std::string("*/")))
    {
        instance->SetContent(content_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        content_field = std::shared_ptr<CommentContentListResult>(new CommentContentListResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool CommentParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<CommentResult> result = std::shared_ptr<CommentResult>(new CommentResult());
    return this->ParseSingleSave(index,result);
}

bool CommentParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<CommentResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool CommentParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<CommentResult> result = std::shared_ptr<CommentResult>(new CommentResult());
    return this->ParseOptionalSave(index,result);
}

bool CommentParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<CommentListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<Comment>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<CommentResult> result = std::shared_ptr<CommentResult>(new CommentResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool CommentParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<CommentListResult> result = std::shared_ptr<CommentListResult>(new CommentListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

CommentResult::CommentResult()
{
    this->value = NULL;
    this->result = false;
}

void CommentResult::SetValue(OmniPointer<Comment> new_value)
{
    this->value = new_value;
}

OmniPointer<Comment> CommentResult::GetValue()
{
    return this->value;
}

void CommentResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool CommentResult::GetResult()
{
    return this->result;
}

CommentListResult::CommentListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void CommentListResult::SetValue(std::vector<OmniPointer<Comment>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<Comment>> CommentListResult::GetValue()
{
    return this->value;
}

void CommentListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool CommentListResult::GetResult()
{
    return this->result;
}

Comment::Comment()
{
    this->length_string = NULL;
    /*this->content_field = NO_DEFAULT;*/
}

void Comment::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string Comment::UnParse()
{
    return this->length_string->GetString();
}

void Comment::SetContent(std::vector<OmniPointer<CommentContent>> input_value)
{
    this->content_field = input_value;
}

std::vector<OmniPointer<CommentContent>> Comment::GetContent()
{
    return this->content_field;
}

NonStarCharacterParser::NonStarCharacterParser()
{
    this->parser_network = NULL;
}

void NonStarCharacterParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool NonStarCharacterParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<NonStarCharacterResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<NonStarCharacter> instance = std::shared_ptr<NonStarCharacter>(new NonStarCharacter());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&character_range_parser_instance->ParseSingle(index,0x00,0x29))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    if (true&&character_range_parser_instance->ParseSingle(index,0x2B,0xFF))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    result->SetResult(false);
    return result->GetResult();
}

bool NonStarCharacterParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<NonStarCharacterResult> result = std::shared_ptr<NonStarCharacterResult>(new NonStarCharacterResult());
    return this->ParseSingleSave(index,result);
}

bool NonStarCharacterParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<NonStarCharacterResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool NonStarCharacterParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<NonStarCharacterResult> result = std::shared_ptr<NonStarCharacterResult>(new NonStarCharacterResult());
    return this->ParseOptionalSave(index,result);
}

bool NonStarCharacterParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<NonStarCharacterListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<NonStarCharacter>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<NonStarCharacterResult> result = std::shared_ptr<NonStarCharacterResult>(new NonStarCharacterResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool NonStarCharacterParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<NonStarCharacterListResult> result = std::shared_ptr<NonStarCharacterListResult>(new NonStarCharacterListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

NonStarCharacterResult::NonStarCharacterResult()
{
    this->value = NULL;
    this->result = false;
}

void NonStarCharacterResult::SetValue(OmniPointer<NonStarCharacter> new_value)
{
    this->value = new_value;
}

OmniPointer<NonStarCharacter> NonStarCharacterResult::GetValue()
{
    return this->value;
}

void NonStarCharacterResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool NonStarCharacterResult::GetResult()
{
    return this->result;
}

NonStarCharacterListResult::NonStarCharacterListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void NonStarCharacterListResult::SetValue(std::vector<OmniPointer<NonStarCharacter>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<NonStarCharacter>> NonStarCharacterListResult::GetValue()
{
    return this->value;
}

void NonStarCharacterListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool NonStarCharacterListResult::GetResult()
{
    return this->result;
}

NonStarCharacter::NonStarCharacter()
{
    this->length_string = NULL;
}

void NonStarCharacter::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string NonStarCharacter::UnParse()
{
    return this->length_string->GetString();
}

NonSlashCharacterParser::NonSlashCharacterParser()
{
    this->parser_network = NULL;
}

void NonSlashCharacterParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool NonSlashCharacterParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<NonSlashCharacterResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<NonSlashCharacter> instance = std::shared_ptr<NonSlashCharacter>(new NonSlashCharacter());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&character_range_parser_instance->ParseSingle(index,0x00,0x2E))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    if (true&&character_range_parser_instance->ParseSingle(index,0x30,0xFF))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    result->SetResult(false);
    return result->GetResult();
}

bool NonSlashCharacterParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<NonSlashCharacterResult> result = std::shared_ptr<NonSlashCharacterResult>(new NonSlashCharacterResult());
    return this->ParseSingleSave(index,result);
}

bool NonSlashCharacterParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<NonSlashCharacterResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool NonSlashCharacterParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<NonSlashCharacterResult> result = std::shared_ptr<NonSlashCharacterResult>(new NonSlashCharacterResult());
    return this->ParseOptionalSave(index,result);
}

bool NonSlashCharacterParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<NonSlashCharacterListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<NonSlashCharacter>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<NonSlashCharacterResult> result = std::shared_ptr<NonSlashCharacterResult>(new NonSlashCharacterResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool NonSlashCharacterParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<NonSlashCharacterListResult> result = std::shared_ptr<NonSlashCharacterListResult>(new NonSlashCharacterListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

NonSlashCharacterResult::NonSlashCharacterResult()
{
    this->value = NULL;
    this->result = false;
}

void NonSlashCharacterResult::SetValue(OmniPointer<NonSlashCharacter> new_value)
{
    this->value = new_value;
}

OmniPointer<NonSlashCharacter> NonSlashCharacterResult::GetValue()
{
    return this->value;
}

void NonSlashCharacterResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool NonSlashCharacterResult::GetResult()
{
    return this->result;
}

NonSlashCharacterListResult::NonSlashCharacterListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void NonSlashCharacterListResult::SetValue(std::vector<OmniPointer<NonSlashCharacter>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<NonSlashCharacter>> NonSlashCharacterListResult::GetValue()
{
    return this->value;
}

void NonSlashCharacterListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool NonSlashCharacterListResult::GetResult()
{
    return this->result;
}

NonSlashCharacter::NonSlashCharacter()
{
    this->length_string = NULL;
}

void NonSlashCharacter::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string NonSlashCharacter::UnParse()
{
    return this->length_string->GetString();
}

CommentContentParser::CommentContentParser()
{
    this->parser_network = NULL;
}

void CommentContentParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool CommentContentParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<CommentContentResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<CommentContent> instance = std::shared_ptr<CommentContent>(new CommentContent());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&non_star_character_parser_instance->ParseSingle(index))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    if (true&&string_parser_instance->ParseSingle(index,std::string("*"))&&non_slash_character_parser_instance->ParseSingle(index))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    result->SetResult(false);
    return result->GetResult();
}

bool CommentContentParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<CommentContentResult> result = std::shared_ptr<CommentContentResult>(new CommentContentResult());
    return this->ParseSingleSave(index,result);
}

bool CommentContentParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<CommentContentResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool CommentContentParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<CommentContentResult> result = std::shared_ptr<CommentContentResult>(new CommentContentResult());
    return this->ParseOptionalSave(index,result);
}

bool CommentContentParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<CommentContentListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<CommentContent>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<CommentContentResult> result = std::shared_ptr<CommentContentResult>(new CommentContentResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool CommentContentParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<CommentContentListResult> result = std::shared_ptr<CommentContentListResult>(new CommentContentListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

CommentContentResult::CommentContentResult()
{
    this->value = NULL;
    this->result = false;
}

void CommentContentResult::SetValue(OmniPointer<CommentContent> new_value)
{
    this->value = new_value;
}

OmniPointer<CommentContent> CommentContentResult::GetValue()
{
    return this->value;
}

void CommentContentResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool CommentContentResult::GetResult()
{
    return this->result;
}

CommentContentListResult::CommentContentListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void CommentContentListResult::SetValue(std::vector<OmniPointer<CommentContent>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<CommentContent>> CommentContentListResult::GetValue()
{
    return this->value;
}

void CommentContentListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool CommentContentListResult::GetResult()
{
    return this->result;
}

CommentContent::CommentContent()
{
    this->length_string = NULL;
}

void CommentContent::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string CommentContent::UnParse()
{
    return this->length_string->GetString();
}

QualfiedNameParser::QualfiedNameParser()
{
    this->parser_network = NULL;
}

void QualfiedNameParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool QualfiedNameParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<QualfiedNameResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<QualfiedName> instance = std::shared_ptr<QualfiedName>(new QualfiedName());
    OmniPointer<NameTailResult> tail_field = std::shared_ptr<NameTailResult>(new NameTailResult());
    OmniPointer<NameResult> name_field = std::shared_ptr<NameResult>(new NameResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&name_parser_instance->ParseSingleSave(index,name_field)&&name_tail_parser_instance->ParseOptionalSave(index,tail_field))
    {
        instance->SetTail(tail_field->GetValue());
        instance->SetName(name_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        tail_field = std::shared_ptr<NameTailResult>(new NameTailResult());
        name_field = std::shared_ptr<NameResult>(new NameResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool QualfiedNameParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<QualfiedNameResult> result = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
    return this->ParseSingleSave(index,result);
}

bool QualfiedNameParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<QualfiedNameResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool QualfiedNameParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<QualfiedNameResult> result = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
    return this->ParseOptionalSave(index,result);
}

bool QualfiedNameParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<QualfiedNameListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<QualfiedName>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<QualfiedNameResult> result = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool QualfiedNameParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<QualfiedNameListResult> result = std::shared_ptr<QualfiedNameListResult>(new QualfiedNameListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

QualfiedNameResult::QualfiedNameResult()
{
    this->value = NULL;
    this->result = false;
}

void QualfiedNameResult::SetValue(OmniPointer<QualfiedName> new_value)
{
    this->value = new_value;
}

OmniPointer<QualfiedName> QualfiedNameResult::GetValue()
{
    return this->value;
}

void QualfiedNameResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool QualfiedNameResult::GetResult()
{
    return this->result;
}

QualfiedNameListResult::QualfiedNameListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void QualfiedNameListResult::SetValue(std::vector<OmniPointer<QualfiedName>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<QualfiedName>> QualfiedNameListResult::GetValue()
{
    return this->value;
}

void QualfiedNameListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool QualfiedNameListResult::GetResult()
{
    return this->result;
}

QualfiedName::QualfiedName()
{
    this->length_string = NULL;
    this->tail_field = NULL;
    this->name_field = NULL;
}

void QualfiedName::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string QualfiedName::UnParse()
{
    return this->length_string->GetString();
}

void QualfiedName::SetTail(OmniPointer<NameTail> input_value)
{
    this->tail_field = input_value;
}

OmniPointer<NameTail> QualfiedName::GetTail()
{
    return this->tail_field;
}

void QualfiedName::SetName(OmniPointer<Name> input_value)
{
    this->name_field = input_value;
}

OmniPointer<Name> QualfiedName::GetName()
{
    return this->name_field;
}

NameTailParser::NameTailParser()
{
    this->parser_network = NULL;
}

void NameTailParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool NameTailParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<NameTailResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<NameTail> instance = std::shared_ptr<NameTail>(new NameTail());
    OmniPointer<NameTailResult> tail_field = std::shared_ptr<NameTailResult>(new NameTailResult());
    OmniPointer<NameResult> name_field = std::shared_ptr<NameResult>(new NameResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&string_parser_instance->ParseSingle(index,std::string("."))&&name_parser_instance->ParseSingleSave(index,name_field)&&name_tail_parser_instance->ParseOptionalSave(index,tail_field))
    {
        instance->SetTail(tail_field->GetValue());
        instance->SetName(name_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        tail_field = std::shared_ptr<NameTailResult>(new NameTailResult());
        name_field = std::shared_ptr<NameResult>(new NameResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool NameTailParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<NameTailResult> result = std::shared_ptr<NameTailResult>(new NameTailResult());
    return this->ParseSingleSave(index,result);
}

bool NameTailParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<NameTailResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool NameTailParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<NameTailResult> result = std::shared_ptr<NameTailResult>(new NameTailResult());
    return this->ParseOptionalSave(index,result);
}

bool NameTailParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<NameTailListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<NameTail>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<NameTailResult> result = std::shared_ptr<NameTailResult>(new NameTailResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool NameTailParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<NameTailListResult> result = std::shared_ptr<NameTailListResult>(new NameTailListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

NameTailResult::NameTailResult()
{
    this->value = NULL;
    this->result = false;
}

void NameTailResult::SetValue(OmniPointer<NameTail> new_value)
{
    this->value = new_value;
}

OmniPointer<NameTail> NameTailResult::GetValue()
{
    return this->value;
}

void NameTailResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool NameTailResult::GetResult()
{
    return this->result;
}

NameTailListResult::NameTailListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void NameTailListResult::SetValue(std::vector<OmniPointer<NameTail>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<NameTail>> NameTailListResult::GetValue()
{
    return this->value;
}

void NameTailListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool NameTailListResult::GetResult()
{
    return this->result;
}

NameTail::NameTail()
{
    this->length_string = NULL;
    this->tail_field = NULL;
    this->name_field = NULL;
}

void NameTail::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string NameTail::UnParse()
{
    return this->length_string->GetString();
}

void NameTail::SetTail(OmniPointer<NameTail> input_value)
{
    this->tail_field = input_value;
}

OmniPointer<NameTail> NameTail::GetTail()
{
    return this->tail_field;
}

void NameTail::SetName(OmniPointer<Name> input_value)
{
    this->name_field = input_value;
}

OmniPointer<Name> NameTail::GetName()
{
    return this->name_field;
}

NameParser::NameParser()
{
    this->parser_network = NULL;
}

void NameParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool NameParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<NameResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<Name> instance = std::shared_ptr<Name>(new Name());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&name_character_parser_instance->ParseMany(index,1,-1))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    result->SetResult(false);
    return result->GetResult();
}

bool NameParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<NameResult> result = std::shared_ptr<NameResult>(new NameResult());
    return this->ParseSingleSave(index,result);
}

bool NameParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<NameResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool NameParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<NameResult> result = std::shared_ptr<NameResult>(new NameResult());
    return this->ParseOptionalSave(index,result);
}

bool NameParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<NameListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<Name>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<NameResult> result = std::shared_ptr<NameResult>(new NameResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool NameParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<NameListResult> result = std::shared_ptr<NameListResult>(new NameListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

NameResult::NameResult()
{
    this->value = NULL;
    this->result = false;
}

void NameResult::SetValue(OmniPointer<Name> new_value)
{
    this->value = new_value;
}

OmniPointer<Name> NameResult::GetValue()
{
    return this->value;
}

void NameResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool NameResult::GetResult()
{
    return this->result;
}

NameListResult::NameListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void NameListResult::SetValue(std::vector<OmniPointer<Name>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<Name>> NameListResult::GetValue()
{
    return this->value;
}

void NameListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool NameListResult::GetResult()
{
    return this->result;
}

Name::Name()
{
    this->length_string = NULL;
}

void Name::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string Name::UnParse()
{
    return this->length_string->GetString();
}

NameCharacterParser::NameCharacterParser()
{
    this->parser_network = NULL;
}

void NameCharacterParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool NameCharacterParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<NameCharacterResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<NameCharacter> instance = std::shared_ptr<NameCharacter>(new NameCharacter());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&character_range_parser_instance->ParseSingle(index,0x30,0x39))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    if (true&&character_range_parser_instance->ParseSingle(index,0x41,0x5A))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    if (true&&string_parser_instance->ParseSingle(index,std::string("_")))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    if (true&&character_range_parser_instance->ParseSingle(index,0x61,0x7A))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    result->SetResult(false);
    return result->GetResult();
}

bool NameCharacterParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<NameCharacterResult> result = std::shared_ptr<NameCharacterResult>(new NameCharacterResult());
    return this->ParseSingleSave(index,result);
}

bool NameCharacterParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<NameCharacterResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool NameCharacterParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<NameCharacterResult> result = std::shared_ptr<NameCharacterResult>(new NameCharacterResult());
    return this->ParseOptionalSave(index,result);
}

bool NameCharacterParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<NameCharacterListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<NameCharacter>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<NameCharacterResult> result = std::shared_ptr<NameCharacterResult>(new NameCharacterResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool NameCharacterParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<NameCharacterListResult> result = std::shared_ptr<NameCharacterListResult>(new NameCharacterListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

NameCharacterResult::NameCharacterResult()
{
    this->value = NULL;
    this->result = false;
}

void NameCharacterResult::SetValue(OmniPointer<NameCharacter> new_value)
{
    this->value = new_value;
}

OmniPointer<NameCharacter> NameCharacterResult::GetValue()
{
    return this->value;
}

void NameCharacterResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool NameCharacterResult::GetResult()
{
    return this->result;
}

NameCharacterListResult::NameCharacterListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void NameCharacterListResult::SetValue(std::vector<OmniPointer<NameCharacter>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<NameCharacter>> NameCharacterListResult::GetValue()
{
    return this->value;
}

void NameCharacterListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool NameCharacterListResult::GetResult()
{
    return this->result;
}

NameCharacter::NameCharacter()
{
    this->length_string = NULL;
}

void NameCharacter::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string NameCharacter::UnParse()
{
    return this->length_string->GetString();
}

BooleanParser::BooleanParser()
{
    this->parser_network = NULL;
}

void BooleanParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool BooleanParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<BooleanResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<Boolean> instance = std::shared_ptr<Boolean>(new Boolean());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&string_parser_instance->ParseSingle(index,std::string("true")))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    if (true&&string_parser_instance->ParseSingle(index,std::string("false")))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    result->SetResult(false);
    return result->GetResult();
}

bool BooleanParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<BooleanResult> result = std::shared_ptr<BooleanResult>(new BooleanResult());
    return this->ParseSingleSave(index,result);
}

bool BooleanParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<BooleanResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool BooleanParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<BooleanResult> result = std::shared_ptr<BooleanResult>(new BooleanResult());
    return this->ParseOptionalSave(index,result);
}

bool BooleanParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<BooleanListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<Boolean>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<BooleanResult> result = std::shared_ptr<BooleanResult>(new BooleanResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool BooleanParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<BooleanListResult> result = std::shared_ptr<BooleanListResult>(new BooleanListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

BooleanResult::BooleanResult()
{
    this->value = NULL;
    this->result = false;
}

void BooleanResult::SetValue(OmniPointer<Boolean> new_value)
{
    this->value = new_value;
}

OmniPointer<Boolean> BooleanResult::GetValue()
{
    return this->value;
}

void BooleanResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool BooleanResult::GetResult()
{
    return this->result;
}

BooleanListResult::BooleanListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void BooleanListResult::SetValue(std::vector<OmniPointer<Boolean>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<Boolean>> BooleanListResult::GetValue()
{
    return this->value;
}

void BooleanListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool BooleanListResult::GetResult()
{
    return this->result;
}

Boolean::Boolean()
{
    this->length_string = NULL;
}

void Boolean::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string Boolean::UnParse()
{
    return this->length_string->GetString();
}

ByteParser::ByteParser()
{
    this->parser_network = NULL;
}

void ByteParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool ByteParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<ByteResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<Byte> instance = std::shared_ptr<Byte>(new Byte());
    OmniPointer<ByteDigitResult> low_field = std::shared_ptr<ByteDigitResult>(new ByteDigitResult());
    OmniPointer<ByteDigitResult> high_field = std::shared_ptr<ByteDigitResult>(new ByteDigitResult());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&string_parser_instance->ParseSingle(index,std::string("0x"))&&byte_digit_parser_instance->ParseSingleSave(index,high_field)&&byte_digit_parser_instance->ParseSingleSave(index,low_field))
    {
        instance->SetLow(low_field->GetValue());
        instance->SetHigh(high_field->GetValue());
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        low_field = std::shared_ptr<ByteDigitResult>(new ByteDigitResult());
        high_field = std::shared_ptr<ByteDigitResult>(new ByteDigitResult());
    }
    result->SetResult(false);
    return result->GetResult();
}

bool ByteParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<ByteResult> result = std::shared_ptr<ByteResult>(new ByteResult());
    return this->ParseSingleSave(index,result);
}

bool ByteParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ByteResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool ByteParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<ByteResult> result = std::shared_ptr<ByteResult>(new ByteResult());
    return this->ParseOptionalSave(index,result);
}

bool ByteParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<ByteListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<Byte>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<ByteResult> result = std::shared_ptr<ByteResult>(new ByteResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool ByteParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<ByteListResult> result = std::shared_ptr<ByteListResult>(new ByteListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

ByteResult::ByteResult()
{
    this->value = NULL;
    this->result = false;
}

void ByteResult::SetValue(OmniPointer<Byte> new_value)
{
    this->value = new_value;
}

OmniPointer<Byte> ByteResult::GetValue()
{
    return this->value;
}

void ByteResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool ByteResult::GetResult()
{
    return this->result;
}

ByteListResult::ByteListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void ByteListResult::SetValue(std::vector<OmniPointer<Byte>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<Byte>> ByteListResult::GetValue()
{
    return this->value;
}

void ByteListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool ByteListResult::GetResult()
{
    return this->result;
}

Byte::Byte()
{
    this->length_string = NULL;
    this->low_field = NULL;
    this->high_field = NULL;
}

void Byte::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string Byte::UnParse()
{
    return this->length_string->GetString();
}

void Byte::SetLow(OmniPointer<ByteDigit> input_value)
{
    this->low_field = input_value;
}

OmniPointer<ByteDigit> Byte::GetLow()
{
    return this->low_field;
}

void Byte::SetHigh(OmniPointer<ByteDigit> input_value)
{
    this->high_field = input_value;
}

OmniPointer<ByteDigit> Byte::GetHigh()
{
    return this->high_field;
}

ByteDigitParser::ByteDigitParser()
{
    this->parser_network = NULL;
}

void ByteDigitParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool ByteDigitParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<ByteDigitResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<ByteDigit> instance = std::shared_ptr<ByteDigit>(new ByteDigit());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&character_range_parser_instance->ParseSingle(index,0x30,0x39))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    if (true&&character_range_parser_instance->ParseSingle(index,0x41,0x46))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    result->SetResult(false);
    return result->GetResult();
}

bool ByteDigitParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<ByteDigitResult> result = std::shared_ptr<ByteDigitResult>(new ByteDigitResult());
    return this->ParseSingleSave(index,result);
}

bool ByteDigitParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ByteDigitResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool ByteDigitParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<ByteDigitResult> result = std::shared_ptr<ByteDigitResult>(new ByteDigitResult());
    return this->ParseOptionalSave(index,result);
}

bool ByteDigitParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<ByteDigitListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<ByteDigit>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<ByteDigitResult> result = std::shared_ptr<ByteDigitResult>(new ByteDigitResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool ByteDigitParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<ByteDigitListResult> result = std::shared_ptr<ByteDigitListResult>(new ByteDigitListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

ByteDigitResult::ByteDigitResult()
{
    this->value = NULL;
    this->result = false;
}

void ByteDigitResult::SetValue(OmniPointer<ByteDigit> new_value)
{
    this->value = new_value;
}

OmniPointer<ByteDigit> ByteDigitResult::GetValue()
{
    return this->value;
}

void ByteDigitResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool ByteDigitResult::GetResult()
{
    return this->result;
}

ByteDigitListResult::ByteDigitListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void ByteDigitListResult::SetValue(std::vector<OmniPointer<ByteDigit>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<ByteDigit>> ByteDigitListResult::GetValue()
{
    return this->value;
}

void ByteDigitListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool ByteDigitListResult::GetResult()
{
    return this->result;
}

ByteDigit::ByteDigit()
{
    this->length_string = NULL;
}

void ByteDigit::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string ByteDigit::UnParse()
{
    return this->length_string->GetString();
}

NegativeParser::NegativeParser()
{
    this->parser_network = NULL;
}

void NegativeParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool NegativeParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<NegativeResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<Negative> instance = std::shared_ptr<Negative>(new Negative());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&string_parser_instance->ParseSingle(index,std::string("-")))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    result->SetResult(false);
    return result->GetResult();
}

bool NegativeParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<NegativeResult> result = std::shared_ptr<NegativeResult>(new NegativeResult());
    return this->ParseSingleSave(index,result);
}

bool NegativeParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<NegativeResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool NegativeParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<NegativeResult> result = std::shared_ptr<NegativeResult>(new NegativeResult());
    return this->ParseOptionalSave(index,result);
}

bool NegativeParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<NegativeListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<Negative>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<NegativeResult> result = std::shared_ptr<NegativeResult>(new NegativeResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool NegativeParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<NegativeListResult> result = std::shared_ptr<NegativeListResult>(new NegativeListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

NegativeResult::NegativeResult()
{
    this->value = NULL;
    this->result = false;
}

void NegativeResult::SetValue(OmniPointer<Negative> new_value)
{
    this->value = new_value;
}

OmniPointer<Negative> NegativeResult::GetValue()
{
    return this->value;
}

void NegativeResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool NegativeResult::GetResult()
{
    return this->result;
}

NegativeListResult::NegativeListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void NegativeListResult::SetValue(std::vector<OmniPointer<Negative>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<Negative>> NegativeListResult::GetValue()
{
    return this->value;
}

void NegativeListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool NegativeListResult::GetResult()
{
    return this->result;
}

Negative::Negative()
{
    this->length_string = NULL;
}

void Negative::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string Negative::UnParse()
{
    return this->length_string->GetString();
}

DecimalParser::DecimalParser()
{
    this->parser_network = NULL;
}

void DecimalParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool DecimalParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<DecimalResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<Decimal> instance = std::shared_ptr<Decimal>(new Decimal());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&negative_parser_instance->ParseOptional(index)&&number_parser_instance->ParseSingle(index)&&string_parser_instance->ParseSingle(index,std::string("."))&&number_parser_instance->ParseSingle(index))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    result->SetResult(false);
    return result->GetResult();
}

bool DecimalParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<DecimalResult> result = std::shared_ptr<DecimalResult>(new DecimalResult());
    return this->ParseSingleSave(index,result);
}

bool DecimalParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<DecimalResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool DecimalParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<DecimalResult> result = std::shared_ptr<DecimalResult>(new DecimalResult());
    return this->ParseOptionalSave(index,result);
}

bool DecimalParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<DecimalListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<Decimal>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<DecimalResult> result = std::shared_ptr<DecimalResult>(new DecimalResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool DecimalParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<DecimalListResult> result = std::shared_ptr<DecimalListResult>(new DecimalListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

DecimalResult::DecimalResult()
{
    this->value = NULL;
    this->result = false;
}

void DecimalResult::SetValue(OmniPointer<Decimal> new_value)
{
    this->value = new_value;
}

OmniPointer<Decimal> DecimalResult::GetValue()
{
    return this->value;
}

void DecimalResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool DecimalResult::GetResult()
{
    return this->result;
}

DecimalListResult::DecimalListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void DecimalListResult::SetValue(std::vector<OmniPointer<Decimal>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<Decimal>> DecimalListResult::GetValue()
{
    return this->value;
}

void DecimalListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool DecimalListResult::GetResult()
{
    return this->result;
}

Decimal::Decimal()
{
    this->length_string = NULL;
}

void Decimal::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string Decimal::UnParse()
{
    return this->length_string->GetString();
}

NumberParser::NumberParser()
{
    this->parser_network = NULL;
}

void NumberParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool NumberParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<NumberResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<Number> instance = std::shared_ptr<Number>(new Number());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&negative_parser_instance->ParseOptional(index)&&digit_parser_instance->ParseMany(index,1,-1))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    result->SetResult(false);
    return result->GetResult();
}

bool NumberParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<NumberResult> result = std::shared_ptr<NumberResult>(new NumberResult());
    return this->ParseSingleSave(index,result);
}

bool NumberParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<NumberResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool NumberParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<NumberResult> result = std::shared_ptr<NumberResult>(new NumberResult());
    return this->ParseOptionalSave(index,result);
}

bool NumberParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<NumberListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<Number>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<NumberResult> result = std::shared_ptr<NumberResult>(new NumberResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool NumberParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<NumberListResult> result = std::shared_ptr<NumberListResult>(new NumberListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

NumberResult::NumberResult()
{
    this->value = NULL;
    this->result = false;
}

void NumberResult::SetValue(OmniPointer<Number> new_value)
{
    this->value = new_value;
}

OmniPointer<Number> NumberResult::GetValue()
{
    return this->value;
}

void NumberResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool NumberResult::GetResult()
{
    return this->result;
}

NumberListResult::NumberListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void NumberListResult::SetValue(std::vector<OmniPointer<Number>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<Number>> NumberListResult::GetValue()
{
    return this->value;
}

void NumberListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool NumberListResult::GetResult()
{
    return this->result;
}

Number::Number()
{
    this->length_string = NULL;
}

void Number::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string Number::UnParse()
{
    return this->length_string->GetString();
}

DigitParser::DigitParser()
{
    this->parser_network = NULL;
}

void DigitParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool DigitParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<DigitResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<Digit> instance = std::shared_ptr<Digit>(new Digit());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&character_range_parser_instance->ParseSingle(index,0x30,0x39))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    result->SetResult(false);
    return result->GetResult();
}

bool DigitParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<DigitResult> result = std::shared_ptr<DigitResult>(new DigitResult());
    return this->ParseSingleSave(index,result);
}

bool DigitParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<DigitResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool DigitParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<DigitResult> result = std::shared_ptr<DigitResult>(new DigitResult());
    return this->ParseOptionalSave(index,result);
}

bool DigitParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<DigitListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<Digit>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<DigitResult> result = std::shared_ptr<DigitResult>(new DigitResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool DigitParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<DigitListResult> result = std::shared_ptr<DigitListResult>(new DigitListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

DigitResult::DigitResult()
{
    this->value = NULL;
    this->result = false;
}

void DigitResult::SetValue(OmniPointer<Digit> new_value)
{
    this->value = new_value;
}

OmniPointer<Digit> DigitResult::GetValue()
{
    return this->value;
}

void DigitResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool DigitResult::GetResult()
{
    return this->result;
}

DigitListResult::DigitListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void DigitListResult::SetValue(std::vector<OmniPointer<Digit>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<Digit>> DigitListResult::GetValue()
{
    return this->value;
}

void DigitListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool DigitListResult::GetResult()
{
    return this->result;
}

Digit::Digit()
{
    this->length_string = NULL;
}

void Digit::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string Digit::UnParse()
{
    return this->length_string->GetString();
}

LiteralParser::LiteralParser()
{
    this->parser_network = NULL;
}

void LiteralParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool LiteralParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<LiteralResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<Literal> instance = std::shared_ptr<Literal>(new Literal());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&literal_character_parser_instance->ParseMany(index,0,-1))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    result->SetResult(false);
    return result->GetResult();
}

bool LiteralParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<LiteralResult> result = std::shared_ptr<LiteralResult>(new LiteralResult());
    return this->ParseSingleSave(index,result);
}

bool LiteralParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<LiteralResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool LiteralParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<LiteralResult> result = std::shared_ptr<LiteralResult>(new LiteralResult());
    return this->ParseOptionalSave(index,result);
}

bool LiteralParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<LiteralListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<Literal>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<LiteralResult> result = std::shared_ptr<LiteralResult>(new LiteralResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool LiteralParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<LiteralListResult> result = std::shared_ptr<LiteralListResult>(new LiteralListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

LiteralResult::LiteralResult()
{
    this->value = NULL;
    this->result = false;
}

void LiteralResult::SetValue(OmniPointer<Literal> new_value)
{
    this->value = new_value;
}

OmniPointer<Literal> LiteralResult::GetValue()
{
    return this->value;
}

void LiteralResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool LiteralResult::GetResult()
{
    return this->result;
}

LiteralListResult::LiteralListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void LiteralListResult::SetValue(std::vector<OmniPointer<Literal>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<Literal>> LiteralListResult::GetValue()
{
    return this->value;
}

void LiteralListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool LiteralListResult::GetResult()
{
    return this->result;
}

Literal::Literal()
{
    this->length_string = NULL;
}

void Literal::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string Literal::UnParse()
{
    return this->length_string->GetString();
}

LiteralCharacterParser::LiteralCharacterParser()
{
    this->parser_network = NULL;
}

void LiteralCharacterParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool LiteralCharacterParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<LiteralCharacterResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<LiteralCharacter> instance = std::shared_ptr<LiteralCharacter>(new LiteralCharacter());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&character_range_parser_instance->ParseSingle(index,0x00,0x21))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    if (true&&string_parser_instance->ParseSingle(index,std::string("\\\"")))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    if (true&&character_range_parser_instance->ParseSingle(index,0x23,0x5B))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    if (true&&string_parser_instance->ParseSingle(index,std::string("\\\\")))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    if (true&&character_range_parser_instance->ParseSingle(index,0x5D,0xFF))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    result->SetResult(false);
    return result->GetResult();
}

bool LiteralCharacterParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<LiteralCharacterResult> result = std::shared_ptr<LiteralCharacterResult>(new LiteralCharacterResult());
    return this->ParseSingleSave(index,result);
}

bool LiteralCharacterParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<LiteralCharacterResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool LiteralCharacterParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<LiteralCharacterResult> result = std::shared_ptr<LiteralCharacterResult>(new LiteralCharacterResult());
    return this->ParseOptionalSave(index,result);
}

bool LiteralCharacterParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<LiteralCharacterListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<LiteralCharacter>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<LiteralCharacterResult> result = std::shared_ptr<LiteralCharacterResult>(new LiteralCharacterResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool LiteralCharacterParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<LiteralCharacterListResult> result = std::shared_ptr<LiteralCharacterListResult>(new LiteralCharacterListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

LiteralCharacterResult::LiteralCharacterResult()
{
    this->value = NULL;
    this->result = false;
}

void LiteralCharacterResult::SetValue(OmniPointer<LiteralCharacter> new_value)
{
    this->value = new_value;
}

OmniPointer<LiteralCharacter> LiteralCharacterResult::GetValue()
{
    return this->value;
}

void LiteralCharacterResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool LiteralCharacterResult::GetResult()
{
    return this->result;
}

LiteralCharacterListResult::LiteralCharacterListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void LiteralCharacterListResult::SetValue(std::vector<OmniPointer<LiteralCharacter>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<LiteralCharacter>> LiteralCharacterListResult::GetValue()
{
    return this->value;
}

void LiteralCharacterListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool LiteralCharacterListResult::GetResult()
{
    return this->result;
}

LiteralCharacter::LiteralCharacter()
{
    this->length_string = NULL;
}

void LiteralCharacter::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string LiteralCharacter::UnParse()
{
    return this->length_string->GetString();
}

WhitespaceParser::WhitespaceParser()
{
    this->parser_network = NULL;
}

void WhitespaceParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
{
    this->parser_network = input;
}

bool WhitespaceParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<WhitespaceResult> result)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
    consumed_string->SetData(index->GetData());
    consumed_string->SetStart(index->GetStart());
    consumed_string->SetLength(0);
    OmniPointer<Whitespace> instance = std::shared_ptr<Whitespace>(new Whitespace());
    OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = this->parser_network->GetCTCodeFileParser();
    OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = this->parser_network->GetExternalDefinitionParser();
    OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = this->parser_network->GetUnmanagedTypeParser();
    OmniPointer<DefinitionParser> definition_parser_instance = this->parser_network->GetDefinitionParser();
    OmniPointer<InterfaceDefParser> interface_def_parser_instance = this->parser_network->GetInterfaceDefParser();
    OmniPointer<ClassDefParser> class_def_parser_instance = this->parser_network->GetClassDefParser();
    OmniPointer<ImplementationSpecParser> implementation_spec_parser_instance = this->parser_network->GetImplementationSpecParser();
    OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = this->parser_network->GetContentDeclarationParser();
    OmniPointer<ContentDefinitionParser> content_definition_parser_instance = this->parser_network->GetContentDefinitionParser();
    OmniPointer<PrimativeTypeParser> primative_type_parser_instance = this->parser_network->GetPrimativeTypeParser();
    OmniPointer<DefinedTypeParser> defined_type_parser_instance = this->parser_network->GetDefinedTypeParser();
    OmniPointer<SingletonTypeParser> singleton_type_parser_instance = this->parser_network->GetSingletonTypeParser();
    OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = this->parser_network->GetDimensionalNoteParser();
    OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = this->parser_network->GetDimensionalTypeParser();
    OmniPointer<MapNoteParser> map_note_parser_instance = this->parser_network->GetMapNoteParser();
    OmniPointer<MapTypeParser> map_type_parser_instance = this->parser_network->GetMapTypeParser();
    OmniPointer<ValueTypeParser> value_type_parser_instance = this->parser_network->GetValueTypeParser();
    OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = this->parser_network->GetParameterListDefParser();
    OmniPointer<ParameterListParser> parameter_list_parser_instance = this->parser_network->GetParameterListParser();
    OmniPointer<CodeBlockParser> code_block_parser_instance = this->parser_network->GetCodeBlockParser();
    OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = this->parser_network->GetDeclarationAssignParser();
    OmniPointer<DeclarationParser> declaration_parser_instance = this->parser_network->GetDeclarationParser();
    OmniPointer<AssignmentParser> assignment_parser_instance = this->parser_network->GetAssignmentParser();
    OmniPointer<ReturnParser> return_parser_instance = this->parser_network->GetReturnParser();
    OmniPointer<ElseTailParser> else_tail_parser_instance = this->parser_network->GetElseTailParser();
    OmniPointer<ConditionalParser> conditional_parser_instance = this->parser_network->GetConditionalParser();
    OmniPointer<LoopParser> loop_parser_instance = this->parser_network->GetLoopParser();
    OmniPointer<CallParser> call_parser_instance = this->parser_network->GetCallParser();
    OmniPointer<AllocateParser> allocate_parser_instance = this->parser_network->GetAllocateParser();
    OmniPointer<InstructionParser> instruction_parser_instance = this->parser_network->GetInstructionParser();
    OmniPointer<RValueSingleParser> r_value_single_parser_instance = this->parser_network->GetRValueSingleParser();
    OmniPointer<RValueTailParser> r_value_tail_parser_instance = this->parser_network->GetRValueTailParser();
    OmniPointer<RValueParser> r_value_parser_instance = this->parser_network->GetRValueParser();
    OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = this->parser_network->GetBinaryOperatorParser();
    OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = this->parser_network->GetUnaryOperatorParser();
    OmniPointer<CommentParser> comment_parser_instance = this->parser_network->GetCommentParser();
    OmniPointer<NonStarCharacterParser> non_star_character_parser_instance = this->parser_network->GetNonStarCharacterParser();
    OmniPointer<NonSlashCharacterParser> non_slash_character_parser_instance = this->parser_network->GetNonSlashCharacterParser();
    OmniPointer<CommentContentParser> comment_content_parser_instance = this->parser_network->GetCommentContentParser();
    OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = this->parser_network->GetQualfiedNameParser();
    OmniPointer<NameTailParser> name_tail_parser_instance = this->parser_network->GetNameTailParser();
    OmniPointer<NameParser> name_parser_instance = this->parser_network->GetNameParser();
    OmniPointer<NameCharacterParser> name_character_parser_instance = this->parser_network->GetNameCharacterParser();
    OmniPointer<BooleanParser> boolean_parser_instance = this->parser_network->GetBooleanParser();
    OmniPointer<ByteParser> byte_parser_instance = this->parser_network->GetByteParser();
    OmniPointer<ByteDigitParser> byte_digit_parser_instance = this->parser_network->GetByteDigitParser();
    OmniPointer<NegativeParser> negative_parser_instance = this->parser_network->GetNegativeParser();
    OmniPointer<DecimalParser> decimal_parser_instance = this->parser_network->GetDecimalParser();
    OmniPointer<NumberParser> number_parser_instance = this->parser_network->GetNumberParser();
    OmniPointer<DigitParser> digit_parser_instance = this->parser_network->GetDigitParser();
    OmniPointer<LiteralParser> literal_parser_instance = this->parser_network->GetLiteralParser();
    OmniPointer<LiteralCharacterParser> literal_character_parser_instance = this->parser_network->GetLiteralCharacterParser();
    OmniPointer<WhitespaceParser> whitespace_parser_instance = this->parser_network->GetWhitespaceParser();
    OmniPointer<StringParser> string_parser_instance = this->parser_network->GetStringParser();
    OmniPointer<CharacterParser> character_parser_instance = this->parser_network->GetCharacterParser();
    OmniPointer<CharacterRangeParser> character_range_parser_instance = this->parser_network->GetCharacterRangeParser();
    if (true&&character_range_parser_instance->ParseSingle(index,0x00,0x20))
    {
        consumed_string->SetLength(index->GetStart()-index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return result->GetResult();
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
    }
    result->SetResult(false);
    return result->GetResult();
}

bool WhitespaceParser::ParseSingle(OmniPointer<LengthString> index)
{
    OmniPointer<WhitespaceResult> result = std::shared_ptr<WhitespaceResult>(new WhitespaceResult());
    return this->ParseSingleSave(index,result);
}

bool WhitespaceParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<WhitespaceResult> result)
{
    this->ParseSingleSave(index,result);
    result->SetResult(true);
    return true;
}

bool WhitespaceParser::ParseOptional(OmniPointer<LengthString> index)
{
    OmniPointer<WhitespaceResult> result = std::shared_ptr<WhitespaceResult>(new WhitespaceResult());
    return this->ParseOptionalSave(index,result);
}

bool WhitespaceParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<WhitespaceListResult> list_result, int minimum, int maximum)
{
    int index_start = index->GetStart();
    int index_length = index->GetLength();
    std::vector<OmniPointer<Whitespace>> results;
    int count = 0;
    int max_check = maximum;
    bool check_next = true;
    if (maximum<0)
    {
        max_check = count+1;
    }
    while (check_next&&count<max_check)
    {
        OmniPointer<WhitespaceResult> result = std::shared_ptr<WhitespaceResult>(new WhitespaceResult());
        this->ParseSingleSave(index,result);
        check_next = result->GetResult();
        if (result->GetResult())
        {
            count = count+1;
            Append(results,result->GetValue());
        }
        if (maximum<0)
        {
            max_check = count+1;
        }
    }
    if (count>=minimum&&count<=max_check)
    {
        list_result->SetValue(results);
        list_result->SetResult(true);
    }
    else
    {
        index->SetStart(index_start);
        index->SetLength(index_length);
        list_result->SetResult(false);
    }
    return list_result->GetResult();
}

bool WhitespaceParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
{
    OmniPointer<WhitespaceListResult> result = std::shared_ptr<WhitespaceListResult>(new WhitespaceListResult());
    return this->ParseManySave(index,result,minimum,maximum);
}

WhitespaceResult::WhitespaceResult()
{
    this->value = NULL;
    this->result = false;
}

void WhitespaceResult::SetValue(OmniPointer<Whitespace> new_value)
{
    this->value = new_value;
}

OmniPointer<Whitespace> WhitespaceResult::GetValue()
{
    return this->value;
}

void WhitespaceResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool WhitespaceResult::GetResult()
{
    return this->result;
}

WhitespaceListResult::WhitespaceListResult()
{
    /*this->value = NO_DEFAULT;*/
    this->result = false;
}

void WhitespaceListResult::SetValue(std::vector<OmniPointer<Whitespace>> new_value)
{
    this->value = new_value;
}

std::vector<OmniPointer<Whitespace>> WhitespaceListResult::GetValue()
{
    return this->value;
}

void WhitespaceListResult::SetResult(bool new_result)
{
    this->result = new_result;
}

bool WhitespaceListResult::GetResult()
{
    return this->result;
}

Whitespace::Whitespace()
{
    this->length_string = NULL;
}

void Whitespace::SetLengthString(OmniPointer<LengthString> new_value)
{
    this->length_string = std::shared_ptr<LengthString>(new LengthString());
    this->length_string->SetData(new_value->GetData());
    this->length_string->SetStart(new_value->GetStart());
    this->length_string->SetLength(new_value->GetLength());
}

std::string Whitespace::UnParse()
{
    return this->length_string->GetString();
}


};
};
};
};
