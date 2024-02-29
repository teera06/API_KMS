#include "Stage1_Level.h"

// Actor
#include "Stage1_MAP.h" 

#include "Kirby_Player.h"
#include "Monster_Base.h"
#include "pengi_Ice.h"
#include "Monster_Fire.h"
#include "Kirby_HpBar.h"

// 리소스 (이미지, 사운드) 로드하기 위해 필요한 헤더
#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h> // Level 0 EngineDirectory
#include <EngineBase\EngineFile.h> // Level0 EngineFile

UStage1_Level::UStage1_Level()
{
}

UStage1_Level::~UStage1_Level()
{
}

void UStage1_Level::BeginPlay()
{
	ULevel::BeginPlay();

	UEngineDirectory NewPath; // 현재 파일 경로

	NewPath.MoveToSearchChild("GameResources");
	NewPath.Move("Stage"); // 폴더 이동
	NewPath.Move("stage1");
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
	UEngineResourcesManager::GetInst().CuttingImage("Effects.png", 10, 4);
	UEngineResourcesManager::GetInst().CuttingImage("hitkirby_Right.png", 10, 4);
	UEngineResourcesManager::GetInst().CuttingImage("hitkirby_Left.png", 10, 4);
	UEngineResourcesManager::GetInst().CuttingImage("changeHUD.png", 5, 2);

	// 이미지 컷팅 -> 몬스터 관련 이미지
	UEngineResourcesManager::GetInst().CuttingImage("Dee_Left.png", 5, 2);
	UEngineResourcesManager::GetInst().CuttingImage("Dee_Right.png", 5, 2);
	UEngineResourcesManager::GetInst().CuttingImage("Pengi_Right.png", 5, 2);
	UEngineResourcesManager::GetInst().CuttingImage("Pengi_Left.png", 5, 2);
	UEngineResourcesManager::GetInst().CuttingImage("Flamer_Right.png", 5, 4);
	UEngineResourcesManager::GetInst().CuttingImage("Flamer_Left.png", 5, 4);

	//NewPath.Move("GameResources"); // 현재 폴더에서 다른 폴더로 이동
	//NewPath.Move("sound"); // 폴더 이동

	std::list<UEngineFile> testList = NewPath.AllFile({ ".wav", ".mp3" }, true);
	// 엔진만의 규칙을 정할거냐.
	for (UEngineFile& File : testList)
	{
		UEngineSound::Load(File.GetFullPath());
	}

	//BGMPlayer = UEngineSound::SoundPlay("Foot_1_1.wav");
	//BGMPlayer.Loop();
	// BGMPlayer = UEngineSound::SoundPlay("anipang_ingame_wav.wav");
	// BGMPlayer.Off();
	

	SetCameraPos({ 0,400 }); // 카메라 위치 설정

	// 맵 생성
	NewMap = SpawnActor<AStage1_MAP>();
	NewMap->SetMapImage("stage1_map.png");
	//Map->SetMapImage("stage2_map.png");
	NewMap->SetColMapImage("cor_map.png");
	NewMap->SwitchDebug();

	// 커비와 커비 상태창 Actor 생성
	NewPlayer=SpawnActor<AKirby_Player>();
	NewPlayer->SetActorLocation({ 500,1000 });
	
	NewHpBar=SpawnActor<AKirby_HpBar>();

	// 몬스터 Actor 생성
	NewBaseMonster.reserve(Basesize);
	for (int i = 0; i < Basesize; i++)
	{
		NewBase = SpawnActor<AMonster_Base>();
		NewBase->SetActorLocation({800+i*800,700 });

		NewBaseMonster.push_back(NewBase);
	}
	
	NewIceMonster.reserve(Icesize);
	for (int i = 0; i < Icesize; i++)
	{
		NewIce = SpawnActor<Apengi_Ice>();
		NewIce->SetActorLocation({ 1100 + i * 800,800 });

		NewIceMonster.push_back(NewIce);
	}

	NewFireMonster.reserve(Firesize);
	for (int i = 0; i < Firesize; i++)
	{
		NewFire = SpawnActor<AMonster_Fire>();
		NewFire->SetActorLocation({ 1000 + i * 1000,600 +i*-150});

		NewFireMonster.push_back(NewFire);
	}
}

void UStage1_Level::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}

void UStage1_Level::LevelStart(ULevel* _PrevLevel)
{

	ULevel::LevelStart(_PrevLevel);
	
}

void UStage1_Level::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);

	if (NewMap != nullptr)
	{
		NewMap->Destroy();
	}

	if (NewPlayer != nullptr)
	{
		NewPlayer->Destroy();
	}

	if (NewHpBar != nullptr)
	{
		NewPlayer->Destroy();
	}

	if (NewBase != nullptr)
	{
		NewBase->Destroy();
	}

	if (NewIce != nullptr)
	{
		NewIce->Destroy();
	}

	if (NewFire != nullptr)
	{
		NewFire->Destroy();
	}

	NewBaseMonster.clear();
	
	NewIceMonster.clear();

	NewFireMonster.clear();
}

