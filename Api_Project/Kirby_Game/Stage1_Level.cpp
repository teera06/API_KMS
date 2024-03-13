#include "Stage1_Level.h"

// Actor
#include "Stage1_MAP.h" 
#include "Stage2_Level.h"

#include "Kirby_Player.h"
#include "Monster_Base.h"
#include "pengi_Ice.h"
#include "Monster_Fire.h"
#include "Kirby_HpBar.h"

// ���ҽ� (�̹���, ����) �ε��ϱ� ���� �ʿ��� ���
#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h> // Level 0 EngineDirectory
#include <EngineBase\EngineFile.h> // Level0 EngineFile

bool UStage1_Level::LoadCheck = false;

UStage1_Level::UStage1_Level()
{
}

UStage1_Level::~UStage1_Level()
{
}

void UStage1_Level::BeginPlay()
{
	ULevel::BeginPlay();

	if (false == LoadCheck)
	{
		LoadCheck = true;
		UEngineDirectory NewPath; // ���� ���� ���

		NewPath.MoveToSearchChild("GameResources");
		NewPath.Move("Stage"); // ���� �̵�
		NewPath.Move("stage1");
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
		UEngineResourcesManager::GetInst().CuttingImage("kirby_Right.png", 10, 7);
		UEngineResourcesManager::GetInst().CuttingImage("kirby_Left.png", 10, 7);
		UEngineResourcesManager::GetInst().CuttingImage("kirby2_Right.png", 10, 6);
		UEngineResourcesManager::GetInst().CuttingImage("kirby2_Left.png", 10, 6);
		UEngineResourcesManager::GetInst().CuttingImage("Ice_Right.png", 10, 12);
		UEngineResourcesManager::GetInst().CuttingImage("Ice_Left.png", 10, 12);
		UEngineResourcesManager::GetInst().CuttingImage("Fire_Right.png", 10, 16);
		UEngineResourcesManager::GetInst().CuttingImage("Fire_Left.png", 10, 16);
		UEngineResourcesManager::GetInst().CuttingImage("effect_Right.png", 8, 2);
		UEngineResourcesManager::GetInst().CuttingImage("effect_Left.png", 8, 2);
		UEngineResourcesManager::GetInst().CuttingImage("Effects2_Right.png", 10, 4);
		UEngineResourcesManager::GetInst().CuttingImage("Effects2_Left.png", 10, 4);
		UEngineResourcesManager::GetInst().CuttingImage("hitkirby_Right.png", 10, 4);
		UEngineResourcesManager::GetInst().CuttingImage("hitkirby_Left.png", 10, 4);
		UEngineResourcesManager::GetInst().CuttingImage("changeHUD.png", 5, 2);

		// �̹��� ���� -> ���� ���� �̹���
		UEngineResourcesManager::GetInst().CuttingImage("Dee_Left.png", 5, 2);
		UEngineResourcesManager::GetInst().CuttingImage("Dee_Right.png", 5, 2);
		UEngineResourcesManager::GetInst().CuttingImage("Pengi_Right.png", 5, 2);
		UEngineResourcesManager::GetInst().CuttingImage("Pengi_Left.png", 5, 2);
		UEngineResourcesManager::GetInst().CuttingImage("Flamer_Right.png", 5, 4);
		UEngineResourcesManager::GetInst().CuttingImage("Flamer_Left.png", 5, 4);

		std::list<UEngineFile> testList = NewPath.AllFile({ ".wav", ".mp3" }, true);
		// �������� ��Ģ�� ���Ұų�.
		for (UEngineFile& File : testList)
		{
			UEngineSound::Load(File.GetFullPath());
		}

		//BGMPlayer = UEngineSound::SoundPlay("Foot_1_1.wav");
		//BGMPlayer.Loop();
		// BGMPlayer = UEngineSound::SoundPlay("anipang_ingame_wav.wav");
		// BGMPlayer.Off();
	}
}

void UStage1_Level::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}

void UStage1_Level::LevelStart(ULevel* _PrevLevel)
{

	ULevel::LevelStart(_PrevLevel);
	SetCameraPos({ 0,400 }); // ī�޶� ��ġ ����

	// �� ����
	NewMap = SpawnActor<AStage1_MAP>();
	NewMap->SetMapImage("stage1_map.png");
	NewMap->SetColMapImage("cor_map.png");
	NewMap->SwitchDebug();

	// Ŀ��� Ŀ�� ����â Actor ����
	NewPlayer = SpawnActor<AKirby_Player>();
	NewPlayer->ReStartState();
	NewPlayer->SetActorLocation({ 500,1000 });
	NewPlayer->SetHp(100);
	NewPlayer->SetStageCheck(1);

	NewHpBar = SpawnActor<AKirby_HpBar>();

	// ���� Actor ����

	NewBase[0] = SpawnActor<AMonster_Base>();
	NewBase[0]->SetActorLocation({ 800,900 });

	for (int i = 1; i < Basesize; i++)
	{
		NewBase[i] = SpawnActor<AMonster_Base>();
		NewBase[i]->SetActorLocation({ 800 + i * 800,700 });
	}

	for (int i = 0; i < Icesize; i++)
	{
		NewIce[i] = SpawnActor<Apengi_Ice>();
		NewIce[i]->SetActorLocation({ 1100 + i * 800,800 });
	}

	NewFire[0] = SpawnActor<AMonster_Fire>();
	NewFire[0]->SetActorLocation({ 1000,600 });

	NewFire[1] = SpawnActor<AMonster_Fire>();
	NewFire[1]->SetActorLocation({ 3000,400 });
	
	
	GEngine->CreateLevel<UStage2_Level>("Stage2_Level"); // stage2_Level ���� ���� �̸� �غ�
}

void UStage1_Level::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);

	GEngine->DestroyLevel("Stage1_Level"); // Level ����

}

