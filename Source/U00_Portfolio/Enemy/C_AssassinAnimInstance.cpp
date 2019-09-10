#include "C_AssassinAnimInstance.h"	
#include "C_Assassin_Enemy.h"
#include "C_AssassinAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

void UC_AssassinAnimInstance::NativeUpdateAnimation(float Delta)
{
	Super::NativeUpdateAnimation(Delta);

	APawn* pawn = TryGetPawnOwner();
	Enemy = Cast<AC_Assassin_Enemy>(pawn);
	if (Enemy == NULL) return;


	Speed = Enemy->GetVelocity().Size();
	Direction = CalculateDirection(Enemy->GetVelocity(), Enemy->GetActorRotation());
	bInAir = Enemy->GetCharacterMovement()->IsFalling();

	bDead = Enemy->GetDead();
	bHit = Enemy->GetBeingHit();
}