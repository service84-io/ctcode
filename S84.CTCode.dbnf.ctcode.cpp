#include "S84.CTCode.dbnf.ctcode.hpp"


namespace s84
{
namespace ctcode
{
namespace dbnf
{
namespace ctcode
{
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
        if (value_length > index->GetLength())
        {
            result->SetResult(false);
            return false;
        }

        int offset_index = 0;
        while (offset_index < value_length)
        {
            if (At(index_data->GetData(), index->GetStart() + offset_index) != At(value, offset_index))
            {
                result->SetResult(false);
                return false;
            }

            offset_index = offset_index + 1;
        }

        index->SetStart(index->GetStart() + value_length);
        index->SetLength(index->GetLength() - value_length);
        consumed_string->SetLength(index->GetStart() - index_start);
        instance->SetLengthString(consumed_string);
        result->SetValue(instance);
        result->SetResult(true);
        return true;
    }

    bool StringParser::ParseSingle(OmniPointer<LengthString> index, std::string value)
    {
        OmniPointer<StringResult> result = std::shared_ptr<StringResult>(new StringResult());
        return ParseSingleSave(index, value, result);
    }

    void StringResult::SetValue(OmniPointer<String> new_value)
    {
        value = new_value;
    }

    OmniPointer<String> StringResult::GetValue()
    {
        return value;
    }

    void StringResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool StringResult::GetResult()
    {
        return result;
    }

    void StringListResult::SetValue(std::vector<OmniPointer<String>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<String>> StringListResult::GetValue()
    {
        return value;
    }

    void StringListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool StringListResult::GetResult()
    {
        return result;
    }

    void String::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string String::UnParse()
    {
        return length_string->GetString();
    }

    bool CharacterParser::ParseSingle(OmniPointer<LengthString> index, int value)
    {
        if (0 == index->GetLength())
        {
            return false;
        }

        OmniPointer<LargeString> index_data = index->GetData();
        int current_character = IntAt(index_data->GetData(), index->GetStart());
        if (current_character == value)
        {
            index->SetStart(index->GetStart() + 1);
            index->SetLength(index->GetLength() - 1);
            return true;
        }

        return false;
    }

    void CharacterResult::SetValue(OmniPointer<Character> new_value)
    {
        value = new_value;
    }

    OmniPointer<Character> CharacterResult::GetValue()
    {
        return value;
    }

    void CharacterResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool CharacterResult::GetResult()
    {
        return result;
    }

    void CharacterListResult::SetValue(std::vector<OmniPointer<Character>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<Character>> CharacterListResult::GetValue()
    {
        return value;
    }

    void CharacterListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool CharacterListResult::GetResult()
    {
        return result;
    }

    void Character::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string Character::UnParse()
    {
        return length_string->GetString();
    }

    bool CharacterRangeParser::ParseSingle(OmniPointer<LengthString> index, int low_value, int high_value)
    {
        if (0 == index->GetLength())
        {
            return false;
        }

        OmniPointer<LargeString> index_data = index->GetData();
        int current_character = IntAt(index_data->GetData(), index->GetStart());
        if (low_value <= current_character && current_character <= high_value)
        {
            index->SetStart(index->GetStart() + 1);
            index->SetLength(index->GetLength() - 1);
            return true;
        }

        return false;
    }

    void CharacterRangeResult::SetValue(OmniPointer<CharacterRange> new_value)
    {
        value = new_value;
    }

    OmniPointer<CharacterRange> CharacterRangeResult::GetValue()
    {
        return value;
    }

    void CharacterRangeResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool CharacterRangeResult::GetResult()
    {
        return result;
    }

    void CharacterRangeListResult::SetValue(std::vector<OmniPointer<CharacterRange>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<CharacterRange>> CharacterRangeListResult::GetValue()
    {
        return value;
    }

    void CharacterRangeListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool CharacterRangeListResult::GetResult()
    {
        return result;
    }

    void CharacterRange::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string CharacterRange::UnParse()
    {
        return length_string->GetString();
    }

    OmniPointer<CTCodeFileParser> ParserNetwork::GetCTCodeFileParser()
    {
        return c_t_code_file_parser_field;
    }

    OmniPointer<ExternalDefinitionParser> ParserNetwork::GetExternalDefinitionParser()
    {
        return external_definition_parser_field;
    }

    OmniPointer<UnmanagedTypeParser> ParserNetwork::GetUnmanagedTypeParser()
    {
        return unmanaged_type_parser_field;
    }

    OmniPointer<DefinitionParser> ParserNetwork::GetDefinitionParser()
    {
        return definition_parser_field;
    }

    OmniPointer<InterfaceDefParser> ParserNetwork::GetInterfaceDefParser()
    {
        return interface_def_parser_field;
    }

    OmniPointer<ClassDefParser> ParserNetwork::GetClassDefParser()
    {
        return class_def_parser_field;
    }

    OmniPointer<ContentDeclarationParser> ParserNetwork::GetContentDeclarationParser()
    {
        return content_declaration_parser_field;
    }

    OmniPointer<ContentDefinitionParser> ParserNetwork::GetContentDefinitionParser()
    {
        return content_definition_parser_field;
    }

    OmniPointer<PrimativeTypeParser> ParserNetwork::GetPrimativeTypeParser()
    {
        return primative_type_parser_field;
    }

    OmniPointer<DefinedTypeParser> ParserNetwork::GetDefinedTypeParser()
    {
        return defined_type_parser_field;
    }

    OmniPointer<SingletonTypeParser> ParserNetwork::GetSingletonTypeParser()
    {
        return singleton_type_parser_field;
    }

    OmniPointer<DimensionalNoteParser> ParserNetwork::GetDimensionalNoteParser()
    {
        return dimensional_note_parser_field;
    }

    OmniPointer<DimensionalTypeParser> ParserNetwork::GetDimensionalTypeParser()
    {
        return dimensional_type_parser_field;
    }

    OmniPointer<MapNoteParser> ParserNetwork::GetMapNoteParser()
    {
        return map_note_parser_field;
    }

    OmniPointer<MapTypeParser> ParserNetwork::GetMapTypeParser()
    {
        return map_type_parser_field;
    }

    OmniPointer<ValueTypeParser> ParserNetwork::GetValueTypeParser()
    {
        return value_type_parser_field;
    }

    OmniPointer<ParameterListDefParser> ParserNetwork::GetParameterListDefParser()
    {
        return parameter_list_def_parser_field;
    }

    OmniPointer<ParameterListParser> ParserNetwork::GetParameterListParser()
    {
        return parameter_list_parser_field;
    }

    OmniPointer<CodeBlockParser> ParserNetwork::GetCodeBlockParser()
    {
        return code_block_parser_field;
    }

    OmniPointer<DeclarationAssignParser> ParserNetwork::GetDeclarationAssignParser()
    {
        return declaration_assign_parser_field;
    }

    OmniPointer<DeclarationParser> ParserNetwork::GetDeclarationParser()
    {
        return declaration_parser_field;
    }

    OmniPointer<AssignmentParser> ParserNetwork::GetAssignmentParser()
    {
        return assignment_parser_field;
    }

    OmniPointer<ReturnParser> ParserNetwork::GetReturnParser()
    {
        return return_parser_field;
    }

    OmniPointer<ElseTailParser> ParserNetwork::GetElseTailParser()
    {
        return else_tail_parser_field;
    }

    OmniPointer<ConditionalParser> ParserNetwork::GetConditionalParser()
    {
        return conditional_parser_field;
    }

    OmniPointer<LoopParser> ParserNetwork::GetLoopParser()
    {
        return loop_parser_field;
    }

    OmniPointer<CallParser> ParserNetwork::GetCallParser()
    {
        return call_parser_field;
    }

    OmniPointer<AllocateParser> ParserNetwork::GetAllocateParser()
    {
        return allocate_parser_field;
    }

    OmniPointer<InstructionParser> ParserNetwork::GetInstructionParser()
    {
        return instruction_parser_field;
    }

    OmniPointer<RValueSingleParser> ParserNetwork::GetRValueSingleParser()
    {
        return r_value_single_parser_field;
    }

    OmniPointer<RValueTailParser> ParserNetwork::GetRValueTailParser()
    {
        return r_value_tail_parser_field;
    }

    OmniPointer<RValueParser> ParserNetwork::GetRValueParser()
    {
        return r_value_parser_field;
    }

    OmniPointer<BinaryOperatorParser> ParserNetwork::GetBinaryOperatorParser()
    {
        return binary_operator_parser_field;
    }

    OmniPointer<UnaryOperatorParser> ParserNetwork::GetUnaryOperatorParser()
    {
        return unary_operator_parser_field;
    }

    OmniPointer<CommentParser> ParserNetwork::GetCommentParser()
    {
        return comment_parser_field;
    }

    OmniPointer<CommentCharacterParser> ParserNetwork::GetCommentCharacterParser()
    {
        return comment_character_parser_field;
    }

    OmniPointer<QualfiedNameParser> ParserNetwork::GetQualfiedNameParser()
    {
        return qualfied_name_parser_field;
    }

    OmniPointer<NameTailParser> ParserNetwork::GetNameTailParser()
    {
        return name_tail_parser_field;
    }

    OmniPointer<NameParser> ParserNetwork::GetNameParser()
    {
        return name_parser_field;
    }

    OmniPointer<NameCharacterParser> ParserNetwork::GetNameCharacterParser()
    {
        return name_character_parser_field;
    }

    OmniPointer<BooleanParser> ParserNetwork::GetBooleanParser()
    {
        return boolean_parser_field;
    }

    OmniPointer<ByteParser> ParserNetwork::GetByteParser()
    {
        return byte_parser_field;
    }

    OmniPointer<ByteDigitParser> ParserNetwork::GetByteDigitParser()
    {
        return byte_digit_parser_field;
    }

    OmniPointer<NegativeParser> ParserNetwork::GetNegativeParser()
    {
        return negative_parser_field;
    }

    OmniPointer<DecimalParser> ParserNetwork::GetDecimalParser()
    {
        return decimal_parser_field;
    }

    OmniPointer<NumberParser> ParserNetwork::GetNumberParser()
    {
        return number_parser_field;
    }

    OmniPointer<DigitParser> ParserNetwork::GetDigitParser()
    {
        return digit_parser_field;
    }

    OmniPointer<LiteralParser> ParserNetwork::GetLiteralParser()
    {
        return literal_parser_field;
    }

    OmniPointer<LiteralCharacterParser> ParserNetwork::GetLiteralCharacterParser()
    {
        return literal_character_parser_field;
    }

    OmniPointer<WhitespaceParser> ParserNetwork::GetWhitespaceParser()
    {
        return whitespace_parser_field;
    }

    OmniPointer<StringParser> ParserNetwork::GetStringParser()
    {
        return string_parser_field;
    }

    OmniPointer<CharacterParser> ParserNetwork::GetCharacterParser()
    {
        return character_parser_field;
    }

    OmniPointer<CharacterRangeParser> ParserNetwork::GetCharacterRangeParser()
    {
        return character_range_parser_field;
    }

    void ParserNetwork::Initialize()
    {
        c_t_code_file_parser_field = std::shared_ptr<CTCodeFileParser>(new CTCodeFileParser());
        c_t_code_file_parser_field->SetParserNetwork(this);
        external_definition_parser_field = std::shared_ptr<ExternalDefinitionParser>(new ExternalDefinitionParser());
        external_definition_parser_field->SetParserNetwork(this);
        unmanaged_type_parser_field = std::shared_ptr<UnmanagedTypeParser>(new UnmanagedTypeParser());
        unmanaged_type_parser_field->SetParserNetwork(this);
        definition_parser_field = std::shared_ptr<DefinitionParser>(new DefinitionParser());
        definition_parser_field->SetParserNetwork(this);
        interface_def_parser_field = std::shared_ptr<InterfaceDefParser>(new InterfaceDefParser());
        interface_def_parser_field->SetParserNetwork(this);
        class_def_parser_field = std::shared_ptr<ClassDefParser>(new ClassDefParser());
        class_def_parser_field->SetParserNetwork(this);
        content_declaration_parser_field = std::shared_ptr<ContentDeclarationParser>(new ContentDeclarationParser());
        content_declaration_parser_field->SetParserNetwork(this);
        content_definition_parser_field = std::shared_ptr<ContentDefinitionParser>(new ContentDefinitionParser());
        content_definition_parser_field->SetParserNetwork(this);
        primative_type_parser_field = std::shared_ptr<PrimativeTypeParser>(new PrimativeTypeParser());
        primative_type_parser_field->SetParserNetwork(this);
        defined_type_parser_field = std::shared_ptr<DefinedTypeParser>(new DefinedTypeParser());
        defined_type_parser_field->SetParserNetwork(this);
        singleton_type_parser_field = std::shared_ptr<SingletonTypeParser>(new SingletonTypeParser());
        singleton_type_parser_field->SetParserNetwork(this);
        dimensional_note_parser_field = std::shared_ptr<DimensionalNoteParser>(new DimensionalNoteParser());
        dimensional_note_parser_field->SetParserNetwork(this);
        dimensional_type_parser_field = std::shared_ptr<DimensionalTypeParser>(new DimensionalTypeParser());
        dimensional_type_parser_field->SetParserNetwork(this);
        map_note_parser_field = std::shared_ptr<MapNoteParser>(new MapNoteParser());
        map_note_parser_field->SetParserNetwork(this);
        map_type_parser_field = std::shared_ptr<MapTypeParser>(new MapTypeParser());
        map_type_parser_field->SetParserNetwork(this);
        value_type_parser_field = std::shared_ptr<ValueTypeParser>(new ValueTypeParser());
        value_type_parser_field->SetParserNetwork(this);
        parameter_list_def_parser_field = std::shared_ptr<ParameterListDefParser>(new ParameterListDefParser());
        parameter_list_def_parser_field->SetParserNetwork(this);
        parameter_list_parser_field = std::shared_ptr<ParameterListParser>(new ParameterListParser());
        parameter_list_parser_field->SetParserNetwork(this);
        code_block_parser_field = std::shared_ptr<CodeBlockParser>(new CodeBlockParser());
        code_block_parser_field->SetParserNetwork(this);
        declaration_assign_parser_field = std::shared_ptr<DeclarationAssignParser>(new DeclarationAssignParser());
        declaration_assign_parser_field->SetParserNetwork(this);
        declaration_parser_field = std::shared_ptr<DeclarationParser>(new DeclarationParser());
        declaration_parser_field->SetParserNetwork(this);
        assignment_parser_field = std::shared_ptr<AssignmentParser>(new AssignmentParser());
        assignment_parser_field->SetParserNetwork(this);
        return_parser_field = std::shared_ptr<ReturnParser>(new ReturnParser());
        return_parser_field->SetParserNetwork(this);
        else_tail_parser_field = std::shared_ptr<ElseTailParser>(new ElseTailParser());
        else_tail_parser_field->SetParserNetwork(this);
        conditional_parser_field = std::shared_ptr<ConditionalParser>(new ConditionalParser());
        conditional_parser_field->SetParserNetwork(this);
        loop_parser_field = std::shared_ptr<LoopParser>(new LoopParser());
        loop_parser_field->SetParserNetwork(this);
        call_parser_field = std::shared_ptr<CallParser>(new CallParser());
        call_parser_field->SetParserNetwork(this);
        allocate_parser_field = std::shared_ptr<AllocateParser>(new AllocateParser());
        allocate_parser_field->SetParserNetwork(this);
        instruction_parser_field = std::shared_ptr<InstructionParser>(new InstructionParser());
        instruction_parser_field->SetParserNetwork(this);
        r_value_single_parser_field = std::shared_ptr<RValueSingleParser>(new RValueSingleParser());
        r_value_single_parser_field->SetParserNetwork(this);
        r_value_tail_parser_field = std::shared_ptr<RValueTailParser>(new RValueTailParser());
        r_value_tail_parser_field->SetParserNetwork(this);
        r_value_parser_field = std::shared_ptr<RValueParser>(new RValueParser());
        r_value_parser_field->SetParserNetwork(this);
        binary_operator_parser_field = std::shared_ptr<BinaryOperatorParser>(new BinaryOperatorParser());
        binary_operator_parser_field->SetParserNetwork(this);
        unary_operator_parser_field = std::shared_ptr<UnaryOperatorParser>(new UnaryOperatorParser());
        unary_operator_parser_field->SetParserNetwork(this);
        comment_parser_field = std::shared_ptr<CommentParser>(new CommentParser());
        comment_parser_field->SetParserNetwork(this);
        comment_character_parser_field = std::shared_ptr<CommentCharacterParser>(new CommentCharacterParser());
        comment_character_parser_field->SetParserNetwork(this);
        qualfied_name_parser_field = std::shared_ptr<QualfiedNameParser>(new QualfiedNameParser());
        qualfied_name_parser_field->SetParserNetwork(this);
        name_tail_parser_field = std::shared_ptr<NameTailParser>(new NameTailParser());
        name_tail_parser_field->SetParserNetwork(this);
        name_parser_field = std::shared_ptr<NameParser>(new NameParser());
        name_parser_field->SetParserNetwork(this);
        name_character_parser_field = std::shared_ptr<NameCharacterParser>(new NameCharacterParser());
        name_character_parser_field->SetParserNetwork(this);
        boolean_parser_field = std::shared_ptr<BooleanParser>(new BooleanParser());
        boolean_parser_field->SetParserNetwork(this);
        byte_parser_field = std::shared_ptr<ByteParser>(new ByteParser());
        byte_parser_field->SetParserNetwork(this);
        byte_digit_parser_field = std::shared_ptr<ByteDigitParser>(new ByteDigitParser());
        byte_digit_parser_field->SetParserNetwork(this);
        negative_parser_field = std::shared_ptr<NegativeParser>(new NegativeParser());
        negative_parser_field->SetParserNetwork(this);
        decimal_parser_field = std::shared_ptr<DecimalParser>(new DecimalParser());
        decimal_parser_field->SetParserNetwork(this);
        number_parser_field = std::shared_ptr<NumberParser>(new NumberParser());
        number_parser_field->SetParserNetwork(this);
        digit_parser_field = std::shared_ptr<DigitParser>(new DigitParser());
        digit_parser_field->SetParserNetwork(this);
        literal_parser_field = std::shared_ptr<LiteralParser>(new LiteralParser());
        literal_parser_field->SetParserNetwork(this);
        literal_character_parser_field = std::shared_ptr<LiteralCharacterParser>(new LiteralCharacterParser());
        literal_character_parser_field->SetParserNetwork(this);
        whitespace_parser_field = std::shared_ptr<WhitespaceParser>(new WhitespaceParser());
        whitespace_parser_field->SetParserNetwork(this);
        string_parser_field = std::shared_ptr<StringParser>(new StringParser());
        character_parser_field = std::shared_ptr<CharacterParser>(new CharacterParser());
    }

    void DBNFOmniType::SetCTCodeFile(OmniPointer<CTCodeFile> input_value)
    {
        c_t_code_file_field = input_value;
    }

    OmniPointer<CTCodeFile> DBNFOmniType::GetCTCodeFile()
    {
        return c_t_code_file_field;
    }

    void DBNFOmniType::SetExternalDefinition(OmniPointer<ExternalDefinition> input_value)
    {
        external_definition_field = input_value;
    }

    OmniPointer<ExternalDefinition> DBNFOmniType::GetExternalDefinition()
    {
        return external_definition_field;
    }

    void DBNFOmniType::SetUnmanagedType(OmniPointer<UnmanagedType> input_value)
    {
        unmanaged_type_field = input_value;
    }

    OmniPointer<UnmanagedType> DBNFOmniType::GetUnmanagedType()
    {
        return unmanaged_type_field;
    }

    void DBNFOmniType::SetDefinition(OmniPointer<Definition> input_value)
    {
        definition_field = input_value;
    }

    OmniPointer<Definition> DBNFOmniType::GetDefinition()
    {
        return definition_field;
    }

    void DBNFOmniType::SetInterfaceDef(OmniPointer<InterfaceDef> input_value)
    {
        interface_def_field = input_value;
    }

    OmniPointer<InterfaceDef> DBNFOmniType::GetInterfaceDef()
    {
        return interface_def_field;
    }

    void DBNFOmniType::SetClassDef(OmniPointer<ClassDef> input_value)
    {
        class_def_field = input_value;
    }

    OmniPointer<ClassDef> DBNFOmniType::GetClassDef()
    {
        return class_def_field;
    }

    void DBNFOmniType::SetContentDeclaration(OmniPointer<ContentDeclaration> input_value)
    {
        content_declaration_field = input_value;
    }

    OmniPointer<ContentDeclaration> DBNFOmniType::GetContentDeclaration()
    {
        return content_declaration_field;
    }

    void DBNFOmniType::SetContentDefinition(OmniPointer<ContentDefinition> input_value)
    {
        content_definition_field = input_value;
    }

    OmniPointer<ContentDefinition> DBNFOmniType::GetContentDefinition()
    {
        return content_definition_field;
    }

    void DBNFOmniType::SetPrimativeType(OmniPointer<PrimativeType> input_value)
    {
        primative_type_field = input_value;
    }

    OmniPointer<PrimativeType> DBNFOmniType::GetPrimativeType()
    {
        return primative_type_field;
    }

    void DBNFOmniType::SetDefinedType(OmniPointer<DefinedType> input_value)
    {
        defined_type_field = input_value;
    }

    OmniPointer<DefinedType> DBNFOmniType::GetDefinedType()
    {
        return defined_type_field;
    }

    void DBNFOmniType::SetSingletonType(OmniPointer<SingletonType> input_value)
    {
        singleton_type_field = input_value;
    }

    OmniPointer<SingletonType> DBNFOmniType::GetSingletonType()
    {
        return singleton_type_field;
    }

    void DBNFOmniType::SetDimensionalNote(OmniPointer<DimensionalNote> input_value)
    {
        dimensional_note_field = input_value;
    }

    OmniPointer<DimensionalNote> DBNFOmniType::GetDimensionalNote()
    {
        return dimensional_note_field;
    }

    void DBNFOmniType::SetDimensionalType(OmniPointer<DimensionalType> input_value)
    {
        dimensional_type_field = input_value;
    }

    OmniPointer<DimensionalType> DBNFOmniType::GetDimensionalType()
    {
        return dimensional_type_field;
    }

    void DBNFOmniType::SetMapNote(OmniPointer<MapNote> input_value)
    {
        map_note_field = input_value;
    }

    OmniPointer<MapNote> DBNFOmniType::GetMapNote()
    {
        return map_note_field;
    }

    void DBNFOmniType::SetMapType(OmniPointer<MapType> input_value)
    {
        map_type_field = input_value;
    }

    OmniPointer<MapType> DBNFOmniType::GetMapType()
    {
        return map_type_field;
    }

    void DBNFOmniType::SetValueType(OmniPointer<ValueType> input_value)
    {
        value_type_field = input_value;
    }

    OmniPointer<ValueType> DBNFOmniType::GetValueType()
    {
        return value_type_field;
    }

    void DBNFOmniType::SetParameterListDef(OmniPointer<ParameterListDef> input_value)
    {
        parameter_list_def_field = input_value;
    }

    OmniPointer<ParameterListDef> DBNFOmniType::GetParameterListDef()
    {
        return parameter_list_def_field;
    }

    void DBNFOmniType::SetParameterList(OmniPointer<ParameterList> input_value)
    {
        parameter_list_field = input_value;
    }

    OmniPointer<ParameterList> DBNFOmniType::GetParameterList()
    {
        return parameter_list_field;
    }

    void DBNFOmniType::SetCodeBlock(OmniPointer<CodeBlock> input_value)
    {
        code_block_field = input_value;
    }

    OmniPointer<CodeBlock> DBNFOmniType::GetCodeBlock()
    {
        return code_block_field;
    }

    void DBNFOmniType::SetDeclarationAssign(OmniPointer<DeclarationAssign> input_value)
    {
        declaration_assign_field = input_value;
    }

    OmniPointer<DeclarationAssign> DBNFOmniType::GetDeclarationAssign()
    {
        return declaration_assign_field;
    }

    void DBNFOmniType::SetDeclaration(OmniPointer<Declaration> input_value)
    {
        declaration_field = input_value;
    }

    OmniPointer<Declaration> DBNFOmniType::GetDeclaration()
    {
        return declaration_field;
    }

    void DBNFOmniType::SetAssignment(OmniPointer<Assignment> input_value)
    {
        assignment_field = input_value;
    }

    OmniPointer<Assignment> DBNFOmniType::GetAssignment()
    {
        return assignment_field;
    }

    void DBNFOmniType::SetReturn(OmniPointer<Return> input_value)
    {
        return_field = input_value;
    }

    OmniPointer<Return> DBNFOmniType::GetReturn()
    {
        return return_field;
    }

    void DBNFOmniType::SetElseTail(OmniPointer<ElseTail> input_value)
    {
        else_tail_field = input_value;
    }

    OmniPointer<ElseTail> DBNFOmniType::GetElseTail()
    {
        return else_tail_field;
    }

    void DBNFOmniType::SetConditional(OmniPointer<Conditional> input_value)
    {
        conditional_field = input_value;
    }

    OmniPointer<Conditional> DBNFOmniType::GetConditional()
    {
        return conditional_field;
    }

    void DBNFOmniType::SetLoop(OmniPointer<Loop> input_value)
    {
        loop_field = input_value;
    }

    OmniPointer<Loop> DBNFOmniType::GetLoop()
    {
        return loop_field;
    }

    void DBNFOmniType::SetCall(OmniPointer<Call> input_value)
    {
        call_field = input_value;
    }

    OmniPointer<Call> DBNFOmniType::GetCall()
    {
        return call_field;
    }

    void DBNFOmniType::SetAllocate(OmniPointer<Allocate> input_value)
    {
        allocate_field = input_value;
    }

    OmniPointer<Allocate> DBNFOmniType::GetAllocate()
    {
        return allocate_field;
    }

    void DBNFOmniType::SetInstruction(OmniPointer<Instruction> input_value)
    {
        instruction_field = input_value;
    }

    OmniPointer<Instruction> DBNFOmniType::GetInstruction()
    {
        return instruction_field;
    }

    void DBNFOmniType::SetRValueSingle(OmniPointer<RValueSingle> input_value)
    {
        r_value_single_field = input_value;
    }

    OmniPointer<RValueSingle> DBNFOmniType::GetRValueSingle()
    {
        return r_value_single_field;
    }

    void DBNFOmniType::SetRValueTail(OmniPointer<RValueTail> input_value)
    {
        r_value_tail_field = input_value;
    }

    OmniPointer<RValueTail> DBNFOmniType::GetRValueTail()
    {
        return r_value_tail_field;
    }

    void DBNFOmniType::SetRValue(OmniPointer<RValue> input_value)
    {
        r_value_field = input_value;
    }

    OmniPointer<RValue> DBNFOmniType::GetRValue()
    {
        return r_value_field;
    }

    void DBNFOmniType::SetBinaryOperator(OmniPointer<BinaryOperator> input_value)
    {
        binary_operator_field = input_value;
    }

    OmniPointer<BinaryOperator> DBNFOmniType::GetBinaryOperator()
    {
        return binary_operator_field;
    }

    void DBNFOmniType::SetUnaryOperator(OmniPointer<UnaryOperator> input_value)
    {
        unary_operator_field = input_value;
    }

    OmniPointer<UnaryOperator> DBNFOmniType::GetUnaryOperator()
    {
        return unary_operator_field;
    }

    void DBNFOmniType::SetComment(OmniPointer<Comment> input_value)
    {
        comment_field = input_value;
    }

    OmniPointer<Comment> DBNFOmniType::GetComment()
    {
        return comment_field;
    }

    void DBNFOmniType::SetCommentCharacter(OmniPointer<CommentCharacter> input_value)
    {
        comment_character_field = input_value;
    }

    OmniPointer<CommentCharacter> DBNFOmniType::GetCommentCharacter()
    {
        return comment_character_field;
    }

    void DBNFOmniType::SetQualfiedName(OmniPointer<QualfiedName> input_value)
    {
        qualfied_name_field = input_value;
    }

    OmniPointer<QualfiedName> DBNFOmniType::GetQualfiedName()
    {
        return qualfied_name_field;
    }

    void DBNFOmniType::SetNameTail(OmniPointer<NameTail> input_value)
    {
        name_tail_field = input_value;
    }

    OmniPointer<NameTail> DBNFOmniType::GetNameTail()
    {
        return name_tail_field;
    }

    void DBNFOmniType::SetName(OmniPointer<Name> input_value)
    {
        name_field = input_value;
    }

    OmniPointer<Name> DBNFOmniType::GetName()
    {
        return name_field;
    }

    void DBNFOmniType::SetNameCharacter(OmniPointer<NameCharacter> input_value)
    {
        name_character_field = input_value;
    }

    OmniPointer<NameCharacter> DBNFOmniType::GetNameCharacter()
    {
        return name_character_field;
    }

    void DBNFOmniType::SetBoolean(OmniPointer<Boolean> input_value)
    {
        boolean_field = input_value;
    }

    OmniPointer<Boolean> DBNFOmniType::GetBoolean()
    {
        return boolean_field;
    }

    void DBNFOmniType::SetByte(OmniPointer<Byte> input_value)
    {
        byte_field = input_value;
    }

    OmniPointer<Byte> DBNFOmniType::GetByte()
    {
        return byte_field;
    }

    void DBNFOmniType::SetByteDigit(OmniPointer<ByteDigit> input_value)
    {
        byte_digit_field = input_value;
    }

    OmniPointer<ByteDigit> DBNFOmniType::GetByteDigit()
    {
        return byte_digit_field;
    }

    void DBNFOmniType::SetNegative(OmniPointer<Negative> input_value)
    {
        negative_field = input_value;
    }

    OmniPointer<Negative> DBNFOmniType::GetNegative()
    {
        return negative_field;
    }

    void DBNFOmniType::SetDecimal(OmniPointer<Decimal> input_value)
    {
        decimal_field = input_value;
    }

    OmniPointer<Decimal> DBNFOmniType::GetDecimal()
    {
        return decimal_field;
    }

    void DBNFOmniType::SetNumber(OmniPointer<Number> input_value)
    {
        number_field = input_value;
    }

    OmniPointer<Number> DBNFOmniType::GetNumber()
    {
        return number_field;
    }

    void DBNFOmniType::SetDigit(OmniPointer<Digit> input_value)
    {
        digit_field = input_value;
    }

    OmniPointer<Digit> DBNFOmniType::GetDigit()
    {
        return digit_field;
    }

    void DBNFOmniType::SetLiteral(OmniPointer<Literal> input_value)
    {
        literal_field = input_value;
    }

    OmniPointer<Literal> DBNFOmniType::GetLiteral()
    {
        return literal_field;
    }

    void DBNFOmniType::SetLiteralCharacter(OmniPointer<LiteralCharacter> input_value)
    {
        literal_character_field = input_value;
    }

    OmniPointer<LiteralCharacter> DBNFOmniType::GetLiteralCharacter()
    {
        return literal_character_field;
    }

    void DBNFOmniType::SetWhitespace(OmniPointer<Whitespace> input_value)
    {
        whitespace_field = input_value;
    }

    OmniPointer<Whitespace> DBNFOmniType::GetWhitespace()
    {
        return whitespace_field;
    }

    void DBNFOmniTypeResult::SetValue(OmniPointer<DBNFOmniType> new_value)
    {
        value = new_value;
    }

    OmniPointer<DBNFOmniType> DBNFOmniTypeResult::GetValue()
    {
        return value;
    }

    void DBNFOmniTypeResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool DBNFOmniTypeResult::GetResult()
    {
        return result;
    }

    void DBNFOmniTypeResult::SetCTCodeFile(OmniPointer<CTCodeFile> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetCTCodeFile(input_value);
    }

    void DBNFOmniTypeResult::SetExternalDefinition(OmniPointer<ExternalDefinition> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetExternalDefinition(input_value);
    }

    void DBNFOmniTypeResult::SetUnmanagedType(OmniPointer<UnmanagedType> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetUnmanagedType(input_value);
    }

    void DBNFOmniTypeResult::SetDefinition(OmniPointer<Definition> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetDefinition(input_value);
    }

    void DBNFOmniTypeResult::SetInterfaceDef(OmniPointer<InterfaceDef> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetInterfaceDef(input_value);
    }

    void DBNFOmniTypeResult::SetClassDef(OmniPointer<ClassDef> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetClassDef(input_value);
    }

    void DBNFOmniTypeResult::SetContentDeclaration(OmniPointer<ContentDeclaration> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetContentDeclaration(input_value);
    }

    void DBNFOmniTypeResult::SetContentDefinition(OmniPointer<ContentDefinition> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetContentDefinition(input_value);
    }

    void DBNFOmniTypeResult::SetPrimativeType(OmniPointer<PrimativeType> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetPrimativeType(input_value);
    }

    void DBNFOmniTypeResult::SetDefinedType(OmniPointer<DefinedType> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetDefinedType(input_value);
    }

    void DBNFOmniTypeResult::SetSingletonType(OmniPointer<SingletonType> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetSingletonType(input_value);
    }

    void DBNFOmniTypeResult::SetDimensionalNote(OmniPointer<DimensionalNote> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetDimensionalNote(input_value);
    }

    void DBNFOmniTypeResult::SetDimensionalType(OmniPointer<DimensionalType> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetDimensionalType(input_value);
    }

    void DBNFOmniTypeResult::SetMapNote(OmniPointer<MapNote> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetMapNote(input_value);
    }

    void DBNFOmniTypeResult::SetMapType(OmniPointer<MapType> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetMapType(input_value);
    }

    void DBNFOmniTypeResult::SetValueType(OmniPointer<ValueType> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetValueType(input_value);
    }

    void DBNFOmniTypeResult::SetParameterListDef(OmniPointer<ParameterListDef> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetParameterListDef(input_value);
    }

    void DBNFOmniTypeResult::SetParameterList(OmniPointer<ParameterList> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetParameterList(input_value);
    }

    void DBNFOmniTypeResult::SetCodeBlock(OmniPointer<CodeBlock> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetCodeBlock(input_value);
    }

    void DBNFOmniTypeResult::SetDeclarationAssign(OmniPointer<DeclarationAssign> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetDeclarationAssign(input_value);
    }

    void DBNFOmniTypeResult::SetDeclaration(OmniPointer<Declaration> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetDeclaration(input_value);
    }

    void DBNFOmniTypeResult::SetAssignment(OmniPointer<Assignment> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetAssignment(input_value);
    }

    void DBNFOmniTypeResult::SetReturn(OmniPointer<Return> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetReturn(input_value);
    }

    void DBNFOmniTypeResult::SetElseTail(OmniPointer<ElseTail> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetElseTail(input_value);
    }

    void DBNFOmniTypeResult::SetConditional(OmniPointer<Conditional> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetConditional(input_value);
    }

    void DBNFOmniTypeResult::SetLoop(OmniPointer<Loop> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetLoop(input_value);
    }

    void DBNFOmniTypeResult::SetCall(OmniPointer<Call> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetCall(input_value);
    }

    void DBNFOmniTypeResult::SetAllocate(OmniPointer<Allocate> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetAllocate(input_value);
    }

    void DBNFOmniTypeResult::SetInstruction(OmniPointer<Instruction> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetInstruction(input_value);
    }

    void DBNFOmniTypeResult::SetRValueSingle(OmniPointer<RValueSingle> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetRValueSingle(input_value);
    }

    void DBNFOmniTypeResult::SetRValueTail(OmniPointer<RValueTail> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetRValueTail(input_value);
    }

    void DBNFOmniTypeResult::SetRValue(OmniPointer<RValue> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetRValue(input_value);
    }

    void DBNFOmniTypeResult::SetBinaryOperator(OmniPointer<BinaryOperator> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetBinaryOperator(input_value);
    }

    void DBNFOmniTypeResult::SetUnaryOperator(OmniPointer<UnaryOperator> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetUnaryOperator(input_value);
    }

    void DBNFOmniTypeResult::SetComment(OmniPointer<Comment> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetComment(input_value);
    }

    void DBNFOmniTypeResult::SetCommentCharacter(OmniPointer<CommentCharacter> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetCommentCharacter(input_value);
    }

    void DBNFOmniTypeResult::SetQualfiedName(OmniPointer<QualfiedName> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetQualfiedName(input_value);
    }

    void DBNFOmniTypeResult::SetNameTail(OmniPointer<NameTail> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetNameTail(input_value);
    }

    void DBNFOmniTypeResult::SetName(OmniPointer<Name> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetName(input_value);
    }

    void DBNFOmniTypeResult::SetNameCharacter(OmniPointer<NameCharacter> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetNameCharacter(input_value);
    }

    void DBNFOmniTypeResult::SetBoolean(OmniPointer<Boolean> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetBoolean(input_value);
    }

    void DBNFOmniTypeResult::SetByte(OmniPointer<Byte> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetByte(input_value);
    }

    void DBNFOmniTypeResult::SetByteDigit(OmniPointer<ByteDigit> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetByteDigit(input_value);
    }

    void DBNFOmniTypeResult::SetNegative(OmniPointer<Negative> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetNegative(input_value);
    }

    void DBNFOmniTypeResult::SetDecimal(OmniPointer<Decimal> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetDecimal(input_value);
    }

    void DBNFOmniTypeResult::SetNumber(OmniPointer<Number> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetNumber(input_value);
    }

    void DBNFOmniTypeResult::SetDigit(OmniPointer<Digit> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetDigit(input_value);
    }

    void DBNFOmniTypeResult::SetLiteral(OmniPointer<Literal> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetLiteral(input_value);
    }

    void DBNFOmniTypeResult::SetLiteralCharacter(OmniPointer<LiteralCharacter> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetLiteralCharacter(input_value);
    }

    void DBNFOmniTypeResult::SetWhitespace(OmniPointer<Whitespace> input_value)
    {
        value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
        value->SetWhitespace(input_value);
    }

    void DBNFOmniTypeListResult::SetValue(std::vector<OmniPointer<DBNFOmniType>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<DBNFOmniType>> DBNFOmniTypeListResult::GetValue()
    {
        return value;
    }

    void DBNFOmniTypeListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool DBNFOmniTypeListResult::GetResult()
    {
        return result;
    }

    void DBNFOmniTypeListResult::SetCTCodeFile(std::vector<OmniPointer<CTCodeFile>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetCTCodeFile(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetExternalDefinition(std::vector<OmniPointer<ExternalDefinition>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetExternalDefinition(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetUnmanagedType(std::vector<OmniPointer<UnmanagedType>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetUnmanagedType(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetDefinition(std::vector<OmniPointer<Definition>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetDefinition(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetInterfaceDef(std::vector<OmniPointer<InterfaceDef>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetInterfaceDef(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetClassDef(std::vector<OmniPointer<ClassDef>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetClassDef(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetContentDeclaration(std::vector<OmniPointer<ContentDeclaration>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetContentDeclaration(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetContentDefinition(std::vector<OmniPointer<ContentDefinition>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetContentDefinition(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetPrimativeType(std::vector<OmniPointer<PrimativeType>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetPrimativeType(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetDefinedType(std::vector<OmniPointer<DefinedType>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetDefinedType(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetSingletonType(std::vector<OmniPointer<SingletonType>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetSingletonType(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetDimensionalNote(std::vector<OmniPointer<DimensionalNote>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetDimensionalNote(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetDimensionalType(std::vector<OmniPointer<DimensionalType>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetDimensionalType(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetMapNote(std::vector<OmniPointer<MapNote>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetMapNote(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetMapType(std::vector<OmniPointer<MapType>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetMapType(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetValueType(std::vector<OmniPointer<ValueType>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetValueType(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetParameterListDef(std::vector<OmniPointer<ParameterListDef>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetParameterListDef(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetParameterList(std::vector<OmniPointer<ParameterList>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetParameterList(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetCodeBlock(std::vector<OmniPointer<CodeBlock>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetCodeBlock(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetDeclarationAssign(std::vector<OmniPointer<DeclarationAssign>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetDeclarationAssign(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetDeclaration(std::vector<OmniPointer<Declaration>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetDeclaration(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetAssignment(std::vector<OmniPointer<Assignment>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetAssignment(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetReturn(std::vector<OmniPointer<Return>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetReturn(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetElseTail(std::vector<OmniPointer<ElseTail>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetElseTail(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetConditional(std::vector<OmniPointer<Conditional>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetConditional(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetLoop(std::vector<OmniPointer<Loop>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetLoop(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetCall(std::vector<OmniPointer<Call>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetCall(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetAllocate(std::vector<OmniPointer<Allocate>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetAllocate(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetInstruction(std::vector<OmniPointer<Instruction>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetInstruction(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetRValueSingle(std::vector<OmniPointer<RValueSingle>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetRValueSingle(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetRValueTail(std::vector<OmniPointer<RValueTail>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetRValueTail(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetRValue(std::vector<OmniPointer<RValue>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetRValue(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetBinaryOperator(std::vector<OmniPointer<BinaryOperator>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetBinaryOperator(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetUnaryOperator(std::vector<OmniPointer<UnaryOperator>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetUnaryOperator(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetComment(std::vector<OmniPointer<Comment>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetComment(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetCommentCharacter(std::vector<OmniPointer<CommentCharacter>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetCommentCharacter(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetQualfiedName(std::vector<OmniPointer<QualfiedName>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetQualfiedName(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetNameTail(std::vector<OmniPointer<NameTail>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetNameTail(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetName(std::vector<OmniPointer<Name>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetName(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetNameCharacter(std::vector<OmniPointer<NameCharacter>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetNameCharacter(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetBoolean(std::vector<OmniPointer<Boolean>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetBoolean(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetByte(std::vector<OmniPointer<Byte>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetByte(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetByteDigit(std::vector<OmniPointer<ByteDigit>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetByteDigit(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetNegative(std::vector<OmniPointer<Negative>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetNegative(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetDecimal(std::vector<OmniPointer<Decimal>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetDecimal(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetNumber(std::vector<OmniPointer<Number>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetNumber(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetDigit(std::vector<OmniPointer<Digit>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetDigit(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetLiteral(std::vector<OmniPointer<Literal>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetLiteral(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetLiteralCharacter(std::vector<OmniPointer<LiteralCharacter>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetLiteralCharacter(Element(input_value, index));
            index = index + 1;
        }
    }

    void DBNFOmniTypeListResult::SetWhitespace(std::vector<OmniPointer<Whitespace>> input_value)
    {
        int index = 0;
        while (index < Size(input_value))
        {
            OmniPointer<DBNFOmniType> value = std::shared_ptr<DBNFOmniType>(new DBNFOmniType());
            value->SetWhitespace(Element(input_value, index));
            index = index + 1;
        }
    }

    void LargeString::SetData(std::string new_data)
    {
        data = new_data;
    }

    std::string LargeString::GetData()
    {
        return data;
    }

    void LengthString::SetData(OmniPointer<LargeString> new_data)
    {
        data = new_data;
    }

    OmniPointer<LargeString> LengthString::GetData()
    {
        return data;
    }

    void LengthString::SetStart(int new_start)
    {
        start = new_start;
    }

    int LengthString::GetStart()
    {
        return start;
    }

    void LengthString::SetLength(int new_length)
    {
        length = new_length;
    }

    int LengthString::GetLength()
    {
        return length;
    }

    std::string LengthString::GetString()
    {
        std::string deep_data = data->GetData();
        std::string result;
        int index = start;
        int end = start + length;
        while (index < end)
        {
            result = Concat(result, At(deep_data, index));
            index = index + 1;
        }

        return result;
    }

    void CTCodeFileParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<ExternalDefinitionListResult> declarations_field = std::shared_ptr<ExternalDefinitionListResult>(new ExternalDefinitionListResult());
        OmniPointer<DefinitionListResult> definitions_field = std::shared_ptr<DefinitionListResult>(new DefinitionListResult());
        OmniPointer<UnmanagedTypeListResult> unmanaged_types_field = std::shared_ptr<UnmanagedTypeListResult>(new UnmanagedTypeListResult());
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && external_definition_parser_instance->ParseManySave(index, declarations_field, 0, -1) && unmanaged_type_parser_instance->ParseManySave(index, unmanaged_types_field, 0, -1) && definition_parser_instance->ParseManySave(index, definitions_field, 0, -1))
        {
            instance->SetDeclarations(declarations_field->GetValue());
            instance->SetDefinitions(definitions_field->GetValue());
            instance->SetUnmanagedTypes(unmanaged_types_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            declarations_field = std::shared_ptr<ExternalDefinitionListResult>(new ExternalDefinitionListResult());
            definitions_field = std::shared_ptr<DefinitionListResult>(new DefinitionListResult());
            unmanaged_types_field = std::shared_ptr<UnmanagedTypeListResult>(new UnmanagedTypeListResult());
        }

        result->SetResult(false);
        return result->GetResult();
    }

    bool CTCodeFileParser::ParseSingle(OmniPointer<LengthString> index)
    {
        OmniPointer<CTCodeFileResult> result = std::shared_ptr<CTCodeFileResult>(new CTCodeFileResult());
        return ParseSingleSave(index, result);
    }

    bool CTCodeFileParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<CTCodeFileResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool CTCodeFileParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<CTCodeFileResult> result = std::shared_ptr<CTCodeFileResult>(new CTCodeFileResult());
        return ParseOptionalSave(index, result);
    }

    bool CTCodeFileParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<CTCodeFileListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<CTCodeFile>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<CTCodeFileResult> result = std::shared_ptr<CTCodeFileResult>(new CTCodeFileResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void CTCodeFileResult::SetValue(OmniPointer<CTCodeFile> new_value)
    {
        value = new_value;
    }

    OmniPointer<CTCodeFile> CTCodeFileResult::GetValue()
    {
        return value;
    }

    void CTCodeFileResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool CTCodeFileResult::GetResult()
    {
        return result;
    }

    void CTCodeFileListResult::SetValue(std::vector<OmniPointer<CTCodeFile>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<CTCodeFile>> CTCodeFileListResult::GetValue()
    {
        return value;
    }

    void CTCodeFileListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool CTCodeFileListResult::GetResult()
    {
        return result;
    }

    void CTCodeFile::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string CTCodeFile::UnParse()
    {
        return length_string->GetString();
    }

    void CTCodeFile::SetDeclarations(std::vector<OmniPointer<ExternalDefinition>> input_value)
    {
        declarations_field = input_value;
    }

    std::vector<OmniPointer<ExternalDefinition>> CTCodeFile::GetDeclarations()
    {
        return declarations_field;
    }

    void CTCodeFile::SetDefinitions(std::vector<OmniPointer<Definition>> input_value)
    {
        definitions_field = input_value;
    }

    std::vector<OmniPointer<Definition>> CTCodeFile::GetDefinitions()
    {
        return definitions_field;
    }

    void CTCodeFile::SetUnmanagedTypes(std::vector<OmniPointer<UnmanagedType>> input_value)
    {
        unmanaged_types_field = input_value;
    }

    std::vector<OmniPointer<UnmanagedType>> CTCodeFile::GetUnmanagedTypes()
    {
        return unmanaged_types_field;
    }

    void ExternalDefinitionParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && string_parser_instance->ParseSingle(index, std::string("exdef")) && whitespace_parser_instance->ParseMany(index, 0, -1) && qualfied_name_parser_instance->ParseSingleSave(index, exdef_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string(";")) && whitespace_parser_instance->ParseMany(index, 0, -1))
        {
            instance->SetExdef(exdef_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
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
        return ParseSingleSave(index, result);
    }

    bool ExternalDefinitionParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ExternalDefinitionResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool ExternalDefinitionParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<ExternalDefinitionResult> result = std::shared_ptr<ExternalDefinitionResult>(new ExternalDefinitionResult());
        return ParseOptionalSave(index, result);
    }

    bool ExternalDefinitionParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<ExternalDefinitionListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<ExternalDefinition>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<ExternalDefinitionResult> result = std::shared_ptr<ExternalDefinitionResult>(new ExternalDefinitionResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void ExternalDefinitionResult::SetValue(OmniPointer<ExternalDefinition> new_value)
    {
        value = new_value;
    }

    OmniPointer<ExternalDefinition> ExternalDefinitionResult::GetValue()
    {
        return value;
    }

    void ExternalDefinitionResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool ExternalDefinitionResult::GetResult()
    {
        return result;
    }

    void ExternalDefinitionListResult::SetValue(std::vector<OmniPointer<ExternalDefinition>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<ExternalDefinition>> ExternalDefinitionListResult::GetValue()
    {
        return value;
    }

    void ExternalDefinitionListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool ExternalDefinitionListResult::GetResult()
    {
        return result;
    }

    void ExternalDefinition::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string ExternalDefinition::UnParse()
    {
        return length_string->GetString();
    }

    void ExternalDefinition::SetExdef(OmniPointer<QualfiedName> input_value)
    {
        exdef_field = input_value;
    }

    OmniPointer<QualfiedName> ExternalDefinition::GetExdef()
    {
        return exdef_field;
    }

    void UnmanagedTypeParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && string_parser_instance->ParseSingle(index, std::string("unmanaged")) && whitespace_parser_instance->ParseMany(index, 0, -1) && qualfied_name_parser_instance->ParseSingleSave(index, unmanaged_type_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string(";")) && whitespace_parser_instance->ParseMany(index, 0, -1))
        {
            instance->SetUnmanagedType(unmanaged_type_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
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
        return ParseSingleSave(index, result);
    }

    bool UnmanagedTypeParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<UnmanagedTypeResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool UnmanagedTypeParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<UnmanagedTypeResult> result = std::shared_ptr<UnmanagedTypeResult>(new UnmanagedTypeResult());
        return ParseOptionalSave(index, result);
    }

    bool UnmanagedTypeParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<UnmanagedTypeListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<UnmanagedType>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<UnmanagedTypeResult> result = std::shared_ptr<UnmanagedTypeResult>(new UnmanagedTypeResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void UnmanagedTypeResult::SetValue(OmniPointer<UnmanagedType> new_value)
    {
        value = new_value;
    }

    OmniPointer<UnmanagedType> UnmanagedTypeResult::GetValue()
    {
        return value;
    }

    void UnmanagedTypeResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool UnmanagedTypeResult::GetResult()
    {
        return result;
    }

    void UnmanagedTypeListResult::SetValue(std::vector<OmniPointer<UnmanagedType>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<UnmanagedType>> UnmanagedTypeListResult::GetValue()
    {
        return value;
    }

    void UnmanagedTypeListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool UnmanagedTypeListResult::GetResult()
    {
        return result;
    }

    void UnmanagedType::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string UnmanagedType::UnParse()
    {
        return length_string->GetString();
    }

    void UnmanagedType::SetUnmanagedType(OmniPointer<QualfiedName> input_value)
    {
        unmanaged_type_field = input_value;
    }

    OmniPointer<QualfiedName> UnmanagedType::GetUnmanagedType()
    {
        return unmanaged_type_field;
    }

    void DefinitionParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && interface_def_parser_instance->ParseSingleSave(index, interface_def_field))
        {
            instance->SetClassDef(class_def_field->GetValue());
            instance->SetInterfaceDef(interface_def_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && class_def_parser_instance->ParseSingleSave(index, class_def_field))
        {
            instance->SetClassDef(class_def_field->GetValue());
            instance->SetInterfaceDef(interface_def_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
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
        return ParseSingleSave(index, result);
    }

    bool DefinitionParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<DefinitionResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool DefinitionParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<DefinitionResult> result = std::shared_ptr<DefinitionResult>(new DefinitionResult());
        return ParseOptionalSave(index, result);
    }

    bool DefinitionParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<DefinitionListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<Definition>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<DefinitionResult> result = std::shared_ptr<DefinitionResult>(new DefinitionResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void DefinitionResult::SetValue(OmniPointer<Definition> new_value)
    {
        value = new_value;
    }

    OmniPointer<Definition> DefinitionResult::GetValue()
    {
        return value;
    }

    void DefinitionResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool DefinitionResult::GetResult()
    {
        return result;
    }

    void DefinitionListResult::SetValue(std::vector<OmniPointer<Definition>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<Definition>> DefinitionListResult::GetValue()
    {
        return value;
    }

    void DefinitionListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool DefinitionListResult::GetResult()
    {
        return result;
    }

    void Definition::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string Definition::UnParse()
    {
        return length_string->GetString();
    }

    void Definition::SetClassDef(OmniPointer<ClassDef> input_value)
    {
        class_def_field = input_value;
    }

    OmniPointer<ClassDef> Definition::GetClassDef()
    {
        return class_def_field;
    }

    void Definition::SetInterfaceDef(OmniPointer<InterfaceDef> input_value)
    {
        interface_def_field = input_value;
    }

    OmniPointer<InterfaceDef> Definition::GetInterfaceDef()
    {
        return interface_def_field;
    }

    void InterfaceDefParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CommentResult> comment_field = std::shared_ptr<CommentResult>(new CommentResult());
        OmniPointer<ContentDeclarationListResult> declarations_field = std::shared_ptr<ContentDeclarationListResult>(new ContentDeclarationListResult());
        OmniPointer<NameResult> name_field = std::shared_ptr<NameResult>(new NameResult());
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && comment_parser_instance->ParseOptionalSave(index, comment_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string("interface")) && whitespace_parser_instance->ParseMany(index, 1, -1) && name_parser_instance->ParseSingleSave(index, name_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string("{")) && whitespace_parser_instance->ParseMany(index, 0, -1) && content_declaration_parser_instance->ParseManySave(index, declarations_field, 0, -1) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string("}")) && whitespace_parser_instance->ParseMany(index, 0, -1))
        {
            instance->SetComment(comment_field->GetValue());
            instance->SetDeclarations(declarations_field->GetValue());
            instance->SetName(name_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            comment_field = std::shared_ptr<CommentResult>(new CommentResult());
            declarations_field = std::shared_ptr<ContentDeclarationListResult>(new ContentDeclarationListResult());
            name_field = std::shared_ptr<NameResult>(new NameResult());
        }

        result->SetResult(false);
        return result->GetResult();
    }

    bool InterfaceDefParser::ParseSingle(OmniPointer<LengthString> index)
    {
        OmniPointer<InterfaceDefResult> result = std::shared_ptr<InterfaceDefResult>(new InterfaceDefResult());
        return ParseSingleSave(index, result);
    }

    bool InterfaceDefParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<InterfaceDefResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool InterfaceDefParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<InterfaceDefResult> result = std::shared_ptr<InterfaceDefResult>(new InterfaceDefResult());
        return ParseOptionalSave(index, result);
    }

    bool InterfaceDefParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<InterfaceDefListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<InterfaceDef>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<InterfaceDefResult> result = std::shared_ptr<InterfaceDefResult>(new InterfaceDefResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void InterfaceDefResult::SetValue(OmniPointer<InterfaceDef> new_value)
    {
        value = new_value;
    }

    OmniPointer<InterfaceDef> InterfaceDefResult::GetValue()
    {
        return value;
    }

    void InterfaceDefResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool InterfaceDefResult::GetResult()
    {
        return result;
    }

    void InterfaceDefListResult::SetValue(std::vector<OmniPointer<InterfaceDef>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<InterfaceDef>> InterfaceDefListResult::GetValue()
    {
        return value;
    }

    void InterfaceDefListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool InterfaceDefListResult::GetResult()
    {
        return result;
    }

    void InterfaceDef::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string InterfaceDef::UnParse()
    {
        return length_string->GetString();
    }

    void InterfaceDef::SetComment(OmniPointer<Comment> input_value)
    {
        comment_field = input_value;
    }

    OmniPointer<Comment> InterfaceDef::GetComment()
    {
        return comment_field;
    }

    void InterfaceDef::SetDeclarations(std::vector<OmniPointer<ContentDeclaration>> input_value)
    {
        declarations_field = input_value;
    }

    std::vector<OmniPointer<ContentDeclaration>> InterfaceDef::GetDeclarations()
    {
        return declarations_field;
    }

    void InterfaceDef::SetName(OmniPointer<Name> input_value)
    {
        name_field = input_value;
    }

    OmniPointer<Name> InterfaceDef::GetName()
    {
        return name_field;
    }

    void ClassDefParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CommentResult> comment_field = std::shared_ptr<CommentResult>(new CommentResult());
        OmniPointer<ContentDefinitionListResult> definitions_field = std::shared_ptr<ContentDefinitionListResult>(new ContentDefinitionListResult());
        OmniPointer<NameResult> name_field = std::shared_ptr<NameResult>(new NameResult());
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && comment_parser_instance->ParseOptionalSave(index, comment_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string("class")) && whitespace_parser_instance->ParseMany(index, 1, -1) && name_parser_instance->ParseSingleSave(index, name_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string("{")) && whitespace_parser_instance->ParseMany(index, 0, -1) && content_definition_parser_instance->ParseManySave(index, definitions_field, 0, -1) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string("}")) && whitespace_parser_instance->ParseMany(index, 0, -1))
        {
            instance->SetComment(comment_field->GetValue());
            instance->SetDefinitions(definitions_field->GetValue());
            instance->SetName(name_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            comment_field = std::shared_ptr<CommentResult>(new CommentResult());
            definitions_field = std::shared_ptr<ContentDefinitionListResult>(new ContentDefinitionListResult());
            name_field = std::shared_ptr<NameResult>(new NameResult());
        }

        result->SetResult(false);
        return result->GetResult();
    }

    bool ClassDefParser::ParseSingle(OmniPointer<LengthString> index)
    {
        OmniPointer<ClassDefResult> result = std::shared_ptr<ClassDefResult>(new ClassDefResult());
        return ParseSingleSave(index, result);
    }

    bool ClassDefParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ClassDefResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool ClassDefParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<ClassDefResult> result = std::shared_ptr<ClassDefResult>(new ClassDefResult());
        return ParseOptionalSave(index, result);
    }

    bool ClassDefParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<ClassDefListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<ClassDef>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<ClassDefResult> result = std::shared_ptr<ClassDefResult>(new ClassDefResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void ClassDefResult::SetValue(OmniPointer<ClassDef> new_value)
    {
        value = new_value;
    }

    OmniPointer<ClassDef> ClassDefResult::GetValue()
    {
        return value;
    }

    void ClassDefResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool ClassDefResult::GetResult()
    {
        return result;
    }

    void ClassDefListResult::SetValue(std::vector<OmniPointer<ClassDef>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<ClassDef>> ClassDefListResult::GetValue()
    {
        return value;
    }

    void ClassDefListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool ClassDefListResult::GetResult()
    {
        return result;
    }

    void ClassDef::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string ClassDef::UnParse()
    {
        return length_string->GetString();
    }

    void ClassDef::SetComment(OmniPointer<Comment> input_value)
    {
        comment_field = input_value;
    }

    OmniPointer<Comment> ClassDef::GetComment()
    {
        return comment_field;
    }

    void ClassDef::SetDefinitions(std::vector<OmniPointer<ContentDefinition>> input_value)
    {
        definitions_field = input_value;
    }

    std::vector<OmniPointer<ContentDefinition>> ClassDef::GetDefinitions()
    {
        return definitions_field;
    }

    void ClassDef::SetName(OmniPointer<Name> input_value)
    {
        name_field = input_value;
    }

    OmniPointer<Name> ClassDef::GetName()
    {
        return name_field;
    }

    void ContentDeclarationParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CommentResult> comment_field = std::shared_ptr<CommentResult>(new CommentResult());
        OmniPointer<NameResult> name_field = std::shared_ptr<NameResult>(new NameResult());
        OmniPointer<ParameterListDefResult> parameters_field = std::shared_ptr<ParameterListDefResult>(new ParameterListDefResult());
        OmniPointer<ValueTypeResult> type_field = std::shared_ptr<ValueTypeResult>(new ValueTypeResult());
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && comment_parser_instance->ParseOptionalSave(index, comment_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string("function")) && whitespace_parser_instance->ParseMany(index, 1, -1) && value_type_parser_instance->ParseSingleSave(index, type_field) && whitespace_parser_instance->ParseMany(index, 1, -1) && name_parser_instance->ParseSingleSave(index, name_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string("(")) && whitespace_parser_instance->ParseMany(index, 0, -1) && parameter_list_def_parser_instance->ParseOptionalSave(index, parameters_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string(")")) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string(";")) && whitespace_parser_instance->ParseMany(index, 0, -1))
        {
            instance->SetComment(comment_field->GetValue());
            instance->SetName(name_field->GetValue());
            instance->SetParameters(parameters_field->GetValue());
            instance->SetType(type_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            comment_field = std::shared_ptr<CommentResult>(new CommentResult());
            name_field = std::shared_ptr<NameResult>(new NameResult());
            parameters_field = std::shared_ptr<ParameterListDefResult>(new ParameterListDefResult());
            type_field = std::shared_ptr<ValueTypeResult>(new ValueTypeResult());
        }

        result->SetResult(false);
        return result->GetResult();
    }

    bool ContentDeclarationParser::ParseSingle(OmniPointer<LengthString> index)
    {
        OmniPointer<ContentDeclarationResult> result = std::shared_ptr<ContentDeclarationResult>(new ContentDeclarationResult());
        return ParseSingleSave(index, result);
    }

    bool ContentDeclarationParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ContentDeclarationResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool ContentDeclarationParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<ContentDeclarationResult> result = std::shared_ptr<ContentDeclarationResult>(new ContentDeclarationResult());
        return ParseOptionalSave(index, result);
    }

    bool ContentDeclarationParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<ContentDeclarationListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<ContentDeclaration>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<ContentDeclarationResult> result = std::shared_ptr<ContentDeclarationResult>(new ContentDeclarationResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void ContentDeclarationResult::SetValue(OmniPointer<ContentDeclaration> new_value)
    {
        value = new_value;
    }

    OmniPointer<ContentDeclaration> ContentDeclarationResult::GetValue()
    {
        return value;
    }

    void ContentDeclarationResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool ContentDeclarationResult::GetResult()
    {
        return result;
    }

    void ContentDeclarationListResult::SetValue(std::vector<OmniPointer<ContentDeclaration>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<ContentDeclaration>> ContentDeclarationListResult::GetValue()
    {
        return value;
    }

    void ContentDeclarationListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool ContentDeclarationListResult::GetResult()
    {
        return result;
    }

    void ContentDeclaration::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string ContentDeclaration::UnParse()
    {
        return length_string->GetString();
    }

    void ContentDeclaration::SetComment(OmniPointer<Comment> input_value)
    {
        comment_field = input_value;
    }

    OmniPointer<Comment> ContentDeclaration::GetComment()
    {
        return comment_field;
    }

    void ContentDeclaration::SetName(OmniPointer<Name> input_value)
    {
        name_field = input_value;
    }

    OmniPointer<Name> ContentDeclaration::GetName()
    {
        return name_field;
    }

    void ContentDeclaration::SetParameters(OmniPointer<ParameterListDef> input_value)
    {
        parameters_field = input_value;
    }

    OmniPointer<ParameterListDef> ContentDeclaration::GetParameters()
    {
        return parameters_field;
    }

    void ContentDeclaration::SetType(OmniPointer<ValueType> input_value)
    {
        type_field = input_value;
    }

    OmniPointer<ValueType> ContentDeclaration::GetType()
    {
        return type_field;
    }

    void ContentDefinitionParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CommentResult> comment_field = std::shared_ptr<CommentResult>(new CommentResult());
        OmniPointer<CodeBlockResult> function_body_field = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
        OmniPointer<NameResult> name_field = std::shared_ptr<NameResult>(new NameResult());
        OmniPointer<ParameterListDefResult> parameters_field = std::shared_ptr<ParameterListDefResult>(new ParameterListDefResult());
        OmniPointer<ValueTypeResult> type_field = std::shared_ptr<ValueTypeResult>(new ValueTypeResult());
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && comment_parser_instance->ParseOptionalSave(index, comment_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string("function")) && whitespace_parser_instance->ParseMany(index, 1, -1) && value_type_parser_instance->ParseSingleSave(index, type_field) && whitespace_parser_instance->ParseMany(index, 1, -1) && name_parser_instance->ParseSingleSave(index, name_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string("(")) && whitespace_parser_instance->ParseMany(index, 0, -1) && parameter_list_def_parser_instance->ParseOptionalSave(index, parameters_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string(")")) && whitespace_parser_instance->ParseMany(index, 0, -1) && code_block_parser_instance->ParseSingleSave(index, function_body_field) && whitespace_parser_instance->ParseMany(index, 0, -1))
        {
            instance->SetComment(comment_field->GetValue());
            instance->SetFunctionBody(function_body_field->GetValue());
            instance->SetName(name_field->GetValue());
            instance->SetParameters(parameters_field->GetValue());
            instance->SetType(type_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            comment_field = std::shared_ptr<CommentResult>(new CommentResult());
            function_body_field = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
            name_field = std::shared_ptr<NameResult>(new NameResult());
            parameters_field = std::shared_ptr<ParameterListDefResult>(new ParameterListDefResult());
            type_field = std::shared_ptr<ValueTypeResult>(new ValueTypeResult());
        }

        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && comment_parser_instance->ParseOptionalSave(index, comment_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && value_type_parser_instance->ParseSingleSave(index, type_field) && whitespace_parser_instance->ParseMany(index, 1, -1) && name_parser_instance->ParseSingleSave(index, name_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string(";")) && whitespace_parser_instance->ParseMany(index, 0, -1))
        {
            instance->SetComment(comment_field->GetValue());
            instance->SetFunctionBody(function_body_field->GetValue());
            instance->SetName(name_field->GetValue());
            instance->SetParameters(parameters_field->GetValue());
            instance->SetType(type_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            comment_field = std::shared_ptr<CommentResult>(new CommentResult());
            function_body_field = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
            name_field = std::shared_ptr<NameResult>(new NameResult());
            parameters_field = std::shared_ptr<ParameterListDefResult>(new ParameterListDefResult());
            type_field = std::shared_ptr<ValueTypeResult>(new ValueTypeResult());
        }

        result->SetResult(false);
        return result->GetResult();
    }

    bool ContentDefinitionParser::ParseSingle(OmniPointer<LengthString> index)
    {
        OmniPointer<ContentDefinitionResult> result = std::shared_ptr<ContentDefinitionResult>(new ContentDefinitionResult());
        return ParseSingleSave(index, result);
    }

    bool ContentDefinitionParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ContentDefinitionResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool ContentDefinitionParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<ContentDefinitionResult> result = std::shared_ptr<ContentDefinitionResult>(new ContentDefinitionResult());
        return ParseOptionalSave(index, result);
    }

    bool ContentDefinitionParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<ContentDefinitionListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<ContentDefinition>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<ContentDefinitionResult> result = std::shared_ptr<ContentDefinitionResult>(new ContentDefinitionResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void ContentDefinitionResult::SetValue(OmniPointer<ContentDefinition> new_value)
    {
        value = new_value;
    }

    OmniPointer<ContentDefinition> ContentDefinitionResult::GetValue()
    {
        return value;
    }

    void ContentDefinitionResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool ContentDefinitionResult::GetResult()
    {
        return result;
    }

    void ContentDefinitionListResult::SetValue(std::vector<OmniPointer<ContentDefinition>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<ContentDefinition>> ContentDefinitionListResult::GetValue()
    {
        return value;
    }

    void ContentDefinitionListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool ContentDefinitionListResult::GetResult()
    {
        return result;
    }

    void ContentDefinition::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string ContentDefinition::UnParse()
    {
        return length_string->GetString();
    }

    void ContentDefinition::SetComment(OmniPointer<Comment> input_value)
    {
        comment_field = input_value;
    }

    OmniPointer<Comment> ContentDefinition::GetComment()
    {
        return comment_field;
    }

    void ContentDefinition::SetFunctionBody(OmniPointer<CodeBlock> input_value)
    {
        function_body_field = input_value;
    }

    OmniPointer<CodeBlock> ContentDefinition::GetFunctionBody()
    {
        return function_body_field;
    }

    void ContentDefinition::SetName(OmniPointer<Name> input_value)
    {
        name_field = input_value;
    }

    OmniPointer<Name> ContentDefinition::GetName()
    {
        return name_field;
    }

    void ContentDefinition::SetParameters(OmniPointer<ParameterListDef> input_value)
    {
        parameters_field = input_value;
    }

    OmniPointer<ParameterListDef> ContentDefinition::GetParameters()
    {
        return parameters_field;
    }

    void ContentDefinition::SetType(OmniPointer<ValueType> input_value)
    {
        type_field = input_value;
    }

    OmniPointer<ValueType> ContentDefinition::GetType()
    {
        return type_field;
    }

    void PrimativeTypeParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && string_parser_instance->ParseSingle(index, std::string("int")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("string")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("bool")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("float")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("void")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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
        return ParseSingleSave(index, result);
    }

    bool PrimativeTypeParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<PrimativeTypeResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool PrimativeTypeParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<PrimativeTypeResult> result = std::shared_ptr<PrimativeTypeResult>(new PrimativeTypeResult());
        return ParseOptionalSave(index, result);
    }

    bool PrimativeTypeParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<PrimativeTypeListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<PrimativeType>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<PrimativeTypeResult> result = std::shared_ptr<PrimativeTypeResult>(new PrimativeTypeResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void PrimativeTypeResult::SetValue(OmniPointer<PrimativeType> new_value)
    {
        value = new_value;
    }

    OmniPointer<PrimativeType> PrimativeTypeResult::GetValue()
    {
        return value;
    }

    void PrimativeTypeResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool PrimativeTypeResult::GetResult()
    {
        return result;
    }

    void PrimativeTypeListResult::SetValue(std::vector<OmniPointer<PrimativeType>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<PrimativeType>> PrimativeTypeListResult::GetValue()
    {
        return value;
    }

    void PrimativeTypeListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool PrimativeTypeListResult::GetResult()
    {
        return result;
    }

    void PrimativeType::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string PrimativeType::UnParse()
    {
        return length_string->GetString();
    }

    void DefinedTypeParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && qualfied_name_parser_instance->ParseSingleSave(index, name_field))
        {
            instance->SetName(name_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
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
        return ParseSingleSave(index, result);
    }

    bool DefinedTypeParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<DefinedTypeResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool DefinedTypeParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<DefinedTypeResult> result = std::shared_ptr<DefinedTypeResult>(new DefinedTypeResult());
        return ParseOptionalSave(index, result);
    }

    bool DefinedTypeParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<DefinedTypeListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<DefinedType>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<DefinedTypeResult> result = std::shared_ptr<DefinedTypeResult>(new DefinedTypeResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void DefinedTypeResult::SetValue(OmniPointer<DefinedType> new_value)
    {
        value = new_value;
    }

    OmniPointer<DefinedType> DefinedTypeResult::GetValue()
    {
        return value;
    }

    void DefinedTypeResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool DefinedTypeResult::GetResult()
    {
        return result;
    }

    void DefinedTypeListResult::SetValue(std::vector<OmniPointer<DefinedType>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<DefinedType>> DefinedTypeListResult::GetValue()
    {
        return value;
    }

    void DefinedTypeListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool DefinedTypeListResult::GetResult()
    {
        return result;
    }

    void DefinedType::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string DefinedType::UnParse()
    {
        return length_string->GetString();
    }

    void DefinedType::SetName(OmniPointer<QualfiedName> input_value)
    {
        name_field = input_value;
    }

    OmniPointer<QualfiedName> DefinedType::GetName()
    {
        return name_field;
    }

    void SingletonTypeParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && primative_type_parser_instance->ParseSingleSave(index, primative_type_field))
        {
            instance->SetDefinedType(defined_type_field->GetValue());
            instance->SetPrimativeType(primative_type_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && defined_type_parser_instance->ParseSingleSave(index, defined_type_field))
        {
            instance->SetDefinedType(defined_type_field->GetValue());
            instance->SetPrimativeType(primative_type_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
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
        return ParseSingleSave(index, result);
    }

    bool SingletonTypeParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<SingletonTypeResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool SingletonTypeParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<SingletonTypeResult> result = std::shared_ptr<SingletonTypeResult>(new SingletonTypeResult());
        return ParseOptionalSave(index, result);
    }

    bool SingletonTypeParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<SingletonTypeListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<SingletonType>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<SingletonTypeResult> result = std::shared_ptr<SingletonTypeResult>(new SingletonTypeResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void SingletonTypeResult::SetValue(OmniPointer<SingletonType> new_value)
    {
        value = new_value;
    }

    OmniPointer<SingletonType> SingletonTypeResult::GetValue()
    {
        return value;
    }

    void SingletonTypeResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool SingletonTypeResult::GetResult()
    {
        return result;
    }

    void SingletonTypeListResult::SetValue(std::vector<OmniPointer<SingletonType>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<SingletonType>> SingletonTypeListResult::GetValue()
    {
        return value;
    }

    void SingletonTypeListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool SingletonTypeListResult::GetResult()
    {
        return result;
    }

    void SingletonType::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string SingletonType::UnParse()
    {
        return length_string->GetString();
    }

    void SingletonType::SetDefinedType(OmniPointer<DefinedType> input_value)
    {
        defined_type_field = input_value;
    }

    OmniPointer<DefinedType> SingletonType::GetDefinedType()
    {
        return defined_type_field;
    }

    void SingletonType::SetPrimativeType(OmniPointer<PrimativeType> input_value)
    {
        primative_type_field = input_value;
    }

    OmniPointer<PrimativeType> SingletonType::GetPrimativeType()
    {
        return primative_type_field;
    }

    void DimensionalNoteParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string("[")) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string("]")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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
        return ParseSingleSave(index, result);
    }

    bool DimensionalNoteParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<DimensionalNoteResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool DimensionalNoteParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<DimensionalNoteResult> result = std::shared_ptr<DimensionalNoteResult>(new DimensionalNoteResult());
        return ParseOptionalSave(index, result);
    }

    bool DimensionalNoteParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<DimensionalNoteListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<DimensionalNote>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<DimensionalNoteResult> result = std::shared_ptr<DimensionalNoteResult>(new DimensionalNoteResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void DimensionalNoteResult::SetValue(OmniPointer<DimensionalNote> new_value)
    {
        value = new_value;
    }

    OmniPointer<DimensionalNote> DimensionalNoteResult::GetValue()
    {
        return value;
    }

    void DimensionalNoteResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool DimensionalNoteResult::GetResult()
    {
        return result;
    }

    void DimensionalNoteListResult::SetValue(std::vector<OmniPointer<DimensionalNote>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<DimensionalNote>> DimensionalNoteListResult::GetValue()
    {
        return value;
    }

    void DimensionalNoteListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool DimensionalNoteListResult::GetResult()
    {
        return result;
    }

    void DimensionalNote::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string DimensionalNote::UnParse()
    {
        return length_string->GetString();
    }

    void DimensionalTypeParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && singleton_type_parser_instance->ParseSingleSave(index, singleton_type_field) && dimensional_note_parser_instance->ParseManySave(index, dimensional_note_field, 1, -1))
        {
            instance->SetDimensionalNote(dimensional_note_field->GetValue());
            instance->SetSingletonType(singleton_type_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
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
        return ParseSingleSave(index, result);
    }

    bool DimensionalTypeParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<DimensionalTypeResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool DimensionalTypeParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<DimensionalTypeResult> result = std::shared_ptr<DimensionalTypeResult>(new DimensionalTypeResult());
        return ParseOptionalSave(index, result);
    }

    bool DimensionalTypeParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<DimensionalTypeListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<DimensionalType>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<DimensionalTypeResult> result = std::shared_ptr<DimensionalTypeResult>(new DimensionalTypeResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void DimensionalTypeResult::SetValue(OmniPointer<DimensionalType> new_value)
    {
        value = new_value;
    }

    OmniPointer<DimensionalType> DimensionalTypeResult::GetValue()
    {
        return value;
    }

    void DimensionalTypeResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool DimensionalTypeResult::GetResult()
    {
        return result;
    }

    void DimensionalTypeListResult::SetValue(std::vector<OmniPointer<DimensionalType>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<DimensionalType>> DimensionalTypeListResult::GetValue()
    {
        return value;
    }

    void DimensionalTypeListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool DimensionalTypeListResult::GetResult()
    {
        return result;
    }

    void DimensionalType::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string DimensionalType::UnParse()
    {
        return length_string->GetString();
    }

    void DimensionalType::SetDimensionalNote(std::vector<OmniPointer<DimensionalNote>> input_value)
    {
        dimensional_note_field = input_value;
    }

    std::vector<OmniPointer<DimensionalNote>> DimensionalType::GetDimensionalNote()
    {
        return dimensional_note_field;
    }

    void DimensionalType::SetSingletonType(OmniPointer<SingletonType> input_value)
    {
        singleton_type_field = input_value;
    }

    OmniPointer<SingletonType> DimensionalType::GetSingletonType()
    {
        return singleton_type_field;
    }

    void MapNoteParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string("{")) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string("}")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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
        return ParseSingleSave(index, result);
    }

    bool MapNoteParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<MapNoteResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool MapNoteParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<MapNoteResult> result = std::shared_ptr<MapNoteResult>(new MapNoteResult());
        return ParseOptionalSave(index, result);
    }

    bool MapNoteParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<MapNoteListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<MapNote>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<MapNoteResult> result = std::shared_ptr<MapNoteResult>(new MapNoteResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void MapNoteResult::SetValue(OmniPointer<MapNote> new_value)
    {
        value = new_value;
    }

    OmniPointer<MapNote> MapNoteResult::GetValue()
    {
        return value;
    }

    void MapNoteResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool MapNoteResult::GetResult()
    {
        return result;
    }

    void MapNoteListResult::SetValue(std::vector<OmniPointer<MapNote>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<MapNote>> MapNoteListResult::GetValue()
    {
        return value;
    }

    void MapNoteListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool MapNoteListResult::GetResult()
    {
        return result;
    }

    void MapNote::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string MapNote::UnParse()
    {
        return length_string->GetString();
    }

    void MapTypeParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && singleton_type_parser_instance->ParseSingleSave(index, singleton_type_field) && map_note_parser_instance->ParseSingleSave(index, map_note_field))
        {
            instance->SetMapNote(map_note_field->GetValue());
            instance->SetSingletonType(singleton_type_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
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
        return ParseSingleSave(index, result);
    }

    bool MapTypeParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<MapTypeResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool MapTypeParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<MapTypeResult> result = std::shared_ptr<MapTypeResult>(new MapTypeResult());
        return ParseOptionalSave(index, result);
    }

    bool MapTypeParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<MapTypeListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<MapType>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<MapTypeResult> result = std::shared_ptr<MapTypeResult>(new MapTypeResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void MapTypeResult::SetValue(OmniPointer<MapType> new_value)
    {
        value = new_value;
    }

    OmniPointer<MapType> MapTypeResult::GetValue()
    {
        return value;
    }

    void MapTypeResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool MapTypeResult::GetResult()
    {
        return result;
    }

    void MapTypeListResult::SetValue(std::vector<OmniPointer<MapType>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<MapType>> MapTypeListResult::GetValue()
    {
        return value;
    }

    void MapTypeListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool MapTypeListResult::GetResult()
    {
        return result;
    }

    void MapType::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string MapType::UnParse()
    {
        return length_string->GetString();
    }

    void MapType::SetMapNote(OmniPointer<MapNote> input_value)
    {
        map_note_field = input_value;
    }

    OmniPointer<MapNote> MapType::GetMapNote()
    {
        return map_note_field;
    }

    void MapType::SetSingletonType(OmniPointer<SingletonType> input_value)
    {
        singleton_type_field = input_value;
    }

    OmniPointer<SingletonType> MapType::GetSingletonType()
    {
        return singleton_type_field;
    }

    void ValueTypeParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<DimensionalTypeResult> dimensional_type_field = std::shared_ptr<DimensionalTypeResult>(new DimensionalTypeResult());
        OmniPointer<MapTypeResult> map_type_field = std::shared_ptr<MapTypeResult>(new MapTypeResult());
        OmniPointer<SingletonTypeResult> singleton_type_field = std::shared_ptr<SingletonTypeResult>(new SingletonTypeResult());
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && dimensional_type_parser_instance->ParseSingleSave(index, dimensional_type_field))
        {
            instance->SetDimensionalType(dimensional_type_field->GetValue());
            instance->SetMapType(map_type_field->GetValue());
            instance->SetSingletonType(singleton_type_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            dimensional_type_field = std::shared_ptr<DimensionalTypeResult>(new DimensionalTypeResult());
            map_type_field = std::shared_ptr<MapTypeResult>(new MapTypeResult());
            singleton_type_field = std::shared_ptr<SingletonTypeResult>(new SingletonTypeResult());
        }

        if (true && map_type_parser_instance->ParseSingleSave(index, map_type_field))
        {
            instance->SetDimensionalType(dimensional_type_field->GetValue());
            instance->SetMapType(map_type_field->GetValue());
            instance->SetSingletonType(singleton_type_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            dimensional_type_field = std::shared_ptr<DimensionalTypeResult>(new DimensionalTypeResult());
            map_type_field = std::shared_ptr<MapTypeResult>(new MapTypeResult());
            singleton_type_field = std::shared_ptr<SingletonTypeResult>(new SingletonTypeResult());
        }

        if (true && singleton_type_parser_instance->ParseSingleSave(index, singleton_type_field))
        {
            instance->SetDimensionalType(dimensional_type_field->GetValue());
            instance->SetMapType(map_type_field->GetValue());
            instance->SetSingletonType(singleton_type_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            dimensional_type_field = std::shared_ptr<DimensionalTypeResult>(new DimensionalTypeResult());
            map_type_field = std::shared_ptr<MapTypeResult>(new MapTypeResult());
            singleton_type_field = std::shared_ptr<SingletonTypeResult>(new SingletonTypeResult());
        }

        result->SetResult(false);
        return result->GetResult();
    }

    bool ValueTypeParser::ParseSingle(OmniPointer<LengthString> index)
    {
        OmniPointer<ValueTypeResult> result = std::shared_ptr<ValueTypeResult>(new ValueTypeResult());
        return ParseSingleSave(index, result);
    }

    bool ValueTypeParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ValueTypeResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool ValueTypeParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<ValueTypeResult> result = std::shared_ptr<ValueTypeResult>(new ValueTypeResult());
        return ParseOptionalSave(index, result);
    }

    bool ValueTypeParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<ValueTypeListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<ValueType>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<ValueTypeResult> result = std::shared_ptr<ValueTypeResult>(new ValueTypeResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void ValueTypeResult::SetValue(OmniPointer<ValueType> new_value)
    {
        value = new_value;
    }

    OmniPointer<ValueType> ValueTypeResult::GetValue()
    {
        return value;
    }

    void ValueTypeResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool ValueTypeResult::GetResult()
    {
        return result;
    }

    void ValueTypeListResult::SetValue(std::vector<OmniPointer<ValueType>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<ValueType>> ValueTypeListResult::GetValue()
    {
        return value;
    }

    void ValueTypeListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool ValueTypeListResult::GetResult()
    {
        return result;
    }

    void ValueType::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string ValueType::UnParse()
    {
        return length_string->GetString();
    }

    void ValueType::SetDimensionalType(OmniPointer<DimensionalType> input_value)
    {
        dimensional_type_field = input_value;
    }

    OmniPointer<DimensionalType> ValueType::GetDimensionalType()
    {
        return dimensional_type_field;
    }

    void ValueType::SetMapType(OmniPointer<MapType> input_value)
    {
        map_type_field = input_value;
    }

    OmniPointer<MapType> ValueType::GetMapType()
    {
        return map_type_field;
    }

    void ValueType::SetSingletonType(OmniPointer<SingletonType> input_value)
    {
        singleton_type_field = input_value;
    }

    OmniPointer<SingletonType> ValueType::GetSingletonType()
    {
        return singleton_type_field;
    }

    void ParameterListDefParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<NameResult> name_field = std::shared_ptr<NameResult>(new NameResult());
        OmniPointer<ParameterListDefResult> parameter_tail_field = std::shared_ptr<ParameterListDefResult>(new ParameterListDefResult());
        OmniPointer<ValueTypeResult> type_field = std::shared_ptr<ValueTypeResult>(new ValueTypeResult());
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && value_type_parser_instance->ParseSingleSave(index, type_field) && whitespace_parser_instance->ParseMany(index, 1, -1) && name_parser_instance->ParseSingleSave(index, name_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string(",")) && whitespace_parser_instance->ParseMany(index, 0, -1) && parameter_list_def_parser_instance->ParseSingleSave(index, parameter_tail_field))
        {
            instance->SetName(name_field->GetValue());
            instance->SetParameterTail(parameter_tail_field->GetValue());
            instance->SetType(type_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
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
            parameter_tail_field = std::shared_ptr<ParameterListDefResult>(new ParameterListDefResult());
            type_field = std::shared_ptr<ValueTypeResult>(new ValueTypeResult());
        }

        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && value_type_parser_instance->ParseSingleSave(index, type_field) && whitespace_parser_instance->ParseMany(index, 1, -1) && name_parser_instance->ParseSingleSave(index, name_field) && whitespace_parser_instance->ParseMany(index, 0, -1))
        {
            instance->SetName(name_field->GetValue());
            instance->SetParameterTail(parameter_tail_field->GetValue());
            instance->SetType(type_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
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
            parameter_tail_field = std::shared_ptr<ParameterListDefResult>(new ParameterListDefResult());
            type_field = std::shared_ptr<ValueTypeResult>(new ValueTypeResult());
        }

        result->SetResult(false);
        return result->GetResult();
    }

    bool ParameterListDefParser::ParseSingle(OmniPointer<LengthString> index)
    {
        OmniPointer<ParameterListDefResult> result = std::shared_ptr<ParameterListDefResult>(new ParameterListDefResult());
        return ParseSingleSave(index, result);
    }

    bool ParameterListDefParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ParameterListDefResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool ParameterListDefParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<ParameterListDefResult> result = std::shared_ptr<ParameterListDefResult>(new ParameterListDefResult());
        return ParseOptionalSave(index, result);
    }

    bool ParameterListDefParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<ParameterListDefListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<ParameterListDef>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<ParameterListDefResult> result = std::shared_ptr<ParameterListDefResult>(new ParameterListDefResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void ParameterListDefResult::SetValue(OmniPointer<ParameterListDef> new_value)
    {
        value = new_value;
    }

    OmniPointer<ParameterListDef> ParameterListDefResult::GetValue()
    {
        return value;
    }

    void ParameterListDefResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool ParameterListDefResult::GetResult()
    {
        return result;
    }

    void ParameterListDefListResult::SetValue(std::vector<OmniPointer<ParameterListDef>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<ParameterListDef>> ParameterListDefListResult::GetValue()
    {
        return value;
    }

    void ParameterListDefListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool ParameterListDefListResult::GetResult()
    {
        return result;
    }

    void ParameterListDef::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string ParameterListDef::UnParse()
    {
        return length_string->GetString();
    }

    void ParameterListDef::SetName(OmniPointer<Name> input_value)
    {
        name_field = input_value;
    }

    OmniPointer<Name> ParameterListDef::GetName()
    {
        return name_field;
    }

    void ParameterListDef::SetParameterTail(OmniPointer<ParameterListDef> input_value)
    {
        parameter_tail_field = input_value;
    }

    OmniPointer<ParameterListDef> ParameterListDef::GetParameterTail()
    {
        return parameter_tail_field;
    }

    void ParameterListDef::SetType(OmniPointer<ValueType> input_value)
    {
        type_field = input_value;
    }

    OmniPointer<ValueType> ParameterListDef::GetType()
    {
        return type_field;
    }

    void ParameterListParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<RValueResult> rvalue_field = std::shared_ptr<RValueResult>(new RValueResult());
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && r_value_parser_instance->ParseSingleSave(index, rvalue_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string(",")) && whitespace_parser_instance->ParseMany(index, 0, -1) && parameter_list_parser_instance->ParseSingleSave(index, parameter_tail_field))
        {
            instance->SetParameterTail(parameter_tail_field->GetValue());
            instance->SetRvalue(rvalue_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
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
            rvalue_field = std::shared_ptr<RValueResult>(new RValueResult());
        }

        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && r_value_parser_instance->ParseSingleSave(index, rvalue_field) && whitespace_parser_instance->ParseMany(index, 0, -1))
        {
            instance->SetParameterTail(parameter_tail_field->GetValue());
            instance->SetRvalue(rvalue_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
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
            rvalue_field = std::shared_ptr<RValueResult>(new RValueResult());
        }

        result->SetResult(false);
        return result->GetResult();
    }

    bool ParameterListParser::ParseSingle(OmniPointer<LengthString> index)
    {
        OmniPointer<ParameterListResult> result = std::shared_ptr<ParameterListResult>(new ParameterListResult());
        return ParseSingleSave(index, result);
    }

    bool ParameterListParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ParameterListResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool ParameterListParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<ParameterListResult> result = std::shared_ptr<ParameterListResult>(new ParameterListResult());
        return ParseOptionalSave(index, result);
    }

    bool ParameterListParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<ParameterListListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<ParameterList>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<ParameterListResult> result = std::shared_ptr<ParameterListResult>(new ParameterListResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void ParameterListResult::SetValue(OmniPointer<ParameterList> new_value)
    {
        value = new_value;
    }

    OmniPointer<ParameterList> ParameterListResult::GetValue()
    {
        return value;
    }

    void ParameterListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool ParameterListResult::GetResult()
    {
        return result;
    }

    void ParameterListListResult::SetValue(std::vector<OmniPointer<ParameterList>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<ParameterList>> ParameterListListResult::GetValue()
    {
        return value;
    }

    void ParameterListListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool ParameterListListResult::GetResult()
    {
        return result;
    }

    void ParameterList::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string ParameterList::UnParse()
    {
        return length_string->GetString();
    }

    void ParameterList::SetParameterTail(OmniPointer<ParameterList> input_value)
    {
        parameter_tail_field = input_value;
    }

    OmniPointer<ParameterList> ParameterList::GetParameterTail()
    {
        return parameter_tail_field;
    }

    void ParameterList::SetRvalue(OmniPointer<RValue> input_value)
    {
        rvalue_field = input_value;
    }

    OmniPointer<RValue> ParameterList::GetRvalue()
    {
        return rvalue_field;
    }

    void CodeBlockParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string("{")) && whitespace_parser_instance->ParseMany(index, 0, -1) && instruction_parser_instance->ParseManySave(index, instructions_field, 0, -1) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string("}")) && whitespace_parser_instance->ParseMany(index, 0, -1))
        {
            instance->SetInstructions(instructions_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
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
        return ParseSingleSave(index, result);
    }

    bool CodeBlockParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<CodeBlockResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool CodeBlockParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<CodeBlockResult> result = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
        return ParseOptionalSave(index, result);
    }

    bool CodeBlockParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<CodeBlockListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<CodeBlock>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<CodeBlockResult> result = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void CodeBlockResult::SetValue(OmniPointer<CodeBlock> new_value)
    {
        value = new_value;
    }

    OmniPointer<CodeBlock> CodeBlockResult::GetValue()
    {
        return value;
    }

    void CodeBlockResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool CodeBlockResult::GetResult()
    {
        return result;
    }

    void CodeBlockListResult::SetValue(std::vector<OmniPointer<CodeBlock>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<CodeBlock>> CodeBlockListResult::GetValue()
    {
        return value;
    }

    void CodeBlockListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool CodeBlockListResult::GetResult()
    {
        return result;
    }

    void CodeBlock::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string CodeBlock::UnParse()
    {
        return length_string->GetString();
    }

    void CodeBlock::SetInstructions(std::vector<OmniPointer<Instruction>> input_value)
    {
        instructions_field = input_value;
    }

    std::vector<OmniPointer<Instruction>> CodeBlock::GetInstructions()
    {
        return instructions_field;
    }

    void DeclarationAssignParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<RValueResult> rvalue_field = std::shared_ptr<RValueResult>(new RValueResult());
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string("=")) && whitespace_parser_instance->ParseMany(index, 0, -1) && r_value_parser_instance->ParseSingleSave(index, rvalue_field) && whitespace_parser_instance->ParseMany(index, 0, -1))
        {
            instance->SetRvalue(rvalue_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            rvalue_field = std::shared_ptr<RValueResult>(new RValueResult());
        }

        result->SetResult(false);
        return result->GetResult();
    }

    bool DeclarationAssignParser::ParseSingle(OmniPointer<LengthString> index)
    {
        OmniPointer<DeclarationAssignResult> result = std::shared_ptr<DeclarationAssignResult>(new DeclarationAssignResult());
        return ParseSingleSave(index, result);
    }

    bool DeclarationAssignParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<DeclarationAssignResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool DeclarationAssignParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<DeclarationAssignResult> result = std::shared_ptr<DeclarationAssignResult>(new DeclarationAssignResult());
        return ParseOptionalSave(index, result);
    }

    bool DeclarationAssignParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<DeclarationAssignListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<DeclarationAssign>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<DeclarationAssignResult> result = std::shared_ptr<DeclarationAssignResult>(new DeclarationAssignResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void DeclarationAssignResult::SetValue(OmniPointer<DeclarationAssign> new_value)
    {
        value = new_value;
    }

    OmniPointer<DeclarationAssign> DeclarationAssignResult::GetValue()
    {
        return value;
    }

    void DeclarationAssignResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool DeclarationAssignResult::GetResult()
    {
        return result;
    }

    void DeclarationAssignListResult::SetValue(std::vector<OmniPointer<DeclarationAssign>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<DeclarationAssign>> DeclarationAssignListResult::GetValue()
    {
        return value;
    }

    void DeclarationAssignListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool DeclarationAssignListResult::GetResult()
    {
        return result;
    }

    void DeclarationAssign::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string DeclarationAssign::UnParse()
    {
        return length_string->GetString();
    }

    void DeclarationAssign::SetRvalue(OmniPointer<RValue> input_value)
    {
        rvalue_field = input_value;
    }

    OmniPointer<RValue> DeclarationAssign::GetRvalue()
    {
        return rvalue_field;
    }

    void DeclarationParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<DeclarationAssignResult> assignment_field = std::shared_ptr<DeclarationAssignResult>(new DeclarationAssignResult());
        OmniPointer<NameResult> name_field = std::shared_ptr<NameResult>(new NameResult());
        OmniPointer<ValueTypeResult> type_field = std::shared_ptr<ValueTypeResult>(new ValueTypeResult());
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && value_type_parser_instance->ParseSingleSave(index, type_field) && whitespace_parser_instance->ParseMany(index, 1, -1) && name_parser_instance->ParseSingleSave(index, name_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && declaration_assign_parser_instance->ParseOptionalSave(index, assignment_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string(";")) && whitespace_parser_instance->ParseMany(index, 0, -1))
        {
            instance->SetAssignment(assignment_field->GetValue());
            instance->SetName(name_field->GetValue());
            instance->SetType(type_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            assignment_field = std::shared_ptr<DeclarationAssignResult>(new DeclarationAssignResult());
            name_field = std::shared_ptr<NameResult>(new NameResult());
            type_field = std::shared_ptr<ValueTypeResult>(new ValueTypeResult());
        }

        result->SetResult(false);
        return result->GetResult();
    }

    bool DeclarationParser::ParseSingle(OmniPointer<LengthString> index)
    {
        OmniPointer<DeclarationResult> result = std::shared_ptr<DeclarationResult>(new DeclarationResult());
        return ParseSingleSave(index, result);
    }

    bool DeclarationParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<DeclarationResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool DeclarationParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<DeclarationResult> result = std::shared_ptr<DeclarationResult>(new DeclarationResult());
        return ParseOptionalSave(index, result);
    }

    bool DeclarationParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<DeclarationListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<Declaration>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<DeclarationResult> result = std::shared_ptr<DeclarationResult>(new DeclarationResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void DeclarationResult::SetValue(OmniPointer<Declaration> new_value)
    {
        value = new_value;
    }

    OmniPointer<Declaration> DeclarationResult::GetValue()
    {
        return value;
    }

    void DeclarationResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool DeclarationResult::GetResult()
    {
        return result;
    }

    void DeclarationListResult::SetValue(std::vector<OmniPointer<Declaration>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<Declaration>> DeclarationListResult::GetValue()
    {
        return value;
    }

    void DeclarationListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool DeclarationListResult::GetResult()
    {
        return result;
    }

    void Declaration::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string Declaration::UnParse()
    {
        return length_string->GetString();
    }

    void Declaration::SetAssignment(OmniPointer<DeclarationAssign> input_value)
    {
        assignment_field = input_value;
    }

    OmniPointer<DeclarationAssign> Declaration::GetAssignment()
    {
        return assignment_field;
    }

    void Declaration::SetName(OmniPointer<Name> input_value)
    {
        name_field = input_value;
    }

    OmniPointer<Name> Declaration::GetName()
    {
        return name_field;
    }

    void Declaration::SetType(OmniPointer<ValueType> input_value)
    {
        type_field = input_value;
    }

    OmniPointer<ValueType> Declaration::GetType()
    {
        return type_field;
    }

    void AssignmentParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<NameResult> lvalue_field = std::shared_ptr<NameResult>(new NameResult());
        OmniPointer<RValueResult> rvalue_field = std::shared_ptr<RValueResult>(new RValueResult());
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && name_parser_instance->ParseSingleSave(index, lvalue_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string("=")) && whitespace_parser_instance->ParseMany(index, 0, -1) && r_value_parser_instance->ParseSingleSave(index, rvalue_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string(";")) && whitespace_parser_instance->ParseMany(index, 0, -1))
        {
            instance->SetLvalue(lvalue_field->GetValue());
            instance->SetRvalue(rvalue_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            lvalue_field = std::shared_ptr<NameResult>(new NameResult());
            rvalue_field = std::shared_ptr<RValueResult>(new RValueResult());
        }

        result->SetResult(false);
        return result->GetResult();
    }

    bool AssignmentParser::ParseSingle(OmniPointer<LengthString> index)
    {
        OmniPointer<AssignmentResult> result = std::shared_ptr<AssignmentResult>(new AssignmentResult());
        return ParseSingleSave(index, result);
    }

    bool AssignmentParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<AssignmentResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool AssignmentParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<AssignmentResult> result = std::shared_ptr<AssignmentResult>(new AssignmentResult());
        return ParseOptionalSave(index, result);
    }

    bool AssignmentParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<AssignmentListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<Assignment>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<AssignmentResult> result = std::shared_ptr<AssignmentResult>(new AssignmentResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void AssignmentResult::SetValue(OmniPointer<Assignment> new_value)
    {
        value = new_value;
    }

    OmniPointer<Assignment> AssignmentResult::GetValue()
    {
        return value;
    }

    void AssignmentResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool AssignmentResult::GetResult()
    {
        return result;
    }

    void AssignmentListResult::SetValue(std::vector<OmniPointer<Assignment>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<Assignment>> AssignmentListResult::GetValue()
    {
        return value;
    }

    void AssignmentListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool AssignmentListResult::GetResult()
    {
        return result;
    }

    void Assignment::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string Assignment::UnParse()
    {
        return length_string->GetString();
    }

    void Assignment::SetLvalue(OmniPointer<Name> input_value)
    {
        lvalue_field = input_value;
    }

    OmniPointer<Name> Assignment::GetLvalue()
    {
        return lvalue_field;
    }

    void Assignment::SetRvalue(OmniPointer<RValue> input_value)
    {
        rvalue_field = input_value;
    }

    OmniPointer<RValue> Assignment::GetRvalue()
    {
        return rvalue_field;
    }

    void ReturnParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<StringResult> rtn_field = std::shared_ptr<StringResult>(new StringResult());
        OmniPointer<RValueResult> rvalue_field = std::shared_ptr<RValueResult>(new RValueResult());
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingleSave(index, std::string("return"), rtn_field) && whitespace_parser_instance->ParseMany(index, 1, -1) && r_value_parser_instance->ParseSingleSave(index, rvalue_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string(";")) && whitespace_parser_instance->ParseMany(index, 0, -1))
        {
            instance->SetRtn(rtn_field->GetValue());
            instance->SetRvalue(rvalue_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            rtn_field = std::shared_ptr<StringResult>(new StringResult());
            rvalue_field = std::shared_ptr<RValueResult>(new RValueResult());
        }

        result->SetResult(false);
        return result->GetResult();
    }

    bool ReturnParser::ParseSingle(OmniPointer<LengthString> index)
    {
        OmniPointer<ReturnResult> result = std::shared_ptr<ReturnResult>(new ReturnResult());
        return ParseSingleSave(index, result);
    }

    bool ReturnParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ReturnResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool ReturnParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<ReturnResult> result = std::shared_ptr<ReturnResult>(new ReturnResult());
        return ParseOptionalSave(index, result);
    }

    bool ReturnParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<ReturnListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<Return>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<ReturnResult> result = std::shared_ptr<ReturnResult>(new ReturnResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void ReturnResult::SetValue(OmniPointer<Return> new_value)
    {
        value = new_value;
    }

    OmniPointer<Return> ReturnResult::GetValue()
    {
        return value;
    }

    void ReturnResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool ReturnResult::GetResult()
    {
        return result;
    }

    void ReturnListResult::SetValue(std::vector<OmniPointer<Return>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<Return>> ReturnListResult::GetValue()
    {
        return value;
    }

    void ReturnListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool ReturnListResult::GetResult()
    {
        return result;
    }

    void Return::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string Return::UnParse()
    {
        return length_string->GetString();
    }

    void Return::SetRtn(OmniPointer<String> input_value)
    {
        rtn_field = input_value;
    }

    OmniPointer<String> Return::GetRtn()
    {
        return rtn_field;
    }

    void Return::SetRvalue(OmniPointer<RValue> input_value)
    {
        rvalue_field = input_value;
    }

    OmniPointer<RValue> Return::GetRvalue()
    {
        return rvalue_field;
    }

    void ElseTailParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingleSave(index, std::string("else"), else_key_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && code_block_parser_instance->ParseSingleSave(index, code_block_field) && whitespace_parser_instance->ParseMany(index, 0, -1))
        {
            instance->SetCodeBlock(code_block_field->GetValue());
            instance->SetElseKey(else_key_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
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
        return ParseSingleSave(index, result);
    }

    bool ElseTailParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ElseTailResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool ElseTailParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<ElseTailResult> result = std::shared_ptr<ElseTailResult>(new ElseTailResult());
        return ParseOptionalSave(index, result);
    }

    bool ElseTailParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<ElseTailListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<ElseTail>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<ElseTailResult> result = std::shared_ptr<ElseTailResult>(new ElseTailResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void ElseTailResult::SetValue(OmniPointer<ElseTail> new_value)
    {
        value = new_value;
    }

    OmniPointer<ElseTail> ElseTailResult::GetValue()
    {
        return value;
    }

    void ElseTailResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool ElseTailResult::GetResult()
    {
        return result;
    }

    void ElseTailListResult::SetValue(std::vector<OmniPointer<ElseTail>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<ElseTail>> ElseTailListResult::GetValue()
    {
        return value;
    }

    void ElseTailListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool ElseTailListResult::GetResult()
    {
        return result;
    }

    void ElseTail::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string ElseTail::UnParse()
    {
        return length_string->GetString();
    }

    void ElseTail::SetCodeBlock(OmniPointer<CodeBlock> input_value)
    {
        code_block_field = input_value;
    }

    OmniPointer<CodeBlock> ElseTail::GetCodeBlock()
    {
        return code_block_field;
    }

    void ElseTail::SetElseKey(OmniPointer<String> input_value)
    {
        else_key_field = input_value;
    }

    OmniPointer<String> ElseTail::GetElseKey()
    {
        return else_key_field;
    }

    void ConditionalParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CodeBlockResult> code_block_field = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
        OmniPointer<StringResult> conditional_key_field = std::shared_ptr<StringResult>(new StringResult());
        OmniPointer<ElseTailResult> else_tail_field = std::shared_ptr<ElseTailResult>(new ElseTailResult());
        OmniPointer<RValueResult> rvalue_field = std::shared_ptr<RValueResult>(new RValueResult());
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingleSave(index, std::string("if"), conditional_key_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string("(")) && whitespace_parser_instance->ParseMany(index, 0, -1) && r_value_parser_instance->ParseSingleSave(index, rvalue_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string(")")) && whitespace_parser_instance->ParseMany(index, 0, -1) && code_block_parser_instance->ParseSingleSave(index, code_block_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && else_tail_parser_instance->ParseOptionalSave(index, else_tail_field))
        {
            instance->SetCodeBlock(code_block_field->GetValue());
            instance->SetConditionalKey(conditional_key_field->GetValue());
            instance->SetElseTail(else_tail_field->GetValue());
            instance->SetRvalue(rvalue_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
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
            conditional_key_field = std::shared_ptr<StringResult>(new StringResult());
            else_tail_field = std::shared_ptr<ElseTailResult>(new ElseTailResult());
            rvalue_field = std::shared_ptr<RValueResult>(new RValueResult());
        }

        result->SetResult(false);
        return result->GetResult();
    }

    bool ConditionalParser::ParseSingle(OmniPointer<LengthString> index)
    {
        OmniPointer<ConditionalResult> result = std::shared_ptr<ConditionalResult>(new ConditionalResult());
        return ParseSingleSave(index, result);
    }

    bool ConditionalParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ConditionalResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool ConditionalParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<ConditionalResult> result = std::shared_ptr<ConditionalResult>(new ConditionalResult());
        return ParseOptionalSave(index, result);
    }

    bool ConditionalParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<ConditionalListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<Conditional>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<ConditionalResult> result = std::shared_ptr<ConditionalResult>(new ConditionalResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void ConditionalResult::SetValue(OmniPointer<Conditional> new_value)
    {
        value = new_value;
    }

    OmniPointer<Conditional> ConditionalResult::GetValue()
    {
        return value;
    }

    void ConditionalResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool ConditionalResult::GetResult()
    {
        return result;
    }

    void ConditionalListResult::SetValue(std::vector<OmniPointer<Conditional>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<Conditional>> ConditionalListResult::GetValue()
    {
        return value;
    }

    void ConditionalListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool ConditionalListResult::GetResult()
    {
        return result;
    }

    void Conditional::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string Conditional::UnParse()
    {
        return length_string->GetString();
    }

    void Conditional::SetCodeBlock(OmniPointer<CodeBlock> input_value)
    {
        code_block_field = input_value;
    }

    OmniPointer<CodeBlock> Conditional::GetCodeBlock()
    {
        return code_block_field;
    }

    void Conditional::SetConditionalKey(OmniPointer<String> input_value)
    {
        conditional_key_field = input_value;
    }

    OmniPointer<String> Conditional::GetConditionalKey()
    {
        return conditional_key_field;
    }

    void Conditional::SetElseTail(OmniPointer<ElseTail> input_value)
    {
        else_tail_field = input_value;
    }

    OmniPointer<ElseTail> Conditional::GetElseTail()
    {
        return else_tail_field;
    }

    void Conditional::SetRvalue(OmniPointer<RValue> input_value)
    {
        rvalue_field = input_value;
    }

    OmniPointer<RValue> Conditional::GetRvalue()
    {
        return rvalue_field;
    }

    void LoopParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<StringResult> loop_key_field = std::shared_ptr<StringResult>(new StringResult());
        OmniPointer<RValueResult> rvalue_field = std::shared_ptr<RValueResult>(new RValueResult());
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingleSave(index, std::string("while"), loop_key_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string("(")) && whitespace_parser_instance->ParseMany(index, 0, -1) && r_value_parser_instance->ParseSingleSave(index, rvalue_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string(")")) && whitespace_parser_instance->ParseMany(index, 0, -1) && code_block_parser_instance->ParseSingleSave(index, code_block_field) && whitespace_parser_instance->ParseMany(index, 0, -1))
        {
            instance->SetCodeBlock(code_block_field->GetValue());
            instance->SetLoopKey(loop_key_field->GetValue());
            instance->SetRvalue(rvalue_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
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
            loop_key_field = std::shared_ptr<StringResult>(new StringResult());
            rvalue_field = std::shared_ptr<RValueResult>(new RValueResult());
        }

        result->SetResult(false);
        return result->GetResult();
    }

    bool LoopParser::ParseSingle(OmniPointer<LengthString> index)
    {
        OmniPointer<LoopResult> result = std::shared_ptr<LoopResult>(new LoopResult());
        return ParseSingleSave(index, result);
    }

    bool LoopParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<LoopResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool LoopParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<LoopResult> result = std::shared_ptr<LoopResult>(new LoopResult());
        return ParseOptionalSave(index, result);
    }

    bool LoopParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<LoopListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<Loop>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<LoopResult> result = std::shared_ptr<LoopResult>(new LoopResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void LoopResult::SetValue(OmniPointer<Loop> new_value)
    {
        value = new_value;
    }

    OmniPointer<Loop> LoopResult::GetValue()
    {
        return value;
    }

    void LoopResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool LoopResult::GetResult()
    {
        return result;
    }

    void LoopListResult::SetValue(std::vector<OmniPointer<Loop>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<Loop>> LoopListResult::GetValue()
    {
        return value;
    }

    void LoopListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool LoopListResult::GetResult()
    {
        return result;
    }

    void Loop::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string Loop::UnParse()
    {
        return length_string->GetString();
    }

    void Loop::SetCodeBlock(OmniPointer<CodeBlock> input_value)
    {
        code_block_field = input_value;
    }

    OmniPointer<CodeBlock> Loop::GetCodeBlock()
    {
        return code_block_field;
    }

    void Loop::SetLoopKey(OmniPointer<String> input_value)
    {
        loop_key_field = input_value;
    }

    OmniPointer<String> Loop::GetLoopKey()
    {
        return loop_key_field;
    }

    void Loop::SetRvalue(OmniPointer<RValue> input_value)
    {
        rvalue_field = input_value;
    }

    OmniPointer<RValue> Loop::GetRvalue()
    {
        return rvalue_field;
    }

    void CallParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<NameResult> function_field = std::shared_ptr<NameResult>(new NameResult());
        OmniPointer<ParameterListResult> parameters_field = std::shared_ptr<ParameterListResult>(new ParameterListResult());
        OmniPointer<NameResult> variable_field = std::shared_ptr<NameResult>(new NameResult());
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && name_parser_instance->ParseSingleSave(index, variable_field) && string_parser_instance->ParseSingle(index, std::string(".")) && name_parser_instance->ParseSingleSave(index, function_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string("(")) && whitespace_parser_instance->ParseMany(index, 0, -1) && parameter_list_parser_instance->ParseOptionalSave(index, parameters_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string(")")) && whitespace_parser_instance->ParseMany(index, 0, -1))
        {
            instance->SetFunction(function_field->GetValue());
            instance->SetParameters(parameters_field->GetValue());
            instance->SetVariable(variable_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            function_field = std::shared_ptr<NameResult>(new NameResult());
            parameters_field = std::shared_ptr<ParameterListResult>(new ParameterListResult());
            variable_field = std::shared_ptr<NameResult>(new NameResult());
        }

        if (true && name_parser_instance->ParseSingleSave(index, function_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string("(")) && whitespace_parser_instance->ParseMany(index, 0, -1) && parameter_list_parser_instance->ParseOptionalSave(index, parameters_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string(")")) && whitespace_parser_instance->ParseMany(index, 0, -1))
        {
            instance->SetFunction(function_field->GetValue());
            instance->SetParameters(parameters_field->GetValue());
            instance->SetVariable(variable_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            function_field = std::shared_ptr<NameResult>(new NameResult());
            parameters_field = std::shared_ptr<ParameterListResult>(new ParameterListResult());
            variable_field = std::shared_ptr<NameResult>(new NameResult());
        }

        result->SetResult(false);
        return result->GetResult();
    }

    bool CallParser::ParseSingle(OmniPointer<LengthString> index)
    {
        OmniPointer<CallResult> result = std::shared_ptr<CallResult>(new CallResult());
        return ParseSingleSave(index, result);
    }

    bool CallParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<CallResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool CallParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<CallResult> result = std::shared_ptr<CallResult>(new CallResult());
        return ParseOptionalSave(index, result);
    }

    bool CallParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<CallListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<Call>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<CallResult> result = std::shared_ptr<CallResult>(new CallResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void CallResult::SetValue(OmniPointer<Call> new_value)
    {
        value = new_value;
    }

    OmniPointer<Call> CallResult::GetValue()
    {
        return value;
    }

    void CallResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool CallResult::GetResult()
    {
        return result;
    }

    void CallListResult::SetValue(std::vector<OmniPointer<Call>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<Call>> CallListResult::GetValue()
    {
        return value;
    }

    void CallListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool CallListResult::GetResult()
    {
        return result;
    }

    void Call::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string Call::UnParse()
    {
        return length_string->GetString();
    }

    void Call::SetFunction(OmniPointer<Name> input_value)
    {
        function_field = input_value;
    }

    OmniPointer<Name> Call::GetFunction()
    {
        return function_field;
    }

    void Call::SetParameters(OmniPointer<ParameterList> input_value)
    {
        parameters_field = input_value;
    }

    OmniPointer<ParameterList> Call::GetParameters()
    {
        return parameters_field;
    }

    void Call::SetVariable(OmniPointer<Name> input_value)
    {
        variable_field = input_value;
    }

    OmniPointer<Name> Call::GetVariable()
    {
        return variable_field;
    }

    void AllocateParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string("new")) && whitespace_parser_instance->ParseMany(index, 1, -1) && qualfied_name_parser_instance->ParseSingleSave(index, managed_type_field) && whitespace_parser_instance->ParseMany(index, 0, -1))
        {
            instance->SetManagedType(managed_type_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
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
        return ParseSingleSave(index, result);
    }

    bool AllocateParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<AllocateResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool AllocateParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<AllocateResult> result = std::shared_ptr<AllocateResult>(new AllocateResult());
        return ParseOptionalSave(index, result);
    }

    bool AllocateParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<AllocateListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<Allocate>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<AllocateResult> result = std::shared_ptr<AllocateResult>(new AllocateResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void AllocateResult::SetValue(OmniPointer<Allocate> new_value)
    {
        value = new_value;
    }

    OmniPointer<Allocate> AllocateResult::GetValue()
    {
        return value;
    }

    void AllocateResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool AllocateResult::GetResult()
    {
        return result;
    }

    void AllocateListResult::SetValue(std::vector<OmniPointer<Allocate>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<Allocate>> AllocateListResult::GetValue()
    {
        return value;
    }

    void AllocateListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool AllocateListResult::GetResult()
    {
        return result;
    }

    void Allocate::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string Allocate::UnParse()
    {
        return length_string->GetString();
    }

    void Allocate::SetManagedType(OmniPointer<QualfiedName> input_value)
    {
        managed_type_field = input_value;
    }

    OmniPointer<QualfiedName> Allocate::GetManagedType()
    {
        return managed_type_field;
    }

    void InstructionParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<AssignmentResult> assignment_field = std::shared_ptr<AssignmentResult>(new AssignmentResult());
        OmniPointer<CallResult> call_field = std::shared_ptr<CallResult>(new CallResult());
        OmniPointer<CodeBlockResult> code_block_field = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
        OmniPointer<CommentResult> comment_field = std::shared_ptr<CommentResult>(new CommentResult());
        OmniPointer<ConditionalResult> conditional_field = std::shared_ptr<ConditionalResult>(new ConditionalResult());
        OmniPointer<DeclarationResult> declaration_field = std::shared_ptr<DeclarationResult>(new DeclarationResult());
        OmniPointer<LoopResult> loop_field = std::shared_ptr<LoopResult>(new LoopResult());
        OmniPointer<ReturnResult> rtn_field = std::shared_ptr<ReturnResult>(new ReturnResult());
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && comment_parser_instance->ParseOptionalSave(index, comment_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && code_block_parser_instance->ParseSingleSave(index, code_block_field))
        {
            instance->SetAssignment(assignment_field->GetValue());
            instance->SetCall(call_field->GetValue());
            instance->SetCodeBlock(code_block_field->GetValue());
            instance->SetComment(comment_field->GetValue());
            instance->SetConditional(conditional_field->GetValue());
            instance->SetDeclaration(declaration_field->GetValue());
            instance->SetLoop(loop_field->GetValue());
            instance->SetRtn(rtn_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            assignment_field = std::shared_ptr<AssignmentResult>(new AssignmentResult());
            call_field = std::shared_ptr<CallResult>(new CallResult());
            code_block_field = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
            comment_field = std::shared_ptr<CommentResult>(new CommentResult());
            conditional_field = std::shared_ptr<ConditionalResult>(new ConditionalResult());
            declaration_field = std::shared_ptr<DeclarationResult>(new DeclarationResult());
            loop_field = std::shared_ptr<LoopResult>(new LoopResult());
            rtn_field = std::shared_ptr<ReturnResult>(new ReturnResult());
        }

        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && comment_parser_instance->ParseOptionalSave(index, comment_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && return_parser_instance->ParseSingleSave(index, rtn_field))
        {
            instance->SetAssignment(assignment_field->GetValue());
            instance->SetCall(call_field->GetValue());
            instance->SetCodeBlock(code_block_field->GetValue());
            instance->SetComment(comment_field->GetValue());
            instance->SetConditional(conditional_field->GetValue());
            instance->SetDeclaration(declaration_field->GetValue());
            instance->SetLoop(loop_field->GetValue());
            instance->SetRtn(rtn_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            assignment_field = std::shared_ptr<AssignmentResult>(new AssignmentResult());
            call_field = std::shared_ptr<CallResult>(new CallResult());
            code_block_field = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
            comment_field = std::shared_ptr<CommentResult>(new CommentResult());
            conditional_field = std::shared_ptr<ConditionalResult>(new ConditionalResult());
            declaration_field = std::shared_ptr<DeclarationResult>(new DeclarationResult());
            loop_field = std::shared_ptr<LoopResult>(new LoopResult());
            rtn_field = std::shared_ptr<ReturnResult>(new ReturnResult());
        }

        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && comment_parser_instance->ParseOptionalSave(index, comment_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && declaration_parser_instance->ParseSingleSave(index, declaration_field))
        {
            instance->SetAssignment(assignment_field->GetValue());
            instance->SetCall(call_field->GetValue());
            instance->SetCodeBlock(code_block_field->GetValue());
            instance->SetComment(comment_field->GetValue());
            instance->SetConditional(conditional_field->GetValue());
            instance->SetDeclaration(declaration_field->GetValue());
            instance->SetLoop(loop_field->GetValue());
            instance->SetRtn(rtn_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            assignment_field = std::shared_ptr<AssignmentResult>(new AssignmentResult());
            call_field = std::shared_ptr<CallResult>(new CallResult());
            code_block_field = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
            comment_field = std::shared_ptr<CommentResult>(new CommentResult());
            conditional_field = std::shared_ptr<ConditionalResult>(new ConditionalResult());
            declaration_field = std::shared_ptr<DeclarationResult>(new DeclarationResult());
            loop_field = std::shared_ptr<LoopResult>(new LoopResult());
            rtn_field = std::shared_ptr<ReturnResult>(new ReturnResult());
        }

        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && comment_parser_instance->ParseOptionalSave(index, comment_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && assignment_parser_instance->ParseSingleSave(index, assignment_field))
        {
            instance->SetAssignment(assignment_field->GetValue());
            instance->SetCall(call_field->GetValue());
            instance->SetCodeBlock(code_block_field->GetValue());
            instance->SetComment(comment_field->GetValue());
            instance->SetConditional(conditional_field->GetValue());
            instance->SetDeclaration(declaration_field->GetValue());
            instance->SetLoop(loop_field->GetValue());
            instance->SetRtn(rtn_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            assignment_field = std::shared_ptr<AssignmentResult>(new AssignmentResult());
            call_field = std::shared_ptr<CallResult>(new CallResult());
            code_block_field = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
            comment_field = std::shared_ptr<CommentResult>(new CommentResult());
            conditional_field = std::shared_ptr<ConditionalResult>(new ConditionalResult());
            declaration_field = std::shared_ptr<DeclarationResult>(new DeclarationResult());
            loop_field = std::shared_ptr<LoopResult>(new LoopResult());
            rtn_field = std::shared_ptr<ReturnResult>(new ReturnResult());
        }

        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && comment_parser_instance->ParseOptionalSave(index, comment_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && call_parser_instance->ParseSingleSave(index, call_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string(";")) && whitespace_parser_instance->ParseMany(index, 0, -1))
        {
            instance->SetAssignment(assignment_field->GetValue());
            instance->SetCall(call_field->GetValue());
            instance->SetCodeBlock(code_block_field->GetValue());
            instance->SetComment(comment_field->GetValue());
            instance->SetConditional(conditional_field->GetValue());
            instance->SetDeclaration(declaration_field->GetValue());
            instance->SetLoop(loop_field->GetValue());
            instance->SetRtn(rtn_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            assignment_field = std::shared_ptr<AssignmentResult>(new AssignmentResult());
            call_field = std::shared_ptr<CallResult>(new CallResult());
            code_block_field = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
            comment_field = std::shared_ptr<CommentResult>(new CommentResult());
            conditional_field = std::shared_ptr<ConditionalResult>(new ConditionalResult());
            declaration_field = std::shared_ptr<DeclarationResult>(new DeclarationResult());
            loop_field = std::shared_ptr<LoopResult>(new LoopResult());
            rtn_field = std::shared_ptr<ReturnResult>(new ReturnResult());
        }

        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && comment_parser_instance->ParseOptionalSave(index, comment_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && conditional_parser_instance->ParseSingleSave(index, conditional_field))
        {
            instance->SetAssignment(assignment_field->GetValue());
            instance->SetCall(call_field->GetValue());
            instance->SetCodeBlock(code_block_field->GetValue());
            instance->SetComment(comment_field->GetValue());
            instance->SetConditional(conditional_field->GetValue());
            instance->SetDeclaration(declaration_field->GetValue());
            instance->SetLoop(loop_field->GetValue());
            instance->SetRtn(rtn_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            assignment_field = std::shared_ptr<AssignmentResult>(new AssignmentResult());
            call_field = std::shared_ptr<CallResult>(new CallResult());
            code_block_field = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
            comment_field = std::shared_ptr<CommentResult>(new CommentResult());
            conditional_field = std::shared_ptr<ConditionalResult>(new ConditionalResult());
            declaration_field = std::shared_ptr<DeclarationResult>(new DeclarationResult());
            loop_field = std::shared_ptr<LoopResult>(new LoopResult());
            rtn_field = std::shared_ptr<ReturnResult>(new ReturnResult());
        }

        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && comment_parser_instance->ParseOptionalSave(index, comment_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && loop_parser_instance->ParseSingleSave(index, loop_field))
        {
            instance->SetAssignment(assignment_field->GetValue());
            instance->SetCall(call_field->GetValue());
            instance->SetCodeBlock(code_block_field->GetValue());
            instance->SetComment(comment_field->GetValue());
            instance->SetConditional(conditional_field->GetValue());
            instance->SetDeclaration(declaration_field->GetValue());
            instance->SetLoop(loop_field->GetValue());
            instance->SetRtn(rtn_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            assignment_field = std::shared_ptr<AssignmentResult>(new AssignmentResult());
            call_field = std::shared_ptr<CallResult>(new CallResult());
            code_block_field = std::shared_ptr<CodeBlockResult>(new CodeBlockResult());
            comment_field = std::shared_ptr<CommentResult>(new CommentResult());
            conditional_field = std::shared_ptr<ConditionalResult>(new ConditionalResult());
            declaration_field = std::shared_ptr<DeclarationResult>(new DeclarationResult());
            loop_field = std::shared_ptr<LoopResult>(new LoopResult());
            rtn_field = std::shared_ptr<ReturnResult>(new ReturnResult());
        }

        result->SetResult(false);
        return result->GetResult();
    }

    bool InstructionParser::ParseSingle(OmniPointer<LengthString> index)
    {
        OmniPointer<InstructionResult> result = std::shared_ptr<InstructionResult>(new InstructionResult());
        return ParseSingleSave(index, result);
    }

    bool InstructionParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<InstructionResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool InstructionParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<InstructionResult> result = std::shared_ptr<InstructionResult>(new InstructionResult());
        return ParseOptionalSave(index, result);
    }

    bool InstructionParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<InstructionListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<Instruction>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<InstructionResult> result = std::shared_ptr<InstructionResult>(new InstructionResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void InstructionResult::SetValue(OmniPointer<Instruction> new_value)
    {
        value = new_value;
    }

    OmniPointer<Instruction> InstructionResult::GetValue()
    {
        return value;
    }

    void InstructionResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool InstructionResult::GetResult()
    {
        return result;
    }

    void InstructionListResult::SetValue(std::vector<OmniPointer<Instruction>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<Instruction>> InstructionListResult::GetValue()
    {
        return value;
    }

    void InstructionListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool InstructionListResult::GetResult()
    {
        return result;
    }

    void Instruction::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string Instruction::UnParse()
    {
        return length_string->GetString();
    }

    void Instruction::SetAssignment(OmniPointer<Assignment> input_value)
    {
        assignment_field = input_value;
    }

    OmniPointer<Assignment> Instruction::GetAssignment()
    {
        return assignment_field;
    }

    void Instruction::SetCall(OmniPointer<Call> input_value)
    {
        call_field = input_value;
    }

    OmniPointer<Call> Instruction::GetCall()
    {
        return call_field;
    }

    void Instruction::SetCodeBlock(OmniPointer<CodeBlock> input_value)
    {
        code_block_field = input_value;
    }

    OmniPointer<CodeBlock> Instruction::GetCodeBlock()
    {
        return code_block_field;
    }

    void Instruction::SetComment(OmniPointer<Comment> input_value)
    {
        comment_field = input_value;
    }

    OmniPointer<Comment> Instruction::GetComment()
    {
        return comment_field;
    }

    void Instruction::SetConditional(OmniPointer<Conditional> input_value)
    {
        conditional_field = input_value;
    }

    OmniPointer<Conditional> Instruction::GetConditional()
    {
        return conditional_field;
    }

    void Instruction::SetDeclaration(OmniPointer<Declaration> input_value)
    {
        declaration_field = input_value;
    }

    OmniPointer<Declaration> Instruction::GetDeclaration()
    {
        return declaration_field;
    }

    void Instruction::SetLoop(OmniPointer<Loop> input_value)
    {
        loop_field = input_value;
    }

    OmniPointer<Loop> Instruction::GetLoop()
    {
        return loop_field;
    }

    void Instruction::SetRtn(OmniPointer<Return> input_value)
    {
        rtn_field = input_value;
    }

    OmniPointer<Return> Instruction::GetRtn()
    {
        return rtn_field;
    }

    void RValueSingleParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<AllocateResult> allocate_field = std::shared_ptr<AllocateResult>(new AllocateResult());
        OmniPointer<BooleanResult> boolean_literal_field = std::shared_ptr<BooleanResult>(new BooleanResult());
        OmniPointer<ByteResult> byte_literal_field = std::shared_ptr<ByteResult>(new ByteResult());
        OmniPointer<CallResult> call_field = std::shared_ptr<CallResult>(new CallResult());
        OmniPointer<DecimalResult> decimal_literal_field = std::shared_ptr<DecimalResult>(new DecimalResult());
        OmniPointer<NumberResult> integer_literal_field = std::shared_ptr<NumberResult>(new NumberResult());
        OmniPointer<LiteralResult> string_literal_field = std::shared_ptr<LiteralResult>(new LiteralResult());
        OmniPointer<UnaryOperatorResult> unary_operator_field = std::shared_ptr<UnaryOperatorResult>(new UnaryOperatorResult());
        OmniPointer<NameResult> variable_field = std::shared_ptr<NameResult>(new NameResult());
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && unary_operator_parser_instance->ParseOptionalSave(index, unary_operator_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && call_parser_instance->ParseSingleSave(index, call_field))
        {
            instance->SetAllocate(allocate_field->GetValue());
            instance->SetBooleanLiteral(boolean_literal_field->GetValue());
            instance->SetByteLiteral(byte_literal_field->GetValue());
            instance->SetCall(call_field->GetValue());
            instance->SetDecimalLiteral(decimal_literal_field->GetValue());
            instance->SetIntegerLiteral(integer_literal_field->GetValue());
            instance->SetStringLiteral(string_literal_field->GetValue());
            instance->SetUnaryOperator(unary_operator_field->GetValue());
            instance->SetVariable(variable_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            allocate_field = std::shared_ptr<AllocateResult>(new AllocateResult());
            boolean_literal_field = std::shared_ptr<BooleanResult>(new BooleanResult());
            byte_literal_field = std::shared_ptr<ByteResult>(new ByteResult());
            call_field = std::shared_ptr<CallResult>(new CallResult());
            decimal_literal_field = std::shared_ptr<DecimalResult>(new DecimalResult());
            integer_literal_field = std::shared_ptr<NumberResult>(new NumberResult());
            string_literal_field = std::shared_ptr<LiteralResult>(new LiteralResult());
            unary_operator_field = std::shared_ptr<UnaryOperatorResult>(new UnaryOperatorResult());
            variable_field = std::shared_ptr<NameResult>(new NameResult());
        }

        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && unary_operator_parser_instance->ParseOptionalSave(index, unary_operator_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && allocate_parser_instance->ParseSingleSave(index, allocate_field))
        {
            instance->SetAllocate(allocate_field->GetValue());
            instance->SetBooleanLiteral(boolean_literal_field->GetValue());
            instance->SetByteLiteral(byte_literal_field->GetValue());
            instance->SetCall(call_field->GetValue());
            instance->SetDecimalLiteral(decimal_literal_field->GetValue());
            instance->SetIntegerLiteral(integer_literal_field->GetValue());
            instance->SetStringLiteral(string_literal_field->GetValue());
            instance->SetUnaryOperator(unary_operator_field->GetValue());
            instance->SetVariable(variable_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            allocate_field = std::shared_ptr<AllocateResult>(new AllocateResult());
            boolean_literal_field = std::shared_ptr<BooleanResult>(new BooleanResult());
            byte_literal_field = std::shared_ptr<ByteResult>(new ByteResult());
            call_field = std::shared_ptr<CallResult>(new CallResult());
            decimal_literal_field = std::shared_ptr<DecimalResult>(new DecimalResult());
            integer_literal_field = std::shared_ptr<NumberResult>(new NumberResult());
            string_literal_field = std::shared_ptr<LiteralResult>(new LiteralResult());
            unary_operator_field = std::shared_ptr<UnaryOperatorResult>(new UnaryOperatorResult());
            variable_field = std::shared_ptr<NameResult>(new NameResult());
        }

        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && unary_operator_parser_instance->ParseOptionalSave(index, unary_operator_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && byte_parser_instance->ParseSingleSave(index, byte_literal_field))
        {
            instance->SetAllocate(allocate_field->GetValue());
            instance->SetBooleanLiteral(boolean_literal_field->GetValue());
            instance->SetByteLiteral(byte_literal_field->GetValue());
            instance->SetCall(call_field->GetValue());
            instance->SetDecimalLiteral(decimal_literal_field->GetValue());
            instance->SetIntegerLiteral(integer_literal_field->GetValue());
            instance->SetStringLiteral(string_literal_field->GetValue());
            instance->SetUnaryOperator(unary_operator_field->GetValue());
            instance->SetVariable(variable_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            allocate_field = std::shared_ptr<AllocateResult>(new AllocateResult());
            boolean_literal_field = std::shared_ptr<BooleanResult>(new BooleanResult());
            byte_literal_field = std::shared_ptr<ByteResult>(new ByteResult());
            call_field = std::shared_ptr<CallResult>(new CallResult());
            decimal_literal_field = std::shared_ptr<DecimalResult>(new DecimalResult());
            integer_literal_field = std::shared_ptr<NumberResult>(new NumberResult());
            string_literal_field = std::shared_ptr<LiteralResult>(new LiteralResult());
            unary_operator_field = std::shared_ptr<UnaryOperatorResult>(new UnaryOperatorResult());
            variable_field = std::shared_ptr<NameResult>(new NameResult());
        }

        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && unary_operator_parser_instance->ParseOptionalSave(index, unary_operator_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && decimal_parser_instance->ParseSingleSave(index, decimal_literal_field))
        {
            instance->SetAllocate(allocate_field->GetValue());
            instance->SetBooleanLiteral(boolean_literal_field->GetValue());
            instance->SetByteLiteral(byte_literal_field->GetValue());
            instance->SetCall(call_field->GetValue());
            instance->SetDecimalLiteral(decimal_literal_field->GetValue());
            instance->SetIntegerLiteral(integer_literal_field->GetValue());
            instance->SetStringLiteral(string_literal_field->GetValue());
            instance->SetUnaryOperator(unary_operator_field->GetValue());
            instance->SetVariable(variable_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            allocate_field = std::shared_ptr<AllocateResult>(new AllocateResult());
            boolean_literal_field = std::shared_ptr<BooleanResult>(new BooleanResult());
            byte_literal_field = std::shared_ptr<ByteResult>(new ByteResult());
            call_field = std::shared_ptr<CallResult>(new CallResult());
            decimal_literal_field = std::shared_ptr<DecimalResult>(new DecimalResult());
            integer_literal_field = std::shared_ptr<NumberResult>(new NumberResult());
            string_literal_field = std::shared_ptr<LiteralResult>(new LiteralResult());
            unary_operator_field = std::shared_ptr<UnaryOperatorResult>(new UnaryOperatorResult());
            variable_field = std::shared_ptr<NameResult>(new NameResult());
        }

        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && unary_operator_parser_instance->ParseOptionalSave(index, unary_operator_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && number_parser_instance->ParseSingleSave(index, integer_literal_field))
        {
            instance->SetAllocate(allocate_field->GetValue());
            instance->SetBooleanLiteral(boolean_literal_field->GetValue());
            instance->SetByteLiteral(byte_literal_field->GetValue());
            instance->SetCall(call_field->GetValue());
            instance->SetDecimalLiteral(decimal_literal_field->GetValue());
            instance->SetIntegerLiteral(integer_literal_field->GetValue());
            instance->SetStringLiteral(string_literal_field->GetValue());
            instance->SetUnaryOperator(unary_operator_field->GetValue());
            instance->SetVariable(variable_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            allocate_field = std::shared_ptr<AllocateResult>(new AllocateResult());
            boolean_literal_field = std::shared_ptr<BooleanResult>(new BooleanResult());
            byte_literal_field = std::shared_ptr<ByteResult>(new ByteResult());
            call_field = std::shared_ptr<CallResult>(new CallResult());
            decimal_literal_field = std::shared_ptr<DecimalResult>(new DecimalResult());
            integer_literal_field = std::shared_ptr<NumberResult>(new NumberResult());
            string_literal_field = std::shared_ptr<LiteralResult>(new LiteralResult());
            unary_operator_field = std::shared_ptr<UnaryOperatorResult>(new UnaryOperatorResult());
            variable_field = std::shared_ptr<NameResult>(new NameResult());
        }

        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && unary_operator_parser_instance->ParseOptionalSave(index, unary_operator_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && boolean_parser_instance->ParseSingleSave(index, boolean_literal_field))
        {
            instance->SetAllocate(allocate_field->GetValue());
            instance->SetBooleanLiteral(boolean_literal_field->GetValue());
            instance->SetByteLiteral(byte_literal_field->GetValue());
            instance->SetCall(call_field->GetValue());
            instance->SetDecimalLiteral(decimal_literal_field->GetValue());
            instance->SetIntegerLiteral(integer_literal_field->GetValue());
            instance->SetStringLiteral(string_literal_field->GetValue());
            instance->SetUnaryOperator(unary_operator_field->GetValue());
            instance->SetVariable(variable_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            allocate_field = std::shared_ptr<AllocateResult>(new AllocateResult());
            boolean_literal_field = std::shared_ptr<BooleanResult>(new BooleanResult());
            byte_literal_field = std::shared_ptr<ByteResult>(new ByteResult());
            call_field = std::shared_ptr<CallResult>(new CallResult());
            decimal_literal_field = std::shared_ptr<DecimalResult>(new DecimalResult());
            integer_literal_field = std::shared_ptr<NumberResult>(new NumberResult());
            string_literal_field = std::shared_ptr<LiteralResult>(new LiteralResult());
            unary_operator_field = std::shared_ptr<UnaryOperatorResult>(new UnaryOperatorResult());
            variable_field = std::shared_ptr<NameResult>(new NameResult());
        }

        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && unary_operator_parser_instance->ParseOptionalSave(index, unary_operator_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && name_parser_instance->ParseSingleSave(index, variable_field))
        {
            instance->SetAllocate(allocate_field->GetValue());
            instance->SetBooleanLiteral(boolean_literal_field->GetValue());
            instance->SetByteLiteral(byte_literal_field->GetValue());
            instance->SetCall(call_field->GetValue());
            instance->SetDecimalLiteral(decimal_literal_field->GetValue());
            instance->SetIntegerLiteral(integer_literal_field->GetValue());
            instance->SetStringLiteral(string_literal_field->GetValue());
            instance->SetUnaryOperator(unary_operator_field->GetValue());
            instance->SetVariable(variable_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            allocate_field = std::shared_ptr<AllocateResult>(new AllocateResult());
            boolean_literal_field = std::shared_ptr<BooleanResult>(new BooleanResult());
            byte_literal_field = std::shared_ptr<ByteResult>(new ByteResult());
            call_field = std::shared_ptr<CallResult>(new CallResult());
            decimal_literal_field = std::shared_ptr<DecimalResult>(new DecimalResult());
            integer_literal_field = std::shared_ptr<NumberResult>(new NumberResult());
            string_literal_field = std::shared_ptr<LiteralResult>(new LiteralResult());
            unary_operator_field = std::shared_ptr<UnaryOperatorResult>(new UnaryOperatorResult());
            variable_field = std::shared_ptr<NameResult>(new NameResult());
        }

        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && unary_operator_parser_instance->ParseOptionalSave(index, unary_operator_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && string_parser_instance->ParseSingle(index, std::string("\"")) && literal_parser_instance->ParseSingleSave(index, string_literal_field) && string_parser_instance->ParseSingle(index, std::string("\"")))
        {
            instance->SetAllocate(allocate_field->GetValue());
            instance->SetBooleanLiteral(boolean_literal_field->GetValue());
            instance->SetByteLiteral(byte_literal_field->GetValue());
            instance->SetCall(call_field->GetValue());
            instance->SetDecimalLiteral(decimal_literal_field->GetValue());
            instance->SetIntegerLiteral(integer_literal_field->GetValue());
            instance->SetStringLiteral(string_literal_field->GetValue());
            instance->SetUnaryOperator(unary_operator_field->GetValue());
            instance->SetVariable(variable_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            allocate_field = std::shared_ptr<AllocateResult>(new AllocateResult());
            boolean_literal_field = std::shared_ptr<BooleanResult>(new BooleanResult());
            byte_literal_field = std::shared_ptr<ByteResult>(new ByteResult());
            call_field = std::shared_ptr<CallResult>(new CallResult());
            decimal_literal_field = std::shared_ptr<DecimalResult>(new DecimalResult());
            integer_literal_field = std::shared_ptr<NumberResult>(new NumberResult());
            string_literal_field = std::shared_ptr<LiteralResult>(new LiteralResult());
            unary_operator_field = std::shared_ptr<UnaryOperatorResult>(new UnaryOperatorResult());
            variable_field = std::shared_ptr<NameResult>(new NameResult());
        }

        result->SetResult(false);
        return result->GetResult();
    }

    bool RValueSingleParser::ParseSingle(OmniPointer<LengthString> index)
    {
        OmniPointer<RValueSingleResult> result = std::shared_ptr<RValueSingleResult>(new RValueSingleResult());
        return ParseSingleSave(index, result);
    }

    bool RValueSingleParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<RValueSingleResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool RValueSingleParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<RValueSingleResult> result = std::shared_ptr<RValueSingleResult>(new RValueSingleResult());
        return ParseOptionalSave(index, result);
    }

    bool RValueSingleParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<RValueSingleListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<RValueSingle>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<RValueSingleResult> result = std::shared_ptr<RValueSingleResult>(new RValueSingleResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void RValueSingleResult::SetValue(OmniPointer<RValueSingle> new_value)
    {
        value = new_value;
    }

    OmniPointer<RValueSingle> RValueSingleResult::GetValue()
    {
        return value;
    }

    void RValueSingleResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool RValueSingleResult::GetResult()
    {
        return result;
    }

    void RValueSingleListResult::SetValue(std::vector<OmniPointer<RValueSingle>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<RValueSingle>> RValueSingleListResult::GetValue()
    {
        return value;
    }

    void RValueSingleListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool RValueSingleListResult::GetResult()
    {
        return result;
    }

    void RValueSingle::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string RValueSingle::UnParse()
    {
        return length_string->GetString();
    }

    void RValueSingle::SetAllocate(OmniPointer<Allocate> input_value)
    {
        allocate_field = input_value;
    }

    OmniPointer<Allocate> RValueSingle::GetAllocate()
    {
        return allocate_field;
    }

    void RValueSingle::SetBooleanLiteral(OmniPointer<Boolean> input_value)
    {
        boolean_literal_field = input_value;
    }

    OmniPointer<Boolean> RValueSingle::GetBooleanLiteral()
    {
        return boolean_literal_field;
    }

    void RValueSingle::SetByteLiteral(OmniPointer<Byte> input_value)
    {
        byte_literal_field = input_value;
    }

    OmniPointer<Byte> RValueSingle::GetByteLiteral()
    {
        return byte_literal_field;
    }

    void RValueSingle::SetCall(OmniPointer<Call> input_value)
    {
        call_field = input_value;
    }

    OmniPointer<Call> RValueSingle::GetCall()
    {
        return call_field;
    }

    void RValueSingle::SetDecimalLiteral(OmniPointer<Decimal> input_value)
    {
        decimal_literal_field = input_value;
    }

    OmniPointer<Decimal> RValueSingle::GetDecimalLiteral()
    {
        return decimal_literal_field;
    }

    void RValueSingle::SetIntegerLiteral(OmniPointer<Number> input_value)
    {
        integer_literal_field = input_value;
    }

    OmniPointer<Number> RValueSingle::GetIntegerLiteral()
    {
        return integer_literal_field;
    }

    void RValueSingle::SetStringLiteral(OmniPointer<Literal> input_value)
    {
        string_literal_field = input_value;
    }

    OmniPointer<Literal> RValueSingle::GetStringLiteral()
    {
        return string_literal_field;
    }

    void RValueSingle::SetUnaryOperator(OmniPointer<UnaryOperator> input_value)
    {
        unary_operator_field = input_value;
    }

    OmniPointer<UnaryOperator> RValueSingle::GetUnaryOperator()
    {
        return unary_operator_field;
    }

    void RValueSingle::SetVariable(OmniPointer<Name> input_value)
    {
        variable_field = input_value;
    }

    OmniPointer<Name> RValueSingle::GetVariable()
    {
        return variable_field;
    }

    void RValueTailParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<BinaryOperatorResult> binary_operator_field = std::shared_ptr<BinaryOperatorResult>(new BinaryOperatorResult());
        OmniPointer<RValueTailResult> tail_field = std::shared_ptr<RValueTailResult>(new RValueTailResult());
        OmniPointer<RValueSingleResult> value_field = std::shared_ptr<RValueSingleResult>(new RValueSingleResult());
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && whitespace_parser_instance->ParseMany(index, 0, -1) && binary_operator_parser_instance->ParseSingleSave(index, binary_operator_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && r_value_single_parser_instance->ParseSingleSave(index, value_field) && whitespace_parser_instance->ParseMany(index, 0, -1) && r_value_tail_parser_instance->ParseOptionalSave(index, tail_field))
        {
            instance->SetBinaryOperator(binary_operator_field->GetValue());
            instance->SetTail(tail_field->GetValue());
            instance->SetValue(value_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            binary_operator_field = std::shared_ptr<BinaryOperatorResult>(new BinaryOperatorResult());
            tail_field = std::shared_ptr<RValueTailResult>(new RValueTailResult());
            value_field = std::shared_ptr<RValueSingleResult>(new RValueSingleResult());
        }

        result->SetResult(false);
        return result->GetResult();
    }

    bool RValueTailParser::ParseSingle(OmniPointer<LengthString> index)
    {
        OmniPointer<RValueTailResult> result = std::shared_ptr<RValueTailResult>(new RValueTailResult());
        return ParseSingleSave(index, result);
    }

    bool RValueTailParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<RValueTailResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool RValueTailParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<RValueTailResult> result = std::shared_ptr<RValueTailResult>(new RValueTailResult());
        return ParseOptionalSave(index, result);
    }

    bool RValueTailParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<RValueTailListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<RValueTail>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<RValueTailResult> result = std::shared_ptr<RValueTailResult>(new RValueTailResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void RValueTailResult::SetValue(OmniPointer<RValueTail> new_value)
    {
        value = new_value;
    }

    OmniPointer<RValueTail> RValueTailResult::GetValue()
    {
        return value;
    }

    void RValueTailResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool RValueTailResult::GetResult()
    {
        return result;
    }

    void RValueTailListResult::SetValue(std::vector<OmniPointer<RValueTail>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<RValueTail>> RValueTailListResult::GetValue()
    {
        return value;
    }

    void RValueTailListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool RValueTailListResult::GetResult()
    {
        return result;
    }

    void RValueTail::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string RValueTail::UnParse()
    {
        return length_string->GetString();
    }

    void RValueTail::SetBinaryOperator(OmniPointer<BinaryOperator> input_value)
    {
        binary_operator_field = input_value;
    }

    OmniPointer<BinaryOperator> RValueTail::GetBinaryOperator()
    {
        return binary_operator_field;
    }

    void RValueTail::SetTail(OmniPointer<RValueTail> input_value)
    {
        tail_field = input_value;
    }

    OmniPointer<RValueTail> RValueTail::GetTail()
    {
        return tail_field;
    }

    void RValueTail::SetValue(OmniPointer<RValueSingle> input_value)
    {
        value_field = input_value;
    }

    OmniPointer<RValueSingle> RValueTail::GetValue()
    {
        return value_field;
    }

    void RValueParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && r_value_single_parser_instance->ParseSingleSave(index, value_field) && r_value_tail_parser_instance->ParseOptionalSave(index, tail_field))
        {
            instance->SetTail(tail_field->GetValue());
            instance->SetValue(value_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
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
        return ParseSingleSave(index, result);
    }

    bool RValueParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<RValueResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool RValueParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<RValueResult> result = std::shared_ptr<RValueResult>(new RValueResult());
        return ParseOptionalSave(index, result);
    }

    bool RValueParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<RValueListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<RValue>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<RValueResult> result = std::shared_ptr<RValueResult>(new RValueResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void RValueResult::SetValue(OmniPointer<RValue> new_value)
    {
        value = new_value;
    }

    OmniPointer<RValue> RValueResult::GetValue()
    {
        return value;
    }

    void RValueResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool RValueResult::GetResult()
    {
        return result;
    }

    void RValueListResult::SetValue(std::vector<OmniPointer<RValue>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<RValue>> RValueListResult::GetValue()
    {
        return value;
    }

    void RValueListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool RValueListResult::GetResult()
    {
        return result;
    }

    void RValue::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string RValue::UnParse()
    {
        return length_string->GetString();
    }

    void RValue::SetTail(OmniPointer<RValueTail> input_value)
    {
        tail_field = input_value;
    }

    OmniPointer<RValueTail> RValue::GetTail()
    {
        return tail_field;
    }

    void RValue::SetValue(OmniPointer<RValueSingle> input_value)
    {
        value_field = input_value;
    }

    OmniPointer<RValueSingle> RValue::GetValue()
    {
        return value_field;
    }

    void BinaryOperatorParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<StringResult> addition_field = std::shared_ptr<StringResult>(new StringResult());
        OmniPointer<StringResult> and_op_field = std::shared_ptr<StringResult>(new StringResult());
        OmniPointer<StringResult> equality_field = std::shared_ptr<StringResult>(new StringResult());
        OmniPointer<StringResult> greater_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
        OmniPointer<StringResult> greater_than_field = std::shared_ptr<StringResult>(new StringResult());
        OmniPointer<StringResult> less_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
        OmniPointer<StringResult> less_than_field = std::shared_ptr<StringResult>(new StringResult());
        OmniPointer<StringResult> not_equality_field = std::shared_ptr<StringResult>(new StringResult());
        OmniPointer<StringResult> or_op_field = std::shared_ptr<StringResult>(new StringResult());
        OmniPointer<StringResult> subtraction_field = std::shared_ptr<StringResult>(new StringResult());
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && string_parser_instance->ParseSingleSave(index, std::string("+"), addition_field))
        {
            instance->SetAddition(addition_field->GetValue());
            instance->SetAndOp(and_op_field->GetValue());
            instance->SetEquality(equality_field->GetValue());
            instance->SetGreaterThanEq(greater_than_eq_field->GetValue());
            instance->SetGreaterThan(greater_than_field->GetValue());
            instance->SetLessThanEq(less_than_eq_field->GetValue());
            instance->SetLessThan(less_than_field->GetValue());
            instance->SetNotEquality(not_equality_field->GetValue());
            instance->SetOrOp(or_op_field->GetValue());
            instance->SetSubtraction(subtraction_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            addition_field = std::shared_ptr<StringResult>(new StringResult());
            and_op_field = std::shared_ptr<StringResult>(new StringResult());
            equality_field = std::shared_ptr<StringResult>(new StringResult());
            greater_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
            greater_than_field = std::shared_ptr<StringResult>(new StringResult());
            less_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
            less_than_field = std::shared_ptr<StringResult>(new StringResult());
            not_equality_field = std::shared_ptr<StringResult>(new StringResult());
            or_op_field = std::shared_ptr<StringResult>(new StringResult());
            subtraction_field = std::shared_ptr<StringResult>(new StringResult());
        }

        if (true && string_parser_instance->ParseSingleSave(index, std::string("-"), subtraction_field))
        {
            instance->SetAddition(addition_field->GetValue());
            instance->SetAndOp(and_op_field->GetValue());
            instance->SetEquality(equality_field->GetValue());
            instance->SetGreaterThanEq(greater_than_eq_field->GetValue());
            instance->SetGreaterThan(greater_than_field->GetValue());
            instance->SetLessThanEq(less_than_eq_field->GetValue());
            instance->SetLessThan(less_than_field->GetValue());
            instance->SetNotEquality(not_equality_field->GetValue());
            instance->SetOrOp(or_op_field->GetValue());
            instance->SetSubtraction(subtraction_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            addition_field = std::shared_ptr<StringResult>(new StringResult());
            and_op_field = std::shared_ptr<StringResult>(new StringResult());
            equality_field = std::shared_ptr<StringResult>(new StringResult());
            greater_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
            greater_than_field = std::shared_ptr<StringResult>(new StringResult());
            less_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
            less_than_field = std::shared_ptr<StringResult>(new StringResult());
            not_equality_field = std::shared_ptr<StringResult>(new StringResult());
            or_op_field = std::shared_ptr<StringResult>(new StringResult());
            subtraction_field = std::shared_ptr<StringResult>(new StringResult());
        }

        if (true && string_parser_instance->ParseSingleSave(index, std::string("<="), less_than_eq_field))
        {
            instance->SetAddition(addition_field->GetValue());
            instance->SetAndOp(and_op_field->GetValue());
            instance->SetEquality(equality_field->GetValue());
            instance->SetGreaterThanEq(greater_than_eq_field->GetValue());
            instance->SetGreaterThan(greater_than_field->GetValue());
            instance->SetLessThanEq(less_than_eq_field->GetValue());
            instance->SetLessThan(less_than_field->GetValue());
            instance->SetNotEquality(not_equality_field->GetValue());
            instance->SetOrOp(or_op_field->GetValue());
            instance->SetSubtraction(subtraction_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            addition_field = std::shared_ptr<StringResult>(new StringResult());
            and_op_field = std::shared_ptr<StringResult>(new StringResult());
            equality_field = std::shared_ptr<StringResult>(new StringResult());
            greater_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
            greater_than_field = std::shared_ptr<StringResult>(new StringResult());
            less_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
            less_than_field = std::shared_ptr<StringResult>(new StringResult());
            not_equality_field = std::shared_ptr<StringResult>(new StringResult());
            or_op_field = std::shared_ptr<StringResult>(new StringResult());
            subtraction_field = std::shared_ptr<StringResult>(new StringResult());
        }

        if (true && string_parser_instance->ParseSingleSave(index, std::string(">="), greater_than_eq_field))
        {
            instance->SetAddition(addition_field->GetValue());
            instance->SetAndOp(and_op_field->GetValue());
            instance->SetEquality(equality_field->GetValue());
            instance->SetGreaterThanEq(greater_than_eq_field->GetValue());
            instance->SetGreaterThan(greater_than_field->GetValue());
            instance->SetLessThanEq(less_than_eq_field->GetValue());
            instance->SetLessThan(less_than_field->GetValue());
            instance->SetNotEquality(not_equality_field->GetValue());
            instance->SetOrOp(or_op_field->GetValue());
            instance->SetSubtraction(subtraction_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            addition_field = std::shared_ptr<StringResult>(new StringResult());
            and_op_field = std::shared_ptr<StringResult>(new StringResult());
            equality_field = std::shared_ptr<StringResult>(new StringResult());
            greater_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
            greater_than_field = std::shared_ptr<StringResult>(new StringResult());
            less_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
            less_than_field = std::shared_ptr<StringResult>(new StringResult());
            not_equality_field = std::shared_ptr<StringResult>(new StringResult());
            or_op_field = std::shared_ptr<StringResult>(new StringResult());
            subtraction_field = std::shared_ptr<StringResult>(new StringResult());
        }

        if (true && string_parser_instance->ParseSingleSave(index, std::string("=="), equality_field))
        {
            instance->SetAddition(addition_field->GetValue());
            instance->SetAndOp(and_op_field->GetValue());
            instance->SetEquality(equality_field->GetValue());
            instance->SetGreaterThanEq(greater_than_eq_field->GetValue());
            instance->SetGreaterThan(greater_than_field->GetValue());
            instance->SetLessThanEq(less_than_eq_field->GetValue());
            instance->SetLessThan(less_than_field->GetValue());
            instance->SetNotEquality(not_equality_field->GetValue());
            instance->SetOrOp(or_op_field->GetValue());
            instance->SetSubtraction(subtraction_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            addition_field = std::shared_ptr<StringResult>(new StringResult());
            and_op_field = std::shared_ptr<StringResult>(new StringResult());
            equality_field = std::shared_ptr<StringResult>(new StringResult());
            greater_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
            greater_than_field = std::shared_ptr<StringResult>(new StringResult());
            less_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
            less_than_field = std::shared_ptr<StringResult>(new StringResult());
            not_equality_field = std::shared_ptr<StringResult>(new StringResult());
            or_op_field = std::shared_ptr<StringResult>(new StringResult());
            subtraction_field = std::shared_ptr<StringResult>(new StringResult());
        }

        if (true && string_parser_instance->ParseSingleSave(index, std::string("!="), not_equality_field))
        {
            instance->SetAddition(addition_field->GetValue());
            instance->SetAndOp(and_op_field->GetValue());
            instance->SetEquality(equality_field->GetValue());
            instance->SetGreaterThanEq(greater_than_eq_field->GetValue());
            instance->SetGreaterThan(greater_than_field->GetValue());
            instance->SetLessThanEq(less_than_eq_field->GetValue());
            instance->SetLessThan(less_than_field->GetValue());
            instance->SetNotEquality(not_equality_field->GetValue());
            instance->SetOrOp(or_op_field->GetValue());
            instance->SetSubtraction(subtraction_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            addition_field = std::shared_ptr<StringResult>(new StringResult());
            and_op_field = std::shared_ptr<StringResult>(new StringResult());
            equality_field = std::shared_ptr<StringResult>(new StringResult());
            greater_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
            greater_than_field = std::shared_ptr<StringResult>(new StringResult());
            less_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
            less_than_field = std::shared_ptr<StringResult>(new StringResult());
            not_equality_field = std::shared_ptr<StringResult>(new StringResult());
            or_op_field = std::shared_ptr<StringResult>(new StringResult());
            subtraction_field = std::shared_ptr<StringResult>(new StringResult());
        }

        if (true && string_parser_instance->ParseSingleSave(index, std::string("<"), less_than_field))
        {
            instance->SetAddition(addition_field->GetValue());
            instance->SetAndOp(and_op_field->GetValue());
            instance->SetEquality(equality_field->GetValue());
            instance->SetGreaterThanEq(greater_than_eq_field->GetValue());
            instance->SetGreaterThan(greater_than_field->GetValue());
            instance->SetLessThanEq(less_than_eq_field->GetValue());
            instance->SetLessThan(less_than_field->GetValue());
            instance->SetNotEquality(not_equality_field->GetValue());
            instance->SetOrOp(or_op_field->GetValue());
            instance->SetSubtraction(subtraction_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            addition_field = std::shared_ptr<StringResult>(new StringResult());
            and_op_field = std::shared_ptr<StringResult>(new StringResult());
            equality_field = std::shared_ptr<StringResult>(new StringResult());
            greater_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
            greater_than_field = std::shared_ptr<StringResult>(new StringResult());
            less_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
            less_than_field = std::shared_ptr<StringResult>(new StringResult());
            not_equality_field = std::shared_ptr<StringResult>(new StringResult());
            or_op_field = std::shared_ptr<StringResult>(new StringResult());
            subtraction_field = std::shared_ptr<StringResult>(new StringResult());
        }

        if (true && string_parser_instance->ParseSingleSave(index, std::string(">"), greater_than_field))
        {
            instance->SetAddition(addition_field->GetValue());
            instance->SetAndOp(and_op_field->GetValue());
            instance->SetEquality(equality_field->GetValue());
            instance->SetGreaterThanEq(greater_than_eq_field->GetValue());
            instance->SetGreaterThan(greater_than_field->GetValue());
            instance->SetLessThanEq(less_than_eq_field->GetValue());
            instance->SetLessThan(less_than_field->GetValue());
            instance->SetNotEquality(not_equality_field->GetValue());
            instance->SetOrOp(or_op_field->GetValue());
            instance->SetSubtraction(subtraction_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            addition_field = std::shared_ptr<StringResult>(new StringResult());
            and_op_field = std::shared_ptr<StringResult>(new StringResult());
            equality_field = std::shared_ptr<StringResult>(new StringResult());
            greater_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
            greater_than_field = std::shared_ptr<StringResult>(new StringResult());
            less_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
            less_than_field = std::shared_ptr<StringResult>(new StringResult());
            not_equality_field = std::shared_ptr<StringResult>(new StringResult());
            or_op_field = std::shared_ptr<StringResult>(new StringResult());
            subtraction_field = std::shared_ptr<StringResult>(new StringResult());
        }

        if (true && string_parser_instance->ParseSingleSave(index, std::string("||"), or_op_field))
        {
            instance->SetAddition(addition_field->GetValue());
            instance->SetAndOp(and_op_field->GetValue());
            instance->SetEquality(equality_field->GetValue());
            instance->SetGreaterThanEq(greater_than_eq_field->GetValue());
            instance->SetGreaterThan(greater_than_field->GetValue());
            instance->SetLessThanEq(less_than_eq_field->GetValue());
            instance->SetLessThan(less_than_field->GetValue());
            instance->SetNotEquality(not_equality_field->GetValue());
            instance->SetOrOp(or_op_field->GetValue());
            instance->SetSubtraction(subtraction_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            addition_field = std::shared_ptr<StringResult>(new StringResult());
            and_op_field = std::shared_ptr<StringResult>(new StringResult());
            equality_field = std::shared_ptr<StringResult>(new StringResult());
            greater_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
            greater_than_field = std::shared_ptr<StringResult>(new StringResult());
            less_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
            less_than_field = std::shared_ptr<StringResult>(new StringResult());
            not_equality_field = std::shared_ptr<StringResult>(new StringResult());
            or_op_field = std::shared_ptr<StringResult>(new StringResult());
            subtraction_field = std::shared_ptr<StringResult>(new StringResult());
        }

        if (true && string_parser_instance->ParseSingleSave(index, std::string("&&"), and_op_field))
        {
            instance->SetAddition(addition_field->GetValue());
            instance->SetAndOp(and_op_field->GetValue());
            instance->SetEquality(equality_field->GetValue());
            instance->SetGreaterThanEq(greater_than_eq_field->GetValue());
            instance->SetGreaterThan(greater_than_field->GetValue());
            instance->SetLessThanEq(less_than_eq_field->GetValue());
            instance->SetLessThan(less_than_field->GetValue());
            instance->SetNotEquality(not_equality_field->GetValue());
            instance->SetOrOp(or_op_field->GetValue());
            instance->SetSubtraction(subtraction_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            addition_field = std::shared_ptr<StringResult>(new StringResult());
            and_op_field = std::shared_ptr<StringResult>(new StringResult());
            equality_field = std::shared_ptr<StringResult>(new StringResult());
            greater_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
            greater_than_field = std::shared_ptr<StringResult>(new StringResult());
            less_than_eq_field = std::shared_ptr<StringResult>(new StringResult());
            less_than_field = std::shared_ptr<StringResult>(new StringResult());
            not_equality_field = std::shared_ptr<StringResult>(new StringResult());
            or_op_field = std::shared_ptr<StringResult>(new StringResult());
            subtraction_field = std::shared_ptr<StringResult>(new StringResult());
        }

        result->SetResult(false);
        return result->GetResult();
    }

    bool BinaryOperatorParser::ParseSingle(OmniPointer<LengthString> index)
    {
        OmniPointer<BinaryOperatorResult> result = std::shared_ptr<BinaryOperatorResult>(new BinaryOperatorResult());
        return ParseSingleSave(index, result);
    }

    bool BinaryOperatorParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<BinaryOperatorResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool BinaryOperatorParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<BinaryOperatorResult> result = std::shared_ptr<BinaryOperatorResult>(new BinaryOperatorResult());
        return ParseOptionalSave(index, result);
    }

    bool BinaryOperatorParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<BinaryOperatorListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<BinaryOperator>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<BinaryOperatorResult> result = std::shared_ptr<BinaryOperatorResult>(new BinaryOperatorResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void BinaryOperatorResult::SetValue(OmniPointer<BinaryOperator> new_value)
    {
        value = new_value;
    }

    OmniPointer<BinaryOperator> BinaryOperatorResult::GetValue()
    {
        return value;
    }

    void BinaryOperatorResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool BinaryOperatorResult::GetResult()
    {
        return result;
    }

    void BinaryOperatorListResult::SetValue(std::vector<OmniPointer<BinaryOperator>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<BinaryOperator>> BinaryOperatorListResult::GetValue()
    {
        return value;
    }

    void BinaryOperatorListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool BinaryOperatorListResult::GetResult()
    {
        return result;
    }

    void BinaryOperator::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string BinaryOperator::UnParse()
    {
        return length_string->GetString();
    }

    void BinaryOperator::SetAddition(OmniPointer<String> input_value)
    {
        addition_field = input_value;
    }

    OmniPointer<String> BinaryOperator::GetAddition()
    {
        return addition_field;
    }

    void BinaryOperator::SetAndOp(OmniPointer<String> input_value)
    {
        and_op_field = input_value;
    }

    OmniPointer<String> BinaryOperator::GetAndOp()
    {
        return and_op_field;
    }

    void BinaryOperator::SetEquality(OmniPointer<String> input_value)
    {
        equality_field = input_value;
    }

    OmniPointer<String> BinaryOperator::GetEquality()
    {
        return equality_field;
    }

    void BinaryOperator::SetGreaterThanEq(OmniPointer<String> input_value)
    {
        greater_than_eq_field = input_value;
    }

    OmniPointer<String> BinaryOperator::GetGreaterThanEq()
    {
        return greater_than_eq_field;
    }

    void BinaryOperator::SetGreaterThan(OmniPointer<String> input_value)
    {
        greater_than_field = input_value;
    }

    OmniPointer<String> BinaryOperator::GetGreaterThan()
    {
        return greater_than_field;
    }

    void BinaryOperator::SetLessThanEq(OmniPointer<String> input_value)
    {
        less_than_eq_field = input_value;
    }

    OmniPointer<String> BinaryOperator::GetLessThanEq()
    {
        return less_than_eq_field;
    }

    void BinaryOperator::SetLessThan(OmniPointer<String> input_value)
    {
        less_than_field = input_value;
    }

    OmniPointer<String> BinaryOperator::GetLessThan()
    {
        return less_than_field;
    }

    void BinaryOperator::SetNotEquality(OmniPointer<String> input_value)
    {
        not_equality_field = input_value;
    }

    OmniPointer<String> BinaryOperator::GetNotEquality()
    {
        return not_equality_field;
    }

    void BinaryOperator::SetOrOp(OmniPointer<String> input_value)
    {
        or_op_field = input_value;
    }

    OmniPointer<String> BinaryOperator::GetOrOp()
    {
        return or_op_field;
    }

    void BinaryOperator::SetSubtraction(OmniPointer<String> input_value)
    {
        subtraction_field = input_value;
    }

    OmniPointer<String> BinaryOperator::GetSubtraction()
    {
        return subtraction_field;
    }

    void UnaryOperatorParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && string_parser_instance->ParseSingleSave(index, std::string("!"), negation_field))
        {
            instance->SetNegation(negation_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
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
        return ParseSingleSave(index, result);
    }

    bool UnaryOperatorParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<UnaryOperatorResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool UnaryOperatorParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<UnaryOperatorResult> result = std::shared_ptr<UnaryOperatorResult>(new UnaryOperatorResult());
        return ParseOptionalSave(index, result);
    }

    bool UnaryOperatorParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<UnaryOperatorListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<UnaryOperator>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<UnaryOperatorResult> result = std::shared_ptr<UnaryOperatorResult>(new UnaryOperatorResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void UnaryOperatorResult::SetValue(OmniPointer<UnaryOperator> new_value)
    {
        value = new_value;
    }

    OmniPointer<UnaryOperator> UnaryOperatorResult::GetValue()
    {
        return value;
    }

    void UnaryOperatorResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool UnaryOperatorResult::GetResult()
    {
        return result;
    }

    void UnaryOperatorListResult::SetValue(std::vector<OmniPointer<UnaryOperator>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<UnaryOperator>> UnaryOperatorListResult::GetValue()
    {
        return value;
    }

    void UnaryOperatorListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool UnaryOperatorListResult::GetResult()
    {
        return result;
    }

    void UnaryOperator::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string UnaryOperator::UnParse()
    {
        return length_string->GetString();
    }

    void UnaryOperator::SetNegation(OmniPointer<String> input_value)
    {
        negation_field = input_value;
    }

    OmniPointer<String> UnaryOperator::GetNegation()
    {
        return negation_field;
    }

    void CommentParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CommentCharacterListResult> content_field = std::shared_ptr<CommentCharacterListResult>(new CommentCharacterListResult());
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && string_parser_instance->ParseSingle(index, std::string("/*")) && comment_character_parser_instance->ParseManySave(index, content_field, 0, -1) && string_parser_instance->ParseSingle(index, std::string("*/")))
        {
            instance->SetContent(content_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            content_field = std::shared_ptr<CommentCharacterListResult>(new CommentCharacterListResult());
        }

        result->SetResult(false);
        return result->GetResult();
    }

    bool CommentParser::ParseSingle(OmniPointer<LengthString> index)
    {
        OmniPointer<CommentResult> result = std::shared_ptr<CommentResult>(new CommentResult());
        return ParseSingleSave(index, result);
    }

    bool CommentParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<CommentResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool CommentParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<CommentResult> result = std::shared_ptr<CommentResult>(new CommentResult());
        return ParseOptionalSave(index, result);
    }

    bool CommentParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<CommentListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<Comment>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<CommentResult> result = std::shared_ptr<CommentResult>(new CommentResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void CommentResult::SetValue(OmniPointer<Comment> new_value)
    {
        value = new_value;
    }

    OmniPointer<Comment> CommentResult::GetValue()
    {
        return value;
    }

    void CommentResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool CommentResult::GetResult()
    {
        return result;
    }

    void CommentListResult::SetValue(std::vector<OmniPointer<Comment>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<Comment>> CommentListResult::GetValue()
    {
        return value;
    }

    void CommentListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool CommentListResult::GetResult()
    {
        return result;
    }

    void Comment::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string Comment::UnParse()
    {
        return length_string->GetString();
    }

    void Comment::SetContent(std::vector<OmniPointer<CommentCharacter>> input_value)
    {
        content_field = input_value;
    }

    std::vector<OmniPointer<CommentCharacter>> Comment::GetContent()
    {
        return content_field;
    }

    void CommentCharacterParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
    }

    bool CommentCharacterParser::ParseSingleSave(OmniPointer<LengthString> index, OmniPointer<CommentCharacterResult> result)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        OmniPointer<LengthString> consumed_string = std::shared_ptr<LengthString>(new LengthString());
        consumed_string->SetData(index->GetData());
        consumed_string->SetStart(index->GetStart());
        consumed_string->SetLength(0);
        OmniPointer<CommentCharacter> instance = std::shared_ptr<CommentCharacter>(new CommentCharacter());
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && whitespace_parser_instance->ParseSingle(index))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && name_character_parser_instance->ParseSingle(index))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("!")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("\\\"")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("#")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("$")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("%")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("&")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("'")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("(")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string(")")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("+")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string(",")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("-")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string(".")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("/")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string(":")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string(";")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("<")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("=")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string(">")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("?")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("@")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("[")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("]")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("^")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("_")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("{")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("|")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("}")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("~")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

    bool CommentCharacterParser::ParseSingle(OmniPointer<LengthString> index)
    {
        OmniPointer<CommentCharacterResult> result = std::shared_ptr<CommentCharacterResult>(new CommentCharacterResult());
        return ParseSingleSave(index, result);
    }

    bool CommentCharacterParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<CommentCharacterResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool CommentCharacterParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<CommentCharacterResult> result = std::shared_ptr<CommentCharacterResult>(new CommentCharacterResult());
        return ParseOptionalSave(index, result);
    }

    bool CommentCharacterParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<CommentCharacterListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<CommentCharacter>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<CommentCharacterResult> result = std::shared_ptr<CommentCharacterResult>(new CommentCharacterResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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

    bool CommentCharacterParser::ParseMany(OmniPointer<LengthString> index, int minimum, int maximum)
    {
        OmniPointer<CommentCharacterListResult> result = std::shared_ptr<CommentCharacterListResult>(new CommentCharacterListResult());
        return ParseManySave(index, result, minimum, maximum);
    }

    void CommentCharacterResult::SetValue(OmniPointer<CommentCharacter> new_value)
    {
        value = new_value;
    }

    OmniPointer<CommentCharacter> CommentCharacterResult::GetValue()
    {
        return value;
    }

    void CommentCharacterResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool CommentCharacterResult::GetResult()
    {
        return result;
    }

    void CommentCharacterListResult::SetValue(std::vector<OmniPointer<CommentCharacter>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<CommentCharacter>> CommentCharacterListResult::GetValue()
    {
        return value;
    }

    void CommentCharacterListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool CommentCharacterListResult::GetResult()
    {
        return result;
    }

    void CommentCharacter::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string CommentCharacter::UnParse()
    {
        return length_string->GetString();
    }

    void QualfiedNameParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<NameResult> name_field = std::shared_ptr<NameResult>(new NameResult());
        OmniPointer<NameTailResult> tail_field = std::shared_ptr<NameTailResult>(new NameTailResult());
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && name_parser_instance->ParseSingleSave(index, name_field) && name_tail_parser_instance->ParseOptionalSave(index, tail_field))
        {
            instance->SetName(name_field->GetValue());
            instance->SetTail(tail_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
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
            tail_field = std::shared_ptr<NameTailResult>(new NameTailResult());
        }

        result->SetResult(false);
        return result->GetResult();
    }

    bool QualfiedNameParser::ParseSingle(OmniPointer<LengthString> index)
    {
        OmniPointer<QualfiedNameResult> result = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
        return ParseSingleSave(index, result);
    }

    bool QualfiedNameParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<QualfiedNameResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool QualfiedNameParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<QualfiedNameResult> result = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
        return ParseOptionalSave(index, result);
    }

    bool QualfiedNameParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<QualfiedNameListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<QualfiedName>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<QualfiedNameResult> result = std::shared_ptr<QualfiedNameResult>(new QualfiedNameResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void QualfiedNameResult::SetValue(OmniPointer<QualfiedName> new_value)
    {
        value = new_value;
    }

    OmniPointer<QualfiedName> QualfiedNameResult::GetValue()
    {
        return value;
    }

    void QualfiedNameResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool QualfiedNameResult::GetResult()
    {
        return result;
    }

    void QualfiedNameListResult::SetValue(std::vector<OmniPointer<QualfiedName>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<QualfiedName>> QualfiedNameListResult::GetValue()
    {
        return value;
    }

    void QualfiedNameListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool QualfiedNameListResult::GetResult()
    {
        return result;
    }

    void QualfiedName::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string QualfiedName::UnParse()
    {
        return length_string->GetString();
    }

    void QualfiedName::SetName(OmniPointer<Name> input_value)
    {
        name_field = input_value;
    }

    OmniPointer<Name> QualfiedName::GetName()
    {
        return name_field;
    }

    void QualfiedName::SetTail(OmniPointer<NameTail> input_value)
    {
        tail_field = input_value;
    }

    OmniPointer<NameTail> QualfiedName::GetTail()
    {
        return tail_field;
    }

    void NameTailParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<NameResult> name_field = std::shared_ptr<NameResult>(new NameResult());
        OmniPointer<NameTailResult> tail_field = std::shared_ptr<NameTailResult>(new NameTailResult());
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && string_parser_instance->ParseSingle(index, std::string(".")) && name_parser_instance->ParseSingleSave(index, name_field) && name_tail_parser_instance->ParseOptionalSave(index, tail_field))
        {
            instance->SetName(name_field->GetValue());
            instance->SetTail(tail_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
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
            tail_field = std::shared_ptr<NameTailResult>(new NameTailResult());
        }

        result->SetResult(false);
        return result->GetResult();
    }

    bool NameTailParser::ParseSingle(OmniPointer<LengthString> index)
    {
        OmniPointer<NameTailResult> result = std::shared_ptr<NameTailResult>(new NameTailResult());
        return ParseSingleSave(index, result);
    }

    bool NameTailParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<NameTailResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool NameTailParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<NameTailResult> result = std::shared_ptr<NameTailResult>(new NameTailResult());
        return ParseOptionalSave(index, result);
    }

    bool NameTailParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<NameTailListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<NameTail>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<NameTailResult> result = std::shared_ptr<NameTailResult>(new NameTailResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void NameTailResult::SetValue(OmniPointer<NameTail> new_value)
    {
        value = new_value;
    }

    OmniPointer<NameTail> NameTailResult::GetValue()
    {
        return value;
    }

    void NameTailResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool NameTailResult::GetResult()
    {
        return result;
    }

    void NameTailListResult::SetValue(std::vector<OmniPointer<NameTail>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<NameTail>> NameTailListResult::GetValue()
    {
        return value;
    }

    void NameTailListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool NameTailListResult::GetResult()
    {
        return result;
    }

    void NameTail::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string NameTail::UnParse()
    {
        return length_string->GetString();
    }

    void NameTail::SetName(OmniPointer<Name> input_value)
    {
        name_field = input_value;
    }

    OmniPointer<Name> NameTail::GetName()
    {
        return name_field;
    }

    void NameTail::SetTail(OmniPointer<NameTail> input_value)
    {
        tail_field = input_value;
    }

    OmniPointer<NameTail> NameTail::GetTail()
    {
        return tail_field;
    }

    void NameParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && name_character_parser_instance->ParseMany(index, 1, -1))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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
        return ParseSingleSave(index, result);
    }

    bool NameParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<NameResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool NameParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<NameResult> result = std::shared_ptr<NameResult>(new NameResult());
        return ParseOptionalSave(index, result);
    }

    bool NameParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<NameListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<Name>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<NameResult> result = std::shared_ptr<NameResult>(new NameResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void NameResult::SetValue(OmniPointer<Name> new_value)
    {
        value = new_value;
    }

    OmniPointer<Name> NameResult::GetValue()
    {
        return value;
    }

    void NameResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool NameResult::GetResult()
    {
        return result;
    }

    void NameListResult::SetValue(std::vector<OmniPointer<Name>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<Name>> NameListResult::GetValue()
    {
        return value;
    }

    void NameListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool NameListResult::GetResult()
    {
        return result;
    }

    void Name::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string Name::UnParse()
    {
        return length_string->GetString();
    }

    void NameCharacterParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && character_range_parser_instance->ParseSingle(index, 0x30, 0x39))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && character_range_parser_instance->ParseSingle(index, 0x41, 0x5A))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("_")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && character_range_parser_instance->ParseSingle(index, 0x61, 0x7A))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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
        return ParseSingleSave(index, result);
    }

    bool NameCharacterParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<NameCharacterResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool NameCharacterParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<NameCharacterResult> result = std::shared_ptr<NameCharacterResult>(new NameCharacterResult());
        return ParseOptionalSave(index, result);
    }

    bool NameCharacterParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<NameCharacterListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<NameCharacter>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<NameCharacterResult> result = std::shared_ptr<NameCharacterResult>(new NameCharacterResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void NameCharacterResult::SetValue(OmniPointer<NameCharacter> new_value)
    {
        value = new_value;
    }

    OmniPointer<NameCharacter> NameCharacterResult::GetValue()
    {
        return value;
    }

    void NameCharacterResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool NameCharacterResult::GetResult()
    {
        return result;
    }

    void NameCharacterListResult::SetValue(std::vector<OmniPointer<NameCharacter>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<NameCharacter>> NameCharacterListResult::GetValue()
    {
        return value;
    }

    void NameCharacterListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool NameCharacterListResult::GetResult()
    {
        return result;
    }

    void NameCharacter::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string NameCharacter::UnParse()
    {
        return length_string->GetString();
    }

    void BooleanParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && string_parser_instance->ParseSingle(index, std::string("true")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("false")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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
        return ParseSingleSave(index, result);
    }

    bool BooleanParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<BooleanResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool BooleanParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<BooleanResult> result = std::shared_ptr<BooleanResult>(new BooleanResult());
        return ParseOptionalSave(index, result);
    }

    bool BooleanParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<BooleanListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<Boolean>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<BooleanResult> result = std::shared_ptr<BooleanResult>(new BooleanResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void BooleanResult::SetValue(OmniPointer<Boolean> new_value)
    {
        value = new_value;
    }

    OmniPointer<Boolean> BooleanResult::GetValue()
    {
        return value;
    }

    void BooleanResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool BooleanResult::GetResult()
    {
        return result;
    }

    void BooleanListResult::SetValue(std::vector<OmniPointer<Boolean>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<Boolean>> BooleanListResult::GetValue()
    {
        return value;
    }

    void BooleanListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool BooleanListResult::GetResult()
    {
        return result;
    }

    void Boolean::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string Boolean::UnParse()
    {
        return length_string->GetString();
    }

    void ByteParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<ByteDigitResult> high_field = std::shared_ptr<ByteDigitResult>(new ByteDigitResult());
        OmniPointer<ByteDigitResult> low_field = std::shared_ptr<ByteDigitResult>(new ByteDigitResult());
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && string_parser_instance->ParseSingle(index, std::string("0x")) && byte_digit_parser_instance->ParseSingleSave(index, high_field) && byte_digit_parser_instance->ParseSingleSave(index, low_field))
        {
            instance->SetHigh(high_field->GetValue());
            instance->SetLow(low_field->GetValue());
            consumed_string->SetLength(index->GetStart() - index_start);
            instance->SetLengthString(consumed_string);
            result->SetValue(instance);
            result->SetResult(true);
            return result->GetResult();
        }
        else
        {
            index->SetStart(index_start);
            index->SetLength(index_length);
            high_field = std::shared_ptr<ByteDigitResult>(new ByteDigitResult());
            low_field = std::shared_ptr<ByteDigitResult>(new ByteDigitResult());
        }

        result->SetResult(false);
        return result->GetResult();
    }

    bool ByteParser::ParseSingle(OmniPointer<LengthString> index)
    {
        OmniPointer<ByteResult> result = std::shared_ptr<ByteResult>(new ByteResult());
        return ParseSingleSave(index, result);
    }

    bool ByteParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ByteResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool ByteParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<ByteResult> result = std::shared_ptr<ByteResult>(new ByteResult());
        return ParseOptionalSave(index, result);
    }

    bool ByteParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<ByteListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<Byte>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<ByteResult> result = std::shared_ptr<ByteResult>(new ByteResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void ByteResult::SetValue(OmniPointer<Byte> new_value)
    {
        value = new_value;
    }

    OmniPointer<Byte> ByteResult::GetValue()
    {
        return value;
    }

    void ByteResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool ByteResult::GetResult()
    {
        return result;
    }

    void ByteListResult::SetValue(std::vector<OmniPointer<Byte>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<Byte>> ByteListResult::GetValue()
    {
        return value;
    }

    void ByteListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool ByteListResult::GetResult()
    {
        return result;
    }

    void Byte::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string Byte::UnParse()
    {
        return length_string->GetString();
    }

    void Byte::SetHigh(OmniPointer<ByteDigit> input_value)
    {
        high_field = input_value;
    }

    OmniPointer<ByteDigit> Byte::GetHigh()
    {
        return high_field;
    }

    void Byte::SetLow(OmniPointer<ByteDigit> input_value)
    {
        low_field = input_value;
    }

    OmniPointer<ByteDigit> Byte::GetLow()
    {
        return low_field;
    }

    void ByteDigitParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && character_range_parser_instance->ParseSingle(index, 0x30, 0x39))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && character_range_parser_instance->ParseSingle(index, 0x41, 0x46))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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
        return ParseSingleSave(index, result);
    }

    bool ByteDigitParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<ByteDigitResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool ByteDigitParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<ByteDigitResult> result = std::shared_ptr<ByteDigitResult>(new ByteDigitResult());
        return ParseOptionalSave(index, result);
    }

    bool ByteDigitParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<ByteDigitListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<ByteDigit>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<ByteDigitResult> result = std::shared_ptr<ByteDigitResult>(new ByteDigitResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void ByteDigitResult::SetValue(OmniPointer<ByteDigit> new_value)
    {
        value = new_value;
    }

    OmniPointer<ByteDigit> ByteDigitResult::GetValue()
    {
        return value;
    }

    void ByteDigitResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool ByteDigitResult::GetResult()
    {
        return result;
    }

    void ByteDigitListResult::SetValue(std::vector<OmniPointer<ByteDigit>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<ByteDigit>> ByteDigitListResult::GetValue()
    {
        return value;
    }

    void ByteDigitListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool ByteDigitListResult::GetResult()
    {
        return result;
    }

    void ByteDigit::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string ByteDigit::UnParse()
    {
        return length_string->GetString();
    }

    void NegativeParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && string_parser_instance->ParseSingle(index, std::string("-")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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
        return ParseSingleSave(index, result);
    }

    bool NegativeParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<NegativeResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool NegativeParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<NegativeResult> result = std::shared_ptr<NegativeResult>(new NegativeResult());
        return ParseOptionalSave(index, result);
    }

    bool NegativeParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<NegativeListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<Negative>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<NegativeResult> result = std::shared_ptr<NegativeResult>(new NegativeResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void NegativeResult::SetValue(OmniPointer<Negative> new_value)
    {
        value = new_value;
    }

    OmniPointer<Negative> NegativeResult::GetValue()
    {
        return value;
    }

    void NegativeResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool NegativeResult::GetResult()
    {
        return result;
    }

    void NegativeListResult::SetValue(std::vector<OmniPointer<Negative>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<Negative>> NegativeListResult::GetValue()
    {
        return value;
    }

    void NegativeListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool NegativeListResult::GetResult()
    {
        return result;
    }

    void Negative::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string Negative::UnParse()
    {
        return length_string->GetString();
    }

    void DecimalParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && negative_parser_instance->ParseOptional(index) && number_parser_instance->ParseSingle(index) && string_parser_instance->ParseSingle(index, std::string(".")) && number_parser_instance->ParseSingle(index))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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
        return ParseSingleSave(index, result);
    }

    bool DecimalParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<DecimalResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool DecimalParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<DecimalResult> result = std::shared_ptr<DecimalResult>(new DecimalResult());
        return ParseOptionalSave(index, result);
    }

    bool DecimalParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<DecimalListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<Decimal>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<DecimalResult> result = std::shared_ptr<DecimalResult>(new DecimalResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void DecimalResult::SetValue(OmniPointer<Decimal> new_value)
    {
        value = new_value;
    }

    OmniPointer<Decimal> DecimalResult::GetValue()
    {
        return value;
    }

    void DecimalResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool DecimalResult::GetResult()
    {
        return result;
    }

    void DecimalListResult::SetValue(std::vector<OmniPointer<Decimal>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<Decimal>> DecimalListResult::GetValue()
    {
        return value;
    }

    void DecimalListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool DecimalListResult::GetResult()
    {
        return result;
    }

    void Decimal::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string Decimal::UnParse()
    {
        return length_string->GetString();
    }

    void NumberParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && negative_parser_instance->ParseOptional(index) && digit_parser_instance->ParseMany(index, 1, -1))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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
        return ParseSingleSave(index, result);
    }

    bool NumberParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<NumberResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool NumberParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<NumberResult> result = std::shared_ptr<NumberResult>(new NumberResult());
        return ParseOptionalSave(index, result);
    }

    bool NumberParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<NumberListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<Number>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<NumberResult> result = std::shared_ptr<NumberResult>(new NumberResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void NumberResult::SetValue(OmniPointer<Number> new_value)
    {
        value = new_value;
    }

    OmniPointer<Number> NumberResult::GetValue()
    {
        return value;
    }

    void NumberResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool NumberResult::GetResult()
    {
        return result;
    }

    void NumberListResult::SetValue(std::vector<OmniPointer<Number>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<Number>> NumberListResult::GetValue()
    {
        return value;
    }

    void NumberListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool NumberListResult::GetResult()
    {
        return result;
    }

    void Number::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string Number::UnParse()
    {
        return length_string->GetString();
    }

    void DigitParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && character_range_parser_instance->ParseSingle(index, 0x30, 0x39))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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
        return ParseSingleSave(index, result);
    }

    bool DigitParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<DigitResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool DigitParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<DigitResult> result = std::shared_ptr<DigitResult>(new DigitResult());
        return ParseOptionalSave(index, result);
    }

    bool DigitParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<DigitListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<Digit>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<DigitResult> result = std::shared_ptr<DigitResult>(new DigitResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void DigitResult::SetValue(OmniPointer<Digit> new_value)
    {
        value = new_value;
    }

    OmniPointer<Digit> DigitResult::GetValue()
    {
        return value;
    }

    void DigitResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool DigitResult::GetResult()
    {
        return result;
    }

    void DigitListResult::SetValue(std::vector<OmniPointer<Digit>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<Digit>> DigitListResult::GetValue()
    {
        return value;
    }

    void DigitListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool DigitListResult::GetResult()
    {
        return result;
    }

    void Digit::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string Digit::UnParse()
    {
        return length_string->GetString();
    }

    void LiteralParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && literal_character_parser_instance->ParseMany(index, 0, -1))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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
        return ParseSingleSave(index, result);
    }

    bool LiteralParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<LiteralResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool LiteralParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<LiteralResult> result = std::shared_ptr<LiteralResult>(new LiteralResult());
        return ParseOptionalSave(index, result);
    }

    bool LiteralParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<LiteralListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<Literal>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<LiteralResult> result = std::shared_ptr<LiteralResult>(new LiteralResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void LiteralResult::SetValue(OmniPointer<Literal> new_value)
    {
        value = new_value;
    }

    OmniPointer<Literal> LiteralResult::GetValue()
    {
        return value;
    }

    void LiteralResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool LiteralResult::GetResult()
    {
        return result;
    }

    void LiteralListResult::SetValue(std::vector<OmniPointer<Literal>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<Literal>> LiteralListResult::GetValue()
    {
        return value;
    }

    void LiteralListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool LiteralListResult::GetResult()
    {
        return result;
    }

    void Literal::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string Literal::UnParse()
    {
        return length_string->GetString();
    }

    void LiteralCharacterParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && character_range_parser_instance->ParseSingle(index, 0x00, 0x21))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("\\\"")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && character_range_parser_instance->ParseSingle(index, 0x23, 0x5B))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && string_parser_instance->ParseSingle(index, std::string("\\\\")))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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

        if (true && character_range_parser_instance->ParseSingle(index, 0x5D, 0xFF))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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
        return ParseSingleSave(index, result);
    }

    bool LiteralCharacterParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<LiteralCharacterResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool LiteralCharacterParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<LiteralCharacterResult> result = std::shared_ptr<LiteralCharacterResult>(new LiteralCharacterResult());
        return ParseOptionalSave(index, result);
    }

    bool LiteralCharacterParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<LiteralCharacterListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<LiteralCharacter>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<LiteralCharacterResult> result = std::shared_ptr<LiteralCharacterResult>(new LiteralCharacterResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void LiteralCharacterResult::SetValue(OmniPointer<LiteralCharacter> new_value)
    {
        value = new_value;
    }

    OmniPointer<LiteralCharacter> LiteralCharacterResult::GetValue()
    {
        return value;
    }

    void LiteralCharacterResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool LiteralCharacterResult::GetResult()
    {
        return result;
    }

    void LiteralCharacterListResult::SetValue(std::vector<OmniPointer<LiteralCharacter>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<LiteralCharacter>> LiteralCharacterListResult::GetValue()
    {
        return value;
    }

    void LiteralCharacterListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool LiteralCharacterListResult::GetResult()
    {
        return result;
    }

    void LiteralCharacter::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string LiteralCharacter::UnParse()
    {
        return length_string->GetString();
    }

    void WhitespaceParser::SetParserNetwork(OmniPointer<ParserNetwork> input)
    {
        parser_network = input;
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
        OmniPointer<CTCodeFileParser> c_t_code_file_parser_instance = parser_network->GetCTCodeFileParser();
        OmniPointer<ExternalDefinitionParser> external_definition_parser_instance = parser_network->GetExternalDefinitionParser();
        OmniPointer<UnmanagedTypeParser> unmanaged_type_parser_instance = parser_network->GetUnmanagedTypeParser();
        OmniPointer<DefinitionParser> definition_parser_instance = parser_network->GetDefinitionParser();
        OmniPointer<InterfaceDefParser> interface_def_parser_instance = parser_network->GetInterfaceDefParser();
        OmniPointer<ClassDefParser> class_def_parser_instance = parser_network->GetClassDefParser();
        OmniPointer<ContentDeclarationParser> content_declaration_parser_instance = parser_network->GetContentDeclarationParser();
        OmniPointer<ContentDefinitionParser> content_definition_parser_instance = parser_network->GetContentDefinitionParser();
        OmniPointer<PrimativeTypeParser> primative_type_parser_instance = parser_network->GetPrimativeTypeParser();
        OmniPointer<DefinedTypeParser> defined_type_parser_instance = parser_network->GetDefinedTypeParser();
        OmniPointer<SingletonTypeParser> singleton_type_parser_instance = parser_network->GetSingletonTypeParser();
        OmniPointer<DimensionalNoteParser> dimensional_note_parser_instance = parser_network->GetDimensionalNoteParser();
        OmniPointer<DimensionalTypeParser> dimensional_type_parser_instance = parser_network->GetDimensionalTypeParser();
        OmniPointer<MapNoteParser> map_note_parser_instance = parser_network->GetMapNoteParser();
        OmniPointer<MapTypeParser> map_type_parser_instance = parser_network->GetMapTypeParser();
        OmniPointer<ValueTypeParser> value_type_parser_instance = parser_network->GetValueTypeParser();
        OmniPointer<ParameterListDefParser> parameter_list_def_parser_instance = parser_network->GetParameterListDefParser();
        OmniPointer<ParameterListParser> parameter_list_parser_instance = parser_network->GetParameterListParser();
        OmniPointer<CodeBlockParser> code_block_parser_instance = parser_network->GetCodeBlockParser();
        OmniPointer<DeclarationAssignParser> declaration_assign_parser_instance = parser_network->GetDeclarationAssignParser();
        OmniPointer<DeclarationParser> declaration_parser_instance = parser_network->GetDeclarationParser();
        OmniPointer<AssignmentParser> assignment_parser_instance = parser_network->GetAssignmentParser();
        OmniPointer<ReturnParser> return_parser_instance = parser_network->GetReturnParser();
        OmniPointer<ElseTailParser> else_tail_parser_instance = parser_network->GetElseTailParser();
        OmniPointer<ConditionalParser> conditional_parser_instance = parser_network->GetConditionalParser();
        OmniPointer<LoopParser> loop_parser_instance = parser_network->GetLoopParser();
        OmniPointer<CallParser> call_parser_instance = parser_network->GetCallParser();
        OmniPointer<AllocateParser> allocate_parser_instance = parser_network->GetAllocateParser();
        OmniPointer<InstructionParser> instruction_parser_instance = parser_network->GetInstructionParser();
        OmniPointer<RValueSingleParser> r_value_single_parser_instance = parser_network->GetRValueSingleParser();
        OmniPointer<RValueTailParser> r_value_tail_parser_instance = parser_network->GetRValueTailParser();
        OmniPointer<RValueParser> r_value_parser_instance = parser_network->GetRValueParser();
        OmniPointer<BinaryOperatorParser> binary_operator_parser_instance = parser_network->GetBinaryOperatorParser();
        OmniPointer<UnaryOperatorParser> unary_operator_parser_instance = parser_network->GetUnaryOperatorParser();
        OmniPointer<CommentParser> comment_parser_instance = parser_network->GetCommentParser();
        OmniPointer<CommentCharacterParser> comment_character_parser_instance = parser_network->GetCommentCharacterParser();
        OmniPointer<QualfiedNameParser> qualfied_name_parser_instance = parser_network->GetQualfiedNameParser();
        OmniPointer<NameTailParser> name_tail_parser_instance = parser_network->GetNameTailParser();
        OmniPointer<NameParser> name_parser_instance = parser_network->GetNameParser();
        OmniPointer<NameCharacterParser> name_character_parser_instance = parser_network->GetNameCharacterParser();
        OmniPointer<BooleanParser> boolean_parser_instance = parser_network->GetBooleanParser();
        OmniPointer<ByteParser> byte_parser_instance = parser_network->GetByteParser();
        OmniPointer<ByteDigitParser> byte_digit_parser_instance = parser_network->GetByteDigitParser();
        OmniPointer<NegativeParser> negative_parser_instance = parser_network->GetNegativeParser();
        OmniPointer<DecimalParser> decimal_parser_instance = parser_network->GetDecimalParser();
        OmniPointer<NumberParser> number_parser_instance = parser_network->GetNumberParser();
        OmniPointer<DigitParser> digit_parser_instance = parser_network->GetDigitParser();
        OmniPointer<LiteralParser> literal_parser_instance = parser_network->GetLiteralParser();
        OmniPointer<LiteralCharacterParser> literal_character_parser_instance = parser_network->GetLiteralCharacterParser();
        OmniPointer<WhitespaceParser> whitespace_parser_instance = parser_network->GetWhitespaceParser();
        OmniPointer<StringParser> string_parser_instance = parser_network->GetStringParser();
        OmniPointer<CharacterParser> character_parser_instance = parser_network->GetCharacterParser();
        OmniPointer<CharacterRangeParser> character_range_parser_instance = parser_network->GetCharacterRangeParser();
        if (true && character_range_parser_instance->ParseSingle(index, 0x00, 0x20))
        {
            consumed_string->SetLength(index->GetStart() - index_start);
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
        return ParseSingleSave(index, result);
    }

    bool WhitespaceParser::ParseOptionalSave(OmniPointer<LengthString> index, OmniPointer<WhitespaceResult> result)
    {
        ParseSingleSave(index, result);
        result->SetResult(true);
        return true;
    }

    bool WhitespaceParser::ParseOptional(OmniPointer<LengthString> index)
    {
        OmniPointer<WhitespaceResult> result = std::shared_ptr<WhitespaceResult>(new WhitespaceResult());
        return ParseOptionalSave(index, result);
    }

    bool WhitespaceParser::ParseManySave(OmniPointer<LengthString> index, OmniPointer<WhitespaceListResult> list_result, int minimum, int maximum)
    {
        int index_start = index->GetStart();
        int index_length = index->GetLength();
        std::vector<OmniPointer<Whitespace>> results;
        int count = 0;
        int max_check = maximum;
        bool check_next = true;
        if (maximum < 0)
        {
            max_check = count + 1;
        }

        while (check_next && count < max_check)
        {
            OmniPointer<WhitespaceResult> result = std::shared_ptr<WhitespaceResult>(new WhitespaceResult());
            ParseSingleSave(index, result);
            check_next = result->GetResult();
            if (result->GetResult())
            {
                count = count + 1;
                Append(results, result->GetValue());
            }

            if (maximum < 0)
            {
                max_check = count + 1;
            }
        }

        if (count >= minimum && count <= max_check)
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
        return ParseManySave(index, result, minimum, maximum);
    }

    void WhitespaceResult::SetValue(OmniPointer<Whitespace> new_value)
    {
        value = new_value;
    }

    OmniPointer<Whitespace> WhitespaceResult::GetValue()
    {
        return value;
    }

    void WhitespaceResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool WhitespaceResult::GetResult()
    {
        return result;
    }

    void WhitespaceListResult::SetValue(std::vector<OmniPointer<Whitespace>> new_value)
    {
        value = new_value;
    }

    std::vector<OmniPointer<Whitespace>> WhitespaceListResult::GetValue()
    {
        return value;
    }

    void WhitespaceListResult::SetResult(bool new_result)
    {
        result = new_result;
    }

    bool WhitespaceListResult::GetResult()
    {
        return result;
    }

    void Whitespace::SetLengthString(OmniPointer<LengthString> new_value)
    {
        length_string = std::shared_ptr<LengthString>(new LengthString());
        length_string->SetData(new_value->GetData());
        length_string->SetStart(new_value->GetStart());
        length_string->SetLength(new_value->GetLength());
    }

    std::string Whitespace::UnParse()
    {
        return length_string->GetString();
    }

};
};
};
};
