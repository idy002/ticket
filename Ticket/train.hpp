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

	void write( ostream & out ) {
		tic::write( out, type );
		tic::write( out, prices );
		tic::write( out, remains );
	}
	void read( istream & in ) {
		tic::read( in, type );
		tic::read( in, prices );
		tic::read( in, remains );
	}
};
struct Train {
	string id;
	vector<string> stations;
	vector<int> dists;
	vector<Time> arrive, leave;
    map<Date,pair<bool,map<string,Seat>>> seats;

    inline bool isZero( double x ) {
        return x > -1e-8 && x < 1e-8;
    }

	public:
	void init() { 
		id.clear();
		stations.clear();
		dists.clear();
		arrive.clear();
		leave.clear();
		seats.clear();
	}

	bool operator<( const Train & rhs ) const {
		return id < rhs.id;
	}

    void startSell( Date date ) {
        if( !seats.count(date) )
            seats[date] = seats[Date(0,0,0)];
        seats[date].first = true;
    }

    void stopSell( Date date ) {
        if( seats.count(date) )
            seats[date].first = false;
    }

    bool isSelling( Date date ) {
        if( seats.count(date) == 0 ) return false;
        else return seats[date].first;
    }

    void queryTicket( Date date, string from, string to, vector<pair<Ticket,int>> & result ) {
        if( !isSelling(date) ) return;
        map<string,Seat> &vseat = seats[date].second;
		int tfrom, tto;
        for( int t = 0; t < (int)stations.size(); t++ ) {
            if( stations[t] == from ) tfrom = t;
            if( stations[t] == to ) tto = t;
        }
        for( auto it = vseat.begin(); it != vseat.end(); ++it ) {
            Seat &seat = it->second;
            if( tto && isZero(seat.prices[tto]) ) continue;
            if( tfrom && isZero(seat.prices[tfrom]) ) continue;

			int available = seat.remains[tfrom+1];
			for( int tt = tfrom + 1; tt <= tto; tt++ ) 
				available = min( available, seat.remains[tt] );
			Ticket ticket;
			ticket.date = date;
			ticket.trainid = id;
			ticket.from = from;
			ticket.to = to;
			ticket.type = seat.type;
			ticket.leave = leave[tfrom];
			ticket.arrive = arrive[tto];
			ticket.dist = dists[tto] - dists[tfrom];
			ticket.price = seat.prices[tto] - seat.prices[tfrom];
			result.push_back( pair<Ticket,int>( ticket, available ) );
		}
	}

    bool buyTicket( Date date, string from, string to, string type, int cnt, pair<Ticket,int> & result ) {
        if( !isSelling(date) ) return false;
        if( !seats[date].second.count(type) ) return false;

		int tfrom, tto;
		for( int t = 0; t < (int)stations.size(); t++ ) {
			if( stations[t] == from ) tfrom = t;
			if( stations[t] == to ) tto = t;
		}

        Seat &seat = seats[date].second[type];
        if( tfrom && isZero(seat.prices[tfrom]) ) return false;
        if( tto && isZero(seat.prices[tto] )) return false;

        int available = seat.remains[tfrom+1];
        for( int tt = tfrom + 1; tt <= tto; tt++ )
            available = min( available, seat.remains[tt] );
        available = min( available, cnt );
        for( int tt = tfrom + 1; tt <= tto; tt++ )
            seat.remains[tt] -= available;
        Ticket & ticket = result.first;
        ticket.trainid = id;
        ticket.date = date;
        ticket.from = from;
        ticket.to = to;
        ticket.type = seat.type;
        ticket.leave = leave[tfrom];
        ticket.arrive = arrive[tto];
        ticket.dist = dists[tto] - dists[tfrom];
        ticket.price = seat.prices[tto] - seat.prices[tfrom];
        result.second = available;
        return true;
	}

    int buyTicket( const Ticket & ticket, int cnt ) {
        if( !isSelling(ticket.date) ) return 0;

        int tfrom, tto;
		for( int t = 0; t < (int)stations.size(); t++ ) {
			if( ticket.from == stations[t] ) tfrom = t;
			if( ticket.to == stations[t] ) tto = t;
		}

        Seat &seat = seats[ticket.date].second[ticket.type];
        int available = seat.remains[tfrom+1];
        for( int tt = tfrom + 1; tt <= tto; tt++ )
            available = min( available, seat.remains[tt] );
        int ret = min( available, cnt );
        for( int tt = tfrom + 1; tt <= tto; tt++ )
            seat.remains[tt] -= ret;
        return ret;
	}

	void refundTicket( const Ticket & ticket, int cnt ) {
        int tfrom, tto;
        for( int t = 0; t < (int)stations.size(); t++ ) {
            if( ticket.from == stations[t] ) tfrom = t;
            if( ticket.to == stations[t] ) tto = t;
        }

        Seat &seat = seats[ticket.date].second[ticket.type];
        for( int tt = tfrom + 1; tt <= tto; tt++ )
            seat.remains[tt] += cnt;
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
