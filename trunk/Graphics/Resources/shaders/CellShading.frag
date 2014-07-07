varying vec4 diffuse,ambient;
varying vec3 normal,lightDir,halfVector;
uniform sampler2D tex;

void main()
{
	vec3 n,halfV;
	float NdotL,NdotHV, factor;
	/* The ambient term will always be present */

	vec4 color = ambient;
	/* a fragment shader can't write a varying variable, hence we need

	a new variable to store the normalized interpolated normal */
	n = normalize(normal);
	/* compute the dot product between normal and ldir */

	NdotL = max(dot(n,lightDir),0.0);
		
	if(NdotL > 0.95){
	
		factor = 1.0;
		
	}else if(NdotL > 0.7){
	
		factor = 0.7;
		
	}else if(NdotL > 0.3){
	
		factor = 0.3;
		
	}else{
		factor = 0.1;
	}	
	
		
	if (NdotL > 0.0) {
		color += diffuse * factor;
	}

  	vec4 texel = texture2D(tex,gl_TexCoord[0].st);

	vec3 ct,cf;
	float at, af;
	
	ct = texel.rgb;
	at = texel.a;
	
	cf = color.rgb;
	af = color.a;
  
  	vec3 fColor = cf * ct;
  	float alpha = af * at;
  	
  gl_FragColor = vec4(fColor, alpha);

	//gl_FragColor = color;

}