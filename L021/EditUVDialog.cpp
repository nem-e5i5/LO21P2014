#include "EditUVDialog.h"


EditUVDialog::EditUVDialog(QWidget* parent) : QDialog(parent)
{
	setupUi(this);
}


EditUVDialog::~EditUVDialog()
{
}


// Affiche une bo�te de dialogue avec les informations de l'UV pass� en param�tre, cette UV est �dit� par l'utilisateur. Retourne la r�f�rence pass� en param�tre
UV& EditUVDialog::ShowDialog(UV& Uv, QWidget* parent)
{
	EditUVDialog x = EditUVDialog(parent);
	//TODO: faire une initialisation propre de la gui
	int rflag = x.exec();
	if (rflag == 1)
	{
		//TODO: routine de mise � jour
	}
	return Uv;
}
