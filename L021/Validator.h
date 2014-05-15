#pragma once
#include "AllUtility.h"
#include "DossierEtCursus.h"
/*class Validator
{
	typedef function<bool(Dossier)> predicate;
	predicate Imp;

	Validator()
	{

	}
};

bool CreditValidate(Dossier subject, int nbr, UVType t)
{
	auto x = subject.UVIterator();
	auto candidate = Where<UVEncours*>(x, x.getEnd(), [=](UVEncours* u) { return u->get_type() == t; });
	int sum = Aggregate<UVEncours*, int>(candidate, candidate.getEnd(), [](int s, UVEncours* u) { return s + u->get_nb_credit(); }, subject.getNbEquivalences(t));
	return sum >= nbr;
}