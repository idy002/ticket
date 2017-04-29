/*
 * railway.hpp - implenment the main class of the ticket Project: Railway
 */
#ifndef TICKET_RAILWAY_HPP
#define TICKET_RAILWAY_HPP

#include <string>

#include "lib/set.hpp"
#include "lib/map.hpp"
#include "lib/vector.hpp"

#include "account.hpp"
#include "ticket.hpp"
#include "train.hpp"

namespace tic {

using std::string;
using tic::vector;
using tic::set;
using tic::map;

class Railway {
	private:
		map<string,User> users;
		map<string,Manager> managers;
		map<pair<string,string>,vector<string>> table;
		map<string,Train> trans;
		set<Log> logs;

	public:	//	for normal user
		Railway() {}
		vector<pair<Ticket,int>> queryTicket( Date date, string from, string to ) {
			vector<pair<Ticket,int>> result;
			pair<string,string> range(from,to);
			if( table.count(range) == 0 ) return result;
			vector<string> trainids = table[range];
			for( int t = 0; t < (int)trainids.size(); t++ ) {
				const string & id = trainids[t];
				trans.at(id).queryTicket( date, from, to, result );
			}
			return result;
		}
		void buyTicket( const Ticket & ticket, int cnt ) {
			string trainid = ticket.trainid;
			trans.at(trainid).buyTicket( ticket, cnt );
		}
		void refundTicket( string userid, const Ticket & ticket, int cnt ) {
			string trainid = ticket.trainid;
			users.at(userid).refundTicket(ticket,cnt);
			trans.at(tranid).refundTicket(ticket,cnt);
		}
		bool addUser( string userid, string name, string password ) {
			if( users.count(userid) ) return false;
			users[userid] = User( userid, name, password );
			return true;
		}
		bool modifyUserName( string userid, string newName ) {
			if( users.count(userid) == 0 ) return false;
			users[userid].name = newname;
			return true;
		}
		bool modifyUserPassword( string userid, string newPassword ) {
			if( users.count(userid) == 0 ) return false;
			users[userid].password = newPassoword;
			return true;
		}

	public:	//	for manager user
		bool addTrain( const Train & train ) {
			if( trans.count(train.id) ) return false;
			trans[train.id] = train;
		}
		bool modifyTrain( const Train & newtrain ) {
			if( trans.count(newtrain.id) == 0 ) return false;
			Train & train = trans[newtrain.id];
			if( train.sellout > 0 ) return false;
			train = newtrain;
			train.total = train.sellout = 0;
			return true;
		}
		bool deleteTrain( string trainid ) {
			if( trans.count(newtrain.id) == 0 ) return false;
			Train & train = trans[newtrain.id];
			if( train.sellout > 0 ) return false;
			trans.erase(trainid);
			return true;
		}
		bool startSell( string trainid, Date date ) {
			if( trains.count(trainid) == 0 ) return false;
			Train & train = trains[trainid];
			if( train.seats.count(date) ) return false;
			train.seats[date] = train.seats[Date(0,0,0)];
			return true;
		}
		bool stopSell( string trainid, Date date ) {
			if( trains.count(trainid) == 0 ) return false;
			Train & train = trains[trainid];
			if( train.seats.count(date) == 0 ) return false;
			train.seats[date].hasStop = true;
			return true;
		}

	public: //	for both normal users and manager users
		vector<Ticket,int> queryUserBoughtTicket( string userid ) {
			vector<Ticket,int> result;
			if( users.count(userid) == 0 ) return result;
			User & user = users[userid];
			user.queryBoughtTickets( result );
			return result;
		}
		vector<Ticket,int> queryUserRefundedTicket( string userid ) {
			vector<Ticket,int> result;
			if( users.count(userid) == 0 ) return result;
			User & user = users[userid];
			user.queryRefundedTickets( result );
			return result;
		}
	public: //	input and output
		void readFromFile( const char * filename ) {
		}
		void writeToFile( const char * filename ) {
		}
};

}

#endif


