namespace S84.CTCode.Transpiler.StringHelper.ctcode;

public class StringHelper
{
    public StringHelper()
    {
    }

    public void WriteLines(S84.CTCode.System.ctcode.OutputStream? destination,List<string?>? lines)
    {
        int? lines_index = 0;
        while (AsBoolean(lines_index<Size(lines)))
        {
            string? line = Element(lines,lines_index);
            destination?.WriteLine(line);
            lines_index = lines_index+1;
        }
    }

    public bool? IsReserved(string? name)
    {
        return AsBoolean(AsBoolean(AsBoolean(AsBoolean(AsBoolean(AsBoolean(AsBoolean(AsBoolean(AsBoolean(AsBoolean(AsBoolean(AsBoolean(AsBoolean(AsBoolean(false)||AsBoolean(this?.BeginsWith("ReservedPrefix",name)))||AsBoolean(this?.BeginsWith("reserved_prefix_",name)))||AsBoolean(name=="GetType"))||AsBoolean(name=="Object"))||AsBoolean(name=="Return"))||AsBoolean(name=="String"))||AsBoolean(name=="boolean"))||AsBoolean(name=="char"))||AsBoolean(name=="decimal"))||AsBoolean(name=="end"))||AsBoolean(name=="float"))||AsBoolean(name=="object"))||AsBoolean(name=="string"))||AsBoolean(false);
    }

    public string? Indentation(int? indent)
    {
        string? result = "";
        result = "";
        while (AsBoolean(indent>0))
        {
            indent = indent-1;
            result = Concat(result,"    ");
        }
        return result;
    }

    public bool? BeginsWith(string? prefix,string? value)
    {
        if (AsBoolean(Length(prefix)>Length(value)))
        {
            return false;
        }
        int? prefix_index = 0;
        while (AsBoolean(prefix_index<Length(prefix)))
        {
            if (AsBoolean(At(prefix,prefix_index)!=At(value,prefix_index)))
            {
                return false;
            }
            prefix_index = prefix_index+1;
        }
        return true;
    }

    public string? DotToSlash(string? input)
    {
        string? result = "";
        int? input_index = 0;
        while (AsBoolean(input_index<Length(input)))
        {
            string? character = At(input,input_index);
            if (AsBoolean(character=="."))
            {
                result = Concat(result,"/");
            }
            else
            {
                result = Concat(result,character);
            }
            input_index = input_index+1;
        }
        return result;
    }

    public string? DotToFwdSlash(string? input)
    {
        string? result = "";
        int? input_index = 0;
        while (AsBoolean(input_index<Length(input)))
        {
            string? character = At(input,input_index);
            if (AsBoolean(character=="."))
            {
                result = Concat(result,"\\");
            }
            else
            {
                result = Concat(result,character);
            }
            input_index = input_index+1;
        }
        return result;
    }

    public string? StripDot(string? input)
    {
        int? index = 0;
        index = 0;
        string? result = "";
        result = "";
        while (AsBoolean(index<Length(input)))
        {
            string? character = "";
            character = At(input,index);
            if (AsBoolean(character=="."))
            {
                result = Concat(result,"_");
            }
            else
            {
                result = Concat(result,character);
            }
            index = index+1;
        }
        return result;
    }

    public string? SnakeCaseToCamelCase(string? snake_case)
    {
        bool? capitalize_this_letter = true;
        string? camel_case = "";
        int? index = 0;
        index = 0;
        while (AsBoolean(index<Length(snake_case)))
        {
            string? source_character = At(snake_case,index);
            if (AsBoolean(source_character=="_"))
            {
                capitalize_this_letter = true;
            }
            else
            {
                if (AsBoolean(capitalize_this_letter==true))
                {
                    string? upper_character = this?.CharacterToUpper(source_character);
                    capitalize_this_letter = false;
                    camel_case = Concat(camel_case,upper_character);
                }
                else
                {
                    capitalize_this_letter = false;
                    camel_case = Concat(camel_case,source_character);
                }
            }
            index = index+1;
        }
        return camel_case;
    }

    public string? CamelCaseToSnakeCase(string? camel_case)
    {
        string? delimiter = "_";
        string? snake_case = "";
        int? index = 0;
        while (AsBoolean(index<Length(camel_case)))
        {
            string? source_character = At(camel_case,index);
            string? lower_character = this?.CharacterToLower(source_character);
            if (AsBoolean(AsBoolean(this?.IsUpper(source_character))||AsBoolean(this?.IsDigit(source_character))))
            {
                bool? is_first_character = Length(snake_case)==0;
                if (AsBoolean(!is_first_character))
                {
                    snake_case = Concat(snake_case,delimiter);
                }
            }
            snake_case = Concat(snake_case,lower_character);
            index = index+1;
        }
        return snake_case;
    }

    public bool? IsUpper(string? character)
    {
        bool? result = false;
        result = false;
        result = AsBoolean(result)||AsBoolean(character=="A");
        result = AsBoolean(result)||AsBoolean(character=="B");
        result = AsBoolean(result)||AsBoolean(character=="C");
        result = AsBoolean(result)||AsBoolean(character=="D");
        result = AsBoolean(result)||AsBoolean(character=="E");
        result = AsBoolean(result)||AsBoolean(character=="F");
        result = AsBoolean(result)||AsBoolean(character=="G");
        result = AsBoolean(result)||AsBoolean(character=="H");
        result = AsBoolean(result)||AsBoolean(character=="I");
        result = AsBoolean(result)||AsBoolean(character=="J");
        result = AsBoolean(result)||AsBoolean(character=="K");
        result = AsBoolean(result)||AsBoolean(character=="L");
        result = AsBoolean(result)||AsBoolean(character=="M");
        result = AsBoolean(result)||AsBoolean(character=="N");
        result = AsBoolean(result)||AsBoolean(character=="O");
        result = AsBoolean(result)||AsBoolean(character=="P");
        result = AsBoolean(result)||AsBoolean(character=="Q");
        result = AsBoolean(result)||AsBoolean(character=="R");
        result = AsBoolean(result)||AsBoolean(character=="S");
        result = AsBoolean(result)||AsBoolean(character=="T");
        result = AsBoolean(result)||AsBoolean(character=="U");
        result = AsBoolean(result)||AsBoolean(character=="V");
        result = AsBoolean(result)||AsBoolean(character=="W");
        result = AsBoolean(result)||AsBoolean(character=="X");
        result = AsBoolean(result)||AsBoolean(character=="Y");
        result = AsBoolean(result)||AsBoolean(character=="Z");
        return result;
    }

    public bool? IsDigit(string? character)
    {
        bool? result = false;
        result = false;
        result = AsBoolean(result)||AsBoolean(character=="0");
        result = AsBoolean(result)||AsBoolean(character=="1");
        result = AsBoolean(result)||AsBoolean(character=="2");
        result = AsBoolean(result)||AsBoolean(character=="3");
        result = AsBoolean(result)||AsBoolean(character=="4");
        result = AsBoolean(result)||AsBoolean(character=="5");
        result = AsBoolean(result)||AsBoolean(character=="6");
        result = AsBoolean(result)||AsBoolean(character=="7");
        result = AsBoolean(result)||AsBoolean(character=="8");
        result = AsBoolean(result)||AsBoolean(character=="9");
        return result;
    }

    public string? ToLower(string? input)
    {
        int? index = 0;
        string? result = "";
        while (AsBoolean(index<Length(input)))
        {
            string? character = At(input,index);
            string? lower_character = this?.CharacterToLower(character);
            result = Concat(result,lower_character);
            index = index+1;
        }
        return result;
    }

    public string? CharacterToLower(string? input)
    {
        if (AsBoolean(input=="A"))
        {
            return "a";
        }
        if (AsBoolean(input=="B"))
        {
            return "b";
        }
        if (AsBoolean(input=="C"))
        {
            return "c";
        }
        if (AsBoolean(input=="D"))
        {
            return "d";
        }
        if (AsBoolean(input=="E"))
        {
            return "e";
        }
        if (AsBoolean(input=="F"))
        {
            return "f";
        }
        if (AsBoolean(input=="G"))
        {
            return "g";
        }
        if (AsBoolean(input=="H"))
        {
            return "h";
        }
        if (AsBoolean(input=="I"))
        {
            return "i";
        }
        if (AsBoolean(input=="J"))
        {
            return "j";
        }
        if (AsBoolean(input=="K"))
        {
            return "k";
        }
        if (AsBoolean(input=="L"))
        {
            return "l";
        }
        if (AsBoolean(input=="M"))
        {
            return "m";
        }
        if (AsBoolean(input=="N"))
        {
            return "n";
        }
        if (AsBoolean(input=="O"))
        {
            return "o";
        }
        if (AsBoolean(input=="P"))
        {
            return "p";
        }
        if (AsBoolean(input=="Q"))
        {
            return "q";
        }
        if (AsBoolean(input=="R"))
        {
            return "r";
        }
        if (AsBoolean(input=="S"))
        {
            return "s";
        }
        if (AsBoolean(input=="T"))
        {
            return "t";
        }
        if (AsBoolean(input=="U"))
        {
            return "u";
        }
        if (AsBoolean(input=="V"))
        {
            return "v";
        }
        if (AsBoolean(input=="W"))
        {
            return "w";
        }
        if (AsBoolean(input=="X"))
        {
            return "x";
        }
        if (AsBoolean(input=="Y"))
        {
            return "y";
        }
        if (AsBoolean(input=="Z"))
        {
            return "z";
        }
        return input;
    }

    public string? ToUpper(string? input)
    {
        int? index = 0;
        string? result = "";
        while (AsBoolean(index<Length(input)))
        {
            string? character = At(input,index);
            string? upper_character = this?.CharacterToUpper(character);
            result = Concat(result,upper_character);
            index = index+1;
        }
        return result;
    }

    public string? CharacterToUpper(string? input)
    {
        if (AsBoolean(input=="a"))
        {
            return "A";
        }
        if (AsBoolean(input=="b"))
        {
            return "B";
        }
        if (AsBoolean(input=="c"))
        {
            return "C";
        }
        if (AsBoolean(input=="d"))
        {
            return "D";
        }
        if (AsBoolean(input=="e"))
        {
            return "E";
        }
        if (AsBoolean(input=="f"))
        {
            return "F";
        }
        if (AsBoolean(input=="g"))
        {
            return "G";
        }
        if (AsBoolean(input=="h"))
        {
            return "H";
        }
        if (AsBoolean(input=="i"))
        {
            return "I";
        }
        if (AsBoolean(input=="j"))
        {
            return "J";
        }
        if (AsBoolean(input=="k"))
        {
            return "K";
        }
        if (AsBoolean(input=="l"))
        {
            return "L";
        }
        if (AsBoolean(input=="m"))
        {
            return "M";
        }
        if (AsBoolean(input=="n"))
        {
            return "N";
        }
        if (AsBoolean(input=="o"))
        {
            return "O";
        }
        if (AsBoolean(input=="p"))
        {
            return "P";
        }
        if (AsBoolean(input=="q"))
        {
            return "Q";
        }
        if (AsBoolean(input=="r"))
        {
            return "R";
        }
        if (AsBoolean(input=="s"))
        {
            return "S";
        }
        if (AsBoolean(input=="t"))
        {
            return "T";
        }
        if (AsBoolean(input=="u"))
        {
            return "U";
        }
        if (AsBoolean(input=="v"))
        {
            return "V";
        }
        if (AsBoolean(input=="w"))
        {
            return "W";
        }
        if (AsBoolean(input=="x"))
        {
            return "X";
        }
        if (AsBoolean(input=="y"))
        {
            return "Y";
        }
        if (AsBoolean(input=="z"))
        {
            return "Z";
        }
        return input;
    }

    private static void ClearList<T>(List<T>? input) { input?.Clear(); }
    private static int? Size<T>(List<T>? input) { return input?.Count; }
    private static T? Element<T>(List<T>? input, int? element) { return input != null ? input[element??0] : default; }
    private static void Append<T>(List<T>? input, T element) { input?.Add(element); }
    private static void ClearMap<T>(Dictionary<string, T>? input) { input?.Clear();  }
    private static void SetKV<T>(Dictionary<string, T>? input, string? key, T element) { input?.Add(key??"", element); }
    private static List<string?>? Keys<T>(Dictionary<string, T>? input) { return new List<string?>(input?.Keys?.ToList()??new List<string>()); }
    private static bool? HasKV<T>(Dictionary<string, T>? input, string? key) { return input?.ContainsKey(key??""); }
    private static T? GetKV<T>(Dictionary<string, T>? input, string? key) { return input != null ? input[key??""] : default; }
    private static int? Length(string? input) { return input?.Length;  }
    private static string? At(string? input, int? index) { return input?.Length > index ? input?.Substring(index??0, 1) : "";  }
    private static int? IntAt(string? input, int? index) { return input?.Length > index ? (input[index??0] + 255 % 255) : 0;  }
    private static string? Concat(string? left, string? right) { return left + right; }
    private static bool AsBoolean(bool value) { return value; }
    private static bool AsBoolean<T>(T? value) { return value != null && !value.Equals(false); }
}
