/*
 * shared_ptr.h - implement the shared_ptr template
 */
#ifndef TICKET_MAP_H
#define TICKET_MAP_H

#include "exception.hpp"

template<typename T>
class shared_ptr {
	size_t * count;
	T * pointer;
	void release() {
		if( --(*count) == 0 ) {
			delete pointer;
			delete count;
		}
	}
	public:
	shared_ptr( T * p = 0 ):pointer(p),count(new size_t(1)) { }
	shared_ptr( const shared_ptr & rhs ) {
		if( this == &rhs ) return;
		count = rhs.count;
		pointer = rhs.pointer;
		(*count)++;
	}
	shared_ptr & operator=( const shared_ptr & rhs ) {
		if( this == &rhs ) return *this;
		release();
		pointer = rhs.pointer;
		count = rhs.count;
		(*count)++;
		return *this;
	}
	T & operator*() {
		if( pointer ) return *pointer;
		throw bad_pointer();
	}
	T * operator->() {
		if( pointer ) return pointer;
		throw bad_pointer();
	}
	~shared_ptr() {
		release();
	}
};

#endif
