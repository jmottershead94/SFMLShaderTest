#pragma once

#include <SFML/Graphics/Glsl.hpp>
#include <SFML/Graphics/Transform.hpp>
#include "ShaderEffect.h"
#include "../Lights/Light.h"

/*
 * This class should produce a lighting effect.
 * NOTE: It currently does not ( in progress - check lighting.frag ).
 */
class LightEffect : public ShaderEffect
{
	public:
		explicit LightEffect(std::vector<sf::Sprite>& sprites, const size_t numberOfLights, sf::Font& font, sf::Text& extraText);
		~LightEffect();

		bool onLoad();
		void onUpdate(float time, float x, float y);
		void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		size_t _numberOfLights;
		std::vector<sf::Sprite> _sprites;
		Light _ambientLight;
		std::vector<Light*> _lights;
		sf::Shader _shader;
		sf::RenderWindow* _window;
		sf::Font* _font;
		sf::Text* _intensityText;

		void controls();
};

