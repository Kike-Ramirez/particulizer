#ifdef GL_ES
precision mediump float;
#endif

#extension GL_OES_standard_derivatives : enable

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

void main( void ) {

	vec2 position = ( gl_FragCoord.xy / resolution.xy ) + mouse / 4.0;

	float color = 0.0;
	color += sin( position.x * cos( time / 15.0 ) * 800.0 ) + cos( position.y * cos( time / 500.0 ) * 10.0 );
	color += sin( position.y * sin( time / 10.0 ) * 400.0 ) + cos( position.x * sin( time / 500.0 ) * 40.0 );
	color += sin( position.x * sin( time / 5.0 ) * 100.0 ) + sin( position.y * sin( time / 500.0 ) * 80.0 );
	color *= sin( time / 10.0 ) * 0.5;

	gl_FragColor = vec4( vec3( color, color * 0.5, sin( color + time / 3.0 ) * 0.75 ), 10.0 );

}