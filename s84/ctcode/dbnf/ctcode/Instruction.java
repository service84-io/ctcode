package s84.ctcode.dbnf.ctcode;

public class Instruction {
    public Instruction()
    {
        this.length_string = null;
        this.assignment_field = null;
        this.call_field = null;
        this.code_block_field = null;
        this.comment_field = null;
        this.conditional_field = null;
        this.declaration_field = null;
        this.loop_field = null;
        this.rtn_field = null;
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

    public void SetAssignment(Assignment input_value)
    {
        this.assignment_field = input_value;
    }

    public Assignment GetAssignment()
    {
        return this.assignment_field;
    }

    public void SetCall(Call input_value)
    {
        this.call_field = input_value;
    }

    public Call GetCall()
    {
        return this.call_field;
    }

    public void SetCodeBlock(CodeBlock input_value)
    {
        this.code_block_field = input_value;
    }

    public CodeBlock GetCodeBlock()
    {
        return this.code_block_field;
    }

    public void SetComment(Comment input_value)
    {
        this.comment_field = input_value;
    }

    public Comment GetComment()
    {
        return this.comment_field;
    }

    public void SetConditional(Conditional input_value)
    {
        this.conditional_field = input_value;
    }

    public Conditional GetConditional()
    {
        return this.conditional_field;
    }

    public void SetDeclaration(Declaration input_value)
    {
        this.declaration_field = input_value;
    }

    public Declaration GetDeclaration()
    {
        return this.declaration_field;
    }

    public void SetLoop(Loop input_value)
    {
        this.loop_field = input_value;
    }

    public Loop GetLoop()
    {
        return this.loop_field;
    }

    public void SetRtn(Return input_value)
    {
        this.rtn_field = input_value;
    }

    public Return GetRtn()
    {
        return this.rtn_field;
    }

    private LengthString length_string;
    private Assignment assignment_field;
    private Call call_field;
    private CodeBlock code_block_field;
    private Comment comment_field;
    private Conditional conditional_field;
    private Declaration declaration_field;
    private Loop loop_field;
    private Return rtn_field;

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
    private static <T extends Object> boolean AsBoolean(T value) { return value != null; }
    private static boolean AsBoolean(boolean value) { return value; }
    private static boolean Equals(java.lang.String left, java.lang.String right) { return left.equals(right); }
    private static boolean Equals(boolean left, boolean right) { return left == right; }
    private static boolean Equals(int left, int right) { return left == right; }
    private static boolean Equals(float left, float right) { return left == right; }
}
