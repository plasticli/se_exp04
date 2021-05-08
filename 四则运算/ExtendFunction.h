#pragma once
/**************************************************************************
文件名： ExtendFunction.h
作者：HXP  润色修改：ZC  日期：2017/02/15
描述: 其他的外部函数。
主要功能包括：语言选择、输入检测、题目生成以及显示、答案判定

作者：ZC   日期：2017/03/09
更新：用资源文件管理多语言版本，把语言写到资源中而不是代码中，故对原有代码进行重构

删除：中英文选择函数。
修改：输入检测、答案判定的中英文版本，改成单纯函数模块，不包含不同的语言版本

注：关于Resource[i]中的内容请注意头文件LanguageResource.h内的注释说明

作者：ZC   更新日期：2017/04/18
描述：增加新的函数 Scan 该函数封装了一些功能，用于与用户交互，获取输入数据（完全没必要嘛。。

作者：ZC  日期：2017/05/06
更新：命令行版本。在命令行中输入的参数为：用户要求题目数量的文件路径、最终结果的文件路径
从第一个文件中读取用户要求的题目数量，并把结果输出到第二个文件中。
***************************************************************************/

#include "Expression.h"
#include "LanguageResource.h"

/*对题目数量n的输入检测*/
int GetInt()
{
	int input;
	char ch;
	
	cout << Resource[1];

	while (scanf_s("%d", &input) != 1)//输入的不是%d
	{
		cout << Resource[2];
		while ((ch = getchar()) != '\n')
			putchar(ch);//如果用户输入了字符串，就显示这个字符串，并且在显示“不符合要求”
		cout << Resource[3] << endl;

		cout << Resource[1];
	}

	while((ch = getchar()) != '\n' && ch != EOF);

	while (input <= 0 || input > 100)
	{
		if (input < 0)
		{
			cout << Resource[4] << endl;
			input = GetInt();
		}
		if (input > 100)
		{
			cout << Resource[5] << endl;
			input = GetInt();
		}
		if (input == 0)
		{
			return 0;
		}
	}
	return input;
}

/*对于输入题目的答案answer的输入检测*/
int GetAnswer()
{
	int input;
	char ch;

	while (scanf_s("%d", &input) != 1)//输入的不是%d
	{
		cout << Resource[2];
		while ((ch = getchar()) != '\n')
			putchar(ch);//如果用户输入了字符串，就显示这个字符串，并且在显示“不符合要求”
		cout << Resource[3] << endl;

		cout << Resource[8];
	}

	while ((ch = getchar()) != '\n' && ch != EOF);

	return input;
}


/*返回值是一个表达式类，里面的内容是题目*/
Expression CreateProblems()
{
	int val = FALSE;//正确答案
	Expression expression;

	expression.CreateInfixExpression();
	expression.ReversePolishNotation();
	val = expression.ExpressionValue();

	while (val == FALSE)//确保不会出现答案为非整数的题目
	{
		Expression expression;

		expression.CreateInfixExpression();
		expression.ReversePolishNotation();
		val = expression.ExpressionValue();
	}
	return expression;
}

/*答案判定*/
bool Judge(int answer, Expression & e)
{
	int val = e.ExpressionValue();//正确答案

	if (answer == val)
	{
		cout << Resource[6] << endl << endl;
		return true;
	}
	else
	{
		cout << Resource[7] << val << endl << endl;
		return false;
	}
}

/*两个scan函数，用于与使用标准输入的用户交互取得数据*/
int ScanLanguage(char * language)//两个scan函数用于与用户交互并获取输入信息
{
	while (CheckLanguageSupport(language) == false)//输入语言检测
	{
		if (strcmp("e", language) == 0)
		{
			cout << endl << "The program is going to be finished. Goodbye!~" << endl;
			getchar();
			return -1;
		}
		cout << "Sorry. Your input is wrong or software does not support your language. " << endl;

		ShowLanguageList();
		return -2;
	}
	return 1;
}

int ScanNumofProblems()
{
	int n;
	n = GetInt();//输入检测
	if (n == 0)
	{
		cout << Resource[0] << endl;
		getchar();
		getchar();
		return 0;
	}
	return n;
}

/*输出统计结果给用户，输出到标准输出*/
void Print(int n, int numRight, int numWrong)
{
	static double accuracy;//正确率
	accuracy = (double)numRight / n * 100;

	cout << Resource[9] << endl << endl;
	cout << Resource[10] << numRight << endl;
	cout << Resource[11] << numWrong << endl;
	cout << Resource[12] << accuracy << "%" << endl;

	cout << endl << Resource[0] << endl;
}

/*从文件中读取一个整型数字返回*/
int ReadFile(char *filename)//filename是绝对路径
{
	int n;
	fstream f;
	f.open(filename, ios::in);
	f >> n;
	f.close();
	return n;
}
/*将最终结果写入文件，内容包括：用户输入的题目数，每个生成的表达式、正确答案、用户输入的答案，
		保存到命令行中第二个参数指定的路径。(请注意参数设置)*/

/*写入表达式、用户输入答案、正确答案*/
void WriteExpression(char *filename, Expression expression, int useranswer, int rightanswer, int i)
{
	fstream f;
	f.open(filename, ios::app);

	f << "No." << i << "\t" << expression << endl;
	f << Resource[13] << ": " << useranswer << endl;
	f << Resource[14] << ": " << rightanswer << endl << endl;

	f.close();
	return;
}

/*写入最终结果*/
void WriteResult(char *filename, int n, int numRight, int numWrong)
{
	fstream f;
	f.open(filename, ios::app);

	static double accuracy;//正确率
	accuracy = (double)numRight / n * 100;

	f << Resource[9] << endl << endl;
	f << Resource[10] << numRight << endl;
	f << Resource[11] << numWrong << endl;
	f << Resource[12] << accuracy << "%" << endl;

	f.close();
	return;
}