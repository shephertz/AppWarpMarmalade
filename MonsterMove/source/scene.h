
#ifndef __SCENE__
#define __SCENE__

#include "game.h"

class Scene
{
	std::map<std::string,Player*> m_players;
	Background *m_bg;
public:
	Scene();
	void SetBackGround(Background *);
	void AddPlayer(std::string,Player *);
	void RemovePlayer(std::string);
	void CleanUp();
	Player *GetPlayer(std::string);
	void Render();
	void Update();
	void Move();
	void HitTest(float,float);
	virtual void onHit(std::string){}
	virtual void Touch(int, float,float){}
	virtual void OnUpdate(){}
	virtual void OnMoved(){}
	virtual void OnRender(){}
};

#endif