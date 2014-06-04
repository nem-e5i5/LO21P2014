#ifndef UV_HPP
#define UV_HPP

#include "AllUtility.h"
#include <qdatastream.h>

class UV {
	friend QDataStream& operator>>(QDataStream&, UV&);
	friend QDataStream& operator<<(QDataStream&, const UV&);

	private:
		QString _code;
		QString _titre;
		unsigned int _nb_credit[UVType::size];
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
		unsigned int get_nb_credit (const UVType) const;
		bool get_automne () const;
		bool get_printemps () const;
		bool isnull() const;
		// set
		void set_code (const QString code);
		void set_titre (const QString titre);
		void set_nb_credit(const UVType type, const unsigned int n);
		void set_automne (const bool a);
		void set_printemps (const bool p);

		bool operator==(const UV& o) const;
		bool operator!=(const UV& o) const;
};

QDataStream& operator<<(QDataStream&, const UV&);
QDataStream& operator>>(QDataStream&, UV&);

class UVEncours {
	friend QDataStream& operator>>(QDataStream&, UVEncours&);

	private:
		QString _uv;
		UVStatus _status;
	public:
		UVEncours() {}
		UVEncours(QString uv, const UVStatus s);
		UVStatus get_status() const;
		void set_status(const UVStatus s);

		bool get_hasCompleted() const { return get_status() != UVStatus::F && get_status() != UVStatus::FX && get_status() != UVStatus::ABS && get_status() != UVStatus::RES && get_status() != UVStatus::EC; }

		const UV& get_uv() const;

		bool operator==(const UVEncours& o) const;
		bool operator!=(const UVEncours& o) const;
};
QDataStream& operator<<(QDataStream&, const UVEncours&);
QDataStream& operator>>(QDataStream&, UVEncours&);

#endif // UV_HPP
