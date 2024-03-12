#include "Monster_Mike.h"

#include "ModeEnum.h"

#include "Monster_Base.h"
#include "pengi_Ice.h"
#include "Monster_Fire.h"
#include "Monster_Sir.h"

AMonster_Mike::AMonster_Mike()
{
}

AMonster_Mike::~AMonster_Mike()
{
}

void AMonster_Mike::BeginPlay()
{
	AActor::BeginPlay();

	scale = 2; // 평소 크기
	// 랜더링
	{
		MonsterRenderer = CreateImageRenderer(ERenderOrder::Monster); // 이미지 랜더 생성
		MonsterRenderer->SetImage("MikeMonster_Right.png"); // 이미지 Set
		MonsterRenderer->SetTransform({ {0,1}, {64 * scale, 64 * scale} }); // 랜더의 위치 크기 
	}

	// 콜리전
	{
		MonsterCollision = CreateCollision(ECollisionOrder::MikeMonster);
		MonsterCollision->SetScale({ 60, 60 });
		MonsterCollision->SetColType(ECollisionType::Rect);
	}

	// 애니메이션 만들기
	AniCreate();

	MonsterRenderer->ChangeAnimation("Move_Left");

}

void AMonster_Mike::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	GroundUp();
	if (false == checkLocation) // 첫 업데이트와, 벽에 충돌시에만 실행
	{
		// 이동 범위 지정
		CurLocation = GetActorLocation() * FVector::Right;
		RangeXL = CurLocation + (FVector::Left * RangeX);
		RangeXR = CurLocation + (FVector::Right * RangeX);
	}

	if (false == IsDie) // Destroy(0.3f); -> 조건없이 계속 move업데이트 되면서 0.3f도 똑같이 유지 (한번만 실행해야함)
	{
		checkLocation = true;
		MoveUpdate(_DeltaTime);
	}
	else { // IsDIe가 true이면 MoveUpdate는 연속 실행이 안됨 -> Destroy(0.3f) 작동
		AddActorLocation(DiePos); // 죽으면서 이동
	}
}

void AMonster_Mike::MoveUpdate(float _DeltaTime)
{
	AddActorLocation(GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime)); // 중력 작용

	CalDir();
	Collisiongather(_DeltaTime);
	CalResult(_DeltaTime);
}

void AMonster_Mike::BaseMove(float _DeltaTime)
{
	FVector Move = FVector::Zero;
	FVector CurX = GetActorLocation() * FVector::Right;

	if (RangeXL.iX() >= CurX.iX() || RangeXR.iX() <= CurX.iX()) // 기본 몬스터 이동 방향 좌우 +-100 그 범위 벗어나는 경우 -> 방향 변환
	{
		StartDir.X *= -1;
		AddActorLocation(StartDir * FVector::Right * _DeltaTime * 100.0f); // 해당 범위 벗어나야 아래의 else문을 실행할 수 있기에 다시 범위안으로 옮기고 리턴
		return;
	}
	else
	{
		if (StartDir.iX() == -1) // 왼쪽 방향에 얼지 않은 상태
		{
			MonsterRenderer->ChangeAnimation("Move_Left");
			WallX = -20;
		}
		else if (StartDir.iX() == 1) { // 오른쪽 방향에 얼지 않은 상태
			MonsterRenderer->ChangeAnimation("Move_Right");
			WallX = 20;
		}

		Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX() + WallX, GetActorLocation().iY() - 30, Color8Bit::RedA);

		if (ColorR == Color8Bit(255, 0, 0, 0)) // 벽 픽셀 충돌
		{
			StartDir.X *= -1;
			checkLocation = false; // 몬스터가 벽에 닿으면 방향전환과 동시에 다시 위치 지정
		}
		else { // 충돌하지 않은 경우
			Move += StartDir * _DeltaTime * MoveSpeed;
		}

		AddActorLocation(Move); // 최종 움직임 계산
	}
}

void AMonster_Mike::AniCreate()
{
	// 기본 걷는 모션
	MonsterRenderer->CreateAnimation("Move_Right", "MikeMonster_Right.png", { 0,1,2,5,6 }, 0.1f, true); // 걷기
	MonsterRenderer->CreateAnimation("Move_Left", "MikeMonster_Left.png", {0,1,2,5,6}, 0.1f, true); // 걷기
	MonsterRenderer->CreateAnimation("die_Right", "MikeMonster_Right.png", 4, 4, 0.2f, false); // 죽는 애니메이션
	MonsterRenderer->CreateAnimation("die_Left", "MikeMonster_Left.png", 4, 4, 0.2f, false); // 죽는 애니메이션
}

void AMonster_Mike::Collisiongather(float _DeltaTime)
{
	// 콜리전 
	std::vector<UCollision*> Result;
	if (true == MonsterCollision->CollisionCheck(ECollisionOrder::kirby, Result)) // 얼지 않은 상태에서 플레이어와 충돌
	{
		if (true == BaseOn) // 흡수할 때의 몬스터 충돌 -> 몬스터는 플레이어와 충돌할 경우 바로 죽음
		{
			Destroy();
		}
		else {// 일반적인 플레이와의 충돌
			MainPlayer->Sethitstate(true); // 플레이어 충돌 체크
			MainPlayer->SetHitDir(MonsterDirNormal * FVector::Right);
			MainPlayer->GetKirbyRender()->SetAlpha(0.5f);
			MainPlayer->GetKirbyCollision()->ActiveOff();
			MainPlayer->AddHP(GetAtt());
			MainPlayer->HitStart(); // hit 상태 스타트
			if (MonsterDirNormal.iX() == -1) // 몬스터가 플레이어를 향하는 방향의 반대 방향으로 힘이 작용
			{
				MonsterRenderer->ChangeAnimation("die_Left"); // 죽는 애니메이션

			}
			else {
				MonsterRenderer->ChangeAnimation("die_Right"); // 죽는 애니메이션
			}
			DiePos = MonsterDirNormal * -200.0f * _DeltaTime * FVector::Right; // 죽으면서 이동하는 위치 계산
			IsDie = true; // 죽음 체크
		}
	}
}

void AMonster_Mike::CalDir()
{
	FVector PlayerPos = MainPlayer->GetActorLocation();  // 플레이어 위치
	FVector MonsterPos = GetActorLocation(); // 몬스터 위치

	FVector MonsterDir = PlayerPos - MonsterPos; // 플레이어 위치 - 몬스터 위치 = 방향 ex) 몬스터가 플레이어에게 향하는 방향
	MonsterDirNormal = MonsterDir.Normalize2DReturn();  // 해당값을 정규화 
}

void AMonster_Mike::CalResult(float _DeltaTime)
{
	
	if (true == IsDie) // 죽으면
	{
		Destroy(0.3f); // 0.3f 뒤에 삭제
	}
	else {
		BaseMove(_DeltaTime);
	}
}

void AMonster_Mike::GroundUp()
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
