#pragma once
class EngineWindow
{
public:
	// constrcuter destructer
	EngineWindow(); // 디폴트 생성자
	~EngineWindow(); // 디폴트 소멸자

	// delete Function
	EngineWindow(const EngineWindow& _Other) = delete; // 디폴트 복사 생성자
	EngineWindow(EngineWindow&& _Other) noexcept = delete; 
	EngineWindow& operator=(const EngineWindow& _Other) = delete; // 디폴트 대입 연산자
	EngineWindow& operator=(EngineWindow&& _Other) noexcept = delete;

protected:

private:
};

