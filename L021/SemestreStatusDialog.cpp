#include "SemestreStatusDialog.h"

SemestreStatusDialog::SemestreStatusDialog(QWidget* parent) : QDialog(parent)
{
	setupUi(this);
}

SemestreStatusDialog::~SemestreStatusDialog()
{
}

SemestreSuivi& SemestreStatusDialog::ShowDialog(SemestreSuivi& SS, QWidget* parent)
{
	SemestreStatusDialog x(parent);
	x.semestre_status_combo->setCurrentText(SemestreStatusName(SS.get_Status()));
	x.checkbox->setChecked(SS.get_ALEtranger());

	x.cs_spin->setValue(SS.get_Prevision(UVType::CS));
	x.tm_spin->setValue(SS.get_Prevision(UVType::TM));
	x.tsh_spin->setValue(SS.get_Prevision(UVType::TSH));
	x.sp_spin->setValue(SS.get_Prevision(UVType::SP));

	int rflag = x.exec();
	if (rflag == 1)
	{
		SS.set_Status(SemestreStatusFromName(
			x.semestre_status_combo->currentText()));
		SS.set_ALEtranger(x.checkbox->isChecked());

		SS.set_Prevision(UVType::CS, x.cs_spin->value());
		SS.set_Prevision(UVType::TM, x.tm_spin->value());
		SS.set_Prevision(UVType::TSH, x.tsh_spin->value());
		SS.set_Prevision(UVType::SP, x.sp_spin->value());
	}
	return SS;
}