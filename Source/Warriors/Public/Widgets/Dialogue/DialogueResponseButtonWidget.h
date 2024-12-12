// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "DataTables/DialogueResponseDataTable.h"
#include "Widgets/WarriorWidgetBase.h"
#include "DialogueResponseButtonWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClickResponseButton,FText,ResponseText);

class UDialogueOverlayWidget;

UCLASS()
class WARRIORS_API UDialogueResponseButtonWidget : public UWarriorWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Response",meta=(AllowPrivateAccess="true",ExposeOnSpawn="true"))
	FText ResponseText;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Response",meta=(AllowPrivateAccess="true",ExposeOnSpawn="true"))
	UDialogueOverlayWidget* DialogueOverlayWidget;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Response",meta=(AllowPrivateAccess="true",ExposeOnSpawn="true"))
	int32 DialogueResponseArrayIndex = 0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Response",meta=(AllowPrivateAccess="true",ExposeOnSpawn="true"))
	FDialogueResponseDataTable DialogueResponse;
public:
	UPROPERTY(BlueprintCallable,BlueprintAssignable)
	FOnClickResponseButton OnClickResponseButton;

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void OnClicked();

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void OnHovered();

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void OnUnHovered();
};
