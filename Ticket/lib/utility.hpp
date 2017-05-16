#ifndef TICKET_UTILITY_HPP
#define TICKET_UTILITY_HPP

//#include <utility>

#include <istream>
#include <fstream>
#include <ostream>
#include <string>
#include <sstream>
#include <QTime>
#include <QDate>
#include <QString>
#include "exceptions.hpp"

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
      //  in >> val;
    }
    template<class T>
    void write_default( ostream & out, T & val ) {
     //   out << val << " ";
        out.write( (char*) & val, sizeof(val) );
    }
    template<class T>
    void load( const char * filename, T & val ) {
        std::ifstream in;
        in.open( filename, std::ios_base::in | std::ios_base::binary );
        if( in.fail() )
            throw tic::fail_to_open_file();
        read( in, val );
        in.close();
    }
    template<class T>
    void save( const char * filename, T & val ) {
        std::ofstream out;
        out.open( filename, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc );
        if( out.fail() )
            throw tic::fail_to_open_file();
        write( out, val );
        out.close();
    }

    void read( istream &in, int & val );
    void write( ostream &out, int & val );
    void read( istream &in, size_t & val );
    void write( ostream &out, size_t & val );
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
    void read( istream &in, uchar &v );
    void write( ostream &out, uchar &v );
    void read( istream &in, ushort &v );
    void write( ostream &out, ushort &v );
    void read( istream &in, void * &v );
    void write( ostream &out, void * &v );
    void read( istream &in, QDateTime &dt );
    void write( ostream &out, QDateTime &dt );
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

       QDateTime transDateTime( QDate curdate, QDateTime deftime );
}

#endif
