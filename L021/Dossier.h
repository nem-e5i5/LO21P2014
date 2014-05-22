#pragma once
#include <vector>
#include <map>
#include <functional>
#include "UV.hpp"
#include "AllUtility.h"

using namespace std;

class Cursus;
class UVEncours;
class Dossier
{
	friend QDataStream& operator<<(QDataStream&, const Dossier&);
	friend QDataStream& operator>>(QDataStream&, Dossier&);;

	vector<UVEncours> UVsuivi;
	vector<QString> Cursussuivi;
	map<QString, QString> Metadata;

	int Equivalences[UVType::size];

public:

	//créer si n'existe pas, passer "" supprime la clé
	void Setmeta(QString, QString);
	QString Getmeta(QString);

	IdentityIterator<UVEncours, vector<UVEncours>::iterator> UVIterator();

	SelectIterator<QString, const Cursus&, vector<QString>::iterator> CursusIterator();

	int getNbEquivalences(UVType t);

	void setNbEquivalences(UVType t, int value);

	bool validerDossier();

	void InscriptionUV(const UV& x);
	void InscriptionUVByName(QString x);
	void InscriptionCursus(const Cursus& x);
	void InscriptionCursusByName(QString x);

	Dossier();
	~Dossier();
};

QDataStream& operator<<(QDataStream&, const Dossier&);
QDataStream& operator>>(QDataStream&, Dossier&);