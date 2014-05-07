#pragma once
#include <vector>
#include <hash_map>
#include <functional>
#include "UV.hpp"
#include "Cursus.h"
#include "AllUtility.h"

using namespace std;

class Dossier
{
	vector<UVEncours*> UVsuivi;
	vector<Cursus*> Cursussuivi;
	hash_map<QString, QString> Metadata;

	int Equivalences[UVType::size];

public:

	//créer si n'existe pas, passer "" supprime la clé
	void Setmeta(QString, QString);
	QString Getmeta(QString);

	IdentityIterator<UVEncours*, vector<UVEncours*>::iterator> UVIterator()
	{
		return IdentityIterator<UVEncours*, vector<UVEncours*>::iterator>(UVsuivi.begin(), UVsuivi.end());
	}

	IdentityIterator<Cursus*, vector<Cursus*>::iterator> CursusIterator()
	{
		return IdentityIterator<Cursus*, vector<Cursus*>::iterator>(Cursussuivi.begin(), Cursussuivi.end());
	}

	int getNbEquivalences(UVType t)
	{ 
		return Equivalences[t];
	}

	void setNbEquivalences(UVType t, int value = 0)
	{
		Equivalences[t] = value;
	}

	bool validerDossier();

	Dossier();
	~Dossier();
};

