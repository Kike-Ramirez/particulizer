#ifdef GL_ES
precision mediump float;
#endif

#extension GL_OES_standard_derivatives : enable

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;


float rand(vec2 pos){return fract(sin(dot(pos,vec2(9.837811484,200.6181231174))));}


void main( void ) {

	vec2 position = ( gl_FragCoord.xy / resolution.xy ) + mouse / 4.0;

	float color = 0.0;
	color += rand(position*10.0);
	gl_FragColor = vec4(color);

}