/*
 * train.hpp - implement Seat struct and Train class
 */
#ifndef TICKET_TRAIN_HPP
#define TICKET_TRAIN_HPP

struct Seat {
	string type;
	vector<double> prices;
	vector<int> remains;

	void write( ostream & out ) {
		write( out, type );
		write( out, prices );
		write( out, remains );
	}
	void read( istream & in ) {
		read( in, type );
		read( in, prices );
		read( in, remains );
	}
};
class Train {
	string id
	vector<string> stations;
	vector<int> dists;
	vector<Time> arrive, leave;
	map<Time,vector<Seat>> seats;

	public:
	bool operator<( const Train & rhs ) const {
		return id < rhs.id;
	}
	vector<pair<Ticket,int>> queryTicket( Time time, string from, string to ) {
	}
	pair<Ticket,int> buyTicket( Time time, string from, string to, string type, int cnt ) {
	}
	void refundTicket( const Ticket & ticket, int cnt ) {
	}
	void write( ostream & out ) {
	}
	void read( istream & in ) {
	}
};

#endif
