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
	AddUVDialog::ShowDialog();
}

void L021GUI::EditUv()
{
	//TODO: selectionneur d'UV
	UV x = UV::null;
	EditUVDialog::ShowDialog(x);
}