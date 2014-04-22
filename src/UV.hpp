#ifndef UV_HPP
#define UV_HPP

#include <QString>
#include <QDebug>
#include "Other.hpp"

class UV {
	private:
		QString _code;
		QString _titre;
		UVType _type;
		unsigned int _nb_credit;
		bool _automne;
		bool _printemps;
	public:
		UV(const QString code, const QString titre, const UVType type, const unsigned int n, const bool a, const bool p);
		// get
		QString get_code () const;
		QString get_titre () const;
		UVType get_type () const;
		unsigned int get_nb_credit () const;
		bool get_automne () const;
		bool get_printemps () const;
		// set
		void set_code (const QString code);
		void set_titre (const QString titre);
		void set_type (const UVType type);
		void set_nb_credit (const unsigned int n);
		void set_automne (const bool a);
		void set_printemps (const bool p);
};

class UVList {
	private:
		std::vector<UV*> _uv_list;
		std::vector<UV*>::iterator search_UV(const QString& code);
	public:
		UVList() {
			_uv_list={};
		}
		void add_UV (UV* uv);
		void remove_UV (const QString& code);
		UV* get_UV (const QString& code);

		class Iterator {
			friend class UVList;
			private:
				unsigned int _i;
				const UVList* _owner;
				Iterator(const UVList* owner) {
					_i=0;
					_owner=owner;
				}
			public:
				UV* get_current() {
					return _owner->_uv_list[_i];
				}
				void begin() {
					_i=0;
				}
				void next() {
					_i+=1;
				}
				bool end() {
					if (_i >= _owner->_uv_list.size()) {
						return true;
					}
					else {
						return false;
					}
				}
		};

		Iterator get_iterator() {
			return Iterator(this);
		}

};

#endif // UV_HPP
