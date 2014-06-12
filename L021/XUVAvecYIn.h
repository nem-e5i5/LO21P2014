#pragma once
#include "DossierEtCursus.h"

define_validator(XUVAvecYIn)
QStringList t;
int nb;
UVStatus s;

bool Validate(Dossier d) const;
bool MayValidate(Dossier d) const;
bool Improve(Dossier d, UV u) const;

QString Prety_print() { return QString("Avoir ") + QString::number(nb) + QString::fromWCharArray(L" UV dans la liste(") + t.join(", ") + ") avec une note minimum de " + UVStatusName(s); }

void Serialize(QDataStream& str) const
{
	str << nb;
	str << s;
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
	s = static_cast<UVStatus>(tmp);
	str >> tmp;
	t = QStringList();
	for (int i = 0; i < tmp; ++i)
	{
		str >> tmp2;
		t << tmp2;
	}
}
};