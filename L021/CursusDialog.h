#pragma once
#include <qobject.h>
#include <qdialog.h>
#include <qscrollarea.h>
#include "ui_cursus_dialog.h"
#include "Cursus.h"
#include "ValidatorDialog.h"
#include <vector>
#include <QSpinBox>
#include <qbuffer.h>

class CursusDialog :
	public QDialog,
	public Ui::cursus_dialog

{
	Q_OBJECT

	Cursus dst;
	CursusDialog(QWidget* parent);
	~CursusDialog(){}
	void ListUpdated();

public:
	static Cursus& ShowDialog(Cursus& src, QWidget* parent = nullptr);
	static Cursus ShowDialog(QWidget* parent = nullptr);


	private slots:
	void AjouterValidator();
	void SupprimerValidator();
	void EditerValidator();

};