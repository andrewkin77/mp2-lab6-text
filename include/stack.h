#pragma once
template <class T>
class TStack
{
	T* arr;
	int size;
	int num;
public:

	TStack(int s = 100)
	{
		arr = new T[s];
		size = s;
		num = -1;
	}

	~TStack() 
	{
		delete[] arr;
	}

	TStack(const TStack<T>& a) 
	{
		size = a.size;
		num = a.num;
		arr = new T[size];
		for (int i = 0; i <= num; i++) 
		{
			arr[i] = a.arr[i];
		}
	}

	TStack<T>& operator=(const TStack<T>& a) 
	{
		if(size != a.size) 
		{
			size = a.size;
			delete[] arr;
			arr = new T[size];
		}
		num = a.num;
		for (int i = 0; i < size; i++)
			arr[i] = a.arr[i];
		return *this;
	}

	bool IsEmpty() 
	{
		return num == -1;
	}

	bool IsFull() 
	{
		return num == size - 1;
	}

	void push(T a) 
	{
		if (IsFull()) 
			throw - 1;

		arr[++num] = a;
	}

	T pop() 
	{
		if (IsEmpty()) 
			throw - 1;

		return arr[num--];
	}

	T top() 
	{
		if (IsEmpty()) 
			throw - 1;

		return arr[num];
	}

	void clear() 
	{
		num = -1;
	}
};