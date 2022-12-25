#pragma once
#include<iostream>
using namespace std;
struct LZW
{  
	string word;//词条
     int NO;//码字
	LZW* lchild,* rchild;
}; 
LZW* InserBST(LZW* bt, int k,string word)  //插入节点数据and创建树
{
	if (bt == NULL)
	{
		bt = new LZW;
		bt->NO = k; bt->word = word;
		bt->lchild = bt->rchild = NULL;
	}
	else if (k < bt->NO)
		bt->lchild = InserBST(bt->lchild, k,word);
	else if (k > bt->NO)
		bt->rchild = InserBST(bt->rchild, k,word);

	return bt;
}



void InOrder(LZW* b) //中序遍历递归
{
	if (b != NULL)
	{
		InOrder(b->lchild);
		cout << b->NO << " " << b->word << endl;
		InOrder(b->rchild);
	}
}

LZW* find_for_word(const string& word, LZW* bt)
{
	LZW* p = bt;
	LZW* f = NULL;//初始化
	while (p != NULL && p->word != word) {//往下搜索
		
			f = p;
			p = p->rchild;
		
	}
	return p;//若数值不存在，则指向NULL结点被返回
}
LZW* find_for_NO(const int& NO, LZW* bt)
{
	LZW* p = bt;
	LZW* f = NULL;//初始化
	while (p != NULL && p->NO != NO) {//往下搜索

		f = p;
		p = p->rchild;

	}
	return p;//若数值不存在，则指向NULL结点被返回
}
void Delete(const int& k, LZW*& p) {
	//在p为根的二叉排序树上删除关键字为k的结点
	LZW* s, * temp;
	if (p != NULL)
		if (k < p->NO)//还没找到p
			Delete(k, p->lchild);//递归地在p的左子树上删除关键字为k的结点
		else if (k > p->NO)
			Delete(k, p->rchild);//递归地在p的左子树上删除关键字为k的结点
		else if (p->lchild != NULL && p->rchild != NULL) {//找到p,但是p的左右子树都不空 
			//s = Min(p->rchild);
			temp = p->rchild;
			while (temp->lchild != NULL) {
				temp = temp->lchild;
			}//找到p的右子树上最小的数s，替换掉p，然后删掉s
			s = temp;
			p->NO = s->NO;//将p替换成s
			Delete(s->NO, p->rchild);//递归地删掉s
		}
		else {//相等找到,但是左或右为空
			temp = p;
			if (p->lchild == NULL)       p = p->rchild;//左子树空，则将p替换为右子树上第一个结点
			else if (p->rchild == NULL)  p = p->lchild;//右子树空，则将p替换为左子树上第一个结点
			delete temp;
		}
}

