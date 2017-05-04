#include <bits/stdc++.h>


class Type {
	public:
		void f() {
			std::ifstream fin;
			fin.open( "a.txt" );
		}
		void readTrainFromFile( const char * filename ) {
			std::ifstream fin;
			fin.open( filename, std::ifstream::in );
		}
};


int main() {
	Type a;
}
