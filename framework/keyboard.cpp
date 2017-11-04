#include "keyboard.h"

Keyboard::Keyboard() {
	//Set the global key handler to this object
	glKeys = this;
	//Setup keyboard callbacks
	glutKeyboardFunc(keyDownHandler);
	glutKeyboardUpFunc(keyUpHandler);
	glutSpecialFunc(specialKeyDownHandler);
	glutSpecialUpFunc(specialKeyUpHandler);

	//Re-Initialize keyboard arrays
	for(int i = 0; i < KEYS_ARR_SIZE; i++) {
		glKeys->keyDowns[i] = 0;
		glKeys->keyUps[i] = 0;
		glKeys->keysPressed[i] = 0;
	}

	//Re-Initialize special keyboard arrays
	for(int i = 0; i < SKEYS_ARR_SIZE; i++) {
		glKeys->sKeyDowns[i] = 0;
		glKeys->sKeyUps[i] = 0;
		glKeys->sKeysPressed[i] = 0;
	}

	//Reset Keyboard values
	resetKeyEvents();
}

Keyboard::~Keyboard() {}

void Keyboard::resetKeyEvents() {
	int i = 0;

	//Re-Initialize keyboard arrays
	for(i = 0; i < KEYS_ARR_SIZE; i++) {
		glKeys->keyDowns[i] = 0;
		glKeys->keyUps[i] = 0;
	}

	//Re-Initialize special keyboard arrays
	for(i = 0; i < SKEYS_ARR_SIZE; i++) {
		glKeys->sKeyDowns[i] = 0;
		glKeys->sKeyUps[i] = 0;
	}
}

void Keyboard::keyDownHandler(unsigned char key, int x, int y) {
	//Update pressed key to true in keys array
	setKey(glKeys->keysPressed, (int)key, true);
	//Update key down event
	setKey(glKeys->keyDowns, (int)key, true);

	//If the key is a lowercase key, also set the uppercase version
	if ((int)key >= 'a' && (int)key <= 'z') {
		//Update pressed key to true in keys array
		setKey(glKeys->keysPressed, (int)key - ASCII_CAPS_DIFFERENCE, true);
		//Update key down event
		setKey(glKeys->keyDowns, (int)key - ASCII_CAPS_DIFFERENCE, true);
	}
	//If the key is uppercase, also set the lowercase version
	else if ((int)key >= 'A' && (int)key <= 'Z') {
		//Update pressed key to true in keys array
		setKey(glKeys->keysPressed, (int)key + ASCII_CAPS_DIFFERENCE, true);
		//Update key down event
		setKey(glKeys->keyDowns, (int)key + ASCII_CAPS_DIFFERENCE, true);
	}
}

void Keyboard::keyUpHandler(unsigned char key, int x, int y) {
	//Update pressed key to true in keys array
	setKey(glKeys->keysPressed, (int)key, false);
	//Update key down event
	setKey(glKeys->keyUps, (int)key, true);

	//If the key is a lowercase key, also set the uppercase version
	if ((int)key >= 'a' && (int)key <= 'z') {
		//Update pressed key to true in keys array
		setKey(glKeys->keysPressed, (int)key - 32, false);
		//Update key down event
		setKey(glKeys->keyUps, (int)key - 32, true);
	}
	//If the key is uppercase, also set the lowercase version
	else if ((int)key >= 'A' && (int)key <= 'Z') {
		//Update pressed key to true in keys array
		setKey(glKeys->keysPressed, (int)key + 32, false);
		//Update key down event
		setKey(glKeys->keyUps, (int)key + 32, true);
	}
}

void Keyboard::specialKeyDownHandler(int key, int x, int y) {
	//Update pressed key to true in keys array
	setKey(glKeys->sKeysPressed, key, true);
	//Update key down event
	setKey(glKeys->sKeyDowns, key, true);
}

void Keyboard::specialKeyUpHandler(int key, int x, int y) {
	//Update pressed key to true in keys array
	setKey(glKeys->sKeysPressed, key, false);
	//Update key down event
	setKey(glKeys->sKeyUps, key, true);
}

void Keyboard::setKey(unsigned short* keys, int key, bool val) {
	//Get the index where the bit falls in the array
	const unsigned short arrIndex = key / SIZEOF_SHORT;
	//Get the bitmask for setting the value
	const unsigned short mask = 1 << (key % SIZEOF_SHORT);

	if (val)
		//If the value is true then set the bit
		keys[arrIndex] = keys[arrIndex] | mask;
	else
		//if the value is false then unset the bit
		keys[arrIndex] = keys[arrIndex] & ~mask;
}

bool Keyboard::getKey(unsigned short* keys, int key) {
	//Get the index where the bit falls in the array
	const unsigned short arrIndex = key / SIZEOF_SHORT;
	//Get the bitmask for setting the value
	const unsigned short mask = 1 << (key % SIZEOF_SHORT);

	unsigned short val = keys[arrIndex] & mask;

	//Return value of bit
	return (keys[arrIndex] & mask) != 0;
}

bool Keyboard::isPressed(unsigned char key) {
	return getKey(glKeys->keysPressed, key);
}

bool Keyboard::keyDownEvent(unsigned char key) {
	return getKey(glKeys->keyDowns, key);
}

bool Keyboard::keyUpEvent(unsigned char key) {
	return getKey(glKeys->keyUps, key);
}

bool Keyboard::isSpecialKeyPressed(SPECIAL_KEYS key) {
	return getKey(glKeys->sKeysPressed, key);
}

bool Keyboard::specialKeyDown(SPECIAL_KEYS key) {
	return getKey(glKeys->sKeyDowns, key);
}

bool Keyboard::specialKeyUp(SPECIAL_KEYS key) {
	return getKey(glKeys->sKeyUps, key);
}