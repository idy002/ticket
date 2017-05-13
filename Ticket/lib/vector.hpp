/*
 * vector.h - implement the vector template
 */
#ifndef TICKET_VECTOR_HPP
#define TICKET_VECTOR_HPP

#include <vector>
#include <istream>
#include <ostream>
#include <QDebug>

#include "utility.hpp"

namespace tic {
	using std::istream;
	using std::ostream;
	template<class T>
	class vector {
		std::vector<T> vc;
		public:
		vector(){}
		vector( const vector<T> & vec ):vc(vec.vc) { }
		T & operator[]( size_t i ) {
			return vc[i];
		}
		vector & operator=( const vector<T> & vec ) {
			if( &vec == this ) return *this;
			vc = vec.vc;
			return *this;
		}
		size_t size() const {
			return vc.size();
		}
		void resize( size_t sz ) {
			vc.resize(sz);
		}
		bool empty() const {
			return vc.empty();
		}
		void clear() {
			vc.clear();
		}
		T & back() {
			return vc.back();
		}
		T & front() {
			return vc.front();
		}
		void push_back( const T & val ) {
			vc.push_back(val);
		}
		void pop_back() {
			vc.pop_back();
		}
		void write( ostream & out ) {
			size_t len = vc.size();
            tic::write( out, len );
            for( size_t i = 0; i < len; i++ ) {
				tic::write( out, vc[i] );
            }
		}
		void read( istream & in ) {
			size_t len;
            tic::read( in, len );
			vc.resize( len );
            for( size_t i = 0; i < len; i++ ) {
				tic::read( in, vc[i] );
            }
		}
	};
}

#endif
