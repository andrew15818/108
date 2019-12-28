#version 430

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 k;

uniform vec3 lightPos;
uniform vec3 eyePos;
uniform mat4 Projection;
uniform mat4 ModelView;

out vec3 lightCoordinates;
out vec3 K;
out vec4 newNormal;
out vec4 modelViewPosition;
out vec4 modelViewLight;

void main() {
	vec4 modelViewPosition = ModelView * vec4(position, 1.0);
  	gl_Position = Projection * ModelView * vec4(position, 1.0);
	mat4 normalMatrix = transpose(inverse(ModelView));
	newNormal =   normalMatrix * vec4(normal, 0.0);
	

	lightCoordinates = lightPos;
	K = k;
}
