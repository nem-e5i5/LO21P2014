#pragma once
#include <qdialog.h>
#include "ui_AddUV.h"
#include "UV.hpp"
class UVDialog :
	public Ui::DialogUV,
	QDialog
{
public:
	UVDialog(QWidget* parent);
	~UVDialog();
	// Affiche une bo�te de dialogue avec les informations de l'UV pass� en param�tre, cette UV est �dit� par l'utilisateur. Retourne la r�f�rence pass� en param�tre
	static UV& ShowDialog(UV& Uv, QWidget* parent = nullptr);
	static UV ShowDialog(QWidget* parent = nullptr);
};

