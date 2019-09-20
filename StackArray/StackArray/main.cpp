#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <sstream>

class Stack
{
public:
	void Push(const int value)
	{
		if (top >= maxLength-1)
			std::cout << "Stack is full!!\n";
		else
		{
			top++;
			array[top] = value;
		}
	}
	int Pop()
	{
		int retVal = -1;
		if(IsEmpty())
			std::cout << "The stack is empty\n";
		else
		{
			retVal = array[top];
			array[top] = 0;
			std::cout << "Popped value is: " << retVal << std::endl;
			top--;
		}
		return retVal;
	}
	int Peek() const
	{
		int retVal = -1;
		if (IsEmpty())
			std::cout << "The stack is empty\n";
		else
		{
			retVal = array[top];
			std::cout << "Top value is: " << retVal << std::endl;
		}
		return retVal;
	}
	bool IsEmpty() const
	{
		return top < 0;
	}
private:
	static constexpr int maxLength = 5;
	int array[maxLength] = { 0 };
	int top = -1;
};

void Test1()
{
	Stack stack;
	stack.Push(0);
	stack.Push(1);
	stack.Push(2);
	stack.Push(3);
	stack.Push(4);
	stack.Push(5);
	stack.Push(6);
	stack.Peek();
	stack.Pop();
	stack.Pop();
	stack.Pop();
	stack.Pop();
	stack.Pop();
	stack.Pop();
}

void Test2()
{
	Stack stack1;
	stack1.Push(1);
	stack1.Push(2);

	Stack stack2 = stack1;
	stack2.Pop();
	stack1 = stack2;

	stack1.Pop();
}

int main()
{
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);

	Test1();
	Test2();

	_CrtDumpMemoryLeaks();
	std::cin.get();

	return 0;
}