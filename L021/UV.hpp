#ifndef UV_HPP
#define UV_HPP

#include "Other.hpp"

class UV {
	private:
		QString _code;
		QString _titre;
		UVType _type;
		unsigned int _nb_credit;
		bool _automne;
		bool _printemps;
		bool _is_null;
		
	public:
		static const UV null;
		UV();
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

class UVEncours: public UV {
	private:
		UVStatus _status;
	public:
		UVEncours(const QString code, const QString titre, const UVType type, const unsigned int n, const bool a, const bool p, const UVStatus s);
		UVStatus get_status() const;
		void set_status(const UVStatus s);
};

#endif // UV_HPP
