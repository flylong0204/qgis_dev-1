#include "qgisapp.h"
#include <QtGui/QApplication>

#include <qgsapplication.h>

int main(int argc, char *argv[])
{
	//QApplication a(argc, argv);
	QgsApplication myApp(argc, argv, true);
	QgsApplication::setPrefixPath("D:/Program Files (x86)/QGIS 2.18", true);
	QgsApplication::initQgis();
	myApp.connect(&myApp, SIGNAL(lastWindowClosed()), &myApp, SLOT(quit()));

	QgisApp *w = new QgisApp();
	w->show();

	int retval = myApp.exec();
	delete w;
	return retval;

	//return a.exec();
}
