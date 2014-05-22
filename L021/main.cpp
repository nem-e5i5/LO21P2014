#include "l021gui.h"
#include <QtWidgets>

int main(int argc, char *argv[])
{
	register_validator(Credit);

	UTProfiler* prf = UTProfiler::GetInstance();
	
	prf->UVrefByName("lol21") = UV(QString("lol21"), "rire fort", UVType::CS, 6, false, false);
	prf->UVrefByName("lol20") = UV(QString("lol20"), "haha", UVType::CS, 6, false, false);
	prf->UVrefByName("lol19") = UV(QString("lol19"), "hihi", UVType::CS, 6, false, false);
	
	Dossier& x = prf->MonDossier;
	Cursus y("counter strike");
	x.InscriptionUVByName("lol21");
	(*x.UVIterator()).set_status(UVStatus::A);
	y.addValidator(new CreditValidator(UVType::CS, 6));
	x.InscriptionCursusByName("counter strike");

	prf->CursusrefByName("counter strike") = y;

	prf->AppToBinFile("test.bin");

	UTProfiler::ResetInstance();
	prf = UTProfiler::GetInstance();

	prf->BinFileToApp("test.bin");

	QApplication a(argc, argv);
	L021GUI w;
	w.show();
	return a.exec();
}
