#pragma once
class EngineCore
{
public:
	// constrcuter destructer
	EngineCore(); // 디폴트 생성자
	~EngineCore(); // 디폴트 소멸자

	// delete Function
	EngineCore(const EngineCore& _Other) = delete; // 디폴트 복사 생성자
	EngineCore(EngineCore&& _Other) noexcept = delete; 
	EngineCore& operator=(const EngineCore& _Other) = delete; // 디폴트 대입 연산자
	EngineCore& operator=(EngineCore&& _Other) noexcept = delete;

protected:

private:
};

