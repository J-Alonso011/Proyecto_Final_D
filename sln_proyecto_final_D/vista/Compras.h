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
	///////Leer compra completo
	void leerComprasCompleta() {
		ConexionBD cn;
		cn.abrir_conexion();

		if (cn.getConector()) {
			string consulta = "SELECT * FROM compras;";
			const char* q = consulta.c_str();
			MYSQL_RES* resultado;
			MYSQL_ROW fila;

			if (!mysql_query(cn.getConector(), q)) {
				resultado = mysql_store_result(cn.getConector());
				cout << "ID | No. Orden | ID Proveedor | Fecha Orden | Fecha Ingreso" << endl;
				while ((fila = mysql_fetch_row(resultado))) {
					cout << fila[0] << " | " << fila[1] << " | " << fila[2] << " | " << fila[3] << " | " << fila[4] << endl;
				}
			}
			else {
				cout << "Error al leer compras: " << mysql_error(cn.getConector()) << endl;
			}
		}

		cn.cerrar_conexion();
	}
	/////////Actualizar compra completa
	void actualizarCompraCompleta() {
		ConexionBD cn;
		cn.abrir_conexion();

		if (cn.getConector()) {
			int id;
			cout << "Ingrese ID de la compra a actualizar: ";
			cin >> id;

			cout << "Ingrese nuevo No. Orden de Compra: ";
			cin >> no_orden_compra;
			prov.leerProveedor();
			cout << "Ingrese nuevo ID Proveedor: ";
			cin >> idProveedor;

			string update = "UPDATE compras SET no_orden_compra = " + to_string(no_orden_compra) +
				", idProveedor = " + to_string(idProveedor) + " WHERE idCompra = " + to_string(id) + ";";

			if (mysql_query(cn.getConector(), update.c_str()) == 0) {
				cout << "Compra actualizada exitosamente." << endl;

				// Primero eliminar detalles existentes
				string eliminarDetalle = "DELETE FROM compras_detalle WHERE idCompra = " + to_string(id) + ";";
				if (mysql_query(cn.getConector(), eliminarDetalle.c_str()) != 0) {
					cout << "Error al eliminar productos anteriores: " << mysql_error(cn.getConector()) << endl;
				}

				// Agregar nuevos detalles
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
						"VALUES(" + to_string(id) + ", " + to_string(idProducto) + ", " +
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
				cout << "Error al actualizar compra: " << mysql_error(cn.getConector()) << endl;
			}
		}

		cn.cerrar_conexion();
	}
	///////Eliminar compra completa
	void eliminarCompraCompleta() {
		ConexionBD cn;
		cn.abrir_conexion();

		if (cn.getConector()) {
			int id;
			cout << "Ingrese ID de la compra a eliminar: ";
			cin >> id;

			string eliminarDetalle = "DELETE FROM compras_detalle WHERE idCompra = " + to_string(id) + ";";
			string eliminarCompra = "DELETE FROM compras WHERE idCompra = " + to_string(id) + ";";

			if (mysql_query(cn.getConector(), eliminarDetalle.c_str()) == 0 &&
				mysql_query(cn.getConector(), eliminarCompra.c_str()) == 0) {
				cout << "Compra eliminada correctamente." << endl;
			}
			else {
				cout << "Error al eliminar la compra: " << mysql_error(cn.getConector()) << endl;
			}
		}

		cn.cerrar_conexion();
	}
	///////factura compra
	void imprimirFacturaCompra() {
		ConexionBD cn;
		cn.abrir_conexion();

		if (cn.getConector()) {
			int id;
			cout << "Ingrese ID de la compra para imprimir factura: ";
			cin >> id;

			string consulta = "SELECT c.idCompra, c.no_orden_compra, c.fecha_orden, c.fechaingreso, p.proveedor "
				"FROM compras c INNER JOIN proveedores p ON c.idProveedor = p.idProveedor "
				"WHERE c.idCompra = " + to_string(id) + ";";

			MYSQL_RES* resultado;
			MYSQL_ROW fila;

			if (!mysql_query(cn.getConector(), consulta.c_str())) {
				resultado = mysql_store_result(cn.getConector());
				if ((fila = mysql_fetch_row(resultado))) {
					cout << "===================================================" << endl;
					cout << "----- Factura de Compra -----" << endl;
					cout << "===================================================" << endl;
					cout << "ID Compra: " << fila[0] << endl;
					cout << "No. Orden: " << fila[1] << endl;
					cout << "Fecha Orden: " << fila[2] << endl;
					cout << "Fecha Ingreso: " << fila[3] << endl;
					cout << "Proveedor: " << fila[4] << endl;
					cout << "---------------------------------------------------" << endl;
					string consultaDetalle = "SELECT pr.producto, cd.cantidad, cd.precio_costo_unitario, "
						"(cd.cantidad * cd.precio_costo_unitario) as total "
						"FROM compras_detalle cd INNER JOIN productos pr ON cd.idProducto = pr.idProducto "
						"WHERE cd.idCompra = " + to_string(id) + ";";

					if (!mysql_query(cn.getConector(), consultaDetalle.c_str())) {
						MYSQL_RES* resDetalle = mysql_store_result(cn.getConector());
						MYSQL_ROW filaDetalle;

						double totalCompra = 0;
						cout << "---------------------------------------------------" << endl;
						cout << "\nProductos:\n";
						cout << "Producto | Cantidad | Precio Unitario | Total" << endl;


						while ((filaDetalle = mysql_fetch_row(resDetalle))) {
							cout << filaDetalle[0] << " | " << filaDetalle[1] << " | " << filaDetalle[2]
								<< " | " << filaDetalle[3] << endl;
							totalCompra += atof(filaDetalle[3]);
						}

						cout << "\nTotal de la compra: Q" << totalCompra << endl;
						cout << "===================================================" << endl;
					}
				}
				else {
					cout << "No se encontr  la compra." << endl;
				}
			}
			else {
				cout << "Error al consultar compra: " << mysql_error(cn.getConector()) << endl;
			}
		}

		cn.cerrar_conexion();
	}
	//////////////////menu
	void menuComprasCompleto() {
		int opcionmenuventas;
		do {
			cout << "\n--- Menu Maestro-Detalle de Ventas ---\n";
			cout << "1. Crear Compra\n";
			cout << "2. Leer Compra\n";
			cout << "3. Actualizar Compra\n";
			cout << "4. Eliminar Compra\n";
			cout << "5. Salir\n";
			cout << "Seleccione una opcion: ";
			cin >> opcionmenuventas;

			switch (opcionmenuventas) {
			case 1:
				crearCompraCompleta();
				break;
			case 2:
				leerComprasCompleta();
				break;
			case 3:
				leerComprasCompleta();
				actualizarCompraCompleta();
				break;
			case 4:
				leerComprasCompleta();
				eliminarCompraCompleta();
				break;
			case 5:
				cout << "Saliendo...\n";
				return;
				break;
			default: cout << "Opcion invalida.\n"; break;
			}
		} while (opcionmenuventas != 5);
	}



};

