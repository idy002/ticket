#ifndef TICKET_UTILITY_HPP
#define TICKET_UTILITY_HPP

//#include <utility>

#include <istream>
#include <ostream>

namespace tic {
	//	utilities for general use
	template<class T1, class T2>
		class pair {
			public:
				T1 first;
				T2 second;
				constexpr pair() : first(), second() {}
				pair(const pair &other) = default;
				pair(pair &&other) = default;
				pair(const T1 &x, const T2 &y) : first(x), second(y) {}
				template<class U1, class U2>
					pair(U1 &&x, U2 &&y) : first(x), second(y) {}
				template<class U1, class U2>
					pair(const pair<U1, U2> &other) : first(other.first), second(other.second) {}
				template<class U1, class U2>
					pair(pair<U1, U2> &&other) : first(other.first), second(other.second) {}
		};

	template<class T> 
		T max( const T &a, const T &b ) {
			if( a < b ) return b;
			return a;
		}
	template<class T> 
		T min( const T &a, const T &b ) {
			if( a < b ) return b;
			return a;
		}
	template<class T>
		void swap( T &a, T &b ) {
			T c;
			c = a;
			a = b;
			b = c;
		}

	//	utilities for file input/output
	using std::istream;
	using std::ostream;

	void read( istream &in, int  & val ) {
		in.read( (char*) & val, sizeof(val) );
	}

	void write( ostream &out, int & val ) {
		out.write( (char*) & val, sizeof(val) );
	}

	template<class T>
		void write( ostream &out, T & val ) {
			val.write( out );
		}
	template<class T>
		void read( istream &in, T & val ) {
			val.read( in );
		}
}

#endif
