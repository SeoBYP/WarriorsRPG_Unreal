// Vince Petrelli All Rights Reserved


#include "Components/Inventory/InventoryComponent.h"
#include "Characters/WarriorHeroCharacter.h"
#include "WarriorDebugHelper.h"
#include "Inventory/ItemDataTable.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Systems/SaveLoadSubSystem.h"
#include "Inventory/ItemDataTable.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(false);
	// ...
}

void UInventoryComponent::InitializeComponent()
{
	Super::InitializeComponent();

}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	LoadInventory();
	Contents.SetNum(InventorySize);
	OnUpdatedInventory.AddDynamic(this,&UInventoryComponent::SaveInventory);
}


void UInventoryComponent::RemoveItem_Implementation(int32 Index, bool RemoveWholeStack, bool IsConsumed)
{
}

void UInventoryComponent::DropItem_Implementation(FName ItemID, int32 Quantity)
{
	// DropBagInventory를 생성합니다.
	if(Quantity > 1)
	{
		if (AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(DropBagInventory.Get(),GetDropLocation(),FRotator()))
		{
			UE_LOG(LogTemp, Log, TEXT("Spawned DropBagInventory successfully!"));
			
			if(UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>(SpawnedActor->GetComponentByClass(UInventoryComponent::StaticClass())))
			{
				bool Success = false;
				int32 QuantityRemaining = 0;
				InventoryComponent->AddInventory(ItemID,Quantity,Success,QuantityRemaining);
			}
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Spawned DropBagInventory Failed!"));
		}
	}
	// 해당 아이템 데이터의 있는 클래스 액터를 생성합니다.
	else
	{
		// 로컬 변수 이름 변경
		FItemDataTable LocalItemDataTable = GetItemData(ItemID);
		if (AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(LocalItemDataTable.ItemClass.Get(),GetDropLocation(),FRotator()))
		{
			UGameInstance* GameInstance = GetWorld()->GetGameInstance();
			if(!ensure(GameInstance))
			{
				Debug::LogWarning("GameInstance is null");
				return;
			}
			USaveLoadSubSystem* SaveLoadSubSystem = GameInstance->GetSubsystem<USaveLoadSubSystem>();
			if(!ensure(SaveLoadSubSystem))
			{
				Debug::LogWarning("SaveLoadSubSystem is null");
				return;
			}
			// UClass*를 저장할 수 있도록 소프트 클래스 포인터가 아닌 UClass*를 사용
			UClass* SpawnedActorClass = SpawnedActor->GetClass();
			SaveLoadSubSystem->GetLevelSaveData()->ActorsAdded.Add(SpawnedActorClass,SpawnedActor->GetActorTransform());
			SaveLoadSubSystem->SaveLevelSaveData();
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Spawned ItemDataTable Failed!"));
		}
	}
}

void UInventoryComponent::AddInventory(FName ItemID, int32 Quantity,bool& Success, int32& QuantityRemaining)
{
	int32 LocalQuantity = Quantity;
	bool HasFailed = false;

	while (LocalQuantity > 0 && !HasFailed)
	{
		int32 Index = 0;
		bool Founded = false;
		FindSlot(ItemID,Index,Founded);
		if(Founded)
		{
			AddItemStack(Index);
			LocalQuantity--;
		}
		else
		{
			bool HasEmptySlot = false;
			GetAnyEmptySlotAvailable(HasEmptySlot,Index);
			if(!HasEmptySlot)
			{
				HasFailed = true;
				break;
			}
			bool CreateSlot = false;
			CreateNewStack(ItemID,1,CreateSlot);
			if(CreateSlot)
			{
				LocalQuantity--;
			}
			else
			{
				HasFailed = true;
				break;
			}
		}
	}
	if(!HasFailed)
	{
		if(AWarriorHeroCharacter* HeroCharacter = SafeGetOwnerPawn<AWarriorHeroCharacter>())
		{
			HeroCharacter->OnRequestObjectiveID.Broadcast(ItemID.ToString(),Quantity);
		}
	}
	OnUpdatedInventory.Broadcast();
	Success = !HasFailed;
	QuantityRemaining = LocalQuantity;
}

void UInventoryComponent::QueryInventory(FName ItemID, int32 Quantity, bool& Success, int32& OutQuantity)
{
	int RemainTotal = 0;
	for(int i = 0; i < Contents.Num(); i++)
	{
		if(ItemID != Contents[i].ItemID)
			continue;
		RemainTotal += Contents[i].Quantity;
	}
	Success = RemainTotal >= Quantity;
	OutQuantity = RemainTotal;
}


void UInventoryComponent::FindSlot(FName ItemID, int32& Index, bool& FoundSlot)
{
	for(int i = 0; i < Contents.Num(); i++)
	{
		if(Contents[i].ItemID != ItemID)
			continue;
		if(Contents[i].Quantity < GetMaxStackSize(ItemID))
		{
			Index = i;
			FoundSlot = true;
			return;
		}
	}
	Index = -1;
	FoundSlot = false;
}

void UInventoryComponent::RemoveFromInventory(int32 Index, bool RemoveWholeStack, bool IsConsumed)
{
	if(!Contents.IsValidIndex(Index))
	{
		Debug::LogWarning(FString::Printf(TEXT("%d Index is Not Valid Index"),Index));
		return;
	}
	FName ItemID = Contents[Index].ItemID;
	int32 Quantity = Contents[Index].Quantity;
	if(RemoveWholeStack || Quantity == 1)
	{
		Contents[Index] = FInventorySlotStruct{"",0};
		if(!IsConsumed) DropItem(ItemID,Quantity);
	}
	else
	{
		Contents[Index].Quantity -= 1;
		if(!IsConsumed) DropItem(ItemID,Quantity);
	}
	OnUpdatedInventory.Broadcast();
}

int32 UInventoryComponent::GetMaxStackSize(FName ItemID)
{
	// ItemDataTable이 nullptr이면 경고 출력하고 -1 반환
	if (!ensure(ItemDataTable)) 
	{
		Debug::LogWarning("ItemDataTable is null");
		return -1; 
	}
	
	// 서식 문자열을 TEXT() 매크로로 감싸서 사용
	if(FItemDataTable* Data = ItemDataTable->FindRow<FItemDataTable>(ItemID, FString::Printf(TEXT("Can't Found Row in ItemDataTable %ls"), *ItemID.ToString())))
	{
		return Data->StackSize;
	}
	return -1;
}

void UInventoryComponent::AddItemStack(int32 Index, int32 Quantity)
{
	if(Contents.IsValidIndex(Index))
	{
		Contents[Index].Quantity += Quantity;
	}
}

void UInventoryComponent::GetAnyEmptySlotAvailable(bool& HasEmptySlot, int32& EmptyIndex)
{
	for(int i = 0; i < Contents.Num(); i++)
	{
		if(Contents[i].Quantity <= 0)
		{
			EmptyIndex = i;
			HasEmptySlot = true;
			return;
		}
	}
	EmptyIndex = -1;
	HasEmptySlot = false;
}

void UInventoryComponent::CreateNewStack(FName ItemID, int32 Quantity,bool& Success)
{
	int32 EmptyIndex = 0;
	bool HasEmptySlot = false;
	GetAnyEmptySlotAvailable(HasEmptySlot,EmptyIndex);
	if(HasEmptySlot)
	{
		FInventorySlotStruct Slot{};
		Slot.ItemID = ItemID;
		Slot.Quantity = Quantity;
		Contents[EmptyIndex] = Slot;
		Success = true;
	}
	else
	{
		Success = false;
	}
}

void UInventoryComponent::ConsumeItem(int32 Index)
{
	if(!Contents.IsValidIndex(Index))
	{
		Debug::LogWarning(FString::Printf(TEXT("%d Index is Not Valid Index"),Index));
		return;
	}
	RemoveFromInventory(Index,false,true);
	OnUpdatedInventory.Broadcast();
}

void UInventoryComponent::TransferSlots(int32 SourceIndex, UInventoryComponent* SourceInventory, int32 DestinationIndex)
{
	if(!ensure(SourceInventory))
	{
		Debug::LogWarning("SourceInventory is null");
		return;
	}
	FInventorySlotStruct LocalInventorySlot = SourceInventory->Contents[SourceIndex];
	if(DestinationIndex < 0)
	{
		return;
	}
	bool isSameItem = Contents[DestinationIndex].ItemID == LocalInventorySlot.ItemID;
	if(isSameItem)
	{
		int32 Temp = LocalInventorySlot.Quantity + Contents[DestinationIndex].Quantity;
		int32 MaxQuantity = GetMaxStackSize(LocalInventorySlot.ItemID);
		int32 SourceClampedQuantity = UKismetMathLibrary::Clamp(Temp - MaxQuantity,0,MaxQuantity);
		FName SourceItemID = SourceClampedQuantity > 0 ? LocalInventorySlot.ItemID : "";
		SourceInventory->Contents[SourceIndex] = FInventorySlotStruct{SourceItemID,SourceClampedQuantity};

		int32 CurrentClampedQuantity = UKismetMathLibrary::Clamp(Temp,0,MaxQuantity);
		Contents[DestinationIndex] = FInventorySlotStruct{LocalInventorySlot.ItemID,CurrentClampedQuantity};
	}
	else
	{
		// 타겟 인벤토리에 원본 인벤토리의 슬롯값을 설정
		SourceInventory->Contents[SourceIndex] = Contents[DestinationIndex];
		// 원본 인벤토리에 타겟 인벤토리의 슬롯값을 설정
		Contents[DestinationIndex] = LocalInventorySlot;
	}
	OnUpdatedInventory.Broadcast();
	SourceInventory->OnUpdatedInventory.Broadcast();
}

void UInventoryComponent::LoadInventory()
{
	UGameInstance* GameInstance = GetWorld()->GetGameInstance();
	if(!ensure(GameInstance))
	{
		Debug::LogWarning("GameInstance is null");
		return;
	}
	USaveLoadSubSystem* SaveLoadSubSystem = GameInstance->GetSubsystem<USaveLoadSubSystem>();
	if(!ensure(SaveLoadSubSystem))
	{
		Debug::LogWarning("SaveLoadSubSystem is null");
		return;
	}
	
	if(AWarriorHeroCharacter* HeroCharacter = SafeGetOwnerPawn<AWarriorHeroCharacter>())
	{
		Contents = SaveLoadSubSystem->GetInventorySaveData()->InventoryContents;
	}
	else
	{
		TSoftObjectPtr<UInventoryComponent> InventoryComponentSoftPtr = this;
		if(FContainerStruct* ContainerStruct = SaveLoadSubSystem->GetLevelSaveData()->ContainersAdded.Find(InventoryComponentSoftPtr))
		{
			Contents = ContainerStruct->Contents;
		}
		else
		{
			Debug::LogWarning("No matching container found in ContainersAdded");
		}
	}
}

void UInventoryComponent::SaveInventory()
{
	UGameInstance* GameInstance = GetWorld()->GetGameInstance();
	if(!ensure(GameInstance))
	{
		Debug::LogWarning("GameInstance is null");
		return;
	}
	USaveLoadSubSystem* SaveLoadSubSystem = GameInstance->GetSubsystem<USaveLoadSubSystem>();
	if(!ensure(SaveLoadSubSystem))
	{
		Debug::LogWarning("SaveLoadSubSystem is null");
		return;
	}

	
	if(AWarriorHeroCharacter* HeroCharacter = SafeGetOwnerPawn<AWarriorHeroCharacter>())
	{
		SaveLoadSubSystem->GetInventorySaveData()->InventoryContents = Contents;
		SaveLoadSubSystem->SaveInventorySaveData();
	}
	else
	{
		TSoftObjectPtr<UInventoryComponent> InventoryComponentSoftPtr = this;
		FContainerStruct ContainerStruct;
		ContainerStruct.Contents = Contents;
		ContainerStruct.Transform = GetOwner()->GetTransform();
		SaveLoadSubSystem->GetLevelSaveData()->ContainersAdded.Add(InventoryComponentSoftPtr,ContainerStruct);
	}
}

FItemDataTable UInventoryComponent::GetItemData(FName ItemID)
{
	// ItemDataTable이 nullptr이면 경고 출력하고 -1 반환
	if (!ensure(ItemDataTable)) 
	{
		Debug::LogWarning("ItemDataTable is null");
		return FItemDataTable(); 
	}
	
	// 서식 문자열을 TEXT() 매크로로 감싸서 사용
	if(FItemDataTable* Data = ItemDataTable->FindRow<FItemDataTable>(ItemID, FString::Printf(TEXT("Can't Found Row in ItemDataTable %ls"), *ItemID.ToString())))
	{
		return *Data;
	}
	return FItemDataTable(); 
}

int32 UInventoryComponent::GetItemQuantity(FName ItemID)
{
	int32 TotalQuantity = 0;
	for(int i = 0; i < Contents.Num(); i++)
	{
		if(Contents[i].ItemID == ItemID)
		{
			TotalQuantity += Contents[i].Quantity;
		}
	}
	return TotalQuantity;
}

int32 UInventoryComponent::GetTotalQuantity()
{
	int32 TotalQuantity = 0;
	for(int i = 0; i < Contents.Num(); i++)
	{
		TotalQuantity += Contents[i].Quantity;
	}
	return TotalQuantity;
}

FVector UInventoryComponent::GetDropLocation()
{
	FVector Start = GetOwningPawn()->GetActorLocation();
	FVector End = GetOwningPawn()->GetActorForwardVector();
	const FVector RandomEndLocation = UKismetMathLibrary::RandomUnitVectorInConeInRadians(End,AngleRadians) * RandomOffset - FVector(0,0,-500);

	FHitResult HitResult;
	ETraceTypeQuery DropTraceQuery = UEngineTypes::ConvertToTraceType(DropTraceChannel); // 감지할 트레이스 채널 설정
	bool BlockingHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(),Start,RandomEndLocation,DropTraceQuery,
		false,{GetOwner()},GetDrawDebugType(),HitResult,true,
		FLinearColor::Red, FLinearColor::Green);

	if(BlockingHit)
	{
		return HitResult.Location;
	}
	return Start + UKismetMathLibrary::RandomUnitVectorInConeInRadians(End,AngleRadians) * RandomOffset;
}

void UInventoryComponent::PrintContents()
{
	for(int i = 0; i < Contents.Num(); i++)
	{
		Debug::Log(FString::Printf(TEXT("%d : %s = %d"),i,*Contents[i].ItemID.ToString(),Contents[i].Quantity));
	}
}
