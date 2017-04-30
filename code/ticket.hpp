/*
 * ticket.hpp - implement Ticket structure 
 */
#ifndef TICKET_TICKET_HPP
#define TICKET_TICKET_HPP

#include "lib/lib.hpp"

namespace tic {

struct Ticket {
	string trainid;
	string from, to;
	string type;
	Date date;
	Time during;
	int dist;
	double price;

	bool operator<( const Ticket & rhs ) const {
		if( date != rhs.date ) return date < rhs.date;
		if( from != rhs.from ) return from < rhs.from;
		if( to != rhs.to ) return to < rhs.to;
		if( type != rhs.type ) return type < rhs.type;
		return false;
	}
	bool operator==( const Ticket & rhs ) const {
		return (date == rhs.date && from == rhs.from && to == rhs.to && type == rhs.type);
	}
	void write( ostream & out ) {
		tic::write( out, date );
		tic::write( out, trainid );
		tic::write( out, from );
		tic::write( out, to );
		tic::write( out, type );
		tic::write( out, dist );
		tic::write( out, during );
		tic::write( out, price );
	}
	void read( istream & in ) {
		tic::read( in, date );
		tic::read( in, trainid );
		tic::read( in, from );
		tic::read( in, to );
		tic::read( in, type );
		tic::read( in, dist );
		tic::read( in, during );
		tic::read( in, price );
	}
};

}

#endif
