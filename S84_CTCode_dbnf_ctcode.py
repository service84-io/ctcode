def ClearList(input: list) -> None: input.clear()
def Size(input: list) -> int: return len(input)
def Element(input: list, element: int ) -> any: return input[element]
def Append(input: list, element: any) -> None: input.append(element)
def ClearMap(input: dict) -> None: input.clear()
def SetKV(input: dict, key: str, element: any) -> None: input[key] = element
def Keys(input: dict) -> list[str]:
    result: list[str] = []
    for key in input.keys():
        result.append(key)
    return result
def HasKV(input: dict, key: str) -> bool: return key in input
def GetKV(input: dict, key: str) -> any: return input[key]
def Length(input: str) -> int: return len(input)
def At(input: str, index: int) -> str: return input[index:index+1]
def IntAt(input: str, index: int) -> int: return ord(input[index:index+1])
def Concat(left: str, right: str) -> str: return left + right

class StringParser:
    def __init__(self: 'StringParser'):
        pass

    def ParseSingleSave(self: 'StringParser',index: 'LengthString',value: 'str',result: 'StringResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        index_data: 'LargeString' = index.GetData()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'String' = String()
        value_length: 'int' = Length(value)
        if value_length>index.GetLength():
            result.SetResult(False)
            return False
        offset_index: 'int' = 0
        while offset_index<value_length:
            if index_data.GetAt(index.GetStart()+offset_index)!=At(value,offset_index):
                result.SetResult(False)
                return False
            offset_index = offset_index+1
        index.SetStart(index.GetStart()+value_length)
        index.SetLength(index.GetLength()-value_length)
        consumed_string.SetLength(index.GetStart()-index_start)
        instance.SetLengthString(consumed_string)
        result.SetValue(instance)
        result.SetResult(True)
        return True

    def ParseSingle(self: 'StringParser',index: 'LengthString',value: 'str') -> 'bool':
        result: 'StringResult' = StringResult()
        return self.ParseSingleSave(index,value,result)

class StringResult:
    def __init__(self: 'StringResult'):
        self.value: String = None
        self.result: bool = False

    def SetValue(self: 'StringResult',new_value: 'String') -> 'None':
        self.value = new_value

    def GetValue(self: 'StringResult') -> 'String':
        return self.value

    def SetResult(self: 'StringResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'StringResult') -> 'bool':
        return self.result

class StringListResult:
    def __init__(self: 'StringListResult'):
        self.value: list[String] = []
        self.result: bool = False

    def SetValue(self: 'StringListResult',new_value: 'list[String]') -> 'None':
        self.value = new_value

    def GetValue(self: 'StringListResult') -> 'list[String]':
        return self.value

    def SetResult(self: 'StringListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'StringListResult') -> 'bool':
        return self.result

class String:
    def __init__(self: 'String'):
        self.length_string: LengthString = None

    def SetLengthString(self: 'String',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'String') -> 'str':
        return self.length_string.GetString()

class CharacterParser:
    def __init__(self: 'CharacterParser'):
        pass

    def ParseSingle(self: 'CharacterParser',index: 'LengthString',value: 'int') -> 'bool':
        if 0==index.GetLength():
            return False
        index_data: 'LargeString' = index.GetData()
        current_character: 'int' = index_data.GetIntAt(index.GetStart())
        if current_character==value:
            index.SetStart(index.GetStart()+1)
            index.SetLength(index.GetLength()-1)
            return True
        return False

class CharacterResult:
    def __init__(self: 'CharacterResult'):
        self.value: Character = None
        self.result: bool = False

    def SetValue(self: 'CharacterResult',new_value: 'Character') -> 'None':
        self.value = new_value

    def GetValue(self: 'CharacterResult') -> 'Character':
        return self.value

    def SetResult(self: 'CharacterResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'CharacterResult') -> 'bool':
        return self.result

class CharacterListResult:
    def __init__(self: 'CharacterListResult'):
        self.value: list[Character] = []
        self.result: bool = False

    def SetValue(self: 'CharacterListResult',new_value: 'list[Character]') -> 'None':
        self.value = new_value

    def GetValue(self: 'CharacterListResult') -> 'list[Character]':
        return self.value

    def SetResult(self: 'CharacterListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'CharacterListResult') -> 'bool':
        return self.result

class Character:
    def __init__(self: 'Character'):
        self.length_string: LengthString = None

    def SetLengthString(self: 'Character',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'Character') -> 'str':
        return self.length_string.GetString()

class CharacterRangeParser:
    def __init__(self: 'CharacterRangeParser'):
        pass

    def ParseSingle(self: 'CharacterRangeParser',index: 'LengthString',low_value: 'int',high_value: 'int') -> 'bool':
        if 0==index.GetLength():
            return False
        index_data: 'LargeString' = index.GetData()
        current_character: 'int' = index_data.GetIntAt(index.GetStart())
        if low_value<=current_character and current_character<=high_value:
            index.SetStart(index.GetStart()+1)
            index.SetLength(index.GetLength()-1)
            return True
        return False

class CharacterRangeResult:
    def __init__(self: 'CharacterRangeResult'):
        self.value: CharacterRange = None
        self.result: bool = False

    def SetValue(self: 'CharacterRangeResult',new_value: 'CharacterRange') -> 'None':
        self.value = new_value

    def GetValue(self: 'CharacterRangeResult') -> 'CharacterRange':
        return self.value

    def SetResult(self: 'CharacterRangeResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'CharacterRangeResult') -> 'bool':
        return self.result

class CharacterRangeListResult:
    def __init__(self: 'CharacterRangeListResult'):
        self.value: list[CharacterRange] = []
        self.result: bool = False

    def SetValue(self: 'CharacterRangeListResult',new_value: 'list[CharacterRange]') -> 'None':
        self.value = new_value

    def GetValue(self: 'CharacterRangeListResult') -> 'list[CharacterRange]':
        return self.value

    def SetResult(self: 'CharacterRangeListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'CharacterRangeListResult') -> 'bool':
        return self.result

class CharacterRange:
    def __init__(self: 'CharacterRange'):
        self.length_string: LengthString = None

    def SetLengthString(self: 'CharacterRange',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'CharacterRange') -> 'str':
        return self.length_string.GetString()

class ParserNetwork:
    def __init__(self: 'ParserNetwork'):
        self.c_t_code_file_parser_field: CTCodeFileParser = None
        self.external_definition_parser_field: ExternalDefinitionParser = None
        self.unmanaged_type_parser_field: UnmanagedTypeParser = None
        self.definition_parser_field: DefinitionParser = None
        self.interface_def_parser_field: InterfaceDefParser = None
        self.class_def_parser_field: ClassDefParser = None
        self.implementation_spec_parser_field: ImplementationSpecParser = None
        self.content_declaration_parser_field: ContentDeclarationParser = None
        self.content_definition_parser_field: ContentDefinitionParser = None
        self.primative_type_parser_field: PrimativeTypeParser = None
        self.defined_type_parser_field: DefinedTypeParser = None
        self.singleton_type_parser_field: SingletonTypeParser = None
        self.dimensional_note_parser_field: DimensionalNoteParser = None
        self.dimensional_type_parser_field: DimensionalTypeParser = None
        self.map_note_parser_field: MapNoteParser = None
        self.map_type_parser_field: MapTypeParser = None
        self.value_type_parser_field: ValueTypeParser = None
        self.parameter_list_def_parser_field: ParameterListDefParser = None
        self.parameter_list_parser_field: ParameterListParser = None
        self.code_block_parser_field: CodeBlockParser = None
        self.declaration_assign_parser_field: DeclarationAssignParser = None
        self.declaration_parser_field: DeclarationParser = None
        self.assignment_parser_field: AssignmentParser = None
        self.return_parser_field: ReturnParser = None
        self.else_tail_parser_field: ElseTailParser = None
        self.conditional_parser_field: ConditionalParser = None
        self.loop_parser_field: LoopParser = None
        self.call_parser_field: CallParser = None
        self.allocate_parser_field: AllocateParser = None
        self.instruction_parser_field: InstructionParser = None
        self.r_value_single_parser_field: RValueSingleParser = None
        self.r_value_tail_parser_field: RValueTailParser = None
        self.r_value_parser_field: RValueParser = None
        self.binary_operator_parser_field: BinaryOperatorParser = None
        self.unary_operator_parser_field: UnaryOperatorParser = None
        self.comment_parser_field: CommentParser = None
        self.non_star_character_parser_field: NonStarCharacterParser = None
        self.non_slash_character_parser_field: NonSlashCharacterParser = None
        self.comment_content_parser_field: CommentContentParser = None
        self.qualfied_name_parser_field: QualfiedNameParser = None
        self.name_tail_parser_field: NameTailParser = None
        self.name_parser_field: NameParser = None
        self.name_character_parser_field: NameCharacterParser = None
        self.boolean_parser_field: BooleanParser = None
        self.byte_parser_field: ByteParser = None
        self.byte_digit_parser_field: ByteDigitParser = None
        self.negative_parser_field: NegativeParser = None
        self.decimal_parser_field: DecimalParser = None
        self.number_parser_field: NumberParser = None
        self.digit_parser_field: DigitParser = None
        self.literal_parser_field: LiteralParser = None
        self.literal_character_parser_field: LiteralCharacterParser = None
        self.whitespace_parser_field: WhitespaceParser = None
        self.string_parser_field: StringParser = None
        self.character_parser_field: CharacterParser = None
        self.character_range_parser_field: CharacterRangeParser = None

    def GetCTCodeFileParser(self: 'ParserNetwork') -> 'CTCodeFileParser':
        return self.c_t_code_file_parser_field

    def GetExternalDefinitionParser(self: 'ParserNetwork') -> 'ExternalDefinitionParser':
        return self.external_definition_parser_field

    def GetUnmanagedTypeParser(self: 'ParserNetwork') -> 'UnmanagedTypeParser':
        return self.unmanaged_type_parser_field

    def GetDefinitionParser(self: 'ParserNetwork') -> 'DefinitionParser':
        return self.definition_parser_field

    def GetInterfaceDefParser(self: 'ParserNetwork') -> 'InterfaceDefParser':
        return self.interface_def_parser_field

    def GetClassDefParser(self: 'ParserNetwork') -> 'ClassDefParser':
        return self.class_def_parser_field

    def GetImplementationSpecParser(self: 'ParserNetwork') -> 'ImplementationSpecParser':
        return self.implementation_spec_parser_field

    def GetContentDeclarationParser(self: 'ParserNetwork') -> 'ContentDeclarationParser':
        return self.content_declaration_parser_field

    def GetContentDefinitionParser(self: 'ParserNetwork') -> 'ContentDefinitionParser':
        return self.content_definition_parser_field

    def GetPrimativeTypeParser(self: 'ParserNetwork') -> 'PrimativeTypeParser':
        return self.primative_type_parser_field

    def GetDefinedTypeParser(self: 'ParserNetwork') -> 'DefinedTypeParser':
        return self.defined_type_parser_field

    def GetSingletonTypeParser(self: 'ParserNetwork') -> 'SingletonTypeParser':
        return self.singleton_type_parser_field

    def GetDimensionalNoteParser(self: 'ParserNetwork') -> 'DimensionalNoteParser':
        return self.dimensional_note_parser_field

    def GetDimensionalTypeParser(self: 'ParserNetwork') -> 'DimensionalTypeParser':
        return self.dimensional_type_parser_field

    def GetMapNoteParser(self: 'ParserNetwork') -> 'MapNoteParser':
        return self.map_note_parser_field

    def GetMapTypeParser(self: 'ParserNetwork') -> 'MapTypeParser':
        return self.map_type_parser_field

    def GetValueTypeParser(self: 'ParserNetwork') -> 'ValueTypeParser':
        return self.value_type_parser_field

    def GetParameterListDefParser(self: 'ParserNetwork') -> 'ParameterListDefParser':
        return self.parameter_list_def_parser_field

    def GetParameterListParser(self: 'ParserNetwork') -> 'ParameterListParser':
        return self.parameter_list_parser_field

    def GetCodeBlockParser(self: 'ParserNetwork') -> 'CodeBlockParser':
        return self.code_block_parser_field

    def GetDeclarationAssignParser(self: 'ParserNetwork') -> 'DeclarationAssignParser':
        return self.declaration_assign_parser_field

    def GetDeclarationParser(self: 'ParserNetwork') -> 'DeclarationParser':
        return self.declaration_parser_field

    def GetAssignmentParser(self: 'ParserNetwork') -> 'AssignmentParser':
        return self.assignment_parser_field

    def GetReturnParser(self: 'ParserNetwork') -> 'ReturnParser':
        return self.return_parser_field

    def GetElseTailParser(self: 'ParserNetwork') -> 'ElseTailParser':
        return self.else_tail_parser_field

    def GetConditionalParser(self: 'ParserNetwork') -> 'ConditionalParser':
        return self.conditional_parser_field

    def GetLoopParser(self: 'ParserNetwork') -> 'LoopParser':
        return self.loop_parser_field

    def GetCallParser(self: 'ParserNetwork') -> 'CallParser':
        return self.call_parser_field

    def GetAllocateParser(self: 'ParserNetwork') -> 'AllocateParser':
        return self.allocate_parser_field

    def GetInstructionParser(self: 'ParserNetwork') -> 'InstructionParser':
        return self.instruction_parser_field

    def GetRValueSingleParser(self: 'ParserNetwork') -> 'RValueSingleParser':
        return self.r_value_single_parser_field

    def GetRValueTailParser(self: 'ParserNetwork') -> 'RValueTailParser':
        return self.r_value_tail_parser_field

    def GetRValueParser(self: 'ParserNetwork') -> 'RValueParser':
        return self.r_value_parser_field

    def GetBinaryOperatorParser(self: 'ParserNetwork') -> 'BinaryOperatorParser':
        return self.binary_operator_parser_field

    def GetUnaryOperatorParser(self: 'ParserNetwork') -> 'UnaryOperatorParser':
        return self.unary_operator_parser_field

    def GetCommentParser(self: 'ParserNetwork') -> 'CommentParser':
        return self.comment_parser_field

    def GetNonStarCharacterParser(self: 'ParserNetwork') -> 'NonStarCharacterParser':
        return self.non_star_character_parser_field

    def GetNonSlashCharacterParser(self: 'ParserNetwork') -> 'NonSlashCharacterParser':
        return self.non_slash_character_parser_field

    def GetCommentContentParser(self: 'ParserNetwork') -> 'CommentContentParser':
        return self.comment_content_parser_field

    def GetQualfiedNameParser(self: 'ParserNetwork') -> 'QualfiedNameParser':
        return self.qualfied_name_parser_field

    def GetNameTailParser(self: 'ParserNetwork') -> 'NameTailParser':
        return self.name_tail_parser_field

    def GetNameParser(self: 'ParserNetwork') -> 'NameParser':
        return self.name_parser_field

    def GetNameCharacterParser(self: 'ParserNetwork') -> 'NameCharacterParser':
        return self.name_character_parser_field

    def GetBooleanParser(self: 'ParserNetwork') -> 'BooleanParser':
        return self.boolean_parser_field

    def GetByteParser(self: 'ParserNetwork') -> 'ByteParser':
        return self.byte_parser_field

    def GetByteDigitParser(self: 'ParserNetwork') -> 'ByteDigitParser':
        return self.byte_digit_parser_field

    def GetNegativeParser(self: 'ParserNetwork') -> 'NegativeParser':
        return self.negative_parser_field

    def GetDecimalParser(self: 'ParserNetwork') -> 'DecimalParser':
        return self.decimal_parser_field

    def GetNumberParser(self: 'ParserNetwork') -> 'NumberParser':
        return self.number_parser_field

    def GetDigitParser(self: 'ParserNetwork') -> 'DigitParser':
        return self.digit_parser_field

    def GetLiteralParser(self: 'ParserNetwork') -> 'LiteralParser':
        return self.literal_parser_field

    def GetLiteralCharacterParser(self: 'ParserNetwork') -> 'LiteralCharacterParser':
        return self.literal_character_parser_field

    def GetWhitespaceParser(self: 'ParserNetwork') -> 'WhitespaceParser':
        return self.whitespace_parser_field

    def GetStringParser(self: 'ParserNetwork') -> 'StringParser':
        return self.string_parser_field

    def GetCharacterParser(self: 'ParserNetwork') -> 'CharacterParser':
        return self.character_parser_field

    def GetCharacterRangeParser(self: 'ParserNetwork') -> 'CharacterRangeParser':
        return self.character_range_parser_field

    def Initialize(self: 'ParserNetwork') -> 'None':
        self.c_t_code_file_parser_field = CTCodeFileParser()
        self.c_t_code_file_parser_field.SetParserNetwork(self)
        self.external_definition_parser_field = ExternalDefinitionParser()
        self.external_definition_parser_field.SetParserNetwork(self)
        self.unmanaged_type_parser_field = UnmanagedTypeParser()
        self.unmanaged_type_parser_field.SetParserNetwork(self)
        self.definition_parser_field = DefinitionParser()
        self.definition_parser_field.SetParserNetwork(self)
        self.interface_def_parser_field = InterfaceDefParser()
        self.interface_def_parser_field.SetParserNetwork(self)
        self.class_def_parser_field = ClassDefParser()
        self.class_def_parser_field.SetParserNetwork(self)
        self.implementation_spec_parser_field = ImplementationSpecParser()
        self.implementation_spec_parser_field.SetParserNetwork(self)
        self.content_declaration_parser_field = ContentDeclarationParser()
        self.content_declaration_parser_field.SetParserNetwork(self)
        self.content_definition_parser_field = ContentDefinitionParser()
        self.content_definition_parser_field.SetParserNetwork(self)
        self.primative_type_parser_field = PrimativeTypeParser()
        self.primative_type_parser_field.SetParserNetwork(self)
        self.defined_type_parser_field = DefinedTypeParser()
        self.defined_type_parser_field.SetParserNetwork(self)
        self.singleton_type_parser_field = SingletonTypeParser()
        self.singleton_type_parser_field.SetParserNetwork(self)
        self.dimensional_note_parser_field = DimensionalNoteParser()
        self.dimensional_note_parser_field.SetParserNetwork(self)
        self.dimensional_type_parser_field = DimensionalTypeParser()
        self.dimensional_type_parser_field.SetParserNetwork(self)
        self.map_note_parser_field = MapNoteParser()
        self.map_note_parser_field.SetParserNetwork(self)
        self.map_type_parser_field = MapTypeParser()
        self.map_type_parser_field.SetParserNetwork(self)
        self.value_type_parser_field = ValueTypeParser()
        self.value_type_parser_field.SetParserNetwork(self)
        self.parameter_list_def_parser_field = ParameterListDefParser()
        self.parameter_list_def_parser_field.SetParserNetwork(self)
        self.parameter_list_parser_field = ParameterListParser()
        self.parameter_list_parser_field.SetParserNetwork(self)
        self.code_block_parser_field = CodeBlockParser()
        self.code_block_parser_field.SetParserNetwork(self)
        self.declaration_assign_parser_field = DeclarationAssignParser()
        self.declaration_assign_parser_field.SetParserNetwork(self)
        self.declaration_parser_field = DeclarationParser()
        self.declaration_parser_field.SetParserNetwork(self)
        self.assignment_parser_field = AssignmentParser()
        self.assignment_parser_field.SetParserNetwork(self)
        self.return_parser_field = ReturnParser()
        self.return_parser_field.SetParserNetwork(self)
        self.else_tail_parser_field = ElseTailParser()
        self.else_tail_parser_field.SetParserNetwork(self)
        self.conditional_parser_field = ConditionalParser()
        self.conditional_parser_field.SetParserNetwork(self)
        self.loop_parser_field = LoopParser()
        self.loop_parser_field.SetParserNetwork(self)
        self.call_parser_field = CallParser()
        self.call_parser_field.SetParserNetwork(self)
        self.allocate_parser_field = AllocateParser()
        self.allocate_parser_field.SetParserNetwork(self)
        self.instruction_parser_field = InstructionParser()
        self.instruction_parser_field.SetParserNetwork(self)
        self.r_value_single_parser_field = RValueSingleParser()
        self.r_value_single_parser_field.SetParserNetwork(self)
        self.r_value_tail_parser_field = RValueTailParser()
        self.r_value_tail_parser_field.SetParserNetwork(self)
        self.r_value_parser_field = RValueParser()
        self.r_value_parser_field.SetParserNetwork(self)
        self.binary_operator_parser_field = BinaryOperatorParser()
        self.binary_operator_parser_field.SetParserNetwork(self)
        self.unary_operator_parser_field = UnaryOperatorParser()
        self.unary_operator_parser_field.SetParserNetwork(self)
        self.comment_parser_field = CommentParser()
        self.comment_parser_field.SetParserNetwork(self)
        self.non_star_character_parser_field = NonStarCharacterParser()
        self.non_star_character_parser_field.SetParserNetwork(self)
        self.non_slash_character_parser_field = NonSlashCharacterParser()
        self.non_slash_character_parser_field.SetParserNetwork(self)
        self.comment_content_parser_field = CommentContentParser()
        self.comment_content_parser_field.SetParserNetwork(self)
        self.qualfied_name_parser_field = QualfiedNameParser()
        self.qualfied_name_parser_field.SetParserNetwork(self)
        self.name_tail_parser_field = NameTailParser()
        self.name_tail_parser_field.SetParserNetwork(self)
        self.name_parser_field = NameParser()
        self.name_parser_field.SetParserNetwork(self)
        self.name_character_parser_field = NameCharacterParser()
        self.name_character_parser_field.SetParserNetwork(self)
        self.boolean_parser_field = BooleanParser()
        self.boolean_parser_field.SetParserNetwork(self)
        self.byte_parser_field = ByteParser()
        self.byte_parser_field.SetParserNetwork(self)
        self.byte_digit_parser_field = ByteDigitParser()
        self.byte_digit_parser_field.SetParserNetwork(self)
        self.negative_parser_field = NegativeParser()
        self.negative_parser_field.SetParserNetwork(self)
        self.decimal_parser_field = DecimalParser()
        self.decimal_parser_field.SetParserNetwork(self)
        self.number_parser_field = NumberParser()
        self.number_parser_field.SetParserNetwork(self)
        self.digit_parser_field = DigitParser()
        self.digit_parser_field.SetParserNetwork(self)
        self.literal_parser_field = LiteralParser()
        self.literal_parser_field.SetParserNetwork(self)
        self.literal_character_parser_field = LiteralCharacterParser()
        self.literal_character_parser_field.SetParserNetwork(self)
        self.whitespace_parser_field = WhitespaceParser()
        self.whitespace_parser_field.SetParserNetwork(self)
        self.string_parser_field = StringParser()
        self.character_parser_field = CharacterParser()
        self.character_range_parser_field = CharacterRangeParser()

class DBNFOmniType:
    def __init__(self: 'DBNFOmniType'):
        self.c_t_code_file_field: CTCodeFile = None
        self.external_definition_field: ExternalDefinition = None
        self.unmanaged_type_field: UnmanagedType = None
        self.definition_field: Definition = None
        self.interface_def_field: InterfaceDef = None
        self.class_def_field: ClassDef = None
        self.implementation_spec_field: ImplementationSpec = None
        self.content_declaration_field: ContentDeclaration = None
        self.content_definition_field: ContentDefinition = None
        self.primative_type_field: PrimativeType = None
        self.defined_type_field: DefinedType = None
        self.singleton_type_field: SingletonType = None
        self.dimensional_note_field: DimensionalNote = None
        self.dimensional_type_field: DimensionalType = None
        self.map_note_field: MapNote = None
        self.map_type_field: MapType = None
        self.value_type_field: ValueType = None
        self.parameter_list_def_field: ParameterListDef = None
        self.parameter_list_field: ParameterList = None
        self.code_block_field: CodeBlock = None
        self.declaration_assign_field: DeclarationAssign = None
        self.declaration_field: Declaration = None
        self.assignment_field: Assignment = None
        self.return_field: Return = None
        self.else_tail_field: ElseTail = None
        self.conditional_field: Conditional = None
        self.loop_field: Loop = None
        self.call_field: Call = None
        self.allocate_field: Allocate = None
        self.instruction_field: Instruction = None
        self.r_value_single_field: RValueSingle = None
        self.r_value_tail_field: RValueTail = None
        self.r_value_field: RValue = None
        self.binary_operator_field: BinaryOperator = None
        self.unary_operator_field: UnaryOperator = None
        self.comment_field: Comment = None
        self.non_star_character_field: NonStarCharacter = None
        self.non_slash_character_field: NonSlashCharacter = None
        self.comment_content_field: CommentContent = None
        self.qualfied_name_field: QualfiedName = None
        self.name_tail_field: NameTail = None
        self.name_field: Name = None
        self.name_character_field: NameCharacter = None
        self.boolean_field: Boolean = None
        self.byte_field: Byte = None
        self.byte_digit_field: ByteDigit = None
        self.negative_field: Negative = None
        self.decimal_field: Decimal = None
        self.number_field: Number = None
        self.digit_field: Digit = None
        self.literal_field: Literal = None
        self.literal_character_field: LiteralCharacter = None
        self.whitespace_field: Whitespace = None

    def SetCTCodeFile(self: 'DBNFOmniType',input_value: 'CTCodeFile') -> 'None':
        self.c_t_code_file_field = input_value

    def GetCTCodeFile(self: 'DBNFOmniType') -> 'CTCodeFile':
        return self.c_t_code_file_field

    def SetExternalDefinition(self: 'DBNFOmniType',input_value: 'ExternalDefinition') -> 'None':
        self.external_definition_field = input_value

    def GetExternalDefinition(self: 'DBNFOmniType') -> 'ExternalDefinition':
        return self.external_definition_field

    def SetUnmanagedType(self: 'DBNFOmniType',input_value: 'UnmanagedType') -> 'None':
        self.unmanaged_type_field = input_value

    def GetUnmanagedType(self: 'DBNFOmniType') -> 'UnmanagedType':
        return self.unmanaged_type_field

    def SetDefinition(self: 'DBNFOmniType',input_value: 'Definition') -> 'None':
        self.definition_field = input_value

    def GetDefinition(self: 'DBNFOmniType') -> 'Definition':
        return self.definition_field

    def SetInterfaceDef(self: 'DBNFOmniType',input_value: 'InterfaceDef') -> 'None':
        self.interface_def_field = input_value

    def GetInterfaceDef(self: 'DBNFOmniType') -> 'InterfaceDef':
        return self.interface_def_field

    def SetClassDef(self: 'DBNFOmniType',input_value: 'ClassDef') -> 'None':
        self.class_def_field = input_value

    def GetClassDef(self: 'DBNFOmniType') -> 'ClassDef':
        return self.class_def_field

    def SetImplementationSpec(self: 'DBNFOmniType',input_value: 'ImplementationSpec') -> 'None':
        self.implementation_spec_field = input_value

    def GetImplementationSpec(self: 'DBNFOmniType') -> 'ImplementationSpec':
        return self.implementation_spec_field

    def SetContentDeclaration(self: 'DBNFOmniType',input_value: 'ContentDeclaration') -> 'None':
        self.content_declaration_field = input_value

    def GetContentDeclaration(self: 'DBNFOmniType') -> 'ContentDeclaration':
        return self.content_declaration_field

    def SetContentDefinition(self: 'DBNFOmniType',input_value: 'ContentDefinition') -> 'None':
        self.content_definition_field = input_value

    def GetContentDefinition(self: 'DBNFOmniType') -> 'ContentDefinition':
        return self.content_definition_field

    def SetPrimativeType(self: 'DBNFOmniType',input_value: 'PrimativeType') -> 'None':
        self.primative_type_field = input_value

    def GetPrimativeType(self: 'DBNFOmniType') -> 'PrimativeType':
        return self.primative_type_field

    def SetDefinedType(self: 'DBNFOmniType',input_value: 'DefinedType') -> 'None':
        self.defined_type_field = input_value

    def GetDefinedType(self: 'DBNFOmniType') -> 'DefinedType':
        return self.defined_type_field

    def SetSingletonType(self: 'DBNFOmniType',input_value: 'SingletonType') -> 'None':
        self.singleton_type_field = input_value

    def GetSingletonType(self: 'DBNFOmniType') -> 'SingletonType':
        return self.singleton_type_field

    def SetDimensionalNote(self: 'DBNFOmniType',input_value: 'DimensionalNote') -> 'None':
        self.dimensional_note_field = input_value

    def GetDimensionalNote(self: 'DBNFOmniType') -> 'DimensionalNote':
        return self.dimensional_note_field

    def SetDimensionalType(self: 'DBNFOmniType',input_value: 'DimensionalType') -> 'None':
        self.dimensional_type_field = input_value

    def GetDimensionalType(self: 'DBNFOmniType') -> 'DimensionalType':
        return self.dimensional_type_field

    def SetMapNote(self: 'DBNFOmniType',input_value: 'MapNote') -> 'None':
        self.map_note_field = input_value

    def GetMapNote(self: 'DBNFOmniType') -> 'MapNote':
        return self.map_note_field

    def SetMapType(self: 'DBNFOmniType',input_value: 'MapType') -> 'None':
        self.map_type_field = input_value

    def GetMapType(self: 'DBNFOmniType') -> 'MapType':
        return self.map_type_field

    def SetValueType(self: 'DBNFOmniType',input_value: 'ValueType') -> 'None':
        self.value_type_field = input_value

    def GetValueType(self: 'DBNFOmniType') -> 'ValueType':
        return self.value_type_field

    def SetParameterListDef(self: 'DBNFOmniType',input_value: 'ParameterListDef') -> 'None':
        self.parameter_list_def_field = input_value

    def GetParameterListDef(self: 'DBNFOmniType') -> 'ParameterListDef':
        return self.parameter_list_def_field

    def SetParameterList(self: 'DBNFOmniType',input_value: 'ParameterList') -> 'None':
        self.parameter_list_field = input_value

    def GetParameterList(self: 'DBNFOmniType') -> 'ParameterList':
        return self.parameter_list_field

    def SetCodeBlock(self: 'DBNFOmniType',input_value: 'CodeBlock') -> 'None':
        self.code_block_field = input_value

    def GetCodeBlock(self: 'DBNFOmniType') -> 'CodeBlock':
        return self.code_block_field

    def SetDeclarationAssign(self: 'DBNFOmniType',input_value: 'DeclarationAssign') -> 'None':
        self.declaration_assign_field = input_value

    def GetDeclarationAssign(self: 'DBNFOmniType') -> 'DeclarationAssign':
        return self.declaration_assign_field

    def SetDeclaration(self: 'DBNFOmniType',input_value: 'Declaration') -> 'None':
        self.declaration_field = input_value

    def GetDeclaration(self: 'DBNFOmniType') -> 'Declaration':
        return self.declaration_field

    def SetAssignment(self: 'DBNFOmniType',input_value: 'Assignment') -> 'None':
        self.assignment_field = input_value

    def GetAssignment(self: 'DBNFOmniType') -> 'Assignment':
        return self.assignment_field

    def SetReturn(self: 'DBNFOmniType',input_value: 'Return') -> 'None':
        self.return_field = input_value

    def GetReturn(self: 'DBNFOmniType') -> 'Return':
        return self.return_field

    def SetElseTail(self: 'DBNFOmniType',input_value: 'ElseTail') -> 'None':
        self.else_tail_field = input_value

    def GetElseTail(self: 'DBNFOmniType') -> 'ElseTail':
        return self.else_tail_field

    def SetConditional(self: 'DBNFOmniType',input_value: 'Conditional') -> 'None':
        self.conditional_field = input_value

    def GetConditional(self: 'DBNFOmniType') -> 'Conditional':
        return self.conditional_field

    def SetLoop(self: 'DBNFOmniType',input_value: 'Loop') -> 'None':
        self.loop_field = input_value

    def GetLoop(self: 'DBNFOmniType') -> 'Loop':
        return self.loop_field

    def SetCall(self: 'DBNFOmniType',input_value: 'Call') -> 'None':
        self.call_field = input_value

    def GetCall(self: 'DBNFOmniType') -> 'Call':
        return self.call_field

    def SetAllocate(self: 'DBNFOmniType',input_value: 'Allocate') -> 'None':
        self.allocate_field = input_value

    def GetAllocate(self: 'DBNFOmniType') -> 'Allocate':
        return self.allocate_field

    def SetInstruction(self: 'DBNFOmniType',input_value: 'Instruction') -> 'None':
        self.instruction_field = input_value

    def GetInstruction(self: 'DBNFOmniType') -> 'Instruction':
        return self.instruction_field

    def SetRValueSingle(self: 'DBNFOmniType',input_value: 'RValueSingle') -> 'None':
        self.r_value_single_field = input_value

    def GetRValueSingle(self: 'DBNFOmniType') -> 'RValueSingle':
        return self.r_value_single_field

    def SetRValueTail(self: 'DBNFOmniType',input_value: 'RValueTail') -> 'None':
        self.r_value_tail_field = input_value

    def GetRValueTail(self: 'DBNFOmniType') -> 'RValueTail':
        return self.r_value_tail_field

    def SetRValue(self: 'DBNFOmniType',input_value: 'RValue') -> 'None':
        self.r_value_field = input_value

    def GetRValue(self: 'DBNFOmniType') -> 'RValue':
        return self.r_value_field

    def SetBinaryOperator(self: 'DBNFOmniType',input_value: 'BinaryOperator') -> 'None':
        self.binary_operator_field = input_value

    def GetBinaryOperator(self: 'DBNFOmniType') -> 'BinaryOperator':
        return self.binary_operator_field

    def SetUnaryOperator(self: 'DBNFOmniType',input_value: 'UnaryOperator') -> 'None':
        self.unary_operator_field = input_value

    def GetUnaryOperator(self: 'DBNFOmniType') -> 'UnaryOperator':
        return self.unary_operator_field

    def SetComment(self: 'DBNFOmniType',input_value: 'Comment') -> 'None':
        self.comment_field = input_value

    def GetComment(self: 'DBNFOmniType') -> 'Comment':
        return self.comment_field

    def SetNonStarCharacter(self: 'DBNFOmniType',input_value: 'NonStarCharacter') -> 'None':
        self.non_star_character_field = input_value

    def GetNonStarCharacter(self: 'DBNFOmniType') -> 'NonStarCharacter':
        return self.non_star_character_field

    def SetNonSlashCharacter(self: 'DBNFOmniType',input_value: 'NonSlashCharacter') -> 'None':
        self.non_slash_character_field = input_value

    def GetNonSlashCharacter(self: 'DBNFOmniType') -> 'NonSlashCharacter':
        return self.non_slash_character_field

    def SetCommentContent(self: 'DBNFOmniType',input_value: 'CommentContent') -> 'None':
        self.comment_content_field = input_value

    def GetCommentContent(self: 'DBNFOmniType') -> 'CommentContent':
        return self.comment_content_field

    def SetQualfiedName(self: 'DBNFOmniType',input_value: 'QualfiedName') -> 'None':
        self.qualfied_name_field = input_value

    def GetQualfiedName(self: 'DBNFOmniType') -> 'QualfiedName':
        return self.qualfied_name_field

    def SetNameTail(self: 'DBNFOmniType',input_value: 'NameTail') -> 'None':
        self.name_tail_field = input_value

    def GetNameTail(self: 'DBNFOmniType') -> 'NameTail':
        return self.name_tail_field

    def SetName(self: 'DBNFOmniType',input_value: 'Name') -> 'None':
        self.name_field = input_value

    def GetName(self: 'DBNFOmniType') -> 'Name':
        return self.name_field

    def SetNameCharacter(self: 'DBNFOmniType',input_value: 'NameCharacter') -> 'None':
        self.name_character_field = input_value

    def GetNameCharacter(self: 'DBNFOmniType') -> 'NameCharacter':
        return self.name_character_field

    def SetBoolean(self: 'DBNFOmniType',input_value: 'Boolean') -> 'None':
        self.boolean_field = input_value

    def GetBoolean(self: 'DBNFOmniType') -> 'Boolean':
        return self.boolean_field

    def SetByte(self: 'DBNFOmniType',input_value: 'Byte') -> 'None':
        self.byte_field = input_value

    def GetByte(self: 'DBNFOmniType') -> 'Byte':
        return self.byte_field

    def SetByteDigit(self: 'DBNFOmniType',input_value: 'ByteDigit') -> 'None':
        self.byte_digit_field = input_value

    def GetByteDigit(self: 'DBNFOmniType') -> 'ByteDigit':
        return self.byte_digit_field

    def SetNegative(self: 'DBNFOmniType',input_value: 'Negative') -> 'None':
        self.negative_field = input_value

    def GetNegative(self: 'DBNFOmniType') -> 'Negative':
        return self.negative_field

    def SetDecimal(self: 'DBNFOmniType',input_value: 'Decimal') -> 'None':
        self.decimal_field = input_value

    def GetDecimal(self: 'DBNFOmniType') -> 'Decimal':
        return self.decimal_field

    def SetNumber(self: 'DBNFOmniType',input_value: 'Number') -> 'None':
        self.number_field = input_value

    def GetNumber(self: 'DBNFOmniType') -> 'Number':
        return self.number_field

    def SetDigit(self: 'DBNFOmniType',input_value: 'Digit') -> 'None':
        self.digit_field = input_value

    def GetDigit(self: 'DBNFOmniType') -> 'Digit':
        return self.digit_field

    def SetLiteral(self: 'DBNFOmniType',input_value: 'Literal') -> 'None':
        self.literal_field = input_value

    def GetLiteral(self: 'DBNFOmniType') -> 'Literal':
        return self.literal_field

    def SetLiteralCharacter(self: 'DBNFOmniType',input_value: 'LiteralCharacter') -> 'None':
        self.literal_character_field = input_value

    def GetLiteralCharacter(self: 'DBNFOmniType') -> 'LiteralCharacter':
        return self.literal_character_field

    def SetWhitespace(self: 'DBNFOmniType',input_value: 'Whitespace') -> 'None':
        self.whitespace_field = input_value

    def GetWhitespace(self: 'DBNFOmniType') -> 'Whitespace':
        return self.whitespace_field

class DBNFOmniTypeResult:
    def __init__(self: 'DBNFOmniTypeResult'):
        self.value: DBNFOmniType = None
        self.result: bool = False

    def SetValue(self: 'DBNFOmniTypeResult',new_value: 'DBNFOmniType') -> 'None':
        self.value = new_value

    def GetValue(self: 'DBNFOmniTypeResult') -> 'DBNFOmniType':
        return self.value

    def SetResult(self: 'DBNFOmniTypeResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'DBNFOmniTypeResult') -> 'bool':
        return self.result

    def SetCTCodeFile(self: 'DBNFOmniTypeResult',input_value: 'CTCodeFile') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetCTCodeFile(input_value)

    def SetExternalDefinition(self: 'DBNFOmniTypeResult',input_value: 'ExternalDefinition') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetExternalDefinition(input_value)

    def SetUnmanagedType(self: 'DBNFOmniTypeResult',input_value: 'UnmanagedType') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetUnmanagedType(input_value)

    def SetDefinition(self: 'DBNFOmniTypeResult',input_value: 'Definition') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetDefinition(input_value)

    def SetInterfaceDef(self: 'DBNFOmniTypeResult',input_value: 'InterfaceDef') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetInterfaceDef(input_value)

    def SetClassDef(self: 'DBNFOmniTypeResult',input_value: 'ClassDef') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetClassDef(input_value)

    def SetImplementationSpec(self: 'DBNFOmniTypeResult',input_value: 'ImplementationSpec') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetImplementationSpec(input_value)

    def SetContentDeclaration(self: 'DBNFOmniTypeResult',input_value: 'ContentDeclaration') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetContentDeclaration(input_value)

    def SetContentDefinition(self: 'DBNFOmniTypeResult',input_value: 'ContentDefinition') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetContentDefinition(input_value)

    def SetPrimativeType(self: 'DBNFOmniTypeResult',input_value: 'PrimativeType') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetPrimativeType(input_value)

    def SetDefinedType(self: 'DBNFOmniTypeResult',input_value: 'DefinedType') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetDefinedType(input_value)

    def SetSingletonType(self: 'DBNFOmniTypeResult',input_value: 'SingletonType') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetSingletonType(input_value)

    def SetDimensionalNote(self: 'DBNFOmniTypeResult',input_value: 'DimensionalNote') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetDimensionalNote(input_value)

    def SetDimensionalType(self: 'DBNFOmniTypeResult',input_value: 'DimensionalType') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetDimensionalType(input_value)

    def SetMapNote(self: 'DBNFOmniTypeResult',input_value: 'MapNote') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetMapNote(input_value)

    def SetMapType(self: 'DBNFOmniTypeResult',input_value: 'MapType') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetMapType(input_value)

    def SetValueType(self: 'DBNFOmniTypeResult',input_value: 'ValueType') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetValueType(input_value)

    def SetParameterListDef(self: 'DBNFOmniTypeResult',input_value: 'ParameterListDef') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetParameterListDef(input_value)

    def SetParameterList(self: 'DBNFOmniTypeResult',input_value: 'ParameterList') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetParameterList(input_value)

    def SetCodeBlock(self: 'DBNFOmniTypeResult',input_value: 'CodeBlock') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetCodeBlock(input_value)

    def SetDeclarationAssign(self: 'DBNFOmniTypeResult',input_value: 'DeclarationAssign') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetDeclarationAssign(input_value)

    def SetDeclaration(self: 'DBNFOmniTypeResult',input_value: 'Declaration') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetDeclaration(input_value)

    def SetAssignment(self: 'DBNFOmniTypeResult',input_value: 'Assignment') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetAssignment(input_value)

    def SetReturn(self: 'DBNFOmniTypeResult',input_value: 'Return') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetReturn(input_value)

    def SetElseTail(self: 'DBNFOmniTypeResult',input_value: 'ElseTail') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetElseTail(input_value)

    def SetConditional(self: 'DBNFOmniTypeResult',input_value: 'Conditional') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetConditional(input_value)

    def SetLoop(self: 'DBNFOmniTypeResult',input_value: 'Loop') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetLoop(input_value)

    def SetCall(self: 'DBNFOmniTypeResult',input_value: 'Call') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetCall(input_value)

    def SetAllocate(self: 'DBNFOmniTypeResult',input_value: 'Allocate') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetAllocate(input_value)

    def SetInstruction(self: 'DBNFOmniTypeResult',input_value: 'Instruction') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetInstruction(input_value)

    def SetRValueSingle(self: 'DBNFOmniTypeResult',input_value: 'RValueSingle') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetRValueSingle(input_value)

    def SetRValueTail(self: 'DBNFOmniTypeResult',input_value: 'RValueTail') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetRValueTail(input_value)

    def SetRValue(self: 'DBNFOmniTypeResult',input_value: 'RValue') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetRValue(input_value)

    def SetBinaryOperator(self: 'DBNFOmniTypeResult',input_value: 'BinaryOperator') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetBinaryOperator(input_value)

    def SetUnaryOperator(self: 'DBNFOmniTypeResult',input_value: 'UnaryOperator') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetUnaryOperator(input_value)

    def SetComment(self: 'DBNFOmniTypeResult',input_value: 'Comment') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetComment(input_value)

    def SetNonStarCharacter(self: 'DBNFOmniTypeResult',input_value: 'NonStarCharacter') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetNonStarCharacter(input_value)

    def SetNonSlashCharacter(self: 'DBNFOmniTypeResult',input_value: 'NonSlashCharacter') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetNonSlashCharacter(input_value)

    def SetCommentContent(self: 'DBNFOmniTypeResult',input_value: 'CommentContent') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetCommentContent(input_value)

    def SetQualfiedName(self: 'DBNFOmniTypeResult',input_value: 'QualfiedName') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetQualfiedName(input_value)

    def SetNameTail(self: 'DBNFOmniTypeResult',input_value: 'NameTail') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetNameTail(input_value)

    def SetName(self: 'DBNFOmniTypeResult',input_value: 'Name') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetName(input_value)

    def SetNameCharacter(self: 'DBNFOmniTypeResult',input_value: 'NameCharacter') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetNameCharacter(input_value)

    def SetBoolean(self: 'DBNFOmniTypeResult',input_value: 'Boolean') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetBoolean(input_value)

    def SetByte(self: 'DBNFOmniTypeResult',input_value: 'Byte') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetByte(input_value)

    def SetByteDigit(self: 'DBNFOmniTypeResult',input_value: 'ByteDigit') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetByteDigit(input_value)

    def SetNegative(self: 'DBNFOmniTypeResult',input_value: 'Negative') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetNegative(input_value)

    def SetDecimal(self: 'DBNFOmniTypeResult',input_value: 'Decimal') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetDecimal(input_value)

    def SetNumber(self: 'DBNFOmniTypeResult',input_value: 'Number') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetNumber(input_value)

    def SetDigit(self: 'DBNFOmniTypeResult',input_value: 'Digit') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetDigit(input_value)

    def SetLiteral(self: 'DBNFOmniTypeResult',input_value: 'Literal') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetLiteral(input_value)

    def SetLiteralCharacter(self: 'DBNFOmniTypeResult',input_value: 'LiteralCharacter') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetLiteralCharacter(input_value)

    def SetWhitespace(self: 'DBNFOmniTypeResult',input_value: 'Whitespace') -> 'None':
        self.value = DBNFOmniType()
        self.value.SetWhitespace(input_value)

class DBNFOmniTypeListResult:
    def __init__(self: 'DBNFOmniTypeListResult'):
        self.value: list[DBNFOmniType] = []
        self.result: bool = False

    def SetValue(self: 'DBNFOmniTypeListResult',new_value: 'list[DBNFOmniType]') -> 'None':
        self.value = new_value

    def GetValue(self: 'DBNFOmniTypeListResult') -> 'list[DBNFOmniType]':
        return self.value

    def SetResult(self: 'DBNFOmniTypeListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'DBNFOmniTypeListResult') -> 'bool':
        return self.result

    def SetCTCodeFile(self: 'DBNFOmniTypeListResult',input_value: 'list[CTCodeFile]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetCTCodeFile(Element(input_value,index))
            index = index+1

    def SetExternalDefinition(self: 'DBNFOmniTypeListResult',input_value: 'list[ExternalDefinition]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetExternalDefinition(Element(input_value,index))
            index = index+1

    def SetUnmanagedType(self: 'DBNFOmniTypeListResult',input_value: 'list[UnmanagedType]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetUnmanagedType(Element(input_value,index))
            index = index+1

    def SetDefinition(self: 'DBNFOmniTypeListResult',input_value: 'list[Definition]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetDefinition(Element(input_value,index))
            index = index+1

    def SetInterfaceDef(self: 'DBNFOmniTypeListResult',input_value: 'list[InterfaceDef]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetInterfaceDef(Element(input_value,index))
            index = index+1

    def SetClassDef(self: 'DBNFOmniTypeListResult',input_value: 'list[ClassDef]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetClassDef(Element(input_value,index))
            index = index+1

    def SetImplementationSpec(self: 'DBNFOmniTypeListResult',input_value: 'list[ImplementationSpec]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetImplementationSpec(Element(input_value,index))
            index = index+1

    def SetContentDeclaration(self: 'DBNFOmniTypeListResult',input_value: 'list[ContentDeclaration]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetContentDeclaration(Element(input_value,index))
            index = index+1

    def SetContentDefinition(self: 'DBNFOmniTypeListResult',input_value: 'list[ContentDefinition]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetContentDefinition(Element(input_value,index))
            index = index+1

    def SetPrimativeType(self: 'DBNFOmniTypeListResult',input_value: 'list[PrimativeType]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetPrimativeType(Element(input_value,index))
            index = index+1

    def SetDefinedType(self: 'DBNFOmniTypeListResult',input_value: 'list[DefinedType]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetDefinedType(Element(input_value,index))
            index = index+1

    def SetSingletonType(self: 'DBNFOmniTypeListResult',input_value: 'list[SingletonType]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetSingletonType(Element(input_value,index))
            index = index+1

    def SetDimensionalNote(self: 'DBNFOmniTypeListResult',input_value: 'list[DimensionalNote]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetDimensionalNote(Element(input_value,index))
            index = index+1

    def SetDimensionalType(self: 'DBNFOmniTypeListResult',input_value: 'list[DimensionalType]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetDimensionalType(Element(input_value,index))
            index = index+1

    def SetMapNote(self: 'DBNFOmniTypeListResult',input_value: 'list[MapNote]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetMapNote(Element(input_value,index))
            index = index+1

    def SetMapType(self: 'DBNFOmniTypeListResult',input_value: 'list[MapType]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetMapType(Element(input_value,index))
            index = index+1

    def SetValueType(self: 'DBNFOmniTypeListResult',input_value: 'list[ValueType]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetValueType(Element(input_value,index))
            index = index+1

    def SetParameterListDef(self: 'DBNFOmniTypeListResult',input_value: 'list[ParameterListDef]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetParameterListDef(Element(input_value,index))
            index = index+1

    def SetParameterList(self: 'DBNFOmniTypeListResult',input_value: 'list[ParameterList]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetParameterList(Element(input_value,index))
            index = index+1

    def SetCodeBlock(self: 'DBNFOmniTypeListResult',input_value: 'list[CodeBlock]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetCodeBlock(Element(input_value,index))
            index = index+1

    def SetDeclarationAssign(self: 'DBNFOmniTypeListResult',input_value: 'list[DeclarationAssign]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetDeclarationAssign(Element(input_value,index))
            index = index+1

    def SetDeclaration(self: 'DBNFOmniTypeListResult',input_value: 'list[Declaration]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetDeclaration(Element(input_value,index))
            index = index+1

    def SetAssignment(self: 'DBNFOmniTypeListResult',input_value: 'list[Assignment]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetAssignment(Element(input_value,index))
            index = index+1

    def SetReturn(self: 'DBNFOmniTypeListResult',input_value: 'list[Return]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetReturn(Element(input_value,index))
            index = index+1

    def SetElseTail(self: 'DBNFOmniTypeListResult',input_value: 'list[ElseTail]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetElseTail(Element(input_value,index))
            index = index+1

    def SetConditional(self: 'DBNFOmniTypeListResult',input_value: 'list[Conditional]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetConditional(Element(input_value,index))
            index = index+1

    def SetLoop(self: 'DBNFOmniTypeListResult',input_value: 'list[Loop]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetLoop(Element(input_value,index))
            index = index+1

    def SetCall(self: 'DBNFOmniTypeListResult',input_value: 'list[Call]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetCall(Element(input_value,index))
            index = index+1

    def SetAllocate(self: 'DBNFOmniTypeListResult',input_value: 'list[Allocate]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetAllocate(Element(input_value,index))
            index = index+1

    def SetInstruction(self: 'DBNFOmniTypeListResult',input_value: 'list[Instruction]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetInstruction(Element(input_value,index))
            index = index+1

    def SetRValueSingle(self: 'DBNFOmniTypeListResult',input_value: 'list[RValueSingle]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetRValueSingle(Element(input_value,index))
            index = index+1

    def SetRValueTail(self: 'DBNFOmniTypeListResult',input_value: 'list[RValueTail]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetRValueTail(Element(input_value,index))
            index = index+1

    def SetRValue(self: 'DBNFOmniTypeListResult',input_value: 'list[RValue]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetRValue(Element(input_value,index))
            index = index+1

    def SetBinaryOperator(self: 'DBNFOmniTypeListResult',input_value: 'list[BinaryOperator]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetBinaryOperator(Element(input_value,index))
            index = index+1

    def SetUnaryOperator(self: 'DBNFOmniTypeListResult',input_value: 'list[UnaryOperator]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetUnaryOperator(Element(input_value,index))
            index = index+1

    def SetComment(self: 'DBNFOmniTypeListResult',input_value: 'list[Comment]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetComment(Element(input_value,index))
            index = index+1

    def SetNonStarCharacter(self: 'DBNFOmniTypeListResult',input_value: 'list[NonStarCharacter]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetNonStarCharacter(Element(input_value,index))
            index = index+1

    def SetNonSlashCharacter(self: 'DBNFOmniTypeListResult',input_value: 'list[NonSlashCharacter]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetNonSlashCharacter(Element(input_value,index))
            index = index+1

    def SetCommentContent(self: 'DBNFOmniTypeListResult',input_value: 'list[CommentContent]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetCommentContent(Element(input_value,index))
            index = index+1

    def SetQualfiedName(self: 'DBNFOmniTypeListResult',input_value: 'list[QualfiedName]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetQualfiedName(Element(input_value,index))
            index = index+1

    def SetNameTail(self: 'DBNFOmniTypeListResult',input_value: 'list[NameTail]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetNameTail(Element(input_value,index))
            index = index+1

    def SetName(self: 'DBNFOmniTypeListResult',input_value: 'list[Name]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetName(Element(input_value,index))
            index = index+1

    def SetNameCharacter(self: 'DBNFOmniTypeListResult',input_value: 'list[NameCharacter]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetNameCharacter(Element(input_value,index))
            index = index+1

    def SetBoolean(self: 'DBNFOmniTypeListResult',input_value: 'list[Boolean]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetBoolean(Element(input_value,index))
            index = index+1

    def SetByte(self: 'DBNFOmniTypeListResult',input_value: 'list[Byte]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetByte(Element(input_value,index))
            index = index+1

    def SetByteDigit(self: 'DBNFOmniTypeListResult',input_value: 'list[ByteDigit]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetByteDigit(Element(input_value,index))
            index = index+1

    def SetNegative(self: 'DBNFOmniTypeListResult',input_value: 'list[Negative]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetNegative(Element(input_value,index))
            index = index+1

    def SetDecimal(self: 'DBNFOmniTypeListResult',input_value: 'list[Decimal]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetDecimal(Element(input_value,index))
            index = index+1

    def SetNumber(self: 'DBNFOmniTypeListResult',input_value: 'list[Number]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetNumber(Element(input_value,index))
            index = index+1

    def SetDigit(self: 'DBNFOmniTypeListResult',input_value: 'list[Digit]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetDigit(Element(input_value,index))
            index = index+1

    def SetLiteral(self: 'DBNFOmniTypeListResult',input_value: 'list[Literal]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetLiteral(Element(input_value,index))
            index = index+1

    def SetLiteralCharacter(self: 'DBNFOmniTypeListResult',input_value: 'list[LiteralCharacter]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetLiteralCharacter(Element(input_value,index))
            index = index+1

    def SetWhitespace(self: 'DBNFOmniTypeListResult',input_value: 'list[Whitespace]') -> 'None':
        index: 'int' = 0
        while index<Size(input_value):
            value: 'DBNFOmniType' = DBNFOmniType()
            value.SetWhitespace(Element(input_value,index))
            index = index+1

class LargeString:
    def __init__(self: 'LargeString'):
        self.data: str = ""

    def SetData(self: 'LargeString',new_data: 'str') -> 'None':
        self.data = new_data

    def GetData(self: 'LargeString') -> 'str':
        return self.data

    def GetIntAt(self: 'LargeString',offset: 'int') -> 'int':
        return IntAt(self.data,offset)

    def GetAt(self: 'LargeString',offset: 'int') -> 'str':
        return At(self.data,offset)

class LengthString:
    def __init__(self: 'LengthString'):
        self.data: LargeString = None
        self.start: int = 0
        self.length: int = 0

    def SetData(self: 'LengthString',new_data: 'LargeString') -> 'None':
        self.data = new_data

    def GetData(self: 'LengthString') -> 'LargeString':
        return self.data

    def SetStart(self: 'LengthString',new_start: 'int') -> 'None':
        self.start = new_start

    def GetStart(self: 'LengthString') -> 'int':
        return self.start

    def SetLength(self: 'LengthString',new_length: 'int') -> 'None':
        self.length = new_length

    def GetLength(self: 'LengthString') -> 'int':
        return self.length

    def GetString(self: 'LengthString') -> 'str':
        deep_data: 'str' = self.data.GetData()
        result: 'str' = ""
        index: 'int' = self.start
        end: 'int' = self.start+self.length
        while index<end:
            result = Concat(result,At(deep_data,index))
            index = index+1
        return result

class CTCodeFileParser:
    def __init__(self: 'CTCodeFileParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'CTCodeFileParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'CTCodeFileParser',index: 'LengthString',result: 'CTCodeFileResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'CTCodeFile' = CTCodeFile()
        declarations_field: 'ExternalDefinitionListResult' = ExternalDefinitionListResult()
        definitions_field: 'DefinitionListResult' = DefinitionListResult()
        unmanaged_types_field: 'UnmanagedTypeListResult' = UnmanagedTypeListResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and external_definition_parser_instance.ParseManySave(index,declarations_field,0,-1) and unmanaged_type_parser_instance.ParseManySave(index,unmanaged_types_field,0,-1) and definition_parser_instance.ParseManySave(index,definitions_field,0,-1):
            instance.SetDeclarations(declarations_field.GetValue())
            instance.SetDefinitions(definitions_field.GetValue())
            instance.SetUnmanagedTypes(unmanaged_types_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            declarations_field = ExternalDefinitionListResult()
            definitions_field = DefinitionListResult()
            unmanaged_types_field = UnmanagedTypeListResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'CTCodeFileParser',index: 'LengthString') -> 'bool':
        result: 'CTCodeFileResult' = CTCodeFileResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'CTCodeFileParser',index: 'LengthString',result: 'CTCodeFileResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'CTCodeFileParser',index: 'LengthString') -> 'bool':
        result: 'CTCodeFileResult' = CTCodeFileResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'CTCodeFileParser',index: 'LengthString',list_result: 'CTCodeFileListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[CTCodeFile]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'CTCodeFileResult' = CTCodeFileResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'CTCodeFileParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'CTCodeFileListResult' = CTCodeFileListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class CTCodeFileResult:
    def __init__(self: 'CTCodeFileResult'):
        self.value: CTCodeFile = None
        self.result: bool = False

    def SetValue(self: 'CTCodeFileResult',new_value: 'CTCodeFile') -> 'None':
        self.value = new_value

    def GetValue(self: 'CTCodeFileResult') -> 'CTCodeFile':
        return self.value

    def SetResult(self: 'CTCodeFileResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'CTCodeFileResult') -> 'bool':
        return self.result

class CTCodeFileListResult:
    def __init__(self: 'CTCodeFileListResult'):
        self.value: list[CTCodeFile] = []
        self.result: bool = False

    def SetValue(self: 'CTCodeFileListResult',new_value: 'list[CTCodeFile]') -> 'None':
        self.value = new_value

    def GetValue(self: 'CTCodeFileListResult') -> 'list[CTCodeFile]':
        return self.value

    def SetResult(self: 'CTCodeFileListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'CTCodeFileListResult') -> 'bool':
        return self.result

class CTCodeFile:
    def __init__(self: 'CTCodeFile'):
        self.length_string: LengthString = None
        self.declarations_field: list[ExternalDefinition] = []
        self.definitions_field: list[Definition] = []
        self.unmanaged_types_field: list[UnmanagedType] = []

    def SetLengthString(self: 'CTCodeFile',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'CTCodeFile') -> 'str':
        return self.length_string.GetString()

    def SetDeclarations(self: 'CTCodeFile',input_value: 'list[ExternalDefinition]') -> 'None':
        self.declarations_field = input_value

    def GetDeclarations(self: 'CTCodeFile') -> 'list[ExternalDefinition]':
        return self.declarations_field

    def SetDefinitions(self: 'CTCodeFile',input_value: 'list[Definition]') -> 'None':
        self.definitions_field = input_value

    def GetDefinitions(self: 'CTCodeFile') -> 'list[Definition]':
        return self.definitions_field

    def SetUnmanagedTypes(self: 'CTCodeFile',input_value: 'list[UnmanagedType]') -> 'None':
        self.unmanaged_types_field = input_value

    def GetUnmanagedTypes(self: 'CTCodeFile') -> 'list[UnmanagedType]':
        return self.unmanaged_types_field

class ExternalDefinitionParser:
    def __init__(self: 'ExternalDefinitionParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'ExternalDefinitionParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'ExternalDefinitionParser',index: 'LengthString',result: 'ExternalDefinitionResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'ExternalDefinition' = ExternalDefinition()
        exdef_field: 'QualfiedNameResult' = QualfiedNameResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and string_parser_instance.ParseSingle(index,"exdef") and whitespace_parser_instance.ParseMany(index,0,-1) and qualfied_name_parser_instance.ParseSingleSave(index,exdef_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,";") and whitespace_parser_instance.ParseMany(index,0,-1):
            instance.SetExdef(exdef_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            exdef_field = QualfiedNameResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'ExternalDefinitionParser',index: 'LengthString') -> 'bool':
        result: 'ExternalDefinitionResult' = ExternalDefinitionResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'ExternalDefinitionParser',index: 'LengthString',result: 'ExternalDefinitionResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'ExternalDefinitionParser',index: 'LengthString') -> 'bool':
        result: 'ExternalDefinitionResult' = ExternalDefinitionResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'ExternalDefinitionParser',index: 'LengthString',list_result: 'ExternalDefinitionListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[ExternalDefinition]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'ExternalDefinitionResult' = ExternalDefinitionResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'ExternalDefinitionParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'ExternalDefinitionListResult' = ExternalDefinitionListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class ExternalDefinitionResult:
    def __init__(self: 'ExternalDefinitionResult'):
        self.value: ExternalDefinition = None
        self.result: bool = False

    def SetValue(self: 'ExternalDefinitionResult',new_value: 'ExternalDefinition') -> 'None':
        self.value = new_value

    def GetValue(self: 'ExternalDefinitionResult') -> 'ExternalDefinition':
        return self.value

    def SetResult(self: 'ExternalDefinitionResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'ExternalDefinitionResult') -> 'bool':
        return self.result

class ExternalDefinitionListResult:
    def __init__(self: 'ExternalDefinitionListResult'):
        self.value: list[ExternalDefinition] = []
        self.result: bool = False

    def SetValue(self: 'ExternalDefinitionListResult',new_value: 'list[ExternalDefinition]') -> 'None':
        self.value = new_value

    def GetValue(self: 'ExternalDefinitionListResult') -> 'list[ExternalDefinition]':
        return self.value

    def SetResult(self: 'ExternalDefinitionListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'ExternalDefinitionListResult') -> 'bool':
        return self.result

class ExternalDefinition:
    def __init__(self: 'ExternalDefinition'):
        self.length_string: LengthString = None
        self.exdef_field: QualfiedName = None

    def SetLengthString(self: 'ExternalDefinition',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'ExternalDefinition') -> 'str':
        return self.length_string.GetString()

    def SetExdef(self: 'ExternalDefinition',input_value: 'QualfiedName') -> 'None':
        self.exdef_field = input_value

    def GetExdef(self: 'ExternalDefinition') -> 'QualfiedName':
        return self.exdef_field

class UnmanagedTypeParser:
    def __init__(self: 'UnmanagedTypeParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'UnmanagedTypeParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'UnmanagedTypeParser',index: 'LengthString',result: 'UnmanagedTypeResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'UnmanagedType' = UnmanagedType()
        unmanaged_type_field: 'QualfiedNameResult' = QualfiedNameResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and string_parser_instance.ParseSingle(index,"unmanaged") and whitespace_parser_instance.ParseMany(index,0,-1) and qualfied_name_parser_instance.ParseSingleSave(index,unmanaged_type_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,";") and whitespace_parser_instance.ParseMany(index,0,-1):
            instance.SetUnmanagedType(unmanaged_type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            unmanaged_type_field = QualfiedNameResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'UnmanagedTypeParser',index: 'LengthString') -> 'bool':
        result: 'UnmanagedTypeResult' = UnmanagedTypeResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'UnmanagedTypeParser',index: 'LengthString',result: 'UnmanagedTypeResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'UnmanagedTypeParser',index: 'LengthString') -> 'bool':
        result: 'UnmanagedTypeResult' = UnmanagedTypeResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'UnmanagedTypeParser',index: 'LengthString',list_result: 'UnmanagedTypeListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[UnmanagedType]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'UnmanagedTypeResult' = UnmanagedTypeResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'UnmanagedTypeParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'UnmanagedTypeListResult' = UnmanagedTypeListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class UnmanagedTypeResult:
    def __init__(self: 'UnmanagedTypeResult'):
        self.value: UnmanagedType = None
        self.result: bool = False

    def SetValue(self: 'UnmanagedTypeResult',new_value: 'UnmanagedType') -> 'None':
        self.value = new_value

    def GetValue(self: 'UnmanagedTypeResult') -> 'UnmanagedType':
        return self.value

    def SetResult(self: 'UnmanagedTypeResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'UnmanagedTypeResult') -> 'bool':
        return self.result

class UnmanagedTypeListResult:
    def __init__(self: 'UnmanagedTypeListResult'):
        self.value: list[UnmanagedType] = []
        self.result: bool = False

    def SetValue(self: 'UnmanagedTypeListResult',new_value: 'list[UnmanagedType]') -> 'None':
        self.value = new_value

    def GetValue(self: 'UnmanagedTypeListResult') -> 'list[UnmanagedType]':
        return self.value

    def SetResult(self: 'UnmanagedTypeListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'UnmanagedTypeListResult') -> 'bool':
        return self.result

class UnmanagedType:
    def __init__(self: 'UnmanagedType'):
        self.length_string: LengthString = None
        self.unmanaged_type_field: QualfiedName = None

    def SetLengthString(self: 'UnmanagedType',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'UnmanagedType') -> 'str':
        return self.length_string.GetString()

    def SetUnmanagedType(self: 'UnmanagedType',input_value: 'QualfiedName') -> 'None':
        self.unmanaged_type_field = input_value

    def GetUnmanagedType(self: 'UnmanagedType') -> 'QualfiedName':
        return self.unmanaged_type_field

class DefinitionParser:
    def __init__(self: 'DefinitionParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'DefinitionParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'DefinitionParser',index: 'LengthString',result: 'DefinitionResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'Definition' = Definition()
        class_def_field: 'ClassDefResult' = ClassDefResult()
        interface_def_field: 'InterfaceDefResult' = InterfaceDefResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and interface_def_parser_instance.ParseSingleSave(index,interface_def_field):
            instance.SetClassDef(class_def_field.GetValue())
            instance.SetInterfaceDef(interface_def_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            class_def_field = ClassDefResult()
            interface_def_field = InterfaceDefResult()
        if True and class_def_parser_instance.ParseSingleSave(index,class_def_field):
            instance.SetClassDef(class_def_field.GetValue())
            instance.SetInterfaceDef(interface_def_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            class_def_field = ClassDefResult()
            interface_def_field = InterfaceDefResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'DefinitionParser',index: 'LengthString') -> 'bool':
        result: 'DefinitionResult' = DefinitionResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'DefinitionParser',index: 'LengthString',result: 'DefinitionResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'DefinitionParser',index: 'LengthString') -> 'bool':
        result: 'DefinitionResult' = DefinitionResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'DefinitionParser',index: 'LengthString',list_result: 'DefinitionListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[Definition]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'DefinitionResult' = DefinitionResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'DefinitionParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'DefinitionListResult' = DefinitionListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class DefinitionResult:
    def __init__(self: 'DefinitionResult'):
        self.value: Definition = None
        self.result: bool = False

    def SetValue(self: 'DefinitionResult',new_value: 'Definition') -> 'None':
        self.value = new_value

    def GetValue(self: 'DefinitionResult') -> 'Definition':
        return self.value

    def SetResult(self: 'DefinitionResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'DefinitionResult') -> 'bool':
        return self.result

class DefinitionListResult:
    def __init__(self: 'DefinitionListResult'):
        self.value: list[Definition] = []
        self.result: bool = False

    def SetValue(self: 'DefinitionListResult',new_value: 'list[Definition]') -> 'None':
        self.value = new_value

    def GetValue(self: 'DefinitionListResult') -> 'list[Definition]':
        return self.value

    def SetResult(self: 'DefinitionListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'DefinitionListResult') -> 'bool':
        return self.result

class Definition:
    def __init__(self: 'Definition'):
        self.length_string: LengthString = None
        self.class_def_field: ClassDef = None
        self.interface_def_field: InterfaceDef = None

    def SetLengthString(self: 'Definition',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'Definition') -> 'str':
        return self.length_string.GetString()

    def SetClassDef(self: 'Definition',input_value: 'ClassDef') -> 'None':
        self.class_def_field = input_value

    def GetClassDef(self: 'Definition') -> 'ClassDef':
        return self.class_def_field

    def SetInterfaceDef(self: 'Definition',input_value: 'InterfaceDef') -> 'None':
        self.interface_def_field = input_value

    def GetInterfaceDef(self: 'Definition') -> 'InterfaceDef':
        return self.interface_def_field

class InterfaceDefParser:
    def __init__(self: 'InterfaceDefParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'InterfaceDefParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'InterfaceDefParser',index: 'LengthString',result: 'InterfaceDefResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'InterfaceDef' = InterfaceDef()
        comment_field: 'CommentResult' = CommentResult()
        declarations_field: 'ContentDeclarationListResult' = ContentDeclarationListResult()
        name_field: 'NameResult' = NameResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and comment_parser_instance.ParseOptionalSave(index,comment_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,"interface") and whitespace_parser_instance.ParseMany(index,1,-1) and name_parser_instance.ParseSingleSave(index,name_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,"{") and whitespace_parser_instance.ParseMany(index,0,-1) and content_declaration_parser_instance.ParseManySave(index,declarations_field,0,-1) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,"}") and whitespace_parser_instance.ParseMany(index,0,-1):
            instance.SetComment(comment_field.GetValue())
            instance.SetDeclarations(declarations_field.GetValue())
            instance.SetName(name_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            comment_field = CommentResult()
            declarations_field = ContentDeclarationListResult()
            name_field = NameResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'InterfaceDefParser',index: 'LengthString') -> 'bool':
        result: 'InterfaceDefResult' = InterfaceDefResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'InterfaceDefParser',index: 'LengthString',result: 'InterfaceDefResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'InterfaceDefParser',index: 'LengthString') -> 'bool':
        result: 'InterfaceDefResult' = InterfaceDefResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'InterfaceDefParser',index: 'LengthString',list_result: 'InterfaceDefListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[InterfaceDef]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'InterfaceDefResult' = InterfaceDefResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'InterfaceDefParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'InterfaceDefListResult' = InterfaceDefListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class InterfaceDefResult:
    def __init__(self: 'InterfaceDefResult'):
        self.value: InterfaceDef = None
        self.result: bool = False

    def SetValue(self: 'InterfaceDefResult',new_value: 'InterfaceDef') -> 'None':
        self.value = new_value

    def GetValue(self: 'InterfaceDefResult') -> 'InterfaceDef':
        return self.value

    def SetResult(self: 'InterfaceDefResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'InterfaceDefResult') -> 'bool':
        return self.result

class InterfaceDefListResult:
    def __init__(self: 'InterfaceDefListResult'):
        self.value: list[InterfaceDef] = []
        self.result: bool = False

    def SetValue(self: 'InterfaceDefListResult',new_value: 'list[InterfaceDef]') -> 'None':
        self.value = new_value

    def GetValue(self: 'InterfaceDefListResult') -> 'list[InterfaceDef]':
        return self.value

    def SetResult(self: 'InterfaceDefListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'InterfaceDefListResult') -> 'bool':
        return self.result

class InterfaceDef:
    def __init__(self: 'InterfaceDef'):
        self.length_string: LengthString = None
        self.comment_field: Comment = None
        self.declarations_field: list[ContentDeclaration] = []
        self.name_field: Name = None

    def SetLengthString(self: 'InterfaceDef',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'InterfaceDef') -> 'str':
        return self.length_string.GetString()

    def SetComment(self: 'InterfaceDef',input_value: 'Comment') -> 'None':
        self.comment_field = input_value

    def GetComment(self: 'InterfaceDef') -> 'Comment':
        return self.comment_field

    def SetDeclarations(self: 'InterfaceDef',input_value: 'list[ContentDeclaration]') -> 'None':
        self.declarations_field = input_value

    def GetDeclarations(self: 'InterfaceDef') -> 'list[ContentDeclaration]':
        return self.declarations_field

    def SetName(self: 'InterfaceDef',input_value: 'Name') -> 'None':
        self.name_field = input_value

    def GetName(self: 'InterfaceDef') -> 'Name':
        return self.name_field

class ClassDefParser:
    def __init__(self: 'ClassDefParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'ClassDefParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'ClassDefParser',index: 'LengthString',result: 'ClassDefResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'ClassDef' = ClassDef()
        comment_field: 'CommentResult' = CommentResult()
        definitions_field: 'ContentDefinitionListResult' = ContentDefinitionListResult()
        implementing_field: 'ImplementationSpecResult' = ImplementationSpecResult()
        name_field: 'NameResult' = NameResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and comment_parser_instance.ParseOptionalSave(index,comment_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,"class") and whitespace_parser_instance.ParseMany(index,1,-1) and name_parser_instance.ParseSingleSave(index,name_field) and implementation_spec_parser_instance.ParseOptionalSave(index,implementing_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,"{") and whitespace_parser_instance.ParseMany(index,0,-1) and content_definition_parser_instance.ParseManySave(index,definitions_field,0,-1) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,"}") and whitespace_parser_instance.ParseMany(index,0,-1):
            instance.SetComment(comment_field.GetValue())
            instance.SetDefinitions(definitions_field.GetValue())
            instance.SetImplementing(implementing_field.GetValue())
            instance.SetName(name_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            comment_field = CommentResult()
            definitions_field = ContentDefinitionListResult()
            implementing_field = ImplementationSpecResult()
            name_field = NameResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'ClassDefParser',index: 'LengthString') -> 'bool':
        result: 'ClassDefResult' = ClassDefResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'ClassDefParser',index: 'LengthString',result: 'ClassDefResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'ClassDefParser',index: 'LengthString') -> 'bool':
        result: 'ClassDefResult' = ClassDefResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'ClassDefParser',index: 'LengthString',list_result: 'ClassDefListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[ClassDef]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'ClassDefResult' = ClassDefResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'ClassDefParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'ClassDefListResult' = ClassDefListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class ClassDefResult:
    def __init__(self: 'ClassDefResult'):
        self.value: ClassDef = None
        self.result: bool = False

    def SetValue(self: 'ClassDefResult',new_value: 'ClassDef') -> 'None':
        self.value = new_value

    def GetValue(self: 'ClassDefResult') -> 'ClassDef':
        return self.value

    def SetResult(self: 'ClassDefResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'ClassDefResult') -> 'bool':
        return self.result

class ClassDefListResult:
    def __init__(self: 'ClassDefListResult'):
        self.value: list[ClassDef] = []
        self.result: bool = False

    def SetValue(self: 'ClassDefListResult',new_value: 'list[ClassDef]') -> 'None':
        self.value = new_value

    def GetValue(self: 'ClassDefListResult') -> 'list[ClassDef]':
        return self.value

    def SetResult(self: 'ClassDefListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'ClassDefListResult') -> 'bool':
        return self.result

class ClassDef:
    def __init__(self: 'ClassDef'):
        self.length_string: LengthString = None
        self.comment_field: Comment = None
        self.definitions_field: list[ContentDefinition] = []
        self.implementing_field: ImplementationSpec = None
        self.name_field: Name = None

    def SetLengthString(self: 'ClassDef',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'ClassDef') -> 'str':
        return self.length_string.GetString()

    def SetComment(self: 'ClassDef',input_value: 'Comment') -> 'None':
        self.comment_field = input_value

    def GetComment(self: 'ClassDef') -> 'Comment':
        return self.comment_field

    def SetDefinitions(self: 'ClassDef',input_value: 'list[ContentDefinition]') -> 'None':
        self.definitions_field = input_value

    def GetDefinitions(self: 'ClassDef') -> 'list[ContentDefinition]':
        return self.definitions_field

    def SetImplementing(self: 'ClassDef',input_value: 'ImplementationSpec') -> 'None':
        self.implementing_field = input_value

    def GetImplementing(self: 'ClassDef') -> 'ImplementationSpec':
        return self.implementing_field

    def SetName(self: 'ClassDef',input_value: 'Name') -> 'None':
        self.name_field = input_value

    def GetName(self: 'ClassDef') -> 'Name':
        return self.name_field

class ImplementationSpecParser:
    def __init__(self: 'ImplementationSpecParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'ImplementationSpecParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'ImplementationSpecParser',index: 'LengthString',result: 'ImplementationSpecResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'ImplementationSpec' = ImplementationSpec()
        interface_field: 'QualfiedNameResult' = QualfiedNameResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and whitespace_parser_instance.ParseMany(index,1,-1) and string_parser_instance.ParseSingle(index,"implements") and whitespace_parser_instance.ParseMany(index,1,-1) and qualfied_name_parser_instance.ParseSingleSave(index,interface_field) and whitespace_parser_instance.ParseMany(index,0,-1):
            instance.SetInterface(interface_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            interface_field = QualfiedNameResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'ImplementationSpecParser',index: 'LengthString') -> 'bool':
        result: 'ImplementationSpecResult' = ImplementationSpecResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'ImplementationSpecParser',index: 'LengthString',result: 'ImplementationSpecResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'ImplementationSpecParser',index: 'LengthString') -> 'bool':
        result: 'ImplementationSpecResult' = ImplementationSpecResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'ImplementationSpecParser',index: 'LengthString',list_result: 'ImplementationSpecListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[ImplementationSpec]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'ImplementationSpecResult' = ImplementationSpecResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'ImplementationSpecParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'ImplementationSpecListResult' = ImplementationSpecListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class ImplementationSpecResult:
    def __init__(self: 'ImplementationSpecResult'):
        self.value: ImplementationSpec = None
        self.result: bool = False

    def SetValue(self: 'ImplementationSpecResult',new_value: 'ImplementationSpec') -> 'None':
        self.value = new_value

    def GetValue(self: 'ImplementationSpecResult') -> 'ImplementationSpec':
        return self.value

    def SetResult(self: 'ImplementationSpecResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'ImplementationSpecResult') -> 'bool':
        return self.result

class ImplementationSpecListResult:
    def __init__(self: 'ImplementationSpecListResult'):
        self.value: list[ImplementationSpec] = []
        self.result: bool = False

    def SetValue(self: 'ImplementationSpecListResult',new_value: 'list[ImplementationSpec]') -> 'None':
        self.value = new_value

    def GetValue(self: 'ImplementationSpecListResult') -> 'list[ImplementationSpec]':
        return self.value

    def SetResult(self: 'ImplementationSpecListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'ImplementationSpecListResult') -> 'bool':
        return self.result

class ImplementationSpec:
    def __init__(self: 'ImplementationSpec'):
        self.length_string: LengthString = None
        self.interface_field: QualfiedName = None

    def SetLengthString(self: 'ImplementationSpec',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'ImplementationSpec') -> 'str':
        return self.length_string.GetString()

    def SetInterface(self: 'ImplementationSpec',input_value: 'QualfiedName') -> 'None':
        self.interface_field = input_value

    def GetInterface(self: 'ImplementationSpec') -> 'QualfiedName':
        return self.interface_field

class ContentDeclarationParser:
    def __init__(self: 'ContentDeclarationParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'ContentDeclarationParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'ContentDeclarationParser',index: 'LengthString',result: 'ContentDeclarationResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'ContentDeclaration' = ContentDeclaration()
        comment_field: 'CommentResult' = CommentResult()
        name_field: 'NameResult' = NameResult()
        parameters_field: 'ParameterListDefResult' = ParameterListDefResult()
        type_field: 'ValueTypeResult' = ValueTypeResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and comment_parser_instance.ParseOptionalSave(index,comment_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,"function") and whitespace_parser_instance.ParseMany(index,1,-1) and value_type_parser_instance.ParseSingleSave(index,type_field) and whitespace_parser_instance.ParseMany(index,1,-1) and name_parser_instance.ParseSingleSave(index,name_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,"(") and whitespace_parser_instance.ParseMany(index,0,-1) and parameter_list_def_parser_instance.ParseOptionalSave(index,parameters_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,")") and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,";") and whitespace_parser_instance.ParseMany(index,0,-1):
            instance.SetComment(comment_field.GetValue())
            instance.SetName(name_field.GetValue())
            instance.SetParameters(parameters_field.GetValue())
            instance.SetType(type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            comment_field = CommentResult()
            name_field = NameResult()
            parameters_field = ParameterListDefResult()
            type_field = ValueTypeResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'ContentDeclarationParser',index: 'LengthString') -> 'bool':
        result: 'ContentDeclarationResult' = ContentDeclarationResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'ContentDeclarationParser',index: 'LengthString',result: 'ContentDeclarationResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'ContentDeclarationParser',index: 'LengthString') -> 'bool':
        result: 'ContentDeclarationResult' = ContentDeclarationResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'ContentDeclarationParser',index: 'LengthString',list_result: 'ContentDeclarationListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[ContentDeclaration]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'ContentDeclarationResult' = ContentDeclarationResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'ContentDeclarationParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'ContentDeclarationListResult' = ContentDeclarationListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class ContentDeclarationResult:
    def __init__(self: 'ContentDeclarationResult'):
        self.value: ContentDeclaration = None
        self.result: bool = False

    def SetValue(self: 'ContentDeclarationResult',new_value: 'ContentDeclaration') -> 'None':
        self.value = new_value

    def GetValue(self: 'ContentDeclarationResult') -> 'ContentDeclaration':
        return self.value

    def SetResult(self: 'ContentDeclarationResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'ContentDeclarationResult') -> 'bool':
        return self.result

class ContentDeclarationListResult:
    def __init__(self: 'ContentDeclarationListResult'):
        self.value: list[ContentDeclaration] = []
        self.result: bool = False

    def SetValue(self: 'ContentDeclarationListResult',new_value: 'list[ContentDeclaration]') -> 'None':
        self.value = new_value

    def GetValue(self: 'ContentDeclarationListResult') -> 'list[ContentDeclaration]':
        return self.value

    def SetResult(self: 'ContentDeclarationListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'ContentDeclarationListResult') -> 'bool':
        return self.result

class ContentDeclaration:
    def __init__(self: 'ContentDeclaration'):
        self.length_string: LengthString = None
        self.comment_field: Comment = None
        self.name_field: Name = None
        self.parameters_field: ParameterListDef = None
        self.type_field: ValueType = None

    def SetLengthString(self: 'ContentDeclaration',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'ContentDeclaration') -> 'str':
        return self.length_string.GetString()

    def SetComment(self: 'ContentDeclaration',input_value: 'Comment') -> 'None':
        self.comment_field = input_value

    def GetComment(self: 'ContentDeclaration') -> 'Comment':
        return self.comment_field

    def SetName(self: 'ContentDeclaration',input_value: 'Name') -> 'None':
        self.name_field = input_value

    def GetName(self: 'ContentDeclaration') -> 'Name':
        return self.name_field

    def SetParameters(self: 'ContentDeclaration',input_value: 'ParameterListDef') -> 'None':
        self.parameters_field = input_value

    def GetParameters(self: 'ContentDeclaration') -> 'ParameterListDef':
        return self.parameters_field

    def SetType(self: 'ContentDeclaration',input_value: 'ValueType') -> 'None':
        self.type_field = input_value

    def GetType(self: 'ContentDeclaration') -> 'ValueType':
        return self.type_field

class ContentDefinitionParser:
    def __init__(self: 'ContentDefinitionParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'ContentDefinitionParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'ContentDefinitionParser',index: 'LengthString',result: 'ContentDefinitionResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'ContentDefinition' = ContentDefinition()
        comment_field: 'CommentResult' = CommentResult()
        function_body_field: 'CodeBlockResult' = CodeBlockResult()
        name_field: 'NameResult' = NameResult()
        parameters_field: 'ParameterListDefResult' = ParameterListDefResult()
        type_field: 'ValueTypeResult' = ValueTypeResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and comment_parser_instance.ParseOptionalSave(index,comment_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,"function") and whitespace_parser_instance.ParseMany(index,1,-1) and value_type_parser_instance.ParseSingleSave(index,type_field) and whitespace_parser_instance.ParseMany(index,1,-1) and name_parser_instance.ParseSingleSave(index,name_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,"(") and whitespace_parser_instance.ParseMany(index,0,-1) and parameter_list_def_parser_instance.ParseOptionalSave(index,parameters_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,")") and whitespace_parser_instance.ParseMany(index,0,-1) and code_block_parser_instance.ParseSingleSave(index,function_body_field) and whitespace_parser_instance.ParseMany(index,0,-1):
            instance.SetComment(comment_field.GetValue())
            instance.SetFunctionBody(function_body_field.GetValue())
            instance.SetName(name_field.GetValue())
            instance.SetParameters(parameters_field.GetValue())
            instance.SetType(type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            comment_field = CommentResult()
            function_body_field = CodeBlockResult()
            name_field = NameResult()
            parameters_field = ParameterListDefResult()
            type_field = ValueTypeResult()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and comment_parser_instance.ParseOptionalSave(index,comment_field) and whitespace_parser_instance.ParseMany(index,0,-1) and value_type_parser_instance.ParseSingleSave(index,type_field) and whitespace_parser_instance.ParseMany(index,1,-1) and name_parser_instance.ParseSingleSave(index,name_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,";") and whitespace_parser_instance.ParseMany(index,0,-1):
            instance.SetComment(comment_field.GetValue())
            instance.SetFunctionBody(function_body_field.GetValue())
            instance.SetName(name_field.GetValue())
            instance.SetParameters(parameters_field.GetValue())
            instance.SetType(type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            comment_field = CommentResult()
            function_body_field = CodeBlockResult()
            name_field = NameResult()
            parameters_field = ParameterListDefResult()
            type_field = ValueTypeResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'ContentDefinitionParser',index: 'LengthString') -> 'bool':
        result: 'ContentDefinitionResult' = ContentDefinitionResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'ContentDefinitionParser',index: 'LengthString',result: 'ContentDefinitionResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'ContentDefinitionParser',index: 'LengthString') -> 'bool':
        result: 'ContentDefinitionResult' = ContentDefinitionResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'ContentDefinitionParser',index: 'LengthString',list_result: 'ContentDefinitionListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[ContentDefinition]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'ContentDefinitionResult' = ContentDefinitionResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'ContentDefinitionParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'ContentDefinitionListResult' = ContentDefinitionListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class ContentDefinitionResult:
    def __init__(self: 'ContentDefinitionResult'):
        self.value: ContentDefinition = None
        self.result: bool = False

    def SetValue(self: 'ContentDefinitionResult',new_value: 'ContentDefinition') -> 'None':
        self.value = new_value

    def GetValue(self: 'ContentDefinitionResult') -> 'ContentDefinition':
        return self.value

    def SetResult(self: 'ContentDefinitionResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'ContentDefinitionResult') -> 'bool':
        return self.result

class ContentDefinitionListResult:
    def __init__(self: 'ContentDefinitionListResult'):
        self.value: list[ContentDefinition] = []
        self.result: bool = False

    def SetValue(self: 'ContentDefinitionListResult',new_value: 'list[ContentDefinition]') -> 'None':
        self.value = new_value

    def GetValue(self: 'ContentDefinitionListResult') -> 'list[ContentDefinition]':
        return self.value

    def SetResult(self: 'ContentDefinitionListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'ContentDefinitionListResult') -> 'bool':
        return self.result

class ContentDefinition:
    def __init__(self: 'ContentDefinition'):
        self.length_string: LengthString = None
        self.comment_field: Comment = None
        self.function_body_field: CodeBlock = None
        self.name_field: Name = None
        self.parameters_field: ParameterListDef = None
        self.type_field: ValueType = None

    def SetLengthString(self: 'ContentDefinition',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'ContentDefinition') -> 'str':
        return self.length_string.GetString()

    def SetComment(self: 'ContentDefinition',input_value: 'Comment') -> 'None':
        self.comment_field = input_value

    def GetComment(self: 'ContentDefinition') -> 'Comment':
        return self.comment_field

    def SetFunctionBody(self: 'ContentDefinition',input_value: 'CodeBlock') -> 'None':
        self.function_body_field = input_value

    def GetFunctionBody(self: 'ContentDefinition') -> 'CodeBlock':
        return self.function_body_field

    def SetName(self: 'ContentDefinition',input_value: 'Name') -> 'None':
        self.name_field = input_value

    def GetName(self: 'ContentDefinition') -> 'Name':
        return self.name_field

    def SetParameters(self: 'ContentDefinition',input_value: 'ParameterListDef') -> 'None':
        self.parameters_field = input_value

    def GetParameters(self: 'ContentDefinition') -> 'ParameterListDef':
        return self.parameters_field

    def SetType(self: 'ContentDefinition',input_value: 'ValueType') -> 'None':
        self.type_field = input_value

    def GetType(self: 'ContentDefinition') -> 'ValueType':
        return self.type_field

class PrimativeTypeParser:
    def __init__(self: 'PrimativeTypeParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'PrimativeTypeParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'PrimativeTypeParser',index: 'LengthString',result: 'PrimativeTypeResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'PrimativeType' = PrimativeType()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and string_parser_instance.ParseSingle(index,"int"):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        if True and string_parser_instance.ParseSingle(index,"string"):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        if True and string_parser_instance.ParseSingle(index,"bool"):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        if True and string_parser_instance.ParseSingle(index,"float"):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        if True and string_parser_instance.ParseSingle(index,"void"):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'PrimativeTypeParser',index: 'LengthString') -> 'bool':
        result: 'PrimativeTypeResult' = PrimativeTypeResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'PrimativeTypeParser',index: 'LengthString',result: 'PrimativeTypeResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'PrimativeTypeParser',index: 'LengthString') -> 'bool':
        result: 'PrimativeTypeResult' = PrimativeTypeResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'PrimativeTypeParser',index: 'LengthString',list_result: 'PrimativeTypeListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[PrimativeType]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'PrimativeTypeResult' = PrimativeTypeResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'PrimativeTypeParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'PrimativeTypeListResult' = PrimativeTypeListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class PrimativeTypeResult:
    def __init__(self: 'PrimativeTypeResult'):
        self.value: PrimativeType = None
        self.result: bool = False

    def SetValue(self: 'PrimativeTypeResult',new_value: 'PrimativeType') -> 'None':
        self.value = new_value

    def GetValue(self: 'PrimativeTypeResult') -> 'PrimativeType':
        return self.value

    def SetResult(self: 'PrimativeTypeResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'PrimativeTypeResult') -> 'bool':
        return self.result

class PrimativeTypeListResult:
    def __init__(self: 'PrimativeTypeListResult'):
        self.value: list[PrimativeType] = []
        self.result: bool = False

    def SetValue(self: 'PrimativeTypeListResult',new_value: 'list[PrimativeType]') -> 'None':
        self.value = new_value

    def GetValue(self: 'PrimativeTypeListResult') -> 'list[PrimativeType]':
        return self.value

    def SetResult(self: 'PrimativeTypeListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'PrimativeTypeListResult') -> 'bool':
        return self.result

class PrimativeType:
    def __init__(self: 'PrimativeType'):
        self.length_string: LengthString = None

    def SetLengthString(self: 'PrimativeType',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'PrimativeType') -> 'str':
        return self.length_string.GetString()

class DefinedTypeParser:
    def __init__(self: 'DefinedTypeParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'DefinedTypeParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'DefinedTypeParser',index: 'LengthString',result: 'DefinedTypeResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'DefinedType' = DefinedType()
        name_field: 'QualfiedNameResult' = QualfiedNameResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and qualfied_name_parser_instance.ParseSingleSave(index,name_field):
            instance.SetName(name_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            name_field = QualfiedNameResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'DefinedTypeParser',index: 'LengthString') -> 'bool':
        result: 'DefinedTypeResult' = DefinedTypeResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'DefinedTypeParser',index: 'LengthString',result: 'DefinedTypeResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'DefinedTypeParser',index: 'LengthString') -> 'bool':
        result: 'DefinedTypeResult' = DefinedTypeResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'DefinedTypeParser',index: 'LengthString',list_result: 'DefinedTypeListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[DefinedType]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'DefinedTypeResult' = DefinedTypeResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'DefinedTypeParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'DefinedTypeListResult' = DefinedTypeListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class DefinedTypeResult:
    def __init__(self: 'DefinedTypeResult'):
        self.value: DefinedType = None
        self.result: bool = False

    def SetValue(self: 'DefinedTypeResult',new_value: 'DefinedType') -> 'None':
        self.value = new_value

    def GetValue(self: 'DefinedTypeResult') -> 'DefinedType':
        return self.value

    def SetResult(self: 'DefinedTypeResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'DefinedTypeResult') -> 'bool':
        return self.result

class DefinedTypeListResult:
    def __init__(self: 'DefinedTypeListResult'):
        self.value: list[DefinedType] = []
        self.result: bool = False

    def SetValue(self: 'DefinedTypeListResult',new_value: 'list[DefinedType]') -> 'None':
        self.value = new_value

    def GetValue(self: 'DefinedTypeListResult') -> 'list[DefinedType]':
        return self.value

    def SetResult(self: 'DefinedTypeListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'DefinedTypeListResult') -> 'bool':
        return self.result

class DefinedType:
    def __init__(self: 'DefinedType'):
        self.length_string: LengthString = None
        self.name_field: QualfiedName = None

    def SetLengthString(self: 'DefinedType',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'DefinedType') -> 'str':
        return self.length_string.GetString()

    def SetName(self: 'DefinedType',input_value: 'QualfiedName') -> 'None':
        self.name_field = input_value

    def GetName(self: 'DefinedType') -> 'QualfiedName':
        return self.name_field

class SingletonTypeParser:
    def __init__(self: 'SingletonTypeParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'SingletonTypeParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'SingletonTypeParser',index: 'LengthString',result: 'SingletonTypeResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'SingletonType' = SingletonType()
        defined_type_field: 'DefinedTypeResult' = DefinedTypeResult()
        primative_type_field: 'PrimativeTypeResult' = PrimativeTypeResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and primative_type_parser_instance.ParseSingleSave(index,primative_type_field):
            instance.SetDefinedType(defined_type_field.GetValue())
            instance.SetPrimativeType(primative_type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            defined_type_field = DefinedTypeResult()
            primative_type_field = PrimativeTypeResult()
        if True and defined_type_parser_instance.ParseSingleSave(index,defined_type_field):
            instance.SetDefinedType(defined_type_field.GetValue())
            instance.SetPrimativeType(primative_type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            defined_type_field = DefinedTypeResult()
            primative_type_field = PrimativeTypeResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'SingletonTypeParser',index: 'LengthString') -> 'bool':
        result: 'SingletonTypeResult' = SingletonTypeResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'SingletonTypeParser',index: 'LengthString',result: 'SingletonTypeResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'SingletonTypeParser',index: 'LengthString') -> 'bool':
        result: 'SingletonTypeResult' = SingletonTypeResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'SingletonTypeParser',index: 'LengthString',list_result: 'SingletonTypeListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[SingletonType]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'SingletonTypeResult' = SingletonTypeResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'SingletonTypeParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'SingletonTypeListResult' = SingletonTypeListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class SingletonTypeResult:
    def __init__(self: 'SingletonTypeResult'):
        self.value: SingletonType = None
        self.result: bool = False

    def SetValue(self: 'SingletonTypeResult',new_value: 'SingletonType') -> 'None':
        self.value = new_value

    def GetValue(self: 'SingletonTypeResult') -> 'SingletonType':
        return self.value

    def SetResult(self: 'SingletonTypeResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'SingletonTypeResult') -> 'bool':
        return self.result

class SingletonTypeListResult:
    def __init__(self: 'SingletonTypeListResult'):
        self.value: list[SingletonType] = []
        self.result: bool = False

    def SetValue(self: 'SingletonTypeListResult',new_value: 'list[SingletonType]') -> 'None':
        self.value = new_value

    def GetValue(self: 'SingletonTypeListResult') -> 'list[SingletonType]':
        return self.value

    def SetResult(self: 'SingletonTypeListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'SingletonTypeListResult') -> 'bool':
        return self.result

class SingletonType:
    def __init__(self: 'SingletonType'):
        self.length_string: LengthString = None
        self.defined_type_field: DefinedType = None
        self.primative_type_field: PrimativeType = None

    def SetLengthString(self: 'SingletonType',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'SingletonType') -> 'str':
        return self.length_string.GetString()

    def SetDefinedType(self: 'SingletonType',input_value: 'DefinedType') -> 'None':
        self.defined_type_field = input_value

    def GetDefinedType(self: 'SingletonType') -> 'DefinedType':
        return self.defined_type_field

    def SetPrimativeType(self: 'SingletonType',input_value: 'PrimativeType') -> 'None':
        self.primative_type_field = input_value

    def GetPrimativeType(self: 'SingletonType') -> 'PrimativeType':
        return self.primative_type_field

class DimensionalNoteParser:
    def __init__(self: 'DimensionalNoteParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'DimensionalNoteParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'DimensionalNoteParser',index: 'LengthString',result: 'DimensionalNoteResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'DimensionalNote' = DimensionalNote()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,"[") and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,"]"):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'DimensionalNoteParser',index: 'LengthString') -> 'bool':
        result: 'DimensionalNoteResult' = DimensionalNoteResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'DimensionalNoteParser',index: 'LengthString',result: 'DimensionalNoteResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'DimensionalNoteParser',index: 'LengthString') -> 'bool':
        result: 'DimensionalNoteResult' = DimensionalNoteResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'DimensionalNoteParser',index: 'LengthString',list_result: 'DimensionalNoteListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[DimensionalNote]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'DimensionalNoteResult' = DimensionalNoteResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'DimensionalNoteParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'DimensionalNoteListResult' = DimensionalNoteListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class DimensionalNoteResult:
    def __init__(self: 'DimensionalNoteResult'):
        self.value: DimensionalNote = None
        self.result: bool = False

    def SetValue(self: 'DimensionalNoteResult',new_value: 'DimensionalNote') -> 'None':
        self.value = new_value

    def GetValue(self: 'DimensionalNoteResult') -> 'DimensionalNote':
        return self.value

    def SetResult(self: 'DimensionalNoteResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'DimensionalNoteResult') -> 'bool':
        return self.result

class DimensionalNoteListResult:
    def __init__(self: 'DimensionalNoteListResult'):
        self.value: list[DimensionalNote] = []
        self.result: bool = False

    def SetValue(self: 'DimensionalNoteListResult',new_value: 'list[DimensionalNote]') -> 'None':
        self.value = new_value

    def GetValue(self: 'DimensionalNoteListResult') -> 'list[DimensionalNote]':
        return self.value

    def SetResult(self: 'DimensionalNoteListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'DimensionalNoteListResult') -> 'bool':
        return self.result

class DimensionalNote:
    def __init__(self: 'DimensionalNote'):
        self.length_string: LengthString = None

    def SetLengthString(self: 'DimensionalNote',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'DimensionalNote') -> 'str':
        return self.length_string.GetString()

class DimensionalTypeParser:
    def __init__(self: 'DimensionalTypeParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'DimensionalTypeParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'DimensionalTypeParser',index: 'LengthString',result: 'DimensionalTypeResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'DimensionalType' = DimensionalType()
        dimensional_note_field: 'DimensionalNoteListResult' = DimensionalNoteListResult()
        singleton_type_field: 'SingletonTypeResult' = SingletonTypeResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and singleton_type_parser_instance.ParseSingleSave(index,singleton_type_field) and dimensional_note_parser_instance.ParseManySave(index,dimensional_note_field,1,-1):
            instance.SetDimensionalNote(dimensional_note_field.GetValue())
            instance.SetSingletonType(singleton_type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            dimensional_note_field = DimensionalNoteListResult()
            singleton_type_field = SingletonTypeResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'DimensionalTypeParser',index: 'LengthString') -> 'bool':
        result: 'DimensionalTypeResult' = DimensionalTypeResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'DimensionalTypeParser',index: 'LengthString',result: 'DimensionalTypeResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'DimensionalTypeParser',index: 'LengthString') -> 'bool':
        result: 'DimensionalTypeResult' = DimensionalTypeResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'DimensionalTypeParser',index: 'LengthString',list_result: 'DimensionalTypeListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[DimensionalType]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'DimensionalTypeResult' = DimensionalTypeResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'DimensionalTypeParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'DimensionalTypeListResult' = DimensionalTypeListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class DimensionalTypeResult:
    def __init__(self: 'DimensionalTypeResult'):
        self.value: DimensionalType = None
        self.result: bool = False

    def SetValue(self: 'DimensionalTypeResult',new_value: 'DimensionalType') -> 'None':
        self.value = new_value

    def GetValue(self: 'DimensionalTypeResult') -> 'DimensionalType':
        return self.value

    def SetResult(self: 'DimensionalTypeResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'DimensionalTypeResult') -> 'bool':
        return self.result

class DimensionalTypeListResult:
    def __init__(self: 'DimensionalTypeListResult'):
        self.value: list[DimensionalType] = []
        self.result: bool = False

    def SetValue(self: 'DimensionalTypeListResult',new_value: 'list[DimensionalType]') -> 'None':
        self.value = new_value

    def GetValue(self: 'DimensionalTypeListResult') -> 'list[DimensionalType]':
        return self.value

    def SetResult(self: 'DimensionalTypeListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'DimensionalTypeListResult') -> 'bool':
        return self.result

class DimensionalType:
    def __init__(self: 'DimensionalType'):
        self.length_string: LengthString = None
        self.dimensional_note_field: list[DimensionalNote] = []
        self.singleton_type_field: SingletonType = None

    def SetLengthString(self: 'DimensionalType',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'DimensionalType') -> 'str':
        return self.length_string.GetString()

    def SetDimensionalNote(self: 'DimensionalType',input_value: 'list[DimensionalNote]') -> 'None':
        self.dimensional_note_field = input_value

    def GetDimensionalNote(self: 'DimensionalType') -> 'list[DimensionalNote]':
        return self.dimensional_note_field

    def SetSingletonType(self: 'DimensionalType',input_value: 'SingletonType') -> 'None':
        self.singleton_type_field = input_value

    def GetSingletonType(self: 'DimensionalType') -> 'SingletonType':
        return self.singleton_type_field

class MapNoteParser:
    def __init__(self: 'MapNoteParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'MapNoteParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'MapNoteParser',index: 'LengthString',result: 'MapNoteResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'MapNote' = MapNote()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,"{") and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,"}"):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'MapNoteParser',index: 'LengthString') -> 'bool':
        result: 'MapNoteResult' = MapNoteResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'MapNoteParser',index: 'LengthString',result: 'MapNoteResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'MapNoteParser',index: 'LengthString') -> 'bool':
        result: 'MapNoteResult' = MapNoteResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'MapNoteParser',index: 'LengthString',list_result: 'MapNoteListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[MapNote]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'MapNoteResult' = MapNoteResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'MapNoteParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'MapNoteListResult' = MapNoteListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class MapNoteResult:
    def __init__(self: 'MapNoteResult'):
        self.value: MapNote = None
        self.result: bool = False

    def SetValue(self: 'MapNoteResult',new_value: 'MapNote') -> 'None':
        self.value = new_value

    def GetValue(self: 'MapNoteResult') -> 'MapNote':
        return self.value

    def SetResult(self: 'MapNoteResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'MapNoteResult') -> 'bool':
        return self.result

class MapNoteListResult:
    def __init__(self: 'MapNoteListResult'):
        self.value: list[MapNote] = []
        self.result: bool = False

    def SetValue(self: 'MapNoteListResult',new_value: 'list[MapNote]') -> 'None':
        self.value = new_value

    def GetValue(self: 'MapNoteListResult') -> 'list[MapNote]':
        return self.value

    def SetResult(self: 'MapNoteListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'MapNoteListResult') -> 'bool':
        return self.result

class MapNote:
    def __init__(self: 'MapNote'):
        self.length_string: LengthString = None

    def SetLengthString(self: 'MapNote',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'MapNote') -> 'str':
        return self.length_string.GetString()

class MapTypeParser:
    def __init__(self: 'MapTypeParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'MapTypeParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'MapTypeParser',index: 'LengthString',result: 'MapTypeResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'MapType' = MapType()
        map_note_field: 'MapNoteResult' = MapNoteResult()
        singleton_type_field: 'SingletonTypeResult' = SingletonTypeResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and singleton_type_parser_instance.ParseSingleSave(index,singleton_type_field) and map_note_parser_instance.ParseSingleSave(index,map_note_field):
            instance.SetMapNote(map_note_field.GetValue())
            instance.SetSingletonType(singleton_type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            map_note_field = MapNoteResult()
            singleton_type_field = SingletonTypeResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'MapTypeParser',index: 'LengthString') -> 'bool':
        result: 'MapTypeResult' = MapTypeResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'MapTypeParser',index: 'LengthString',result: 'MapTypeResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'MapTypeParser',index: 'LengthString') -> 'bool':
        result: 'MapTypeResult' = MapTypeResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'MapTypeParser',index: 'LengthString',list_result: 'MapTypeListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[MapType]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'MapTypeResult' = MapTypeResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'MapTypeParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'MapTypeListResult' = MapTypeListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class MapTypeResult:
    def __init__(self: 'MapTypeResult'):
        self.value: MapType = None
        self.result: bool = False

    def SetValue(self: 'MapTypeResult',new_value: 'MapType') -> 'None':
        self.value = new_value

    def GetValue(self: 'MapTypeResult') -> 'MapType':
        return self.value

    def SetResult(self: 'MapTypeResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'MapTypeResult') -> 'bool':
        return self.result

class MapTypeListResult:
    def __init__(self: 'MapTypeListResult'):
        self.value: list[MapType] = []
        self.result: bool = False

    def SetValue(self: 'MapTypeListResult',new_value: 'list[MapType]') -> 'None':
        self.value = new_value

    def GetValue(self: 'MapTypeListResult') -> 'list[MapType]':
        return self.value

    def SetResult(self: 'MapTypeListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'MapTypeListResult') -> 'bool':
        return self.result

class MapType:
    def __init__(self: 'MapType'):
        self.length_string: LengthString = None
        self.map_note_field: MapNote = None
        self.singleton_type_field: SingletonType = None

    def SetLengthString(self: 'MapType',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'MapType') -> 'str':
        return self.length_string.GetString()

    def SetMapNote(self: 'MapType',input_value: 'MapNote') -> 'None':
        self.map_note_field = input_value

    def GetMapNote(self: 'MapType') -> 'MapNote':
        return self.map_note_field

    def SetSingletonType(self: 'MapType',input_value: 'SingletonType') -> 'None':
        self.singleton_type_field = input_value

    def GetSingletonType(self: 'MapType') -> 'SingletonType':
        return self.singleton_type_field

class ValueTypeParser:
    def __init__(self: 'ValueTypeParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'ValueTypeParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'ValueTypeParser',index: 'LengthString',result: 'ValueTypeResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'ValueType' = ValueType()
        dimensional_type_field: 'DimensionalTypeResult' = DimensionalTypeResult()
        map_type_field: 'MapTypeResult' = MapTypeResult()
        singleton_type_field: 'SingletonTypeResult' = SingletonTypeResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and dimensional_type_parser_instance.ParseSingleSave(index,dimensional_type_field):
            instance.SetDimensionalType(dimensional_type_field.GetValue())
            instance.SetMapType(map_type_field.GetValue())
            instance.SetSingletonType(singleton_type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            dimensional_type_field = DimensionalTypeResult()
            map_type_field = MapTypeResult()
            singleton_type_field = SingletonTypeResult()
        if True and map_type_parser_instance.ParseSingleSave(index,map_type_field):
            instance.SetDimensionalType(dimensional_type_field.GetValue())
            instance.SetMapType(map_type_field.GetValue())
            instance.SetSingletonType(singleton_type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            dimensional_type_field = DimensionalTypeResult()
            map_type_field = MapTypeResult()
            singleton_type_field = SingletonTypeResult()
        if True and singleton_type_parser_instance.ParseSingleSave(index,singleton_type_field):
            instance.SetDimensionalType(dimensional_type_field.GetValue())
            instance.SetMapType(map_type_field.GetValue())
            instance.SetSingletonType(singleton_type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            dimensional_type_field = DimensionalTypeResult()
            map_type_field = MapTypeResult()
            singleton_type_field = SingletonTypeResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'ValueTypeParser',index: 'LengthString') -> 'bool':
        result: 'ValueTypeResult' = ValueTypeResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'ValueTypeParser',index: 'LengthString',result: 'ValueTypeResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'ValueTypeParser',index: 'LengthString') -> 'bool':
        result: 'ValueTypeResult' = ValueTypeResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'ValueTypeParser',index: 'LengthString',list_result: 'ValueTypeListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[ValueType]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'ValueTypeResult' = ValueTypeResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'ValueTypeParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'ValueTypeListResult' = ValueTypeListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class ValueTypeResult:
    def __init__(self: 'ValueTypeResult'):
        self.value: ValueType = None
        self.result: bool = False

    def SetValue(self: 'ValueTypeResult',new_value: 'ValueType') -> 'None':
        self.value = new_value

    def GetValue(self: 'ValueTypeResult') -> 'ValueType':
        return self.value

    def SetResult(self: 'ValueTypeResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'ValueTypeResult') -> 'bool':
        return self.result

class ValueTypeListResult:
    def __init__(self: 'ValueTypeListResult'):
        self.value: list[ValueType] = []
        self.result: bool = False

    def SetValue(self: 'ValueTypeListResult',new_value: 'list[ValueType]') -> 'None':
        self.value = new_value

    def GetValue(self: 'ValueTypeListResult') -> 'list[ValueType]':
        return self.value

    def SetResult(self: 'ValueTypeListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'ValueTypeListResult') -> 'bool':
        return self.result

class ValueType:
    def __init__(self: 'ValueType'):
        self.length_string: LengthString = None
        self.dimensional_type_field: DimensionalType = None
        self.map_type_field: MapType = None
        self.singleton_type_field: SingletonType = None

    def SetLengthString(self: 'ValueType',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'ValueType') -> 'str':
        return self.length_string.GetString()

    def SetDimensionalType(self: 'ValueType',input_value: 'DimensionalType') -> 'None':
        self.dimensional_type_field = input_value

    def GetDimensionalType(self: 'ValueType') -> 'DimensionalType':
        return self.dimensional_type_field

    def SetMapType(self: 'ValueType',input_value: 'MapType') -> 'None':
        self.map_type_field = input_value

    def GetMapType(self: 'ValueType') -> 'MapType':
        return self.map_type_field

    def SetSingletonType(self: 'ValueType',input_value: 'SingletonType') -> 'None':
        self.singleton_type_field = input_value

    def GetSingletonType(self: 'ValueType') -> 'SingletonType':
        return self.singleton_type_field

class ParameterListDefParser:
    def __init__(self: 'ParameterListDefParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'ParameterListDefParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'ParameterListDefParser',index: 'LengthString',result: 'ParameterListDefResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'ParameterListDef' = ParameterListDef()
        name_field: 'NameResult' = NameResult()
        parameter_tail_field: 'ParameterListDefResult' = ParameterListDefResult()
        type_field: 'ValueTypeResult' = ValueTypeResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and value_type_parser_instance.ParseSingleSave(index,type_field) and whitespace_parser_instance.ParseMany(index,1,-1) and name_parser_instance.ParseSingleSave(index,name_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,",") and whitespace_parser_instance.ParseMany(index,0,-1) and parameter_list_def_parser_instance.ParseSingleSave(index,parameter_tail_field):
            instance.SetName(name_field.GetValue())
            instance.SetParameterTail(parameter_tail_field.GetValue())
            instance.SetType(type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            name_field = NameResult()
            parameter_tail_field = ParameterListDefResult()
            type_field = ValueTypeResult()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and value_type_parser_instance.ParseSingleSave(index,type_field) and whitespace_parser_instance.ParseMany(index,1,-1) and name_parser_instance.ParseSingleSave(index,name_field) and whitespace_parser_instance.ParseMany(index,0,-1):
            instance.SetName(name_field.GetValue())
            instance.SetParameterTail(parameter_tail_field.GetValue())
            instance.SetType(type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            name_field = NameResult()
            parameter_tail_field = ParameterListDefResult()
            type_field = ValueTypeResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'ParameterListDefParser',index: 'LengthString') -> 'bool':
        result: 'ParameterListDefResult' = ParameterListDefResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'ParameterListDefParser',index: 'LengthString',result: 'ParameterListDefResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'ParameterListDefParser',index: 'LengthString') -> 'bool':
        result: 'ParameterListDefResult' = ParameterListDefResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'ParameterListDefParser',index: 'LengthString',list_result: 'ParameterListDefListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[ParameterListDef]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'ParameterListDefResult' = ParameterListDefResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'ParameterListDefParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'ParameterListDefListResult' = ParameterListDefListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class ParameterListDefResult:
    def __init__(self: 'ParameterListDefResult'):
        self.value: ParameterListDef = None
        self.result: bool = False

    def SetValue(self: 'ParameterListDefResult',new_value: 'ParameterListDef') -> 'None':
        self.value = new_value

    def GetValue(self: 'ParameterListDefResult') -> 'ParameterListDef':
        return self.value

    def SetResult(self: 'ParameterListDefResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'ParameterListDefResult') -> 'bool':
        return self.result

class ParameterListDefListResult:
    def __init__(self: 'ParameterListDefListResult'):
        self.value: list[ParameterListDef] = []
        self.result: bool = False

    def SetValue(self: 'ParameterListDefListResult',new_value: 'list[ParameterListDef]') -> 'None':
        self.value = new_value

    def GetValue(self: 'ParameterListDefListResult') -> 'list[ParameterListDef]':
        return self.value

    def SetResult(self: 'ParameterListDefListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'ParameterListDefListResult') -> 'bool':
        return self.result

class ParameterListDef:
    def __init__(self: 'ParameterListDef'):
        self.length_string: LengthString = None
        self.name_field: Name = None
        self.parameter_tail_field: ParameterListDef = None
        self.type_field: ValueType = None

    def SetLengthString(self: 'ParameterListDef',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'ParameterListDef') -> 'str':
        return self.length_string.GetString()

    def SetName(self: 'ParameterListDef',input_value: 'Name') -> 'None':
        self.name_field = input_value

    def GetName(self: 'ParameterListDef') -> 'Name':
        return self.name_field

    def SetParameterTail(self: 'ParameterListDef',input_value: 'ParameterListDef') -> 'None':
        self.parameter_tail_field = input_value

    def GetParameterTail(self: 'ParameterListDef') -> 'ParameterListDef':
        return self.parameter_tail_field

    def SetType(self: 'ParameterListDef',input_value: 'ValueType') -> 'None':
        self.type_field = input_value

    def GetType(self: 'ParameterListDef') -> 'ValueType':
        return self.type_field

class ParameterListParser:
    def __init__(self: 'ParameterListParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'ParameterListParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'ParameterListParser',index: 'LengthString',result: 'ParameterListResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'ParameterList' = ParameterList()
        parameter_tail_field: 'ParameterListResult' = ParameterListResult()
        r_value_field: 'RValueResult' = RValueResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and r_value_parser_instance.ParseSingleSave(index,r_value_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,",") and whitespace_parser_instance.ParseMany(index,0,-1) and parameter_list_parser_instance.ParseSingleSave(index,parameter_tail_field):
            instance.SetParameterTail(parameter_tail_field.GetValue())
            instance.SetRValue(r_value_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            parameter_tail_field = ParameterListResult()
            r_value_field = RValueResult()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and r_value_parser_instance.ParseSingleSave(index,r_value_field) and whitespace_parser_instance.ParseMany(index,0,-1):
            instance.SetParameterTail(parameter_tail_field.GetValue())
            instance.SetRValue(r_value_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            parameter_tail_field = ParameterListResult()
            r_value_field = RValueResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'ParameterListParser',index: 'LengthString') -> 'bool':
        result: 'ParameterListResult' = ParameterListResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'ParameterListParser',index: 'LengthString',result: 'ParameterListResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'ParameterListParser',index: 'LengthString') -> 'bool':
        result: 'ParameterListResult' = ParameterListResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'ParameterListParser',index: 'LengthString',list_result: 'ParameterListListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[ParameterList]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'ParameterListResult' = ParameterListResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'ParameterListParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'ParameterListListResult' = ParameterListListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class ParameterListResult:
    def __init__(self: 'ParameterListResult'):
        self.value: ParameterList = None
        self.result: bool = False

    def SetValue(self: 'ParameterListResult',new_value: 'ParameterList') -> 'None':
        self.value = new_value

    def GetValue(self: 'ParameterListResult') -> 'ParameterList':
        return self.value

    def SetResult(self: 'ParameterListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'ParameterListResult') -> 'bool':
        return self.result

class ParameterListListResult:
    def __init__(self: 'ParameterListListResult'):
        self.value: list[ParameterList] = []
        self.result: bool = False

    def SetValue(self: 'ParameterListListResult',new_value: 'list[ParameterList]') -> 'None':
        self.value = new_value

    def GetValue(self: 'ParameterListListResult') -> 'list[ParameterList]':
        return self.value

    def SetResult(self: 'ParameterListListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'ParameterListListResult') -> 'bool':
        return self.result

class ParameterList:
    def __init__(self: 'ParameterList'):
        self.length_string: LengthString = None
        self.parameter_tail_field: ParameterList = None
        self.r_value_field: RValue = None

    def SetLengthString(self: 'ParameterList',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'ParameterList') -> 'str':
        return self.length_string.GetString()

    def SetParameterTail(self: 'ParameterList',input_value: 'ParameterList') -> 'None':
        self.parameter_tail_field = input_value

    def GetParameterTail(self: 'ParameterList') -> 'ParameterList':
        return self.parameter_tail_field

    def SetRValue(self: 'ParameterList',input_value: 'RValue') -> 'None':
        self.r_value_field = input_value

    def GetRValue(self: 'ParameterList') -> 'RValue':
        return self.r_value_field

class CodeBlockParser:
    def __init__(self: 'CodeBlockParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'CodeBlockParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'CodeBlockParser',index: 'LengthString',result: 'CodeBlockResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'CodeBlock' = CodeBlock()
        instructions_field: 'InstructionListResult' = InstructionListResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,"{") and whitespace_parser_instance.ParseMany(index,0,-1) and instruction_parser_instance.ParseManySave(index,instructions_field,0,-1) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,"}") and whitespace_parser_instance.ParseMany(index,0,-1):
            instance.SetInstructions(instructions_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            instructions_field = InstructionListResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'CodeBlockParser',index: 'LengthString') -> 'bool':
        result: 'CodeBlockResult' = CodeBlockResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'CodeBlockParser',index: 'LengthString',result: 'CodeBlockResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'CodeBlockParser',index: 'LengthString') -> 'bool':
        result: 'CodeBlockResult' = CodeBlockResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'CodeBlockParser',index: 'LengthString',list_result: 'CodeBlockListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[CodeBlock]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'CodeBlockResult' = CodeBlockResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'CodeBlockParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'CodeBlockListResult' = CodeBlockListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class CodeBlockResult:
    def __init__(self: 'CodeBlockResult'):
        self.value: CodeBlock = None
        self.result: bool = False

    def SetValue(self: 'CodeBlockResult',new_value: 'CodeBlock') -> 'None':
        self.value = new_value

    def GetValue(self: 'CodeBlockResult') -> 'CodeBlock':
        return self.value

    def SetResult(self: 'CodeBlockResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'CodeBlockResult') -> 'bool':
        return self.result

class CodeBlockListResult:
    def __init__(self: 'CodeBlockListResult'):
        self.value: list[CodeBlock] = []
        self.result: bool = False

    def SetValue(self: 'CodeBlockListResult',new_value: 'list[CodeBlock]') -> 'None':
        self.value = new_value

    def GetValue(self: 'CodeBlockListResult') -> 'list[CodeBlock]':
        return self.value

    def SetResult(self: 'CodeBlockListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'CodeBlockListResult') -> 'bool':
        return self.result

class CodeBlock:
    def __init__(self: 'CodeBlock'):
        self.length_string: LengthString = None
        self.instructions_field: list[Instruction] = []

    def SetLengthString(self: 'CodeBlock',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'CodeBlock') -> 'str':
        return self.length_string.GetString()

    def SetInstructions(self: 'CodeBlock',input_value: 'list[Instruction]') -> 'None':
        self.instructions_field = input_value

    def GetInstructions(self: 'CodeBlock') -> 'list[Instruction]':
        return self.instructions_field

class DeclarationAssignParser:
    def __init__(self: 'DeclarationAssignParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'DeclarationAssignParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'DeclarationAssignParser',index: 'LengthString',result: 'DeclarationAssignResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'DeclarationAssign' = DeclarationAssign()
        r_value_field: 'RValueResult' = RValueResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,"=") and whitespace_parser_instance.ParseMany(index,0,-1) and r_value_parser_instance.ParseSingleSave(index,r_value_field) and whitespace_parser_instance.ParseMany(index,0,-1):
            instance.SetRValue(r_value_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            r_value_field = RValueResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'DeclarationAssignParser',index: 'LengthString') -> 'bool':
        result: 'DeclarationAssignResult' = DeclarationAssignResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'DeclarationAssignParser',index: 'LengthString',result: 'DeclarationAssignResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'DeclarationAssignParser',index: 'LengthString') -> 'bool':
        result: 'DeclarationAssignResult' = DeclarationAssignResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'DeclarationAssignParser',index: 'LengthString',list_result: 'DeclarationAssignListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[DeclarationAssign]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'DeclarationAssignResult' = DeclarationAssignResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'DeclarationAssignParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'DeclarationAssignListResult' = DeclarationAssignListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class DeclarationAssignResult:
    def __init__(self: 'DeclarationAssignResult'):
        self.value: DeclarationAssign = None
        self.result: bool = False

    def SetValue(self: 'DeclarationAssignResult',new_value: 'DeclarationAssign') -> 'None':
        self.value = new_value

    def GetValue(self: 'DeclarationAssignResult') -> 'DeclarationAssign':
        return self.value

    def SetResult(self: 'DeclarationAssignResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'DeclarationAssignResult') -> 'bool':
        return self.result

class DeclarationAssignListResult:
    def __init__(self: 'DeclarationAssignListResult'):
        self.value: list[DeclarationAssign] = []
        self.result: bool = False

    def SetValue(self: 'DeclarationAssignListResult',new_value: 'list[DeclarationAssign]') -> 'None':
        self.value = new_value

    def GetValue(self: 'DeclarationAssignListResult') -> 'list[DeclarationAssign]':
        return self.value

    def SetResult(self: 'DeclarationAssignListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'DeclarationAssignListResult') -> 'bool':
        return self.result

class DeclarationAssign:
    def __init__(self: 'DeclarationAssign'):
        self.length_string: LengthString = None
        self.r_value_field: RValue = None

    def SetLengthString(self: 'DeclarationAssign',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'DeclarationAssign') -> 'str':
        return self.length_string.GetString()

    def SetRValue(self: 'DeclarationAssign',input_value: 'RValue') -> 'None':
        self.r_value_field = input_value

    def GetRValue(self: 'DeclarationAssign') -> 'RValue':
        return self.r_value_field

class DeclarationParser:
    def __init__(self: 'DeclarationParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'DeclarationParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'DeclarationParser',index: 'LengthString',result: 'DeclarationResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'Declaration' = Declaration()
        assignment_field: 'DeclarationAssignResult' = DeclarationAssignResult()
        name_field: 'NameResult' = NameResult()
        type_field: 'ValueTypeResult' = ValueTypeResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and value_type_parser_instance.ParseSingleSave(index,type_field) and whitespace_parser_instance.ParseMany(index,1,-1) and name_parser_instance.ParseSingleSave(index,name_field) and whitespace_parser_instance.ParseMany(index,0,-1) and declaration_assign_parser_instance.ParseOptionalSave(index,assignment_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,";") and whitespace_parser_instance.ParseMany(index,0,-1):
            instance.SetAssignment(assignment_field.GetValue())
            instance.SetName(name_field.GetValue())
            instance.SetType(type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            assignment_field = DeclarationAssignResult()
            name_field = NameResult()
            type_field = ValueTypeResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'DeclarationParser',index: 'LengthString') -> 'bool':
        result: 'DeclarationResult' = DeclarationResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'DeclarationParser',index: 'LengthString',result: 'DeclarationResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'DeclarationParser',index: 'LengthString') -> 'bool':
        result: 'DeclarationResult' = DeclarationResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'DeclarationParser',index: 'LengthString',list_result: 'DeclarationListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[Declaration]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'DeclarationResult' = DeclarationResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'DeclarationParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'DeclarationListResult' = DeclarationListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class DeclarationResult:
    def __init__(self: 'DeclarationResult'):
        self.value: Declaration = None
        self.result: bool = False

    def SetValue(self: 'DeclarationResult',new_value: 'Declaration') -> 'None':
        self.value = new_value

    def GetValue(self: 'DeclarationResult') -> 'Declaration':
        return self.value

    def SetResult(self: 'DeclarationResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'DeclarationResult') -> 'bool':
        return self.result

class DeclarationListResult:
    def __init__(self: 'DeclarationListResult'):
        self.value: list[Declaration] = []
        self.result: bool = False

    def SetValue(self: 'DeclarationListResult',new_value: 'list[Declaration]') -> 'None':
        self.value = new_value

    def GetValue(self: 'DeclarationListResult') -> 'list[Declaration]':
        return self.value

    def SetResult(self: 'DeclarationListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'DeclarationListResult') -> 'bool':
        return self.result

class Declaration:
    def __init__(self: 'Declaration'):
        self.length_string: LengthString = None
        self.assignment_field: DeclarationAssign = None
        self.name_field: Name = None
        self.type_field: ValueType = None

    def SetLengthString(self: 'Declaration',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'Declaration') -> 'str':
        return self.length_string.GetString()

    def SetAssignment(self: 'Declaration',input_value: 'DeclarationAssign') -> 'None':
        self.assignment_field = input_value

    def GetAssignment(self: 'Declaration') -> 'DeclarationAssign':
        return self.assignment_field

    def SetName(self: 'Declaration',input_value: 'Name') -> 'None':
        self.name_field = input_value

    def GetName(self: 'Declaration') -> 'Name':
        return self.name_field

    def SetType(self: 'Declaration',input_value: 'ValueType') -> 'None':
        self.type_field = input_value

    def GetType(self: 'Declaration') -> 'ValueType':
        return self.type_field

class AssignmentParser:
    def __init__(self: 'AssignmentParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'AssignmentParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'AssignmentParser',index: 'LengthString',result: 'AssignmentResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'Assignment' = Assignment()
        l_value_field: 'QualfiedNameResult' = QualfiedNameResult()
        r_value_field: 'RValueResult' = RValueResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and qualfied_name_parser_instance.ParseSingleSave(index,l_value_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,"=") and whitespace_parser_instance.ParseMany(index,0,-1) and r_value_parser_instance.ParseSingleSave(index,r_value_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,";") and whitespace_parser_instance.ParseMany(index,0,-1):
            instance.SetLValue(l_value_field.GetValue())
            instance.SetRValue(r_value_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            l_value_field = QualfiedNameResult()
            r_value_field = RValueResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'AssignmentParser',index: 'LengthString') -> 'bool':
        result: 'AssignmentResult' = AssignmentResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'AssignmentParser',index: 'LengthString',result: 'AssignmentResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'AssignmentParser',index: 'LengthString') -> 'bool':
        result: 'AssignmentResult' = AssignmentResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'AssignmentParser',index: 'LengthString',list_result: 'AssignmentListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[Assignment]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'AssignmentResult' = AssignmentResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'AssignmentParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'AssignmentListResult' = AssignmentListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class AssignmentResult:
    def __init__(self: 'AssignmentResult'):
        self.value: Assignment = None
        self.result: bool = False

    def SetValue(self: 'AssignmentResult',new_value: 'Assignment') -> 'None':
        self.value = new_value

    def GetValue(self: 'AssignmentResult') -> 'Assignment':
        return self.value

    def SetResult(self: 'AssignmentResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'AssignmentResult') -> 'bool':
        return self.result

class AssignmentListResult:
    def __init__(self: 'AssignmentListResult'):
        self.value: list[Assignment] = []
        self.result: bool = False

    def SetValue(self: 'AssignmentListResult',new_value: 'list[Assignment]') -> 'None':
        self.value = new_value

    def GetValue(self: 'AssignmentListResult') -> 'list[Assignment]':
        return self.value

    def SetResult(self: 'AssignmentListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'AssignmentListResult') -> 'bool':
        return self.result

class Assignment:
    def __init__(self: 'Assignment'):
        self.length_string: LengthString = None
        self.l_value_field: QualfiedName = None
        self.r_value_field: RValue = None

    def SetLengthString(self: 'Assignment',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'Assignment') -> 'str':
        return self.length_string.GetString()

    def SetLValue(self: 'Assignment',input_value: 'QualfiedName') -> 'None':
        self.l_value_field = input_value

    def GetLValue(self: 'Assignment') -> 'QualfiedName':
        return self.l_value_field

    def SetRValue(self: 'Assignment',input_value: 'RValue') -> 'None':
        self.r_value_field = input_value

    def GetRValue(self: 'Assignment') -> 'RValue':
        return self.r_value_field

class ReturnParser:
    def __init__(self: 'ReturnParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'ReturnParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'ReturnParser',index: 'LengthString',result: 'ReturnResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'Return' = Return()
        r_value_field: 'RValueResult' = RValueResult()
        rtn_field: 'StringResult' = StringResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingleSave(index,"return",rtn_field) and whitespace_parser_instance.ParseMany(index,1,-1) and r_value_parser_instance.ParseSingleSave(index,r_value_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,";") and whitespace_parser_instance.ParseMany(index,0,-1):
            instance.SetRValue(r_value_field.GetValue())
            instance.SetRtn(rtn_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            r_value_field = RValueResult()
            rtn_field = StringResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'ReturnParser',index: 'LengthString') -> 'bool':
        result: 'ReturnResult' = ReturnResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'ReturnParser',index: 'LengthString',result: 'ReturnResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'ReturnParser',index: 'LengthString') -> 'bool':
        result: 'ReturnResult' = ReturnResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'ReturnParser',index: 'LengthString',list_result: 'ReturnListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[Return]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'ReturnResult' = ReturnResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'ReturnParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'ReturnListResult' = ReturnListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class ReturnResult:
    def __init__(self: 'ReturnResult'):
        self.value: Return = None
        self.result: bool = False

    def SetValue(self: 'ReturnResult',new_value: 'Return') -> 'None':
        self.value = new_value

    def GetValue(self: 'ReturnResult') -> 'Return':
        return self.value

    def SetResult(self: 'ReturnResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'ReturnResult') -> 'bool':
        return self.result

class ReturnListResult:
    def __init__(self: 'ReturnListResult'):
        self.value: list[Return] = []
        self.result: bool = False

    def SetValue(self: 'ReturnListResult',new_value: 'list[Return]') -> 'None':
        self.value = new_value

    def GetValue(self: 'ReturnListResult') -> 'list[Return]':
        return self.value

    def SetResult(self: 'ReturnListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'ReturnListResult') -> 'bool':
        return self.result

class Return:
    def __init__(self: 'Return'):
        self.length_string: LengthString = None
        self.r_value_field: RValue = None
        self.rtn_field: String = None

    def SetLengthString(self: 'Return',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'Return') -> 'str':
        return self.length_string.GetString()

    def SetRValue(self: 'Return',input_value: 'RValue') -> 'None':
        self.r_value_field = input_value

    def GetRValue(self: 'Return') -> 'RValue':
        return self.r_value_field

    def SetRtn(self: 'Return',input_value: 'String') -> 'None':
        self.rtn_field = input_value

    def GetRtn(self: 'Return') -> 'String':
        return self.rtn_field

class ElseTailParser:
    def __init__(self: 'ElseTailParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'ElseTailParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'ElseTailParser',index: 'LengthString',result: 'ElseTailResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'ElseTail' = ElseTail()
        code_block_field: 'CodeBlockResult' = CodeBlockResult()
        else_key_field: 'StringResult' = StringResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingleSave(index,"else",else_key_field) and whitespace_parser_instance.ParseMany(index,0,-1) and code_block_parser_instance.ParseSingleSave(index,code_block_field) and whitespace_parser_instance.ParseMany(index,0,-1):
            instance.SetCodeBlock(code_block_field.GetValue())
            instance.SetElseKey(else_key_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            code_block_field = CodeBlockResult()
            else_key_field = StringResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'ElseTailParser',index: 'LengthString') -> 'bool':
        result: 'ElseTailResult' = ElseTailResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'ElseTailParser',index: 'LengthString',result: 'ElseTailResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'ElseTailParser',index: 'LengthString') -> 'bool':
        result: 'ElseTailResult' = ElseTailResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'ElseTailParser',index: 'LengthString',list_result: 'ElseTailListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[ElseTail]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'ElseTailResult' = ElseTailResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'ElseTailParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'ElseTailListResult' = ElseTailListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class ElseTailResult:
    def __init__(self: 'ElseTailResult'):
        self.value: ElseTail = None
        self.result: bool = False

    def SetValue(self: 'ElseTailResult',new_value: 'ElseTail') -> 'None':
        self.value = new_value

    def GetValue(self: 'ElseTailResult') -> 'ElseTail':
        return self.value

    def SetResult(self: 'ElseTailResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'ElseTailResult') -> 'bool':
        return self.result

class ElseTailListResult:
    def __init__(self: 'ElseTailListResult'):
        self.value: list[ElseTail] = []
        self.result: bool = False

    def SetValue(self: 'ElseTailListResult',new_value: 'list[ElseTail]') -> 'None':
        self.value = new_value

    def GetValue(self: 'ElseTailListResult') -> 'list[ElseTail]':
        return self.value

    def SetResult(self: 'ElseTailListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'ElseTailListResult') -> 'bool':
        return self.result

class ElseTail:
    def __init__(self: 'ElseTail'):
        self.length_string: LengthString = None
        self.code_block_field: CodeBlock = None
        self.else_key_field: String = None

    def SetLengthString(self: 'ElseTail',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'ElseTail') -> 'str':
        return self.length_string.GetString()

    def SetCodeBlock(self: 'ElseTail',input_value: 'CodeBlock') -> 'None':
        self.code_block_field = input_value

    def GetCodeBlock(self: 'ElseTail') -> 'CodeBlock':
        return self.code_block_field

    def SetElseKey(self: 'ElseTail',input_value: 'String') -> 'None':
        self.else_key_field = input_value

    def GetElseKey(self: 'ElseTail') -> 'String':
        return self.else_key_field

class ConditionalParser:
    def __init__(self: 'ConditionalParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'ConditionalParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'ConditionalParser',index: 'LengthString',result: 'ConditionalResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'Conditional' = Conditional()
        code_block_field: 'CodeBlockResult' = CodeBlockResult()
        conditional_key_field: 'StringResult' = StringResult()
        else_tail_field: 'ElseTailResult' = ElseTailResult()
        r_value_field: 'RValueResult' = RValueResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingleSave(index,"if",conditional_key_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,"(") and whitespace_parser_instance.ParseMany(index,0,-1) and r_value_parser_instance.ParseSingleSave(index,r_value_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,")") and whitespace_parser_instance.ParseMany(index,0,-1) and code_block_parser_instance.ParseSingleSave(index,code_block_field) and whitespace_parser_instance.ParseMany(index,0,-1) and else_tail_parser_instance.ParseOptionalSave(index,else_tail_field):
            instance.SetCodeBlock(code_block_field.GetValue())
            instance.SetConditionalKey(conditional_key_field.GetValue())
            instance.SetElseTail(else_tail_field.GetValue())
            instance.SetRValue(r_value_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            code_block_field = CodeBlockResult()
            conditional_key_field = StringResult()
            else_tail_field = ElseTailResult()
            r_value_field = RValueResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'ConditionalParser',index: 'LengthString') -> 'bool':
        result: 'ConditionalResult' = ConditionalResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'ConditionalParser',index: 'LengthString',result: 'ConditionalResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'ConditionalParser',index: 'LengthString') -> 'bool':
        result: 'ConditionalResult' = ConditionalResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'ConditionalParser',index: 'LengthString',list_result: 'ConditionalListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[Conditional]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'ConditionalResult' = ConditionalResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'ConditionalParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'ConditionalListResult' = ConditionalListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class ConditionalResult:
    def __init__(self: 'ConditionalResult'):
        self.value: Conditional = None
        self.result: bool = False

    def SetValue(self: 'ConditionalResult',new_value: 'Conditional') -> 'None':
        self.value = new_value

    def GetValue(self: 'ConditionalResult') -> 'Conditional':
        return self.value

    def SetResult(self: 'ConditionalResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'ConditionalResult') -> 'bool':
        return self.result

class ConditionalListResult:
    def __init__(self: 'ConditionalListResult'):
        self.value: list[Conditional] = []
        self.result: bool = False

    def SetValue(self: 'ConditionalListResult',new_value: 'list[Conditional]') -> 'None':
        self.value = new_value

    def GetValue(self: 'ConditionalListResult') -> 'list[Conditional]':
        return self.value

    def SetResult(self: 'ConditionalListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'ConditionalListResult') -> 'bool':
        return self.result

class Conditional:
    def __init__(self: 'Conditional'):
        self.length_string: LengthString = None
        self.code_block_field: CodeBlock = None
        self.conditional_key_field: String = None
        self.else_tail_field: ElseTail = None
        self.r_value_field: RValue = None

    def SetLengthString(self: 'Conditional',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'Conditional') -> 'str':
        return self.length_string.GetString()

    def SetCodeBlock(self: 'Conditional',input_value: 'CodeBlock') -> 'None':
        self.code_block_field = input_value

    def GetCodeBlock(self: 'Conditional') -> 'CodeBlock':
        return self.code_block_field

    def SetConditionalKey(self: 'Conditional',input_value: 'String') -> 'None':
        self.conditional_key_field = input_value

    def GetConditionalKey(self: 'Conditional') -> 'String':
        return self.conditional_key_field

    def SetElseTail(self: 'Conditional',input_value: 'ElseTail') -> 'None':
        self.else_tail_field = input_value

    def GetElseTail(self: 'Conditional') -> 'ElseTail':
        return self.else_tail_field

    def SetRValue(self: 'Conditional',input_value: 'RValue') -> 'None':
        self.r_value_field = input_value

    def GetRValue(self: 'Conditional') -> 'RValue':
        return self.r_value_field

class LoopParser:
    def __init__(self: 'LoopParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'LoopParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'LoopParser',index: 'LengthString',result: 'LoopResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'Loop' = Loop()
        code_block_field: 'CodeBlockResult' = CodeBlockResult()
        loop_key_field: 'StringResult' = StringResult()
        r_value_field: 'RValueResult' = RValueResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingleSave(index,"while",loop_key_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,"(") and whitespace_parser_instance.ParseMany(index,0,-1) and r_value_parser_instance.ParseSingleSave(index,r_value_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,")") and whitespace_parser_instance.ParseMany(index,0,-1) and code_block_parser_instance.ParseSingleSave(index,code_block_field) and whitespace_parser_instance.ParseMany(index,0,-1):
            instance.SetCodeBlock(code_block_field.GetValue())
            instance.SetLoopKey(loop_key_field.GetValue())
            instance.SetRValue(r_value_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            code_block_field = CodeBlockResult()
            loop_key_field = StringResult()
            r_value_field = RValueResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'LoopParser',index: 'LengthString') -> 'bool':
        result: 'LoopResult' = LoopResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'LoopParser',index: 'LengthString',result: 'LoopResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'LoopParser',index: 'LengthString') -> 'bool':
        result: 'LoopResult' = LoopResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'LoopParser',index: 'LengthString',list_result: 'LoopListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[Loop]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'LoopResult' = LoopResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'LoopParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'LoopListResult' = LoopListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class LoopResult:
    def __init__(self: 'LoopResult'):
        self.value: Loop = None
        self.result: bool = False

    def SetValue(self: 'LoopResult',new_value: 'Loop') -> 'None':
        self.value = new_value

    def GetValue(self: 'LoopResult') -> 'Loop':
        return self.value

    def SetResult(self: 'LoopResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'LoopResult') -> 'bool':
        return self.result

class LoopListResult:
    def __init__(self: 'LoopListResult'):
        self.value: list[Loop] = []
        self.result: bool = False

    def SetValue(self: 'LoopListResult',new_value: 'list[Loop]') -> 'None':
        self.value = new_value

    def GetValue(self: 'LoopListResult') -> 'list[Loop]':
        return self.value

    def SetResult(self: 'LoopListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'LoopListResult') -> 'bool':
        return self.result

class Loop:
    def __init__(self: 'Loop'):
        self.length_string: LengthString = None
        self.code_block_field: CodeBlock = None
        self.loop_key_field: String = None
        self.r_value_field: RValue = None

    def SetLengthString(self: 'Loop',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'Loop') -> 'str':
        return self.length_string.GetString()

    def SetCodeBlock(self: 'Loop',input_value: 'CodeBlock') -> 'None':
        self.code_block_field = input_value

    def GetCodeBlock(self: 'Loop') -> 'CodeBlock':
        return self.code_block_field

    def SetLoopKey(self: 'Loop',input_value: 'String') -> 'None':
        self.loop_key_field = input_value

    def GetLoopKey(self: 'Loop') -> 'String':
        return self.loop_key_field

    def SetRValue(self: 'Loop',input_value: 'RValue') -> 'None':
        self.r_value_field = input_value

    def GetRValue(self: 'Loop') -> 'RValue':
        return self.r_value_field

class CallParser:
    def __init__(self: 'CallParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'CallParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'CallParser',index: 'LengthString',result: 'CallResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'Call' = Call()
        function_chain_field: 'QualfiedNameResult' = QualfiedNameResult()
        function_field: 'NameResult' = NameResult()
        parameters_field: 'ParameterListResult' = ParameterListResult()
        variable_field: 'NameResult' = NameResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and name_parser_instance.ParseSingleSave(index,variable_field) and string_parser_instance.ParseSingle(index,".") and name_parser_instance.ParseSingleSave(index,function_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,"(") and whitespace_parser_instance.ParseMany(index,0,-1) and parameter_list_parser_instance.ParseOptionalSave(index,parameters_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,")") and whitespace_parser_instance.ParseMany(index,0,-1):
            instance.SetFunctionChain(function_chain_field.GetValue())
            instance.SetFunction(function_field.GetValue())
            instance.SetParameters(parameters_field.GetValue())
            instance.SetVariable(variable_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            function_chain_field = QualfiedNameResult()
            function_field = NameResult()
            parameters_field = ParameterListResult()
            variable_field = NameResult()
        if True and name_parser_instance.ParseSingleSave(index,function_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,"(") and whitespace_parser_instance.ParseMany(index,0,-1) and parameter_list_parser_instance.ParseOptionalSave(index,parameters_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,")") and whitespace_parser_instance.ParseMany(index,0,-1):
            instance.SetFunctionChain(function_chain_field.GetValue())
            instance.SetFunction(function_field.GetValue())
            instance.SetParameters(parameters_field.GetValue())
            instance.SetVariable(variable_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            function_chain_field = QualfiedNameResult()
            function_field = NameResult()
            parameters_field = ParameterListResult()
            variable_field = NameResult()
        if True and qualfied_name_parser_instance.ParseSingleSave(index,function_chain_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,"(") and whitespace_parser_instance.ParseMany(index,0,-1) and parameter_list_parser_instance.ParseOptionalSave(index,parameters_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,")") and whitespace_parser_instance.ParseMany(index,0,-1):
            instance.SetFunctionChain(function_chain_field.GetValue())
            instance.SetFunction(function_field.GetValue())
            instance.SetParameters(parameters_field.GetValue())
            instance.SetVariable(variable_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            function_chain_field = QualfiedNameResult()
            function_field = NameResult()
            parameters_field = ParameterListResult()
            variable_field = NameResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'CallParser',index: 'LengthString') -> 'bool':
        result: 'CallResult' = CallResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'CallParser',index: 'LengthString',result: 'CallResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'CallParser',index: 'LengthString') -> 'bool':
        result: 'CallResult' = CallResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'CallParser',index: 'LengthString',list_result: 'CallListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[Call]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'CallResult' = CallResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'CallParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'CallListResult' = CallListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class CallResult:
    def __init__(self: 'CallResult'):
        self.value: Call = None
        self.result: bool = False

    def SetValue(self: 'CallResult',new_value: 'Call') -> 'None':
        self.value = new_value

    def GetValue(self: 'CallResult') -> 'Call':
        return self.value

    def SetResult(self: 'CallResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'CallResult') -> 'bool':
        return self.result

class CallListResult:
    def __init__(self: 'CallListResult'):
        self.value: list[Call] = []
        self.result: bool = False

    def SetValue(self: 'CallListResult',new_value: 'list[Call]') -> 'None':
        self.value = new_value

    def GetValue(self: 'CallListResult') -> 'list[Call]':
        return self.value

    def SetResult(self: 'CallListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'CallListResult') -> 'bool':
        return self.result

class Call:
    def __init__(self: 'Call'):
        self.length_string: LengthString = None
        self.function_chain_field: QualfiedName = None
        self.function_field: Name = None
        self.parameters_field: ParameterList = None
        self.variable_field: Name = None

    def SetLengthString(self: 'Call',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'Call') -> 'str':
        return self.length_string.GetString()

    def SetFunctionChain(self: 'Call',input_value: 'QualfiedName') -> 'None':
        self.function_chain_field = input_value

    def GetFunctionChain(self: 'Call') -> 'QualfiedName':
        return self.function_chain_field

    def SetFunction(self: 'Call',input_value: 'Name') -> 'None':
        self.function_field = input_value

    def GetFunction(self: 'Call') -> 'Name':
        return self.function_field

    def SetParameters(self: 'Call',input_value: 'ParameterList') -> 'None':
        self.parameters_field = input_value

    def GetParameters(self: 'Call') -> 'ParameterList':
        return self.parameters_field

    def SetVariable(self: 'Call',input_value: 'Name') -> 'None':
        self.variable_field = input_value

    def GetVariable(self: 'Call') -> 'Name':
        return self.variable_field

class AllocateParser:
    def __init__(self: 'AllocateParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'AllocateParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'AllocateParser',index: 'LengthString',result: 'AllocateResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'Allocate' = Allocate()
        managed_type_field: 'QualfiedNameResult' = QualfiedNameResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,"new") and whitespace_parser_instance.ParseMany(index,1,-1) and qualfied_name_parser_instance.ParseSingleSave(index,managed_type_field) and whitespace_parser_instance.ParseMany(index,0,-1):
            instance.SetManagedType(managed_type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            managed_type_field = QualfiedNameResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'AllocateParser',index: 'LengthString') -> 'bool':
        result: 'AllocateResult' = AllocateResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'AllocateParser',index: 'LengthString',result: 'AllocateResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'AllocateParser',index: 'LengthString') -> 'bool':
        result: 'AllocateResult' = AllocateResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'AllocateParser',index: 'LengthString',list_result: 'AllocateListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[Allocate]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'AllocateResult' = AllocateResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'AllocateParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'AllocateListResult' = AllocateListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class AllocateResult:
    def __init__(self: 'AllocateResult'):
        self.value: Allocate = None
        self.result: bool = False

    def SetValue(self: 'AllocateResult',new_value: 'Allocate') -> 'None':
        self.value = new_value

    def GetValue(self: 'AllocateResult') -> 'Allocate':
        return self.value

    def SetResult(self: 'AllocateResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'AllocateResult') -> 'bool':
        return self.result

class AllocateListResult:
    def __init__(self: 'AllocateListResult'):
        self.value: list[Allocate] = []
        self.result: bool = False

    def SetValue(self: 'AllocateListResult',new_value: 'list[Allocate]') -> 'None':
        self.value = new_value

    def GetValue(self: 'AllocateListResult') -> 'list[Allocate]':
        return self.value

    def SetResult(self: 'AllocateListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'AllocateListResult') -> 'bool':
        return self.result

class Allocate:
    def __init__(self: 'Allocate'):
        self.length_string: LengthString = None
        self.managed_type_field: QualfiedName = None

    def SetLengthString(self: 'Allocate',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'Allocate') -> 'str':
        return self.length_string.GetString()

    def SetManagedType(self: 'Allocate',input_value: 'QualfiedName') -> 'None':
        self.managed_type_field = input_value

    def GetManagedType(self: 'Allocate') -> 'QualfiedName':
        return self.managed_type_field

class InstructionParser:
    def __init__(self: 'InstructionParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'InstructionParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'InstructionParser',index: 'LengthString',result: 'InstructionResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'Instruction' = Instruction()
        assignment_field: 'AssignmentResult' = AssignmentResult()
        call_field: 'CallResult' = CallResult()
        code_block_field: 'CodeBlockResult' = CodeBlockResult()
        comment_field: 'CommentResult' = CommentResult()
        conditional_field: 'ConditionalResult' = ConditionalResult()
        declaration_field: 'DeclarationResult' = DeclarationResult()
        loop_field: 'LoopResult' = LoopResult()
        rtn_field: 'ReturnResult' = ReturnResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and comment_parser_instance.ParseOptionalSave(index,comment_field) and whitespace_parser_instance.ParseMany(index,0,-1) and code_block_parser_instance.ParseSingleSave(index,code_block_field):
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
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            assignment_field = AssignmentResult()
            call_field = CallResult()
            code_block_field = CodeBlockResult()
            comment_field = CommentResult()
            conditional_field = ConditionalResult()
            declaration_field = DeclarationResult()
            loop_field = LoopResult()
            rtn_field = ReturnResult()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and comment_parser_instance.ParseOptionalSave(index,comment_field) and whitespace_parser_instance.ParseMany(index,0,-1) and return_parser_instance.ParseSingleSave(index,rtn_field):
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
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            assignment_field = AssignmentResult()
            call_field = CallResult()
            code_block_field = CodeBlockResult()
            comment_field = CommentResult()
            conditional_field = ConditionalResult()
            declaration_field = DeclarationResult()
            loop_field = LoopResult()
            rtn_field = ReturnResult()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and comment_parser_instance.ParseOptionalSave(index,comment_field) and whitespace_parser_instance.ParseMany(index,0,-1) and declaration_parser_instance.ParseSingleSave(index,declaration_field):
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
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            assignment_field = AssignmentResult()
            call_field = CallResult()
            code_block_field = CodeBlockResult()
            comment_field = CommentResult()
            conditional_field = ConditionalResult()
            declaration_field = DeclarationResult()
            loop_field = LoopResult()
            rtn_field = ReturnResult()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and comment_parser_instance.ParseOptionalSave(index,comment_field) and whitespace_parser_instance.ParseMany(index,0,-1) and assignment_parser_instance.ParseSingleSave(index,assignment_field):
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
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            assignment_field = AssignmentResult()
            call_field = CallResult()
            code_block_field = CodeBlockResult()
            comment_field = CommentResult()
            conditional_field = ConditionalResult()
            declaration_field = DeclarationResult()
            loop_field = LoopResult()
            rtn_field = ReturnResult()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and comment_parser_instance.ParseOptionalSave(index,comment_field) and whitespace_parser_instance.ParseMany(index,0,-1) and call_parser_instance.ParseSingleSave(index,call_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,";") and whitespace_parser_instance.ParseMany(index,0,-1):
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
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            assignment_field = AssignmentResult()
            call_field = CallResult()
            code_block_field = CodeBlockResult()
            comment_field = CommentResult()
            conditional_field = ConditionalResult()
            declaration_field = DeclarationResult()
            loop_field = LoopResult()
            rtn_field = ReturnResult()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and comment_parser_instance.ParseOptionalSave(index,comment_field) and whitespace_parser_instance.ParseMany(index,0,-1) and conditional_parser_instance.ParseSingleSave(index,conditional_field):
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
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            assignment_field = AssignmentResult()
            call_field = CallResult()
            code_block_field = CodeBlockResult()
            comment_field = CommentResult()
            conditional_field = ConditionalResult()
            declaration_field = DeclarationResult()
            loop_field = LoopResult()
            rtn_field = ReturnResult()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and comment_parser_instance.ParseOptionalSave(index,comment_field) and whitespace_parser_instance.ParseMany(index,0,-1) and loop_parser_instance.ParseSingleSave(index,loop_field):
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
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            assignment_field = AssignmentResult()
            call_field = CallResult()
            code_block_field = CodeBlockResult()
            comment_field = CommentResult()
            conditional_field = ConditionalResult()
            declaration_field = DeclarationResult()
            loop_field = LoopResult()
            rtn_field = ReturnResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'InstructionParser',index: 'LengthString') -> 'bool':
        result: 'InstructionResult' = InstructionResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'InstructionParser',index: 'LengthString',result: 'InstructionResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'InstructionParser',index: 'LengthString') -> 'bool':
        result: 'InstructionResult' = InstructionResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'InstructionParser',index: 'LengthString',list_result: 'InstructionListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[Instruction]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'InstructionResult' = InstructionResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'InstructionParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'InstructionListResult' = InstructionListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class InstructionResult:
    def __init__(self: 'InstructionResult'):
        self.value: Instruction = None
        self.result: bool = False

    def SetValue(self: 'InstructionResult',new_value: 'Instruction') -> 'None':
        self.value = new_value

    def GetValue(self: 'InstructionResult') -> 'Instruction':
        return self.value

    def SetResult(self: 'InstructionResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'InstructionResult') -> 'bool':
        return self.result

class InstructionListResult:
    def __init__(self: 'InstructionListResult'):
        self.value: list[Instruction] = []
        self.result: bool = False

    def SetValue(self: 'InstructionListResult',new_value: 'list[Instruction]') -> 'None':
        self.value = new_value

    def GetValue(self: 'InstructionListResult') -> 'list[Instruction]':
        return self.value

    def SetResult(self: 'InstructionListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'InstructionListResult') -> 'bool':
        return self.result

class Instruction:
    def __init__(self: 'Instruction'):
        self.length_string: LengthString = None
        self.assignment_field: Assignment = None
        self.call_field: Call = None
        self.code_block_field: CodeBlock = None
        self.comment_field: Comment = None
        self.conditional_field: Conditional = None
        self.declaration_field: Declaration = None
        self.loop_field: Loop = None
        self.rtn_field: Return = None

    def SetLengthString(self: 'Instruction',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'Instruction') -> 'str':
        return self.length_string.GetString()

    def SetAssignment(self: 'Instruction',input_value: 'Assignment') -> 'None':
        self.assignment_field = input_value

    def GetAssignment(self: 'Instruction') -> 'Assignment':
        return self.assignment_field

    def SetCall(self: 'Instruction',input_value: 'Call') -> 'None':
        self.call_field = input_value

    def GetCall(self: 'Instruction') -> 'Call':
        return self.call_field

    def SetCodeBlock(self: 'Instruction',input_value: 'CodeBlock') -> 'None':
        self.code_block_field = input_value

    def GetCodeBlock(self: 'Instruction') -> 'CodeBlock':
        return self.code_block_field

    def SetComment(self: 'Instruction',input_value: 'Comment') -> 'None':
        self.comment_field = input_value

    def GetComment(self: 'Instruction') -> 'Comment':
        return self.comment_field

    def SetConditional(self: 'Instruction',input_value: 'Conditional') -> 'None':
        self.conditional_field = input_value

    def GetConditional(self: 'Instruction') -> 'Conditional':
        return self.conditional_field

    def SetDeclaration(self: 'Instruction',input_value: 'Declaration') -> 'None':
        self.declaration_field = input_value

    def GetDeclaration(self: 'Instruction') -> 'Declaration':
        return self.declaration_field

    def SetLoop(self: 'Instruction',input_value: 'Loop') -> 'None':
        self.loop_field = input_value

    def GetLoop(self: 'Instruction') -> 'Loop':
        return self.loop_field

    def SetRtn(self: 'Instruction',input_value: 'Return') -> 'None':
        self.rtn_field = input_value

    def GetRtn(self: 'Instruction') -> 'Return':
        return self.rtn_field

class RValueSingleParser:
    def __init__(self: 'RValueSingleParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'RValueSingleParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'RValueSingleParser',index: 'LengthString',result: 'RValueSingleResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'RValueSingle' = RValueSingle()
        allocate_field: 'AllocateResult' = AllocateResult()
        boolean_literal_field: 'BooleanResult' = BooleanResult()
        byte_literal_field: 'ByteResult' = ByteResult()
        call_field: 'CallResult' = CallResult()
        decimal_literal_field: 'DecimalResult' = DecimalResult()
        integer_literal_field: 'NumberResult' = NumberResult()
        string_literal_field: 'LiteralResult' = LiteralResult()
        unary_operator_field: 'UnaryOperatorResult' = UnaryOperatorResult()
        variable_field: 'QualfiedNameResult' = QualfiedNameResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and unary_operator_parser_instance.ParseOptionalSave(index,unary_operator_field) and whitespace_parser_instance.ParseMany(index,0,-1) and call_parser_instance.ParseSingleSave(index,call_field):
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
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            allocate_field = AllocateResult()
            boolean_literal_field = BooleanResult()
            byte_literal_field = ByteResult()
            call_field = CallResult()
            decimal_literal_field = DecimalResult()
            integer_literal_field = NumberResult()
            string_literal_field = LiteralResult()
            unary_operator_field = UnaryOperatorResult()
            variable_field = QualfiedNameResult()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and unary_operator_parser_instance.ParseOptionalSave(index,unary_operator_field) and whitespace_parser_instance.ParseMany(index,0,-1) and allocate_parser_instance.ParseSingleSave(index,allocate_field):
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
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            allocate_field = AllocateResult()
            boolean_literal_field = BooleanResult()
            byte_literal_field = ByteResult()
            call_field = CallResult()
            decimal_literal_field = DecimalResult()
            integer_literal_field = NumberResult()
            string_literal_field = LiteralResult()
            unary_operator_field = UnaryOperatorResult()
            variable_field = QualfiedNameResult()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and unary_operator_parser_instance.ParseOptionalSave(index,unary_operator_field) and whitespace_parser_instance.ParseMany(index,0,-1) and byte_parser_instance.ParseSingleSave(index,byte_literal_field):
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
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            allocate_field = AllocateResult()
            boolean_literal_field = BooleanResult()
            byte_literal_field = ByteResult()
            call_field = CallResult()
            decimal_literal_field = DecimalResult()
            integer_literal_field = NumberResult()
            string_literal_field = LiteralResult()
            unary_operator_field = UnaryOperatorResult()
            variable_field = QualfiedNameResult()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and unary_operator_parser_instance.ParseOptionalSave(index,unary_operator_field) and whitespace_parser_instance.ParseMany(index,0,-1) and decimal_parser_instance.ParseSingleSave(index,decimal_literal_field):
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
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            allocate_field = AllocateResult()
            boolean_literal_field = BooleanResult()
            byte_literal_field = ByteResult()
            call_field = CallResult()
            decimal_literal_field = DecimalResult()
            integer_literal_field = NumberResult()
            string_literal_field = LiteralResult()
            unary_operator_field = UnaryOperatorResult()
            variable_field = QualfiedNameResult()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and unary_operator_parser_instance.ParseOptionalSave(index,unary_operator_field) and whitespace_parser_instance.ParseMany(index,0,-1) and number_parser_instance.ParseSingleSave(index,integer_literal_field):
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
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            allocate_field = AllocateResult()
            boolean_literal_field = BooleanResult()
            byte_literal_field = ByteResult()
            call_field = CallResult()
            decimal_literal_field = DecimalResult()
            integer_literal_field = NumberResult()
            string_literal_field = LiteralResult()
            unary_operator_field = UnaryOperatorResult()
            variable_field = QualfiedNameResult()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and unary_operator_parser_instance.ParseOptionalSave(index,unary_operator_field) and whitespace_parser_instance.ParseMany(index,0,-1) and boolean_parser_instance.ParseSingleSave(index,boolean_literal_field):
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
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            allocate_field = AllocateResult()
            boolean_literal_field = BooleanResult()
            byte_literal_field = ByteResult()
            call_field = CallResult()
            decimal_literal_field = DecimalResult()
            integer_literal_field = NumberResult()
            string_literal_field = LiteralResult()
            unary_operator_field = UnaryOperatorResult()
            variable_field = QualfiedNameResult()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and unary_operator_parser_instance.ParseOptionalSave(index,unary_operator_field) and whitespace_parser_instance.ParseMany(index,0,-1) and qualfied_name_parser_instance.ParseSingleSave(index,variable_field):
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
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            allocate_field = AllocateResult()
            boolean_literal_field = BooleanResult()
            byte_literal_field = ByteResult()
            call_field = CallResult()
            decimal_literal_field = DecimalResult()
            integer_literal_field = NumberResult()
            string_literal_field = LiteralResult()
            unary_operator_field = UnaryOperatorResult()
            variable_field = QualfiedNameResult()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and unary_operator_parser_instance.ParseOptionalSave(index,unary_operator_field) and whitespace_parser_instance.ParseMany(index,0,-1) and string_parser_instance.ParseSingle(index,"\"") and literal_parser_instance.ParseSingleSave(index,string_literal_field) and string_parser_instance.ParseSingle(index,"\""):
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
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            allocate_field = AllocateResult()
            boolean_literal_field = BooleanResult()
            byte_literal_field = ByteResult()
            call_field = CallResult()
            decimal_literal_field = DecimalResult()
            integer_literal_field = NumberResult()
            string_literal_field = LiteralResult()
            unary_operator_field = UnaryOperatorResult()
            variable_field = QualfiedNameResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'RValueSingleParser',index: 'LengthString') -> 'bool':
        result: 'RValueSingleResult' = RValueSingleResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'RValueSingleParser',index: 'LengthString',result: 'RValueSingleResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'RValueSingleParser',index: 'LengthString') -> 'bool':
        result: 'RValueSingleResult' = RValueSingleResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'RValueSingleParser',index: 'LengthString',list_result: 'RValueSingleListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[RValueSingle]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'RValueSingleResult' = RValueSingleResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'RValueSingleParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'RValueSingleListResult' = RValueSingleListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class RValueSingleResult:
    def __init__(self: 'RValueSingleResult'):
        self.value: RValueSingle = None
        self.result: bool = False

    def SetValue(self: 'RValueSingleResult',new_value: 'RValueSingle') -> 'None':
        self.value = new_value

    def GetValue(self: 'RValueSingleResult') -> 'RValueSingle':
        return self.value

    def SetResult(self: 'RValueSingleResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'RValueSingleResult') -> 'bool':
        return self.result

class RValueSingleListResult:
    def __init__(self: 'RValueSingleListResult'):
        self.value: list[RValueSingle] = []
        self.result: bool = False

    def SetValue(self: 'RValueSingleListResult',new_value: 'list[RValueSingle]') -> 'None':
        self.value = new_value

    def GetValue(self: 'RValueSingleListResult') -> 'list[RValueSingle]':
        return self.value

    def SetResult(self: 'RValueSingleListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'RValueSingleListResult') -> 'bool':
        return self.result

class RValueSingle:
    def __init__(self: 'RValueSingle'):
        self.length_string: LengthString = None
        self.allocate_field: Allocate = None
        self.boolean_literal_field: Boolean = None
        self.byte_literal_field: Byte = None
        self.call_field: Call = None
        self.decimal_literal_field: Decimal = None
        self.integer_literal_field: Number = None
        self.string_literal_field: Literal = None
        self.unary_operator_field: UnaryOperator = None
        self.variable_field: QualfiedName = None

    def SetLengthString(self: 'RValueSingle',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'RValueSingle') -> 'str':
        return self.length_string.GetString()

    def SetAllocate(self: 'RValueSingle',input_value: 'Allocate') -> 'None':
        self.allocate_field = input_value

    def GetAllocate(self: 'RValueSingle') -> 'Allocate':
        return self.allocate_field

    def SetBooleanLiteral(self: 'RValueSingle',input_value: 'Boolean') -> 'None':
        self.boolean_literal_field = input_value

    def GetBooleanLiteral(self: 'RValueSingle') -> 'Boolean':
        return self.boolean_literal_field

    def SetByteLiteral(self: 'RValueSingle',input_value: 'Byte') -> 'None':
        self.byte_literal_field = input_value

    def GetByteLiteral(self: 'RValueSingle') -> 'Byte':
        return self.byte_literal_field

    def SetCall(self: 'RValueSingle',input_value: 'Call') -> 'None':
        self.call_field = input_value

    def GetCall(self: 'RValueSingle') -> 'Call':
        return self.call_field

    def SetDecimalLiteral(self: 'RValueSingle',input_value: 'Decimal') -> 'None':
        self.decimal_literal_field = input_value

    def GetDecimalLiteral(self: 'RValueSingle') -> 'Decimal':
        return self.decimal_literal_field

    def SetIntegerLiteral(self: 'RValueSingle',input_value: 'Number') -> 'None':
        self.integer_literal_field = input_value

    def GetIntegerLiteral(self: 'RValueSingle') -> 'Number':
        return self.integer_literal_field

    def SetStringLiteral(self: 'RValueSingle',input_value: 'Literal') -> 'None':
        self.string_literal_field = input_value

    def GetStringLiteral(self: 'RValueSingle') -> 'Literal':
        return self.string_literal_field

    def SetUnaryOperator(self: 'RValueSingle',input_value: 'UnaryOperator') -> 'None':
        self.unary_operator_field = input_value

    def GetUnaryOperator(self: 'RValueSingle') -> 'UnaryOperator':
        return self.unary_operator_field

    def SetVariable(self: 'RValueSingle',input_value: 'QualfiedName') -> 'None':
        self.variable_field = input_value

    def GetVariable(self: 'RValueSingle') -> 'QualfiedName':
        return self.variable_field

class RValueTailParser:
    def __init__(self: 'RValueTailParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'RValueTailParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'RValueTailParser',index: 'LengthString',result: 'RValueTailResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'RValueTail' = RValueTail()
        binary_operator_field: 'BinaryOperatorResult' = BinaryOperatorResult()
        tail_field: 'RValueTailResult' = RValueTailResult()
        value_field: 'RValueSingleResult' = RValueSingleResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and whitespace_parser_instance.ParseMany(index,0,-1) and binary_operator_parser_instance.ParseSingleSave(index,binary_operator_field) and whitespace_parser_instance.ParseMany(index,0,-1) and r_value_single_parser_instance.ParseSingleSave(index,value_field) and whitespace_parser_instance.ParseMany(index,0,-1) and r_value_tail_parser_instance.ParseOptionalSave(index,tail_field):
            instance.SetBinaryOperator(binary_operator_field.GetValue())
            instance.SetTail(tail_field.GetValue())
            instance.SetValue(value_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            binary_operator_field = BinaryOperatorResult()
            tail_field = RValueTailResult()
            value_field = RValueSingleResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'RValueTailParser',index: 'LengthString') -> 'bool':
        result: 'RValueTailResult' = RValueTailResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'RValueTailParser',index: 'LengthString',result: 'RValueTailResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'RValueTailParser',index: 'LengthString') -> 'bool':
        result: 'RValueTailResult' = RValueTailResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'RValueTailParser',index: 'LengthString',list_result: 'RValueTailListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[RValueTail]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'RValueTailResult' = RValueTailResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'RValueTailParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'RValueTailListResult' = RValueTailListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class RValueTailResult:
    def __init__(self: 'RValueTailResult'):
        self.value: RValueTail = None
        self.result: bool = False

    def SetValue(self: 'RValueTailResult',new_value: 'RValueTail') -> 'None':
        self.value = new_value

    def GetValue(self: 'RValueTailResult') -> 'RValueTail':
        return self.value

    def SetResult(self: 'RValueTailResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'RValueTailResult') -> 'bool':
        return self.result

class RValueTailListResult:
    def __init__(self: 'RValueTailListResult'):
        self.value: list[RValueTail] = []
        self.result: bool = False

    def SetValue(self: 'RValueTailListResult',new_value: 'list[RValueTail]') -> 'None':
        self.value = new_value

    def GetValue(self: 'RValueTailListResult') -> 'list[RValueTail]':
        return self.value

    def SetResult(self: 'RValueTailListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'RValueTailListResult') -> 'bool':
        return self.result

class RValueTail:
    def __init__(self: 'RValueTail'):
        self.length_string: LengthString = None
        self.binary_operator_field: BinaryOperator = None
        self.tail_field: RValueTail = None
        self.value_field: RValueSingle = None

    def SetLengthString(self: 'RValueTail',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'RValueTail') -> 'str':
        return self.length_string.GetString()

    def SetBinaryOperator(self: 'RValueTail',input_value: 'BinaryOperator') -> 'None':
        self.binary_operator_field = input_value

    def GetBinaryOperator(self: 'RValueTail') -> 'BinaryOperator':
        return self.binary_operator_field

    def SetTail(self: 'RValueTail',input_value: 'RValueTail') -> 'None':
        self.tail_field = input_value

    def GetTail(self: 'RValueTail') -> 'RValueTail':
        return self.tail_field

    def SetValue(self: 'RValueTail',input_value: 'RValueSingle') -> 'None':
        self.value_field = input_value

    def GetValue(self: 'RValueTail') -> 'RValueSingle':
        return self.value_field

class RValueParser:
    def __init__(self: 'RValueParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'RValueParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'RValueParser',index: 'LengthString',result: 'RValueResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'RValue' = RValue()
        tail_field: 'RValueTailResult' = RValueTailResult()
        value_field: 'RValueSingleResult' = RValueSingleResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and r_value_single_parser_instance.ParseSingleSave(index,value_field) and r_value_tail_parser_instance.ParseOptionalSave(index,tail_field):
            instance.SetTail(tail_field.GetValue())
            instance.SetValue(value_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            tail_field = RValueTailResult()
            value_field = RValueSingleResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'RValueParser',index: 'LengthString') -> 'bool':
        result: 'RValueResult' = RValueResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'RValueParser',index: 'LengthString',result: 'RValueResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'RValueParser',index: 'LengthString') -> 'bool':
        result: 'RValueResult' = RValueResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'RValueParser',index: 'LengthString',list_result: 'RValueListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[RValue]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'RValueResult' = RValueResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'RValueParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'RValueListResult' = RValueListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class RValueResult:
    def __init__(self: 'RValueResult'):
        self.value: RValue = None
        self.result: bool = False

    def SetValue(self: 'RValueResult',new_value: 'RValue') -> 'None':
        self.value = new_value

    def GetValue(self: 'RValueResult') -> 'RValue':
        return self.value

    def SetResult(self: 'RValueResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'RValueResult') -> 'bool':
        return self.result

class RValueListResult:
    def __init__(self: 'RValueListResult'):
        self.value: list[RValue] = []
        self.result: bool = False

    def SetValue(self: 'RValueListResult',new_value: 'list[RValue]') -> 'None':
        self.value = new_value

    def GetValue(self: 'RValueListResult') -> 'list[RValue]':
        return self.value

    def SetResult(self: 'RValueListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'RValueListResult') -> 'bool':
        return self.result

class RValue:
    def __init__(self: 'RValue'):
        self.length_string: LengthString = None
        self.tail_field: RValueTail = None
        self.value_field: RValueSingle = None

    def SetLengthString(self: 'RValue',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'RValue') -> 'str':
        return self.length_string.GetString()

    def SetTail(self: 'RValue',input_value: 'RValueTail') -> 'None':
        self.tail_field = input_value

    def GetTail(self: 'RValue') -> 'RValueTail':
        return self.tail_field

    def SetValue(self: 'RValue',input_value: 'RValueSingle') -> 'None':
        self.value_field = input_value

    def GetValue(self: 'RValue') -> 'RValueSingle':
        return self.value_field

class BinaryOperatorParser:
    def __init__(self: 'BinaryOperatorParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'BinaryOperatorParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'BinaryOperatorParser',index: 'LengthString',result: 'BinaryOperatorResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'BinaryOperator' = BinaryOperator()
        addition_field: 'StringResult' = StringResult()
        and_op_field: 'StringResult' = StringResult()
        equality_field: 'StringResult' = StringResult()
        greater_than_eq_field: 'StringResult' = StringResult()
        greater_than_field: 'StringResult' = StringResult()
        less_than_eq_field: 'StringResult' = StringResult()
        less_than_field: 'StringResult' = StringResult()
        not_equality_field: 'StringResult' = StringResult()
        or_op_field: 'StringResult' = StringResult()
        subtraction_field: 'StringResult' = StringResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and string_parser_instance.ParseSingleSave(index,"+",addition_field):
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
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            addition_field = StringResult()
            and_op_field = StringResult()
            equality_field = StringResult()
            greater_than_eq_field = StringResult()
            greater_than_field = StringResult()
            less_than_eq_field = StringResult()
            less_than_field = StringResult()
            not_equality_field = StringResult()
            or_op_field = StringResult()
            subtraction_field = StringResult()
        if True and string_parser_instance.ParseSingleSave(index,"-",subtraction_field):
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
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            addition_field = StringResult()
            and_op_field = StringResult()
            equality_field = StringResult()
            greater_than_eq_field = StringResult()
            greater_than_field = StringResult()
            less_than_eq_field = StringResult()
            less_than_field = StringResult()
            not_equality_field = StringResult()
            or_op_field = StringResult()
            subtraction_field = StringResult()
        if True and string_parser_instance.ParseSingleSave(index,"<=",less_than_eq_field):
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
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            addition_field = StringResult()
            and_op_field = StringResult()
            equality_field = StringResult()
            greater_than_eq_field = StringResult()
            greater_than_field = StringResult()
            less_than_eq_field = StringResult()
            less_than_field = StringResult()
            not_equality_field = StringResult()
            or_op_field = StringResult()
            subtraction_field = StringResult()
        if True and string_parser_instance.ParseSingleSave(index,">=",greater_than_eq_field):
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
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            addition_field = StringResult()
            and_op_field = StringResult()
            equality_field = StringResult()
            greater_than_eq_field = StringResult()
            greater_than_field = StringResult()
            less_than_eq_field = StringResult()
            less_than_field = StringResult()
            not_equality_field = StringResult()
            or_op_field = StringResult()
            subtraction_field = StringResult()
        if True and string_parser_instance.ParseSingleSave(index,"==",equality_field):
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
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            addition_field = StringResult()
            and_op_field = StringResult()
            equality_field = StringResult()
            greater_than_eq_field = StringResult()
            greater_than_field = StringResult()
            less_than_eq_field = StringResult()
            less_than_field = StringResult()
            not_equality_field = StringResult()
            or_op_field = StringResult()
            subtraction_field = StringResult()
        if True and string_parser_instance.ParseSingleSave(index,"!=",not_equality_field):
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
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            addition_field = StringResult()
            and_op_field = StringResult()
            equality_field = StringResult()
            greater_than_eq_field = StringResult()
            greater_than_field = StringResult()
            less_than_eq_field = StringResult()
            less_than_field = StringResult()
            not_equality_field = StringResult()
            or_op_field = StringResult()
            subtraction_field = StringResult()
        if True and string_parser_instance.ParseSingleSave(index,"<",less_than_field):
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
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            addition_field = StringResult()
            and_op_field = StringResult()
            equality_field = StringResult()
            greater_than_eq_field = StringResult()
            greater_than_field = StringResult()
            less_than_eq_field = StringResult()
            less_than_field = StringResult()
            not_equality_field = StringResult()
            or_op_field = StringResult()
            subtraction_field = StringResult()
        if True and string_parser_instance.ParseSingleSave(index,">",greater_than_field):
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
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            addition_field = StringResult()
            and_op_field = StringResult()
            equality_field = StringResult()
            greater_than_eq_field = StringResult()
            greater_than_field = StringResult()
            less_than_eq_field = StringResult()
            less_than_field = StringResult()
            not_equality_field = StringResult()
            or_op_field = StringResult()
            subtraction_field = StringResult()
        if True and string_parser_instance.ParseSingleSave(index,"||",or_op_field):
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
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            addition_field = StringResult()
            and_op_field = StringResult()
            equality_field = StringResult()
            greater_than_eq_field = StringResult()
            greater_than_field = StringResult()
            less_than_eq_field = StringResult()
            less_than_field = StringResult()
            not_equality_field = StringResult()
            or_op_field = StringResult()
            subtraction_field = StringResult()
        if True and string_parser_instance.ParseSingleSave(index,"&&",and_op_field):
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
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            addition_field = StringResult()
            and_op_field = StringResult()
            equality_field = StringResult()
            greater_than_eq_field = StringResult()
            greater_than_field = StringResult()
            less_than_eq_field = StringResult()
            less_than_field = StringResult()
            not_equality_field = StringResult()
            or_op_field = StringResult()
            subtraction_field = StringResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'BinaryOperatorParser',index: 'LengthString') -> 'bool':
        result: 'BinaryOperatorResult' = BinaryOperatorResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'BinaryOperatorParser',index: 'LengthString',result: 'BinaryOperatorResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'BinaryOperatorParser',index: 'LengthString') -> 'bool':
        result: 'BinaryOperatorResult' = BinaryOperatorResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'BinaryOperatorParser',index: 'LengthString',list_result: 'BinaryOperatorListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[BinaryOperator]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'BinaryOperatorResult' = BinaryOperatorResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'BinaryOperatorParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'BinaryOperatorListResult' = BinaryOperatorListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class BinaryOperatorResult:
    def __init__(self: 'BinaryOperatorResult'):
        self.value: BinaryOperator = None
        self.result: bool = False

    def SetValue(self: 'BinaryOperatorResult',new_value: 'BinaryOperator') -> 'None':
        self.value = new_value

    def GetValue(self: 'BinaryOperatorResult') -> 'BinaryOperator':
        return self.value

    def SetResult(self: 'BinaryOperatorResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'BinaryOperatorResult') -> 'bool':
        return self.result

class BinaryOperatorListResult:
    def __init__(self: 'BinaryOperatorListResult'):
        self.value: list[BinaryOperator] = []
        self.result: bool = False

    def SetValue(self: 'BinaryOperatorListResult',new_value: 'list[BinaryOperator]') -> 'None':
        self.value = new_value

    def GetValue(self: 'BinaryOperatorListResult') -> 'list[BinaryOperator]':
        return self.value

    def SetResult(self: 'BinaryOperatorListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'BinaryOperatorListResult') -> 'bool':
        return self.result

class BinaryOperator:
    def __init__(self: 'BinaryOperator'):
        self.length_string: LengthString = None
        self.addition_field: String = None
        self.and_op_field: String = None
        self.equality_field: String = None
        self.greater_than_eq_field: String = None
        self.greater_than_field: String = None
        self.less_than_eq_field: String = None
        self.less_than_field: String = None
        self.not_equality_field: String = None
        self.or_op_field: String = None
        self.subtraction_field: String = None

    def SetLengthString(self: 'BinaryOperator',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'BinaryOperator') -> 'str':
        return self.length_string.GetString()

    def SetAddition(self: 'BinaryOperator',input_value: 'String') -> 'None':
        self.addition_field = input_value

    def GetAddition(self: 'BinaryOperator') -> 'String':
        return self.addition_field

    def SetAndOp(self: 'BinaryOperator',input_value: 'String') -> 'None':
        self.and_op_field = input_value

    def GetAndOp(self: 'BinaryOperator') -> 'String':
        return self.and_op_field

    def SetEquality(self: 'BinaryOperator',input_value: 'String') -> 'None':
        self.equality_field = input_value

    def GetEquality(self: 'BinaryOperator') -> 'String':
        return self.equality_field

    def SetGreaterThanEq(self: 'BinaryOperator',input_value: 'String') -> 'None':
        self.greater_than_eq_field = input_value

    def GetGreaterThanEq(self: 'BinaryOperator') -> 'String':
        return self.greater_than_eq_field

    def SetGreaterThan(self: 'BinaryOperator',input_value: 'String') -> 'None':
        self.greater_than_field = input_value

    def GetGreaterThan(self: 'BinaryOperator') -> 'String':
        return self.greater_than_field

    def SetLessThanEq(self: 'BinaryOperator',input_value: 'String') -> 'None':
        self.less_than_eq_field = input_value

    def GetLessThanEq(self: 'BinaryOperator') -> 'String':
        return self.less_than_eq_field

    def SetLessThan(self: 'BinaryOperator',input_value: 'String') -> 'None':
        self.less_than_field = input_value

    def GetLessThan(self: 'BinaryOperator') -> 'String':
        return self.less_than_field

    def SetNotEquality(self: 'BinaryOperator',input_value: 'String') -> 'None':
        self.not_equality_field = input_value

    def GetNotEquality(self: 'BinaryOperator') -> 'String':
        return self.not_equality_field

    def SetOrOp(self: 'BinaryOperator',input_value: 'String') -> 'None':
        self.or_op_field = input_value

    def GetOrOp(self: 'BinaryOperator') -> 'String':
        return self.or_op_field

    def SetSubtraction(self: 'BinaryOperator',input_value: 'String') -> 'None':
        self.subtraction_field = input_value

    def GetSubtraction(self: 'BinaryOperator') -> 'String':
        return self.subtraction_field

class UnaryOperatorParser:
    def __init__(self: 'UnaryOperatorParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'UnaryOperatorParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'UnaryOperatorParser',index: 'LengthString',result: 'UnaryOperatorResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'UnaryOperator' = UnaryOperator()
        negation_field: 'StringResult' = StringResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and string_parser_instance.ParseSingleSave(index,"!",negation_field):
            instance.SetNegation(negation_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            negation_field = StringResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'UnaryOperatorParser',index: 'LengthString') -> 'bool':
        result: 'UnaryOperatorResult' = UnaryOperatorResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'UnaryOperatorParser',index: 'LengthString',result: 'UnaryOperatorResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'UnaryOperatorParser',index: 'LengthString') -> 'bool':
        result: 'UnaryOperatorResult' = UnaryOperatorResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'UnaryOperatorParser',index: 'LengthString',list_result: 'UnaryOperatorListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[UnaryOperator]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'UnaryOperatorResult' = UnaryOperatorResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'UnaryOperatorParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'UnaryOperatorListResult' = UnaryOperatorListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class UnaryOperatorResult:
    def __init__(self: 'UnaryOperatorResult'):
        self.value: UnaryOperator = None
        self.result: bool = False

    def SetValue(self: 'UnaryOperatorResult',new_value: 'UnaryOperator') -> 'None':
        self.value = new_value

    def GetValue(self: 'UnaryOperatorResult') -> 'UnaryOperator':
        return self.value

    def SetResult(self: 'UnaryOperatorResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'UnaryOperatorResult') -> 'bool':
        return self.result

class UnaryOperatorListResult:
    def __init__(self: 'UnaryOperatorListResult'):
        self.value: list[UnaryOperator] = []
        self.result: bool = False

    def SetValue(self: 'UnaryOperatorListResult',new_value: 'list[UnaryOperator]') -> 'None':
        self.value = new_value

    def GetValue(self: 'UnaryOperatorListResult') -> 'list[UnaryOperator]':
        return self.value

    def SetResult(self: 'UnaryOperatorListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'UnaryOperatorListResult') -> 'bool':
        return self.result

class UnaryOperator:
    def __init__(self: 'UnaryOperator'):
        self.length_string: LengthString = None
        self.negation_field: String = None

    def SetLengthString(self: 'UnaryOperator',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'UnaryOperator') -> 'str':
        return self.length_string.GetString()

    def SetNegation(self: 'UnaryOperator',input_value: 'String') -> 'None':
        self.negation_field = input_value

    def GetNegation(self: 'UnaryOperator') -> 'String':
        return self.negation_field

class CommentParser:
    def __init__(self: 'CommentParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'CommentParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'CommentParser',index: 'LengthString',result: 'CommentResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'Comment' = Comment()
        content_field: 'CommentContentListResult' = CommentContentListResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and string_parser_instance.ParseSingle(index,"/*") and comment_content_parser_instance.ParseManySave(index,content_field,0,-1) and string_parser_instance.ParseSingle(index,"*/"):
            instance.SetContent(content_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            content_field = CommentContentListResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'CommentParser',index: 'LengthString') -> 'bool':
        result: 'CommentResult' = CommentResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'CommentParser',index: 'LengthString',result: 'CommentResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'CommentParser',index: 'LengthString') -> 'bool':
        result: 'CommentResult' = CommentResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'CommentParser',index: 'LengthString',list_result: 'CommentListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[Comment]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'CommentResult' = CommentResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'CommentParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'CommentListResult' = CommentListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class CommentResult:
    def __init__(self: 'CommentResult'):
        self.value: Comment = None
        self.result: bool = False

    def SetValue(self: 'CommentResult',new_value: 'Comment') -> 'None':
        self.value = new_value

    def GetValue(self: 'CommentResult') -> 'Comment':
        return self.value

    def SetResult(self: 'CommentResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'CommentResult') -> 'bool':
        return self.result

class CommentListResult:
    def __init__(self: 'CommentListResult'):
        self.value: list[Comment] = []
        self.result: bool = False

    def SetValue(self: 'CommentListResult',new_value: 'list[Comment]') -> 'None':
        self.value = new_value

    def GetValue(self: 'CommentListResult') -> 'list[Comment]':
        return self.value

    def SetResult(self: 'CommentListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'CommentListResult') -> 'bool':
        return self.result

class Comment:
    def __init__(self: 'Comment'):
        self.length_string: LengthString = None
        self.content_field: list[CommentContent] = []

    def SetLengthString(self: 'Comment',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'Comment') -> 'str':
        return self.length_string.GetString()

    def SetContent(self: 'Comment',input_value: 'list[CommentContent]') -> 'None':
        self.content_field = input_value

    def GetContent(self: 'Comment') -> 'list[CommentContent]':
        return self.content_field

class NonStarCharacterParser:
    def __init__(self: 'NonStarCharacterParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'NonStarCharacterParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'NonStarCharacterParser',index: 'LengthString',result: 'NonStarCharacterResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'NonStarCharacter' = NonStarCharacter()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and character_range_parser_instance.ParseSingle(index,0x00,0x29):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        if True and character_range_parser_instance.ParseSingle(index,0x2B,0xFF):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'NonStarCharacterParser',index: 'LengthString') -> 'bool':
        result: 'NonStarCharacterResult' = NonStarCharacterResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'NonStarCharacterParser',index: 'LengthString',result: 'NonStarCharacterResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'NonStarCharacterParser',index: 'LengthString') -> 'bool':
        result: 'NonStarCharacterResult' = NonStarCharacterResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'NonStarCharacterParser',index: 'LengthString',list_result: 'NonStarCharacterListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[NonStarCharacter]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'NonStarCharacterResult' = NonStarCharacterResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'NonStarCharacterParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'NonStarCharacterListResult' = NonStarCharacterListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class NonStarCharacterResult:
    def __init__(self: 'NonStarCharacterResult'):
        self.value: NonStarCharacter = None
        self.result: bool = False

    def SetValue(self: 'NonStarCharacterResult',new_value: 'NonStarCharacter') -> 'None':
        self.value = new_value

    def GetValue(self: 'NonStarCharacterResult') -> 'NonStarCharacter':
        return self.value

    def SetResult(self: 'NonStarCharacterResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'NonStarCharacterResult') -> 'bool':
        return self.result

class NonStarCharacterListResult:
    def __init__(self: 'NonStarCharacterListResult'):
        self.value: list[NonStarCharacter] = []
        self.result: bool = False

    def SetValue(self: 'NonStarCharacterListResult',new_value: 'list[NonStarCharacter]') -> 'None':
        self.value = new_value

    def GetValue(self: 'NonStarCharacterListResult') -> 'list[NonStarCharacter]':
        return self.value

    def SetResult(self: 'NonStarCharacterListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'NonStarCharacterListResult') -> 'bool':
        return self.result

class NonStarCharacter:
    def __init__(self: 'NonStarCharacter'):
        self.length_string: LengthString = None

    def SetLengthString(self: 'NonStarCharacter',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'NonStarCharacter') -> 'str':
        return self.length_string.GetString()

class NonSlashCharacterParser:
    def __init__(self: 'NonSlashCharacterParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'NonSlashCharacterParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'NonSlashCharacterParser',index: 'LengthString',result: 'NonSlashCharacterResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'NonSlashCharacter' = NonSlashCharacter()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and character_range_parser_instance.ParseSingle(index,0x00,0x2E):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        if True and character_range_parser_instance.ParseSingle(index,0x30,0xFF):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'NonSlashCharacterParser',index: 'LengthString') -> 'bool':
        result: 'NonSlashCharacterResult' = NonSlashCharacterResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'NonSlashCharacterParser',index: 'LengthString',result: 'NonSlashCharacterResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'NonSlashCharacterParser',index: 'LengthString') -> 'bool':
        result: 'NonSlashCharacterResult' = NonSlashCharacterResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'NonSlashCharacterParser',index: 'LengthString',list_result: 'NonSlashCharacterListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[NonSlashCharacter]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'NonSlashCharacterResult' = NonSlashCharacterResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'NonSlashCharacterParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'NonSlashCharacterListResult' = NonSlashCharacterListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class NonSlashCharacterResult:
    def __init__(self: 'NonSlashCharacterResult'):
        self.value: NonSlashCharacter = None
        self.result: bool = False

    def SetValue(self: 'NonSlashCharacterResult',new_value: 'NonSlashCharacter') -> 'None':
        self.value = new_value

    def GetValue(self: 'NonSlashCharacterResult') -> 'NonSlashCharacter':
        return self.value

    def SetResult(self: 'NonSlashCharacterResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'NonSlashCharacterResult') -> 'bool':
        return self.result

class NonSlashCharacterListResult:
    def __init__(self: 'NonSlashCharacterListResult'):
        self.value: list[NonSlashCharacter] = []
        self.result: bool = False

    def SetValue(self: 'NonSlashCharacterListResult',new_value: 'list[NonSlashCharacter]') -> 'None':
        self.value = new_value

    def GetValue(self: 'NonSlashCharacterListResult') -> 'list[NonSlashCharacter]':
        return self.value

    def SetResult(self: 'NonSlashCharacterListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'NonSlashCharacterListResult') -> 'bool':
        return self.result

class NonSlashCharacter:
    def __init__(self: 'NonSlashCharacter'):
        self.length_string: LengthString = None

    def SetLengthString(self: 'NonSlashCharacter',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'NonSlashCharacter') -> 'str':
        return self.length_string.GetString()

class CommentContentParser:
    def __init__(self: 'CommentContentParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'CommentContentParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'CommentContentParser',index: 'LengthString',result: 'CommentContentResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'CommentContent' = CommentContent()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and non_star_character_parser_instance.ParseSingle(index):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        if True and string_parser_instance.ParseSingle(index,"*") and non_slash_character_parser_instance.ParseSingle(index):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'CommentContentParser',index: 'LengthString') -> 'bool':
        result: 'CommentContentResult' = CommentContentResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'CommentContentParser',index: 'LengthString',result: 'CommentContentResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'CommentContentParser',index: 'LengthString') -> 'bool':
        result: 'CommentContentResult' = CommentContentResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'CommentContentParser',index: 'LengthString',list_result: 'CommentContentListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[CommentContent]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'CommentContentResult' = CommentContentResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'CommentContentParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'CommentContentListResult' = CommentContentListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class CommentContentResult:
    def __init__(self: 'CommentContentResult'):
        self.value: CommentContent = None
        self.result: bool = False

    def SetValue(self: 'CommentContentResult',new_value: 'CommentContent') -> 'None':
        self.value = new_value

    def GetValue(self: 'CommentContentResult') -> 'CommentContent':
        return self.value

    def SetResult(self: 'CommentContentResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'CommentContentResult') -> 'bool':
        return self.result

class CommentContentListResult:
    def __init__(self: 'CommentContentListResult'):
        self.value: list[CommentContent] = []
        self.result: bool = False

    def SetValue(self: 'CommentContentListResult',new_value: 'list[CommentContent]') -> 'None':
        self.value = new_value

    def GetValue(self: 'CommentContentListResult') -> 'list[CommentContent]':
        return self.value

    def SetResult(self: 'CommentContentListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'CommentContentListResult') -> 'bool':
        return self.result

class CommentContent:
    def __init__(self: 'CommentContent'):
        self.length_string: LengthString = None

    def SetLengthString(self: 'CommentContent',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'CommentContent') -> 'str':
        return self.length_string.GetString()

class QualfiedNameParser:
    def __init__(self: 'QualfiedNameParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'QualfiedNameParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'QualfiedNameParser',index: 'LengthString',result: 'QualfiedNameResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'QualfiedName' = QualfiedName()
        name_field: 'NameResult' = NameResult()
        tail_field: 'NameTailResult' = NameTailResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and name_parser_instance.ParseSingleSave(index,name_field) and name_tail_parser_instance.ParseOptionalSave(index,tail_field):
            instance.SetName(name_field.GetValue())
            instance.SetTail(tail_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            name_field = NameResult()
            tail_field = NameTailResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'QualfiedNameParser',index: 'LengthString') -> 'bool':
        result: 'QualfiedNameResult' = QualfiedNameResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'QualfiedNameParser',index: 'LengthString',result: 'QualfiedNameResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'QualfiedNameParser',index: 'LengthString') -> 'bool':
        result: 'QualfiedNameResult' = QualfiedNameResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'QualfiedNameParser',index: 'LengthString',list_result: 'QualfiedNameListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[QualfiedName]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'QualfiedNameResult' = QualfiedNameResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'QualfiedNameParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'QualfiedNameListResult' = QualfiedNameListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class QualfiedNameResult:
    def __init__(self: 'QualfiedNameResult'):
        self.value: QualfiedName = None
        self.result: bool = False

    def SetValue(self: 'QualfiedNameResult',new_value: 'QualfiedName') -> 'None':
        self.value = new_value

    def GetValue(self: 'QualfiedNameResult') -> 'QualfiedName':
        return self.value

    def SetResult(self: 'QualfiedNameResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'QualfiedNameResult') -> 'bool':
        return self.result

class QualfiedNameListResult:
    def __init__(self: 'QualfiedNameListResult'):
        self.value: list[QualfiedName] = []
        self.result: bool = False

    def SetValue(self: 'QualfiedNameListResult',new_value: 'list[QualfiedName]') -> 'None':
        self.value = new_value

    def GetValue(self: 'QualfiedNameListResult') -> 'list[QualfiedName]':
        return self.value

    def SetResult(self: 'QualfiedNameListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'QualfiedNameListResult') -> 'bool':
        return self.result

class QualfiedName:
    def __init__(self: 'QualfiedName'):
        self.length_string: LengthString = None
        self.name_field: Name = None
        self.tail_field: NameTail = None

    def SetLengthString(self: 'QualfiedName',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'QualfiedName') -> 'str':
        return self.length_string.GetString()

    def SetName(self: 'QualfiedName',input_value: 'Name') -> 'None':
        self.name_field = input_value

    def GetName(self: 'QualfiedName') -> 'Name':
        return self.name_field

    def SetTail(self: 'QualfiedName',input_value: 'NameTail') -> 'None':
        self.tail_field = input_value

    def GetTail(self: 'QualfiedName') -> 'NameTail':
        return self.tail_field

class NameTailParser:
    def __init__(self: 'NameTailParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'NameTailParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'NameTailParser',index: 'LengthString',result: 'NameTailResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'NameTail' = NameTail()
        name_field: 'NameResult' = NameResult()
        tail_field: 'NameTailResult' = NameTailResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and string_parser_instance.ParseSingle(index,".") and name_parser_instance.ParseSingleSave(index,name_field) and name_tail_parser_instance.ParseOptionalSave(index,tail_field):
            instance.SetName(name_field.GetValue())
            instance.SetTail(tail_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            name_field = NameResult()
            tail_field = NameTailResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'NameTailParser',index: 'LengthString') -> 'bool':
        result: 'NameTailResult' = NameTailResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'NameTailParser',index: 'LengthString',result: 'NameTailResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'NameTailParser',index: 'LengthString') -> 'bool':
        result: 'NameTailResult' = NameTailResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'NameTailParser',index: 'LengthString',list_result: 'NameTailListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[NameTail]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'NameTailResult' = NameTailResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'NameTailParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'NameTailListResult' = NameTailListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class NameTailResult:
    def __init__(self: 'NameTailResult'):
        self.value: NameTail = None
        self.result: bool = False

    def SetValue(self: 'NameTailResult',new_value: 'NameTail') -> 'None':
        self.value = new_value

    def GetValue(self: 'NameTailResult') -> 'NameTail':
        return self.value

    def SetResult(self: 'NameTailResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'NameTailResult') -> 'bool':
        return self.result

class NameTailListResult:
    def __init__(self: 'NameTailListResult'):
        self.value: list[NameTail] = []
        self.result: bool = False

    def SetValue(self: 'NameTailListResult',new_value: 'list[NameTail]') -> 'None':
        self.value = new_value

    def GetValue(self: 'NameTailListResult') -> 'list[NameTail]':
        return self.value

    def SetResult(self: 'NameTailListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'NameTailListResult') -> 'bool':
        return self.result

class NameTail:
    def __init__(self: 'NameTail'):
        self.length_string: LengthString = None
        self.name_field: Name = None
        self.tail_field: NameTail = None

    def SetLengthString(self: 'NameTail',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'NameTail') -> 'str':
        return self.length_string.GetString()

    def SetName(self: 'NameTail',input_value: 'Name') -> 'None':
        self.name_field = input_value

    def GetName(self: 'NameTail') -> 'Name':
        return self.name_field

    def SetTail(self: 'NameTail',input_value: 'NameTail') -> 'None':
        self.tail_field = input_value

    def GetTail(self: 'NameTail') -> 'NameTail':
        return self.tail_field

class NameParser:
    def __init__(self: 'NameParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'NameParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'NameParser',index: 'LengthString',result: 'NameResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'Name' = Name()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and name_character_parser_instance.ParseMany(index,1,-1):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'NameParser',index: 'LengthString') -> 'bool':
        result: 'NameResult' = NameResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'NameParser',index: 'LengthString',result: 'NameResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'NameParser',index: 'LengthString') -> 'bool':
        result: 'NameResult' = NameResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'NameParser',index: 'LengthString',list_result: 'NameListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[Name]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'NameResult' = NameResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'NameParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'NameListResult' = NameListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class NameResult:
    def __init__(self: 'NameResult'):
        self.value: Name = None
        self.result: bool = False

    def SetValue(self: 'NameResult',new_value: 'Name') -> 'None':
        self.value = new_value

    def GetValue(self: 'NameResult') -> 'Name':
        return self.value

    def SetResult(self: 'NameResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'NameResult') -> 'bool':
        return self.result

class NameListResult:
    def __init__(self: 'NameListResult'):
        self.value: list[Name] = []
        self.result: bool = False

    def SetValue(self: 'NameListResult',new_value: 'list[Name]') -> 'None':
        self.value = new_value

    def GetValue(self: 'NameListResult') -> 'list[Name]':
        return self.value

    def SetResult(self: 'NameListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'NameListResult') -> 'bool':
        return self.result

class Name:
    def __init__(self: 'Name'):
        self.length_string: LengthString = None

    def SetLengthString(self: 'Name',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'Name') -> 'str':
        return self.length_string.GetString()

class NameCharacterParser:
    def __init__(self: 'NameCharacterParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'NameCharacterParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'NameCharacterParser',index: 'LengthString',result: 'NameCharacterResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'NameCharacter' = NameCharacter()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and character_range_parser_instance.ParseSingle(index,0x30,0x39):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        if True and character_range_parser_instance.ParseSingle(index,0x41,0x5A):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        if True and string_parser_instance.ParseSingle(index,"_"):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        if True and character_range_parser_instance.ParseSingle(index,0x61,0x7A):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'NameCharacterParser',index: 'LengthString') -> 'bool':
        result: 'NameCharacterResult' = NameCharacterResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'NameCharacterParser',index: 'LengthString',result: 'NameCharacterResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'NameCharacterParser',index: 'LengthString') -> 'bool':
        result: 'NameCharacterResult' = NameCharacterResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'NameCharacterParser',index: 'LengthString',list_result: 'NameCharacterListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[NameCharacter]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'NameCharacterResult' = NameCharacterResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'NameCharacterParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'NameCharacterListResult' = NameCharacterListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class NameCharacterResult:
    def __init__(self: 'NameCharacterResult'):
        self.value: NameCharacter = None
        self.result: bool = False

    def SetValue(self: 'NameCharacterResult',new_value: 'NameCharacter') -> 'None':
        self.value = new_value

    def GetValue(self: 'NameCharacterResult') -> 'NameCharacter':
        return self.value

    def SetResult(self: 'NameCharacterResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'NameCharacterResult') -> 'bool':
        return self.result

class NameCharacterListResult:
    def __init__(self: 'NameCharacterListResult'):
        self.value: list[NameCharacter] = []
        self.result: bool = False

    def SetValue(self: 'NameCharacterListResult',new_value: 'list[NameCharacter]') -> 'None':
        self.value = new_value

    def GetValue(self: 'NameCharacterListResult') -> 'list[NameCharacter]':
        return self.value

    def SetResult(self: 'NameCharacterListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'NameCharacterListResult') -> 'bool':
        return self.result

class NameCharacter:
    def __init__(self: 'NameCharacter'):
        self.length_string: LengthString = None

    def SetLengthString(self: 'NameCharacter',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'NameCharacter') -> 'str':
        return self.length_string.GetString()

class BooleanParser:
    def __init__(self: 'BooleanParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'BooleanParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'BooleanParser',index: 'LengthString',result: 'BooleanResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'Boolean' = Boolean()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and string_parser_instance.ParseSingle(index,"true"):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        if True and string_parser_instance.ParseSingle(index,"false"):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'BooleanParser',index: 'LengthString') -> 'bool':
        result: 'BooleanResult' = BooleanResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'BooleanParser',index: 'LengthString',result: 'BooleanResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'BooleanParser',index: 'LengthString') -> 'bool':
        result: 'BooleanResult' = BooleanResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'BooleanParser',index: 'LengthString',list_result: 'BooleanListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[Boolean]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'BooleanResult' = BooleanResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'BooleanParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'BooleanListResult' = BooleanListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class BooleanResult:
    def __init__(self: 'BooleanResult'):
        self.value: Boolean = None
        self.result: bool = False

    def SetValue(self: 'BooleanResult',new_value: 'Boolean') -> 'None':
        self.value = new_value

    def GetValue(self: 'BooleanResult') -> 'Boolean':
        return self.value

    def SetResult(self: 'BooleanResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'BooleanResult') -> 'bool':
        return self.result

class BooleanListResult:
    def __init__(self: 'BooleanListResult'):
        self.value: list[Boolean] = []
        self.result: bool = False

    def SetValue(self: 'BooleanListResult',new_value: 'list[Boolean]') -> 'None':
        self.value = new_value

    def GetValue(self: 'BooleanListResult') -> 'list[Boolean]':
        return self.value

    def SetResult(self: 'BooleanListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'BooleanListResult') -> 'bool':
        return self.result

class Boolean:
    def __init__(self: 'Boolean'):
        self.length_string: LengthString = None

    def SetLengthString(self: 'Boolean',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'Boolean') -> 'str':
        return self.length_string.GetString()

class ByteParser:
    def __init__(self: 'ByteParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'ByteParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'ByteParser',index: 'LengthString',result: 'ByteResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'Byte' = Byte()
        high_field: 'ByteDigitResult' = ByteDigitResult()
        low_field: 'ByteDigitResult' = ByteDigitResult()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and string_parser_instance.ParseSingle(index,"0x") and byte_digit_parser_instance.ParseSingleSave(index,high_field) and byte_digit_parser_instance.ParseSingleSave(index,low_field):
            instance.SetHigh(high_field.GetValue())
            instance.SetLow(low_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            high_field = ByteDigitResult()
            low_field = ByteDigitResult()
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'ByteParser',index: 'LengthString') -> 'bool':
        result: 'ByteResult' = ByteResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'ByteParser',index: 'LengthString',result: 'ByteResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'ByteParser',index: 'LengthString') -> 'bool':
        result: 'ByteResult' = ByteResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'ByteParser',index: 'LengthString',list_result: 'ByteListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[Byte]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'ByteResult' = ByteResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'ByteParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'ByteListResult' = ByteListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class ByteResult:
    def __init__(self: 'ByteResult'):
        self.value: Byte = None
        self.result: bool = False

    def SetValue(self: 'ByteResult',new_value: 'Byte') -> 'None':
        self.value = new_value

    def GetValue(self: 'ByteResult') -> 'Byte':
        return self.value

    def SetResult(self: 'ByteResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'ByteResult') -> 'bool':
        return self.result

class ByteListResult:
    def __init__(self: 'ByteListResult'):
        self.value: list[Byte] = []
        self.result: bool = False

    def SetValue(self: 'ByteListResult',new_value: 'list[Byte]') -> 'None':
        self.value = new_value

    def GetValue(self: 'ByteListResult') -> 'list[Byte]':
        return self.value

    def SetResult(self: 'ByteListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'ByteListResult') -> 'bool':
        return self.result

class Byte:
    def __init__(self: 'Byte'):
        self.length_string: LengthString = None
        self.high_field: ByteDigit = None
        self.low_field: ByteDigit = None

    def SetLengthString(self: 'Byte',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'Byte') -> 'str':
        return self.length_string.GetString()

    def SetHigh(self: 'Byte',input_value: 'ByteDigit') -> 'None':
        self.high_field = input_value

    def GetHigh(self: 'Byte') -> 'ByteDigit':
        return self.high_field

    def SetLow(self: 'Byte',input_value: 'ByteDigit') -> 'None':
        self.low_field = input_value

    def GetLow(self: 'Byte') -> 'ByteDigit':
        return self.low_field

class ByteDigitParser:
    def __init__(self: 'ByteDigitParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'ByteDigitParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'ByteDigitParser',index: 'LengthString',result: 'ByteDigitResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'ByteDigit' = ByteDigit()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and character_range_parser_instance.ParseSingle(index,0x30,0x39):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        if True and character_range_parser_instance.ParseSingle(index,0x41,0x46):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'ByteDigitParser',index: 'LengthString') -> 'bool':
        result: 'ByteDigitResult' = ByteDigitResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'ByteDigitParser',index: 'LengthString',result: 'ByteDigitResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'ByteDigitParser',index: 'LengthString') -> 'bool':
        result: 'ByteDigitResult' = ByteDigitResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'ByteDigitParser',index: 'LengthString',list_result: 'ByteDigitListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[ByteDigit]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'ByteDigitResult' = ByteDigitResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'ByteDigitParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'ByteDigitListResult' = ByteDigitListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class ByteDigitResult:
    def __init__(self: 'ByteDigitResult'):
        self.value: ByteDigit = None
        self.result: bool = False

    def SetValue(self: 'ByteDigitResult',new_value: 'ByteDigit') -> 'None':
        self.value = new_value

    def GetValue(self: 'ByteDigitResult') -> 'ByteDigit':
        return self.value

    def SetResult(self: 'ByteDigitResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'ByteDigitResult') -> 'bool':
        return self.result

class ByteDigitListResult:
    def __init__(self: 'ByteDigitListResult'):
        self.value: list[ByteDigit] = []
        self.result: bool = False

    def SetValue(self: 'ByteDigitListResult',new_value: 'list[ByteDigit]') -> 'None':
        self.value = new_value

    def GetValue(self: 'ByteDigitListResult') -> 'list[ByteDigit]':
        return self.value

    def SetResult(self: 'ByteDigitListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'ByteDigitListResult') -> 'bool':
        return self.result

class ByteDigit:
    def __init__(self: 'ByteDigit'):
        self.length_string: LengthString = None

    def SetLengthString(self: 'ByteDigit',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'ByteDigit') -> 'str':
        return self.length_string.GetString()

class NegativeParser:
    def __init__(self: 'NegativeParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'NegativeParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'NegativeParser',index: 'LengthString',result: 'NegativeResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'Negative' = Negative()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and string_parser_instance.ParseSingle(index,"-"):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'NegativeParser',index: 'LengthString') -> 'bool':
        result: 'NegativeResult' = NegativeResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'NegativeParser',index: 'LengthString',result: 'NegativeResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'NegativeParser',index: 'LengthString') -> 'bool':
        result: 'NegativeResult' = NegativeResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'NegativeParser',index: 'LengthString',list_result: 'NegativeListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[Negative]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'NegativeResult' = NegativeResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'NegativeParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'NegativeListResult' = NegativeListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class NegativeResult:
    def __init__(self: 'NegativeResult'):
        self.value: Negative = None
        self.result: bool = False

    def SetValue(self: 'NegativeResult',new_value: 'Negative') -> 'None':
        self.value = new_value

    def GetValue(self: 'NegativeResult') -> 'Negative':
        return self.value

    def SetResult(self: 'NegativeResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'NegativeResult') -> 'bool':
        return self.result

class NegativeListResult:
    def __init__(self: 'NegativeListResult'):
        self.value: list[Negative] = []
        self.result: bool = False

    def SetValue(self: 'NegativeListResult',new_value: 'list[Negative]') -> 'None':
        self.value = new_value

    def GetValue(self: 'NegativeListResult') -> 'list[Negative]':
        return self.value

    def SetResult(self: 'NegativeListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'NegativeListResult') -> 'bool':
        return self.result

class Negative:
    def __init__(self: 'Negative'):
        self.length_string: LengthString = None

    def SetLengthString(self: 'Negative',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'Negative') -> 'str':
        return self.length_string.GetString()

class DecimalParser:
    def __init__(self: 'DecimalParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'DecimalParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'DecimalParser',index: 'LengthString',result: 'DecimalResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'Decimal' = Decimal()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and negative_parser_instance.ParseOptional(index) and number_parser_instance.ParseSingle(index) and string_parser_instance.ParseSingle(index,".") and number_parser_instance.ParseSingle(index):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'DecimalParser',index: 'LengthString') -> 'bool':
        result: 'DecimalResult' = DecimalResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'DecimalParser',index: 'LengthString',result: 'DecimalResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'DecimalParser',index: 'LengthString') -> 'bool':
        result: 'DecimalResult' = DecimalResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'DecimalParser',index: 'LengthString',list_result: 'DecimalListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[Decimal]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'DecimalResult' = DecimalResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'DecimalParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'DecimalListResult' = DecimalListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class DecimalResult:
    def __init__(self: 'DecimalResult'):
        self.value: Decimal = None
        self.result: bool = False

    def SetValue(self: 'DecimalResult',new_value: 'Decimal') -> 'None':
        self.value = new_value

    def GetValue(self: 'DecimalResult') -> 'Decimal':
        return self.value

    def SetResult(self: 'DecimalResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'DecimalResult') -> 'bool':
        return self.result

class DecimalListResult:
    def __init__(self: 'DecimalListResult'):
        self.value: list[Decimal] = []
        self.result: bool = False

    def SetValue(self: 'DecimalListResult',new_value: 'list[Decimal]') -> 'None':
        self.value = new_value

    def GetValue(self: 'DecimalListResult') -> 'list[Decimal]':
        return self.value

    def SetResult(self: 'DecimalListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'DecimalListResult') -> 'bool':
        return self.result

class Decimal:
    def __init__(self: 'Decimal'):
        self.length_string: LengthString = None

    def SetLengthString(self: 'Decimal',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'Decimal') -> 'str':
        return self.length_string.GetString()

class NumberParser:
    def __init__(self: 'NumberParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'NumberParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'NumberParser',index: 'LengthString',result: 'NumberResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'Number' = Number()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and negative_parser_instance.ParseOptional(index) and digit_parser_instance.ParseMany(index,1,-1):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'NumberParser',index: 'LengthString') -> 'bool':
        result: 'NumberResult' = NumberResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'NumberParser',index: 'LengthString',result: 'NumberResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'NumberParser',index: 'LengthString') -> 'bool':
        result: 'NumberResult' = NumberResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'NumberParser',index: 'LengthString',list_result: 'NumberListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[Number]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'NumberResult' = NumberResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'NumberParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'NumberListResult' = NumberListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class NumberResult:
    def __init__(self: 'NumberResult'):
        self.value: Number = None
        self.result: bool = False

    def SetValue(self: 'NumberResult',new_value: 'Number') -> 'None':
        self.value = new_value

    def GetValue(self: 'NumberResult') -> 'Number':
        return self.value

    def SetResult(self: 'NumberResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'NumberResult') -> 'bool':
        return self.result

class NumberListResult:
    def __init__(self: 'NumberListResult'):
        self.value: list[Number] = []
        self.result: bool = False

    def SetValue(self: 'NumberListResult',new_value: 'list[Number]') -> 'None':
        self.value = new_value

    def GetValue(self: 'NumberListResult') -> 'list[Number]':
        return self.value

    def SetResult(self: 'NumberListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'NumberListResult') -> 'bool':
        return self.result

class Number:
    def __init__(self: 'Number'):
        self.length_string: LengthString = None

    def SetLengthString(self: 'Number',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'Number') -> 'str':
        return self.length_string.GetString()

class DigitParser:
    def __init__(self: 'DigitParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'DigitParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'DigitParser',index: 'LengthString',result: 'DigitResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'Digit' = Digit()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and character_range_parser_instance.ParseSingle(index,0x30,0x39):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'DigitParser',index: 'LengthString') -> 'bool':
        result: 'DigitResult' = DigitResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'DigitParser',index: 'LengthString',result: 'DigitResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'DigitParser',index: 'LengthString') -> 'bool':
        result: 'DigitResult' = DigitResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'DigitParser',index: 'LengthString',list_result: 'DigitListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[Digit]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'DigitResult' = DigitResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'DigitParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'DigitListResult' = DigitListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class DigitResult:
    def __init__(self: 'DigitResult'):
        self.value: Digit = None
        self.result: bool = False

    def SetValue(self: 'DigitResult',new_value: 'Digit') -> 'None':
        self.value = new_value

    def GetValue(self: 'DigitResult') -> 'Digit':
        return self.value

    def SetResult(self: 'DigitResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'DigitResult') -> 'bool':
        return self.result

class DigitListResult:
    def __init__(self: 'DigitListResult'):
        self.value: list[Digit] = []
        self.result: bool = False

    def SetValue(self: 'DigitListResult',new_value: 'list[Digit]') -> 'None':
        self.value = new_value

    def GetValue(self: 'DigitListResult') -> 'list[Digit]':
        return self.value

    def SetResult(self: 'DigitListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'DigitListResult') -> 'bool':
        return self.result

class Digit:
    def __init__(self: 'Digit'):
        self.length_string: LengthString = None

    def SetLengthString(self: 'Digit',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'Digit') -> 'str':
        return self.length_string.GetString()

class LiteralParser:
    def __init__(self: 'LiteralParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'LiteralParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'LiteralParser',index: 'LengthString',result: 'LiteralResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'Literal' = Literal()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and literal_character_parser_instance.ParseMany(index,0,-1):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'LiteralParser',index: 'LengthString') -> 'bool':
        result: 'LiteralResult' = LiteralResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'LiteralParser',index: 'LengthString',result: 'LiteralResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'LiteralParser',index: 'LengthString') -> 'bool':
        result: 'LiteralResult' = LiteralResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'LiteralParser',index: 'LengthString',list_result: 'LiteralListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[Literal]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'LiteralResult' = LiteralResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'LiteralParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'LiteralListResult' = LiteralListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class LiteralResult:
    def __init__(self: 'LiteralResult'):
        self.value: Literal = None
        self.result: bool = False

    def SetValue(self: 'LiteralResult',new_value: 'Literal') -> 'None':
        self.value = new_value

    def GetValue(self: 'LiteralResult') -> 'Literal':
        return self.value

    def SetResult(self: 'LiteralResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'LiteralResult') -> 'bool':
        return self.result

class LiteralListResult:
    def __init__(self: 'LiteralListResult'):
        self.value: list[Literal] = []
        self.result: bool = False

    def SetValue(self: 'LiteralListResult',new_value: 'list[Literal]') -> 'None':
        self.value = new_value

    def GetValue(self: 'LiteralListResult') -> 'list[Literal]':
        return self.value

    def SetResult(self: 'LiteralListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'LiteralListResult') -> 'bool':
        return self.result

class Literal:
    def __init__(self: 'Literal'):
        self.length_string: LengthString = None

    def SetLengthString(self: 'Literal',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'Literal') -> 'str':
        return self.length_string.GetString()

class LiteralCharacterParser:
    def __init__(self: 'LiteralCharacterParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'LiteralCharacterParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'LiteralCharacterParser',index: 'LengthString',result: 'LiteralCharacterResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'LiteralCharacter' = LiteralCharacter()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and character_range_parser_instance.ParseSingle(index,0x00,0x21):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        if True and string_parser_instance.ParseSingle(index,"\\\""):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        if True and character_range_parser_instance.ParseSingle(index,0x23,0x5B):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        if True and string_parser_instance.ParseSingle(index,"\\\\"):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        if True and character_range_parser_instance.ParseSingle(index,0x5D,0xFF):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'LiteralCharacterParser',index: 'LengthString') -> 'bool':
        result: 'LiteralCharacterResult' = LiteralCharacterResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'LiteralCharacterParser',index: 'LengthString',result: 'LiteralCharacterResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'LiteralCharacterParser',index: 'LengthString') -> 'bool':
        result: 'LiteralCharacterResult' = LiteralCharacterResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'LiteralCharacterParser',index: 'LengthString',list_result: 'LiteralCharacterListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[LiteralCharacter]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'LiteralCharacterResult' = LiteralCharacterResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'LiteralCharacterParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'LiteralCharacterListResult' = LiteralCharacterListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class LiteralCharacterResult:
    def __init__(self: 'LiteralCharacterResult'):
        self.value: LiteralCharacter = None
        self.result: bool = False

    def SetValue(self: 'LiteralCharacterResult',new_value: 'LiteralCharacter') -> 'None':
        self.value = new_value

    def GetValue(self: 'LiteralCharacterResult') -> 'LiteralCharacter':
        return self.value

    def SetResult(self: 'LiteralCharacterResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'LiteralCharacterResult') -> 'bool':
        return self.result

class LiteralCharacterListResult:
    def __init__(self: 'LiteralCharacterListResult'):
        self.value: list[LiteralCharacter] = []
        self.result: bool = False

    def SetValue(self: 'LiteralCharacterListResult',new_value: 'list[LiteralCharacter]') -> 'None':
        self.value = new_value

    def GetValue(self: 'LiteralCharacterListResult') -> 'list[LiteralCharacter]':
        return self.value

    def SetResult(self: 'LiteralCharacterListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'LiteralCharacterListResult') -> 'bool':
        return self.result

class LiteralCharacter:
    def __init__(self: 'LiteralCharacter'):
        self.length_string: LengthString = None

    def SetLengthString(self: 'LiteralCharacter',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'LiteralCharacter') -> 'str':
        return self.length_string.GetString()

class WhitespaceParser:
    def __init__(self: 'WhitespaceParser'):
        self.parser_network: ParserNetwork = None

    def SetParserNetwork(self: 'WhitespaceParser',input: 'ParserNetwork') -> 'None':
        self.parser_network = input

    def ParseSingleSave(self: 'WhitespaceParser',index: 'LengthString',result: 'WhitespaceResult') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        consumed_string: 'LengthString' = LengthString()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance: 'Whitespace' = Whitespace()
        c_t_code_file_parser_instance: 'CTCodeFileParser' = self.parser_network.GetCTCodeFileParser()
        external_definition_parser_instance: 'ExternalDefinitionParser' = self.parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance: 'UnmanagedTypeParser' = self.parser_network.GetUnmanagedTypeParser()
        definition_parser_instance: 'DefinitionParser' = self.parser_network.GetDefinitionParser()
        interface_def_parser_instance: 'InterfaceDefParser' = self.parser_network.GetInterfaceDefParser()
        class_def_parser_instance: 'ClassDefParser' = self.parser_network.GetClassDefParser()
        implementation_spec_parser_instance: 'ImplementationSpecParser' = self.parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance: 'ContentDeclarationParser' = self.parser_network.GetContentDeclarationParser()
        content_definition_parser_instance: 'ContentDefinitionParser' = self.parser_network.GetContentDefinitionParser()
        primative_type_parser_instance: 'PrimativeTypeParser' = self.parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance: 'DefinedTypeParser' = self.parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance: 'SingletonTypeParser' = self.parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance: 'DimensionalNoteParser' = self.parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance: 'DimensionalTypeParser' = self.parser_network.GetDimensionalTypeParser()
        map_note_parser_instance: 'MapNoteParser' = self.parser_network.GetMapNoteParser()
        map_type_parser_instance: 'MapTypeParser' = self.parser_network.GetMapTypeParser()
        value_type_parser_instance: 'ValueTypeParser' = self.parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance: 'ParameterListDefParser' = self.parser_network.GetParameterListDefParser()
        parameter_list_parser_instance: 'ParameterListParser' = self.parser_network.GetParameterListParser()
        code_block_parser_instance: 'CodeBlockParser' = self.parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance: 'DeclarationAssignParser' = self.parser_network.GetDeclarationAssignParser()
        declaration_parser_instance: 'DeclarationParser' = self.parser_network.GetDeclarationParser()
        assignment_parser_instance: 'AssignmentParser' = self.parser_network.GetAssignmentParser()
        return_parser_instance: 'ReturnParser' = self.parser_network.GetReturnParser()
        else_tail_parser_instance: 'ElseTailParser' = self.parser_network.GetElseTailParser()
        conditional_parser_instance: 'ConditionalParser' = self.parser_network.GetConditionalParser()
        loop_parser_instance: 'LoopParser' = self.parser_network.GetLoopParser()
        call_parser_instance: 'CallParser' = self.parser_network.GetCallParser()
        allocate_parser_instance: 'AllocateParser' = self.parser_network.GetAllocateParser()
        instruction_parser_instance: 'InstructionParser' = self.parser_network.GetInstructionParser()
        r_value_single_parser_instance: 'RValueSingleParser' = self.parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance: 'RValueTailParser' = self.parser_network.GetRValueTailParser()
        r_value_parser_instance: 'RValueParser' = self.parser_network.GetRValueParser()
        binary_operator_parser_instance: 'BinaryOperatorParser' = self.parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance: 'UnaryOperatorParser' = self.parser_network.GetUnaryOperatorParser()
        comment_parser_instance: 'CommentParser' = self.parser_network.GetCommentParser()
        non_star_character_parser_instance: 'NonStarCharacterParser' = self.parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance: 'NonSlashCharacterParser' = self.parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance: 'CommentContentParser' = self.parser_network.GetCommentContentParser()
        qualfied_name_parser_instance: 'QualfiedNameParser' = self.parser_network.GetQualfiedNameParser()
        name_tail_parser_instance: 'NameTailParser' = self.parser_network.GetNameTailParser()
        name_parser_instance: 'NameParser' = self.parser_network.GetNameParser()
        name_character_parser_instance: 'NameCharacterParser' = self.parser_network.GetNameCharacterParser()
        boolean_parser_instance: 'BooleanParser' = self.parser_network.GetBooleanParser()
        byte_parser_instance: 'ByteParser' = self.parser_network.GetByteParser()
        byte_digit_parser_instance: 'ByteDigitParser' = self.parser_network.GetByteDigitParser()
        negative_parser_instance: 'NegativeParser' = self.parser_network.GetNegativeParser()
        decimal_parser_instance: 'DecimalParser' = self.parser_network.GetDecimalParser()
        number_parser_instance: 'NumberParser' = self.parser_network.GetNumberParser()
        digit_parser_instance: 'DigitParser' = self.parser_network.GetDigitParser()
        literal_parser_instance: 'LiteralParser' = self.parser_network.GetLiteralParser()
        literal_character_parser_instance: 'LiteralCharacterParser' = self.parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance: 'WhitespaceParser' = self.parser_network.GetWhitespaceParser()
        string_parser_instance: 'StringParser' = self.parser_network.GetStringParser()
        character_parser_instance: 'CharacterParser' = self.parser_network.GetCharacterParser()
        character_range_parser_instance: 'CharacterRangeParser' = self.parser_network.GetCharacterRangeParser()
        if True and character_range_parser_instance.ParseSingle(index,0x00,0x20):
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(True)
            return result.GetResult()
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
        result.SetResult(False)
        return result.GetResult()

    def ParseSingle(self: 'WhitespaceParser',index: 'LengthString') -> 'bool':
        result: 'WhitespaceResult' = WhitespaceResult()
        return self.ParseSingleSave(index,result)

    def ParseOptionalSave(self: 'WhitespaceParser',index: 'LengthString',result: 'WhitespaceResult') -> 'bool':
        self.ParseSingleSave(index,result)
        result.SetResult(True)
        return True

    def ParseOptional(self: 'WhitespaceParser',index: 'LengthString') -> 'bool':
        result: 'WhitespaceResult' = WhitespaceResult()
        return self.ParseOptionalSave(index,result)

    def ParseManySave(self: 'WhitespaceParser',index: 'LengthString',list_result: 'WhitespaceListResult',minimum: 'int',maximum: 'int') -> 'bool':
        index_start: 'int' = index.GetStart()
        index_length: 'int' = index.GetLength()
        results: 'list[Whitespace]' = []
        count: 'int' = 0
        max_check: 'int' = maximum
        check_next: 'bool' = True
        if maximum<0:
            max_check = count+1
        while check_next and count<max_check:
            result: 'WhitespaceResult' = WhitespaceResult()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if result.GetResult():
                count = count+1
                Append(results,result.GetValue())
            if maximum<0:
                max_check = count+1
        if count>=minimum and count<=max_check:
            list_result.SetValue(results)
            list_result.SetResult(True)
        else:
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(False)
        return list_result.GetResult()

    def ParseMany(self: 'WhitespaceParser',index: 'LengthString',minimum: 'int',maximum: 'int') -> 'bool':
        result: 'WhitespaceListResult' = WhitespaceListResult()
        return self.ParseManySave(index,result,minimum,maximum)

class WhitespaceResult:
    def __init__(self: 'WhitespaceResult'):
        self.value: Whitespace = None
        self.result: bool = False

    def SetValue(self: 'WhitespaceResult',new_value: 'Whitespace') -> 'None':
        self.value = new_value

    def GetValue(self: 'WhitespaceResult') -> 'Whitespace':
        return self.value

    def SetResult(self: 'WhitespaceResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'WhitespaceResult') -> 'bool':
        return self.result

class WhitespaceListResult:
    def __init__(self: 'WhitespaceListResult'):
        self.value: list[Whitespace] = []
        self.result: bool = False

    def SetValue(self: 'WhitespaceListResult',new_value: 'list[Whitespace]') -> 'None':
        self.value = new_value

    def GetValue(self: 'WhitespaceListResult') -> 'list[Whitespace]':
        return self.value

    def SetResult(self: 'WhitespaceListResult',new_result: 'bool') -> 'None':
        self.result = new_result

    def GetResult(self: 'WhitespaceListResult') -> 'bool':
        return self.result

class Whitespace:
    def __init__(self: 'Whitespace'):
        self.length_string: LengthString = None

    def SetLengthString(self: 'Whitespace',new_value: 'LengthString') -> 'None':
        self.length_string = LengthString()
        self.length_string.SetData(new_value.GetData())
        self.length_string.SetStart(new_value.GetStart())
        self.length_string.SetLength(new_value.GetLength())

    def UnParse(self: 'Whitespace') -> 'str':
        return self.length_string.GetString()

