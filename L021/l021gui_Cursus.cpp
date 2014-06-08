#include "l021gui.h"

void L021GUI::AddCursus()
{
	auto x = CursusDialog::ShowDialog();
	if (x == Cursus::null) Notify(L"Action annulée");
	else
	{
		UTProfiler::GetInstance()->CursusrefByName(x.getName()) = x;
		CursusListChanged();
	}
}

void L021GUI::EditCursus()
{
	if (ui.cursus_list->selectedItems().size() > 0)
	{
		QString name = ui.cursus_list->selectedItems().at(0)->text();
		Cursus c = UTProfiler::GetInstance()->CursusrefByName(name);
		CursusDialog::ShowDialog(c);
		if (name != c.getName())
		{
			UTProfiler::GetInstance()->RemoveCursus(name);
			UTProfiler::GetInstance()->CursusrefByName(c.getName()) = c;
		}
		else UTProfiler::GetInstance()->CursusrefByName(name) = c;
		CursusListChanged();
		CursusList_DossierChanged();
	}
	else Notify(L"Pas de cursus sélectionné");
}

void L021GUI::RemoveCursus()
{
	if (ui.cursus_list->selectedItems().size() > 0)
	{
		QString name = ui.cursus_list->selectedItems().at(0)->text();
		UTProfiler::GetInstance()->RemoveCursus(name);
		CursusListChanged();
		CursusList_DossierChanged();
	}
	else Notify(L"Pas de cursus sélectionné");
}

void L021GUI::CursusListChanged()
{
	ui.cursus_list->clearContents();
	auto iter = UTProfiler::GetInstance()->CursusIterator();
	for (int i = 0; !iter.ended(); ++iter)
	{
		auto item = *iter;
		ui.cursus_list->setRowCount(i + 1);
		ui.cursus_list->setItem(i, 0, new QTableWidgetItem(item.getName()));
		++i;
	}
}