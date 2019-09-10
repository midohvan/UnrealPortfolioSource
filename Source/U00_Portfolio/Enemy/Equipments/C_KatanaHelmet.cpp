#include "C_KatanaHelmet.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

AC_KatanaHelmet::AC_KatanaHelmet()
{
	PrimaryActorTick.bCanEverTick = true;

	HelmetMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(FName("Helmet"));
	RootComponent = HelmetMeshComp;

	HelmetMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(FName("HelmetCapsule"));
	CapsuleCollision->SetupAttachment(HelmetMeshComp);
	CapsuleCollision->SetBoundsScale(50);
	CapsuleCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}