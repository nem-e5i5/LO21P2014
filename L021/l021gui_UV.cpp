#include "l021gui.h"

void L021GUI::AddUv()
{
	UV x = UVDialog::ShowDialog();
	if (!x.isnull())
	{
		UTProfiler::GetInstance()->UVrefByName(x.get_code()) = x;
		UVListChanged();
		UVList_DossierChanged();
		Notify(L"UV ajouté avec succès");
	}
	else Notify(L"Action annulée");
}

void L021GUI::EditUv()
{
	if (ui.tableWidget->selectedItems().size() > 0)
	{
		QString t = ui.tableWidget->selectedItems()[0]->text();
		UV& x = UTProfiler::GetInstance()->UVrefByName(t);
		UVDialog::ShowDialog(x);
		UVListChanged();
		UVList_DossierChanged();
	}
	else Notify(L"Pas d'uv choisie");
}

void L021GUI::RemoveUV()
{
	if (ui.tableWidget->selectedItems().size() > 0)
	{
		QString t = ui.tableWidget->selectedItems()[0]->text();
		UV& x = UTProfiler::GetInstance()->UVrefByName(t);
		UTProfiler::GetInstance()->RemoveUV(t);
		UVListChanged();
		UVList_DossierChanged();
	}
	else Notify(L"Pas d'uv choisie");
}

void L021GUI::UVListChanged()
{
	auto iter = UTProfiler::GetInstance()->UVIterator();
	ui.tableWidget->clearContents();
	int i = 0;
	for (; !iter.ended(); ++iter)
	{
		ui.tableWidget->setRowCount(i + 1);
		ui.tableWidget->setItem(i, 0, new QTableWidgetItem((*iter).get_code()));
		ui.tableWidget->setItem(i, 1, new QTableWidgetItem(UVTypeName((*iter).get_type())));
		ui.tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number((*iter).get_nb_credit((*iter).get_type()))));
		ui.tableWidget->setItem(i, 3, new QTableWidgetItem((*iter).get_titre()));
		++i;
	}
}