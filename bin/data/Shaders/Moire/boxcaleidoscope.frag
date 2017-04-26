#ifdef GL_ES
precision mediump float;
#endif

#extension GL_OES_standard_derivatives : enable

#//umu

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

void main( void ) {

	vec2 uv= ( gl_FragCoord.xy / resolution.xy ) *2.0 -1.0;
	uv *=5.;
	uv.x *= resolution.x/resolution.y;
	
	
	vec2 pos = uv * 2.;
	
	int step = 0;
	bool found;
	for (int i = 0;i<32;i++){
		found = true;
		if (pos.x<0.) 
		{
			pos.x *= -1.;
			step ++;
			found = false;
		}
		if (pos.y<0.)
		{
			pos.y *= -1.;
			step ++;
			found = false;
		}
		if (pos.x + pos.y > 1.){
			pos = vec2(-pos.y+mouse.x*8., -pos.x+mouse.y*8.);
			step ++;
			found = false;
		}
		
		
	}
	
	float ma = 64.;
	vec3 col = vec3(step)/ma;
	
	gl_FragColor = vec4(col,1.);

	

}