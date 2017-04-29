/*
 * account.hpp - implement Account class
 */
#ifndef TICKET_ACCOUNT_HPP
#define TICKET_ACCOUNT_HPP

#include <string>

#include "lib/map.hpp"
#include "lib/vector.hpp"
#include "lib/set.hpp"
#include "lib/utility.hpp"

using std::string;
using tic::map;
using tic::set;
using tic::vector;

class Account {
	string id;
	string name;
	string password;

	public:
	Account( string id, string name = string(), string password = string() ) {
		this->id = id;
		this->name = name;
		this->password = password;
	}
	string getPassword() {
		return password;
	}
	void setPassword( string password ) {
		this->password = password;
	}
	string getName() {
		return name;
	}
	void setName( string name ) {
		this->name = name;
	}
	bool operator<( const Pair &r, const Pair &s ) {
		return r.id < s.id;
	}
	void write( ostream & out ) {
		write( out, id );
		write( out, name );
		write( out, password );
	}
	void read( istream & in ) {
		read( in, id );
		read( in, name );
		read( in, password );
	}
};
class User : public Account {
	map<Ticket,int> bought;
	map<Ticket,int> refunded;
	
	public:
	User( string id, string name = string(), string password = string() )
		:Account(id,name,password){ }
	void addTicket( Ticket tc, int cnt ) {
		bought[tc] += cnt;
	}
	void refundTicket( const Ticket & ticket, int cnt ) {
		int & tcnt = bought[tc];
		refunded[tc] += cnt;
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
		User::write( out );
		write( out, bought );
		write( out, refunded );
	}
	void read( istream & in ) {
		User::read( in );
		read( in, bought );
		read( in, refunded );
	}
};
class Manager : public Account {
	public:
	Manager( string id, string name = string(), string password = string() )
		:Account(id,name,password){ }
	void write( ostream & out ) {
		User::write( out );
	}
	void read( istream & in ) {
		User::read( in );
	}
};

#endif
