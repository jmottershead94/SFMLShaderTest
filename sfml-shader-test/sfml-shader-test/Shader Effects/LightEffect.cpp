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
		randColour.g = 25;
		randColour.b = 128;
		//randColour.r = std::rand() % 255;
		//randColour.g = std::rand() % 255;
		//randColour.b = std::rand() % 255;

		Light* light = new Light(randPosition, randColour, 0.75f);
		light->setDynamic(true);
		light->setRadius(20.0f);
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

		_shader.setUniform("light.position", position);
		_shader.setUniform("light.colour", colour);
		_shader.setUniform("light.intensity", _lights[i]->intensity());
		_shader.setUniform("light.radius", _lights[i]->radius());
		_shader.setUniform("light.angleSpread", _lights[i]->angleSpread());
		_shader.setUniform("light.angle", _lights[i]->angle());
		_shader.setUniform("light.dynamic", _lights[i]->isDynamic());
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