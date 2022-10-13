#include "Vegas.hpp"
#include "SR.hpp"

namespace Iswenzz::CoD4x
{
	Vegas::Vegas() : TCP(200)
	{
		NET_TCPAddEventType(OnMessage, OnConnect, OnDisconnect, ServiceID);
	}

	qboolean Vegas::Connect(netadr_t *from, msg_t *msg)
	{
		Log::WriteLine("connected");

		return qtrue;
	}

	void Vegas::Disconnect(netadr_t *from)
	{
		Log::WriteLine("disconnected");
	}

	int Vegas::Message(netadr_t *from, msg_t *msg)
	{
		Log::WriteLine("message");

		MSG_BeginReading(msg);

		char id[30];
		char name[30];

		MSG_ReadString(msg, reinterpret_cast<char*>(&id), sizeof(id));
		MSG_ReadString(msg, reinterpret_cast<char*>(&name), sizeof(name));

		char r = 0;
		char g = 0;
		char b = 0;
		char a = 0;

		if (MSG_ReadByte(msg))
		{
			r = MSG_ReadByte(msg);
			g = MSG_ReadByte(msg);
			b = MSG_ReadByte(msg);
			a = MSG_ReadByte(msg);
		}

		Color.split = { r, g, b, a };
		Material = SV_FindMaterial(name);
		return 0;
	}
}

C_EXTERN
{
	qboolean OnConnect(netadr_t *from, msg_t *msg, int *connectionId)
	{
		return SR->Vegas->Connect(from, msg);
	}

	void OnDisconnect(netadr_t *from, int connectionId)
	{
		SR->Vegas->Disconnect(from);
	}

	int OnMessage(netadr_t *from, msg_t *msg, int connectionId)
	{
		return SR->Vegas->Message(from, msg);
	}
}
