#include "DossierEtCursus.h"

// UV //
const UV UV::null = UV();

UV::UV() : _is_null(true) { }
UV::UV(const QString code, const QString titre, const UVType type, const unsigned int n, const bool a, const bool p) : _is_null(false) {
	_code=code;
	_titre=titre;
	for (auto& x : _nb_credit) x = 0;
	_nb_credit[type]=n;
	_automne=a;
	_printemps=p;
}
// get
QString UV::get_code () const {
	return _code;
}
QString UV::get_titre () const {
	return _titre;
}
UVType UV::get_type() const 
{
	int j = 0;
	for (int i = 0; i < UVType::size; ++i)
	{
		if (_nb_credit[i] > 0) 
			if (j == 0) j = i;
			else j = UVType::Mixe;
	}
	return static_cast<UVType>(j);
}
unsigned int UV::get_nb_credit (const UVType t) const {
	if (t < UVType::size)
		return _nb_credit[t];
	return Sum<int>(&_nb_credit[0], &_nb_credit[UVType::size], 0);
}
bool UV::get_automne () const {
	return _automne;
}
bool UV::get_printemps () const {
	return _printemps;
}
bool UV::isnull() const {
	return _is_null;
}

// set
void UV::set_code (const QString code) {
	_code=code;
}
void UV::set_titre (const QString titre) {
	_titre=titre;
}
void UV::set_nb_credit (const UVType t, const unsigned int n) {
	_nb_credit[t]=n;
}
void UV::set_automne (const bool a) {
	_automne=a;
}
void UV::set_printemps (const bool p) {
	_printemps=p;
}

// UVEncours //
UVEncours::UVEncours(QString uv, const UVStatus s) {
	_uv = uv;
	_status=s;
}
UVStatus UVEncours::get_status() const {
	return _status;
}
void UVEncours::set_status(const UVStatus s) {
	_status=s;
}

const UV& UVEncours::get_uv() const { return UTProfiler::GetInstance()->UVrefByName(_uv); }

QDataStream& operator<<(QDataStream& str, const UV& x)
{
	str << x.get_code()
		<< x.get_titre();
	for (auto n : x._nb_credit) str << n;
	str	<< x.get_automne()
		<< x.get_printemps()
		<< x.isnull();
	return str;
}
QDataStream& operator>>(QDataStream& str, UV& x)
{
	str >> x._code
		>> x._titre;
	for (auto& n : x._nb_credit) str >> n;
	str	>> x._automne
		>> x._printemps
		>> x._is_null;
	return str;
}

QDataStream& operator<<(QDataStream& str, const UVEncours& x)
{
	str << x.get_uv().get_code();
	str << static_cast<int>(x.get_status());
	return str;
}
QDataStream& operator>>(QDataStream& str, UVEncours& x)
{
	int tmp2;
	str >> x._uv >> tmp2;

	x.set_status(static_cast<UVStatus>(tmp2));
	return str;
}
