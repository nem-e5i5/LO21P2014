#pragma once
#include <functional>
#include <vector>
#include "AllUtility.h"
//#include "UTProfiler.h"
#include "UV.hpp"
#include <qdatastream.h>
#include <qstring.h>

using namespace std;

#define define_validator(name) \
	struct name##Validator : public CursusValidator{ \
		name##Validator() : CursusValidator(){}\
		QString getName() const { return #name; } \
			struct name##ValidatorFactory : public ValidatorFactory{ \
				name##Validator* proceed() const { return new name##Validator(); }\
				CursusValidator* proceed(const CursusValidator& x) const { return new name##Validator(dynamic_cast<const name##Validator&>(x)); }\
			}; \
	
#define register_validator(name) CursusValidator::Validators[#name] = new name##Validator::##name##ValidatorFactory()

class Dossier;


class ValidatorFactory;
class CursusValidator {
protected:
	virtual void Serialize(QDataStream&) const = 0;
	virtual void UnSerialize(QDataStream&) = 0;
	
public:
	//UTILISER EXCLUSIVEMENT AVEC declare/define_validator
	//on fait pas de ménage mémoire car cela est fait pour durer pendant toute l'execution
	static map<QString, const ValidatorFactory*> Validators;

	virtual QString getName() const = 0;
	virtual QString Prety_print() { return getName(); }
	CursusValidator() {}
	virtual bool Validate(Dossier d) const = 0;
	virtual bool MayValidate(Dossier d) const = 0;
	virtual bool Improve(Dossier d, UV u) const = 0;

	virtual bool Improvable() const { return true; }

	void true_Serialize(QDataStream& str) { str << getName(); Serialize(str); }
	
	//Cette fonction créer un CursusValidator* à l'aide d'une abstract factory, à vous de libérer la mémoire après usage
	static CursusValidator* true_UnSerialize(QDataStream& str);

	virtual ~CursusValidator() {}
}; 
class ValidatorFactory /* abstract factory*/ {
public:
	virtual CursusValidator* proceed() const = 0;
	virtual CursusValidator* proceed(const CursusValidator& x) const = 0;
};

class Cursus
{
	friend QDataStream& operator<<(QDataStream&, const Cursus&);
	friend QDataStream& operator>>(QDataStream&, Cursus&);

	QString Name;
	vector<CursusValidator*> Validators;
public:
	static const Cursus null;
	//Utiliser new, le pointeur sera géré par l'objet lui même, pas de delete après
	void addValidator(CursusValidator* x);
	void removeValidator(CursusValidator* x);
	void removeValidatorAt(int at);

	SelectIterator<CursusValidator*, QString, vector<CursusValidator*>::iterator> validatorNameList();
	IdentityIterator<CursusValidator*, vector<CursusValidator*>::iterator> validatorList();

	QString getName() const { return Name; }
	void Rename(QString x) { Name = x; }

	bool Validate(Dossier d) const;
	bool MayValidate(Dossier d) const;
	bool Improve(Dossier d, UV u) const;
	bool MayValidateImprovable(Dossier d) const;

	Cursus() : Cursus(""){}
	Cursus(const Cursus&);
	const Cursus& operator=(const Cursus&);
	Cursus(QString name);
	~Cursus();

	bool operator==(const Cursus& o) const { return Name == o.Name; }
};

QDataStream& operator<<(QDataStream&, const Cursus&);
QDataStream& operator>>(QDataStream&, Cursus&);
