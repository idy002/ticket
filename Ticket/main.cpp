#include "mainwindow.hpp"
#include "railway.hpp"
#include "logindialog.h"
#include "userdialog.h"
#include "managerdialog.h"
#include "welcomedialog.h"
#include <QMessageBox>
#include <QApplication>
#include <QSplashScreen>
#include <fstream>
#include <QDebug>
#include <QThread>
#include <new>

Railway railway;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*
    QString data_path = "D:/TicketData/BigSet/";
    QString train_file = data_path + "trains.out";
    QString process_file = data_path + "process.out";
    QString data_file = data_path + "railway.data";

    railway.readTrainFromFile( train_file );
    railway.readProcessFromFile( process_file );

    save( data_file.toStdString().c_str(), railway );
    return 0;
    */

    QPixmap pixmap( ":/myimages/images/timg.png" );
    QSplashScreen splash(pixmap);
    splash.show();
    splash.showMessage( "加载数据中..." );
    a.processEvents();
    LoginDialog loginDialog;
    loginDialog.show();
    splash.finish( &loginDialog );

    return a.exec();
}
