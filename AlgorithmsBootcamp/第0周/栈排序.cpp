#include<iostream>
#include<stack>
using namespace std;

stack<int> stackSorting(stack<int>);

int main() {
	int n;
	cin >> n;
	stack<int> RStack;  //乱序的栈(RandomStack) 
	for(int i = 0; i < n; ++i) {
		int tmp;
		cin >> tmp;
		RStack.push(tmp);
	}
	stack<int> SStack = stackSorting(RStack);  //从栈底到栈顶，降序排序的栈(SortedStack)
	while(!SStack.empty()) {
		cout << SStack.top() << endl;  //将该序列按升序输出(LIFO)
		SStack.pop();
	}
	return 0;
}

//RStack：输入栈，栈中的所有元素即是待排序的元素
//返回值：输出栈SStack，即排序后的序列，满足从栈底至栈顶为降序 
stack<int> stackSorting(stack<int> RStack) {
	stack<int> SStack;  //存放返回值，即输出栈 
	if(RStack.empty()) {  //边界情况，因为后续马上有涉及栈顶元素的操作（top、pop操作） 
		return SStack;
	}
	
	int tmp = RStack.top();  //已保证不是空栈，tmp记录下一个要压入SStack的数 
	RStack.pop();	//注意C++top和pop操作是分开的，即pop函数没有返回值 
	//注意不要漏判断条件
	while(!RStack.empty() || (!SStack.empty() && SStack.top() < tmp)) {	//!!! 执行循环的条件；注意第二种情况（top操作之前）必须要保证SStack不为空 
		if(SStack.empty() || SStack.top() >= tmp) {  //直接将tmp压入SStack的情况。使用<=，保证算法的稳定性 
			SStack.push(tmp);
			
			// 更新tmp 
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
