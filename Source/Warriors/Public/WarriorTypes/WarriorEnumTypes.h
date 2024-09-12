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