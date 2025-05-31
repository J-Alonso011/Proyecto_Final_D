#include <iostream>
#include "ConexionBD.h"
#include "Puestos.h"
#include "Proveedores.h"
#include "Marcas.h"
#include "Cliente.h"
#include "Productos.h"
#include "Empleados.h"
#include "Ventas.h"
#include "Compras.h"
using namespace std;



int main() {
    int opcion;
    Puestos p;
    Proveedores pro;
    Marcas m;
    Cliente c;
    Productos prod;
    Empleados e;
    Ventas vc;
    Compras cc;


    do {
        cout << "\n========= MENU CLIENTES =========\n";
        cout << "1. Puestos\n";
        cout << "2. Proveedores\n";
        cout << "3. Marcas\n";
        cout << "4. Clientes\n";
        cout << "5. Productos\n";
        cout << "6. Empleados\n";
        cout << "7. Crear Venta-detalle\n";
        cout << "8. Imprimir Factura\n";
        cout << "9. Compras y compras detalle\n";
        cout << "10. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1:
            p.MenuPuestos();
            break;
        case 2:
            pro.MenuProveedores();
            break;
        case 3:
            m.MenuMarcas();
            break;
        case 4:
            c.MenuClientes();
            break;
        case 5:
            prod.MenuProductos();
            break;
        case 6:
            e.MenuEmpleados();
            break;
        case 7:
            vc.menuVentasCompleto();
            break;
        case 8:
        {
            Ventas v;
            v.leerVentasCompleto();
            int idVentaBuscar;
            cout << "Ingrese el ID de la venta que desea imprimir: ";
            cin >> idVentaBuscar;
            v.setidVenta(idVentaBuscar);
            v.imprimirFactura();
            system("pause");
            break;
        }
        case 9:
            cc.crearCompraCompleta();
            break;
        case 10:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opción inválida. Intente de nuevo." << endl;
        }

        system("pause");
        system("cls");
    } while (opcion != 10);

    return 0;
}

