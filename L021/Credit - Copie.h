#pragma once
#include "DossierEtCursus.h"

struct CreditValidator : public CursusValidator{

	CreditValidator() : CursusValidator(){}
	QString getName() const { return "Credit"; }
	struct CreditValidatorFactory : public ValidatorFactory{
		CreditValidator* proceed() const { return new CreditValidator(); }
		CursusValidator* proceed(const CursusValidator& x) const { return new CreditValidator(dynamic_cast<const CreditValidator&>(x)); }
	};

UVType t;
int nb;

CreditValidator(UVType _t, int nbr) : CursusValidator(), t(_t), nb(nbr) {}

bool Validate(Dossier d) const;
bool MayValidate(Dossier d) const;
bool Improve(Dossier d, UV u) const;

QString Prety_print() { return QString("Avoir ") + QString::number(nb) + QString::fromWCharArray(L" crédits ") + UVTypeName(t); }

void Serialize(QDataStream& str) const
{
	str << static_cast<int>(t)
		<< nb;
}

void UnSerialize(QDataStream& str)
{
	int tmp;
	str >> tmp;
	t = static_cast<UVType>(tmp);
	str >> nb;
}
};