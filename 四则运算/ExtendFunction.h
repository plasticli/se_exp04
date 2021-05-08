#pragma once
/**************************************************************************
�ļ����� ExtendFunction.h
���ߣ�HXP  ��ɫ�޸ģ�ZC  ���ڣ�2017/02/15
����: �������ⲿ������
��Ҫ���ܰ���������ѡ�������⡢��Ŀ�����Լ���ʾ�����ж�

���ߣ�ZC   ���ڣ�2017/03/09
���£�����Դ�ļ���������԰汾��������д����Դ�ж����Ǵ����У��ʶ�ԭ�д�������ع�

ɾ������Ӣ��ѡ������
�޸ģ������⡢���ж�����Ӣ�İ汾���ĳɵ�������ģ�飬��������ͬ�����԰汾

ע������Resource[i]�е�������ע��ͷ�ļ�LanguageResource.h�ڵ�ע��˵��

���ߣ�ZC   �������ڣ�2017/04/18
�����������µĺ��� Scan �ú�����װ��һЩ���ܣ��������û���������ȡ�������ݣ���ȫû��Ҫ���

���ߣ�ZC  ���ڣ�2017/05/06
���£������а汾����������������Ĳ���Ϊ���û�Ҫ����Ŀ�������ļ�·�������ս�����ļ�·��
�ӵ�һ���ļ��ж�ȡ�û�Ҫ�����Ŀ���������ѽ��������ڶ����ļ��С�
***************************************************************************/

#include "Expression.h"
#include "LanguageResource.h"

/*����Ŀ����n��������*/
int GetInt()
{
	int input;
	char ch;
	
	cout << Resource[1];

	while (scanf_s("%d", &input) != 1)//����Ĳ���%d
	{
		cout << Resource[2];
		while ((ch = getchar()) != '\n')
			putchar(ch);//����û��������ַ���������ʾ����ַ�������������ʾ��������Ҫ��
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

/*����������Ŀ�Ĵ�answer��������*/
int GetAnswer()
{
	int input;
	char ch;

	while (scanf_s("%d", &input) != 1)//����Ĳ���%d
	{
		cout << Resource[2];
		while ((ch = getchar()) != '\n')
			putchar(ch);//����û��������ַ���������ʾ����ַ�������������ʾ��������Ҫ��
		cout << Resource[3] << endl;

		cout << Resource[8];
	}

	while ((ch = getchar()) != '\n' && ch != EOF);

	return input;
}


/*����ֵ��һ�����ʽ�࣬�������������Ŀ*/
Expression CreateProblems()
{
	int val = FALSE;//��ȷ��
	Expression expression;

	expression.CreateInfixExpression();
	expression.ReversePolishNotation();
	val = expression.ExpressionValue();

	while (val == FALSE)//ȷ��������ִ�Ϊ����������Ŀ
	{
		Expression expression;

		expression.CreateInfixExpression();
		expression.ReversePolishNotation();
		val = expression.ExpressionValue();
	}
	return expression;
}

/*���ж�*/
bool Judge(int answer, Expression & e)
{
	int val = e.ExpressionValue();//��ȷ��

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

/*����scan������������ʹ�ñ�׼������û�����ȡ������*/
int ScanLanguage(char * language)//����scan�����������û���������ȡ������Ϣ
{
	while (CheckLanguageSupport(language) == false)//�������Լ��
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
	n = GetInt();//������
	if (n == 0)
	{
		cout << Resource[0] << endl;
		getchar();
		getchar();
		return 0;
	}
	return n;
}

/*���ͳ�ƽ�����û����������׼���*/
void Print(int n, int numRight, int numWrong)
{
	static double accuracy;//��ȷ��
	accuracy = (double)numRight / n * 100;

	cout << Resource[9] << endl << endl;
	cout << Resource[10] << numRight << endl;
	cout << Resource[11] << numWrong << endl;
	cout << Resource[12] << accuracy << "%" << endl;

	cout << endl << Resource[0] << endl;
}

/*���ļ��ж�ȡһ���������ַ���*/
int ReadFile(char *filename)//filename�Ǿ���·��
{
	int n;
	fstream f;
	f.open(filename, ios::in);
	f >> n;
	f.close();
	return n;
}
/*�����ս��д���ļ������ݰ������û��������Ŀ����ÿ�����ɵı��ʽ����ȷ�𰸡��û�����Ĵ𰸣�
		���浽�������еڶ�������ָ����·����(��ע���������)*/

/*д����ʽ���û�����𰸡���ȷ��*/
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

/*д�����ս��*/
void WriteResult(char *filename, int n, int numRight, int numWrong)
{
	fstream f;
	f.open(filename, ios::app);

	static double accuracy;//��ȷ��
	accuracy = (double)numRight / n * 100;

	f << Resource[9] << endl << endl;
	f << Resource[10] << numRight << endl;
	f << Resource[11] << numWrong << endl;
	f << Resource[12] << accuracy << "%" << endl;

	f.close();
	return;
}