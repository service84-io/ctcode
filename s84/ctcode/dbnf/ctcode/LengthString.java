package s84.ctcode.dbnf.ctcode;

public class LengthString {
    public LengthString()
    {
        this.data = null;
        this.start = 0;
        this.length = 0;
    }

    public void SetData(LargeString new_data)
    {
        this.data = new_data;
    }

    public LargeString GetData()
    {
        return this.data;
    }

    public void SetStart(int new_start)
    {
        this.start = new_start;
    }

    public int GetStart()
    {
        return this.start;
    }

    public void SetLength(int new_length)
    {
        this.length = new_length;
    }

    public int GetLength()
    {
        return this.length;
    }

    public java.lang.String GetString()
    {
        java.lang.String deep_data = this.data.GetData();
        java.lang.String result = "";
        int index = this.start;
        int reserved_prefix_end = (this.start+this.length);
        while (AsBoolean((index<reserved_prefix_end)))
        {
            result = Concat(result, At(deep_data, index));
            index = (index+1);
        }
        return result;
    }

    private LargeString data;
    private int start;
    private int length;

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
