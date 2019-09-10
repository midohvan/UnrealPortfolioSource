#pragma once

#include "C_Log.h"
#include "Engine/World.h"
#include "ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#define CheckNull(p){ if(p == NULL) return ; }
#define CheckNullResult(p, result){ if(p == NULL) return result; }