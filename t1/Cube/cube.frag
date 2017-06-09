#version 330 core 
out vec4 fColor;  



in vec2 UV;
in vec4 fragmentColor;

uniform sampler2D myTextureSampler;

uniform sampler2D myTextureSampler2;


void  main()  
{  

fColor = vec4(texture( myTextureSampler, UV ).rgb,1) + vec4(texture( myTextureSampler2, UV ).rgb,1);//fragmentColor + 
}  