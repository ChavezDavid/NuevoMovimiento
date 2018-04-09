#version 330 core
//La nprimera linea es la version

//Atributos de entrada
layout(location = 0) in vec4 posicion;
in vec4 color;
uniform mat4 transformaciones;

//Atributos de salida
out vec4 fragmentColor;

//Funcion main
void main()
{
	//La posicion de salida del vertice se guarda en el gl_Position (vec4)
	gl_Position = transformaciones * posicion;

	//Valor outColoro
	fragmentColor = color;
}