#include "l021gui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	L021GUI w;
	w.show();
	return a.exec();
}
