#pragma once

#include <iostream>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

using namespace std;

class Bullet
{
private:
	sf::Sprite shape;

	sf::Vector2f direction;
	float movementSpeed;

public:
	Bullet();
	Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_X, float dir_Y, float movement_Speed);//Puntero en texture con el fin de cargarlo una sola vez 
	virtual ~Bullet();

	//Accesos
	const sf::FloatRect getBounds()const;
	

	//Funciones
	void update();
	void render(sf::RenderTarget* target);
};

