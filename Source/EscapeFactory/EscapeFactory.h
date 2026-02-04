// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/** Main log category used across the project */
DECLARE_LOG_CATEGORY_EXTERN(LogEscapeFactory, Log, All);

DECLARE_LOG_CATEGORY_EXTERN(EscapeFactory, Log, All);
#define EFLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define EFLOG_S(Verbosity) UE_LOG(EscapeFactory, Verbosity, TEXT("%s"), *EFLOG_CALLINFO)
#define EFLOG(Verbosity, Format, ...) UE_LOG(EscapeFactory, Verbosity, TEXT("%s %s"), *EFLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

#define EFCHECK(Expr, ...) {if(!(Expr)) {EFLOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__;}}

