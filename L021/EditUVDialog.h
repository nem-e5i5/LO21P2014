#pragma once
#include "ui_AddUV.h"
#include "UV.h"
class EditUVDialog :
	public Ui::DialogUV
{
public:
	EditUVDialog();
	~EditUVDialog();
	// Affiche une bo�te de dialogue avec les informations de l'UV pass� en param�tre, cette UV est �dit� par l'utilisateur. Retourne la r�f�rence pass� en param�tre
	static UV& ShowDialog(UV& Uv);
};

