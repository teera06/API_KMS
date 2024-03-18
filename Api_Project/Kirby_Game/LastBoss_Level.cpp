#include "LastBoss_Level.h"

#include "EndingLevel.h"

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

bool ULastBoss_Level::LoadCheck = false;
ULastBoss_Level::ULastBoss_Level()
{
}

ULastBoss_Level::~ULastBoss_Level()
{
}

void ULastBoss_Level::BeginPlay()
{
	ULevel::BeginPlay();

	if (false == LoadCheck)
	{
		LoadCheck = true;
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
		UEngineResourcesManager::GetInst().CuttingImage("EndingMap.png", 3, 3);

		std::list<UEngineFile> SoundList = NewPath.AllFile({ ".wav", ".mp3" }, true);
		// �������� ��Ģ�� ���Ұų�.
		for (UEngineFile& File : SoundList)
		{
			UEngineSound::Load(File.GetFullPath());
		}
	}
}

void ULastBoss_Level::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (true == NewPlayer->GetMainBossEvent() && false == EventCheck)
	{
		EventCheck = true;
		NewBossHpBar->ActiveOn();
		NewMainBoss->SetActorLocation({ 900,150 });
		NewMainBoss->ActiveOn();
	}

	if (NewMainBoss->GetHp() <= 0 && true == NewMainBoss->GetEndingChange() && false == LevelChange)
	{
		NewMap->GetEventRenderer1()->ActiveOn();
		NewMap->GetEventRenderer1()->ChangeAnimation("EndingMap1");
		if (true == NewMap->GetEventRenderer1()->IsCurAnimationEnd())
		{
			GEngine->ChangeLevel("Ending_Level");
			LevelChange = true;
		}

		if (false == AniEnd)
		{
			AniEnd = true;
			NewMap->GetEventRenderer2()->SetActive(true, 4.0f);
			NewMap->GetEventRenderer2()->ChangeAnimation("EndingMap2");
		}
	}
}

void ULastBoss_Level::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
	BGMPlayer = UEngineSound::SoundPlay("LastBGM.mp3");
	BGMPlayer.SetVolume(0.7f);
	BGMPlayer.Loop();
	SetCameraPos({100,-40 }); // ī�޶� ��ġ ����

	// �� ����
	NewMap = SpawnActor < ALast_Map > ();
	NewMap->SetMapImage("LastMap.png");
	
	NewMap->SetColMapImage("Cor4_Map.png");
	NewMap->SwitchDebug();

	// Ŀ��� Ŀ�� ����â Actor ����
	NewPlayer = SpawnActor<AKirby_Player>();
	NewPlayer->SetActorLocation({ 400,500 });

	NewHpBar = SpawnActor<AKirby_HpBar>();

	SpawnActor<AHammer>()->SetActorLocation({610,370});
	
	NewMainBoss = SpawnActor<AMainBoss>();
	NewMainBoss->ActiveOff();
	NewBossHpBar=SpawnActor<ABossHpBar>();
	NewBossHpBar->ActiveOff();

	GEngine->CreateLevel<UEndingLevel>("Ending_Level"); // stage2_Level ���� ���� �̸� �غ�
}

void ULastBoss_Level::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);
	BGMPlayer.Off();
	GEngine->DestroyLevel("LastBoss_Level"); // Level ����
}
