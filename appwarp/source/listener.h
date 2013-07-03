
/**
 *
 * @author Suyash Mohan (suyash.mohan@shephertz.co.in)
 */

#ifndef __APPWARP_LISTENER__
#define __APPWARP_LISTENER__

#include <vector>

namespace AppWarp
{
	class ConnectionRequestListener
	{
	public:
		/**
		 * Invoked in response to a connect request.
		 * @param result
		 */
		virtual void onConnectDone(int result) {};

		/**
		 * Invoked in response to a disconnect request.
		 * @param result
		 */
		virtual void onDisConnectDone(int result) {};
	};

	class LobbyRequestListener
	{
	public:
		/**
		 * Invoked in response to a joinLobby request.
		 * @param levent
		 */
		virtual void onJoinLobbyDone(AppWarp::lobby levent) {};

		/**
		 * Invoked in response to a leaveLobby request.
		 * @param levent
		 */
		virtual void onLeaveLobbyDone(AppWarp::lobby levent) {};

		/**
		 * Invoked in response to a subscribeLobby request.
		 * @param levent
		 */
		virtual void onSubscribeLobbyDone(AppWarp::lobby levent) {};

		/**
		 * Invoked in response to a UnSubscribeLobby request.
		 * @param levent
		 */
		virtual void onUnsubscribeLobbyDone(AppWarp::lobby levent) {};

		/**
		 * Invoked in response to a getLiveLobbyInfo request.
		 * @param levent
		 */
		virtual void onGetLiveLobbyInfoDone(AppWarp::livelobby levent) {};
	};

	class NotificationListener
	{
	public:
		/**
		 * Invoked when a room is created. Lobby subscribers will receive this.
		 * @param revent
		 */
		virtual void onRoomCreated(AppWarp::room revent) {}

		/**
		 * Invoked when a room is deleted. Lobby subscribers will receive this.
		 * @param revent
		 */
		virtual void onRoomDestroyed(AppWarp::room revent) {}

		/**
		 * Invoked when a user leaves a room. Lobby and the concerned room subscribers 
		 * will receive this.
		 * @param revent
		 * @param user
		 */
		virtual void onUserLeftRoom(AppWarp::room revent, std::string user) {}

		/**
		 * Invoked when a user joins a room. Lobby and the concerned room subscribers 
		 * will receive this.
		 * @param revent
		 * @param user
		 */
		virtual void onUserJoinedRoom(AppWarp::room revent, std::string user) {}

		/**
		 * Invoked when a user leaves a lobby. Lobby subscribers will receive this.
		 * @param levent
		 * @param user
		 */
		virtual void onUserLeftLobby(AppWarp::lobby levent, std::string user) {}

		/**
		 * Invoked when a user joins a lobby. Lobby subscribers will receive this.
		 * @param levent
		 * @param user
		 */
		virtual void onUserJoinedLobby(AppWarp::lobby levent, std::string user) {}

		/**
		 * Invoked when a joined user sends a chat. Rooms subscribers will receive this.
		 * @param chatevent
		 */
		virtual void onChatReceived(AppWarp::chat chatevent) {}

		/**
		 * Invoked when a joined user sends a updatePeers request. Rooms subscribers 
		 * will receive this.
		 * @param update
		 * @param len
		 */
		virtual void onUpdatePeersReceived(AppWarp::byte update[], int len) {}

		/**
		 * Invoked when a user change room property. Lobby and the concerned room subscribers 
		 * will receive this.
		 * @param revent
		 * @param user
		 * @param properties
		 */
		virtual void onUserChangeRoomProperty(AppWarp::room revent, std::string user,std::map<std::string, std::string> properties){}
	};

	class RoomRequestListener
	{
	public:
		/**
		 * Invoked in response to a subscribeRoom request.
		 * @param revent
		 */
		virtual void onSubscribeRoomDone(AppWarp::room revent){}

		/**
		 * Invoked in response to a UnSubscribeRoom request.
		 * @param revent
		 */
		virtual void onUnsubscribeRoomDone(AppWarp::room revent){}

		/**
		 * Invoked in response to a joinRoom request.
		 * @param revent
		 */
		virtual void onJoinRoomDone(AppWarp::room revent){}

		/**
		 * Invoked in response to a leaveRoom request.
		 * @param revent
		 */
		virtual void onLeaveRoomDone (AppWarp::room revent){}

		/**
		 * Invoked in response to a getLiveRoomInfo request.
		 * @param revent
		 */
		virtual void onGetLiveRoomInfoDone(AppWarp::liveroom revent){}

		/**
		 * Invoked in response to a setCustomRoomData request.
		 * @param revent
		 */
		virtual void onSetCustomRoomDataDone (AppWarp::liveroom revent){}

		/* 
		 * Invoked in response to add property to any room
		 * @param revent
		 */
		virtual void onUpdatePropertyDone(AppWarp::liveroom revent){}
	};

	class ZoneRequestListener
	{
	public:
		/**
		 * Invoked in response to a createRoom request.
		 * @param revent
		 */
		virtual void onCreateRoomDone (AppWarp::room revent){}

		/**
		 * Invoked in response to a deleteRoom request.
		 * @param revent
		 */
		virtual void onDeleteRoomDone (AppWarp::room revent){} 

		/**
		 * Invoked in response to a getAllRooms request.
		 * @param revent
		 */
		virtual void onGetAllRoomsDone (AppWarp::liveresult revent){}

		/**
		 * Invoked in response to a getOnlineUsers request.
		 * @param revent
		 */
		virtual void onGetOnlineUsersDone (AppWarp::liveresult revent){}

		/**
		 * Invoked in response to a getLiveUserInfo request.
		 * @param uevent
		 */
		virtual void onGetLiveUserInfoDone (AppWarp::liveuser uevent){}

		/**
		 * Invoked in response to a setCustomRoomData request.
		 * @param uevent
		 */
		virtual void onSetCustomUserInfoDone (AppWarp::liveuser uevent){}

		/**
		 * Invoked in response to a getMatchMaking Rooms request.
		 * @param mevent
		 */
		virtual void onGetMatchedRoomsDone(AppWarp::matchedroom mevent){}
	};

	class ChatRequestListener
	{
	public:
		/**
		 * Result of SendChat request. The result value maps to a WarpResponseResultCode
		 * @param result
		 */
		virtual void onSendChatDone(int result){}
	};

	class UpdateRequestListener
	{
	public:
		/**
		 * Result of SendUpdatePeers request. The result value maps to a WarpResponseResultCode
		 * @param result
		 */
		virtual void onSendUpdateDone(int result){}
	};
}

#endif