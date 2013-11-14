
/**
Using AppWarp, developers can now add realtime communication to their Marmalade games to build 
beautiful, rich and engaging multiplayer games. The great thing is that developers can do this 
without any server side code or socket level programming as all the communication is managed 
by AppWarp Marmalade SDK and cloud.

@author Suyash Mohan (suyash.mohan@shephertz.co.in)
*/

#ifndef __APPWARP__
#define __APPWARP__

#include <string>
#include <time.h>
#include <sstream>
#include <map>
#include <vector>

#include "IwHTTP.h"
//#include "IwGx.h"

#include "HMAC_SHA1.h"
#include "base64.h"
#include "urlencode.h"
#include "cJSON.h"

#include "defines.h"
#include "utilities.h"
#include "requests.h"
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

		std::string userName;
		CIwHTTP *http;
		static int32 GotHeaders(void *, void *);

		bool m_isConnected;
	public:
		~Client();

		/**
		 * Tells whether AppWARP SDK is connected to AppWARP server or not
		 * @return bool
		 */
		bool isConnected() { return m_isConnected; }

		/**
		* Returns the singleton instance of WarpClient
		*/
		static Client* getInstance();

		/**
		 * This should be your first API call to WarpClient. This will instantiate
		 * the WarpClient singleton and set it up to be used with the keys provided
		 * in params. Calling it more than once will return error. This will setup
		 * the client to work with the cloud server appwarp.shephertz.com
		 *
		 * @param apikey
		 * @param secretekey
		 * @return void
		 */
		static void initialize(std::string apikey, std::string secretekey);

		/**
		 * Set your listener object on which callbacks will be invoked when a
		 * response from the server is received for connect, authenticate and
		 * disconnect APIs.
		 *
		 * @param listener
		 * @return void
		 */
		void setConnectionRequestListener(ConnectionRequestListener *listener);

		/**
		 * Set your listener object on which callbacks will be invoked when a
		 * response from the server is received for Lobby requests like
		 * join/leaveLobby, subscribe/unsubscribeLobby and getLiveLobbyInfo
		 *
		 * @param listener
		 * @return void
		 */
		void setLobbyRequestListener(LobbyRequestListener *listener);

		/**
		 * Set your listener object on which callbacks will be invoked when a
		 * notification is received from the server for any resource that has been
		 * subscribed to.
		 *
		 * @param listener
		 * @return void
		 */
		void setNotificationListener(NotificationListener *listener);

		/**
		 * Set your listener object on which callbacks will be invoked when a
		 * response from the server is received for sendChat request.
		 *
		 * @param listener
		 * @return void
		 */
		void setChatRequestListener(ChatRequestListener *listener);

		/**
		 * Set your listener object on which callbacks will be invoked when a
		 * response from the server is received for Room requests like
		 * join/leaveRoom, subscribe/unsubscribeRoom and getLiveRoomInfo
		 *
		 * @param listener
		 * @return void
		 */
		void setRoomRequestListener(RoomRequestListener *listener);

		/**
		 * Set your listener object on which callbacks will be invoked when a
		 * response from the server is received for Zone level requests like
		 * create/deleteRoom, User requests etc. disconnect APIs.
		 *
		 * @param listener
		 * @return void
		 */
		void setZoneRequestListener(ZoneRequestListener *listener);

		/**
		 * Set your listener object on which callbacks will be invoked when a
		 * response from the server is received for sendUpdate request.
		 *
		 * @param listener
		 * @return void
		 */
		void setUpdateRequestListener(UpdateRequestListener *listener);

		/**
		 * Initiates your connection with the WARP server. The result of the
		 * operation is provided in the onConnectDone callback of the
		 * ConnectionListener.
		 *
		 * @param user
		 * @return void
		 */
		void connect(std::string user);

		/**
		 * Disconnects the connection with the WARP server. The result for this
		 * request will be provided in the onDisconnectDone callback of the
		 * ConnectionListener.
		 *
		 * @return void
		 */
		void disconnect();

		/**
		 * sends a join lobby request to the server. Result of the request is
		 * provided in the onJoinLobbyDone callback of the LobbyListener
		 *
		 * @return void
		 */
		void joinLobby();

		/**
		 * sends a leave lobby request to the server. Result of the request is
		 * provided in the onLeaveLobbyDone callback of the LobbyListener
		 *
		 * @return void
		 */
		void leaveLobby();

		/**
		 * sends a subscribe lobby request to the server. Result of the request is
		 * provided in the onSubscribeLobbyDone callback of the LobbyListener
		 *
		 * @return void
		 */
		void subscribeLobby();

		/**
		 * sends a unsubscribe lobby request to the server. Result of the request is
		 * provided in the onUnSubscribeLobbyDone callback of the LobbyListener
		 *
		 * @return void
		 */
		void unsubscribeLobby();

		/**
		 * sends a join room request to the server. Result of the request is
		 * provided in the onJoinRoomDone callback of the RoomListener.
		 *
		 * @param roomId
		 * @return void
		 */
		void joinRoom(std::string roomId);

		/**
		 * sends a subscribe room request to the server. Result of the request is
		 * provided in the onSubscribeRoomDone callback of the RoomListener.
		 *
		 * @param roomId
		 * @return void
		 */
		void subscribeRoom(std::string roomId);

		/**
		 * sends a leave room request to the server. Result of the request is
		 * provided in the onLeaveRoomDone callback of the RoomListener.
		 *
		 * @param roomId
		 * @return void
		 */
		void leaveRoom(std::string roomId);

		/**
		 * sends a unsubscribe room request to the server. Result of the request is
		 * provided in the onUnsubscribeRoomDone callback of the RoomListener.
		 *
		 * @param roomId
		 * @return void
		 */
		void unsubscribeRoom(std::string roomId);
		
		/**
		 * sends a create room request to the server. Result of the request is
		 * provided in the onCreateRoomDone callback of the ZoneRequestListener.
		 *
		 * @param name
		 * @param owner
		 * @param maxUsers
		 * @return void
		 */
		void createRoom(std::string name,std::string owner,int maxUsers);

		/**
		 * sends a create room request to the server. Result of the request is
		 * provided in the onCreateRoomDone callback of the ZoneRequestListener.
		 *
		 * @param name
		 * @param owner
		 * @param maxUsers
		 * @param properties
		 * @return void
		 */
		void createRoom(std::string name,std::string owner,int maxUsers,std::map<std::string,std::string> properties);

		 /**
		 * sends a delete room request to the server. Result of the request is
		 * provided in the onDeleteRoomDone callback of the ZoneListener.
		 *
		 * @param roomId
		 * @return void
		 */
		void deleteRoom(std::string roomId);

		/**
		 * Retrieves live information of the room from the server. Result is
		 * provided in the onGetLiveRoomInfo callback of the RoomListener.
		 *
		 * @param roomid
		 * @return void
		 */
		void getLiveRoomInfo(std::string roomid);

		/**
		 * Retrieves live information of the lobby from the server. Result is
		 * provided in the onGetLiveLobbyInfo callback of the LobbyListener.
		 *
		 * @return void
		 */
		void getLiveLobbyInfo();

		/**
		 * Retrieves live information of the user from the server. Result is
		 * provided in the onGetLiveUserInfo callback of the ZoneListener.
		 *
		 * @param username
		 * @return void
		 */
		void getLiveUserInfo(std::string username);

		/**
		 * sends a chat message to room in which the user is currently joined.
		 * Result of the request is provided in the onSendChatDone callback of the
		 * ChatListener.
		 *
		 * @param message
		 * @return void
		 */
		void sendChat(std::string message);

		/**
		 * sends a custom update message to room in which the user is currently
		 * joined. Result of the request is provided in the onSendUpdatePeersDone
		 * callback of the UpdateListener.
		 *
		 * @param update
		 * @param updateLen
		 */
		void sendUpdate(byte* update,int updateLen);

		/**
		 * Updates the custom roomData associated with the given user on the server.
		 * Result is provided in the onSetCustomUserDataDone callback of the
		 * ZoneListener.
		 *
		 * @param username
		 * @param roomData
		 * @return void
		 */
		void setCustomUserData(std::string username, std::string roomData);

		/**
		 * Updates the custom roomData associated with the given room on the server.
		 * Result is provided in the onSetCustomRoomDataDone callback of the
		 * RoomListener.
		 *
		 * @param roomid
		 * @param roomData
		 * @return void
		 */
		void setCustomRoomData(std::string roomid, std::string roomData);

		/**
		 * Retrieves room ids of all the live rooms on the server. Result is
		 * provided in the onGetAllRoomsDone callback of the ZoneListener.
		 *
		 * @return void
		 */
		void getAllRooms();

		/**
		 * Retrieves usernames of all the users connected to the server. Result is
		 * provided in the onGetOnlineUsers callback of the ZoneListener.
		 *
		 * return @void
		 */
		void getOnlineUsers();

		/**
		 * sends a update room properties request to the server to update the properties of the room
		 * Result of the request is provided
		 * in the onJoinRoomDone callback of the RoomListener.
		 * @param roomId 
		 * @param properties 
		 * @param removeProperties 
		 */
		void updateRoomProperties(std::string roomId, std::map<std::string,std::string> properties,std::vector<std::string> removeProperties);

		/**
		 * sends a update room properties request to the server to update the properties of the room
		 * Result of the request is provided
		 * in the onJoinRoomDone callback of the RoomListener.
		 *
		 * @param roomId 
		 * @param properties 
		 * return @void
		 */
		void updateRoomProperties(std::string, std::map<std::string,std::string>);

		/**Match making
		 * sends a join room request to the server if user want to join a room with n user
		 * Result of the request is provided
		 * in the onJoinRoomDone callback of the RoomListener.
		 *
		 * @param userCount 
		 * return @void
		 */
		void joinRoomWithNUser(int userCount);

		/**Match making
		 * sends a join room request to the server if user want to join a room with required properties
		 * Result of the request is provided
		 * in the onJoinRoomDone callback of the RoomListener.
		 *
		 * @param properties 
		 * return @void
		 */
		void joinRoomWithProperties(std::map<std::string,std::string> properties);

		/**
		 * Retrieves information of the rooms that contain n user in it from the server. Result is
		 * provided in the onGetLiveRoomInfo callback of the RoomListener.
		 *
		 * @param userCount
		 * return @void
		 */
		void getRoomWithNUser(int userCount);

		/**
		 * Retrieves information of the room that contain specific 
		 * properties from the server. Result is
		 * provided in the onGetLiveRoomInfo callback of the RoomListener.
		 *
		 * @param properties
		 * @return void
		 */
		void getRoomWithProperties(std::map<std::string,std::string> properties);

		/**
		 * Terminate the SDK and frees the all allocating memory
		 *
		 * @return void
		 */
		void terminate();

		/**
		 * Updates the Warp SDK. Should be called every once in a loop if SetPollingMode was set to true
		 * By default SetPollingMode is set to true
		 *
		 * @return void
		 */
		void Update();

		/**
		 * sends a private message to user it it does not matter user is in which room.
		 * Result of the request is provided in the onSendChatDone callback of the
		 * ChatListener.
		 *
		 * @param to
		 * @param message
		 */
		void sendPrivateChat(std::string to, std::string msg);

		/**
		 * Retrieves information of the room that contain user in given range it from the server. 
		 * Result is provided in the onGetLiveRoomInfo callback of the RoomListener.
		 * 
		 * @param minUser, maxUser
		 */
		void getRoomsInRange(int min, int max);

		/*
		 * send a join room request to server with matchmaking parameters this method 
		 * allow user to choose room with user to specified range and also a flag
		 * which decide priority to room
		 * Result of the request is provided in the onJoinRoomDone callback of the RoomListener.
		 * 
		 * @ params
		 * minUser: number of minimum user in the room
		 * maxUser: number if maximum user in the room
		 * maxPreferred: define search priority
		 */
		void joinRoomInRange(int min, int max, bool maxPreferred);

		/*
		 * Lock the properties associated with the joined room on the server for requested user. 
		 * Result is provided in the onLockPropertyDone callback of the registered 
		 * RoomRequestListener objects. Lock properties will fail if any other user has lock on same
		 * property, otherwise property will be added in lockTable with owner name. This request 
		 * (if successful) will also result in an onUserChangeRoomProperty notification on the 
		 * registered NotifyListener objects to be triggered for all subscribed users of the room.
		 *
		 * @param properties
		 */
		void lockRoomProperties(std::map<std::string,std::string> properties);

		/*
		 * Unlock the properties associated with the joined room on the server for requested user. 
		 * Result is provided in the onUnlockPropertyDone callback of the registered 
		 * RoomRequestListener objects. Unlock properties will fail if any other user has lock on 
		 * same property, otherwise property will be removed from lock table. This request 
		 * (if successful) will also result in an onUserChangeRoomProperty notification on the 
		 * registered NotifyListener objects to be triggered for all subscribed users of the room.
		 *
		 * @param properties
		 */
		void unlockRoomProperties(std::vector<std::string> properties);

		/**
		 * Used Internally should not be used explicitly
		 */
		void sockonConnection(int);

		/**
		 * Used Internally should not be used explicitly
		 */
		void sockonMsg(char[], int len);
	};
}

#endif