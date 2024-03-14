// copyright MGK


#include "UI/WidgetController/MyWidgetController.h"

void UMyWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UMyWidgetController::BroadcastInitialValues()
{
}

void UMyWidgetController::BindCallbacksToDependencies()
{
}
