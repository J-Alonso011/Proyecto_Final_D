#pragma once
#include "ConexionBD.h"
#include "Persona.h"
#include <mysql.h>
#include <iostream>
#include <string>

using namespace std;
class Cliente : Persona {
	//atributos
public:
	int idCliente = 0;
	string correo_electronico, fechaingreso;

	//constructor
public:
	Cliente() {}
	Cliente(int idC, string nom, string ape, string n, bool g, string tel, string ce, string fi) : Persona(nom, ape, n, g, tel) {
		idCliente = idC;
		correo_electronico = ce;
		fechaingreso = fi;
	}
	//////metodos
	/////set
	void setIdCliente(int id) { idCliente = id; }
	void setnombres(string nom) { nombres = nom; }
	void setapellidos(string ape) { apellidos = ape; }
	void setnit(string n) { NIT = n; }
	void setgenero(bool g) { genero = g; }
	void settelefono(string tel) { telefono = tel; }
	void setcorreo_electronico(string ce) { correo_electronico = ce; }
	void setfecha(string fi) { fechaingreso = fi; }
	/////get 
	int getIdCliente() { return idCliente; }
	string getnombres() { return nombres; }
	string getapellidos() { return apellidos; }
	string getnit() { return NIT; }
	bool getgenero() { return genero; }
	string gettelefono() { return telefono; }
	string getcorreo() { return correo_electronico; }
	string getfecha() { return fechaingreso; }
	//////////////////////CREAR///////////////////////////////////////////
	void crear() {
		cout << "\n--- Crear Cliente ---\n";
		cout << "Ingrese Nombres: ";
		getline(cin, nombres);
		cout << "Ingrese Apellidos: ";
		getline(cin, apellidos);
		cout << "Ingrese Nit: ";
		getline(cin, NIT);
		cout << "Ingrese Genero (1 masculino 0 femenino): ";
		cin >> genero;
		cin.ignore();
		cout << "Ingrese Telefono: ";
		getline(cin, telefono);
		cout << "Ingrese Correo Electronico: ";
		getline(cin, correo_electronico);
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string g = to_string(genero);
			string insert = "INSERT INTO clientes(nombres,apellidos,NIT,genero,telefono,correo_electronico,fechaingreso)VALUES('" + nombres + "','" + apellidos + "','" + NIT + "'," + g + ",'" + telefono + "','" + correo_electronico + "',now()); ";
			const char* i = insert.c_str();
			q_estado = mysql_query(cn.getConector(), i);
			if (!q_estado) { cout << "ingreso exitoso..." << endl; }
			else { cout << "error al ingresar..." << mysql_error(cn.getConector()) << endl; }
		}
		else { cout << "error en la conexion..." << endl; }
		cn.cerrar_conexion();
	}
	///////////////////////////////LEER/////////////////////////////////
	void leerClientes() {
		cout << "-----------------------------CLIENTES----------------------------" << endl;
		int q_estado = 0;
		//instanciar la clase
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		if (cn.getConector()) {
			string consulta = "select * from clientes;";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConector());
				while (fila = mysql_fetch_row(resultado)) {
					cout << "Id Cliente:" << fila[0] << "\n"
						<< "Nombres:" << fila[1] << "\n"
						<< "Apellidos:" << fila[2] << "\n"
						<< "Nit:" << fila[3] << "\n"
						<< "Genero:" << fila[4] << "\n"
						<< "Telefono:" << fila[5] << "\n"
						<< "Correo Electronico:" << fila[6] << "\n"
						<< "Fecha de Ingreso:" << fila[7] << "\n"
						<< "-----------------------------CLIENTES----------------------------" << endl;
				}
			}
			else { cout << "fallo consulta" << endl; }
		}
		else { cout << "Fallo la conexion" << endl; }
		cn.cerrar_conexion();
	}
	/////////////////////ACTUALIZAR/////////////////////////
	void actualizar() {
		cout << "\n--- Actualizar Clientes ---\n";
		cout << "Ingrese ID del cliente a actualizar: ";
		cin >> idCliente;
		cin.ignore();
		cout << "Ingrese Nombres: ";
		getline(cin, nombres);
		cout << "Ingrese Apellidos: ";
		getline(cin, apellidos);
		cout << "Ingrese Nit: ";
		getline(cin, NIT);
		cout << "Ingrese Genero: ";
		cin >> genero;
		cin.ignore();
		cout << "Ingrese Telefono: ";
		getline(cin, telefono);
		cout << "Ingrese Correo Electronico: ";
		getline(cin, correo_electronico);
		int q_estado = 0;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string idC = to_string(idCliente);
			string g = to_string(genero);
			string update = "UPDATE clientes SET nombres = '" + nombres + "', apellidos = '" + apellidos + "', NIT = '" + NIT + "', genero = " + g + ", telefono = '" + telefono + "', correo_electronico = '" + correo_electronico + "', fechaingreso = now() WHERE idCliente = " + idC + ";";
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
		cout << "\n--- Borrar Clientes ---\n";
		cout << "Ingrese ID del cliente a eliminar: ";
		cin >> idCliente;
		cin.ignore();
		int q_estado = 0;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string idC = to_string(idCliente);
			string consulta = "delete from clientes where idCliente = " + idC + "";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) { cout << "eliminacion exitosa" << endl; }
			else { cout << "eliminacion fallida" << endl; }
		}
		else { cout << "fallo la conexion"; }
		cn.cerrar_conexion();
	}
	//////////////MENU///////////////////////////////////////
	void MenuClientes() {
		int opcionClientes;

		do {
			cout << "\n========= MENU CLIENTES =========\n";
			cout << "1. Crear Cliente\n";
			cout << "2. Mostrar Cliente\n";
			cout << "3. Actualizar Cliente\n";
			cout << "4. Eliminar Cliente\n";
			cout << "5. Menu Principal\n";
			cout << "6. Salir\n";
			cout << "Seleccione una opcion: ";
			cin >> opcionClientes;
			cin.ignore();

			switch (opcionClientes) {
			case 1:
				crear();
				break;
			case 2:
				leerClientes();
				break;
			case 3:
				leerClientes();
				actualizar();
				break;
			case 4:
				leerClientes();
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
		} while (opcionClientes != 5);
	}
};

