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
	UVDialog x = UVDialog(parent);
	//TODO: faire une initialisation propre de la gui
	int rflag = x.exec();
	if (rflag == 1)
	{
		//TODO: routine de mise à jour
	}
	return Uv;
}

UV UVDialog::ShowDialog(QWidget* parent)
{
	UVDialog x = UVDialog(parent);
	int rflag = x.exec();
	if (rflag == 0)
		return UV::null;
	else
		//TODO: faire une construction propre
		return UV::null;
}
