
#include "scene.h"
#include "player.h"
#include "background.h"

Scene::Scene()
{
	m_bg = NULL;
}

void Scene::SetBackGround(Background *bg)
{
	m_bg = bg;
}

void Scene::AddPlayer(std::string id,Player *p)
{
	m_players.insert(std::pair<std::string,Player*>(id,p));
}

void Scene::RemovePlayer(std::string id)
{
	Player *p = GetPlayer(id);
	if(p != NULL)
	{
		delete p;
		m_players.erase(id);
	}
}

Player *Scene::GetPlayer(std::string id)
{
	std::map<std::string,Player*>::iterator it = m_players.find(id);
	if(it == m_players.end())
		return NULL;
	else
		return it->second;
}

void Scene::CleanUp()
{
	if(m_bg != NULL)
		delete m_bg;

	for (std::map<std::string,Player*>::iterator it=m_players.begin(); it!=m_players.end(); ++it)
	{
		if(it->second != NULL)
			delete it->second;
	}

	m_players.clear();
}

void Scene::Update()
{
	for (std::map<std::string,Player*>::iterator it=m_players.begin(); it!=m_players.end(); ++it)
		it->second->Update();

	OnUpdate();
}

void Scene::Move()
{
	for (std::map<std::string,Player*>::iterator it=m_players.begin(); it!=m_players.end(); ++it)
		it->second->Move();

	OnMoved();
}

void Scene::Render()
{
	m_bg->Render();
	for (std::map<std::string,Player*>::iterator it=m_players.begin(); it!=m_players.end(); ++it)
	{
		if(it->second != NULL)
			it->second->Render();
	}

	OnRender();
}

void Scene::HitTest(float x, float y)
{
	for (std::map<std::string,Player*>::iterator it=m_players.begin(); it!=m_players.end(); ++it)
	{
		Player *p = it->second;
		Vector pos = p->GetPosition();
		Vector size = p->GetSize();

		if(x > pos.x && x < (pos.x + size.x))
		{
			if(y > pos.y && y < (pos.y + size.y))
			{
				onHit(it->first);
			}
		}
	}
}