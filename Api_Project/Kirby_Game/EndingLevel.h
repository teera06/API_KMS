#pragma once
#include <EngineCore/Level.h>

class UEndingLevel : public ULevel
{
public:
	// constrcuter destructer
	UEndingLevel(); // ����Ʈ ������
	~UEndingLevel(); // ����Ʈ �Ҹ���

	// delete Function
	UEndingLevel(const UEndingLevel& _Other) = delete; // ����Ʈ ���� ������
	UEndingLevel(UEndingLevel&& _Other) noexcept = delete; 
	UEndingLevel& operator=(const UEndingLevel& _Other) = delete; // ����Ʈ ���� ������
	UEndingLevel& operator=(UEndingLevel&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _Level) override;
	void LevelEnd(ULevel* _Level) override;
private:
};

