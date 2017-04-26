#ifdef GL_ES
precision mediump float;
#endif

#extension GL_OES_standard_derivatives : enable

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

void main( void ) {

    vec2 position = ( gl_FragCoord.xy / resolution.xy ) - mouse;

    float c = length(position);
    vec3 color = vec3(c);

    color -= abs(sin(position.y * 100.0 + time * 5.0)) * 0.08; // (1)
    color -= abs(sin(position.y * 300.0 - time * 10.0)) * 0.05; // (2)

    gl_FragColor = vec4( vec3(1.-color), 1.0 );

}