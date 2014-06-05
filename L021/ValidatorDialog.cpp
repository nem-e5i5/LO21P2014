#include "ValidatorDialog.h"

ValidatorDialog::ValidatorDialog(QWidget* parent)
{
	widget_list={};
	setupUi(this);
}
ValidatorDialog::~ValidatorDialog()
{

}
Cursus& ValidatorDialog::ShowDialog(Cursus& cr, QWidget* parent)
{
	return cr;
}
Cursus ValidatorDialog::ShowDialog(QWidget* parent)
{
	ValidatorDialog x(parent);
	QObject::connect(x.add_button, SIGNAL(clicked()), &x, SLOT(AjouterLigne()));
	int rflag = x.exec();
	if (rflag == 0)
		return Cursus::null;
	else
	{

	}
}

void ValidatorDialog::AjouterLigne() {
	QStringList combo_options = {"int", "string", "UV", "bool", "UVType", "UVStatus", "Cursus"};

	QComboBox* combo= new(QComboBox);
	combo->addItems(combo_options);
	widget_list.push_back({combo, nullptr});
	formLayout_2->setWidget(widget_list.size() -1, QFormLayout::ItemRole::LabelRole, combo);
	combo->show();
}

void ValidatorDialog::RetirerLigne() {

}
