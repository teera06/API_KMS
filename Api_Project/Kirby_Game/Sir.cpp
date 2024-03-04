#include "Sir.h"

ASir::ASir()
{
}

ASir::~ASir()
{
}

void ASir::Tick(float _DeltaTime)
{
}

void ASir::BeginPlay()
{
}

void ASir::SkillDir()
{
	if (GetDir().iX() == FVector::Left.iX())
	{
		IceRenderer->ChangeAnimation("Ice_Right");
	}
	else
	{
		IceRenderer->ChangeAnimation("Ice_Left");
	}

	IceCollision->SetPosition({ GetDir().iX() * 120,0 });
	IceRenderer->SetPosition({ GetDir().iX() * 125,-5 });
}

void ASir::Collisiongather(float _DeltaTime)
{

}
