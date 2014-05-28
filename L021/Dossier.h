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

typedef LinearizeIterator <UVEncours, SelectIterator<SemestreSuivi, UVEncoursOnVectorIterator, vector<SemestreSuivi>::iterator>> SemestreLinearizer;
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

	SelectIterator<QString, const Cursus&, vector<QString>::iterator> CursusIterator();

	int getNbEquivalences(UVType t);

	void setNbEquivalences(UVType t, int value);

	bool validerDossier();

	void NouveauSemestre();

	void InscriptionUV(const UV& x);
	void InscriptionUVByName(QString x);
	void InscriptionCursus(const Cursus& x);
	void InscriptionCursusByName(QString x);

	Dossier();
	~Dossier();
};

QDataStream& operator<<(QDataStream&, const Dossier&);
QDataStream& operator>>(QDataStream&, Dossier&);