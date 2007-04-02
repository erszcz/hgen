#include <QApplication>
#include <QObject>

#include "HGenMain.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	HGenMain main;
	
	main.show();
	return app.exec();
}
