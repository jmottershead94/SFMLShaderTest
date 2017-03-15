/*
 * This shader will be responsible for providing lighting in the game.
 */

/*
 * Defines here for our lighting.
 */
#define NUMBER_OF_LIGHTS 1
#define PI 3.1415

/*
 * Holds information about the ambient lighting in the scene.
 */
struct AmbientLight
{
	vec4 colour;
	float intensity;
};

/*
 * Holds information about lights.
 */
struct Light
{
	vec2 position;
	vec3 colour;
	float intensity;
	float radius;
	float angleSpread;
	float angle;
	bool dynamic;
};

// Function Prototypes.
float calculateDistance(vec2 pointOne, vec2 pointTwo);
vec4 shineLight(Light currentLight);

// Variables to setup in the .cpp files.
uniform sampler2D texture;
uniform Light light;
uniform float time;

/*
 * Entry point for the shader.
 */
void main()
{
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	vec4 finalColour = pixel;
	
	AmbientLight ambLight;
	ambLight.colour = vec4(0.0f, 0.0f, 0.0f, 0.25f);
	ambLight.intensity = 0.5f;

	finalColour += ambLight.colour;
	finalColour += shineLight(light);
	finalColour.w *= (light.intensity * ambLight.intensity);

	gl_FragColor = finalColour;
}

float calculateDistance(vec2 pointOne, vec2 pointTwo)
{
	float result = 0.0f;
	float x = (pointTwo.x - pointOne.x) * (pointTwo.x - pointOne.x);
	float y = (pointTwo.y - pointOne.y) * (pointTwo.y - pointOne.y);
	result = sqrt(x + y);

	return result;
}

vec4 shineLight(Light currentLight)
{	
	float dis = calculateDistance(currentLight.position, gl_FragCoord.xy);

	if(currentLight.radius >= dis)										// This pixel is out of range.
		return vec4(currentLight.colour, currentLight.intensity);
	else if(currentLight.radius < dis)									// Otherwise, the pixel is in range of the light.
		return vec4(0.0f, 0.0f, 0.0f, 0.0f);
}