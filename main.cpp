#include <QApplication>
#include "mainwindow.h"

using namespace std;

/** @function main */
int main( int argc, char* argv[] )
{
	QApplication app(argc, argv);
    MainWindow window;
    window.show();
	return app.exec();
}
