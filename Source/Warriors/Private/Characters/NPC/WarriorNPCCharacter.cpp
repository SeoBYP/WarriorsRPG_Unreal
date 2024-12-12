// Vince Petrelli All Rights Reserved


#include "Characters/NPC/WarriorNPCCharacter.h"
#include "Components/Dialogue/NPCDialogueComponent.h"
#include "WarriorDebugHelper.h"
#include "Components/Interaction/InteractableComponent.h"
#include "Components/Quest/QuestGiverComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AWarriorNPCCharacter::AWarriorNPCCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	NPCDialogueComponent = CreateDefaultSubobject<UNPCDialogueComponent>(TEXT("NPCDialogueComponent"));
	QuestGiverComponent = CreateDefaultSubobject<UQuestGiverComponent>(TEXT("QuestGiverComponent"));

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("InteractableComponent"));
	InteractableComponent->SetupAttachment(GetMesh());
}

void AWarriorNPCCharacter::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = PropertyChangedEvent.GetPropertyName();
	UE_LOG(LogTemp, Warning, TEXT("Property Changed: %s"), *PropertyName.ToString());

	if (PropertyName == "RowName")
	{
		UE_LOG(LogTemp, Warning, TEXT("Calling UpdateNPCProperties from PostEditChangeProperty"));
		UpdateNPCProperties();
	}
}


void AWarriorNPCCharacter::UpdateNPCProperties()
{
	UE_LOG(LogTemp, Warning, TEXT("UpdateNPCProperties called"));  // 함수 호출 여부 확인

	if (NPCDataTableRowHandle.DataTable == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("NPCDataTableRowHandle's DataTable is null!"));
		return;
	}

	// 데이터 테이블에서 NPC 데이터 가져오기
	FNPCDataTable* NPCData = NPCDataTableRowHandle.GetRow<FNPCDataTable>(TEXT("Invalid Row Name"));
	if (NPCData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Row with name %s not found in NPCDataTable."), *NPCDataTableRowHandle.RowName.ToString());
		return;
	}

	NPCDataTable = *NPCData;
	// 데이터 테이블의 값을 속성에 할당
	// NPCID = NPCData->ID;
	// NPCName = NPCData->Name;
	// NPCType = NPCData->NPCType;
	// NPCSubType = NPCData->NPCSubType;

	UE_LOG(LogTemp, Warning, TEXT("NPC Properties updated: ID = %s, Name = %s"), *NPCDataTable.ID, *NPCDataTable.Name.ToString());
}