/*
 * train.hpp - implement Seat struct and Train class
 */
#ifndef TICKET_TRAIN_HPP
#define TICKET_TRAIN_HPP

#include "lib/lib.hpp"

#include "ticket.hpp"

namespace tic {
struct Seat {
	string type;
	vector<double> prices;
	vector<int> remains;
	bool hasStop;

	void write( ostream & out ) {
		tic::write( out, type );
		tic::write( out, prices );
		tic::write( out, remains );
		tic::write( out, hasStop );
	}
	void read( istream & in ) {
		tic::read( in, type );
		tic::read( in, prices );
		tic::read( in, remains );
		tic::read( in, hasStop );
	}
};
class Train {
	string id;
	vector<string> stations;
	vector<int> dists;
	vector<Time> arrive, leave;
	map<Date,vector<Seat>> seats;
	int total, sellout;

	public:
	bool operator<( const Train & rhs ) const {
		return id < rhs.id;
	}
	void queryTicket( Date date, string from, string to, vector<pair<Ticket,int>> & result ) {
		if( seats.count(date) == 0 ) return;
		vector<Seat> &vseat = seats[date];
		int tfrom, tto;
		for( int t = 0; t < (int)stations.size(); t++ ) {
			if( stations[t] == from ) tfrom = t;
			if( stations[t] == to ) tto = t;
		}
		if( tfrom >= tto ) return;
		for( int t = 0; t < (int)vseat.size(); t++ ) {
			Seat &seat = vseat[t];
			int available = seat.remains[tfrom+1];
			for( int tt = tfrom + 1; tt <= tto; tt++ ) 
				available = min( available, seat.remains[tt] );
			if( available > 0 ) {
				Ticket ticket;
				ticket.date = date;
				ticket.trainid = id;
				ticket.from = from;
				ticket.to = to;
				ticket.type = seat.type;
				ticket.during = arrive[tto] - leave[tfrom];
				ticket.dist = dists[tto] - dists[tfrom];
				ticket.price = seat.prices[tto] - seat.prices[tfrom];
				if( seat.hasStop ) available = 0;
				result.push_back( pair<Ticket,int>( ticket, available ) );
			}
		}
	}
	void buyTicket( const Ticket & ticket, int cnt ) {
		int tfrom, tto;
		for( int t = 0; t < (int)stations.size(); t++ ) {
			if( ticket.from == stations[t] ) tfrom = t;
			if( ticket.to == stations[t] ) tto = t;
		}
		if( tfrom >= tto ) return;
		vector<Seat> &vseat = seats.at( ticket.date );
		for( int t = 0; t < (int)vseat.size(); t++ ) {
			if( vseat[t].type == ticket.type ) {
				Seat &seat = vseat[t];
				int available = seat.remains[tfrom+1];
				for( int tt = tfrom + 1; tt <= tto; tt++ )
					available = min( available, seat.remains[tt] );
				int ret = min( available, cnt );
				for( int tt = tfrom + 1; tt <= tto; tt++ )
					seat.remains[tt] -= ret;
				return;
			}
		}
	}
	void refundTicket( const Ticket & ticket, int cnt ) {
		int tfrom, tto;
		for( int t = 0; t < (int)stations.size(); t++ ) {
			if( ticket.from == stations[t] ) tfrom = t;
			if( ticket.to == stations[t] ) tto = t;
		}
		if( tfrom >= tto ) return;
		vector<Seat> &vseat = seats.at( ticket.date );
		for( int t = 0; t < (int)vseat.size(); t++ ) {
			if( vseat[t].type == ticket.type ) {
				Seat &seat = vseat[t];
				for( int tt = tfrom + 1; tt <= tto; tt++ )
					seat.remains[tt] += cnt;
				return;
			}
		}

	}
	void write( ostream & out ) {
		tic::write( out, id );
		tic::write( out, stations );
		tic::write( out, dists );
		tic::write( out, arrive );
		tic::write( out, leave );
		tic::write( out, seats );
	}
	void read( istream & in ) {
		tic::read( in, id );
		tic::read( in, stations );
		tic::read( in, dists );
		tic::read( in, arrive );
		tic::read( in, leave );
		tic::read( in, seats );
	}
};

}

#endif
