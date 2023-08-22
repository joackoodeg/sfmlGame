#include "Game.h"

//Funciones privadas
void Game::initWindow()
{
	this->window = new::sf::RenderWindow(sf::VideoMode(800, 600), "Game name", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("../Textures/laserBullet.png");
}

void Game::initGui()
{
	//Cargar Fuente
	if (!this->font.loadFromFile("Fonts/Retro.ttf")) 
	{
		cout << "FAILED TO LOAD FONT" << endl;
	}
	
	//Cargar texto
	this->pointText.setPosition(650.f, 20.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(20);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("test");

	//Game Over 
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game Over");
	this->gameOverText.setPosition(this->window->getSize().x/2.f - this->gameOverText.getGlobalBounds().width/2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);


	//Player GUI
	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));

}

void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("../Textures/backgroundEdit.jpg")) 
	{
		cout << "FAILED TO LOAD WORLD" << endl;
	}
	this->worldBackground.setTexture(this->worldBackgroundTex);
	this->worldBackground.setScale(0.3f, 0.3f);
}

void Game::initSystems()
{
	this->points = 0;
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initEnemies()
{
	//IDEA: A medida de que el jugador aumenta los puntos podria disminuir el spawnTimerMax
	this->spawnTimerMax = 100.f;
	this->spawnTimer = this->spawnTimerMax;
}

void Game::initDowngrades()
{
	//IDEA: A medida de que el jugador aumenta los puntos podria aumentar los downgrade
	this->spawnTimerDMax = 10000.f;
	this->spawnTimerD = this->spawnTimerMax;
}

//Constructor y Destructor
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initGui();
	this->initWorld();
	this->initSystems();
	this->initPlayer();
	this->initEnemies();
	this->initDowngrades();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	//Borrar texturas
	for (auto& texture : this->textures) 
	{
		delete texture.second;
	}

	//Borrar balas
	for (auto* i : this->bullets) 
	{
		delete i;
	}

	//Borrar enemigos
	for (auto* i : this->enemies)
	{
		delete i;
	}

	//Borrar downgrades
	for (auto* i : this->downgrades)
	{
		delete i;
	}
}

//Funciones
void Game::run()
{
	while (this->window->isOpen()) 
	{
		this->updatePollEvents();
		
		if (player->getHp() > 0)
		{
			this->update();
			this->render();
		}
	}
}

void Game::updatePollEvents()
{
	sf::Event ev;
	while (this->window->pollEvent(ev))
	{
		if (ev.Event::type == sf::Event::Closed or ev.Event::key.code == sf::Keyboard::Escape)
		{
			this->window->close();
		}
	}

}

void Game::updateInput()
{
	//Movimiento del jugador\
	//Izquierda
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->player->move(-1.f, 0.f);
	}
	//Derecha
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->player->move(1.f, 0.f);
	}
	//Arriba
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->player->move(0.f, -1.f);
	}
	//Abajo
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->player->move(0.f, 1.f);
	}

	//Crear la bala
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->player->canAttack())
	{
		this->bullets.push_back(new Bullet(this->textures["BULLET"],this->player->getPos().x + (this->player->getBounds().height)/2.f, this->player->getPos().y, 0.f, -1.f, 5.f));
	}
}

void Game::updateGui()
{
	stringstream ss;
	ss <<"Points: "<< this->points;
	this->pointText.setString(ss.str());

	//Update Player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent,this->playerHpBar.getSize().y));

}

void Game::updateWorld()
{

}

void Game::updateCollision()
{
	//Colision Izquierda 
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}

	//Colision Derecha
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x) 
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}

	//Colision Arriba
	if (this->player->getBounds().top < 0.f) 
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}

	//Colsion Abajo
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}

	
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets) {
		bullet->update();

		//Si la bala sobrepasa la ventana
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//Borrar la bala
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			//--counter;
		}
		++counter;
	}
}

void Game::updateEnemies()
{
	//Spawning
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax) 
	{
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x, -100.f));
		this->spawnTimer = 0.f;
	}

	//Update
	
	unsigned counter = 0;
	for (auto* enemy : this->enemies) {
		enemy->update();

		//Si el enemigo sobrepasa la ventana // old: (enemy->getBounds().top + enemy->getBounds().height > this->window->getSize().x)
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			//Borrar el enemigo || Primero se lo borra y luego se lo quita del vector (porque es dinamico), de esta forma se evitan problemas con la memoria
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			//--counter;
		}

		//Colision jugador con enemigos
		else if (enemy->getBounds().intersects(this->player->getBounds())) 
		{
			this->player->loseHp(this->enemies.at(counter)->getDamage());
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			//--counter;
		}

		++counter;
	}
}

void Game::updateDowngrades()
{
	//Spawning
	this->spawnTimerD += 0.005f;
	if (this->spawnTimerD >= this->spawnTimerMax)
	{
		this->downgrades.push_back(new Downgrade(rand() % this->window->getSize().x, rand() % this->window->getSize().y));
		this->spawnTimerD = 0.f;
	}

	//Update
	unsigned counter = 0;
	for (auto* downgrade : this->downgrades) {
		downgrade->update();

		//Colision jugador con downgrades
		 if (downgrade->getBounds().intersects(this->player->getBounds()))
		{
			 if (this->points > 10) {this->points -= (this->downgrades.at(counter)->getPoints()); }
			this->player->loseHp(this->downgrades.at(counter)->getDamage());
			delete this->downgrades.at(counter);
			this->downgrades.erase(this->downgrades.begin() + counter);
			//--counter;
		}

		++counter;
	}
}

void Game::updateCombat()
{
	/*  OLD VERSION 
	for (size_t i = 0; i < this->enemies.size(); ++i) {
		bool enemy_removed = false;
		this->enemies[i]->update();


		for (size_t k = 0; k < this->bullets.size() && !enemy_removed; ++k) {
			if (this->bullets[k]->getBounds().intersects(this->enemies[i]->getBounds()))
			{
				this->bullets.erase(this->bullets.begin() + k);
				this->enemies.erase(this->enemies.begin() + i);
				enemy_removed = true;
			}
		}

		if (!enemy_removed)
		{
			//Borrar los enemigos por debajo de la ventana

			if (this->enemies[i]->getBounds().top > this->window->getSize().y)
			{
				this->enemies.erase(enemies.begin() + i);
				enemy_removed = true;
			}
		}

	}
	*/
	
	for (size_t i = 0; i < enemies.size(); ++i) //Primer loop para el vector que tenga menos elementos
	{
		bool enemy_deleted = false; //Evitar que siga checkeando las balas si es que ya existio una colision previa, porque esto provocaria que busque la interseccion de un enemigo ya elimminado con la siguiente bala a checkear

		for (size_t k = 0; k < bullets.size() && !enemy_deleted; k++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds())) 
			{
				this->points += this->enemies[i]->getPoints();
				
				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				enemy_deleted = true; 
			}
		}
	}

}

void Game::update()
{
	this->updateInput();
	this->player->update();
	this->updateCollision();
	this->updateBullets();
	this->updateEnemies();
	this->updateCombat();
	this->updateGui();
	this->updateWorld();

	this->updateDowngrades();
}

void Game::render()
{
	//Borrar frame anterior
	this->window->clear();

	//Renderizar mundo
	this->renderWorld();

	//Crear frame actual
	this->player->render(*this->window);//Dado que la ventana es un puntero es necesario desreferenciarla

	for (auto *bullet : this->bullets) {
		bullet->render(this->window);
	}

	for (auto *enemy : this->enemies) {
		enemy->render(this->window);
	}

	for (auto* downgrade : this->downgrades) {
		downgrade->render(this->window);
	}

	this->renderGui();
	
	//Game Over
	if (this->player->getHp() <= 0) 
	{
		this->window->draw(this->gameOverText);
	}

	//Mostrar frame actual
	this->window->display();
}

void Game::renderGui()
{
	this->window->draw(this->pointText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}
