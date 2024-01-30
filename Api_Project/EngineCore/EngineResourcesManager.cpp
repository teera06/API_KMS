#include "EngineResourcesManager.h"
#include <EnginePlatform\WindowImage.h> // Level2 WindowImage
#include <EngineBase\EngineString.h>
#include <EngineBase\EngineDebug.h>
#include "EngineCore.h"
#include "EngineBase\EngineDebug.h"

//UEngineResourcesManager UEngineResourcesManager::Inst;
//UEngineResourcesManager* UEngineResourcesManager::pInst = nullptr;

UEngineResourcesManager::UEngineResourcesManager()
{
}

UEngineResourcesManager::~UEngineResourcesManager() // �Ҹ��ڿ��� �� ����
{
	for (std::pair<const std::string, UWindowImage*>& Pair : Images)
	{
		delete Pair.second;
		Pair.second = nullptr;
	}

	Images.clear();
}

UWindowImage* UEngineResourcesManager::LoadImg(std::string_view _Path)
{
	UEnginePath NewPath = UEnginePath(std::filesystem::path(_Path));
	std::string FileName = NewPath.GetFileName();
	return LoadImg(_Path, FileName);
}

UWindowImage* UEngineResourcesManager::LoadImg(std::string_view _Path, std::string_view _Name)
{
	// ��� �̸��� �빮�ڷ�
	std::string UpperName = UEngineString::ToUpper(_Name); // �빮�� ��ȯ

	if (true == Images.contains(UpperName)) // Map(Images) -> �̹� �����ϴ� ��� -> ���� ó��
	{
		// ������ ��峪 ����׿����� �ӷ��� �����ʿ䰡 ����.
		// ���ӿ��� ���� ������� ���� ���뿡 ���ؼ��� �ӷ��� ������ �ʴ´�.
		MsgBoxAssert(std::string("��� : ") + std::string(_Path) + "���ϸ� : " + std::string(_Name) + "�̹� �ε��� ������ �� �ε��Ϸ��� �߽��ϴ�");
		return nullptr;
	}

	// (�ڽ�)UWindowImage <-UPathObject <- UNameObject(�θ�)
	UWindowImage* NewImage = new UWindowImage(); // �����Ҵ�
	NewImage->SetName(UpperName); // �����̸� -> Level0 (NameObject)
	NewImage->SetPath(_Path); // ��� -> Level0 (PathObject)
	NewImage->Load(GEngine->MainWindow.GetWindowImage()); // Level1 (WindowImage), Ȯ���ڿ� ���� �̹��� �ε� �غ�() �� Ȯ���ϱ�

	// .Png .bmp => Ȯ���ڸ� �ٲٸ� png�� bmp�� �ȴٰ� �����ߴ� �л��� �־��µ� �ƴմϴ�.
	// ����� �̹��� ���� ���α׷����� ������ �����ϰ� �����ϼž� �մϴ�.
	// �ϴ� winapi�� �⺻������ png�� ����ϴ� �Լ��� �������� �ʽ��ϴ�.
	// ������ bmp�� �˴ϴ�.
	// .Png�� �ε��ؼ� bmp�� �����ؼ� ����� �̴ϴ�. => ó���մϴ�.
	// �׷��� Png�� ����ϴ°͵� �ƴϰ� �κ� ������
	Images[UpperName] = NewImage; // Map(Images) ���� ����

	return nullptr;

}

UWindowImage* UEngineResourcesManager::FindImg(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name); // �ҹ��� -> �빮�� ��ȯ -> ����: �񱳽� �빮�� ����

	if (false == Images.contains(UpperName)) // Map���� �����ϴ� ������ �������� ���� ���
	{
		MsgBoxAssert("���ϸ� : " + std::string(_Name) + "�� �������� �ʴ� �̹����Դϴ�");
		return nullptr; // ����
	}

	return Images[UpperName]; // Map�� �����ϴ� ���ϸ��� ����
}