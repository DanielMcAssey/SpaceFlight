#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#pragma comment(lib, "XInput.lib")

struct GamepadState
{
public:
	bool Disconnected;
	struct { float X, Y; } LStick, RStick;
	float LTrigger, RTrigger;
	struct { bool LShoulder, RShoulder, A, B, X, Y, Back, Start, LThumb, RThumb; } Buttons;
	struct { bool Up, Down, Left, Right; } DPad;

	struct { bool LShoulder, RShoulder, A, B, X, Y, Back, Start, LThumb, RThumb; } ButtonsSingle;
	struct { bool Up, Down, Left, Right; } DPadSingle;

	struct { bool LShoulder, RShoulder, A, B, X, Y, Back, Start, LThumb, RThumb; } ButtonsOld;
	struct { bool Up, Down, Left, Right; } DPadOld;
};

class InputManager
{
public:
	InputManager(void);
	~InputManager(void);

	void Update();
	GamepadState GetState(int _gamepad_id);
	void SetVibration(int _gamepad_id, float _left_rocker_amount, float _right_rocker_amount);
protected:
	XINPUT_STATE mInputState[4];
	GamepadState mGamepads[4];
	GamepadState mGamepadError;
};

#endif // INPUTMANAGER_H