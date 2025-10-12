def ClearList(input); input.clear(); end
def Size(input); return input.length(); end
def Element(input, element); return input[element]; end
def Append(input, element); input.push(element); end
def ClearMap(input); input.clear(); end
def SetKV(input, key, element); input[key] = element; end
def Keys(input); return input.keys(); end
def HasKV(input, key); return input.has_key?(key); end
def GetKV(input, key); return input[key]; end
def Length(input); return input.length(); end
def At(input, index); return input[index]; end
def IntAt(input, index); return input[index].ord(); end
def Concat(left, right); return left + right; end

module S84
module CTCODE
module DBNF
module CTCODE

class StringParser
    def initialize()
    end

    def ParseSingleSave(index, value, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        index_data = index.GetData()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = ReservedPrefixString.new()
        value_length = Length(value)
        if (value_length>index.GetLength())
            result.SetResult(false)
            return false
        end
        offset_index = 0
        while (offset_index<value_length)
            if (index_data.GetAt(index.GetStart()+offset_index)!=At(value,offset_index))
                result.SetResult(false)
                return false
            end
            offset_index = offset_index+1
        end
        index.SetStart(index.GetStart()+value_length)
        index.SetLength(index.GetLength()-value_length)
        consumed_string.SetLength(index.GetStart()-index_start)
        instance.SetLengthString(consumed_string)
        result.SetValue(instance)
        result.SetResult(true)
        return true
    end

    def ParseSingle(index, value)
        result = StringResult.new()
        return self.ParseSingleSave(index,value,result)
    end
end

class StringResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class StringListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class ReservedPrefixString
    def initialize()
        @length_string = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end
end

class CharacterParser
    def initialize()
    end

    def ParseSingle(index, value)
        if (0==index.GetLength())
            return false
        end
        index_data = index.GetData()
        current_character = index_data.GetIntAt(index.GetStart())
        if (current_character==value)
            index.SetStart(index.GetStart()+1)
            index.SetLength(index.GetLength()-1)
            return true
        end
        return false
    end
end

class CharacterResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class CharacterListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class Character
    def initialize()
        @length_string = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end
end

class CharacterRangeParser
    def initialize()
    end

    def ParseSingle(index, low_value, high_value)
        if (0==index.GetLength())
            return false
        end
        index_data = index.GetData()
        current_character = index_data.GetIntAt(index.GetStart())
        if (low_value<=current_character && current_character<=high_value)
            index.SetStart(index.GetStart()+1)
            index.SetLength(index.GetLength()-1)
            return true
        end
        return false
    end
end

class CharacterRangeResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class CharacterRangeListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class CharacterRange
    def initialize()
        @length_string = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end
end

class ParserNetwork
    def initialize()
        @c_t_code_file_parser_field = nil
        @external_definition_parser_field = nil
        @unmanaged_type_parser_field = nil
        @definition_parser_field = nil
        @interface_def_parser_field = nil
        @class_def_parser_field = nil
        @implementation_spec_parser_field = nil
        @content_declaration_parser_field = nil
        @content_definition_parser_field = nil
        @primative_type_parser_field = nil
        @defined_type_parser_field = nil
        @singleton_type_parser_field = nil
        @dimensional_note_parser_field = nil
        @dimensional_type_parser_field = nil
        @map_note_parser_field = nil
        @map_type_parser_field = nil
        @value_type_parser_field = nil
        @parameter_list_def_parser_field = nil
        @parameter_list_parser_field = nil
        @code_block_parser_field = nil
        @declaration_assign_parser_field = nil
        @declaration_parser_field = nil
        @assignment_parser_field = nil
        @return_parser_field = nil
        @else_tail_parser_field = nil
        @conditional_parser_field = nil
        @loop_parser_field = nil
        @call_parser_field = nil
        @allocate_parser_field = nil
        @instruction_parser_field = nil
        @r_value_single_parser_field = nil
        @r_value_tail_parser_field = nil
        @r_value_parser_field = nil
        @binary_operator_parser_field = nil
        @unary_operator_parser_field = nil
        @comment_parser_field = nil
        @non_star_character_parser_field = nil
        @non_slash_character_parser_field = nil
        @comment_content_parser_field = nil
        @qualfied_name_parser_field = nil
        @name_tail_parser_field = nil
        @name_parser_field = nil
        @name_character_parser_field = nil
        @boolean_parser_field = nil
        @byte_parser_field = nil
        @byte_digit_parser_field = nil
        @negative_parser_field = nil
        @decimal_parser_field = nil
        @number_parser_field = nil
        @digit_parser_field = nil
        @literal_parser_field = nil
        @literal_character_parser_field = nil
        @whitespace_parser_field = nil
        @string_parser_field = nil
        @character_parser_field = nil
        @character_range_parser_field = nil
    end

    def GetCTCodeFileParser()
        return @c_t_code_file_parser_field
    end

    def GetExternalDefinitionParser()
        return @external_definition_parser_field
    end

    def GetUnmanagedTypeParser()
        return @unmanaged_type_parser_field
    end

    def GetDefinitionParser()
        return @definition_parser_field
    end

    def GetInterfaceDefParser()
        return @interface_def_parser_field
    end

    def GetClassDefParser()
        return @class_def_parser_field
    end

    def GetImplementationSpecParser()
        return @implementation_spec_parser_field
    end

    def GetContentDeclarationParser()
        return @content_declaration_parser_field
    end

    def GetContentDefinitionParser()
        return @content_definition_parser_field
    end

    def GetPrimativeTypeParser()
        return @primative_type_parser_field
    end

    def GetDefinedTypeParser()
        return @defined_type_parser_field
    end

    def GetSingletonTypeParser()
        return @singleton_type_parser_field
    end

    def GetDimensionalNoteParser()
        return @dimensional_note_parser_field
    end

    def GetDimensionalTypeParser()
        return @dimensional_type_parser_field
    end

    def GetMapNoteParser()
        return @map_note_parser_field
    end

    def GetMapTypeParser()
        return @map_type_parser_field
    end

    def GetValueTypeParser()
        return @value_type_parser_field
    end

    def GetParameterListDefParser()
        return @parameter_list_def_parser_field
    end

    def GetParameterListParser()
        return @parameter_list_parser_field
    end

    def GetCodeBlockParser()
        return @code_block_parser_field
    end

    def GetDeclarationAssignParser()
        return @declaration_assign_parser_field
    end

    def GetDeclarationParser()
        return @declaration_parser_field
    end

    def GetAssignmentParser()
        return @assignment_parser_field
    end

    def GetReturnParser()
        return @return_parser_field
    end

    def GetElseTailParser()
        return @else_tail_parser_field
    end

    def GetConditionalParser()
        return @conditional_parser_field
    end

    def GetLoopParser()
        return @loop_parser_field
    end

    def GetCallParser()
        return @call_parser_field
    end

    def GetAllocateParser()
        return @allocate_parser_field
    end

    def GetInstructionParser()
        return @instruction_parser_field
    end

    def GetRValueSingleParser()
        return @r_value_single_parser_field
    end

    def GetRValueTailParser()
        return @r_value_tail_parser_field
    end

    def GetRValueParser()
        return @r_value_parser_field
    end

    def GetBinaryOperatorParser()
        return @binary_operator_parser_field
    end

    def GetUnaryOperatorParser()
        return @unary_operator_parser_field
    end

    def GetCommentParser()
        return @comment_parser_field
    end

    def GetNonStarCharacterParser()
        return @non_star_character_parser_field
    end

    def GetNonSlashCharacterParser()
        return @non_slash_character_parser_field
    end

    def GetCommentContentParser()
        return @comment_content_parser_field
    end

    def GetQualfiedNameParser()
        return @qualfied_name_parser_field
    end

    def GetNameTailParser()
        return @name_tail_parser_field
    end

    def GetNameParser()
        return @name_parser_field
    end

    def GetNameCharacterParser()
        return @name_character_parser_field
    end

    def GetBooleanParser()
        return @boolean_parser_field
    end

    def GetByteParser()
        return @byte_parser_field
    end

    def GetByteDigitParser()
        return @byte_digit_parser_field
    end

    def GetNegativeParser()
        return @negative_parser_field
    end

    def GetDecimalParser()
        return @decimal_parser_field
    end

    def GetNumberParser()
        return @number_parser_field
    end

    def GetDigitParser()
        return @digit_parser_field
    end

    def GetLiteralParser()
        return @literal_parser_field
    end

    def GetLiteralCharacterParser()
        return @literal_character_parser_field
    end

    def GetWhitespaceParser()
        return @whitespace_parser_field
    end

    def GetStringParser()
        return @string_parser_field
    end

    def GetCharacterParser()
        return @character_parser_field
    end

    def GetCharacterRangeParser()
        return @character_range_parser_field
    end

    def Initialize()
        @c_t_code_file_parser_field = CTCodeFileParser.new()
        @c_t_code_file_parser_field.SetParserNetwork(self)
        @external_definition_parser_field = ExternalDefinitionParser.new()
        @external_definition_parser_field.SetParserNetwork(self)
        @unmanaged_type_parser_field = UnmanagedTypeParser.new()
        @unmanaged_type_parser_field.SetParserNetwork(self)
        @definition_parser_field = DefinitionParser.new()
        @definition_parser_field.SetParserNetwork(self)
        @interface_def_parser_field = InterfaceDefParser.new()
        @interface_def_parser_field.SetParserNetwork(self)
        @class_def_parser_field = ClassDefParser.new()
        @class_def_parser_field.SetParserNetwork(self)
        @implementation_spec_parser_field = ImplementationSpecParser.new()
        @implementation_spec_parser_field.SetParserNetwork(self)
        @content_declaration_parser_field = ContentDeclarationParser.new()
        @content_declaration_parser_field.SetParserNetwork(self)
        @content_definition_parser_field = ContentDefinitionParser.new()
        @content_definition_parser_field.SetParserNetwork(self)
        @primative_type_parser_field = PrimativeTypeParser.new()
        @primative_type_parser_field.SetParserNetwork(self)
        @defined_type_parser_field = DefinedTypeParser.new()
        @defined_type_parser_field.SetParserNetwork(self)
        @singleton_type_parser_field = SingletonTypeParser.new()
        @singleton_type_parser_field.SetParserNetwork(self)
        @dimensional_note_parser_field = DimensionalNoteParser.new()
        @dimensional_note_parser_field.SetParserNetwork(self)
        @dimensional_type_parser_field = DimensionalTypeParser.new()
        @dimensional_type_parser_field.SetParserNetwork(self)
        @map_note_parser_field = MapNoteParser.new()
        @map_note_parser_field.SetParserNetwork(self)
        @map_type_parser_field = MapTypeParser.new()
        @map_type_parser_field.SetParserNetwork(self)
        @value_type_parser_field = ValueTypeParser.new()
        @value_type_parser_field.SetParserNetwork(self)
        @parameter_list_def_parser_field = ParameterListDefParser.new()
        @parameter_list_def_parser_field.SetParserNetwork(self)
        @parameter_list_parser_field = ParameterListParser.new()
        @parameter_list_parser_field.SetParserNetwork(self)
        @code_block_parser_field = CodeBlockParser.new()
        @code_block_parser_field.SetParserNetwork(self)
        @declaration_assign_parser_field = DeclarationAssignParser.new()
        @declaration_assign_parser_field.SetParserNetwork(self)
        @declaration_parser_field = DeclarationParser.new()
        @declaration_parser_field.SetParserNetwork(self)
        @assignment_parser_field = AssignmentParser.new()
        @assignment_parser_field.SetParserNetwork(self)
        @return_parser_field = ReturnParser.new()
        @return_parser_field.SetParserNetwork(self)
        @else_tail_parser_field = ElseTailParser.new()
        @else_tail_parser_field.SetParserNetwork(self)
        @conditional_parser_field = ConditionalParser.new()
        @conditional_parser_field.SetParserNetwork(self)
        @loop_parser_field = LoopParser.new()
        @loop_parser_field.SetParserNetwork(self)
        @call_parser_field = CallParser.new()
        @call_parser_field.SetParserNetwork(self)
        @allocate_parser_field = AllocateParser.new()
        @allocate_parser_field.SetParserNetwork(self)
        @instruction_parser_field = InstructionParser.new()
        @instruction_parser_field.SetParserNetwork(self)
        @r_value_single_parser_field = RValueSingleParser.new()
        @r_value_single_parser_field.SetParserNetwork(self)
        @r_value_tail_parser_field = RValueTailParser.new()
        @r_value_tail_parser_field.SetParserNetwork(self)
        @r_value_parser_field = RValueParser.new()
        @r_value_parser_field.SetParserNetwork(self)
        @binary_operator_parser_field = BinaryOperatorParser.new()
        @binary_operator_parser_field.SetParserNetwork(self)
        @unary_operator_parser_field = UnaryOperatorParser.new()
        @unary_operator_parser_field.SetParserNetwork(self)
        @comment_parser_field = CommentParser.new()
        @comment_parser_field.SetParserNetwork(self)
        @non_star_character_parser_field = NonStarCharacterParser.new()
        @non_star_character_parser_field.SetParserNetwork(self)
        @non_slash_character_parser_field = NonSlashCharacterParser.new()
        @non_slash_character_parser_field.SetParserNetwork(self)
        @comment_content_parser_field = CommentContentParser.new()
        @comment_content_parser_field.SetParserNetwork(self)
        @qualfied_name_parser_field = QualfiedNameParser.new()
        @qualfied_name_parser_field.SetParserNetwork(self)
        @name_tail_parser_field = NameTailParser.new()
        @name_tail_parser_field.SetParserNetwork(self)
        @name_parser_field = NameParser.new()
        @name_parser_field.SetParserNetwork(self)
        @name_character_parser_field = NameCharacterParser.new()
        @name_character_parser_field.SetParserNetwork(self)
        @boolean_parser_field = BooleanParser.new()
        @boolean_parser_field.SetParserNetwork(self)
        @byte_parser_field = ByteParser.new()
        @byte_parser_field.SetParserNetwork(self)
        @byte_digit_parser_field = ByteDigitParser.new()
        @byte_digit_parser_field.SetParserNetwork(self)
        @negative_parser_field = NegativeParser.new()
        @negative_parser_field.SetParserNetwork(self)
        @decimal_parser_field = DecimalParser.new()
        @decimal_parser_field.SetParserNetwork(self)
        @number_parser_field = NumberParser.new()
        @number_parser_field.SetParserNetwork(self)
        @digit_parser_field = DigitParser.new()
        @digit_parser_field.SetParserNetwork(self)
        @literal_parser_field = LiteralParser.new()
        @literal_parser_field.SetParserNetwork(self)
        @literal_character_parser_field = LiteralCharacterParser.new()
        @literal_character_parser_field.SetParserNetwork(self)
        @whitespace_parser_field = WhitespaceParser.new()
        @whitespace_parser_field.SetParserNetwork(self)
        @string_parser_field = StringParser.new()
        @character_parser_field = CharacterParser.new()
        @character_range_parser_field = CharacterRangeParser.new()
    end
end

class DBNFOmniType
    def initialize()
        @c_t_code_file_field = nil
        @external_definition_field = nil
        @unmanaged_type_field = nil
        @definition_field = nil
        @interface_def_field = nil
        @class_def_field = nil
        @implementation_spec_field = nil
        @content_declaration_field = nil
        @content_definition_field = nil
        @primative_type_field = nil
        @defined_type_field = nil
        @singleton_type_field = nil
        @dimensional_note_field = nil
        @dimensional_type_field = nil
        @map_note_field = nil
        @map_type_field = nil
        @value_type_field = nil
        @parameter_list_def_field = nil
        @parameter_list_field = nil
        @code_block_field = nil
        @declaration_assign_field = nil
        @declaration_field = nil
        @assignment_field = nil
        @return_field = nil
        @else_tail_field = nil
        @conditional_field = nil
        @loop_field = nil
        @call_field = nil
        @allocate_field = nil
        @instruction_field = nil
        @r_value_single_field = nil
        @r_value_tail_field = nil
        @r_value_field = nil
        @binary_operator_field = nil
        @unary_operator_field = nil
        @comment_field = nil
        @non_star_character_field = nil
        @non_slash_character_field = nil
        @comment_content_field = nil
        @qualfied_name_field = nil
        @name_tail_field = nil
        @name_field = nil
        @name_character_field = nil
        @boolean_field = nil
        @byte_field = nil
        @byte_digit_field = nil
        @negative_field = nil
        @decimal_field = nil
        @number_field = nil
        @digit_field = nil
        @literal_field = nil
        @literal_character_field = nil
        @whitespace_field = nil
    end

    def SetCTCodeFile(input_value)
        @c_t_code_file_field = input_value
    end

    def GetCTCodeFile()
        return @c_t_code_file_field
    end

    def SetExternalDefinition(input_value)
        @external_definition_field = input_value
    end

    def GetExternalDefinition()
        return @external_definition_field
    end

    def SetUnmanagedType(input_value)
        @unmanaged_type_field = input_value
    end

    def GetUnmanagedType()
        return @unmanaged_type_field
    end

    def SetDefinition(input_value)
        @definition_field = input_value
    end

    def GetDefinition()
        return @definition_field
    end

    def SetInterfaceDef(input_value)
        @interface_def_field = input_value
    end

    def GetInterfaceDef()
        return @interface_def_field
    end

    def SetClassDef(input_value)
        @class_def_field = input_value
    end

    def GetClassDef()
        return @class_def_field
    end

    def SetImplementationSpec(input_value)
        @implementation_spec_field = input_value
    end

    def GetImplementationSpec()
        return @implementation_spec_field
    end

    def SetContentDeclaration(input_value)
        @content_declaration_field = input_value
    end

    def GetContentDeclaration()
        return @content_declaration_field
    end

    def SetContentDefinition(input_value)
        @content_definition_field = input_value
    end

    def GetContentDefinition()
        return @content_definition_field
    end

    def SetPrimativeType(input_value)
        @primative_type_field = input_value
    end

    def GetPrimativeType()
        return @primative_type_field
    end

    def SetDefinedType(input_value)
        @defined_type_field = input_value
    end

    def GetDefinedType()
        return @defined_type_field
    end

    def SetSingletonType(input_value)
        @singleton_type_field = input_value
    end

    def GetSingletonType()
        return @singleton_type_field
    end

    def SetDimensionalNote(input_value)
        @dimensional_note_field = input_value
    end

    def GetDimensionalNote()
        return @dimensional_note_field
    end

    def SetDimensionalType(input_value)
        @dimensional_type_field = input_value
    end

    def GetDimensionalType()
        return @dimensional_type_field
    end

    def SetMapNote(input_value)
        @map_note_field = input_value
    end

    def GetMapNote()
        return @map_note_field
    end

    def SetMapType(input_value)
        @map_type_field = input_value
    end

    def GetMapType()
        return @map_type_field
    end

    def SetValueType(input_value)
        @value_type_field = input_value
    end

    def GetValueType()
        return @value_type_field
    end

    def SetParameterListDef(input_value)
        @parameter_list_def_field = input_value
    end

    def GetParameterListDef()
        return @parameter_list_def_field
    end

    def SetParameterList(input_value)
        @parameter_list_field = input_value
    end

    def GetParameterList()
        return @parameter_list_field
    end

    def SetCodeBlock(input_value)
        @code_block_field = input_value
    end

    def GetCodeBlock()
        return @code_block_field
    end

    def SetDeclarationAssign(input_value)
        @declaration_assign_field = input_value
    end

    def GetDeclarationAssign()
        return @declaration_assign_field
    end

    def SetDeclaration(input_value)
        @declaration_field = input_value
    end

    def GetDeclaration()
        return @declaration_field
    end

    def SetAssignment(input_value)
        @assignment_field = input_value
    end

    def GetAssignment()
        return @assignment_field
    end

    def SetReturn(input_value)
        @return_field = input_value
    end

    def GetReturn()
        return @return_field
    end

    def SetElseTail(input_value)
        @else_tail_field = input_value
    end

    def GetElseTail()
        return @else_tail_field
    end

    def SetConditional(input_value)
        @conditional_field = input_value
    end

    def GetConditional()
        return @conditional_field
    end

    def SetLoop(input_value)
        @loop_field = input_value
    end

    def GetLoop()
        return @loop_field
    end

    def SetCall(input_value)
        @call_field = input_value
    end

    def GetCall()
        return @call_field
    end

    def SetAllocate(input_value)
        @allocate_field = input_value
    end

    def GetAllocate()
        return @allocate_field
    end

    def SetInstruction(input_value)
        @instruction_field = input_value
    end

    def GetInstruction()
        return @instruction_field
    end

    def SetRValueSingle(input_value)
        @r_value_single_field = input_value
    end

    def GetRValueSingle()
        return @r_value_single_field
    end

    def SetRValueTail(input_value)
        @r_value_tail_field = input_value
    end

    def GetRValueTail()
        return @r_value_tail_field
    end

    def SetRValue(input_value)
        @r_value_field = input_value
    end

    def GetRValue()
        return @r_value_field
    end

    def SetBinaryOperator(input_value)
        @binary_operator_field = input_value
    end

    def GetBinaryOperator()
        return @binary_operator_field
    end

    def SetUnaryOperator(input_value)
        @unary_operator_field = input_value
    end

    def GetUnaryOperator()
        return @unary_operator_field
    end

    def SetComment(input_value)
        @comment_field = input_value
    end

    def GetComment()
        return @comment_field
    end

    def SetNonStarCharacter(input_value)
        @non_star_character_field = input_value
    end

    def GetNonStarCharacter()
        return @non_star_character_field
    end

    def SetNonSlashCharacter(input_value)
        @non_slash_character_field = input_value
    end

    def GetNonSlashCharacter()
        return @non_slash_character_field
    end

    def SetCommentContent(input_value)
        @comment_content_field = input_value
    end

    def GetCommentContent()
        return @comment_content_field
    end

    def SetQualfiedName(input_value)
        @qualfied_name_field = input_value
    end

    def GetQualfiedName()
        return @qualfied_name_field
    end

    def SetNameTail(input_value)
        @name_tail_field = input_value
    end

    def GetNameTail()
        return @name_tail_field
    end

    def SetName(input_value)
        @name_field = input_value
    end

    def GetName()
        return @name_field
    end

    def SetNameCharacter(input_value)
        @name_character_field = input_value
    end

    def GetNameCharacter()
        return @name_character_field
    end

    def SetBoolean(input_value)
        @boolean_field = input_value
    end

    def GetBoolean()
        return @boolean_field
    end

    def SetByte(input_value)
        @byte_field = input_value
    end

    def GetByte()
        return @byte_field
    end

    def SetByteDigit(input_value)
        @byte_digit_field = input_value
    end

    def GetByteDigit()
        return @byte_digit_field
    end

    def SetNegative(input_value)
        @negative_field = input_value
    end

    def GetNegative()
        return @negative_field
    end

    def SetDecimal(input_value)
        @decimal_field = input_value
    end

    def GetDecimal()
        return @decimal_field
    end

    def SetNumber(input_value)
        @number_field = input_value
    end

    def GetNumber()
        return @number_field
    end

    def SetDigit(input_value)
        @digit_field = input_value
    end

    def GetDigit()
        return @digit_field
    end

    def SetLiteral(input_value)
        @literal_field = input_value
    end

    def GetLiteral()
        return @literal_field
    end

    def SetLiteralCharacter(input_value)
        @literal_character_field = input_value
    end

    def GetLiteralCharacter()
        return @literal_character_field
    end

    def SetWhitespace(input_value)
        @whitespace_field = input_value
    end

    def GetWhitespace()
        return @whitespace_field
    end
end

class DBNFOmniTypeResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end

    def SetCTCodeFile(input_value)
        @value = DBNFOmniType.new()
        @value.SetCTCodeFile(input_value)
    end

    def SetExternalDefinition(input_value)
        @value = DBNFOmniType.new()
        @value.SetExternalDefinition(input_value)
    end

    def SetUnmanagedType(input_value)
        @value = DBNFOmniType.new()
        @value.SetUnmanagedType(input_value)
    end

    def SetDefinition(input_value)
        @value = DBNFOmniType.new()
        @value.SetDefinition(input_value)
    end

    def SetInterfaceDef(input_value)
        @value = DBNFOmniType.new()
        @value.SetInterfaceDef(input_value)
    end

    def SetClassDef(input_value)
        @value = DBNFOmniType.new()
        @value.SetClassDef(input_value)
    end

    def SetImplementationSpec(input_value)
        @value = DBNFOmniType.new()
        @value.SetImplementationSpec(input_value)
    end

    def SetContentDeclaration(input_value)
        @value = DBNFOmniType.new()
        @value.SetContentDeclaration(input_value)
    end

    def SetContentDefinition(input_value)
        @value = DBNFOmniType.new()
        @value.SetContentDefinition(input_value)
    end

    def SetPrimativeType(input_value)
        @value = DBNFOmniType.new()
        @value.SetPrimativeType(input_value)
    end

    def SetDefinedType(input_value)
        @value = DBNFOmniType.new()
        @value.SetDefinedType(input_value)
    end

    def SetSingletonType(input_value)
        @value = DBNFOmniType.new()
        @value.SetSingletonType(input_value)
    end

    def SetDimensionalNote(input_value)
        @value = DBNFOmniType.new()
        @value.SetDimensionalNote(input_value)
    end

    def SetDimensionalType(input_value)
        @value = DBNFOmniType.new()
        @value.SetDimensionalType(input_value)
    end

    def SetMapNote(input_value)
        @value = DBNFOmniType.new()
        @value.SetMapNote(input_value)
    end

    def SetMapType(input_value)
        @value = DBNFOmniType.new()
        @value.SetMapType(input_value)
    end

    def SetValueType(input_value)
        @value = DBNFOmniType.new()
        @value.SetValueType(input_value)
    end

    def SetParameterListDef(input_value)
        @value = DBNFOmniType.new()
        @value.SetParameterListDef(input_value)
    end

    def SetParameterList(input_value)
        @value = DBNFOmniType.new()
        @value.SetParameterList(input_value)
    end

    def SetCodeBlock(input_value)
        @value = DBNFOmniType.new()
        @value.SetCodeBlock(input_value)
    end

    def SetDeclarationAssign(input_value)
        @value = DBNFOmniType.new()
        @value.SetDeclarationAssign(input_value)
    end

    def SetDeclaration(input_value)
        @value = DBNFOmniType.new()
        @value.SetDeclaration(input_value)
    end

    def SetAssignment(input_value)
        @value = DBNFOmniType.new()
        @value.SetAssignment(input_value)
    end

    def SetReturn(input_value)
        @value = DBNFOmniType.new()
        @value.SetReturn(input_value)
    end

    def SetElseTail(input_value)
        @value = DBNFOmniType.new()
        @value.SetElseTail(input_value)
    end

    def SetConditional(input_value)
        @value = DBNFOmniType.new()
        @value.SetConditional(input_value)
    end

    def SetLoop(input_value)
        @value = DBNFOmniType.new()
        @value.SetLoop(input_value)
    end

    def SetCall(input_value)
        @value = DBNFOmniType.new()
        @value.SetCall(input_value)
    end

    def SetAllocate(input_value)
        @value = DBNFOmniType.new()
        @value.SetAllocate(input_value)
    end

    def SetInstruction(input_value)
        @value = DBNFOmniType.new()
        @value.SetInstruction(input_value)
    end

    def SetRValueSingle(input_value)
        @value = DBNFOmniType.new()
        @value.SetRValueSingle(input_value)
    end

    def SetRValueTail(input_value)
        @value = DBNFOmniType.new()
        @value.SetRValueTail(input_value)
    end

    def SetRValue(input_value)
        @value = DBNFOmniType.new()
        @value.SetRValue(input_value)
    end

    def SetBinaryOperator(input_value)
        @value = DBNFOmniType.new()
        @value.SetBinaryOperator(input_value)
    end

    def SetUnaryOperator(input_value)
        @value = DBNFOmniType.new()
        @value.SetUnaryOperator(input_value)
    end

    def SetComment(input_value)
        @value = DBNFOmniType.new()
        @value.SetComment(input_value)
    end

    def SetNonStarCharacter(input_value)
        @value = DBNFOmniType.new()
        @value.SetNonStarCharacter(input_value)
    end

    def SetNonSlashCharacter(input_value)
        @value = DBNFOmniType.new()
        @value.SetNonSlashCharacter(input_value)
    end

    def SetCommentContent(input_value)
        @value = DBNFOmniType.new()
        @value.SetCommentContent(input_value)
    end

    def SetQualfiedName(input_value)
        @value = DBNFOmniType.new()
        @value.SetQualfiedName(input_value)
    end

    def SetNameTail(input_value)
        @value = DBNFOmniType.new()
        @value.SetNameTail(input_value)
    end

    def SetName(input_value)
        @value = DBNFOmniType.new()
        @value.SetName(input_value)
    end

    def SetNameCharacter(input_value)
        @value = DBNFOmniType.new()
        @value.SetNameCharacter(input_value)
    end

    def SetBoolean(input_value)
        @value = DBNFOmniType.new()
        @value.SetBoolean(input_value)
    end

    def SetByte(input_value)
        @value = DBNFOmniType.new()
        @value.SetByte(input_value)
    end

    def SetByteDigit(input_value)
        @value = DBNFOmniType.new()
        @value.SetByteDigit(input_value)
    end

    def SetNegative(input_value)
        @value = DBNFOmniType.new()
        @value.SetNegative(input_value)
    end

    def SetDecimal(input_value)
        @value = DBNFOmniType.new()
        @value.SetDecimal(input_value)
    end

    def SetNumber(input_value)
        @value = DBNFOmniType.new()
        @value.SetNumber(input_value)
    end

    def SetDigit(input_value)
        @value = DBNFOmniType.new()
        @value.SetDigit(input_value)
    end

    def SetLiteral(input_value)
        @value = DBNFOmniType.new()
        @value.SetLiteral(input_value)
    end

    def SetLiteralCharacter(input_value)
        @value = DBNFOmniType.new()
        @value.SetLiteralCharacter(input_value)
    end

    def SetWhitespace(input_value)
        @value = DBNFOmniType.new()
        @value.SetWhitespace(input_value)
    end
end

class DBNFOmniTypeListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end

    def SetCTCodeFile(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetCTCodeFile(Element(input_value,index))
            index = index+1
        end
    end

    def SetExternalDefinition(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetExternalDefinition(Element(input_value,index))
            index = index+1
        end
    end

    def SetUnmanagedType(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetUnmanagedType(Element(input_value,index))
            index = index+1
        end
    end

    def SetDefinition(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetDefinition(Element(input_value,index))
            index = index+1
        end
    end

    def SetInterfaceDef(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetInterfaceDef(Element(input_value,index))
            index = index+1
        end
    end

    def SetClassDef(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetClassDef(Element(input_value,index))
            index = index+1
        end
    end

    def SetImplementationSpec(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetImplementationSpec(Element(input_value,index))
            index = index+1
        end
    end

    def SetContentDeclaration(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetContentDeclaration(Element(input_value,index))
            index = index+1
        end
    end

    def SetContentDefinition(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetContentDefinition(Element(input_value,index))
            index = index+1
        end
    end

    def SetPrimativeType(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetPrimativeType(Element(input_value,index))
            index = index+1
        end
    end

    def SetDefinedType(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetDefinedType(Element(input_value,index))
            index = index+1
        end
    end

    def SetSingletonType(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetSingletonType(Element(input_value,index))
            index = index+1
        end
    end

    def SetDimensionalNote(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetDimensionalNote(Element(input_value,index))
            index = index+1
        end
    end

    def SetDimensionalType(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetDimensionalType(Element(input_value,index))
            index = index+1
        end
    end

    def SetMapNote(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetMapNote(Element(input_value,index))
            index = index+1
        end
    end

    def SetMapType(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetMapType(Element(input_value,index))
            index = index+1
        end
    end

    def SetValueType(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetValueType(Element(input_value,index))
            index = index+1
        end
    end

    def SetParameterListDef(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetParameterListDef(Element(input_value,index))
            index = index+1
        end
    end

    def SetParameterList(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetParameterList(Element(input_value,index))
            index = index+1
        end
    end

    def SetCodeBlock(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetCodeBlock(Element(input_value,index))
            index = index+1
        end
    end

    def SetDeclarationAssign(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetDeclarationAssign(Element(input_value,index))
            index = index+1
        end
    end

    def SetDeclaration(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetDeclaration(Element(input_value,index))
            index = index+1
        end
    end

    def SetAssignment(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetAssignment(Element(input_value,index))
            index = index+1
        end
    end

    def SetReturn(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetReturn(Element(input_value,index))
            index = index+1
        end
    end

    def SetElseTail(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetElseTail(Element(input_value,index))
            index = index+1
        end
    end

    def SetConditional(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetConditional(Element(input_value,index))
            index = index+1
        end
    end

    def SetLoop(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetLoop(Element(input_value,index))
            index = index+1
        end
    end

    def SetCall(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetCall(Element(input_value,index))
            index = index+1
        end
    end

    def SetAllocate(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetAllocate(Element(input_value,index))
            index = index+1
        end
    end

    def SetInstruction(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetInstruction(Element(input_value,index))
            index = index+1
        end
    end

    def SetRValueSingle(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetRValueSingle(Element(input_value,index))
            index = index+1
        end
    end

    def SetRValueTail(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetRValueTail(Element(input_value,index))
            index = index+1
        end
    end

    def SetRValue(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetRValue(Element(input_value,index))
            index = index+1
        end
    end

    def SetBinaryOperator(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetBinaryOperator(Element(input_value,index))
            index = index+1
        end
    end

    def SetUnaryOperator(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetUnaryOperator(Element(input_value,index))
            index = index+1
        end
    end

    def SetComment(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetComment(Element(input_value,index))
            index = index+1
        end
    end

    def SetNonStarCharacter(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetNonStarCharacter(Element(input_value,index))
            index = index+1
        end
    end

    def SetNonSlashCharacter(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetNonSlashCharacter(Element(input_value,index))
            index = index+1
        end
    end

    def SetCommentContent(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetCommentContent(Element(input_value,index))
            index = index+1
        end
    end

    def SetQualfiedName(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetQualfiedName(Element(input_value,index))
            index = index+1
        end
    end

    def SetNameTail(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetNameTail(Element(input_value,index))
            index = index+1
        end
    end

    def SetName(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetName(Element(input_value,index))
            index = index+1
        end
    end

    def SetNameCharacter(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetNameCharacter(Element(input_value,index))
            index = index+1
        end
    end

    def SetBoolean(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetBoolean(Element(input_value,index))
            index = index+1
        end
    end

    def SetByte(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetByte(Element(input_value,index))
            index = index+1
        end
    end

    def SetByteDigit(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetByteDigit(Element(input_value,index))
            index = index+1
        end
    end

    def SetNegative(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetNegative(Element(input_value,index))
            index = index+1
        end
    end

    def SetDecimal(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetDecimal(Element(input_value,index))
            index = index+1
        end
    end

    def SetNumber(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetNumber(Element(input_value,index))
            index = index+1
        end
    end

    def SetDigit(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetDigit(Element(input_value,index))
            index = index+1
        end
    end

    def SetLiteral(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetLiteral(Element(input_value,index))
            index = index+1
        end
    end

    def SetLiteralCharacter(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetLiteralCharacter(Element(input_value,index))
            index = index+1
        end
    end

    def SetWhitespace(input_value)
        index = 0
        while (index<Size(input_value))
            value = DBNFOmniType.new()
            value.SetWhitespace(Element(input_value,index))
            index = index+1
        end
    end
end

class LargeString
    def initialize()
        @data = ""
    end

    def SetData(new_data)
        @data = new_data
    end

    def GetData()
        return @data
    end

    def GetIntAt(offset)
        return IntAt(@data,offset)
    end

    def GetAt(offset)
        return At(@data,offset)
    end
end

class LengthString
    def initialize()
        @data = nil
        @start = 0
        @length = 0
    end

    def SetData(new_data)
        @data = new_data
    end

    def GetData()
        return @data
    end

    def SetStart(new_start)
        @start = new_start
    end

    def GetStart()
        return @start
    end

    def SetLength(new_length)
        @length = new_length
    end

    def GetLength()
        return @length
    end

    def GetString()
        deep_data = @data.GetData()
        result = ""
        index = @start
        reserved_prefix_end = @start+@length
        while (index<reserved_prefix_end)
            result = Concat(result,At(deep_data,index))
            index = index+1
        end
        return result
    end
end

class CTCodeFileParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = CTCodeFile.new()
        declarations_field = ExternalDefinitionListResult.new()
        definitions_field = DefinitionListResult.new()
        unmanaged_types_field = UnmanagedTypeListResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && external_definition_parser_instance.ParseManySave(index,declarations_field,0,-1) && unmanaged_type_parser_instance.ParseManySave(index,unmanaged_types_field,0,-1) && definition_parser_instance.ParseManySave(index,definitions_field,0,-1))
            instance.SetDeclarations(declarations_field.GetValue())
            instance.SetDefinitions(definitions_field.GetValue())
            instance.SetUnmanagedTypes(unmanaged_types_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            declarations_field = ExternalDefinitionListResult.new()
            definitions_field = DefinitionListResult.new()
            unmanaged_types_field = UnmanagedTypeListResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = CTCodeFileResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = CTCodeFileResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = CTCodeFileResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = CTCodeFileListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class CTCodeFileResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class CTCodeFileListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class CTCodeFile
    def initialize()
        @length_string = nil
        @declarations_field = Array.new()
        @definitions_field = Array.new()
        @unmanaged_types_field = Array.new()
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetDeclarations(input_value)
        @declarations_field = input_value
    end

    def GetDeclarations()
        return @declarations_field
    end

    def SetDefinitions(input_value)
        @definitions_field = input_value
    end

    def GetDefinitions()
        return @definitions_field
    end

    def SetUnmanagedTypes(input_value)
        @unmanaged_types_field = input_value
    end

    def GetUnmanagedTypes()
        return @unmanaged_types_field
    end
end

class ExternalDefinitionParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = ExternalDefinition.new()
        exdef_field = QualfiedNameResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && string_parser_instance.ParseSingle(index,"exdef") && whitespace_parser_instance.ParseMany(index,0,-1) && qualfied_name_parser_instance.ParseSingleSave(index,exdef_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,";") && whitespace_parser_instance.ParseMany(index,0,-1))
            instance.SetExdef(exdef_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            exdef_field = QualfiedNameResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = ExternalDefinitionResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = ExternalDefinitionResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = ExternalDefinitionResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = ExternalDefinitionListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class ExternalDefinitionResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class ExternalDefinitionListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class ExternalDefinition
    def initialize()
        @length_string = nil
        @exdef_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetExdef(input_value)
        @exdef_field = input_value
    end

    def GetExdef()
        return @exdef_field
    end
end

class UnmanagedTypeParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = UnmanagedType.new()
        unmanaged_type_field = QualfiedNameResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && string_parser_instance.ParseSingle(index,"unmanaged") && whitespace_parser_instance.ParseMany(index,0,-1) && qualfied_name_parser_instance.ParseSingleSave(index,unmanaged_type_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,";") && whitespace_parser_instance.ParseMany(index,0,-1))
            instance.SetUnmanagedType(unmanaged_type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            unmanaged_type_field = QualfiedNameResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = UnmanagedTypeResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = UnmanagedTypeResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = UnmanagedTypeResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = UnmanagedTypeListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class UnmanagedTypeResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class UnmanagedTypeListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class UnmanagedType
    def initialize()
        @length_string = nil
        @unmanaged_type_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetUnmanagedType(input_value)
        @unmanaged_type_field = input_value
    end

    def GetUnmanagedType()
        return @unmanaged_type_field
    end
end

class DefinitionParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = Definition.new()
        class_def_field = ClassDefResult.new()
        interface_def_field = InterfaceDefResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && interface_def_parser_instance.ParseSingleSave(index,interface_def_field))
            instance.SetClassDef(class_def_field.GetValue())
            instance.SetInterfaceDef(interface_def_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            class_def_field = ClassDefResult.new()
            interface_def_field = InterfaceDefResult.new()
        end
        if (true && class_def_parser_instance.ParseSingleSave(index,class_def_field))
            instance.SetClassDef(class_def_field.GetValue())
            instance.SetInterfaceDef(interface_def_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            class_def_field = ClassDefResult.new()
            interface_def_field = InterfaceDefResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = DefinitionResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = DefinitionResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = DefinitionResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = DefinitionListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class DefinitionResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class DefinitionListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class Definition
    def initialize()
        @length_string = nil
        @class_def_field = nil
        @interface_def_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetClassDef(input_value)
        @class_def_field = input_value
    end

    def GetClassDef()
        return @class_def_field
    end

    def SetInterfaceDef(input_value)
        @interface_def_field = input_value
    end

    def GetInterfaceDef()
        return @interface_def_field
    end
end

class InterfaceDefParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = InterfaceDef.new()
        comment_field = CommentResult.new()
        declarations_field = ContentDeclarationListResult.new()
        name_field = NameResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && comment_parser_instance.ParseOptionalSave(index,comment_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"interface") && whitespace_parser_instance.ParseMany(index,1,-1) && name_parser_instance.ParseSingleSave(index,name_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"{") && whitespace_parser_instance.ParseMany(index,0,-1) && content_declaration_parser_instance.ParseManySave(index,declarations_field,0,-1) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"}") && whitespace_parser_instance.ParseMany(index,0,-1))
            instance.SetComment(comment_field.GetValue())
            instance.SetDeclarations(declarations_field.GetValue())
            instance.SetName(name_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            comment_field = CommentResult.new()
            declarations_field = ContentDeclarationListResult.new()
            name_field = NameResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = InterfaceDefResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = InterfaceDefResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = InterfaceDefResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = InterfaceDefListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class InterfaceDefResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class InterfaceDefListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class InterfaceDef
    def initialize()
        @length_string = nil
        @comment_field = nil
        @declarations_field = Array.new()
        @name_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetComment(input_value)
        @comment_field = input_value
    end

    def GetComment()
        return @comment_field
    end

    def SetDeclarations(input_value)
        @declarations_field = input_value
    end

    def GetDeclarations()
        return @declarations_field
    end

    def SetName(input_value)
        @name_field = input_value
    end

    def GetName()
        return @name_field
    end
end

class ClassDefParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = ClassDef.new()
        comment_field = CommentResult.new()
        definitions_field = ContentDefinitionListResult.new()
        implementing_field = ImplementationSpecResult.new()
        name_field = NameResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && comment_parser_instance.ParseOptionalSave(index,comment_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"class") && whitespace_parser_instance.ParseMany(index,1,-1) && name_parser_instance.ParseSingleSave(index,name_field) && implementation_spec_parser_instance.ParseOptionalSave(index,implementing_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"{") && whitespace_parser_instance.ParseMany(index,0,-1) && content_definition_parser_instance.ParseManySave(index,definitions_field,0,-1) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"}") && whitespace_parser_instance.ParseMany(index,0,-1))
            instance.SetComment(comment_field.GetValue())
            instance.SetDefinitions(definitions_field.GetValue())
            instance.SetImplementing(implementing_field.GetValue())
            instance.SetName(name_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            comment_field = CommentResult.new()
            definitions_field = ContentDefinitionListResult.new()
            implementing_field = ImplementationSpecResult.new()
            name_field = NameResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = ClassDefResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = ClassDefResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = ClassDefResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = ClassDefListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class ClassDefResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class ClassDefListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class ClassDef
    def initialize()
        @length_string = nil
        @comment_field = nil
        @definitions_field = Array.new()
        @implementing_field = nil
        @name_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetComment(input_value)
        @comment_field = input_value
    end

    def GetComment()
        return @comment_field
    end

    def SetDefinitions(input_value)
        @definitions_field = input_value
    end

    def GetDefinitions()
        return @definitions_field
    end

    def SetImplementing(input_value)
        @implementing_field = input_value
    end

    def GetImplementing()
        return @implementing_field
    end

    def SetName(input_value)
        @name_field = input_value
    end

    def GetName()
        return @name_field
    end
end

class ImplementationSpecParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = ImplementationSpec.new()
        interface_field = QualfiedNameResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,1,-1) && string_parser_instance.ParseSingle(index,"implements") && whitespace_parser_instance.ParseMany(index,1,-1) && qualfied_name_parser_instance.ParseSingleSave(index,interface_field) && whitespace_parser_instance.ParseMany(index,0,-1))
            instance.SetInterface(interface_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            interface_field = QualfiedNameResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = ImplementationSpecResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = ImplementationSpecResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = ImplementationSpecResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = ImplementationSpecListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class ImplementationSpecResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class ImplementationSpecListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class ImplementationSpec
    def initialize()
        @length_string = nil
        @interface_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetInterface(input_value)
        @interface_field = input_value
    end

    def GetInterface()
        return @interface_field
    end
end

class ContentDeclarationParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = ContentDeclaration.new()
        comment_field = CommentResult.new()
        name_field = NameResult.new()
        parameters_field = ParameterListDefResult.new()
        type_field = ValueTypeResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && comment_parser_instance.ParseOptionalSave(index,comment_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"function") && whitespace_parser_instance.ParseMany(index,1,-1) && value_type_parser_instance.ParseSingleSave(index,type_field) && whitespace_parser_instance.ParseMany(index,1,-1) && name_parser_instance.ParseSingleSave(index,name_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"(") && whitespace_parser_instance.ParseMany(index,0,-1) && parameter_list_def_parser_instance.ParseOptionalSave(index,parameters_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,")") && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,";") && whitespace_parser_instance.ParseMany(index,0,-1))
            instance.SetComment(comment_field.GetValue())
            instance.SetName(name_field.GetValue())
            instance.SetParameters(parameters_field.GetValue())
            instance.SetType(type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            comment_field = CommentResult.new()
            name_field = NameResult.new()
            parameters_field = ParameterListDefResult.new()
            type_field = ValueTypeResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = ContentDeclarationResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = ContentDeclarationResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = ContentDeclarationResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = ContentDeclarationListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class ContentDeclarationResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class ContentDeclarationListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class ContentDeclaration
    def initialize()
        @length_string = nil
        @comment_field = nil
        @name_field = nil
        @parameters_field = nil
        @type_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetComment(input_value)
        @comment_field = input_value
    end

    def GetComment()
        return @comment_field
    end

    def SetName(input_value)
        @name_field = input_value
    end

    def GetName()
        return @name_field
    end

    def SetParameters(input_value)
        @parameters_field = input_value
    end

    def GetParameters()
        return @parameters_field
    end

    def SetType(input_value)
        @type_field = input_value
    end

    def ReservedPrefixGetType()
        return @type_field
    end
end

class ContentDefinitionParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = ContentDefinition.new()
        comment_field = CommentResult.new()
        function_body_field = CodeBlockResult.new()
        name_field = NameResult.new()
        parameters_field = ParameterListDefResult.new()
        type_field = ValueTypeResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && comment_parser_instance.ParseOptionalSave(index,comment_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"function") && whitespace_parser_instance.ParseMany(index,1,-1) && value_type_parser_instance.ParseSingleSave(index,type_field) && whitespace_parser_instance.ParseMany(index,1,-1) && name_parser_instance.ParseSingleSave(index,name_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"(") && whitespace_parser_instance.ParseMany(index,0,-1) && parameter_list_def_parser_instance.ParseOptionalSave(index,parameters_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,")") && whitespace_parser_instance.ParseMany(index,0,-1) && code_block_parser_instance.ParseSingleSave(index,function_body_field) && whitespace_parser_instance.ParseMany(index,0,-1))
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
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            comment_field = CommentResult.new()
            function_body_field = CodeBlockResult.new()
            name_field = NameResult.new()
            parameters_field = ParameterListDefResult.new()
            type_field = ValueTypeResult.new()
        end
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && comment_parser_instance.ParseOptionalSave(index,comment_field) && whitespace_parser_instance.ParseMany(index,0,-1) && value_type_parser_instance.ParseSingleSave(index,type_field) && whitespace_parser_instance.ParseMany(index,1,-1) && name_parser_instance.ParseSingleSave(index,name_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,";") && whitespace_parser_instance.ParseMany(index,0,-1))
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
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            comment_field = CommentResult.new()
            function_body_field = CodeBlockResult.new()
            name_field = NameResult.new()
            parameters_field = ParameterListDefResult.new()
            type_field = ValueTypeResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = ContentDefinitionResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = ContentDefinitionResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = ContentDefinitionResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = ContentDefinitionListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class ContentDefinitionResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class ContentDefinitionListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class ContentDefinition
    def initialize()
        @length_string = nil
        @comment_field = nil
        @function_body_field = nil
        @name_field = nil
        @parameters_field = nil
        @type_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetComment(input_value)
        @comment_field = input_value
    end

    def GetComment()
        return @comment_field
    end

    def SetFunctionBody(input_value)
        @function_body_field = input_value
    end

    def GetFunctionBody()
        return @function_body_field
    end

    def SetName(input_value)
        @name_field = input_value
    end

    def GetName()
        return @name_field
    end

    def SetParameters(input_value)
        @parameters_field = input_value
    end

    def GetParameters()
        return @parameters_field
    end

    def SetType(input_value)
        @type_field = input_value
    end

    def ReservedPrefixGetType()
        return @type_field
    end
end

class PrimativeTypeParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = PrimativeType.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && string_parser_instance.ParseSingle(index,"int"))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        if (true && string_parser_instance.ParseSingle(index,"string"))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        if (true && string_parser_instance.ParseSingle(index,"bool"))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        if (true && string_parser_instance.ParseSingle(index,"float"))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        if (true && string_parser_instance.ParseSingle(index,"void"))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = PrimativeTypeResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = PrimativeTypeResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = PrimativeTypeResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = PrimativeTypeListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class PrimativeTypeResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class PrimativeTypeListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class PrimativeType
    def initialize()
        @length_string = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end
end

class DefinedTypeParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = DefinedType.new()
        name_field = QualfiedNameResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && qualfied_name_parser_instance.ParseSingleSave(index,name_field))
            instance.SetName(name_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            name_field = QualfiedNameResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = DefinedTypeResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = DefinedTypeResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = DefinedTypeResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = DefinedTypeListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class DefinedTypeResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class DefinedTypeListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class DefinedType
    def initialize()
        @length_string = nil
        @name_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetName(input_value)
        @name_field = input_value
    end

    def GetName()
        return @name_field
    end
end

class SingletonTypeParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = SingletonType.new()
        defined_type_field = DefinedTypeResult.new()
        primative_type_field = PrimativeTypeResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && primative_type_parser_instance.ParseSingleSave(index,primative_type_field))
            instance.SetDefinedType(defined_type_field.GetValue())
            instance.SetPrimativeType(primative_type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            defined_type_field = DefinedTypeResult.new()
            primative_type_field = PrimativeTypeResult.new()
        end
        if (true && defined_type_parser_instance.ParseSingleSave(index,defined_type_field))
            instance.SetDefinedType(defined_type_field.GetValue())
            instance.SetPrimativeType(primative_type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            defined_type_field = DefinedTypeResult.new()
            primative_type_field = PrimativeTypeResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = SingletonTypeResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = SingletonTypeResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = SingletonTypeResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = SingletonTypeListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class SingletonTypeResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class SingletonTypeListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class SingletonType
    def initialize()
        @length_string = nil
        @defined_type_field = nil
        @primative_type_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetDefinedType(input_value)
        @defined_type_field = input_value
    end

    def GetDefinedType()
        return @defined_type_field
    end

    def SetPrimativeType(input_value)
        @primative_type_field = input_value
    end

    def GetPrimativeType()
        return @primative_type_field
    end
end

class DimensionalNoteParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = DimensionalNote.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"[") && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"]"))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = DimensionalNoteResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = DimensionalNoteResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = DimensionalNoteResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = DimensionalNoteListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class DimensionalNoteResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class DimensionalNoteListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class DimensionalNote
    def initialize()
        @length_string = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end
end

class DimensionalTypeParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = DimensionalType.new()
        dimensional_note_field = DimensionalNoteListResult.new()
        singleton_type_field = SingletonTypeResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && singleton_type_parser_instance.ParseSingleSave(index,singleton_type_field) && dimensional_note_parser_instance.ParseManySave(index,dimensional_note_field,1,-1))
            instance.SetDimensionalNote(dimensional_note_field.GetValue())
            instance.SetSingletonType(singleton_type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            dimensional_note_field = DimensionalNoteListResult.new()
            singleton_type_field = SingletonTypeResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = DimensionalTypeResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = DimensionalTypeResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = DimensionalTypeResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = DimensionalTypeListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class DimensionalTypeResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class DimensionalTypeListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class DimensionalType
    def initialize()
        @length_string = nil
        @dimensional_note_field = Array.new()
        @singleton_type_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetDimensionalNote(input_value)
        @dimensional_note_field = input_value
    end

    def GetDimensionalNote()
        return @dimensional_note_field
    end

    def SetSingletonType(input_value)
        @singleton_type_field = input_value
    end

    def GetSingletonType()
        return @singleton_type_field
    end
end

class MapNoteParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = MapNote.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"{") && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"}"))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = MapNoteResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = MapNoteResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = MapNoteResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = MapNoteListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class MapNoteResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class MapNoteListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class MapNote
    def initialize()
        @length_string = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end
end

class MapTypeParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = MapType.new()
        map_note_field = MapNoteResult.new()
        singleton_type_field = SingletonTypeResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && singleton_type_parser_instance.ParseSingleSave(index,singleton_type_field) && map_note_parser_instance.ParseSingleSave(index,map_note_field))
            instance.SetMapNote(map_note_field.GetValue())
            instance.SetSingletonType(singleton_type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            map_note_field = MapNoteResult.new()
            singleton_type_field = SingletonTypeResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = MapTypeResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = MapTypeResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = MapTypeResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = MapTypeListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class MapTypeResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class MapTypeListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class MapType
    def initialize()
        @length_string = nil
        @map_note_field = nil
        @singleton_type_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetMapNote(input_value)
        @map_note_field = input_value
    end

    def GetMapNote()
        return @map_note_field
    end

    def SetSingletonType(input_value)
        @singleton_type_field = input_value
    end

    def GetSingletonType()
        return @singleton_type_field
    end
end

class ValueTypeParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = ValueType.new()
        dimensional_type_field = DimensionalTypeResult.new()
        map_type_field = MapTypeResult.new()
        singleton_type_field = SingletonTypeResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && dimensional_type_parser_instance.ParseSingleSave(index,dimensional_type_field))
            instance.SetDimensionalType(dimensional_type_field.GetValue())
            instance.SetMapType(map_type_field.GetValue())
            instance.SetSingletonType(singleton_type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            dimensional_type_field = DimensionalTypeResult.new()
            map_type_field = MapTypeResult.new()
            singleton_type_field = SingletonTypeResult.new()
        end
        if (true && map_type_parser_instance.ParseSingleSave(index,map_type_field))
            instance.SetDimensionalType(dimensional_type_field.GetValue())
            instance.SetMapType(map_type_field.GetValue())
            instance.SetSingletonType(singleton_type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            dimensional_type_field = DimensionalTypeResult.new()
            map_type_field = MapTypeResult.new()
            singleton_type_field = SingletonTypeResult.new()
        end
        if (true && singleton_type_parser_instance.ParseSingleSave(index,singleton_type_field))
            instance.SetDimensionalType(dimensional_type_field.GetValue())
            instance.SetMapType(map_type_field.GetValue())
            instance.SetSingletonType(singleton_type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            dimensional_type_field = DimensionalTypeResult.new()
            map_type_field = MapTypeResult.new()
            singleton_type_field = SingletonTypeResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = ValueTypeResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = ValueTypeResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = ValueTypeResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = ValueTypeListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class ValueTypeResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class ValueTypeListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class ValueType
    def initialize()
        @length_string = nil
        @dimensional_type_field = nil
        @map_type_field = nil
        @singleton_type_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetDimensionalType(input_value)
        @dimensional_type_field = input_value
    end

    def GetDimensionalType()
        return @dimensional_type_field
    end

    def SetMapType(input_value)
        @map_type_field = input_value
    end

    def GetMapType()
        return @map_type_field
    end

    def SetSingletonType(input_value)
        @singleton_type_field = input_value
    end

    def GetSingletonType()
        return @singleton_type_field
    end
end

class ParameterListDefParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = ParameterListDef.new()
        name_field = NameResult.new()
        parameter_tail_field = ParameterListDefResult.new()
        type_field = ValueTypeResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && value_type_parser_instance.ParseSingleSave(index,type_field) && whitespace_parser_instance.ParseMany(index,1,-1) && name_parser_instance.ParseSingleSave(index,name_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,",") && whitespace_parser_instance.ParseMany(index,0,-1) && parameter_list_def_parser_instance.ParseSingleSave(index,parameter_tail_field))
            instance.SetName(name_field.GetValue())
            instance.SetParameterTail(parameter_tail_field.GetValue())
            instance.SetType(type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            name_field = NameResult.new()
            parameter_tail_field = ParameterListDefResult.new()
            type_field = ValueTypeResult.new()
        end
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && value_type_parser_instance.ParseSingleSave(index,type_field) && whitespace_parser_instance.ParseMany(index,1,-1) && name_parser_instance.ParseSingleSave(index,name_field) && whitespace_parser_instance.ParseMany(index,0,-1))
            instance.SetName(name_field.GetValue())
            instance.SetParameterTail(parameter_tail_field.GetValue())
            instance.SetType(type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            name_field = NameResult.new()
            parameter_tail_field = ParameterListDefResult.new()
            type_field = ValueTypeResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = ParameterListDefResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = ParameterListDefResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = ParameterListDefResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = ParameterListDefListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class ParameterListDefResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class ParameterListDefListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class ParameterListDef
    def initialize()
        @length_string = nil
        @name_field = nil
        @parameter_tail_field = nil
        @type_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetName(input_value)
        @name_field = input_value
    end

    def GetName()
        return @name_field
    end

    def SetParameterTail(input_value)
        @parameter_tail_field = input_value
    end

    def GetParameterTail()
        return @parameter_tail_field
    end

    def SetType(input_value)
        @type_field = input_value
    end

    def ReservedPrefixGetType()
        return @type_field
    end
end

class ParameterListParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = ParameterList.new()
        parameter_tail_field = ParameterListResult.new()
        r_value_field = RValueResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && r_value_parser_instance.ParseSingleSave(index,r_value_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,",") && whitespace_parser_instance.ParseMany(index,0,-1) && parameter_list_parser_instance.ParseSingleSave(index,parameter_tail_field))
            instance.SetParameterTail(parameter_tail_field.GetValue())
            instance.SetRValue(r_value_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            parameter_tail_field = ParameterListResult.new()
            r_value_field = RValueResult.new()
        end
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && r_value_parser_instance.ParseSingleSave(index,r_value_field) && whitespace_parser_instance.ParseMany(index,0,-1))
            instance.SetParameterTail(parameter_tail_field.GetValue())
            instance.SetRValue(r_value_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            parameter_tail_field = ParameterListResult.new()
            r_value_field = RValueResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = ParameterListResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = ParameterListResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = ParameterListResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = ParameterListListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class ParameterListResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class ParameterListListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class ParameterList
    def initialize()
        @length_string = nil
        @parameter_tail_field = nil
        @r_value_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetParameterTail(input_value)
        @parameter_tail_field = input_value
    end

    def GetParameterTail()
        return @parameter_tail_field
    end

    def SetRValue(input_value)
        @r_value_field = input_value
    end

    def GetRValue()
        return @r_value_field
    end
end

class CodeBlockParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = CodeBlock.new()
        instructions_field = InstructionListResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"{") && whitespace_parser_instance.ParseMany(index,0,-1) && instruction_parser_instance.ParseManySave(index,instructions_field,0,-1) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"}") && whitespace_parser_instance.ParseMany(index,0,-1))
            instance.SetInstructions(instructions_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            instructions_field = InstructionListResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = CodeBlockResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = CodeBlockResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = CodeBlockResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = CodeBlockListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class CodeBlockResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class CodeBlockListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class CodeBlock
    def initialize()
        @length_string = nil
        @instructions_field = Array.new()
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetInstructions(input_value)
        @instructions_field = input_value
    end

    def GetInstructions()
        return @instructions_field
    end
end

class DeclarationAssignParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = DeclarationAssign.new()
        r_value_field = RValueResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"=") && whitespace_parser_instance.ParseMany(index,0,-1) && r_value_parser_instance.ParseSingleSave(index,r_value_field) && whitespace_parser_instance.ParseMany(index,0,-1))
            instance.SetRValue(r_value_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            r_value_field = RValueResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = DeclarationAssignResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = DeclarationAssignResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = DeclarationAssignResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = DeclarationAssignListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class DeclarationAssignResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class DeclarationAssignListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class DeclarationAssign
    def initialize()
        @length_string = nil
        @r_value_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetRValue(input_value)
        @r_value_field = input_value
    end

    def GetRValue()
        return @r_value_field
    end
end

class DeclarationParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = Declaration.new()
        assignment_field = DeclarationAssignResult.new()
        name_field = NameResult.new()
        type_field = ValueTypeResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && value_type_parser_instance.ParseSingleSave(index,type_field) && whitespace_parser_instance.ParseMany(index,1,-1) && name_parser_instance.ParseSingleSave(index,name_field) && whitespace_parser_instance.ParseMany(index,0,-1) && declaration_assign_parser_instance.ParseOptionalSave(index,assignment_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,";") && whitespace_parser_instance.ParseMany(index,0,-1))
            instance.SetAssignment(assignment_field.GetValue())
            instance.SetName(name_field.GetValue())
            instance.SetType(type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            assignment_field = DeclarationAssignResult.new()
            name_field = NameResult.new()
            type_field = ValueTypeResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = DeclarationResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = DeclarationResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = DeclarationResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = DeclarationListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class DeclarationResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class DeclarationListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class Declaration
    def initialize()
        @length_string = nil
        @assignment_field = nil
        @name_field = nil
        @type_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetAssignment(input_value)
        @assignment_field = input_value
    end

    def GetAssignment()
        return @assignment_field
    end

    def SetName(input_value)
        @name_field = input_value
    end

    def GetName()
        return @name_field
    end

    def SetType(input_value)
        @type_field = input_value
    end

    def ReservedPrefixGetType()
        return @type_field
    end
end

class AssignmentParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = Assignment.new()
        l_value_field = QualfiedNameResult.new()
        r_value_field = RValueResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && qualfied_name_parser_instance.ParseSingleSave(index,l_value_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"=") && whitespace_parser_instance.ParseMany(index,0,-1) && r_value_parser_instance.ParseSingleSave(index,r_value_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,";") && whitespace_parser_instance.ParseMany(index,0,-1))
            instance.SetLValue(l_value_field.GetValue())
            instance.SetRValue(r_value_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            l_value_field = QualfiedNameResult.new()
            r_value_field = RValueResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = AssignmentResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = AssignmentResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = AssignmentResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = AssignmentListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class AssignmentResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class AssignmentListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class Assignment
    def initialize()
        @length_string = nil
        @l_value_field = nil
        @r_value_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetLValue(input_value)
        @l_value_field = input_value
    end

    def GetLValue()
        return @l_value_field
    end

    def SetRValue(input_value)
        @r_value_field = input_value
    end

    def GetRValue()
        return @r_value_field
    end
end

class ReturnParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = ReservedPrefixReturn.new()
        r_value_field = RValueResult.new()
        rtn_field = StringResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingleSave(index,"return",rtn_field) && whitespace_parser_instance.ParseMany(index,1,-1) && r_value_parser_instance.ParseSingleSave(index,r_value_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,";") && whitespace_parser_instance.ParseMany(index,0,-1))
            instance.SetRValue(r_value_field.GetValue())
            instance.SetRtn(rtn_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            r_value_field = RValueResult.new()
            rtn_field = StringResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = ReturnResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = ReturnResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = ReturnResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = ReturnListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class ReturnResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class ReturnListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class ReservedPrefixReturn
    def initialize()
        @length_string = nil
        @r_value_field = nil
        @rtn_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetRValue(input_value)
        @r_value_field = input_value
    end

    def GetRValue()
        return @r_value_field
    end

    def SetRtn(input_value)
        @rtn_field = input_value
    end

    def GetRtn()
        return @rtn_field
    end
end

class ElseTailParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = ElseTail.new()
        code_block_field = CodeBlockResult.new()
        else_key_field = StringResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingleSave(index,"else",else_key_field) && whitespace_parser_instance.ParseMany(index,0,-1) && code_block_parser_instance.ParseSingleSave(index,code_block_field) && whitespace_parser_instance.ParseMany(index,0,-1))
            instance.SetCodeBlock(code_block_field.GetValue())
            instance.SetElseKey(else_key_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            code_block_field = CodeBlockResult.new()
            else_key_field = StringResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = ElseTailResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = ElseTailResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = ElseTailResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = ElseTailListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class ElseTailResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class ElseTailListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class ElseTail
    def initialize()
        @length_string = nil
        @code_block_field = nil
        @else_key_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetCodeBlock(input_value)
        @code_block_field = input_value
    end

    def GetCodeBlock()
        return @code_block_field
    end

    def SetElseKey(input_value)
        @else_key_field = input_value
    end

    def GetElseKey()
        return @else_key_field
    end
end

class ConditionalParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = Conditional.new()
        code_block_field = CodeBlockResult.new()
        conditional_key_field = StringResult.new()
        else_tail_field = ElseTailResult.new()
        r_value_field = RValueResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingleSave(index,"if",conditional_key_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"(") && whitespace_parser_instance.ParseMany(index,0,-1) && r_value_parser_instance.ParseSingleSave(index,r_value_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,")") && whitespace_parser_instance.ParseMany(index,0,-1) && code_block_parser_instance.ParseSingleSave(index,code_block_field) && whitespace_parser_instance.ParseMany(index,0,-1) && else_tail_parser_instance.ParseOptionalSave(index,else_tail_field))
            instance.SetCodeBlock(code_block_field.GetValue())
            instance.SetConditionalKey(conditional_key_field.GetValue())
            instance.SetElseTail(else_tail_field.GetValue())
            instance.SetRValue(r_value_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            code_block_field = CodeBlockResult.new()
            conditional_key_field = StringResult.new()
            else_tail_field = ElseTailResult.new()
            r_value_field = RValueResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = ConditionalResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = ConditionalResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = ConditionalResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = ConditionalListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class ConditionalResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class ConditionalListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class Conditional
    def initialize()
        @length_string = nil
        @code_block_field = nil
        @conditional_key_field = nil
        @else_tail_field = nil
        @r_value_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetCodeBlock(input_value)
        @code_block_field = input_value
    end

    def GetCodeBlock()
        return @code_block_field
    end

    def SetConditionalKey(input_value)
        @conditional_key_field = input_value
    end

    def GetConditionalKey()
        return @conditional_key_field
    end

    def SetElseTail(input_value)
        @else_tail_field = input_value
    end

    def GetElseTail()
        return @else_tail_field
    end

    def SetRValue(input_value)
        @r_value_field = input_value
    end

    def GetRValue()
        return @r_value_field
    end
end

class LoopParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = Loop.new()
        code_block_field = CodeBlockResult.new()
        loop_key_field = StringResult.new()
        r_value_field = RValueResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingleSave(index,"while",loop_key_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"(") && whitespace_parser_instance.ParseMany(index,0,-1) && r_value_parser_instance.ParseSingleSave(index,r_value_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,")") && whitespace_parser_instance.ParseMany(index,0,-1) && code_block_parser_instance.ParseSingleSave(index,code_block_field) && whitespace_parser_instance.ParseMany(index,0,-1))
            instance.SetCodeBlock(code_block_field.GetValue())
            instance.SetLoopKey(loop_key_field.GetValue())
            instance.SetRValue(r_value_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            code_block_field = CodeBlockResult.new()
            loop_key_field = StringResult.new()
            r_value_field = RValueResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = LoopResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = LoopResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = LoopResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = LoopListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class LoopResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class LoopListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class Loop
    def initialize()
        @length_string = nil
        @code_block_field = nil
        @loop_key_field = nil
        @r_value_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetCodeBlock(input_value)
        @code_block_field = input_value
    end

    def GetCodeBlock()
        return @code_block_field
    end

    def SetLoopKey(input_value)
        @loop_key_field = input_value
    end

    def GetLoopKey()
        return @loop_key_field
    end

    def SetRValue(input_value)
        @r_value_field = input_value
    end

    def GetRValue()
        return @r_value_field
    end
end

class CallParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = Call.new()
        function_chain_field = QualfiedNameResult.new()
        function_field = NameResult.new()
        parameters_field = ParameterListResult.new()
        variable_field = NameResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && name_parser_instance.ParseSingleSave(index,variable_field) && string_parser_instance.ParseSingle(index,".") && name_parser_instance.ParseSingleSave(index,function_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"(") && whitespace_parser_instance.ParseMany(index,0,-1) && parameter_list_parser_instance.ParseOptionalSave(index,parameters_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,")") && whitespace_parser_instance.ParseMany(index,0,-1))
            instance.SetFunctionChain(function_chain_field.GetValue())
            instance.SetFunction(function_field.GetValue())
            instance.SetParameters(parameters_field.GetValue())
            instance.SetVariable(variable_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            function_chain_field = QualfiedNameResult.new()
            function_field = NameResult.new()
            parameters_field = ParameterListResult.new()
            variable_field = NameResult.new()
        end
        if (true && name_parser_instance.ParseSingleSave(index,function_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"(") && whitespace_parser_instance.ParseMany(index,0,-1) && parameter_list_parser_instance.ParseOptionalSave(index,parameters_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,")") && whitespace_parser_instance.ParseMany(index,0,-1))
            instance.SetFunctionChain(function_chain_field.GetValue())
            instance.SetFunction(function_field.GetValue())
            instance.SetParameters(parameters_field.GetValue())
            instance.SetVariable(variable_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            function_chain_field = QualfiedNameResult.new()
            function_field = NameResult.new()
            parameters_field = ParameterListResult.new()
            variable_field = NameResult.new()
        end
        if (true && qualfied_name_parser_instance.ParseSingleSave(index,function_chain_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"(") && whitespace_parser_instance.ParseMany(index,0,-1) && parameter_list_parser_instance.ParseOptionalSave(index,parameters_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,")") && whitespace_parser_instance.ParseMany(index,0,-1))
            instance.SetFunctionChain(function_chain_field.GetValue())
            instance.SetFunction(function_field.GetValue())
            instance.SetParameters(parameters_field.GetValue())
            instance.SetVariable(variable_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            function_chain_field = QualfiedNameResult.new()
            function_field = NameResult.new()
            parameters_field = ParameterListResult.new()
            variable_field = NameResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = CallResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = CallResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = CallResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = CallListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class CallResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class CallListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class Call
    def initialize()
        @length_string = nil
        @function_chain_field = nil
        @function_field = nil
        @parameters_field = nil
        @variable_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetFunctionChain(input_value)
        @function_chain_field = input_value
    end

    def GetFunctionChain()
        return @function_chain_field
    end

    def SetFunction(input_value)
        @function_field = input_value
    end

    def GetFunction()
        return @function_field
    end

    def SetParameters(input_value)
        @parameters_field = input_value
    end

    def GetParameters()
        return @parameters_field
    end

    def SetVariable(input_value)
        @variable_field = input_value
    end

    def GetVariable()
        return @variable_field
    end
end

class AllocateParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = Allocate.new()
        managed_type_field = QualfiedNameResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"new") && whitespace_parser_instance.ParseMany(index,1,-1) && qualfied_name_parser_instance.ParseSingleSave(index,managed_type_field) && whitespace_parser_instance.ParseMany(index,0,-1))
            instance.SetManagedType(managed_type_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            managed_type_field = QualfiedNameResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = AllocateResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = AllocateResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = AllocateResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = AllocateListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class AllocateResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class AllocateListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class Allocate
    def initialize()
        @length_string = nil
        @managed_type_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetManagedType(input_value)
        @managed_type_field = input_value
    end

    def GetManagedType()
        return @managed_type_field
    end
end

class InstructionParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = Instruction.new()
        assignment_field = AssignmentResult.new()
        call_field = CallResult.new()
        code_block_field = CodeBlockResult.new()
        comment_field = CommentResult.new()
        conditional_field = ConditionalResult.new()
        declaration_field = DeclarationResult.new()
        loop_field = LoopResult.new()
        rtn_field = ReturnResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && comment_parser_instance.ParseOptionalSave(index,comment_field) && whitespace_parser_instance.ParseMany(index,0,-1) && code_block_parser_instance.ParseSingleSave(index,code_block_field))
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
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            assignment_field = AssignmentResult.new()
            call_field = CallResult.new()
            code_block_field = CodeBlockResult.new()
            comment_field = CommentResult.new()
            conditional_field = ConditionalResult.new()
            declaration_field = DeclarationResult.new()
            loop_field = LoopResult.new()
            rtn_field = ReturnResult.new()
        end
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && comment_parser_instance.ParseOptionalSave(index,comment_field) && whitespace_parser_instance.ParseMany(index,0,-1) && return_parser_instance.ParseSingleSave(index,rtn_field))
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
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            assignment_field = AssignmentResult.new()
            call_field = CallResult.new()
            code_block_field = CodeBlockResult.new()
            comment_field = CommentResult.new()
            conditional_field = ConditionalResult.new()
            declaration_field = DeclarationResult.new()
            loop_field = LoopResult.new()
            rtn_field = ReturnResult.new()
        end
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && comment_parser_instance.ParseOptionalSave(index,comment_field) && whitespace_parser_instance.ParseMany(index,0,-1) && declaration_parser_instance.ParseSingleSave(index,declaration_field))
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
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            assignment_field = AssignmentResult.new()
            call_field = CallResult.new()
            code_block_field = CodeBlockResult.new()
            comment_field = CommentResult.new()
            conditional_field = ConditionalResult.new()
            declaration_field = DeclarationResult.new()
            loop_field = LoopResult.new()
            rtn_field = ReturnResult.new()
        end
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && comment_parser_instance.ParseOptionalSave(index,comment_field) && whitespace_parser_instance.ParseMany(index,0,-1) && assignment_parser_instance.ParseSingleSave(index,assignment_field))
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
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            assignment_field = AssignmentResult.new()
            call_field = CallResult.new()
            code_block_field = CodeBlockResult.new()
            comment_field = CommentResult.new()
            conditional_field = ConditionalResult.new()
            declaration_field = DeclarationResult.new()
            loop_field = LoopResult.new()
            rtn_field = ReturnResult.new()
        end
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && comment_parser_instance.ParseOptionalSave(index,comment_field) && whitespace_parser_instance.ParseMany(index,0,-1) && call_parser_instance.ParseSingleSave(index,call_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,";") && whitespace_parser_instance.ParseMany(index,0,-1))
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
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            assignment_field = AssignmentResult.new()
            call_field = CallResult.new()
            code_block_field = CodeBlockResult.new()
            comment_field = CommentResult.new()
            conditional_field = ConditionalResult.new()
            declaration_field = DeclarationResult.new()
            loop_field = LoopResult.new()
            rtn_field = ReturnResult.new()
        end
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && comment_parser_instance.ParseOptionalSave(index,comment_field) && whitespace_parser_instance.ParseMany(index,0,-1) && conditional_parser_instance.ParseSingleSave(index,conditional_field))
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
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            assignment_field = AssignmentResult.new()
            call_field = CallResult.new()
            code_block_field = CodeBlockResult.new()
            comment_field = CommentResult.new()
            conditional_field = ConditionalResult.new()
            declaration_field = DeclarationResult.new()
            loop_field = LoopResult.new()
            rtn_field = ReturnResult.new()
        end
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && comment_parser_instance.ParseOptionalSave(index,comment_field) && whitespace_parser_instance.ParseMany(index,0,-1) && loop_parser_instance.ParseSingleSave(index,loop_field))
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
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            assignment_field = AssignmentResult.new()
            call_field = CallResult.new()
            code_block_field = CodeBlockResult.new()
            comment_field = CommentResult.new()
            conditional_field = ConditionalResult.new()
            declaration_field = DeclarationResult.new()
            loop_field = LoopResult.new()
            rtn_field = ReturnResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = InstructionResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = InstructionResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = InstructionResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = InstructionListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class InstructionResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class InstructionListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class Instruction
    def initialize()
        @length_string = nil
        @assignment_field = nil
        @call_field = nil
        @code_block_field = nil
        @comment_field = nil
        @conditional_field = nil
        @declaration_field = nil
        @loop_field = nil
        @rtn_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetAssignment(input_value)
        @assignment_field = input_value
    end

    def GetAssignment()
        return @assignment_field
    end

    def SetCall(input_value)
        @call_field = input_value
    end

    def GetCall()
        return @call_field
    end

    def SetCodeBlock(input_value)
        @code_block_field = input_value
    end

    def GetCodeBlock()
        return @code_block_field
    end

    def SetComment(input_value)
        @comment_field = input_value
    end

    def GetComment()
        return @comment_field
    end

    def SetConditional(input_value)
        @conditional_field = input_value
    end

    def GetConditional()
        return @conditional_field
    end

    def SetDeclaration(input_value)
        @declaration_field = input_value
    end

    def GetDeclaration()
        return @declaration_field
    end

    def SetLoop(input_value)
        @loop_field = input_value
    end

    def GetLoop()
        return @loop_field
    end

    def SetRtn(input_value)
        @rtn_field = input_value
    end

    def GetRtn()
        return @rtn_field
    end
end

class RValueSingleParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = RValueSingle.new()
        allocate_field = AllocateResult.new()
        boolean_literal_field = BooleanResult.new()
        byte_literal_field = ByteResult.new()
        call_field = CallResult.new()
        decimal_literal_field = DecimalResult.new()
        integer_literal_field = NumberResult.new()
        string_literal_field = LiteralResult.new()
        unary_operator_field = UnaryOperatorResult.new()
        variable_field = QualfiedNameResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && unary_operator_parser_instance.ParseOptionalSave(index,unary_operator_field) && whitespace_parser_instance.ParseMany(index,0,-1) && call_parser_instance.ParseSingleSave(index,call_field))
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
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            allocate_field = AllocateResult.new()
            boolean_literal_field = BooleanResult.new()
            byte_literal_field = ByteResult.new()
            call_field = CallResult.new()
            decimal_literal_field = DecimalResult.new()
            integer_literal_field = NumberResult.new()
            string_literal_field = LiteralResult.new()
            unary_operator_field = UnaryOperatorResult.new()
            variable_field = QualfiedNameResult.new()
        end
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && unary_operator_parser_instance.ParseOptionalSave(index,unary_operator_field) && whitespace_parser_instance.ParseMany(index,0,-1) && allocate_parser_instance.ParseSingleSave(index,allocate_field))
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
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            allocate_field = AllocateResult.new()
            boolean_literal_field = BooleanResult.new()
            byte_literal_field = ByteResult.new()
            call_field = CallResult.new()
            decimal_literal_field = DecimalResult.new()
            integer_literal_field = NumberResult.new()
            string_literal_field = LiteralResult.new()
            unary_operator_field = UnaryOperatorResult.new()
            variable_field = QualfiedNameResult.new()
        end
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && unary_operator_parser_instance.ParseOptionalSave(index,unary_operator_field) && whitespace_parser_instance.ParseMany(index,0,-1) && byte_parser_instance.ParseSingleSave(index,byte_literal_field))
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
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            allocate_field = AllocateResult.new()
            boolean_literal_field = BooleanResult.new()
            byte_literal_field = ByteResult.new()
            call_field = CallResult.new()
            decimal_literal_field = DecimalResult.new()
            integer_literal_field = NumberResult.new()
            string_literal_field = LiteralResult.new()
            unary_operator_field = UnaryOperatorResult.new()
            variable_field = QualfiedNameResult.new()
        end
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && unary_operator_parser_instance.ParseOptionalSave(index,unary_operator_field) && whitespace_parser_instance.ParseMany(index,0,-1) && decimal_parser_instance.ParseSingleSave(index,decimal_literal_field))
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
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            allocate_field = AllocateResult.new()
            boolean_literal_field = BooleanResult.new()
            byte_literal_field = ByteResult.new()
            call_field = CallResult.new()
            decimal_literal_field = DecimalResult.new()
            integer_literal_field = NumberResult.new()
            string_literal_field = LiteralResult.new()
            unary_operator_field = UnaryOperatorResult.new()
            variable_field = QualfiedNameResult.new()
        end
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && unary_operator_parser_instance.ParseOptionalSave(index,unary_operator_field) && whitespace_parser_instance.ParseMany(index,0,-1) && number_parser_instance.ParseSingleSave(index,integer_literal_field))
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
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            allocate_field = AllocateResult.new()
            boolean_literal_field = BooleanResult.new()
            byte_literal_field = ByteResult.new()
            call_field = CallResult.new()
            decimal_literal_field = DecimalResult.new()
            integer_literal_field = NumberResult.new()
            string_literal_field = LiteralResult.new()
            unary_operator_field = UnaryOperatorResult.new()
            variable_field = QualfiedNameResult.new()
        end
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && unary_operator_parser_instance.ParseOptionalSave(index,unary_operator_field) && whitespace_parser_instance.ParseMany(index,0,-1) && boolean_parser_instance.ParseSingleSave(index,boolean_literal_field))
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
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            allocate_field = AllocateResult.new()
            boolean_literal_field = BooleanResult.new()
            byte_literal_field = ByteResult.new()
            call_field = CallResult.new()
            decimal_literal_field = DecimalResult.new()
            integer_literal_field = NumberResult.new()
            string_literal_field = LiteralResult.new()
            unary_operator_field = UnaryOperatorResult.new()
            variable_field = QualfiedNameResult.new()
        end
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && unary_operator_parser_instance.ParseOptionalSave(index,unary_operator_field) && whitespace_parser_instance.ParseMany(index,0,-1) && qualfied_name_parser_instance.ParseSingleSave(index,variable_field))
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
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            allocate_field = AllocateResult.new()
            boolean_literal_field = BooleanResult.new()
            byte_literal_field = ByteResult.new()
            call_field = CallResult.new()
            decimal_literal_field = DecimalResult.new()
            integer_literal_field = NumberResult.new()
            string_literal_field = LiteralResult.new()
            unary_operator_field = UnaryOperatorResult.new()
            variable_field = QualfiedNameResult.new()
        end
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && unary_operator_parser_instance.ParseOptionalSave(index,unary_operator_field) && whitespace_parser_instance.ParseMany(index,0,-1) && string_parser_instance.ParseSingle(index,"\"") && literal_parser_instance.ParseSingleSave(index,string_literal_field) && string_parser_instance.ParseSingle(index,"\""))
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
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            allocate_field = AllocateResult.new()
            boolean_literal_field = BooleanResult.new()
            byte_literal_field = ByteResult.new()
            call_field = CallResult.new()
            decimal_literal_field = DecimalResult.new()
            integer_literal_field = NumberResult.new()
            string_literal_field = LiteralResult.new()
            unary_operator_field = UnaryOperatorResult.new()
            variable_field = QualfiedNameResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = RValueSingleResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = RValueSingleResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = RValueSingleResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = RValueSingleListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class RValueSingleResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class RValueSingleListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class RValueSingle
    def initialize()
        @length_string = nil
        @allocate_field = nil
        @boolean_literal_field = nil
        @byte_literal_field = nil
        @call_field = nil
        @decimal_literal_field = nil
        @integer_literal_field = nil
        @string_literal_field = nil
        @unary_operator_field = nil
        @variable_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetAllocate(input_value)
        @allocate_field = input_value
    end

    def GetAllocate()
        return @allocate_field
    end

    def SetBooleanLiteral(input_value)
        @boolean_literal_field = input_value
    end

    def GetBooleanLiteral()
        return @boolean_literal_field
    end

    def SetByteLiteral(input_value)
        @byte_literal_field = input_value
    end

    def GetByteLiteral()
        return @byte_literal_field
    end

    def SetCall(input_value)
        @call_field = input_value
    end

    def GetCall()
        return @call_field
    end

    def SetDecimalLiteral(input_value)
        @decimal_literal_field = input_value
    end

    def GetDecimalLiteral()
        return @decimal_literal_field
    end

    def SetIntegerLiteral(input_value)
        @integer_literal_field = input_value
    end

    def GetIntegerLiteral()
        return @integer_literal_field
    end

    def SetStringLiteral(input_value)
        @string_literal_field = input_value
    end

    def GetStringLiteral()
        return @string_literal_field
    end

    def SetUnaryOperator(input_value)
        @unary_operator_field = input_value
    end

    def GetUnaryOperator()
        return @unary_operator_field
    end

    def SetVariable(input_value)
        @variable_field = input_value
    end

    def GetVariable()
        return @variable_field
    end
end

class RValueTailParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = RValueTail.new()
        binary_operator_field = BinaryOperatorResult.new()
        tail_field = RValueTailResult.new()
        value_field = RValueSingleResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && whitespace_parser_instance.ParseMany(index,0,-1) && binary_operator_parser_instance.ParseSingleSave(index,binary_operator_field) && whitespace_parser_instance.ParseMany(index,0,-1) && r_value_single_parser_instance.ParseSingleSave(index,value_field) && whitespace_parser_instance.ParseMany(index,0,-1) && r_value_tail_parser_instance.ParseOptionalSave(index,tail_field))
            instance.SetBinaryOperator(binary_operator_field.GetValue())
            instance.SetTail(tail_field.GetValue())
            instance.SetValue(value_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            binary_operator_field = BinaryOperatorResult.new()
            tail_field = RValueTailResult.new()
            value_field = RValueSingleResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = RValueTailResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = RValueTailResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = RValueTailResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = RValueTailListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class RValueTailResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class RValueTailListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class RValueTail
    def initialize()
        @length_string = nil
        @binary_operator_field = nil
        @tail_field = nil
        @value_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetBinaryOperator(input_value)
        @binary_operator_field = input_value
    end

    def GetBinaryOperator()
        return @binary_operator_field
    end

    def SetTail(input_value)
        @tail_field = input_value
    end

    def GetTail()
        return @tail_field
    end

    def SetValue(input_value)
        @value_field = input_value
    end

    def GetValue()
        return @value_field
    end
end

class RValueParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = RValue.new()
        tail_field = RValueTailResult.new()
        value_field = RValueSingleResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && r_value_single_parser_instance.ParseSingleSave(index,value_field) && r_value_tail_parser_instance.ParseOptionalSave(index,tail_field))
            instance.SetTail(tail_field.GetValue())
            instance.SetValue(value_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            tail_field = RValueTailResult.new()
            value_field = RValueSingleResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = RValueResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = RValueResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = RValueResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = RValueListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class RValueResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class RValueListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class RValue
    def initialize()
        @length_string = nil
        @tail_field = nil
        @value_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetTail(input_value)
        @tail_field = input_value
    end

    def GetTail()
        return @tail_field
    end

    def SetValue(input_value)
        @value_field = input_value
    end

    def GetValue()
        return @value_field
    end
end

class BinaryOperatorParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = BinaryOperator.new()
        addition_field = StringResult.new()
        and_op_field = StringResult.new()
        equality_field = StringResult.new()
        greater_than_eq_field = StringResult.new()
        greater_than_field = StringResult.new()
        less_than_eq_field = StringResult.new()
        less_than_field = StringResult.new()
        not_equality_field = StringResult.new()
        or_op_field = StringResult.new()
        subtraction_field = StringResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && string_parser_instance.ParseSingleSave(index,"+",addition_field))
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
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            addition_field = StringResult.new()
            and_op_field = StringResult.new()
            equality_field = StringResult.new()
            greater_than_eq_field = StringResult.new()
            greater_than_field = StringResult.new()
            less_than_eq_field = StringResult.new()
            less_than_field = StringResult.new()
            not_equality_field = StringResult.new()
            or_op_field = StringResult.new()
            subtraction_field = StringResult.new()
        end
        if (true && string_parser_instance.ParseSingleSave(index,"-",subtraction_field))
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
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            addition_field = StringResult.new()
            and_op_field = StringResult.new()
            equality_field = StringResult.new()
            greater_than_eq_field = StringResult.new()
            greater_than_field = StringResult.new()
            less_than_eq_field = StringResult.new()
            less_than_field = StringResult.new()
            not_equality_field = StringResult.new()
            or_op_field = StringResult.new()
            subtraction_field = StringResult.new()
        end
        if (true && string_parser_instance.ParseSingleSave(index,"<=",less_than_eq_field))
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
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            addition_field = StringResult.new()
            and_op_field = StringResult.new()
            equality_field = StringResult.new()
            greater_than_eq_field = StringResult.new()
            greater_than_field = StringResult.new()
            less_than_eq_field = StringResult.new()
            less_than_field = StringResult.new()
            not_equality_field = StringResult.new()
            or_op_field = StringResult.new()
            subtraction_field = StringResult.new()
        end
        if (true && string_parser_instance.ParseSingleSave(index,">=",greater_than_eq_field))
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
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            addition_field = StringResult.new()
            and_op_field = StringResult.new()
            equality_field = StringResult.new()
            greater_than_eq_field = StringResult.new()
            greater_than_field = StringResult.new()
            less_than_eq_field = StringResult.new()
            less_than_field = StringResult.new()
            not_equality_field = StringResult.new()
            or_op_field = StringResult.new()
            subtraction_field = StringResult.new()
        end
        if (true && string_parser_instance.ParseSingleSave(index,"==",equality_field))
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
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            addition_field = StringResult.new()
            and_op_field = StringResult.new()
            equality_field = StringResult.new()
            greater_than_eq_field = StringResult.new()
            greater_than_field = StringResult.new()
            less_than_eq_field = StringResult.new()
            less_than_field = StringResult.new()
            not_equality_field = StringResult.new()
            or_op_field = StringResult.new()
            subtraction_field = StringResult.new()
        end
        if (true && string_parser_instance.ParseSingleSave(index,"!=",not_equality_field))
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
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            addition_field = StringResult.new()
            and_op_field = StringResult.new()
            equality_field = StringResult.new()
            greater_than_eq_field = StringResult.new()
            greater_than_field = StringResult.new()
            less_than_eq_field = StringResult.new()
            less_than_field = StringResult.new()
            not_equality_field = StringResult.new()
            or_op_field = StringResult.new()
            subtraction_field = StringResult.new()
        end
        if (true && string_parser_instance.ParseSingleSave(index,"<",less_than_field))
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
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            addition_field = StringResult.new()
            and_op_field = StringResult.new()
            equality_field = StringResult.new()
            greater_than_eq_field = StringResult.new()
            greater_than_field = StringResult.new()
            less_than_eq_field = StringResult.new()
            less_than_field = StringResult.new()
            not_equality_field = StringResult.new()
            or_op_field = StringResult.new()
            subtraction_field = StringResult.new()
        end
        if (true && string_parser_instance.ParseSingleSave(index,">",greater_than_field))
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
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            addition_field = StringResult.new()
            and_op_field = StringResult.new()
            equality_field = StringResult.new()
            greater_than_eq_field = StringResult.new()
            greater_than_field = StringResult.new()
            less_than_eq_field = StringResult.new()
            less_than_field = StringResult.new()
            not_equality_field = StringResult.new()
            or_op_field = StringResult.new()
            subtraction_field = StringResult.new()
        end
        if (true && string_parser_instance.ParseSingleSave(index,"||",or_op_field))
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
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            addition_field = StringResult.new()
            and_op_field = StringResult.new()
            equality_field = StringResult.new()
            greater_than_eq_field = StringResult.new()
            greater_than_field = StringResult.new()
            less_than_eq_field = StringResult.new()
            less_than_field = StringResult.new()
            not_equality_field = StringResult.new()
            or_op_field = StringResult.new()
            subtraction_field = StringResult.new()
        end
        if (true && string_parser_instance.ParseSingleSave(index,"&&",and_op_field))
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
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            addition_field = StringResult.new()
            and_op_field = StringResult.new()
            equality_field = StringResult.new()
            greater_than_eq_field = StringResult.new()
            greater_than_field = StringResult.new()
            less_than_eq_field = StringResult.new()
            less_than_field = StringResult.new()
            not_equality_field = StringResult.new()
            or_op_field = StringResult.new()
            subtraction_field = StringResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = BinaryOperatorResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = BinaryOperatorResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = BinaryOperatorResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = BinaryOperatorListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class BinaryOperatorResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class BinaryOperatorListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class BinaryOperator
    def initialize()
        @length_string = nil
        @addition_field = nil
        @and_op_field = nil
        @equality_field = nil
        @greater_than_eq_field = nil
        @greater_than_field = nil
        @less_than_eq_field = nil
        @less_than_field = nil
        @not_equality_field = nil
        @or_op_field = nil
        @subtraction_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetAddition(input_value)
        @addition_field = input_value
    end

    def GetAddition()
        return @addition_field
    end

    def SetAndOp(input_value)
        @and_op_field = input_value
    end

    def GetAndOp()
        return @and_op_field
    end

    def SetEquality(input_value)
        @equality_field = input_value
    end

    def GetEquality()
        return @equality_field
    end

    def SetGreaterThanEq(input_value)
        @greater_than_eq_field = input_value
    end

    def GetGreaterThanEq()
        return @greater_than_eq_field
    end

    def SetGreaterThan(input_value)
        @greater_than_field = input_value
    end

    def GetGreaterThan()
        return @greater_than_field
    end

    def SetLessThanEq(input_value)
        @less_than_eq_field = input_value
    end

    def GetLessThanEq()
        return @less_than_eq_field
    end

    def SetLessThan(input_value)
        @less_than_field = input_value
    end

    def GetLessThan()
        return @less_than_field
    end

    def SetNotEquality(input_value)
        @not_equality_field = input_value
    end

    def GetNotEquality()
        return @not_equality_field
    end

    def SetOrOp(input_value)
        @or_op_field = input_value
    end

    def GetOrOp()
        return @or_op_field
    end

    def SetSubtraction(input_value)
        @subtraction_field = input_value
    end

    def GetSubtraction()
        return @subtraction_field
    end
end

class UnaryOperatorParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = UnaryOperator.new()
        negation_field = StringResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && string_parser_instance.ParseSingleSave(index,"!",negation_field))
            instance.SetNegation(negation_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            negation_field = StringResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = UnaryOperatorResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = UnaryOperatorResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = UnaryOperatorResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = UnaryOperatorListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class UnaryOperatorResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class UnaryOperatorListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class UnaryOperator
    def initialize()
        @length_string = nil
        @negation_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetNegation(input_value)
        @negation_field = input_value
    end

    def GetNegation()
        return @negation_field
    end
end

class CommentParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = Comment.new()
        content_field = CommentContentListResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && string_parser_instance.ParseSingle(index,"/*") && comment_content_parser_instance.ParseManySave(index,content_field,0,-1) && string_parser_instance.ParseSingle(index,"*/"))
            instance.SetContent(content_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            content_field = CommentContentListResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = CommentResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = CommentResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = CommentResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = CommentListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class CommentResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class CommentListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class Comment
    def initialize()
        @length_string = nil
        @content_field = Array.new()
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetContent(input_value)
        @content_field = input_value
    end

    def GetContent()
        return @content_field
    end
end

class NonStarCharacterParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = NonStarCharacter.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && character_range_parser_instance.ParseSingle(index,0x00,0x29))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        if (true && character_range_parser_instance.ParseSingle(index,0x2B,0xFF))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = NonStarCharacterResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = NonStarCharacterResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = NonStarCharacterResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = NonStarCharacterListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class NonStarCharacterResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class NonStarCharacterListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class NonStarCharacter
    def initialize()
        @length_string = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end
end

class NonSlashCharacterParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = NonSlashCharacter.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && character_range_parser_instance.ParseSingle(index,0x00,0x2E))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        if (true && character_range_parser_instance.ParseSingle(index,0x30,0xFF))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = NonSlashCharacterResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = NonSlashCharacterResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = NonSlashCharacterResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = NonSlashCharacterListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class NonSlashCharacterResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class NonSlashCharacterListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class NonSlashCharacter
    def initialize()
        @length_string = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end
end

class CommentContentParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = CommentContent.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && non_star_character_parser_instance.ParseSingle(index))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        if (true && string_parser_instance.ParseSingle(index,"*") && non_slash_character_parser_instance.ParseSingle(index))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = CommentContentResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = CommentContentResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = CommentContentResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = CommentContentListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class CommentContentResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class CommentContentListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class CommentContent
    def initialize()
        @length_string = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end
end

class QualfiedNameParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = QualfiedName.new()
        name_field = NameResult.new()
        tail_field = NameTailResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && name_parser_instance.ParseSingleSave(index,name_field) && name_tail_parser_instance.ParseOptionalSave(index,tail_field))
            instance.SetName(name_field.GetValue())
            instance.SetTail(tail_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            name_field = NameResult.new()
            tail_field = NameTailResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = QualfiedNameResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = QualfiedNameResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = QualfiedNameResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = QualfiedNameListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class QualfiedNameResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class QualfiedNameListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class QualfiedName
    def initialize()
        @length_string = nil
        @name_field = nil
        @tail_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetName(input_value)
        @name_field = input_value
    end

    def GetName()
        return @name_field
    end

    def SetTail(input_value)
        @tail_field = input_value
    end

    def GetTail()
        return @tail_field
    end
end

class NameTailParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = NameTail.new()
        name_field = NameResult.new()
        tail_field = NameTailResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && string_parser_instance.ParseSingle(index,".") && name_parser_instance.ParseSingleSave(index,name_field) && name_tail_parser_instance.ParseOptionalSave(index,tail_field))
            instance.SetName(name_field.GetValue())
            instance.SetTail(tail_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            name_field = NameResult.new()
            tail_field = NameTailResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = NameTailResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = NameTailResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = NameTailResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = NameTailListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class NameTailResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class NameTailListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class NameTail
    def initialize()
        @length_string = nil
        @name_field = nil
        @tail_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetName(input_value)
        @name_field = input_value
    end

    def GetName()
        return @name_field
    end

    def SetTail(input_value)
        @tail_field = input_value
    end

    def GetTail()
        return @tail_field
    end
end

class NameParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = Name.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && name_character_parser_instance.ParseMany(index,1,-1))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = NameResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = NameResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = NameResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = NameListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class NameResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class NameListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class Name
    def initialize()
        @length_string = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end
end

class NameCharacterParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = NameCharacter.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && character_range_parser_instance.ParseSingle(index,0x30,0x39))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        if (true && character_range_parser_instance.ParseSingle(index,0x41,0x5A))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        if (true && string_parser_instance.ParseSingle(index,"_"))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        if (true && character_range_parser_instance.ParseSingle(index,0x61,0x7A))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = NameCharacterResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = NameCharacterResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = NameCharacterResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = NameCharacterListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class NameCharacterResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class NameCharacterListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class NameCharacter
    def initialize()
        @length_string = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end
end

class BooleanParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = Boolean.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && string_parser_instance.ParseSingle(index,"true"))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        if (true && string_parser_instance.ParseSingle(index,"false"))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = BooleanResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = BooleanResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = BooleanResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = BooleanListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class BooleanResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class BooleanListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class Boolean
    def initialize()
        @length_string = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end
end

class ByteParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = Byte.new()
        high_field = ByteDigitResult.new()
        low_field = ByteDigitResult.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && string_parser_instance.ParseSingle(index,"0x") && byte_digit_parser_instance.ParseSingleSave(index,high_field) && byte_digit_parser_instance.ParseSingleSave(index,low_field))
            instance.SetHigh(high_field.GetValue())
            instance.SetLow(low_field.GetValue())
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            high_field = ByteDigitResult.new()
            low_field = ByteDigitResult.new()
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = ByteResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = ByteResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = ByteResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = ByteListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class ByteResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class ByteListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class Byte
    def initialize()
        @length_string = nil
        @high_field = nil
        @low_field = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end

    def SetHigh(input_value)
        @high_field = input_value
    end

    def GetHigh()
        return @high_field
    end

    def SetLow(input_value)
        @low_field = input_value
    end

    def GetLow()
        return @low_field
    end
end

class ByteDigitParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = ByteDigit.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && character_range_parser_instance.ParseSingle(index,0x30,0x39))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        if (true && character_range_parser_instance.ParseSingle(index,0x41,0x46))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = ByteDigitResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = ByteDigitResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = ByteDigitResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = ByteDigitListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class ByteDigitResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class ByteDigitListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class ByteDigit
    def initialize()
        @length_string = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end
end

class NegativeParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = Negative.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && string_parser_instance.ParseSingle(index,"-"))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = NegativeResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = NegativeResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = NegativeResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = NegativeListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class NegativeResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class NegativeListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class Negative
    def initialize()
        @length_string = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end
end

class DecimalParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = Decimal.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && negative_parser_instance.ParseOptional(index) && number_parser_instance.ParseSingle(index) && string_parser_instance.ParseSingle(index,".") && number_parser_instance.ParseSingle(index))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = DecimalResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = DecimalResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = DecimalResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = DecimalListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class DecimalResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class DecimalListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class Decimal
    def initialize()
        @length_string = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end
end

class NumberParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = Number.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && negative_parser_instance.ParseOptional(index) && digit_parser_instance.ParseMany(index,1,-1))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = NumberResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = NumberResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = NumberResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = NumberListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class NumberResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class NumberListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class Number
    def initialize()
        @length_string = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end
end

class DigitParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = Digit.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && character_range_parser_instance.ParseSingle(index,0x30,0x39))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = DigitResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = DigitResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = DigitResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = DigitListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class DigitResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class DigitListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class Digit
    def initialize()
        @length_string = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end
end

class LiteralParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = Literal.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && literal_character_parser_instance.ParseMany(index,0,-1))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = LiteralResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = LiteralResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = LiteralResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = LiteralListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class LiteralResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class LiteralListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class Literal
    def initialize()
        @length_string = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end
end

class LiteralCharacterParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = LiteralCharacter.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && character_range_parser_instance.ParseSingle(index,0x00,0x21))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        if (true && string_parser_instance.ParseSingle(index,"\\\""))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        if (true && character_range_parser_instance.ParseSingle(index,0x23,0x5B))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        if (true && string_parser_instance.ParseSingle(index,"\\\\"))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        if (true && character_range_parser_instance.ParseSingle(index,0x5D,0xFF))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = LiteralCharacterResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = LiteralCharacterResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = LiteralCharacterResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = LiteralCharacterListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class LiteralCharacterResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class LiteralCharacterListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class LiteralCharacter
    def initialize()
        @length_string = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end
end

class WhitespaceParser
    def initialize()
        @parser_network = nil
    end

    def SetParserNetwork(input)
        @parser_network = input
    end

    def ParseSingleSave(index, result)
        index_start = index.GetStart()
        index_length = index.GetLength()
        consumed_string = LengthString.new()
        consumed_string.SetData(index.GetData())
        consumed_string.SetStart(index.GetStart())
        consumed_string.SetLength(0)
        instance = Whitespace.new()
        c_t_code_file_parser_instance = @parser_network.GetCTCodeFileParser()
        external_definition_parser_instance = @parser_network.GetExternalDefinitionParser()
        unmanaged_type_parser_instance = @parser_network.GetUnmanagedTypeParser()
        definition_parser_instance = @parser_network.GetDefinitionParser()
        interface_def_parser_instance = @parser_network.GetInterfaceDefParser()
        class_def_parser_instance = @parser_network.GetClassDefParser()
        implementation_spec_parser_instance = @parser_network.GetImplementationSpecParser()
        content_declaration_parser_instance = @parser_network.GetContentDeclarationParser()
        content_definition_parser_instance = @parser_network.GetContentDefinitionParser()
        primative_type_parser_instance = @parser_network.GetPrimativeTypeParser()
        defined_type_parser_instance = @parser_network.GetDefinedTypeParser()
        singleton_type_parser_instance = @parser_network.GetSingletonTypeParser()
        dimensional_note_parser_instance = @parser_network.GetDimensionalNoteParser()
        dimensional_type_parser_instance = @parser_network.GetDimensionalTypeParser()
        map_note_parser_instance = @parser_network.GetMapNoteParser()
        map_type_parser_instance = @parser_network.GetMapTypeParser()
        value_type_parser_instance = @parser_network.GetValueTypeParser()
        parameter_list_def_parser_instance = @parser_network.GetParameterListDefParser()
        parameter_list_parser_instance = @parser_network.GetParameterListParser()
        code_block_parser_instance = @parser_network.GetCodeBlockParser()
        declaration_assign_parser_instance = @parser_network.GetDeclarationAssignParser()
        declaration_parser_instance = @parser_network.GetDeclarationParser()
        assignment_parser_instance = @parser_network.GetAssignmentParser()
        return_parser_instance = @parser_network.GetReturnParser()
        else_tail_parser_instance = @parser_network.GetElseTailParser()
        conditional_parser_instance = @parser_network.GetConditionalParser()
        loop_parser_instance = @parser_network.GetLoopParser()
        call_parser_instance = @parser_network.GetCallParser()
        allocate_parser_instance = @parser_network.GetAllocateParser()
        instruction_parser_instance = @parser_network.GetInstructionParser()
        r_value_single_parser_instance = @parser_network.GetRValueSingleParser()
        r_value_tail_parser_instance = @parser_network.GetRValueTailParser()
        r_value_parser_instance = @parser_network.GetRValueParser()
        binary_operator_parser_instance = @parser_network.GetBinaryOperatorParser()
        unary_operator_parser_instance = @parser_network.GetUnaryOperatorParser()
        comment_parser_instance = @parser_network.GetCommentParser()
        non_star_character_parser_instance = @parser_network.GetNonStarCharacterParser()
        non_slash_character_parser_instance = @parser_network.GetNonSlashCharacterParser()
        comment_content_parser_instance = @parser_network.GetCommentContentParser()
        qualfied_name_parser_instance = @parser_network.GetQualfiedNameParser()
        name_tail_parser_instance = @parser_network.GetNameTailParser()
        name_parser_instance = @parser_network.GetNameParser()
        name_character_parser_instance = @parser_network.GetNameCharacterParser()
        boolean_parser_instance = @parser_network.GetBooleanParser()
        byte_parser_instance = @parser_network.GetByteParser()
        byte_digit_parser_instance = @parser_network.GetByteDigitParser()
        negative_parser_instance = @parser_network.GetNegativeParser()
        decimal_parser_instance = @parser_network.GetDecimalParser()
        number_parser_instance = @parser_network.GetNumberParser()
        digit_parser_instance = @parser_network.GetDigitParser()
        literal_parser_instance = @parser_network.GetLiteralParser()
        literal_character_parser_instance = @parser_network.GetLiteralCharacterParser()
        whitespace_parser_instance = @parser_network.GetWhitespaceParser()
        string_parser_instance = @parser_network.GetStringParser()
        character_parser_instance = @parser_network.GetCharacterParser()
        character_range_parser_instance = @parser_network.GetCharacterRangeParser()
        if (true && character_range_parser_instance.ParseSingle(index,0x00,0x20))
            consumed_string.SetLength(index.GetStart()-index_start)
            instance.SetLengthString(consumed_string)
            result.SetValue(instance)
            result.SetResult(true)
            return result.GetResult()
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
        end
        result.SetResult(false)
        return result.GetResult()
    end

    def ParseSingle(index)
        result = WhitespaceResult.new()
        return self.ParseSingleSave(index,result)
    end

    def ParseOptionalSave(index, result)
        self.ParseSingleSave(index,result)
        result.SetResult(true)
        return true
    end

    def ParseOptional(index)
        result = WhitespaceResult.new()
        return self.ParseOptionalSave(index,result)
    end

    def ParseManySave(index, list_result, minimum, maximum)
        index_start = index.GetStart()
        index_length = index.GetLength()
        results = Array.new()
        count = 0
        max_check = maximum
        check_next = true
        if (maximum<0)
            max_check = count+1
        end
        while (check_next && count<max_check)
            result = WhitespaceResult.new()
            self.ParseSingleSave(index,result)
            check_next = result.GetResult()
            if (result.GetResult())
                count = count+1
                Append(results,result.GetValue())
            end
            if (maximum<0)
                max_check = count+1
            end
        end
        if (count>=minimum && count<=max_check)
            list_result.SetValue(results)
            list_result.SetResult(true)
        else
            index.SetStart(index_start)
            index.SetLength(index_length)
            list_result.SetResult(false)
        end
        return list_result.GetResult()
    end

    def ParseMany(index, minimum, maximum)
        result = WhitespaceListResult.new()
        return self.ParseManySave(index,result,minimum,maximum)
    end
end

class WhitespaceResult
    def initialize()
        @value = nil
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class WhitespaceListResult
    def initialize()
        @value = Array.new()
        @result = false
    end

    def SetValue(new_value)
        @value = new_value
    end

    def GetValue()
        return @value
    end

    def SetResult(new_result)
        @result = new_result
    end

    def GetResult()
        return @result
    end
end

class Whitespace
    def initialize()
        @length_string = nil
    end

    def SetLengthString(new_value)
        @length_string = LengthString.new()
        @length_string.SetData(new_value.GetData())
        @length_string.SetStart(new_value.GetStart())
        @length_string.SetLength(new_value.GetLength())
    end

    def UnParse()
        return @length_string.GetString()
    end
end

end
end
end
end
