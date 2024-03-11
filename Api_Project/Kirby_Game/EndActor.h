#pragma once
#include <EngineCore\Actor.h>
#include<EngineCore/EngineCore.h>

class EndActor : public AActor
{
public:
	// constrcuter destructer
	EndActor(); // ����Ʈ ������
	~EndActor(); // ����Ʈ �Ҹ���

	// delete Function
	EndActor(const EndActor& _Other) = delete; // ����Ʈ ���� ������
	EndActor(EndActor&& _Other) noexcept = delete; 
	EndActor& operator=(const EndActor& _Other) = delete; // ����Ʈ ���� ������
	EndActor& operator=(EndActor&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	UImageRenderer* EndRenderer = nullptr;
	FVector windowScale = GEngine->MainWindow.GetWindowScale();

};

