#pragma once

#include "UV.hpp"
#include "AllUtility.h"
#include "DossierEtCursus.h"
#include <qfile.h>
#include <qstring.h>
#include <qdatastream.h>
#include <qtextstream.h>

class Cursus;
class UV;
class Dossier;
class UTProfiler
{
	//DEBUG
	friend int main(int argc, char *argv[]);

	map<QString, UV> UVList;
	map<QString, Cursus> CursusList;
	Dossier MonDossier;
	UTProfiler();
	static UTProfiler* ssx;
public:
	
	~UTProfiler();

	static UTProfiler* GetInstance()
	//! Retourne une instance du singleton UTProfiler.
	{
		if (!ssx) ssx = new UTProfiler();
		return ssx;
	}

	static void ResetInstance()
	//! Retourne une nouvelle instance du singleton UTProfiler.
	{
		if (ssx) delete ssx;
		ssx = new UTProfiler();
	}

	Dossier& getDossier() { return MonDossier; }

	SelectIterator<pair<QString, UV>, UV, map<QString, UV>::iterator> UVIterator();

	SelectIterator<pair<QString, Cursus>, Cursus, map<QString, Cursus>::iterator> CursusIterator();

	UV& UVrefByName(QString name) 
	//! Retourne une reference sur l'UV de nom name. Si l'UV n'existe pas elle est cree.
	{ return UVList[name]; }
	Cursus& CursusrefByName(QString name)
	//! Retourne une reference sur le Cursus de nom name. Si le Cursus n'existe pas il est cree.
	{ return CursusList[name]; }

	bool UVExists(QString name)
	//! Retourne true si l'UV existe, false sinon.
	{ return UVList.find(name) != UVList.end(); }
	bool CursusExists(QString name)
	//! Retourne true si le Cursus existe, false sinon.
	{ return CursusList.find(name) != CursusList.end(); }

	void RemoveUV(QString name);
	void RemoveCursus(QString name);


	void AppToBinFile(QString fname);

	void BinFileToApp(QString fname);

	void ImportUVOnly(QString fname);

	void ImportUVOnlytxt(QString fname);


	void AutoComplete();
};

