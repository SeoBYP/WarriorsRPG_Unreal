// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "WarriorInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class WARRIORS_API UWarriorInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	// Template란?
	// 템플릿(Template)은 C++에서 제네릭 프로그래밍을 가능하게 하는 기능입니다.
	// 즉, 함수나 클래스를 작성할 때 구체적인 데이터 타입에 의존하지 않고,
	// 다양한 데이터 타입을 처리할 수 있도록 일반화할 수 있습니다.
	// 이 코드에서는 템플릿을 사용하여 다양한 객체와 콜백 함수를 입력 액션에 바인딩할 수 있게 합니다.
	
	/** 템플릿 함수: 입력 액션을 바인딩합니다.
	 *  UserObject: 입력 액션이 바인딩될 객체의 타입
	 *  CallbackFunc: 입력 액션이 호출될 때 실행될 함수
	 */
	template<class UserObject,typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig,const FGameplayTag& InInputTag,ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func);
	
};

template <class UserObject, typename CallbackFunc>
void UWarriorInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig,
	const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
	// 입력 구성 데이터 에셋이 null인지 확인
	checkf(InInputConfig,TEXT("Input Config data asset is null, can not proceed with binding"));

	// 입력 태그에 해당하는 입력 액션을 찾습니다.
	if(UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		// 액션을 바인딩합니다.
		BindAction(FoundAction,TriggerEvent,ContextObject,Func);
	}
}
