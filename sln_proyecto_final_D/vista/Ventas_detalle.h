#pragma once
#include "conexionBD.h"
#include <mysql.h>
#include <iostream>
#include <string>

using namespace std;
class Ventas_detalle {
	//atributos
protected:
	int idventa_detalle = 0, idVenta = 0, idProducto;
	string cantidad;
	float precio_unitario;
	//constructores
public:
	Ventas_detalle() {}
	Ventas_detalle(int idVD, int idV, int idP, string can, float pu) {
		idventa_detalle = idVD;
		idVenta = idV;
		idProducto = idP;
		cantidad = can;
		precio_unitario = pu;
	}
	/// metodos
	/// set
	void setidVenta_detalle(int idVD) { idventa_detalle = idVD; }
	void setidVenta(int idV) { idVenta = idV; }
	void setidProducto(int idP) { idProducto = idP; }
	void setcantidad(string can) { cantidad = can; }
	void setprecio_unitario(float pu) { precio_unitario = pu; }
	/// get
	int getidVenta_detalle() { return idventa_detalle; }
	int getidVenta() { return idVenta; }
	int getidProducto() { return idProducto; }
	string getcantidad() { return cantidad; }
	float getprecio_unitario() { return precio_unitario; }
	//////////////////////CREAR///////////////////////////////////////////
	void crear() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string idV = to_string(idVenta);
			string idP = to_string(idProducto);
			string pu = to_string(precio_unitario);
			string insert = "INSERT INTO ventas_detalle(idVenta,idProducto,cantidad,precio_unitario)VALUES(" + idV + "," + idP + ",'" + cantidad + "'," + pu + "); ";
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
		cout << "-----------------------------Ventas detalle----------------------------" << endl;
		int q_estado = 0;
		//instanciar la clase
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		if (cn.getConector()) {
			string consulta = "select * from ventas_detalle;";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConector());
				while (fila = mysql_fetch_row(resultado)) { cout << "Id Venta_detalle:" << fila[0] << ", " << "idVenta:" << fila[1] << ", " << "idProducto:" << fila[2] << ", " << "cantidad:" << fila[3] << ", " << "Precio unitario:" << fila[4] << ", " << endl; }
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
			string idVd = to_string(idventa_detalle);
			string idV = to_string(idVenta);
			string idP = to_string(idProducto);
			string pu = to_string(precio_unitario);
			string update = "UPDATE ventas_detalle SET idVenta = " + idV + ", idProducto = " + idP + ", cantidad= '" + cantidad + "', precio_unitario= " + pu + " ""WHERE idventa_detalle = " + idVd + ";";
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
			string idVd = to_string(idventa_detalle);
			string consulta = "delete from ventas_detalle where idventa_detalle = " + idVd + "";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) { cout << "eliminacion exitosa" << endl; }
			else { cout << "eliminacion fallida" << endl; }
		}
		else { cout << "fallo la conexion"; }
		cn.cerrar_conexion();
	}












};


