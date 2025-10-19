package s84.ctcode.dbnf.ctcode;

public class ValueType {
    public ValueType()
    {
        this.length_string = null;
        this.dimensional_type_field = null;
        this.map_type_field = null;
        this.singleton_type_field = null;
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

    public void SetDimensionalType(DimensionalType input_value)
    {
        this.dimensional_type_field = input_value;
    }

    public DimensionalType GetDimensionalType()
    {
        return this.dimensional_type_field;
    }

    public void SetMapType(MapType input_value)
    {
        this.map_type_field = input_value;
    }

    public MapType GetMapType()
    {
        return this.map_type_field;
    }

    public void SetSingletonType(SingletonType input_value)
    {
        this.singleton_type_field = input_value;
    }

    public SingletonType GetSingletonType()
    {
        return this.singleton_type_field;
    }

    private LengthString length_string;
    private DimensionalType dimensional_type_field;
    private MapType map_type_field;
    private SingletonType singleton_type_field;

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
