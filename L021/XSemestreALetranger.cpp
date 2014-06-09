#include "XSemestreALetranger.h"
bool XSemestreALetrangerValidator::Validate(Dossier d) const
{
	auto iter = d.SemestreIterator();
	auto sl = Select<SemestreSuivi, unsigned int>(iter, iter.getEnd(),
	[=](const SemestreSuivi& x)
	{ return
	x.get_Status() == SemestreStatus::Fini && 
	x.get_ALEtranger() ?
	1 : 0;
	});
	int ag = Sum<unsigned int>(sl, sl.getEnd(), 0);
	return ag >= nb;
}

bool XSemestreALetrangerValidator::MayValidate(Dossier d) const
{
	auto iter = d.SemestreIterator();
	auto sl = Select<SemestreSuivi, unsigned int>(iter, iter.getEnd(),
		[=](const SemestreSuivi& x)
	{ return
	x.get_ALEtranger() ?
	1 : 0;
	});
	int ag = Sum<unsigned int>(sl, sl.getEnd(), 0);
	return ag >= nb;
}

bool XSemestreALetrangerValidator::Improve(Dossier d, UV u) const
{
	return false;
}