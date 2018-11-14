#ifndef _KPerpCore_Keyboard_hpp_
#define _KPerpCore_Keyboard_hpp_

namespace kp {
	enum class Mouse {
		LeftButton = 1,
		RightButton = 2,
		MiddleButton = 4,
		X1 = 5,
		X2 = 6,

		Horizontal = 1000,
		Vertical = 1001,
	};
	enum class Key {
		Cancel = 3,
		BackSpace = 8,
		Tab,

		// 0x0E - 0x0F			(...)

		Clear = 12,
		Return,
		Shift = 16,
		Control,
		Menu,
		Pause,
		Captial,
		Kana,

		// 0x16					(...)

		Junja = 17,
		Final,
		Kanji,

		// 0x1A					(...)

		Escape = 27,
		Convert,
		NonConvert,
		Accept,
		Modechange,

		Space,
		Prior,
		Next,
		End,
		Home,
		Left,
		Up,
		Right,
		Down,
		Select,
		Print,
		Execute,
		Snapshot,
		Insert,
		Delete,
		Help,

		// 0x29 - 0x39			0 1 ... 9
		// 0x3A - 0x40			: ; < = > ? @
		// 0x41 - 0x5A			A  B ... Z (a b ... z)

		WindowLeft = 91,
		WindowRight,
		Apps,

		// 0x5E					(...)

		Sleep = 95,

		Numpad0,
		Numpad1,
		Numpad2,
		Numpad3,
		Numpad4,
		Numpad5,
		Numpad6,
		Numpad7,
		Numpad8,
		Numpad9,
		NumpadMultiply,
		NumpadAdd,
		NumpadSeparator,
		NumpadSubtract,
		NumpadDecimal,
		NumpadDivide,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		F13,
		F14,
		F15,
		F16,
		F17,
		F18,
		F19,
		F20,
		F21,
		F22,
		F23,
		F24,

		NavigationView,
		NavigationMenu,
		NavigationUp,
		NavigationDown,
		NavigationLeft,
		NavigationRight,
		NavigationAccept,
		NavigationCancel,

		Numlock,
		Scroll,

		NumpadEnter,

		// 0x92 - 0x96			(Exclude NumpadEnter)(For other systems)

		LeftShift = 160,
		RightShift,
		LeftControl,
		RightControl,
		LeftAlt,
		RightAlt,
		
		BrowserBack,
		BrowserForward,
		BrowserRefresh,
		BrowserStop,
		Browsersearch,
		BrowserFavorites,
		BrowserHome,

		VolumeMute,
		VolumeDown,
		VolumeUp,
		MediaNextTrack,
		MediaPrevTrack,
		MediaStop,
		MediaPlayPause,
		LaunchMail,
		LaunchMediaSelect,
		App1,
		App2,

		// 0xB8 - 0xB9			(...)

		SemiColon = 186,		// Colon
		Equal,					// Add
		Comma,					// Less than
		Subtract,				// Underscore
		Period,					// Greater than
		Slash,					// Question Mark
		BackTick,				// Tilde

		// 0xC1 - OxC2			(...)

		Gamepad_A = 195,
		Gamepad_B,
		Gamepad_X,
		Gamepad_Y,
		Gamepad_Right_Shoulder,
		Gamepad_Left_Shoulder,
		Gamepad_Left_Trigger,
		Gamepad_Right_Trigger,
		Gamepad_Dpad_Up,
		Gamepad_Dpad_Down,
		Gamepad_Dpad_Left,
		Gamepad_Dpad_Right,
		Gamepad_Menu,
		Gamepad_View,
		Gamepad_Left_Thumbstick_Button,
		Gamepad_Right_Thumbstick_Button,
		Gamepad_Left_Thumbstick_Up,
		Gamepad_Left_Thumbstick_Down,
		Gamepad_Left_Thumbstick_Right,
		Gamepad_Left_Thumbstick_Left,
		Gamepad_Right_Thumbstick_Up,
		Gamepad_Right_Thumbstick_Down,
		Gamepad_Right_Thumbstick_Right,
		Gamepad_Right_Thumbstick_Left,
		
		LeftSquareBracket,			// Left Curly Bracket
		BackSlash,					// Vertical Bar
		RightSquareBracket,			// Right Curly Bracket
		Quote,						// Double Quotes

		// 0xDF - 0xE0				(...)
	};
}

#endif
