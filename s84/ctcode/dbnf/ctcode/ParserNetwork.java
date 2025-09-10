package s84.ctcode.dbnf.ctcode;

public class ParserNetwork {
    public ParserNetwork()
    {
        this.c_t_code_file_parser_field = null;
        this.external_definition_parser_field = null;
        this.unmanaged_type_parser_field = null;
        this.definition_parser_field = null;
        this.interface_def_parser_field = null;
        this.class_def_parser_field = null;
        this.implementation_spec_parser_field = null;
        this.content_declaration_parser_field = null;
        this.content_definition_parser_field = null;
        this.primative_type_parser_field = null;
        this.defined_type_parser_field = null;
        this.singleton_type_parser_field = null;
        this.dimensional_note_parser_field = null;
        this.dimensional_type_parser_field = null;
        this.map_note_parser_field = null;
        this.map_type_parser_field = null;
        this.value_type_parser_field = null;
        this.parameter_list_def_parser_field = null;
        this.parameter_list_parser_field = null;
        this.code_block_parser_field = null;
        this.declaration_assign_parser_field = null;
        this.declaration_parser_field = null;
        this.assignment_parser_field = null;
        this.return_parser_field = null;
        this.else_tail_parser_field = null;
        this.conditional_parser_field = null;
        this.loop_parser_field = null;
        this.call_parser_field = null;
        this.allocate_parser_field = null;
        this.instruction_parser_field = null;
        this.r_value_single_parser_field = null;
        this.r_value_tail_parser_field = null;
        this.r_value_parser_field = null;
        this.binary_operator_parser_field = null;
        this.unary_operator_parser_field = null;
        this.comment_parser_field = null;
        this.non_star_character_parser_field = null;
        this.non_slash_character_parser_field = null;
        this.comment_content_parser_field = null;
        this.qualfied_name_parser_field = null;
        this.name_tail_parser_field = null;
        this.name_parser_field = null;
        this.name_character_parser_field = null;
        this.boolean_parser_field = null;
        this.byte_parser_field = null;
        this.byte_digit_parser_field = null;
        this.negative_parser_field = null;
        this.decimal_parser_field = null;
        this.number_parser_field = null;
        this.digit_parser_field = null;
        this.literal_parser_field = null;
        this.literal_character_parser_field = null;
        this.whitespace_parser_field = null;
        this.string_parser_field = null;
        this.character_parser_field = null;
        this.character_range_parser_field = null;
    }

    public CTCodeFileParser GetCTCodeFileParser()
    {
        return this.c_t_code_file_parser_field;
    }

    public ExternalDefinitionParser GetExternalDefinitionParser()
    {
        return this.external_definition_parser_field;
    }

    public UnmanagedTypeParser GetUnmanagedTypeParser()
    {
        return this.unmanaged_type_parser_field;
    }

    public DefinitionParser GetDefinitionParser()
    {
        return this.definition_parser_field;
    }

    public InterfaceDefParser GetInterfaceDefParser()
    {
        return this.interface_def_parser_field;
    }

    public ClassDefParser GetClassDefParser()
    {
        return this.class_def_parser_field;
    }

    public ImplementationSpecParser GetImplementationSpecParser()
    {
        return this.implementation_spec_parser_field;
    }

    public ContentDeclarationParser GetContentDeclarationParser()
    {
        return this.content_declaration_parser_field;
    }

    public ContentDefinitionParser GetContentDefinitionParser()
    {
        return this.content_definition_parser_field;
    }

    public PrimativeTypeParser GetPrimativeTypeParser()
    {
        return this.primative_type_parser_field;
    }

    public DefinedTypeParser GetDefinedTypeParser()
    {
        return this.defined_type_parser_field;
    }

    public SingletonTypeParser GetSingletonTypeParser()
    {
        return this.singleton_type_parser_field;
    }

    public DimensionalNoteParser GetDimensionalNoteParser()
    {
        return this.dimensional_note_parser_field;
    }

    public DimensionalTypeParser GetDimensionalTypeParser()
    {
        return this.dimensional_type_parser_field;
    }

    public MapNoteParser GetMapNoteParser()
    {
        return this.map_note_parser_field;
    }

    public MapTypeParser GetMapTypeParser()
    {
        return this.map_type_parser_field;
    }

    public ValueTypeParser GetValueTypeParser()
    {
        return this.value_type_parser_field;
    }

    public ParameterListDefParser GetParameterListDefParser()
    {
        return this.parameter_list_def_parser_field;
    }

    public ParameterListParser GetParameterListParser()
    {
        return this.parameter_list_parser_field;
    }

    public CodeBlockParser GetCodeBlockParser()
    {
        return this.code_block_parser_field;
    }

    public DeclarationAssignParser GetDeclarationAssignParser()
    {
        return this.declaration_assign_parser_field;
    }

    public DeclarationParser GetDeclarationParser()
    {
        return this.declaration_parser_field;
    }

    public AssignmentParser GetAssignmentParser()
    {
        return this.assignment_parser_field;
    }

    public ReturnParser GetReturnParser()
    {
        return this.return_parser_field;
    }

    public ElseTailParser GetElseTailParser()
    {
        return this.else_tail_parser_field;
    }

    public ConditionalParser GetConditionalParser()
    {
        return this.conditional_parser_field;
    }

    public LoopParser GetLoopParser()
    {
        return this.loop_parser_field;
    }

    public CallParser GetCallParser()
    {
        return this.call_parser_field;
    }

    public AllocateParser GetAllocateParser()
    {
        return this.allocate_parser_field;
    }

    public InstructionParser GetInstructionParser()
    {
        return this.instruction_parser_field;
    }

    public RValueSingleParser GetRValueSingleParser()
    {
        return this.r_value_single_parser_field;
    }

    public RValueTailParser GetRValueTailParser()
    {
        return this.r_value_tail_parser_field;
    }

    public RValueParser GetRValueParser()
    {
        return this.r_value_parser_field;
    }

    public BinaryOperatorParser GetBinaryOperatorParser()
    {
        return this.binary_operator_parser_field;
    }

    public UnaryOperatorParser GetUnaryOperatorParser()
    {
        return this.unary_operator_parser_field;
    }

    public CommentParser GetCommentParser()
    {
        return this.comment_parser_field;
    }

    public NonStarCharacterParser GetNonStarCharacterParser()
    {
        return this.non_star_character_parser_field;
    }

    public NonSlashCharacterParser GetNonSlashCharacterParser()
    {
        return this.non_slash_character_parser_field;
    }

    public CommentContentParser GetCommentContentParser()
    {
        return this.comment_content_parser_field;
    }

    public QualfiedNameParser GetQualfiedNameParser()
    {
        return this.qualfied_name_parser_field;
    }

    public NameTailParser GetNameTailParser()
    {
        return this.name_tail_parser_field;
    }

    public NameParser GetNameParser()
    {
        return this.name_parser_field;
    }

    public NameCharacterParser GetNameCharacterParser()
    {
        return this.name_character_parser_field;
    }

    public BooleanParser GetBooleanParser()
    {
        return this.boolean_parser_field;
    }

    public ByteParser GetByteParser()
    {
        return this.byte_parser_field;
    }

    public ByteDigitParser GetByteDigitParser()
    {
        return this.byte_digit_parser_field;
    }

    public NegativeParser GetNegativeParser()
    {
        return this.negative_parser_field;
    }

    public DecimalParser GetDecimalParser()
    {
        return this.decimal_parser_field;
    }

    public NumberParser GetNumberParser()
    {
        return this.number_parser_field;
    }

    public DigitParser GetDigitParser()
    {
        return this.digit_parser_field;
    }

    public LiteralParser GetLiteralParser()
    {
        return this.literal_parser_field;
    }

    public LiteralCharacterParser GetLiteralCharacterParser()
    {
        return this.literal_character_parser_field;
    }

    public WhitespaceParser GetWhitespaceParser()
    {
        return this.whitespace_parser_field;
    }

    public StringParser GetStringParser()
    {
        return this.string_parser_field;
    }

    public CharacterParser GetCharacterParser()
    {
        return this.character_parser_field;
    }

    public CharacterRangeParser GetCharacterRangeParser()
    {
        return this.character_range_parser_field;
    }

    public void Initialize()
    {
        this.c_t_code_file_parser_field = new CTCodeFileParser();
        this.c_t_code_file_parser_field.SetParserNetwork(this);
        this.external_definition_parser_field = new ExternalDefinitionParser();
        this.external_definition_parser_field.SetParserNetwork(this);
        this.unmanaged_type_parser_field = new UnmanagedTypeParser();
        this.unmanaged_type_parser_field.SetParserNetwork(this);
        this.definition_parser_field = new DefinitionParser();
        this.definition_parser_field.SetParserNetwork(this);
        this.interface_def_parser_field = new InterfaceDefParser();
        this.interface_def_parser_field.SetParserNetwork(this);
        this.class_def_parser_field = new ClassDefParser();
        this.class_def_parser_field.SetParserNetwork(this);
        this.implementation_spec_parser_field = new ImplementationSpecParser();
        this.implementation_spec_parser_field.SetParserNetwork(this);
        this.content_declaration_parser_field = new ContentDeclarationParser();
        this.content_declaration_parser_field.SetParserNetwork(this);
        this.content_definition_parser_field = new ContentDefinitionParser();
        this.content_definition_parser_field.SetParserNetwork(this);
        this.primative_type_parser_field = new PrimativeTypeParser();
        this.primative_type_parser_field.SetParserNetwork(this);
        this.defined_type_parser_field = new DefinedTypeParser();
        this.defined_type_parser_field.SetParserNetwork(this);
        this.singleton_type_parser_field = new SingletonTypeParser();
        this.singleton_type_parser_field.SetParserNetwork(this);
        this.dimensional_note_parser_field = new DimensionalNoteParser();
        this.dimensional_note_parser_field.SetParserNetwork(this);
        this.dimensional_type_parser_field = new DimensionalTypeParser();
        this.dimensional_type_parser_field.SetParserNetwork(this);
        this.map_note_parser_field = new MapNoteParser();
        this.map_note_parser_field.SetParserNetwork(this);
        this.map_type_parser_field = new MapTypeParser();
        this.map_type_parser_field.SetParserNetwork(this);
        this.value_type_parser_field = new ValueTypeParser();
        this.value_type_parser_field.SetParserNetwork(this);
        this.parameter_list_def_parser_field = new ParameterListDefParser();
        this.parameter_list_def_parser_field.SetParserNetwork(this);
        this.parameter_list_parser_field = new ParameterListParser();
        this.parameter_list_parser_field.SetParserNetwork(this);
        this.code_block_parser_field = new CodeBlockParser();
        this.code_block_parser_field.SetParserNetwork(this);
        this.declaration_assign_parser_field = new DeclarationAssignParser();
        this.declaration_assign_parser_field.SetParserNetwork(this);
        this.declaration_parser_field = new DeclarationParser();
        this.declaration_parser_field.SetParserNetwork(this);
        this.assignment_parser_field = new AssignmentParser();
        this.assignment_parser_field.SetParserNetwork(this);
        this.return_parser_field = new ReturnParser();
        this.return_parser_field.SetParserNetwork(this);
        this.else_tail_parser_field = new ElseTailParser();
        this.else_tail_parser_field.SetParserNetwork(this);
        this.conditional_parser_field = new ConditionalParser();
        this.conditional_parser_field.SetParserNetwork(this);
        this.loop_parser_field = new LoopParser();
        this.loop_parser_field.SetParserNetwork(this);
        this.call_parser_field = new CallParser();
        this.call_parser_field.SetParserNetwork(this);
        this.allocate_parser_field = new AllocateParser();
        this.allocate_parser_field.SetParserNetwork(this);
        this.instruction_parser_field = new InstructionParser();
        this.instruction_parser_field.SetParserNetwork(this);
        this.r_value_single_parser_field = new RValueSingleParser();
        this.r_value_single_parser_field.SetParserNetwork(this);
        this.r_value_tail_parser_field = new RValueTailParser();
        this.r_value_tail_parser_field.SetParserNetwork(this);
        this.r_value_parser_field = new RValueParser();
        this.r_value_parser_field.SetParserNetwork(this);
        this.binary_operator_parser_field = new BinaryOperatorParser();
        this.binary_operator_parser_field.SetParserNetwork(this);
        this.unary_operator_parser_field = new UnaryOperatorParser();
        this.unary_operator_parser_field.SetParserNetwork(this);
        this.comment_parser_field = new CommentParser();
        this.comment_parser_field.SetParserNetwork(this);
        this.non_star_character_parser_field = new NonStarCharacterParser();
        this.non_star_character_parser_field.SetParserNetwork(this);
        this.non_slash_character_parser_field = new NonSlashCharacterParser();
        this.non_slash_character_parser_field.SetParserNetwork(this);
        this.comment_content_parser_field = new CommentContentParser();
        this.comment_content_parser_field.SetParserNetwork(this);
        this.qualfied_name_parser_field = new QualfiedNameParser();
        this.qualfied_name_parser_field.SetParserNetwork(this);
        this.name_tail_parser_field = new NameTailParser();
        this.name_tail_parser_field.SetParserNetwork(this);
        this.name_parser_field = new NameParser();
        this.name_parser_field.SetParserNetwork(this);
        this.name_character_parser_field = new NameCharacterParser();
        this.name_character_parser_field.SetParserNetwork(this);
        this.boolean_parser_field = new BooleanParser();
        this.boolean_parser_field.SetParserNetwork(this);
        this.byte_parser_field = new ByteParser();
        this.byte_parser_field.SetParserNetwork(this);
        this.byte_digit_parser_field = new ByteDigitParser();
        this.byte_digit_parser_field.SetParserNetwork(this);
        this.negative_parser_field = new NegativeParser();
        this.negative_parser_field.SetParserNetwork(this);
        this.decimal_parser_field = new DecimalParser();
        this.decimal_parser_field.SetParserNetwork(this);
        this.number_parser_field = new NumberParser();
        this.number_parser_field.SetParserNetwork(this);
        this.digit_parser_field = new DigitParser();
        this.digit_parser_field.SetParserNetwork(this);
        this.literal_parser_field = new LiteralParser();
        this.literal_parser_field.SetParserNetwork(this);
        this.literal_character_parser_field = new LiteralCharacterParser();
        this.literal_character_parser_field.SetParserNetwork(this);
        this.whitespace_parser_field = new WhitespaceParser();
        this.whitespace_parser_field.SetParserNetwork(this);
        this.string_parser_field = new StringParser();
        this.character_parser_field = new CharacterParser();
        this.character_range_parser_field = new CharacterRangeParser();
    }

    private CTCodeFileParser c_t_code_file_parser_field;
    private ExternalDefinitionParser external_definition_parser_field;
    private UnmanagedTypeParser unmanaged_type_parser_field;
    private DefinitionParser definition_parser_field;
    private InterfaceDefParser interface_def_parser_field;
    private ClassDefParser class_def_parser_field;
    private ImplementationSpecParser implementation_spec_parser_field;
    private ContentDeclarationParser content_declaration_parser_field;
    private ContentDefinitionParser content_definition_parser_field;
    private PrimativeTypeParser primative_type_parser_field;
    private DefinedTypeParser defined_type_parser_field;
    private SingletonTypeParser singleton_type_parser_field;
    private DimensionalNoteParser dimensional_note_parser_field;
    private DimensionalTypeParser dimensional_type_parser_field;
    private MapNoteParser map_note_parser_field;
    private MapTypeParser map_type_parser_field;
    private ValueTypeParser value_type_parser_field;
    private ParameterListDefParser parameter_list_def_parser_field;
    private ParameterListParser parameter_list_parser_field;
    private CodeBlockParser code_block_parser_field;
    private DeclarationAssignParser declaration_assign_parser_field;
    private DeclarationParser declaration_parser_field;
    private AssignmentParser assignment_parser_field;
    private ReturnParser return_parser_field;
    private ElseTailParser else_tail_parser_field;
    private ConditionalParser conditional_parser_field;
    private LoopParser loop_parser_field;
    private CallParser call_parser_field;
    private AllocateParser allocate_parser_field;
    private InstructionParser instruction_parser_field;
    private RValueSingleParser r_value_single_parser_field;
    private RValueTailParser r_value_tail_parser_field;
    private RValueParser r_value_parser_field;
    private BinaryOperatorParser binary_operator_parser_field;
    private UnaryOperatorParser unary_operator_parser_field;
    private CommentParser comment_parser_field;
    private NonStarCharacterParser non_star_character_parser_field;
    private NonSlashCharacterParser non_slash_character_parser_field;
    private CommentContentParser comment_content_parser_field;
    private QualfiedNameParser qualfied_name_parser_field;
    private NameTailParser name_tail_parser_field;
    private NameParser name_parser_field;
    private NameCharacterParser name_character_parser_field;
    private BooleanParser boolean_parser_field;
    private ByteParser byte_parser_field;
    private ByteDigitParser byte_digit_parser_field;
    private NegativeParser negative_parser_field;
    private DecimalParser decimal_parser_field;
    private NumberParser number_parser_field;
    private DigitParser digit_parser_field;
    private LiteralParser literal_parser_field;
    private LiteralCharacterParser literal_character_parser_field;
    private WhitespaceParser whitespace_parser_field;
    private StringParser string_parser_field;
    private CharacterParser character_parser_field;
    private CharacterRangeParser character_range_parser_field;

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
