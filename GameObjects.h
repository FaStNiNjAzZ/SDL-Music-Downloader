#pragma once
// =======================================================
// Libraries / Headers to include 
#include "Game.h"

class GameObject
{
public:
	GameObject();
	void update();
	void render();
	void setAlive(bool state) { isActive = state; }
	void addX(float xAmount) { x += xAmount; }
	void addY(float yAmount) { y += yAmount; }
	void Loadtexture(const char* spriteFileName);

	float getX() { return x; }
	float getY() { return y; }

protected: // derived classes can access
	bool isActive = false;
	float x = -100, y = -100;	 // off the screen by default
	float xVel = 0, yVel = 0;
	float speed = 6;
	float angle = 0;

	SDL_Rect srcRect = { 0,0,0,0 };
	SDL_Rect destRect = { 0,0,0,0 };
	SDL_Texture* spriteTexture = nullptr;
};

// =======================================================


class Projectile :GameObject
{
public:
	bool getAliveState() { return isActive; }
	void setAlive(bool state) { isActive = state; }
	void setBulletSpeed(float newSpeed) { speed = newSpeed; }
	float getX() { return x; }
	float getY() { return y; }
	Uint32 getSize() { return bulletSize; }

private:
	Uint32 lastTimeActivated = 0;
	Uint32 disableTime = 0;
	Uint32  bulletSize = 0;
	float damage = 100, range = 20;
};



// =======================================================

class PlayerCharacter :GameObject
{
public:
	float getX() { return x; }
	float getY() { return y; }
	float getAngle() { return angle; }
private:
	float drag = 0.99F;
	float acceleration = 50;
	int rotationSpeed = 360;
};

// =======================================================

class NPC :GameObject {
public:
	void setAlive(bool state) { isActive = state; }
	bool getAliveState() { return isActive; }
	void setSpeed(float newSpeed) { speed = newSpeed; }
	float getX() { return x; }
	float getY() { return y; }

private:
	float drag = 0.99F;
	float acceleration = 50;
};
