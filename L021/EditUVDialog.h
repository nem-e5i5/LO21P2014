#pragma once
#include "ui_AddUV.h"
#include "UV.h"
class EditUVDialog :
	public Ui::DialogUV
{
public:
	EditUVDialog();
	~EditUVDialog();
	// Affiche une boîte de dialogue avec les informations de l'UV passé en paramètre, cette UV est édité par l'utilisateur. Retourne la référence passé en paramètre
	static UV& ShowDialog(UV& Uv);
};

