#include "ValidatorDialog.h"

ValidatorDialog::ValidatorDialog(QWidget* parent)
{
	setupUi(this);
}
ValidatorDialog::~ValidatorDialog()
{

}
static Cursus& ShowDialog(Cursus& cr, QWidget* parent = nullptr)
{

}
static Cursus ShowDialog(QWidget* parent = nullptr)
{
	ValidatorDialog x(parent);
	int rflag = x.exec();
	if (rflag == 0)
		return Cursus::null;
	else
	{

	}
}

void ValidatorDialog::AjouterLigne()
{

}
void ValidatorDialog::RetirerLigne()
{

}