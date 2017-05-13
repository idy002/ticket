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
		map<pair<string,string>,vector<string>> table;
		map<string,Train> trains;
        set<Log> logs;

        string curUserid;

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
            logs.insert( Log(QDate::currentDate(),QTime::currentTime(),curUserid,
                             QString( "查询 %1 从 %2 到 %3 的 [%4] 类型列车的车票")
                             .arg(date.toString()).arg(from).arg(to).arg(heads)
                             )
                         );
        }

        int buyTicket( string userid, const Ticket & ticket, int cnt ) {
			string trainid = ticket.trainid;
            if( trains.count(trainid) == 0 ) return 0;
            int bcnt = trains.at(trainid).buyTicket( ticket, cnt );
            users[userid].addTicket( ticket, bcnt );
            logs.insert( Log(QDate::currentDate(),QTime::currentTime(),curUserid,
                             QString( "购买 %1 %2 从 %3 到 %4 的 %5 类型车票 %6 张")
                             .arg(ticket.date.toString()).arg(ticket.trainid).arg(ticket.from).arg(ticket.to).arg(ticket.type).arg(bcnt)
                             )
                         );
            return bcnt;
		}

        int buyTicket( string userid, Date date, string trainid, string from, string to, string type, int cnt ) {
            pair<Ticket,int> pr;
            bool suc = trains[trainid].buyTicket( date, from, to, type, cnt, pr );
            if( suc ) {
                users[userid].addTicket( pr.first, pr.second );
                return pr.second;
                logs.insert( Log(QDate::currentDate(),QTime::currentTime(),curUserid,
                                 QString( "购买 %1 %2 从 %3 到 %4 的 %5 类型车票 %6 张")
                                 .arg(date.toString()).arg(trainid).arg(from).arg(to).arg(type).arg(pr.second)
                                 )
                );
            }
            return 0;
        }

        int refundTicket( string userid, const Ticket & ticket, int cnt ) {
			string trainid = ticket.trainid;
            int rcnt = users.at(userid).refundTicket(ticket,cnt);
            trains.at(trainid).refundTicket(ticket,rcnt);
            logs.insert( Log(QDate::currentDate(),QTime::currentTime(),curUserid,
                             QString( "退 %1 %2 从 %3 到 %4 的 %5 类型车票 %6 张")
                             .arg(ticket.date.toString()).arg(ticket.trainid).arg(ticket.from).arg(ticket.to).arg(ticket.type).arg(rcnt)
                             )
            );
            return rcnt;
		}

        bool addUser( string userid, string name, string password, bool applyManager ) {
			if( users.count(userid) ) return false;
            users[userid] = User( userid, name, password, applyManager );
            logs.insert( Log(QDate::currentDate(),QTime::currentTime(),curUserid,
                             QString( "用户 %1 注册成功，姓名：%2 密码：%3 是否申请管理员权限：[%4]")
                             .arg(userid).arg(name).arg(password).arg(applyManager ? "YES" : "NO" )
                             )
            );
            return true;
		}

        void modifyUserName( string userid, string name ) {
            if( users.count(userid) ) {
                QString old = users[userid].name;
                users[userid].name = name;
                logs.insert( Log(QDate::currentDate(),QTime::currentTime(),curUserid,
                                 QString( "修改 %1 用户姓名 %2 -> 3" )
                                 .arg(userid).arg(old).arg(name)
                                 )
                );

            }
        }
        void modifyUserPassword( string userid, string password ) {
            if( users.count(userid) ) {
                QString old = users[userid].password;
                users[userid].password = password;
                logs.insert( Log(QDate::currentDate(),QTime::currentTime(),curUserid,
                                 QString( "修改 %1 用户密码 %2 -> 3" )
                                 .arg(userid).arg(old).arg(password)
                                 )
                );
            }
        }

	public:	//	for manager user
		bool addTrain( const Train & train ) {
			if( trains.count(train.id) ) return false;
			trains[train.id] = train;
            logs.insert( Log(QDate::currentDate(),QTime::currentTime(),curUserid,
                             QString( "添加列车 %1，共 %2 站，座位类型有 %3 种")
                             .arg(train.id).arg(train.stations.size()).arg(train.seats[Date(1,1,1)].second.size())
                             )
            );
            return true;
		}
		bool deleteTrain( string trainid ) {
			if( trains.count(trainid) == 0 ) return false;
            Train &train = trains[trainid];
            logs.insert( Log(QDate::currentDate(),QTime::currentTime(),curUserid,
                             QString( "删除列车 %1，共 %2 站，座位类型有 %3 种")
                             .arg(train.id).arg(train.stations.size()).arg(train.seats[Date(1,1,1)].second.size())
                             )
            );
            trains.erase(trains.find(trainid));
            return true;
		}
        bool isSelling( string trainid, Date date ) {
            if( trains.count(trainid) == 0 ) return false;
            Train & train = trains[trainid];
            return train.isSelling(date);
        }

        void startSell( string trainid, Date date ) {
            if( trains.count(trainid) == 0 ) return;
			Train & train = trains[trainid];
            train.startSell(date);
            logs.insert( Log(QDate::currentDate(),QTime::currentTime(),curUserid,
                             QString( "开始发售 %1 %2 的车票")
                             .arg(trainid).arg(date.toString())
                             )
            );
        }

        void delSell( string trainid, Date date ) {
            if( trains.count(trainid) == 0 ) return;
            Train & train = trains[trainid];
            train.delSell(date);
            logs.insert( Log(QDate::currentDate(),QTime::currentTime(),curUserid,
                             QString( "删除发售 %1 %2 的车票的记录")
                             .arg(trainid).arg(date.toString())
                             )
            );
        }

        void stopSell( string trainid, Date date ) {
            if( trains.count(trainid) == 0 ) return;
			Train & train = trains[trainid];
            train.stopSell( date );
            logs.insert( Log(QDate::currentDate(),QTime::currentTime(),curUserid,
                             QString( "停止发售 %1 %2 的车票")
                             .arg(trainid).arg(date.toString())
                             )
            );
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
        void readTrainFromFile( QString filename ) {
			std::ifstream fin;
            fin.open( filename.toStdString().c_str(), std::ifstream::in );
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
				vc = readTokens(fin);
				if( vc.size() <= 5 ) 
					throw unexcepted_file_format();
                map<string,Seat> & def_seats = train.seats[Date(1,1,1)].second;
                train.seats[Date(1,1,1)].first = true;
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
                            def_seats[header[i]].prices.push_back( vc[i].mid(1).toDouble() );
                            def_seats[header[i]].remains.push_back( DefaultPassengerNumber );
						}
					} else {
						trains[train.id] = train;
						break;
					}
				}
			}
			buildTable();
		}
        void readProcessFromFile( QString filename ) {
            //	0	 	1		2		3	4	5		6	7		8	9 10  11  12  13
            //	刘鸟慧 067117193 bought 11 一等座 tickets of D2337 from 潮汕 to 汕尾 in 2017-4-16
            QFile file( filename.toStdString().c_str() );
            if( !file.open(QIODevice::ReadOnly | QIODevice::Text) )
                throw fail_to_open_file();
            QTextStream in(&file);
            in.setCodec( "UTF-8" );
            while( !in.atEnd() ) {
                QString line = in.readLine();
                QStringList list = line.split( " ", QString::SkipEmptyParts );
                if( list.size() != 14 ) {
                    if( list.size() == 0 )
                        continue;
                    else
                        throw unexcepted_file_format();
                }

                if( users.count(list[1]) == 0 ) {
                    User user;
                    user.id = list[1];
                    user.name = list[0];
                    user.password = "000000";
                    users[user.id] = user;
                }
                string userid = list[1];
                string trainid = list[7];
                string type = list[4];
                string from = list[9];
                string to = list[11];
                Date date = QDate::fromString( list[13], "yyyy-M-d" );
                int cnt = list[3].toInt();
                if( trains.count(trainid) == 0 ) continue;
                if( list[2][0] == 'b' ) {	//	bought
                    startSell( trainid, date );
                    buyTicket( userid, date, trainid, from, to, type, cnt );
                } else {	//	refunded
                    vector<pair<Ticket,int>> result;
                    users[userid].queryBoughtTickets( result );
                    for( int t = 0; t < (int)result.size(); t++ ) {
                        Ticket &tk = result[t].first;
                        if( tk.date == date && tk.trainid == trainid && tk.from == from && tk.to == to && tk.type == type )
                            refundTicket( userid, tk, min(result[t].second, cnt) );
                    }
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
			tic::read( in, table );
			tic::read( in, trains );
			tic::read( in, logs );
		}
		void write( ostream & out ) {
			tic::write( out, users );
			tic::write( out, table );
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

