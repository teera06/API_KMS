#pragma once
// 키보드를 제어해주는 건 OS일것이기 때문에
// 입력에 대한 함수도 당연히 OS가 우리에게 제공해야 합니다.
#include <Windows.h>
#include <map>

// AllStateClass
// 설명 :
class EngineInput
{
	friend class InputInitCreator;

private:
	class EngineKey
	{
		friend EngineInput;

	public:
		bool Down = false; // 누른 순간
		bool Press = false; // 계속 누르면
		bool Up = false; // 떼어진 순간
		bool Free = true; // 누리지 않으면

		float PressTime = 0.0f;

		int Key = -1; // VK_LBUTTON

		EngineKey()
		{

		}

		EngineKey(int _Key)
			: Key(_Key)
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

	static bool IsPress(int _Key)
	{
		return AllKeys[VK_LBUTTON].Down;
	}

protected:
	//              'A'  상태가 어때?
	static std::map<int, EngineKey> AllKeys;

private:
	static void InputInit();
};

