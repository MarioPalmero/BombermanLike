// - Mario Palmero [2017], zlib/libpng licensed.

#include "UI/Widgets/Public/MenuUserWidget.h"
#include "../Public/MenuUserWidget.h"

AUIPlayerController * UMenuUserWidget::GetUIPlayerController()
{
	return m_UIController;
}

void UMenuUserWidget::SetUIPlayerController(AUIPlayerController * controller)
{
	m_UIController = controller;
}
