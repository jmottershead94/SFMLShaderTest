#pragma once
#include "ShaderEffect.h"

/*
 * This class should produce a stormy pixel effect.
 */
class PixelStormEffect : public ShaderEffect
{
	public:
		explicit PixelStormEffect();

		bool onLoad();
		void onUpdate(float time, float x, float y);
		void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		sf::VertexArray _points;
		sf::Shader _shader;
};