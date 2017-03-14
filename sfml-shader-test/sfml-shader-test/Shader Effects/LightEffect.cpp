#include "LightEffect.h"

/*
 * Sets up the shader effect.
 */
LightEffect::LightEffect(std::vector<sf::Sprite>& sprites, const size_t numberOfLights) : ShaderEffect("Lights!"),
	_numberOfLights(numberOfLights)
{
	_sprites = sprites;
}

/*
 * Cleans up pointers.
 */
LightEffect::~LightEffect()
{
	for (size_t i = 0; i < _lights.size(); ++i)
		delete _lights[i];
}

/*
 * Notifies us if this shader has been loaded successfully or not.
 * @return bool if this shader has loaded or not.
 */
bool LightEffect::onLoad()
{
	for (int i = 0; i < _numberOfLights; ++i)
	{
		// Calculating random positions.
		sf::Vector3f randPosition;
		randPosition.x = static_cast<float>(std::rand() % 800);
		randPosition.y = static_cast<float>(std::rand() % 600);
		randPosition.z = 1.0f;

		// Calculating random colours.
		sf::Color randColour;
		randColour.r = 255;
		randColour.g = 0;
		randColour.b = 0;
		//randColour.r = std::rand() % 255;
		//randColour.g = std::rand() % 255;
		//randColour.b = std::rand() % 255;

		Light* light = new Light(randPosition, randColour);
		light->setupBulb();
		_lights.push_back(light);
	}

	if (!_shader.loadFromFile("./shaders/lighting.frag", sf::Shader::Fragment))
		return false;
	
	_shader.setUniform("texture", sf::Shader::CurrentTexture);

	return true;
}

/*
 * Called every frame.
 * @param time the amount of time passed since the last frame update (dt).
 * @param x part of a 2D coordinate system that can be used in the shader.
 * @param y part of a 2D coordinate system that can be used in the shader.
 */
void LightEffect::onUpdate(float time, float x, float y)
{
	_shader.setUniform("time", time);

	for (size_t i = 0; i < _lights.size(); ++i)
	{
		// -----------------------------------------------------------------------------------------------------
		//	NORMAL UPDATES.
		//

		_lights[i]->setPosition(sf::Vector3f(x * 800, y * 600, 1.0f));
		_lights[i]->updateBulb();

		// -----------------------------------------------------------------------------------------------------
		//
		// SHADER UPDATES.
		//

		// Accessing light values once so there are less calls to _lights[i] with each iteration.
		const sf::Vector2f position(_lights[i]->position().x, _lights[i]->position().y);
		const sf::Vector3f colour(_lights[i]->colour().r, _lights[i]->colour().g, _lights[i]->colour().b);
		const float a = static_cast<float>(_lights[i]->colour().a);

		_shader.setUniform("light.position", position);
		_shader.setUniform("light.direction", sf::Vector2f(0.0f, 1.0f));
		_shader.setUniform("light.colour", colour);
	}

	// Render each of the sprites with this lighting shader.
	for (size_t i = 0; i < _sprites.size(); ++i)
	{
		sf::Vector3f pos(_sprites[i].getPosition().x, _sprites[i].getPosition().y, 1.0f);
		sf::Vector2f dim(_sprites[i].getGlobalBounds().width, _sprites[i].getGlobalBounds().height);

		sf::Vector2f vecMax(pos.x + (dim.x * 0.5f), pos.y + (dim.y * 0.5f));
		sf::Vector2f vecMin(pos.x - (dim.x * 0.5f), pos.y - (dim.y * 0.5f));
		_shader.setUniform("segment.vecMax", vecMax);
		_shader.setUniform("segment.vecMin", vecMin);

		//const sf::Glsl::Vec3 position(pos);
		//_shader.setUniform("position", position);

		//const sf::Glsl::Vec2 dimension(dim);
	}
}

/*
 * Called every render cycle.
 * @param target the target to draw to.
 * @param states additional information used to define how to draw the target.
 */
void LightEffect::onDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.shader = &_shader;
	
	if (_sprites.size() > 0)
	{
		// Render each of the sprites with this lighting shader.
		for (size_t i = 0; i < _sprites.size(); ++i)
		{
			target.draw(_sprites[i], states);
		}
	}

	if (_lights.size() > 0)
	{
		// Draw the light bulb sprites.
		for (size_t j = 0; j < _lights.size(); ++j)
			target.draw(_lights[j]->sprite());
	}
}