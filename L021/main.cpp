#include "l021gui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	std::vector<UV>* v = new std::vector<UV>();
	v->push_back(UV(QString("lol21"), "rire fort", UVType::CS, 6, false, false));
	v->push_back(UV(QString("lol20"), "rire moins fort", UVType::CS, 6, false, false));
	std::shared_ptr<std::vector<UV>> p = std::shared_ptr<std::vector<UV>>(v);
	Ensemble<UV> eUV(p);

	auto n = eUV.Where([](const UV& i) {return i.get_code() == "lol21"; });
	while (auto i = n.nextItem()) ;

	QApplication a(argc, argv);
	L021GUI w;
	w.show();
	return a.exec();
}
