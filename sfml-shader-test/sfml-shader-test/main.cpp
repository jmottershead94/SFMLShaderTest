#include "PixelStormEffect.h"
#include "WaveEffect.h"
#include <vector>

/*
 * Entry point for the main application.
 */
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Shader Test", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	sf::Font font;
	if (!font.loadFromFile("../assets/art/heygorgeous.ttf"))
		return -1;

	sf::Texture texture;
	if (!texture.loadFromFile("../assets/art/button.png"))
		return -1;
	texture.setSmooth(true);

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(400, 300);

	std::vector<ShaderEffect*> effects;
	effects.push_back(new PixelStormEffect());
	effects.push_back(new WaveEffect(sprite));
	std::size_t current = 0;

	sf::Text description("Current Effect: " + effects[current]->getName(), font, 20);
	description.setPosition(20, 555);
	description.setFillColor(sf::Color::White);

	// Load the shaders in.
	for (std::size_t i = 0; i < effects.size(); ++i)
		effects[i]->load();

	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
					case sf::Keyboard::Escape:
					{
						window.close();
						break;
					}
					case sf::Keyboard::Left:
					{
						if (current == 0)
							current = effects.size() - 1;
						else
							current--;

						description.setString("Current Effect: " + effects[current]->getName());

						break;
					}
					case sf::Keyboard::Right:
					{
						if (current == effects.size() - 1)
							current = 0;
						else
							current++;

						description.setString("Current Effect: " + effects[current]->getName());

						break;
					}
					default:
						break;
				}
			}
		}

		// Update the current example
		float x = static_cast<float>(sf::Mouse::getPosition(window).x) / window.getSize().x;
		float y = static_cast<float>(sf::Mouse::getPosition(window).y) / window.getSize().y;
		effects[current]->update(clock.getElapsedTime().asSeconds(), x, y);

		window.clear(sf::Color::Black);
		window.draw(*effects[current]);
		window.draw(description);
		window.display();
	}

	for (std::size_t i = 0; i < effects.size(); ++i)
		delete effects[i];

	return 0;
}