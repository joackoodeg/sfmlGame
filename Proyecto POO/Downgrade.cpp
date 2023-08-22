#include "Downgrade.h"

void Downgrade::initVariables()
{
	this->pointCount = rand() % 8 + 3;
	this->type = 0;

	this->points = 3;
	this->damage = 1;
}

void Downgrade::initShape()
{
	this->shape.setRadius(this->pointCount * 5);

	this->shape.setFillColor(sf::Color(150, 50, 250));

	// set a 10-pixel wide orange outline
	this -> shape.setOutlineThickness(10);
	this -> shape.setOutlineColor(sf::Color(250, 150, 100));
}


//Constructor y Destructor
Downgrade::Downgrade(float pos_X, float pos_Y)
{
	this->initVariables();
	this->initShape();
	this->shape.setPosition(pos_X, pos_Y);
}

Downgrade::~Downgrade()
{
}

//Accesors
const sf::FloatRect Downgrade::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Downgrade::getPoints() const
{
	return this->points;
}

const int& Downgrade::getDamage() const
{
	return this->damage;
}

//Funciones
void Downgrade::update()
{
	
}

void Downgrade::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
