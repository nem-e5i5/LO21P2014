#include "EquivDialog.h"


EquivDialog::EquivDialog(QWidget* parent) : QDialog(parent)
{
	setupUi(this);
}


EquivDialog::~EquivDialog()
{
}


void EquivDialog::ShowDialog(int* equiv, QWidget* parent)
{
	EquivDialog x(parent);
	x.cs_spin ->setValue(equiv[UVType::CS] );
	x.sp_spin ->setValue(equiv[UVType::SP] );
	x.tm_spin ->setValue(equiv[UVType::TM] );
	x.tsh_spin->setValue(equiv[UVType::TSH]);

	int rflag = x.exec();
	if (rflag == 1)
	{
		equiv[UVType::CS]  = x.cs_spin ->value();
		equiv[UVType::SP]  = x.sp_spin ->value();
		equiv[UVType::TM]  = x.tm_spin ->value();
		equiv[UVType::TSH] = x.tsh_spin->value();
	}
}