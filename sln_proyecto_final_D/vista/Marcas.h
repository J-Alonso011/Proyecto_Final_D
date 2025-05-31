#pragma once
#include "conexionBD.h"
#include <mysql.h>
#include <iostream>
#include <string>

using namespace std;
class Marcas {
	//atributos de la clase 
protected:
	int idMarca = 0;
	string marca;
public:
	//constructores
	Marcas() {}
	Marcas(int idM, string m) { idMarca = idM; marca = m; }
	//metodos
	//set
	void setidMarca(int idM) { idMarca = idM; }
	void setmarca(string m) { marca = m; }
	// get 
	int getidMarca() { return idMarca; }
	string getmarca() { return marca; }
	//////////////////////CREAR///////////////////////////////////////////
	void crear() {
		cout << "\n--- Crear Marcas ---\n";
		cout << "Ingrese Marca: ";
		getline(cin, marca);
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string insert = "INSERT INTO marcas(marca)VALUES('" + marca + "'); ";
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
		cout << "-------------------------------------Marcas-------------------------------------------" << endl;
		int q_estado = 0;
		//instanciar la clase
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		if (cn.getConector()) {
			string consulta = "select * from marcas;";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConector());
				while (fila = mysql_fetch_row(resultado)) { cout << "Id Marca:" << fila[0] << ", " << "Marca:" << fila[1] << ", " << endl; }
			}
			else { cout << "fallo consulta" << endl; }
		}
		else { cout << "Fallo la conexion" << endl; }
		cn.cerrar_conexion();
	}
	/////////////////////ACTUALIZAR/////////////////////////
	void actualizar() {
		cout << "\n--- Actualizar Marcas ---\n";
		cout << "Ingrese ID de la Marca a actualizar: ";
		cin >> idMarca;
		cin.ignore();
		cout << "Ingrese Marca: ";
		getline(cin, marca);
		int q_estado = 0;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string idM = to_string(idMarca);
			string consulta = "update marcas set marca = '" + marca + "' where idMarca = '" + idM + "'";
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
		cout << "\n--- Eliminar Marcas ---\n";
		cout << "Ingrese ID de la marca a eliminar: ";
		cin >> idMarca;
		int q_estado = 0;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string idM = to_string(idMarca);
			string consulta = "delete from marcas where idMarca = " + idM + "";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) { cout << "eliminacion exitosa" << endl; }
			else { cout << "eliminacion fallida" << endl; }
		}
		else { cout << "fallo la conexion"; }
		cn.cerrar_conexion();
	}
	//////////////MENU///////////////////////////////////////
	void MenuMarcas() {
		int opcionMarcas;

		do {
			cout << "\n========= MENU Marcas =========\n";
			cout << "1. Crear Marca\n";
			cout << "2. Mostrar Marca\n";
			cout << "3. Actualizar Marca\n";
			cout << "4. Eliminar Marca\n";
			cout << "5. Menu Principal\n";
			cout << "6. Salir\n";
			cout << "Seleccione una opcion: ";
			cin >> opcionMarcas;
			cin.ignore();

			switch (opcionMarcas) {
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
		} while (opcionMarcas != 6);
	}
};
