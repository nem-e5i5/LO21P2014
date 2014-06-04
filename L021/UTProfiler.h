#pragma once

#include "UV.hpp"
#include "AllUtility.h"
#include "DossierEtCursus.h"
#include <qfile.h>
#include <qstring.h>
#include <qdatastream.h>

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
	{
		if (!ssx) ssx = new UTProfiler();
		return ssx;
	}

	static void ResetInstance()
	{
		if (ssx) delete ssx;
		ssx = new UTProfiler();
	}

	Dossier& getDossier() { return MonDossier; }

	SelectIterator<pair<QString, UV>, UV, map<QString, UV>::iterator> UVIterator();

	SelectIterator<pair<QString, Cursus>, Cursus, map<QString, Cursus>::iterator> CursusIterator();

	UV& UVrefByName(QString name) { return UVList[name]; }
	Cursus& CursusrefByName(QString name) { return CursusList[name]; }

	bool UVExists(QString name) { return UVList.find(name) != UVList.end(); }
	bool CursusExists(QString name) { return CursusList.find(name) != CursusList.end(); }

	void RemoveUV(QString name);
	void RemoveCursus(QString name);


	void AppToBinFile(QString fname);

	void BinFileToApp(QString fname);
};

