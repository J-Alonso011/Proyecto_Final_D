#pragma once
#include "conexionBD.h"
#include "Cliente.h"
#include "Empleados.h"
#include "Productos.h"
#include <mysql.h>
#include <ctime>
#include <regex>
#include <algorithm>
#include <cctype>
#include <locale>
#include <iostream>
#include <string>

using namespace std;
class Ventas {
	Cliente cli;
	Empleados emp;
	Productos prod;
	//atributos
protected:
	int idVenta = 0, nofactura = 0, idCliente, idEmpleado;
	string serie, fechafactura, fechaingreso;
	double total = 0.0;
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
	void leerVenta() {
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
				while (fila = mysql_fetch_row(resultado)) {
					cout << "Id Venta:" << fila[0] << "\n"
						<< "No factura:" << fila[1] << "\n"
						<< "serie:" << fila[2] << "\n"
						<< "Fecha Factura:" << fila[3] << "\n"
						<< "Id Cliente:" << fila[4] << "\n"
						<< "Id Empleado:" << fila[5] << "\n"
						<< "Fecha Ingreso:" << fila[6] << "\n"
						<< "-----------------------------Ventas----------------------------" << endl;
				}
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
		// === Validar formato del NIT ===
	bool validarNIT(const string& nit) {
		if (nit == "C/F" || nit == "CF" || nit == "c/f" || nit == "cf") return true;

		size_t guion = nit.find('-');
		if (guion == string::npos) return false;

		string numero = nit.substr(0, guion);
		string verificador = nit.substr(guion + 1);

		for (char c : numero) {
			if (!isdigit(c)) return false;
		}
		return verificador.length() == 1 && isdigit(verificador[0]);
	}

	// === Buscar o crear cliente por NIT ===
	int obtenerOCrearClientePorNIT(MYSQL* conector, const string& nit) {
		MYSQL_RES* resultado;
		MYSQL_ROW fila;
		int cliente_id = 0;
		string nit_limpio = trim(nit);

		// Consulta con insensibilidad a may sculas/min sculas y espacios
		string consulta = "SELECT idCliente FROM clientes WHERE UPPER(TRIM(NIT)) = UPPER(TRIM('" + nit_limpio + "'));";

		if (!mysql_query(conector, consulta.c_str())) {
			resultado = mysql_store_result(conector);
			if ((fila = mysql_fetch_row(resultado))) {
				cliente_id = atoi(fila[0]);
				cout << "Cliente existente. ID: " << cliente_id << endl;
				mysql_free_result(resultado);
				return cliente_id;
			}
			mysql_free_result(resultado);
		}

		cout << "Cliente no encontrado. Ingrese datos del nuevo cliente:\n";
		string temp;
		Cliente cliente;
		cliente.setnit(nit_limpio);
		cout << "Nombres: ";
		getline(cin, temp); cliente.setnombres(temp);
		cout << "Apellidos: ";
		getline(cin, temp); cliente.setapellidos(temp);
		cout << "Genero (1 masculino, 0 femenino): ";
		bool gen; cin >> gen; cin.ignore(); cliente.setgenero(gen);
		cout << "Telefono: ";
		getline(cin, temp); cliente.settelefono(temp);
		cout << "Correo Electronico: ";
		getline(cin, temp); cliente.setcorreo_electronico(temp);

		string insert_cliente = "INSERT INTO clientes(nombres, apellidos, NIT, genero, telefono, correo_electronico, fechaingreso) VALUES('" +
			cliente.getnombres() + "','" + cliente.getapellidos() + "','" + cliente.getnit() + "'," +
			to_string(cliente.getgenero()) + ",'" + cliente.gettelefono() + "','" + cliente.getcorreo() + "', now());";

		if (!mysql_query(conector, insert_cliente.c_str())) {
			cliente_id = mysql_insert_id(conector);
			cout << "Nuevo cliente creado. ID: " << cliente_id << endl;
			return cliente_id;
		}
		else {
			cout << "Error al insertar cliente: " << mysql_error(conector) << endl;
			return -1;
		}
	}

	// === Obtener siguiente n mero de factura ===
	int obtenerNuevoNumeroFactura(MYSQL* conector) {
		string consulta = "SELECT IFNULL(MAX(nofactura), 0) + 1 FROM ventas;";
		if (mysql_query(conector, consulta.c_str()) == 0) {
			MYSQL_RES* resultado = mysql_store_result(conector);
			MYSQL_ROW fila = mysql_fetch_row(resultado);
			int nuevo = stoi(fila[0]);
			mysql_free_result(resultado);
			return nuevo;
		}
		return 1;
	}
	////////
	string trim(const string& str) {
		auto start = find_if_not(str.begin(), str.end(), [](unsigned char ch) {
			return isspace(ch);
			});

		auto end = find_if_not(str.rbegin(), str.rend(), [](unsigned char ch) {
			return isspace(ch);
			}).base();

		if (start >= end) return "";

		return string(start, end);
	}
	///crear la venta/////////////
	void crearVentaCompleta() {

		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();

		if (!cn.getConector()) {
			cout << "Error de conexi n a la base de datos.\n";
			return;
		}

		string nit;
		cout << "Ingrese NIT del cliente: ";
		cin.ignore();
		getline(cin, nit);
		nit = trim(nit);

		int cliente_id = obtenerOCrearClientePorNIT(cn.getConector(), nit);
		if (cliente_id == -1) {
			cn.cerrar_conexion();
			return;
		}

		// Asignar autom ticamente serie y n mero de factura
		string serie = "A";  // Cambia aqu  seg n tu l gica para la serie
		int nofactura = obtenerNuevoNumeroFactura(cn.getConector());

		cout << "Serie de factura asignada: " << serie << endl;
		cout << "Numero de factura asignado: " << nofactura << endl;
		emp.leerEmpleado();
		cout << "Ingrese el Id del empleado:" << endl;
		cin >> idEmpleado;
		cin.ignore();

		string idE = to_string(idEmpleado);
		string insert_venta = "INSERT INTO ventas(nofactura, serie, fechafactura, idCliente,idEmpleado,fechaingreso) VALUES(" +
			to_string(nofactura) + ",'" + serie + "', now(), " + to_string(cliente_id) + "," + (idE)+",now());";

		if (!mysql_query(cn.getConector(), insert_venta.c_str())) {
			int idVenta = mysql_insert_id(cn.getConector());
			cout << "Venta creada. ID: " << idVenta << endl;

			MYSQL_RES* resultado;
			MYSQL_ROW fila;
			char continuar = 's';
			double total = 0.0;

			while (continuar == 's' || continuar == 'S') {
				int id_producto, cantidad;
				double precio_unitario;
				prod.leerProductos();
				cout << "Ingrese ID del producto: ";
				cin >> id_producto;
				cout << "Ingrese cantidad: ";
				cin >> cantidad;
				cin.ignore();

				string consulta_prod = "SELECT precio_venta FROM productos WHERE idProducto = " + to_string(id_producto) + ";";
				if (!mysql_query(cn.getConector(), consulta_prod.c_str())) {
					resultado = mysql_store_result(cn.getConector());
					if ((fila = mysql_fetch_row(resultado))) {
						precio_unitario = atof(fila[0]);
						double subtotal = cantidad * precio_unitario;
						total += subtotal;

						string insert_detalle = "INSERT INTO ventas_detalle(idVenta, idProducto, cantidad, precio_unitario) VALUES(" +
							to_string(idVenta) + "," + to_string(id_producto) + "," + to_string(cantidad) + "," + to_string(precio_unitario) + ");";

						if (!mysql_query(cn.getConector(), insert_detalle.c_str())) {
							cout << "Detalle de venta agregado.\n";
						}
						else {
							cout << "Error al insertar detalle de venta: " << mysql_error(cn.getConector()) << endl;
						}
					}
					else {
						cout << "Producto no encontrado.\n";
					}
					mysql_free_result(resultado);
				}

				cout << "Desea agregar otro producto? (s/n): ";
				cin >> continuar;
				cin.ignore();
			}

			cout << "Venta registrada con total: Q" << total << endl;
		}
		else {
			cout << "Error al registrar venta: " << mysql_error(cn.getConector()) << endl;
		}

		cn.cerrar_conexion();
	}

	/////////leer venta completa
	void leerVentasCompleto() {
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();

		if (cn.getConector()) {
			string consultaVentas = "SELECT v.idVenta, v.nofactura, v.serie, v.fechafactura, "
				"c.nombres AS cliente, e.nombres AS empleado, v.fechaingreso "
				"FROM ventas v "
				"INNER JOIN clientes c ON v.idCliente = c.idCliente "
				"INNER JOIN empleados e ON v.idEmpleado = e.idEmpleado;";
			MYSQL_RES* resultadoVentas;
			MYSQL_ROW filaVenta;

			if (mysql_query(cn.getConector(), consultaVentas.c_str()) == 0) {
				resultadoVentas = mysql_store_result(cn.getConector());
				while ((filaVenta = mysql_fetch_row(resultadoVentas)) != NULL) {
					cout << "\nVenta ID: " << filaVenta[0] << "\n"
						<< " | Factura: " << filaVenta[1] << "\n"
						<< " | Serie: " << filaVenta[2] << "\n"
						<< " | Fecha: " << filaVenta[3] << "\n"
						<< " | Cliente: " << filaVenta[4] << "\n"
						<< " | Empleado: " << filaVenta[5] << "\n"
						<< " | Ingreso: " << filaVenta[6] << endl;

					string consultaDetalles = "SELECT vd.idProducto, p.producto, vd.cantidad, vd.precio_unitario "
						"FROM ventas_detalle vd "
						"INNER JOIN productos p ON vd.idProducto = p.idProducto "
						"WHERE vd.idVenta = " + string(filaVenta[0]) + ";";

					MYSQL_RES* resultadoDetalle;
					MYSQL_ROW filaDetalle;

					if (mysql_query(cn.getConector(), consultaDetalles.c_str()) == 0) {
						resultadoDetalle = mysql_store_result(cn.getConector());
						while ((filaDetalle = mysql_fetch_row(resultadoDetalle)) != NULL) {
							cout << "  -> Producto ID: " << filaDetalle[0]
								<< " | Nombre: " << filaDetalle[1]
								<< " | Cantidad: " << filaDetalle[2]
								<< " | Precio: " << filaDetalle[3] << endl;
						}
						mysql_free_result(resultadoDetalle);
					}
				}
				mysql_free_result(resultadoVentas);
			}
			else {
				cout << "Error al leer ventas: " << mysql_error(cn.getConector()) << endl;
			}

		}
		else {
			cout << "Error de conexi n a la base de datos.\n";
		}

		cn.cerrar_conexion();
	}
	////////// actualizar venta completa
	void actualizarVentaCompleta() {
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();

		if (cn.getConector()) {
			int idVenta;
			cout << "Ingrese el ID de la venta a actualizar: ";
			cin >> idVenta;

			cout << "Nuevo No. Factura: ";
			cin >> nofactura;
			cin.ignore();
			cout << "Nueva Serie: ";
			getline(cin, serie);
			cli.leerClientes();
			cout << "Nuevo ID Cliente: ";
			cin >> idCliente;
			emp.leerEmpleado();
			cout << "Nuevo ID Empleado: ";
			cin >> idEmpleado;

			string updateVenta = "UPDATE ventas SET nofactura = " + to_string(nofactura) +
				", serie = '" + serie + "', idCliente = " + to_string(idCliente) +
				", idEmpleado = " + to_string(idEmpleado) +
				" WHERE idVenta = " + to_string(idVenta) + ";";

			if (mysql_query(cn.getConector(), updateVenta.c_str()) == 0) {
				cout << "Venta actualizada.\n";

				// Borrar detalles existentes
				string deleteDetalles = "DELETE FROM ventas_detalle WHERE idVenta = " + to_string(idVenta) + ";";
				mysql_query(cn.getConector(), deleteDetalles.c_str());

				// Insertar nuevos detalles
				char opcion;
				do {
					int idProducto, cantidad;
					float precio_unitario;
					prod.leerProductos();
					cout << "ID Producto: ";
					cin >> idProducto;
					cout << "Cantidad: ";
					cin >> cantidad;
					cout << "Precio Unitario: ";
					cin >> precio_unitario;

					string insertDetalle = "INSERT INTO ventas_detalle(idVenta, idProducto, cantidad, precio_unitario) "
						"VALUES(" + to_string(idVenta) + ", " + to_string(idProducto) + ", " +
						to_string(cantidad) + ", " + to_string(precio_unitario) + ");";

					if (mysql_query(cn.getConector(), insertDetalle.c_str()) == 0) {
						cout << "Detalle agregado.\n";
					}
					else {
						cout << "Error al agregar detalle: " << mysql_error(cn.getConector()) << endl;
					}

					cout << " Agregar otro producto? (s/n): ";
					cin >> opcion;

				} while (opcion == 's' || opcion == 'S');

			}
			else {
				cout << "Error al actualizar venta: " << mysql_error(cn.getConector()) << endl;
			}

		}
		else {
			cout << "Error de conexi n.\n";
		}

		cn.cerrar_conexion();
	}
	/////////eliminar venta completa
	void eliminarVentaCompleta() {
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();

		if (cn.getConector()) {
			int idVenta;
			cout << "Ingrese ID de la venta a eliminar: ";
			cin >> idVenta;

			string deleteDetalles = "DELETE FROM ventas_detalle WHERE idVenta = " + to_string(idVenta) + ";";
			mysql_query(cn.getConector(), deleteDetalles.c_str());

			string deleteVenta = "DELETE FROM ventas WHERE idVenta = " + to_string(idVenta) + ";";

			if (mysql_query(cn.getConector(), deleteVenta.c_str()) == 0) {
				cout << "Venta eliminada exitosamente.\n";
			}
			else {
				cout << "Error al eliminar venta: " << mysql_error(cn.getConector()) << endl;
			}

		}
		else {
			cout << "Error de conexi n.\n";
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
	//////////////////menu
	void menuVentasCompleto() {
		int opcionmenuventas;
		do {
			cout << "\n--- Menu Maestro-Detalle de Ventas ---\n";
			cout << "1. Crear Venta\n";
			cout << "2. Leer Ventas\n";
			cout << "3. Actualizar Venta\n";
			cout << "4. Eliminar Venta\n";
			cout << "5. Salir\n";
			cout << "Seleccione una opcion: ";
			cin >> opcionmenuventas;

			switch (opcionmenuventas) {
			case 1:
				crearVentaCompleta();
				break;
			case 2:
				leerVentasCompleto();
				break;
			case 3:
				leerVentasCompleto();
				actualizarVentaCompleta();
				break;
			case 4:
				leerVentasCompleto();
				eliminarVentaCompleta();
				break;
			case 5:
				cout << "Saliendo...\n";
				return;
				break;
			default: cout << "Opci n inv lida.\n"; break;
			}
		} while (opcionmenuventas != 5);
	}
};

