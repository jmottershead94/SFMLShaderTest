#include "ShaderManager.h"

/*
 * Sets up the shader manager.
 * @param window the current render window used for the application.
 */
ShaderManager::ShaderManager(sf::RenderWindow& window) :
	_currentShader(0),
	_window(&window)
{}

/*
 * Cleans up pointers from the shader manager.
 */
ShaderManager::~ShaderManager()
{
	for (size_t i = 0; i < _effects.size(); ++i)
		delete _effects[i];
}

/*
 * Adds a new shader effect to the shader manager.
 * @param effect the new shader effect to add to the vector of effects.
 */
void ShaderManager::addEffect(ShaderEffect* effect)
{
	_effects.push_back(effect);
}

/*
 * Loads all of the shaders.
 */
void ShaderManager::load()
{
	for (size_t i = 0; i < _effects.size(); ++i)
		_effects[i]->load();
}

/*
 * Called every frame.
 * @param time the amount of time passed since the last frame update (dt).
 * @param x part of a 2D coordinate system that can be used in the shader.
 * @param y part of a 2D coordinate system that can be used in the shader.
 */
void ShaderManager::update(float time, float x, float y)
{
	_effects[_currentShader]->update(time, x, y);
}

/*
 * Called every render cycle.
 */
void ShaderManager::draw()
{
	_window->draw(*_effects[_currentShader]);
}

/*
 * Increments to the next shader in the effects vector.
 */
void ShaderManager::nextShader()
{
	if (_currentShader == _effects.size() - 1)
		_currentShader = 0;
	else
		_currentShader++;
}

/*
 * Decrements to the previous shader in the effects vector.
 */
void ShaderManager::previousShader()
{
	if (_currentShader == 0)
		_currentShader = _effects.size() - 1;
	else
		_currentShader--;
}