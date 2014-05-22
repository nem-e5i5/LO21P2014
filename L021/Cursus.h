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
		CreditValidator() : CursusValidator(){}\
		QString getName() { return #name; } \
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

	virtual QString getName() = 0;
	CursusValidator() {}
	virtual bool Validate(Dossier d) const = 0;

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

 
define_validator(Credit)
	UVType t;
	int nb;

	CreditValidator(UVType _t, int nbr) : CursusValidator(), t(_t), nb(nbr) {}

	bool Validate(Dossier d) const;

	void Serialize(QDataStream& str) const
	{
		str << static_cast<int>(t)
			<< nb;
	}

	void UnSerialize(QDataStream& str)
	{
		int tmp;
		str >> tmp;
		t = static_cast<UVType>(tmp);
		str >> nb;
	}

};

class Cursus
{
	friend QDataStream& operator<<(QDataStream&, const Cursus&);
	friend QDataStream& operator>>(QDataStream&, Cursus&);

	QString Name;
	vector<CursusValidator*> Validators;
public:
	
	//Utiliser new, le pointeur sera géré par l'objet lui même, pas de delete après
	int addValidator(CursusValidator* x);
	void removeValidator(int Id);

	QString getName() const { return Name; }

	bool Validate(Dossier d) const;
	Cursus() : Cursus(""){}
	Cursus(const Cursus&);
	const Cursus& operator=(const Cursus&);
	Cursus(QString name);
	~Cursus();
};

QDataStream& operator<<(QDataStream&, const Cursus&);
QDataStream& operator>>(QDataStream&, Cursus&);
