#include "l021gui.h"

void L021GUI::AddCursus_Dossier()
{
	
}

void L021GUI::RemoveCursus_Dossier()
{
	if (ui.dossier_cursus_list->selectedItems().size() > 0)
	{
		QString t = ui.dossier_cursus_list->selectedItems()[0]->text();
		UTProfiler::GetInstance()->getDossier().DesinscriptionCursusByName(t);
		CursusList_DossierChanged();
	}
	else Notify(L"Pas de cursus choisi");
}

void L021GUI::CursusList_DossierChanged()
{
	ui.dossier_cursus_list->clearContents();
	auto iter = UTProfiler::GetInstance()->getDossier().CursusIterator();
	
	for (int i = 0; !iter.ended(); ++iter)
	{
		ui.dossier_cursus_list->setRowCount(i + 1);
		ui.dossier_cursus_list->setItem(i, 0, new QTableWidgetItem((*iter).getName()));
		ui.dossier_cursus_list->setItem(i, 1, new QTableWidgetItem((*iter).Validate(UTProfiler::GetInstance()->getDossier()) ? "Oui": "Non"));
		++i;
	}
}