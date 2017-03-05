#include "WaveEffect.h"

/*
 * Sets up the shader effect.
 * @param sprite the sprite that we want to affect with this shader.
 */
WaveEffect::WaveEffect(sf::Sprite& sprite) : ShaderEffect("Wavey")
{
	_target = &sprite;
}

/*
 * Notifies us if this shader has been loaded successfully or not.
 * @return bool if this shader has loaded or not.
 */
bool WaveEffect::onLoad()
{
	if (!_shader.loadFromFile("./shaders/wave.vert", sf::Shader::Vertex))
		return false;

	return true;
}

/*
 * Called every frame.
 * @param time the amount of time passed since the last frame update (dt).
 * @param x part of a 2D coordinate system that can be used in the shader.
 * @param y part of a 2D coordinate system that can be used in the shader.
 */
void WaveEffect::onUpdate(float time, float x, float y)
{
	_shader.setUniform("wave_phase", time);
	_shader.setUniform("wave_amplitude", sf::Vector2f(x * 40.0f, y * 40.0f));
}

/*
 * Called every render cycle.
 * @param target the target to draw.
 * @param states additional information used to define how to draw the target.
 */
void WaveEffect::onDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.shader = &_shader;
	target.draw(*_target, states);
}