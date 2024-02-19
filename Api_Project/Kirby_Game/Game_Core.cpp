#include "Game_Core.h"
#include "Kirby_Player.h"
#include "TitleLevel.h"
#include "Stage1_Level.h"

#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h> // Level 0 EngineDirectory
#include <EngineBase\EngineFile.h> // Level0 EngineFile

UGame_Core::UGame_Core()
	: UEngineCore()
{
}

UGame_Core::~UGame_Core()
{
}

// 게임시작
void UGame_Core::BeginPlay()  
{
	UEngineCore::BeginPlay();

	MainWindow.SetWindowPosition({ 200,100 }); // 윈도우창이 뜨는 위치 Set
	MainWindow.SetWindowScale({ 1200, 800}); // 윈도우창 크기 Set

	UEngineDirectory NewPath; // 현재 파일 경로

	NewPath.MoveParent(); // 현재 파일 경로의 상위(부모) 폴더로 이동

	// 커비의 기본 움직임 이미지는 모든 스테이지에서 사용하므로 코어에서 로드
	NewPath.Move("GameResources"); // 현재 폴더에서 다른 폴더로 이동
	NewPath.Move("kirby_resources"); // 경로 이동
	NewPath.Move("kirby_Base"); // 경로 이동


	// 확장자도 마찬가지 대소문자 구분을 무조건 대문자로 바꿔서 찾을것이다..
	std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);

	for (UEngineFile& File : AllFileList)
	{
		//std::string FullPath = File.GetFullPath(); // 파일의 전체 경로
		// 싱글톤 잊지 말라고 일부러 GetInst를 사용하겠습니다.
		UEngineResourcesManager::GetInst().LoadImg(File.GetFullPath()); // 로딩 -> Map(Iamges)
	}
	
	// WindowImage std::vector<UImageInfo> Infos; 에서 컷한 이미지 스케일, 위치 관리
	UEngineResourcesManager::GetInst().CuttingImage("kirby_Right.png", 10, 7);
	UEngineResourcesManager::GetInst().CuttingImage("kirby_Left.png", 10, 7);
	UEngineResourcesManager::GetInst().CuttingImage("kirby2_Right.png", 10, 6);
	UEngineResourcesManager::GetInst().CuttingImage("kirby2_Left.png", 10, 6);
	UEngineResourcesManager::GetInst().CuttingImage("effect_Right.png", 8, 2);
	UEngineResourcesManager::GetInst().CuttingImage("effect_Left.png", 8, 2);

	SetFrame(60); //-> 프로그래머가 컴퓨터 프레임을 고정시킬수 있다.

	// EngineCore에서 std::map<std::string, ULevel*> AllLevel; map으로 관리
	CreateLevel<UTitleLevel>("TitleLevel"); // 타이틀 레벨
	CreateLevel<UStage1_Level>("Stage1_Level"); // stage1_Level
	
	ChangeLevel("TitleLevel"); // 레벨 변경
}

void UGame_Core::Tick(float _DeltaTime)
{
	UEngineCore::Tick(_DeltaTime);
	// 플레이어 움직여야 한다.
	if (true == UEngineInput::IsDown(VK_F2))
	{
		GEngine->EngineDebugSwitch();
	}
}

void UGame_Core::End()
{
	UEngineCore::End();
}