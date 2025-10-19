namespace S84.CTCode.Transpiler.StandardStructure.ctcode;

public interface TargetSpecificFunctions
{
    void Initialize();
    void SetSystem(S84.CTCode.System.ctcode.System? system);
    void SetCTCodeFile(S84.CTCode.dbnf.ctcode.CTCodeFile? c_t_code_file);
    void SetBaseName(string? base_name);
    void SetLogger(S84.CTCode.System.ctcode.OutputStream? logger);
    int? GetBaseIndentation();
    string? GetCallName(string? name);
    string? GetVariableName(string? name);
    string? GetVariableChain(List<string?>? name_parts);
    string? ConvertCall(List<string?>? name_chain,List<string?>? parameters);
    string? ConvertAllocate(string? type);
    string? ConvertByte(string? high,string? low);
    string? ConvertDecimal(string? reserved_prefix_decimal);
    string? ConvertNumber(string? number);
    string? ConvertBoolean(string? reserved_prefix_boolean);
    string? ConvertVariable(string? variable);
    string? ConvertString(string? literal);
    string? UnaryOperator(string? op,string? r_value);
    string? BinaryOperator(string? op,string? r_value_l,string? r_value_r);
    string? GetTypeName(string? name);
    string? GetDimensionalType(string? singleton_type,int? dimensions);
    string? GetMapType(string? singleton_type);
    string? GetPrimativeType(string? c_t_type);
    string? GetDefinedType(string? c_t_type);
    string? GetQualifiedTypeName(List<string?>? name_parts);
    void BeginProcessingCTCodeFile();
    void FinishProcessingCTCodeFile();
    void ProcessExdef(string? exdef);
    void ProcessUnmanagedType(string? unmanaged_type);
    void BeginProcessingInterface(string? interface_name);
    void ProcessInterfaceFunctionDeclaration(string? return_type,string? function_name,List<ParameterDeclaration?>? parameters);
    void FinishProcessingInterface(string? interface_name);
    void BeginProcessingClass(string? class_name,string? implementing);
    void BeginProcessingClassFunctionDefinition(string? return_type,string? function_name,List<ParameterDeclaration?>? parameters);
    void BeginProcessCodeBlock(int? indent);
    void FinishProcessCodeBlock(int? indent);
    void BeginProcessConditional(int? indent,string? r_value);
    void ProcessElse(int? indent);
    void FinishProcessConditional(int? indent,string? r_value);
    void BeginProcessLoop(int? indent,string? r_value);
    void FinishProcessLoop(int? indent,string? r_value);
    void ProcessRtn(int? indent,string? r_value);
    void ProcessDeclaration(int? indent,string? type,string? l_value,string? r_value);
    void ProcessAssignment(int? indent,string? l_value,string? r_value);
    void ProcessCall(int? indent,string? call);
    void FinishProcessingClassFunctionDefinition(string? return_type,string? function_name,List<ParameterDeclaration?>? parameters);
    void ProcessClassMemberDeclaration(string? member_type,string? member_name);
    void FinishProcessingClass(string? class_name,string? implementing);
}

public class ParameterDeclaration
{
    private string? type;
    private string? name;

    public ParameterDeclaration()
    {
        this.type = "";
        this.name = "";
    }

    public string? ReservedPrefixGetType()
    {
        return this?.type;
    }

    public void SetType(string? input)
    {
        this.type = input;
    }

    public string? GetName()
    {
        return this?.name;
    }

    public void SetName(string? input)
    {
        this.name = input;
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
public class IntegerReference
{
    private int? value;

    public IntegerReference()
    {
        this.value = 0;
    }

    public int? GetValue()
    {
        return this?.value;
    }

    public void SetValue(int? value)
    {
        this.value = value;
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
public class StandardStructure : S84.CTCode.Transpiler.ctcode.Transpiler
{
    private S84.CTCode.System.ctcode.System? system;
    private S84.CTCode.dbnf.ctcode.CTCodeFile? c_t_code_file;
    private string? base_name;
    private List<List<string?>?>? operator_precedent;
    private S84.CTCode.System.ctcode.OutputStream? logger;
    private TargetSpecificFunctions? target_specific_functions;

    public StandardStructure()
    {
        this.system = null;
        this.c_t_code_file = null;
        this.base_name = "";
        this.operator_precedent = new List<List<string?>?>();
        this.logger = null;
        this.target_specific_functions = null;
    }

    public void SetTargetSpecificFunctions(TargetSpecificFunctions? target_specific_functions)
    {
        this.target_specific_functions = target_specific_functions;
    }

    public int? Transpile(S84.CTCode.System.ctcode.System? system,S84.CTCode.dbnf.ctcode.CTCodeFile? c_t_code_file,string? base_name)
    {
        ClearList(this?.operator_precedent);
        this?.PopulateOperatorPrecedent();
        this.system = system;
        this.c_t_code_file = c_t_code_file;
        this.base_name = base_name;
        this.logger = system?.GetLoggerDestination();
        this?.target_specific_functions?.SetSystem(this?.system);
        this?.target_specific_functions?.SetCTCodeFile(this?.c_t_code_file);
        this?.target_specific_functions?.SetBaseName(this?.base_name);
        this?.target_specific_functions?.SetLogger(this?.logger);
        this?.ProcessCTCodeFile(c_t_code_file);
        return 0;
    }

    public void ProcessCTCodeFile(S84.CTCode.dbnf.ctcode.CTCodeFile? c_t_code_file)
    {
        this?.target_specific_functions?.BeginProcessingCTCodeFile();
        this?.ProcessExdefs(c_t_code_file);
        this?.ProcessUnmanagedTypes(c_t_code_file);
        this?.ProcessDefinitions(c_t_code_file);
        this?.target_specific_functions?.FinishProcessingCTCodeFile();
    }

    public void ProcessExdefs(S84.CTCode.dbnf.ctcode.CTCodeFile? c_t_code_file)
    {
        List<S84.CTCode.dbnf.ctcode.ExternalDefinition?>? exdefs = c_t_code_file?.GetDeclarations();
        int? exdefs_index = 0;
        while (AsBoolean(exdefs_index<Size(exdefs)))
        {
            S84.CTCode.dbnf.ctcode.ExternalDefinition? exdef = Element(exdefs,exdefs_index);
            S84.CTCode.dbnf.ctcode.QualfiedName? exdef_name = exdef?.GetExdef();
            this?.target_specific_functions?.ProcessExdef(exdef_name?.UnParse());
            exdefs_index = exdefs_index+1;
        }
    }

    public void ProcessUnmanagedTypes(S84.CTCode.dbnf.ctcode.CTCodeFile? c_t_code_file)
    {
        List<S84.CTCode.dbnf.ctcode.UnmanagedType?>? unmanaged_types = c_t_code_file?.GetUnmanagedTypes();
        int? unmanaged_types_index = 0;
        while (AsBoolean(unmanaged_types_index<Size(unmanaged_types)))
        {
            S84.CTCode.dbnf.ctcode.UnmanagedType? unmanaged_type = Element(unmanaged_types,unmanaged_types_index);
            this?.target_specific_functions?.ProcessUnmanagedType(this?.GetQualifiedTypeNameInternal(unmanaged_type?.GetUnmanagedType()));
            unmanaged_types_index = unmanaged_types_index+1;
        }
    }

    public void ProcessDefinitions(S84.CTCode.dbnf.ctcode.CTCodeFile? c_t_code_file)
    {
        List<S84.CTCode.dbnf.ctcode.Definition?>? definitions = c_t_code_file?.GetDefinitions();
        int? definitions_index = 0;
        while (AsBoolean(definitions_index<Size(definitions)))
        {
            S84.CTCode.dbnf.ctcode.Definition? definition = null;
            definition = Element(definitions,definitions_index);
            if (AsBoolean(definition?.GetInterfaceDef()))
            {
                this?.ProcessInterfaceDefinition(definition?.GetInterfaceDef());
            }
            if (AsBoolean(definition?.GetClassDef()))
            {
                this?.ProcessClassDefinition(definition?.GetClassDef());
            }
            definitions_index = definitions_index+1;
        }
    }

    public List<ParameterDeclaration?>? GetParameters(S84.CTCode.dbnf.ctcode.ParameterListDef? parameter_list_def)
    {
        List<ParameterDeclaration?>? result = new List<ParameterDeclaration?>();
        while (AsBoolean(parameter_list_def))
        {
            ParameterDeclaration? parameter = new ParameterDeclaration();
            parameter?.SetType(this?.ReservedPrefixGetType(parameter_list_def?.ReservedPrefixGetType()));
            parameter?.SetName(this?.target_specific_functions?.GetVariableName(this?.NameToString(parameter_list_def?.GetName())));
            Append(result,parameter);
            parameter_list_def = parameter_list_def?.GetParameterTail();
        }
        return result;
    }

    public void ProcessInterfaceDefinition(S84.CTCode.dbnf.ctcode.InterfaceDef? interface_definition)
    {
        string? interface_name = this?.target_specific_functions?.GetTypeName(this?.NameToString(interface_definition?.GetName()));
        this?.target_specific_functions?.BeginProcessingInterface(interface_name);
        List<S84.CTCode.dbnf.ctcode.ContentDeclaration?>? declarations = interface_definition?.GetDeclarations();
        int? declarations_index = 0;
        while (AsBoolean(declarations_index<Size(declarations)))
        {
            S84.CTCode.dbnf.ctcode.ContentDeclaration? declaration = Element(declarations,declarations_index);
            string? return_type = this?.ReservedPrefixGetType(declaration?.ReservedPrefixGetType());
            string? function_name = this?.target_specific_functions?.GetCallName(this?.NameToString(declaration?.GetName()));
            List<ParameterDeclaration?>? parameters = this?.GetParameters(declaration?.GetParameters());
            this?.target_specific_functions?.ProcessInterfaceFunctionDeclaration(return_type,function_name,parameters);
            declarations_index = declarations_index+1;
        }
        this?.target_specific_functions?.FinishProcessingInterface(interface_name);
    }

    public void ProcessClassDefinition(S84.CTCode.dbnf.ctcode.ClassDef? class_definition)
    {
        string? class_name = this?.target_specific_functions?.GetTypeName(this?.NameToString(class_definition?.GetName()));
        string? implementing = "";
        S84.CTCode.dbnf.ctcode.ImplementationSpec? implementation_spec = class_definition?.GetImplementing();
        if (AsBoolean(implementation_spec))
        {
            implementing = this?.GetQualifiedTypeNameInternal(implementation_spec?.GetInterface());
        }
        this?.target_specific_functions?.BeginProcessingClass(class_name,implementing);
        List<S84.CTCode.dbnf.ctcode.ContentDefinition?>? definitions = class_definition?.GetDefinitions();
        int? definitions_index = 0;
        while (AsBoolean(definitions_index<Size(definitions)))
        {
            S84.CTCode.dbnf.ctcode.ContentDefinition? definition = Element(definitions,definitions_index);
            if (AsBoolean(definition?.GetFunctionBody()))
            {
                string? return_type = this?.ReservedPrefixGetType(definition?.ReservedPrefixGetType());
                string? function_name = this?.target_specific_functions?.GetCallName(this?.NameToString(definition?.GetName()));
                List<ParameterDeclaration?>? parameters = this?.GetParameters(definition?.GetParameters());
                this?.target_specific_functions?.BeginProcessingClassFunctionDefinition(return_type,function_name,parameters);
                this?.ProcessCodeBlockInternal(this?.target_specific_functions?.GetBaseIndentation(),definition?.GetFunctionBody());
                this?.target_specific_functions?.FinishProcessingClassFunctionDefinition(return_type,function_name,parameters);
            }
            else
            {
                string? member_type = this?.ReservedPrefixGetType(definition?.ReservedPrefixGetType());
                string? member_name = this?.target_specific_functions?.GetVariableName(this?.NameToString(definition?.GetName()));
                this?.target_specific_functions?.ProcessClassMemberDeclaration(member_type,member_name);
            }
            definitions_index = definitions_index+1;
        }
        this?.target_specific_functions?.FinishProcessingClass(class_name,implementing);
    }

    public void ProcessInstructionInternal(int? indent,S84.CTCode.dbnf.ctcode.Instruction? instruction)
    {
        if (AsBoolean(instruction?.GetCodeBlock()))
        {
            this?.ProcessCodeBlockInternal(indent,instruction?.GetCodeBlock());
        }
        if (AsBoolean(instruction?.GetRtn()))
        {
            this?.ProcessRtnInternal(indent,instruction?.GetRtn());
        }
        if (AsBoolean(instruction?.GetDeclaration()))
        {
            this?.ProcessDeclarationInternal(indent,instruction?.GetDeclaration());
        }
        if (AsBoolean(instruction?.GetAssignment()))
        {
            this?.ProcessAssignmentInternal(indent,instruction?.GetAssignment());
        }
        if (AsBoolean(instruction?.GetCall()))
        {
            this?.ProcessCallInternal(indent,instruction?.GetCall());
        }
        if (AsBoolean(instruction?.GetConditional()))
        {
            this?.ProcessConditionalInternal(indent,instruction?.GetConditional());
        }
        if (AsBoolean(instruction?.GetLoop()))
        {
            this?.ProcessLoopInternal(indent,instruction?.GetLoop());
        }
    }

    public void ProcessCodeBlockInternal(int? indent,S84.CTCode.dbnf.ctcode.CodeBlock? code_block)
    {
        this?.target_specific_functions?.BeginProcessCodeBlock(indent);
        List<S84.CTCode.dbnf.ctcode.Instruction?>? instructions = code_block?.GetInstructions();
        int? instructions_index = 0;
        while (AsBoolean(instructions_index<Size(instructions)))
        {
            this?.ProcessInstructionInternal(indent+1,Element(instructions,instructions_index));
            instructions_index = instructions_index+1;
        }
        this?.target_specific_functions?.FinishProcessCodeBlock(indent);
    }

    public void ProcessConditionalInternal(int? indent,S84.CTCode.dbnf.ctcode.Conditional? conditional)
    {
        string? r_value = this?.GetRValueInternal(conditional?.GetRValue());
        this?.target_specific_functions?.BeginProcessConditional(indent,r_value);
        this?.ProcessCodeBlockInternal(indent,conditional?.GetCodeBlock());
        if (AsBoolean(conditional?.GetElseTail()))
        {
            S84.CTCode.dbnf.ctcode.ElseTail? else_tail = conditional?.GetElseTail();
            this?.target_specific_functions?.ProcessElse(indent);
            this?.ProcessCodeBlockInternal(indent,else_tail?.GetCodeBlock());
        }
        this?.target_specific_functions?.FinishProcessConditional(indent,r_value);
    }

    public void ProcessLoopInternal(int? indent,S84.CTCode.dbnf.ctcode.Loop? loop)
    {
        string? r_value = this?.GetRValueInternal(loop?.GetRValue());
        this?.target_specific_functions?.BeginProcessLoop(indent,r_value);
        this?.ProcessCodeBlockInternal(indent,loop?.GetCodeBlock());
        this?.target_specific_functions?.FinishProcessLoop(indent,r_value);
    }

    public void ProcessRtnInternal(int? indent,S84.CTCode.dbnf.ctcode.ReservedPrefixReturn? rtn)
    {
        string? r_value = this?.GetRValueInternal(rtn?.GetRValue());
        this?.target_specific_functions?.ProcessRtn(indent,r_value);
    }

    public void ProcessDeclarationInternal(int? indent,S84.CTCode.dbnf.ctcode.Declaration? declaration)
    {
        string? type = this?.ReservedPrefixGetType(declaration?.ReservedPrefixGetType());
        string? l_value = this?.target_specific_functions?.GetVariableName(this?.NameToString(declaration?.GetName()));
        string? r_value = "";
        S84.CTCode.dbnf.ctcode.DeclarationAssign? declaration_assignment = declaration?.GetAssignment();
        if (AsBoolean(declaration_assignment))
        {
            r_value = this?.GetRValueInternal(declaration_assignment?.GetRValue());
        }
        this?.target_specific_functions?.ProcessDeclaration(indent,type,l_value,r_value);
    }

    public void ProcessAssignmentInternal(int? indent,S84.CTCode.dbnf.ctcode.Assignment? assignment)
    {
        this?.target_specific_functions?.ProcessAssignment(indent,this?.GetVariableChainInternal(assignment?.GetLValue()),this?.GetRValueInternal(assignment?.GetRValue()));
    }

    public void ProcessCallInternal(int? indent,S84.CTCode.dbnf.ctcode.Call? call)
    {
        this?.target_specific_functions?.ProcessCall(indent,this?.ConvertCallInternal(call));
    }

    public string? ConvertCallInternal(S84.CTCode.dbnf.ctcode.Call? call)
    {
        List<string?>? name_chain = new List<string?>();
        List<string?>? parameters = new List<string?>();
        if (AsBoolean(call?.GetVariable()))
        {
            Append(name_chain,this?.target_specific_functions?.GetVariableName(this?.NameToString(call?.GetVariable())));
        }
        if (AsBoolean(call?.GetFunction()))
        {
            Append(name_chain,this?.target_specific_functions?.GetCallName(this?.NameToString(call?.GetFunction())));
        }
        if (AsBoolean(call?.GetFunctionChain()))
        {
            S84.CTCode.dbnf.ctcode.QualfiedName? function_chain = call?.GetFunctionChain();
            S84.CTCode.dbnf.ctcode.NameTail? name_tail = function_chain?.GetTail();
            if (AsBoolean(function_chain?.GetTail()))
            {
                Append(name_chain,this?.target_specific_functions?.GetVariableName(this?.NameToString(function_chain?.GetName())));
            }
            else
            {
                Append(name_chain,this?.target_specific_functions?.GetCallName(this?.NameToString(function_chain?.GetName())));
            }
            while (AsBoolean(name_tail))
            {
                if (AsBoolean(name_tail?.GetTail()))
                {
                    Append(name_chain,this?.target_specific_functions?.GetVariableName(this?.NameToString(name_tail?.GetName())));
                }
                else
                {
                    Append(name_chain,this?.target_specific_functions?.GetCallName(this?.NameToString(name_tail?.GetName())));
                }
                name_tail = name_tail?.GetTail();
            }
        }
        S84.CTCode.dbnf.ctcode.ParameterList? parameter_list = call?.GetParameters();
        while (AsBoolean(parameter_list))
        {
            Append(parameters,this?.GetRValueInternal(parameter_list?.GetRValue()));
            parameter_list = parameter_list?.GetParameterTail();
        }
        return this?.target_specific_functions?.ConvertCall(name_chain,parameters);
    }

    public string? GetSingletonType(S84.CTCode.dbnf.ctcode.SingletonType? singleton_type)
    {
        if (AsBoolean(singleton_type?.GetPrimativeType()))
        {
            return this?.target_specific_functions?.GetPrimativeType(singleton_type?.UnParse());
        }
        if (AsBoolean(singleton_type?.GetDefinedType()))
        {
            S84.CTCode.dbnf.ctcode.DefinedType? defined_type = singleton_type?.GetDefinedType();
            return this?.target_specific_functions?.GetDefinedType(this?.GetQualifiedTypeNameInternal(defined_type?.GetName()));
        }
        return "";
    }

    public string? GetRValueSingleBasisInternal(S84.CTCode.dbnf.ctcode.RValueSingle? r_value_single)
    {
        S84.CTCode.dbnf.ctcode.Call? call = r_value_single?.GetCall();
        if (AsBoolean(call))
        {
            return this?.ConvertCallInternal(call);
        }
        S84.CTCode.dbnf.ctcode.Allocate? allocate = r_value_single?.GetAllocate();
        if (AsBoolean(allocate))
        {
            return this?.target_specific_functions?.ConvertAllocate(this?.GetQualifiedTypeNameInternal(allocate?.GetManagedType()));
        }
        S84.CTCode.dbnf.ctcode.Byte? byte_literal = r_value_single?.GetByteLiteral();
        if (AsBoolean(byte_literal))
        {
            S84.CTCode.dbnf.ctcode.ByteDigit? high = byte_literal?.GetHigh();
            S84.CTCode.dbnf.ctcode.ByteDigit? low = byte_literal?.GetLow();
            return this?.target_specific_functions?.ConvertByte(high?.UnParse(),low?.UnParse());
        }
        S84.CTCode.dbnf.ctcode.Decimal? decimal_literal = r_value_single?.GetDecimalLiteral();
        if (AsBoolean(decimal_literal))
        {
            return this?.target_specific_functions?.ConvertDecimal(decimal_literal?.UnParse());
        }
        S84.CTCode.dbnf.ctcode.Number? integer_literal = r_value_single?.GetIntegerLiteral();
        if (AsBoolean(integer_literal))
        {
            return this?.target_specific_functions?.ConvertNumber(integer_literal?.UnParse());
        }
        S84.CTCode.dbnf.ctcode.Boolean? boolean_literal = r_value_single?.GetBooleanLiteral();
        if (AsBoolean(boolean_literal))
        {
            return this?.target_specific_functions?.ConvertBoolean(boolean_literal?.UnParse());
        }
        S84.CTCode.dbnf.ctcode.QualfiedName? variable = r_value_single?.GetVariable();
        if (AsBoolean(variable))
        {
            return this?.target_specific_functions?.ConvertVariable(this?.GetVariableChainInternal(variable));
        }
        S84.CTCode.dbnf.ctcode.Literal? string_literal = r_value_single?.GetStringLiteral();
        if (AsBoolean(string_literal))
        {
            return this?.target_specific_functions?.ConvertString(string_literal?.UnParse());
        }
        return "";
    }

    public string? GetRValueSingleInternal(S84.CTCode.dbnf.ctcode.RValueSingle? r_value_single)
    {
        S84.CTCode.dbnf.ctcode.UnaryOperator? unary_operator = r_value_single?.GetUnaryOperator();
        if (AsBoolean(unary_operator))
        {
            return this?.target_specific_functions?.UnaryOperator(unary_operator?.UnParse(),this?.GetRValueSingleBasisInternal(r_value_single));
        }
        return this?.GetRValueSingleBasisInternal(r_value_single);
    }

    public void PopulateOperatorPrecedent()
    {
        List<string?>? precedent__0_operators = new List<string?>();
        Append(precedent__0_operators,"+");
        Append(precedent__0_operators,"-");
        Append(this?.operator_precedent,precedent__0_operators);
        List<string?>? precedent__1_operators = new List<string?>();
        Append(precedent__1_operators,"<=");
        Append(precedent__1_operators,">=");
        Append(precedent__1_operators,"==");
        Append(precedent__1_operators,"!=");
        Append(precedent__1_operators,"<");
        Append(precedent__1_operators,">");
        Append(this?.operator_precedent,precedent__1_operators);
        List<string?>? precedent__2_operators = new List<string?>();
        Append(precedent__2_operators,"&&");
        Append(this?.operator_precedent,precedent__2_operators);
        List<string?>? precedent__3_operators = new List<string?>();
        Append(precedent__3_operators,"||");
        Append(this?.operator_precedent,precedent__3_operators);
        List<string?>? precedent__4_operators = new List<string?>();
        Append(precedent__4_operators,"");
        Append(this?.operator_precedent,precedent__4_operators);
    }

    public bool? OverPrecedent(string? op,int? precedent)
    {
        precedent = precedent+1;
        while (AsBoolean(precedent<Size(this?.operator_precedent)))
        {
            List<string?>? precedent_operators = Element(this?.operator_precedent,precedent);
            int? index = 0;
            while (AsBoolean(index<Size(precedent_operators)))
            {
                string? checking_op = Element(precedent_operators,index);
                if (AsBoolean(checking_op==op))
                {
                    return true;
                }
                index = index+1;
            }
            precedent = precedent+1;
        }
        return false;
    }

    public string? BinaryOperatorPrecedentMerge(List<string?>? values,List<string?>? operators,IntegerReference? index,int? precedent)
    {
        if (AsBoolean(precedent==-1))
        {
            return Element(values,index?.GetValue());
        }
        string? r_value_l = this?.BinaryOperatorPrecedentMerge(values,operators,index,precedent-1);
        while (AsBoolean(index?.GetValue()<Size(operators)))
        {
            string? op = Element(operators,index?.GetValue());
            if (AsBoolean(this?.OverPrecedent(op,precedent)))
            {
                return r_value_l;
            }
            index?.SetValue(index?.GetValue()+1);
            string? r_value_r = this?.BinaryOperatorPrecedentMerge(values,operators,index,precedent-1);
            r_value_l = this?.target_specific_functions?.BinaryOperator(op,r_value_l,r_value_r);
        }
        return r_value_l;
    }

    public string? GetRValueInternal(S84.CTCode.dbnf.ctcode.RValue? r_value)
    {
        List<string?>? values = new List<string?>();
        List<string?>? operators = new List<string?>();
        IntegerReference? index = new IntegerReference();
        index?.SetValue(0);
        Append(values,this?.GetRValueSingleInternal(r_value?.GetValue()));
        S84.CTCode.dbnf.ctcode.RValueTail? r_value_tail = r_value?.GetTail();
        while (AsBoolean(r_value_tail))
        {
            S84.CTCode.dbnf.ctcode.BinaryOperator? binary_operator = r_value_tail?.GetBinaryOperator();
            Append(values,this?.GetRValueSingleInternal(r_value_tail?.GetValue()));
            Append(operators,binary_operator?.UnParse());
            r_value_tail = r_value_tail?.GetTail();
        }
        return this?.BinaryOperatorPrecedentMerge(values,operators,index,Size(this?.operator_precedent));
    }

    public string? GetQualifiedTypeNameInternal(S84.CTCode.dbnf.ctcode.QualfiedName? qualified_name)
    {
        List<string?>? name_parts = new List<string?>();
        Append(name_parts,this?.NameToString(qualified_name?.GetName()));
        S84.CTCode.dbnf.ctcode.NameTail? tail = qualified_name?.GetTail();
        while (AsBoolean(tail))
        {
            Append(name_parts,this?.NameToString(tail?.GetName()));
            tail = tail?.GetTail();
        }
        return this?.target_specific_functions?.GetQualifiedTypeName(name_parts);
    }

    public string? GetVariableChainInternal(S84.CTCode.dbnf.ctcode.QualfiedName? qualified_name)
    {
        List<string?>? name_parts = new List<string?>();
        Append(name_parts,this?.NameToString(qualified_name?.GetName()));
        S84.CTCode.dbnf.ctcode.NameTail? tail = qualified_name?.GetTail();
        while (AsBoolean(tail))
        {
            Append(name_parts,this?.NameToString(tail?.GetName()));
            tail = tail?.GetTail();
        }
        return this?.target_specific_functions?.GetVariableChain(name_parts);
    }

    public string? ReservedPrefixGetType(S84.CTCode.dbnf.ctcode.ValueType? type)
    {
        if (AsBoolean(type?.GetDimensionalType()))
        {
            S84.CTCode.dbnf.ctcode.DimensionalType? dimensional_type = type?.GetDimensionalType();
            S84.CTCode.dbnf.ctcode.SingletonType? singleton_type = dimensional_type?.GetSingletonType();
            return this?.target_specific_functions?.GetDimensionalType(this?.GetSingletonType(singleton_type),Size(dimensional_type?.GetDimensionalNote()));
        }
        if (AsBoolean(type?.GetMapType()))
        {
            S84.CTCode.dbnf.ctcode.MapType? map_type = type?.GetMapType();
            S84.CTCode.dbnf.ctcode.SingletonType? singleton_type = map_type?.GetSingletonType();
            return this?.target_specific_functions?.GetMapType(this?.GetSingletonType(singleton_type));
        }
        if (AsBoolean(type?.GetSingletonType()))
        {
            S84.CTCode.dbnf.ctcode.SingletonType? singleton_type = type?.GetSingletonType();
            return this?.GetSingletonType(singleton_type);
        }
        return "";
    }

    public string? NameToString(S84.CTCode.dbnf.ctcode.Name? name)
    {
        if (AsBoolean(name))
        {
            return name?.UnParse();
        }
        else
        {
            return "";
        }
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
