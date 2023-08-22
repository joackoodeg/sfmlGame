#pragma once

#include <iostream>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

using namespace std;

class Downgrade
{
	unsigned pointCount;
	sf::CircleShape shape;
	
	int type;
	int points;
	int damage;

	//Funciones privadas
	void initVariables();
	void initShape();

public:
	Downgrade(float pos_X, float pos_Y);
	virtual ~Downgrade();

	//Accesors
	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;

	//Funciones 
	void update();
	void render(sf::RenderTarget* target);
};
