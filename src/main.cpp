#include <QApplication>
#include <QDebug>
#include "gui.hpp"
#include "Other.hpp"
#include "UV.hpp"

/*
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	gui w;
	w.show();

	return a.exec();
}
*/

int main() {
	UVList l;
	UV uv1=UV("LO21", "POO", TM, 6, false, true);
	UV uv2=UV("NF16", "algo", CS, 6, true, true);
	l.add_UV(&uv1);
	l.add_UV(&uv2);
	for (UVList::Iterator i = l.get_iterator(); i.end()==false; i.next()) {
		qDebug() << i.get_current()->get_type() << endl;
	}
	return 0;
}
