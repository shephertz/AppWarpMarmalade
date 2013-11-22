

#include "player.h"

Player::Player()
{
	Position.x = 0;
	Position.y = 0;
	Velocity.x = 0;
	Velocity.y = 0;
	Target.x = 0;
	Target.y = 0;

	spirit = NULL;
}
Player::~Player()
{
	if(spirit != NULL)
		delete spirit;
}
void Player::SetPosition(float x,float y)
{
	Position.x = x;
	Position.y = y;
}
void Player::SetVelocity(float x,float y)
{
	Velocity.x = x;
	Velocity.y = y;
}
void Player::Init(std::string path)
{
	spirit = Iw2DCreateImage(path.c_str());
}
void Player::Update()
{
	Position.x += Velocity.x;
	Position.y += Velocity.y;
}
void Player::Render()
{
	Iw2DDrawImage(spirit,CIwFVec2(Position.x,Position.y));
}
void Player::SetTarget(float x,float y)
{
	Target.x = x-(spirit->GetWidth()/2);
	Target.y = y-(spirit->GetHeight()/2);
}
void Player::Move()
{
	if(Position.x < Target.x)
		Position.x += Velocity.x;
	if(Position.y < Target.y)
		Position.y += Velocity.y;
	if(Position.x > Target.x)
		Position.x -= Velocity.x;
	if(Position.y > Target.y)
		Position.y -= Velocity.y;
}

Vector Player::GetPosition()
{
	return Position;
}

Vector Player::GetVelocity()
{
	return Velocity;
}

Vector Player::GetSize()
{
	Vector size;
	size.x = spirit->GetWidth();
	size.y = spirit->GetHeight();
	return size;
}