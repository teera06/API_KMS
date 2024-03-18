#include "LastBoss_Level.h"

#include "EndingLevel.h"

#include "Last_Map.h"
#include "Kirby_Player.h" 
#include "Kirby_HpBar.h"
#include "Hammer.h"
#include "MainBoss.h"
#include "BossHpBar.h"



// 리소스 (이미지, 사운드) 로드하기 위해 필요한 헤더
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
		UEngineDirectory NewPath; // 현재 파일 경로

		NewPath.MoveToSearchChild("GameResources");
		NewPath.Move("Stage"); // 폴더 이동
		NewPath.Move("LastStage");

		// 확장자도 마찬가지 대소문자 구분을 무조건 대문자로 바꿔서 찾을것이다..
		std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);
		// png, bmp 파일 
		// true -> 폴더 안의 폴더안에 이미지도 재귀함수로 체크

		for (UEngineFile& File : AllFileList)
		{
			std::string FullPath = File.GetFullPath(); // 파일의 전체 경로
			// 싱글톤 잊지 말라고 일부러 GetInst를 사용하겠습니다.
			UEngineResourcesManager::GetInst().LoadImg(FullPath); // 로딩 -> Map(Iamges)
		}
		// 이미지 컷팅 -> 커비 관련 이미지
		UEngineResourcesManager::GetInst().CuttingImage("Hammer_Right.png", 10, 13);
		UEngineResourcesManager::GetInst().CuttingImage("Hammer_Left.png", 10, 13);
		UEngineResourcesManager::GetInst().CuttingImage("King_Right.png", 10, 8);
		UEngineResourcesManager::GetInst().CuttingImage("King_Left.png", 10, 8);
		UEngineResourcesManager::GetInst().CuttingImage("EndingMap.png", 3, 3);

		std::list<UEngineFile> SoundList = NewPath.AllFile({ ".wav", ".mp3" }, true);
		// 엔진만의 규칙을 정할거냐.
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
	SetCameraPos({100,-40 }); // 카메라 위치 설정

	// 맵 생성
	NewMap = SpawnActor < ALast_Map > ();
	NewMap->SetMapImage("LastMap.png");
	
	NewMap->SetColMapImage("Cor4_Map.png");
	NewMap->SwitchDebug();

	// 커비와 커비 상태창 Actor 생성
	NewPlayer = SpawnActor<AKirby_Player>();
	NewPlayer->SetActorLocation({ 400,500 });

	NewHpBar = SpawnActor<AKirby_HpBar>();

	SpawnActor<AHammer>()->SetActorLocation({610,370});
	
	NewMainBoss = SpawnActor<AMainBoss>();
	NewMainBoss->ActiveOff();
	NewBossHpBar=SpawnActor<ABossHpBar>();
	NewBossHpBar->ActiveOff();

	GEngine->CreateLevel<UEndingLevel>("Ending_Level"); // stage2_Level 다음 레벨 미리 준비
}

void ULastBoss_Level::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);
	BGMPlayer.Off();
	GEngine->DestroyLevel("LastBoss_Level"); // Level 정리
}
