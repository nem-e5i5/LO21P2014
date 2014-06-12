#include "CursusDialog.h"

CursusDialog::CursusDialog(QWidget* parent) : QDialog(parent)
{
	setupUi(this);
	QObject::connect(add_validator_button, SIGNAL(clicked()), this, SLOT(AjouterValidator()));
	QObject::connect(remove_validator_button, SIGNAL(clicked()), this, SLOT(SupprimerValidator()));
	QObject::connect(modify_validator_button, SIGNAL(clicked()), this, SLOT(EditerValidator()));
}

Cursus& CursusDialog::ShowDialog(Cursus& src, QWidget* parent)
{
	CursusDialog x(parent);
	x.dst = src;
	x.cursusName_edit->setText(src.getName());
	x.cursusName_edit->setEnabled(false);
	x.ListUpdated();
	int rflag = x.exec();
	if (rflag == 0) Notify(L"Modifications annulées");
	else
	{
		src = x.dst;
		//src.Rename(x.cursusName_edit->text());
	}
	return src;
}

Cursus CursusDialog::ShowDialog(QWidget* parent)
{
	CursusDialog x(parent);
	int rflag = x.exec();
	if (rflag == 0) return Cursus::null;
	else 
	{
		x.dst.Rename(x.cursusName_edit->text());
		return x.dst;
	}
}

void CursusDialog::EditerValidator()
{
	//TODO
}

void CursusDialog::SupprimerValidator()
{
	if (validator_list->selectedItems().size() > 0)
	{
		int toremove = validator_list->selectedItems().at(0)->row();
		dst.removeValidatorAt(toremove);
		ListUpdated();
	}
	else Notify(L"Vous devez sélectionner un validateur");
}

void CursusDialog::AjouterValidator()
{
	auto* x = ValidatorDialog::ShowDialog();
	if (x != nullptr)
	{
		dst.addValidator(x);
		ListUpdated();
	}
	else Notify(L"Action annulée");
}

void CursusDialog::ListUpdated()
{
	this->validator_list->clearContents();
	int i = 0;
	auto iter = dst.validatorList();
	for (; !iter.ended(); ++iter)
	{
		auto item = *iter;
		validator_list->setRowCount(i + 1);
		validator_list->setItem(i, 0, new QTableWidgetItem(item->Prety_print()));
		++i;
	}
}