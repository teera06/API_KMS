#include "Monster_Fire.h"

#include "Monster_Base.h"
#include "ModeEnum.h"

#include "pengi_Ice.h"
AMonster_Fire::AMonster_Fire()
{
}

AMonster_Fire::~AMonster_Fire()
{
}

void AMonster_Fire::IceState()
{
	scale = 2;
	MonsterRenderer->ChangeAnimation("MonsterIce");
	MonsterRenderer->SetTransform({ {0,1}, {64 * scale, 64 * scale} }); // ������ ��ġ ũ�� 
	IsIce = true;
}

void AMonster_Fire::BeginPlay()
{
	AActor::BeginPlay();

	scale = 3; // ��� ũ��
	// ������
	{
		MonsterRenderer = CreateImageRenderer(ERenderOrder::Monster); // �̹��� ���� ����
		MonsterRenderer->SetImage("Flamer_Right.png"); // �̹��� Set
		MonsterRenderer->SetTransform({ {0,1}, {64 * scale, 64 * scale} }); // ������ ��ġ ũ�� 
	}

	// �ݸ���
	{
		MonsterCollision = CreateCollision(ECollisionOrder::FireMonster);
		MonsterCollision->SetScale({ 70, 70 });
		MonsterCollision->SetColType(ECollisionType::Rect);
	}

	// �ִϸ��̼� �����
	AniCreate();

	MonsterRenderer->ChangeAnimation("Move_Left");
}

void AMonster_Fire::Tick(float _DeltaTime)
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

void AMonster_Fire::MoveUpdate(float _DeltaTime)
{
	CalDir(_DeltaTime);
	Collisiongather(_DeltaTime);
	CalResult(_DeltaTime);
	
}

void AMonster_Fire::BaseMove(float _DeltaTime)
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
		if (StartDir.iX() == -1 && IsIce == false) // ���� ���⿡ ���� ���� ����
		{
			MonsterRenderer->ChangeAnimation("Move_Left");
			WallX = -20;
		}
		else if (StartDir.iX() == 1 && IsIce == false) { // ������ ���⿡ ���� ���� ����
			MonsterRenderer->ChangeAnimation("Move_Right");
			WallX = 20;
		}

		Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX() + WallX, GetActorLocation().iY() - 30, Color8Bit::RedA);

		if (ColorR == Color8Bit(255, 0, 0, 0)) // �� �ȼ� �浹
		{
			if (true == IsIce) // ���� ������ ���
			{
				IceMove = FVector::Zero; // ������ 0
				Destroy(); // ����
			}
			else { // �ƴ� ���� ���� ��ȯ
				StartDir.X *= -1;
				checkLocation = false; // ���Ͱ� ���� ������ ������ȯ�� ���ÿ� �ٽ� ��ġ ����
			}
		}
		else { // �浹���� ���� ���
			Move += StartDir * _DeltaTime * MoveSpeed;
		}

		if (true == IsIce) // ���� ������ ��� ���� ���� ���� ������ �������� �ؼ��� �ȵȴ�.
		{
			Move = FVector::Zero;
		}

		AddActorLocation(Move); // ���� ������ ���
	}
}

void AMonster_Fire::AniCreate()
{
	// �⺻ �ȴ� ���

	MonsterRenderer->CreateAnimation("Move_Right", "Flamer_Right.png", 0, 3, 0.1f, true); // �ȱ�
	MonsterRenderer->CreateAnimation("Move_Left", "Flamer_Left.png", 0, 3, 0.1f, true); // �ȱ�
	MonsterRenderer->CreateAnimation("Att_Right", "Flamer_Right.png", 6, 13, 0.1f, true); // �ȱ�
	MonsterRenderer->CreateAnimation("Att_Left", "Flamer_Left.png", 6, 13, 0.1f, true); // �ȱ�
	MonsterRenderer->CreateAnimation("die_Right", "Flamer_Right.png", 4, 5, 0.2f, false); // �״� �ִϸ��̼�
	MonsterRenderer->CreateAnimation("die_Left", "Flamer_Left.png", 4, 5, 0.2f, false); // �״� �ִϸ��̼�
	MonsterRenderer->CreateAnimation("MonsterIce", "Ice_Right.png", 108, 108, false); // ����
}

void AMonster_Fire::IceToMonster(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (true == MonsterCollision->CollisionCheck(ECollisionOrder::Monster, Result)) // ���� ���� ���¿��� �÷��̾�� �浹
	{
		//MonsterRenderer->SetAlpha(0.5f+nf);
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AMonster_Base* Monster = dynamic_cast<AMonster_Base*>(Ptr);

		// ����ڵ�

		if (nullptr == Monster)
		{
			MsgBoxAssert("���ͺ��̽� �÷��̾� �ν� ����");
		}
		Monster->GetMonsterRenderer()->ChangeAnimation("die_Right"); // �״� �ִϸ��̼�
		DiePos = MonsterDirNormal * -200.0f * _DeltaTime * FVector::Right; // �����鼭 �̵��ϴ� ��ġ ���
		Monster->SetIsDie(true);
		Monster->SetDiePos(DiePos);
		Monster->Destroy(0.3f);
		Destroy();
	}
	else if (true == MonsterCollision->CollisionCheck(ECollisionOrder::iceMonster, Result))
	{
		//MonsterRenderer->SetAlpha(0.5f+nf);
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		Apengi_Ice* Monster = dynamic_cast<Apengi_Ice*>(Ptr);

		// ����ڵ�

		if (nullptr == Monster)
		{
			MsgBoxAssert("���ͺ��̽� �÷��̾� �ν� ����");
		}

		Monster->GetMonsterRenderer()->ChangeAnimation("die_Right"); // �״� �ִϸ��̼�
		DiePos = MonsterDirNormal * -200.0f * _DeltaTime * FVector::Right; // �����鼭 �̵��ϴ� ��ġ ���
		Monster->SetIsDie(true);
		Monster->SetDiePos(DiePos);
		Monster->Destroy(0.3f);
		Destroy();
	}
}

void AMonster_Fire::Collisiongather(float _DeltaTime)
{
	// �ݸ��� 
	std::vector<UCollision*> Result;
	if (true == MonsterCollision->CollisionCheck(ECollisionOrder::kirby, Result) && IsIce == false) // ���� ���� ���¿��� �÷��̾�� �浹
	{
		if (true == GetBaseOnOff()) // ������ ���� ���� �浹 -> ���ʹ� �÷��̾�� �浹�� ��� �ٷ� ����
		{
			Destroy();
		}
		else {// �Ϲ����� �÷��̿��� �浹
			MainPlayer->Sethitstate(true); // �÷��̾� �浹 üũ
			MainPlayer->GetKirbyRender()->SetAlpha(0.5f);
			MainPlayer->GetKirbyCollision()->ActiveOff();
			MainPlayer->AddHP(-20);
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
	else if ((true == MonsterCollision->CollisionCheck(ECollisionOrder::kirby, Result) && IsIce == true)) { // ���� ���·� Ŀ��� �浹 �ϴ� ���
		// ���� ���� �϶� ������ ���
		if (MonsterDirNormal.iX() == -1) // ���Ͱ� �÷��̾ ���ϴ� ������ �ݴ� �������� ���� �ۿ�
		{
			WallX = 20;
			IceMove = FVector::Right * IceSpeed * _DeltaTime;

		}
		else {
			WallX = -20;
			IceMove = FVector::Left * IceSpeed * _DeltaTime;
		}
	}
}

void AMonster_Fire::CalDir(float _DeltaTime)
{
	FVector PlayerPos = MainPlayer->GetActorLocation();  // �÷��̾� ��ġ
	FVector MonsterPos = GetActorLocation(); // ���� ��ġ

	FVector MosterXL = MonsterPos + FVector::Left * sight; // ���� ���� �÷��̾� �ν� �þ� X��
	FVector MosterXR = MonsterPos + FVector::Right * sight; // ���� ������ �÷��̾� �ν� �þ� X��

	
	FVector PlayerX = PlayerPos * FVector::Right; // �÷��̾� ��ġ X��

	FVector MonsterDir = PlayerPos - MonsterPos; // �÷��̾� ��ġ - ���� ��ġ = ���� ex) ���Ͱ� �÷��̾�� ���ϴ� ����
	MonsterDirNormal = MonsterDir.Normalize2DReturn();  // �ش簪�� ����ȭ 

	MovePos = FVector::Zero; // �÷��̾� �߰� �� �̵�

	if (MosterXL.iX() < PlayerX.iX() && MosterXR.iX() > PlayerX.iX()) // ���� �þ߿� ������ ��� X�� ���� ����, ������
	{
		IsAtt = true;
		MoveSpeed = 100.0f;
		if (MonsterDirNormal.iX() == -1 && IsIce == false) // ���� ����
		{
			MonsterRenderer->ChangeAnimation("Att_Left");
			WallX = -20;
		}
		else if (MonsterDirNormal.iX() == 1 && IsIce == false) { // ������ ����
			MonsterRenderer->ChangeAnimation("Att_Right");
			WallX = 20;
		}
		MovePos += MonsterDirNormal * _DeltaTime * MoveSpeed; // ���Ͱ� �÷��̾��� Y�൵ �ν��� �� ������ FVector::Right �� ���� X�ุ �߰�
	}
	else {
		//MovePos = FVector::Zero;
		IsAtt = false;
		if (MonsterDirNormal.iX() == -1 && IsIce == false) // ���� ����
		{
			MonsterRenderer->ChangeAnimation("Move_Left");
			WallX = -20;
		}
		else if (MonsterDirNormal.iX() == 1 && IsIce == false) { // ������ ����
			MonsterRenderer->ChangeAnimation("Move_Right");
			WallX = 20;
		}
	}
}

void AMonster_Fire::CalResult(float _DeltaTime)
{
	if (true == IsIce)
	{
		IceToMonster(_DeltaTime);
	}

	// ���� ���¿��� ���� �浹�� �ٷ� ���� -> ���� ����Ʈ ������ ����
	Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX() + WallX, GetActorLocation().iY() - 30, Color8Bit::RedA);
	if (ColorR == Color8Bit(255, 0, 0, 0))
	{
		if (true == IsIce)
		{
			IceMove = FVector::Zero;
			Destroy();
		}
	}

	if (true == IsDie) // ������
	{
		Destroy(0.3f); // 0.3f �ڿ� ����
	}
	else {
		if (false == IsIce) // �װų�, �������°� �ƴϸ� �Ϲ� �ൿ
		{
			if (true == IsAtt)
			{
				AddActorLocation(MovePos);
			}
			else {
				BaseMove(_DeltaTime);
			}
		}
		else {
			AddActorLocation(IceMove);
		}
	}
}

void AMonster_Fire::GroundUp()
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