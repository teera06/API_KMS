#include "SubBoss.h"

SubBoss::SubBoss()
{
}

SubBoss::~SubBoss()
{
}

void SubBoss::BeginPlay()
{

}

void SubBoss::Tick(float _DeltaTime)
{

}

void SubBoss::CalDir(float _DeltaTime)
{
	FVector PlayerPos = MainPlayer->GetActorLocation();  // 플레이어 위치
	FVector MonsterPos = GetActorLocation(); // 몬스터 위치

	FVector AttXL = MonsterPos + FVector::Left * AttRange; // 몬스터 왼쪽 플레이어 인식 시야 X축
	FVector AttXR = MonsterPos + FVector::Right * AttRange; // 몬스터 오른쪽 플레이어 인식 시야 X축

	FVector PlayerX = PlayerPos * FVector::Right; // 플레이어 위치 X축

	FVector MonsterDir = PlayerPos - MonsterPos; // 플레이어 위치 - 몬스터 위치 = 방향 ex) 몬스터가 플레이어에게 향하는 방향
	MonsterDirNormal = MonsterDir.Normalize2DReturn();  // 해당값을 정규화 

	MovePos = FVector::Zero; // 플레이어 추격 시 이동

	if (MonsterDirNormal.iX() == -1) // 왼쪽 방향
	{
		MonsterRenderer->ChangeAnimation("Move_Left");
		WallX = -20;
	}
	else if (MonsterDirNormal.iX() == 1 && IsIce == false) { // 오른쪽 방향
		MonsterRenderer->ChangeAnimation("Move_Right");
		WallX = 20;
	}
	MovePos += MonsterDirNormal * _DeltaTime * MoveSpeed * FVector::Right; // 몬스터가 플레이어의 Y축도 인식할 수 있으니 FVector::Right 를 곱해 X축만 추격

	// 플레이어를 향해 공격
	if (AttXL.iX() < PlayerX.iX() && AttXR.iX() > PlayerX.iX() && MainPlayer->GetActorLocation().iY() >= GetActorLocation().iY() - 30) // 몬스터 시야에 포착된 경우 X축 기준 왼쪽, 오른쪽
	{
		IsAtt = true;
	}
}

void SubBoss::IceAtt()
{
}

void SubBoss::Collisiongather(float _DeltaTime)
{
}

void SubBoss::CalResult(float _DeltaTime)
{
}

void SubBoss::GroundUp()
{
	while (true)
	{
		Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY() - 1, Color8Bit::RedA);
		if (ColorR == Color8Bit(255, 0, 0, 0))
		{
			AddActorLocation(FVector::Up * 2);
		}
		else
		{
			break;
		}
	}
}

void SubBoss::MoveUpdate(float _DeltaTime)
{
}

void SubBoss::AniCreate()
{
	MonsterRenderer->CreateAnimation("Move_Right", "Tock_Right.png", 7, 9, 0.3f, true);
	MonsterRenderer->CreateAnimation("Move_Left", "Tock_Left.png", 7, 9, 0.3f, true);
	MonsterRenderer->CreateAnimation("Att_Right", "Tock_Right.png", 4, 6, 0.15f, false);
	MonsterRenderer->CreateAnimation("Att_Left", "Tock_Left.png", 4, 6, 0.15f, false);

	MonsterRenderer->CreateAnimation("die_Right", "Tock_Left.png", 11, 13, 0.3f, true); // 죽음 
	MonsterRenderer->CreateAnimation("die_Left", "Tock_Right.png",11, 13, 0.3f, true); // 죽음 
	
	//MonsterRenderer->CreateAnimation("Effect", "Effects.png", 29, 30, 0.1f, true); // 죽는 애니메이션
}
