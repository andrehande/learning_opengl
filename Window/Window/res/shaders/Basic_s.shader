#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
uniform mat4 transform;
void main()
{
	gl_Position =  transform * position;
};

#shader fragment
#version 330 core

out vec4 color;
uniform vec3 changeColor;

void main()
{
	color = vec4(changeColor, 0.6);
};