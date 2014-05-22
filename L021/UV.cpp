#include "DossierEtCursus.h"

// UV //
const UV UV::null = UV();

UV::UV() : _is_null(true) { }
UV::UV(const QString code, const QString titre, const UVType type, const unsigned int n, const bool a, const bool p) : _is_null(false) {
	_code=code;
	_titre=titre;
	_type=type;
	_nb_credit=n;
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
UVType UV::get_type () const {
	return _type;
}
unsigned int UV::get_nb_credit () const {
	return _nb_credit;
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
void UV::set_type (const UVType type) {
	_type=type;
}
void UV::set_nb_credit (const unsigned int n) {
	_nb_credit=n;
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
		<< x.get_titre()
		<< x.get_type()
		<< x.get_nb_credit()
		<< x.get_automne()
		<< x.get_printemps()
		<< x.isnull();
	return str;
}
QDataStream& operator>>(QDataStream& str, UV& x)
{
	int tmp;
	str >> x._code
		>> x._titre
		>> tmp
		>> x._nb_credit
		>> x._automne
		>> x._printemps
		>> x._is_null;
	x._type = static_cast<UVType>(tmp);
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
