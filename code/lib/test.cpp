#include <cstdio>
#include "map.hpp"


int main() {
	int n = 100;
	tic::map<int,int> mp;
	for( int i = 1; i <= n; i++ )
		mp[i] = i * i;
	for( tic::map<int,int>::iterator it = mp.begin(); it != mp.end(); ++it )
		printf( "%d %d\n", it->first, it->second );

}

