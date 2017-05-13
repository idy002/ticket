/*
 * account.hpp - implement Account class
 */
#ifndef TICKET_ACCOUNT_HPP
#define TICKET_ACCOUNT_HPP

#include "lib/lib.hpp"
#include "ticket.hpp"

using tic::write;
using tic::read;
namespace tic {

struct User {
    public:
	string id;
	string name;
	string password;
    bool isManager;
    map<Ticket,int> bought;
    map<Ticket,int> refunded;

	public:
    User( string id = string(), string name = string(), string password = string(), bool isManager = false )
        :id(id),name(name),password(password),isManager(isManager),bought(),refunded() {}
    void addTicket( Ticket tc, int cnt ) {
        bought[tc] += cnt;
    }
    int refundTicket( const Ticket & ticket, int cnt ) {
        int tcnt = bought[ticket];
        int rcnt = min( tcnt, cnt );
        refunded[ticket] += rcnt;
        bought[ticket] -= rcnt;
        if( tcnt == rcnt ) bought.erase( bought.find(ticket) );
        return rcnt;
    }
    void queryBoughtTickets( vector<pair<Ticket,int>> & result ) {
        for( map<Ticket,int>::iterator it = bought.begin();
                it != bought.end(); ++it )
            result.push_back( *it );
    }
    void queryRefundedTickets( vector<pair<Ticket,int>> & result ) {
        for( map<Ticket,int>::iterator it = refunded.begin();
                it != refunded.end(); ++it )
            result.push_back( *it );
    }
    void write( ostream & out ) {
		tic::write( out, id );
		tic::write( out, name );
		tic::write( out, password );
        tic::write( out, isManager );
        tic::write( out, bought );
        tic::write( out, refunded );
    }
	void read( istream & in ) {
		tic::read( in, id );
		tic::read( in, name );
		tic::read( in, password );
        tic::read( in, isManager );
        tic::read( in, bought );
        tic::read( in, refunded );
    }
};

}

#endif
