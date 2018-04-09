#pragma once

#include <stdio.h>
#include <stdlib.h>
#define GLEW_STATIC
#include "GL\glew.h"
#include "GLFW\\glfw3.h"

#include <iostream>
#include <fstream>

#include <string>
#include <vector>

using namespace std;

class Shader
{ public:
	GLuint getID(); //Obtener el ID del shader
	Shader(const char * rutaVertx, const char * rutaFragment);
	void enlazarShader();
	void desenlazarShader();

private:
	GLuint shaderID;
	void verificarCompilacion(GLuint in);
	void verificarVinculación(GLuint in);
};
