#include "l021gui.h"

L021GUI::L021GUI(QWidget *parent)
: QMainWindow(parent)
{
	ui.setupUi(this);
	QObject::connect(ui.add_uv_button, SIGNAL(clicked()), this, SLOT(AddUv()));
	QObject::connect(ui.modifie_uv_button, SIGNAL(clicked()), this, SLOT(EditUv()));
	QObject::connect(ui.remove_uv_button, SIGNAL(clicked()), this, SLOT(RemoveUV()));
	UVListChanged();
}

L021GUI::~L021GUI()
{

}