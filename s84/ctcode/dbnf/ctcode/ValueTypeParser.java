package s84.ctcode.dbnf.ctcode;

public class ValueTypeParser {
    public ValueTypeParser()
    {
        this.parser_network = null;
    }

    public void SetParserNetwork(ParserNetwork input)
    {
        this.parser_network = input;
    }

    public boolean ParseSingleSave(LengthString index, ValueTypeResult result)
    {
        int index_start = index.GetStart();
        int index_length = index.GetLength();
        LengthString consumed_string = new LengthString();
        consumed_string.SetData(index.GetData());
        consumed_string.SetStart(index.GetStart());
        consumed_string.SetLength(0);
        ValueType instance = new ValueType();
        DimensionalTypeResult dimensional_type_field = new DimensionalTypeResult();
        MapTypeResult map_type_field = new MapTypeResult();
        SingletonTypeResult singleton_type_field = new SingletonTypeResult();
        CTCodeFileParser c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser();
        ExternalDefinitionParser external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser();
        UnmanagedTypeParser unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser();
        DefinitionParser definition_parser_instance = this.parser_network.GetDefinitionParser();
        InterfaceDefParser interface_def_parser_instance = this.parser_network.GetInterfaceDefParser();
        ClassDefParser class_def_parser_instance = this.parser_network.GetClassDefParser();
        ImplementationSpecParser implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser();
        ContentDeclarationParser content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser();
        ContentDefinitionParser content_definition_parser_instance = this.parser_network.GetContentDefinitionParser();
        PrimativeTypeParser primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser();
        DefinedTypeParser defined_type_parser_instance = this.parser_network.GetDefinedTypeParser();
        SingletonTypeParser singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser();
        DimensionalNoteParser dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser();
        DimensionalTypeParser dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser();
        MapNoteParser map_note_parser_instance = this.parser_network.GetMapNoteParser();
        MapTypeParser map_type_parser_instance = this.parser_network.GetMapTypeParser();
        ValueTypeParser value_type_parser_instance = this.parser_network.GetValueTypeParser();
        ParameterListDefParser parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser();
        ParameterListParser parameter_list_parser_instance = this.parser_network.GetParameterListParser();
        CodeBlockParser code_block_parser_instance = this.parser_network.GetCodeBlockParser();
        DeclarationAssignParser declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser();
        DeclarationParser declaration_parser_instance = this.parser_network.GetDeclarationParser();
        AssignmentParser assignment_parser_instance = this.parser_network.GetAssignmentParser();
        ReturnParser return_parser_instance = this.parser_network.GetReturnParser();
        ElseTailParser else_tail_parser_instance = this.parser_network.GetElseTailParser();
        ConditionalParser conditional_parser_instance = this.parser_network.GetConditionalParser();
        LoopParser loop_parser_instance = this.parser_network.GetLoopParser();
        CallParser call_parser_instance = this.parser_network.GetCallParser();
        AllocateParser allocate_parser_instance = this.parser_network.GetAllocateParser();
        InstructionParser instruction_parser_instance = this.parser_network.GetInstructionParser();
        RValueSingleParser r_value_single_parser_instance = this.parser_network.GetRValueSingleParser();
        RValueTailParser r_value_tail_parser_instance = this.parser_network.GetRValueTailParser();
        RValueParser r_value_parser_instance = this.parser_network.GetRValueParser();
        BinaryOperatorParser binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser();
        UnaryOperatorParser unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser();
        CommentParser comment_parser_instance = this.parser_network.GetCommentParser();
        NonStarCharacterParser non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser();
        NonSlashCharacterParser non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser();
        CommentContentParser comment_content_parser_instance = this.parser_network.GetCommentContentParser();
        QualfiedNameParser qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser();
        NameTailParser name_tail_parser_instance = this.parser_network.GetNameTailParser();
        NameParser name_parser_instance = this.parser_network.GetNameParser();
        NameCharacterParser name_character_parser_instance = this.parser_network.GetNameCharacterParser();
        BooleanParser boolean_parser_instance = this.parser_network.GetBooleanParser();
        ByteParser byte_parser_instance = this.parser_network.GetByteParser();
        ByteDigitParser byte_digit_parser_instance = this.parser_network.GetByteDigitParser();
        NegativeParser negative_parser_instance = this.parser_network.GetNegativeParser();
        DecimalParser decimal_parser_instance = this.parser_network.GetDecimalParser();
        NumberParser number_parser_instance = this.parser_network.GetNumberParser();
        DigitParser digit_parser_instance = this.parser_network.GetDigitParser();
        LiteralParser literal_parser_instance = this.parser_network.GetLiteralParser();
        LiteralCharacterParser literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser();
        WhitespaceParser whitespace_parser_instance = this.parser_network.GetWhitespaceParser();
        StringParser string_parser_instance = this.parser_network.GetStringParser();
        CharacterParser character_parser_instance = this.parser_network.GetCharacterParser();
        CharacterRangeParser character_range_parser_instance = this.parser_network.GetCharacterRangeParser();
        if (AsBoolean((AsBoolean(true) && AsBoolean(dimensional_type_parser_instance.ParseSingleSave(index, dimensional_type_field)))))
        {
            instance.SetDimensionalType(dimensional_type_field.GetValue());
            instance.SetMapType(map_type_field.GetValue());
            instance.SetSingletonType(singleton_type_field.GetValue());
            consumed_string.SetLength((index.GetStart()-index_start));
            instance.SetLengthString(consumed_string);
            result.SetValue(instance);
            result.SetResult(true);
            return result.GetResult();
        }
        else
        {
            index.SetStart(index_start);
            index.SetLength(index_length);
            dimensional_type_field = new DimensionalTypeResult();
            map_type_field = new MapTypeResult();
            singleton_type_field = new SingletonTypeResult();
        }
        if (AsBoolean((AsBoolean(true) && AsBoolean(map_type_parser_instance.ParseSingleSave(index, map_type_field)))))
        {
            instance.SetDimensionalType(dimensional_type_field.GetValue());
            instance.SetMapType(map_type_field.GetValue());
            instance.SetSingletonType(singleton_type_field.GetValue());
            consumed_string.SetLength((index.GetStart()-index_start));
            instance.SetLengthString(consumed_string);
            result.SetValue(instance);
            result.SetResult(true);
            return result.GetResult();
        }
        else
        {
            index.SetStart(index_start);
            index.SetLength(index_length);
            dimensional_type_field = new DimensionalTypeResult();
            map_type_field = new MapTypeResult();
            singleton_type_field = new SingletonTypeResult();
        }
        if (AsBoolean((AsBoolean(true) && AsBoolean(singleton_type_parser_instance.ParseSingleSave(index, singleton_type_field)))))
        {
            instance.SetDimensionalType(dimensional_type_field.GetValue());
            instance.SetMapType(map_type_field.GetValue());
            instance.SetSingletonType(singleton_type_field.GetValue());
            consumed_string.SetLength((index.GetStart()-index_start));
            instance.SetLengthString(consumed_string);
            result.SetValue(instance);
            result.SetResult(true);
            return result.GetResult();
        }
        else
        {
            index.SetStart(index_start);
            index.SetLength(index_length);
            dimensional_type_field = new DimensionalTypeResult();
            map_type_field = new MapTypeResult();
            singleton_type_field = new SingletonTypeResult();
        }
        result.SetResult(false);
        return result.GetResult();
    }

    public boolean ParseSingle(LengthString index)
    {
        ValueTypeResult result = new ValueTypeResult();
        return this.ParseSingleSave(index, result);
    }

    public boolean ParseOptionalSave(LengthString index, ValueTypeResult result)
    {
        this.ParseSingleSave(index, result);
        result.SetResult(true);
        return true;
    }

    public boolean ParseOptional(LengthString index)
    {
        ValueTypeResult result = new ValueTypeResult();
        return this.ParseOptionalSave(index, result);
    }

    public boolean ParseManySave(LengthString index, ValueTypeListResult list_result, int minimum, int maximum)
    {
        int index_start = index.GetStart();
        int index_length = index.GetLength();
        java.util.ArrayList<ValueType> results = new java.util.ArrayList<>();
        int count = 0;
        int max_check = maximum;
        boolean check_next = true;
        if (AsBoolean((maximum<0)))
        {
            max_check = (count+1);
        }
        while (AsBoolean((AsBoolean(check_next) && AsBoolean((count<max_check)))))
        {
            ValueTypeResult result = new ValueTypeResult();
            this.ParseSingleSave(index, result);
            check_next = result.GetResult();
            if (AsBoolean(result.GetResult()))
            {
                count = (count+1);
                Append(results, result.GetValue());
            }
            if (AsBoolean((maximum<0)))
            {
                max_check = (count+1);
            }
        }
        if (AsBoolean((AsBoolean((count>=minimum)) && AsBoolean((count<=max_check)))))
        {
            list_result.SetValue(results);
            list_result.SetResult(true);
        }
        else
        {
            index.SetStart(index_start);
            index.SetLength(index_length);
            list_result.SetResult(false);
        }
        return list_result.GetResult();
    }

    public boolean ParseMany(LengthString index, int minimum, int maximum)
    {
        ValueTypeListResult result = new ValueTypeListResult();
        return this.ParseManySave(index, result, minimum, maximum);
    }

    private ParserNetwork parser_network;

    private static <T> void ClearList(java.util.ArrayList<T> input) { input.clear(); }
    private static <T> int Size(java.util.ArrayList<T> input) { return input.size(); }
    private static <T> T Element(java.util.ArrayList<T> input, int element) { return input.get(element); }
    private static <T> void Append(java.util.ArrayList<T> input, T element) { input.add(element); }
    private static <T> void ClearMap(java.util.HashMap<java.lang.String, T> input) { input.clear(); }
    private static <T> void SetKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key, T element) { input.put(key, element); }
    private static <T> java.util.ArrayList<java.lang.String> Keys(java.util.HashMap<java.lang.String, T> input) { return new java.util.ArrayList<>(input.keySet()); }
    private static <T> boolean HasKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key) { return input.containsKey(key); }
    private static <T> T GetKV(java.util.HashMap<java.lang.String, T> input, java.lang.String key) { return input.get(key); }
    private static int Length(java.lang.String input) { return input.length(); }
    private static java.lang.String At(java.lang.String input, int index) { try { return input.substring(index, index + 1);} catch(Exception e) { return ""; }}
    private static int IntAt(java.lang.String input, int index) { return (int)input.charAt(index); }
    private static java.lang.String Concat(java.lang.String left, java.lang.String right) { return left + right; }
    private static <T extends Object> boolean AsBoolean(T value) { return value != null; }
    private static boolean AsBoolean(boolean value) { return value; }
    private static boolean Equals(java.lang.String left, java.lang.String right) { return left.equals(right); }
    private static boolean Equals(boolean left, boolean right) { return left == right; }
    private static boolean Equals(int left, int right) { return left == right; }
    private static boolean Equals(float left, float right) { return left == right; }
}
