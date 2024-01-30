#pragma once
#include <EngineBase\PathObject.h>
#include <Windows.h>

// 설명 :
class UWindowImage : public UPathObject
{
public:
	// constrcuter destructer
	UWindowImage();
	~UWindowImage();

	// delete Function
	UWindowImage(const UWindowImage& _Other) = delete;
	UWindowImage(UWindowImage&& _Other) noexcept = delete;
	UWindowImage& operator=(const UWindowImage& _Other) = delete;
	UWindowImage& operator=(UWindowImage&& _Other) noexcept = delete;

	// bool을 리턴해서 false면 실패 true면 성공
	bool Load(HDC _MainDC);

protected:

private:
	HBITMAP BitMap;
	HDC ImageDC;
	BITMAP Info;
};

