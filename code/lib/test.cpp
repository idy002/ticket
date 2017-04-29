#include <bits/stdc++.h>
#include "map.hpp"

using tic::map;


map<int,int> read( const char *filename ) {
	std::ifstream in( filename );
	map<int,int> mp;
	read( in, mp );
	in.close();
	return mp;
}
void write( const char *filename, map<int,int> &mp ) {
	std::ofstream out( filename );
	write( out, mp );
	out.close();
}
int main() {
	int n = 10000;
	tic::map<int,int> mp;
	for( int i = 0; i < n; i++ )
		mp[i] = i * i;
	write( "mpdata", mp );
	map<int,int> mmp = read("mpdata");
	for( map<int,int>::iterator it = mmp.begin(); it != mmp.end();
			++it )
		printf( "%d %d\n", it->first, it->second );
}

