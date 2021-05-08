#pragma once
/********************************
�ļ����� stack.h
���ߣ�ZC   ���ڣ�2017/02/15
����: ���ݽṹջ��stack���������෽��
*********************************/
class Stack
{
private:
	int *Data;
	int posi;
public:
	Stack();
	~Stack();
	bool empty() const;
	int top() const;
	bool push(const int & item);
	bool pop();
	int size();
};

/*stack�෽��*/
Stack::Stack()
{
	Data = new int[50];
}

Stack::~Stack()
{
	delete[] Data;
}
bool Stack::empty()const
{
	return posi == 0;
}

int Stack::top()const
{
	if (empty())
	{
		return false;
	}
	else
	{
		return Data[posi - 1];
	}
}

bool Stack::push(const int & item)
{
	if (posi < 50)
	{
		Data[posi++] = item;
		return true;
	}
	else
	{
		return false;
	}
}

bool Stack::pop()
{
	if (posi > 0)
	{
		int temp;
		temp = Data[--posi];
		return true;
	}
	else
	{
		return false;
	}
}

int Stack::size()
{
	return posi;
}