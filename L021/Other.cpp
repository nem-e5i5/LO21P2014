#include "Other.hpp"

QString UVTypeName(UVType t)
/**
 * Retourne le nom de l'UVType 
 */
{
	switch (t)
	{
	case UVType::CS: return "CS";
	case UVType::TM: return "TM";
	case UVType::TSH: return "TSH";
	case UVType::SP: return "SP";
	case UVType::Mixe: return "Mixe";
	}
	return "ErreurTypename";
}

QString UVStatusName(UVStatus t)
/**
 * Retourne le nom de l'UVStatus
 */
{
	switch (t)
	{
	case A:
		return "A";
	case B:
		return "B";
	case C:
		return "C";
	case D:
		return "D";
	case E:
		return "E";
	case F:
		return "F";
	case FX:
		return "FX";
	case RES:
		return "RES";
	case ABS:
		return "ABS";
	case EC:
		return "EC";
	}
	return "ErreurStatus";
}