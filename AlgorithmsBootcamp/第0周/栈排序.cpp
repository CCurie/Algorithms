#include<iostream>
#include<stack>
using namespace std;

stack<int> stackSorting(stack<int>);

int main() {
	int n;
	cin >> n;
	stack<int> RStack;  //�����ջ(RandomStack) 
	for(int i = 0; i < n; ++i) {
		int tmp;
		cin >> tmp;
		RStack.push(tmp);
	}
	stack<int> SStack = stackSorting(RStack);  //��ջ�׵�ջ�������������ջ(SortedStack)
	while(!SStack.empty()) {
		cout << SStack.top() << endl;  //�������а��������(LIFO)
		SStack.pop();
	}
	return 0;
}

//RStack������ջ��ջ�е�����Ԫ�ؼ��Ǵ������Ԫ��
//����ֵ�����ջSStack�������������У������ջ����ջ��Ϊ���� 
stack<int> stackSorting(stack<int> RStack) {
	stack<int> SStack;  //��ŷ���ֵ�������ջ 
	if(RStack.empty()) {  //�߽��������Ϊ�����������漰ջ��Ԫ�صĲ�����top��pop������ 
		return SStack;
	}
	
	int tmp = RStack.top();  //�ѱ�֤���ǿ�ջ��tmp��¼��һ��Ҫѹ��SStack���� 
	RStack.pop();	//ע��C++top��pop�����Ƿֿ��ģ���pop����û�з���ֵ 
	//ע�ⲻҪ©�ж�����
	while(!RStack.empty() || (!SStack.empty() && SStack.top() < tmp)) {	//!!! ִ��ѭ����������ע��ڶ��������top����֮ǰ������Ҫ��֤SStack��Ϊ�� 
		if(SStack.empty() || SStack.top() >= tmp) {  //ֱ�ӽ�tmpѹ��SStack�������ʹ��<=����֤�㷨���ȶ��� 
			SStack.push(tmp);
			
			// ����tmp 
			tmp = RStack.top();
			RStack.pop();
		}	
		else {
			RStack.push(SStack.top());
			SStack.pop();
		}
	}
	SStack.push(tmp);	//!!!
	
    return SStack;
} 
