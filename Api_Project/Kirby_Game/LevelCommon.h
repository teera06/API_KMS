#pragma once
class ULevelCommon
{
public:
	// constrcuter destructer
	ULevelCommon(); // ����Ʈ ������
	~ULevelCommon(); // ����Ʈ �Ҹ���

	// delete Function
	ULevelCommon(const ULevelCommon& _Other) = delete; // ����Ʈ ���� ������
	ULevelCommon(ULevelCommon&& _Other) noexcept = delete; 
	ULevelCommon& operator=(const ULevelCommon& _Other) = delete; // ����Ʈ ���� ������
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

