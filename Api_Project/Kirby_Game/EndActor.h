#pragma once
#include <EngineCore\Actor.h>
#include<EngineCore/EngineCore.h>

class AEndActor : public AActor
{
public:
	// constrcuter destructer
	AEndActor(); // ����Ʈ ������
	~AEndActor(); // ����Ʈ �Ҹ���

	// delete Function
	AEndActor(const AEndActor& _Other) = delete; // ����Ʈ ���� ������
	AEndActor(AEndActor&& _Other) noexcept = delete; 
	AEndActor& operator=(const AEndActor& _Other) = delete; // ����Ʈ ���� ������
	AEndActor& operator=(AEndActor&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	UImageRenderer* EndRenderer = nullptr;
	UImageRenderer* KirbyRenderer = nullptr;
	FVector windowScale = GEngine->MainWindow.GetWindowScale();

};

