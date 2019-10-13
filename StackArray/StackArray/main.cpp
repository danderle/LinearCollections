#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <sstream>

//Stack class
//this is a static stack, number of values are limited
class Stack
{
public:
	//Pushes values to the stack
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
	//Pops the values off the stack
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
	//Peeks the top value of the stack
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
	//Checks whether the stack is empty
	bool IsEmpty() const
	{
		return top < 0;
	}
private:
	static constexpr int maxLength = 5;
	int array[maxLength] = { 0 };
	int top = -1;
};

//Test 1
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

//Test 2
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
	//Setup for the memory leak output
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);

	Test1();
	Test2();

	//Dumps any memory leaked to the console
	_CrtDumpMemoryLeaks();
	std::cin.get();

	return 0;
}