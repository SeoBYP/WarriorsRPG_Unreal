﻿#pragma once

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


UENUM()
enum class EWarriorCountDownActionInput : uint8
{
	Start,
	Cancel
};

UENUM()
enum class EWarriorCountDownActionOutput : uint8
{
	Updated,
	Completed,
	Cancelled
};

UENUM(BlueprintType)
enum class EWarriorGameDifficulty : uint8{
	Easy,
	Normal,
	Hard,
	VeryHard,
};

UENUM(BlueprintType)
enum class EWarriorInputMode : uint8{
	GameOnly,
	UIOnly,
};

UENUM(BlueprintType)
enum class EObjectiveType : uint8
{
	Location,
	Kill,
	Interact,
	Collect,
};