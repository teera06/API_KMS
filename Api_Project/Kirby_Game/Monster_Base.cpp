#include "Monster_Base.h"
#include "ModeEnum.h"

#include "pengi_Ice.h"
#include "Monster_Fire.h"
#include "Monster_Sir.h"

AMonster_Base::AMonster_Base()
{
}

AMonster_Base::~AMonster_Base()
{
}

// �� ����
void AMonster_Base::IceState()
{
	scale = 2;
	MonsterRenderer->ChangeAnimation("MonsterIce");
	MonsterRenderer->SetTransform({ {0,1}, {64*scale, 64*scale} }); // ������ ��ġ ũ�� 
	IsIce = true;
}

void AMonster_Base::BeginPlay()
{
	AActor::BeginPlay();

	scale = 3; // ��� ũ��
	// ������
	{
		MonsterRenderer = CreateImageRenderer(ERenderOrder::Monster); // �̹��� ���� ����
		MonsterRenderer->SetImage("Dee_Right.png"); // �̹��� Set
		MonsterRenderer->SetTransform({ {0,1}, {64* scale, 64* scale} }); // ������ ��ġ ũ�� 

		MonsterDieRenderer = CreateImageRenderer(ERenderOrder::effect); // �̹��� ���� ����
		MonsterDieRenderer->SetImage("Effects2_Left.png"); // �̹��� Set
		MonsterDieRenderer->SetTransform({ {0,1}, {64 * 2, 64 * 2} }); // ������ ��ġ ũ�� 
		MonsterDieRenderer->ActiveOff();
	}

	// �ݸ���
	{
		MonsterCollision = CreateCollision(ECollisionOrder::Monster);
		MonsterCollision->SetScale({ 60, 60 });
		MonsterCollision->SetColType(ECollisionType::Rect);
	}

	// �ִϸ��̼� �����
	AniCreate();
	MonsterRenderer->ChangeAnimation("Move_Left");
}


void AMonster_Base::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	GroundUp();
	if (false == checkLocation) // ù ������Ʈ��, ���� �浹�ÿ��� ����
	{
		// �̵� ���� ����
		CurLocation = GetActorLocation()*FVector::Right; 
		RangeXL = CurLocation + (FVector::Left * RangeX);
		RangeXR = CurLocation + (FVector::Right * RangeX);
	}

	if (false == IsDie) // Destroy(0.3f); -> ���Ǿ��� ��� move������Ʈ �Ǹ鼭 0.3f�� �Ȱ��� ���� (�ѹ��� �����ؾ���)
	{
		checkLocation = true;
		MoveUpdate(_DeltaTime);
	}
	else { // IsDIe�� true�̸� MoveUpdate�� ���� ������ �ȵ� -> Destroy(0.3f) �۵�
		if (false == Iseffect && false==IsIce)
		{
			Iseffect = true;
			MonsterDieRenderer->SetActive(true, 0.15f);
			MonsterDieRenderer->ChangeAnimation("effect");
		}
		AddActorLocation(DiePos); 
	}
}

void AMonster_Base::MoveUpdate(float _DeltaTime)
{
	AddActorLocation(GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime)); // �߷� �ۿ�
	
	CalDir();
	Collisiongather(_DeltaTime);
	CalResult(_DeltaTime);
}

void AMonster_Base::AniCreate()
{
	// �⺻ �ȴ� ���
	MonsterDieRenderer->CreateAnimation("effect", "Effects2_Left.png", 21, 24, 0.1f, false); // �ȱ�

	MonsterRenderer->CreateAnimation("Move_Right", "Dee_Right.png", 0, 4, 0.1f, true); // �ȱ�
	MonsterRenderer->CreateAnimation("Move_Left", "Dee_Left.png", 0, 4, 0.1f, true); // �ȱ�
	MonsterRenderer->CreateAnimation("MonsterIce", "Ice_Right.png", 108, 108, false); // ����
	MonsterRenderer->CreateAnimation("die_Right", "Dee_Right.png", 5, 5,0.2f, false); // �״� �ִϸ��̼�
	MonsterRenderer->CreateAnimation("die_Left", "Dee_Left.png", 5, 5, 0.2f, false); // �״� �ִϸ��̼�
	MonsterRenderer->CreateAnimation("Effect", "Effects2_RIght.png", 29, 30, 0.1f, true); // �״� �ִϸ��̼�
}

void AMonster_Base::IceToMonster(float _DeltaTime) // ������ ���¿��� �ٸ� ���Ϳ��� �浹 ����
{
	std::vector<UCollision*> Result;
	if (true == MonsterCollision->CollisionCheck(ECollisionOrder::Monster, Result)) // �Ϲ� ������ ���
	{
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AMonster_Base* Monster = dynamic_cast<AMonster_Base*>(Ptr);

		// ����ڵ�

		if (nullptr == Monster)
		{
			MsgBoxAssert("���ͺ��̽� �÷��̾� �ν� ����");
		}
		DiePos = MonsterDirNormal * -200.0f * _DeltaTime * FVector::Right; // �����鼭 �̵��ϴ� ��ġ ���

		Monster->GetMonsterRenderer()->ChangeAnimation("die_Right"); // �״� �ִϸ��̼�
		Monster->SetIsDie(true);
		Monster->SetDiePos(DiePos);
		Monster->Destroy(0.3f);

		MonsterRenderer->ChangeAnimation("Effect");
		IsDie = true;
		UEngineSound::SoundPlay("MonsterIceDie.wav");
	}
	else if (true == MonsterCollision->CollisionCheck(ECollisionOrder::iceMonster, Result))
	{
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		Apengi_Ice* Monster = dynamic_cast<Apengi_Ice*>(Ptr);

		// ����ڵ�

		if (nullptr == Monster)
		{
			MsgBoxAssert("���ͺ��̽� �÷��̾� �ν� ����");
		}

		DiePos = MonsterDirNormal * -200.0f * _DeltaTime * FVector::Right; // �����鼭 �̵��ϴ� ��ġ ���
		
		Monster->GetMonsterRenderer()->ChangeAnimation("die_Right"); // �״� �ִϸ��̼�
		Monster->SetIsDie(true);
		Monster->SetDiePos(DiePos);
		Monster->Destroy(0.3f);
		
		MonsterRenderer->ChangeAnimation("Effect");
		IsDie = true;
		UEngineSound::SoundPlay("MonsterIceDie.wav");
	}
	else if (true == MonsterCollision->CollisionCheck(ECollisionOrder::FireMonster, Result))
	{
		//MonsterRenderer->SetAlpha(0.5f+nf);
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AMonster_Fire* Monster = dynamic_cast<AMonster_Fire*>(Ptr);

		// ����ڵ�

		if (nullptr == Monster)
		{
			MsgBoxAssert("���ͺ��̽� �÷��̾� �ν� ����");
		}
		DiePos = MonsterDirNormal * -200.0f * _DeltaTime * FVector::Right; // �����鼭 �̵��ϴ� ��ġ ���
		
		Monster->GetMonsterRenderer()->ChangeAnimation("die_Right"); // �״� �ִϸ��̼�
		Monster->SetIsDie(true);
		Monster->SetDiePos(DiePos);
		Monster->Destroy(0.3f);
		
		MonsterRenderer->ChangeAnimation("Effect");
		IsDie = true;
		UEngineSound::SoundPlay("MonsterIceDie.wav");
	}
	else if (true == MonsterCollision->CollisionCheck(ECollisionOrder::SirMonster, Result))
	{
		//MonsterRenderer->SetAlpha(0.5f+nf);
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AMonster_Sir* Monster = dynamic_cast<AMonster_Sir*>(Ptr);

		// ����ڵ�

		if (nullptr == Monster)
		{
			MsgBoxAssert("���ͺ��̽� �÷��̾� �ν� ����");
		}
		DiePos = MonsterDirNormal * -200.0f * _DeltaTime * FVector::Right; // �����鼭 �̵��ϴ� ��ġ ���
		
		Monster->GetMonsterRenderer()->ChangeAnimation("die_Right"); // �״� �ִϸ��̼�
		Monster->SetIsDie(true);
		Monster->SetDiePos(DiePos);
		Monster->Destroy(0.3f);
		
		MonsterRenderer->ChangeAnimation("Effect");
		IsDie = true;
		UEngineSound::SoundPlay("MonsterIceDie.wav");
	}
}

void AMonster_Base::Collisiongather(float _DeltaTime)
{
	// �ݸ��� 
	std::vector<UCollision*> Result;
	if (true == MonsterCollision->CollisionCheck(ECollisionOrder::kirby, Result) && IsIce == false) // ���� ���� ���¿��� �÷��̾�� �浹
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

void AMonster_Base::CalDir() // �÷��̾� ��ġ Ȯ��
{
	FVector PlayerPos = MainPlayer->GetActorLocation();  // �÷��̾� ��ġ
	FVector MonsterPos = GetActorLocation(); // ���� ��ġ

	FVector MonsterDir = PlayerPos - MonsterPos; // �÷��̾� ��ġ - ���� ��ġ = ���� ex) ���Ͱ� �÷��̾�� ���ϴ� ����
	MonsterDirNormal = MonsterDir.Normalize2DReturn();  // �ش簪�� ����ȭ 
}

void AMonster_Base::CalResult(float _DeltaTime)
{
	if (true == IsIce)
	{
		IceToMonster(_DeltaTime);
	}

	// ���� ���¿��� ���� �浹�� �ٷ� ���� -> ���� ����Ʈ ������ ���
	Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX() + WallX, GetActorLocation().iY() - 30, Color8Bit::RedA);
	if (ColorR == Color8Bit(255, 0, 0, 0) && true==IsIce)
	{
		UEngineSound::SoundPlay("MonsterIceDie.wav");
		IceMove = FVector::Zero;
		MonsterRenderer->ChangeAnimation("Effect");
		IsDie = true;
	}

	if (true == IsDie) // ������
	{
		UEngineSound::SoundPlay("MonsterDie.wav");
		Destroy(0.3f); // 0.3f �ڿ� ����
	}
	else {
		if (false == IsIce) // �װų�, �������°� �ƴϸ� �Ϲ� �ൿ
		{
			BaseMove(_DeltaTime);
		}
		else {
			AddActorLocation(IceMove);
		}
	}
}

void AMonster_Base::GroundUp()
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

// �⺻ �ൿ ����
void AMonster_Base::BaseMove(float _DeltaTime)
{

	FVector Move = FVector::Zero;
	FVector CurX = GetActorLocation() * FVector::Right;

	if (RangeXL.iX() >= CurX.iX() || RangeXR.iX()<=CurX.iX()) // �⺻ ���� �̵� ���� �¿� +-100 �� ���� ����� ��� -> ���� ��ȯ
	{
		StartDir.X *= -1;
		AddActorLocation(StartDir*FVector::Right * _DeltaTime * 100.0f); // �ش� ���� ����� �Ʒ��� else���� ������ �� �ֱ⿡ �ٽ� ���������� �ű�� ����
		return;
	}
	else
	{
		if (StartDir.iX() == -1 && IsIce == false) // ���� ���⿡ ���� ���� ����
		{
			MonsterRenderer->ChangeAnimation("Move_Left");
			WallX = -20;
		}
		else if(StartDir.iX() == 1 && IsIce == false){ // ������ ���⿡ ���� ���� ����
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




