
#include "game.h"
#include "scene.h"

void Game::AddScene(std::string id,Scene *scene)
{
	m_scenes.insert(std::pair<std::string,Scene*>(id,scene));
	currentScene = id;
}

void Game::SetScene(std::string id)
{
	currentScene = id;
}

void Game::CleanUp()
{
	for (std::map<std::string,Scene*>::iterator it=m_scenes.begin(); it!=m_scenes.end(); ++it)
	{
		IwDebugTraceLinePrintf("Cleaning %s",it->first.c_str());
		it->second->CleanUp();
	}

	m_scenes.clear();
}

void Game::Update()
{
	m_scenes[currentScene]->Update();
}

void Game::Render()
{
	m_scenes[currentScene]->Render();
}

void Game::Move()
{
	m_scenes[currentScene]->Move();
}

void Game::Touch(int pressed, float x,float y)
{
	m_scenes[currentScene]->Touch(pressed,x,y);
}

Scene* Game::GetScene(std::string id)
{
	std::map<std::string,Scene*>::iterator it = m_scenes.find(id);
	if(it == m_scenes.end())
		return NULL;
	else
		return it->second;
}

std::string Game::GetCurrentScene()
{
	return currentScene;
}