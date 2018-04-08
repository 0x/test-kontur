#include "parser.hpp"



int globIndex(0);
extern  const int valueNotDefine(3);
int valueNumberToken;
TokenValue currToken;

Number::Number(int el) : e(el) {}

int Number::ValueExpr()
{
	return int(e);
}

Conjuction::Conjuction(std::shared_ptr<Expression> N1, std::shared_ptr<Expression> N2) :n1(N1), n2(N2) {}

int Conjuction::ValueExpr()
{
	switch (n1->ValueExpr() * n2->ValueExpr())
	{
	case(0):
		return 0;
	case(1):
		return 1;
	default:
		return valueNotDefine;
		break;
	}
}

Disjuction::Disjuction(std::shared_ptr<Expression> N1, std::shared_ptr<Expression> N2) :n1(N1), n2(N2) {}

int Disjuction::ValueExpr()
{
	switch (n1->ValueExpr() + n2->ValueExpr())
	{
	case(1):
	case(2):
	case(4):
		return 1;
	case(0):
		return 0;
	default:
		return valueNotDefine;
	}
}

TokenValue GetToken(std::string input)
{
	char token = input[globIndex];
	globIndex++;

	if (!token)
		return currToken = TokenValue::END;

	switch (token)
	{
	case '\0':
		return currToken = TokenValue::END;
	case '&':
	case '|':
		return currToken = TokenValue(token);
	}

	valueNumberToken = token - '0';
	return currToken = TokenValue::NUMBER;
}

std::shared_ptr<Expression> Parser(std::string input)
{
	std::shared_ptr<Expression> tmp(SecondPr(input));

	globIndex = 0;
	return tmp;
}

std::shared_ptr<Expression> SecondPr(std::string get)
{
	std::shared_ptr<Expression> left(FirstPr(get));

	while (true)
	{
		switch (currToken)
		{
		case TokenValue::DISJUNCTION:
			left = std::make_shared<Disjuction>(left, Parce(get));
			break;
		default:
			return left;
		}
	}
}

std::shared_ptr<Expression> FirstPr(std::string get)
{
	std::shared_ptr<Expression> left(Parce(get));

	while (true)
	{
		switch (currToken)
		{
		case TokenValue::CONJUNCTION:
			left = std::make_shared<Conjuction>(left, Parce(get));
			break;
		default:
			return left;
		}
	}
}

std::shared_ptr<Expression> Parce(std::string get)
{
	GetToken(get);
	GetToken(get);
	std::shared_ptr<Expression> num(new Number(valueNumberToken));
	return num;
}

