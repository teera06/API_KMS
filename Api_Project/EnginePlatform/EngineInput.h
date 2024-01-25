#pragma once
// 키보드를 제어해주는 건 OS일것이기 때문에
// 입력에 대한 함수도 당연히 OS가 우리에게 제공해야 합니다.
#include <Windows.h>
#include <map>
#include <EngineBase\EngineDebug.h>

// AllStateClass
// 기능 : 입력키의 Map을 통한 자료구조 정리 및 입력키의 상태 관리
class EngineInput
{
	friend class InputInitCreator; //InputInitCreator클래스에게 private:인것도 제공

private:
	class /*EngineInput::*/EngineKey
	{
		friend EngineInput;

	public:
		// 입력 상태
		bool Down = false; // 누른 순간
		bool Press = false; // 계속 누르면
		bool Up = false; // 떼어진 순간
		bool Free = true; // 눌리지 않으면

		float PressTime = 0.0f; // 미정

		int Key = -1; // VK_LBUTTON // 기본 키값

		void KeyCheck(); // 현재 키 입력 상태에 따른 위의 입력 상태 변화

		EngineKey()
		{

		}

		EngineKey(int _Key)
			: Key(_Key) // 생성자에서 키값을 받아옴
		{

		}
	};

public:
	// constrcuter destructer
	EngineInput();
	~EngineInput();

	// delete Function
	EngineInput(const EngineInput& _Other) = delete;
	EngineInput(EngineInput&& _Other) noexcept = delete;
	EngineInput& operator=(const EngineInput& _Other) = delete;
	EngineInput& operator=(EngineInput&& _Other) noexcept = delete;

	static bool IsDown(int _Key) // 키값을 통해
	{
		if (false == AllKeys.contains(_Key))
		{
			MsgBoxAssert("입력설정이 존재하지 않는 키 입니다");
		}

		return AllKeys[_Key].Down;
	}

	static bool IsPress(int _Key)
	{
		if (false == AllKeys.contains(_Key))
		{
			MsgBoxAssert("입력설정이 존재하지 않는 키 입니다");
		}

		return AllKeys[_Key].Press;
	}

	static bool IsUp(int _Key)
	{
		if (false == AllKeys.contains(_Key))
		{
			MsgBoxAssert("입력설정이 존재하지 않는 키 입니다");
		}

		return AllKeys[_Key].Up;
	}

	static bool IsFree(int _Key)
	{
		if (false == AllKeys.contains(_Key))
		{
			MsgBoxAssert("입력설정이 존재하지 않는 키 입니다");
		}

		return AllKeys[_Key].Free;
	}

	static void KeyCheckTick(float _DeltaTime);

protected:
	//              'A'  상태가 어때?
	static std::map<int, EngineKey> AllKeys; // Key의 목록을 map으로 관리

	int Value;

private:
	static void InputInit();
};

