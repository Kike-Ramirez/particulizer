#ifdef GL_ES
precision mediump float;
#endif

#extension GL_OES_standard_derivatives : enable

// wolframautas "rule 30", can't get them to work properly because no actual bitshift and bitwise

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform sampler2D tex;
vec4 white = vec4(1.0);
vec4 black = vec4(vec3(0.0),1.0);
vec4 color;
bool get(int x, int y){
	if( texture2D(tex,(gl_FragCoord.xy+vec2(x,y))/floor(vec2(resolution.x,resolution.y))) == black ){ return true;}
	return false;
}
bool XOR(bool a, bool b) {
    return (a && !b) || (b && !a);
}
// https://www.shadertoy.com/view/XtSSWW
int bitwise(int x, int y) {
    int outval = -1;
    ivec2 xy = ivec2(x,y);
    for (int i=0; i<8; ++i) {
        ivec2 shift = xy / 2;
        ivec2 lowestBit = xy - shift *2;
        if (XOR(lowestBit.x != 0, lowestBit.y != 0)) {
           outval += 1;
        }
        xy = shift;
    }
    return outval;
}

void main( void ) {
	//dist gl_FragCoord.xy

	ivec2 cord = ivec2(gl_FragCoord.xy);
	color=white;
	int wrap=1;
	if(mouse.x<0.1){color=white;}
	else{
	if(cord.y==int(resolution.y-1.0)){wrap = 1-int(resolution.y);}
	int r = 33+int(mouse.y*2.)*5;
	int s = get(-1,wrap)?1:0;
            s +=get( 0,wrap)?2:0;
	    s +=get( 1,wrap)?4:0;
		s = int(pow(2.0,float(s)));
		if( bitwise(r/s,1) == 1){
			color = black;
		} else { color = white;}}
	vec2 d = mouse.xy*resolution.xy-gl_FragCoord.xy;d*=d;float dist = d.x+d.y;if (dist < 10.0) {color=black;}
	gl_FragColor = color;
}