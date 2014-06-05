#include "ValidatorDialog.h"

ValidatorDialog::ValidatorDialog(QWidget* parent)
{
	widget_list={};
	setupUi(this);
	QObject::connect(add_button, SIGNAL(clicked()), this, SLOT(AjouterLigne()));
}
ValidatorDialog::~ValidatorDialog()
{

}
/*static Cursus& ShowDialog(Cursus& cr, QWidget* parent = nullptr)
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
<<<<<<< HEAD
}*/

void ValidatorDialog::AjouterLigne() {
	QStringList combo_options = {"int", "string", "UV", "bool", "UVType", "UVStatus", "Cursus"};

	QComboBox* combo= new(QComboBox);
	combo->addItems(combo_options);
	widget_list.push_back({combo, nullptr});
	formLayout_2->setWidget(0, QFormLayout::ItemRole::LabelRole, combo);
	combo->show();
}

void ValidatorDialog::RetirerLigne() {

}
=======
}

void ValidatorDialog::AjouterLigne()
{

}
void ValidatorDialog::RetirerLigne()
{

}
>>>>>>> 5af6803e667d32e9a2d2ce7e627face99a3ea3a4
