/*
 * shared_ptr.h - implement the shared_ptr template
 */
#ifndef TICKET_MAP_H
#define TICKET_MAP_H

template<typename T>
class shared_ptr {
	size_t * count;
	T * pointer;
	public:
	shared_ptr( T * ptr = 0 ):ptr(ptr),count(new size_t(0)) {
		if( ptr )
			*count = 1;
		else
			*count = 0;
	}
};

#endif
