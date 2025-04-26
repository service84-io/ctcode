#include <algorithm>
#include <fstream>
#include <iostream>
#include <locale>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>

#include "S84.CTCode.dbnf.hpp"
#include "S84.CTCode.CPPTranspiler.ctcode.hpp"
#include "transpiler.hpp"
#include <vector>

#define USE_CTCODE 1

namespace s84
{
namespace ctcode
{
class OStreamWriter : public s84::ctcode::cpptranspiler::ctcode::OutputStream {
public:
	OStreamWriter(std::ostream& stream) : destination(stream) {}

    virtual void WriteLine(std::string line) {
		destination << line << std::endl;
	}

private:
	std::ostream& destination;
};
class CPPTranspiler : public s84::ctcode::Transpiler
{
public:
#if USE_CTCODE
	s84::ctcode::cpptranspiler::ctcode::CPPTranspilerCTCodeLogic ctcodeLogic;
#endif

	CPPTranspiler()
	{
	}
	virtual ~CPPTranspiler()
	{
	}

	virtual int Transpile(const char* buffer, std::string base_name)
	{
		const char* index = buffer;
		s84::ctcode::dbnf::CTCodeFile* ctcodeFile = s84::ctcode::dbnf::CTCodeFile::Parse(index);

		if(ctcodeFile)
		{
			std::ofstream header(base_name + ".hpp", std::ofstream::trunc | std::ofstream::out);
			std::ofstream implementation(base_name + ".cpp", std::ofstream::trunc | std::ofstream::out);
			#if USE_CTCODE
			OStreamWriter header_stream(header);
			OStreamWriter implementation_stream(implementation);
			std::vector<std::string> base_name_tokens = ctcodeLogic.TokenizeBaseName(base_name);
			ctcodeLogic.GenerateHeader(ctcodeFile, &header_stream, base_name_tokens);
			ctcodeLogic.GenerateImplementation(ctcodeFile, &implementation_stream, base_name, base_name_tokens);
			#else
			std::vector<std::string> base_name_tokens = TokenizeBaseName(base_name);
			GenerateHeader(ctcodeFile, header, base_name_tokens);
			GenerateImplementation(ctcodeFile, implementation, base_name, base_name_tokens);
			#endif
			return 0;
		}
		else
		{
			return 1;
		}
	}

	void GenerateHeader(s84::ctcode::dbnf::CTCodeFile* ctcodeFile, std::ostream& header, std::vector<std::string> base_name_tokens)
	{
		#if USE_CTCODE
		OStreamWriter stream(header);
		return ctcodeLogic.GenerateHeader(ctcodeFile, &stream, base_name_tokens);
		#endif
		std::string guard_name = GenerateGuardName(base_name_tokens);
		header << "#ifndef " << guard_name << std::endl;
		header << "#define " << guard_name << std::endl;
		header << std::endl;

		std::vector<s84::ctcode::dbnf::ExternalDefinition*> exdefs = ctcodeFile->GetDeclarations()->GetVector();

		for (std::vector<s84::ctcode::dbnf::ExternalDefinition*>::iterator index = exdefs.begin();index!=exdefs.end();index++) {
			s84::ctcode::dbnf::QualfiedName* exdef_name = (*index)->GetExdef();
			header << "#include \"" << GetExdefHeaderString(exdef_name) << "\"" << std::endl;
		}

		header << std::endl;
		header << "#include <cstring>" << std::endl;
		header << "#include <list>" << std::endl;
		header << "#include <string>" << std::endl;
		header << "#include <vector>" << std::endl;
		header << std::endl;

		for(std::vector<std::string>::iterator base_name_token = base_name_tokens.begin();base_name_token != base_name_tokens.end();++base_name_token)
		{
			header << "namespace " << ToLower(*base_name_token) << std::endl;
			header << "{" << std::endl;
		}

		header << "namespace ctcode" << std::endl;
		header << "{" << std::endl;
		WriteForwardDeclaration(ctcodeFile, header);
		WriteClassDeclarations(ctcodeFile, header);

		for(std::vector<std::string>::iterator base_name_token = base_name_tokens.begin();base_name_token != base_name_tokens.end();++base_name_token)
		{
			header << "};" << std::endl;
		}
		
		header << "};" << std::endl;
		header << std::endl;
		header << "#endif" << std::endl;
	}

	void WriteForwardDeclaration(s84::ctcode::dbnf::CTCodeFile* ctcodeFile, std::ostream& header)
	{
		#if USE_CTCODE
		OStreamWriter stream(header);
		return ctcodeLogic.WriteForwardDeclaration(ctcodeFile, &stream);
		#endif
		std::vector<s84::ctcode::dbnf::Definition*> definitions = ctcodeFile->GetDefinitions()->GetVector();

		for (std::vector<s84::ctcode::dbnf::Definition*>::iterator definitionIndex = definitions.begin();definitionIndex != definitions.end();definitionIndex++){
			s84::ctcode::dbnf::InterfaceDef* interfaceDefinition = (*definitionIndex)->GetInterfaceDef();
			s84::ctcode::dbnf::ClassDef* classDefinition = (*definitionIndex)->GetClassDef();

			if (interfaceDefinition) {
				header << "class " << GenerateClassName(interfaceDefinition->GetName()) << ";" << std::endl;
			}

			if (classDefinition) {
				header << "class " << GenerateClassName(classDefinition->GetName()) << ";" << std::endl;
			}
		}
	}

	void WriteClassDeclarations(s84::ctcode::dbnf::CTCodeFile* ctcodeFile, std::ostream& header)
	{
		#if USE_CTCODE
		OStreamWriter stream(header);
		return ctcodeLogic.WriteClassDeclarations(ctcodeFile, &stream);
		#endif
		std::vector<s84::ctcode::dbnf::Definition*> definitions = ctcodeFile->GetDefinitions()->GetVector();

		header << std::endl;
		header << "template<typename T>" << std::endl;
		header << "inline int Size(std::vector<T> input) { return input.size(); };" << std::endl;
		header << "template<typename T>" << std::endl;
		header << "inline T Element(std::vector<T> input, int element) { return input.at(element); };" << std::endl;
		header << "template<typename T>" << std::endl;
		header << "inline std::vector<T> Append(std::vector<T> input, T element) { input.push_back(element); return input; };" << std::endl;
		header << "inline int Length(std::string input) { return (int)input.length(); };" << std::endl;
		header << "inline std::string At(std::string input, int index) { return input.substr(index, 1); };" << std::endl;
		header << "inline std::string Concat(std::string left, std::string right) { return left + right; };" << std::endl;

		for (std::vector<s84::ctcode::dbnf::Definition*>::iterator definitionIndex = definitions.begin();definitionIndex != definitions.end();definitionIndex++){
			s84::ctcode::dbnf::InterfaceDef* interfaceDefinition = (*definitionIndex)->GetInterfaceDef();
			s84::ctcode::dbnf::ClassDef* classDefinition = (*definitionIndex)->GetClassDef();

			if (interfaceDefinition) {
				WriteInterfaceDeclaration(interfaceDefinition, header);
			}

			if (classDefinition) {
				WriteClassDeclaration(classDefinition, header);
			}
		}
	}

	void WriteInterfaceDeclaration(s84::ctcode::dbnf::InterfaceDef* interfaceDefinition, std::ostream& header)
	{
		#if USE_CTCODE
		OStreamWriter stream(header);
		return ctcodeLogic.WriteInterfaceDeclaration(interfaceDefinition, &stream);
		#endif
		std::string class_name = GenerateClassName(interfaceDefinition->GetName());
		header << std::endl;
		header << "class " << class_name << std::endl;
		header << "{" << std::endl;
		header << "public:" << std::endl;
		header << "    inline " << class_name << "() {};" << std::endl;
		header << "    inline ~" << class_name << "() {};" << std::endl;

		std::vector<s84::ctcode::dbnf::ContentDeclaration*> declarations = interfaceDefinition->GetDeclarations()->GetVector();

		if(declarations.size() > 0)
		{
			header << std::endl;

			for (std::vector<s84::ctcode::dbnf::ContentDeclaration*>::iterator index = declarations.begin(); index != declarations.end();++index)
			{
				header << "    virtual " << GetType((*index)->GetType()) << " " << GenerateCallName((*index)->GetName()) << "(" <<  GenerateParameterList((*index)->GetParameters()) << ") = 0;" << std::endl;
			}
		}

		header << "};" << std::endl;
	}

	void WriteClassDeclaration(s84::ctcode::dbnf::ClassDef* classDefinition, std::ostream& header)
	{
		#if USE_CTCODE
		OStreamWriter stream(header);
		return ctcodeLogic.WriteClassDeclaration(classDefinition, &stream);
		#endif
		std::string class_name = GenerateClassName(classDefinition->GetName());
		header << std::endl;
		header << "class " << class_name << std::endl;
		header << "{" << std::endl;
		header << "public:" << std::endl;
		header << "    inline " << class_name << "() {};" << std::endl;
		header << "    inline ~" << class_name << "() {};" << std::endl;

		std::vector<s84::ctcode::dbnf::ContentDefinition*> definitions = classDefinition->GetDefinitions()->GetVector();
		std::vector<s84::ctcode::dbnf::ContentDefinition*> functionDefinitions;
		std::vector<s84::ctcode::dbnf::ContentDefinition*> memberDefinitions;

		for (std::vector<s84::ctcode::dbnf::ContentDefinition*>::iterator index = definitions.begin(); index != definitions.end();++index)
		{
			if ((*index)->GetFunctionBody() == NULL) {
				memberDefinitions.push_back((*index));
			} else {
				functionDefinitions.push_back((*index));
			}
		}

		if(functionDefinitions.size() > 0)
		{
			header << std::endl;

			for (std::vector<s84::ctcode::dbnf::ContentDefinition*>::iterator index = functionDefinitions.begin(); index != functionDefinitions.end();++index)
			{
				if ((*index)->GetFunctionBody() != NULL) {
					header << "    " << GetType((*index)->GetType()) << " " << GenerateCallName((*index)->GetName()) << "(" <<  GenerateParameterList((*index)->GetParameters()) << ");" << std::endl;
				}
			}
		}

		if(memberDefinitions.size() > 0)
		{
			header << std::endl;
			header << "private:" << std::endl;

			for (std::vector<s84::ctcode::dbnf::ContentDefinition*>::iterator index = memberDefinitions.begin(); index != memberDefinitions.end();++index)
			{
				if ((*index)->GetFunctionBody() == NULL) {
					header << "    " << GetType((*index)->GetType()) << " " << GenerateVariableName((*index)->GetName()) << ";" << std::endl;
				}
			}
		}

		header << "};" << std::endl;
	}

	void GenerateImplementation(s84::ctcode::dbnf::CTCodeFile* ctcodeFile, std::ostream& implementation, std::string base_name, std::vector<std::string> base_name_tokens)
	{
		#if USE_CTCODE
		OStreamWriter stream(implementation);
		return ctcodeLogic.GenerateImplementation(ctcodeFile, &stream, base_name, base_name_tokens);
		#endif
		implementation << "#include \"" + base_name +".hpp\"" << std::endl;
		implementation << std::endl;

		std::vector<s84::ctcode::dbnf::ExternalDefinition*> exdefs = ctcodeFile->GetDeclarations()->GetVector();

		for (std::vector<s84::ctcode::dbnf::ExternalDefinition*>::iterator index = exdefs.begin();index!=exdefs.end();index++) {
			s84::ctcode::dbnf::QualfiedName* exdef_name = (*index)->GetExdef();
			implementation << "#include \"" << GetExdefHeaderString(exdef_name) << "\"" << std::endl;
		}

		implementation << std::endl;

		for(std::vector<std::string>::iterator base_name_token = base_name_tokens.begin();base_name_token != base_name_tokens.end();++base_name_token)
		{
			implementation << "namespace " << ToLower(*base_name_token) << std::endl;
			implementation << "{" << std::endl;
		}

		implementation << "namespace ctcode" << std::endl;
		implementation << "{" << std::endl;
		WriteFunctionDefinitions(ctcodeFile, implementation);

		for(std::vector<std::string>::iterator base_name_token = base_name_tokens.begin();base_name_token != base_name_tokens.end();++base_name_token)
		{
			implementation << "};" << std::endl;
		}
		
		implementation << "};" << std::endl;
	}

	void WriteFunctionDefinitions(s84::ctcode::dbnf::CTCodeFile* ctcodeFile, std::ostream& implementation)
	{
		#if USE_CTCODE
		OStreamWriter stream(implementation);
		return ctcodeLogic.WriteFunctionDefinitions(ctcodeFile, &stream);
		#endif
		std::vector<s84::ctcode::dbnf::Definition*> definitions = ctcodeFile->GetDefinitions()->GetVector();
		std::vector<s84::ctcode::dbnf::ClassDef*> classDefinitions;

		for (std::vector<s84::ctcode::dbnf::Definition*>::iterator definitionIndex = definitions.begin();definitionIndex != definitions.end();definitionIndex++){
			s84::ctcode::dbnf::ClassDef* classDefinition = (*definitionIndex)->GetClassDef();

			if (classDefinition) {
				classDefinitions.push_back(classDefinition);
			}
		}

		for (std::vector<s84::ctcode::dbnf::ClassDef*>::iterator definitionIndex = classDefinitions.begin();definitionIndex != classDefinitions.end();definitionIndex++){
			WriteClassDefinition(*definitionIndex, implementation, definitionIndex == classDefinitions.begin());
		}
	}

	void WriteClassDefinition(s84::ctcode::dbnf::ClassDef* classDefinition, std::ostream& implementation, bool first_class_definition)
	{
		#if USE_CTCODE
		OStreamWriter stream(implementation);
		return ctcodeLogic.WriteClassDefinition(classDefinition, &stream, first_class_definition);
		#endif
		std::string class_name = GenerateClassName(classDefinition->GetName());

		std::vector<s84::ctcode::dbnf::ContentDefinition*> definitions = classDefinition->GetDefinitions()->GetVector();
		std::vector<s84::ctcode::dbnf::ContentDefinition*> functionDefinitions;

		for (std::vector<s84::ctcode::dbnf::ContentDefinition*>::iterator index = definitions.begin(); index != definitions.end();++index)
		{
			if ((*index)->GetFunctionBody() != NULL) {
				functionDefinitions.push_back((*index));
			}
		}

		if(functionDefinitions.size() > 0)
		{
			for (std::vector<s84::ctcode::dbnf::ContentDefinition*>::iterator index = functionDefinitions.begin(); index != functionDefinitions.end();++index)
			{
				if ((!first_class_definition) || index != functionDefinitions.begin()) {
					implementation << std::endl;
				}

				if ((*index)->GetFunctionBody() != NULL) {
					implementation << "    " << GetType((*index)->GetType()) << " " << class_name << "::" << GenerateCallName((*index)->GetName()) << "(" <<  GenerateParameterList((*index)->GetParameters()) << ")" << std::endl;
					WriteCodeBlock(1, implementation, (*index)->GetFunctionBody(), true);
				}
			}
		}
	}

	void WriteInstruction(int indent, std::ostream& implementation, s84::ctcode::dbnf::Instruction* instruction, bool add_newline_after_code_block) {
		#if USE_CTCODE
		OStreamWriter stream(implementation);
		return ctcodeLogic.WriteInstruction(indent, &stream, instruction, add_newline_after_code_block);
		#endif
		if (instruction->GetCodeBlock()) {
			WriteCodeBlock(indent, implementation, instruction->GetCodeBlock(), add_newline_after_code_block);
		}

		if (instruction->GetRtn()) {
			WriteRtn(indent, implementation, instruction->GetRtn());
		}

		if (instruction->GetDeclaration()) {
			WriteDeclaration(indent, implementation, instruction->GetDeclaration());
		}

		if (instruction->GetAssignment()) {
			WriteAssignment(indent, implementation, instruction->GetAssignment());
		}

		if (instruction->GetCall()) {
			WriteCall(indent, implementation, instruction->GetCall());
		}

		if (instruction->GetConditional()) {
			WriteConditional(indent, implementation, instruction->GetConditional(), add_newline_after_code_block);
		}

		if (instruction->GetLoop()) {
			WriteLoop(indent, implementation, instruction->GetLoop(), add_newline_after_code_block);
		}
	}

	void WriteCodeBlock(int indent, std::ostream& implementation, s84::ctcode::dbnf::CodeBlock* code_block, bool add_newline_after_code_block) {
		#if USE_CTCODE
		OStreamWriter stream(implementation);
		return ctcodeLogic.WriteCodeBlock(indent, &stream, code_block, add_newline_after_code_block);
		#endif
		implementation << indentation(indent) << "{" << std::endl;

		std::vector<s84::ctcode::dbnf::Instruction*> instructions = code_block->GetInstructions()->GetVector();
		std::vector<s84::ctcode::dbnf::Instruction*>::iterator last = instructions.end()--;

		for (std::vector<s84::ctcode::dbnf::Instruction*>::iterator index = instructions.begin(); index != instructions.end(); index++) {
			WriteInstruction(indent + 1, implementation, (*index), index != last);
		}

		implementation << indentation(indent) << "}" << std::endl;

		if (add_newline_after_code_block) {
			implementation << std::endl;
		}
	}

	void WriteConditional(int indent, std::ostream& implementation, s84::ctcode::dbnf::Conditional* conditional, bool add_newline_after_code_block) {
		#if USE_CTCODE
		OStreamWriter stream(implementation);
		return ctcodeLogic.WriteConditional(indent, &stream, conditional, add_newline_after_code_block);
		#endif
		implementation << indentation(indent) << "if (" << GetRValueString(conditional->GetRvalue()) << ")" << std::endl;

		if (conditional->GetElseTail()) {
			WriteCodeBlock(indent, implementation, conditional->GetCodeBlock(), false);
			implementation << indentation(indent) << "else" << std::endl;
			WriteCodeBlock(indent, implementation, conditional->GetElseTail()->GetCodeBlock(), add_newline_after_code_block);
		} else {
			WriteCodeBlock(indent, implementation, conditional->GetCodeBlock(), add_newline_after_code_block);
		}
	}

	void WriteLoop(int indent, std::ostream& implementation, s84::ctcode::dbnf::Loop* loop, bool add_newline_after_code_block) {
		#if USE_CTCODE
		OStreamWriter stream(implementation);
		return ctcodeLogic.WriteLoop(indent, &stream, loop, add_newline_after_code_block);
		#endif
		implementation << indentation(indent) << "while (" << GetRValueString(loop->GetRvalue()) << ")" << std::endl;
		WriteCodeBlock(indent, implementation, loop->GetCodeBlock(), add_newline_after_code_block);
	}

	void WriteRtn(int indent, std::ostream& implementation, s84::ctcode::dbnf::Return* rtn) {
		#if USE_CTCODE
		OStreamWriter stream(implementation);
		return ctcodeLogic.WriteRtn(indent, &stream, rtn);
		#endif
		implementation << indentation(indent) << "return " << GetRValueString(rtn->GetRvalue()) << ";" << std::endl;
	}

	void WriteDeclaration(int indent, std::ostream& implementation, s84::ctcode::dbnf::Declaration* declaration) {
		#if USE_CTCODE
		OStreamWriter stream(implementation);
		return ctcodeLogic.WriteDeclaration(indent, &stream, declaration);
		#endif
		std::string assignment_suffix;
		assignment_suffix = "";

		if (declaration->GetAssignment()) {
			assignment_suffix = " = " + GetRValueString(declaration->GetAssignment()->GetRvalue());
		}

		implementation << indentation(indent) << GetVariableDefinition(declaration->GetType(), declaration->GetName()) << assignment_suffix << ";" << std::endl;
	}

	void WriteAssignment(int indent, std::ostream& implementation, s84::ctcode::dbnf::Assignment* assignment) {
		#if USE_CTCODE
		OStreamWriter stream(implementation);
		return ctcodeLogic.WriteAssignment(indent, &stream, assignment);
		#endif
		implementation << indentation(indent) << GenerateVariableName(assignment->GetLvalue()) << " = " << GetRValueString(assignment->GetRvalue()) << ";" << std::endl;
	}

	void WriteCall(int indent, std::ostream& implementation, s84::ctcode::dbnf::Call* call) {
		#if USE_CTCODE
		OStreamWriter stream(implementation);
		return ctcodeLogic.WriteCall(indent, &stream, call);
		#endif
		implementation << indentation(indent) << GetCallString(call) << ";" << std::endl;
	}

	std::string GetExdefHeaderString(s84::ctcode::dbnf::QualfiedName* exdef_name) {
		#if USE_CTCODE
		return ctcodeLogic.GetExdefHeaderString(exdef_name);
		#endif
		return exdef_name->UnParse() + ".hpp";
	}

	std::string indentation(int indent) {
		#if USE_CTCODE
		return ctcodeLogic.Indentation(indent);
		#endif
		std::string result = "";

		while (indent > 0) {
			indent = indent - 1;
			result = result + "    ";
		}

		return result;
	}

	std::string GetRValueSingleString(s84::ctcode::dbnf::RValueSingle* rValueSingle) {
		#if USE_CTCODE
		return ctcodeLogic.GetRValueSingleUnaryString(rValueSingle);
		#endif
		return GetRValueSingleUnaryString(rValueSingle) + GetRValueSingleCoreString(rValueSingle);
	}

	std::string GetRValueSingleUnaryString(s84::ctcode::dbnf::RValueSingle* rValueSingle) {
		#if USE_CTCODE
		return ctcodeLogic.GetRValueSingleUnaryString(rValueSingle);
		#endif
		if (rValueSingle->GetUnaryOperator()) {
			s84::ctcode::dbnf::UnaryOperator* unaryOperator = rValueSingle->GetUnaryOperator();

			if (unaryOperator->GetNegation()) {
				return "!";
			}

			return "/*WARNING UnaryOperator FALL THROUGH*/";
		} else {
			return "";
		}
	}

	std::string GetCallString(s84::ctcode::dbnf::Call* call) {
		#if USE_CTCODE
		return ctcodeLogic.GetCallString(call);
		#endif
		std::string result;
		result = "";

		if (call->GetVariable()) {
			result = result + GenerateVariableName(call->GetVariable()) + "->";
		}

		result = result + GenerateCallName(call->GetFunction()) + "(" + GenerateCallingParameterList(call->GetParameters()) + ")";
		return result;
	}

	std::string GetRValueSingleCoreString(s84::ctcode::dbnf::RValueSingle* rValueSingle) {
		#if USE_CTCODE
		return ctcodeLogic.GetRValueSingleCoreString(rValueSingle);
		#endif
		if (rValueSingle->GetCall()) {
			return GetCallString(rValueSingle->GetCall());
		}

		if (rValueSingle->GetDecimalLiteral()) {
			return rValueSingle->UnParse();
		}

		if (rValueSingle->GetIntegerLiteral()) {
			return rValueSingle->UnParse();
		}

		if (rValueSingle->GetBooleanLiteral()) {
			return rValueSingle->UnParse();
		}

		if (rValueSingle->GetVariable()) {
			return GenerateVariableName(rValueSingle->GetVariable());
		}

		if (rValueSingle->GetStringLiteral()) {
			return rValueSingle->UnParse();
		}

		return "/*WARNING RValueSingle FALL THROUGH*/";
	}

	std::string GetOperator(s84::ctcode::dbnf::BinaryOperator* op) {
		#if USE_CTCODE
		return ctcodeLogic.GetOperator(op);
		#endif
		if (op->GetAddition()) {
			return "+";
		}

		if (op->GetSubtraction()) {
			return "-";
		}

		if (op->GetLessThan()) {
			return "<";
		}

		if (op->GetLessThanEq()) {
			return "<=";
		}

		if (op->GetEquality()) {
			return "==";
		}

		if (op->GetNotEquality()) {
			return "!=";
		}

		if (op->GetGreaterThanEq()) {
			return ">=";
		}

		if (op->GetGreaterThan()) {
			return ">";
		}

		if (op->GetOrOp()) {
			return "||";
		}

		if (op->GetAndOp()) {
			return "&&";
		}

		return "/*WARNING BinaryOperator FALL THROUGH*/";
	}

	std::string GetRValueTail(s84::ctcode::dbnf::RValueTail* rValueTail) {
		#if USE_CTCODE
		return ctcodeLogic.GetRValueTail(rValueTail);
		#endif
		if (rValueTail) {
			s84::ctcode::dbnf::BinaryOperator* op = rValueTail->GetBinaryOperator();

			return " " + GetOperator(op) + " " + GetRValueSingleString(rValueTail->GetValue()) + GetRValueTail(rValueTail->GetTail());
		}

		return "";
	}

	std::string GetRValueString(s84::ctcode::dbnf::RValue* rValue) {
		#if USE_CTCODE
		return ctcodeLogic.GetRValueString(rValue);
		#endif
		return GetRValueSingleString(rValue->GetValue()) + GetRValueTail(rValue->GetTail());
	}

	std::string GetVariableDefinition(s84::ctcode::dbnf::ValueType* type, s84::ctcode::dbnf::Name* name) {
		#if USE_CTCODE
		return ctcodeLogic.GetVariableDefinition(type, name);
		#endif
		return GetType(type) + " " + GenerateVariableName(name);
	}

	std::string GetParameterString(s84::ctcode::dbnf::ParameterListDef* parameter) {
		#if USE_CTCODE
		return ctcodeLogic.GetParameterString(parameter);
		#endif
		return GetVariableDefinition(parameter->GetType(), parameter->GetName());
	}

	std::string GenerateParameterListTail(s84::ctcode::dbnf::ParameterListDef* parameters) {
		#if USE_CTCODE
		return ctcodeLogic.GenerateParameterListTail(parameters);
		#endif
		if (parameters) {
			return ", " + GetParameterString(parameters) + GenerateParameterListTail(parameters->GetParameterTail());
		}

		return "";
	}

	std::string GenerateParameterList(s84::ctcode::dbnf::ParameterListDef* parameters) {
		#if USE_CTCODE
		return ctcodeLogic.GenerateParameterList(parameters);
		#endif
		if (parameters) {
			return GetParameterString(parameters) + GenerateParameterListTail(parameters->GetParameterTail());
		} else {
			return "";
		}
	}

	std::string GenerateCallingParameterList(s84::ctcode::dbnf::ParameterList* parameters) {
		#if USE_CTCODE
		return ctcodeLogic.GenerateCallingParameterList(parameters);
		#endif
		if (parameters) {
			return GetCallingParameterString(parameters) + GenerateCallingParameterListTail(parameters->GetParameterTail());
		} else {
			return "";
		}
	}

	std::string GetCallingParameterString(s84::ctcode::dbnf::ParameterList* parameter) {
		#if USE_CTCODE
		return ctcodeLogic.GetCallingParameterString(parameter);
		#endif
		if (parameter) {
			return GetRValueString(parameter->GetRvalue());
		}
		else {
			return "";
		}
	}

	std::string GenerateCallingParameterListTail(s84::ctcode::dbnf::ParameterList* parameters) {
		#if USE_CTCODE
		return ctcodeLogic.GenerateCallingParameterListTail(parameters);
		#endif
		if (parameters) {
			return ", " + GetCallingParameterString(parameters) + GenerateCallingParameterListTail(parameters->GetParameterTail());
		}

		return "";
	}

	std::string GetType(s84::ctcode::dbnf::ValueType* value_type) {
		#if USE_CTCODE
		return ctcodeLogic.GetType(value_type);
		#endif
		if (value_type->GetDimensionalType()) {
			return GetDimensionalType(value_type->GetDimensionalType());
		}

		if (value_type->GetSingletonType()) {
			return GetSingletonType(value_type->GetSingletonType());
		}

		return "/*WARNING ValueType FALL THROUGH*/";
	}

	std::string GetDimensionalType(s84::ctcode::dbnf::DimensionalType* dimensional_type) {
		#if USE_CTCODE
		return ctcodeLogic.GetDimensionalType(dimensional_type);
		#endif
		int dimensionalNotes;
		dimensionalNotes = dimensional_type->GetDimensionalNote()->GetVector().size();
		return GetDimensionalPrefix(dimensionalNotes) + GetSingletonType(dimensional_type->GetSingletonType()) + GetDimensionalSuffix(dimensionalNotes);
	}

	std::string GetDimensionalPrefix(int dimensionalNotes) {
		#if USE_CTCODE
		return ctcodeLogic.GetDimensionalPrefix(dimensionalNotes);
		#endif
		std::string dimensionalPrefix;
		dimensionalPrefix = "";

		while (dimensionalNotes > 0) {
			dimensionalPrefix = dimensionalPrefix + "std::vector<";
			dimensionalNotes--;
		}

		return dimensionalPrefix;
	}

	std::string GetDimensionalSuffix(int dimensionalNotes) {
		#if USE_CTCODE
		return ctcodeLogic.GetDimensionalSuffix(dimensionalNotes);
		#endif
		std::string dimensionalSuffix;
		dimensionalSuffix = "";

		while (dimensionalNotes > 0) {
			dimensionalSuffix = dimensionalSuffix + ">";
			dimensionalNotes--;
		}

		return dimensionalSuffix;
	}

	std::string GetSingletonType(s84::ctcode::dbnf::SingletonType* singleton_type) {
		#if USE_CTCODE
		return ctcodeLogic.GetSingletonType(singleton_type);
		#endif
		if (singleton_type->GetDefinedType()) {
			return GetDefinedType(singleton_type->GetDefinedType()->GetName());
		}

		if (singleton_type->GetPrimativeType()) {
			std::string primative_type = singleton_type->GetPrimativeType()->UnParse();

			if (primative_type == "int") {
				return "int";
			}

			if (primative_type == "string") {
				return "std::string";
			}

			if (primative_type == "bool") {
				return "bool";
			}

			if (primative_type == "float") {
				return "float";
			}

			if (primative_type == "void") {
				return "void";
			}

			return "/*WARNING PrimativeType FALL THROUGH*/";
		}

		return "/*WARNING SingletonType FALL THROUGH*/";
	}

	std::string GetDefinedType(s84::ctcode::dbnf::QualfiedName* qualified_name) {
		#if USE_CTCODE
		return ctcodeLogic.GetDefinedType(qualified_name);
		#endif
		if (qualified_name->GetTail()) {
			return ToLower(qualified_name->GetName()->UnParse()) + GetDefinedTypeTail(qualified_name->GetTail());
		} else {
			return GenerateClassName(qualified_name->GetName()) + "*";
		}
	}

	std::string GetDefinedTypeTail(s84::ctcode::dbnf::NameTail* name_tail) {
		#if USE_CTCODE
		return ctcodeLogic.GetDefinedTypeTail(name_tail);
		#endif
		if (name_tail->GetTail()) {
			return "::" + ToLower(name_tail->GetName()->UnParse()) + GetDefinedTypeTail(name_tail->GetTail());
		} else {
			return "::" + GenerateClassName(name_tail->GetName()) + "*";
		}
	}

	std::string GenerateClassName(s84::ctcode::dbnf::Name* name_node)
	{
		#if USE_CTCODE
		return ctcodeLogic.GenerateClassName(name_node);
		#endif
		if (name_node)
		{
			return SnakeCaseToCamelCase(name_node->UnParse());
		}
		else
		{
			return "";
		}
	}

	std::string GenerateVariableName(s84::ctcode::dbnf::Name* name_node)
	{
		#if USE_CTCODE
		return ctcodeLogic.GenerateVariableName(name_node);
		#endif
		if(name_node)
		{
			return CamelCaseToSnakeCase(name_node->UnParse());
		}
		else
		{
			return "";
		}
	}

	std::string GenerateCallName(s84::ctcode::dbnf::Name* name_node)
	{
		#if USE_CTCODE
		return ctcodeLogic.GenerateCallName(name_node);
		#endif
		if (name_node)
		{
			return SnakeCaseToCamelCase(name_node->UnParse());
		}
		else
		{
			return "";
		}
	}

	std::vector<std::string> TokenizeBaseName(std::string name)
	{
		#if USE_CTCODE
		return ctcodeLogic.TokenizeBaseName(name);
		#endif
		std::vector<std::string> base_name_tokens;
		std::stringstream splitter(name);
		std::string item;
		
		while(std::getline(splitter, item, '.'))
		{
			base_name_tokens.push_back(item);
		}

		base_name_tokens.pop_back();
		return base_name_tokens;
	}

	std::string GenerateGuardName(std::vector<std::string> base_name_tokens)
	{
		#if USE_CTCODE
		return ctcodeLogic.GenerateGuardName(base_name_tokens);
		#endif
		std::string guard_name;

		for(std::vector<std::string>::iterator base_name_token = base_name_tokens.begin();base_name_token != base_name_tokens.end();++base_name_token)
		{
			guard_name += ToUpper(*base_name_token) + "_";
		}

		guard_name += "CTCODE_H";
		return guard_name;
	}

	std::string SnakeCaseToCamelCase(std::string snake_case)
	{
		#if USE_CTCODE
		return ctcodeLogic.SnakeCaseToCamelCase(snake_case);
		#endif
		bool capitalize_this_letter = true;
		std::string camel_case = "";

		for(std::string::iterator index = snake_case.begin();index != snake_case.end();++index)
		{
			if(*index == '_')
			{
				capitalize_this_letter = true;
			}
			else if(capitalize_this_letter)
			{
				capitalize_this_letter = false;
				camel_case += static_cast<char>(toupper(*index));
			}
			else
			{
				capitalize_this_letter = false;
				camel_case += *index;
			}
		}

		return camel_case;
	}

	std::string CamelCaseToSnakeCase(std::string camel_case)
	{
		#if USE_CTCODE
		return ctcodeLogic.CamelCaseToSnakeCase(camel_case);
		#endif
		bool in_abbreviation = true;
		std::string snake_case = "";

		for(std::string::iterator index = camel_case.begin();index != camel_case.end();++index)
		{
			if(isupper(*index) || isdigit(*index))
			{
				if (!in_abbreviation && !snake_case.empty()) {
					snake_case += '_';
				}

				snake_case += static_cast<char>(tolower(*index));
				in_abbreviation = true;
			}
			else if (*index == '_') {
				snake_case += '_';
				in_abbreviation = true;
			} else
			{
				snake_case += *index;
				in_abbreviation = false;
			}
		}

		return snake_case;
	}

	std::string ToLower(std::string string)
	{
		#if USE_CTCODE
		return ctcodeLogic.ToLower(string);
		#endif
		std::transform(string.begin(), string.end(), string.begin(), tolower);
		return string;
	}

	std::string ToUpper(std::string string)
	{
		#if USE_CTCODE
		return ctcodeLogic.ToUpper(string);
		#endif
		std::transform(string.begin(), string.end(), string.begin(), toupper);
		return string;
	}
};
};
};

static int AddCPPTranspiler()
{
	static s84::ctcode::CPPTranspiler g_cpp_transpiler;
	s84::ctcode::Transpiler::AddTranspiler("s84::ctcode::CPPTranspiler", &g_cpp_transpiler);
	return 0;
}

static int initializer = AddCPPTranspiler();
