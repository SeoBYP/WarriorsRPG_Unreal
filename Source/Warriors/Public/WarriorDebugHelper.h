#pragma once

namespace Debug
{
	static void DebugLog(const FString& Msg, const FColor& Color = FColor::Green,int32 InKey = -1)
	{
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey,7.0f,Color,Msg);
			UE_LOG(LogTemp,Display,TEXT("%s"),*Msg);
		}
	}

	static void DebugLog(const FString& FloatTitle,float FloatValueToPrint, const FColor& Color = FColor::Green,int32 InKey =-1)
	{
		if(GEngine)
		{
			const FString FinalMSG = FloatTitle + TEXT(": ") + FString::SanitizeFloat(FloatValueToPrint);
			GEngine->AddOnScreenDebugMessage(InKey,7.0f,Color,FinalMSG);
			UE_LOG(LogTemp,Display,TEXT("%s"),*FinalMSG);
		}
	}
	
	static void LogWarning(const FString& Msg, const FColor& Color= FColor::Yellow,int32 InKey = -1)
	{
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey,7.0f,Color,Msg);
			UE_LOG(LogTemp,Warning,TEXT("%s"),*Msg);
		}
	}

	static void LogError(const FString& Msg, const FColor& Color= FColor::Red,int32 InKey = -1)
	{
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey,7.0f,Color,Msg);
			UE_LOG(LogTemp,Error,TEXT("%s"),*Msg);
		}
	}

	
}
