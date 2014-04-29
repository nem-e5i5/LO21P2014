#include "l021gui.h"
#include <QtWidgets>

int main(int argc, char *argv[])
{
	std::vector<UV>* v = new std::vector<UV>();
	v->push_back(UV(QString("lol21"), "rire fort", UVType::CS, 6, false, false));
	v->push_back(UV(QString("lol20"), "rire moins fort", UVType::CS, 6, false, false));
<<<<<<< HEAD
	v->push_back(UV(QString("lol19"), "rire encore moins fort", UVType::CS, 6, false, false));
	
	auto va = Where<UV>(v->begin(), v->end(), [](const UV& x) { return x.get_code().startsWith("lol2"); });
	auto vb = Where<UV>(va, va.getEnd(), [](const UV& x) { return x.get_code().endsWith("0"); });
	auto vc = Select<UV, QString>(vb, vb.getEnd(), [](const UV& x) {return x.get_titre(); });
	auto vd = Union<UV>(va, va.getEnd(), vb, vb.getEnd(), [](const UV& a, const UV& b) {return a.get_code() == b.get_code(); });
	auto ve = Intersect<UV>(v->begin(), v->end(), va, va.getEnd(), [](const UV& a, const UV& b) {return a.get_code() == b.get_code(); });
	auto v2 = toVector<UV>(ve, ve.getEnd());
	v2.at(0);
=======
	std::shared_ptr<std::vector<UV>> p = std::shared_ptr<std::vector<UV>>(v);

	Ensemble<UV> eUV(p);

	auto n = eUV.Where([](const UV& i) {return i.get_code() == "lol21"; });
	while (auto i = n.nextItem()) ;

>>>>>>> 2fac733231fb6b3156c23b26cc4aef6911c850fc
	QApplication a(argc, argv);
	L021GUI w;
	w.show();
	return a.exec();
}
