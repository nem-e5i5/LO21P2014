#include "Credit.h"
bool CreditValidator::Validate(Dossier d) const
{
	auto iter = d.SemestreIterator();
	auto sl = Select<SemestreSuivi, unsigned int>(iter, iter.getEnd(), [=](const SemestreSuivi& x) { return x.get_nb_credit_effective(t); });
	int ag = Sum<unsigned int>(sl, sl.getEnd(), d.getNbEquivalences(t));
	return ag >= nb;
}

bool CreditValidator::MayValidate(Dossier d) const
{
	auto iter = d.SemestreIterator();
	auto sl = Select<SemestreSuivi, unsigned int>(iter, iter.getEnd(), [=](const SemestreSuivi& x) { return x.get_nb_credit_previsional(t); });
	int ag = Sum<unsigned int>(sl, sl.getEnd(), d.getNbEquivalences(t));
	return ag >= nb;
}

bool CreditValidator::Improve(Dossier d, UV u) const
{
	return u.get_nb_credit(t) > 0;
}