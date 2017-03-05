#include "ShaderEffect.h"

/*
 * Sets up the shader effect.
 * @param const std::string& the name of this shader.
 */
ShaderEffect::ShaderEffect(const std::string& name) :
	_name(name),
	_isLoaded(false)
{}

/*
 * Used to set the loading status of this shader effect.
 */
void ShaderEffect::load()
{
	_isLoaded = sf::Shader::isAvailable() && onLoad();
}

/*
 * Called every frame.
 * @param time the amount of time passed since the last frame update (dt).
 * @param x part of a 2D coordinate system that can be used in the shader.
 * @param y part of a 2D coordinate system that can be used in the shader.
 */
void ShaderEffect::update(float time, float x, float y)
{
	if (_isLoaded)
		onUpdate(time, x, y);
}

/*
 * Called every render cycle.
 * @param target the target to draw.
 * @param states additional information used to define how to draw the target.
 */
void ShaderEffect::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (_isLoaded)
		onDraw(target, states);
	//else
	//	std::cout << "Shader not supported" << std::endl;
}