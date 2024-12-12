// Vince Petrelli All Rights Reserved


#include "Systems/WidgetSubSystem.h"

#include "WarriorDebugHelper.h"
#include "WarriorFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

void UWidgetSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UWidgetSubSystem::Deinitialize()
{
	Super::Deinitialize();
}

void UWidgetSubSystem::AddToViewPort(UUserWidget* InUserWidget, EWarriorWidgetType WidgetType)
{
	if(!ensure(InUserWidget))
	{
		Debug::LogError(TEXT("User Widget Is NULL"));
		return;
	}
	if(DisplayingWidgets.Contains(InUserWidget))
	{
		Debug::Log(FString::Printf(TEXT("Added to viewport %s"),*InUserWidget->GetName()));
		return;
	}
	int ZOrder = static_cast<int>(WidgetType);
	DisplayingWidgets.AddUnique(InUserWidget);
	InUserWidget->AddToViewport(ZOrder);
	
	if(APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0))
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetHideCursorDuringCapture(true);
		PlayerController->SetInputMode(InputMode);
		PlayerController->SetIgnoreLookInput(false);
		PlayerController->SetShowMouseCursor(true);
	}
}

void UWidgetSubSystem::RemoveFromViewPort(UUserWidget* InUserWidget)
{
	if(!ensure(InUserWidget))
	{
		Debug::LogError(TEXT("User Widget Is NULL"));
		return;
	}
	if(!DisplayingWidgets.Contains(InUserWidget))
	{
		Debug::Log(FString::Printf(TEXT("Non Added to viewport %s"),*InUserWidget->GetName()));
		return;
	}
	
	InUserWidget->RemoveFromParent();
	DisplayingWidgets.Remove(InUserWidget);

	if(DisplayingWidgets.IsEmpty())
	{
		if(APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0))
		{
			FInputModeGameOnly InputMode;
			PlayerController->SetInputMode(InputMode);
			PlayerController->SetShowMouseCursor(false);
		}
	}
}

bool UWidgetSubSystem::IsDisplayingWidget(UUserWidget* InUserWidget)
{
	if(!ensure(InUserWidget))
	{
		Debug::LogError(TEXT("User Widget Is NULL"));
		return false;
	}
	return DisplayingWidgets.Contains(InUserWidget);
}
