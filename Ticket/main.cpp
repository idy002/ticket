#include "mainwindow.hpp"
#include "railway.hpp"
#include "logindialog.h"
#include "userdialog.h"
#include "managerdialog.h"
#include <QMessageBox>
#include <QApplication>
#include <fstream>

Railway railway;
string curUserid;

void load( const char * filename ) {
    ifstream in;
    in.open( filename );
    if( in.fail() )
        throw tic::fail_to_open_file();
    railway.read( in );
    in.close();
}
void save( const char * filename ) {
    ofstream out;
    out.open( filename );
    if( out.fail() )
        throw tic::fail_to_open_file();
    railway.write( out );
    out.close();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginDialog loginDialog;

//    railway.users[string("idy002")].password = "dingyaoyao";
//    railway.managers[string("idy003")].password = "dingyaoyao";
//    railway.readTrainFromFile( "D:/trains.out" );
    load( "D:/railway.data" );

    while(true) {
        if( loginDialog.exec() == QDialog::Accepted ) {
            if( railway.users.count(curUserid) ) {
                UserDialog userDialog;
                if( userDialog.exec() != QDialog::Accepted ) {
                    break;
                }
            } else {
                ManagerDialog managerDialog;
                if( managerDialog.exec() != QDialog::Accepted ) {
                    break;
                }
            }
        } else {
            break;
        }
    }

    save( "D:/railway.data" );
    return 0;
//    return a.exec();
}
