#pragma once
class EngineSound
{
public:
	// constrcuter destructer
	EngineSound(); // 디폴트 생성자
	~EngineSound(); // 디폴트 소멸자

	// delete Function
	EngineSound(const EngineSound& _Other) = delete; // 디폴트 복사 생성자
	EngineSound(EngineSound&& _Other) noexcept = delete; 
	EngineSound& operator=(const EngineSound& _Other) = delete; // 디폴트 대입 연산자
	EngineSound& operator=(EngineSound&& _Other) noexcept = delete;

protected:

private:
};

