#pragma once
#include <qdialog.h>
#include <qstring.h>
#include "ui_UV_popup.h"
#include "UV.hpp"
class UVList :
	public QDialog,
	public Ui::Dialog
{
public:
	UVList(QWidget* parent);
	~UVList();
	template<class src>
	//énumérateur sur liste d'uv
	static QString ShowDialog(QWidget* parent, src begin, src end);
};

