/*
 * log.hpp - implement Log struct
 */
#ifndef TICKET_LOG_HPP
#define TICKET_LOG_HPP

#include <string>

#include "lib/time.hpp"

namespace tic {

struct Log {
	Date date;
	Time time;
    string userid;
	string message;
    Log(){}
    Log( Date date, Time time, string userid, string message ):date(date),time(time),userid(userid),message(message) {}
	bool operator<( const Log & rhs ) const {
		if( date != rhs.date ) return date < rhs.date;
        if( time != rhs.time ) return time < rhs.time;
        return userid < rhs.userid;
	}
	void write( ostream & out ) {
		tic::write( out, date );
		tic::write( out, time );
        tic::write( out, userid );
        tic::write( out, message );
	}
	void read( istream & in ) {
		tic::read( in, date );
		tic::read( in, time );
        tic::read( in, userid );
        tic::read( in, message );
	}
};

}

#endif
