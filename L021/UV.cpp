#include "UV.hpp"

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
UVEncours::UVEncours(UVEncours(const UV* uv, const UVStatus s) {
	_uv = uv;
	_status=s;
}
UVStatus UVEncours::get_status() const {
	return _status;
}
void UVEncours::set_status(const UVStatus s) {
	_status=s;
}
