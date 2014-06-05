#include "ValidatorDialog.h"

ValidatorDialog::ValidatorDialog(QWidget* parent)
{
	widget_list={};
	setupUi(this);
}
ValidatorDialog::~ValidatorDialog()
{

}
/*Cursus& ValidatorDialog::ShowDialog(Cursus& cr, QWidget* parent)
{
	return cr;
}
Cursus ValidatorDialog::ShowDialog(QWidget* parent)
{
	ValidatorDialog x(parent);
	int rflag = x.exec();
	if (rflag == 0)
		return Cursus::null;
	else
	{

	}
}*/

void ValidatorDialog::AjouterLigne() {
	static const QStringList combo_options = {"int", "string", "UV", "bool", "UVType", "UVStatus", "Cursus"};

	QComboBox* combo= new(QComboBox);
	combo->addItems(combo_options);
	widget_list.push_back({combo, nullptr});
	formLayout_2->setWidget(widget_list.size() -1, QFormLayout::ItemRole::LabelRole, combo);
	combo->show();
	QObject::connect(combo, SIGNAL(currentTextChanged(QString)), this, SLOT(ComboChanged(QString)));
}

void ValidatorDialog::ComboChanged(QString s) {
	QObject* sender=QObject::sender();
	for (int i=0; i<widget_list.size(); i++) {
		if (widget_list[i][0]==sender) {
			delete(widget_list[i][1]);
			// remove from form_layout2
			if (s=="int") {
				widget_list[i][1]= new QSpinBox;
				formLayout_2->setWidget(i, QFormLayout::ItemRole::FieldRole, widget_list[i][1]);
				widget_list[i][1]->show();
			}

			return;
		}
	}
}

void ValidatorDialog::RetirerLigne() {

}
