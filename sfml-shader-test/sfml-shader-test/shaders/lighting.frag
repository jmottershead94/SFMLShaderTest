uniform sampler2D texture;

// Light Variables.
uniform vec3 lightPosition;
uniform vec3 lightColour;
uniform float alpha;

void main()
{
	vec4 pixel;
	pixel.xyz = lightColour.xyz;
	pixel.w = alpha;
	
	float distance = sqrt(pow(gl_FragCoord.x - lightPosition.x, 2.0f) + pow(gl_FragCoord.y - lightPosition.y, 2.0f));

	if (floor(lightPosition.x) == floor(gl_FragCoord.x) && floor(lightPosition.y) == floor(gl_FragCoord.y)) 
		distance = 0.1f;

	if (distance > lightPosition.z) 
		distance = lightPosition.z;

	vec2 pos = gl_TexCoord[0].xy; 
	gl_FragColor = mix(texture2D(texture, pos), pixel, 1.0f - (distance / lightPosition.z)); 
}