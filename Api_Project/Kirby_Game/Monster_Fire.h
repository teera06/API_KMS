#pragma once
class AMonster_Fire
{
public:
	// constrcuter destructer
	AMonster_Fire(); // 디폴트 생성자
	~AMonster_Fire(); // 디폴트 소멸자

	// delete Function
	AMonster_Fire(const AMonster_Fire& _Other) = delete; // 디폴트 복사 생성자
	AMonster_Fire(AMonster_Fire&& _Other) noexcept = delete; 
	AMonster_Fire& operator=(const AMonster_Fire& _Other) = delete; // 디폴트 대입 연산자
	AMonster_Fire& operator=(AMonster_Fire&& _Other) noexcept = delete;

protected:

private:
};

