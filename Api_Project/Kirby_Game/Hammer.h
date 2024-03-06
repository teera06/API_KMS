#pragma once
class Hammer
{
public:
	// constrcuter destructer
	Hammer(); // 디폴트 생성자
	~Hammer(); // 디폴트 소멸자

	// delete Function
	Hammer(const Hammer& _Other) = delete; // 디폴트 복사 생성자
	Hammer(Hammer&& _Other) noexcept = delete; 
	Hammer& operator=(const Hammer& _Other) = delete; // 디폴트 대입 연산자
	Hammer& operator=(Hammer&& _Other) noexcept = delete;

protected:

private:
};

