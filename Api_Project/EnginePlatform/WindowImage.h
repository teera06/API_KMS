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
	// 윈도우에서 지원해주는 H붙은 애들은 다 struct HBITMAP__{int unused;}; typedef struct HBITMAP__ *HBITMAP
	// 포인터이면서 8바이트 정수입니다.
	HBITMAP hBitMap = 0;
	HDC ImageDC = 0;
	BITMAP Info = BITMAP();
};

