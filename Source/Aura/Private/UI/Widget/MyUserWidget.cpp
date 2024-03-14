// copyright MGK


#include "UI/Widget/MyUserWidget.h"

void UMyUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
