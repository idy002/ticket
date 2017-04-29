/*
 * log.hpp - implement Log struct
 */
#ifndef TICKET_LOG_HPP
#define TICKET_LOG_HPP

#include <string>

#include "lib/date.hpp"

struct Log {
	Date date;
	Time time;
	string message;
	bool operator<( const Log & rhs ) const {
		if( date != rhs.date ) return date < rhs.date;
		return time < rhs.time;
		return false;
	}
}

#endif
