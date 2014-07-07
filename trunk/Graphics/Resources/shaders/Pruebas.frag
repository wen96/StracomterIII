varying vec3 normal, eyeVec;
#define MAX_LIGHTS 8
#define NUM_LIGHTS 2
varying vec3 lightDir[MAX_LIGHTS];
uniform sampler2D tex;

void main (void)
{
  vec4 final_color = gl_FrontLightModelProduct.sceneColor;
  vec3 N = normalize(normal);
  int i;
  for (i=0; i<NUM_LIGHTS; ++i)
  {
    vec3 L = normalize(lightDir[i]);
    float lambertTerm = dot(N,L);
    if (lambertTerm > 0.0)
    {
      final_color += gl_LightSource[i].diffuse * gl_FrontMaterial.diffuse * lambertTerm;
      vec3 E = normalize(eyeVec);
      vec3 R = reflect(-L, N);
      float specular = pow(max(dot(R, E), 0.0), gl_FrontMaterial.shininess);
      final_color += gl_LightSource[i].specular * gl_FrontMaterial.specular * specular;
    }
  }
  
  	vec4 texel = texture2D(tex,gl_TexCoord[0].st);

	vec3 ct,cf;
	float at, af;
	
	ct = texel.rgb;
	at = texel.a;
	
	cf = final_color.rgb;
	af = final_color.a;
  
  	vec3 color = cf * ct;
  	float alpha = af * at;
  	
  //gl_FragColor = vec4(color, alpha);
  gl_FragColor = final_color;
}
