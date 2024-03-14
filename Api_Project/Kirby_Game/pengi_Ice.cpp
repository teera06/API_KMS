#include "pengi_Ice.h"
#include "ModeEnum.h"
#include "Monster_Base.h"
#include "Monster_Fire.h"
#include "Monster_Sir.h"
#include "Ice.h"

#include <EngineCore/EngineCore.h> // GetWorld ��� -> Level ���� �̿�
Apengi_Ice::Apengi_Ice()
{
}

Apengi_Ice::~Apengi_Ice()
{
}

void Apengi_Ice::IceState()
{
	scale = 2;
	MonsterRenderer->ChangeAnimation("MonsterIce");
	MonsterRenderer->SetTransform({ {0,1}, {64 * scale, 64 * scale} }); // ������ ��ġ ũ�� 
	IsIce = true;
}

void Apengi_Ice::BeginPlay()
{
	AActor::BeginPlay();

	scale = 5;
	{
		MonsterRenderer = CreateImageRenderer(ERenderOrder::Monster); // �̹��� ���� ����
		MonsterRenderer->SetImage("pengi_Right.png"); // �̹��� Set
		MonsterRenderer->SetTransform({ {0,0}, {64*scale, 64*scale} }); // ������ ��ġ ũ�� 

		MonsterDieRenderer = CreateImageRenderer(ERenderOrder::effect); // �̹��� ���� ����
		MonsterDieRenderer->SetImage("Effects2_Left.png"); // �̹��� Set
		MonsterDieRenderer->SetTransform({ {0,1}, {64 * 2, 64 * 2} }); // ������ ��ġ ũ�� 
		MonsterDieRenderer->ActiveOff();
	}

	{
		MonsterCollision = CreateCollision(ECollisionOrder::iceMonster);
		MonsterCollision->SetScale({ 60, 60 });
		MonsterCollision->SetColType(ECollisionType::Rect);
	}

	AniCreate();
	SoundCreate();
	MonsterRenderer->ChangeAnimation("Idle_Left");
}

void Apengi_Ice::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	GroundUp();
	if (false == IsDie) // Destroy(0.3f); -> ���Ǿ��� ��� move������Ʈ �Ǹ鼭 0.3f�� �Ȱ��� ���� (�ѹ��� �����ؾ���)
	{
		MoveUpdate(_DeltaTime);
	}
	else { // IsDIe�� true�̸� MoveUpdate�� ���� ������ �ȵ� -> Destroy(0.3f) �۵�
		HitDietime -= _DeltaTime;
		if (HitDietime < 0 && false==IsIce)
		{
			SHitDie.On();
		}
		else if (HitDietime < 0 && true == IsIce)
		{
			SIceDie.On();
		}

		if (false == Iseffect && false==IsIce)
		{
			Iseffect = true;
			MonsterDieRenderer->SetActive(true, 0.15f);
			MonsterDieRenderer->ChangeAnimation("effect");
		}
		AddActorLocation(DiePos); // �����鼭 �̵�
	}
}

void Apengi_Ice::AniCreate()
{
	MonsterDieRenderer->CreateAnimation("effect", "Effects2_Left.png", 21, 24, 0.1f, false); // �ȱ�

	MonsterRenderer->CreateAnimation("Idle_Right", "Pengi_Right.png", 0, 0, 0.3f, true);  
	MonsterRenderer->CreateAnimation("Idle_Left", "Pengi_Left.png", 0, 0, 0.3f, true); 
	MonsterRenderer->CreateAnimation("Move_Right", "Pengi_Right.png", 1, 3, 0.3f, true); 
	MonsterRenderer->CreateAnimation("Move_Left", "Pengi_Left.png", 1, 3, 0.3f, true); 
	MonsterRenderer->CreateAnimation("Att_Right", "Pengi_Right.png", 4, 6, 0.15f, false);
	MonsterRenderer->CreateAnimation("Att_Left", "Pengi_Left.png",4, 6, 0.15f, false);

	MonsterRenderer->CreateAnimation("die_Right", "Pengi_Left.png", 7, 8, 0.3f, true); // ���� 
	MonsterRenderer->CreateAnimation("die_Left", "Pengi_Right.png", 7, 8, 0.3f, true); // ���� 
	MonsterRenderer->CreateAnimation("MonsterIce", "Ice_Right.png", 108, 108, false); // ����
	MonsterRenderer->CreateAnimation("Effect", "Effects2_RIght.png", 29, 30, 0.1f, true); // �״� �ִϸ��̼�
}

void Apengi_Ice::SoundCreate()
{
	{
		SHitDie = UEngineSound::SoundPlay("MonsterDie.wav");
		SHitDie.SetVolume(0.6f);
		SHitDie.Off();
	}

	{
		SIceDie = UEngineSound::SoundPlay("MonsterIceDie.wav");
		SIceDie.SetVolume(0.6f);
		SIceDie.Off();
	}

	{
		SIceAtt = UEngineSound::SoundPlay("Ice.wav");
		SIceAtt.SetVolume(0.6f);
		SIceAtt.Off();
	}
}

void Apengi_Ice::IceToMonster(float _DeltaTime)
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
		MonsterRenderer->ChangeAnimation("Effect");
		IsDie = true;
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
		MonsterRenderer->ChangeAnimation("Effect");
		IsDie = true;
	}
	else if (true == MonsterCollision->CollisionCheck(ECollisionOrder::FireMonster, Result))
	{
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AMonster_Fire* Monster = dynamic_cast<AMonster_Fire*>(Ptr);

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
		MonsterRenderer->ChangeAnimation("Effect");
		IsDie = true;
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

		Monster->GetMonsterRenderer()->ChangeAnimation("die_Right"); // �״� �ִϸ��̼�
		DiePos = MonsterDirNormal * -200.0f * _DeltaTime * FVector::Right; // �����鼭 �̵��ϴ� ��ġ ���
		Monster->SetIsDie(true);
		Monster->SetDiePos(DiePos);
		Monster->Destroy(0.3f);
		MonsterRenderer->ChangeAnimation("Effect");
		IsDie = true;
	}
}

void Apengi_Ice::Collisiongather(float _DeltaTime)
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
			MainPlayer->SetHitDir(MonsterDirNormal*FVector::Right);
			MainPlayer->AddHP(GetAtt());
			MainPlayer->HitStart(); // hit ���� ��ŸƮ
			MainPlayer->GetKirbyRender()->SetAlpha(0.5f);
			MainPlayer->GetKirbyCollision()->ActiveOff();

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

void Apengi_Ice::CalResult(float _DeltaTime)
{
	if (true == IsIce)
	{
		IceToMonster(_DeltaTime);
	}
	// ���� ���¿��� ���� �浹�� �ٷ� ���� -> ���� ����Ʈ ������ ���
	Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX() + WallX, GetActorLocation().iY() - 30, Color8Bit::RedA);
	if (ColorR == Color8Bit(255, 0, 0, 0))
	{
		if (true == IsIce)
		{
			IceMove = FVector::Zero;
			MonsterRenderer->ChangeAnimation("Effect");
			IsDie = true;
		}

		MovePos = FVector::Zero;

	}

	if (true == IsDie) // ������
	{
		Destroy(0.3f); // 0.3f �ڿ� ����
	}
	else {
		if (false == IsIce) // �װų�, �������°� �ƴϸ� �Ϲ� �ൿ
		{
			std::vector<UCollision*> Result;
			if (true == MonsterCollision->CollisionCheck(ECollisionOrder::IceBox, Result, MovePos * FVector::Right))
			{
				return;
			}
			AddActorLocation(MovePos);
		}
		else {
			MovePos = FVector::Zero;
			AddActorLocation(IceMove);
		}
	}
}

void Apengi_Ice::CalDir(float _DeltaTime)
{
	FVector PlayerPos = MainPlayer->GetActorLocation();  // �÷��̾� ��ġ
	FVector MonsterPos = GetActorLocation(); // ���� ��ġ

	FVector MosterXL = MonsterPos + FVector::Left * sight; // ���� ���� �÷��̾� �ν� �þ� X��
	FVector MosterXR = MonsterPos + FVector::Right * sight; // ���� ������ �÷��̾� �ν� �þ� X��

	FVector AttXL = MonsterPos + FVector::Left * AttRange; // ���� ���� �÷��̾� ���� ����
	FVector AttXR = MonsterPos + FVector::Right * AttRange; // ���� ������ �÷��̾� ���� ����

	FVector PlayerX = PlayerPos * FVector::Right; // �÷��̾� ��ġ X��

	FVector MonsterDir = PlayerPos - MonsterPos; // �÷��̾� ��ġ - ���� ��ġ = ���� ex) ���Ͱ� �÷��̾�� ���ϴ� ����
	MonsterDirNormal = MonsterDir.Normalize2DReturn();  // �ش簪�� ����ȭ 

	MovePos = FVector::Zero; // �÷��̾� �߰� �� �̵�

	if (MosterXL.iX() < PlayerX.iX() && MosterXR.iX() > PlayerX.iX()) // ���� �þ߿� ������ ��� X�� ���� ����, ������
	{
		if (MonsterDirNormal.iX() == -1  && IsIce == false) // ���� ����
		{
			MonsterRenderer->ChangeAnimation("Move_Left");
			WallX = -20;
		}
		else if ((MonsterDirNormal.iX() == 1 || MonsterDirNormal.iX() == 0) && IsIce == false) { // ������ ����
			MonsterRenderer->ChangeAnimation("Move_Right");
			WallX = 20;
		}
		MovePos += MonsterDirNormal * _DeltaTime * MoveSpeed * FVector::Right; // ���Ͱ� �÷��̾��� Y�൵ �ν��� �� ������ FVector::Right �� ���� X�ุ �߰�
	}
	else { // �÷��̾ ���� �þ� ���� ��� ���� �ൿ����
		if (MonsterDirNormal.iX() == -1 && IsIce == false) // ���� ����
		{
			MonsterRenderer->ChangeAnimation("Idle_Left");
			WallX = -20;
		}
		else if (MonsterDirNormal.iX() == 1 && IsIce == false) { // ������ ����
			MonsterRenderer->ChangeAnimation("Idle_Right");
			WallX = 20;
		}
	}

	// �÷��̾ ���� ����
	if (AttXL.iX() < PlayerX.iX() && AttXR.iX() > PlayerX.iX() && MainPlayer->GetActorLocation().iY()>=GetActorLocation().iY()-30) // ���� �þ߿� ������ ��� X�� ���� ����, ������
	{
		IsAtt = true;
	}
}

void Apengi_Ice::IceAtt()
{

	if (false == IceAttcheck)
	{
		IceAttcheck = true;
		AIce* NewIce = GetWorld()->SpawnActor<AIce>();
		NewIce->SetActorLocation(this->GetActorLocation());
		NewIce->SetOwner(EIceOwner::iceMonster);
		if (MonsterDirNormal.iX() == -1 && IsIce == false) // ���� ����
		{
			MonsterRenderer->ChangeAnimation("Att_Left");
			NewIce->SetDir(FVector::Left);
		}
		else if ((MonsterDirNormal.iX() == 1 || MonsterDirNormal.iX() == 0) && IsIce == false) { // ������ ����
			MonsterRenderer->ChangeAnimation("Att_Right");
			NewIce->SetDir(FVector::Right);
		}
	}

	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		IsAtt = false;
		skillcooldowntime = 6.0f;
	}
}

void Apengi_Ice::GroundUp()
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

void Apengi_Ice::MoveUpdate(float _DeltaTime)
{
	AddActorLocation(GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime)); // �߷� �ۿ�

	skillcooldowntime -= _DeltaTime;
	if (true == IsAtt && skillcooldowntime<0.0f && false == BaseOn && false==IsIce)
	{
		MovePos = FVector::Zero;
		SIceAtt.On();
		IceAtt();
	}
	else {
		SIceAtt.Replay();
		SIceAtt.Off();
		IceAttcheck = false;
		CalDir(_DeltaTime);
		Collisiongather(_DeltaTime);
		CalResult(_DeltaTime);
	}
}




