#pragma once
#include "conexionBD.h"
#include "Proveedores.h"
#include "Productos.h"
#include <mysql.h>
#include <iostream>
#include <string>

using namespace std;

class Compras {
	Proveedores prov;
	Productos prod;
	//atributos
protected:
	int idCompra = 0, no_orden_compra = 0, idProveedor;
	string fecha_orden, fechaingreso;
	//constructores
public:
	Compras() {}
	Compras(int idCo, int noc, int idP, string fo, string fi) {
		idCompra = idCo;
		no_orden_compra = noc;
		idProveedor = idP;
		fecha_orden = fo;
		fechaingreso = fi;
	}
	/// metodos
	/// set
	void setidCompra(int idCo) { idCompra = idCo; }
	void setno_orden_compra(int noc) { no_orden_compra = noc; }
	void setidProveedor(int idP) { idProveedor = idP; }
	void setfecha_orden(string fo) { fecha_orden = fo; }
	void setfechaingreso(string fi) { fechaingreso = fi; }
	/// get 
	int getidCompra() { return idCompra; }
	int getno_orden_compra() { return no_orden_compra; }
	int getidProveedor() { return idProveedor; }
	string getfecha_orden() { return fecha_orden; }
	string getfechaingreso() { return fechaingreso; }
	//////////////////////CREAR///////////////////////////////////////////
	void crear() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string noc = to_string(no_orden_compra);
			string idP = to_string(idProveedor);
			string insert = "INSERT INTO compras(no_orden_compra,idProveedor,fecha_orden,fechaingreso)VALUES(" + noc + "," + idP + ",'" + fecha_orden + "',now()); ";
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
		cout << "-----------------------------Compras----------------------------" << endl;
		int q_estado = 0;
		//instanciar la clase
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		if (cn.getConector()) {
			string consulta = "select * from compras;";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConector());
				while (fila = mysql_fetch_row(resultado)) { cout << "Id Compra:" << fila[0] << ", " << "No orden compra:" << fila[1] << ", " << "idProveedor:" << fila[2] << ", " << "Fecha orden:" << fila[3] << ", " << "Fecha ingreso:" << fila[4] << ", " << endl; }
			}
			else { cout << "fallo consulta" << endl; }
		}
		else { cout << "Fallo la conexion" << endl; }
		cn.cerrar_conexion();
	}
	/////////////////////ACTUALIZAR/////////////////////////
	void actualizar() {
		int q_estado = 0;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string idCo = to_string(idCompra);
			string noc = to_string(no_orden_compra);
			string idP = to_string(idProveedor);
			string update = "UPDATE compras SET no_orden_compra = " + noc + ", idProveedor = " + idP + ", fecha_orden= '" + fecha_orden + "', fechaingreso= now() ""WHERE idCompra = " + idCo + ";";
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
		int q_estado = 0;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string idCo = to_string(idCompra);
			string consulta = "delete from compras where idVenta = " + idCo + "";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) { cout << "eliminacion exitosa" << endl; }
			else { cout << "eliminacion fallida" << endl; }
		}
		else { cout << "fallo la conexion"; }
		cn.cerrar_conexion();
	}
	//////////Compra completa//////////////////////
	void crearCompraCompleta() {
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();

		if (cn.getConector()) {
			int no_orden, idProveedor;
			string fecha_orden;


			cout << "Ingrese No. Orden de Compra: ";
			cin >> no_orden;
			prov.leerProveedor();
			cout << "Ingrese ID Proveedor: ";
			cin >> idProveedor;
			cin.ignore();


			string insertCompra = "INSERT INTO compras(no_orden_compra, idProveedor, fecha_orden, fechaingreso) "
				"VALUES(" + to_string(no_orden) + ", " + to_string(idProveedor) + ", now(), now());";

			if (mysql_query(cn.getConector(), insertCompra.c_str()) == 0) {
				int idCompraGenerado = mysql_insert_id(cn.getConector());
				cout << "Compra creada con ID: " << idCompraGenerado << endl;

				//ingresar detalles de productos
				char opcion;
				do {
					int idProducto, cantidad;
					float precio_unitario;
					prod.leerProductos();
					cout << "Ingrese ID del Producto: ";
					cin >> idProducto;
					cout << "Ingrese Cantidad: ";
					cin >> cantidad;
					cout << "Ingrese Precio Costo Unitario: ";
					cin >> precio_unitario;

					string insertDetalle = "INSERT INTO compras_detalle(idCompra, idProducto, cantidad, precio_costo_unitario) "
						"VALUES(" + to_string(idCompraGenerado) + ", " + to_string(idProducto) + ", " +
						to_string(cantidad) + ", " + to_string(precio_unitario) + ");";

					if (mysql_query(cn.getConector(), insertDetalle.c_str()) == 0) {
						cout << "Producto agregado." << endl;
					}
					else {
						cout << "Error al agregar producto: " << mysql_error(cn.getConector()) << endl;
					}

					cout << "Desea agregar otro producto? (s/n): ";
					cin >> opcion;
				} while (opcion == 's' || opcion == 'S');

			}
			else {
				cout << "Error al crear la compra: " << mysql_error(cn.getConector()) << endl;
			}

		}
		else {
			cout << "Error de conexi n a la base de datos." << endl;
		}

		cn.cerrar_conexion();
	}










};


