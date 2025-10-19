function ClearList(input) { input.length = 0; }
function Size(input) { return input.length; }
function Element(input, element) { return input[element]; }
function Append(input, element) { input.push(element); }
function ClearMap(input) { input.clear(); }
function SetKV(input, key, element) { input.set(key, element); }
function Keys(input) { return Array.from(input.keys()); }
function HasKV(input, key) { return input.has(key); }
function GetKV(input, key) { return input.get(key); }
function Length(input) { return input.length; }
function At(input, index) { return input[index]; }
function IntAt(input, index) { return input.charCodeAt(index); }
function Concat(left, right) { return left + right; }

export class StringParser {
    constructor() {
    }

    ParseSingleSave(index, value, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var index_data = index.GetData()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new ReservedPrefixString()
        var value_length = Length(value)
        if (value_length>index.GetLength())
        {
            result.SetResult(false)
            return false
        }
        var offset_index = 0
        while (offset_index<value_length)
        {
            if (index_data.GetAt(index.GetStart()+offset_index)!=At(value,offset_index))
            {
                result.SetResult(false)
                return false
            }
            offset_index = offset_index+1
        }
        index.SetStart(index.GetStart()+value_length)
        index.SetLength(index.GetLength()-value_length)
        consumed_string.SetLength(index.GetStart()-index_start)
        instance.SetLengthString(consumed_string)
        result.SetValue(instance)
        result.SetResult(true)
        return true
    }

    ParseSingle(index, value)
    {
        var result = new StringResult()
        return this.ParseSingleSave(index,value,result)
    }
}

export class StringResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class StringListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class ReservedPrefixString {
    constructor() {
        this.length_string = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }
}

export class CharacterParser {
    constructor() {
    }

    ParseSingle(index, value)
    {
        if (0==index.GetLength())
        {
            return false
        }
        var index_data = index.GetData()
        var current_character = index_data.GetIntAt(index.GetStart())
        if (current_character==value)
        {
            index.SetStart(index.GetStart()+1)
            index.SetLength(index.GetLength()-1)
            return true
        }
        return false
    }
}

export class CharacterResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class CharacterListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class Character {
    constructor() {
        this.length_string = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }
}

export class CharacterRangeParser {
    constructor() {
    }

    ParseSingle(index, low_value, high_value)
    {
        if (0==index.GetLength())
        {
            return false
        }
        var index_data = index.GetData()
        var current_character = index_data.GetIntAt(index.GetStart())
        if (low_value<=current_character && current_character<=high_value)
        {
            index.SetStart(index.GetStart()+1)
            index.SetLength(index.GetLength()-1)
            return true
        }
        return false
    }
}

export class CharacterRangeResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class CharacterRangeListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class CharacterRange {
    constructor() {
        this.length_string = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }
}

export class ParserNetwork {
    constructor() {
        this.c_t_code_file_parser_field = null
        this.external_definition_parser_field = null
        this.unmanaged_type_parser_field = null
        this.definition_parser_field = null
        this.interface_def_parser_field = null
        this.class_def_parser_field = null
        this.implementation_spec_parser_field = null
        this.content_declaration_parser_field = null
        this.content_definition_parser_field = null
        this.primative_type_parser_field = null
        this.defined_type_parser_field = null
        this.singleton_type_parser_field = null
        this.dimensional_note_parser_field = null
        this.dimensional_type_parser_field = null
        this.map_note_parser_field = null
        this.map_type_parser_field = null
        this.value_type_parser_field = null
        this.parameter_list_def_parser_field = null
        this.parameter_list_parser_field = null
        this.code_block_parser_field = null
        this.declaration_assign_parser_field = null
        this.declaration_parser_field = null
        this.assignment_parser_field = null
        this.return_parser_field = null
        this.else_tail_parser_field = null
        this.conditional_parser_field = null
        this.loop_parser_field = null
        this.call_parser_field = null
        this.allocate_parser_field = null
        this.instruction_parser_field = null
        this.r_value_single_parser_field = null
        this.r_value_tail_parser_field = null
        this.r_value_parser_field = null
        this.binary_operator_parser_field = null
        this.unary_operator_parser_field = null
        this.comment_parser_field = null
        this.non_star_character_parser_field = null
        this.non_slash_character_parser_field = null
        this.comment_content_parser_field = null
        this.qualfied_name_parser_field = null
        this.name_tail_parser_field = null
        this.name_parser_field = null
        this.name_character_parser_field = null
        this.boolean_parser_field = null
        this.byte_parser_field = null
        this.byte_digit_parser_field = null
        this.negative_parser_field = null
        this.decimal_parser_field = null
        this.number_parser_field = null
        this.digit_parser_field = null
        this.literal_parser_field = null
        this.literal_character_parser_field = null
        this.whitespace_parser_field = null
        this.string_parser_field = null
        this.character_parser_field = null
        this.character_range_parser_field = null
    }

    GetCTCodeFileParser()
    {
        return this.c_t_code_file_parser_field
    }

    GetExternalDefinitionParser()
    {
        return this.external_definition_parser_field
    }

    GetUnmanagedTypeParser()
    {
        return this.unmanaged_type_parser_field
    }

    GetDefinitionParser()
    {
        return this.definition_parser_field
    }

    GetInterfaceDefParser()
    {
        return this.interface_def_parser_field
    }

    GetClassDefParser()
    {
        return this.class_def_parser_field
    }

    GetImplementationSpecParser()
    {
        return this.implementation_spec_parser_field
    }

    GetContentDeclarationParser()
    {
        return this.content_declaration_parser_field
    }

    GetContentDefinitionParser()
    {
        return this.content_definition_parser_field
    }

    GetPrimativeTypeParser()
    {
        return this.primative_type_parser_field
    }

    GetDefinedTypeParser()
    {
        return this.defined_type_parser_field
    }

    GetSingletonTypeParser()
    {
        return this.singleton_type_parser_field
    }

    GetDimensionalNoteParser()
    {
        return this.dimensional_note_parser_field
    }

    GetDimensionalTypeParser()
    {
        return this.dimensional_type_parser_field
    }

    GetMapNoteParser()
    {
        return this.map_note_parser_field
    }

    GetMapTypeParser()
    {
        return this.map_type_parser_field
    }

    GetValueTypeParser()
    {
        return this.value_type_parser_field
    }

    GetParameterListDefParser()
    {
        return this.parameter_list_def_parser_field
    }

    GetParameterListParser()
    {
        return this.parameter_list_parser_field
    }

    GetCodeBlockParser()
    {
        return this.code_block_parser_field
    }

    GetDeclarationAssignParser()
    {
        return this.declaration_assign_parser_field
    }

    GetDeclarationParser()
    {
        return this.declaration_parser_field
    }

    GetAssignmentParser()
    {
        return this.assignment_parser_field
    }

    GetReturnParser()
    {
        return this.return_parser_field
    }

    GetElseTailParser()
    {
        return this.else_tail_parser_field
    }

    GetConditionalParser()
    {
        return this.conditional_parser_field
    }

    GetLoopParser()
    {
        return this.loop_parser_field
    }

    GetCallParser()
    {
        return this.call_parser_field
    }

    GetAllocateParser()
    {
        return this.allocate_parser_field
    }

    GetInstructionParser()
    {
        return this.instruction_parser_field
    }

    GetRValueSingleParser()
    {
        return this.r_value_single_parser_field
    }

    GetRValueTailParser()
    {
        return this.r_value_tail_parser_field
    }

    GetRValueParser()
    {
        return this.r_value_parser_field
    }

    GetBinaryOperatorParser()
    {
        return this.binary_operator_parser_field
    }

    GetUnaryOperatorParser()
    {
        return this.unary_operator_parser_field
    }

    GetCommentParser()
    {
        return this.comment_parser_field
    }

    GetNonStarCharacterParser()
    {
        return this.non_star_character_parser_field
    }

    GetNonSlashCharacterParser()
    {
        return this.non_slash_character_parser_field
    }

    GetCommentContentParser()
    {
        return this.comment_content_parser_field
    }

    GetQualfiedNameParser()
    {
        return this.qualfied_name_parser_field
    }

    GetNameTailParser()
    {
        return this.name_tail_parser_field
    }

    GetNameParser()
    {
        return this.name_parser_field
    }

    GetNameCharacterParser()
    {
        return this.name_character_parser_field
    }

    GetBooleanParser()
    {
        return this.boolean_parser_field
    }

    GetByteParser()
    {
        return this.byte_parser_field
    }

    GetByteDigitParser()
    {
        return this.byte_digit_parser_field
    }

    GetNegativeParser()
    {
        return this.negative_parser_field
    }

    GetDecimalParser()
    {
        return this.decimal_parser_field
    }

    GetNumberParser()
    {
        return this.number_parser_field
    }

    GetDigitParser()
    {
        return this.digit_parser_field
    }

    GetLiteralParser()
    {
        return this.literal_parser_field
    }

    GetLiteralCharacterParser()
    {
        return this.literal_character_parser_field
    }

    GetWhitespaceParser()
    {
        return this.whitespace_parser_field
    }

    GetStringParser()
    {
        return this.string_parser_field
    }

    GetCharacterParser()
    {
        return this.character_parser_field
    }

    GetCharacterRangeParser()
    {
        return this.character_range_parser_field
    }

    Initialize()
    {
        this.c_t_code_file_parser_field = new CTCodeFileParser()
        this.c_t_code_file_parser_field.SetParserNetwork(this)
        this.external_definition_parser_field = new ExternalDefinitionParser()
        this.external_definition_parser_field.SetParserNetwork(this)
        this.unmanaged_type_parser_field = new UnmanagedTypeParser()
        this.unmanaged_type_parser_field.SetParserNetwork(this)
        this.definition_parser_field = new DefinitionParser()
        this.definition_parser_field.SetParserNetwork(this)
        this.interface_def_parser_field = new InterfaceDefParser()
        this.interface_def_parser_field.SetParserNetwork(this)
        this.class_def_parser_field = new ClassDefParser()
        this.class_def_parser_field.SetParserNetwork(this)
        this.implementation_spec_parser_field = new ImplementationSpecParser()
        this.implementation_spec_parser_field.SetParserNetwork(this)
        this.content_declaration_parser_field = new ContentDeclarationParser()
        this.content_declaration_parser_field.SetParserNetwork(this)
        this.content_definition_parser_field = new ContentDefinitionParser()
        this.content_definition_parser_field.SetParserNetwork(this)
        this.primative_type_parser_field = new PrimativeTypeParser()
        this.primative_type_parser_field.SetParserNetwork(this)
        this.defined_type_parser_field = new DefinedTypeParser()
        this.defined_type_parser_field.SetParserNetwork(this)
        this.singleton_type_parser_field = new SingletonTypeParser()
        this.singleton_type_parser_field.SetParserNetwork(this)
        this.dimensional_note_parser_field = new DimensionalNoteParser()
        this.dimensional_note_parser_field.SetParserNetwork(this)
        this.dimensional_type_parser_field = new DimensionalTypeParser()
        this.dimensional_type_parser_field.SetParserNetwork(this)
        this.map_note_parser_field = new MapNoteParser()
        this.map_note_parser_field.SetParserNetwork(this)
        this.map_type_parser_field = new MapTypeParser()
        this.map_type_parser_field.SetParserNetwork(this)
        this.value_type_parser_field = new ValueTypeParser()
        this.value_type_parser_field.SetParserNetwork(this)
        this.parameter_list_def_parser_field = new ParameterListDefParser()
        this.parameter_list_def_parser_field.SetParserNetwork(this)
        this.parameter_list_parser_field = new ParameterListParser()
        this.parameter_list_parser_field.SetParserNetwork(this)
        this.code_block_parser_field = new CodeBlockParser()
        this.code_block_parser_field.SetParserNetwork(this)
        this.declaration_assign_parser_field = new DeclarationAssignParser()
        this.declaration_assign_parser_field.SetParserNetwork(this)
        this.declaration_parser_field = new DeclarationParser()
        this.declaration_parser_field.SetParserNetwork(this)
        this.assignment_parser_field = new AssignmentParser()
        this.assignment_parser_field.SetParserNetwork(this)
        this.return_parser_field = new ReturnParser()
        this.return_parser_field.SetParserNetwork(this)
        this.else_tail_parser_field = new ElseTailParser()
        this.else_tail_parser_field.SetParserNetwork(this)
        this.conditional_parser_field = new ConditionalParser()
        this.conditional_parser_field.SetParserNetwork(this)
        this.loop_parser_field = new LoopParser()
        this.loop_parser_field.SetParserNetwork(this)
        this.call_parser_field = new CallParser()
        this.call_parser_field.SetParserNetwork(this)
        this.allocate_parser_field = new AllocateParser()
        this.allocate_parser_field.SetParserNetwork(this)
        this.instruction_parser_field = new InstructionParser()
        this.instruction_parser_field.SetParserNetwork(this)
        this.r_value_single_parser_field = new RValueSingleParser()
        this.r_value_single_parser_field.SetParserNetwork(this)
        this.r_value_tail_parser_field = new RValueTailParser()
        this.r_value_tail_parser_field.SetParserNetwork(this)
        this.r_value_parser_field = new RValueParser()
        this.r_value_parser_field.SetParserNetwork(this)
        this.binary_operator_parser_field = new BinaryOperatorParser()
        this.binary_operator_parser_field.SetParserNetwork(this)
        this.unary_operator_parser_field = new UnaryOperatorParser()
        this.unary_operator_parser_field.SetParserNetwork(this)
        this.comment_parser_field = new CommentParser()
        this.comment_parser_field.SetParserNetwork(this)
        this.non_star_character_parser_field = new NonStarCharacterParser()
        this.non_star_character_parser_field.SetParserNetwork(this)
        this.non_slash_character_parser_field = new NonSlashCharacterParser()
        this.non_slash_character_parser_field.SetParserNetwork(this)
        this.comment_content_parser_field = new CommentContentParser()
        this.comment_content_parser_field.SetParserNetwork(this)
        this.qualfied_name_parser_field = new QualfiedNameParser()
        this.qualfied_name_parser_field.SetParserNetwork(this)
        this.name_tail_parser_field = new NameTailParser()
        this.name_tail_parser_field.SetParserNetwork(this)
        this.name_parser_field = new NameParser()
        this.name_parser_field.SetParserNetwork(this)
        this.name_character_parser_field = new NameCharacterParser()
        this.name_character_parser_field.SetParserNetwork(this)
        this.boolean_parser_field = new BooleanParser()
        this.boolean_parser_field.SetParserNetwork(this)
        this.byte_parser_field = new ByteParser()
        this.byte_parser_field.SetParserNetwork(this)
        this.byte_digit_parser_field = new ByteDigitParser()
        this.byte_digit_parser_field.SetParserNetwork(this)
        this.negative_parser_field = new NegativeParser()
        this.negative_parser_field.SetParserNetwork(this)
        this.decimal_parser_field = new DecimalParser()
        this.decimal_parser_field.SetParserNetwork(this)
        this.number_parser_field = new NumberParser()
        this.number_parser_field.SetParserNetwork(this)
        this.digit_parser_field = new DigitParser()
        this.digit_parser_field.SetParserNetwork(this)
        this.literal_parser_field = new LiteralParser()
        this.literal_parser_field.SetParserNetwork(this)
        this.literal_character_parser_field = new LiteralCharacterParser()
        this.literal_character_parser_field.SetParserNetwork(this)
        this.whitespace_parser_field = new WhitespaceParser()
        this.whitespace_parser_field.SetParserNetwork(this)
        this.string_parser_field = new StringParser()
        this.character_parser_field = new CharacterParser()
        this.character_range_parser_field = new CharacterRangeParser()
    }
}

export class DBNFOmniType {
    constructor() {
        this.c_t_code_file_field = null
        this.external_definition_field = null
        this.unmanaged_type_field = null
        this.definition_field = null
        this.interface_def_field = null
        this.class_def_field = null
        this.implementation_spec_field = null
        this.content_declaration_field = null
        this.content_definition_field = null
        this.primative_type_field = null
        this.defined_type_field = null
        this.singleton_type_field = null
        this.dimensional_note_field = null
        this.dimensional_type_field = null
        this.map_note_field = null
        this.map_type_field = null
        this.value_type_field = null
        this.parameter_list_def_field = null
        this.parameter_list_field = null
        this.code_block_field = null
        this.declaration_assign_field = null
        this.declaration_field = null
        this.assignment_field = null
        this.return_field = null
        this.else_tail_field = null
        this.conditional_field = null
        this.loop_field = null
        this.call_field = null
        this.allocate_field = null
        this.instruction_field = null
        this.r_value_single_field = null
        this.r_value_tail_field = null
        this.r_value_field = null
        this.binary_operator_field = null
        this.unary_operator_field = null
        this.comment_field = null
        this.non_star_character_field = null
        this.non_slash_character_field = null
        this.comment_content_field = null
        this.qualfied_name_field = null
        this.name_tail_field = null
        this.name_field = null
        this.name_character_field = null
        this.boolean_field = null
        this.byte_field = null
        this.byte_digit_field = null
        this.negative_field = null
        this.decimal_field = null
        this.number_field = null
        this.digit_field = null
        this.literal_field = null
        this.literal_character_field = null
        this.whitespace_field = null
    }

    SetCTCodeFile(input_value)
    {
        this.c_t_code_file_field = input_value
    }

    GetCTCodeFile()
    {
        return this.c_t_code_file_field
    }

    SetExternalDefinition(input_value)
    {
        this.external_definition_field = input_value
    }

    GetExternalDefinition()
    {
        return this.external_definition_field
    }

    SetUnmanagedType(input_value)
    {
        this.unmanaged_type_field = input_value
    }

    GetUnmanagedType()
    {
        return this.unmanaged_type_field
    }

    SetDefinition(input_value)
    {
        this.definition_field = input_value
    }

    GetDefinition()
    {
        return this.definition_field
    }

    SetInterfaceDef(input_value)
    {
        this.interface_def_field = input_value
    }

    GetInterfaceDef()
    {
        return this.interface_def_field
    }

    SetClassDef(input_value)
    {
        this.class_def_field = input_value
    }

    GetClassDef()
    {
        return this.class_def_field
    }

    SetImplementationSpec(input_value)
    {
        this.implementation_spec_field = input_value
    }

    GetImplementationSpec()
    {
        return this.implementation_spec_field
    }

    SetContentDeclaration(input_value)
    {
        this.content_declaration_field = input_value
    }

    GetContentDeclaration()
    {
        return this.content_declaration_field
    }

    SetContentDefinition(input_value)
    {
        this.content_definition_field = input_value
    }

    GetContentDefinition()
    {
        return this.content_definition_field
    }

    SetPrimativeType(input_value)
    {
        this.primative_type_field = input_value
    }

    GetPrimativeType()
    {
        return this.primative_type_field
    }

    SetDefinedType(input_value)
    {
        this.defined_type_field = input_value
    }

    GetDefinedType()
    {
        return this.defined_type_field
    }

    SetSingletonType(input_value)
    {
        this.singleton_type_field = input_value
    }

    GetSingletonType()
    {
        return this.singleton_type_field
    }

    SetDimensionalNote(input_value)
    {
        this.dimensional_note_field = input_value
    }

    GetDimensionalNote()
    {
        return this.dimensional_note_field
    }

    SetDimensionalType(input_value)
    {
        this.dimensional_type_field = input_value
    }

    GetDimensionalType()
    {
        return this.dimensional_type_field
    }

    SetMapNote(input_value)
    {
        this.map_note_field = input_value
    }

    GetMapNote()
    {
        return this.map_note_field
    }

    SetMapType(input_value)
    {
        this.map_type_field = input_value
    }

    GetMapType()
    {
        return this.map_type_field
    }

    SetValueType(input_value)
    {
        this.value_type_field = input_value
    }

    GetValueType()
    {
        return this.value_type_field
    }

    SetParameterListDef(input_value)
    {
        this.parameter_list_def_field = input_value
    }

    GetParameterListDef()
    {
        return this.parameter_list_def_field
    }

    SetParameterList(input_value)
    {
        this.parameter_list_field = input_value
    }

    GetParameterList()
    {
        return this.parameter_list_field
    }

    SetCodeBlock(input_value)
    {
        this.code_block_field = input_value
    }

    GetCodeBlock()
    {
        return this.code_block_field
    }

    SetDeclarationAssign(input_value)
    {
        this.declaration_assign_field = input_value
    }

    GetDeclarationAssign()
    {
        return this.declaration_assign_field
    }

    SetDeclaration(input_value)
    {
        this.declaration_field = input_value
    }

    GetDeclaration()
    {
        return this.declaration_field
    }

    SetAssignment(input_value)
    {
        this.assignment_field = input_value
    }

    GetAssignment()
    {
        return this.assignment_field
    }

    SetReturn(input_value)
    {
        this.return_field = input_value
    }

    GetReturn()
    {
        return this.return_field
    }

    SetElseTail(input_value)
    {
        this.else_tail_field = input_value
    }

    GetElseTail()
    {
        return this.else_tail_field
    }

    SetConditional(input_value)
    {
        this.conditional_field = input_value
    }

    GetConditional()
    {
        return this.conditional_field
    }

    SetLoop(input_value)
    {
        this.loop_field = input_value
    }

    GetLoop()
    {
        return this.loop_field
    }

    SetCall(input_value)
    {
        this.call_field = input_value
    }

    GetCall()
    {
        return this.call_field
    }

    SetAllocate(input_value)
    {
        this.allocate_field = input_value
    }

    GetAllocate()
    {
        return this.allocate_field
    }

    SetInstruction(input_value)
    {
        this.instruction_field = input_value
    }

    GetInstruction()
    {
        return this.instruction_field
    }

    SetRValueSingle(input_value)
    {
        this.r_value_single_field = input_value
    }

    GetRValueSingle()
    {
        return this.r_value_single_field
    }

    SetRValueTail(input_value)
    {
        this.r_value_tail_field = input_value
    }

    GetRValueTail()
    {
        return this.r_value_tail_field
    }

    SetRValue(input_value)
    {
        this.r_value_field = input_value
    }

    GetRValue()
    {
        return this.r_value_field
    }

    SetBinaryOperator(input_value)
    {
        this.binary_operator_field = input_value
    }

    GetBinaryOperator()
    {
        return this.binary_operator_field
    }

    SetUnaryOperator(input_value)
    {
        this.unary_operator_field = input_value
    }

    GetUnaryOperator()
    {
        return this.unary_operator_field
    }

    SetComment(input_value)
    {
        this.comment_field = input_value
    }

    GetComment()
    {
        return this.comment_field
    }

    SetNonStarCharacter(input_value)
    {
        this.non_star_character_field = input_value
    }

    GetNonStarCharacter()
    {
        return this.non_star_character_field
    }

    SetNonSlashCharacter(input_value)
    {
        this.non_slash_character_field = input_value
    }

    GetNonSlashCharacter()
    {
        return this.non_slash_character_field
    }

    SetCommentContent(input_value)
    {
        this.comment_content_field = input_value
    }

    GetCommentContent()
    {
        return this.comment_content_field
    }

    SetQualfiedName(input_value)
    {
        this.qualfied_name_field = input_value
    }

    GetQualfiedName()
    {
        return this.qualfied_name_field
    }

    SetNameTail(input_value)
    {
        this.name_tail_field = input_value
    }

    GetNameTail()
    {
        return this.name_tail_field
    }

    SetName(input_value)
    {
        this.name_field = input_value
    }

    GetName()
    {
        return this.name_field
    }

    SetNameCharacter(input_value)
    {
        this.name_character_field = input_value
    }

    GetNameCharacter()
    {
        return this.name_character_field
    }

    SetBoolean(input_value)
    {
        this.boolean_field = input_value
    }

    GetBoolean()
    {
        return this.boolean_field
    }

    SetByte(input_value)
    {
        this.byte_field = input_value
    }

    GetByte()
    {
        return this.byte_field
    }

    SetByteDigit(input_value)
    {
        this.byte_digit_field = input_value
    }

    GetByteDigit()
    {
        return this.byte_digit_field
    }

    SetNegative(input_value)
    {
        this.negative_field = input_value
    }

    GetNegative()
    {
        return this.negative_field
    }

    SetDecimal(input_value)
    {
        this.decimal_field = input_value
    }

    GetDecimal()
    {
        return this.decimal_field
    }

    SetNumber(input_value)
    {
        this.number_field = input_value
    }

    GetNumber()
    {
        return this.number_field
    }

    SetDigit(input_value)
    {
        this.digit_field = input_value
    }

    GetDigit()
    {
        return this.digit_field
    }

    SetLiteral(input_value)
    {
        this.literal_field = input_value
    }

    GetLiteral()
    {
        return this.literal_field
    }

    SetLiteralCharacter(input_value)
    {
        this.literal_character_field = input_value
    }

    GetLiteralCharacter()
    {
        return this.literal_character_field
    }

    SetWhitespace(input_value)
    {
        this.whitespace_field = input_value
    }

    GetWhitespace()
    {
        return this.whitespace_field
    }
}

export class DBNFOmniTypeResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }

    SetCTCodeFile(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetCTCodeFile(input_value)
    }

    SetExternalDefinition(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetExternalDefinition(input_value)
    }

    SetUnmanagedType(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetUnmanagedType(input_value)
    }

    SetDefinition(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetDefinition(input_value)
    }

    SetInterfaceDef(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetInterfaceDef(input_value)
    }

    SetClassDef(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetClassDef(input_value)
    }

    SetImplementationSpec(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetImplementationSpec(input_value)
    }

    SetContentDeclaration(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetContentDeclaration(input_value)
    }

    SetContentDefinition(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetContentDefinition(input_value)
    }

    SetPrimativeType(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetPrimativeType(input_value)
    }

    SetDefinedType(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetDefinedType(input_value)
    }

    SetSingletonType(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetSingletonType(input_value)
    }

    SetDimensionalNote(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetDimensionalNote(input_value)
    }

    SetDimensionalType(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetDimensionalType(input_value)
    }

    SetMapNote(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetMapNote(input_value)
    }

    SetMapType(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetMapType(input_value)
    }

    SetValueType(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetValueType(input_value)
    }

    SetParameterListDef(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetParameterListDef(input_value)
    }

    SetParameterList(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetParameterList(input_value)
    }

    SetCodeBlock(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetCodeBlock(input_value)
    }

    SetDeclarationAssign(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetDeclarationAssign(input_value)
    }

    SetDeclaration(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetDeclaration(input_value)
    }

    SetAssignment(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetAssignment(input_value)
    }

    SetReturn(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetReturn(input_value)
    }

    SetElseTail(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetElseTail(input_value)
    }

    SetConditional(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetConditional(input_value)
    }

    SetLoop(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetLoop(input_value)
    }

    SetCall(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetCall(input_value)
    }

    SetAllocate(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetAllocate(input_value)
    }

    SetInstruction(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetInstruction(input_value)
    }

    SetRValueSingle(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetRValueSingle(input_value)
    }

    SetRValueTail(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetRValueTail(input_value)
    }

    SetRValue(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetRValue(input_value)
    }

    SetBinaryOperator(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetBinaryOperator(input_value)
    }

    SetUnaryOperator(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetUnaryOperator(input_value)
    }

    SetComment(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetComment(input_value)
    }

    SetNonStarCharacter(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetNonStarCharacter(input_value)
    }

    SetNonSlashCharacter(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetNonSlashCharacter(input_value)
    }

    SetCommentContent(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetCommentContent(input_value)
    }

    SetQualfiedName(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetQualfiedName(input_value)
    }

    SetNameTail(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetNameTail(input_value)
    }

    SetName(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetName(input_value)
    }

    SetNameCharacter(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetNameCharacter(input_value)
    }

    SetBoolean(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetBoolean(input_value)
    }

    SetByte(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetByte(input_value)
    }

    SetByteDigit(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetByteDigit(input_value)
    }

    SetNegative(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetNegative(input_value)
    }

    SetDecimal(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetDecimal(input_value)
    }

    SetNumber(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetNumber(input_value)
    }

    SetDigit(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetDigit(input_value)
    }

    SetLiteral(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetLiteral(input_value)
    }

    SetLiteralCharacter(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetLiteralCharacter(input_value)
    }

    SetWhitespace(input_value)
    {
        this.value = new DBNFOmniType()
        this.value.SetWhitespace(input_value)
    }
}

export class DBNFOmniTypeListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }

    SetCTCodeFile(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetCTCodeFile(Element(input_value,index))
            index = index+1
        }
    }

    SetExternalDefinition(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetExternalDefinition(Element(input_value,index))
            index = index+1
        }
    }

    SetUnmanagedType(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetUnmanagedType(Element(input_value,index))
            index = index+1
        }
    }

    SetDefinition(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetDefinition(Element(input_value,index))
            index = index+1
        }
    }

    SetInterfaceDef(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetInterfaceDef(Element(input_value,index))
            index = index+1
        }
    }

    SetClassDef(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetClassDef(Element(input_value,index))
            index = index+1
        }
    }

    SetImplementationSpec(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetImplementationSpec(Element(input_value,index))
            index = index+1
        }
    }

    SetContentDeclaration(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetContentDeclaration(Element(input_value,index))
            index = index+1
        }
    }

    SetContentDefinition(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetContentDefinition(Element(input_value,index))
            index = index+1
        }
    }

    SetPrimativeType(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetPrimativeType(Element(input_value,index))
            index = index+1
        }
    }

    SetDefinedType(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetDefinedType(Element(input_value,index))
            index = index+1
        }
    }

    SetSingletonType(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetSingletonType(Element(input_value,index))
            index = index+1
        }
    }

    SetDimensionalNote(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetDimensionalNote(Element(input_value,index))
            index = index+1
        }
    }

    SetDimensionalType(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetDimensionalType(Element(input_value,index))
            index = index+1
        }
    }

    SetMapNote(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetMapNote(Element(input_value,index))
            index = index+1
        }
    }

    SetMapType(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetMapType(Element(input_value,index))
            index = index+1
        }
    }

    SetValueType(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetValueType(Element(input_value,index))
            index = index+1
        }
    }

    SetParameterListDef(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetParameterListDef(Element(input_value,index))
            index = index+1
        }
    }

    SetParameterList(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetParameterList(Element(input_value,index))
            index = index+1
        }
    }

    SetCodeBlock(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetCodeBlock(Element(input_value,index))
            index = index+1
        }
    }

    SetDeclarationAssign(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetDeclarationAssign(Element(input_value,index))
            index = index+1
        }
    }

    SetDeclaration(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetDeclaration(Element(input_value,index))
            index = index+1
        }
    }

    SetAssignment(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetAssignment(Element(input_value,index))
            index = index+1
        }
    }

    SetReturn(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetReturn(Element(input_value,index))
            index = index+1
        }
    }

    SetElseTail(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetElseTail(Element(input_value,index))
            index = index+1
        }
    }

    SetConditional(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetConditional(Element(input_value,index))
            index = index+1
        }
    }

    SetLoop(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetLoop(Element(input_value,index))
            index = index+1
        }
    }

    SetCall(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetCall(Element(input_value,index))
            index = index+1
        }
    }

    SetAllocate(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetAllocate(Element(input_value,index))
            index = index+1
        }
    }

    SetInstruction(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetInstruction(Element(input_value,index))
            index = index+1
        }
    }

    SetRValueSingle(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetRValueSingle(Element(input_value,index))
            index = index+1
        }
    }

    SetRValueTail(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetRValueTail(Element(input_value,index))
            index = index+1
        }
    }

    SetRValue(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetRValue(Element(input_value,index))
            index = index+1
        }
    }

    SetBinaryOperator(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetBinaryOperator(Element(input_value,index))
            index = index+1
        }
    }

    SetUnaryOperator(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetUnaryOperator(Element(input_value,index))
            index = index+1
        }
    }

    SetComment(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetComment(Element(input_value,index))
            index = index+1
        }
    }

    SetNonStarCharacter(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetNonStarCharacter(Element(input_value,index))
            index = index+1
        }
    }

    SetNonSlashCharacter(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetNonSlashCharacter(Element(input_value,index))
            index = index+1
        }
    }

    SetCommentContent(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetCommentContent(Element(input_value,index))
            index = index+1
        }
    }

    SetQualfiedName(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetQualfiedName(Element(input_value,index))
            index = index+1
        }
    }

    SetNameTail(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetNameTail(Element(input_value,index))
            index = index+1
        }
    }

    SetName(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetName(Element(input_value,index))
            index = index+1
        }
    }

    SetNameCharacter(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetNameCharacter(Element(input_value,index))
            index = index+1
        }
    }

    SetBoolean(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetBoolean(Element(input_value,index))
            index = index+1
        }
    }

    SetByte(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetByte(Element(input_value,index))
            index = index+1
        }
    }

    SetByteDigit(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetByteDigit(Element(input_value,index))
            index = index+1
        }
    }

    SetNegative(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetNegative(Element(input_value,index))
            index = index+1
        }
    }

    SetDecimal(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetDecimal(Element(input_value,index))
            index = index+1
        }
    }

    SetNumber(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetNumber(Element(input_value,index))
            index = index+1
        }
    }

    SetDigit(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetDigit(Element(input_value,index))
            index = index+1
        }
    }

    SetLiteral(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetLiteral(Element(input_value,index))
            index = index+1
        }
    }

    SetLiteralCharacter(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetLiteralCharacter(Element(input_value,index))
            index = index+1
        }
    }

    SetWhitespace(input_value)
    {
        var index = 0
        while (index<Size(input_value))
        {
            var value = new DBNFOmniType()
            value.SetWhitespace(Element(input_value,index))
            index = index+1
        }
    }
}

export class LargeString {
    constructor() {
        this.data = ""
    }

    SetData(new_data)
    {
        this.data = new_data
    }

    GetData()
    {
        return this.data
    }

    GetIntAt(offset)
    {
        return IntAt(this.data,offset)
    }

    GetAt(offset)
    {
        return At(this.data,offset)
    }
}

export class LengthString {
    constructor() {
        this.data = null
        this.start = 0
        this.length = 0
    }

    SetData(new_data)
    {
        this.data = new_data
    }

    GetData()
    {
        return this.data
    }

    SetStart(new_start)
    {
        this.start = new_start
    }

    GetStart()
    {
        return this.start
    }

    SetLength(new_length)
    {
        this.length = new_length
    }

    GetLength()
    {
        return this.length
    }

    GetString()
    {
        var deep_data = this.data.GetData()
        var result = ""
        var index = this.start
        var reserved_prefix_end = this.start+this.length
        while (index<reserved_prefix_end)
        {
            result = Concat(result,At(deep_data,index))
            index = index+1
        }
        return result
    }
}

export class CTCodeFileParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new CTCodeFile()
        var declarations_field = new ExternalDefinitionListResult()
        var definitions_field = new DefinitionListResult()
        var unmanaged_types_field = new UnmanagedTypeListResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && external_definition_parser_instance.ParseManySave(index,declarations_field,0,-1) && unmanaged_type_parser_instance.ParseManySave(index,unmanaged_types_field,0,-1) && definition_parser_instance.ParseManySave(index,definitions_field,0,-1))
        {
            instance.SetDeclarations(declarations_field.GetValue())
            instance.SetDefinitions(definitions_field.GetValue())
            instance.SetUnmanagedTypes(unmanaged_types_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            declarations_field = new ExternalDefinitionListResult()
            definitions_field = new DefinitionListResult()
            unmanaged_types_field = new UnmanagedTypeListResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new CTCodeFileResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new CTCodeFileResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new CTCodeFileResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new CTCodeFileListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class CTCodeFileResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class CTCodeFileListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class CTCodeFile {
    constructor() {
        this.length_string = null
        this.declarations_field = []
        this.definitions_field = []
        this.unmanaged_types_field = []
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetDeclarations(input_value)
    {
        this.declarations_field = input_value
    }

    GetDeclarations()
    {
        return this.declarations_field
    }

    SetDefinitions(input_value)
    {
        this.definitions_field = input_value
    }

    GetDefinitions()
    {
        return this.definitions_field
    }

    SetUnmanagedTypes(input_value)
    {
        this.unmanaged_types_field = input_value
    }

    GetUnmanagedTypes()
    {
        return this.unmanaged_types_field
    }
}

export class ExternalDefinitionParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new ExternalDefinition()
        var exdef_field = new QualfiedNameResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && string_parser_instance.ParseSingle(index,"exdef") && whitespace_parser_instance.ParseMany(index,0,-1) && qualfied_name_parser_instance.ParseSingleSave(index,exdef_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,";") && whitespace_parser_instance.ParseMany(index,0,-1))
        {
            instance.SetExdef(exdef_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            exdef_field = new QualfiedNameResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new ExternalDefinitionResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new ExternalDefinitionResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new ExternalDefinitionResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new ExternalDefinitionListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class ExternalDefinitionResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class ExternalDefinitionListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class ExternalDefinition {
    constructor() {
        this.length_string = null
        this.exdef_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetExdef(input_value)
    {
        this.exdef_field = input_value
    }

    GetExdef()
    {
        return this.exdef_field
    }
}

export class UnmanagedTypeParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new UnmanagedType()
        var unmanaged_type_field = new QualfiedNameResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && string_parser_instance.ParseSingle(index,"unmanaged") && whitespace_parser_instance.ParseMany(index,0,-1) && qualfied_name_parser_instance.ParseSingleSave(index,unmanaged_type_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,";") && whitespace_parser_instance.ParseMany(index,0,-1))
        {
            instance.SetUnmanagedType(unmanaged_type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            unmanaged_type_field = new QualfiedNameResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new UnmanagedTypeResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new UnmanagedTypeResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new UnmanagedTypeResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new UnmanagedTypeListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class UnmanagedTypeResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class UnmanagedTypeListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class UnmanagedType {
    constructor() {
        this.length_string = null
        this.unmanaged_type_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetUnmanagedType(input_value)
    {
        this.unmanaged_type_field = input_value
    }

    GetUnmanagedType()
    {
        return this.unmanaged_type_field
    }
}

export class DefinitionParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new Definition()
        var class_def_field = new ClassDefResult()
        var interface_def_field = new InterfaceDefResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && interface_def_parser_instance.ParseSingleSave(index,interface_def_field))
        {
            instance.SetClassDef(class_def_field.GetValue())
            instance.SetInterfaceDef(interface_def_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            class_def_field = new ClassDefResult()
            interface_def_field = new InterfaceDefResult()
        }
        if (true && class_def_parser_instance.ParseSingleSave(index,class_def_field))
        {
            instance.SetClassDef(class_def_field.GetValue())
            instance.SetInterfaceDef(interface_def_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            class_def_field = new ClassDefResult()
            interface_def_field = new InterfaceDefResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new DefinitionResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new DefinitionResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new DefinitionResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new DefinitionListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class DefinitionResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class DefinitionListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class Definition {
    constructor() {
        this.length_string = null
        this.class_def_field = null
        this.interface_def_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetClassDef(input_value)
    {
        this.class_def_field = input_value
    }

    GetClassDef()
    {
        return this.class_def_field
    }

    SetInterfaceDef(input_value)
    {
        this.interface_def_field = input_value
    }

    GetInterfaceDef()
    {
        return this.interface_def_field
    }
}

export class InterfaceDefParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new InterfaceDef()
        var comment_field = new CommentResult()
        var declarations_field = new ContentDeclarationListResult()
        var name_field = new NameResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && comment_parser_instance.ParseOptionalSave(index,comment_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"interface") && whitespace_parser_instance.ParseMany(index,1,-1) && name_parser_instance.ParseSingleSave(index,name_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"{") && whitespace_parser_instance.ParseMany(index,0,-1) && content_declaration_parser_instance.ParseManySave(index,declarations_field,0,-1) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"}") && whitespace_parser_instance.ParseMany(index,0,-1))
        {
            instance.SetComment(comment_field.GetValue())
            instance.SetDeclarations(declarations_field.GetValue())
            instance.SetName(name_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            comment_field = new CommentResult()
            declarations_field = new ContentDeclarationListResult()
            name_field = new NameResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new InterfaceDefResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new InterfaceDefResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new InterfaceDefResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new InterfaceDefListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class InterfaceDefResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class InterfaceDefListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class InterfaceDef {
    constructor() {
        this.length_string = null
        this.comment_field = null
        this.declarations_field = []
        this.name_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetComment(input_value)
    {
        this.comment_field = input_value
    }

    GetComment()
    {
        return this.comment_field
    }

    SetDeclarations(input_value)
    {
        this.declarations_field = input_value
    }

    GetDeclarations()
    {
        return this.declarations_field
    }

    SetName(input_value)
    {
        this.name_field = input_value
    }

    GetName()
    {
        return this.name_field
    }
}

export class ClassDefParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new ClassDef()
        var comment_field = new CommentResult()
        var definitions_field = new ContentDefinitionListResult()
        var implementing_field = new ImplementationSpecResult()
        var name_field = new NameResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && comment_parser_instance.ParseOptionalSave(index,comment_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"class") && whitespace_parser_instance.ParseMany(index,1,-1) && name_parser_instance.ParseSingleSave(index,name_field) && implementation_spec_parser_instance.ParseOptionalSave(index,implementing_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"{") && whitespace_parser_instance.ParseMany(index,0,-1) && content_definition_parser_instance.ParseManySave(index,definitions_field,0,-1) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"}") && whitespace_parser_instance.ParseMany(index,0,-1))
        {
            instance.SetComment(comment_field.GetValue())
            instance.SetDefinitions(definitions_field.GetValue())
            instance.SetImplementing(implementing_field.GetValue())
            instance.SetName(name_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            comment_field = new CommentResult()
            definitions_field = new ContentDefinitionListResult()
            implementing_field = new ImplementationSpecResult()
            name_field = new NameResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new ClassDefResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new ClassDefResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new ClassDefResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new ClassDefListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class ClassDefResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class ClassDefListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class ClassDef {
    constructor() {
        this.length_string = null
        this.comment_field = null
        this.definitions_field = []
        this.implementing_field = null
        this.name_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetComment(input_value)
    {
        this.comment_field = input_value
    }

    GetComment()
    {
        return this.comment_field
    }

    SetDefinitions(input_value)
    {
        this.definitions_field = input_value
    }

    GetDefinitions()
    {
        return this.definitions_field
    }

    SetImplementing(input_value)
    {
        this.implementing_field = input_value
    }

    GetImplementing()
    {
        return this.implementing_field
    }

    SetName(input_value)
    {
        this.name_field = input_value
    }

    GetName()
    {
        return this.name_field
    }
}

export class ImplementationSpecParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new ImplementationSpec()
        var interface_field = new QualfiedNameResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,1,-1) && string_parser_instance.ParseSingle(index,"implements") && whitespace_parser_instance.ParseMany(index,1,-1) && qualfied_name_parser_instance.ParseSingleSave(index,interface_field) && whitespace_parser_instance.ParseMany(index,0,-1))
        {
            instance.SetInterface(interface_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            interface_field = new QualfiedNameResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new ImplementationSpecResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new ImplementationSpecResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new ImplementationSpecResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new ImplementationSpecListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class ImplementationSpecResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class ImplementationSpecListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class ImplementationSpec {
    constructor() {
        this.length_string = null
        this.interface_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetInterface(input_value)
    {
        this.interface_field = input_value
    }

    GetInterface()
    {
        return this.interface_field
    }
}

export class ContentDeclarationParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new ContentDeclaration()
        var comment_field = new CommentResult()
        var name_field = new NameResult()
        var parameters_field = new ParameterListDefResult()
        var type_field = new ValueTypeResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && comment_parser_instance.ParseOptionalSave(index,comment_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"function") && whitespace_parser_instance.ParseMany(index,1,-1) && value_type_parser_instance.ParseSingleSave(index,type_field) && whitespace_parser_instance.ParseMany(index,1,-1) && name_parser_instance.ParseSingleSave(index,name_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"(") && whitespace_parser_instance.ParseMany(index,0,-1) && parameter_list_def_parser_instance.ParseOptionalSave(index,parameters_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,")") && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,";") && whitespace_parser_instance.ParseMany(index,0,-1))
        {
            instance.SetComment(comment_field.GetValue())
            instance.SetName(name_field.GetValue())
            instance.SetParameters(parameters_field.GetValue())
            instance.SetType(type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            comment_field = new CommentResult()
            name_field = new NameResult()
            parameters_field = new ParameterListDefResult()
            type_field = new ValueTypeResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new ContentDeclarationResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new ContentDeclarationResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new ContentDeclarationResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new ContentDeclarationListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class ContentDeclarationResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class ContentDeclarationListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class ContentDeclaration {
    constructor() {
        this.length_string = null
        this.comment_field = null
        this.name_field = null
        this.parameters_field = null
        this.type_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetComment(input_value)
    {
        this.comment_field = input_value
    }

    GetComment()
    {
        return this.comment_field
    }

    SetName(input_value)
    {
        this.name_field = input_value
    }

    GetName()
    {
        return this.name_field
    }

    SetParameters(input_value)
    {
        this.parameters_field = input_value
    }

    GetParameters()
    {
        return this.parameters_field
    }

    SetType(input_value)
    {
        this.type_field = input_value
    }

    ReservedPrefixGetType()
    {
        return this.type_field
    }
}

export class ContentDefinitionParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new ContentDefinition()
        var comment_field = new CommentResult()
        var function_body_field = new CodeBlockResult()
        var name_field = new NameResult()
        var parameters_field = new ParameterListDefResult()
        var type_field = new ValueTypeResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && comment_parser_instance.ParseOptionalSave(index,comment_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"function") && whitespace_parser_instance.ParseMany(index,1,-1) && value_type_parser_instance.ParseSingleSave(index,type_field) && whitespace_parser_instance.ParseMany(index,1,-1) && name_parser_instance.ParseSingleSave(index,name_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"(") && whitespace_parser_instance.ParseMany(index,0,-1) && parameter_list_def_parser_instance.ParseOptionalSave(index,parameters_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,")") && whitespace_parser_instance.ParseMany(index,0,-1) && code_block_parser_instance.ParseSingleSave(index,function_body_field) && whitespace_parser_instance.ParseMany(index,0,-1))
        {
            instance.SetComment(comment_field.GetValue())
            instance.SetFunctionBody(function_body_field.GetValue())
            instance.SetName(name_field.GetValue())
            instance.SetParameters(parameters_field.GetValue())
            instance.SetType(type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            comment_field = new CommentResult()
            function_body_field = new CodeBlockResult()
            name_field = new NameResult()
            parameters_field = new ParameterListDefResult()
            type_field = new ValueTypeResult()
        }
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && comment_parser_instance.ParseOptionalSave(index,comment_field) && whitespace_parser_instance.ParseMany(index,0,-1) && value_type_parser_instance.ParseSingleSave(index,type_field) && whitespace_parser_instance.ParseMany(index,1,-1) && name_parser_instance.ParseSingleSave(index,name_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,";") && whitespace_parser_instance.ParseMany(index,0,-1))
        {
            instance.SetComment(comment_field.GetValue())
            instance.SetFunctionBody(function_body_field.GetValue())
            instance.SetName(name_field.GetValue())
            instance.SetParameters(parameters_field.GetValue())
            instance.SetType(type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            comment_field = new CommentResult()
            function_body_field = new CodeBlockResult()
            name_field = new NameResult()
            parameters_field = new ParameterListDefResult()
            type_field = new ValueTypeResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new ContentDefinitionResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new ContentDefinitionResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new ContentDefinitionResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new ContentDefinitionListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class ContentDefinitionResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class ContentDefinitionListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class ContentDefinition {
    constructor() {
        this.length_string = null
        this.comment_field = null
        this.function_body_field = null
        this.name_field = null
        this.parameters_field = null
        this.type_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetComment(input_value)
    {
        this.comment_field = input_value
    }

    GetComment()
    {
        return this.comment_field
    }

    SetFunctionBody(input_value)
    {
        this.function_body_field = input_value
    }

    GetFunctionBody()
    {
        return this.function_body_field
    }

    SetName(input_value)
    {
        this.name_field = input_value
    }

    GetName()
    {
        return this.name_field
    }

    SetParameters(input_value)
    {
        this.parameters_field = input_value
    }

    GetParameters()
    {
        return this.parameters_field
    }

    SetType(input_value)
    {
        this.type_field = input_value
    }

    ReservedPrefixGetType()
    {
        return this.type_field
    }
}

export class PrimativeTypeParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new PrimativeType()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && string_parser_instance.ParseSingle(index,"int"))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        if (true && string_parser_instance.ParseSingle(index,"string"))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        if (true && string_parser_instance.ParseSingle(index,"bool"))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        if (true && string_parser_instance.ParseSingle(index,"float"))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        if (true && string_parser_instance.ParseSingle(index,"void"))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new PrimativeTypeResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new PrimativeTypeResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new PrimativeTypeResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new PrimativeTypeListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class PrimativeTypeResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class PrimativeTypeListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class PrimativeType {
    constructor() {
        this.length_string = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }
}

export class DefinedTypeParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new DefinedType()
        var name_field = new QualfiedNameResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && qualfied_name_parser_instance.ParseSingleSave(index,name_field))
        {
            instance.SetName(name_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            name_field = new QualfiedNameResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new DefinedTypeResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new DefinedTypeResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new DefinedTypeResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new DefinedTypeListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class DefinedTypeResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class DefinedTypeListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class DefinedType {
    constructor() {
        this.length_string = null
        this.name_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetName(input_value)
    {
        this.name_field = input_value
    }

    GetName()
    {
        return this.name_field
    }
}

export class SingletonTypeParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new SingletonType()
        var defined_type_field = new DefinedTypeResult()
        var primative_type_field = new PrimativeTypeResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && primative_type_parser_instance.ParseSingleSave(index,primative_type_field))
        {
            instance.SetDefinedType(defined_type_field.GetValue())
            instance.SetPrimativeType(primative_type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            defined_type_field = new DefinedTypeResult()
            primative_type_field = new PrimativeTypeResult()
        }
        if (true && defined_type_parser_instance.ParseSingleSave(index,defined_type_field))
        {
            instance.SetDefinedType(defined_type_field.GetValue())
            instance.SetPrimativeType(primative_type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            defined_type_field = new DefinedTypeResult()
            primative_type_field = new PrimativeTypeResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new SingletonTypeResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new SingletonTypeResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new SingletonTypeResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new SingletonTypeListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class SingletonTypeResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class SingletonTypeListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class SingletonType {
    constructor() {
        this.length_string = null
        this.defined_type_field = null
        this.primative_type_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetDefinedType(input_value)
    {
        this.defined_type_field = input_value
    }

    GetDefinedType()
    {
        return this.defined_type_field
    }

    SetPrimativeType(input_value)
    {
        this.primative_type_field = input_value
    }

    GetPrimativeType()
    {
        return this.primative_type_field
    }
}

export class DimensionalNoteParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new DimensionalNote()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"[") && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"]"))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new DimensionalNoteResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new DimensionalNoteResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new DimensionalNoteResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new DimensionalNoteListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class DimensionalNoteResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class DimensionalNoteListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class DimensionalNote {
    constructor() {
        this.length_string = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }
}

export class DimensionalTypeParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new DimensionalType()
        var dimensional_note_field = new DimensionalNoteListResult()
        var singleton_type_field = new SingletonTypeResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && singleton_type_parser_instance.ParseSingleSave(index,singleton_type_field) && dimensional_note_parser_instance.ParseManySave(index,dimensional_note_field,1,-1))
        {
            instance.SetDimensionalNote(dimensional_note_field.GetValue())
            instance.SetSingletonType(singleton_type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            dimensional_note_field = new DimensionalNoteListResult()
            singleton_type_field = new SingletonTypeResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new DimensionalTypeResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new DimensionalTypeResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new DimensionalTypeResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new DimensionalTypeListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class DimensionalTypeResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class DimensionalTypeListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class DimensionalType {
    constructor() {
        this.length_string = null
        this.dimensional_note_field = []
        this.singleton_type_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetDimensionalNote(input_value)
    {
        this.dimensional_note_field = input_value
    }

    GetDimensionalNote()
    {
        return this.dimensional_note_field
    }

    SetSingletonType(input_value)
    {
        this.singleton_type_field = input_value
    }

    GetSingletonType()
    {
        return this.singleton_type_field
    }
}

export class MapNoteParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new MapNote()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"{") && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"}"))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new MapNoteResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new MapNoteResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new MapNoteResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new MapNoteListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class MapNoteResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class MapNoteListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class MapNote {
    constructor() {
        this.length_string = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }
}

export class MapTypeParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new MapType()
        var map_note_field = new MapNoteResult()
        var singleton_type_field = new SingletonTypeResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && singleton_type_parser_instance.ParseSingleSave(index,singleton_type_field) && map_note_parser_instance.ParseSingleSave(index,map_note_field))
        {
            instance.SetMapNote(map_note_field.GetValue())
            instance.SetSingletonType(singleton_type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            map_note_field = new MapNoteResult()
            singleton_type_field = new SingletonTypeResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new MapTypeResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new MapTypeResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new MapTypeResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new MapTypeListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class MapTypeResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class MapTypeListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class MapType {
    constructor() {
        this.length_string = null
        this.map_note_field = null
        this.singleton_type_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetMapNote(input_value)
    {
        this.map_note_field = input_value
    }

    GetMapNote()
    {
        return this.map_note_field
    }

    SetSingletonType(input_value)
    {
        this.singleton_type_field = input_value
    }

    GetSingletonType()
    {
        return this.singleton_type_field
    }
}

export class ValueTypeParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new ValueType()
        var dimensional_type_field = new DimensionalTypeResult()
        var map_type_field = new MapTypeResult()
        var singleton_type_field = new SingletonTypeResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && dimensional_type_parser_instance.ParseSingleSave(index,dimensional_type_field))
        {
            instance.SetDimensionalType(dimensional_type_field.GetValue())
            instance.SetMapType(map_type_field.GetValue())
            instance.SetSingletonType(singleton_type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            dimensional_type_field = new DimensionalTypeResult()
            map_type_field = new MapTypeResult()
            singleton_type_field = new SingletonTypeResult()
        }
        if (true && map_type_parser_instance.ParseSingleSave(index,map_type_field))
        {
            instance.SetDimensionalType(dimensional_type_field.GetValue())
            instance.SetMapType(map_type_field.GetValue())
            instance.SetSingletonType(singleton_type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            dimensional_type_field = new DimensionalTypeResult()
            map_type_field = new MapTypeResult()
            singleton_type_field = new SingletonTypeResult()
        }
        if (true && singleton_type_parser_instance.ParseSingleSave(index,singleton_type_field))
        {
            instance.SetDimensionalType(dimensional_type_field.GetValue())
            instance.SetMapType(map_type_field.GetValue())
            instance.SetSingletonType(singleton_type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            dimensional_type_field = new DimensionalTypeResult()
            map_type_field = new MapTypeResult()
            singleton_type_field = new SingletonTypeResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new ValueTypeResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new ValueTypeResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new ValueTypeResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new ValueTypeListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class ValueTypeResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class ValueTypeListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class ValueType {
    constructor() {
        this.length_string = null
        this.dimensional_type_field = null
        this.map_type_field = null
        this.singleton_type_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetDimensionalType(input_value)
    {
        this.dimensional_type_field = input_value
    }

    GetDimensionalType()
    {
        return this.dimensional_type_field
    }

    SetMapType(input_value)
    {
        this.map_type_field = input_value
    }

    GetMapType()
    {
        return this.map_type_field
    }

    SetSingletonType(input_value)
    {
        this.singleton_type_field = input_value
    }

    GetSingletonType()
    {
        return this.singleton_type_field
    }
}

export class ParameterListDefParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new ParameterListDef()
        var name_field = new NameResult()
        var parameter_tail_field = new ParameterListDefResult()
        var type_field = new ValueTypeResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && value_type_parser_instance.ParseSingleSave(index,type_field) && whitespace_parser_instance.ParseMany(index,1,-1) && name_parser_instance.ParseSingleSave(index,name_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,",") && whitespace_parser_instance.ParseMany(index,0,-1) && parameter_list_def_parser_instance.ParseSingleSave(index,parameter_tail_field))
        {
            instance.SetName(name_field.GetValue())
            instance.SetParameterTail(parameter_tail_field.GetValue())
            instance.SetType(type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            name_field = new NameResult()
            parameter_tail_field = new ParameterListDefResult()
            type_field = new ValueTypeResult()
        }
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && value_type_parser_instance.ParseSingleSave(index,type_field) && whitespace_parser_instance.ParseMany(index,1,-1) && name_parser_instance.ParseSingleSave(index,name_field) && whitespace_parser_instance.ParseMany(index,0,-1))
        {
            instance.SetName(name_field.GetValue())
            instance.SetParameterTail(parameter_tail_field.GetValue())
            instance.SetType(type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            name_field = new NameResult()
            parameter_tail_field = new ParameterListDefResult()
            type_field = new ValueTypeResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new ParameterListDefResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new ParameterListDefResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new ParameterListDefResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new ParameterListDefListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class ParameterListDefResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class ParameterListDefListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class ParameterListDef {
    constructor() {
        this.length_string = null
        this.name_field = null
        this.parameter_tail_field = null
        this.type_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetName(input_value)
    {
        this.name_field = input_value
    }

    GetName()
    {
        return this.name_field
    }

    SetParameterTail(input_value)
    {
        this.parameter_tail_field = input_value
    }

    GetParameterTail()
    {
        return this.parameter_tail_field
    }

    SetType(input_value)
    {
        this.type_field = input_value
    }

    ReservedPrefixGetType()
    {
        return this.type_field
    }
}

export class ParameterListParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new ParameterList()
        var parameter_tail_field = new ParameterListResult()
        var r_value_field = new RValueResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && r_value_parser_instance.ParseSingleSave(index,r_value_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,",") && whitespace_parser_instance.ParseMany(index,0,-1) && parameter_list_parser_instance.ParseSingleSave(index,parameter_tail_field))
        {
            instance.SetParameterTail(parameter_tail_field.GetValue())
            instance.SetRValue(r_value_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            parameter_tail_field = new ParameterListResult()
            r_value_field = new RValueResult()
        }
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && r_value_parser_instance.ParseSingleSave(index,r_value_field) && whitespace_parser_instance.ParseMany(index,0,-1))
        {
            instance.SetParameterTail(parameter_tail_field.GetValue())
            instance.SetRValue(r_value_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            parameter_tail_field = new ParameterListResult()
            r_value_field = new RValueResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new ParameterListResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new ParameterListResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new ParameterListResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new ParameterListListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class ParameterListResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class ParameterListListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class ParameterList {
    constructor() {
        this.length_string = null
        this.parameter_tail_field = null
        this.r_value_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetParameterTail(input_value)
    {
        this.parameter_tail_field = input_value
    }

    GetParameterTail()
    {
        return this.parameter_tail_field
    }

    SetRValue(input_value)
    {
        this.r_value_field = input_value
    }

    GetRValue()
    {
        return this.r_value_field
    }
}

export class CodeBlockParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new CodeBlock()
        var instructions_field = new InstructionListResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"{") && whitespace_parser_instance.ParseMany(index,0,-1) && instruction_parser_instance.ParseManySave(index,instructions_field,0,-1) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"}") && whitespace_parser_instance.ParseMany(index,0,-1))
        {
            instance.SetInstructions(instructions_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            instructions_field = new InstructionListResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new CodeBlockResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new CodeBlockResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new CodeBlockResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new CodeBlockListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class CodeBlockResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class CodeBlockListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class CodeBlock {
    constructor() {
        this.length_string = null
        this.instructions_field = []
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetInstructions(input_value)
    {
        this.instructions_field = input_value
    }

    GetInstructions()
    {
        return this.instructions_field
    }
}

export class DeclarationAssignParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new DeclarationAssign()
        var r_value_field = new RValueResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"=") && whitespace_parser_instance.ParseMany(index,0,-1) && r_value_parser_instance.ParseSingleSave(index,r_value_field) && whitespace_parser_instance.ParseMany(index,0,-1))
        {
            instance.SetRValue(r_value_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            r_value_field = new RValueResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new DeclarationAssignResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new DeclarationAssignResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new DeclarationAssignResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new DeclarationAssignListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class DeclarationAssignResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class DeclarationAssignListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class DeclarationAssign {
    constructor() {
        this.length_string = null
        this.r_value_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetRValue(input_value)
    {
        this.r_value_field = input_value
    }

    GetRValue()
    {
        return this.r_value_field
    }
}

export class DeclarationParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new Declaration()
        var assignment_field = new DeclarationAssignResult()
        var name_field = new NameResult()
        var type_field = new ValueTypeResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && value_type_parser_instance.ParseSingleSave(index,type_field) && whitespace_parser_instance.ParseMany(index,1,-1) && name_parser_instance.ParseSingleSave(index,name_field) && whitespace_parser_instance.ParseMany(index,0,-1) && declaration_assign_parser_instance.ParseOptionalSave(index,assignment_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,";") && whitespace_parser_instance.ParseMany(index,0,-1))
        {
            instance.SetAssignment(assignment_field.GetValue())
            instance.SetName(name_field.GetValue())
            instance.SetType(type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            assignment_field = new DeclarationAssignResult()
            name_field = new NameResult()
            type_field = new ValueTypeResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new DeclarationResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new DeclarationResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new DeclarationResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new DeclarationListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class DeclarationResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class DeclarationListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class Declaration {
    constructor() {
        this.length_string = null
        this.assignment_field = null
        this.name_field = null
        this.type_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetAssignment(input_value)
    {
        this.assignment_field = input_value
    }

    GetAssignment()
    {
        return this.assignment_field
    }

    SetName(input_value)
    {
        this.name_field = input_value
    }

    GetName()
    {
        return this.name_field
    }

    SetType(input_value)
    {
        this.type_field = input_value
    }

    ReservedPrefixGetType()
    {
        return this.type_field
    }
}

export class AssignmentParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new Assignment()
        var l_value_field = new QualfiedNameResult()
        var r_value_field = new RValueResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && qualfied_name_parser_instance.ParseSingleSave(index,l_value_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"=") && whitespace_parser_instance.ParseMany(index,0,-1) && r_value_parser_instance.ParseSingleSave(index,r_value_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,";") && whitespace_parser_instance.ParseMany(index,0,-1))
        {
            instance.SetLValue(l_value_field.GetValue())
            instance.SetRValue(r_value_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            l_value_field = new QualfiedNameResult()
            r_value_field = new RValueResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new AssignmentResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new AssignmentResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new AssignmentResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new AssignmentListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class AssignmentResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class AssignmentListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class Assignment {
    constructor() {
        this.length_string = null
        this.l_value_field = null
        this.r_value_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetLValue(input_value)
    {
        this.l_value_field = input_value
    }

    GetLValue()
    {
        return this.l_value_field
    }

    SetRValue(input_value)
    {
        this.r_value_field = input_value
    }

    GetRValue()
    {
        return this.r_value_field
    }
}

export class ReturnParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new ReservedPrefixReturn()
        var r_value_field = new RValueResult()
        var rtn_field = new StringResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingleSave(index,"return",rtn_field) && whitespace_parser_instance.ParseMany(index,1,-1) && r_value_parser_instance.ParseSingleSave(index,r_value_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,";") && whitespace_parser_instance.ParseMany(index,0,-1))
        {
            instance.SetRValue(r_value_field.GetValue())
            instance.SetRtn(rtn_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            r_value_field = new RValueResult()
            rtn_field = new StringResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new ReturnResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new ReturnResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new ReturnResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new ReturnListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class ReturnResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class ReturnListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class ReservedPrefixReturn {
    constructor() {
        this.length_string = null
        this.r_value_field = null
        this.rtn_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetRValue(input_value)
    {
        this.r_value_field = input_value
    }

    GetRValue()
    {
        return this.r_value_field
    }

    SetRtn(input_value)
    {
        this.rtn_field = input_value
    }

    GetRtn()
    {
        return this.rtn_field
    }
}

export class ElseTailParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new ElseTail()
        var code_block_field = new CodeBlockResult()
        var else_key_field = new StringResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingleSave(index,"else",else_key_field) && whitespace_parser_instance.ParseMany(index,0,-1) && code_block_parser_instance.ParseSingleSave(index,code_block_field) && whitespace_parser_instance.ParseMany(index,0,-1))
        {
            instance.SetCodeBlock(code_block_field.GetValue())
            instance.SetElseKey(else_key_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            code_block_field = new CodeBlockResult()
            else_key_field = new StringResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new ElseTailResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new ElseTailResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new ElseTailResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new ElseTailListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class ElseTailResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class ElseTailListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class ElseTail {
    constructor() {
        this.length_string = null
        this.code_block_field = null
        this.else_key_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetCodeBlock(input_value)
    {
        this.code_block_field = input_value
    }

    GetCodeBlock()
    {
        return this.code_block_field
    }

    SetElseKey(input_value)
    {
        this.else_key_field = input_value
    }

    GetElseKey()
    {
        return this.else_key_field
    }
}

export class ConditionalParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new Conditional()
        var code_block_field = new CodeBlockResult()
        var conditional_key_field = new StringResult()
        var else_tail_field = new ElseTailResult()
        var r_value_field = new RValueResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingleSave(index,"if",conditional_key_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"(") && whitespace_parser_instance.ParseMany(index,0,-1) && r_value_parser_instance.ParseSingleSave(index,r_value_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,")") && whitespace_parser_instance.ParseMany(index,0,-1) && code_block_parser_instance.ParseSingleSave(index,code_block_field) && whitespace_parser_instance.ParseMany(index,0,-1) && else_tail_parser_instance.ParseOptionalSave(index,else_tail_field))
        {
            instance.SetCodeBlock(code_block_field.GetValue())
            instance.SetConditionalKey(conditional_key_field.GetValue())
            instance.SetElseTail(else_tail_field.GetValue())
            instance.SetRValue(r_value_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            code_block_field = new CodeBlockResult()
            conditional_key_field = new StringResult()
            else_tail_field = new ElseTailResult()
            r_value_field = new RValueResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new ConditionalResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new ConditionalResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new ConditionalResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new ConditionalListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class ConditionalResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class ConditionalListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class Conditional {
    constructor() {
        this.length_string = null
        this.code_block_field = null
        this.conditional_key_field = null
        this.else_tail_field = null
        this.r_value_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetCodeBlock(input_value)
    {
        this.code_block_field = input_value
    }

    GetCodeBlock()
    {
        return this.code_block_field
    }

    SetConditionalKey(input_value)
    {
        this.conditional_key_field = input_value
    }

    GetConditionalKey()
    {
        return this.conditional_key_field
    }

    SetElseTail(input_value)
    {
        this.else_tail_field = input_value
    }

    GetElseTail()
    {
        return this.else_tail_field
    }

    SetRValue(input_value)
    {
        this.r_value_field = input_value
    }

    GetRValue()
    {
        return this.r_value_field
    }
}

export class LoopParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new Loop()
        var code_block_field = new CodeBlockResult()
        var loop_key_field = new StringResult()
        var r_value_field = new RValueResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingleSave(index,"while",loop_key_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"(") && whitespace_parser_instance.ParseMany(index,0,-1) && r_value_parser_instance.ParseSingleSave(index,r_value_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,")") && whitespace_parser_instance.ParseMany(index,0,-1) && code_block_parser_instance.ParseSingleSave(index,code_block_field) && whitespace_parser_instance.ParseMany(index,0,-1))
        {
            instance.SetCodeBlock(code_block_field.GetValue())
            instance.SetLoopKey(loop_key_field.GetValue())
            instance.SetRValue(r_value_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            code_block_field = new CodeBlockResult()
            loop_key_field = new StringResult()
            r_value_field = new RValueResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new LoopResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new LoopResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new LoopResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new LoopListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class LoopResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class LoopListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class Loop {
    constructor() {
        this.length_string = null
        this.code_block_field = null
        this.loop_key_field = null
        this.r_value_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetCodeBlock(input_value)
    {
        this.code_block_field = input_value
    }

    GetCodeBlock()
    {
        return this.code_block_field
    }

    SetLoopKey(input_value)
    {
        this.loop_key_field = input_value
    }

    GetLoopKey()
    {
        return this.loop_key_field
    }

    SetRValue(input_value)
    {
        this.r_value_field = input_value
    }

    GetRValue()
    {
        return this.r_value_field
    }
}

export class CallParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new Call()
        var function_chain_field = new QualfiedNameResult()
        var function_field = new NameResult()
        var parameters_field = new ParameterListResult()
        var variable_field = new NameResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && name_parser_instance.ParseSingleSave(index,variable_field) && string_parser_instance.ParseSingle(index,".") && name_parser_instance.ParseSingleSave(index,function_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"(") && whitespace_parser_instance.ParseMany(index,0,-1) && parameter_list_parser_instance.ParseOptionalSave(index,parameters_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,")") && whitespace_parser_instance.ParseMany(index,0,-1))
        {
            instance.SetFunctionChain(function_chain_field.GetValue())
            instance.SetFunction(function_field.GetValue())
            instance.SetParameters(parameters_field.GetValue())
            instance.SetVariable(variable_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            function_chain_field = new QualfiedNameResult()
            function_field = new NameResult()
            parameters_field = new ParameterListResult()
            variable_field = new NameResult()
        }
        if (true && name_parser_instance.ParseSingleSave(index,function_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"(") && whitespace_parser_instance.ParseMany(index,0,-1) && parameter_list_parser_instance.ParseOptionalSave(index,parameters_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,")") && whitespace_parser_instance.ParseMany(index,0,-1))
        {
            instance.SetFunctionChain(function_chain_field.GetValue())
            instance.SetFunction(function_field.GetValue())
            instance.SetParameters(parameters_field.GetValue())
            instance.SetVariable(variable_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            function_chain_field = new QualfiedNameResult()
            function_field = new NameResult()
            parameters_field = new ParameterListResult()
            variable_field = new NameResult()
        }
        if (true && qualfied_name_parser_instance.ParseSingleSave(index,function_chain_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"(") && whitespace_parser_instance.ParseMany(index,0,-1) && parameter_list_parser_instance.ParseOptionalSave(index,parameters_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,")") && whitespace_parser_instance.ParseMany(index,0,-1))
        {
            instance.SetFunctionChain(function_chain_field.GetValue())
            instance.SetFunction(function_field.GetValue())
            instance.SetParameters(parameters_field.GetValue())
            instance.SetVariable(variable_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            function_chain_field = new QualfiedNameResult()
            function_field = new NameResult()
            parameters_field = new ParameterListResult()
            variable_field = new NameResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new CallResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new CallResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new CallResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new CallListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class CallResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class CallListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class Call {
    constructor() {
        this.length_string = null
        this.function_chain_field = null
        this.function_field = null
        this.parameters_field = null
        this.variable_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetFunctionChain(input_value)
    {
        this.function_chain_field = input_value
    }

    GetFunctionChain()
    {
        return this.function_chain_field
    }

    SetFunction(input_value)
    {
        this.function_field = input_value
    }

    GetFunction()
    {
        return this.function_field
    }

    SetParameters(input_value)
    {
        this.parameters_field = input_value
    }

    GetParameters()
    {
        return this.parameters_field
    }

    SetVariable(input_value)
    {
        this.variable_field = input_value
    }

    GetVariable()
    {
        return this.variable_field
    }
}

export class AllocateParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new Allocate()
        var managed_type_field = new QualfiedNameResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"new") && whitespace_parser_instance.ParseMany(index,1,-1) && qualfied_name_parser_instance.ParseSingleSave(index,managed_type_field) && whitespace_parser_instance.ParseMany(index,0,-1))
        {
            instance.SetManagedType(managed_type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            managed_type_field = new QualfiedNameResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new AllocateResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new AllocateResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new AllocateResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new AllocateListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class AllocateResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class AllocateListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class Allocate {
    constructor() {
        this.length_string = null
        this.managed_type_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetManagedType(input_value)
    {
        this.managed_type_field = input_value
    }

    GetManagedType()
    {
        return this.managed_type_field
    }
}

export class InstructionParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new Instruction()
        var assignment_field = new AssignmentResult()
        var call_field = new CallResult()
        var code_block_field = new CodeBlockResult()
        var comment_field = new CommentResult()
        var conditional_field = new ConditionalResult()
        var declaration_field = new DeclarationResult()
        var loop_field = new LoopResult()
        var rtn_field = new ReturnResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && comment_parser_instance.ParseOptionalSave(index,comment_field) && whitespace_parser_instance.ParseMany(index,0,-1) && code_block_parser_instance.ParseSingleSave(index,code_block_field))
        {
            instance.SetAssignment(assignment_field.GetValue())
            instance.SetCall(call_field.GetValue())
            instance.SetCodeBlock(code_block_field.GetValue())
            instance.SetComment(comment_field.GetValue())
            instance.SetConditional(conditional_field.GetValue())
            instance.SetDeclaration(declaration_field.GetValue())
            instance.SetLoop(loop_field.GetValue())
            instance.SetRtn(rtn_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            assignment_field = new AssignmentResult()
            call_field = new CallResult()
            code_block_field = new CodeBlockResult()
            comment_field = new CommentResult()
            conditional_field = new ConditionalResult()
            declaration_field = new DeclarationResult()
            loop_field = new LoopResult()
            rtn_field = new ReturnResult()
        }
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && comment_parser_instance.ParseOptionalSave(index,comment_field) && whitespace_parser_instance.ParseMany(index,0,-1) && return_parser_instance.ParseSingleSave(index,rtn_field))
        {
            instance.SetAssignment(assignment_field.GetValue())
            instance.SetCall(call_field.GetValue())
            instance.SetCodeBlock(code_block_field.GetValue())
            instance.SetComment(comment_field.GetValue())
            instance.SetConditional(conditional_field.GetValue())
            instance.SetDeclaration(declaration_field.GetValue())
            instance.SetLoop(loop_field.GetValue())
            instance.SetRtn(rtn_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            assignment_field = new AssignmentResult()
            call_field = new CallResult()
            code_block_field = new CodeBlockResult()
            comment_field = new CommentResult()
            conditional_field = new ConditionalResult()
            declaration_field = new DeclarationResult()
            loop_field = new LoopResult()
            rtn_field = new ReturnResult()
        }
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && comment_parser_instance.ParseOptionalSave(index,comment_field) && whitespace_parser_instance.ParseMany(index,0,-1) && declaration_parser_instance.ParseSingleSave(index,declaration_field))
        {
            instance.SetAssignment(assignment_field.GetValue())
            instance.SetCall(call_field.GetValue())
            instance.SetCodeBlock(code_block_field.GetValue())
            instance.SetComment(comment_field.GetValue())
            instance.SetConditional(conditional_field.GetValue())
            instance.SetDeclaration(declaration_field.GetValue())
            instance.SetLoop(loop_field.GetValue())
            instance.SetRtn(rtn_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            assignment_field = new AssignmentResult()
            call_field = new CallResult()
            code_block_field = new CodeBlockResult()
            comment_field = new CommentResult()
            conditional_field = new ConditionalResult()
            declaration_field = new DeclarationResult()
            loop_field = new LoopResult()
            rtn_field = new ReturnResult()
        }
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && comment_parser_instance.ParseOptionalSave(index,comment_field) && whitespace_parser_instance.ParseMany(index,0,-1) && assignment_parser_instance.ParseSingleSave(index,assignment_field))
        {
            instance.SetAssignment(assignment_field.GetValue())
            instance.SetCall(call_field.GetValue())
            instance.SetCodeBlock(code_block_field.GetValue())
            instance.SetComment(comment_field.GetValue())
            instance.SetConditional(conditional_field.GetValue())
            instance.SetDeclaration(declaration_field.GetValue())
            instance.SetLoop(loop_field.GetValue())
            instance.SetRtn(rtn_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            assignment_field = new AssignmentResult()
            call_field = new CallResult()
            code_block_field = new CodeBlockResult()
            comment_field = new CommentResult()
            conditional_field = new ConditionalResult()
            declaration_field = new DeclarationResult()
            loop_field = new LoopResult()
            rtn_field = new ReturnResult()
        }
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && comment_parser_instance.ParseOptionalSave(index,comment_field) && whitespace_parser_instance.ParseMany(index,0,-1) && call_parser_instance.ParseSingleSave(index,call_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,";") && whitespace_parser_instance.ParseMany(index,0,-1))
        {
            instance.SetAssignment(assignment_field.GetValue())
            instance.SetCall(call_field.GetValue())
            instance.SetCodeBlock(code_block_field.GetValue())
            instance.SetComment(comment_field.GetValue())
            instance.SetConditional(conditional_field.GetValue())
            instance.SetDeclaration(declaration_field.GetValue())
            instance.SetLoop(loop_field.GetValue())
            instance.SetRtn(rtn_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            assignment_field = new AssignmentResult()
            call_field = new CallResult()
            code_block_field = new CodeBlockResult()
            comment_field = new CommentResult()
            conditional_field = new ConditionalResult()
            declaration_field = new DeclarationResult()
            loop_field = new LoopResult()
            rtn_field = new ReturnResult()
        }
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && comment_parser_instance.ParseOptionalSave(index,comment_field) && whitespace_parser_instance.ParseMany(index,0,-1) && conditional_parser_instance.ParseSingleSave(index,conditional_field))
        {
            instance.SetAssignment(assignment_field.GetValue())
            instance.SetCall(call_field.GetValue())
            instance.SetCodeBlock(code_block_field.GetValue())
            instance.SetComment(comment_field.GetValue())
            instance.SetConditional(conditional_field.GetValue())
            instance.SetDeclaration(declaration_field.GetValue())
            instance.SetLoop(loop_field.GetValue())
            instance.SetRtn(rtn_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            assignment_field = new AssignmentResult()
            call_field = new CallResult()
            code_block_field = new CodeBlockResult()
            comment_field = new CommentResult()
            conditional_field = new ConditionalResult()
            declaration_field = new DeclarationResult()
            loop_field = new LoopResult()
            rtn_field = new ReturnResult()
        }
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && comment_parser_instance.ParseOptionalSave(index,comment_field) && whitespace_parser_instance.ParseMany(index,0,-1) && loop_parser_instance.ParseSingleSave(index,loop_field))
        {
            instance.SetAssignment(assignment_field.GetValue())
            instance.SetCall(call_field.GetValue())
            instance.SetCodeBlock(code_block_field.GetValue())
            instance.SetComment(comment_field.GetValue())
            instance.SetConditional(conditional_field.GetValue())
            instance.SetDeclaration(declaration_field.GetValue())
            instance.SetLoop(loop_field.GetValue())
            instance.SetRtn(rtn_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            assignment_field = new AssignmentResult()
            call_field = new CallResult()
            code_block_field = new CodeBlockResult()
            comment_field = new CommentResult()
            conditional_field = new ConditionalResult()
            declaration_field = new DeclarationResult()
            loop_field = new LoopResult()
            rtn_field = new ReturnResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new InstructionResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new InstructionResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new InstructionResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new InstructionListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class InstructionResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class InstructionListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class Instruction {
    constructor() {
        this.length_string = null
        this.assignment_field = null
        this.call_field = null
        this.code_block_field = null
        this.comment_field = null
        this.conditional_field = null
        this.declaration_field = null
        this.loop_field = null
        this.rtn_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetAssignment(input_value)
    {
        this.assignment_field = input_value
    }

    GetAssignment()
    {
        return this.assignment_field
    }

    SetCall(input_value)
    {
        this.call_field = input_value
    }

    GetCall()
    {
        return this.call_field
    }

    SetCodeBlock(input_value)
    {
        this.code_block_field = input_value
    }

    GetCodeBlock()
    {
        return this.code_block_field
    }

    SetComment(input_value)
    {
        this.comment_field = input_value
    }

    GetComment()
    {
        return this.comment_field
    }

    SetConditional(input_value)
    {
        this.conditional_field = input_value
    }

    GetConditional()
    {
        return this.conditional_field
    }

    SetDeclaration(input_value)
    {
        this.declaration_field = input_value
    }

    GetDeclaration()
    {
        return this.declaration_field
    }

    SetLoop(input_value)
    {
        this.loop_field = input_value
    }

    GetLoop()
    {
        return this.loop_field
    }

    SetRtn(input_value)
    {
        this.rtn_field = input_value
    }

    GetRtn()
    {
        return this.rtn_field
    }
}

export class RValueSingleParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new RValueSingle()
        var allocate_field = new AllocateResult()
        var boolean_literal_field = new BooleanResult()
        var byte_literal_field = new ByteResult()
        var call_field = new CallResult()
        var decimal_literal_field = new DecimalResult()
        var integer_literal_field = new NumberResult()
        var string_literal_field = new LiteralResult()
        var unary_operator_field = new UnaryOperatorResult()
        var variable_field = new QualfiedNameResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && unary_operator_parser_instance.ParseOptionalSave(index,unary_operator_field) && whitespace_parser_instance.ParseMany(index,0,-1) && call_parser_instance.ParseSingleSave(index,call_field))
        {
            instance.SetAllocate(allocate_field.GetValue())
            instance.SetBooleanLiteral(boolean_literal_field.GetValue())
            instance.SetByteLiteral(byte_literal_field.GetValue())
            instance.SetCall(call_field.GetValue())
            instance.SetDecimalLiteral(decimal_literal_field.GetValue())
            instance.SetIntegerLiteral(integer_literal_field.GetValue())
            instance.SetStringLiteral(string_literal_field.GetValue())
            instance.SetUnaryOperator(unary_operator_field.GetValue())
            instance.SetVariable(variable_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            allocate_field = new AllocateResult()
            boolean_literal_field = new BooleanResult()
            byte_literal_field = new ByteResult()
            call_field = new CallResult()
            decimal_literal_field = new DecimalResult()
            integer_literal_field = new NumberResult()
            string_literal_field = new LiteralResult()
            unary_operator_field = new UnaryOperatorResult()
            variable_field = new QualfiedNameResult()
        }
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && unary_operator_parser_instance.ParseOptionalSave(index,unary_operator_field) && whitespace_parser_instance.ParseMany(index,0,-1) && allocate_parser_instance.ParseSingleSave(index,allocate_field))
        {
            instance.SetAllocate(allocate_field.GetValue())
            instance.SetBooleanLiteral(boolean_literal_field.GetValue())
            instance.SetByteLiteral(byte_literal_field.GetValue())
            instance.SetCall(call_field.GetValue())
            instance.SetDecimalLiteral(decimal_literal_field.GetValue())
            instance.SetIntegerLiteral(integer_literal_field.GetValue())
            instance.SetStringLiteral(string_literal_field.GetValue())
            instance.SetUnaryOperator(unary_operator_field.GetValue())
            instance.SetVariable(variable_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            allocate_field = new AllocateResult()
            boolean_literal_field = new BooleanResult()
            byte_literal_field = new ByteResult()
            call_field = new CallResult()
            decimal_literal_field = new DecimalResult()
            integer_literal_field = new NumberResult()
            string_literal_field = new LiteralResult()
            unary_operator_field = new UnaryOperatorResult()
            variable_field = new QualfiedNameResult()
        }
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && unary_operator_parser_instance.ParseOptionalSave(index,unary_operator_field) && whitespace_parser_instance.ParseMany(index,0,-1) && byte_parser_instance.ParseSingleSave(index,byte_literal_field))
        {
            instance.SetAllocate(allocate_field.GetValue())
            instance.SetBooleanLiteral(boolean_literal_field.GetValue())
            instance.SetByteLiteral(byte_literal_field.GetValue())
            instance.SetCall(call_field.GetValue())
            instance.SetDecimalLiteral(decimal_literal_field.GetValue())
            instance.SetIntegerLiteral(integer_literal_field.GetValue())
            instance.SetStringLiteral(string_literal_field.GetValue())
            instance.SetUnaryOperator(unary_operator_field.GetValue())
            instance.SetVariable(variable_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            allocate_field = new AllocateResult()
            boolean_literal_field = new BooleanResult()
            byte_literal_field = new ByteResult()
            call_field = new CallResult()
            decimal_literal_field = new DecimalResult()
            integer_literal_field = new NumberResult()
            string_literal_field = new LiteralResult()
            unary_operator_field = new UnaryOperatorResult()
            variable_field = new QualfiedNameResult()
        }
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && unary_operator_parser_instance.ParseOptionalSave(index,unary_operator_field) && whitespace_parser_instance.ParseMany(index,0,-1) && decimal_parser_instance.ParseSingleSave(index,decimal_literal_field))
        {
            instance.SetAllocate(allocate_field.GetValue())
            instance.SetBooleanLiteral(boolean_literal_field.GetValue())
            instance.SetByteLiteral(byte_literal_field.GetValue())
            instance.SetCall(call_field.GetValue())
            instance.SetDecimalLiteral(decimal_literal_field.GetValue())
            instance.SetIntegerLiteral(integer_literal_field.GetValue())
            instance.SetStringLiteral(string_literal_field.GetValue())
            instance.SetUnaryOperator(unary_operator_field.GetValue())
            instance.SetVariable(variable_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            allocate_field = new AllocateResult()
            boolean_literal_field = new BooleanResult()
            byte_literal_field = new ByteResult()
            call_field = new CallResult()
            decimal_literal_field = new DecimalResult()
            integer_literal_field = new NumberResult()
            string_literal_field = new LiteralResult()
            unary_operator_field = new UnaryOperatorResult()
            variable_field = new QualfiedNameResult()
        }
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && unary_operator_parser_instance.ParseOptionalSave(index,unary_operator_field) && whitespace_parser_instance.ParseMany(index,0,-1) && number_parser_instance.ParseSingleSave(index,integer_literal_field))
        {
            instance.SetAllocate(allocate_field.GetValue())
            instance.SetBooleanLiteral(boolean_literal_field.GetValue())
            instance.SetByteLiteral(byte_literal_field.GetValue())
            instance.SetCall(call_field.GetValue())
            instance.SetDecimalLiteral(decimal_literal_field.GetValue())
            instance.SetIntegerLiteral(integer_literal_field.GetValue())
            instance.SetStringLiteral(string_literal_field.GetValue())
            instance.SetUnaryOperator(unary_operator_field.GetValue())
            instance.SetVariable(variable_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            allocate_field = new AllocateResult()
            boolean_literal_field = new BooleanResult()
            byte_literal_field = new ByteResult()
            call_field = new CallResult()
            decimal_literal_field = new DecimalResult()
            integer_literal_field = new NumberResult()
            string_literal_field = new LiteralResult()
            unary_operator_field = new UnaryOperatorResult()
            variable_field = new QualfiedNameResult()
        }
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && unary_operator_parser_instance.ParseOptionalSave(index,unary_operator_field) && whitespace_parser_instance.ParseMany(index,0,-1) && boolean_parser_instance.ParseSingleSave(index,boolean_literal_field))
        {
            instance.SetAllocate(allocate_field.GetValue())
            instance.SetBooleanLiteral(boolean_literal_field.GetValue())
            instance.SetByteLiteral(byte_literal_field.GetValue())
            instance.SetCall(call_field.GetValue())
            instance.SetDecimalLiteral(decimal_literal_field.GetValue())
            instance.SetIntegerLiteral(integer_literal_field.GetValue())
            instance.SetStringLiteral(string_literal_field.GetValue())
            instance.SetUnaryOperator(unary_operator_field.GetValue())
            instance.SetVariable(variable_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            allocate_field = new AllocateResult()
            boolean_literal_field = new BooleanResult()
            byte_literal_field = new ByteResult()
            call_field = new CallResult()
            decimal_literal_field = new DecimalResult()
            integer_literal_field = new NumberResult()
            string_literal_field = new LiteralResult()
            unary_operator_field = new UnaryOperatorResult()
            variable_field = new QualfiedNameResult()
        }
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && unary_operator_parser_instance.ParseOptionalSave(index,unary_operator_field) && whitespace_parser_instance.ParseMany(index,0,-1) && qualfied_name_parser_instance.ParseSingleSave(index,variable_field))
        {
            instance.SetAllocate(allocate_field.GetValue())
            instance.SetBooleanLiteral(boolean_literal_field.GetValue())
            instance.SetByteLiteral(byte_literal_field.GetValue())
            instance.SetCall(call_field.GetValue())
            instance.SetDecimalLiteral(decimal_literal_field.GetValue())
            instance.SetIntegerLiteral(integer_literal_field.GetValue())
            instance.SetStringLiteral(string_literal_field.GetValue())
            instance.SetUnaryOperator(unary_operator_field.GetValue())
            instance.SetVariable(variable_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            allocate_field = new AllocateResult()
            boolean_literal_field = new BooleanResult()
            byte_literal_field = new ByteResult()
            call_field = new CallResult()
            decimal_literal_field = new DecimalResult()
            integer_literal_field = new NumberResult()
            string_literal_field = new LiteralResult()
            unary_operator_field = new UnaryOperatorResult()
            variable_field = new QualfiedNameResult()
        }
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && unary_operator_parser_instance.ParseOptionalSave(index,unary_operator_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"\"") && literal_parser_instance.ParseSingleSave(index,string_literal_field) && string_parser_instance.ParseSingle(index,"\""))
        {
            instance.SetAllocate(allocate_field.GetValue())
            instance.SetBooleanLiteral(boolean_literal_field.GetValue())
            instance.SetByteLiteral(byte_literal_field.GetValue())
            instance.SetCall(call_field.GetValue())
            instance.SetDecimalLiteral(decimal_literal_field.GetValue())
            instance.SetIntegerLiteral(integer_literal_field.GetValue())
            instance.SetStringLiteral(string_literal_field.GetValue())
            instance.SetUnaryOperator(unary_operator_field.GetValue())
            instance.SetVariable(variable_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            allocate_field = new AllocateResult()
            boolean_literal_field = new BooleanResult()
            byte_literal_field = new ByteResult()
            call_field = new CallResult()
            decimal_literal_field = new DecimalResult()
            integer_literal_field = new NumberResult()
            string_literal_field = new LiteralResult()
            unary_operator_field = new UnaryOperatorResult()
            variable_field = new QualfiedNameResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new RValueSingleResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new RValueSingleResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new RValueSingleResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new RValueSingleListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class RValueSingleResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class RValueSingleListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class RValueSingle {
    constructor() {
        this.length_string = null
        this.allocate_field = null
        this.boolean_literal_field = null
        this.byte_literal_field = null
        this.call_field = null
        this.decimal_literal_field = null
        this.integer_literal_field = null
        this.string_literal_field = null
        this.unary_operator_field = null
        this.variable_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetAllocate(input_value)
    {
        this.allocate_field = input_value
    }

    GetAllocate()
    {
        return this.allocate_field
    }

    SetBooleanLiteral(input_value)
    {
        this.boolean_literal_field = input_value
    }

    GetBooleanLiteral()
    {
        return this.boolean_literal_field
    }

    SetByteLiteral(input_value)
    {
        this.byte_literal_field = input_value
    }

    GetByteLiteral()
    {
        return this.byte_literal_field
    }

    SetCall(input_value)
    {
        this.call_field = input_value
    }

    GetCall()
    {
        return this.call_field
    }

    SetDecimalLiteral(input_value)
    {
        this.decimal_literal_field = input_value
    }

    GetDecimalLiteral()
    {
        return this.decimal_literal_field
    }

    SetIntegerLiteral(input_value)
    {
        this.integer_literal_field = input_value
    }

    GetIntegerLiteral()
    {
        return this.integer_literal_field
    }

    SetStringLiteral(input_value)
    {
        this.string_literal_field = input_value
    }

    GetStringLiteral()
    {
        return this.string_literal_field
    }

    SetUnaryOperator(input_value)
    {
        this.unary_operator_field = input_value
    }

    GetUnaryOperator()
    {
        return this.unary_operator_field
    }

    SetVariable(input_value)
    {
        this.variable_field = input_value
    }

    GetVariable()
    {
        return this.variable_field
    }
}

export class RValueTailParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new RValueTail()
        var binary_operator_field = new BinaryOperatorResult()
        var tail_field = new RValueTailResult()
        var value_field = new RValueSingleResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && binary_operator_parser_instance.ParseSingleSave(index,binary_operator_field) && whitespace_parser_instance.ParseMany(index,0,-1) && r_value_single_parser_instance.ParseSingleSave(index,value_field) && whitespace_parser_instance.ParseMany(index,0,-1) && r_value_tail_parser_instance.ParseOptionalSave(index,tail_field))
        {
            instance.SetBinaryOperator(binary_operator_field.GetValue())
            instance.SetTail(tail_field.GetValue())
            instance.SetValue(value_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            binary_operator_field = new BinaryOperatorResult()
            tail_field = new RValueTailResult()
            value_field = new RValueSingleResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new RValueTailResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new RValueTailResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new RValueTailResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new RValueTailListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class RValueTailResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class RValueTailListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class RValueTail {
    constructor() {
        this.length_string = null
        this.binary_operator_field = null
        this.tail_field = null
        this.value_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetBinaryOperator(input_value)
    {
        this.binary_operator_field = input_value
    }

    GetBinaryOperator()
    {
        return this.binary_operator_field
    }

    SetTail(input_value)
    {
        this.tail_field = input_value
    }

    GetTail()
    {
        return this.tail_field
    }

    SetValue(input_value)
    {
        this.value_field = input_value
    }

    GetValue()
    {
        return this.value_field
    }
}

export class RValueParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new RValue()
        var tail_field = new RValueTailResult()
        var value_field = new RValueSingleResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && r_value_single_parser_instance.ParseSingleSave(index,value_field) && r_value_tail_parser_instance.ParseOptionalSave(index,tail_field))
        {
            instance.SetTail(tail_field.GetValue())
            instance.SetValue(value_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            tail_field = new RValueTailResult()
            value_field = new RValueSingleResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new RValueResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new RValueResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new RValueResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new RValueListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class RValueResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class RValueListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class RValue {
    constructor() {
        this.length_string = null
        this.tail_field = null
        this.value_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetTail(input_value)
    {
        this.tail_field = input_value
    }

    GetTail()
    {
        return this.tail_field
    }

    SetValue(input_value)
    {
        this.value_field = input_value
    }

    GetValue()
    {
        return this.value_field
    }
}

export class BinaryOperatorParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new BinaryOperator()
        var addition_field = new StringResult()
        var and_op_field = new StringResult()
        var equality_field = new StringResult()
        var greater_than_eq_field = new StringResult()
        var greater_than_field = new StringResult()
        var less_than_eq_field = new StringResult()
        var less_than_field = new StringResult()
        var not_equality_field = new StringResult()
        var or_op_field = new StringResult()
        var subtraction_field = new StringResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && string_parser_instance.ParseSingleSave(index,"+",addition_field))
        {
            instance.SetAddition(addition_field.GetValue())
            instance.SetAndOp(and_op_field.GetValue())
            instance.SetEquality(equality_field.GetValue())
            instance.SetGreaterThanEq(greater_than_eq_field.GetValue())
            instance.SetGreaterThan(greater_than_field.GetValue())
            instance.SetLessThanEq(less_than_eq_field.GetValue())
            instance.SetLessThan(less_than_field.GetValue())
            instance.SetNotEquality(not_equality_field.GetValue())
            instance.SetOrOp(or_op_field.GetValue())
            instance.SetSubtraction(subtraction_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            addition_field = new StringResult()
            and_op_field = new StringResult()
            equality_field = new StringResult()
            greater_than_eq_field = new StringResult()
            greater_than_field = new StringResult()
            less_than_eq_field = new StringResult()
            less_than_field = new StringResult()
            not_equality_field = new StringResult()
            or_op_field = new StringResult()
            subtraction_field = new StringResult()
        }
        if (true && string_parser_instance.ParseSingleSave(index,"-",subtraction_field))
        {
            instance.SetAddition(addition_field.GetValue())
            instance.SetAndOp(and_op_field.GetValue())
            instance.SetEquality(equality_field.GetValue())
            instance.SetGreaterThanEq(greater_than_eq_field.GetValue())
            instance.SetGreaterThan(greater_than_field.GetValue())
            instance.SetLessThanEq(less_than_eq_field.GetValue())
            instance.SetLessThan(less_than_field.GetValue())
            instance.SetNotEquality(not_equality_field.GetValue())
            instance.SetOrOp(or_op_field.GetValue())
            instance.SetSubtraction(subtraction_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            addition_field = new StringResult()
            and_op_field = new StringResult()
            equality_field = new StringResult()
            greater_than_eq_field = new StringResult()
            greater_than_field = new StringResult()
            less_than_eq_field = new StringResult()
            less_than_field = new StringResult()
            not_equality_field = new StringResult()
            or_op_field = new StringResult()
            subtraction_field = new StringResult()
        }
        if (true && string_parser_instance.ParseSingleSave(index,"<=",less_than_eq_field))
        {
            instance.SetAddition(addition_field.GetValue())
            instance.SetAndOp(and_op_field.GetValue())
            instance.SetEquality(equality_field.GetValue())
            instance.SetGreaterThanEq(greater_than_eq_field.GetValue())
            instance.SetGreaterThan(greater_than_field.GetValue())
            instance.SetLessThanEq(less_than_eq_field.GetValue())
            instance.SetLessThan(less_than_field.GetValue())
            instance.SetNotEquality(not_equality_field.GetValue())
            instance.SetOrOp(or_op_field.GetValue())
            instance.SetSubtraction(subtraction_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            addition_field = new StringResult()
            and_op_field = new StringResult()
            equality_field = new StringResult()
            greater_than_eq_field = new StringResult()
            greater_than_field = new StringResult()
            less_than_eq_field = new StringResult()
            less_than_field = new StringResult()
            not_equality_field = new StringResult()
            or_op_field = new StringResult()
            subtraction_field = new StringResult()
        }
        if (true && string_parser_instance.ParseSingleSave(index,">=",greater_than_eq_field))
        {
            instance.SetAddition(addition_field.GetValue())
            instance.SetAndOp(and_op_field.GetValue())
            instance.SetEquality(equality_field.GetValue())
            instance.SetGreaterThanEq(greater_than_eq_field.GetValue())
            instance.SetGreaterThan(greater_than_field.GetValue())
            instance.SetLessThanEq(less_than_eq_field.GetValue())
            instance.SetLessThan(less_than_field.GetValue())
            instance.SetNotEquality(not_equality_field.GetValue())
            instance.SetOrOp(or_op_field.GetValue())
            instance.SetSubtraction(subtraction_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            addition_field = new StringResult()
            and_op_field = new StringResult()
            equality_field = new StringResult()
            greater_than_eq_field = new StringResult()
            greater_than_field = new StringResult()
            less_than_eq_field = new StringResult()
            less_than_field = new StringResult()
            not_equality_field = new StringResult()
            or_op_field = new StringResult()
            subtraction_field = new StringResult()
        }
        if (true && string_parser_instance.ParseSingleSave(index,"==",equality_field))
        {
            instance.SetAddition(addition_field.GetValue())
            instance.SetAndOp(and_op_field.GetValue())
            instance.SetEquality(equality_field.GetValue())
            instance.SetGreaterThanEq(greater_than_eq_field.GetValue())
            instance.SetGreaterThan(greater_than_field.GetValue())
            instance.SetLessThanEq(less_than_eq_field.GetValue())
            instance.SetLessThan(less_than_field.GetValue())
            instance.SetNotEquality(not_equality_field.GetValue())
            instance.SetOrOp(or_op_field.GetValue())
            instance.SetSubtraction(subtraction_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            addition_field = new StringResult()
            and_op_field = new StringResult()
            equality_field = new StringResult()
            greater_than_eq_field = new StringResult()
            greater_than_field = new StringResult()
            less_than_eq_field = new StringResult()
            less_than_field = new StringResult()
            not_equality_field = new StringResult()
            or_op_field = new StringResult()
            subtraction_field = new StringResult()
        }
        if (true && string_parser_instance.ParseSingleSave(index,"!=",not_equality_field))
        {
            instance.SetAddition(addition_field.GetValue())
            instance.SetAndOp(and_op_field.GetValue())
            instance.SetEquality(equality_field.GetValue())
            instance.SetGreaterThanEq(greater_than_eq_field.GetValue())
            instance.SetGreaterThan(greater_than_field.GetValue())
            instance.SetLessThanEq(less_than_eq_field.GetValue())
            instance.SetLessThan(less_than_field.GetValue())
            instance.SetNotEquality(not_equality_field.GetValue())
            instance.SetOrOp(or_op_field.GetValue())
            instance.SetSubtraction(subtraction_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            addition_field = new StringResult()
            and_op_field = new StringResult()
            equality_field = new StringResult()
            greater_than_eq_field = new StringResult()
            greater_than_field = new StringResult()
            less_than_eq_field = new StringResult()
            less_than_field = new StringResult()
            not_equality_field = new StringResult()
            or_op_field = new StringResult()
            subtraction_field = new StringResult()
        }
        if (true && string_parser_instance.ParseSingleSave(index,"<",less_than_field))
        {
            instance.SetAddition(addition_field.GetValue())
            instance.SetAndOp(and_op_field.GetValue())
            instance.SetEquality(equality_field.GetValue())
            instance.SetGreaterThanEq(greater_than_eq_field.GetValue())
            instance.SetGreaterThan(greater_than_field.GetValue())
            instance.SetLessThanEq(less_than_eq_field.GetValue())
            instance.SetLessThan(less_than_field.GetValue())
            instance.SetNotEquality(not_equality_field.GetValue())
            instance.SetOrOp(or_op_field.GetValue())
            instance.SetSubtraction(subtraction_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            addition_field = new StringResult()
            and_op_field = new StringResult()
            equality_field = new StringResult()
            greater_than_eq_field = new StringResult()
            greater_than_field = new StringResult()
            less_than_eq_field = new StringResult()
            less_than_field = new StringResult()
            not_equality_field = new StringResult()
            or_op_field = new StringResult()
            subtraction_field = new StringResult()
        }
        if (true && string_parser_instance.ParseSingleSave(index,">",greater_than_field))
        {
            instance.SetAddition(addition_field.GetValue())
            instance.SetAndOp(and_op_field.GetValue())
            instance.SetEquality(equality_field.GetValue())
            instance.SetGreaterThanEq(greater_than_eq_field.GetValue())
            instance.SetGreaterThan(greater_than_field.GetValue())
            instance.SetLessThanEq(less_than_eq_field.GetValue())
            instance.SetLessThan(less_than_field.GetValue())
            instance.SetNotEquality(not_equality_field.GetValue())
            instance.SetOrOp(or_op_field.GetValue())
            instance.SetSubtraction(subtraction_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            addition_field = new StringResult()
            and_op_field = new StringResult()
            equality_field = new StringResult()
            greater_than_eq_field = new StringResult()
            greater_than_field = new StringResult()
            less_than_eq_field = new StringResult()
            less_than_field = new StringResult()
            not_equality_field = new StringResult()
            or_op_field = new StringResult()
            subtraction_field = new StringResult()
        }
        if (true && string_parser_instance.ParseSingleSave(index,"||",or_op_field))
        {
            instance.SetAddition(addition_field.GetValue())
            instance.SetAndOp(and_op_field.GetValue())
            instance.SetEquality(equality_field.GetValue())
            instance.SetGreaterThanEq(greater_than_eq_field.GetValue())
            instance.SetGreaterThan(greater_than_field.GetValue())
            instance.SetLessThanEq(less_than_eq_field.GetValue())
            instance.SetLessThan(less_than_field.GetValue())
            instance.SetNotEquality(not_equality_field.GetValue())
            instance.SetOrOp(or_op_field.GetValue())
            instance.SetSubtraction(subtraction_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            addition_field = new StringResult()
            and_op_field = new StringResult()
            equality_field = new StringResult()
            greater_than_eq_field = new StringResult()
            greater_than_field = new StringResult()
            less_than_eq_field = new StringResult()
            less_than_field = new StringResult()
            not_equality_field = new StringResult()
            or_op_field = new StringResult()
            subtraction_field = new StringResult()
        }
        if (true && string_parser_instance.ParseSingleSave(index,"&&",and_op_field))
        {
            instance.SetAddition(addition_field.GetValue())
            instance.SetAndOp(and_op_field.GetValue())
            instance.SetEquality(equality_field.GetValue())
            instance.SetGreaterThanEq(greater_than_eq_field.GetValue())
            instance.SetGreaterThan(greater_than_field.GetValue())
            instance.SetLessThanEq(less_than_eq_field.GetValue())
            instance.SetLessThan(less_than_field.GetValue())
            instance.SetNotEquality(not_equality_field.GetValue())
            instance.SetOrOp(or_op_field.GetValue())
            instance.SetSubtraction(subtraction_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            addition_field = new StringResult()
            and_op_field = new StringResult()
            equality_field = new StringResult()
            greater_than_eq_field = new StringResult()
            greater_than_field = new StringResult()
            less_than_eq_field = new StringResult()
            less_than_field = new StringResult()
            not_equality_field = new StringResult()
            or_op_field = new StringResult()
            subtraction_field = new StringResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new BinaryOperatorResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new BinaryOperatorResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new BinaryOperatorResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new BinaryOperatorListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class BinaryOperatorResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class BinaryOperatorListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class BinaryOperator {
    constructor() {
        this.length_string = null
        this.addition_field = null
        this.and_op_field = null
        this.equality_field = null
        this.greater_than_eq_field = null
        this.greater_than_field = null
        this.less_than_eq_field = null
        this.less_than_field = null
        this.not_equality_field = null
        this.or_op_field = null
        this.subtraction_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetAddition(input_value)
    {
        this.addition_field = input_value
    }

    GetAddition()
    {
        return this.addition_field
    }

    SetAndOp(input_value)
    {
        this.and_op_field = input_value
    }

    GetAndOp()
    {
        return this.and_op_field
    }

    SetEquality(input_value)
    {
        this.equality_field = input_value
    }

    GetEquality()
    {
        return this.equality_field
    }

    SetGreaterThanEq(input_value)
    {
        this.greater_than_eq_field = input_value
    }

    GetGreaterThanEq()
    {
        return this.greater_than_eq_field
    }

    SetGreaterThan(input_value)
    {
        this.greater_than_field = input_value
    }

    GetGreaterThan()
    {
        return this.greater_than_field
    }

    SetLessThanEq(input_value)
    {
        this.less_than_eq_field = input_value
    }

    GetLessThanEq()
    {
        return this.less_than_eq_field
    }

    SetLessThan(input_value)
    {
        this.less_than_field = input_value
    }

    GetLessThan()
    {
        return this.less_than_field
    }

    SetNotEquality(input_value)
    {
        this.not_equality_field = input_value
    }

    GetNotEquality()
    {
        return this.not_equality_field
    }

    SetOrOp(input_value)
    {
        this.or_op_field = input_value
    }

    GetOrOp()
    {
        return this.or_op_field
    }

    SetSubtraction(input_value)
    {
        this.subtraction_field = input_value
    }

    GetSubtraction()
    {
        return this.subtraction_field
    }
}

export class UnaryOperatorParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new UnaryOperator()
        var negation_field = new StringResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && string_parser_instance.ParseSingleSave(index,"!",negation_field))
        {
            instance.SetNegation(negation_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            negation_field = new StringResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new UnaryOperatorResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new UnaryOperatorResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new UnaryOperatorResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new UnaryOperatorListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class UnaryOperatorResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class UnaryOperatorListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class UnaryOperator {
    constructor() {
        this.length_string = null
        this.negation_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetNegation(input_value)
    {
        this.negation_field = input_value
    }

    GetNegation()
    {
        return this.negation_field
    }
}

export class CommentParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new Comment()
        var content_field = new CommentContentListResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && string_parser_instance.ParseSingle(index,"/*") && comment_content_parser_instance.ParseManySave(index,content_field,0,-1) && string_parser_instance.ParseSingle(index,"*/"))
        {
            instance.SetContent(content_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            content_field = new CommentContentListResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new CommentResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new CommentResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new CommentResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new CommentListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class CommentResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class CommentListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class Comment {
    constructor() {
        this.length_string = null
        this.content_field = []
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetContent(input_value)
    {
        this.content_field = input_value
    }

    GetContent()
    {
        return this.content_field
    }
}

export class NonStarCharacterParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new NonStarCharacter()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && character_range_parser_instance.ParseSingle(index,0x00,0x29))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        if (true && character_range_parser_instance.ParseSingle(index,0x2B,0xFF))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new NonStarCharacterResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new NonStarCharacterResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new NonStarCharacterResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new NonStarCharacterListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class NonStarCharacterResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class NonStarCharacterListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class NonStarCharacter {
    constructor() {
        this.length_string = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }
}

export class NonSlashCharacterParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new NonSlashCharacter()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && character_range_parser_instance.ParseSingle(index,0x00,0x2E))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        if (true && character_range_parser_instance.ParseSingle(index,0x30,0xFF))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new NonSlashCharacterResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new NonSlashCharacterResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new NonSlashCharacterResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new NonSlashCharacterListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class NonSlashCharacterResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class NonSlashCharacterListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class NonSlashCharacter {
    constructor() {
        this.length_string = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }
}

export class CommentContentParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new CommentContent()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && non_star_character_parser_instance.ParseSingle(index))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        if (true && string_parser_instance.ParseSingle(index,"*") && non_slash_character_parser_instance.ParseSingle(index))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new CommentContentResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new CommentContentResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new CommentContentResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new CommentContentListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class CommentContentResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class CommentContentListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class CommentContent {
    constructor() {
        this.length_string = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }
}

export class QualfiedNameParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new QualfiedName()
        var name_field = new NameResult()
        var tail_field = new NameTailResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && name_parser_instance.ParseSingleSave(index,name_field) && name_tail_parser_instance.ParseOptionalSave(index,tail_field))
        {
            instance.SetName(name_field.GetValue())
            instance.SetTail(tail_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            name_field = new NameResult()
            tail_field = new NameTailResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new QualfiedNameResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new QualfiedNameResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new QualfiedNameResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new QualfiedNameListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class QualfiedNameResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class QualfiedNameListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class QualfiedName {
    constructor() {
        this.length_string = null
        this.name_field = null
        this.tail_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetName(input_value)
    {
        this.name_field = input_value
    }

    GetName()
    {
        return this.name_field
    }

    SetTail(input_value)
    {
        this.tail_field = input_value
    }

    GetTail()
    {
        return this.tail_field
    }
}

export class NameTailParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new NameTail()
        var name_field = new NameResult()
        var tail_field = new NameTailResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && string_parser_instance.ParseSingle(index,".") && name_parser_instance.ParseSingleSave(index,name_field) && name_tail_parser_instance.ParseOptionalSave(index,tail_field))
        {
            instance.SetName(name_field.GetValue())
            instance.SetTail(tail_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            name_field = new NameResult()
            tail_field = new NameTailResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new NameTailResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new NameTailResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new NameTailResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new NameTailListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class NameTailResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class NameTailListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class NameTail {
    constructor() {
        this.length_string = null
        this.name_field = null
        this.tail_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetName(input_value)
    {
        this.name_field = input_value
    }

    GetName()
    {
        return this.name_field
    }

    SetTail(input_value)
    {
        this.tail_field = input_value
    }

    GetTail()
    {
        return this.tail_field
    }
}

export class NameParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new Name()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && name_character_parser_instance.ParseMany(index,1,-1))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new NameResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new NameResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new NameResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new NameListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class NameResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class NameListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class Name {
    constructor() {
        this.length_string = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }
}

export class NameCharacterParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new NameCharacter()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && character_range_parser_instance.ParseSingle(index,0x30,0x39))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        if (true && character_range_parser_instance.ParseSingle(index,0x41,0x5A))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        if (true && string_parser_instance.ParseSingle(index,"_"))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        if (true && character_range_parser_instance.ParseSingle(index,0x61,0x7A))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new NameCharacterResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new NameCharacterResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new NameCharacterResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new NameCharacterListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class NameCharacterResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class NameCharacterListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class NameCharacter {
    constructor() {
        this.length_string = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }
}

export class BooleanParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new Boolean()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && string_parser_instance.ParseSingle(index,"true"))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        if (true && string_parser_instance.ParseSingle(index,"false"))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new BooleanResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new BooleanResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new BooleanResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new BooleanListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class BooleanResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class BooleanListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class Boolean {
    constructor() {
        this.length_string = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }
}

export class ByteParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new Byte()
        var high_field = new ByteDigitResult()
        var low_field = new ByteDigitResult()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && string_parser_instance.ParseSingle(index,"0x") && byte_digit_parser_instance.ParseSingleSave(index,high_field) && byte_digit_parser_instance.ParseSingleSave(index,low_field))
        {
            instance.SetHigh(high_field.GetValue())
            instance.SetLow(low_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            high_field = new ByteDigitResult()
            low_field = new ByteDigitResult()
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new ByteResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new ByteResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new ByteResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new ByteListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class ByteResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class ByteListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class Byte {
    constructor() {
        this.length_string = null
        this.high_field = null
        this.low_field = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }

    SetHigh(input_value)
    {
        this.high_field = input_value
    }

    GetHigh()
    {
        return this.high_field
    }

    SetLow(input_value)
    {
        this.low_field = input_value
    }

    GetLow()
    {
        return this.low_field
    }
}

export class ByteDigitParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new ByteDigit()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && character_range_parser_instance.ParseSingle(index,0x30,0x39))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        if (true && character_range_parser_instance.ParseSingle(index,0x41,0x46))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new ByteDigitResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new ByteDigitResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new ByteDigitResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new ByteDigitListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class ByteDigitResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class ByteDigitListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class ByteDigit {
    constructor() {
        this.length_string = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }
}

export class NegativeParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new Negative()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && string_parser_instance.ParseSingle(index,"-"))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new NegativeResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new NegativeResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new NegativeResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new NegativeListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class NegativeResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class NegativeListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class Negative {
    constructor() {
        this.length_string = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }
}

export class DecimalParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new Decimal()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && negative_parser_instance.ParseOptional(index) && number_parser_instance.ParseSingle(index) && string_parser_instance.ParseSingle(index,".") && number_parser_instance.ParseSingle(index))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new DecimalResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new DecimalResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new DecimalResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new DecimalListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class DecimalResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class DecimalListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class Decimal {
    constructor() {
        this.length_string = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }
}

export class NumberParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new Number()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && negative_parser_instance.ParseOptional(index) && digit_parser_instance.ParseMany(index,1,-1))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new NumberResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new NumberResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new NumberResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new NumberListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class NumberResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class NumberListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class Number {
    constructor() {
        this.length_string = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }
}

export class DigitParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new Digit()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && character_range_parser_instance.ParseSingle(index,0x30,0x39))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new DigitResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new DigitResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new DigitResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new DigitListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class DigitResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class DigitListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class Digit {
    constructor() {
        this.length_string = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }
}

export class LiteralParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new Literal()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && literal_character_parser_instance.ParseMany(index,0,-1))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new LiteralResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new LiteralResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new LiteralResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new LiteralListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class LiteralResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class LiteralListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class Literal {
    constructor() {
        this.length_string = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }
}

export class LiteralCharacterParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new LiteralCharacter()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && character_range_parser_instance.ParseSingle(index,0x00,0x21))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        if (true && string_parser_instance.ParseSingle(index,"\\\""))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        if (true && character_range_parser_instance.ParseSingle(index,0x23,0x5B))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        if (true && string_parser_instance.ParseSingle(index,"\\\\"))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        if (true && character_range_parser_instance.ParseSingle(index,0x5D,0xFF))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new LiteralCharacterResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new LiteralCharacterResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new LiteralCharacterResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new LiteralCharacterListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class LiteralCharacterResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class LiteralCharacterListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class LiteralCharacter {
    constructor() {
        this.length_string = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }
}

export class WhitespaceParser {
    constructor() {
        this.parser_network = null
    }

    SetParserNetwork(input)
    {
        this.parser_network = input
    }

    ParseSingleSave(index, result)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var consumed_string = new LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        var instance = new Whitespace()
        var c_t_code_file_parser_instance = this.parser_network.GetCTCodeFileParser()
        var external_definition_parser_instance = this.parser_network.GetExternalDefinitionParser()
        var unmanaged_type_parser_instance = this.parser_network.GetUnmanagedTypeParser()
        var definition_parser_instance = this.parser_network.GetDefinitionParser()
        var interface_def_parser_instance = this.parser_network.GetInterfaceDefParser()
        var class_def_parser_instance = this.parser_network.GetClassDefParser()
        var implementation_spec_parser_instance = this.parser_network.GetImplementationSpecParser()
        var content_declaration_parser_instance = this.parser_network.GetContentDeclarationParser()
        var content_definition_parser_instance = this.parser_network.GetContentDefinitionParser()
        var primative_type_parser_instance = this.parser_network.GetPrimativeTypeParser()
        var defined_type_parser_instance = this.parser_network.GetDefinedTypeParser()
        var singleton_type_parser_instance = this.parser_network.GetSingletonTypeParser()
        var dimensional_note_parser_instance = this.parser_network.GetDimensionalNoteParser()
        var dimensional_type_parser_instance = this.parser_network.GetDimensionalTypeParser()
        var map_note_parser_instance = this.parser_network.GetMapNoteParser()
        var map_type_parser_instance = this.parser_network.GetMapTypeParser()
        var value_type_parser_instance = this.parser_network.GetValueTypeParser()
        var parameter_list_def_parser_instance = this.parser_network.GetParameterListDefParser()
        var parameter_list_parser_instance = this.parser_network.GetParameterListParser()
        var code_block_parser_instance = this.parser_network.GetCodeBlockParser()
        var declaration_assign_parser_instance = this.parser_network.GetDeclarationAssignParser()
        var declaration_parser_instance = this.parser_network.GetDeclarationParser()
        var assignment_parser_instance = this.parser_network.GetAssignmentParser()
        var return_parser_instance = this.parser_network.GetReturnParser()
        var else_tail_parser_instance = this.parser_network.GetElseTailParser()
        var conditional_parser_instance = this.parser_network.GetConditionalParser()
        var loop_parser_instance = this.parser_network.GetLoopParser()
        var call_parser_instance = this.parser_network.GetCallParser()
        var allocate_parser_instance = this.parser_network.GetAllocateParser()
        var instruction_parser_instance = this.parser_network.GetInstructionParser()
        var r_value_single_parser_instance = this.parser_network.GetRValueSingleParser()
        var r_value_tail_parser_instance = this.parser_network.GetRValueTailParser()
        var r_value_parser_instance = this.parser_network.GetRValueParser()
        var binary_operator_parser_instance = this.parser_network.GetBinaryOperatorParser()
        var unary_operator_parser_instance = this.parser_network.GetUnaryOperatorParser()
        var comment_parser_instance = this.parser_network.GetCommentParser()
        var non_star_character_parser_instance = this.parser_network.GetNonStarCharacterParser()
        var non_slash_character_parser_instance = this.parser_network.GetNonSlashCharacterParser()
        var comment_content_parser_instance = this.parser_network.GetCommentContentParser()
        var qualfied_name_parser_instance = this.parser_network.GetQualfiedNameParser()
        var name_tail_parser_instance = this.parser_network.GetNameTailParser()
        var name_parser_instance = this.parser_network.GetNameParser()
        var name_character_parser_instance = this.parser_network.GetNameCharacterParser()
        var boolean_parser_instance = this.parser_network.GetBooleanParser()
        var byte_parser_instance = this.parser_network.GetByteParser()
        var byte_digit_parser_instance = this.parser_network.GetByteDigitParser()
        var negative_parser_instance = this.parser_network.GetNegativeParser()
        var decimal_parser_instance = this.parser_network.GetDecimalParser()
        var number_parser_instance = this.parser_network.GetNumberParser()
        var digit_parser_instance = this.parser_network.GetDigitParser()
        var literal_parser_instance = this.parser_network.GetLiteralParser()
        var literal_character_parser_instance = this.parser_network.GetLiteralCharacterParser()
        var whitespace_parser_instance = this.parser_network.GetWhitespaceParser()
        var string_parser_instance = this.parser_network.GetStringParser()
        var character_parser_instance = this.parser_network.GetCharacterParser()
        var character_range_parser_instance = this.parser_network.GetCharacterRangeParser()
        if (true && character_range_parser_instance.ParseSingle(index,0x00,0x20))
        {
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
        }
        result.SetResult(false)
        return result.GetResult()
    }

    ParseSingle(index)
    {
        var result = new WhitespaceResult()
        return this.ParseSingleSave(index,result)
    }

    ParseOptionalSave(index, result)
    {
        this.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    }

    ParseOptional(index)
    {
        var result = new WhitespaceResult()
        return this.ParseOptionalSave(index,result)
    }

    ParseManySave(index, list_result, minimum, maximum)
    {
        var index_start = index.GetStart()
        var index_length = index.GetLength()
        var results = []
        var count = 0
        var max_check = maximum
        var check_next = true
        if (maximum<0)
        {
            max_check = count+1
        }
        while (check_next && count<max_check)
        {
            var result = new WhitespaceResult()
            this.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
            {
                count = count+1
                Append(results,result.GetValue())
            }
            if (maximum<0)
            {
                max_check = count+1
            }
        }
        if (count>=minimum && count<=max_check)
        {
            list_result.SetValue(results)
            list_result.SetResult(true)
        }
        else
        {
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        }
        return list_result.GetResult()
    }

    ParseMany(index, minimum, maximum)
    {
        var result = new WhitespaceListResult()
        return this.ParseManySave(index,result,minimum,maximum)
    }
}

export class WhitespaceResult {
    constructor() {
        this.value = null
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class WhitespaceListResult {
    constructor() {
        this.value = []
        this.result = false
    }

    SetValue(new_value)
    {
        this.value = new_value
    }

    GetValue()
    {
        return this.value
    }

    SetResult(new_result)
    {
        this.result = new_result
    }

    GetResult()
    {
        return this.result
    }
}

export class Whitespace {
    constructor() {
        this.length_string = null
    }

    SetLengthString(new_value)
    {
        this.length_string = new LengthString()
        this.length_string.SetData(new_value.GetData())
        this.length_string.SetStart(new_value.GetStart())
        this.length_string.SetLength(new_value.GetLength())
    }

    UnParse()
    {
        return this.length_string.GetString()
    }
}

