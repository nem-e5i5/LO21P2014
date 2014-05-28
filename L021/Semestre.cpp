#include "Semestre.h"

UVEncoursOnVectorIterator SemestreSuivi::UVIterator()
{
	return UVEncoursOnVectorIterator(UVs.begin(), UVs.end());
}

void SemestreSuivi::Inscription(UVEncours e) { UVs.push_back(e); }

int SemestreSuivi::get_nb_credit_effective(UVType type) const
{
	auto x = Where<const UVEncours>(UVs.begin(), UVs.end(), [](const UVEncours& u) { return u.get_hasCompleted(); });
	auto y = Select<const UVEncours, int>(x, x.getEnd(), [=](const UVEncours& u) { return u.get_uv().get_nb_credit(type); });
	return Sum<int>(y, y.getEnd(), 0);
}

int SemestreSuivi::get_nb_credit_previsional(UVType type) const
{
	auto x = Where<const UVEncours>(UVs.begin(), UVs.end(), [](const UVEncours& u) { return u.get_status() == UVStatus::EC; });
	auto y = Select<const UVEncours, int>(x, x.getEnd(), [=](const UVEncours& u) { return u.get_uv().get_nb_credit(type); });
	return Sum<int>(y, y.getEnd(), Prevision[type]);
}

SemestreSuivi::SemestreSuivi(Semestre s, SemestreStatus ss) : SuiviEn(s), Status(ss)
{
	for (auto& x : Prevision) x = 0;
}

SemestreSuivi::SemestreSuivi() : SemestreSuivi(Semestre::Automne, SemestreStatus::SEC)
{
	
}

SemestreSuivi::~SemestreSuivi()
{
}

QDataStream& operator<<(QDataStream& str, const SemestreSuivi& s)
{
	str << static_cast<bool>(s.SuiviEn) << static_cast<int>(s.Status) << s.UVs.size();
	for (auto x : s.UVs) str << x;
	return str;
}
QDataStream& operator>>(QDataStream& str, SemestreSuivi& s)
{
	bool tmp1;
	int tmp2, tmp3;
	str >> tmp1 >> tmp2 >> tmp3;
	s.SuiviEn = static_cast<Semestre>(tmp1);
	s.Status = static_cast<SemestreStatus>(tmp2);

	s.UVs = vector<UVEncours>(tmp3);
	for (int i = 0; i < tmp3; ++i) str >> s.UVs[i];
	return str;
}