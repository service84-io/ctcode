package s84.ctcode.transpiler.standardstructure.ctcode;

import s84.ctcode.dbnf.ctcode.*;
import s84.ctcode.system.ctcode.*;
import s84.ctcode.transpiler.ctcode.*;

public class StandardStructure implements s84.ctcode.transpiler.ctcode.Transpiler {
    public StandardStructure()
    {
        this.system = null;
        this.c_t_code_file = null;
        this.base_name = "";
        this.operator_precedent = new java.util.ArrayList<>();
        this.logger = null;
        this.target_specific_functions = null;
    }

    public void SetTargetSpecificFunctions(TargetSpecificFunctions target_specific_functions)
    {
        this.target_specific_functions = target_specific_functions;
    }

    public int Transpile(s84.ctcode.system.ctcode.System system, s84.ctcode.dbnf.ctcode.CTCodeFile c_t_code_file, java.lang.String base_name)
    {
        ClearList(this.operator_precedent);
        this.PopulateOperatorPrecedent();
        this.system = system;
        this.c_t_code_file = c_t_code_file;
        this.base_name = base_name;
        this.logger = system.GetLoggerDestination();
        this.target_specific_functions.SetSystem(this.system);
        this.target_specific_functions.SetCTCodeFile(this.c_t_code_file);
        this.target_specific_functions.SetBaseName(this.base_name);
        this.target_specific_functions.SetLogger(this.logger);
        this.ProcessCTCodeFile(c_t_code_file);
        return 0;
    }

    public void ProcessCTCodeFile(s84.ctcode.dbnf.ctcode.CTCodeFile c_t_code_file)
    {
        this.target_specific_functions.BeginProcessingCTCodeFile();
        this.ProcessExdefs(c_t_code_file);
        this.ProcessUnmanagedTypes(c_t_code_file);
        this.ProcessDefinitions(c_t_code_file);
        this.target_specific_functions.FinishProcessingCTCodeFile();
    }

    public void ProcessExdefs(s84.ctcode.dbnf.ctcode.CTCodeFile c_t_code_file)
    {
        java.util.ArrayList<s84.ctcode.dbnf.ctcode.ExternalDefinition> exdefs = c_t_code_file.GetDeclarations();
        int exdefs_index = 0;
        while (AsBoolean((exdefs_index<Size(exdefs))))
        {
            s84.ctcode.dbnf.ctcode.ExternalDefinition exdef = Element(exdefs, exdefs_index);
            s84.ctcode.dbnf.ctcode.QualfiedName exdef_name = exdef.GetExdef();
            this.target_specific_functions.ProcessExdef(exdef_name.UnParse());
            exdefs_index = (exdefs_index+1);
        }
    }

    public void ProcessUnmanagedTypes(s84.ctcode.dbnf.ctcode.CTCodeFile c_t_code_file)
    {
        java.util.ArrayList<s84.ctcode.dbnf.ctcode.UnmanagedType> unmanaged_types = c_t_code_file.GetUnmanagedTypes();
        int unmanaged_types_index = 0;
        while (AsBoolean((unmanaged_types_index<Size(unmanaged_types))))
        {
            s84.ctcode.dbnf.ctcode.UnmanagedType unmanaged_type = Element(unmanaged_types, unmanaged_types_index);
            this.target_specific_functions.ProcessUnmanagedType(this.GetQualifiedTypeNameInternal(unmanaged_type.GetUnmanagedType()));
            unmanaged_types_index = (unmanaged_types_index+1);
        }
    }

    public void ProcessDefinitions(s84.ctcode.dbnf.ctcode.CTCodeFile c_t_code_file)
    {
        java.util.ArrayList<s84.ctcode.dbnf.ctcode.Definition> definitions = c_t_code_file.GetDefinitions();
        int definitions_index = 0;
        while (AsBoolean((definitions_index<Size(definitions))))
        {
            s84.ctcode.dbnf.ctcode.Definition definition = null;
            definition = Element(definitions, definitions_index);
            if (AsBoolean(definition.GetInterfaceDef()))
            {
                this.ProcessInterfaceDefinition(definition.GetInterfaceDef());
            }
            if (AsBoolean(definition.GetClassDef()))
            {
                this.ProcessClassDefinition(definition.GetClassDef());
            }
            definitions_index = (definitions_index+1);
        }
    }

    public java.util.ArrayList<ParameterDeclaration> GetParameters(s84.ctcode.dbnf.ctcode.ParameterListDef parameter_list_def)
    {
        java.util.ArrayList<ParameterDeclaration> result = new java.util.ArrayList<>();
        while (AsBoolean(parameter_list_def))
        {
            ParameterDeclaration parameter = new ParameterDeclaration();
            parameter.SetType(this.GetType(parameter_list_def.GetType()));
            parameter.SetName(this.target_specific_functions.GetVariableName(this.NameToString(parameter_list_def.GetName())));
            Append(result, parameter);
            parameter_list_def = parameter_list_def.GetParameterTail();
        }
        return result;
    }

    public void ProcessInterfaceDefinition(s84.ctcode.dbnf.ctcode.InterfaceDef interface_definition)
    {
        java.lang.String interface_name = this.target_specific_functions.GetTypeName(this.NameToString(interface_definition.GetName()));
        this.target_specific_functions.BeginProcessingInterface(interface_name);
        java.util.ArrayList<s84.ctcode.dbnf.ctcode.ContentDeclaration> declarations = interface_definition.GetDeclarations();
        int declarations_index = 0;
        while (AsBoolean((declarations_index<Size(declarations))))
        {
            s84.ctcode.dbnf.ctcode.ContentDeclaration declaration = Element(declarations, declarations_index);
            java.lang.String return_type = this.GetType(declaration.GetType());
            java.lang.String function_name = this.target_specific_functions.GetCallName(this.NameToString(declaration.GetName()));
            java.util.ArrayList<ParameterDeclaration> parameters = this.GetParameters(declaration.GetParameters());
            this.target_specific_functions.ProcessInterfaceFunctionDeclaration(return_type, function_name, parameters);
            declarations_index = (declarations_index+1);
        }
        this.target_specific_functions.FinishProcessingInterface(interface_name);
    }

    public void ProcessClassDefinition(s84.ctcode.dbnf.ctcode.ClassDef class_definition)
    {
        java.lang.String class_name = this.target_specific_functions.GetTypeName(this.NameToString(class_definition.GetName()));
        java.lang.String implementing = "";
        s84.ctcode.dbnf.ctcode.ImplementationSpec implementation_spec = class_definition.GetImplementing();
        if (AsBoolean(implementation_spec))
        {
            implementing = this.GetQualifiedTypeNameInternal(implementation_spec.GetInterface());
        }
        this.target_specific_functions.BeginProcessingClass(class_name, implementing);
        java.util.ArrayList<s84.ctcode.dbnf.ctcode.ContentDefinition> definitions = class_definition.GetDefinitions();
        int definitions_index = 0;
        while (AsBoolean((definitions_index<Size(definitions))))
        {
            s84.ctcode.dbnf.ctcode.ContentDefinition definition = Element(definitions, definitions_index);
            if (AsBoolean(definition.GetFunctionBody()))
            {
                java.lang.String return_type = this.GetType(definition.GetType());
                java.lang.String function_name = this.target_specific_functions.GetCallName(this.NameToString(definition.GetName()));
                java.util.ArrayList<ParameterDeclaration> parameters = this.GetParameters(definition.GetParameters());
                this.target_specific_functions.BeginProcessingClassFunctionDefinition(return_type, function_name, parameters);
                this.ProcessCodeBlockInternal(this.target_specific_functions.GetBaseIndentation(), definition.GetFunctionBody());
                this.target_specific_functions.FinishProcessingClassFunctionDefinition(return_type, function_name, parameters);
            }
            else
            {
                java.lang.String member_type = this.GetType(definition.GetType());
                java.lang.String member_name = this.target_specific_functions.GetVariableName(this.NameToString(definition.GetName()));
                this.target_specific_functions.ProcessClassMemberDeclaration(member_type, member_name);
            }
            definitions_index = (definitions_index+1);
        }
        this.target_specific_functions.FinishProcessingClass(class_name, implementing);
    }

    public void ProcessInstructionInternal(int indent, s84.ctcode.dbnf.ctcode.Instruction instruction)
    {
        if (AsBoolean(instruction.GetCodeBlock()))
        {
            this.ProcessCodeBlockInternal(indent, instruction.GetCodeBlock());
        }
        if (AsBoolean(instruction.GetRtn()))
        {
            this.ProcessRtnInternal(indent, instruction.GetRtn());
        }
        if (AsBoolean(instruction.GetDeclaration()))
        {
            this.ProcessDeclarationInternal(indent, instruction.GetDeclaration());
        }
        if (AsBoolean(instruction.GetAssignment()))
        {
            this.ProcessAssignmentInternal(indent, instruction.GetAssignment());
        }
        if (AsBoolean(instruction.GetCall()))
        {
            this.ProcessCallInternal(indent, instruction.GetCall());
        }
        if (AsBoolean(instruction.GetConditional()))
        {
            this.ProcessConditionalInternal(indent, instruction.GetConditional());
        }
        if (AsBoolean(instruction.GetLoop()))
        {
            this.ProcessLoopInternal(indent, instruction.GetLoop());
        }
    }

    public void ProcessCodeBlockInternal(int indent, s84.ctcode.dbnf.ctcode.CodeBlock code_block)
    {
        this.target_specific_functions.BeginProcessCodeBlock(indent);
        java.util.ArrayList<s84.ctcode.dbnf.ctcode.Instruction> instructions = code_block.GetInstructions();
        int instructions_index = 0;
        while (AsBoolean((instructions_index<Size(instructions))))
        {
            this.ProcessInstructionInternal((indent+1), Element(instructions, instructions_index));
            instructions_index = (instructions_index+1);
        }
        this.target_specific_functions.FinishProcessCodeBlock(indent);
    }

    public void ProcessConditionalInternal(int indent, s84.ctcode.dbnf.ctcode.Conditional conditional)
    {
        java.lang.String r_value = this.GetRValueInternal(conditional.GetRValue());
        this.target_specific_functions.BeginProcessConditional(indent, r_value);
        this.ProcessCodeBlockInternal(indent, conditional.GetCodeBlock());
        if (AsBoolean(conditional.GetElseTail()))
        {
            s84.ctcode.dbnf.ctcode.ElseTail else_tail = conditional.GetElseTail();
            this.target_specific_functions.ProcessElse(indent);
            this.ProcessCodeBlockInternal(indent, else_tail.GetCodeBlock());
        }
        this.target_specific_functions.FinishProcessConditional(indent, r_value);
    }

    public void ProcessLoopInternal(int indent, s84.ctcode.dbnf.ctcode.Loop loop)
    {
        java.lang.String r_value = this.GetRValueInternal(loop.GetRValue());
        this.target_specific_functions.BeginProcessLoop(indent, r_value);
        this.ProcessCodeBlockInternal(indent, loop.GetCodeBlock());
        this.target_specific_functions.FinishProcessLoop(indent, r_value);
    }

    public void ProcessRtnInternal(int indent, s84.ctcode.dbnf.ctcode.Return rtn)
    {
        java.lang.String r_value = this.GetRValueInternal(rtn.GetRValue());
        this.target_specific_functions.ProcessRtn(indent, r_value);
    }

    public void ProcessDeclarationInternal(int indent, s84.ctcode.dbnf.ctcode.Declaration declaration)
    {
        java.lang.String type = this.GetType(declaration.GetType());
        java.lang.String l_value = this.target_specific_functions.GetVariableName(this.NameToString(declaration.GetName()));
        java.lang.String r_value = "";
        s84.ctcode.dbnf.ctcode.DeclarationAssign declaration_assignment = declaration.GetAssignment();
        if (AsBoolean(declaration_assignment))
        {
            r_value = this.GetRValueInternal(declaration_assignment.GetRValue());
        }
        this.target_specific_functions.ProcessDeclaration(indent, type, l_value, r_value);
    }

    public void ProcessAssignmentInternal(int indent, s84.ctcode.dbnf.ctcode.Assignment assignment)
    {
        this.target_specific_functions.ProcessAssignment(indent, this.GetVariableChainInternal(assignment.GetLValue()), this.GetRValueInternal(assignment.GetRValue()));
    }

    public void ProcessCallInternal(int indent, s84.ctcode.dbnf.ctcode.Call call)
    {
        this.target_specific_functions.ProcessCall(indent, this.ConvertCallInternal(call));
    }

    public java.lang.String ConvertCallInternal(s84.ctcode.dbnf.ctcode.Call call)
    {
        java.util.ArrayList<java.lang.String> name_chain = new java.util.ArrayList<>();
        java.util.ArrayList<java.lang.String> parameters = new java.util.ArrayList<>();
        if (AsBoolean(call.GetVariable()))
        {
            Append(name_chain, this.target_specific_functions.GetVariableName(this.NameToString(call.GetVariable())));
        }
        if (AsBoolean(call.GetFunction()))
        {
            Append(name_chain, this.target_specific_functions.GetCallName(this.NameToString(call.GetFunction())));
        }
        if (AsBoolean(call.GetFunctionChain()))
        {
            s84.ctcode.dbnf.ctcode.QualfiedName function_chain = call.GetFunctionChain();
            s84.ctcode.dbnf.ctcode.NameTail name_tail = function_chain.GetTail();
            if (AsBoolean(function_chain.GetTail()))
            {
                Append(name_chain, this.target_specific_functions.GetVariableName(this.NameToString(function_chain.GetName())));
            }
            else
            {
                Append(name_chain, this.target_specific_functions.GetCallName(this.NameToString(function_chain.GetName())));
            }
            while (AsBoolean(name_tail))
            {
                if (AsBoolean(name_tail.GetTail()))
                {
                    Append(name_chain, this.target_specific_functions.GetVariableName(this.NameToString(name_tail.GetName())));
                }
                else
                {
                    Append(name_chain, this.target_specific_functions.GetCallName(this.NameToString(name_tail.GetName())));
                }
                name_tail = name_tail.GetTail();
            }
        }
        s84.ctcode.dbnf.ctcode.ParameterList parameter_list = call.GetParameters();
        while (AsBoolean(parameter_list))
        {
            Append(parameters, this.GetRValueInternal(parameter_list.GetRValue()));
            parameter_list = parameter_list.GetParameterTail();
        }
        return this.target_specific_functions.ConvertCall(name_chain, parameters);
    }

    public java.lang.String GetSingletonType(s84.ctcode.dbnf.ctcode.SingletonType singleton_type)
    {
        if (AsBoolean(singleton_type.GetPrimativeType()))
        {
            return this.target_specific_functions.GetPrimativeType(singleton_type.UnParse());
        }
        if (AsBoolean(singleton_type.GetDefinedType()))
        {
            s84.ctcode.dbnf.ctcode.DefinedType defined_type = singleton_type.GetDefinedType();
            return this.target_specific_functions.GetDefinedType(this.GetQualifiedTypeNameInternal(defined_type.GetName()));
        }
        return "";
    }

    public java.lang.String GetRValueSingleBasisInternal(s84.ctcode.dbnf.ctcode.RValueSingle r_value_single)
    {
        s84.ctcode.dbnf.ctcode.Call call = r_value_single.GetCall();
        if (AsBoolean(call))
        {
            return this.ConvertCallInternal(call);
        }
        s84.ctcode.dbnf.ctcode.Allocate allocate = r_value_single.GetAllocate();
        if (AsBoolean(allocate))
        {
            return this.target_specific_functions.ConvertAllocate(this.GetQualifiedTypeNameInternal(allocate.GetManagedType()));
        }
        s84.ctcode.dbnf.ctcode.Byte byte_literal = r_value_single.GetByteLiteral();
        if (AsBoolean(byte_literal))
        {
            s84.ctcode.dbnf.ctcode.ByteDigit high = byte_literal.GetHigh();
            s84.ctcode.dbnf.ctcode.ByteDigit low = byte_literal.GetLow();
            return this.target_specific_functions.ConvertByte(high.UnParse(), low.UnParse());
        }
        s84.ctcode.dbnf.ctcode.Decimal decimal_literal = r_value_single.GetDecimalLiteral();
        if (AsBoolean(decimal_literal))
        {
            return this.target_specific_functions.ConvertDecimal(decimal_literal.UnParse());
        }
        s84.ctcode.dbnf.ctcode.Number integer_literal = r_value_single.GetIntegerLiteral();
        if (AsBoolean(integer_literal))
        {
            return this.target_specific_functions.ConvertNumber(integer_literal.UnParse());
        }
        s84.ctcode.dbnf.ctcode.Boolean boolean_literal = r_value_single.GetBooleanLiteral();
        if (AsBoolean(boolean_literal))
        {
            return this.target_specific_functions.ConvertBoolean(boolean_literal.UnParse());
        }
        s84.ctcode.dbnf.ctcode.QualfiedName variable = r_value_single.GetVariable();
        if (AsBoolean(variable))
        {
            return this.target_specific_functions.ConvertVariable(this.GetVariableChainInternal(variable));
        }
        s84.ctcode.dbnf.ctcode.Literal string_literal = r_value_single.GetStringLiteral();
        if (AsBoolean(string_literal))
        {
            return this.target_specific_functions.ConvertString(string_literal.UnParse());
        }
        return "";
    }

    public java.lang.String GetRValueSingleInternal(s84.ctcode.dbnf.ctcode.RValueSingle r_value_single)
    {
        s84.ctcode.dbnf.ctcode.UnaryOperator unary_operator = r_value_single.GetUnaryOperator();
        if (AsBoolean(unary_operator))
        {
            return this.target_specific_functions.UnaryOperator(unary_operator.UnParse(), this.GetRValueSingleBasisInternal(r_value_single));
        }
        return this.GetRValueSingleBasisInternal(r_value_single);
    }

    public void PopulateOperatorPrecedent()
    {
        java.util.ArrayList<java.lang.String> precedent__0_operators = new java.util.ArrayList<>();
        Append(precedent__0_operators, "+");
        Append(precedent__0_operators, "-");
        Append(this.operator_precedent, precedent__0_operators);
        java.util.ArrayList<java.lang.String> precedent__1_operators = new java.util.ArrayList<>();
        Append(precedent__1_operators, "<=");
        Append(precedent__1_operators, ">=");
        Append(precedent__1_operators, "==");
        Append(precedent__1_operators, "!=");
        Append(precedent__1_operators, "<");
        Append(precedent__1_operators, ">");
        Append(this.operator_precedent, precedent__1_operators);
        java.util.ArrayList<java.lang.String> precedent__2_operators = new java.util.ArrayList<>();
        Append(precedent__2_operators, "&&");
        Append(this.operator_precedent, precedent__2_operators);
        java.util.ArrayList<java.lang.String> precedent__3_operators = new java.util.ArrayList<>();
        Append(precedent__3_operators, "||");
        Append(this.operator_precedent, precedent__3_operators);
        java.util.ArrayList<java.lang.String> precedent__4_operators = new java.util.ArrayList<>();
        Append(precedent__4_operators, "");
        Append(this.operator_precedent, precedent__4_operators);
    }

    public boolean OverPrecedent(java.lang.String op, int precedent)
    {
        precedent = (precedent+1);
        while (AsBoolean((precedent<Size(this.operator_precedent))))
        {
            java.util.ArrayList<java.lang.String> precedent_operators = Element(this.operator_precedent, precedent);
            int index = 0;
            while (AsBoolean((index<Size(precedent_operators))))
            {
                java.lang.String checking_op = Element(precedent_operators, index);
                if (AsBoolean(Equals(checking_op,op)))
                {
                    return true;
                }
                index = (index+1);
            }
            precedent = (precedent+1);
        }
        return false;
    }

    public java.lang.String BinaryOperatorPrecedentMerge(java.util.ArrayList<java.lang.String> values, java.util.ArrayList<java.lang.String> operators, IntegerReference index, int precedent)
    {
        if (AsBoolean(Equals(precedent,-1)))
        {
            return Element(values, index.GetValue());
        }
        java.lang.String r_value_l = this.BinaryOperatorPrecedentMerge(values, operators, index, (precedent-1));
        while (AsBoolean((index.GetValue()<Size(operators))))
        {
            java.lang.String op = Element(operators, index.GetValue());
            if (AsBoolean(this.OverPrecedent(op, precedent)))
            {
                return r_value_l;
            }
            index.SetValue((index.GetValue()+1));
            java.lang.String r_value_r = this.BinaryOperatorPrecedentMerge(values, operators, index, (precedent-1));
            r_value_l = this.target_specific_functions.BinaryOperator(op, r_value_l, r_value_r);
        }
        return r_value_l;
    }

    public java.lang.String GetRValueInternal(s84.ctcode.dbnf.ctcode.RValue r_value)
    {
        java.util.ArrayList<java.lang.String> values = new java.util.ArrayList<>();
        java.util.ArrayList<java.lang.String> operators = new java.util.ArrayList<>();
        IntegerReference index = new IntegerReference();
        index.SetValue(0);
        Append(values, this.GetRValueSingleInternal(r_value.GetValue()));
        s84.ctcode.dbnf.ctcode.RValueTail r_value_tail = r_value.GetTail();
        while (AsBoolean(r_value_tail))
        {
            s84.ctcode.dbnf.ctcode.BinaryOperator binary_operator = r_value_tail.GetBinaryOperator();
            Append(values, this.GetRValueSingleInternal(r_value_tail.GetValue()));
            Append(operators, binary_operator.UnParse());
            r_value_tail = r_value_tail.GetTail();
        }
        return this.BinaryOperatorPrecedentMerge(values, operators, index, Size(this.operator_precedent));
    }

    public java.lang.String GetQualifiedTypeNameInternal(s84.ctcode.dbnf.ctcode.QualfiedName qualified_name)
    {
        java.util.ArrayList<java.lang.String> name_parts = new java.util.ArrayList<>();
        Append(name_parts, this.NameToString(qualified_name.GetName()));
        s84.ctcode.dbnf.ctcode.NameTail tail = qualified_name.GetTail();
        while (AsBoolean(tail))
        {
            Append(name_parts, this.NameToString(tail.GetName()));
            tail = tail.GetTail();
        }
        return this.target_specific_functions.GetQualifiedTypeName(name_parts);
    }

    public java.lang.String GetVariableChainInternal(s84.ctcode.dbnf.ctcode.QualfiedName qualified_name)
    {
        java.util.ArrayList<java.lang.String> name_parts = new java.util.ArrayList<>();
        Append(name_parts, this.NameToString(qualified_name.GetName()));
        s84.ctcode.dbnf.ctcode.NameTail tail = qualified_name.GetTail();
        while (AsBoolean(tail))
        {
            Append(name_parts, this.NameToString(tail.GetName()));
            tail = tail.GetTail();
        }
        return this.target_specific_functions.GetVariableChain(name_parts);
    }

    public java.lang.String GetType(s84.ctcode.dbnf.ctcode.ValueType type)
    {
        if (AsBoolean(type.GetDimensionalType()))
        {
            s84.ctcode.dbnf.ctcode.DimensionalType dimensional_type = type.GetDimensionalType();
            s84.ctcode.dbnf.ctcode.SingletonType singleton_type = dimensional_type.GetSingletonType();
            return this.target_specific_functions.GetDimensionalType(this.GetSingletonType(singleton_type), Size(dimensional_type.GetDimensionalNote()));
        }
        if (AsBoolean(type.GetMapType()))
        {
            s84.ctcode.dbnf.ctcode.MapType map_type = type.GetMapType();
            s84.ctcode.dbnf.ctcode.SingletonType singleton_type = map_type.GetSingletonType();
            return this.target_specific_functions.GetMapType(this.GetSingletonType(singleton_type));
        }
        if (AsBoolean(type.GetSingletonType()))
        {
            s84.ctcode.dbnf.ctcode.SingletonType singleton_type = type.GetSingletonType();
            return this.GetSingletonType(singleton_type);
        }
        return "";
    }

    public java.lang.String NameToString(s84.ctcode.dbnf.ctcode.Name name)
    {
        if (AsBoolean(name))
        {
            return name.UnParse();
        }
        else
        {
            return "";
        }
    }

    private s84.ctcode.system.ctcode.System system;
    private s84.ctcode.dbnf.ctcode.CTCodeFile c_t_code_file;
    private java.lang.String base_name;
    private java.util.ArrayList<java.util.ArrayList<java.lang.String>> operator_precedent;
    private s84.ctcode.system.ctcode.OutputStream logger;
    private TargetSpecificFunctions target_specific_functions;

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
