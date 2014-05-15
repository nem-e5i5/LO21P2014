#pragma once
#include "UV.hpp"
#include "AllUtility.h"
#include "DossierEtCursus.h"
#include <qfile.h>
#include <qstring.h>
#include <qdatastream.h>

class Cursus;
//class Dossier;
class UTProfiler
{
	vector<UV> UVList;
	vector<Cursus> CursusList;
	//Dossier MonDossier;
	UTProfiler();
	static UTProfiler* ssx;
public:
	
	~UTProfiler();

	static UTProfiler* GetInstance()
	{
		if (!ssx) ssx = new UTProfiler();
		return ssx;
	}

	IdentityIterator<UV, vector<UV>::iterator> UVIterator()
	{
		return IdentityIterator<UV, vector<UV>::iterator>(UVList.begin(), UVList.end());
	}

	IdentityIterator<Cursus, vector<Cursus>::iterator> CursusIterator()
	{
		return IdentityIterator<Cursus, vector<Cursus>::iterator>(CursusList.begin(), CursusList.end());
	}

	void UVToBinFile(QString fname)
	{
		QFile f(fname);
		if (!f.open(QIODevice::WriteOnly))
			return;
		QDataStream dst(&f);

		for (auto uv : UVList)
		{
			dst << uv.get_code();
			dst << uv.get_titre();
			dst << uv.get_type();
			dst << uv.get_nb_credit();
			dst << uv.get_automne();
			dst << uv.get_printemps();
			dst << uv.isnull();
		}

		/*for (auto cr : CursusList)
		{
			dst << uv.get_code();
			dst << uv.get_titre();
			dst << uv.get_type();
			dst << uv.get_nb_credit();
			dst << uv.get_automne();
			dst << uv.get_printemps();
			dst << uv.isnull();
		}*/
	}
};

