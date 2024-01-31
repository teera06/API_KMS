#pragma once
#include <EngineCore\Actor.h>

class ATitleActor : public AActor
{
public:
	// constrcuter destructer
	ATitleActor(); // ����Ʈ ������
	~ATitleActor(); // ����Ʈ �Ҹ���

	// delete Function
	ATitleActor(const ATitleActor& _Other) = delete; // ����Ʈ ���� ������
	ATitleActor(ATitleActor&& _Other) noexcept = delete; 
	ATitleActor& operator=(const ATitleActor& _Other) = delete; // ����Ʈ ���� ������
	ATitleActor& operator=(ATitleActor&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	UImageRenderer* TitleRenderer = nullptr;
};

