#include "UV.hpp"

// UV //

UV::UV(const QString code, const QString titre, const UVType type, const unsigned int n, const bool a, const bool p) {
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

std::vector<UV*>::iterator UVList::search_UV(const QString& code) {
	std::vector<UV*>::iterator i = _uv_list.begin();
	bool found=false;
	while (found==false && i!=_uv_list.end()) {
		if (code == (*i)->get_code()) {
			found=true;
		}
		else {
			i+=1;
		}
	}
	if (found==true) {
		return i;
	}
	else {
		throw(UTException("search_UV("+code+") : not found"));
	}
}
void UVList::add_UV (UV* uv) {
	_uv_list.push_back(uv);
}
void UVList::remove_UV (const QString& code) {
	_uv_list.erase(search_UV(code));
}
UV* UVList::get_UV (const QString& code) {
	return *(search_UV(code));
}
