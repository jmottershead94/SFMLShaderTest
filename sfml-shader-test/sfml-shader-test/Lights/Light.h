#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

/*
 * This class will hold and give information about lights.
 */
class Light
{
	public:
		/*
		 * Sets up the light with default values.
		 */
		explicit Light() :
			_position(sf::Vector3f(0.0f, 0.0f, 1.0f)),
			_colour(sf::Color::White),
			_intensity(1.0f),
			_radius(0.0f),
			_angleSpread(0.0f),
			_angle(0.0f),
			_dynamic(true)
		{}

		/*
		 * Sets up the light with variable values.
		 */
		explicit Light(const sf::Vector3f newPosition, const sf::Color newColour, const float intensity = 1.0f) :
			_position(newPosition),
			_colour(newColour),
			_intensity(intensity),
			_radius(0.0f),
			_angleSpread(0.0f),
			_angle(0.0f),
			_dynamic(true)
		{}

		virtual ~Light() {}

		/*
		 * Sets up the circle shape following the light.
		 */
		void setupBulb()
		{
			_point.setFillColor(sf::Color::Yellow);
			_point.setPosition(_position.x, _position.y);
			_point.setRadius(_radius * 0.5f);
		}

		/*
		 * Updates the position of the bulb to the light.
		 */
		void updateBulb()
		{
			_point.setPosition(_position.x - (_radius * 0.5f), _position.y - (_radius * 0.5f));
		}

		/*
		 * Allows us to set the position of the light.
		 * @param value the new position.
		 */
		inline void const setPosition(const sf::Vector3f value) { _position = value; };

		/*
		 * Allows us to set the colour of the light.
		 * @param value the new colour.
		 */
		inline void const setColour(const sf::Color value)		{ _colour = value; };

		/*
		 * Allows us to set the intensity of the light.
		 * @param value the new intensity value.
		 */
		inline void const setIntensity(const float value)		{ _intensity = value; };

		/*
		 * Allows us to set the radius of the light.
		 * @param value the new radius value.
		 */
		inline void const setRadius(const float value)			{ _radius = value; };

		/*
		 * Allows us to set the angle that the light will shine.
		 * @param value the angle that this light will shine to.
		 */
		inline void const setAngleSpread(const float value)		{ _angleSpread = value; };

		/*
		 * Allows us to set the angle of the light.
		 * @param value the new angle of the light.
		 */
		inline void const setAngle(const float value)			{ _angle = value; };

		/*
		 * Allows us to set the dynamic flag of the light.
		 * @param value if this light is dynamic (can be changed) or static (cannot be changed).
		 */
		inline void const setDynamic(const bool value)			{ _dynamic = value; };

		/*
		 * Provides access to the position of the light.
		 * @return sf::Vector3f& the current light position.
		 */
		inline sf::Vector3f& position()			{ return _position; }

		/*
		 * Provides access to the colour of the light.
		 * @return sf::Color& the current light colour.
		 */
		inline sf::Color& colour()				{ return _colour; }
		
		/*
		 * Provides access to the bulb of the light.
		 * @return sf::CircleShape& the current light bulb.
		 */
		inline sf::CircleShape& sprite()		{ return _point; }
		
		/*
		 * Provides access to the intensity of the light.
		 * @return const float the current light intensity.
		 */
		inline float const intensity()			{ return _intensity; }

		/*
		 * Provides access to the radius of the light.
		 * @return const float the current light radius.
		 */
		inline float const radius()				{ return _radius; }
		
		/*
		 * Provides access to the angle spread of the light (i.e. light cone).
		 * @return const float the current light angle spread.
		 */
		inline float const angleSpread()		{ return _angleSpread; }
		
		/*
		 * Provides access to the angle of the light.
		 * @return const float the current light angle.
		 */
		inline float const angle()				{ return _angle; }
		
		/*
		 * Provides access to the dynamic state of the light.
		 * @return const bool if the light is dynamic (can be changed) or static (cannot be changed).
		 */
		inline bool const isDynamic()			{ return _dynamic; }

	private:
		sf::Vector3f _position;
		sf::Color _colour;
		sf::CircleShape _point;
		float _intensity;
		float _radius;
		float _angleSpread;
		float _angle;
		bool _dynamic;
};