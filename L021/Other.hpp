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
enum UVStatus {A, B, C, D, E, FX, F, RES, ABS, EC, Usize};
QString UVStatusName(UVStatus t);
UVStatus UVStatusFromName(QString t);
enum Semestre : bool { Printemps, Automne };
//Fini, En cours, Planifi�, Propos�
enum SemestreStatus { Fini, SEC, PL, PR, Ssize };
QString SemestreStatusName(SemestreStatus t);
SemestreStatus SemestreStatusFromName(QString);