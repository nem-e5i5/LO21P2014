#include "DossierEtCursus.h"

void Dossier::Setmeta(QString n, QString v) 
{
	if (v == "") Metadata.erase(n);
	Metadata[n] = v;
}

QString Dossier::Getmeta(QString n)
{
	return Metadata[n];
}

IdentityIterator<UVEncours, vector<UVEncours>::iterator> Dossier::UVIterator()
{
	return IdentityIterator<UVEncours, vector<UVEncours>::iterator>(UVsuivi.begin(), UVsuivi.end());
}

SelectIterator<QString, const Cursus&, vector<QString>::iterator> Dossier::CursusIterator()
{
	return Select<QString, const Cursus&>(Cursussuivi.begin(), Cursussuivi.end(),
		[](QString x) { return UTProfiler::GetInstance()->CursusrefByName(x); });
}

int Dossier::getNbEquivalences(UVType t)
{
	return Equivalences[t];
}

void Dossier::setNbEquivalences(UVType t, int value = 0)
{
	Equivalences[t] = value;
}

bool Dossier::validerDossier() 
{ 
	for (auto x = CursusIterator(); !x.ended(); ++x) 
		if (!((*x).Validate(*this))) return false; 
	return true; }

void Dossier::InscriptionUV(const UV& x)
{
	Dossier::InscriptionUVByName(x.get_code());
}
void Dossier::InscriptionCursus(const Cursus& x)
{
	InscriptionCursusByName(x.getName());
}

void Dossier::InscriptionUVByName(QString x)
{
	if (!UTProfiler::GetInstance()->UVExists(x)) throw;
	UVsuivi.push_back(UVEncours(x, UVStatus::EC));
}
void Dossier::InscriptionCursusByName(QString x)
{
	if (!UTProfiler::GetInstance()->CursusExists(x)) throw;
	Cursussuivi.push_back(x);
}

Dossier::Dossier()
{
	for (int i = 0; i < UVType::size; ++i) Equivalences[i] = 0;
}


Dossier::~Dossier()
{
}

QDataStream& operator<<(QDataStream& str, const Dossier& x)
{
	str << x.UVsuivi.size();
	for (auto& u: x.UVsuivi)
		str << u;

	str << x.Cursussuivi.size();
	for (auto& c : x.Cursussuivi)
		str << c;

	str << x.Metadata.size();
	for (auto& pair : x.Metadata)
		str << pair.first << pair.second;

	for (int i = 0; i < UVType::size; ++i)
		str << x.Equivalences[i];

	return str;
}

QDataStream& operator>>(QDataStream& str, Dossier& x)
{
	int tmp;
	UVEncours tmp2("", UVStatus::RES);
	unsigned int tmpptr;
	QString tmpstr, tmpstr2;
	str >> tmp;

	x.UVsuivi = vector<UVEncours>(tmp);
	for (int i = 0; i < tmp; ++i)
	{
		str >> x.UVsuivi[i];
	}

	str >> tmp;
	x.Cursussuivi = vector<QString>(tmp);
	for (int i = 0; i < tmp; ++i)
		str >> x.Cursussuivi[i];

	str >> tmp;
	x.Metadata = map<QString, QString>();
	for (int i = 0; i < tmp; ++i)
	{
		str >> tmpstr >> tmpstr2;
		x.Metadata[tmpstr] = tmpstr2;
	}

	return str;
}