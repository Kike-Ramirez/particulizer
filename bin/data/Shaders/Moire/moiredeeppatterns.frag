#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform vec2 surfacePostion;

float dot2(vec2 p) { return dot(p,p); }

void main( void ) {
	
	vec2 pos = (( gl_FragCoord.xy / resolution.xy ) - vec2(0.5,0.5));	
	
	float t = time * .1;
	float st = sin(t);
	float ct = cos(t);
	
	mat2 m2 = mat2(ct,-st,st,ct);
	
	pos *= m2;
	
	pos.y = -abs(pos.y);
	
	pos *= dot2(pos)*15000.0;
	
	
        float horizon = abs(pos.x); 
        float fov = 0.5;
	float scaling = 2.81;
	
	vec3 p = vec3(pos.x, fov, pos.y - horizon);   
	
	vec2 s = vec2(p.x/p.z, p.y/p.z) * scaling;
	
	s *= 4.0 * (resolution.x/max(resolution.x,resolution.y));
	
	//checkboard texture
	float color = sign((mod(s.x, 0.1) - 0.05) * (mod(s.y-fract(t*3.1), 0.1) - 0.05));	
	//fading
	color *= p.z*p.z*25.0;
	
	float m = dot2(fract(surfacePostion-0.5));
	
	gl_FragColor = vec4( vec3(color)*m, 1.0 );

}