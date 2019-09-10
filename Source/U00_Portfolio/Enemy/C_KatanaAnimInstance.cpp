#include "C_KatanaAnimInstance.h"
#include "Enemy/C_Katana_Enemy.h"
#include "Enemy/C_KatanaAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

void UC_KatanaAnimInstance::NativeUpdateAnimation(float Delta)
{
	Super::NativeUpdateAnimation(Delta);

	APawn* pawn = TryGetPawnOwner();
	Enemy = Cast<AC_Katana_Enemy>(pawn);
	if (Enemy == NULL) return;


	Speed = Enemy->GetVelocity().Size();
	Direction = CalculateDirection(Enemy->GetVelocity(), Enemy->GetActorRotation());
	bInAir = Enemy->GetCharacterMovement()->IsFalling();

	bDead = Enemy->GetDead();
	bHit = Enemy->GetBeingHit();


}
