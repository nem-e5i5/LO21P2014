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

void UTProfiler::ImportUVOnly(QString fname)
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
	for (int i = 0; i < tmp; ++i)
	{
		dst >> tmp3;
		UVList[tmp3.get_code()] = tmp3;
	}
}

void UTProfiler::ImportUVOnlytxt(QString fname)
{
	QFile f(fname);
	if (!f.open(QIODevice::ReadOnly))
		return;
	
	QTextStream str(&f);
	str.setCodec("UTF-8");
	QString name, titre, tmp;
	int Credit;
	UVType t;
	while (!str.atEnd())
	{
		try
		{
			name = str.readLine();
			titre = str.readLine();
			Credit = str.readLine().toInt();
			t = UVTypeFromName(str.readLine());
		}
		catch (exception) { break; }
		UVList[name] = UV(name, titre, t, Credit, true, true);
	}
}

void UTProfiler::AutoComplete()
{
	auto CursusIter = getDossier().CursusIterator();
	if (MonDossier.SemestreIterator().ended())
	{
		MonDossier.NouveauSemestre();
		MonDossier.SemestreRef().set_Status(SemestreStatus::PR);
	}

	for (; !CursusIter.ended(); ++CursusIter)
	//Pour chaque cursus
	{
		auto UVIter = MonDossier.UVPrenableIterator("");
		for (; !(*CursusIter).MayValidate(MonDossier) && !UVIter.ended(); ++UVIter)
		//Pour chaque UV tant que le cursus n'est pas validé
		{
			if ((*CursusIter).Improve(MonDossier, *UVIter))
			//si l'uv améliore le dossier
			{
				if (MonDossier.SemestreRef().get_nb_credit_previsional(UVType::Mixe) + (*UVIter).get_nb_credit(UVType::Mixe) >= 35
					|| MonDossier.SemestreRef().UVCount() >= 7)
				//si le semestre est plein
				{
					//on en commence un nouveau
					MonDossier.NouveauSemestre();
					//de type proposé
					MonDossier.SemestreRef().set_Status(SemestreStatus::PR);
					//auquel on ajoute l'UV voulu
					MonDossier.InscriptionUV(*UVIter);
					//puis on remet l'UVPrenableIterator à 0 (car on a changer de saison et de nouvelles UV peuevnt devenir disponible)
					UVIter = MonDossier.UVPrenableIterator("");
				}
				else
				{
					MonDossier.InscriptionUV(*UVIter);
					UVIter = MonDossier.UVPrenableIterator("");
				}
			}
		}
		if (!(*CursusIter).MayValidate(MonDossier))
		{
			Notify(QString::fromWCharArray(L"Impossible de compléter le dossier. Le cursus ") + (*CursusIter).getName() + " bloque");
			if ((*CursusIter).MayValidateImprovable(MonDossier))
			{
				Notify(QString::fromWCharArray(L"Il semblerait que le bloquage soit causé par des conditions de validations ne concernant pas les UV. Un semestre à l'étranger par exemple? L'application va maintenant continuer l'autocomplétion, il faudra néanmoins pour compléter le dossier une action supplémentaire"));
				continue;
			}
			return;
		}
	}
	//optimisation du nombre d'UV
	auto SemIter = MonDossier.SemestreIterator();
	for (; !SemIter.ended(); ++SemIter)
	{
		auto UVIter = (*SemIter).UVIterator();
		auto uvector = toVector<UVEncours>(UVIter, UVIter.getEnd());
		for (auto uv : uvector)
		{
			(*SemIter).Desinscription(uv.get_uv().get_code());
			CursusIter = MonDossier.CursusIterator();
			for (; !CursusIter.ended(); ++CursusIter)
			{
				if (!(*CursusIter).MayValidate(MonDossier)) break;
			}
			if (!CursusIter.ended()) (*SemIter).Inscription(uv);
		}
	}
	//Optimisation du nombre de semestres
	SemIter = MonDossier.SemestreIterator();
	for (; !SemIter.ended(); ++SemIter)
	{
		if ((*SemIter).get_Status() != SemestreStatus::PL && (*SemIter).get_Status() != SemestreStatus::PR)
			continue;
		auto UVIter = MonDossier.UVIterator();
		auto ____debug = toVector<UVEncours>(UVIter, UVIter.getEnd());

		UVIter = SkipWhile(UVIter, UVIter.getEnd(), [SemIter](const UVEncours& x)
		{
			auto y = SemIter;
			++y;
			if (y.ended()) return true;
			return (*y).UVIterator().ended() || 
				x != (*(*y).UVIterator());
		});
		auto uvector = toVector<UVEncours>(UVIter, UVIter.getEnd());
		for (auto uv : uvector)
		{
			if ((*SemIter).get_Status() == SemestreStatus::PL || (*SemIter).get_Status() == SemestreStatus::PR)
			if ((*SemIter).get_nb_credit_previsional(UVType::Mixe) + uv.get_uv().get_nb_credit(UVType::Mixe) < 35
				&& (*SemIter).UVCount() < 7)
			if ((uv.get_uv().get_automne() && (*SemIter).get_Saison() == Semestre::Automne)
				|| (uv.get_uv().get_printemps() && (*SemIter).get_Saison() == Semestre::Printemps))
			{
				MonDossier.DesinscriptionUVByName(uv.get_uv().get_code());
				(*SemIter).Inscription(uv);
			}
		}
	}
}