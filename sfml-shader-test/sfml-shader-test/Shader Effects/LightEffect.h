#pragma once

#include "ShaderEffect.h"
#include "../Lights/Light.h"

/*
 * This class should produce a lighting effect.
 * NOTE: It currently does not ( in progress - check lighting.frag ).
 */
class LightEffect : public ShaderEffect
{
	public:
		explicit LightEffect(std::vector<sf::Sprite>& sprites);
		~LightEffect();

		bool onLoad();
		void onUpdate(float time, float x, float y);
		void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		std::vector<sf::Sprite> _sprites;
		std::vector<Light*> _lights;
		sf::Shader _shader;
};

