#pragma once
#include <EngineCore\EngineCore.h>

class Game_Core :public EngineCore
{
public:
	// constrcuter destructer
	Game_Core(); // 디폴트 생성자
	~Game_Core(); // 디폴트 소멸자

	// delete Function
	Game_Core(const Game_Core& _Other) = delete; // 디폴트 복사 생성자
	Game_Core(Game_Core&& _Other) noexcept = delete; 
	Game_Core& operator=(const Game_Core& _Other) = delete; // 디폴트 대입 연산자
	Game_Core& operator=(Game_Core&& _Other) noexcept = delete;

protected:
	void EngineStart() override;
	void EngineUpdate() override;
	void EngineEnd() override;
private:
};

