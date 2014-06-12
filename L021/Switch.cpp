#include "Switch.h"
bool SwitchValidator::Validate(Dossier d) const
{
	int ct = 0;
	for (auto& s : t)
	{
		if (UTProfiler::GetInstance()->CursusrefByName(s).Validate(d))
			++ct;
		if (!e && ct >= nb) return true;
	}
	if (ct == nb) return true;
	return false;
}

bool SwitchValidator::MayValidate(Dossier d) const
{
	int ct = 0;
	for (auto& s : t)
	{
		if (UTProfiler::GetInstance()->CursusrefByName(s).MayValidate(d))
			++ct;
		if (!e && ct >= nb) return true;
	}
	if (ct == nb) return true;
	return false;
}

bool SwitchValidator::Improve(Dossier d, UV u) const
{
	if (e) return false;
	int ct = 0;
	for (auto& s : t)
	{
		if (UTProfiler::GetInstance()->CursusrefByName(s).Improve(d, u))
			return true;
	}
	return false;
}