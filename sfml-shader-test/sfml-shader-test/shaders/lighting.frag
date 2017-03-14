/*
 * This shader will be responsible for providing lighting in the game.
 */

/*
 * Holds information about lights.
 */
struct Light
{
	vec2 position;
	vec2 direction;
	vec3 colour;
};

/*
 * Holds information about segments.
 * This will be filled with the maximum and minimum
 * points of the sprites these lights can interact with.
 */
struct Segment
{
	vec2 vecMax;
	vec2 vecMin;
};

// Function Prototypes.
bool rayIntersect(vec2 point, Segment area);

// Variables to setup in the .cpp files.
uniform sampler2D texture;
uniform Light light;
uniform Segment segment;
uniform float time;

/*
 * Entry point for the shader.
 */
void main()
{
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	vec4 finalColour = pixel;
	vec2 ray = light.position + (light.direction * time);
	
	if(rayIntersect(ray, segment))
	{
		finalColour += vec4(light.colour, 1.0f);
	}

	gl_FragColor = finalColour;
}

/*
 * Simple point to AABB collision check, helps to check if a ray point
 * has intersected with a target.
 * @param point the point to test against this segment.
 * @param area the segment to check if the point is inside.
 * @return bool if the point lies inside of the segment.
 */
bool rayIntersect(vec2 point, Segment area)
{
	return
	(
		(point.x >= area.vecMin.x && point.x <= area.vecMax.x) &&
		(point.y >= area.vecMin.y && point.y <= area.vecMax.y)
	);
}