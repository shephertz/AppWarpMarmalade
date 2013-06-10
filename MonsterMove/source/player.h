
#ifndef __PLAYER__
#define __PLAYER__

#include "game.h"

class Player
{
	Vector Position;
	Vector Velocity;
	Vector Target;
	CIw2DImage *spirit;
public:
	Player();
	~Player();
	void SetPosition(float x,float y);
	void SetVelocity(float x,float y);
	Vector GetPosition();
	Vector GetVelocity();
	Vector GetSize();
	void Init(std::string path);
	void Update();
	void Render();
	void SetTarget(float x,float y);
	void Move();
};

#endif