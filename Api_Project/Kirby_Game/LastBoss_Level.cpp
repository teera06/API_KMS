#include "LastBoss_Level.h"

#include "Last_Map.h"
#include "Kirby_Player.h" 
#include "Kirby_HpBar.h"
#include "Hammer.h"
#include "MainBoss.h"
#include "BossHpBar.h"



// ���ҽ� (�̹���, ����) �ε��ϱ� ���� �ʿ��� ���
#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h> // Level 0 EngineDirectory
#include <EngineBase\EngineFile.h> // Level0 EngineFile
ULastBoss_Level::ULastBoss_Level()
{
}

ULastBoss_Level::~ULastBoss_Level()
{
}

void ULastBoss_Level::BeginPlay()
{
	ULevel::BeginPlay();

	UEngineDirectory NewPath; // ���� ���� ���

	NewPath.MoveToSearchChild("GameResources");
	NewPath.Move("Stage"); // ���� �̵�
	NewPath.Move("LastStage");

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
	UEngineResourcesManager::GetInst().CuttingImage("Hammer_Right.png", 10, 13);
	UEngineResourcesManager::GetInst().CuttingImage("Hammer_Left.png", 10, 13);
	UEngineResourcesManager::GetInst().CuttingImage("King_Right.png", 10, 8);
	UEngineResourcesManager::GetInst().CuttingImage("King_Left.png", 10, 8);
}

void ULastBoss_Level::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (true == NewPlayer->GetMainBossEvent() && false == EventCheck)
	{
		EventCheck = true;
		NewBossHpBar->SetActive(true, 1.0f);
		NewMainBoss->SetActorLocation({ 900,100 });
		NewMainBoss->SetActive(true, 1.0f);
	}
}

void ULastBoss_Level::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
	SetCameraPos({100,-40 }); // ī�޶� ��ġ ����

	// �� ����
	NewMap = SpawnActor < ALast_Map > ();
	NewMap->SetMapImage("LastMap.png");
	
	NewMap->SetColMapImage("Cor4_Map.png");
	NewMap->SwitchDebug();

	// Ŀ��� Ŀ�� ����â Actor ����
	NewPlayer = SpawnActor<AKirby_Player>();
	NewPlayer->SetActorLocation({ 400,400 });

	NewHpBar = SpawnActor<AKirby_HpBar>();

	SpawnActor<AHammer>()->SetActorLocation({610,350});
	
	NewMainBoss = SpawnActor<AMainBoss>();
	NewMainBoss->ActiveOff();
	NewBossHpBar=SpawnActor<ABossHpBar>();
	NewBossHpBar->ActiveOff();
}

void ULastBoss_Level::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);

	GEngine->DestroyLevel("LastBoss_Level"); // Level ����
}
