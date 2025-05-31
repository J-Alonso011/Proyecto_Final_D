#pragma once
#include<iostream>
using namespace std;
class Persona {
	// atributos de la clase
public: string nombres, apellidos, NIT, telefono;
	  bool genero;
	  // metodo constructor "tiene el mismo nombre de la clase"
public:
	Persona() {
	}
	Persona(string nom, string ape, string n, bool g, string tel) {
		nombres = nom;
		apellidos = ape;
		NIT = n;
		genero = g;
		telefono = tel;
	}
};

