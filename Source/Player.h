#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>

#include "SDL.h"
#include "SDL_image\SDL_image.h"

#include "Game.h"
#include "GameObject.h"
#include "CirclePO.h"
#include "SpriteHelper.h"

#include "IMessageReceiver.h"
#include "InputMessage.h"
#include "CollisionMessage.h"

namespace SPE
{
	class Game;

	public class Player : public GameObject, public CirclePO, public IMessageReceiver
	{
	public:
								Player(Game *_game, Messenger *_messenger);
		virtual					~Player();

		void					Active(bool _update, bool _render);
		void					Update(float deltaTime);
		void					Render();

		void					Shoot(glm::vec2 direction);

		void					Receive(Message *message);
		void					Receive(InputMessage *message);
		void					Receive(CollisionMessage *message);

	private:
		Game*					game;

		GLuint					sprites;
		float*					spriteRects;
		const unsigned int		spriteNum;
		const unsigned int		spriteSize;

		bool					flowing;
		float					flowSpeed;
		glm::vec2				flowDirection;
		const float				flowTime;
		float					flowTimer;

		float					maxVelocity;
	};
};

#endif
