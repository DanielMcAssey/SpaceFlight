#include "StdAfx.h"
#include "InputManager.h"


InputManager::InputManager(void)
{
	for(int i = 0; i < 4; i++)
	{
		this->mGamepads[i].Disconnected = true;
	}

	this->mGamepadError.Disconnected = true;
}


InputManager::~InputManager(void)
{
}

void InputManager::Update()
{
	DWORD dwResult;

	for(int i = 0; i < 4; i++)
	{
		ZeroMemory(&this->mInputState[i], sizeof(XINPUT_STATE));
		dwResult = XInputGetState(i, &this->mInputState[i]);

		if(dwResult == ERROR_SUCCESS)
		{
			this->mGamepads[i].Disconnected = false;

			if( (this->mInputState[i].Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				this->mInputState[i].Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
				(this->mInputState[i].Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				this->mInputState[i].Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) )
			{
				this->mGamepads[i].LStick.X = 0.0f;
				this->mGamepads[i].LStick.Y = 0.0f;
			}
			else
			{
				this->mGamepads[i].LStick.X = this->mInputState[i].Gamepad.sThumbLX / 255.0f;
				this->mGamepads[i].LStick.Y = this->mInputState[i].Gamepad.sThumbLY / 255.0f;
			}

			if( (this->mInputState[i].Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
				this->mInputState[i].Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
				(this->mInputState[i].Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
				this->mInputState[i].Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) )
			{
				this->mGamepads[i].RStick.X = 0.0f;
				this->mGamepads[i].RStick.Y = 0.0f;
			}
			else
			{
				this->mGamepads[i].RStick.X = this->mInputState[i].Gamepad.sThumbRX / 255.0f;
				this->mGamepads[i].RStick.Y = this->mInputState[i].Gamepad.sThumbRY / 255.0f;
			}

			//Gamepad Triggers
			if(this->mInputState[i].Gamepad.bLeftTrigger >= XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
				this->mGamepads[i].LTrigger = this->mInputState[i].Gamepad.bLeftTrigger / 255.0f;
			else
				this->mGamepads[i].LTrigger = 0.0f;

			if(this->mInputState[i].Gamepad.bRightTrigger >= XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
				this->mGamepads[i].RTrigger = this->mInputState[i].Gamepad.bRightTrigger / 255.0f;
			else
				this->mGamepads[i].RTrigger = 0.0f;

			// Store the previous state
			this->mGamepads[i].ButtonsOld.A = this->mGamepads[i].Buttons.A;
			this->mGamepads[i].ButtonsOld.B = this->mGamepads[i].Buttons.B;
			this->mGamepads[i].ButtonsOld.X = this->mGamepads[i].Buttons.X;
			this->mGamepads[i].ButtonsOld.Y = this->mGamepads[i].Buttons.Y;
			this->mGamepads[i].ButtonsOld.Start = this->mGamepads[i].Buttons.Start;
			this->mGamepads[i].ButtonsOld.Back = this->mGamepads[i].Buttons.Back;
			this->mGamepads[i].ButtonsOld.LShoulder = this->mGamepads[i].Buttons.LShoulder;
			this->mGamepads[i].ButtonsOld.RShoulder = this->mGamepads[i].Buttons.RShoulder;
			this->mGamepads[i].ButtonsOld.LThumb = this->mGamepads[i].Buttons.LThumb;
			this->mGamepads[i].ButtonsOld.RThumb = this->mGamepads[i].Buttons.RThumb;
			this->mGamepads[i].DPadOld.Up = this->mGamepads[i].DPad.Up;
			this->mGamepads[i].DPadOld.Down = this->mGamepads[i].DPad.Down;
			this->mGamepads[i].DPadOld.Left = this->mGamepads[i].DPad.Left;
			this->mGamepads[i].DPadOld.Right = this->mGamepads[i].DPad.Right;

			// Get the gamepad Buttons
			if(this->mInputState[i].Gamepad.wButtons & XINPUT_GAMEPAD_A)
			{
				this->mGamepads[i].Buttons.A = true;
			} else { this->mGamepads[i].Buttons.A = false; }
			if(this->mInputState[i].Gamepad.wButtons & XINPUT_GAMEPAD_B)
			{
				this->mGamepads[i].Buttons.B = true;
			} else { this->mGamepads[i].Buttons.B = false; }
			if(this->mInputState[i].Gamepad.wButtons & XINPUT_GAMEPAD_X)
			{
				this->mGamepads[i].Buttons.X = true;
			} else { this->mGamepads[i].Buttons.X = false; }
			if(this->mInputState[i].Gamepad.wButtons & XINPUT_GAMEPAD_Y)
			{
				this->mGamepads[i].Buttons.Y = true;
			} else { this->mGamepads[i].Buttons.Y = false; }
			if(this->mInputState[i].Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
			{
				this->mGamepads[i].Buttons.Back = true;
			} else { this->mGamepads[i].Buttons.Back = false; }
			if(this->mInputState[i].Gamepad.wButtons & XINPUT_GAMEPAD_START)
			{
				this->mGamepads[i].Buttons.Start = true;
			} else { this->mGamepads[i].Buttons.Start = false; }
			if(this->mInputState[i].Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
			{
				this->mGamepads[i].Buttons.LShoulder = true;
			} else { this->mGamepads[i].Buttons.LShoulder = false; }
			if(this->mInputState[i].Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
			{
				this->mGamepads[i].Buttons.RShoulder = true;
			} else { this->mGamepads[i].Buttons.RShoulder = false; }
			if(this->mInputState[i].Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
			{
				this->mGamepads[i].Buttons.LThumb = true;
			} else { this->mGamepads[i].Buttons.LThumb = false; }
			if(this->mInputState[i].Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
			{
				this->mGamepads[i].Buttons.RThumb = true;
			} else { this->mGamepads[i].Buttons.RThumb = false; }

			// Get the Dpad buttons
			if(this->mInputState[i].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
			{
				this->mGamepads[i].DPad.Up = true;
			} else { this->mGamepads[i].DPad.Up = false; }
			if(this->mInputState[i].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
			{
				this->mGamepads[i].DPad.Down = true;
			} else { this->mGamepads[i].DPad.Down = false; }
			if(this->mInputState[i].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
			{
				this->mGamepads[i].DPad.Left = true;
			} else { this->mGamepads[i].DPad.Left = false; }
			if(this->mInputState[i].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
			{
				this->mGamepads[i].DPad.Right = true;
			} else { this->mGamepads[i].DPad.Right = false; }

			// Set the states for single press buttons
			// A
			if(!this->mGamepads[i].Buttons.A)
				this->mGamepads[i].ButtonsSingle.A = false;
			else
			{
				if(!this->mGamepads[i].ButtonsSingle.A && !this->mGamepads[i].ButtonsOld.A)
					this->mGamepads[i].ButtonsSingle.A = true;
				else
					this->mGamepads[i].ButtonsSingle.A = false;
			}
			// B
			if(!this->mGamepads[i].Buttons.B)
				this->mGamepads[i].ButtonsSingle.B = false;
			else
			{
				if(!this->mGamepads[i].ButtonsSingle.B && !this->mGamepads[i].ButtonsOld.B)
					this->mGamepads[i].ButtonsSingle.B = true;
				else
					this->mGamepads[i].ButtonsSingle.B = false;
			}
			if(!this->mGamepads[i].Buttons.X)
				this->mGamepads[i].ButtonsSingle.X = false;
			else
			{
				// X
				if(!this->mGamepads[i].ButtonsSingle.X && !this->mGamepads[i].ButtonsOld.X)
					this->mGamepads[i].ButtonsSingle.X = true;
				else
					this->mGamepads[i].ButtonsSingle.X = false;
			}
			// Y
			if(!this->mGamepads[i].Buttons.Y)
				this->mGamepads[i].ButtonsSingle.Y = false;
			else
			{
				if(!this->mGamepads[i].ButtonsSingle.Y && !this->mGamepads[i].ButtonsOld.Y)
					this->mGamepads[i].ButtonsSingle.Y = true;
				else
					this->mGamepads[i].ButtonsSingle.Y = false;
			}
			// Start
			if(!this->mGamepads[i].Buttons.Start)
				this->mGamepads[i].ButtonsSingle.Start = false;
			else
			{
				if(!this->mGamepads[i].ButtonsSingle.Start && !this->mGamepads[i].ButtonsOld.Start)
					this->mGamepads[i].ButtonsSingle.Start = true;
				else
					this->mGamepads[i].ButtonsSingle.Start = false;
			}
			// Back
			if(!this->mGamepads[i].Buttons.Back)
				this->mGamepads[i].ButtonsSingle.Back = false;
			else
			{
				if(!this->mGamepads[i].ButtonsSingle.Back && !this->mGamepads[i].ButtonsOld.Back)
					this->mGamepads[i].ButtonsSingle.Back = true;
				else
					this->mGamepads[i].ButtonsSingle.Back = false;
			}
			// Left Shoulder
			if(!this->mGamepads[i].Buttons.LShoulder)
				this->mGamepads[i].ButtonsSingle.LShoulder = false;
			else
			{
				if(!this->mGamepads[i].ButtonsSingle.LShoulder && !this->mGamepads[i].ButtonsOld.LShoulder)
					this->mGamepads[i].ButtonsSingle.LShoulder = true;
				else
					this->mGamepads[i].ButtonsSingle.LShoulder = false;
			}
			// Right Shoulder
			if(!this->mGamepads[i].Buttons.RShoulder)
				this->mGamepads[i].ButtonsSingle.RShoulder = false;
			else
			{
				if(!this->mGamepads[i].ButtonsSingle.RShoulder && !this->mGamepads[i].ButtonsOld.RShoulder)
					this->mGamepads[i].ButtonsSingle.RShoulder = true;
				else
					this->mGamepads[i].ButtonsSingle.RShoulder = false;
			}
			// Left Thumbstick
			if(!this->mGamepads[i].Buttons.LThumb)
				this->mGamepads[i].ButtonsSingle.LThumb = false;
			else
			{
				if(!this->mGamepads[i].ButtonsSingle.LThumb && !this->mGamepads[i].ButtonsOld.LThumb)
					this->mGamepads[i].ButtonsSingle.LThumb = true;
				else
					this->mGamepads[i].ButtonsSingle.LThumb = false;
			}
			// Right Thumbstick
			if(!this->mGamepads[i].Buttons.RThumb)
				this->mGamepads[i].ButtonsSingle.RThumb = false;
			else
			{
				if(!this->mGamepads[i].ButtonsSingle.RThumb && !this->mGamepads[i].ButtonsOld.RThumb)
					this->mGamepads[i].ButtonsSingle.RThumb = true;
				else
					this->mGamepads[i].ButtonsSingle.RThumb = false;
			}

			// DPad Up
			if(!this->mGamepads[i].DPad.Up)
				this->mGamepads[i].DPadSingle.Up = false;
			else
			{
				if(!this->mGamepads[i].DPadSingle.Up && !this->mGamepads[i].DPadOld.Up)
					this->mGamepads[i].DPadSingle.Up = true;
				else
					this->mGamepads[i].DPadSingle.Up = false;
			}
			// DPad Down
			if(!this->mGamepads[i].DPad.Down)
				this->mGamepads[i].DPadSingle.Down = false;
			else
			{
				if(!this->mGamepads[i].DPadSingle.Down && !this->mGamepads[i].DPadOld.Down)
					this->mGamepads[i].DPadSingle.Down = true;
				else
					this->mGamepads[i].DPadSingle.Down = false;
			}
			// DPad Left
			if(!this->mGamepads[i].DPad.Left)
				this->mGamepads[i].DPadSingle.Left = false;
			else
			{
				if(!this->mGamepads[i].DPadSingle.Left && !this->mGamepads[i].DPadOld.Left)
					this->mGamepads[i].DPadSingle.Left = true;
				else
					this->mGamepads[i].DPadSingle.Left = false;
			}
			// DPad Right
			if(!this->mGamepads[i].DPad.Right)
				this->mGamepads[i].DPadSingle.Right = false;
			else
			{
				if(!this->mGamepads[i].DPadSingle.Right && !this->mGamepads[i].DPadOld.Right)
					this->mGamepads[i].DPadSingle.Right = true;
				else
					this->mGamepads[i].DPadSingle.Right = false;
			}
		}
		else
		{
			// error! error! abort!
			this->mGamepads[i].Disconnected = true;
		}
	}
}

GamepadState InputManager::GetState(int _gamepad_id)
{
	if(_gamepad_id > 3)
		return this->mGamepadError;

	return this->mGamepads[_gamepad_id];
}

void InputManager::SetVibration(int _gamepad_id, float _left_rocker_amount, float _right_rocker_amount)
{
	if(_gamepad_id > 3)
		return;

	XINPUT_VIBRATION newVibration;
	ZeroMemory(&newVibration, sizeof(XINPUT_VIBRATION));
	newVibration.wLeftMotorSpeed = 65535 * _left_rocker_amount;
	newVibration.wRightMotorSpeed = 65535 * _right_rocker_amount;
	XInputSetState(_gamepad_id, &newVibration);
}