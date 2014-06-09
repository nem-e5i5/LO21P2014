#include "CreditIn.h"
bool CreditInValidator::Validate(Dossier d) const
{
	auto iter = d.UVIterator();
	auto sl = Select<UVEncours, unsigned int>(iter, iter.getEnd(), 
		[=](const UVEncours& x) 
	{ return 
	t.contains(x.get_uv().get_code()) && 
	x.get_hasCompleted() ? 
		x.get_uv().get_nb_credit(UVType::Mixe) : 0; 
	});
	int ag = Sum<unsigned int>(sl, sl.getEnd(), 0);
	return ag >= nb;
}

bool CreditInValidator::MayValidate(Dossier d) const
{
	auto iter = d.UVIterator();
	auto sl = Select<UVEncours, unsigned int>(iter, iter.getEnd(),
		[=](const UVEncours& x) 
	{ return 
		t.contains(x.get_uv().get_code()) && 
		(x.get_hasCompleted() || x.get_status() == UVStatus::EC)  ? 
			x.get_uv().get_nb_credit(UVType::Mixe) : 0; 
	});
	int ag = Sum<unsigned int>(sl, sl.getEnd(), 0);
	return ag >= nb;
}

bool CreditInValidator::Improve(Dossier d, UV u) const
{
	return t.contains(u.get_code());
}