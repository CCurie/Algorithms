#include<cstdio>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

const int N = 300005;

int Father[N];	//每个节点的父亲节点 
int Rank[N];	//节点的秩（以该节点作为根节点的树的深度），用于启发式合并 


int find(int x) {	//查找节点x所在集合的根；同时进行路径压缩优化 
	int a = x;	//保存所查询的结点 
	while(x != Father[x]) {	//寻找根节点，置于x中 
		x = Father[x];
	} 

	//从a开始，重新走一遍寻找根节点的过程，把路径上经过的所有节点的father置为根节点x
	while(a != Father[a]) {
		int z = a;
		a = Father[a];
		Father[z] = x;
		Rank[x]--;	//!!! 
	} 
	return x;
} 

//给定n个变量以及m个约束，判定是否能找出一种赋值方案满足这m个约束条件 
string getAnswer(int n, int m, vector<int> A, vector<int> B, vector<int> E) {
	//初始化，每个元素都是一个独立的集合 
	for(int i = 1; i <= n; ++i) {
		Father[i] = i;
		Rank[i] = 0;
	} 
	
	//交换！！！注意：必须先处理所有的“相等”，然后再处理“不相等”；否则会产生错误 
	int cnt = 0;
	for(int i = 0; i < m; ++i) {
		if(E[i] == 1) {
			swap(A[i], A[cnt]);
			swap(B[i], B[cnt]);
			swap(E[i], E[cnt]);
			++cnt;
		}
	}
	/* 
	vector<int> A1, B1, E1;
	for(int i = 0; i < m; ++i) {
		if(E[i] == 1) {
			A1.push_back(A[i]);
            B1.push_back(B[i]);
            E1.push_back(E[i]);
		}
	}
	for(int i = 0; i < m; ++i) {
		if(E[i] == 0) {
			A1.push_back(A[i]);
            B1.push_back(B[i]);
            E1.push_back(E[i]);
		}
	}
	*/	 
	
	for(int i = 0; i < m; ++i) {
		int setA = find(A[i]);	//A[i]所在集合的根
		int setB = find(B[i]);	//B[i]所在集合的根
		if(E[i] == 0) {
			if(setA == setB) {
				return "No";
			}
		} 
		else {
			if(setA != setB) {	//按秩合并
				if(Rank[setA] > Rank[setB]) {
					swap(setA, setB);
				}
				Father[setA] = setB;
				if(Rank[setA] == Rank[setB]) {
						++Rank[setB];
				}
				
				/* 
				if(Rank[setA] <= Rank[setB]) {
					Father[setA] = setB;
					if(Rank[setA] == Rank[setB]) {
						Rank[setB]++;
					} 
				}
				else {
					Father[setB] = setA;
					if(Rank[setA] == Rank[setB]) {
						Rank[setA]++;
					}
				}
				*/ 	
			}
		}
	}
	return "Yes"; 
}


int main() {
    int T;
    for (scanf("%d", &T); T--; ) {
        int n, m;
        scanf("%d%d", &n, &m);
        vector<int> A, B, E;
        for (int i = 0; i < m; ++i) {
            int a, b, e;
            scanf("%d%d%d", &a, &b, &e);
            A.push_back(a);
            B.push_back(b);
            E.push_back(e);
        }
        printf("%s\n", getAnswer(n, m, A, B, E).c_str());
    }
    return 0;
}
