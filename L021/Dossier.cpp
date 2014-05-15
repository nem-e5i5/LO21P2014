#include "Dossier.h"


void Dossier::Setmeta(QString n, QString v) 
{
	if (v == "") Metadata.erase(n);
	Metadata[n] = v;
}

QString Dossier::Getmeta(QString n)
{
	return Metadata[n];
}

IdentityIterator<UVEncours*, vector<UVEncours*>::iterator> Dossier::UVIterator()
{
	return IdentityIterator<UVEncours*, vector<UVEncours*>::iterator>(UVsuivi.begin(), UVsuivi.end());
}

IdentityIterator<Cursus*, vector<Cursus*>::iterator> Dossier::CursusIterator()
{
	return IdentityIterator<Cursus*, vector<Cursus*>::iterator>(Cursussuivi.begin(), Cursussuivi.end());
}

int Dossier::getNbEquivalences(UVType t)
{
	return Equivalences[t];
}

void Dossier::setNbEquivalences(UVType t, int value = 0)
{
	Equivalences[t] = value;
}

bool Dossier::validerDossier() { return false; }

Dossier::Dossier()
{
}


Dossier::~Dossier()
{
}
