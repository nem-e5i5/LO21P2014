#pragma once
#include <functional>
#include <vector>
#include "AllUtility.h"
#include "UTProfiler.h"

using namespace std;

class Dossier;

typedef function<bool(const Dossier, const char*)> predicate;

class CursusValidator {
	static int current;
	int TypeCode;

public:
	CursusValidator() : TypeCode(current++){}
	virtual bool Validate(Dossier d) = 0;

	int GetTypeCode() const { return TypeCode; }
};

struct CreditValidator : public CursusValidator
{
	bool Validate(Dossier d){  }
};

class Cursus
{
	vector<CursusValidator> Validators;
public:
	template <class T> //T: CursusValidator
	int addValidator(T x);
	void removeValidator(int Id);

	bool Validate(Dossier d);
	Cursus();
	~Cursus();
};
