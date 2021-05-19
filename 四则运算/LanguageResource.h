#pragma once
/*******************************************************************
文件名： LanguageResource.h
作者：任豆豆 李罗正   日期：2021/05/19
描述: 通过引用文件的内容实现各种不同的语言版本

作者：任豆豆 李罗正   日期：2021/05/19
更新：因为更新了命令行版本所以多了两条语句资源
********************************************************************/
#include<iostream>
#include<fstream>‎

#define MAXLINE 30 //资源文件内的最大行数
#define MAXLEN 200 //每行的最大字符数

//存储资源文件内容的指针数组
char *Resource[MAXLINE] = { (char *)malloc(MAXLEN * sizeof(char)) };

/****************************************************
此表说明了Resource[i]，下标i和其对应的中文内容
其他文件中是其他语言对应的翻译版本

序号i |		Resource[i]的内容	  |		备注
--------------------------------------------------
---
0	  |		程序即将结束，拜拜！~	  |
1	  |		输入题目数量：		  |
2	  |		你的输入：			  |		输入检测
3	  |		不符合要求			  |		输入检测
4	  |		你输入的数字太小。	  |		输入检测
5	  |		你输入的数字太大。	  |		输入检测
6	  |		恭喜你，回答正确！	  |		答案判定
7	  |		答案错误！正确答案是：  |		答案判定
8	  |		请输入你的答案：		  |
9	  |		结果统计				  |
10	  |		您做对的题目数量为：	  |		结果统计
11	  |		您做错的题目数量为：	  |		结果统计
12	  |		正确率为：			  |		结果统计
13    |     您输入的答案是：		  |     输出到文件
14	  |		正确答案为：			  |     输出到文件
*****************************************************/
	

/*展示目前支持的语言列表*/
void ShowLanguageList()
{
	fstream file;//文件流
	file.open("LangResourses\\LanguageList.txt", ios::in);

	int num = 1;
	char language[20];
	cout << "You can choose one of these languages below:" << endl;
	while (file.getline(language, 20))
	{
		cout << num << ". " << language << endl;
		num++;
	}
	file.close();
	cout << "Please input your language name (or input e to exit): ";
}

/*检测用户输入的语言是否支持。如果支持，返回true。不支持返回false*/
bool CheckLanguageSupport(char * users_Lang)
{
	fstream file;

	char Langpath[255] = "";//根据用户的输入去形成一个路径
	strcat_s(Langpath, "LangResourses\\");
	strcat_s(Langpath, users_Lang);
	strcat_s(Langpath, ".txt");

	file.open(Langpath, ios::in);//根据这个路径打开这个资源

	if (file.is_open())
	{
		file.close();
		return true;
	}
	else
	{
		return NULL;
	}
}

/*根据正确的语言文档路径，取得其中的内容以便使用。存放到全局指针数组Resource中*/
void GetResource(char * filepath)
{
	fstream File;
	File.open(filepath, ios::in);
	char one_Line[MAXLEN];

	/*将每行文件的内容放到Resource[i]中，这样可以通过下标i访问各种语句*/
	int i;
	for (i = 0; File.getline(one_Line, MAXLEN); i++)
	{
		Resource[i] = (char *)malloc(MAXLEN * sizeof(char));
		strcpy_s(Resource[i], MAXLEN * sizeof(char), one_Line);
	}
	File.close();
}