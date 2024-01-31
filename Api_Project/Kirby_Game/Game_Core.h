#pragma once
#include <EngineCore\EngineCore.h>

// 설명 :
class UGame_Core : public UEngineCore
{
public:
	// constrcuter destructer
	UGame_Core();
	~UGame_Core();

	// delete Function
	UGame_Core(const UGame_Core& _Other) = delete;
	UGame_Core(UGame_Core&& _Other) noexcept = delete;
	UGame_Core& operator=(const UGame_Core& _Other) = delete;
	UGame_Core& operator=(UGame_Core&& _Other) noexcept = delete;

protected:
	// 부모인 
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void End() override;

private:

};

