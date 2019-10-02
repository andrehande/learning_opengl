#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

void main()
{
	gl_Position =  position;
};

#shader fragment
#version 330 core

out vec4 color;
uniform vec3 changeColor;

void main()
{
	color = vec4(0.231, 0.494, 0.890, 0.6);
};