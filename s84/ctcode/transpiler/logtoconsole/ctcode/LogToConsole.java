package s84.ctcode.transpiler.logtoconsole.ctcode;

import s84.ctcode.dbnf.ctcode.*;
import s84.ctcode.system.ctcode.*;
import s84.ctcode.transpiler.ctcode.*;

public class LogToConsole implements s84.ctcode.transpiler.ctcode.Transpiler {
    public LogToConsole()
    {
        this.system = null;
        this.c_t_code_file = null;
        this.base_name = "";
        this.logger = null;
    }

    public int GetBaseIndentation()
    {
        return 3;
    }

    public java.lang.String GetCallName(s84.ctcode.dbnf.ctcode.Name name)
    {
        if (AsBoolean(name))
        {
            return this.SnakeCaseToCamelCase(name.UnParse());
        }
        else
        {
            return "";
        }
    }

    public java.lang.String GetVariableName(s84.ctcode.dbnf.ctcode.Name name)
    {
        if (AsBoolean(name))
        {
            java.lang.String value = this.CamelCaseToSnakeCase(name.UnParse());
            if (AsBoolean(Equals(value,"myself")))
            {
                return "self";
            }
            return value;
        }
        else
        {
            return "";
        }
    }

    public java.lang.String GetVariableChainNameTail(s84.ctcode.dbnf.ctcode.NameTail tail)
    {
        java.lang.String accessor = ".";
        if (AsBoolean(tail))
        {
            return Concat(Concat(accessor, this.GetVariableName(tail.GetName())), this.GetVariableChainNameTail(tail.GetTail()));
        }
        else
        {
            return "";
        }
    }

    public java.lang.String GetVariableChain(s84.ctcode.dbnf.ctcode.QualfiedName l_value)
    {
        if (AsBoolean(l_value))
        {
            return Concat(this.GetVariableName(l_value.GetName()), this.GetVariableChainNameTail(l_value.GetTail()));
        }
        else
        {
            return "";
        }
    }

    public java.lang.String ConvertCall(java.util.ArrayList<java.lang.String> name_chain, java.util.ArrayList<java.lang.String> parameters)
    {
        java.lang.String result = Element(name_chain, 0);
        int name_chain_index = 1;
        while (AsBoolean((name_chain_index<Size(name_chain))))
        {
            java.lang.String name_part = Element(name_chain, name_chain_index);
            result = Concat(Concat(result, "."), name_part);
            name_chain_index = (name_chain_index+1);
        }
        result = Concat(result, "(");
        if (AsBoolean((Size(parameters)>0)))
        {
            result = Concat(result, Element(parameters, 0));
            int parameters_index = 1;
            while (AsBoolean((parameters_index<Size(parameters))))
            {
                java.lang.String parameter = Element(parameters, parameters_index);
                result = Concat(result, ",");
                result = Concat(result, parameter);
                parameters_index = (parameters_index+1);
            }
        }
        result = Concat(result, ")");
        return result;
    }

    public java.lang.String ConvertAllocate(java.lang.String type)
    {
        return Concat("new ", type);
    }

    public java.lang.String ConvertByte(java.lang.String high, java.lang.String low)
    {
        return Concat(Concat("0x", high), low);
    }

    public java.lang.String ConvertDecimal(java.lang.String decimal)
    {
        return decimal;
    }

    public java.lang.String ConvertNumber(java.lang.String number)
    {
        return number;
    }

    public java.lang.String ConvertBoolean(java.lang.String reserved_prefix_boolean)
    {
        if (AsBoolean(Equals(reserved_prefix_boolean,"true")))
        {
            return "true";
        }
        if (AsBoolean(Equals(reserved_prefix_boolean,"false")))
        {
            return "false";
        }
        return "";
    }

    public java.lang.String ConvertVariable(java.lang.String variable)
    {
        return variable;
    }

    public java.lang.String ConvertString(java.lang.String literal)
    {
        return Concat(Concat("\"", literal), "\"");
    }

    public java.lang.String UnaryOperator(java.lang.String op, java.lang.String r_value)
    {
        if (AsBoolean(Equals(op,"!")))
        {
            return Concat("!", r_value);
        }
        return r_value;
    }

    public java.lang.String BinaryOperator(java.lang.String op, java.lang.String r_value_l, java.lang.String r_value_r)
    {
        if (AsBoolean(Equals(op,"+")))
        {
            return Concat(Concat(r_value_l, "+"), r_value_r);
        }
        if (AsBoolean(Equals(op,"-")))
        {
            return Concat(Concat(r_value_l, "-"), r_value_r);
        }
        if (AsBoolean(Equals(op,"<=")))
        {
            return Concat(Concat(r_value_l, "<="), r_value_r);
        }
        if (AsBoolean(Equals(op,">=")))
        {
            return Concat(Concat(r_value_l, ">="), r_value_r);
        }
        if (AsBoolean(Equals(op,"==")))
        {
            return Concat(Concat(r_value_l, "=="), r_value_r);
        }
        if (AsBoolean(Equals(op,"!=")))
        {
            return Concat(Concat(r_value_l, "!="), r_value_r);
        }
        if (AsBoolean(Equals(op,"<")))
        {
            return Concat(Concat(r_value_l, "<"), r_value_r);
        }
        if (AsBoolean(Equals(op,">")))
        {
            return Concat(Concat(r_value_l, ">"), r_value_r);
        }
        if (AsBoolean(Equals(op,"||")))
        {
            return Concat(Concat(r_value_l, "||"), r_value_r);
        }
        if (AsBoolean(Equals(op,"&&")))
        {
            return Concat(Concat(r_value_l, "&&"), r_value_r);
        }
        return "";
    }

    public java.lang.String GetTypeName(s84.ctcode.dbnf.ctcode.Name name)
    {
        if (AsBoolean(name))
        {
            return this.SnakeCaseToCamelCase(name.UnParse());
        }
        else
        {
            return "";
        }
    }

    public java.lang.String GetDimensionalType(java.lang.String singleton_type, int dimensions)
    {
        java.lang.String result = singleton_type;
        while (AsBoolean((dimensions>0)))
        {
            result = Concat(result, "[]");
            dimensions = (dimensions-1);
        }
        return result;
    }

    public java.lang.String GetMapType(java.lang.String singleton_type)
    {
        return Concat(singleton_type, "{}");
    }

    public java.lang.String GetPrimativeType(java.lang.String c_t_type)
    {
        if (AsBoolean(Equals(c_t_type,"int")))
        {
            return "int";
        }
        if (AsBoolean(Equals(c_t_type,"string")))
        {
            return "string";
        }
        if (AsBoolean(Equals(c_t_type,"bool")))
        {
            return "bool";
        }
        if (AsBoolean(Equals(c_t_type,"float")))
        {
            return "float";
        }
        if (AsBoolean(Equals(c_t_type,"void")))
        {
            return "void";
        }
        return "";
    }

    public java.lang.String GetQualifiedTypeName(java.util.ArrayList<s84.ctcode.dbnf.ctcode.Name> name_parts)
    {
        java.lang.String delimiter = ".";
        s84.ctcode.dbnf.ctcode.Name first_name = Element(name_parts, 0);
        java.lang.String result = first_name.UnParse();
        int name_parts_index = 1;
        while (AsBoolean((name_parts_index<Size(name_parts))))
        {
            s84.ctcode.dbnf.ctcode.Name name = Element(name_parts, name_parts_index);
            result = Concat(Concat(result, delimiter), name.UnParse());
            name_parts_index = (name_parts_index+1);
        }
        return result;
    }

    public void BeginProcessingCTCodeFile()
    {
        this.logger.WriteLine("BeginProcessingCTCodeFile");
    }

    public void ProcessExdef(java.lang.String exdef)
    {
        this.logger.WriteLine(Concat(Concat(this.Indentation(1), "ProcessExdef: "), exdef));
    }

    public void ProcessUnmanagedType(java.lang.String unmanaged_type)
    {
        this.logger.WriteLine(Concat(Concat(this.Indentation(1), "ProcessUnmanagedType: "), unmanaged_type));
    }

    public void BeginProcessingInterface(java.lang.String interface_name)
    {
        this.logger.WriteLine(Concat(Concat(this.Indentation(1), "BeginProcessingInterface: "), interface_name));
    }

    public void ProcessInterfaceFunctionDeclaration(java.lang.String return_type, java.lang.String function_name, java.util.ArrayList<ParameterDeclaration> parameters)
    {
        this.logger.WriteLine(Concat(Concat(Concat(Concat(this.Indentation(2), "ProcessInterfaceFunctionDeclaration: "), return_type), " "), function_name));
    }

    public void FinishProcessingInterface(java.lang.String interface_name)
    {
        this.logger.WriteLine(Concat(Concat(this.Indentation(1), "FinishProcessingInterface: "), interface_name));
    }

    public void BeginProcessingClass(java.lang.String class_name, java.lang.String implementing)
    {
        this.logger.WriteLine(Concat(Concat(Concat(Concat(this.Indentation(1), "BeginProcessingClass: "), class_name), " "), implementing));
    }

    public void BeginProcessingClassFunctionDefinition(java.lang.String return_type, java.lang.String function_name, java.util.ArrayList<ParameterDeclaration> parameters)
    {
        this.logger.WriteLine(Concat(Concat(Concat(Concat(this.Indentation(2), "BeginProcessingClassFunctionDefinition: "), return_type), " "), function_name));
    }

    public void BeginProcessCodeBlock(int indent)
    {
        this.logger.WriteLine(Concat(this.Indentation(indent), "BeginProcessCodeBlock"));
    }

    public void FinishProcessCodeBlock(int indent)
    {
        this.logger.WriteLine(Concat(this.Indentation(indent), "FinishProcessCodeBlock"));
    }

    public void BeginProcessConditional(int indent, java.lang.String r_value)
    {
        this.logger.WriteLine(Concat(Concat(this.Indentation(indent), "BeginProcessConditional: "), r_value));
    }

    public void ProcessElse(int indent)
    {
        this.logger.WriteLine(Concat(this.Indentation(indent), "ProcessElse"));
    }

    public void FinishProcessConditional(int indent, java.lang.String r_value)
    {
        this.logger.WriteLine(Concat(Concat(this.Indentation(indent), "FinishProcessConditional: "), r_value));
    }

    public void BeginProcessLoop(int indent, java.lang.String r_value)
    {
        this.logger.WriteLine(Concat(Concat(this.Indentation(indent), "BeginProcessLoop: "), r_value));
    }

    public void FinishProcessLoop(int indent, java.lang.String r_value)
    {
        this.logger.WriteLine(Concat(Concat(this.Indentation(indent), "FinishProcessLoop: "), r_value));
    }

    public void ProcessRtn(int indent, java.lang.String r_value)
    {
        this.logger.WriteLine(Concat(Concat(this.Indentation(indent), "ProcessRtn: "), r_value));
    }

    public void ProcessDeclaration(int indent, java.lang.String type, java.lang.String l_value, java.lang.String r_value)
    {
        this.logger.WriteLine(Concat(Concat(Concat(Concat(Concat(Concat(this.Indentation(indent), "ProcessDeclaration: "), type), " "), l_value), " "), r_value));
    }

    public void ProcessAssignment(int indent, java.lang.String l_value, java.lang.String r_value)
    {
        this.logger.WriteLine(Concat(Concat(Concat(Concat(this.Indentation(indent), "ProcessAssignment: "), l_value), " "), r_value));
    }

    public void ProcessCall(int indent, java.lang.String call)
    {
        this.logger.WriteLine(Concat(Concat(this.Indentation(indent), "ProcessCall: "), call));
    }

    public void FinishProcessingClassFunctionDefinition(java.lang.String return_type, java.lang.String function_name, java.util.ArrayList<ParameterDeclaration> parameters)
    {
        this.logger.WriteLine(Concat(Concat(Concat(Concat(this.Indentation(2), "FinishProcessingClassFunctionDefinition: "), return_type), " "), function_name));
    }

    public void ProcessClassMemberDeclaration(java.lang.String member_type, java.lang.String member_name)
    {
        this.logger.WriteLine(Concat(Concat(Concat(Concat(this.Indentation(2), "ProcessClassMemberDeclaration: "), member_type), " "), member_name));
    }

    public void FinishProcessingClass(java.lang.String class_name, java.lang.String implementing)
    {
        this.logger.WriteLine(Concat(Concat(this.Indentation(1), "FinishProcessingClass: "), class_name));
    }

    public void FinishProcessingCTCodeFile()
    {
        this.logger.WriteLine("FinishProcessingCTCodeFile");
    }

    public int Transpile(s84.ctcode.system.ctcode.System system, s84.ctcode.dbnf.ctcode.CTCodeFile c_t_code_file, java.lang.String base_name)
    {
        this.system = system;
        this.c_t_code_file = c_t_code_file;
        this.base_name = base_name;
        this.logger = system.GetLoggerDestination();
        this.ProcessCTCodeFile(c_t_code_file);
        return 0;
    }

    public void ProcessCTCodeFile(s84.ctcode.dbnf.ctcode.CTCodeFile c_t_code_file)
    {
        this.BeginProcessingCTCodeFile();
        this.ProcessExdefs(c_t_code_file);
        this.ProcessUnmanagedTypes(c_t_code_file);
        this.ProcessDefinitions(c_t_code_file);
        this.FinishProcessingCTCodeFile();
    }

    public void ProcessExdefs(s84.ctcode.dbnf.ctcode.CTCodeFile c_t_code_file)
    {
        java.util.ArrayList<s84.ctcode.dbnf.ctcode.ExternalDefinition> exdefs = c_t_code_file.GetDeclarations();
        int exdefs_index = 0;
        while (AsBoolean((exdefs_index<Size(exdefs))))
        {
            s84.ctcode.dbnf.ctcode.ExternalDefinition exdef = Element(exdefs, exdefs_index);
            s84.ctcode.dbnf.ctcode.QualfiedName exdef_name = exdef.GetExdef();
            this.ProcessExdef(exdef_name.UnParse());
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
            this.ProcessUnmanagedType(this.GetQualifiedTypeNameInternal(unmanaged_type.GetUnmanagedType()));
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
            parameter.SetName(this.GetVariableName(parameter_list_def.GetName()));
            Append(result, parameter);
            parameter_list_def = parameter_list_def.GetParameterTail();
        }
        return result;
    }

    public void ProcessInterfaceDefinition(s84.ctcode.dbnf.ctcode.InterfaceDef interface_definition)
    {
        java.lang.String interface_name = this.GetTypeName(interface_definition.GetName());
        this.BeginProcessingInterface(interface_name);
        java.util.ArrayList<s84.ctcode.dbnf.ctcode.ContentDeclaration> declarations = interface_definition.GetDeclarations();
        int declarations_index = 0;
        while (AsBoolean((declarations_index<Size(declarations))))
        {
            s84.ctcode.dbnf.ctcode.ContentDeclaration declaration = Element(declarations, declarations_index);
            java.lang.String return_type = this.GetType(declaration.GetType());
            java.lang.String function_name = this.GetCallName(declaration.GetName());
            java.util.ArrayList<ParameterDeclaration> parameters = this.GetParameters(declaration.GetParameters());
            this.ProcessInterfaceFunctionDeclaration(return_type, function_name, parameters);
            declarations_index = (declarations_index+1);
        }
        this.FinishProcessingInterface(interface_name);
    }

    public void ProcessClassDefinition(s84.ctcode.dbnf.ctcode.ClassDef class_definition)
    {
        java.lang.String class_name = this.GetTypeName(class_definition.GetName());
        java.lang.String implementing = "";
        s84.ctcode.dbnf.ctcode.ImplementationSpec implementation_spec = class_definition.GetImplementing();
        if (AsBoolean(implementation_spec))
        {
            implementing = this.GetQualifiedTypeNameInternal(implementation_spec.GetInterface());
        }
        this.BeginProcessingClass(class_name, implementing);
        java.util.ArrayList<s84.ctcode.dbnf.ctcode.ContentDefinition> definitions = class_definition.GetDefinitions();
        int definitions_index = 0;
        while (AsBoolean((definitions_index<Size(definitions))))
        {
            s84.ctcode.dbnf.ctcode.ContentDefinition definition = Element(definitions, definitions_index);
            if (AsBoolean(definition.GetFunctionBody()))
            {
                java.lang.String return_type = this.GetType(definition.GetType());
                java.lang.String function_name = this.GetCallName(definition.GetName());
                java.util.ArrayList<ParameterDeclaration> parameters = this.GetParameters(definition.GetParameters());
                this.BeginProcessingClassFunctionDefinition(return_type, function_name, parameters);
                this.ProcessCodeBlockInternal(this.GetBaseIndentation(), definition.GetFunctionBody());
                this.FinishProcessingClassFunctionDefinition(return_type, function_name, parameters);
            }
            else
            {
                java.lang.String member_type = this.GetType(definition.GetType());
                java.lang.String member_name = this.GetVariableName(definition.GetName());
                this.ProcessClassMemberDeclaration(member_type, member_name);
            }
            definitions_index = (definitions_index+1);
        }
        this.FinishProcessingClass(class_name, implementing);
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
        this.BeginProcessCodeBlock(indent);
        java.util.ArrayList<s84.ctcode.dbnf.ctcode.Instruction> instructions = code_block.GetInstructions();
        int instructions_index = 0;
        while (AsBoolean((instructions_index<Size(instructions))))
        {
            this.ProcessInstructionInternal((indent+1), Element(instructions, instructions_index));
            instructions_index = (instructions_index+1);
        }
        this.FinishProcessCodeBlock(indent);
    }

    public void ProcessConditionalInternal(int indent, s84.ctcode.dbnf.ctcode.Conditional conditional)
    {
        java.lang.String r_value = this.GetRValueInternal(conditional.GetRValue());
        this.BeginProcessConditional(indent, r_value);
        this.ProcessCodeBlockInternal(indent, conditional.GetCodeBlock());
        if (AsBoolean(conditional.GetElseTail()))
        {
            s84.ctcode.dbnf.ctcode.ElseTail else_tail = conditional.GetElseTail();
            this.ProcessElse(indent);
            this.ProcessCodeBlockInternal(indent, else_tail.GetCodeBlock());
        }
        this.FinishProcessConditional(indent, r_value);
    }

    public void ProcessLoopInternal(int indent, s84.ctcode.dbnf.ctcode.Loop loop)
    {
        java.lang.String r_value = this.GetRValueInternal(loop.GetRValue());
        this.BeginProcessLoop(indent, r_value);
        this.ProcessCodeBlockInternal(indent, loop.GetCodeBlock());
        this.FinishProcessLoop(indent, r_value);
    }

    public void ProcessRtnInternal(int indent, s84.ctcode.dbnf.ctcode.Return rtn)
    {
        java.lang.String r_value = this.GetRValueInternal(rtn.GetRValue());
        this.ProcessRtn(indent, r_value);
    }

    public void ProcessDeclarationInternal(int indent, s84.ctcode.dbnf.ctcode.Declaration declaration)
    {
        java.lang.String type = this.GetType(declaration.GetType());
        java.lang.String l_value = this.GetVariableName(declaration.GetName());
        java.lang.String r_value = "";
        s84.ctcode.dbnf.ctcode.DeclarationAssign declaration_assignment = declaration.GetAssignment();
        if (AsBoolean(declaration_assignment))
        {
            r_value = this.GetRValueInternal(declaration_assignment.GetRValue());
        }
        this.ProcessDeclaration(indent, type, l_value, r_value);
    }

    public void ProcessAssignmentInternal(int indent, s84.ctcode.dbnf.ctcode.Assignment assignment)
    {
        this.ProcessAssignment(indent, this.GetVariableChain(assignment.GetLValue()), this.GetRValueInternal(assignment.GetRValue()));
    }

    public void ProcessCallInternal(int indent, s84.ctcode.dbnf.ctcode.Call call)
    {
        this.ProcessCall(indent, this.ConvertCallInternal(call));
    }

    public java.lang.String ConvertCallInternal(s84.ctcode.dbnf.ctcode.Call call)
    {
        java.util.ArrayList<java.lang.String> name_chain = new java.util.ArrayList<>();
        java.util.ArrayList<java.lang.String> parameters = new java.util.ArrayList<>();
        if (AsBoolean(call.GetVariable()))
        {
            Append(name_chain, this.GetVariableName(call.GetVariable()));
        }
        if (AsBoolean(call.GetFunction()))
        {
            Append(name_chain, this.GetCallName(call.GetFunction()));
        }
        if (AsBoolean(call.GetFunctionChain()))
        {
            s84.ctcode.dbnf.ctcode.QualfiedName function_chain = call.GetFunctionChain();
            s84.ctcode.dbnf.ctcode.NameTail name_tail = function_chain.GetTail();
            if (AsBoolean(function_chain.GetTail()))
            {
                Append(name_chain, this.GetVariableName(function_chain.GetName()));
            }
            else
            {
                Append(name_chain, this.GetCallName(function_chain.GetName()));
            }
            while (AsBoolean(name_tail))
            {
                if (AsBoolean(name_tail.GetTail()))
                {
                    Append(name_chain, this.GetVariableName(name_tail.GetName()));
                }
                else
                {
                    Append(name_chain, this.GetCallName(name_tail.GetName()));
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
        return this.ConvertCall(name_chain, parameters);
    }

    public java.lang.String GetSingletonType(s84.ctcode.dbnf.ctcode.SingletonType singleton_type)
    {
        if (AsBoolean(singleton_type.GetPrimativeType()))
        {
            return this.GetPrimativeType(singleton_type.UnParse());
        }
        if (AsBoolean(singleton_type.GetDefinedType()))
        {
            s84.ctcode.dbnf.ctcode.DefinedType defined_type = singleton_type.GetDefinedType();
            return this.GetQualifiedTypeNameInternal(defined_type.GetName());
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
            return this.ConvertAllocate(this.GetQualifiedTypeNameInternal(allocate.GetManagedType()));
        }
        s84.ctcode.dbnf.ctcode.Byte byte_literal = r_value_single.GetByteLiteral();
        if (AsBoolean(byte_literal))
        {
            s84.ctcode.dbnf.ctcode.ByteDigit high = byte_literal.GetHigh();
            s84.ctcode.dbnf.ctcode.ByteDigit low = byte_literal.GetLow();
            return this.ConvertByte(high.UnParse(), low.UnParse());
        }
        s84.ctcode.dbnf.ctcode.Decimal decimal_literal = r_value_single.GetDecimalLiteral();
        if (AsBoolean(decimal_literal))
        {
            return this.ConvertDecimal(decimal_literal.UnParse());
        }
        s84.ctcode.dbnf.ctcode.Number integer_literal = r_value_single.GetIntegerLiteral();
        if (AsBoolean(integer_literal))
        {
            return this.ConvertNumber(integer_literal.UnParse());
        }
        s84.ctcode.dbnf.ctcode.Boolean boolean_literal = r_value_single.GetBooleanLiteral();
        if (AsBoolean(boolean_literal))
        {
            return this.ConvertBoolean(boolean_literal.UnParse());
        }
        s84.ctcode.dbnf.ctcode.QualfiedName variable = r_value_single.GetVariable();
        if (AsBoolean(variable))
        {
            return this.ConvertVariable(this.GetVariableChain(variable));
        }
        s84.ctcode.dbnf.ctcode.Literal string_literal = r_value_single.GetStringLiteral();
        if (AsBoolean(string_literal))
        {
            return this.ConvertString(string_literal.UnParse());
        }
        return "";
    }

    public java.lang.String GetRValueSingleInternal(s84.ctcode.dbnf.ctcode.RValueSingle r_value_single)
    {
        s84.ctcode.dbnf.ctcode.UnaryOperator unary_operator = r_value_single.GetUnaryOperator();
        if (AsBoolean(unary_operator))
        {
            return this.UnaryOperator(unary_operator.UnParse(), this.GetRValueSingleBasisInternal(r_value_single));
        }
        return this.GetRValueSingleBasisInternal(r_value_single);
    }

    public java.lang.String GetRValueBinaryInternal(java.lang.String r_value_l, s84.ctcode.dbnf.ctcode.RValueTail r_value_tail)
    {
        java.lang.String r_value_r = this.GetRValueSingleInternal(r_value_tail.GetValue());
        s84.ctcode.dbnf.ctcode.BinaryOperator binary_operator = r_value_tail.GetBinaryOperator();
        r_value_l = this.BinaryOperator(binary_operator.UnParse(), r_value_l, r_value_r);
        if (AsBoolean(r_value_tail.GetTail()))
        {
            return this.GetRValueBinaryInternal(r_value_l, r_value_tail.GetTail());
        }
        return r_value_l;
    }

    public java.lang.String GetRValueInternal(s84.ctcode.dbnf.ctcode.RValue r_value)
    {
        java.lang.String r_value_l = this.GetRValueSingleInternal(r_value.GetValue());
        if (AsBoolean(r_value.GetTail()))
        {
            return this.GetRValueBinaryInternal(r_value_l, r_value.GetTail());
        }
        return r_value_l;
    }

    public java.lang.String GetQualifiedTypeNameInternal(s84.ctcode.dbnf.ctcode.QualfiedName qualified_name)
    {
        java.util.ArrayList<s84.ctcode.dbnf.ctcode.Name> name_parts = new java.util.ArrayList<>();
        Append(name_parts, qualified_name.GetName());
        s84.ctcode.dbnf.ctcode.NameTail tail = qualified_name.GetTail();
        while (AsBoolean(tail))
        {
            Append(name_parts, tail.GetName());
            tail = tail.GetTail();
        }
        return this.GetQualifiedTypeName(name_parts);
    }

    public java.lang.String GetType(s84.ctcode.dbnf.ctcode.ValueType type)
    {
        if (AsBoolean(type.GetDimensionalType()))
        {
            s84.ctcode.dbnf.ctcode.DimensionalType dimensional_type = type.GetDimensionalType();
            s84.ctcode.dbnf.ctcode.SingletonType singleton_type = dimensional_type.GetSingletonType();
            return this.GetDimensionalType(this.GetSingletonType(singleton_type), Size(dimensional_type.GetDimensionalNote()));
        }
        if (AsBoolean(type.GetMapType()))
        {
            s84.ctcode.dbnf.ctcode.MapType map_type = type.GetMapType();
            s84.ctcode.dbnf.ctcode.SingletonType singleton_type = map_type.GetSingletonType();
            return this.GetMapType(this.GetSingletonType(singleton_type));
        }
        if (AsBoolean(type.GetSingletonType()))
        {
            s84.ctcode.dbnf.ctcode.SingletonType singleton_type = type.GetSingletonType();
            return this.GetSingletonType(singleton_type);
        }
        return "";
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

    private s84.ctcode.system.ctcode.System system;
    private s84.ctcode.dbnf.ctcode.CTCodeFile c_t_code_file;
    private java.lang.String base_name;
    private s84.ctcode.system.ctcode.OutputStream logger;

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
