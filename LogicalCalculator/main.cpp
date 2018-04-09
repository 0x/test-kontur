#include "logCalc.hpp"
#include "parser.hpp"




const  int valueNotDefine(3);
void LogicalCalculator(std::string input, std::string output)
{
	std::ifstream inF(input);
	std::ofstream outF(output);

	int N, M;
	inF >> N >> M;
	for (auto simpleExprIdx = 0; simpleExprIdx < N; simpleExprIdx++)
	{
		std::string simpleExprStr;
		int simpleExprValue;
		inF >> simpleExprStr >> simpleExprValue;
		SimpleExprMap[simpleExprStr] = simpleExprValue;
	}
	std::vector<std::string> CompoundNameVec(M);
	for (auto simpleExprIdx = 0; simpleExprIdx < M; simpleExprIdx++)
	{
		std::string simpleExprStr, tmp;
		std::string	compoundExprStr;
		inF >> simpleExprStr >> tmp;
		getline(inF, compoundExprStr);
		CompoundNameVec[simpleExprIdx] = simpleExprStr;
		CompoundExprMap[simpleExprStr] = compoundExprStr;
	}
	for (auto it : CompoundNameVec)
	{
		std::stringstream compExprSStr, valSimpleExprSStr;
		std::string exprStr;
		compExprSStr << CompoundExprMap[it];
		exprStr = StrToExprStr(compExprSStr, it);

		std::shared_ptr<Expression> y = Parser(exprStr);
		SimpleExprMap[it] = y->ValueExpression();

		if (SimpleExprMap[it] == valueNotDefine)
		{
			outF << "?" << std::endl;
			continue;
		}
		outF << SimpleExprMap[it] << std::endl;
	}
}

std::string StrToExprStr(std::stringstream& compExprSStr, std::string it)
{

	std::string exprStr, A, LogicalOperator;
	while (compExprSStr >> A)
	{
		std::unordered_map<std::string, int>::const_iterator got = SimpleExprMap.find(A);//n
		if (got != SimpleExprMap.end())
		{
			std::string tmp;
			std::stringstream valueSimpleExpr;
			valueSimpleExpr << SimpleExprMap[A];
			valueSimpleExpr >> tmp;
			exprStr += tmp;
		}
		else
		{
			std::unordered_map<std::string, std::string>::const_iterator got = CompoundExprMap.find(A);
			if (got != CompoundExprMap.end())
			{
				std::string tmpStr;
				std::string compoundExprStr = CompoundExprMap[A];
				getline(compExprSStr, tmpStr);
				compExprSStr.clear();
				std::stringstream tmpSStr;
				tmpSStr.str(compoundExprStr);
				std::string exprStr;
				if (A == it)
				{
					SimpleExprMap[A] = valueNotDefine;
				}
				exprStr = StrToExprStr(tmpSStr, it);
				std::shared_ptr<Expression> y = Parser(exprStr);
				std::stringstream tmpVal;
				std::string tmp1;
				std::stringstream tmp2;
				tmpVal << y->ValueExpression();
				int valExpr;
				tmpVal >> tmp1;
				tmp2 << tmp1;
				tmp2 >> valExpr;
				std::string s = A + tmpStr;
				SimpleExprMap[A] = valExpr;
				compExprSStr.str(s);
				continue;
			}

			std::string tmp;
			std::stringstream valueSimpleExpr;
			valueSimpleExpr << valueNotDefine;
			valueSimpleExpr >> tmp;
			exprStr += tmp;
		}
		if (compExprSStr >> LogicalOperator)
		{
			exprStr += LogicalOperator;
		}
	}
	return exprStr;
}



int main(int argc, char *argv[])
{
	//LogicalCalculator("testInput.txt", "testOutput.txt");//потом удалю

	if (argc > 2)
	{
		LogicalCalculator(argv[1], argv[2]);
	}


	return 0;
}

