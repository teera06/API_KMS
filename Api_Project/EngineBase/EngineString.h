#pragma once
class EngineString
{
public:
	// constrcuter destructer
	EngineString(); // 디폴트 생성자
	~EngineString(); // 디폴트 소멸자

	// delete Function
	EngineString(const EngineString& _Other) = delete; // 디폴트 복사 생성자
	EngineString(EngineString&& _Other) noexcept = delete; 
	EngineString& operator=(const EngineString& _Other) = delete; // 디폴트 대입 연산자
	EngineString& operator=(EngineString&& _Other) noexcept = delete;

protected:

private:
};

