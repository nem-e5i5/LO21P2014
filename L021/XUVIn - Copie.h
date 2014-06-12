#pragma once
#include "DossierEtCursus.h"

struct XUVInValidator : public CursusValidator{
	
	XUVInValidator() : CursusValidator(){}
	QString getName() const { return "XUVIn"; } 
	struct XUVInValidatorFactory : public ValidatorFactory{
		XUVInValidator* proceed() const { return new XUVInValidator(); }
		CursusValidator* proceed(const CursusValidator& x) const { return new XUVInValidator(dynamic_cast<const XUVInValidator&>(x)); }
	};
QStringList t;
int nb;

bool Validate(Dossier d) const;
bool MayValidate(Dossier d) const;
bool Improve(Dossier d, UV u) const;

QString Prety_print() { return QString("Avoir ") + QString::number(nb) + QString::fromWCharArray(L" UV dans la liste(") + t.join(", ") + ")"; }

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