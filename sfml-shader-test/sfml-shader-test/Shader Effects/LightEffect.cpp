#include "LightEffect.h"

/*
 * Sets up the shader effect.
 */
LightEffect::LightEffect(std::vector<sf::Sprite>& sprites) : ShaderEffect("Lights!")
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
	for (int i = 0; i < 1; ++i)
	{
		// Calculating random positions.
		sf::Vector3f randPosition;
		randPosition.x = static_cast<float>(std::rand() % 800);
		randPosition.y = static_cast<float>(std::rand() % 600);
		randPosition.z = 1.0f;

		// Calculating random colours.
		sf::Color randColour;
		randColour.r = std::rand() % 255;
		randColour.g = std::rand() % 255;
		randColour.b = std::rand() % 255;

		Light* light = new Light(randPosition, randColour);
		light->setupBulb();
		_lights.push_back(light);
	}

	if (!_shader.loadFromFile("./shaders/lighting.frag", sf::Shader::Type::Fragment))
		return false;

	sf::Vector3f colour(_lights[0]->colour().r, _lights[0]->colour().g, _lights[0]->colour().b);
	float a = static_cast<float>(_lights[0]->colour().a);

	_shader.setUniform("texture", sf::Shader::CurrentTexture);
	_shader.setUniform("lightColour", colour);
	_shader.setUniform("alpha", a);

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
	for (size_t i = 0; i < _lights.size(); ++i)
	{
		_lights[i]->setPosition(sf::Vector3f(x * 800, y * 600, 1.0f));
		_lights[i]->updateBulb();
	}

	_shader.setUniform("lightPosition", _lights[0]->position());
}

/*
 * Called every render cycle.
 * @param target the target to draw.
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
			//_shader.setUniform("texture", _sprites[i].getTexture());
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