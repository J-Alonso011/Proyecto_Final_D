#pragma once
#include "ConexionBD.h"
#include "Marcas.h"
#include <mysql.h>
#include <iostream>
#include <string>

using namespace std;
class Productos {
	Marcas mar;
	//atributos
protected:
	int idProducto = 0, idMarca = 0, existencia = 0;
	string producto, Descripcion, Imagen, fecha_ingreso;
	float precio_costo, precio_venta;

	//constructores
public:
	Productos() {}
	Productos(int idPro, string pro, int idM, string d, string i, float prc, float prv, int e, string f_in) {
		idProducto = idPro;
		producto = pro;
		idMarca = idM;
		Descripcion = d;
		Imagen = i;
		precio_costo = prc;
		precio_venta = prv;
		existencia = e;
		fecha_ingreso = f_in;

	}
	// metodos
	// set
	void setidProducto(int idPro) { idProducto = idPro; }
	void setproducto(string pro) { producto = pro; }
	void setidMarca(int idM) { idMarca = idM; }
	void setDescripcion(string d) { Descripcion = d; }
	void setImagen(string i) { Imagen = i; }
	void setprecio_costo(float prc) { precio_costo = prc; }
	void setprecio_venta(float prv) { precio_venta = prv; }
	void setexistencia(int e) { existencia = e; }
	void setfecha_ingreso(string f_in) { fecha_ingreso = f_in; }
	// get 
	int getidProducto() { return idProducto; }
	string getproducto() { return producto; }
	int getidMarca() { return idMarca; }
	string getDescripcion() { return Descripcion; }
	string getImagen() { return Imagen; }
	float getprecio_costo() { return precio_costo; }
	float getprecio_venta() { return precio_venta; }
	int getexistencia() { return existencia; }
	string getfecha_ingreso() { return fecha_ingreso; }
	//////////////////////CREAR///////////////////////////////////////////
	void crear() {
		cout << "\n--- Crear Productos ---\n";
		cout << "Ingrese Producto: ";
		getline(cin, producto);
		mar.leerMarca();
		cout << "Ingrese idMarca: ";
		cin >> idMarca;
		cin.ignore();
		cout << "Ingrese Descripcion: ";
		getline(cin, Descripcion);
		cout << "Ingrese Imagen: ";
		getline(cin, Imagen);
		cout << "Ingrese Precio Costo: ";
		cin >> precio_costo;
		cin.ignore();
		cout << "Ingrese Precio Venta ";
		cin >> precio_venta;
		cin.ignore();
		cout << "Ingrese Existencia: ";
		cin >> existencia;
		cin.ignore();
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string idM = to_string(idMarca);
			string prc = to_string(precio_costo);
			string prv = to_string(precio_venta);
			string e = to_string(existencia);
			string insert = "INSERT INTO productos(producto,idMarca,Descripcion,Imagen,precio_costo,precio_venta,existencia,fecha_ingreso)VALUES('" + producto + "'," + idM + ",'" + Descripcion + "','" + Imagen + "'," + prc + "," + prv + ",'" + e + "',now()); ";
			const char* i = insert.c_str();
			q_estado = mysql_query(cn.getConector(), i);
			if (!q_estado) { cout << "ingreso exitoso..." << endl; }
			else { cout << "error al ingresar..." << mysql_error(cn.getConector()) << endl; }
		}
		else { cout << "error en la conexion..." << endl; }
		cn.cerrar_conexion();
	}
	///////////////////////////////LEER/////////////////////////////////
	void leerProductos() {
		cout << "-----------------------------PRODUCTOS----------------------------" << endl;
		int q_estado = 0;
		//instanciar la clase
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		if (cn.getConector()) {
			string consulta = "select * from productos;";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConector());
				while (fila = mysql_fetch_row(resultado)) {
					cout << "Id Producto:" << fila[0] << "\n"
						<< "Producto:" << fila[1] << "\n"
						<< "Id_Marca:" << fila[2] << "\n"
						<< "Descripcion:" << fila[3] << "\n"
						<< "Imagen:" << fila[4] << "\n"
						<< "Precio Costo:" << fila[5] << "\n"
						<< "Precio Venta:" << fila[6] << "\n"
						<< "Existencia:" << fila[7] << "\n"
						<< "Fecha de Ingreso:" << fila[8] << "\n"
						<< "----------------------------------PRODUCTOS-----------------------------------" << endl;
				}
			}
			else { cout << "fallo consulta" << endl; }
		}
		else { cout << "Fallo la conexion" << endl; }
		cn.cerrar_conexion();
	}
	/////////////////////ACTUALIZAR/////////////////////////
	void actualizar() {
		cout << "\n--- Actualizar Productos ---\n";
		cout << "Ingrese ID del Producto a actualizar: ";
		cin >> idProducto;
		cin.ignore();
		cout << "Ingrese Producto: ";
		getline(cin, producto);
		mar.leerMarca();
		cout << "Ingrese idMarca: ";
		cin >> idMarca;
		cin.ignore();
		cout << "Ingrese Descripcion: ";
		getline(cin, Descripcion);
		cout << "Ingrese Imagen: ";
		getline(cin, Imagen);
		cout << "Ingrese Precio Costo: ";
		cin >> precio_costo;
		cin.ignore();
		cout << "Ingrese Precio Venta ";
		cin >> precio_venta;
		cin.ignore();
		cout << "Ingrese Existencia: ";
		cin >> existencia;
		cin.ignore();
		int q_estado = 0;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string idPro = to_string(idProducto);
			string idM = to_string(idMarca);
			string prc = to_string(precio_costo);
			string prv = to_string(precio_venta);
			string e = to_string(existencia);
			string update = "UPDATE productos SET producto = '" + producto + "', idMarca = " + idM + ", Descripcion = '" + Descripcion + "', Imagen = '" + Imagen + "',precio_costo =" + prc + ",precio_venta =" + prv + ",existencia=" + e + ",fecha_ingreso=now()  ""WHERE idProducto = " + idPro + ";";
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
		cout << "\n--- Borrar Productos ---\n";
		cout << "Ingrese ID del Producto a eliminar: ";
		cin >> idProducto;
		cin.ignore();
		int q_estado = 0;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string idPro = to_string(idProducto);
			string consulta = "delete from productos where idProducto = " + idPro + "";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) { cout << "eliminacion exitosa" << endl; }
			else { cout << "eliminacion fallida" << endl; }
		}
		else { cout << "fallo la conexion"; }
		cn.cerrar_conexion();
	}
	//////////////MENU///////////////////////////////////////
	void MenuProductos() {
		int opcionProductos;

		do {
			cout << "\n========= MENU PRODUCTOS =========\n";
			cout << "1. Crear Producto\n";
			cout << "2. Mostrar Producto\n";
			cout << "3. Actualizar Producto\n";
			cout << "4. Eliminar Producto\n";
			cout << "5. Menu Principal\n";
			cout << "Seleccione una opcion: ";
			cin >> opcionProductos;
			cin.ignore();

			switch (opcionProductos) {
			case 1:
				crear();
				break;
			case 2:
				leerProductos();
				break;
			case 3:
				leerProductos();
				actualizar();
				break;
			case 4:
				leerProductos();
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
		} while (opcionProductos != 5);
	}
};
