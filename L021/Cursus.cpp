#include "Cursus.h"

template <class T>
int Cursus::addValidator(T x) { Validators.push_back(x); return Validators.size() - 1; }
void Cursus::removeValidator(int Id) { Validators.erase(Validators.begin() + Id); }

bool Cursus::Validate(Dossier d)
{
	for (auto& v : Validators)
	if (!v.Validate(d)) return false;
	return true;
}
Cursus::Cursus(){}
Cursus::~Cursus(){}

bool CreditValidator(Dossier d, const char* data)
{
	int nbr = *(int*)data;
	UVType t = *(UVType*)(data + sizeof(int));

	auto x = d.UVIterator();
	auto candidate = Where<UVEncours*>(x, x.getEnd(), [=](UVEncours* u) { return u->get_uv()->get_type() == t; });
	int sum = Aggregate<UVEncours*, int>(candidate, candidate.getEnd(), [](int s, UVEncours* u) { return s + u->get_uv()->get_nb_credit(); }, d.getNbEquivalences(t));
	return sum >= nbr;
}


