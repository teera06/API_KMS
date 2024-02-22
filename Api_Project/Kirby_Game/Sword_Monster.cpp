#include "Sword_Monster.h"

Sword_Monster::Sword_Monster()
{
}

Sword_Monster::~Sword_Monster()
{
}

void Sword_Monster::MoveUpdate(float _DeltaTime)
{
	FVector Move = FVector::Zero;

	//if (DirMonster.iX() == -1 && IsIce == false)
	//{
		//PengiRenderer->ChangeAnimation("Idel_Left");
		//checkX = -30;
	//}
	//else if (DirMonster.iX() == 1 && IsIce == false) {
		//PengiRenderer->ChangeAnimation("Idel_Right");
		//checkX = 30;
	//}
	//Color8Bit ColorR = ActorCommon::ColMapImage->GetColor(GetActorLocation().iX() + checkX, GetActorLocation().iY() - 30, Color8Bit::RedA);
	//if (ColorR == Color8Bit(255, 0, 0, 0))
	//{
		//if (true == IsIce)
		//{
			//IceMove = FVector::Zero;
			//Destroy();
		//}
		//else {
			//DirMonster.X *= -1;
		//}
	//}
	//else {
		//MoveSpeed = 30.0f;
		//Move += DirMonster * _DeltaTime * MoveSpeed;
	//}

	if (true == IsIce)
	{
		Move = FVector::Zero;
	}
	AddActorLocation(Move);
}
