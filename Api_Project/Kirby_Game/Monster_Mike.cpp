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

	scale = 2; // ��� ũ��
	// ������
	{
		MonsterRenderer = CreateImageRenderer(ERenderOrder::Monster); // �̹��� ���� ����
		MonsterRenderer->SetImage("MikeMonster_Right.png"); // �̹��� Set
		MonsterRenderer->SetTransform({ {0,1}, {64 * scale, 64 * scale} }); // ������ ��ġ ũ�� 
	}

	// �ݸ���
	{
		MonsterCollision = CreateCollision(ECollisionOrder::MikeMonster);
		MonsterCollision->SetScale({ 60, 60 });
		MonsterCollision->SetColType(ECollisionType::Rect);
	}

	// �ִϸ��̼� �����
	AniCreate();

	MonsterRenderer->ChangeAnimation("Move_Left");

}

void AMonster_Mike::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	GroundUp();
	if (false == checkLocation) // ù ������Ʈ��, ���� �浹�ÿ��� ����
	{
		// �̵� ���� ����
		CurLocation = GetActorLocation() * FVector::Right;
		RangeXL = CurLocation + (FVector::Left * RangeX);
		RangeXR = CurLocation + (FVector::Right * RangeX);
	}

	if (false == IsDie) // Destroy(0.3f); -> ���Ǿ��� ��� move������Ʈ �Ǹ鼭 0.3f�� �Ȱ��� ���� (�ѹ��� �����ؾ���)
	{
		checkLocation = true;
		MoveUpdate(_DeltaTime);
	}
	else { // IsDIe�� true�̸� MoveUpdate�� ���� ������ �ȵ� -> Destroy(0.3f) �۵�
		AddActorLocation(DiePos); // �����鼭 �̵�
	}
}

void AMonster_Mike::MoveUpdate(float _DeltaTime)
{
	AddActorLocation(GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime)); // �߷� �ۿ�

	CalDir();
	Collisiongather(_DeltaTime);
	CalResult(_DeltaTime);
}

void AMonster_Mike::BaseMove(float _DeltaTime)
{
	FVector Move = FVector::Zero;
	FVector CurX = GetActorLocation() * FVector::Right;

	if (RangeXL.iX() >= CurX.iX() || RangeXR.iX() <= CurX.iX()) // �⺻ ���� �̵� ���� �¿� +-100 �� ���� ����� ��� -> ���� ��ȯ
	{
		StartDir.X *= -1;
		AddActorLocation(StartDir * FVector::Right * _DeltaTime * 100.0f); // �ش� ���� ����� �Ʒ��� else���� ������ �� �ֱ⿡ �ٽ� ���������� �ű�� ����
		return;
	}
	else
	{
		if (StartDir.iX() == -1) // ���� ���⿡ ���� ���� ����
		{
			MonsterRenderer->ChangeAnimation("Move_Left");
			WallX = -20;
		}
		else if (StartDir.iX() == 1) { // ������ ���⿡ ���� ���� ����
			MonsterRenderer->ChangeAnimation("Move_Right");
			WallX = 20;
		}

		Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX() + WallX, GetActorLocation().iY() - 30, Color8Bit::RedA);

		if (ColorR == Color8Bit(255, 0, 0, 0)) // �� �ȼ� �浹
		{
			StartDir.X *= -1;
			checkLocation = false; // ���Ͱ� ���� ������ ������ȯ�� ���ÿ� �ٽ� ��ġ ����
		}
		else { // �浹���� ���� ���
			Move += StartDir * _DeltaTime * MoveSpeed;
		}

		AddActorLocation(Move); // ���� ������ ���
	}
}

void AMonster_Mike::AniCreate()
{
	// �⺻ �ȴ� ���
	MonsterRenderer->CreateAnimation("Move_Right", "MikeMonster_Right.png", { 0,1,2,5,6 }, 0.1f, true); // �ȱ�
	MonsterRenderer->CreateAnimation("Move_Left", "MikeMonster_Left.png", {0,1,2,5,6}, 0.1f, true); // �ȱ�
	MonsterRenderer->CreateAnimation("die_Right", "MikeMonster_Right.png", 4, 4, 0.2f, false); // �״� �ִϸ��̼�
	MonsterRenderer->CreateAnimation("die_Left", "MikeMonster_Left.png", 4, 4, 0.2f, false); // �״� �ִϸ��̼�
}

void AMonster_Mike::Collisiongather(float _DeltaTime)
{
	// �ݸ��� 
	std::vector<UCollision*> Result;
	if (true == MonsterCollision->CollisionCheck(ECollisionOrder::kirby, Result)) // ���� ���� ���¿��� �÷��̾�� �浹
	{
		if (true == BaseOn) // ����� ���� ���� �浹 -> ���ʹ� �÷��̾�� �浹�� ��� �ٷ� ����
		{
			Destroy();
		}
		else {// �Ϲ����� �÷��̿��� �浹
			MainPlayer->Sethitstate(true); // �÷��̾� �浹 üũ
			MainPlayer->SetHitDir(MonsterDirNormal * FVector::Right);
			MainPlayer->GetKirbyRender()->SetAlpha(0.5f);
			MainPlayer->GetKirbyCollision()->ActiveOff();
			MainPlayer->AddHP(GetAtt());
			MainPlayer->HitStart(); // hit ���� ��ŸƮ
			if (MonsterDirNormal.iX() == -1) // ���Ͱ� �÷��̾ ���ϴ� ������ �ݴ� �������� ���� �ۿ�
			{
				MonsterRenderer->ChangeAnimation("die_Left"); // �״� �ִϸ��̼�

			}
			else {
				MonsterRenderer->ChangeAnimation("die_Right"); // �״� �ִϸ��̼�
			}
			DiePos = MonsterDirNormal * -200.0f * _DeltaTime * FVector::Right; // �����鼭 �̵��ϴ� ��ġ ���
			IsDie = true; // ���� üũ
		}
	}
}

void AMonster_Mike::CalDir()
{
	FVector PlayerPos = MainPlayer->GetActorLocation();  // �÷��̾� ��ġ
	FVector MonsterPos = GetActorLocation(); // ���� ��ġ

	FVector MonsterDir = PlayerPos - MonsterPos; // �÷��̾� ��ġ - ���� ��ġ = ���� ex) ���Ͱ� �÷��̾�� ���ϴ� ����
	MonsterDirNormal = MonsterDir.Normalize2DReturn();  // �ش簪�� ����ȭ 
}

void AMonster_Mike::CalResult(float _DeltaTime)
{
	
	if (true == IsDie) // ������
	{
		Destroy(0.3f); // 0.3f �ڿ� ����
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
