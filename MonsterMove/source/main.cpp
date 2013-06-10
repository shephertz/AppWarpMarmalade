
#include "main.h"

std::string genRandom()
{
	std::string charStr;
	srand (time(NULL));

	for (int i = 0; i < 10; ++i) {
		charStr += (char)(65+(rand() % (26)));
	}

	return charStr;
}

MenuScreen::MenuScreen()
{
	game = NULL;
	app = NULL;
	
	Player *p1 = new Player;
	Player *p2 = new Player;
	Player *p3 = new Player;
	Player *p4 = new Player;
	Player *p5 = new Player;

	p1->Init("monster1.png");
	p2->Init("monster2.png");
	p3->Init("monster3.png");
	p4->Init("monster4.png");
	p5->Init("monster5.png");

	p1->SetPosition((float)((Iw2DGetSurfaceWidth()/2)-65),(float)(Iw2DGetSurfaceHeight()/2-58));
	p2->SetPosition((float)((Iw2DGetSurfaceWidth()/2)+10),(float)(Iw2DGetSurfaceHeight()/2-58));
	p3->SetPosition((float)((Iw2DGetSurfaceWidth()/2)-92),(float)(Iw2DGetSurfaceHeight()/2+10));
	p4->SetPosition((float)((Iw2DGetSurfaceWidth()/2)-28),(float)(Iw2DGetSurfaceHeight()/2+10));
	p5->SetPosition((float)((Iw2DGetSurfaceWidth()/2)+38),(float)(Iw2DGetSurfaceHeight()/2+10));

	Background *bg = new Background;
	bg->Init("bg2.png",(float)Iw2DGetSurfaceWidth(),(float)Iw2DGetSurfaceHeight(),true);

	SetBackGround(bg);
	AddPlayer("monster1",p1);
	AddPlayer("monster2",p2);
	AddPlayer("monster3",p3);
	AddPlayer("monster4",p4);
	AddPlayer("monster5",p5);
}

void MenuScreen::onHit(std::string id)
{
	Player *p = GetPlayer(id);

	if(game != NULL)
	{
		game->Init(id.c_str());
		if(app != NULL)
		{
			app->SetScene("game");
		}
	}
}

void MenuScreen::Touch(int pressed, float x,float y)
{
	if(pressed == 0)
		HitTest(x,y);
}

void GameScreen::Init(std::string name)
{
	Player *p1 = new Player;
	p1->Init(name+".png");

	p1->SetPosition((float)((Iw2DGetSurfaceWidth()/2)-28),(float)(Iw2DGetSurfaceHeight()/2-28));
	p1->SetTarget(p1->GetPosition().x,p1->GetPosition().y);
	p1->SetVelocity(1,1);
	Background *bg = new Background;
	bg->Init("bg.png",(float)Iw2DGetSurfaceWidth(),(float)Iw2DGetSurfaceHeight());

	SetBackGround(bg);
	player = name;
	warpID = name + genRandom();
	AddPlayer(warpID,p1);

	WarpClientRef->connect(warpID);
}

void GameScreen::Touch(int pressed, float x,float y)
{
	if(pressed == 0)
	{
		Player *p = GetPlayer(warpID);
		p->SetTarget(x,y);

		std::stringstream str;
		str << x << "x" << y;
		WarpClientRef->sendChat(str.str());
	}
}

void GameScreen::AddRemotePlayer(std::string name,std::string id,float x,float y)
{
	Player *p1 = new Player;
	p1->Init(name+".png");

	p1->SetPosition((float)((Iw2DGetSurfaceWidth()/2)-28),(float)(Iw2DGetSurfaceHeight()/2-28));
	p1->SetTarget(x,y);
	p1->SetVelocity(1,1);

	AddPlayer(id,p1);
}

void Listener::onConnectDone(int res)
{
	if(res == AppWarp::ResultCode::success)
		appwarp->joinRoom("1440375425");

	gs->msg = "Joining Room...";
}

void Listener::onSubscribeRoomDone(AppWarp::room revent)
{
	if(revent.result == AppWarp::ResultCode::success)
	{
		std::stringstream str;
		str << gs->GetPlayer(gs->warpID)->GetPosition().x << "x" << gs->GetPlayer(gs->warpID)->GetPosition().y;

		appwarp->sendChat(str.str());
	}

	gs->msg = "Connected :-)";
}

void Listener::onJoinRoomDone(AppWarp::room revent)
{
	if(revent.result == AppWarp::ResultCode::success)
		appwarp->subscribeRoom("1440375425");

	gs->msg = "Subscribing Room...";
}

void Listener::onChatReceived(AppWarp::chat chatevent)
{
	if(chatevent.sender != gs->warpID)
	{
		std::size_t loc = chatevent.chat.find('x');
		std::string str1 = chatevent.chat.substr(0,loc);
		std::string str2 = chatevent.chat.substr(loc+1);
		float x = (float)std::atof (str1.c_str());
		float y = (float)std::atof(str2.c_str());
		std::string type = chatevent.sender.substr(0,8);

		Player *p = gs->GetPlayer(chatevent.sender);
		if(p != NULL)
		{
			p->SetTarget(x,y);
		}
		else
		{
			gs->AddRemotePlayer(type,chatevent.sender,x,y);
		}
	}
}

void Listener::onUserLeftRoom(AppWarp::room rData, std::string user)
{
	gs->RemovePlayer(user);
}

void HandleSingleTouchButtonCB(s3ePointerEvent* event,Game *gm)
{
	if(gm != NULL)
	{
		gm->Touch((int)event->m_Pressed,(float)event->m_x,(float)event->m_y);
	}
}

int main()
{
	IwGxInit();
	Iw2DInit();

	AppWarp::Client* WarpClientRef;
	AppWarp::Client::initialize("b29f4030aba3b2bc7002c4eae6815a4130c862c386e43ae2a0a092b27de1c5af","bf45f27e826039754f8dda659166d59ffb7b9dce830ac51d6e6b576ae4b26f7e");
	WarpClientRef = AppWarp::Client::getInstance();

	MenuScreen *menu = new MenuScreen;
	GameScreen *game = new GameScreen(WarpClientRef);

	Game *gm = new Game;
	gm->AddScene("game",game);
	gm->AddScene("menu",menu);

	menu->game = game;
	menu->app = gm;

	Listener listener(WarpClientRef,game);
	WarpClientRef->setConnectionRequestListener(&listener);
	WarpClientRef->setRoomRequestListener(&listener);
	WarpClientRef->setNotificationListener(&listener);

	s3ePointerRegister(S3E_POINTER_BUTTON_EVENT,(s3eCallback)HandleSingleTouchButtonCB,gm);

	while(!s3eDeviceCheckQuitRequest())
	{
		s3eKeyboardUpdate();
		if(s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN)
			break;

		WarpClientRef->Update();
		s3ePointerUpdate();
		IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);

		IwGxPrintSetScale(2);
		IwGxPrintString(0,0,game->msg.c_str());

		gm->Move();
		gm->Render();

		Iw2DSurfaceShow();
		s3eDeviceYield();
	}

	s3ePointerUnRegister(S3E_POINTER_BUTTON_EVENT,(s3eCallback)HandleSingleTouchButtonCB);

	gm->CleanUp();
	delete menu;
	delete game;
	delete gm;

	WarpClientRef->terminate();

	Iw2DTerminate();
	IwGxTerminate();
}