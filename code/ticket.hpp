/*
 * ticket.hpp - implement Ticket structure 
 */
#ifndef TICKET_TICKET_HPP
#define TICKET_TICKET_HPP

struct Ticket {
	string from, to;
	string type;
	int dist;
	int during;
	double price;

	bool operator<( const Ticket & rhs ) const {
		if( from != rhs.from ) return from < rhs.from;
		if( to != rhs.to ) return to < rhs.to;
		if( type != rhs.type ) return type < rhs.type;
		return false;
	}
	bool operator==( const Ticket & rhs ) const {
		return (from == rhs.from && to == rhs.to && type == rhs.type);
	}
	void write( ostream & out ) {
		write( out, from );
		write( out, to );
		write( out, type );
		write( out, dist );
		write( out, during );
		write( out, price );
	}
	void read( istream & in ) {
		read( in, from );
		read( in, to );
		read( in, type );
		read( in, dist );
		read( in, during );
		read( in, price );
	}
};


#endif
