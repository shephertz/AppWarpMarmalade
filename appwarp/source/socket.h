

#ifndef __APPWARP_SOCKET__
#define __APPWARP_SOCKET__

#include "s3eSocket.h"

namespace AppWarp
{
	namespace Utility
	{
		class Socket
		{
			s3eSocket *socket;
			static bool m_connected;
		public:
			Socket();
			~Socket();
			int sockConnect(std::string, int );
			int sockDisconnect();
			static int32 sockConnectCB(s3eSocket *,void *,void *);
			virtual void sockonConnection(int) = 0;
			virtual void sockonMsg(char[], int len ) = 0;
			int sockSend(char *,int);
			static void *sockRecieve(void *);
			static void *sockUpdate(void *);
		};

	}
}

#endif