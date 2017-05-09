/*
 * railway.hpp - implenment the main class of the ticket Project: Railway
 */
#ifndef TICKET_RAILWAY_HPP
#define TICKET_RAILWAY_HPP

#include "lib/lib.hpp"

#include "account.hpp"
#include "ticket.hpp"
#include "train.hpp"
#include "log.hpp"
#include <QFile>
#include <QTextStream>

namespace tic {

using std::stringstream;

const int DefaultPassengerNumber = 30;

class Railway {
	public:	//	TODO: change to private
		map<string,User> users;
		map<string,Manager> managers;
		map<pair<string,string>,vector<string>> table;
        map<string,string> fullname;
		map<string,Train> trains;
        set<Log> logs;

	public:	//	for normal user
		Railway() {}
        void queryTicket( Date date, string from, string to, string heads, vector<pair<Ticket,int>> &result ) {
            pair<string,string> range(from,to);
            if( table.count(range) == 0 ) return;
            vector<string> trainids = table[range];
            for( int t = 0; t < (int)trainids.size(); t++ ) {
                const string & id = trainids[t];
                if( heads.size() == 0 || heads.contains(id[0]) )
                    trains.at(id).queryTicket( date, from, to, result );
            }
        }

        int buyTicket( string userid, const Ticket & ticket, int cnt ) {
			string trainid = ticket.trainid;
            if( trains.count(trainid) == 0 ) return 0;
            int bcnt = trains.at(trainid).buyTicket( ticket, cnt );
            users[userid].addTicket( ticket, bcnt );
            return bcnt;
		}

        int buyTicket( string userid, Date date, string trainid, string from, string to, string type, int cnt ) {
            pair<Ticket,int> pr;
            bool suc = trains[fullname[trainid]].buyTicket( date, from, to, type, cnt, pr );
            if( suc ) {
                users[userid].addTicket( pr.first, pr.second );
                return pr.second;
            }
            return 0;
        }

        bool refundTicket( string userid, const Ticket & ticket, int cnt ) {
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
        bool isSelling( string trainid, Date date ) {
            trainid = fullname[trainid];
            if( trains.count(trainid) == 0 ) return false;
            Train & train = trains[trainid];
            return train.isSelling(date);
        }

        void startSell( string trainid, Date date ) {
            trainid = fullname[trainid];
            if( trains.count(trainid) == 0 ) return;
			Train & train = trains[trainid];
            train.startSell(date);
		}

        void stopSell( string trainid, Date date ) {
            trainid = fullname[trainid];
            if( trains.count(trainid) == 0 ) return;
			Train & train = trains[trainid];
            train.stopSell( date );
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
            vector<string> vec;
            QStringList qsl = s.split( ' ', QString::SkipEmptyParts );
            for( int i = 0; i < qsl.size(); i++ )
                vec.push_back( qsl[i] );
            return vec;
            /*
            stringstream ss(s);
            vector<string> vc;
            string token;
			while(ss >> token) {
                vc.push_back( token );
			}
			return vc;
            */
		}
        vector<string> readTokens( istream & in ) {
            std::string line;
			std::getline( in, line );
            return split(QString::fromStdString(line));
		}
        pair<Time,Time> transTime( string sl, string sr ) {
			Time tl, tr;
            tl = QTime::fromString( sl, "hh:mm" );
            tr = QTime::fromString( sr, "hh:mm" );
            if( !tl.isValid() && !tr.isValid() ) throw unexcepted_file_format();
            if( !tl.isValid() ) tl = tr;
            if( !tr.isValid() ) tr = tl;
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
        void addNameTable( QString str ) {
            if( fullname.count(str) ) return;
            QStringList list = str.split( "/" );
            for( int t = 0; t < list.size(); t++ )
                fullname[list[t]] = str;
            fullname[str] = str;
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
                addNameTable( vc[0] );
				vc = readTokens(fin);
				if( vc.size() <= 5 ) 
					throw unexcepted_file_format();
                map<string,Seat> & def_seats = train.seats[Date(0,0,0)].second;
				for( size_t i = 5; i < vc.size(); i++ ) {
					Seat seat;
					seat.type = vc[i];
                    def_seats[vc[i]] = seat;
				}
                vector<string> header = vc;
				while( true ) {
					vc = readTokens(fin);
					if( vc.size() != 0 ) {
						if( vc.size() != 5 + def_seats.size() ) 
							throw unexcepted_file_format();
						train.stations.push_back( vc[0] );
                        train.dists.push_back( vc[4].toInt() );
						pair<Time,Time> tpr = transTime( vc[2], vc[3] );
						train.arrive.push_back( tpr.first );
						train.leave.push_back( tpr.second );
						size_t sz = train.arrive.size();
						if( sz >= 2 && train.arrive[sz-1] < train.arrive[sz-2] )
                            train.arrive[sz-1] = train.arrive[sz-2].addSecs( 24 * 60 * 60 );
						if( sz >= 2 && train.leave[sz-1] < train.leave[sz-2] )
                            train.leave[sz-1] = train.leave[sz-2].addSecs( 24 * 60 * 60 );
						for( size_t i = 5; i < vc.size(); i++ ) {
                            def_seats[header[i]].prices.push_back( vc[i].mid(2).toDouble() );
                            def_seats[header[i]].remains.push_back( DefaultPassengerNumber );
						}
					} else {
                        train.seats[Date(2000,1,1)] = train.seats[Date(0,0,0)];
						trains[train.id] = train;
						break;
					}
				}
			}
			buildTable();
		}
		void readProcessFromFile( const char * filename ) {
            QFile file( filename );
            if( !file.open(QIODevice::ReadOnly | QIODevice::Text) )
                throw fail_to_open_file();
            QTextStream in(&file);
            while( !in.atEnd() ) {
                QString line = in.readLine();
                QStringList list = line.split( " ", QString::SkipEmptyParts );
                if( users.count(list[1]) == 0 ) {
                    User user;
                    user.id = list[1];
                    user.name = list[0];
                    user.password = "000000";
                    users[user.id] = user;
                }
                User &user = users[list[1]];
                if( list[2][0] == 'b' ) {	//	bought

                } else {	//	refunded

                }

            }
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
            tic::read( in, fullname );
			tic::read( in, trains );
			tic::read( in, logs );
		}
		void write( ostream & out ) {
			tic::write( out, users );
			tic::write( out, managers );
			tic::write( out, table );
            tic::write( out, fullname );
			tic::write( out, trains );
			tic::write( out, logs );
		}
};

}

using tic::Railway;
using tic::Ticket;
using tic::Train;
extern Railway railway;
extern string curUserid;

#endif

