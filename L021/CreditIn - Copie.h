#pragma once
#include "DossierEtCursus.h"

struct CreditInValidator : public CursusValidator{

	CreditInValidator() : CursusValidator(){}
	QString getName() const { return "CreditIn"; }
	struct CreditInValidatorFactory : public ValidatorFactory{
		CreditInValidator* proceed() const { return new CreditInValidator(); }
		CursusValidator* proceed(const CursusValidator& x) const { return new CreditInValidator(dynamic_cast<const CreditInValidator&>(x)); }
	};
QStringList t;
int nb;

bool Validate(Dossier d) const;
bool MayValidate(Dossier d) const;
bool Improve(Dossier d, UV u) const;

QString Prety_print() { return QString("Avoir ") + QString::number(nb) + QString::fromWCharArray(L" crédits dans la liste(") + t.join(", ") + ")"; }

void Serialize(QDataStream& str) const
{
	str << nb;
	str << t.size();
	for (auto u : t)
		str << u;
}

void UnSerialize(QDataStream& str)
{
	int tmp;
	QString tmp2;
	str >> nb;
	str >> tmp;
	t = QStringList();
	for (int i = 0; i < tmp; ++i)
	{
		str >> tmp2;
		t << tmp2;
	}
}
};