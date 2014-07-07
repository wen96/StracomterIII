varying vec4 diffuse,ambient;
varying vec3 normal,lightDir,halfVector;

void main()
{
	gl_TexCoord[0] = gl_MultiTexCoord0;

	/* first transform the normal into eye space and
	normalize the result */
	normal = normalize(gl_NormalMatrix * gl_Normal);

	lightDir = normalize(vec3(gl_LightSource[2].position));
	/* Normalize the halfVector to pass it to the fragment shader */

	halfVector = normalize(gl_LightSource[2].halfVector.xyz);
	/* Compute the diffuse, ambient and globalAmbient terms */

	diffuse = gl_FrontMaterial.diffuse * gl_LightSource[2].diffuse;
	ambient = gl_FrontMaterial.ambient * gl_LightSource[2].ambient;
	ambient += gl_LightModel.ambient * gl_FrontMaterial.ambient;
	gl_Position = ftransform();

}