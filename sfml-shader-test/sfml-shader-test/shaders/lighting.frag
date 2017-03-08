uniform sampler2D texture;

// Light Variables.
uniform vec3 lightPosition[2];
uniform vec3 lightColour[2];
uniform float alpha[2];

// Light Affected Object.
uniform float width;
uniform float height;
//uniform vec2 dimension;

///*
// * This will allow us to determine the distance between two points.
// * @param pointOne the first point to check distance against pointTwo.
// * @param pointTwo the second point to check distance against pointOne.
// * @return float the distance between these two points (i.e. the hypotenuse).
// */
//float distance(vec2 pointOne, vec2 pointTwo)
//{
//	float result = 0.0f;
//	float x = (pointTwo.x - pointOne.x) * (pointTwo.x - pointOne.x);
//	float y = (pointTwo.y - pointOne.y) * (pointTwo.y - pointOne.y);
//
//	result = sqrt(x + y);
//
//	return result;
//}
//
//vec2 getCentre()
//{
//	
//}

void main()
{
	int numberOfLights = 2;
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	vec4 currentLight = pixel;

	for(int i = 0; i < numberOfLights; ++i)
	{		
		float distance = sqrt(pow(gl_FragCoord.x - lightPosition[i].x, 2.0f) + pow(gl_FragCoord.y - lightPosition[i].y, 2.0f));

		if (floor(lightPosition[i].x) == floor(gl_FragCoord.x) && floor(lightPosition[i].y) == floor(gl_FragCoord.y)) 
			distance = 0.1f;

		if (distance > lightPosition[i].z) 
			distance = lightPosition[i].z;

		vec2 pos = gl_TexCoord[0].xy; 
		//currentLight = mix(texture2D(texture, pos), pixel, 1.0f - (distance / lightPosition[i].z)); 
	}
	
	gl_FragColor = currentLight;
}