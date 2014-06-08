#include "DossierEtCursus.h"

map<QString, const ValidatorFactory*> CursusValidator::Validators;
const Cursus Cursus::null = Cursus("null");

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
	auto iter = d.SemestreIterator();
	auto sl = Select<SemestreSuivi, unsigned int>(iter, iter.getEnd(), [=](const SemestreSuivi& x) { return x.get_nb_credit_effective(t); });
	int ag = Sum<unsigned int>(sl, sl.getEnd(), d.getNbEquivalences(t));
	return ag >= nb;
}

void Cursus::addValidator(CursusValidator* x) { Validators.push_back(x); }

void Cursus::removeValidator(CursusValidator* x) { auto y = find(Validators.begin(), Validators.end(), x);  delete *y; Validators.erase(y); }
void Cursus::removeValidatorAt(int at) { auto y = Validators.begin() + at;  delete *y; Validators.erase(y); }
SelectIterator<CursusValidator*, QString, vector<CursusValidator*>::iterator> Cursus::validatorNameList()
{
	return Select<CursusValidator*, QString>(Validators.begin(), Validators.end(), [](CursusValidator* x) { return x->getName(); });
}

IdentityIterator<CursusValidator*, vector<CursusValidator*>::iterator> Cursus::validatorList()
{
	return IdentityIterator<CursusValidator*, vector<CursusValidator*>::iterator>(Validators.begin(), Validators.end());
}

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
	Cursus::~Cursus();
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