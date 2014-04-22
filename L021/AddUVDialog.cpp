#include "AddUVDialog.h"


AddUVDialog::AddUVDialog(QWidget* parent) : QDialog(parent)
{
	setupUi(this);
}


AddUVDialog::~AddUVDialog()
{
}


// Affiche une boîte de dialogue de création d'UV, retourne l'UV saisie ou bien UV::null si rien n'est saisie
UV AddUVDialog::ShowDialog(QWidget* parent)
{
	AddUVDialog x = AddUVDialog(parent);
	int rflag = x.exec();
	if (rflag == 0)
		return UV::null;
	else
		//TODO: faire une construction propre
		return UV::null;
}
