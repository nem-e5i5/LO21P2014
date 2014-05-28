#include "l021gui.h"

L021GUI::L021GUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QObject::connect(ui.actionAjouter, SIGNAL(triggered()), this, SLOT(AddUv()));
	QObject::connect(ui.actionModifier, SIGNAL(triggered()), this, SLOT(EditUv()));
}

L021GUI::~L021GUI()
{

}

void L021GUI::AddUv()
{
	UV x = UVDialog::ShowDialog();
	UTProfiler::GetInstance()->UVrefByName(x.get_code()) = x;
	Notify(L"UV ajout� avec succ�s");
}

void L021GUI::EditUv()
{
	//TODO: selectionneur d'UV
	auto iter = UTProfiler::GetInstance()->UVIterator();
	QString t = UVList::ShowDialog(iter, iter.getEnd());
	if (t != "")
	{
		UV& x = UTProfiler::GetInstance()->UVrefByName(t);
		UVDialog::ShowDialog(x);
	}
}