#include "Player.h"
void Player::initVariables()
{
	this->movementSpeed = 5.f;

	this->attackCooldownMax = 20.f;
	this->attackCooldown = this->attackCooldownMax;

	this->hpMax = 100;
	this->hp = this->hpMax;
}
void Player::initTexture()
{
	//Cargar textura de un archivo
	if (!this->texture.loadFromFile("C:/Proyecto POO/Textures/ship.png")) 
	{
		cout << "ERROR::PLAYER::InitTexture:: No se pudo cargar el archivo" << endl;
	}
}
void Player::initSprite()
{
	//Setear la textura al sprite
	this->sprite.setTexture(this->texture);

	//Reescalar el sprite
	this->sprite.scale(0.05f, 0.05f);

}

//Constructor y Destructor
Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{
}

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

void Player::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::setHp(const int hp)
{
	this->hp = hp;
}

void Player::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0) 
	{
		this->hp = 0;
	}
}

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed*dirX, this->movementSpeed*dirY);
}

const bool Player::canAttack()
{
	//Una vez que attackCoolDown llegue a superar o igualar a attackCoolDownMax, siendo esto a traves de la funcion updateAttack, se permitira al jugador atacar.

	if (this->attackCooldown >= this->attackCooldownMax) 
	{
		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}


//Funciones

void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax) 
	{
		this->attackCooldown+=0.5f;
	}
} 

void Player::update()
{
	this->updateAttack();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

}
