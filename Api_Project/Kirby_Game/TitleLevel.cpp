#include "TitleLevel.h"
#include <EnginePlatform\EngineInput.h>
#include "Stage1_Level.h"
#include <EngineCore/EngineCore.h>

#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h> // Level 0 EngineDirectory
#include <EngineBase\EngineFile.h> // Level0 EngineFile

UTitleLevel::UTitleLevel()
{
}

UTitleLevel::~UTitleLevel()
{
}

void UTitleLevel::BeginPlay()
{
	// �����ΰ� ���;� �Ѵٰ� �����մϴ�.
	UEngineDirectory NewPath; // ���� ���� ���

	// NewPath.Move("ContentsResources");
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

	//SpawnActor<>();
	
}
