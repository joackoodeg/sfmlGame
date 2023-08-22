#include "Enemy.h"

//Funciones Privadas

void Enemy::initVariables()
{
	this->pointCount = rand() % 8 + 3;
	this->type = 0;
	this->speed = static_cast<float>(this->pointCount/4);
	this->hpMax = static_cast<int>(this->pointCount);
	this->hp = this->hpMax;
	this->points = this->pointCount;
	this->damage = this->pointCount;
}

void Enemy::initShape()
{
	//Creados con apartir de regular polygons || A futuro crear distintos tipos con distintos shapes y distintos danos.

	this->shape.setRadius(this->pointCount*5);
	this->shape.setPointCount(this->pointCount);
	this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}

//Constructor y Destructor
Enemy::Enemy(float pos_X, float pos_Y)
{
	this->initVariables();
	this->initShape();
	this->shape.setPosition(pos_X, pos_Y);
}

Enemy::~Enemy()
{
}

//Accesors
const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

//Funciones
void Enemy::update()
{
	this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
