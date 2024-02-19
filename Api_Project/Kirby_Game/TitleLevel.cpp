#include "TitleLevel.h"
#include "TitleActor.h"

#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h> // Level 0 EngineDirectory
#include <EngineBase\EngineFile.h> // Level0 EngineFile

#include <EngineCore/EngineCore.h>

UTitleLevel::UTitleLevel()
{
}

UTitleLevel::~UTitleLevel()
{
}

void UTitleLevel::BeginPlay()
{
	ULevel::BeginPlay();

	UEngineDirectory NewPath; // ���� ���� ���
	FVector windowscale = GEngine->MainWindow.GetWindowScale(); // ������â ũ�� Get

	NewPath.MoveParent(); // ���� ���� ����� ���� ������ �̵�
	NewPath.Move("GameResources"); // ���� �������� �ٸ� ������ �̵�
	NewPath.Move("Title");

	// Ȯ���ڵ� �������� ��ҹ��� ������ ������ �빮�ڷ� �ٲ㼭 ã�����̴�..
	std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true); 

	for (UEngineFile& File : AllFileList)
	{
		std::string FullPath = File.GetFullPath(); // ������ ��ü ���
		// �̱��� ���� ����� �Ϻη� GetInst�� ����ϰڽ��ϴ�.
		UEngineResourcesManager::GetInst().LoadImg(FullPath); // �ε� -> Map(Iamges)
	}
	UEngineResourcesManager::GetInst().CuttingImage("Mapback.png", 6, 1);
	
	SpawnActor<ATitleActor>()->SetActorLocation(windowscale.Half2D()); // ������â �߰��������� TitleActor ��ġ Set
	
}

void UTitleLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (true == UEngineInput::IsDown(VK_LBUTTON))
	{
		GEngine->ChangeLevel("Stage1_Level");
	}
}
