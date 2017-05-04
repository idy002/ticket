/*
 * railway.hpp - implenment the main class of the ticket Project: Railway
 */
#ifndef TICKET_RAILWAY_HPP
#define TICKET_RAILWAY_HPP

#include "lib/lib.hpp"

#include "account.hpp"
#include "ticket.hpp"
#include "train.hpp"

namespace tic {

using std::string;
using tic::vector;
using tic::set;
using tic::map;
using std::ifstream;
using std::ofstream;
using std::stringstream;

const int DefaultPassengerNumber = 30;

class Railway {
	public:	//	TODO: change to private
		map<string,User> users;
		map<string,Manager> managers;
		map<pair<string,string>,vector<string>> table;
		map<string,Train> trains;
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
				trains.at(id).queryTicket( date, from, to, result );
			}
			return result;
		}
		void buyTicket( const Ticket & ticket, int cnt ) {
			string trainid = ticket.trainid;
			trains.at(trainid).buyTicket( ticket, cnt );
		}
		void refundTicket( string userid, const Ticket & ticket, int cnt ) {
			string trainid = ticket.trainid;
			users.at(userid).refundTicket(ticket,cnt);
			trains.at(trainid).refundTicket(ticket,cnt);
		}
		bool addUser( string userid, string name, string password ) {
			if( users.count(userid) ) return false;
			users[userid] = User( userid, name, password );
			return true;
		}
		bool modifyUserName( string userid, string newName ) {
			if( users.count(userid) == 0 ) return false;
			users[userid].modifyName( newName );
//			users[userid].name = newname;
			return true;
		}
		bool modifyUserPassword( string userid, string newPassword ) {
			if( users.count(userid) == 0 ) return false;
//			users[userid].password = newPassoword;
			users[userid].modifyPassword( newPassword );
			return true;
		}

	public:	//	for manager user
		bool addTrain( const Train & train ) {
			if( trains.count(train.id) ) return false;
			trains[train.id] = train;
		}
		bool deleteTrain( string trainid ) {
			if( trains.count(trainid) == 0 ) return false;
			trains.erase(trains.find(trainid));
			return true;
		}
		bool stopTrain( string trainid ) {
			if( trains.count(trainid) == 0 ) return false;
			trains[trainid].hasStop = true;
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
			vector<Seat> & seats = train.seats[date];
			bool canStop = true;
			for( int t = 0; t < (int)seats.size(); t++ ) 
				if( seats[t].sellout > 0 ) canStop = false;
			if( !canStop ) return false;
			for( int t = 0; t < (int)seats.size(); t++ ) 
				seats[t].hasStop = true;
			return true;
		}

	public: //	for both normal users and manager users
		vector<pair<Ticket,int>> queryUserBoughtTicket( string userid ) {
			vector<pair<Ticket,int>> result;
			if( users.count(userid) == 0 ) return result;
			User & user = users[userid];
			user.queryBoughtTickets( result );
			return result;
		}
		vector<pair<Ticket,int>> queryUserRefundedTicket( string userid ) {
			vector<pair<Ticket,int>> result;
			if( users.count(userid) == 0 ) return result;
			User & user = users[userid];
			user.queryRefundedTickets( result );
			return result;
		}

	public: //	input and output
		//	tools to process string
		vector<string> split( const string &s ) {
			stringstream ss(s);
			vector<string> vc;
			string token;
			while(ss >> token) {
				vc.push_back( token );
			}
			return vc;
		}
		vector<string> readTokens( istream & in ) {
			string line;
			std::getline( in, line );
			return split(line);
		}
		pair<Time,Time> transTime( string sl, string sr ) {
			Time tl, tr;
			if( isdigit(sl[0]) ) tl = Time( stoi(sl), stoi(sl.substr(3)), 0 );
			if( isdigit(sr[0]) ) tr = Time( stoi(sr), stoi(sr.substr(0)), 0 );
			if( !isdigit(sl[0]) ) tl = tr;
			if( !isdigit(sr[0]) ) tr = tl;
			return pair<Time,Time>(tl,tr);
		}
		void buildTable() {
			table.clear();
			for( map<string,Train>::iterator it = trains.begin();
					it != trains.end(); ++it ) {
				vector<string> &stations = it->second.stations;
				for( int i = 0; i < (int)stations.size(); i++ )
					for( int j = i + 1; j < (int)stations.size(); j++ ) {
						table[pair<string,string>(stations[i],stations[j])].push_back(it->first);
					}
			}
		}
		void readTrainFromFile( const char * filename ) {
			std::ifstream fin;
			fin.open( filename, std::ifstream::in );
			if( fin.fail() ) throw fail_to_open_file();
			Train train;
			vector<string> vc;
			while( true ) {
				vc = readTokens(fin);
				if( vc.size() == 0 ) break;
				if( vc.size() != 1 ) 
					throw unexcepted_file_format();
				train.init();
				train.id = vc[0];
				train.hasStop = false;
				vc = readTokens(fin);
				if( vc.size() <= 5 ) 
					throw unexcepted_file_format();
				vector<Seat> & def_seats = train.seats[Date(0,0,0)];
				for( size_t i = 5; i < vc.size(); i++ ) {
					Seat seat;
					seat.type = vc[i];
					def_seats.push_back(seat);
				}
				while( true ) {
					vc = readTokens(fin);
					if( vc.size() != 0 ) {
						if( vc.size() != 5 + def_seats.size() ) 
							throw unexcepted_file_format();
						train.stations.push_back( vc[0] );
						train.dists.push_back( stoi(vc[4]) );
						pair<Time,Time> tpr = transTime( vc[2], vc[3] );
						train.arrive.push_back( tpr.first );
						train.leave.push_back( tpr.second );
						size_t sz = train.arrive.size();
						if( sz >= 2 && train.arrive[sz-1] < train.arrive[sz-2] )
							train.arrive[sz-1] = train.arrive[sz-2] + Time(24,0,0);
						if( sz >= 2 && train.leave[sz-1] < train.leave[sz-2] )
							train.leave[sz-1] = train.leave[sz-2] + Time(24,0,0);
						for( size_t i = 5; i < vc.size(); i++ ) {
							def_seats[i-5].prices.push_back( stod(vc[i].substr(2)) );
							if( def_seats[i-5].prices.size() >= 2 
									&& def_seats[i-5].prices.back() == 0.0 )
								train.hasStop = true;
							def_seats[i-5].remains.push_back( DefaultPassengerNumber );
						}
					} else {
						trains[train.id] = train;
						break;
					}
				}
			}
			buildTable();
		}
		void readProcessFromFile( const char * filename ) {
		}
		void print() {
			printf( "number of trains: %d\n", (int)trains.size() );
			set<string> st;
			for( map<string,Train>::iterator it = trains.begin(); it != trains.end(); ++it ) {
//				printf( "id:%s  stations: %d  Running: %3s\n", 
//						it->first.c_str(),
//						(int)it->second.stations.size(),
//						it->second.hasStop ? "NO" : "YES" );
				vector<string> &vc = it->second.stations;
				for( int i = 0; i < (int)vc.size(); i++ )
					st.insert(vc[i]);
			}
			printf( "total stations: %d\n", (int)st.size() );
		}
		void read( istream & in ) {
			tic::read( in, users );
			tic::read( in, managers );
			tic::read( in, table );
			tic::read( in, trains );
			tic::read( in, logs );
		}
		void write( ostream & out ) {
			tic::write( out, users );
			tic::write( out, managers );
			tic::write( out, table );
			tic::write( out, trains );
			tic::write( out, logs );
		}
};

}

#endif

