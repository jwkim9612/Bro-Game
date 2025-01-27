// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "BDatas.h"

DECLARE_LOG_CATEGORY_EXTERN(BroGame, Log, All);
#define BLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define BLOG_S(Verbosity) UE_LOG(BroGame, Verbosity, TEXT("%s"), *BLOG_CALLINFO)
#define BLOG(Verbosity, Format, ...) UE_LOG(BroGame, Verbosity, TEXT("%s %s"), *BLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

#define BCHECK(Expr, ...) {if(!(Expr)) {BLOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__;}}