#pragma once

#include "PixelStormEffect.h"
#include "WaveEffect.h"

/*
 * This class will manage each of the shaders we want to use.
 */
class ShaderManager
{
	public:
		explicit ShaderManager(sf::RenderWindow& window);
		~ShaderManager();
		void addEffect(ShaderEffect* effect);
		void load();
		void update(float time, float x, float y);
		void draw();
		void nextShader();
		void previousShader();

		/*
		 * Allows us to set the new index for the shader effects so we can show different shaders taking effect.
		 * @param newShader the new shader to use.
		 */
		inline void const setCurrentShader(const size_t newShader) { _currentShader = newShader; }

		/*
		 * Provides access to the data structure holding our shaders.
		 * @return const std::vector the vector of shaders.
		 */
		inline std::vector<ShaderEffect*> const effects() { return _effects; }
	
		/*
		 * Provides access to the current shader taking effect.
		 * @return const std::vector the vector of shaders.
		 */
		inline size_t& currentShader() { return _currentShader; }

		/*
		 * Provides access to the name of the current shader.
		 * @return const std::string the name of the current shader.
		 */
		inline std::string const currentShaderName() const { return _effects[_currentShader]->getName(); }

	private:
		std::vector<ShaderEffect*> _effects;
		size_t _currentShader = 0;
		sf::RenderWindow* _window = nullptr;
};