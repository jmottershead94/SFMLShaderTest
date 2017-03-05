#pragma once

#include "ShaderEffect.h"

/*
 * This class should produce a wavey effect.
 */
class WaveEffect : public ShaderEffect
{
	public:
		explicit WaveEffect(sf::Sprite& sprite);

		bool onLoad();
		void onUpdate(float time, float x, float y);
		void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		sf::Sprite* _target;
		sf::Shader _shader;
};

