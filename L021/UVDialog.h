#pragma once
#include <qdialog.h>
#include "ui_AddUV.h"
#include "UV.hpp"
class UVDialog :
	public Ui::DialogUV,
	public QDialog
{
public:
	UVDialog(QWidget* parent);
	~UVDialog();
	// Affiche une boîte de dialogue avec les informations de l'UV passé en paramètre, cette UV est édité par l'utilisateur. Retourne la référence passé en paramètre
	static UV& ShowDialog(UV& Uv, QWidget* parent = nullptr);
	static UV ShowDialog(QWidget* parent = nullptr);
};

