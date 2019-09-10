#include "C_2H_Helmet.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

AC_2H_Helmet::AC_2H_Helmet()
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
void AC_2H_Helmet::BeginPlay()
{
	Super::BeginPlay();

	CapsuleCollision->OnComponentBeginOverlap.AddDynamic(this, &AC_2H_Helmet::OnBeginOverlap);

}

void AC_2H_Helmet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_2H_Helmet::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}

