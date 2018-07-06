#include "MyUI.h"

void MyUI::DisableExcept(BUTTON_TAG tag)
{
	switch (tag)
	{
	case Define::Cir:
	button_rect->setEnabled(false);
		button_trian->setEnabled(false);
		x_button->setEnabled(false);
		break;
	case Define::X: button_rect->setEnabled(false);
		button_trian->setEnabled(false);
		button_cir->setEnabled(false); break;
	case Define::Rectangcle:
		button_trian->setEnabled(false);
		x_button->setEnabled(false);
		button_cir->setEnabled(false);
		break;
	case Define::Tri:button_cir->setEnabled(false);
		button_rect->setEnabled(false);
		x_button->setEnabled(false);
		break;
	}

}

void MyUI::EnableAll()
{
	x_button->setEnabled(true);
	button_rect->setEnabled(true);
	button_cir->setEnabled(true);
	button_trian->setEnabled(true);
}
