#include "C_PlayerAnimInstance.h"
#include "C_Player.h"
#include "C_PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"


void UC_PlayerAnimInstance::NativeUpdateAnimation(float Delta)
{
	Super::NativeUpdateAnimation(Delta);

	APawn* pawn = TryGetPawnOwner();
	player = Cast<AC_Player>(pawn);
	if (player == NULL) return;

	CController = Cast<AC_PlayerController>(player->GetController());
	if (CController == NULL) return;

	Speed = CController->GetControlledPlayer()->GetVelocity().Size();
	Direction = CalculateDirection(CController->GetControlledPlayer()->GetVelocity(), CController->GetControlledPlayer()->GetActorRotation());
	bInAir = CController->GetControlledPlayer()->GetCharacterMovement()->IsFalling();

	bDrawing = CController->GetDrawingWeapon();
	bSheathing = CController->GetSheathingWeapon();
	bDead = CController->GetDead();
	bWeaponDrawn = CController->GetWeaponDrawn();
	
	
}

