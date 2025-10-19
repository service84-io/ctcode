package s84.ctcode.dbnf.ctcode;

public class DBNFOmniTypeListResult {
    public DBNFOmniTypeListResult()
    {
        this.value = new java.util.ArrayList<>();
        this.result = false;
    }

    public void SetValue(java.util.ArrayList<DBNFOmniType> new_value)
    {
        this.value = new_value;
    }

    public java.util.ArrayList<DBNFOmniType> GetValue()
    {
        return this.value;
    }

    public void SetResult(boolean new_result)
    {
        this.result = new_result;
    }

    public boolean GetResult()
    {
        return this.result;
    }

    public void SetCTCodeFile(java.util.ArrayList<CTCodeFile> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetCTCodeFile(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetExternalDefinition(java.util.ArrayList<ExternalDefinition> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetExternalDefinition(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetUnmanagedType(java.util.ArrayList<UnmanagedType> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetUnmanagedType(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetDefinition(java.util.ArrayList<Definition> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetDefinition(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetInterfaceDef(java.util.ArrayList<InterfaceDef> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetInterfaceDef(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetClassDef(java.util.ArrayList<ClassDef> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetClassDef(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetImplementationSpec(java.util.ArrayList<ImplementationSpec> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetImplementationSpec(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetContentDeclaration(java.util.ArrayList<ContentDeclaration> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetContentDeclaration(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetContentDefinition(java.util.ArrayList<ContentDefinition> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetContentDefinition(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetPrimativeType(java.util.ArrayList<PrimativeType> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetPrimativeType(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetDefinedType(java.util.ArrayList<DefinedType> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetDefinedType(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetSingletonType(java.util.ArrayList<SingletonType> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetSingletonType(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetDimensionalNote(java.util.ArrayList<DimensionalNote> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetDimensionalNote(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetDimensionalType(java.util.ArrayList<DimensionalType> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetDimensionalType(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetMapNote(java.util.ArrayList<MapNote> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetMapNote(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetMapType(java.util.ArrayList<MapType> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetMapType(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetValueType(java.util.ArrayList<ValueType> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetValueType(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetParameterListDef(java.util.ArrayList<ParameterListDef> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetParameterListDef(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetParameterList(java.util.ArrayList<ParameterList> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetParameterList(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetCodeBlock(java.util.ArrayList<CodeBlock> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetCodeBlock(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetDeclarationAssign(java.util.ArrayList<DeclarationAssign> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetDeclarationAssign(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetDeclaration(java.util.ArrayList<Declaration> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetDeclaration(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetAssignment(java.util.ArrayList<Assignment> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetAssignment(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetReturn(java.util.ArrayList<ReservedPrefixReturn> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetReturn(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetElseTail(java.util.ArrayList<ElseTail> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetElseTail(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetConditional(java.util.ArrayList<Conditional> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetConditional(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetLoop(java.util.ArrayList<Loop> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetLoop(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetCall(java.util.ArrayList<Call> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetCall(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetAllocate(java.util.ArrayList<Allocate> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetAllocate(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetInstruction(java.util.ArrayList<Instruction> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetInstruction(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetRValueSingle(java.util.ArrayList<RValueSingle> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetRValueSingle(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetRValueTail(java.util.ArrayList<RValueTail> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetRValueTail(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetRValue(java.util.ArrayList<RValue> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetRValue(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetBinaryOperator(java.util.ArrayList<BinaryOperator> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetBinaryOperator(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetUnaryOperator(java.util.ArrayList<UnaryOperator> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetUnaryOperator(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetComment(java.util.ArrayList<Comment> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetComment(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetNonStarCharacter(java.util.ArrayList<NonStarCharacter> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetNonStarCharacter(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetNonSlashCharacter(java.util.ArrayList<NonSlashCharacter> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetNonSlashCharacter(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetCommentContent(java.util.ArrayList<CommentContent> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetCommentContent(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetQualfiedName(java.util.ArrayList<QualfiedName> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetQualfiedName(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetNameTail(java.util.ArrayList<NameTail> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetNameTail(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetName(java.util.ArrayList<Name> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetName(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetNameCharacter(java.util.ArrayList<NameCharacter> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetNameCharacter(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetBoolean(java.util.ArrayList<Boolean> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetBoolean(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetByte(java.util.ArrayList<Byte> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetByte(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetByteDigit(java.util.ArrayList<ByteDigit> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetByteDigit(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetNegative(java.util.ArrayList<Negative> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetNegative(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetDecimal(java.util.ArrayList<Decimal> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetDecimal(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetNumber(java.util.ArrayList<Number> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetNumber(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetDigit(java.util.ArrayList<Digit> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetDigit(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetLiteral(java.util.ArrayList<Literal> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetLiteral(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetLiteralCharacter(java.util.ArrayList<LiteralCharacter> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetLiteralCharacter(Element(input_value, index));
            index = (index+1);
        }
    }

    public void SetWhitespace(java.util.ArrayList<Whitespace> input_value)
    {
        int index = 0;
        while (AsBoolean((index<Size(input_value))))
        {
            DBNFOmniType value = new DBNFOmniType();
            value.SetWhitespace(Element(input_value, index));
            index = (index+1);
        }
    }

    private java.util.ArrayList<DBNFOmniType> value;
    private boolean result;

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
    private static <T extends java.lang.Object> boolean AsBoolean(T value) { return value != null; }
    private static boolean AsBoolean(boolean value) { return value; }
    private static boolean Equals(java.lang.String left, java.lang.String right) { return left.equals(right); }
    private static boolean Equals(boolean left, boolean right) { return left == right; }
    private static boolean Equals(int left, int right) { return left == right; }
    private static boolean Equals(float left, float right) { return left == right; }
}
