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
//! Itere sur l'ensemble des UV du Dossier.
{
	auto x = Select<SemestreSuivi, UVEncoursOnVectorIterator>(Ssuivi.begin(), Ssuivi.end(), [](const SemestreSuivi& s) { return const_cast<SemestreSuivi&>(s).UVIterator(); });
	return Linearize<UVEncours, UVEncoursOnVectorIterator>(x, x.getEnd());
}

WhereIterator<UV, SelectIterator<std::pair<QString, UV>, UV, std::map<QString, UV>::iterator>> Dossier::UVPrenableIterator(QString SId)
//! Liste des UV pouvant etre suivies pour un Semestre donné.
{
	auto& s = SemestreRef(SId);

	auto piter = UTProfiler::GetInstance()->UVIterator();
	auto xiter = s.UVIterator();
	auto viter = UVIterator();
	auto iter = Where<UV>(piter, piter.getEnd(),
		[xiter, viter, &s](const UV x) {
		return
			Where<UVEncours>(xiter, xiter.getEnd(),
			[&x](const UVEncours& y) { return y.get_uv() == x; }).ended() &&
			Where<UVEncours>(viter, viter.getEnd(),
			[&x](const UVEncours& y) { return (y.get_hasCompleted() || y.get_status() == UVStatus::EC) && y.get_uv() == x; }).ended()
			&& ((x.get_automne() && s.get_Saison() == Semestre::Automne) || (x.get_printemps() && s.get_Saison() == Semestre::Printemps));
	}
	); //Différence ensembliste: UV - UV_déjà_prise - UV_déjà_validé - UV_pas_enseigné
	return iter;
}

IdentityIterator<SemestreSuivi, vector<SemestreSuivi>::iterator> Dossier::SemestreIterator()
//! Retourne un itérateur sur l'ensemble des Semestre du Dossier
{
	return IdentityIterator<SemestreSuivi, vector<SemestreSuivi>::iterator>(Ssuivi.begin(), Ssuivi.end());
}

SelectIterator<QString, const Cursus&, vector<QString>::iterator> Dossier::CursusIterator()
//! Retourne un itérateur sur l'ensemble des Cursus du Dossier
{
	return Select<QString, const Cursus&>(Cursussuivi.begin(), Cursussuivi.end(),
		[](QString x) -> const Cursus&{ return UTProfiler::GetInstance()->CursusrefByName(x); });
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
//! Renvoie true si le Dossier est complété, false sinon. 
{ 
	for (auto x = CursusIterator(); !x.ended(); ++x) 
		if (!((*x).Validate(*this))) return false; 
	return true; }

void Dossier::NouveauSemestre(Semestre saison)
//! Créer un nouveau Semestre.
{
	if (Ssuivi.size() > 0) 
		Ssuivi.push_back(
		SemestreSuivi(static_cast<Semestre>(!(*(Ssuivi.end() - 1)).get_Saison()), 
		SemestreStatus::PL));
	else Ssuivi.push_back(SemestreSuivi(saison, SemestreStatus::PL));
}

SemestreSuivi& Dossier::SemestreRef(QString SId)
//! Retourne une reference vers le semestre de nom SId. Si SId="" retourne le dernier Semestre.
{
	if (SId == "") return *(Ssuivi.end() - 1);
	int ct = (SId.mid(1).toInt() - 1) * 2;
	if ((SId[0] == 'A' && Ssuivi[0].get_Saison() == Semestre::Automne)
	 || (SId[0] == 'P' && Ssuivi[0].get_Saison() == Semestre::Printemps)) 
		//Concordance avec le premier
		return Ssuivi[ct];
	else 
		//Discordance
		return Ssuivi[ct + 1];
}

void Dossier::SupprimerSemestre(QString SId)
//! Tente de Supprimer un Semestre du Dossier.
{
	auto& ref = SemestreRef(SId);
	auto iterem = find(Ssuivi.begin(), Ssuivi.end(), ref);
	auto iter = iterem;
	for (auto end = Ssuivi.end(); iter != end; ++iter)
		(*iter).change_Saison();
	Ssuivi.erase(iterem);

}

void Dossier::InscriptionUV(const UV& x)
//! Inscription a une UV pour le Dossier.
{
	Dossier::InscriptionUVByName(x.get_code());
}
void Dossier::InscriptionCursus(const Cursus& x)
//! Inscription a un Cursus pour le Dossier.
{
	InscriptionCursusByName(x.getName());
}

void Dossier::InscriptionUVByName(QString x)
//! Inscription a une UV pour le Dossier en fonction du nom.
{
	if (!UTProfiler::GetInstance()->UVExists(x)) throw;
	(*(Ssuivi.end() - 1)).Inscription(UVEncours(x, UVStatus::EC));
}
void Dossier::InscriptionCursusByName(QString x)
//! Inscription a un Cursus pour le Dossier en fonction du nom.
{
	if (!UTProfiler::GetInstance()->CursusExists(x)) throw;
	Cursussuivi.push_back(x);
}

void Dossier::DesinscriptionCursusByName(QString x)
//! Desinscription d'un Cursus pour le Dossier en fonction du nom.
{
	auto iter = find(Cursussuivi.begin(), Cursussuivi.end(), x);
	if (iter == Cursussuivi.end()) throw;
	Cursussuivi.erase(iter);
}

Dossier::Dossier()
{
	for (int i = 0; i < UVType::size; ++i) Equivalences[i] = 0;
}


Dossier::~Dossier()
{
}

QDataStream& operator<<(QDataStream& str, const Dossier& x)
//! Exporte un dossier dans un QDataStream.
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
//! Importe un dossier depuis un QDataStream.
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