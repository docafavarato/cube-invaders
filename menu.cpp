#include "menu.h"
#include "Game.h"
#include <iostream>

Menu::Menu() {
	font.loadFromFile("metropolian-1.ttf");

	text[0].setFont(font);
	text[0].setFillColor(sf::Color::White);
	text[0].setString("Easy");
	text[0].setPosition(sf::Vector2f(600 / 2, 600 / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	text[1].setFont(font);
	text[1].setFillColor(sf::Color::White);
	text[1].setString("Medium");
	text[1].setPosition(sf::Vector2f(600 / 2, 600 / (MAX_NUMBER_OF_ITEMS + 1) + 60));

	text[2].setFont(font);
	text[2].setFillColor(sf::Color::White);
	text[2].setString("Hard");
	text[2].setPosition(sf::Vector2f(600 / 2, 600 / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	text[3].setFont(font);
	text[3].setFillColor(sf::Color::Red);
	text[3].setString("Exit");
	text[3].setPosition(sf::Vector2f(600 / 2, 600 / (MAX_NUMBER_OF_ITEMS) * 2));

	selectedItemIndex = 0;

	this->initVariables();
	this->initWindow();
}

void Menu::MoveUp() {
	if (selectedItemIndex - 1 >= 0) {
		text[selectedItemIndex].setFillColor(sf::Color::Red);
		selectedItemIndex--;
		text[selectedItemIndex].setFillColor(sf::Color::White);
	}
}

void Menu::MoveDown() {
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
		text[selectedItemIndex].setFillColor(sf::Color::Red);
		selectedItemIndex++;
		text[selectedItemIndex].setFillColor(sf::Color::White);
	}
}

///////////////////////////////////////////

void Menu::initVariables() {
	this->window = nullptr;
}

void Menu::initWindow() {
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Menu", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);

}

/* void Menu::initFont() {
	sf::Font font;
	sf::Text pointsText;
	sf::Text difficultyText;
	sf::Text lifesText;

	font.loadFromFile("metropolian-1.ttf");

	difficultyText.setFont(font);
	difficultyText.setFillColor(sf::Color::White);
	difficultyText.setCharacterSize(20);
	difficultyText.setString("Difficulty: Easy");
	difficultyText.setPosition(600.f, 10.f);

	lifesText.setFont(font);
	lifesText.setFillColor(sf::Color::White);
	lifesText.setCharacterSize(20);
	lifesText.setString("Lifes: " + std::to_string(this->lifes));
	lifesText.setPosition(600.f, 40.f);

	pointsText.setFont(font);
	pointsText.setFillColor(sf::Color::White);
	pointsText.setCharacterSize(40);
	pointsText.setString("Points: " + std::to_string(this->points));
	pointsText.setPosition(10.f, 10.f);

	this->window->draw(pointsText);
	this->window->draw(difficultyText);
	this->window->draw(lifesText);
}*/

void Menu::pollEvents() {
	while (this->window->pollEvent(this->ev)) {
		if (this->ev.type == sf::Event::Closed) {
			this->window->close();
		}

		if (this->ev.type == sf::Event::KeyReleased) {
			if (ev.key.code == sf::Keyboard::Up) {
				this->MoveUp();
			}
			if (ev.key.code == sf::Keyboard::Down) {
				this->MoveDown();
			}
			if (ev.key.code == sf::Keyboard::Enter) {
				Game game;
				if (this->getPressedItem() == 0) {
					while (game.running()) {
						game.update();
						game.render();
					}
				}

				if (this->getPressedItem() == 1) {
					game.lifes = 2;
					game.enemySpawnTimer = 20.f;
					game.maxEnemies = 7;
					while (game.running()) {
						game.update();
						game.render();
					}
				}

				if (this->getPressedItem() == 2) {
					game.lifes = 1;
					game.enemySpawnTimer = 10.f;
					game.maxEnemies = 10;
					while (game.running()) {
						game.update();
						game.render();
					}
				}

				if (this->getPressedItem() == 3) {
					window->close();
				}
			}

		}
	}
}

void Menu::renderMenu() {
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		this->window->draw(text[i]);
	}

	instructions.setFont(font);
	instructions.setPosition(230, 500);
	instructions.setString("Press enter to select");
	this->window->draw(instructions);
}

void Menu::update() {
	this->pollEvents();
}

void Menu::render() {
	this->window->clear();
	this->renderMenu();
	this->window->display();
}

Menu::~Menu() {
	delete this->window;
}

const bool Menu::running() const {
	return this->window->isOpen();
}