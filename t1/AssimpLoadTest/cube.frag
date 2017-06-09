#version 330 core 
out vec4 fColor;  



in vec2 UV;
in vec4 fragmentColor;

uniform sampler2D texture_diffuse;




void  main()  
{  

fColor = vec4(texture( texture_diffuse, UV ).rgb,1);//fragmentColor + 
}  