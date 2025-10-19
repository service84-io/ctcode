package s84.ctcode.dbnf.ctcode;

public class RValueSingle {
    public RValueSingle()
    {
        this.length_string = null;
        this.allocate_field = null;
        this.boolean_literal_field = null;
        this.byte_literal_field = null;
        this.call_field = null;
        this.decimal_literal_field = null;
        this.integer_literal_field = null;
        this.string_literal_field = null;
        this.unary_operator_field = null;
        this.variable_field = null;
    }

    public void SetLengthString(LengthString new_value)
    {
        this.length_string = new LengthString();
        this.length_string.SetData(new_value.GetData());
        this.length_string.SetStart(new_value.GetStart());
        this.length_string.SetLength(new_value.GetLength());
    }

    public java.lang.String UnParse()
    {
        return this.length_string.GetString();
    }

    public void SetAllocate(Allocate input_value)
    {
        this.allocate_field = input_value;
    }

    public Allocate GetAllocate()
    {
        return this.allocate_field;
    }

    public void SetBooleanLiteral(Boolean input_value)
    {
        this.boolean_literal_field = input_value;
    }

    public Boolean GetBooleanLiteral()
    {
        return this.boolean_literal_field;
    }

    public void SetByteLiteral(Byte input_value)
    {
        this.byte_literal_field = input_value;
    }

    public Byte GetByteLiteral()
    {
        return this.byte_literal_field;
    }

    public void SetCall(Call input_value)
    {
        this.call_field = input_value;
    }

    public Call GetCall()
    {
        return this.call_field;
    }

    public void SetDecimalLiteral(Decimal input_value)
    {
        this.decimal_literal_field = input_value;
    }

    public Decimal GetDecimalLiteral()
    {
        return this.decimal_literal_field;
    }

    public void SetIntegerLiteral(Number input_value)
    {
        this.integer_literal_field = input_value;
    }

    public Number GetIntegerLiteral()
    {
        return this.integer_literal_field;
    }

    public void SetStringLiteral(Literal input_value)
    {
        this.string_literal_field = input_value;
    }

    public Literal GetStringLiteral()
    {
        return this.string_literal_field;
    }

    public void SetUnaryOperator(UnaryOperator input_value)
    {
        this.unary_operator_field = input_value;
    }

    public UnaryOperator GetUnaryOperator()
    {
        return this.unary_operator_field;
    }

    public void SetVariable(QualfiedName input_value)
    {
        this.variable_field = input_value;
    }

    public QualfiedName GetVariable()
    {
        return this.variable_field;
    }

    private LengthString length_string;
    private Allocate allocate_field;
    private Boolean boolean_literal_field;
    private Byte byte_literal_field;
    private Call call_field;
    private Decimal decimal_literal_field;
    private Number integer_literal_field;
    private Literal string_literal_field;
    private UnaryOperator unary_operator_field;
    private QualfiedName variable_field;

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
