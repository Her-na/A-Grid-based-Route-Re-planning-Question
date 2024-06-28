#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define CG A.seekg(sizeof(char),ios::cur)//CG change 跳过一个字符；
using namespace std;
int r,c,rbegin,cbegin,rend,cend,blockcount;//初始化总的和行列起止点
int **grid=NULL;
void gridbegin()
{
	grid=new int*[r+1];
for(int i=0;i<r+1;++i)
{
	grid[i]=new int[c+1];
         for(int j=0;j<c+1;++j)
	         grid[i][j]=1;
}
}
void griddelete()
{
	for(int i=0;i<r+1;i++)
	{
		delete[] grid[i];
	}
	delete grid;
}
void Beginning(ifstream &A)
{
	A>>r;CG;A>>c;CG;CG;
	cout<<"The grid has "<<r<<" rows and "<<c<<" columns."<<endl;
	CG;A>>rbegin;CG;A>>cbegin;CG;CG;CG;
	CG;A>>rend;CG;A>>cend;CG;CG;CG;

}
void PUSH_Bolcks(ifstream &A)
{
	int rnow=0,cnow=0;
	char ch;
	A>>ch;
	while(ch!='$')
	{
	A>>rnow;CG;A>>cnow;CG;CG;
	grid[rnow][cnow]=0;
	A>>ch;
	blockcount++;
	}
	CG;CG;
}
struct RouteNode
{
	int row;
	int column;
	int vaule;
	RouteNode* next;
};
RouteNode* create(ifstream &A)
{
	RouteNode* head=NULL,*p1,*p2;
	char ch;
	p1=new RouteNode;
	CG;A>>p1->row;CG;A>>p1->column;CG;A>>ch;CG;
	cout<<"["<<p1->row<<","<<p1->column<<"]->";
	//p1->vaule=0;
	int jishu=1;
	while(!A.eof())
	{
		if(head==NULL)
			head=p1;
		else
			p2->next=p1;
		p2=p1;
		p1=new RouteNode;
		CG;A>>p1->row;CG;A>>p1->column;CG;A>>ch;CG;jishu++;
		if(A.eof())
		{
			cout<<"["<<p1->row<<","<<p1->column<<"]";
			p2->next=p1;
			p2=p1;
			break;
		}
		else cout<<"["<<p1->row<<","<<p1->column<<"]->";
		if(jishu%2==0){ CG;CG;}
		if(jishu%5==0)cout<<endl;
		
	}
	p2->next=NULL;
	return head;
}
int RouteCheak(RouteNode* p)
{
	int count1=1;
	while(p->next!=NULL)
	{
	if(count1==1)
	{
		if(p->row!=rbegin||p->column!=cbegin)
	    {
			 cout<<endl<<"Initial cell in the route is wrong!"<<endl;return 0;
		}
	}
	if(grid[p->row][p->column]==0)
		{cout<<endl<<"There is a bolck on this route!"<<endl;return 0;}
	if(abs((p->next->row-p->row)+(p->next->column-p->column))!=1)
	{
		{cout<<endl<<"There is an illegal move in the route!"<<endl;return 0;}}
	p=p->next;
	count1++;
	}
	if(p->next==NULL)
	{
	    if(p->row!=rend||p->column!=cend)
	        {cout<<endl<<"Goal cell in the route is wrong!"<<endl;return 0;}
	}
	cout<<endl<<"The route is valid!"<<endl;
	return 0;
}
void printgrid(RouteNode *p)
{
	
	for(int i=0;i<r+1;i++)
	{
		for(int j=0;j<c+1;j++)
		{
			
			if(i==0||j==0)
			{
				if(i==j){cout<<'\32'<<" ";continue;}
				else if(i==0) {cout<<j-1<<" ";continue;}
				else {cout<<i-1<<" ";continue;}
			}
			RouteNode* Search;
			int judge=0;
			Search=p;
			while(Search!=NULL)
			{
			if(i-1==(Search->row)&&j-1==(Search->column))
			{
				judge=1;
				if(i-1==rbegin&&j-1==cbegin)
					{cout<<"I"<<" ";break;}
				if(i-1==rend&&j-1==cend)
					{cout<<"G"<<" ";break;}
				if(grid[i-1][j-1]==1){cout<<"*"<<" ";break;}	
				else {cout<<"#"<<" ";break;}
			}
			Search=Search->next;
			}
			if(judge==0)
			{
			if(grid[i-1][j-1]==0){cout<<"#"<<" ";continue;}
		    cout<<'\32'<<" ";
			}
		}
		cout<<endl;
	}
}
void RouteConnect(RouteNode* p1,RouteNode* p2)
{
	RouteNode* p;
	p=p1;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	p->next=p2;
}
RouteNode * ReplanRoute(RouteNode *p)
{
	 int DKr,DKc,LJr,LJc,tra=0,DuanDian=0;//断开和连接
	 while(p->next!=NULL)
	 {  
		 if(grid[p->row][p->column]==1&&grid[p->next->row][p->next->column]==0&&DuanDian==1)
		 {LJr=rend;LJc=cend;break;}
		 if(grid[p->row][p->column]==1&&grid[p->next->row][p->next->column]==0)
		 {DKr=p->row;DKc=p->column;DuanDian++;}
		 if(grid[p->next->row][p->next->column]==1&&grid[p->row][p->column]==0)
		 {LJr=p->next->row;LJc=p->next->column;}
		 p=p->next;
	 }
	 int a=1,a1,b=1,b1;
	 for(int i=DKr+1;i<LJr;i++)
	 {
		 a1=0;
		 for(int j=0;j<c;j++)
		   if(grid[i][j]==1)
			   a1=1;
		 if(a1==0)
		 { a=0;break;}
	 }
	 for(int i=DKc+1;i<LJc;i++)
	 {
		 b1=0;
		 for(int j=0;j<r;j++)
		   if(grid[j][i]==1)
			   b1=1;
		 if(b1==0)
		 { b=0;break;}
	 }
	 if(a==0||b==0)
	 {cout<<"The route can not be repair!"<<endl;return 0;}
	 /*cout<<DKr<<","<<DKc<<endl;
	 cout<<LJr<<","<<LJc<<endl;*///检验起始断开点
	 //建立修复链表的原点
	 RouteNode *node=new RouteNode,*NewHead;
	 node->row=DKr;
	 node->column=DKc;
	 node->vaule=tra;
	 node->next=NULL;
	 NewHead=node;
	 //上下左右遍历路径
	 while(node->row>=0&&node->column>=0&&node->row<r&&node->column<c)
	 {
		 //if(node->row==5&&node->column==0)cout<<"["<<node->row<<","<<node->column<<"]"<<endl;关键节点调试
		 //向下
		 if(node->row+1<r&&grid[node->row+1][node->column]==1)
		 {
			 RouteNode *below=new RouteNode;
			 below->row=node->row+1;
			 below->column=node->column;
			 below->vaule=tra;
			 below->next=NULL;
			 //进入链表
			 RouteConnect(node,below);
			 if(below->row==LJr&&below->column==LJc)
			 return NewHead;
		 }
		 //向左
		 if(node->column-1>=0&&grid[node->row][node->column-1]==1)
		 {
			 RouteNode *left=new RouteNode;
			 left->row=node->row;
			 left->column=node->column-1;
			 left->vaule=tra;
			 left->next=NULL;
			 //进入链表
			 RouteConnect(node,left);
			 if(left->row==LJr&&left->column==LJc)
				 return NewHead;
		 }
		//向右
	    	 if(node->column+1<c&&grid[node->row][node->column+1]==1)
		 {
			 RouteNode *right=new RouteNode;
			 right->row=node->row;
			 right->column=node->column+1;
			 right->vaule=tra;
			 right->next=NULL;
			 //进入链表
			 RouteConnect(node,right);
			 if((right->row==LJr)&&(right->column==LJc))
				 return NewHead;
		 }
		//向上
			 if(node->row-1>=0&&grid[node->row-1][node->column]==1)
		 {
			 RouteNode *above=new RouteNode;
			 above->row=node->row-1;
			 above->column=node->column;
			 above->vaule=tra;
			 above->next=NULL;
			 //进入链表
			 RouteConnect(node,above);
			 if(above->row==LJr&&above->column==LJc)
			   return NewHead;
		 }
			 node=node->next;
			 tra++;
			 //cout<<tra;
	 }
	 return 0;
}
int travel(RouteNode *node)//中间链表剪切函数
{
	RouteNode* p;
	p=node;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	RouteNode* p1;
	while(p!=node)
	{
		p1=node;
		for(int i=0;i<p->vaule;i++)
			p1=p1->next;	
		p1->next=p;
		p=p1;
	}
	return 0;
}
RouteNode * RouteCombine(RouteNode *head,RouteNode *p0)//合并中间链表和原链表函数
{
    RouteNode* p1,*p2;
	if(head==0)
	{
		head=p0;head->next=0;return head;
	}
	p1=head;
	while((p1->row!=p0->row)||(p1->column!=p0->column)&&(p1->next!=NULL))
	{
		p2=p1;p1=p1->next;
	}
	p2->next=p0;
	while(p2->next!=NULL)
	{p2=p2->next;}
	while(p1)
	{
		if((p1->row==p2->row)&&(p1->column==p2->column))
			break;
		p1=p1->next;
	}
	p2->next=p1->next;
	return head;	 
}

int main()
{
	RouteNode* road;
	ifstream infile("text1.txt");
	if(!infile)
	{
		cout<<"文件不存在！\n";
        exit(0);
	}
	//建立文件。接下来读取整个初始表格，用链表。
	cout<<"==STAGE 0==============================="<<endl;
	Beginning(infile);
	gridbegin();
	PUSH_Bolcks(infile);
	cout<<"The grid has "<<blockcount<<" blocks"<<endl;
	cout<<"The initial cell in the grid is ["<<rbegin<<","<<cbegin<<"]."<<endl;
	cout<<"The goal cell in the grid is ["<<rend<<","<<cend<<"]."<<endl;
	road=create(infile);
	RouteCheak(road);
	cout<<"==STAGE 1==============================="<<endl;
	printgrid(road);
	RouteNode *MidRoute;
	MidRoute=ReplanRoute(road);
	if(MidRoute==0)
		return 0;
	//cout<<MidRoute->row<<MidRoute->column;//判断RepalnRuote函数是否发挥作用
	travel(MidRoute);
	road=RouteCombine(road,MidRoute);
	cout<<"======================================="<<endl;
	printgrid(road);
	RouteNode* test;
	test=road;
	int countout=0;
	while(test->next!=NULL)
	{
		cout<<"["<<test->row<<","<<test->column<<"]->";
		countout++;
		if(countout%5==0)
			cout<<endl;
		test=test->next;
	}
	cout<<"["<<test->row<<","<<test->column<<"]";
	RouteCheak(road);	
    infile.close();
    griddelete();
	system("pause");
	return 0;
}