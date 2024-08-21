#pragma once

namespace Debug
{
	static void DebugLog(const FString& Msg, const FColor& Color = FColor::White,int32 InKey = 1)
	{
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey,7.0f,Color,Msg);
			UE_LOG(LogTemp,Display,TEXT("%s"),*Msg);
		}
	}

	
	static void LogWarning(const FString& Msg, const FColor& Color= FColor::Yellow,int32 InKey = 1)
	{
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey,7.0f,Color,Msg);
			UE_LOG(LogTemp,Warning,TEXT("%s"),*Msg);
		}
	}

	static void LogError(const FString& Msg, const FColor& Color= FColor::Red,int32 InKey = 1)
	{
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey,7.0f,Color,Msg);
			UE_LOG(LogTemp,Error,TEXT("%s"),*Msg);
		}
	}

	
}
