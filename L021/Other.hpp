#ifndef UTEXCEPTION_HPP
#define UTEXCEPTION_HPP

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

enum UVType {CS, TM, TSH, SP, size=4};
enum UVStatus {A, B, C, D, E, F, FX, RES, ABS, EC};

#endif // UTEXCEPTION_HPP
