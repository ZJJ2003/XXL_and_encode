#include "LZW.h"
#include<iostream>
#include<string>
#include<fstream>
using namespace std;
string Sequence[100], Sequence1[100];//用来存储两个输入序列
LZW* en_root,*de_root, * en_root1, * de_root1;//两个序列的编码表和译码表
fstream in("in2.txt");
fstream out("out2.txt");//打开文件
int EN_word[100]; int en_num = 0;//数组存储编出来的码字，en_num为计数器
int enword_num = 4,deword_num=4;//记录码字编到多少

void encode(LZW* bt, string s[], int num)//s为输入的序列数组，num为输入的序列的长度
{
	LZW* p = NULL,*q=NULL;
	int a = 0;//a是信源序列数组的下标指针
	string i =s[0];//默认信源序列的第一个词条赋值给i
	
	cout << "编码结果如下：" << endl;
	out << "编码结果如下：" << endl;
	while (1) 
	{
		p = find_for_word(i, bt);//在编码表中找词条为i的元素，如果找不到则返回p=NULL
		if (p != NULL)//找到了词条为i的 码字
		{
			q = p;//将p的地址保存，以便下面输出
		
			a++;
			if (a == num)//当编码进行到序列的最后一个时，直接输出
			{
				out << p->NO<<" ";
				cout << p->NO << " ";
				EN_word[en_num++]=p->NO;
				break;
			}
			i = i + s[a];//i和紧随其后的一个词组合起来，继续搜索

		}
		else//在编码表中没有搜索到词条为i的码字，现在要创建新的码字
		{   
			out << q->NO<<" ";//先把旧的，已经在编码表中的码字输出
			cout << q->NO << " ";
			EN_word[en_num++] = q->NO;//将码字保存在编码数组中，以便后面译码
			enword_num++;
			InserBST(bt, enword_num, i);//添加到编码表中
			i = s[a];//i变为词条的最后一个字母
			
		}
	}
	out << endl;
	cout << endl;
}

void decode(LZW* bt, int en_num)//译码
{
	int a = 0;//数组下标指针
	LZW* p = NULL,*q=NULL;
	string i;
	cout << "译码结果如下：" << endl;
	out << "译码结果如下：" << endl;
goon:while (1)
{
	p = find_for_NO(EN_word[a], bt);//从编码数组中拿出编好的码字，在译码表中查找
	if (p != NULL && a == 0)//第一次译码，由于编码方法的性质，第一次一定能找到
	{
		out << p->word;
		cout << p->word << " ";
		i = p->word;
		de_root = InserBST(bt, ++deword_num, i);//创建新的码字，先把不确定的词条i放入，后面做补充
		a++;
		goto goon;
	}
	if (p != NULL && a != 0)//第2+次在这里
	{
		string k;
		out << p->word;
		cout << p->word << " ";//先将查到的词条输出
		i = p->word;
		k = i.substr(0, 1);//k取词条的第一个字母，用来补全新码字中不确定的词条
		q = find_for_NO(deword_num, de_root);//找到新码字的位置
		q->word = q->word + k;//把k接到最后，完成构建

		de_root = InserBST(bt, ++deword_num, i);//再次创建新的词条，如此循环
		a++;

		if (a == en_num)break;



	}
	if (p == NULL)
	{
		cout << "译码错误！"; break;
	}
}
out << endl;
cout << endl;
}

int main()
{
	
  
	
		cout << "输入需要编码的符号序列，同时用@结尾" << endl;
		int h = 0;//信源序列长度
		while (1)//将要编码的字符存入到数组S中
		{
			char cc;
			in >> cc;

			if (cc == '@')
				break;//在以“@”为结尾的时候结束存储
			string x(1, cc);
			Sequence[h++] = x;
			cout << cc;
		}
		cout << endl;

		en_root = InserBST(en_root, 1, "a");//初始化译码表和编码表
		en_root = InserBST(en_root, 2, "b");
		en_root = InserBST(en_root, 3, "c");
		en_root = InserBST(en_root, 4, "d");

		de_root = InserBST(de_root, 1, "a");
		de_root = InserBST(de_root, 2, "b");
		de_root = InserBST(de_root, 3, "c");
		de_root = InserBST(de_root, 4, "d");

		encode(en_root, Sequence, h);
		decode(de_root, en_num);
		cout << endl;
		cout << "第二组序列：" << endl;
		//第二组序列，先将第一组序列用过的变量初始化
        en_num = 0;
		enword_num = 4; deword_num = 4;
		cout << "输入需要编码的符号序列，同时用@结尾" << endl;
		 h = 0;//信源序列长度
		while (1)//将要编码的字符存入到数组S中
		{
			char cc;
			in >> cc;

			if (cc == '@')
				break;//在以“@”为结尾的时候结束存储
			string x(1, cc);
			Sequence1[h++] = x;
			cout << cc;
		}
		cout << endl;

		en_root1 = InserBST(en_root1, 1, "a");
		en_root1 = InserBST(en_root1, 2, "b");
		en_root1 = InserBST(en_root1, 3, "c");
		en_root1 = InserBST(en_root1, 4, "d");

		de_root1 = InserBST(de_root1, 1, "a");
		de_root1 = InserBST(de_root1, 2, "b");
		de_root1 = InserBST(de_root1, 3, "c");
		de_root1 = InserBST(de_root1, 4, "d");

		encode(en_root1, Sequence1, h);
		decode(de_root1, en_num);
		
	
	//cout << "输出编码表：" << endl;
	//InOrder(en_root);
	//cout << "输出译码表：" << endl;
	//InOrder(de_root);
	return 0;
}
