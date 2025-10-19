package s84.ctcode.dbnf.ctcode;

public class Conditional {
    public Conditional()
    {
        this.length_string = null;
        this.code_block_field = null;
        this.conditional_key_field = null;
        this.else_tail_field = null;
        this.r_value_field = null;
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

    public void SetCodeBlock(CodeBlock input_value)
    {
        this.code_block_field = input_value;
    }

    public CodeBlock GetCodeBlock()
    {
        return this.code_block_field;
    }

    public void SetConditionalKey(String input_value)
    {
        this.conditional_key_field = input_value;
    }

    public String GetConditionalKey()
    {
        return this.conditional_key_field;
    }

    public void SetElseTail(ElseTail input_value)
    {
        this.else_tail_field = input_value;
    }

    public ElseTail GetElseTail()
    {
        return this.else_tail_field;
    }

    public void SetRValue(RValue input_value)
    {
        this.r_value_field = input_value;
    }

    public RValue GetRValue()
    {
        return this.r_value_field;
    }

    private LengthString length_string;
    private CodeBlock code_block_field;
    private String conditional_key_field;
    private ElseTail else_tail_field;
    private RValue r_value_field;

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
