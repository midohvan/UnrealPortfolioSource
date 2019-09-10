#include "C_Trigger_CameraAction.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "C_Player.h"
#include "C_PlayerController.h"

AC_Trigger_CameraAction::AC_Trigger_CameraAction()
{
	OnActorBeginOverlap.AddDynamic(this, &AC_Trigger_CameraAction::OnOverlapBegin);
}

void AC_Trigger_CameraAction::BeginPlay()
{
	Super::BeginPlay();
	//DrawDebugBox(GetWorld(), GetActorLocation(), GetActorScale() * 100, FColor::Magenta, true, -1, 0, 5);

}

void AC_Trigger_CameraAction::OnOverlapBegin(AActor * OverlappedActor, AActor * OtherActor)
{
	if (OtherActor->ActorHasTag("Enemy") == true) return;
	if (OtherActor->ActorHasTag("Equipments") == true) return;
	if (OtherActor == this) return;

	AC_Player* Player = Cast<AC_Player>(OtherActor);
	if (Player == NULL) return;

	AC_PlayerController* AIController = Cast<AC_PlayerController>(Player->GetController());
	if (AIController == NULL) return;

	if (AIController->GetCameraAction() == true) return;

	GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Green, "CameraAction");
	
	AActor* ClosestEnemy = AIController->GetClosestEnemy(Player->GetActorLocation());

	AIController->SetActionCamera(ClosestEnemy);

	this->Destroy();

}
