#include "Stage3_Level.h"


#include "Stage3_Map.h"
#include "LastBoss_Level.h"
#include "Kirby_Player.h" 
#include "Kirby_HpBar.h"
#include "Monster_Sir.h"
#include "Monster_Fire.h"
#include "pengi_Ice.h"
#include "IceBox.h"
#include "Box.h"

#include "SubBoss.h"

// ���ҽ� (�̹���, ����) �ε��ϱ� ���� �ʿ��� ���
#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h> // Level 0 EngineDirectory
#include <EngineBase\EngineFile.h> // Level0 EngineFile

UStage3_Level::UStage3_Level()
{
}

UStage3_Level::~UStage3_Level()
{
}

void UStage3_Level::BeginPlay()
{
	ULevel::BeginPlay();

	if (false == LoadCheck)
	{
		LoadCheck = true;
		UEngineDirectory NewPath; // ���� ���� ���

		NewPath.MoveToSearchChild("GameResources");
		NewPath.Move("Stage"); // ���� �̵�
		NewPath.Move("stage3");
		// Ȯ���ڵ� �������� ��ҹ��� ������ ������ �빮�ڷ� �ٲ㼭 ã�����̴�..
		std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);
		// png, bmp ���� 
		// true -> ���� ���� �����ȿ� �̹����� ����Լ��� üũ

		for (UEngineFile& File : AllFileList)
		{
			std::string FullPath = File.GetFullPath(); // ������ ��ü ���
			// �̱��� ���� ����� �Ϻη� GetInst�� ����ϰڽ��ϴ�.
			UEngineResourcesManager::GetInst().LoadImg(FullPath); // �ε� -> Map(Iamges)
		}

		// �̹��� ���� -> Ŀ�� ���� �̹���
		UEngineResourcesManager::GetInst().CuttingImage("Mike_Right.png", 10, 4);
		UEngineResourcesManager::GetInst().CuttingImage("Mike_Left.png", 10, 4);
		UEngineResourcesManager::GetInst().CuttingImage("MikeMonster_Right.png", 5, 3);
		UEngineResourcesManager::GetInst().CuttingImage("MikeMonster_Left.png", 5, 3);
		UEngineResourcesManager::GetInst().CuttingImage("Tock_Right.png", 10, 3);
		UEngineResourcesManager::GetInst().CuttingImage("Tock_Left.png", 10, 3);
	}
}

void UStage3_Level::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}

void UStage3_Level::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
	SetCameraPos({ 0,0 }); // ī�޶� ��ġ ����

	// �� ����
	NewMap = SpawnActor<AStage3_Map>();
	NewMap->SetMapImage("Stage3_Map.png");
	NewMap->SetColMapImage("cor3_Map.png");
	NewMap->SwitchDebug();

	// Ŀ��� Ŀ�� ����â Actor ����
	NewPlayer = SpawnActor<AKirby_Player>();
	NewPlayer->SetActorLocation({ 500,480 });

	NewHpBar = SpawnActor<AKirby_HpBar>();

	SpawnActor<Apengi_Ice>()->SetActorLocation({ 1000,100 });
	SpawnActor<AMonster_Fire>()->SetActorLocation({ 900,100 });
	SpawnActor<AMonster_Sir>()->SetActorLocation({ 3420,100 });
	NewBox[0] = SpawnActor<ABox>();
	NewBox[0]->SetActorLocation({3800,100});

	NewBox[1] = SpawnActor<ABox>();
	NewBox[1]->SetActorLocation({ 3800,300 });

	NewBox[2] = SpawnActor<ABox>();
	NewBox[2]->SetActorLocation({ 4200,100 });

	NewIceBox[0] = SpawnActor<AIceBox>();
	NewIceBox[0]->SetActorLocation({ 800,400 });

	NewIceBox[1] = SpawnActor<AIceBox>();
	NewIceBox[1]->SetActorLocation({ 1200,400 });

	NewIceBox[2] = SpawnActor<AIceBox>();
	NewIceBox[2]->SetActorLocation({ 1200,100 });

	NewIceBox[3] = SpawnActor<AIceBox>();
	NewIceBox[3]->SetActorLocation({ 1200,50 });
	NewIceBox[3]->SetIsItem(true);
	GEngine->CreateLevel<ULastBoss_Level>("LastBoss_Level"); // stage2_Level ���� ���� �̸� �غ�
}

void UStage3_Level::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);

	GEngine->DestroyLevel("Stage3_Level");
}
