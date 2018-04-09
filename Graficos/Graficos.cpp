// Graficos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#define GLEW_STATIC
#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "glm\gtx\transform.hpp"
#include "glm\glm.hpp"

#include <iostream>

#include "Vertice.h"
#include "Shader.h"
#include "Modelo.h"
#include "Nave.h"

#include <math.h>

using namespace std;

GLfloat red, green, blue;

GLuint posicionID;
GLuint colorID;
GLuint transformacionesID;

Nave *nave;
Modelo *cuadrado;

Shader *shader;

//Declaración de Ventana
GLFWwindow *window;

void actualizar()
{
	int estadoDerecha = glfwGetKey(window, GLFW_KEY_RIGHT);
	if (estadoDerecha == GLFW_PRESS) {
		nave->rotarNave(1);
	}

	int estadoIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);
	if (estadoIzquierda == GLFW_PRESS) {
		nave->rotarNave(0);
	}

	int estadoArriba = glfwGetKey(window, GLFW_KEY_UP);
	if (estadoArriba == GLFW_PRESS) {
		nave->moverNave();
	}

	nave->actualizarTransformaciones();

	/*int estadoArriba = glfwGetKey(window, GLFW_KEY_UP);
	if (estadoArriba == GLFW_PRESS) {
		nave->transformaciones = translate(nave->transformaciones, vec3(0.0f, 0.001f, 0.0f));
	}
	int estadoAbajo = glfwGetKey(window, GLFW_KEY_DOWN);
	if (estadoAbajo == GLFW_PRESS) {
		nave->transformaciones = translate(nave->transformaciones, vec3(0.0f, -0.001f, 0.0f));
	}
	int estadoX = glfwGetKey(window, GLFW_KEY_X);
	if (estadoX == GLFW_PRESS) {
		nave->transformaciones = scale(nave->transformaciones, vec3(1.001f, 1.001f, 1.001f));
	}
	int estadoZ = glfwGetKey(window, GLFW_KEY_Z);
	if (estadoZ == GLFW_PRESS) {
		nave->transformaciones = scale(nave->transformaciones, vec3(0.999f, 0.999f, 0.999f));
	}
	int estadoDerecha = glfwGetKey(window, GLFW_KEY_RIGHT);
	if (estadoDerecha == GLFW_PRESS) {
		nave->transformaciones = rotate(nave->transformaciones, 0.005f, vec3(0.0f, 0.0f, -1.0f));
	}
	int estadoIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);
	if (estadoIzquierda == GLFW_PRESS) {
		nave->transformaciones = rotate(nave->transformaciones, 0.005f, vec3(0.0f, 0.0f, 1.0f));
	}*/
}

void dibujar()
{
	nave->dibujar(GL_POLYGON);
	//cuadrado->dibujar(GL_POLYGON);
}

void inicializarFigura()
{
	nave = new Nave();
	Vertice v1 = { vec4(-0.1f, -0.1f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f) };
	Vertice v2 = { vec4(0.0f, 0.1f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f) };
	Vertice v3 = { vec4(0.1f, -0.1f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f) };

	nave->vertices.push_back(v1);
	nave->vertices.push_back(v2);
	nave->vertices.push_back(v3);
}

void inicializarCuadrado(){
	cuadrado = new Modelo();
	Vertice v1 = { vec4(-0.5f, 0.5f, 0.0f, 1.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f) };
	Vertice v2 = { vec4(0.5f, 0.5f, 0.0f, 1.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f) };
	Vertice v3 = { vec4(0.5f, -0.5f, 0.0f, 1.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f) };
	Vertice v4 = { vec4(-0.5f, -0.5f, 0.0f, 1.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f) };

	cuadrado->vertices.push_back(v1);
	cuadrado->vertices.push_back(v2);
	cuadrado->vertices.push_back(v3);
	cuadrado->vertices.push_back(v4);
}

int main()
{
	//Propiedades de la ventana
	GLfloat ancho = 1024;
	GLfloat alto = 768;

	//Inicialización de GLFW
	if (!glfwInit())
	{
		//Si no se inicia bien termina la ejecución
		exit(EXIT_FAILURE);
	}

	//Inicialización de la ventana
	window = glfwCreateWindow(ancho, alto, "Gráficos", NULL, NULL);

	//Verificación de creación de ventana
	if (!window)
	{
		//Cerrar todos los procesos de GLFW
		glfwTerminate();
		//Termina ejecución
		exit(EXIT_FAILURE);
	}

	//Establecer "windows" como contexto
	glfwMakeContextCurrent(window);

	//Se trae las funciones de OpenGL Moderno
	glewExperimental = true;

	//Inicializar GLEW
	GLenum glewError = glewInit();

	//Verificar si GLEW se inicializo bien
	if (glewError != GLEW_OK)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	const GLubyte *version = glGetString(GL_VERSION);
	cout << "Version de OpenGL:" << version << endl;

	inicializarFigura();
	inicializarCuadrado();

	//Crear instancia del shader
	const char * rutaVertex = "vShaderSimple.shader";
	const char * rutaFragment = "fShaderSimple.shader";

	shader = new Shader(rutaVertex, rutaFragment);

	//Mapeo de atributos
	posicionID = glGetAttribLocation(shader->getID(), "posicion");
	colorID = glGetAttribLocation(shader->getID(), "color");
	transformacionesID = glGetUniformLocation(shader->getID(), "transformaciones");

	//Desenlazar shader
	shader->desenlazarShader();

	nave->shader = shader;
	nave->inicializarVertexArray(posicionID, colorID, transformacionesID);

	cuadrado->shader = shader;
	cuadrado->inicializarVertexArray(posicionID, colorID, transformacionesID);

	//Ciclo de Dibujo
	while (!glfwWindowShouldClose(window))
	{
		//Establecer el area de render (viewport)
		glViewport(0, 0, ancho, alto);
		//Establecer el color con el que se limpia
		glClearColor(red, green, blue, 1);

		//Limpiar pantalla
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de Dibujo
		actualizar();
		dibujar();

		//Intercambio de Buffers
		glfwSwapBuffers(window);
		//Buscar nueva señal de entrada
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
    return 0;
}

