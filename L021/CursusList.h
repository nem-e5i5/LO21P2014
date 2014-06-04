#pragma once
#include <qdialog.h>
#include <ui_cursus_popup.h>
#include "Cursus.h"
class CursusList:
	public QDialog,
	public Ui::cursus_selection_dialog
{
public:
	CursusList(QWidget* parent);
	~CursusList();
	template<class src>
	//énumérateur sur liste de cursus
	static QString ShowDialog(src begin, src end, QWidget* parent = nullptr)
	{
		CursusList f(parent);
		int i = 0;
		while (begin != end)
		{
			f.tableWidget->setRowCount(i + 1);
			const Cursus& c = (*begin);
			f.tableWidget->setItem(i, 0, new QTableWidgetItem(c.getName()));
			++i;
			++begin;
		}
		int ret = f.exec();
		if (ret == 1 && f.tableWidget->selectedItems().size() > 0) return f.tableWidget->selectedItems()[0]->text();
		else return "";
	}
};

