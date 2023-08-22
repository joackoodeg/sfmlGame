#pragma once

#include<map>
#include<string>
#include<sstream>
#include<vector>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Downgrade.h"

class Game
{
private:
	//Ventana
	sf::RenderWindow* window; //Ventaja de que sea puntero: Crear/destruir ventana facilmente, crear nueva, cambiar a fullscreen ,etc

	//Recursos
	map<string,sf::Texture*>textures;
	vector<Bullet*> bullets;

	//Jugador
	Player* player;

	//Interfaz Jugador
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//Enemigos
	float spawnTimer;
	float spawnTimerMax;
	vector<Enemy*> enemies;

	//Downgrades
	float spawnTimerD;
	float spawnTimerDMax;
	vector<Downgrade*> downgrades;

	//Interfaz
	sf::Font font;
	sf::Text pointText;

	sf::Text gameOverText;

	//Mundo - Background
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

	//Sistema
	unsigned points;

	//Funciones privadas
	void initWindow();
	void initTextures();
	void initGui();
	void initWorld();
	void initSystems();

	void initPlayer();
	void initEnemies();
	void initDowngrades();

public:
	//Constructor y Destructor
	Game();
	virtual ~Game();

	//Funciones
	void run();

	void updatePollEvents();
	void updateInput();
	void updateGui();
	void updateWorld();
	void updateCollision();
	void updateBullets();
	void updateEnemies();
	void updateDowngrades();
	void updateCombat();
	void update();
	
	void render();
	void renderGui();
	void renderWorld();
};

