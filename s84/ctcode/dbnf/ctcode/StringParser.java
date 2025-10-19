package s84.ctcode.dbnf.ctcode;

public class StringParser {
    public StringParser()
    {
    }

    public boolean ParseSingleSave(LengthString index, java.lang.String value, StringResult result)
    {
        int index_start = index.GetStart();
        int index_length = index.GetLength();
        LargeString index_data = index.GetData();
        LengthString consumed_string = new LengthString();
        consumed_string.SetData(index.GetData());
        consumed_string.SetStart(index.GetStart());
        consumed_string.SetLength(0);
        ReservedPrefixString instance = new ReservedPrefixString();
        int value_length = Length(value);
        if (AsBoolean((value_length>index.GetLength())))
        {
            result.SetResult(false);
            return false;
        }
        int offset_index = 0;
        while (AsBoolean((offset_index<value_length)))
        {
            if (AsBoolean(!Equals(index_data.GetAt((index.GetStart()+offset_index)),At(value, offset_index))))
            {
                result.SetResult(false);
                return false;
            }
            offset_index = (offset_index+1);
        }
        index.SetStart((index.GetStart()+value_length));
        index.SetLength((index.GetLength()-value_length));
        consumed_string.SetLength((index.GetStart()-index_start));
        instance.SetLengthString(consumed_string);
        result.SetValue(instance);
        result.SetResult(true);
        return true;
    }

    public boolean ParseSingle(LengthString index, java.lang.String value)
    {
        StringResult result = new StringResult();
        return this.ParseSingleSave(index, value, result);
    }

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
