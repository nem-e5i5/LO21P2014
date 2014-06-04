#include "DossierEtCursus.h"

UTProfiler* UTProfiler::ssx = new UTProfiler();

UTProfiler::UTProfiler()
{
}


UTProfiler::~UTProfiler()
{
}

SelectIterator<pair<QString, UV>, UV, map<QString, UV>::iterator> UTProfiler::UVIterator()
{
	return Select<pair<QString, UV>, UV>(UVList.begin(), UVList.end(),
		[](const pair<QString, UV>& x) { return x.second; });
}

SelectIterator<pair<QString, Cursus>, Cursus, map<QString, Cursus>::iterator> UTProfiler::CursusIterator()
{
	return Select<pair<QString, Cursus>, Cursus>(CursusList.begin(), CursusList.end(),
		[](const pair<QString, Cursus>& x) { return x.second; });
}

void UTProfiler::RemoveUV(QString name)
{
	
	auto iter1 = MonDossier.SemestreIterator();
	for (; !iter1.ended(); ++iter1)
		for (auto iter2 = (*iter1).UVIterator(); !iter2.ended(); ++iter2)
		if ((*iter2).get_uv().get_code() == name)
		{
			if ((*iter2).get_hasCompleted()) for (int i = 0; i < UVType::size; ++i)
				MonDossier.setNbEquivalences(static_cast<UVType>(i),
				MonDossier.getNbEquivalences(static_cast<UVType>(i))
				+ (*iter2).get_uv().get_nb_credit(static_cast<UVType>(i)));
			(*iter2) = UVEncours("__NULL__", (*iter2).get_status());
		}
			
	UVList.erase(name);
}

void UTProfiler::RemoveCursus(QString name)
{
	auto iter = MonDossier.CursusIterator();
	for (; !iter.ended(); ++iter)
	{
		if ((*iter).getName() == name)
		{
			MonDossier.DesinscriptionCursusByName(name);
			break;
		}
	}
	CursusList.erase(name);
}

void UTProfiler::AppToBinFile(QString fname)
{
	QFile f(fname);
	if (!f.open(QIODevice::WriteOnly))
		return;
	QDataStream dst(&f);

	dst << UVList.size();

	for (auto iter = UVIterator(); !iter.ended(); ++iter) dst << *iter;


	dst << CursusList.size();

	for (auto iter = CursusIterator(); !iter.ended(); ++iter) dst << *iter;

	dst << MonDossier;
	f.close();
}

void UTProfiler::BinFileToApp(QString fname)
{
	QFile f(fname);
	if (!f.open(QIODevice::ReadOnly))
		return;
	QDataStream dst(&f);

	int tmp;
	Cursus tmp2("");
	UV tmp3;
	Dossier tmp4;

	dst >> tmp;
	UVList = map<QString, UV>();
	for (int i = 0; i < tmp; ++i)
	{
		dst >> tmp3;
		UVList[tmp3.get_code()] = tmp3;
	}

	dst >> tmp;
	CursusList = map<QString, Cursus>();
	for (int i = 0; i < tmp; ++i)
	{
		dst >> tmp2;
		CursusList[tmp2.getName()] = tmp2;
	}

	dst >> MonDossier;
	f.close();
}