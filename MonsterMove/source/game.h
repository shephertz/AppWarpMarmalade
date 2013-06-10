
#ifndef __GAME__
#define __GAME__

#include "s3e.h"
#include "Iw2D.h"
#include "IwGx.h"
#include <string>
#include <map>

struct Vector
{
	float x;
	float y;
};

class Game;
class Scene;
class Background;
class Player;

class Game
{
	std::map<std::string,Scene*> m_scenes;
	std::string currentScene;
public:
	void AddScene(std::string,Scene *);
	void SetScene(std::string);
	std::string GetCurrentScene();
	void CleanUp();
	void Touch(int, float,float);
	void Update();
	void Render();
	void Move();
	Scene* GetScene(std::string);
};

#endif