#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>


class Node
{
public:
	Node() = delete;
	Node(const int value, const int priority)
		:
		value(value),
		priority(priority)
	{}
	Node(const Node& source)
	{
		*this = source;
	}
	Node& operator=(const Node& source)
	{
		value = source.value;
		priority = source.priority;
		if (source.pNext != nullptr)
			pNext = new Node(*source.pNext);
		return *this;
	}
	~Node()
	{
		delete pNext;
		pNext = nullptr;
	}

	int GetPriority() const
	{
		return priority;
	}
	int GetValue() const
	{
		return value;
	}
	void SetPriorityNode(Node* prioNode)
	{
		if (pNext == nullptr)
			pNext = prioNode;
		else if (prioNode->GetPriority() < pNext->GetPriority())
		{
			Node* tmpNext = pNext;
			pNext = prioNode;
			prioNode->pNext = tmpNext;
		}
		else
		{
			pNext->SetPriorityNode(prioNode);
		}
	}
	void SetNext(Node* old)
	{
		pNext = old;
	}
	void Disconnect(Node* disconnect)
	{
		if (pNext == disconnect)
			pNext = nullptr;
		else
			pNext->Disconnect(disconnect);
	}
	Node* GetFront()
	{
		Node* front = nullptr;
		front = pNext == nullptr ? this : pNext->GetFront();
		return front;
	}
private:
	int value = -1;
	int priority = -1;
	Node* pNext = nullptr;
};

class PriorityQueue
{
public:
	PriorityQueue() = default;
	PriorityQueue(const PriorityQueue& source)
	{
		*this = source;
	}
	PriorityQueue& operator=(const PriorityQueue& source)
	{
		if (!IsEmpty())
		{
			delete pBack;
			pBack = pFront = nullptr;
		}
		pBack = new Node(*source.pBack);
		pFront = pBack->GetFront();
		return *this;
	}
	~PriorityQueue()
	{
		delete pBack;
		pBack = pFront = nullptr;

	}

	void Enqueue(const int value, const int priority = 5)
	{
		if (IsEmpty())
		{
			pBack = new Node(value, priority);
			pFront = pBack;
		}
		else
		{
			Node* newNode = new Node(value, priority);
			if (newNode->GetPriority() <= pBack->GetPriority())
			{
				Node* oldBack = pBack;
				pBack = newNode;
				pBack->SetNext(oldBack);
			}
			else
			{
				pBack->SetPriorityNode(newNode);
				pFront = pBack->GetFront();
			}
			
		}
	}
	int Dequeue()
	{
		int retVal = -1;
		int prioVal = -1;
		if (IsEmpty())
			std::cout << "The queue is empty!\n";
		else
		{
			retVal = pFront->GetValue();
			prioVal = pFront->GetPriority();

			if (pBack == pFront)
			{
				delete pBack;
				pBack = pFront = nullptr;
			}
			else
			{
				Node* oldFront = pFront;
				pBack->Disconnect(pFront);
				pFront = pBack->GetFront();
				delete oldFront;
			}
			std::cout << "Dequeued value is: " << retVal << " and has a priority: " << prioVal << std::endl;
		}
		return retVal;
	}
	int PeekFront() const
	{
		int retVal = -1;
		if (IsEmpty())
		{
			std::cout << "The Queue is Empty\n";
		}
		else
		{
			retVal = pFront->GetValue();
			std::cout << "The front value is: " << retVal << std::endl;
		}
		return retVal;
	}
	int PeekBack() const
	{
		int retVal = -1;
		if (IsEmpty())
		{
			std::cout << "The Queue is Empty\n";
		}
		else
		{
			retVal = pBack->GetValue();
			std::cout << "The back value is: " << retVal << std::endl;
		}
		return retVal;
	}
	bool IsEmpty() const
	{
		return pBack == nullptr;
	}
private:
	Node* pFront = nullptr;
	Node* pBack = nullptr;
};

void Test1()
{
	PriorityQueue queue;
	queue.Enqueue(1);
	queue.Enqueue(2);
	queue.Enqueue(3);
	queue.Enqueue(4);
	queue.Enqueue(5);
	queue.Dequeue();
	queue.Dequeue();
	queue.Dequeue();
	queue.Dequeue();
	if (queue.Dequeue() == 5)
		std::cout << "Test 1 passed!\n";
	else
		std::cout << "Test 1 failed!\n";
}

void Test2()
{
	PriorityQueue que1;
	PriorityQueue que2;
	que1.Enqueue(1);
	que1.Enqueue(2);
	que1.Enqueue(3);
	que2 = que1;
	que2.Dequeue();
	que2.Dequeue();
	que1 = que2;
	que1.Dequeue();
	if (que2.PeekBack() == 3)
		std::cout << "Test 2 passed!!\n";
	else
		std::cout << "Test 2 failed!!\n";
}

void Test3()
{
	PriorityQueue que1;
	que1.Enqueue(1, 5);
	que1.Enqueue(2, 5);
	que1.Enqueue(1, 1);
	que1.Enqueue(2, 1);
	que1.Enqueue(1, 3);
	que1.Enqueue(2, 3);
	que1.Enqueue(4, 8);
	que1.Enqueue(5, 8);
	que1.Enqueue(7, 1);
	que1.Enqueue(8, 1);
	
	PriorityQueue que2 = que1;
	que2.Enqueue(40, 20);
	que2.Enqueue(40, 20);
	que2.Enqueue(40, 20);
	que2.Enqueue(40, 20);
	if (que2.Dequeue() == 40)
		std::cout << "Test 3 passed!!\n";
	else
		std::cout << "Test 3 failed!!\n";
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
	Test3();

	_CrtDumpMemoryLeaks();
	getchar();
	return 0;
}