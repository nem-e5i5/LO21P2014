#include "DossierEtCursus.h"

map<QString, const ValidatorFactory*> CursusValidator::Validators;


CursusValidator* CursusValidator::true_UnSerialize(QDataStream& str)
{
	QString t;
	str >> t;
	//Yaaay pas d'erreur
	CursusValidator* ret = Validators[t]->proceed();
	ret->UnSerialize(str);
	return ret;
}


bool CreditValidator::Validate(Dossier d) const
{
	auto iter = d.UVIterator();
	auto cd = Where<UVEncours>(iter, iter.getEnd(), [=](const UVEncours& x) { return x.get_uv().get_type() == t && x.get_hasCompleted(); });
	auto sl = Select<UVEncours, unsigned int>(cd, cd.getEnd(), [](const UVEncours& x) { return x.get_uv().get_nb_credit(); });
	int ag = Sum<unsigned int>(sl, sl.getEnd(), d.getNbEquivalences(t));
	return ag >= nb;
}

int Cursus::addValidator(CursusValidator* x) { Validators.push_back(x); return Validators.size() - 1; }

void Cursus::removeValidator(int Id) { Validators.erase(Validators.begin() + Id); }

bool Cursus::Validate(Dossier d) const
{
	for (auto& v : Validators)
	if (!v->Validate(d)) return false;
	return true;
}

Cursus::Cursus(const Cursus& x): Name(x.Name), 
								 Validators(vector<CursusValidator*>(x.Validators.size()))
{
	for (int i = 0; i < x.Validators.size(); ++i) 
		Validators[i] = CursusValidator::Validators[x.Validators[i]->getName()]->proceed(*x.Validators[i]);
}

const Cursus& Cursus::operator=(const Cursus& x)
{
	if (&x == this) return x;

	Name = x.Name;
	Validators = vector<CursusValidator*>(x.Validators.size());
	for (int i = 0; i < x.Validators.size(); ++i)
		Validators[i] = CursusValidator::Validators[x.Validators[i]->getName()]->proceed(*x.Validators[i]);
	return x;
}

Cursus::Cursus(QString name) : Name(name){}
Cursus::~Cursus(){
	for (auto& v : Validators)
	{
		delete v;
		v = nullptr;
	}
}

QDataStream& operator<<(QDataStream& str, const Cursus& x)
{
	str << x.getName();
	str << x.Validators.size();
	for (auto v : x.Validators)
		v->true_Serialize(str);
	return str;
}
QDataStream& operator>>(QDataStream& str, Cursus& x)
{
	int tmp;
	str >> x.Name;
	str >> tmp;
	x.Validators = vector<CursusValidator*>(tmp);
	for (int i = 0; i < tmp; ++i)
		x.Validators[i] = (CursusValidator::true_UnSerialize(str));
	return str;
}