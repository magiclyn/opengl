#version 330 core 

out vec2 UV;
out vec4 fragmentColor;

layout(location = 0) in vec4 vPosition;
//layout(location = 1) in vec4 incolor;
layout(location = 1) in vec2 vertexUV;

uniform mat4 MVP;

void  main()
{  
	fragmentColor = vec4(1,0,0,1);
	UV = vertexUV;
    gl_Position = MVP * vPosition;  //
}