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

// UVList //
/*
template <typename T>
void UVList<T>::add (T* uv) {
	_uv_list.push_back(uv);
}

template <typename F>
void UVList<T>::removeWhere (F selector) {
	auto x = get_iterator();
	x.nextWhere(selector);
	_uv_list.erase(x.get_current());
}

template <typename T, typename F>
T* UVList<T>::getWhere (F selector) {
	return *(search_UV(code));
}*/
