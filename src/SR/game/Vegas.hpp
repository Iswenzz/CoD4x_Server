#pragma once
#include "net/TCP.hpp"
#include "player/Player.hpp"

C_EXTERN
{
	#include <cvar.h>
}

namespace Iswenzz::CoD4x
{
	/// @brief TCP link betweeen Vegas and the server.
	class Vegas : public TCP
	{
	public:
		inline static cvar_t* IsEnabled;

		hudelem_color_t Color = { 0 };
		int Material = 0;

		/// @brief Initialize a new Vegas TCP link.
		Vegas();
		~Vegas() = default;

		/// @brief User connection.
		/// @param from - The address.
		/// @param msg - The message.
		/// @return qboolean
		qboolean Connect(netadr_t *from, msg_t *msg) override;

		/// @brief Disconnect user.
		/// @param from - The address.
		void Disconnect(netadr_t *from) override;

		/// @brief Received message.
		/// @param from - The address.
		/// @param msg - The message.
		/// @return int
		int Message(netadr_t *from, msg_t *msg) override;

		/// @brief Render vegas to the player.
		/// @param player
		void Frame(Player *player);
	};

	C_EXTERN
	{
		qboolean OnConnect(netadr_t *from, msg_t *msg, int *connectionId);
		void OnDisconnect(netadr_t *from, int connectionId);
		int OnMessage(netadr_t *from, msg_t *msg, int connectionId);
	}
}
