#pragma once

#include "CoreMinimal.h"

class U00_PORTFOLIO_API C_Log
{
public:
	static void Log(int val);
	static void Log(float val);
	static void Log(const FString& val);
	static void Log(const TCHAR* val);
	static void LogNull(UObject* object);

	static void Print(int val, float time = 10.0f, FColor color = FColor::Blue, int32 key = -1);
	static void Print(float val, float time = 10.0f, FColor color = FColor::Blue, int32 key = -1);
	static void Print(const FString& val, float time = 10.0f, FColor color = FColor::Blue, int32 key = -1);
	static void Print(const TCHAR* val, float time = 10.0f, FColor color = FColor::Blue, int32 key = -1);
	static void PrintNull(UObject* object, float time = 10.0f, FColor color = FColor::Blue, int32 key = -1);

};
