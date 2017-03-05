#include "PixelStormEffect.h"

/*
 * Sets up the shader effect.
 */
PixelStormEffect::PixelStormEffect() : ShaderEffect("Stormy!")
{}

/*
 * Notifies us if this shader has been loaded successfully or not.
 * @return bool if this shader has loaded or not.
 */
bool PixelStormEffect::onLoad()
{
	_points.setPrimitiveType(sf::Points);
	for (int i = 0; i < 40000; ++i)
	{
		float x = static_cast<float>(std::rand() % 800);
		float y = static_cast<float>(std::rand() % 600);
		sf::Uint8 r = std::rand() % 255;
		sf::Uint8 g = std::rand() % 255;
		sf::Uint8 b = std::rand() % 255;
		_points.append(sf::Vertex(sf::Vector2f(x, y), sf::Color(r, g, b)));
	}

	if (!_shader.loadFromFile("./shaders/storm.vert", "./shaders/blink.frag"))
		return false;

	return true;
}

/*
 * Called every frame.
 * @param time the amount of time passed since the last frame update (dt).
 * @param x part of a 2D coordinate system that can be used in the shader.
 * @param y part of a 2D coordinate system that can be used in the shader.
 */
void PixelStormEffect::onUpdate(float time, float x, float y)
{
	float radius = 200 + std::cos(time) * 150;
	_shader.setUniform("storm_position", sf::Vector2f(x * 800.0f, y * 600.0f));
	_shader.setUniform("storm_inner_radius", radius / 3.0f);
	_shader.setUniform("storm_total_radius", radius);
	_shader.setUniform("blink_alpha", 0.5f + std::cos(time * 3.0f) * 0.25f);
}

/*
 * Called every render cycle.
 * @param target the target to draw.
 * @param states additional information used to define how to draw the target.
 */
void PixelStormEffect::onDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.shader = &_shader;
	target.draw(_points, states);
}