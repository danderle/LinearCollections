#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <sstream>

class Node
{
public:
	Node() = delete;
	Node(const int val)
	: value(val)
	{}
	Node(Node* oldTop, const int val)
	: next(oldTop), value(val)
	{}
	Node(const Node& source)
	{
		*this = source;
	}
	Node& operator=(const Node& source)
	{
		value = source.value;
		if (source.next != nullptr)
			next = new Node(*source.next);
		return *this;
	}
	~Node()
	{
		delete next;
		next = nullptr;
	}
	int GetValue() const
	{
		return value;
	}
	Node* Delete(Node* oldTop)
	{
		Node* newTop = oldTop->next;
		oldTop->next = nullptr;
		return newTop;
	}
private:
	int value;
	Node* next = nullptr;
};

class Stack
{
public:
	Stack() = default;
	Stack(const Stack& source)
	{
		*this = source;
	}
	Stack& operator=(const Stack& source)
	{
		if (pHead != nullptr)
		{
			delete pHead;
			pHead = nullptr;
		}
		pHead = new Node(*source.pHead);
		return *this;
	}
	~Stack()
	{
		delete pHead;
		pHead = nullptr;
	}
	void Push(const int val)
	{
		pHead = IsEmpty() ? new Node(val) : new Node(pHead, val);
	}
	int Peek() const
	{
		int retVal = -1;
		std::stringstream ss;
		if (!IsEmpty())
		{
			retVal = pHead->GetValue();
			ss << "The top node has the value: " << retVal << "\n";
		}
		else
		{
			ss << "The stack is Empty!!\n";
		}
		std::cout << ss.str();

		return retVal;
	}
	int Pop()
	{
		int retVal = -1;
		std::stringstream ss;
		if (IsEmpty())
		{
			ss << "The stack is Empty!!\n";
		}
		else
		{
			retVal = pHead->GetValue();
			Node* oldTop = pHead;
			pHead = pHead->Delete(oldTop);
			delete oldTop;
			ss << "The deleted node had the value: " << retVal << "\n";
		}
		std::cout << ss.str();
		return retVal;
	}
	bool IsEmpty() const
	{
		return pHead == nullptr;
	}
private:
	Node* pHead = nullptr;
};

void Test1()
{
	Stack stack;
	stack.Push(5);
	stack.Push(6);
	stack.Push(7);
	stack.Push(8);
	if (stack.Peek() == 8)
		std::cout << "Test 1 successful\n";
	else
		std::cout << "Test 1 failed!!\n";
}

void Test2()
{
	Stack stack1;
	stack1.Push(1);
	stack1.Push(2);
	stack1.Push(3);
	Stack stack2 = stack1;
	stack2.Pop();
	stack2.Pop();
	stack1 = stack2;
	stack1.Pop();
	
	if (stack2.Peek() == 1)
		std::cout << "Test 2 successful\n";
	else
		std::cout << "Test 2 failed!!\n";
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