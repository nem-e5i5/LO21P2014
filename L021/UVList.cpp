#include "UVList.h"


UVList::UVList(QWidget* parent) : QDialog(parent)
{
	setupUi(this);
}


UVList::~UVList()
{
}
template<class src>
static QString UVList::ShowDialog(QWidget* parent, src begin, src end)
{
	UVList f(parent);
	int i = 0;
	while(begin != end)
	{
		UV c = (*begin);
		f.tableWidget->setItem(i, 0, new QTableWidgetItem(c.get_code()));
		f.tableWidget->setItem(i, 1, new QTableWidgetItem(UVTypeName(c.get_type())));
		f.tableWidget->setItem(i, 2, new QTableWidgetItem(QString(c.get_nb_credit())));
		f.tableWidget->setItem(i, 3, new QTableWidgetItem(c.get_code()));


		++i;
		++begin;
	}
}