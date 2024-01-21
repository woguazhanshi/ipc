#include<iostream>
#include<algorithm>
#include<bits/stdc++.h>
#define ll long long
#define PP pair<int,int>
using namespace std;

//bool cmp(int a,int b)
//{    return a > b;}



typedef double DataType; //结点权值的数据类型

typedef struct HTNode //单个结点的信息
{
	DataType weight; //权值
	int parent=0; //父节点
	int lc, rc;//左右孩子
	
}*HuffmanTree;

typedef char **HuffmanCode;

void  Select(HuffmanTree& HT, int n, int& s1, int& s2)//优先队列
{
	priority_queue< int,vector<int>,greater<int> > q;
	
	for(int i=1;i<=n;i++)
	{
		if(HT[i].parent ==0)
		q.push(HT[i].weight);
	}
    for(int i=1;i<=2*n-1;i++)
	{
		if(HT[i].weight==q.top() )
		{
			s1=i;
			q.pop();break;
		}
	}	
	for(int i=1;i<=2*n-1;i++)
	{
		if(HT[i].weight==q.top()&&i!=s1 )
		{
			s2=i;
			break;
		}
	}	
}
int length(int i,HuffmanTree &HT){
	if(HT[i].parent ==0)   return 0;
	return length(HT[i].parent ,HT)+1;
	
	
}
int WPL(int n,HuffmanTree &HT)
{
	int wpl=0;
	for(int i=1;i<=n;i++)
	{
		wpl+=HT[i].weight*length(i,HT) ;
	}
	return wpl;
}


void CreateHuff(HuffmanTree& HT, DataType* w, int n)
{
	int m = 2 * n - 1; //哈夫曼树总结点数
	HT = (HuffmanTree)calloc(m + 1, sizeof(HTNode)); //开m+1个HTNode，因为下标为0的HTNode不存储数据
	for (int i = 1; i <= n; i++)
	{
		HT[i].weight = w[i - 1]; //赋权值给n个叶子结点
	}
	for (int i = n + 1; i <= m; i++) //构建哈夫曼树
	{
		//选择权值最小的s1和s2，生成它们的父结点
		int s1, s2;
		Select(HT, i - 1, s1, s2); //在下标为1到i-1的范围找到权值最小的两个值的下标，其中s1的权值小于s2的权值
		HT[i].weight = HT[s1].weight + HT[s2].weight; //i的权重是s1和s2的权重之和
		HT[s1].parent = i; //s1的父亲是i
		HT[s2].parent = i; //s2的父亲是i
		HT[i].lc = s1; //左孩子是s1
		HT[i].rc = s2; //右孩子是s2
	}
	
	
		
	
}


int main(){
	int n; 
	cin >> n;
	DataType* w = (DataType*)malloc(sizeof(DataType)*n);
	int sum=0;
	for(int i=0;i<n;i++)	cin >> w[i];
	 
    HuffmanTree HT;
	CreateHuff(HT,w,n);	
	      
	      cout << WPL(n,HT)<< endl;
         
  
	free(w);
	return 0;
}