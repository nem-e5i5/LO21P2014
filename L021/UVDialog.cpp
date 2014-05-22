#include "UVDialog.h"


UVDialog::UVDialog(QWidget* parent) : QDialog(parent)
{
	setupUi(this);
}


UVDialog::~UVDialog()
{
}


// Affiche une boîte de dialogue avec les informations de l'UV passé en paramètre, cette UV est édité par l'utilisateur. Retourne la référence passé en paramètre
UV& UVDialog::ShowDialog(UV& Uv, QWidget* parent)
{
	UVDialog x(parent);
	x.lineEdit->setEnabled(false);
	x.lineEdit->setText(Uv.get_code());
	x.textEdit->setText(Uv.get_titre());
	x.spinBox->setValue(Uv.get_nb_credit(Uv.get_type()));
	x.comboBox->setCurrentIndex(static_cast<int>(Uv.get_type()));
	x.checkBox->setChecked(Uv.get_printemps());
	x.checkBox_2->setChecked(Uv.get_automne());

	int rflag = x.exec();
	if (rflag == 1)
	{
		Uv = UV(
			Uv.get_code(),
			x.textEdit->toPlainText(),
			static_cast<UVType>(x.comboBox->currentIndex()),
			x.spinBox->value(),
			x.checkBox_2->isChecked(),
			x.checkBox->isChecked()
		);
	}
	return Uv;
}

UV UVDialog::ShowDialog(QWidget* parent)
{
	UVDialog x(parent);
	int rflag = x.exec();
	if (rflag == 0)
		return UV::null;
	else
		//TODO: faire une construction propre
		return UV(
			x.lineEdit->text(),
			x.textEdit->toPlainText(),
			static_cast<UVType>(x.comboBox->currentIndex()),
			x.spinBox->value(),
			x.checkBox_2->isChecked(),
			x.checkBox->isChecked()
		);
}
