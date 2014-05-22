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