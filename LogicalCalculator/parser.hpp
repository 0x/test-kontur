#pragma once
#include <iostream>                                     
#include <fstream>
#include <sstream>
#include <string>
#include <memory>



enum class TokenValue
{
	NUMBER, DISJUNCTION = '|', CONJUNCTION = '&', END
};

TokenValue GetToken(std::string input);

class Expression
{
public:
	virtual int ValueExpr() = 0;
};

std::shared_ptr<Expression> Parser(std::string input);
std::shared_ptr<Expression> FirstPr(std::string get);
std::shared_ptr<Expression> SecondPr(std::string get);
std::shared_ptr<Expression> Parce(std::string get);

class Number : public Expression
{
private:
	int e;
public:
	Number(int el);
	int ValueExpr();
};

class Conjuction : public Expression
{
private:
	std::shared_ptr<Expression> n1, n2;
public:
	Conjuction(std::shared_ptr<Expression> N1, std::shared_ptr<Expression> N2);
	int ValueExpr();
};

class  Disjuction : public Expression
{
private:
	std::shared_ptr<Expression> n1, n2;
public:
	Disjuction(std::shared_ptr<Expression> N1, std::shared_ptr<Expression> N2);
	int ValueExpr();
};

