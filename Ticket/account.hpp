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

class Account {
    public:
	string id;
	string name;
	string password;

	public:
	Account( string id = string(), string name = string(), string password = string() ) {
		this->id = id;
		this->name = name;
		this->password = password;
	}
	string getPassword() {
		return password;
	}
	void modifyPassword( string password ) {
		this->password = password;
	}
	string getName() {
		return name;
	}
	void modifyName( string name ) {
		this->name = name;
	}
	void write( ostream & out ) {
		tic::write( out, id );
		tic::write( out, name );
		tic::write( out, password );
	}
	void read( istream & in ) {
		tic::read( in, id );
		tic::read( in, name );
		tic::read( in, password );
	}
};
class User : public Account {
	map<Ticket,int> bought;
	map<Ticket,int> refunded;
	
	public:
	User( string id = string(), string name = string(), string password = string() ) :Account(id,name,password){ }
	void addTicket( Ticket tc, int cnt ) {
		bought[tc] += cnt;
	}
	void refundTicket( const Ticket & ticket, int cnt ) {
		int & tcnt = bought[ticket];
		refunded[ticket] += cnt;
		tcnt -= cnt;
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
		Account::write( out );
		tic::write( out, bought );
		tic::write( out, refunded );
	}
	void read( istream & in ) {
		Account::read( in );
		tic::read( in, bought );
		tic::read( in, refunded );
	}
};
class Manager : public Account {
	public:
	Manager( string id = string(), string name = string(), string password = string() ) :Account(id,name,password){ }
	void write( ostream & out ) {
		Account::write( out );
	}
	void read( istream & in ) {
		Account::read( in );
	}
};

}

#endif
