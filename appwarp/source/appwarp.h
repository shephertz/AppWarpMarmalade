
#ifndef __APPWARP__
#define __APPWARP__

#include <string>
#include <time.h>
#include <sstream>
#include <map>
#include <vector>

#include "pthread.h"
#include "IwHTTP.h"

#include "defines.h"
#include "socket.h"
#include "listener.h"

namespace AppWarp
{
	extern int AppWarpSessionID;

	class Client : public AppWarp::Utility::Socket
	{
	private:
		std::string APIKEY;
		std::string SECRETKEY;
		std::string APPWARPSERVERHOST;
		std::string LOOKUPHOST;
		int APPWARPSERVERPORT;

		static Client* _instance;
		Client();
		ConnectionRequestListener * _connectionReqListener;
		LobbyRequestListener *_lobbyListener;
		NotificationListener *_notificationListener;
		ChatRequestListener *_chatlistener;
		RoomRequestListener *_roomlistener;
		ZoneRequestListener *_zonelistener;
		UpdateRequestListener *_updatelistener;

		int handleResponse(char *, int);
		int handleNotify(char *, int);
		void handleAuthResponse(response *);
		void handleLobbyResponse(int,response *);
		void handleRoomResponse(int, response *);
		void handleZoneResponse(int, response *);
		pthread_t thread;

		std::string userName;
		CIwHTTP *http;
		static int32 GotHeaders(void *, void *);

		bool threaded;
	public:
		~Client();
		static Client* getInstance();
		static void initialize(std::string, std::string);
		void SetPollingMode(bool);
		void setConnectionRequestListener(ConnectionRequestListener *);
		void setLobbyRequestListener(LobbyRequestListener *);
		void setNotificationListener(NotificationListener *);
		void setChatRequestListener(ChatRequestListener *);
		void setRoomRequestListener(RoomRequestListener *);
		void setZoneRequestListener(ZoneRequestListener *);
		void setUpdateRequestListener(UpdateRequestListener *);

		void connect(std::string);
		void disconnect();
		void joinLobby();
		void leaveLobby();
		void subscribeLobby();
		void unsubscribeLobby();
		void joinRoom(std::string);
		void subscribeRoom(std::string);
		void leaveRoom(std::string);
		void unsubscribeRoom(std::string);
		void createRoom(std::string,std::string,int);
		void createRoom(std::string,std::string,int,std::map<std::string,std::string>);
		void deleteRoom(std::string);
		void getLiveRoomInfo(std::string);
		void getLiveLobbyInfo();
		void getLiveUserInfo(std::string);
		void sendChat(std::string);
		void sendUpdate(byte*,int);
		void setCustomUserData(std::string, std::string);
		void setCustomRoomData(std::string, std::string);
		void getAllRooms();
		void getOnlineUsers();
		void updateRoomProperties(std::string, std::map<std::string,std::string>,std::vector<std::string>);
		void updateRoomProperties(std::string, std::map<std::string,std::string>);
		void joinRoomWithNUser(int);
		void joinRoomWithProperties(std::map<std::string,std::string>);
		void getRoomWithNUser(int);
		void getRoomWithProperties(std::map<std::string,std::string>);
		void terminate();
		void Update();

		void sockonConnection(int);
		void sockonMsg(char[], int len);
	};
}

#endif