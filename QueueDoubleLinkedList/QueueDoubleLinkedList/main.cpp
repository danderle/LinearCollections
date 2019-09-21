#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <sstream>

class Node
{
public:
	Node() = delete;
	Node(const int value)
		:
		value(value)
	{}
	Node(const Node& source)
	{
		*this = source;
	}
	Node& operator=(const Node& source)
	{
		value = source.value;
		if (source.pPrev != nullptr)
		{
			pPrev = new Node(*source.pPrev);
		}
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
	void SetPrev(Node* prev)
	{
		pPrev = prev;
	}
	Node* GetPrev() const
	{
		return pPrev;
	}
	Node* GetNext() const
	{
		return pNext;
	}
	int GetValue() const
	{
		return value;
	}
	void DisconnectNext()
	{
		pNext = nullptr;
	}
	void DisconnectPrev()
	{
		pPrev = nullptr;
	}
private:
	int value;
	Node* pNext = nullptr;
	Node* pPrev = nullptr;
};

class QueueDL
{
public:
	QueueDL() = default;
	QueueDL(const QueueDL& source)
	{
		*this = source;
	}
	QueueDL& operator=(const QueueDL& source)
	{
		if (!IsEmpty())
		{
			delete pBack;
			pBack = nullptr;
			pFront = nullptr;
		}
		pFront = new Node(*source.pFront);
		Node* prev = pFront->GetPrev();
		Node* next = pFront;
		while (prev != nullptr)
		{
			prev->SetNext(next);
			next = prev;
			prev = prev->GetPrev();
		}
		pBack = next;
		return *this;
	}
	~QueueDL()
	{
		delete pBack;
		pBack = nullptr;
		pFront = nullptr;
	}

	void PushToBack(int value)
	{
		if (IsEmpty())
		{
			pBack = new Node(value);
			pFront = pBack;
		}
		else
		{
			Node* oldBack = pBack;
			pBack = new Node(value);
			pBack->SetNext(oldBack);
			oldBack->SetPrev(pBack);
			if (pFront == oldBack)
			{
				pFront->SetPrev(pBack);
			}
		}
	}
	void PushToFront(int value)
	{
		if (IsEmpty())
		{
			pFront = new Node(value);
			pBack = pFront;
		}
		else
		{
			Node* oldFront = pFront;
			pFront = new Node(value);
			pFront->SetPrev(oldFront);
			oldFront->SetNext(pFront);
			if (pBack == oldFront)
			{
				pBack->SetNext(pFront);
			}
		}
	}
	int PeekFront() const
	{
		if (IsEmpty())
			return -1;
		std::stringstream ss;
		ss << "The front value: " << pFront->GetValue();
		std::cout << ss.str() << std::endl;
		return pFront->GetValue();
	}
	int PeekBack() const
	{
		std::stringstream ss;
		ss << "The back value: " << pBack->GetValue();
		std::cout << ss.str() << std::endl;
		return pBack->GetValue();
	}
	int DeleteFront()
	{
		if (IsEmpty())
		{
			std::cout << "Is Empty\n";
			return -1;
		}
		int retVal = pFront->GetValue();
		Node* oldFront = pFront;
		pFront = oldFront->GetPrev();
		if (pFront != nullptr)
			pFront->DisconnectNext();
		else
			pBack = pFront;
		oldFront->DisconnectPrev();
		delete oldFront;
		std::cout << "Deleted front: " << retVal << std::endl;
		return retVal;
	}
	int DeleteBack()
	{
		if (IsEmpty())
		{
			std::cout << "Is Empty\n";
			return -1;
		}
		int retVal = pBack->GetValue();
		Node* oldBack = pBack;
		pBack = oldBack->GetNext();
		if(pBack != nullptr)
			pBack->DisconnectPrev();
		oldBack->DisconnectNext();
		delete oldBack;
		std::cout << "Deleted back: " << retVal << std::endl;
		return retVal;
	}
	void ListFtoB() const
	{
		Node* node = pFront;
		std::stringstream ss;
		ss << "Front <<";
		while (node != nullptr)
		{
			ss << node->GetValue() << "<<";
			node = node->GetPrev();
		}
		ss << " Back";
		std::cout << ss.str() << std::endl;
	}
	void ListBtoF() const
	{
		Node* node = pBack;
		std::stringstream ss;
		ss << "Back >>";
		while (node != nullptr)
		{
			ss << node->GetValue() << ">>";
			node = node->GetNext();
		}
		ss << " Front";
		std::cout << ss.str() << std::endl;
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
	QueueDL queueDl;
	queueDl.PushToBack(1);
	queueDl.PushToBack(2);
	queueDl.PushToBack(3);
	queueDl.PeekFront();
	queueDl.PeekBack();
	queueDl.ListBtoF();
	queueDl.ListFtoB();
}

void Test2()
{
	QueueDL queueDl1;
	queueDl1.PushToFront(1);
	queueDl1.PushToFront(2);
	queueDl1.PushToFront(3);
	QueueDL queueDl2 = queueDl1;
	queueDl2.DeleteBack();
	queueDl2.DeleteFront();
	queueDl2.PushToBack(9);
	queueDl2.PushToBack(9);
	queueDl2.PushToFront(8);
	queueDl2.PushToFront(8);
	queueDl2.ListBtoF();
	queueDl2.ListFtoB();
	
}

void Test3()
{
	QueueDL queueDl1;
	QueueDL queueDl2;
	queueDl2.PushToFront(1);
	queueDl2.PushToFront(2);
	queueDl2.PushToFront(3);
	queueDl1 = queueDl2;
	queueDl1.ListBtoF();
	queueDl1.DeleteBack();
	queueDl1.DeleteBack();
	queueDl1.DeleteBack();
	queueDl1.DeleteBack();
	queueDl1.DeleteBack();
	queueDl2.DeleteFront();
	queueDl2.DeleteFront();
	queueDl2.DeleteFront();
	queueDl2.DeleteFront();
	queueDl1.PushToFront(0);
	queueDl1.DeleteFront();
	queueDl2.PushToBack(1);
	queueDl2.DeleteBack();
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