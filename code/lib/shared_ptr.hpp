/*
 * shared_ptr.h - implement the shared_ptr template
 */
#ifndef TICKET_MAP_HPP
#define TICKET_MAP_HPP
#include "exceptions.hpp"

namespace tic {
	template<typename T>
	class shared_ptr {
		long * cnt;
		T * ptr;
		void release() {
			if( ptr != 0 ) {
				--(*cnt);
				if( *cnt == 0 ) {
					delete ptr;
					delete cnt;
				}
				ptr = 0;
				cnt = 0;
			}
		}
		public:
		shared_ptr() {
			ptr = 0;
			cnt = 0;
		}
		shared_ptr( T * p ) { 
			ptr = p;
			cnt = new long(1);
		}
		shared_ptr( const shared_ptr & other ) {
			if( other.ptr == 0 ) {
				ptr = 0;
				cnt = 0;
			} else {
				ptr = other.ptr;
				cnt = other.cnt;
				++(*cnt);
			}
		}
		shared_ptr & operator=( const shared_ptr & other ) {
			if( this == &other ) return *this;
			release();
			if( other.ptr == 0 ) {
				ptr = 0;
				cnt = 0;
			} else {
				ptr = other.ptr;
				cnt = other.cnt;
				++(*cnt);
			}
		}
		~shared_ptr() {
			release();
		}
		void reset() {
			release();
		}
		void reset( T * p ) {
			release();
			ptr = p;
			cnt = new long(1);
		}
		T * get() const {
			return ptr;
		}
		long use_count() const {
			if( cnt == 0 )
				return 0;
			else
				return *cnt;
		}
		T & operator[]( int index ) const {
			if( ptr == 0 ) throw dereference_empty_pointer();
			return *(ptr + index);
		}
		T & operator*() const {
			if( ptr == 0 ) throw dereference_empty_pointer();
			return *ptr;
		}
		T * operator->() const {
			if( ptr == 0 ) throw dereference_empty_pointer();
			return ptr;
		}
		operator bool() const { 
			return ptr != 0;
		}
		bool operator==( const shared_ptr &rhs ) const {
			return (ptr == rhs.ptr);
		}
		bool operator!=( const shared_ptr &rhs ) const {
			return (ptr != rhs.ptr);
		}
		bool operator<( const shared_ptr &rhs ) const {
			return (ptr < rhs.ptr);
		}
		bool operator>( const shared_ptr &rhs ) const {
			return (ptr > rhs.ptr);
		}
		bool operator<=( const shared_ptr &rhs ) const {
			return (ptr <= rhs.ptr);
		}
		bool operator>=( const shared_ptr &rhs ) const {
			return (ptr >= rhs.ptr);
		}
	};
}

#endif
