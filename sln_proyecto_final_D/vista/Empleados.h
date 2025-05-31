#pragma once
#include "ConexionBD.h"
#include "Persona.h"
#include <mysql.h>
#include <iostream>
#include <string>

using namespace std;
class Empleados : public Persona {
	//atributos
private:
	int idEmpleado = 0, idPuesto = 0;
	string direccion, DPI, fecha_nacimiento, fecha_inicio_labores, fecha_ingreso;

	//constructor
public:
	Empleados() {}
	Empleados(int idE, string nom, string ape, string dir, string tel, string dpi, bool g, string fn, int idP, string fil, string fi, string n) : Persona(nom, ape, n, g, tel) {
		idEmpleado = idE;
		direccion = dir;
		DPI = dpi;
		fecha_nacimiento = fn;
		idPuesto = idP;
		fecha_inicio_labores = fil;
		fecha_ingreso = fi;
	}
	//////metodos
	/////set
	void setidEmpleado(int idE) { idEmpleado = idE; }
	void setnombres(string nom) { nombres = nom; }
	void setapellidos(string ape) { apellidos = ape; }
	void setdireccion(string dir) { direccion = dir; }
	void settelefono(string tel) { telefono = tel; }
	void setDPI(string dpi) { DPI = dpi; }
	void setgenero(bool g) { genero = g; }
	void setfecha_nacimiento(string fn) { fecha_nacimiento = fn; }
	void setidPuesto(int idP) { idPuesto = idP; }
	void setfecha_inicio_labores(string fil) { fecha_inicio_labores = fil; }
	void setfecha_ingreso(string fi) { fecha_ingreso = fi; }
	/////get 
	int getidEmpleado() { return idEmpleado; }
	string getnombres() { return nombres; }
	string getapellidos() { return apellidos; }
	string getdireccion() { return direccion; }
	string gettelefono() { return telefono; }
	string getDPI() { return DPI; }
	bool getgenero() { return genero; }
	string getfecha_nacimiento() { return fecha_nacimiento; }
	int getidPuesto() { return idPuesto; }
	string getfecha_inicio_labores() { return fecha_inicio_labores; }
	string getfecha_ingreso() { return fecha_ingreso; }
	//////////////////////CREAR///////////////////////////////////////////
	void crear() {
		cout << "\n--- Crear Empleado ---\n";
		cout << "Ingrese Nombres: ";
		getline(cin, nombres);
		cout << "Ingrese Apellidos: ";
		getline(cin, apellidos);
		cout << "Ingrese Direccion: ";
		getline(cin, direccion);
		cout << "Ingrese Telefono: ";
		getline(cin, telefono);
		cout << "Ingrese DPI: ";
		getline(cin, DPI);
		cout << "Ingrese Genero: ";
		cin >> genero;
		cin.ignore();
		cout << "Ingrese Fecha Nacimiento (YYYY-MM-DD): ";
		getline(cin, fecha_nacimiento);
		cout << "Ingrese idPuesto: ";
		cin >> idPuesto;
		cin.ignore();
		cout << "Ingrese fecha de Inicio Labores (YYYY-MM-DD): ";
		getline(cin, fecha_inicio_labores);
		cout << "Ingrese fecha de ingreso (YYYY-MM-DD): ";
		getline(cin, fecha_ingreso);
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string g = to_string(genero);
			string idP = to_string(idPuesto);
			string insert = "INSERT INTO empleados(nombres,apellidos,direccion,telefono,DPI,genero,fecha_nacimiento,idPuesto,fecha_inicio_labores,fechaingreso)VALUES('" + nombres + "','" + apellidos + "','" + direccion + "','" + telefono + "','" + DPI + "'," + g + ",'" + fecha_nacimiento + "'," + idP + ",'" + fecha_inicio_labores + "',now()); ";
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
		cout << "-----------------------------EMPLEADOS----------------------------" << endl;
		int q_estado = 0;
		//instanciar la clase
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		if (cn.getConector()) {
			string consulta = "select * from empleados;";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConector());
				while (fila = mysql_fetch_row(resultado)) { cout << "Id Empleado:" << fila[0] << ", " << "Nombres:" << fila[1] << ", " << "Apellidos:" << fila[2] << ", " << "Direccion:" << fila[3] << ", " << "Telefono:" << fila[4] << ", " << "DPI:" << fila[5] << ", " << "Genero:" << fila[6] << ", " << "Fecha_nacimiento:" << fila[7] << ", " << "Id Puesto:" << fila[8] << ", " << "Fecha_Inicio_Labores:" << fila[9] << ", " << "Fecha de Ingreso:" << fila[10] << ", " << endl; }
			}
			else { cout << "fallo consulta" << endl; }
		}
		else { cout << "Fallo la conexion" << endl; }
		cn.cerrar_conexion();
	}
	/////////////////////ACTUALIZAR/////////////////////////
	void actualizar() {
		cout << "\n--- Actualizar Empleados ---\n";
		cout << "Ingrese ID del Empleado a actualizar: ";
		cin >> idEmpleado;
		cin.ignore();
		cout << "Ingrese Nombres: ";
		getline(cin, nombres);
		cout << "Ingrese Apellidos: ";
		getline(cin, apellidos);
		cout << "Ingrese Direccion: ";
		getline(cin, direccion);
		cout << "Ingrese Telefono: ";
		getline(cin, telefono);
		cout << "Ingrese DPI: ";
		getline(cin, DPI);
		cout << "Ingrese Genero: ";
		cin >> genero;
		cin.ignore();
		cout << "Ingrese Fecha Nacimiento (YYYY-MM-DD): ";
		getline(cin, fecha_nacimiento);
		cout << "Ingrese idPuesto: ";
		cin >> idPuesto;
		cin.ignore();
		cout << "Ingrese fecha de Inicio Labores (YYYY-MM-DD): ";
		getline(cin, fecha_inicio_labores);
		cout << "Ingrese fecha de ingreso (YYYY-MM-DD): ";
		getline(cin, fecha_ingreso);
		int q_estado = 0;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string idE = to_string(idEmpleado);
			string g = to_string(genero);
			string idP = to_string(idPuesto);
			string update = "UPDATE empleados SET nombres = '" + nombres + "', apellidos = '" + apellidos + "', direccion = '" + direccion + "', telefono = '" + telefono + "',DPI ='" + DPI + "',genero =" + g + ",fecha_nacimiento='" + fecha_nacimiento + "',idPuesto=" + idP + ",fecha_inicio_labores='" + fecha_inicio_labores + "',fechaingreso='" + fecha_ingreso + "'  ""WHERE idEmpleado = " + idE + ";";
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
		cout << "\n--- Borrar Empleados ---\n";
		cout << "Ingrese ID del Empleado a eliminar: ";
		cin >> idEmpleado;
		cin.ignore();
		int q_estado = 0;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string idE = to_string(idEmpleado);
			string consulta = "delete from empleados where idEmpleado = " + idE + "";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) { cout << "eliminacion exitosa" << endl; }
			else { cout << "eliminacion fallida" << endl; }
		}
		else { cout << "fallo la conexion"; }
		cn.cerrar_conexion();
	}
	//////////////MENU///////////////////////////////////////
	void MenuEmpleados() {
		int opcionEmpleados;

		do {
			cout << "\n========= MENU EMPLEADOS =========\n";
			cout << "1. Crear Empleado\n";
			cout << "2. Mostrar Empleado\n";
			cout << "3. Actualizar Empleado\n";
			cout << "4. Eliminar Empleado\n";
			cout << "5. Menu Principal\n";
			cout << "6. Salir\n";
			cout << "Seleccione una opcion: ";
			cin >> opcionEmpleados;
			cin.ignore();

			switch (opcionEmpleados) {
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
		} while (opcionEmpleados != 6);
	}





};
