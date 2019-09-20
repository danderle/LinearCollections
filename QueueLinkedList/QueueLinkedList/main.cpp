#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <sstream>

class Node
{
public:
	Node() = delete;
	Node(const Node& source)
	{
		*this = source;
	}
	Node(const int value)
		:
		value(value)
	{}
	Node& operator=(const Node& source)
	{
		value = source.value;
		if (source.pNext != nullptr)
			pNext = new Node(*source.pNext);
		return *this;
	}
	~Node()
	{
		delete pNext;
		pNext = nullptr;
	}
	void SetNext(Node* next)
	{
		pNext = next;
	}
	int GetValue() const
	{
		return value;
	}
	Node* GetFront()
	{
		return pNext == nullptr ? this : pNext->GetFront();
	}
	int CountNodes() const
	{
		if (pNext != nullptr)
			return 1 + pNext->CountNodes();
		return 1;
	}
	Node* Disconnect(Node* disconnect)
	{
		Node* prev;
		prev = pNext == disconnect ? this : pNext->Disconnect(disconnect);
		prev->pNext = nullptr;
		return prev;
	}
private:
	int value;
	Node* pNext = nullptr;
};

class Queue
{
public:
	Queue() = default;
	Queue(const Queue& source)
	{
		*this = source;
	}
	Queue& operator=(const Queue& source)
	{
		if (pFront != nullptr && pRear != nullptr)
		{
			delete pRear;
			pRear = nullptr;
			pRear = nullptr;
		}
		pRear = new Node(*source.pRear);
		pFront = pRear->GetFront();
		return *this;
	}
	~Queue()
	{
		delete pRear;
		pFront = nullptr;
		pRear = nullptr;
	}

	void Enqueue(const int value)
	{
		if (IsEmpty())
		{
			pRear = new Node(value);
			pFront = pRear;
		}
		else
		{
			Node* newRear = new Node(value);
			newRear->SetNext(pRear);
			pRear = newRear;
		}
	}
	int Dequeue()
	{
		int retVal = -1;
		std::stringstream ss;
		if (IsEmpty())
		{
			ss << "The queue is empty!!\n";
		}
		else
		{
			retVal = pFront->GetValue();
			if (pFront == pRear)
			{
				delete pFront;
				pFront = pRear = nullptr;
			}
			else
			{
				Node* oldFront = pFront;
				pFront = nullptr;
				pFront = pRear->Disconnect(oldFront);
				delete oldFront;
			}
			ss << "The dequeued value is: " << retVal << "\n";
		}
		std::cout << ss.str();
		return retVal;
	}
	int PeekFront() const
	{
		int retVal = -1;
		std::stringstream ss;
		if (IsEmpty())
		{
			ss << "The queue is empty!!\n";
		}
		else
		{
			retVal = pFront->GetValue();
			ss << "The front value is: " << retVal << "\n";
		}
		std::cout << ss.str();
		return retVal;
	}
	int PeekRear() const
	{
		int retVal = -1;
		std::stringstream ss;
		if (IsEmpty())
		{
			ss << "The queue is empty!!\n";
		}
		else
		{
			retVal = pRear->GetValue();
			ss << "The rear value is: " << retVal << "\n";
		}
		std::cout << ss.str();
		return retVal;
	}
	int Size() const
	{
		if (!IsEmpty())
		{
			return pFront->CountNodes();
		}
		return 0;
	}
	bool IsEmpty() const
	{
		return (pFront == nullptr && pRear == nullptr);
	}
private:
	Node* pFront = nullptr;
	Node* pRear = nullptr;
};

void Test1()
{
	Queue queue;
	queue.Enqueue(1);
	queue.Enqueue(2);
	queue.Enqueue(3);
	if (queue.PeekFront() != 1)
		std::cout << "Test 1 Failed: Wrong front value\n";
	if(queue.PeekRear() != 3)
		std::cout << "Test 1 Failed: Wrong rear value\n";
	queue.Dequeue();
	queue.Dequeue();
	queue.Dequeue();
	queue.Enqueue(1);
	queue.Enqueue(2);
	queue.Enqueue(3);
	if(queue.Dequeue()!= 1)
		std::cout << "Test 1 Failed: Wrong dequeued value\n";
	std::cout << "Test 1 Passed!\n";
}

void Test2()
{
	Queue queue1;
	Queue queue2;
	queue1.Enqueue(1);
	queue1.Enqueue(2);
	queue1.Enqueue(3);
	queue2 = queue1;
	queue2.Dequeue();
	queue2.Dequeue();
	queue1 = queue2;
	queue2.Dequeue();
	queue1.Dequeue();
	if (queue2.IsEmpty() == queue1.IsEmpty())
		std::cout << "Test 2 Passed!!!: Both queues are empty\n";
	else
		std::cout << "Test 2 Failed!!!\n";
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
	getchar();

	return 0;
}