#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>

class Queue
{
public:
	void Enqueue(const int value)
	{
		if (back < maxLength - 1)
		{
			back++;
			array[back] = value;
		}
		else
			std::cout << "Array is full!\n";
	}
	int Dequeue()
	{
		int retVal = -1;
		if (IsEmpty())
			std::cout << "The queue is empty!!\n";
		else
		{
			retVal = array[front];
			array[front] = 0;
			std::cout << "The dequeued value is: " << retVal << std::endl;
			back--;
			SortArray(front);
		}
		return retVal;
	}
	int PeekFront() const
	{
		int retVal = -1;
		if (IsEmpty())
		{
			std::cout << "The queue is empty!!\n";
		}
		else
		{
			retVal = array[front];
			std::cout << "There front value is: " << array[front] << std::endl;
		}
		return retVal;
	}
	int PeekBack() const
	{
		int retVal = -1;
		if (IsEmpty())
		{
			std::cout << "The queue is empty!!\n";
		}
		else
		{
			retVal = array[back];
			std::cout << "There back value is: " << array[back] << std::endl;
		}
		return retVal;
	}
	bool IsEmpty() const
	{
		return back < 0;
	}
private:
	void SortArray(int index)
	{
		if (index + 1 < maxLength)
		{
			array[index] = array[index + 1];
			SortArray(index + 1);
		}
	}
	static constexpr int maxLength = 5;
	int array[maxLength] = { 0 };
	int temp[maxLength];
	static constexpr int front = 0;
	int back = -1;
};

void Test1()
{
	Queue queue;
	queue.Enqueue(1);
	queue.Enqueue(2);
	queue.Enqueue(3);
	queue.Enqueue(4);
	queue.Enqueue(5);
	queue.Enqueue(6);
	queue.PeekFront();
	queue.PeekBack();
	queue.Dequeue();
	queue.Dequeue();
	queue.Dequeue();
	queue.Dequeue();
	queue.Dequeue();
	queue.Dequeue();
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

	_CrtDumpMemoryLeaks();
	getchar();

	return 0;
}