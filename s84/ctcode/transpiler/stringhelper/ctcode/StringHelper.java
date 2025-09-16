package s84.ctcode.transpiler.stringhelper.ctcode;

import s84.ctcode.system.ctcode.*;

public class StringHelper {
    public StringHelper()
    {
    }

    public void WriteLines(s84.ctcode.system.ctcode.OutputStream destination, java.util.ArrayList<java.lang.String> lines)
    {
        int lines_index = 0;
        while (AsBoolean((lines_index<Size(lines))))
        {
            java.lang.String line = Element(lines, lines_index);
            destination.WriteLine(line);
            lines_index = (lines_index+1);
        }
    }

    public java.lang.String Indentation(int indent)
    {
        java.lang.String result = "";
        result = "";
        while (AsBoolean((indent>0)))
        {
            indent = (indent-1);
            result = Concat(result, "    ");
        }
        return result;
    }

    public boolean BeginsWith(java.lang.String prefix, java.lang.String value)
    {
        if (AsBoolean((Length(prefix)>Length(value))))
        {
            return false;
        }
        int prefix_index = 0;
        while (AsBoolean((prefix_index<Length(prefix))))
        {
            if (AsBoolean(!Equals(At(prefix, prefix_index),At(value, prefix_index))))
            {
                return false;
            }
            prefix_index = (prefix_index+1);
        }
        return true;
    }

    public java.lang.String StripDot(java.lang.String input)
    {
        int index = 0;
        index = 0;
        java.lang.String result = "";
        result = "";
        while (AsBoolean((index<Length(input))))
        {
            java.lang.String character = "";
            character = At(input, index);
            if (AsBoolean(Equals(character,".")))
            {
                result = Concat(result, "_");
            }
            else
            {
                result = Concat(result, character);
            }
            index = (index+1);
        }
        return result;
    }

    public java.lang.String SnakeCaseToCamelCase(java.lang.String snake_case)
    {
        boolean capitalize_this_letter = true;
        java.lang.String camel_case = "";
        int index = 0;
        index = 0;
        while (AsBoolean((index<Length(snake_case))))
        {
            java.lang.String source_character = At(snake_case, index);
            if (AsBoolean(Equals(source_character,"_")))
            {
                capitalize_this_letter = true;
            }
            else
            {
                if (AsBoolean(Equals(capitalize_this_letter,true)))
                {
                    java.lang.String upper_character = this.CharacterToUpper(source_character);
                    capitalize_this_letter = false;
                    camel_case = Concat(camel_case, upper_character);
                }
                else
                {
                    capitalize_this_letter = false;
                    camel_case = Concat(camel_case, source_character);
                }
            }
            index = (index+1);
        }
        return camel_case;
    }

    public java.lang.String CamelCaseToSnakeCase(java.lang.String camel_case)
    {
        java.lang.String delimiter = "_";
        java.lang.String snake_case = "";
        int index = 0;
        while (AsBoolean((index<Length(camel_case))))
        {
            java.lang.String source_character = At(camel_case, index);
            java.lang.String lower_character = this.CharacterToLower(source_character);
            if (AsBoolean((AsBoolean(this.IsUpper(source_character)) || AsBoolean(this.IsDigit(source_character)))))
            {
                boolean is_first_character = Equals(Length(snake_case),0);
                if (AsBoolean((! AsBoolean(is_first_character))))
                {
                    snake_case = Concat(snake_case, delimiter);
                }
            }
            snake_case = Concat(snake_case, lower_character);
            index = (index+1);
        }
        return snake_case;
    }

    public boolean IsUpper(java.lang.String character)
    {
        boolean result = false;
        result = false;
        result = (AsBoolean(result) || AsBoolean(Equals(character,"A")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"B")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"C")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"D")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"E")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"F")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"G")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"H")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"I")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"J")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"K")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"L")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"M")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"N")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"O")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"P")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"Q")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"R")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"S")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"T")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"U")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"V")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"W")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"X")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"Y")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"Z")));
        return result;
    }

    public boolean IsDigit(java.lang.String character)
    {
        boolean result = false;
        result = false;
        result = (AsBoolean(result) || AsBoolean(Equals(character,"0")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"1")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"2")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"3")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"4")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"5")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"6")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"7")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"8")));
        result = (AsBoolean(result) || AsBoolean(Equals(character,"9")));
        return result;
    }

    public java.lang.String ToLower(java.lang.String input)
    {
        int index = 0;
        java.lang.String result = "";
        while (AsBoolean((index<Length(input))))
        {
            java.lang.String character = At(input, index);
            java.lang.String lower_character = this.CharacterToLower(character);
            result = Concat(result, lower_character);
            index = (index+1);
        }
        return result;
    }

    public java.lang.String CharacterToLower(java.lang.String input)
    {
        if (AsBoolean(Equals(input,"A")))
        {
            return "a";
        }
        if (AsBoolean(Equals(input,"B")))
        {
            return "b";
        }
        if (AsBoolean(Equals(input,"C")))
        {
            return "c";
        }
        if (AsBoolean(Equals(input,"D")))
        {
            return "d";
        }
        if (AsBoolean(Equals(input,"E")))
        {
            return "e";
        }
        if (AsBoolean(Equals(input,"F")))
        {
            return "f";
        }
        if (AsBoolean(Equals(input,"G")))
        {
            return "g";
        }
        if (AsBoolean(Equals(input,"H")))
        {
            return "h";
        }
        if (AsBoolean(Equals(input,"I")))
        {
            return "i";
        }
        if (AsBoolean(Equals(input,"J")))
        {
            return "j";
        }
        if (AsBoolean(Equals(input,"K")))
        {
            return "k";
        }
        if (AsBoolean(Equals(input,"L")))
        {
            return "l";
        }
        if (AsBoolean(Equals(input,"M")))
        {
            return "m";
        }
        if (AsBoolean(Equals(input,"N")))
        {
            return "n";
        }
        if (AsBoolean(Equals(input,"O")))
        {
            return "o";
        }
        if (AsBoolean(Equals(input,"P")))
        {
            return "p";
        }
        if (AsBoolean(Equals(input,"Q")))
        {
            return "q";
        }
        if (AsBoolean(Equals(input,"R")))
        {
            return "r";
        }
        if (AsBoolean(Equals(input,"S")))
        {
            return "s";
        }
        if (AsBoolean(Equals(input,"T")))
        {
            return "t";
        }
        if (AsBoolean(Equals(input,"U")))
        {
            return "u";
        }
        if (AsBoolean(Equals(input,"V")))
        {
            return "v";
        }
        if (AsBoolean(Equals(input,"W")))
        {
            return "w";
        }
        if (AsBoolean(Equals(input,"X")))
        {
            return "x";
        }
        if (AsBoolean(Equals(input,"Y")))
        {
            return "y";
        }
        if (AsBoolean(Equals(input,"Z")))
        {
            return "z";
        }
        return input;
    }

    public java.lang.String ToUpper(java.lang.String input)
    {
        int index = 0;
        java.lang.String result = "";
        while (AsBoolean((index<Length(input))))
        {
            java.lang.String character = At(input, index);
            java.lang.String upper_character = this.CharacterToUpper(character);
            result = Concat(result, upper_character);
            index = (index+1);
        }
        return result;
    }

    public java.lang.String CharacterToUpper(java.lang.String input)
    {
        if (AsBoolean(Equals(input,"a")))
        {
            return "A";
        }
        if (AsBoolean(Equals(input,"b")))
        {
            return "B";
        }
        if (AsBoolean(Equals(input,"c")))
        {
            return "C";
        }
        if (AsBoolean(Equals(input,"d")))
        {
            return "D";
        }
        if (AsBoolean(Equals(input,"e")))
        {
            return "E";
        }
        if (AsBoolean(Equals(input,"f")))
        {
            return "F";
        }
        if (AsBoolean(Equals(input,"g")))
        {
            return "G";
        }
        if (AsBoolean(Equals(input,"h")))
        {
            return "H";
        }
        if (AsBoolean(Equals(input,"i")))
        {
            return "I";
        }
        if (AsBoolean(Equals(input,"j")))
        {
            return "J";
        }
        if (AsBoolean(Equals(input,"k")))
        {
            return "K";
        }
        if (AsBoolean(Equals(input,"l")))
        {
            return "L";
        }
        if (AsBoolean(Equals(input,"m")))
        {
            return "M";
        }
        if (AsBoolean(Equals(input,"n")))
        {
            return "N";
        }
        if (AsBoolean(Equals(input,"o")))
        {
            return "O";
        }
        if (AsBoolean(Equals(input,"p")))
        {
            return "P";
        }
        if (AsBoolean(Equals(input,"q")))
        {
            return "Q";
        }
        if (AsBoolean(Equals(input,"r")))
        {
            return "R";
        }
        if (AsBoolean(Equals(input,"s")))
        {
            return "S";
        }
        if (AsBoolean(Equals(input,"t")))
        {
            return "T";
        }
        if (AsBoolean(Equals(input,"u")))
        {
            return "U";
        }
        if (AsBoolean(Equals(input,"v")))
        {
            return "V";
        }
        if (AsBoolean(Equals(input,"w")))
        {
            return "W";
        }
        if (AsBoolean(Equals(input,"x")))
        {
            return "X";
        }
        if (AsBoolean(Equals(input,"y")))
        {
            return "Y";
        }
        if (AsBoolean(Equals(input,"z")))
        {
            return "Z";
        }
        return input;
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
    private static <T extends Object> boolean AsBoolean(T value) { return value != null; }
    private static boolean AsBoolean(boolean value) { return value; }
    private static boolean Equals(java.lang.String left, java.lang.String right) { return left.equals(right); }
    private static boolean Equals(boolean left, boolean right) { return left == right; }
    private static boolean Equals(int left, int right) { return left == right; }
    private static boolean Equals(float left, float right) { return left == right; }
}
