#pragma once
#include "conexionBD.h"
#include <mysql.h>
#include <iostream>
#include <string>

using namespace std;

class Puestos
{
	//atributos de la clase 
protected:
	int idPuesto = 0;
	string puesto;
public:
	//constructores
	Puestos() {}
	Puestos(int idP, string pu) { idPuesto = idP; puesto = pu; }
	//metodos
	//set
	void setidPuesto(int idP) { idPuesto = idP; }
	void setpuesto(string pu) { puesto = pu; }
	// get 
	int getidPuesto() { return idPuesto; }
	string getpuesto() { return puesto; }
	//////////////////////CREAR///////////////////////////////////////////
	void crear() {
		cout << "\n--- Crear Puestos ---\n";
		cout << "Ingrese Puesto: ";
		getline(cin, puesto);
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string insert = "INSERT INTO puestos(puesto)VALUES('" + puesto + "'); ";
			const char* i = insert.c_str();
			q_estado = mysql_query(cn.getConector(), i);
			if (!q_estado) { cout << "ingreso exitoso..." << endl; }
			else { cout << "error al ingresar..." << mysql_error(cn.getConector()) << endl; }
		}
		else { cout << "error en la conexion..." << endl; }
		cn.cerrar_conexion();
	}
	///////////////////////////////LEER/////////////////////////////////
	void leer() {
		cout << "-------------------------------------PUESTOS-------------------------------------------" << endl;
		int q_estado = 0;
		//instanciar la clase
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		if (cn.getConector()) {
			string consulta = "select * from puestos;";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConector());
				while (fila = mysql_fetch_row(resultado)) { cout << "Id Puesto:" << fila[0] << ", " << "Puesto:" << fila[1] << ", " << endl; }
			}
			else { cout << "fallo consulta" << endl; }
		}
		else { cout << "Fallo la conexion" << endl; }
		cn.cerrar_conexion();
	}
	/////////////////////ACTUALIZAR/////////////////////////
	void actualizar() {
		cout << "\n--- Actualizar Puestos ---\n";
		cout << "Ingrese ID del Puesto a actualizar: ";
		cin >> idPuesto;
		cin.ignore();
		cout << "Ingrese Puesto: ";
		getline(cin, puesto);
		int q_estado = 0;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string idP = to_string(idPuesto);
			string consulta = "update puestos set Puesto = '" + puesto + "' where idPuesto = '" + idP + "'";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) { cout << "modificacion exitosa" << endl; }
			else { cout << "modificacion fallida" << endl; }
		}
		else { cout << "fallo la conexion"; }
		cn.cerrar_conexion();
	}
	//////////////////////BORRAR/////////////////////////////
	void borrar() {
		cout << "\n--- Eliminar Puesto ---\n";
		cout << "Ingrese ID del Puesto a eliminar: ";
		cin >> idPuesto;
		cin.ignore();
		int q_estado = 0;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string idP = to_string(idPuesto);
			string consulta = "delete from puestos where idPuesto = " + idP + "";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) { cout << "eliminacion exitosa" << endl; }
			else { cout << "eliminacion fallida" << endl; }
		}
		else { cout << "fallo la conexion"; }
		cn.cerrar_conexion();
	}
	//////////////MENU///////////////////////////////////////
	void MenuPuestos() {
		int opcionPuestos;

		do {
			cout << "\n========= MENU Puestos =========\n";
			cout << "1. Crear Puesto\n";
			cout << "2. Mostrar Puestos\n";
			cout << "3. Actualizar Puestos\n";
			cout << "4. Eliminar Puestos\n";
			cout << "5. Menu Principal\n";
			cout << "6. Salir\n";
			cout << "Seleccione una opcion: ";
			cin >> opcionPuestos;
			cin.ignore();

			switch (opcionPuestos) {
			case 1:
				crear();
				break;
			case 2:
				leer();
				break;
			case 3:
				actualizar();
				break;
			case 4:
				borrar();
				break;
			case 5:
				cout << "Regresando al menu principal..." << endl;
				break;
			case 6:
				cout << "Saliendo...............";
				break;
			default:
				cout << "Opción inválida. Intente de nuevo." << endl;
			}

			system("pause");
			system("cls");
		} while (opcionPuestos != 6);
	}
};


