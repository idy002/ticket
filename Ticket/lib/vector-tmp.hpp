/*
 * vector.h - implement the vector template
 */
#ifndef TICKET_MAP_HPP
#define TICKET_MAP_HPP

#include <iostream>
#include <istream>
#include <ostream>
#include <cstdio>
#include <string>
#include "exceptions.hpp"

template <class T>
class vector
{
private:
	T *elem;
	int vsize;
	int capacity;
	
	void DoubleSpace()
	{
		T *tmp = elem;
		capacity *= 2;
		elem = new T [capacity];
		for(int i = 0; i < vsize; i++)
			elem[i] = tmp[i];
		delete [] tmp;
	}
	
public:
	vector()
	{
		elem = new T [4];
		vsize = 0;
		capacity = 4;	
	}
	
	vector(const vector <T> &obj)
	{
		elem = new T [obj -> capacity];
		vsize = obj -> vsize;
		for(int i = 0; i < vsize; i++)
		{
			elem[i] = obj -> elem[i];
		}
		capacity = obj -> capacity;
	}
	
	//operator[]
	T &operator [](int index) const
	{	
		if(index < 0 || index >= vsize)
			throw tic::index_out_of_bound();
		return elem[index];	
	}
	
	//operator=
	vector &operator =(const vector <T> &obj)
	{
		if(this == obj)
			return *this;
		elem = new T [obj -> capacity];
		vsize = obj -> vsize;
		for(int i = 0; i < vsize; i++)
		{
			elem[i] = obj -> elem[i];
		}
		capacity = obj -> capacity;
		return *this;
	}
	
	//front
	T front() const
	{
		if(vsize)
			return elem[0];
		throw tic::container_is_empty();
	}	
	
	//size
	int size() const
	{
		return vsize;	
	}
		
	//empty
	bool empty() const
	{
		if(vsize == 0)
			return 1;
		return 0;
	}
	
	//clear
	void clear()
	{
		vsize = 0;	
	}
	
	//push_back
	void push_back(T op)
	{
		elem[vsize++] = op;
		if(vsize == capacity)
			DoubleSpace();
	}
	
	//pop_back
	T pop_back()
	{
		if(vsize)
			return elem[--vsize];
		throw tic::container_is_empty();
	}
	
	//write
	void write(std::ostream &os)
	{
		tic::write(os, capacity);
		tic::write(os, vsize);
		for(int i = 0; i < vsize; i++)
		{
			tic::write(os, elem[i]);	
		}	
	}
	
	//read
	void read(std::istream &is)
	{
		tic::read(is, capacity);
		tic::read(is, vsize);
		elem = new T [capacity];
		for(int i = 0; i < vsize; i++)
		{
			tic::read(is, elem[i]);	
		}	
	}
	
	//~vector
	~vector()
	{
		if(elem)
			delete [] elem;	
	}
	
	//EXTRA
	void display() const
	{
		printf("===\ncapacity = %d\nvsize = %d\n", capacity, vsize);
		for(int i = 0; i < vsize; i++)
			std::cout << elem[i] << " ";
		printf("\n");	
	}
};

#endif
