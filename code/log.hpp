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
	string message;
	bool operator<( const Log & rhs ) const {
		if( date != rhs.date ) return date < rhs.date;
		return time < rhs.time;
		return false;
	}
	void write( ostream & out ) {
		tic::write( out, date );
		tic::write( out, time );
		tic::write( out, message );
	}
	void read( istream & in ) {
		tic::read( in, date );
		tic::read( in, time );
		tic::read( in, message );
	}
};

}

#endif
