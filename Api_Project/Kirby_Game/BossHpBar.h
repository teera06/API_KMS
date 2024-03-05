#pragma once
class BossHpBar
{
public:
	// constrcuter destructer
	BossHpBar(); // 디폴트 생성자
	~BossHpBar(); // 디폴트 소멸자

	// delete Function
	BossHpBar(const BossHpBar& _Other) = delete; // 디폴트 복사 생성자
	BossHpBar(BossHpBar&& _Other) noexcept = delete; 
	BossHpBar& operator=(const BossHpBar& _Other) = delete; // 디폴트 대입 연산자
	BossHpBar& operator=(BossHpBar&& _Other) noexcept = delete;

protected:

private:
};

