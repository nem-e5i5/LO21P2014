#pragma once
#include <vector>
#include <map>
#include <functional>
#include "UV.hpp"
#include "AllUtility.h"

using namespace std;

class Cursus;
class Dossier
{
	vector<UVEncours*> UVsuivi;
	vector<Cursus*> Cursussuivi;
	map<QString, QString> Metadata;

	int Equivalences[UVType::size];

public:

	//créer si n'existe pas, passer "" supprime la clé
	void Setmeta(QString, QString);
	QString Getmeta(QString);

	IdentityIterator<UVEncours*, vector<UVEncours*>::iterator> UVIterator();

	IdentityIterator<Cursus*, vector<Cursus*>::iterator> CursusIterator();

	int getNbEquivalences(UVType t);

	void setNbEquivalences(UVType t, int value);

	bool validerDossier();

	Dossier();
	~Dossier();
};

