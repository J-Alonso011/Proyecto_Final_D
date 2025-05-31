#pragma once
#include "conexionBD.h"
#include <mysql.h>
#include <iostream>
#include <string>

using namespace std;
class Compras_detalle {
	//atributos
protected:
	int idcompra_detalle = 0, idCompra, idProducto, cantidad;
	float precio_costo_unitario;
	//constructores
public:
	Compras_detalle() {}
	Compras_detalle(int idCd, int idC, int idP, int can, float pcu) {
		idcompra_detalle = idCd;
		idCompra = idC;
		idProducto = idP;
		cantidad = can;
		precio_costo_unitario = pcu;
	}
	/// metodos
	/// set
	void setidcompra_detalle(int idCd) { idcompra_detalle = idCd; }
	void setidCompra(int idC) { idCompra = idC; }
	void setidProducto(int idP) { idProducto = idP; }
	void setcantidad(int can) { cantidad = can; }
	void setprecio_costo_unitario(float pcu) { precio_costo_unitario = pcu; }
	/// get
	int getidcompra_detalle() { return idcompra_detalle; }
	int getidCompra() { return idCompra; }
	int getidProducto() { return idProducto; }
	int getcantidad() { return cantidad; }
	float getprecio_costo_unitario() { return precio_costo_unitario; }
	//////////////////////CREAR///////////////////////////////////////////
	void crear() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string idC = to_string(idCompra);
			string idP = to_string(idProducto);
			string can = to_string(cantidad);
			string pcu = to_string(precio_costo_unitario);
			string insert = "INSERT INTO compras_detalle(idCompra,idProducto,cantidad,precio_costo_unitario)VALUES(" + idC + "," + idP + "," + can + "," + pcu + "); ";
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
		cout << "-----------------------------Compras detalle----------------------------" << endl;
		int q_estado = 0;
		//instanciar la clase
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		if (cn.getConector()) {
			string consulta = "select * from compras_detalle;";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConector());
				while (fila = mysql_fetch_row(resultado)) { cout << "Idcompra_detalle:" << fila[0] << ", " << "idCompra:" << fila[1] << ", " << "idProducto:" << fila[2] << ", " << "cantidad:" << fila[3] << ", " << "Precio Costo unitario:" << fila[4] << ", " << endl; }
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
			string idCd = to_string(idcompra_detalle);
			string idC = to_string(idCompra);
			string idP = to_string(idProducto);
			string can = to_string(cantidad);
			string pcu = to_string(precio_costo_unitario);
			string update = "UPDATE compras_detalle SET idCompra = " + idC + ", idProducto = " + idP + ", cantidad= " + can + ", precio_costo_unitario= " + pcu + " ""WHERE idcompra_detalle = " + idCd + ";";
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
			string idCd = to_string(idcompra_detalle);
			string consulta = "delete from compras_detalle where idcompra_detalle = " + idCd + "";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) { cout << "eliminacion exitosa" << endl; }
			else { cout << "eliminacion fallida" << endl; }
		}
		else { cout << "fallo la conexion"; }
		cn.cerrar_conexion();
	}

















};
