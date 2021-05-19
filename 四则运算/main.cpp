/******************************************************************************
文件名： main.cpp
作者：任豆豆 李罗正   日期：2021/05/19
描述: 主函数，实现主体功能

作者：任豆豆 李罗正   日期：2021/05/19
更新：用资源文件管理多语言版本，把语言写到资源中而不是代码中，故对原有代码进行重构
注：关于Resource[i]中的内容请注意头文件LanguageResource.h内的注释说明

作者：任豆豆 李罗正   日期：2021/05/19
更新：命令行版本。
*******************************************************************************/
#include "Expression.h"
#include "ExtendFunction.h"
#include "LanguageResource.h"
extern char *Resource[MAXLINE];
int main(int argc, char *argv[])
{
	cout << "Arithmetic Test For Primary School Students" << endl << endl;
	ShowLanguageList();
	char language[200];//用户输入语言
	gets_s(language);
	int validLangChoice = ScanLanguage(language);
	while (1) {
		if (validLangChoice == -1)//用户选择退出程序
		{
			return 0;
		}
		else if (validLangChoice == -2)//用户输入有误并选择重新输入
		{
			gets_s(language);
			validLangChoice = ScanLanguage(language);
		}
		else if (validLangChoice == 1)//用户输入的语言正确
		{
			break;
		}
	}

	char Langpath[255] = "";//根据用户的输入去形成一个路径
	strcat_s(Langpath, "LangResourses\\");
	strcat_s(Langpath, language);
	strcat_s(Langpath, ".txt");

	GetResource(Langpath);

	int n;//用户输入想做的题目数量

	n = ScanNumofProblems();  //标准输入
	//n = ReadFile(argv[1]);      //文件输入

	int i;
	bool result;//用于测试答案正确与否

	int answer;//用户输入题目答案
	static int numRight = 0, numWrong = 0;//统计总题数、正确和错误题数

	for (i = 1; i <= n; i++)
	{
		Expression expression; //题目
		expression = CreateProblems();

		cout << "No." << i << "\t" << expression << endl;
		cout << "\t" << Resource[8];

		answer = GetAnswer();

		result = Judge(answer, expression);

		if (result == true)
		{
			numRight++;
		}
		else if (result == false)
		{
			numWrong++;
		}
		//WriteExpression(argv[2], expression, answer, expression.ExpressionValue(), i);//输出到文件
		expression.~Expression();
	}

	Print(n, numRight, numWrong);   //标准输出
	//WriteResult(argv[2], n, numRight, numWrong);//输出到文件

	cout << endl << Resource[0] << endl;

	for (i = 0; i < 13; i++)
	{
		free(Resource[i]);
	}
	system("pause");
	return 0;
}