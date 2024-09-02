// Vince Petrelli All Rights Reserved


#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"
#include "AbilitySystem/WarriorAttributeSet.h"
#include "Utils/WarriorGameplayTags.h"
#include "WarriorDebugHelper.h"

struct FWarriorDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)
	
	FWarriorDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet,AttackPower,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet,DefensePower,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet,DamageTaken,Target,false);
	}
};

static const FWarriorDamageCapture& GetWarriorDamageCapture()
{
	static FWarriorDamageCapture warriorDamageCapture;
	return warriorDamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	/* slow way of doing Capture*/
	// FProperty* AttackPowerProperty = FindFieldChecked<FProperty>(
	// 	UWarriorAttributeSet::StaticClass(),
	// 	GET_MEMBER_NAME_CHECKED(UWarriorAttributeSet, AttackPower)
	// );
	//
	// FGameplayEffectAttributeCaptureDefinition AttackPowerCaptureDefinition
	// (
	// 	AttackPowerProperty,
	// 	EGameplayEffectAttributeCaptureSource::Source,
	// 	false
	// );
	//
	// RelevantAttributesToCapture.Add(AttackPowerCaptureDefinition);

	RelevantAttributesToCapture.Add(GetWarriorDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetWarriorDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetWarriorDamageCapture().DamageTakenDef);
}

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	// EffectSpec.GetContext().GetSourceObject();
	// EffectSpec.GetContext().GetAbility();
	// EffectSpec.GetContext().GetInstigator();
	// EffectSpec.GetContext().GetEffectCauser();
	
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetWarriorDamageCapture().AttackPowerDef,EvaluateParameters,SourceAttackPower);
	
	float BaseDamage = 0.0f;
	int32 UsedLightAttackComboCount = 0;
	int32 UsedHeavyAttackComboCount = 0;
	for(const TPair<FGameplayTag,float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if(TagMagnitude.Key.MatchesTagExact(WarriorsGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
		}
		if(TagMagnitude.Key.MatchesTagExact(WarriorsGameplayTags::Player_SetByCaller_AttackType_Light))
		{
			UsedLightAttackComboCount = TagMagnitude.Value;
		}
		if(TagMagnitude.Key.MatchesTagExact(WarriorsGameplayTags::Player_SetByCaller_AttackType_Heavy))
		{
			UsedHeavyAttackComboCount = TagMagnitude.Value;
		}
	}

	float TargetDefensePower = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetWarriorDamageCapture().DefensePowerDef,EvaluateParameters,TargetDefensePower);
	
	if(UsedLightAttackComboCount != 0)
	{
		const float DamageIncreasePercentLight = (UsedLightAttackComboCount - 1) * 0.05f + 1.0f;

		BaseDamage *= DamageIncreasePercentLight;
	}

	if(UsedHeavyAttackComboCount != 0)
	{
		const float DamageIncreasePercentHeavy = (UsedHeavyAttackComboCount) * 0.15f + 1.0f;

		BaseDamage *= DamageIncreasePercentHeavy;
	}
	
	const float FinalDamageDone = BaseDamage * SourceAttackPower / TargetDefensePower;
	
	if(FinalDamageDone > 0.0f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetWarriorDamageCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				FinalDamageDone
			)
		);
	}
}
