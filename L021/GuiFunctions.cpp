#include "GuiFunctions.h"
void Notify(QString text)
{
	QMessageBox x(QMessageBox::Icon::Information, "Notification", text, QMessageBox::StandardButton::Ok);
	x.exec();
}
void Notify(const wchar_t* text) { Notify(QString::fromWCharArray(text)); }