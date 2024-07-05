/*
 * Created by: Joshua Elkins
 * Date: June 24th, 2023
 */

#include <iostream>
#include <string>
#include "parser.h"
#include "symboltables.h"
#include "lexer.h"
#include "inputbuf.h"

using namespace std;

// int group = 4;

// Syntax Error Function.
void syntax_error()
{
	// printf("I am called\n");
	cout << "Syntax Error\n";
	exit(1);
}

void c1_error(int line_no)
{
	printf("TYPE MISMATCH %d C1\n", line_no);
	exit(1);
}

void c2_error(int line_no)
{
	printf("TYPE MISMATCH %d C2\n", line_no);
	exit(1);
}

void c3_error(int line_no)
{
	printf("TYPE MISMATCH %d C3\n", line_no);
	exit(1);
}

void c4_error(int line_no)
{
	printf("TYPE MISMATCH %d C4\n", line_no);
	exit(1);
}

void c5_error(int line_no)
{
	printf("TYPE MISMATCH %d C5\n", line_no);
	exit(1);
}

string changeType(TokenType type)
{
	if (type == INT)
	{
		return "int";
	}
	else if (type == REAL)
	{
		return "real";
	}
	else if (type == BOO)
	{
		return "bool";
	}
	else
	{
		// Convert int to string
		string s = to_string(type);
		return s;
	}
}

string changeTypeFromInt(int type)
{
	if (type == INT)
	{
		return "int";
	}
	else if (type == REAL)
	{
		return "real";
	}
	else if (type == BOO)
	{
		return "bool";
	}
	else
	{
		string s = to_string(type);
		return s;
	}
}

/*
 * Completed Function.
 * Entry point to the program.
 */
int Parser::parse_program()
{
#ifdef DEBUG
	cout << "Entered Parse Program" << endl;
#endif
	token = lexer.GetToken();
	if (token.token_type == ID)
	{
		lexer.UngetToken(token);
		parse_globalVars();
		/**/
		// symbol_table.printList();
		//  exit(0);
		/**/
		parse_body();
		// symbol_table.printList();
	}
	else if (token.token_type == LBRACE)
	{
		lexer.UngetToken(token);
		parse_body();
	}
	else
	{
		// printf("Error Here 2\n");
		syntax_error();
	}

	return 0;
}

/*
 * Completed Function.
 * Acts as basic entry into the global variable list.
 */
int Parser::parse_globalVars()
{
#ifdef DEBUG
	cout << "Entered Parse Global Variables" << endl;
#endif
	parse_vardecllist();

	return 0;
}

/*
 * Completed
 * Loops our variable declaration list.
 */
int Parser::parse_vardecllist()
{
#ifdef DEBUG
	cout << "Entered Parse Variable Declaration List" << endl;
#endif
	token = lexer.GetToken();
	while (token.token_type == ID)
	{
		lexer.UngetToken(token);
		parse_vardecl();
		token = lexer.GetToken();
	}
	lexer.UngetToken(token);

	return 0;
}

/*
 * Completed Function
 * Acts as a method to handle the declaration statements.
 */
int Parser::parse_vardecl()
{
#ifdef DEBUG
	cout << "Entered Parse Variable Declaration" << endl;
#endif
	// printf("Here\n");
	token = lexer.GetToken();
	if (token.token_type != ID)
	{
		// printf("Error Here 3\n");
		syntax_error();
	}
	lexer.UngetToken(token);
	// Gather ID token info here
	// printf("Hello\n");
	// Get amount of vars in the varlist
	int numOfVars = parse_varlist();

	token = lexer.GetToken();
	if (token.token_type != COLON)
	{
		// printf("Error Here 4\n");
		syntax_error();
	}
	token = lexer.GetToken();
	if (token.token_type == INT || token.token_type == REAL || token.token_type == BOO)
	{
		lexer.UngetToken(token);
		parse_typename(numOfVars);
		// symbol_table.assignTypes(numOfVars, token.token_type);
		token = lexer.GetToken();
		if (token.token_type != SEMICOLON)
		{
			// printf("Error Here 5\n");
			syntax_error();
		}
	}
	else
	{
		// printf("Error Here 6\n");
		syntax_error();
	}

	return 0;
}

/*
 * Completed Function
 * Acts as the gathering function for our variables
 */
int Parser::parse_varlist()
{
#ifdef DEBUG
	cout << "Entered Parse Variable List" << endl;
#endif
	int amount = 0;
	token = lexer.GetToken();
	if (token.token_type != ID)
	{
		// printf("Error Here 7\n");
		syntax_error();
	}
	else
	{
		Token t2 = lexer.GetToken();
		if (t2.token_type == COMMA)
		{
			while (token.token_type == ID && t2.token_type == COMMA)
			{
				// Gather ID token info here
				// Add the ID to the symbol table's linked list
				// printf("Breh\n");
				if (symbol_table.searchForGlobals(token.lexeme) == -1)
				{
					symbol_table.addNode(token.lexeme, ID, symbol_table.global);
					// symbol_table.printList();
					amount++;
				}

				token = lexer.GetToken();
				if (token.token_type != ID)
				{
					// printf("Error Here 8\n");
					syntax_error();
				}
				t2 = lexer.GetToken();
			}
			symbol_table.addNode(token.lexeme, ID, symbol_table.global);
			amount++;
			lexer.UngetToken(t2);
			// printf("Hello\n");
			// symbol_table.printList();
			return amount;
		}
		else
		{
			// Gather singular ID token info here
			// Add the ID to the symbol table's linked list
			symbol_table.addNode(token.lexeme, ID, symbol_table.global);
			lexer.UngetToken(t2);
			return 1;
		}
	}

	return 0;
}

/*
 * Completed Function
 * Just consumes the INT, REAL, or BOO tokens
 */
int Parser::parse_typename(int numOfVars)
{
#ifdef DEBUG
	cout << "Entered Parse Type Name" << endl;
#endif
	token = lexer.GetToken();
	if (token.token_type == INT)
	{
		// We'll be gathering info here
		symbol_table.assignTypes(numOfVars, INT);
	}
	else if (token.token_type == REAL)
	{
		// We'll be gathering info here
		symbol_table.assignTypes(numOfVars, REAL);
	}
	else if (token.token_type == BOO)
	{
		// We'll be gathering info here
		symbol_table.assignTypes(numOfVars, BOO);
	}
	else
	{
		// printf("Error Here 9\n");
		syntax_error();
	}

	return 0;
}

/*
 * Completed Function
 * Acts as the method to consume braces and enter statement list
 */
int Parser::parse_body()
{
#ifdef DEBUG
	cout << "Entered Parse Body" << endl;
#endif
	token = lexer.GetToken();
	if (token.token_type == LBRACE)
	{
		// printf("Yo\n");
		parse_stmtlist();
		token = lexer.GetToken();
		if (token.token_type != RBRACE)
		{
			// printf("Error Here 10\n");
			syntax_error();
		}
	}
	else
	{
		// printf("Error Here 11\n");
		syntax_error();
	}

	return 0;
}

/*
 * Completed Function
 * Acts as our looper to enter all our statements
 */
int Parser::parse_stmtlist()
{
#ifdef DEBUG
	cout << "Entered Parse Statement List" << endl;
#endif
	token = lexer.GetToken();
	while (token.token_type == ID || token.token_type == IF || token.token_type == WHILE || token.token_type == SWITCH)
	{
		lexer.UngetToken(token);
		parse_stmt();
		token = lexer.GetToken();
	}
	lexer.UngetToken(token);

	return 0;
}

/*
 * Completed Function
 * Acts as our method to enter the specific statements
 */
int Parser::parse_stmt()
{
#ifdef DEBUG
	cout << "Entered Parse Statement" << endl;
#endif
	token = lexer.GetToken();
	if (token.token_type == ID)
	{
		lexer.UngetToken(token);
		parse_assstmt();
	}
	else if (token.token_type == IF)
	{
		lexer.UngetToken(token);
		parse_ifstmt();
	}
	else if (token.token_type == WHILE)
	{
		lexer.UngetToken(token);
		parse_whilestmt();
	}
	else if (token.token_type == SWITCH)
	{
		lexer.UngetToken(token);
		parse_switchstmt();
	}
	else
	{
		// printf("Error Here 12\n");
		syntax_error();
	}

	return 0;
}

/*
 * Function Completed
 * Acts as our assignment statement parser
 */
int Parser::parse_assstmt()
{
#ifdef DEBUG
	cout << "Entered Parse Assignment Statement" << endl;
#endif
	// symbol_table.printList();
	token = lexer.GetToken();
	if (token.token_type != ID)
	{
		// printf("Error Here 13\n");
		syntax_error();
	}
	// Get Type of the ID
	int lhs = symbol_table.search(token.lexeme);
	string lhsvar = token.lexeme;

	token = lexer.GetToken();
	if (token.token_type != EQUAL)
	{
		syntax_error();
	}

	int rhs = parse_expression();
	lhs = symbol_table.search(lhsvar);

	if (lhs == 1 || lhs == 2 || lhs == 3)
	{

		if (lhs == rhs)
		{
		}
		else
		{
			if (lhs <= 3 && rhs <= 3)
			{
				c1_error(token.line_no);
			}
			else if (lhs <= 3 && rhs > 4)
			{
				symbol_table.rearrangeTypes(rhs, lhs);
				rhs = lhs;
			}
			else
			{
				symbol_table.rearrangeTypes(rhs, lhs);
				rhs = lhs;
			}
		}
	}
	else
	{
		symbol_table.rearrangeTypes(lhs, rhs);
		lhs = rhs;
	}

	token = lexer.GetToken();
	if (token.token_type != SEMICOLON)
	{
		// printf("Error Here 15\n");
		syntax_error();
	}

	// symbol_table.printList();

	return 0;
}

/*
 * Completed Function
 * Acts as our expression handling.
 */
int Parser::parse_expression()
{
#ifdef DEBUG
	cout << "Entered Parse Expression" << endl;
#endif
	token = lexer.GetToken();
	if (token.token_type == NOT)
	{
		lexer.UngetToken(token);
		parse_unaryOperator();
		int requiredBooleanExpression = parse_expression();
		// printf("Required Boolean Expression: %d\n", requiredBooleanExpression);

		if (requiredBooleanExpression > 4)
		{
			symbol_table.rearrangeTypes(requiredBooleanExpression, 3);
			return (3);
		}
		else if (requiredBooleanExpression != 3)
		{
			c3_error(token.line_no);
		}
		else
		{
			// printf("Yoyo\n");
			return (3);
		}
	}
	else if (token.token_type == ID || token.token_type == NUM || token.token_type == REALNUM || token.token_type == TR || token.token_type == FA || token.token_type == PLUS || token.token_type == MINUS || token.token_type == MULT || token.token_type == DIV || token.token_type == GREATER || token.token_type == LESS || token.token_type == GTEQ || token.token_type == LTEQ || token.token_type == EQUAL || token.token_type == NOTEQUAL)
	{
		// Save varname
		string varnameplease = "";
		if (token.token_type == ID)
		{
			varnameplease = token.lexeme;
		}
		// Run the rest of the Parsing
		if (token.token_type == PLUS || token.token_type == MINUS || token.token_type == MULT || token.token_type == DIV)
		{
			// group++;
			// int currentGroup = group;
			/*string currentVarName = "";
			Token temp = lexer.GetToken();
			if (temp.token_type == ID)
			{
				currentVarName = temp.lexeme;
			}
			lexer.UngetToken(temp);*/

			lexer.UngetToken(token);
			int operatorType = parse_binaryOperator();
			// printf("Operator Type: %d\n", operatorType);
			// printf("Entering Arithmetic Parse Expession\n");
			int firstOperandType = parse_expression();
			// printf("First Operand Type: %s\n", changeTypeFromInt(firstOperandType).c_str());
			int secondOperandType = parse_expression();
			// printf("Second Operand Type: %s\n", changeTypeFromInt(secondOperandType).c_str());
			// printf("Exiting Arithmetic Parse Expession\n");

			/*if (firstOperandType > 4)
			{
				// printf("currentVarName: %s\n", currentVarName.c_str());
				if (firstOperandType != symbol_table.findGroup(currentVarName))
				{
					firstOperandType = symbol_table.findGroup(currentVarName);
				}
			}*/

			if (firstOperandType != secondOperandType)
			{
				// Check the type matching
				if (firstOperandType <= 3 && secondOperandType > 4)
				{
					// printf("I am called\n");
					symbol_table.rearrangeTypes(secondOperandType, firstOperandType);
					secondOperandType = firstOperandType;
					// printf("Hello\n");
				}
				else if (firstOperandType > 3 && secondOperandType <= 3)
				{
					// printf("I am called2\n");
					symbol_table.rearrangeTypes(firstOperandType, secondOperandType); //**
					firstOperandType = secondOperandType;
				}
				else if (firstOperandType > 4 && secondOperandType > 4)
				{
					// printf("I am called3\n");
					symbol_table.rearrangeTypes(secondOperandType, firstOperandType);
					secondOperandType = firstOperandType;
				}
				else
				{
					// printf("Hello\n");
					//  symbol_table.printList();
					c2_error(token.line_no);
				}
			}
			// printf("Second Operand Type: %s\n", changeTypeFromInt(secondOperandType).c_str());
			return secondOperandType;
		}
		else if (token.token_type == GREATER || token.token_type == LESS || token.token_type == GTEQ || token.token_type == LTEQ || token.token_type == EQUAL || token.token_type == NOTEQUAL)
		{
			// group++;
			// int currentGroup = group;
			string currentVarName = "";
			Token temp = lexer.GetToken();
			if (temp.token_type == ID)
			{
				currentVarName = temp.lexeme;
			}
			lexer.UngetToken(temp);

			lexer.UngetToken(token);
			int operatorType = parse_binaryOperator();
			// printf("Entering Comparison Parse Expession\n");
			int firstOperandType = parse_expression();

			// printf("First Operand Type: %s\n", changeTypeFromInt(firstOperandType).c_str());
			int secondOperandType = parse_expression();
			// printf("Second Operand Type: %s\n", changeTypeFromInt(secondOperandType).c_str());
			// printf("Exiting Comparison Parse Expession\n");

			if (firstOperandType > 4)
			{
				// printf("currentVarName: %s\n", currentVarName.c_str());
				if (firstOperandType != symbol_table.findGroup(currentVarName))
				{
					firstOperandType = symbol_table.findGroup(currentVarName);
				}
			}

			if (firstOperandType != secondOperandType)
			{
				if (firstOperandType <= 3 && secondOperandType > 4)
				{
					symbol_table.rearrangeTypes(secondOperandType, firstOperandType);
					secondOperandType = firstOperandType;
					return (3);
				}
				else if (firstOperandType > 4 && secondOperandType <= 3)
				{
					symbol_table.rearrangeTypes(firstOperandType, secondOperandType);
					firstOperandType = secondOperandType;
					return (3);
				}
				else if (secondOperandType > 4 && firstOperandType > 4)
				{
					symbol_table.rearrangeTypes(secondOperandType, firstOperandType);
					secondOperandType = firstOperandType;
					return (3);
				}
				else
				{
					c2_error(token.line_no);
				}
			}
			else
			{
				return 3;
			}
		}
		else if (token.token_type == ID || token.token_type == NUM || token.token_type == REALNUM || token.token_type == TR || token.token_type == FA)
		{
			// printf("Calling on %s\n", token.lexeme.c_str());
			// printf("Token: %s\n", token.lexeme.c_str());
			lexer.UngetToken(token);
			// printf("%s\n", token.lexeme.c_str());
			int type = parse_primary();
			if (type == -1)
			{
				// Set implicit var in Assignments class to current ID
				assignments.setImplicitVar(token.lexeme);
			}
			return type;
		}
	}
	else
	{
		// printf("Error Here 16\n");
		syntax_error();
	}

	return 0;
}

/*
 * Completed Function
 * Gets our NOT token
 */
int Parser::parse_unaryOperator()
{
#ifdef DEBUG
	cout << "Entered Parse Unary Operator" << endl;
#endif
	token = lexer.GetToken();
	if (token.token_type != NOT)
	{
		// printf("Error Here 17\n");
		syntax_error();
	}
	// Do something with the NOT

	return 0;
}

/*
 * Completed Function
 * Acts as our binary handler
 */
int Parser::parse_binaryOperator()
{
#ifdef DEBUG
	cout << "Entered Binary Operator" << endl;
#endif
	// printf("BinaryOperatorCalled\n");
	token = lexer.GetToken();
	if (token.token_type == PLUS || token.token_type == MINUS || token.token_type == MULT || token.token_type == DIV)
	{
		// Do something with these Tokens
		return 1;
	}
	else if (token.token_type == GREATER || token.token_type == LESS || token.token_type == GTEQ || token.token_type == LTEQ || token.token_type == EQUAL || token.token_type == NOTEQUAL)
	{
		// Do something with these Tokens
		return 2;
	}
	else
	{
		// printf("Error Here 18\n");
		syntax_error();
	}

	return 0;
}

/*
 * Completed Function
 * Acts as our primary handler
 */
int Parser::parse_primary()
{
#ifdef DEBUG
	cout << "Entered Parse Primary" << endl;
#endif
	token = lexer.GetToken();
	if (token.token_type == ID || token.token_type == NUM || token.token_type == REALNUM || token.token_type == TR || token.token_type == FA)
	{
		// Do something with these Tokens
		if (token.token_type == ID)
		{
			// printf("ID: %s\n", token.lexeme.c_str());
			int type = symbol_table.search(token.lexeme);
			if (type != -1)
			{
				string temp = token.lexeme + ": " + changeTypeFromInt(type) + " #";
				assignments.addAssignment(temp);
			}
			else
			{
				// Add to the symbol table
				symbol_table.addNode(token.lexeme, symbol_table.global, symbol_table.global);
				type = symbol_table.global;
				symbol_table.global++;
				assignments.addImplicitVar(token.lexeme);
				return type;
			}
			return type;
		}
		else if (token.token_type == NUM)
		{
			// printf("NUM: %s\n", token.lexeme.c_str());
			return INT;
		}
		else if (token.token_type == REALNUM)
		{
			// printf("REALNUM: %s\n", token.lexeme.c_str());
			return REAL;
		}
		else if (token.token_type == TR || token.token_type == FA)
		{
			// printf("TR/FA: %s\n", token.lexeme.c_str());
			return BOO;
		}
	}
	else
	{
		// printf("Error Here 19\n");
		syntax_error();
	}

	return -1;
}

/*
 * Completed Function
 * Acts as our If Statement handler
 */
int Parser::parse_ifstmt()
{
#ifdef DEBUG
	cout << "Entered Parse If Statement" << endl;
#endif
	token = lexer.GetToken();
	if (token.token_type != IF)
	{
		// printf("Error Here 20\n");
		syntax_error();
	}
	token = lexer.GetToken();
	if (token.token_type != LPAREN)
	{
		// printf("Error Here 21\n");
		syntax_error();
	}

	int ifConditionResult = parse_expression();
	// printf("If Condition Result: %d\n", ifConditionResult);
	if (ifConditionResult > 4)
	{
		symbol_table.rearrangeTypes(ifConditionResult, 3);
		// symbol_table.printList();
	}
	else if (ifConditionResult != 3)
	{
		// symbol_table.printList();
		c4_error(token.line_no);
	}

	token = lexer.GetToken();
	if (token.token_type != RPAREN)
	{
		// printf("Error Here 22\n");
		syntax_error();
	}
	parse_body();

	return 0;
}

/*
 * Completed Function
 * Acts as our While Statement handler
 */
int Parser::parse_whilestmt()
{
#ifdef DEBUG
	cout << "Entered Parse While Statement" << endl;
#endif
	token = lexer.GetToken();
	if (token.token_type != WHILE)
	{
		// printf("Error Here 23\n");
		syntax_error();
	}
	token = lexer.GetToken();
	if (token.token_type != LPAREN)
	{
		// printf("Error Here 24\n");
		syntax_error();
	}

	int whileConditionResult = parse_expression();
	if (whileConditionResult > 4)
	{
		symbol_table.rearrangeTypes(whileConditionResult, 3);
	}
	else if (whileConditionResult != 3)
	{
		c4_error(token.line_no);
	}

	token = lexer.GetToken();
	if (token.token_type != RPAREN)
	{
		// printf("Error Here 25\n");
		syntax_error();
	}
	parse_body();

	return 0;
}

/*
 * Completed Function
 * Acts as out Switch Statement handler
 */
int Parser::parse_switchstmt()
{
#ifdef DEBUG
	cout << "Entered Switch Statement" << endl;
#endif
	token = lexer.GetToken();
	if (token.token_type != SWITCH)
	{
		// printf("Error Here 26\n");
		syntax_error();
	}
	token = lexer.GetToken();
	if (token.token_type != LPAREN)
	{
		// printf("Error Here 27\n");
		syntax_error();
	}

	int switchConditionResult = parse_expression();
	// printf("Switch Condition Result: %d\n", switchConditionResult);
	if (switchConditionResult <= 4 && switchConditionResult != 1)
	{
		c5_error(token.line_no);
	}
	else if (switchConditionResult > 4)
	{
		symbol_table.rearrangeTypes(switchConditionResult, 1);
	}

	token = lexer.GetToken();
	if (token.token_type != RPAREN)
	{
		// printf("Error Here 28\n");
		syntax_error();
	}
	token = lexer.GetToken();
	if (token.token_type != LBRACE)
	{
		// printf("Error Here 29\n");
		syntax_error();
	}

	// No Need to Capture the Result of parse_caselist()
	parse_caselist();

	token = lexer.GetToken();
	if (token.token_type != RBRACE)
	{
		// printf("Error Here 30\n");
		syntax_error();
	}

	return 0;
}

/*
 *
 */
int Parser::parse_caselist()
{
#ifdef DEBUG
	cout << "Entered Parse Case List" << endl;
#endif
	token = lexer.GetToken();
	if (token.token_type == CASE)
	{
		while (token.token_type == CASE)
		{
			lexer.UngetToken(token);
			parse_case();
			token = lexer.GetToken();
		}
		lexer.UngetToken(token);
	}
	else
	{
		// printf("Error Here 31\n");
		syntax_error();
	}

	return 0;
}

int Parser::parse_case()
{
#ifdef DEBUG
	cout << "Entered Parse Case" << endl;
#endif
	token = lexer.GetToken();
	if (token.token_type != CASE)
	{
		// printf("Error Here 32\n");
		syntax_error();
	}
	token = lexer.GetToken();
	if (token.token_type != NUM)
	{
		// printf("Error Here 33\n");
		syntax_error();
	}
	// Do something with this
	token = lexer.GetToken();
	if (token.token_type != COLON)
	{
		// printf("Error Here 34\n");
		syntax_error();
	}
	parse_body();

	return 0;
}

int main()
{
#ifdef DEBUG
	cout << "Entered Main" << endl;
#endif
	// printf("Hello\n");
	int i;
	Parser *parseProgram = new Parser();
	i = parseProgram->parse_program();

	// parseProgram->symbol_table.printList();
	parseProgram->symbol_table.outputVars();
	// parseProgram->assignments.printAssignments();
	// cout << "\nEnd of Program" << endl;
	return 0;
}
