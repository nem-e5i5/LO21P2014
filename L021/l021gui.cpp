#include "l021gui.h"

L021GUI::L021GUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QObject::connect(ui.actionAjouter, SIGNAL(), SLOT());
}

L021GUI::~L021GUI()
{

}
