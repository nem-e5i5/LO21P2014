#include <QtWidgets>
#include "L021/ValidatorDialog.h"

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	ValidatorDialog w(nullptr);
	w.show();
	return a.exec();
}
