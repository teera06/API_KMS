#pragma once
class ULevelCommon
{
public:
	// constrcuter destructer
	ULevelCommon(); // 디폴트 생성자
	~ULevelCommon(); // 디폴트 소멸자

	// delete Function
	ULevelCommon(const ULevelCommon& _Other) = delete; // 디폴트 복사 생성자
	ULevelCommon(ULevelCommon&& _Other) noexcept = delete; 
	ULevelCommon& operator=(const ULevelCommon& _Other) = delete; // 디폴트 대입 연산자
	ULevelCommon& operator=(ULevelCommon&& _Other) noexcept = delete;

	void SetCreateCheck(const bool& _CreateCheck)
	{
		CreateCheck = _CreateCheck;
	}

	bool GetCreateCheck()
	{
		return CreateCheck;
	}

	void SetStageCount(const int& _StageCount)
	{
		StageCount = _StageCount;
	}

	int GetStageCount()
	{
		return StageCount;
	}


protected:

private:

	bool CreateCheck = false;

	int StageCount = 0;
};

