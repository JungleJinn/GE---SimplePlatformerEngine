#ifndef GAME_H
#define GAME_H

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_COLORDEPTH 32
#define PI 3.1415926535
#define DEG2RAD PI / 180
#define RAD2DEG 180 / PI

#include <list>
#include <queue>
#include <Time.h>

#include <Windows.h>
#include "GL/GL.h"
#include "GL/glut.h"

#include <glm/glm.hpp>

#include "SDL.h"
#include "SDL_opengl.h"

#include "GameObject.h"
#include "Physics.h"
#include "Log.h"

#include "Player.h"
#include "Floor.h"
#include "Dragon.h"
#include "Bomb.h"
#include "Background.h"

#include "IMessageReceiver.h"
#include "Messenger.h"
#include "Message.h"
#include "InputMessage.h"

#include "ScopedMatrix.h"

namespace SPE
{
	class Player;
	class Floor;
	class Dragon;
	class Background;
	class Bomb;

	public class Game : public IMessageReceiver
	{
	public:
		bool					aiming; // if player is loading the dragon

		glm::vec2				cameraPos;

		Game();
		~Game();
		
		void					Add(PhysicsObject *physicsObject);
		void					Remove(PhysicsObject *physicsObject);
		void					Add(GameObject *gameObject);
		void					Remove(GameObject *gameObject);

		void					SetTimeScale(float _timeScale);

		virtual void			Init();
		virtual void			Update(float deltaTime);
		virtual void			Render();

		void					UpdateGameObjects(float deltaTime);

		void					Receive(Message *message);
		void					Receive(InputMessage *message);

		void					Shoot(float direction);
		void					SpawnBomb();

		void					Reset();
		void					Quit();

	private:
		bool					quit;

		float					timeScale;
		float					deltaTime;
		float					lastUpdateTime;

		std::list<GameObject *> gameObjects;

		Log*					log;

		Messenger*				messenger;

		Physics*				physics;

		Dragon*					dragon;
		Player*					playerBomb;
		std::vector<Bomb*>*		spawnedBombs;
		float					shootSpeed;
		Floor*					floor;
		Background*				background;

		glm::vec2				spawnArea;
		float					spawnHeadStart;
		const float				spawnTime;
		float					spawnTimer;

		void					Play();
	};
};

#endif
