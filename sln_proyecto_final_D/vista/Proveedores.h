#pragma once
#include "conexionBD.h"
#include <mysql.h>
#include <iostream>
#include <string>

using namespace std;
class Proveedores {
	//atributos
protected:
	int idProveedor = 0;
	string proveedor, nit, direccion, telefono;
	//constructores
public:
	Proveedores() {}
	Proveedores(int idPr, string p, string n, string dir, string tel) {
		idProveedor = idPr;
		proveedor = p;
		nit = n;
		direccion = dir;
		telefono = tel;
	}
	// metodos
	// set
	void setidProveedor(int idPr) { idProveedor = idPr; }
	void setproveedor(string p) { proveedor = p; }
	void setnit(string n) { nit = n; }
	void setdireccion(string dir) { direccion = dir; }
	void settelefono(string tel) { telefono = tel; }
	// get 
	int getidProveedor() { return idProveedor; }
	string getproveedor() { return proveedor; }
	string getnit() { return nit; }
	string getdireccion() { return direccion; }
	string gettelefono() { return telefono; }
	//////////////////////CREAR///////////////////////////////////////////
	void crear() {
		cout << "\n--- Crear Proveedores ---\n";
		cout << "Ingrese Proveedor: ";
		getline(cin, proveedor);
		cout << "Ingrese Nit: ";
		getline(cin, nit);
		cout << "Ingrese Direccion: ";
		getline(cin, direccion);
		cout << "Ingrese Telefono: ";
		getline(cin, telefono);
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string insert = "INSERT INTO proveedores(proveedor,nit,direccion,telefono)VALUES('" + proveedor + "','" + nit + "','" + direccion + "','" + telefono + "'); ";
			const char* i = insert.c_str();
			q_estado = mysql_query(cn.getConector(), i);
			if (!q_estado) { cout << "ingreso exitoso..." << endl; }
			else { cout << "error al ingresar..." << mysql_error(cn.getConector()) << endl; }
		}
		else { cout << "error en la conexion..." << endl; }
		cn.cerrar_conexion();
	}
	///////////////////////////////LEER/////////////////////////////////
	void leerProveedor() {
		cout << "-----------------------------PROVEEDORES----------------------------" << endl;
		int q_estado = 0;
		//instanciar la clase
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		if (cn.getConector()) {
			string consulta = "select * from proveedores;";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConector());
				while (fila = mysql_fetch_row(resultado)) {
					cout << "Id Proveedor:" << fila[0] << "\n"
						<< "Proveedor:" << fila[1] << "\n"
						<< "Nit:" << fila[2] << "\n"
						<< "Direccion:" << fila[3] << "\n"
						<< "Telefono:" << fila[4] << "\n"
						<< "-----------------------------PROVEEDORES----------------------------" << endl;
				}
			}
			else { cout << "fallo consulta" << endl; }
		}
		else { cout << "Fallo la conexion" << endl; }
		cn.cerrar_conexion();
	}
	/////////////////////ACTUALIZAR/////////////////////////
	void actualizar() {
		cout << "\n--- Actualizar Proveedores ---\n";
		cout << "Ingrese ID del Proveedor a actualizar: ";
		cin >> idProveedor;
		cin.ignore();
		cout << "Ingrese Proveedor: ";
		getline(cin, proveedor);
		cout << "Ingrese Nit: ";
		getline(cin, nit);
		cout << "Ingrese Direccion: ";
		getline(cin, direccion);
		cout << "Ingrese Telefono: ";
		getline(cin, telefono);
		int q_estado = 0;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string idPr = to_string(idProveedor);
			string update = "UPDATE proveedores SET Proveedor = '" + proveedor + "', Nit = '" + nit + "', Direccion = '" + direccion + "', Telefono= '" + telefono + "' ""WHERE idProveedor = " + idPr + ";";
			const char* u = update.c_str();
			q_estado = mysql_query(cn.getConector(), u);
			if (!q_estado) { cout << "modificacion exitosa" << endl; }
			else { cout << "modificacion fallida" << endl; }
		}
		else { cout << "fallo la conexion"; }
		cn.cerrar_conexion();
	}
	//////////////////////BORRAR/////////////////////////////
	void borrar() {
		cout << "\n--- Eliminar Proveedor ---\n";
		cout << "Ingrese ID del Proveedor a eliminar: ";
		cin >> idProveedor;
		cin.ignore();
		int q_estado = 0;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string idPr = to_string(idProveedor);
			string consulta = "delete from proveedores where idProveedor = " + idPr + "";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) { cout << "eliminacion exitosa" << endl; }
			else { cout << "eliminacion fallida" << endl; }
		}
		else { cout << "fallo la conexion"; }
		cn.cerrar_conexion();
	}
	//////////////MENU///////////////////////////////////////
	void MenuProveedores() {
		int opcionProveedores;

		do {
			cout << "\n========= MENU PROVEEDORES =========\n";
			cout << "1. Crear Provedor\n";
			cout << "2. Mostrar Provedor\n";
			cout << "3. Actualizar Provedor\n";
			cout << "4. Eliminar Provedor\n";
			cout << "5. Menu Principal\n";
			cout << "6. Salir\n";
			cout << "Seleccione una opcion: ";
			cin >> opcionProveedores;
			cin.ignore();

			switch (opcionProveedores) {
			case 1:
				crear();
				break;
			case 2:
				leerProveedor();
				break;
			case 3:
				leerProveedor();
				actualizar();
				break;
			case 4:
				leerProveedor();
				borrar();
				break;
			case 5:
				cout << "Regresando al menu principal..." << endl;
				return;
				break;
			default:
				cout << "Opci n inv lida. Intente de nuevo." << endl;
			}

			system("pause");
			system("cls");
		} while (opcionProveedores != 5);
	}
};


