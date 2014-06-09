#include "l021gui.h"

void L021GUI::AutoComplete()
{
	UTProfiler::GetInstance()->AutoComplete();
	CursusList_DossierChanged();
	UVList_DossierChanged();
}