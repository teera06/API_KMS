#include "LastBoss_Level.h"



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
}

void ULastBoss_Level::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}

void ULastBoss_Level::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
	//SetCameraPos({ 0,400 }); // ī�޶� ��ġ ����

	// �� ����
	//NewMap = SpawnActor<AStage1_MAP>();
	//NewMap->SetMapImage("stage1_map.png");
	//Map->SetMapImage("stage2_map.png");
	//NewMap->SetColMapImage("cor_map.png");
	//NewMap->SwitchDebug();

	// Ŀ��� Ŀ�� ����â Actor ����
	//NewPlayer = SpawnActor<AKirby_Player>();
	//NewPlayer->SetActorLocation({ 500,1000 });

	//NewHpBar = SpawnActor<AKirby_HpBar>();
}

void ULastBoss_Level::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);

	//GEngine->DestroyLevel("LastBoss_Level"); // Level ����
}
