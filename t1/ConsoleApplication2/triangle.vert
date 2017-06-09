in vec4 vPosition;  

uniform vec4 InnerColor;

uniform mat4 MVP;

out vec4 ColorTmep;
void  main()
{  
	ColorTmep = InnerColor;
     gl_Position = MVP * vPosition;  
}