#include "lib/lib.hpp"
#include "ticket.hpp"
#include "account.hpp"
#include "train.hpp"
#include "log.hpp"
#include "railway.hpp"

using tic::Train;
using std::fstream;

tic::Railway railway;

int main() {
	fstream fs;
	fs.open( "tic.data" );
	railway.readTrainFromFile( "../data/trains.out" );
	railway.print();
	write( fs, railway );
}


