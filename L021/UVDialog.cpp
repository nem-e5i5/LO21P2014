#include "UVDialog.h"


UVDialog::UVDialog(QWidget* parent) : QDialog(parent)
{
	setupUi(this);
}


UVDialog::~UVDialog()
{
}


// Affiche une bo�te de dialogue avec les informations de l'UV pass� en param�tre, cette UV est �dit� par l'utilisateur. Retourne la r�f�rence pass� en param�tre
UV& UVDialog::ShowDialog(UV& Uv, QWidget* parent)
{
	UVDialog x = UVDialog(parent);
	//TODO: faire une initialisation propre de la gui
	int rflag = x.exec();
	if (rflag == 1)
	{
		//TODO: routine de mise � jour
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
