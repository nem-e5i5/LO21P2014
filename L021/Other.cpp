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

UVType UVTypeFromName(QString name)
{
	if (name == "CS") return UVType::CS;
	if (name == "TM") return UVType::TM;
	if (name == "TSH") return UVType::TSH;
	if (name == "SP") return UVType::SP;
	if (name == "Mixe") return UVType::Mixe;

	return UVType::Mixe;
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

UVStatus UVStatusFromName(QString t)
{
	if (t == "A") return UVStatus::A;
	if (t == "B") return UVStatus::B;
	if (t == "C") return UVStatus::C;
	if (t == "D") return UVStatus::D;
	if (t == "E") return UVStatus::E;
	if (t == "F") return UVStatus::F;
	if (t == "FX") return UVStatus::FX;
	if (t == "RES") return UVStatus::RES;
	if (t == "ABS") return UVStatus::ABS;
	return UVStatus::EC;
}

QString SemestreStatusName(SemestreStatus t)
{
	switch (t)
	{
	case Fini:
		return "Fini";
	case SEC:
		return "En cours";
	case PL:
		return QString::fromWCharArray(L"Planifié");
	case PR:
		return QString::fromWCharArray(L"Proposé");
	default:
		return "ErreurStatus";
	}
}

SemestreStatus SemestreStatusFromName(QString x)
{
	if (x == "Fini") return SemestreStatus::Fini;
	if (x == "En cours") return SemestreStatus::SEC;
	if (x == QString::fromWCharArray(L"Planifié")) return SemestreStatus::PL;
	if (x == QString::fromWCharArray(L"Proposé")) return SemestreStatus::PR;
}