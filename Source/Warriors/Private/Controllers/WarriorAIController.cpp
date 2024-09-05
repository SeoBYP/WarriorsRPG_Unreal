﻿// Vince Petrelli All Rights Reserved


#include "Controllers/WarriorAIController.h"

#include "AsyncTreeDifferences.h"
#include "DetourCrowdAIController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "WarriorDebugHelper.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AWarriorAIController::AWarriorAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>
	(TEXT("PathFollowingComponent")))
{
	if(UCrowdFollowingComponent* CrowdComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		Debug::DebugLog(TEXT("CrowdFollowingComponent is Valid"));
	}

	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("EnemyAISenseConfig_Sight");
	AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;
	AISenseConfig_Sight->SightRadius = 5000.0f;
	AISenseConfig_Sight->LoseSightRadius = 0;
	AISenseConfig_Sight->PeripheralVisionAngleDegrees = 360.0f;


	EnemyPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("EnemyPerceptionComponent");
	EnemyPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);
	EnemyPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	EnemyPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this,&ThisClass::OnEnemyPerceptionUpdated);

	SetGenericTeamId(FGenericTeamId(1));
}

ETeamAttitude::Type AWarriorAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const APawn* PawnToCheck = Cast<const APawn>(&Other);

	const IGenericTeamAgentInterface* OtherTramAgent = Cast<const IGenericTeamAgentInterface>(PawnToCheck->GetController());

	if(OtherTramAgent && OtherTramAgent->GetGenericTeamId() < GetGenericTeamId())
	{
		return ETeamAttitude::Hostile;		
	}
	return ETeamAttitude::Friendly;
}

void AWarriorAIController::BeginPlay()
{
	Super::BeginPlay();

	if(UCrowdFollowingComponent* CrowdComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		CrowdComp->SetCrowdSimulationState(bEnableDtourCrownAvoidence ? ECrowdSimulationState::Enabled : ECrowdSimulationState::Disabled);

		switch (DetourCrowdAvoidenceQuality)
		{
			case 1: CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low);		break;
			case 2: CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium);	break;
			case 3: CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good);		break;
			case 4: CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);		break;
			default:
				break;
		}

		CrowdComp->SetAvoidanceGroup(1);
		CrowdComp->SetGroupsToAvoid(1);
		CrowdComp->SetCrowdCollisionQueryRange(CollisionQueryRange);
	}
}

void AWarriorAIController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if(UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
	{
		if(!BlackboardComponent->GetValueAsObject(FName("TargetActor")))
		{
			if(Stimulus.WasSuccessfullySensed() && Actor)
			{
				BlackboardComponent->SetValueAsObject(FName("TargetActor"),Actor);
			}
		}
	}
}
