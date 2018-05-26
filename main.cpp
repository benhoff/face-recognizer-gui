#include <QApplication>
#include "gui/mainwindow.h"

/** @function main */
int main( int argc, char* argv[] )
{
	QApplication app(argc, argv);
    MainWindow window;
    window.show();
	return app.exec();
}
