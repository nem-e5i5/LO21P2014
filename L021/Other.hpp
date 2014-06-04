#pragma once

#include <QString>

class UTException {
	private:
		QString _info;
	public:
		UTException(const QString& info){
			_info=info;
		}
		QString get_info() const {
			return _info;
		}
};

enum UVType {CS, TM, TSH, SP, size=4, Mixe};
QString UVTypeName(UVType t);
UVType UVTypeFromName(QString name);
enum UVStatus {A, B, C, D, E, F, FX, RES, ABS, EC};
QString UVStatusName(UVStatus t);
enum Semestre : bool { Printemps, Automne };
//Fini, En cours, Planifié, Proposé
enum SemestreStatus { Fini, SEC, PL, PR };
QString SemestreStatusName(SemestreStatus t);