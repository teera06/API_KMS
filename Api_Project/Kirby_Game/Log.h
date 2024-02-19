
#pragma once
#include <EngineCore\Actor.h>
#include<EngineCore/EngineCore.h>

class ALog : public AActor
{
public:
	// constrcuter destructer
	ALog(); // ����Ʈ ������
	~ALog(); // ����Ʈ �Ҹ���

	// delete Function
	ALog(const ALog& _Other) = delete; // ����Ʈ ���� ������
	ALog(ALog&& _Other) noexcept = delete; 
	ALog& operator=(const ALog& _Other) = delete; // ����Ʈ ���� ������
	ALog& operator=(ALog&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	UImageRenderer* TitleRenderer = nullptr;
	FVector windowScale = GEngine->MainWindow.GetWindowScale();
};

