#include "C_AssassinHelmet.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

AC_AssassinHelmet::AC_AssassinHelmet()
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