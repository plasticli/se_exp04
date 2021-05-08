/******************************************************************************
�ļ����� main.cpp
���ߣ�ZC  ���ڣ�2017/02/15
����: ��������ʵ�����幦��

���ߣ�ZC  ���ڣ�2017/03/09
���£�����Դ�ļ���������԰汾��������д����Դ�ж����Ǵ����У��ʶ�ԭ�д�������ع�
ע������Resource[i]�е�������ע��ͷ�ļ�LanguageResource.h�ڵ�ע��˵��

���ߣ�ZC  ���ڣ�2017/05/06
���£������а汾��
*******************************************************************************/
#include "Expression.h"
#include "ExtendFunction.h"
#include "LanguageResource.h"
extern char *Resource[MAXLINE];
int main(int argc, char *argv[])
{
	cout << "Arithmetic Test For Primary School Students" << endl << endl;
	ShowLanguageList();
	char language[200];//�û���������
	gets_s(language);
	int validLangChoice = ScanLanguage(language);
	while (1) {
		if (validLangChoice == -1)//�û�ѡ���˳�����
		{
			return 0;
		}
		else if (validLangChoice == -2)//�û���������ѡ����������
		{
			gets_s(language);
			validLangChoice = ScanLanguage(language);
		}
		else if (validLangChoice == 1)//�û������������ȷ
		{
			break;
		}
	}

	char Langpath[255] = "";//�����û�������ȥ�γ�һ��·��
	strcat_s(Langpath, "LangResourses\\");
	strcat_s(Langpath, language);
	strcat_s(Langpath, ".txt");

	GetResource(Langpath);

	int n;//�û�������������Ŀ����

	n = ScanNumofProblems();  //��׼����
	//n = ReadFile(argv[1]);      //�ļ�����

	int i;
	bool result;//���ڲ��Դ���ȷ���

	int answer;//�û�������Ŀ��
	static int numRight = 0, numWrong = 0;//ͳ������������ȷ�ʹ�������

	for (i = 1; i <= n; i++)
	{
		Expression expression; //��Ŀ
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
		//WriteExpression(argv[2], expression, answer, expression.ExpressionValue(), i);//������ļ�
		expression.~Expression();
	}

	Print(n, numRight, numWrong);   //��׼���
	//WriteResult(argv[2], n, numRight, numWrong);//������ļ�

	cout << endl << Resource[0] << endl;

	for (i = 0; i < 13; i++)
	{
		free(Resource[i]);
	}
	system("pause");
	return 0;
}