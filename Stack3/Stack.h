#pragma once
#include <iostream>

template <typename Type>
class Stack
{
public:
	Stack()
	{
		top_ = new Type[maxLength()];
		top_--;

		size_ = 0;
	}

	~Stack()
	{
		while (size_ != 0)
			pop();

		top_++;

		delete[] top_;
	}

	void push(Type item)
	{
		if (isStackFull())
			throw "Overflow";

		size_++;
		top_++;
		*top_ = item;
	}

	Type pop()
	{
		if (isStackEmpty())
			throw "Underflow";

		size_--;
		top_--;
		return *(top_ + 1);
	}

	bool isStackEmpty()
	{
		if (size_ == 0)
			return true;
		else
			return false;
	}

	bool isStackFull()
	{
		if (size_ == maxLength())
			return true;
		else
			return false;
	}


private:
	Type * top_;
	int size_;

	int maxLength() const
	{
		return 10;
	}
};


