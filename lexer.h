/*
 * Copyright (C) Rida Bazzi, 2016
 * Edited by Joshua Elkins, 2023
 *
 * Do not share this file with anyone
 */
#ifndef __LEXER__H__
#define __LEXER__H__

#include <vector>
#include <string>

#include "inputbuf.h"

// ------- token types -------------------

typedef enum
{
  END_OF_FILE = 0,
  INT,
  REAL, // 2
  BOO,
  TR,
  FA, // 5
  IF,
  WHILE,
  SWITCH, // 8
  CASE,
  PUBLIC,
  PRIVATE, // 11
  NUM,
  REALNUM,
  NOT,
  PLUS, // 15
  MINUS,
  MULT, // 17
  DIV,
  GTEQ, // 19
  GREATER,
  LTEQ, // 21
  NOTEQUAL,
  LESS, // 23
  LPAREN,
  RPAREN,
  EQUAL,
  COLON,
  COMMA,
  SEMICOLON,
  LBRACE,
  RBRACE,
  ID,
  ERROR
} TokenType;

class Token
{
public:
  void Print();

  std::string lexeme;
  TokenType token_type;
  int line_no;
};

class LexicalAnalyzer
{
public:
  Token GetToken();
  TokenType UngetToken(Token);
  LexicalAnalyzer();

private:
  std::vector<Token> tokens;
  int line_no;
  Token tmp;
  InputBuffer input;

  bool SkipSpace();
  bool SkipComments();
  bool IsKeyword(std::string);
  TokenType FindKeywordIndex(std::string);
  Token ScanIdOrKeyword();
  Token ScanNumber();
};

#endif //__LEXER__H__
