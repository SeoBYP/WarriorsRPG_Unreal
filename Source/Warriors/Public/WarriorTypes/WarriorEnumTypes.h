#pragma once

UENUM(BlueprintType)
enum class EWarriorConfirmType : uint8
{
	YES,
	NO
};

UENUM(BlueprintType)
enum class EWarriorVaildType : uint8
{
	Vaild,
	Invalid,
};

UENUM(BlueprintType)
enum class EWarriorSuccessType : uint8
{
	Successful,
	Failed,
};