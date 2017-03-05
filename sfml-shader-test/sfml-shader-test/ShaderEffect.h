#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

/*
 * Used to produce shader effects in SFML.
 */
class ShaderEffect : public sf::Drawable
{
	public:
		virtual ~ShaderEffect() {};

		void load();
		void update(float time, float x, float y);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		/*
		 * Provides access to the name of this shader.
		 * @return const std::string& the name of this shader.
		 */
		inline std::string const getName() { return _name; }
		
	protected:
		explicit ShaderEffect(const std::string& name);

	private:
		std::string _name;
		bool _isLoaded;

		/*
		 * Virtual methods for inheriting classes to override.
		 */
		virtual bool onLoad() { return false; }
		virtual void onUpdate(float time, float x, float y) {};
		virtual void onDraw(sf::RenderTarget& target, sf::RenderStates states) const {}
};

