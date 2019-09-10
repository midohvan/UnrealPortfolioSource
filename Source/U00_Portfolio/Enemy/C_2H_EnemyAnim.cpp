#include "C_2H_EnemyAnim.h"
#include "C_2H_Enemy.h"
#include "C_EnemyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

void UC_2H_EnemyAnim::NativeUpdateAnimation(float Delta)
{
	Super::NativeUpdateAnimation(Delta);

	APawn* pawn = TryGetPawnOwner();
	Enemy = Cast<AC_2H_Enemy>(pawn);
	if (Enemy == NULL) return;


	Speed = Enemy->GetVelocity().Size();
	Direction = CalculateDirection(Enemy->GetVelocity(), Enemy->GetActorRotation());
	bInAir = Enemy->GetCharacterMovement()->IsFalling();

	bDead = Enemy->GetDead();
	bHit = Enemy->GetBeingHit();


}
