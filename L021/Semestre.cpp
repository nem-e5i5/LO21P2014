#include "Semestre.h"

UVEncoursOnVectorIterator SemestreSuivi::UVIterator()
{
	return UVEncoursOnVectorIterator(UVs.begin(), UVs.end());
}

void SemestreSuivi::Inscription(UVEncours e) { UVs.push_back(e); }
void SemestreSuivi::Desinscription(QString Name)
{
	auto iter = Where<UVEncours>(UVs.begin(), UVs.end(), 
		[=](const UVEncours& x) { return x.get_uv().get_code() == Name; });
	if (iter.ended()) return;
	auto& item = *iter;
	auto stditer = find(UVs.begin(), UVs.end(), item);
	UVs.erase(stditer);
}

int SemestreSuivi::get_nb_credit_effective(UVType type) const
{
	auto x = Where<const UVEncours>(UVs.begin(), UVs.end(), [](const UVEncours& u) { return u.get_hasCompleted(); });
	auto y = Select<const UVEncours, int>(x, x.getEnd(), [=](const UVEncours& u) { return u.get_uv().get_nb_credit(type); });
	return Sum<int>(y, y.getEnd(),
		Status == SemestreStatus::Fini ?
		(type < UVType::size ?
		Prevision[type] :
		Sum<int>(Prevision, Prevision + UVType::size, 0)) : 0);
}

int SemestreSuivi::get_nb_credit_previsional(UVType type) const
{
	auto x = Where<const UVEncours>(UVs.begin(), UVs.end(), [](const UVEncours& u) { return u.get_status() == UVStatus::EC || u.get_hasCompleted(); });
	auto y = Select<const UVEncours, int>(x, x.getEnd(), [=](const UVEncours& u) { return u.get_uv().get_nb_credit(type); });
	return Sum<int>(y, y.getEnd(), 
		type < UVType::size ? 
			Prevision[type] : 
			Sum<int>(Prevision, Prevision + UVType::size, 0));
}

SemestreStatus SemestreSuivi::get_Status() const
{
	return Status;
}

Semestre SemestreSuivi::get_Saison() const
{
	return SuiviEn;
}

void SemestreSuivi::change_Saison()
{
	SuiviEn = static_cast<Semestre>(!SuiviEn);
}

//Comparaison de référence, pas effective mais requise dans le programme
bool SemestreSuivi::operator==(const SemestreSuivi& o) const
{
	return this == &o;
}

SemestreSuivi::SemestreSuivi(Semestre s, SemestreStatus ss) : SuiviEn(s), Status(ss), ALEtranger(false)
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