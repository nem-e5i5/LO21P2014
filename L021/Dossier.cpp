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

SemestreLinearizer Dossier::UVIterator()
{
	auto x = Select<SemestreSuivi, UVEncoursOnVectorIterator>(Ssuivi.begin(), Ssuivi.end(), [](const SemestreSuivi& s) { return const_cast<SemestreSuivi&>(s).UVIterator(); });
	return Linearize<UVEncours>(x, x.getEnd());
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

void Dossier::NouveauSemestre()
{
	Ssuivi.push_back(SemestreSuivi(Semestre::Automne, SemestreStatus::SEC));
}

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
	(*(Ssuivi.end() - 1)).Inscription(UVEncours(x, UVStatus::EC));
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
	str << x.Ssuivi.size();
	for (auto& u: x.Ssuivi)
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

	x.Ssuivi = vector<SemestreSuivi>(tmp);
	for (int i = 0; i < tmp; ++i)
	{
		str >> x.Ssuivi[i];
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