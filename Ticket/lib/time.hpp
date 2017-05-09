/*
 * time.hpp - implement the Time and Date struct, which store and manage time
 */
#ifndef TICKET_TIME_HPP
#define TICKET_TIME_HPP

#include <istream>
#include <ostream>
#include <QTime>
#include <QDate>

namespace tic {

typedef QTime Time;
typedef QDate Date;

/*
struct Time {
	int hour;		//	[0,24)
	int minite;		//	[0,60)
	int second;		//	[0,60)

	Time() {
		hour = minite = second = 0;
	}
	Time( int hour, int minite, int second )
		:hour(hour),minite(minite),second(second){}

	//	return (*this) - rhs, if it's negative, then plus 1 day
	Time operator-( const Time & rhs ) const {
		Time seq;
		seq.second = (hour - rhs.hour) * 60 * 60 
			+ (minite - rhs.minite) * 60
			+ second - rhs.second;
		if( seq.second < 0 ) seq.second += 24 * 60 * 60;
		seq.minite = seq.second / 60;
		seq.second %= 60;
		seq.hour = seq.minite / 60;
		seq.minite %= 60;
		return seq;
	}
	Time operator+( const Time &rhs ) const {
		Time ans;
		ans.hour = hour + rhs.hour;
		ans.minite = minite + rhs.minite;
		ans.second = second + rhs.second;
		ans.minite += ans.second / 60;
		ans.second %= 60;
		ans.hour += ans.minite / 60;
		ans.minite %= 60;
		return ans;
	}
	bool operator<( const Time &rhs ) const {
		if( hour != rhs.hour ) return hour < rhs.hour;
		if( minite != rhs.minite ) return minite < rhs.minite;
		return second < rhs.second;
	}
	void write( ostream & out ) {
		tic::write( out, hour );
		tic::write( out, minite );
		tic::write( out, second );
	}
	void read( istream & in ) {
		tic::read( in, hour );
		tic::read( in, minite );
		tic::read( in, second );
	}
};

struct Date {
	int year;		//	[1000,9999]
	int month;		//	[1,12]
	int day;		//	[1,28~31]

	Date(){
		year = month = day = 0;
	}
	Date( int year, int month, int day )
		:year(year),month(month),day(day){}
	bool operator<( const Date & rhs ) const {
		if( year != rhs.year ) return year < rhs.year;
		if( month != rhs.month ) return month < rhs.month;
		return day < rhs.day;
	}
	bool operator==( const Date & rhs ) const {
		return year == rhs.year && month == rhs.month && day == rhs.day;
	}
	bool operator!=( const Date & rhs ) const {
		return !(*this == rhs);
	}
	void write( ostream & out ) {
		tic::write( out, year );
		tic::write( out, month );
		tic::write( out, day );
	}
	void read( istream & in ) {
		tic::read( in, year );
		tic::read( in, month );
		tic::read( in, day );
	}
};
*/

}

#endif

