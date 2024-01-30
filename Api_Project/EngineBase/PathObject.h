#pragma once
#include "NameObject.h"
#include "EnginePath.h"

// 설명 :
class UPathObject : public UNameObject
{
public:
	// constrcuter destructer
	UPathObject();
	~UPathObject();

	// delete Function
	UPathObject(const UPathObject& _Other) = delete;
	UPathObject(UPathObject&& _Other) noexcept = delete;
	UPathObject& operator=(const UPathObject& _Other) = delete;
	UPathObject& operator=(UPathObject&& _Other) noexcept = delete;

	void SetPath(std::string_view _View) // 파일 경로 -> Set
	{
		Path = _View;
	}

	std::string GetPath()
	{
		return Path;
	}

	UEnginePath GetEnginePath() // 파일 경로 Get
	{
		return UEnginePath(std::filesystem::path(Path));
	}

protected:

private:
	std::string Path;

};

