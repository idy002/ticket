#ifndef TICKET_UTILITY_HPP
#define TICKET_UTILITY_HPP

//#include <utility>

#include <istream>
#include <ostream>
#include <string>
#include <sstream>

namespace tic {
	//	utilities for file input/output
	using std::istream;
	using std::ostream;
	using std::string;

	template<class T>
	void read_default( istream & in, T & val ) {
		in.read( (char*) & val, sizeof(val) );
	}
	template<class T>
	void write_default( ostream & out, T & val ) {
		out.write( (char*) & val, sizeof(val) );
	}
	void read( istream &in, int & val ) { read_default(in,val); }
	void write( ostream &out, int & val ) { write_default(out,val); }
	void read( istream &in, double & val ) { read_default(in,val); }
	void write( ostream &out, double & val ) { write_default(out,val); }
	void read( istream &in, bool & val ) { read_default(in,val); }
	void write( ostream &out, bool & val ) { write_default(out,val); }
	void read( istream & in, string & str ) {
		size_t len;
		in.read( (char*) & len, sizeof(len) );
		str.clear();
		while(len--) {
			char ch;
			in.read( & ch, sizeof(ch) );
			str.push_back(ch);
		}
	}
	void write( ostream & out, string & str ) {
		size_t len = str.size();
		out.write( (char*) & len, sizeof(len) );
		for( size_t i = 0; i < len; i++ )
			out.write( & str[i], sizeof(str[i]) );
	}
	template<class T>
		void write( ostream &out, T & val ) {
			val.write( out );
		}
	template<class T>
		void read( istream &in, T & val ) {
			val.read( in );
		}

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
				void write( ostream & out ) {
					tic::write( out, first );
					tic::write( out, second );
				}
				void read( istream & in ) {
					tic::read( in, first );
					tic::read( in, second );
				}
				bool operator<( const pair & rhs ) const {
					if( first < rhs.first ) return true;
					if( first > rhs.first ) return false;
					return second < rhs.second;
				}
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

}

#endif
