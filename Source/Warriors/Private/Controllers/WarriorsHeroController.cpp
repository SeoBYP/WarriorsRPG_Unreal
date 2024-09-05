// Vince Petrelli All Rights Reserved


#include "Warriors/Public/Controllers/WarriorsHeroController.h"

AWarriorsHeroController::AWarriorsHeroController()
{
	HeroTeamId = FGenericTeamId(0);
}

FGenericTeamId AWarriorsHeroController::GetGenericTeamId() const
{
	return HeroTeamId;
}
