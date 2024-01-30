#pragma once
#include <string>

// 설명 :
class UNameObject
{
public:
	// constrcuter destructer
	UNameObject();
	virtual ~UNameObject();

	// delete Function
	UNameObject(const UNameObject& _Other) = delete;
	UNameObject(UNameObject&& _Other) noexcept = delete;
	UNameObject& operator=(const UNameObject& _Other) = delete;
	UNameObject& operator=(UNameObject&& _Other) noexcept = delete;

	void SetName(std::string_view _View) // 파일명 -> Set
	{
		Name = _View;
	}

	std::string GetName()
	{
		return Name;
	}

protected:

private:
	std::string Name;

};

