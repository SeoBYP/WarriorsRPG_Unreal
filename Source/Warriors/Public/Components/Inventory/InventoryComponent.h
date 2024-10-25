// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PawnExtensionComponentBase.h"
#include "Inventory/InventorySlotStruct.h"
#include "Inventory/ItemDataTable.h"
#include "Kismet/KismetSystemLibrary.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdatedInventory);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent),Blueprintable,BlueprintType)
class WARRIORS_API UInventoryComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();
	virtual void InitializeComponent() override;

	virtual void BeginPlay() override;
	
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category="Inventory",meta=(AllowPrivateAccess="true"))
	int32 InventorySize;

	// 서버와의 통신은 제외합니다.
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category="Inventory",meta=(AllowPrivateAccess="true"))
	TArray<FInventorySlotStruct> Contents;

	UPROPERTY(EditDefaultsOnly,BlueprintreadWrite, Category="Inventory",meta=(AllowPrivateAccess="true"))
	UDataTable* ItemDataTable;

	UPROPERTY(EditDefaultsOnly,BlueprintreadWrite, Category="Inventory",meta=(AllowPrivateAccess="true"))
	TSubclassOf<AActor> DropBagInventory;

	UPROPERTY(EditDefaultsOnly,BlueprintreadWrite, Category="Inventory|DropLocation",meta=(AllowPrivateAccess="true"))
	float AngleRadians = 30.0f;

	UPROPERTY(EditDefaultsOnly,BlueprintreadWrite, Category="Inventory|DropLocation",meta=(AllowPrivateAccess="true"))
	float RandomOffset = 150.0f;

	UPROPERTY(EditDefaultsOnly,BlueprintreadWrite, Category="Inventory|DropLocation",meta=(AllowPrivateAccess="true"))
	TEnumAsByte<ECollisionChannel> DropTraceChannel = ECC_Camera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory|DropLocation", meta=(AllowPrivateAccess=true))
	bool bShowDebugTraces = true;

	
public:
	UPROPERTY(BlueprintCallable,BlueprintAssignable,Category="Inventory")
	FOnUpdatedInventory OnUpdatedInventory;

public:
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="Inventory")
	void RemoveItem(int32 Index,bool RemoveWholeStack,bool IsConsumed);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="Inventory")
	void DropItem(FName ItemID,int32 Quantity);
public:
	UFUNCTION(BlueprintCallable,Category="Inventory")
	void AddInventory(FName ItemID,int32 Quantity,bool& Success, int32& QuantityRemaining);

	UFUNCTION(BlueprintCallable,BlueprintPure,Category="Inventory")
	void QueryInventory(FName ItemID,int32 Quantity,bool& Success, int32& OutQuantity);
	
	UFUNCTION(BlueprintCallable,Category="Inventory")
	void FindSlot(FName ItemID,int32& Index, bool& FoundSlot);

	UFUNCTION(BlueprintCallable,Category="Inventory")
	void RemoveFromInventory(int32 Index,bool RemoveWholeStack,bool IsConsumed);
	
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="Inventory")
	int32 GetMaxStackSize(FName ItemID);

	UFUNCTION(BlueprintCallable,Category="Inventory")
	void AddItemStack(int32 Index,int32 Quantity = 1);

	UFUNCTION(BlueprintCallable,BlueprintPure,Category="Inventory")
	void GetAnyEmptySlotAvailable(bool& HasEmptySlot,int32& EmptyIndex);

	UFUNCTION(BlueprintCallable,Category="Inventory")
	void CreateNewStack(FName ItemID,int32 Quantity,bool& Success);

	UFUNCTION(BlueprintCallable,Category="Inventory")
	void ConsumeItem(int32 Index);

	UFUNCTION(BlueprintCallable,Category="Inventory")
	void TransferSlots(int32 SourceIndex, UInventoryComponent* SourceInventory,int32 DestinationIndex);

public:
	UFUNCTION(BlueprintCallable,Category="Inventory|SaveAndLoad")
	void LoadInventory();

	UFUNCTION(BlueprintCallable,Category="Inventory|SaveAndLoad")
	void SaveInventory();
	
public:
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="Inventory")
	FItemDataTable GetItemData(FName ItemID);

	UFUNCTION(BlueprintCallable,BlueprintPure,Category="Inventory")
	int32 GetItemQuantity(FName ItemID);

	UFUNCTION(BlueprintCallable,BlueprintPure,Category="Inventory")
	int32 GetTotalQuantity();
	
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="Inventory")
	FVector GetDropLocation();

public:
	UFUNCTION(BlueprintCallable,Category="Inventory|Debug")
	void PrintContents();
	
	// 디버그 트레이스를 설정하는 함수
	FORCEINLINE EDrawDebugTrace::Type GetDrawDebugType() const
	{
		return bShowDebugTraces ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None;
	}
	
};
