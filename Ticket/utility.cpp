#include "lib/utility.hpp"
#include <QDate>
#include <QTime>
#include <QChar>
#include <QDebug>

        extern int cccnt;
namespace tic {
    void read( istream &in, int & val ) { read_default(in,val); }
    void write( ostream &out, int & val ) { write_default(out,val); }
    void read( istream &in, double & val ) { read_default(in,val); }
    void write( ostream &out, double & val ) { write_default(out,val); }
    void read( istream &in, bool & val ) { read_default(in,val); }
    void write( ostream &out, bool & val ) { write_default(out,val); }
    void read( istream &in, uchar &v ) { read_default(in,v); }
    void write( ostream &out, uchar &v ) { write_default(out,v); }
    void read( istream &in, ushort &v ) { read_default(in,v); }
    void write( ostream &out, ushort &v ) { write_default(out,v); }
    void read( istream &in, size_t & val ) { read_default(in,val); }
    void write( ostream &out, size_t & val ) { write_default(out,val); }
//    void read( istream &in, void * &v ) { read_default(in,v); }
//   void write( ostream &out, void * &v ) { write_default(out,v); }
    void read( istream & in, string & str ) {
        int len;
        read( in, len );
        str.clear();
        for( int i = 0; i < len; i++ ) {
            ushort code;
            read( in, code );
            str.push_back(QChar(code));
        }
    }
    void write( ostream & out, string & str ) {
        int len = str.size();
        write( out, len );
        for( int i = 0; i < len; i++ ) {
            ushort code = str[i].unicode();
            write( out, code );
        }
    }
    void write( ostream &out, Date & date ) {
        int year = date.year();
        int month = date.month();
        int day = date.day();
        write( out, year );
        write( out, month );
        write( out, day );
    }
    void read( istream &in, Date & date ) {
        int year, month, day;
        read( in, year );
        read( in, month );
        read( in, day );
        date = Date(year,month,day);
    }

    void read( istream &in, Time & time ) {
        int hour, minute, second, msec;
        read( in, hour );
        read( in, minute );
        read( in, second );
        read( in, msec );
        time = Time(hour,minute,second,msec);
    }

    void write( ostream &out, Time & time ) {
        int hour = time.hour();
        int minute = time.minute();
        int second = time.second();
        int msec = time.msec();
        write( out, hour );
        write( out, minute );
        write( out, second );
        write( out, msec );
    }
}
