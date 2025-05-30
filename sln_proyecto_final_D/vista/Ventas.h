#pragma once
#include "conexionBD.h"
#include <mysql.h>
#include <iostream>
#include <string>

using namespace std;
class Ventas {
	//atributos
protected:
	int idVenta = 0, nofactura = 0, idCliente, idEmpleado;
	string serie, fechafactura, fechaingreso;
	//constructores
public:
	Ventas() {}
	Ventas(int idV, int nof, string s, string fcf, int idC, int idE, string fi) {
		idVenta = idV;
		nofactura = nof;
		serie = s;
		fechafactura = fcf;
		idCliente = idC;
		idEmpleado = idE;
		fechaingreso = fi;
	}
	/// metodos
	/// set
	void setidVenta(int idV) { idVenta = idV; }
	void setnofactura(int nof) { nofactura = nof; }
	void setserie(string s) { serie = s; }
	void setfechafactura(string fcf) { fechafactura = fcf; }
	void setidCliente(int idC) { idCliente = idC; }
	void setidEmpleado(int idE) { idEmpleado = idE; }
	void setfechaingreso(string fi) { fechaingreso = fi; }
	/// get 
	int getidVenta() { return idVenta; }
	int getnofactura() { return nofactura; }
	string getserie() { return serie; }
	string getfechafactura() { return fechafactura; }
	int getidCliente() { return idCliente; }
	int getidEmpleado() { return  idEmpleado; }
	string getfechaingreso() { return fechaingreso; }
	//////////////////////CREAR///////////////////////////////////////////
	void crear() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string nof = to_string(nofactura);
			string idC = to_string(idCliente);
			string idE = to_string(idEmpleado);
			string insert = "INSERT INTO ventas(nofactura,serie,fechafactura,idCliente,idEmpleado,fechaingreso)VALUES(" + nof + ",'" + serie + "','" + fechafactura + "'," + idC + "," + idE + ",now()); ";
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
		cout << "-----------------------------Ventas----------------------------" << endl;
		int q_estado = 0;
		//instanciar la clase
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		if (cn.getConector()) {
			string consulta = "select * from ventas;";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConector());
				while (fila = mysql_fetch_row(resultado)) { cout << "Id Venta:" << fila[0] << ", " << "No factura:" << fila[1] << ", " << "serie:" << fila[2] << ", " << "Fecha Factura:" << fila[3] << ", " << "Id Cliente:" << fila[4] << ", " << "Id Empleado:" << fila[5] << ", " << "Fecha Ingreso:" << fila[6] << ", " << endl; }
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
			string idV = to_string(idVenta);
			string nof = to_string(nofactura);
			string idC = to_string(idCliente);
			string idE = to_string(idEmpleado);
			string update = "UPDATE ventas SET nofactura = " + nof + ", serie = '" + serie + "', fechafactura= '" + fechafactura + "', idCliente= " + idC + ",idEmpleado= " + idE + " ""WHERE idVenta = " + idV + ";";
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
			string idV = to_string(idVenta);
			string consulta = "delete from ventas where idVenta = " + idV + "";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) { cout << "eliminacion exitosa" << endl; }
			else { cout << "eliminacion fallida" << endl; }
		}
		else { cout << "fallo la conexion"; }
		cn.cerrar_conexion();
	}
	/////////////////////venta completa/////////////////////////////
	void crearVentaCompleta() {
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();

		if (cn.getConector()) {
			// Paso 1: ingresar datos de la cabecera
			cout << "Ingrese No. Factura: ";
			cin >> nofactura;
			cin.ignore();
			cout << "Ingrese Serie: ";
			getline(cin, serie);
			cout << "Ingrese Fecha Factura (YYYY-MM-DD): ";
			getline(cin, fechafactura);
			cout << "Ingrese ID Cliente: ";
			cin >> idCliente;
			cout << "Ingrese ID Empleado: ";
			cin >> idEmpleado;

			// Insertar venta
			string insertVenta = "INSERT INTO ventas(nofactura, serie, fechafactura, idCliente, idEmpleado, fechaingreso) "
				"VALUES(" + to_string(nofactura) + ", '" + serie + "', '" + fechafactura + "', " +
				to_string(idCliente) + ", " + to_string(idEmpleado) + ", now());";
			if (mysql_query(cn.getConector(), insertVenta.c_str()) == 0) {
				int idVentaGenerado = mysql_insert_id(cn.getConector());
				cout << "Venta creada con ID: " << idVentaGenerado << endl;

				// Paso 2: ingresar productos
				char opcion;
				do {
					int idProducto, cantidad;
					float precio_unitario;

					cout << "Ingrese ID del Producto: ";
					cin >> idProducto;
					cout << "Ingrese Cantidad: ";
					cin >> cantidad;
					cout << "Ingrese Precio Unitario: ";
					cin >> precio_unitario;

					string insertDetalle = "INSERT INTO ventas_detalle(idVenta, idProducto, cantidad, precio_unitario) "
						"VALUES(" + to_string(idVentaGenerado) + ", " + to_string(idProducto) + ", " +
						to_string(cantidad) + ", " + to_string(precio_unitario) + ");";
					if (mysql_query(cn.getConector(), insertDetalle.c_str()) == 0) {
						cout << "Producto agregado." << endl;
					}
					else {
						cout << "Error al agregar producto: " << mysql_error(cn.getConector()) << endl;
					}

					cout << " Desea agregar otro producto? (s/n): ";
					cin >> opcion;
				} while (opcion == 's' || opcion == 'S');

			}
			else {
				cout << "Error al crear la venta: " << mysql_error(cn.getConector()) << endl;
			}

		}
		else {
			cout << "Error de conexi n a la base de datos." << endl;
		}

		cn.cerrar_conexion();
	}
	///////////////////Factura///////////////////////////////
	void imprimirFactura() {
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		int q_estado;

		cn.abrir_conexion();
		if (cn.getConector()) {

			// Obtener datos de la cabecera
			string queryCabecera =
				"SELECT v.nofactura, v.fechafactura, c.nit, c.nombres "
				"FROM ventas v "
				"LEFT JOIN clientes c ON v.idCliente = c.idCliente "
				"WHERE v.idVenta = " + to_string(idVenta) + ";";

			q_estado = mysql_query(cn.getConector(), queryCabecera.c_str());
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConector());

				if ((fila = mysql_fetch_row(resultado))) {
					string noFactura = fila[0] ? fila[0] : "N/A";
					string fecha = fila[1] ? fila[1] : "N/A";
					string nit = fila[2] ? fila[2] : "N/A";
					string cliente = fila[3] ? fila[3] : "N/A";


					// Encabezado
					cout << "===================================================" << endl;
					cout << "                 FACTURA DE VENTA                  " << endl;
					cout << "===================================================" << endl;
					cout << "No Factura: " << noFactura << "        Fecha: " << fecha << endl;
					cout << "NIT: " << nit << endl;
					cout << "Cliente: " << cliente << endl;
					cout << "---------------------------------------------------" << endl;
					cout << "Producto                          Q. Subtotal" << endl;
					cout << "---------------------------------------------------" << endl;

					// Obtener productos
					string queryDetalle =
						"SELECT p.producto, vd.cantidad, vd.precio_unitario "
						"FROM ventas_detalle vd "
						"JOIN productos p ON vd.idProducto = p.idProducto "
						"WHERE vd.idVenta = " + to_string(idVenta) + ";";

					q_estado = mysql_query(cn.getConector(), queryDetalle.c_str());
					float total = 0.0;
					if (!q_estado) {
						resultado = mysql_store_result(cn.getConector());
						bool tiene_productos = false;

						while ((fila = mysql_fetch_row(resultado))) {
							tiene_productos = true;
							string producto = fila[0];
							float cantidad = stof(fila[1]);
							float precio = stof(fila[2]);
							float subtotal = cantidad * precio;
							total += subtotal;

							cout << producto;
							if (producto.length() < 30) {
								cout << string(30 - producto.length(), ' ');
							}
							cout << "Q " << subtotal << endl;
						}

						if (!tiene_productos) {
							cout << "No hay productos asociados a esta venta." << endl;
						}

					}
					else {
						cout << "Error al obtener productos: " << mysql_error(cn.getConector()) << endl;
					}

					cout << "---------------------------------------------------" << endl;
					cout << "TOTAL:                             Q " << total << endl;
					cout << "===================================================" << endl;
					cout << "          Gracias por su compra!" << endl;

				}
				else {
					cout << "No se encontr  ninguna venta con ID " << idVenta << "." << endl;
				}
			}
			else {
				cout << "Error al ejecutar consulta de cabecera: " << mysql_error(cn.getConector()) << endl;
			}

		}
		else {
			cout << "Error de conexi n a la base de datos." << endl;
		}

		cn.cerrar_conexion();
	}
};

