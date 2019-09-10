#include "C_Log.h"
#include "Engine.h"

void C_Log::Log(int val)
{
	GLog->Logf(L"%d", val);
}

void C_Log::Log(float val)
{
	GLog->Logf(L"%f", val);
}

void C_Log::Log(const FString & val)
{
	GLog->Log(val);
}

void C_Log::Log(const TCHAR * val)
{
	GLog->Log(val);
}

void C_Log::LogNull(UObject * object)
{
	GLog->Log(object != NULL ? L"Not Null" : L"Null");
}

void C_Log::Print(int val, float time, FColor color, int32 key)
{
	GEngine->AddOnScreenDebugMessage(key, time, color, FString::Printf(L"%d", val));
}

void C_Log::Print(float val, float time, FColor color, int32 key)
{
	GEngine->AddOnScreenDebugMessage(key, time, color, FString::Printf(L"%f", val));
}

void C_Log::Print(const FString & val, float time, FColor color, int32 key)
{
	GEngine->AddOnScreenDebugMessage(key, time, color, val);
}

void C_Log::Print(const TCHAR * val, float time, FColor color, int32 key)
{
	GEngine->AddOnScreenDebugMessage(key, time, color, val);
}

void C_Log::PrintNull(UObject * object, float time, FColor color, int32 key)
{
	GEngine->AddOnScreenDebugMessage(key, time, color, object != NULL ? "NotNull" : "Null");
}
