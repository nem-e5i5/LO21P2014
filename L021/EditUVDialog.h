#pragma once
#include <qdialog.h>
#include "ui_AddUV.h"
#include "UV.hpp"
class EditUVDialog :
	public Ui::DialogUV,
	QDialog
{
public:
	EditUVDialog(QWidget* parent);
	~EditUVDialog();
	// Affiche une bo�te de dialogue avec les informations de l'UV pass� en param�tre, cette UV est �dit� par l'utilisateur. Retourne la r�f�rence pass� en param�tre
	static UV& ShowDialog(UV& Uv, QWidget* parent = nullptr);
};

