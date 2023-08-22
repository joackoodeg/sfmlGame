#pragma once

#include <iostream>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

using namespace std;

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	
	float movementSpeed;
	float attackCooldown;
	float attackCooldownMax;

	int hp;
	int hpMax;
	
	//Funciones privdadas;
	void initVariables();
	void initTexture();
	void initSprite();

public:
	Player();
	virtual~Player();

	//Accesos
	const sf::Vector2f& getPos()const;
	const sf::FloatRect getBounds()const;
	const int& getHp() const;
	const int& getHpMax() const;

	//Modificadores
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	void setHp(const int hp);
	void loseHp(const int value);

	//Funciones
	void move(const float dirX, const float dirY);
	const bool canAttack();

	void updateAttack();
	void update();

	void render(sf::RenderTarget& target);
};

