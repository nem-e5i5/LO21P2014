#pragma once
#include <vector>
#include <map>
#include <functional>
#include "UV.hpp"
#include "AllUtility.h"
#include "Semestre.h"
#include <stack>

using namespace std;

class Cursus;
class UVEncours;

typedef LinearizeIterator <UVEncours, SelectIterator<SemestreSuivi, UVEncoursOnVectorIterator, vector<SemestreSuivi>::iterator>, UVEncoursOnVectorIterator> SemestreLinearizer;
class Dossier
{
	friend QDataStream& operator<<(QDataStream&, const Dossier&);
	friend QDataStream& operator>>(QDataStream&, Dossier&);;

	vector<SemestreSuivi> Ssuivi;
	vector<QString> Cursussuivi;
	map<QString, QString> Metadata;

	int Equivalences[UVType::size];

public:

	//créer si n'existe pas, passer "" supprime la clé
	void Setmeta(QString, QString);
	QString Getmeta(QString);

	SemestreLinearizer UVIterator();
	WhereIterator<UV, SelectIterator<std::pair<QString, UV>, UV, std::map<QString, UV>::iterator>> UVPrenableIterator(QString SId);
	IdentityIterator<SemestreSuivi, vector<SemestreSuivi>::iterator> SemestreIterator();

	SelectIterator<QString, const Cursus&, vector<QString>::iterator> CursusIterator();

	int getNbEquivalences(UVType t);

	void setNbEquivalences(UVType t, int value);

	bool validerDossier();

	void NouveauSemestre(Semestre saison = Semestre::Automne);

	SemestreSuivi& SemestreRef(QString SId);
	void SupprimerSemestre(QString SId);

	void InscriptionUV(const UV& x);
	void InscriptionUVByName(QString x);
	
	void InscriptionCursus(const Cursus& x);
	void InscriptionCursusByName(QString x);
	void DesinscriptionCursusByName(QString x);

	Dossier();
	~Dossier();
};

QDataStream& operator<<(QDataStream&, const Dossier&);
QDataStream& operator>>(QDataStream&, Dossier&);