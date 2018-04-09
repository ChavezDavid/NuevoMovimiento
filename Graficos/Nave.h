#pragma once
#include "Modelo.h"

#include "glm\gtx\transform.hpp"
#include "glm\glm.hpp"

class Nave : public Modelo {
public:
	Nave();
	float angulo;
	vec3 coordenadas;
	float velocidadAngular = 1.0f;
	float velocidad = 0.01f;
	void rotarNave(int direccion);
	void moverNave();
	void actualizarTransformaciones();
};