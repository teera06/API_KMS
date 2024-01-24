#pragma once
// 전부다 std의 헤더뿐이다.
#include <string>
#include <string_view>

// 기능 : 문자열 대문자 변환
class EngineString
{
public:
	static std::string ToUpper(std::string_view View);
	// string_view 사용하는 이유?
	// std : string타입의 복사본 생성 없이 효율적으로 동작
	// std : string타입의 복사본 생성이 없으면 효율적인 이유?
	// std : string안의 동작은 결국 vector<char>과 같다.
	// vector<char>안에서는 동적할당이 이뤄지므로
	// 문자열 길이가 길어질수록 복사본이 생기는것이 부담이 크다.
protected:

private:
	// constrcuter destructer
	EngineString();
	~EngineString();

	// delete Function
	EngineString(const EngineString& _Other) = delete;
	EngineString(EngineString&& _Other) noexcept = delete;
	EngineString& operator=(const EngineString& _Other) = delete;
	EngineString& operator=(EngineString&& _Other) noexcept = delete;
};

