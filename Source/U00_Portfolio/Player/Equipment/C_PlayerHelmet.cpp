#include "C_PlayerHelmet.h"
#include "Global.h"
#include "Player/C_Player.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"


AC_PlayerHelmet::AC_PlayerHelmet()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerHelmetMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(FName("PlayerHelmet"));
	RootComponent = PlayerHelmetMeshComp;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("HelmetBox"));
	BoxCollision->SetupAttachment(PlayerHelmetMeshComp);
	BoxCollision->SetBoundsScale(50);
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void AC_PlayerHelmet::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC_PlayerHelmet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AC_PlayerHelmet::OnBeginOverlap);

}

void AC_PlayerHelmet::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}

