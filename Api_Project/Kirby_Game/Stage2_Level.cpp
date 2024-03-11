#include "Stage2_Level.h"

#include "Stage3_Level.h"
#include "Stage2_Map.h"
#include "Kirby_Player.h" 
#include "Kirby_HpBar.h"
#include "Monster_Base.h"
#include "Monster_Fire.h"
#include "Monster_Sir.h"
#include "Box.h"

// ���ҽ� (�̹���, ����) �ε��ϱ� ���� �ʿ��� ���
#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h> // Level 0 EngineDirectory
#include <EngineBase\EngineFile.h> // Level0 EngineFile

UStage2_Level::UStage2_Level()
{
}

UStage2_Level::~UStage2_Level()
{
}

void UStage2_Level::BeginPlay()
{
	ULevel::BeginPlay();

	UEngineDirectory NewPath; // ���� ���� ���

	NewPath.MoveToSearchChild("GameResources");
	NewPath.Move("Stage"); // ���� �̵�
	NewPath.Move("stage2");
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
	UEngineResourcesManager::GetInst().CuttingImage("Sir_Right.png", 10, 10);
	UEngineResourcesManager::GetInst().CuttingImage("Sir_Left.png", 10, 10);
	UEngineResourcesManager::GetInst().CuttingImage("SirMonster_Right.png", 5, 5);
	UEngineResourcesManager::GetInst().CuttingImage("SirMonster_Left.png", 5, 5);
	UEngineResourcesManager::GetInst().CuttingImage("item.png", 3, 1);
}

void UStage2_Level::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}

void UStage2_Level::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
	SetCameraPos({ 0,585}); // ī�޶� ��ġ ����

	// �� ����
	NewMap = SpawnActor<AStage2_Map>();
	NewMap->SetMapImage("stage2_map.png");
	NewMap->SetColMapImage("cor2_map.png");
	NewMap->SwitchDebug();

	// Ŀ��� Ŀ�� ����â Actor ����
	NewPlayer = SpawnActor<AKirby_Player>();
	NewPlayer->SetActorLocation({ 500,1200 });

	NewHpBar = SpawnActor<AKirby_HpBar>();

	NewBase[0] = SpawnActor<AMonster_Base>();
	NewBase[0]->SetActorLocation({ 700,1000 });

	NewBase[1] = SpawnActor<AMonster_Base>();
	NewBase[1]->SetActorLocation({1800,1000});
	
	for (int i = 0; i < Firesize; i++)
	{
		NewFire[i] = SpawnActor<AMonster_Fire>();
		NewFire[i]->SetActorLocation({ 1000 + i * 1000,600 });
	}

	NewFire[5]= SpawnActor<AMonster_Fire>();
	NewFire[5]->SetActorLocation({ 3600,1000 });

	
	NewSir[0] = SpawnActor<AMonster_Sir>();
	NewSir[0]->SetActorLocation({1000,800});
	
	NewSir[1] = SpawnActor<AMonster_Sir>();
	NewSir[1]->SetActorLocation({ 2800,1000 });

	NewSir[2] = SpawnActor<AMonster_Sir>();
	NewSir[2]->SetActorLocation({ 4800,1000 });

	NewSir[3] = SpawnActor<AMonster_Sir>();
	NewSir[3]->SetActorLocation({ 5200,600 });
	
	NewBox = SpawnActor<ABox>();
	NewBox->SetIsItem(true);
	NewBox->SetActorLocation({ 3370,1000 });;
	GEngine->CreateLevel<UStage3_Level>("Stage3_Level"); // stage2_Level ���� ���� �̸� �غ�
}

void UStage2_Level::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);

	GEngine->DestroyLevel("Stage2_Level");
}
