#include "EditUVDialog.h"


EditUVDialog::EditUVDialog(QWidget* parent) : QDialog(parent)
{
	setupUi(this);
}


EditUVDialog::~EditUVDialog()
{
}


// Affiche une boîte de dialogue avec les informations de l'UV passé en paramètre, cette UV est édité par l'utilisateur. Retourne la référence passé en paramètre
UV& EditUVDialog::ShowDialog(UV& Uv, QWidget* parent)
{
	EditUVDialog x = EditUVDialog(parent);
	//TODO: faire une initialisation propre de la gui
	int rflag = x.exec();
	if (rflag == 1)
	{
		//TODO: routine de mise à jour
	}
	return Uv;
}
