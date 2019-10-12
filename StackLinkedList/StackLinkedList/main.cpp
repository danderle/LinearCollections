#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <sstream>

//Node class
//each node will point to the next node in the linked list
class Node
{
	//shorthanded the smart pointer declaration
	typedef std::unique_ptr<Node> NodePtr;
public:
	//deleted the default constructor
	Node() = delete;
	//overloaded constructor for values only
	Node(const int val)
	: value(val)
	{}
	//overloaded constructor for previous node and value
	Node(NodePtr oldTop, const int val)
	: pNext(std::move(oldTop)), value(val)
	{}
	//copy constructor
	Node(const Node& source)
	{
		*this = source;
	}
	//copy assignemnt operator for a deep copy
	Node& operator=(const Node& source)
	{
		value = source.value;
		if(source.pNext != nullptr)
			pNext = std::make_unique<Node>(*source.pNext);
		return *this;
	}
	//default move constructor
	Node(Node&& source) = default;
	//default move assignment operator
	Node& operator=(Node&& source) = default;
	
	//returns the value of node
	int GetValue() const
	{
		return value;
	}
	//returns the next and transfers ownership
	NodePtr GetNextNode()
	{
		return std::move(pNext);
	}
private:
	int value;
	NodePtr pNext;
};

//Stack class
//Nodes can only be added or deleted from the top, FILO
class Stack
{
	//shorthanded the smart pointer declaration
	typedef std::unique_ptr<Node> NodePtr;
public:
	//default constructor
	Stack() = default;
	//copy constructor
	Stack(const Stack& source)
	{
		*this = source;
	}
	//copy assignment operator for a deep copy
	Stack& operator=(const Stack& source)
	{
		pHead = std::make_unique<Node>(*source.pHead);
		return *this;
	}
	
	//Adds values to stack
	void Push(const int val)
	{
		pHead = IsEmpty() ? std::make_unique<Node>(val) : std::make_unique<Node>(std::move(pHead), val);
	}
	//checks for the top value
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
	//deletes the top value
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
			pHead = pHead->GetNextNode();
			ss << "The deleted node had the value: " << retVal << "\n";
		}
		std::cout << ss.str();
		return retVal;
	}
	//checks whether the stack is empty
	bool IsEmpty() const
	{
		return pHead == nullptr;
	}
private:
	std::unique_ptr<Node> pHead;
};

//test 1
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

//test 2
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
	//Sets up the memory leak output
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);

	Test1();
	Test2();

	//dumps the output to the console
	_CrtDumpMemoryLeaks();
	std::cin.get();

	return 0;
}