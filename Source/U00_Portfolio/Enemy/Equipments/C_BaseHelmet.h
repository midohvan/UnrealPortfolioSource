
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_BaseHelmet.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;

UCLASS()
class U00_PORTFOLIO_API AC_BaseHelmet : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_BaseHelmet();

	UFUNCTION()
		virtual void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {};

	virtual UCapsuleComponent* GetBoxComponent() { return CapsuleCollision; }
	virtual UStaticMeshComponent* GetMesh() { return HelmetMeshComp; }

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
		UCapsuleComponent* CapsuleCollision;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
		UStaticMeshComponent* HelmetMeshComp;

	UPROPERTY(EditDefaultsOnly)
		float HelmetDuration = 100.0f;




};
