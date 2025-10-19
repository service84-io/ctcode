package s84.ctcode.dbnf.ctcode;

public class Call {
    public Call()
    {
        this.length_string = null;
        this.function_chain_field = null;
        this.function_field = null;
        this.parameters_field = null;
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

    public void SetFunctionChain(QualfiedName input_value)
    {
        this.function_chain_field = input_value;
    }

    public QualfiedName GetFunctionChain()
    {
        return this.function_chain_field;
    }

    public void SetFunction(Name input_value)
    {
        this.function_field = input_value;
    }

    public Name GetFunction()
    {
        return this.function_field;
    }

    public void SetParameters(ParameterList input_value)
    {
        this.parameters_field = input_value;
    }

    public ParameterList GetParameters()
    {
        return this.parameters_field;
    }

    public void SetVariable(Name input_value)
    {
        this.variable_field = input_value;
    }

    public Name GetVariable()
    {
        return this.variable_field;
    }

    private LengthString length_string;
    private QualfiedName function_chain_field;
    private Name function_field;
    private ParameterList parameters_field;
    private Name variable_field;

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
