#pragma once
#include "DossierEtCursus.h"

struct XSemestreALetrangerValidator : public CursusValidator{

	XSemestreALetrangerValidator() : CursusValidator(){}
	QString getName() const { return "XSemestreALetranger"; }
	struct XSemestreALetrangerValidatorFactory : public ValidatorFactory{
		XSemestreALetrangerValidator* proceed() const { return new XSemestreALetrangerValidator(); }
		CursusValidator* proceed(const CursusValidator& x) const { return new XSemestreALetrangerValidator(dynamic_cast<const XSemestreALetrangerValidator&>(x)); }
	};
int nb;

bool Improvable() const { return false; }

bool Validate(Dossier d) const;
bool MayValidate(Dossier d) const;
bool Improve(Dossier d, UV u) const;

QString Prety_print() { return QString("Avoir fait ") + QString::number(nb) + QString::fromWCharArray(L" semestres à l'étranger"); }

void Serialize(QDataStream& str) const
{
	str << nb;
}

void UnSerialize(QDataStream& str)
{
	str >> nb;
}
};