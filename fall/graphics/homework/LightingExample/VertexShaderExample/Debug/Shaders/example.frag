#version 430
out vec4 frag_color;

in vec3 lightCoordinates;
in vec3 K;
in vec4 newNormal;
in vec4 modelViewPosition;
in vec4 modelViewLight;
void main() {
	color3 Ia = vec3(0.2, 0.2, 0.2);
	color3 Id = vec3(0.5, 0.5, 0.5);
	color3 Is = vec3(0.8, 0.8, 0.8);
	color3 I = Ia + Id + Is;
	double alpha = 3.6;
    	frag_color = vec4(0.24, 0.23, 0.23, 0.0);
	vec4 ambient = vec4(1,1,1,0);
	
}
