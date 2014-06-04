#pragma once
#include "AllUtility.h"
#include "UV.hpp"
#include <qdatastream.h>

typedef IdentityIterator<UVEncours, vector<UVEncours>::iterator> UVEncoursOnVectorIterator;
class SemestreSuivi
{
	friend QDataStream& operator<<(QDataStream& str, const SemestreSuivi& s);
	friend QDataStream& operator>>(QDataStream& str, SemestreSuivi& s);

	Semestre SuiviEn;
	SemestreStatus Status;
	bool ALEtranger;
	int Prevision[UVType::size];
	vector<UVEncours> UVs;

public:
	UVEncoursOnVectorIterator UVIterator();
	void Inscription(UVEncours e);
	void Desinscription(QString Name);

	//Mixe pour tout
	int get_nb_credit_effective(UVType type) const;
	int get_nb_credit_previsional(UVType type) const;
	SemestreStatus get_Status() const;
	Semestre get_Saison() const;

	void change_Saison();

	bool operator==(const SemestreSuivi&) const;

	SemestreSuivi(Semestre, SemestreStatus);
	SemestreSuivi();
	~SemestreSuivi();
};

QDataStream& operator<<(QDataStream& str, const SemestreSuivi& s);
QDataStream& operator>>(QDataStream& str, SemestreSuivi& s);