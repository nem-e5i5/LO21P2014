#include "DossierEtCursus.h"

map<QString, const ValidatorFactory*> CursusValidator::Validators;
const Cursus Cursus::null = Cursus("null");

CursusValidator* CursusValidator::true_UnSerialize(QDataStream& str)
//! Decode un Validator depuis un QDataStream.
{
	QString t;
	str >> t;
	//Yaaay pas d'erreur
	CursusValidator* ret = Validators[t]->proceed();
	ret->UnSerialize(str);
	return ret;
}

void Cursus::addValidator(CursusValidator* x) { Validators.push_back(x); }

void Cursus::removeValidator(CursusValidator* x) { auto y = find(Validators.begin(), Validators.end(), x);  delete *y; Validators.erase(y); }
void Cursus::removeValidatorAt(int at) { auto y = Validators.begin() + at;  delete *y; Validators.erase(y); }
SelectIterator<CursusValidator*, QString, vector<CursusValidator*>::iterator> Cursus::validatorNameList()
//! Retourne la liste des noms des Validator du Cursus.
{
	return Select<CursusValidator*, QString>(Validators.begin(), Validators.end(), [](CursusValidator* x) { return x->getName(); });
}

IdentityIterator<CursusValidator*, vector<CursusValidator*>::iterator> Cursus::validatorList()
//! Retourne la liste des Validator.
{
	return IdentityIterator<CursusValidator*, vector<CursusValidator*>::iterator>(Validators.begin(), Validators.end());
}

bool Cursus::Validate(Dossier d) const
//! Retourne true si le Cursus est validé (tout les Validator sont validés), false sinon.
{
	for (auto& v : Validators)
	if (!v->Validate(d)) return false;
	return true;
}

bool Cursus::MayValidate(Dossier d) const
//! Retourne true si le Cursus peut etre validé si toutes les UV en cours sont validés, false sinon.
{
	for (auto& v : Validators)
	if (!v->MayValidate(d)) return false;
	return true;
}

bool Cursus::Improve(Dossier d, UV u) const
//! Retourne true si l'UV améliore le cursus, false sinon.
{
	for (auto& v : Validators) 
	if (v->Improve(d, u) && !v->MayValidate(d)) return true;
	return false;
}

bool Cursus::MayValidateImprovable(Dossier d) const
//! Retourne true si les Cursus pouvant etre validés sont améliorés, false sinon.
{
	for (auto& v : Validators)
	if (v->MayValidate(d) || !v->Improvable()) return true;
	return false;
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
//! Transforme un Cursus en un flux de donnée dans le QDataStream.
{
	str << x.getName();
	str << x.Validators.size();
	for (auto v : x.Validators)
		v->true_Serialize(str);
	return str;
}
QDataStream& operator>>(QDataStream& str, Cursus& x)
//! Transfert un flux de donnée dans le QDataStream vers un Cursus.
{
	int tmp;
	str >> x.Name;
	str >> tmp;
	x.Validators = vector<CursusValidator*>(tmp);
	for (int i = 0; i < tmp; ++i)
		x.Validators[i] = (CursusValidator::true_UnSerialize(str));
	return str;
}