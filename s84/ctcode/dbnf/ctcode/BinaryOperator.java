package s84.ctcode.dbnf.ctcode;

public class BinaryOperator {
    public BinaryOperator()
    {
        this.length_string = null;
        this.addition_field = null;
        this.and_op_field = null;
        this.equality_field = null;
        this.greater_than_eq_field = null;
        this.greater_than_field = null;
        this.less_than_eq_field = null;
        this.less_than_field = null;
        this.not_equality_field = null;
        this.or_op_field = null;
        this.subtraction_field = null;
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

    public void SetAddition(String input_value)
    {
        this.addition_field = input_value;
    }

    public String GetAddition()
    {
        return this.addition_field;
    }

    public void SetAndOp(String input_value)
    {
        this.and_op_field = input_value;
    }

    public String GetAndOp()
    {
        return this.and_op_field;
    }

    public void SetEquality(String input_value)
    {
        this.equality_field = input_value;
    }

    public String GetEquality()
    {
        return this.equality_field;
    }

    public void SetGreaterThanEq(String input_value)
    {
        this.greater_than_eq_field = input_value;
    }

    public String GetGreaterThanEq()
    {
        return this.greater_than_eq_field;
    }

    public void SetGreaterThan(String input_value)
    {
        this.greater_than_field = input_value;
    }

    public String GetGreaterThan()
    {
        return this.greater_than_field;
    }

    public void SetLessThanEq(String input_value)
    {
        this.less_than_eq_field = input_value;
    }

    public String GetLessThanEq()
    {
        return this.less_than_eq_field;
    }

    public void SetLessThan(String input_value)
    {
        this.less_than_field = input_value;
    }

    public String GetLessThan()
    {
        return this.less_than_field;
    }

    public void SetNotEquality(String input_value)
    {
        this.not_equality_field = input_value;
    }

    public String GetNotEquality()
    {
        return this.not_equality_field;
    }

    public void SetOrOp(String input_value)
    {
        this.or_op_field = input_value;
    }

    public String GetOrOp()
    {
        return this.or_op_field;
    }

    public void SetSubtraction(String input_value)
    {
        this.subtraction_field = input_value;
    }

    public String GetSubtraction()
    {
        return this.subtraction_field;
    }

    private LengthString length_string;
    private String addition_field;
    private String and_op_field;
    private String equality_field;
    private String greater_than_eq_field;
    private String greater_than_field;
    private String less_than_eq_field;
    private String less_than_field;
    private String not_equality_field;
    private String or_op_field;
    private String subtraction_field;

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
