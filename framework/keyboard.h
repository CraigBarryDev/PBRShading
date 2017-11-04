#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "GLHeaders.h"

#define ASCII_CAPS_DIFFERENCE 32
#define SIZEOF_SHORT 16

#define KEYS_ARR_SIZE 16
#define SKEYS_ARR_SIZE 2

class Keyboard;

static Keyboard* glKeys;

typedef enum {
	SPECIAL_KEY_F1,
	SPECIAL_KEY_F2,
	SPECIAL_KEY_F3,
	SPECIAL_KEY_F4,
	SPECIAL_KEY_F5,
	SPECIAL_KEY_F6,
	SPECIAL_KEY_F7,
	SPECIAL_KEY_F8,
	SPECIAL_KEY_F9,
	SPECIAL_KEY_F10,
	SPECIAL_KEY_F11,
	SPECIAL_KEY_F12,
	SPECIAL_KEY_LEFT = 100,
	SPECIAL_KEY_RIGHT = 102,
	SPECIAL_KEY_UP,
	SPECIAL_KEY_DOWN,
	SPECIAL_KEY_INSERT,
	SPECIAL_KEY_PAGE_UP,
	SPECIAL_KEY_PAGE_DOWN,
	SPECIAL_KEY_HOME,
	SPECIAL_KEY_END
}SPECIAL_KEYS;

class Keyboard {
public:
	Keyboard();
	~Keyboard();
	void resetKeyEvents();

	bool isPressed(unsigned char key);
	bool keyDownEvent(unsigned char key);
	bool keyUpEvent(unsigned char key);

	bool isSpecialKeyPressed(SPECIAL_KEYS key);
	bool specialKeyDown(SPECIAL_KEYS key);
	bool specialKeyUp(SPECIAL_KEYS key);
private:
	static void keyDownHandler(unsigned char key, int x, int y);
	static void keyUpHandler(unsigned char key, int x, int y);
	static void specialKeyDownHandler(int key, int x, int y);
	static void specialKeyUpHandler(int key, int x, int y);
	static void setKey(unsigned short* keys, int key, bool val);
	static bool getKey(unsigned short* keys, int key);
private:
	unsigned short keysPressed[KEYS_ARR_SIZE];
	unsigned short keyDowns[KEYS_ARR_SIZE];
	unsigned short keyUps[KEYS_ARR_SIZE];

	unsigned short sKeysPressed[SKEYS_ARR_SIZE];
	unsigned short sKeyDowns[SKEYS_ARR_SIZE];
	unsigned short sKeyUps[SKEYS_ARR_SIZE];
};

#endif