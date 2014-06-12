#pragma once
#include "DossierEtCursus.h"

struct SwitchValidator : public CursusValidator{

	SwitchValidator() : CursusValidator(){}
	QString getName() const { return "Switch"; }
	struct SwitchValidatorFactory : public ValidatorFactory{
		SwitchValidator* proceed() const { return new SwitchValidator(); }
		CursusValidator* proceed(const CursusValidator& x) const { return new SwitchValidator(dynamic_cast<const SwitchValidator&>(x)); }
	};
QStringList t;
bool e;
int nb;

bool Validate(Dossier d) const;
bool MayValidate(Dossier d) const;
bool Improve(Dossier d, UV u) const;

QString Prety_print() { return 
	QString::fromWCharArray(L"Avoir validé ") + 
	QString::number(nb) + 
	QString::fromWCharArray(L" cursus") + 
	(e ? " exactement" : "") + 
	QString::fromWCharArray(L" dans la liste(") + t.join(", ") + ")"; }

void Serialize(QDataStream& str) const
{
	str << nb;
	str << e;
	str << t.size();
	for (auto u : t)
		str << u;
}

void UnSerialize(QDataStream& str)
{
	int tmp;
	QString tmp2;
	str >> nb;
	str >> e;
	str >> tmp;
	t = QStringList();
	for (int i = 0; i < tmp; ++i)
	{
		str >> tmp2;
		t << tmp2;
	}
	
}

bool Improvable() {return !e;}
};