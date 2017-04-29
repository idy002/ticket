/*
 * train.hpp - implement Seat struct and Train class
 */
#ifndef TICKET_TRAIN_HPP
#define TICKET_TRAIN_HPP

#include <string>

#include "lib/map.hpp"
#include "lib/vector.hpp"
#include "lib/set.hpp"
#include "lib/utility.hpp"

using std::string;
using tic::map;
using tic::set;
using tic::vector;

struct Seat {
	string type;
	vector<double> prices;
	vector<int> remains;
	bool hasStop;

	void write( ostream & out ) {
		write( out, type );
		write( out, prices );
		write( out, remains );
		write( out, hasStop );
	}
	void read( istream & in ) {
		read( in, type );
		read( in, prices );
		read( in, remains );
		read( in, hasStop );
	}
};
class Train {
	string id
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
			if( ticket.to == station[t] ) tto = t;
		}
		if( tfrom >= tto ) return 0;
		vector<Seat> &vseat = seats.at( ticket.date );
		for( int t = 0; t < (int)vseat.size(); t++ ) {
			if( vseat[t].type == ticket.type ) {
				Seat &seat = vseat[t];
				int available = seat.remains[tfrom+1];
				for( int tt = tfrom + 1; tt <= tto; tt++ )
					available = min( available, seat.remains[tt] );
				int ret = min( available, cnt );
				for( int tt = tfrom + 1; tt <= tto; tt++ )
					seat.remain[tt] -= ret;
				return;
			}
		}
	}
	void refundTicket( const Ticket & ticket, int cnt ) {
		int tfrom, tto;
		for( int t = 0; t < (int)stations.size(); t++ ) {
			if( ticket.from == stations[t] ) tfrom = t;
			if( ticket.to == station[t] ) tto = t;
		}
		if( tfrom >= tto ) return;
		vector<Seat> &vseat = seats.at( ticket.date );
		for( int t = 0; t < (int)vseat.size(); t++ ) {
			if( vseat[t].type == ticket.type ) {
				Seat &seat = vseat[t];
				for( int tt = tfrom + 1; tt <= tto; tt++ )
					seat.remain[tt] += cnt;
				return;
			}
		}

	}
	void write( ostream & out ) {
		write( out, id );
		write( out, stations );
		write( out, dists );
		write( out, arrive );
		write( out, leave );
		write( out, seats );
	}
	void read( istream & in ) {
		read( in, id );
		read( in, stations );
		read( in, dists );
		read( in, arrive );
		read( in, leave );
		read( in, seats );
	}
};

#endif
