#include "ShaderManager.h"

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

	// Setup some new shader effects.
	ShaderManager shaderManager(window);
	shaderManager.addEffect(new PixelStormEffect());
	shaderManager.addEffect(new WaveEffect(sprite));

	sf::Text description("Current Effect: " + shaderManager.currentShaderName(), font, 20);
	description.setPosition(20, 555);
	description.setFillColor(sf::Color::White);

	// Load in the shader files.
	shaderManager.load();

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
						// Go to the previous shader.
						shaderManager.previousShader();
						description.setString("Current Effect: " + shaderManager.currentShaderName());

						break;
					}
					case sf::Keyboard::Right:
					{
						// Go to the next shader.
						shaderManager.nextShader();
						description.setString("Current Effect: " + shaderManager.currentShaderName());

						break;
					}
					default:
						break;
				}
			}
		}

		// Update all of the shaders.
		float x = static_cast<float>(sf::Mouse::getPosition(window).x) / window.getSize().x;
		float y = static_cast<float>(sf::Mouse::getPosition(window).y) / window.getSize().y;
		shaderManager.update(clock.getElapsedTime().asSeconds(), x, y);

		window.clear(sf::Color::Black);

		// Render the effects for the shaders.
		shaderManager.draw();

		window.draw(description);
		window.display();
	}

	return 0;
}