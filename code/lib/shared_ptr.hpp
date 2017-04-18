/*
 * shared_ptr.h - implement the shared_ptr template
 */
#ifndef TICKET_MAP_H
#define TICKET_MAP_H

namespace tic {
	template<typename T>
	class shared_ptr {
		size_t * cnt;
		T * ptr;
		void realse() {
			if( -- (*cnt) == 0 ) {
				delete ptr;
				delete cnt;
			}
		}
		public:
		shared_ptr( T * p ) {
			ptr = p;
			cnt = new int(1);
		}
		shared_ptr( const shared_ptr & other ) {
			if( &other == this ) throw copy_construct_from_self();
			realse();
			ptr = other.ptr;
			cnt = other.cnt;
			(*cnt)++;
		}
	};
}

#endif
