#pragma once
#include <functional>
#include <vector>
#include "Dossier.h"
#include "AllUtility.h"

using namespace std;

struct func {
	typedef function<bool(Dossier)> predicate;
};

class Cursus
{
	vector<func::predicate> Validators;
public:
	int addValidator(func::predicate x);
	void removeValidator(int Id);

	bool Validate(Dossier d)
	{
		for (auto v : Validators)
			if (!v(d)) return false;
		return true;
	}
	Cursus();
	~Cursus();
};

template <class src>
func<src>::predicate CreditValidator(int nbr, UVType t)
{
	return [=](Dossier d)
	{
		auto x = d.UVIterator();
		auto candidate = Where<UVEncours>(x, x.getEnd(), [=](const UVEncours& u) { return u.get_type() == t});
		int sum = Aggregate<UVEncours, int>(candidate, candidate.getEnd(), [](int s, const UVEncours& u) { return s + u.get_nb_credit(); }, d.getNbEquivalences(t));
		return sum >= nbr;
	};
}
