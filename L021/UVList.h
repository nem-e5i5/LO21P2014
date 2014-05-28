#pragma once
#include <qdialog.h>
#include <qstring.h>
#include "ui_UV_popup.h"
#include "UV.hpp"
class UVList :
	public QDialog,
	public Ui::Dialog
{
public:
	UVList(QWidget* parent);
	~UVList();
	template<class src>
	//énumérateur sur liste d'uv
	static QString ShowDialog(src begin, src end, QWidget* parent = nullptr)
	{
		UVList f(parent);
		int i = 0;
		while (begin != end)
		{
			f.tableWidget->setRowCount(i + 1);
			UV c = (*begin);
			f.tableWidget->setItem(i, 0, new QTableWidgetItem(c.get_code()));
			f.tableWidget->setItem(i, 1, new QTableWidgetItem(UVTypeName(c.get_type())));
			f.tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(c.get_nb_credit(c.get_type()))));
			f.tableWidget->setItem(i, 3, new QTableWidgetItem(
				QString(c.get_automne() ? "A" : "") +
				QString(c.get_printemps() ? "P" : "")));


			++i;
			++begin;
		}
		int ret = f.exec();
		if (ret == 1) return f.tableWidget->selectedItems()[0]->text();
		else return "";
	}
};

