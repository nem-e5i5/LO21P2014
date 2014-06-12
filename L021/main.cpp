#include "l021gui.h"
#include <QtWidgets>

int main(int argc, char *argv[])
{
	register_validator(Credit);
	register_validator(CreditIn);
	register_validator(XUVIn);
	register_validator(XSemestreALetranger);
	register_validator(Switch);
	register_validator(XUVAvecYIn);

	UTProfiler* prf = UTProfiler::GetInstance();

	QApplication a(argc, argv);
	L021GUI w;
	w.show();
	return a.exec();
}
