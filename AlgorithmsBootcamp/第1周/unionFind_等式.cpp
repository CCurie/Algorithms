#include<cstdio>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

const int N = 300005;

int Father[N];	//ÿ���ڵ�ĸ��׽ڵ� 
int Rank[N];	//�ڵ���ȣ��Ըýڵ���Ϊ���ڵ��������ȣ�����������ʽ�ϲ� 


int find(int x) {	//���ҽڵ�x���ڼ��ϵĸ���ͬʱ����·��ѹ���Ż� 
	int a = x;	//��������ѯ�Ľ�� 
	while(x != Father[x]) {	//Ѱ�Ҹ��ڵ㣬����x�� 
		x = Father[x];
	} 

	//��a��ʼ��������һ��Ѱ�Ҹ��ڵ�Ĺ��̣���·���Ͼ��������нڵ��father��Ϊ���ڵ�x
	while(a != Father[a]) {
		int z = a;
		a = Father[a];
		Father[z] = x;
		Rank[x]--;	//!!! 
	} 
	return x;
} 

//����n�������Լ�m��Լ�����ж��Ƿ����ҳ�һ�ָ�ֵ����������m��Լ������ 
string getAnswer(int n, int m, vector<int> A, vector<int> B, vector<int> E) {
	//��ʼ����ÿ��Ԫ�ض���һ�������ļ��� 
	for(int i = 1; i <= n; ++i) {
		Father[i] = i;
		Rank[i] = 0;
	} 
	
	//����������ע�⣺�����ȴ������еġ���ȡ���Ȼ���ٴ�������ȡ��������������� 
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
		int setA = find(A[i]);	//A[i]���ڼ��ϵĸ�
		int setB = find(B[i]);	//B[i]���ڼ��ϵĸ�
		if(E[i] == 0) {
			if(setA == setB) {
				return "No";
			}
		} 
		else {
			if(setA != setB) {	//���Ⱥϲ�
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
