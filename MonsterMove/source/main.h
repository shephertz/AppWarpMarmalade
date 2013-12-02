

#include "..\appwarp\appwarp.h"
#include "game.h"
#include "scene.h"
#include "player.h"
#include "background.h"

#include <sstream>

class GameScreen : public Scene
{
	AppWarp::Client *WarpClientRef;
public:
	std::string msg;
	std::string player;
	std::string warpID;
	GameScreen(AppWarp::Client *client){ WarpClientRef = client; }
	void Init(std::string);
	void Touch(int pressed, float x,float y);
	void AddRemotePlayer(std::string,std::string,float,float);
};

class MenuScreen : public Scene
{
public:
	GameScreen *game;
	Game *app;

	MenuScreen();
	void onHit(std::string );
	void Touch(int , float ,float );
};

class Listener : public AppWarp::ConnectionRequestListener, public AppWarp::RoomRequestListener, public AppWarp::NotificationListener
{
	AppWarp::Client *appwarp;
	GameScreen *gs;
public:
	Listener(AppWarp::Client *client, GameScreen *g){ appwarp = client; gs = g; }
	void onConnectDone(int);
	void onSubscribeRoomDone(AppWarp::room revent);
	void onJoinRoomDone(AppWarp::room revent);
	void onChatReceived(AppWarp::chat chatevent);
	void onUserLeftRoom(AppWarp::room rData, std::string user);
};