#ifndef TICKET_UTILITY_HPP
#define TICKET_UTILITY_HPP

//#include <utility>

#include <istream>
#include <ostream>
#include <string>
#include <sstream>
#include <QTime>
#include <QDate>
#include <QString>

namespace tic {
	//	utilities for file input/output
	using std::istream;
	using std::ostream;
    typedef QDate Date;
    typedef QTime Time;
    typedef QString string;

	template<class T> 
		T max( const T &a, const T &b ) {
			if( a < b ) return b;
			return a;
		}
	template<class T> 
		T min( const T &a, const T &b ) {
			if( a < b ) return a;
			return b;
		}
	template<class T>
		void swap( T &a, T &b ) {
			T c;
			c = a;
			a = b;
			b = c;
		}
    template<class T>
        void write( ostream &out, T & val ) {
            val.write( out );
        }
    template<class T>
        void read( istream &in, T & val ) {
            val.read( in );
        }
    template<class T>
    void read_default( istream & in, T & val ) {
        in.read( (char*) & val, sizeof(val) );
    }
    template<class T>
    void write_default( ostream & out, T & val ) {
        out.write( (char*) & val, sizeof(val) );
    }

    void read( istream &in, int & val );
    void write( ostream &out, int & val );
    void read( istream &in, double & val );
    void write( ostream &out, double & val );
    void read( istream &in, bool & val );
    void write( ostream &out, bool & val );
    void read( istream & in, string & str );
    void write( ostream & out, string & str );
    void read( istream &in, Date & date );
    void write( ostream &out, Date & date );
    void read( istream &in, Time & time );
    void write( ostream &out, Time & time );
    void read( istream &in, ushort &v );
    void write( ostream &out, ushort &v );
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
                pair &operator=( const pair &p ) {
                    this->first = p.first;
                    this->second = p.second;
                    return *this;
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
}

#endif
