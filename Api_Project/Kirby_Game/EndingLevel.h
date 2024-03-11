#pragma once
#include <EngineCore/Level.h>

class EndingLevel : public ULevel
{
public:
	// constrcuter destructer
	EndingLevel(); // ����Ʈ ������
	~EndingLevel(); // ����Ʈ �Ҹ���

	// delete Function
	EndingLevel(const EndingLevel& _Other) = delete; // ����Ʈ ���� ������
	EndingLevel(EndingLevel&& _Other) noexcept = delete; 
	EndingLevel& operator=(const EndingLevel& _Other) = delete; // ����Ʈ ���� ������
	EndingLevel& operator=(EndingLevel&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	//void LevelStart(ULevel* _Level) override;
	//void LevelEnd(ULevel* _Level) override;
private:
};

