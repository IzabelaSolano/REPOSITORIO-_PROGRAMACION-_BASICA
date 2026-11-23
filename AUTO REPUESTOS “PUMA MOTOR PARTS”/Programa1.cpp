/**********************************************************************
 * ALUMNA: Iris Izabela Solano Amador
 * NÚMERO DE CUENTA: 20231003826
 * PROGRAMA #1 – AUTO REPUESTOS "PUMA MOTOR PARTS"
 **********************************************************************/

#include <iostream>
#include <string>
#include <iomanip>
#include <limits> 

using namespace std;

int main() {
    // Inventario inicial de los 12 productos según tabla oficial[cite: 1]
    int stock1 = 30; // Filtro de aceite (Motor y Afinación)[cite: 1]
    int stock2 = 80; // Bujía (unidad) (Motor y Afinación)[cite: 1]
    int stock3 = 40; // Aceite 10W-30 (litro) (Motor y Afinación)[cite: 1]
    int stock4 = 25; // Pastillas de freno (juego) (Frenos y Suspensión)[cite: 1]
    int stock5 = 15; // Disco de freno (unidad) (Frenos y Suspensión)[cite: 1]
    int stock6 = 12; // Amortiguador (unidad) (Frenos y Suspensión)[cite: 1]
    int stock7 = 10; // Batería 12V (Eléctrico)[cite: 1]
    int stock8 = 6;  // Alternador (Eléctrico)[cite: 1]
    int stock9 = 60; // Bombillo LED (unidad) (Eléctrico)[cite: 1]
    int stock10 = 20;// Limpiaparabrisas (par) (Accesorios)[cite: 1]
    int stock11 = 50;// Aromatizante (Accesorios)[cite: 1]
    int stock12 = 25;// Cera para auto (Accesorios)[cite: 1]

    // Precios oficiales (Lps.)[cite: 1]
    double precio1 = 120.00, precio2 = 90.00, precio3 = 180.00;
    double precio4 = 450.00, precio5 = 900.00, precio6 = 1200.00;
    double precio7 = 2500.00, precio8 = 3800.00, precio9 = 80.00;
    double precio10 = 250.00, precio11 = 60.00, precio12 = 150.00;

    // Puntos por unidad de cada producto según tabla[cite: 1]
    int pts1 = 10, pts2 = 8, pts3 = 12;
    int pts4 = 25, pts5 = 40, pts6 = 50;
    int pts7 = 80, pts8 = 100, pts9 = 5;
    int pts10 = 15, pts11 = 3, pts12 = 8;

    // Acumuladores para el Módulo de Estadísticas General del Día[cite: 2, 3]
    int totalUnidades1 = 0, totalUnidades2 = 0, totalUnidades3 = 0;
    int totalUnidades4 = 0, totalUnidades5 = 0, totalUnidades6 = 0;
    int totalUnidades7 = 0, totalUnidades8 = 0, totalUnidades9 = 0;
    int totalUnidades10 = 0, totalUnidades11 = 0, totalUnidades12 = 0;

    double dineroMotorAfinacion = 0;
    double dineroFrenosSuspension = 0;
    double dineroElectrico = 0;
    double dineroAccesorios = 0;

    double totalDescuentosDia = 0;
    double totalIsvDia = 0;
    double totalVentasDia = 0;

    int contEfectivo = 0;
    int contTransferencia = 0;

    char continuarCliente = 'S';

    do {
        cout << "\n=======================================================\n";
        cout << "   BIENVENIDO A AUTO REPUESTOS \"PUMA MOTOR PARTS\"       \n";
        cout << "=======================================================\n";

        string nombreCliente;
        char genero;
        int edad;
        int tipoClienteOp;

        cout << "\n--- DATOS DE FACTURACION ---\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nombre del cliente: ";
        getline(cin, nombreCliente);

        cout << "Sexo (H/M): ";
        cin >> genero;
        while (genero != 'H' && genero != 'h' && genero != 'M' && genero != 'm') {
            cout << "Opcion invalida. Ingrese H o M: ";
            cin >> genero;
        }

        cout << "Edad: ";
        cin >> edad;
        while (cin.fail() || edad < 0 || edad > 120) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Edad invalida. Ingrese nuevamente: ";
            cin >> edad;
        }

        cout << "\n--- TIPO DE CLIENTE ---\n";
        cout << "1. Particular (5% de descuento en Accesorios)[cite: 1]\n";
        cout << "2. Taller (10% de descuento en Motor y Afinación)[cite: 1]\n";
        cout << "3. Flotilla (12% de descuento en Frenos y Suspensión)[cite: 1]\n";
        cout << "Seleccione el tipo de cliente (1-3): ";
        cin >> tipoClienteOp;
        while (cin.fail() || tipoClienteOp < 1 || tipoClienteOp > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opcion invalida. Ingrese (1-3): ";
            cin >> tipoClienteOp;
        }

        string nombreTipoCliente = "";
        if (tipoClienteOp == 1) nombreTipoCliente = "Particular (5% Accesorios)";
        else if (tipoClienteOp == 2) nombreTipoCliente = "Taller (10% Motor y Afinación)";
        else if (tipoClienteOp == 3) nombreTipoCliente = "Flotilla (12% Frenos y Suspensión)";

        double subtotalCliente = 0;
        double descuentoCliente = 0;
        int puntosCliente = 0;
        string desgloseFactura = "";

        // Variables temporales de inventario y unidades para el cliente actual (por si cancela)
        int tStock1 = 0, tStock2 = 0, tStock3 = 0, tStock4 = 0, tStock5 = 0, tStock6 = 0;
        int tStock7 = 0, tStock8 = 0, tStock9 = 0, tStock10 = 0, tStock11 = 0, tStock12 = 0;

        int cantFiltroComprado = 0; 
        int cantAceiteComprado = 0;  

        char comprarMas = 'S';
        bool banderaCompra = false;

        // Bucle de compras del cliente (uno o más productos)
        do {
            int codigoProd = 0;
            int cantidad = 0;
            double precioUnit = 0;
            string nombreProd = "";
            int categoriaProd = 0; 
            int puntosProd = 0;
            int* stockRef = nullptr;

            cout << "\n=======================================================\n";
            cout << "             CATALOGO DE PRODUCTOS                     \n";
            cout << "=======================================================\n";
            cout << "[MOTOR Y AFINACION]\n";
            cout << "1. Filtro de aceite        - Lps. 120.00 | Stock: " << stock1 << " | Pts: " << pts1 << "\n";
            cout << "2. Bujía (unidad)          - Lps.  90.00 | Stock: " << stock2 << " | Pts: " << pts2 << "\n";
            cout << "3. Aceite 10W-30 (litro)   - Lps. 180.00 | Stock: " << stock3 << " | Pts: " << pts3 << "\n";
            cout << "[FRENOS Y SUSPENSION]\n";
            cout << "4. Pastillas de freno      - Lps. 450.00 | Stock: " << stock4 << " | Pts: " << pts4 << "\n";
            cout << "5. Disco de freno          - Lps. 900.00 | Stock: " << stock5 << " | Pts: " << pts5 << "\n";
            cout << "6. Amortiguador            - Lps. 1200.00| Stock: " << stock6 << " | Pts: " << pts6 << "\n";
            cout << "[ELECTRICO]\n";
            cout << "7. Batería 12V             - Lps. 2500.00| Stock: " << stock7 << " | Pts: " << pts7 << "\n";
            cout << "8. Alternador              - Lps. 3800.00| Stock: " << stock8 << " | Pts: " << pts8 << "\n";
            cout << "9. Bombillo LED            - Lps.  80.00 | Stock: " << stock9 << " | Pts: " << pts9 << "\n";
            cout << "[ACCESORIOS]\n";
            cout << "10. Limpiaparabrisas (par) - Lps. 250.00 | Stock: " << stock10 << "| Pts: " << pts10 << "\n";
            cout << "11. Aromatizante           - Lps.  60.00 | Stock: " << stock11 << "| Pts: " << pts11 << "\n";
            cout << "12. Cera para auto         - Lps. 150.00 | Stock: " << stock12 << "| Pts: " << pts12 << "\n";
            cout << "-------------------------------------------------------\n";
            cout << "Ingrese el código del producto (1-12): ";
            cin >> codigoProd;

            while (cin.fail() || codigoProd < 1 || codigoProd > 12) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Codigo invalido. Ingrese nuevamente (1-12): ";
                cin >> codigoProd;
            }

            cout << "Cantidad a comprar: ";
            cin >> cantidad;
            while (cin.fail() || cantidad <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Cantidad invalida. Ingrese nuevamente: ";
                cin >> cantidad;
            }

            // Mapeo de datos del producto
            switch (codigoProd) {
                case 1: nombreProd = "Filtro de aceite"; precioUnit = precio1; categoriaProd = 1; puntosProd = pts1; stockRef = &stock1; break;
                case 2: nombreProd = "Bujía (unidad)"; precioUnit = precio2; categoriaProd = 1; puntosProd = pts2; stockRef = &stock2; break;
                case 3: nombreProd = "Aceite 10W-30 (litro)"; precioUnit = precio3; categoriaProd = 1; puntosProd = pts3; stockRef = &stock3; break;
                case 4: nombreProd = "Pastillas de freno (juego)"; precioUnit = precio4; categoriaProd = 2; puntosProd = pts4; stockRef = &stock4; break;
                case 5: nombreProd = "Disco de freno (unidad)"; precioUnit = precio5; categoriaProd = 2; puntosProd = pts5; stockRef = &stock5; break;
                case 6: nombreProd = "Amortiguador (unidad)"; precioUnit = precio6; categoriaProd = 2; puntosProd = pts6; stockRef = &stock6; break;
                case 7: nombreProd = "Batería 12V"; precioUnit = precio7; categoriaProd = 3; puntosProd = pts7; stockRef = &stock7; break;
                case 8: nombreProd = "Alternador"; precioUnit = precio8; categoriaProd = 3; puntosProd = pts8; stockRef = &stock8; break;
                case 9: nombreProd = "Bombillo LED (unidad)"; precioUnit = precio9; categoriaProd = 3; puntosProd = pts9; stockRef = &stock9; break;
                case 10: nombreProd = "Limpiaparabrisas (par)"; precioUnit = precio10; categoriaProd = 4; puntosProd = pts10; stockRef = &stock10; break;
                case 11: nombreProd = "Aromatizante"; precioUnit = precio11; categoriaProd = 4; puntosProd = pts11; stockRef = &stock11; break;
                case 12: nombreProd = "Cera para auto"; precioUnit = precio12; categoriaProd = 4; puntosProd = pts12; stockRef = &stock12; break;
            }

            // Validar stock (requisito: mostrar "Stock insuficiente")[cite: 2]
            if (cantidad > *stockRef) {
                cout << "\n[!] Stock insuficiente. Disponibles en inventario: " << *stockRef << "\n";
                cout << "¿Desea intentar con otro producto? (S/N): ";
                cin >> comprarMas;
                while (comprarMas != 'S' && comprarMas != 's' && comprarMas != 'N' && comprarMas != 'n') {
                    cout << "Ingrese S o N: ";
                    cin >> comprarMas;
                }
                if (comprarMas == 'N' || comprarMas == 'n') {
                    // Validar que si decide no continuar, el bucle externo obligue a tener al menos algo o repetir
                    break;
                }
                continue;
            }

            // Descontar inventario automáticamente[cite: 2]
            *stockRef -= cantidad;
            banderaCompra = true;

            // Registrar temporales para anulación
            if (codigoProd == 1) { tStock1 += cantidad; cantFiltroComprado += cantidad; }
            else if (codigoProd == 2) { tStock2 += cantidad; }
            else if (codigoProd == 3) { tStock3 += cantidad; cantAceiteComprado += cantidad; }
            else if (codigoProd == 4) { tStock4 += cantidad; }
            else if (codigoProd == 5) { tStock5 += cantidad; }
            else if (codigoProd == 6) { tStock6 += cantidad; }
            else if (codigoProd == 7) { tStock7 += cantidad; }
            else if (codigoProd == 8) { tStock8 += cantidad; }
            else if (codigoProd == 9) { tStock9 += cantidad; }
            else if (codigoProd == 10) { tStock10 += cantidad; }
            else if (codigoProd == 11) { tStock11 += cantidad; }
            else if (codigoProd == 12) { tStock12 += cantidad; }

            double brutoItem = precioUnit * cantidad;
            double rebajaItem = 0;
            string descAplicado = "Ninguno";

            // 1. Descuento por Tipo de Cliente[cite: 1]
            if (tipoClienteOp == 1 && categoriaProd == 4) { 
                rebajaItem += brutoItem * 0.05;
                descAplicado = "Desc. Particular (5% Accesorios)";
            } else if (tipoClienteOp == 2 && categoriaProd == 1) { 
                rebajaItem += brutoItem * 0.10;
                descAplicado = "Desc. Taller (10% Motor)";
            } else if (tipoClienteOp == 3 && categoriaProd == 2) { 
                rebajaItem += brutoItem * 0.12;
                descAplicado = "Desc. Flotilla (12% Frenos)";
            }

            // 2. Descuentos Adicionales por Género[cite: 2]
            if ((genero == 'M' || genero == 'm') && categoriaProd == 4) { 
                rebajaItem += brutoItem * 0.10;
                if (descAplicado == "Ninguno") descAplicado = "Mujer (10% Accesorios)";
                else descAplicado += " + Mujer (10%)";
            }
            if ((genero == 'H' || genero == 'h') && categoriaProd == 2) { 
                rebajaItem += brutoItem * 0.05;
                if (descAplicado == "Ninguno") descAplicado = "Hombre (5% Frenos)";
                else descAplicado += " + Hombre (5%)";
            }

            // 3. Tercera Edad (>= 60 años): 10% de descuento general adicional[cite: 2]
            if (edad >= 60) {
                rebajaItem += brutoItem * 0.10;
                if (descAplicado == "Ninguno") descAplicado = "Tercera Edad (10%)";
                else descAplicado += " + Tercera Edad (10%)";
            }

            // 4. Promoción por Volumen (> 5 unidades del mismo producto): 3% adicional[cite: 2]
            if (cantidad > 5) {
                rebajaItem += brutoItem * 0.03;
                if (descAplicado == "Ninguno") descAplicado = "Volumen > 5 (3%)";
                else descAplicado += " + Volumen (3%)";
            }

            double netoItem = brutoItem - rebajaItem;

            desgloseFactura += "   * " + nombreProd + " (" + to_string(cantidad) + " uds) - Subtotal: " + 
                               to_string((int)brutoItem) + " Lps. - Rebaja: " + to_string((int)rebajaItem) + 
                               " Lps. [" + descAplicado + "]\n";

            // Acumular ventas por categoría (sin ISV)[cite: 3] y unidades totales
            if (categoriaProd == 1) dineroMotorAfinacion += netoItem;
            else if (categoriaProd == 2) dineroFrenosSuspension += netoItem;
            else if (categoriaProd == 3) dineroElectrico += netoItem;
            else if (categoriaProd == 4) dineroAccesorios += netoItem;

            if (codigoProd == 1) totalUnidades1 += cantidad;
            else if (codigoProd == 2) totalUnidades2 += cantidad;
            else if (codigoProd == 3) totalUnidades3 += cantidad;
            else if (codigoProd == 4) totalUnidades4 += cantidad;
            else if (codigoProd == 5) totalUnidades5 += cantidad;
            else if (codigoProd == 6) totalUnidades6 += cantidad;
            else if (codigoProd == 7) totalUnidades7 += cantidad;
            else if (codigoProd == 8) totalUnidades8 += cantidad;
            else if (codigoProd == 9) totalUnidades9 += cantidad;
            else if (codigoProd == 10) totalUnidades10 += cantidad;
            else if (codigoProd == 11) totalUnidades11 += cantidad;
            else if (codigoProd == 12) totalUnidades12 += cantidad;

            subtotalCliente += brutoItem;
            descuentoCliente += rebajaItem;
            puntosCliente += (cantidad * puntosProd);

            cout << "¿Desea comprar otro producto? (S/N): ";
            cin >> comprarMas;
            while (comprarMas != 'S' && comprarMas != 's' && comprarMas != 'N' && comprarMas != 'n') {
                cout << "Ingrese S o N: ";
                cin >> comprarMas;
            }

        } while (comprarMas == 'S' || comprarMas == 's');

        // Bucle de validación estricta: No permite avanzar si no seleccionó ningún producto válido
        while (!banderaCompra || subtotalCliente <= 0) {
            cout << "\n[!] No ha seleccionado ningun producto valido. Debe agregar al menos un articulo.\n";
            cout << "¿Desea agregar productos ahora? (S/N): ";
            char opcionSalida;
            cin >> opcionSalida;
            if (opcionSalida == 'S' || opcionSalida == 's') {
                // Reinicia el ciclo de compra para este mismo cliente
                cout << "Volviendo al catalogo de productos...\n";
                // Volvemos a lanzar la lógica de compra simulando el do-while principal con un salto o estructura limpia:
                int codigoProd = 0;
                int cantidad = 0;
                double precioUnit = 0;
                string nombreProd = "";
                int categoriaProd = 0; 
                int puntosProd = 0;
                int* stockRef = nullptr;

                cout << "Ingrese el codigo del producto (1-12): ";
                cin >> codigoProd;
                if (cin.fail() || codigoProd < 1 || codigoProd > 12) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
                cout << "Cantidad a comprar: ";
                cin >> cantidad;
                if (cin.fail() || cantidad <= 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
                // Mapeo rápido para reintentar
                switch (codigoProd) {
                    case 1: nombreProd = "Filtro de aceite"; precioUnit = precio1; categoriaProd = 1; puntosProd = pts1; stockRef = &stock1; break;
                    case 2: nombreProd = "Bujía (unidad)"; precioUnit = precio2; categoriaProd = 1; puntosProd = pts2; stockRef = &stock2; break;
                    case 3: nombreProd = "Aceite 10W-30 (litro)"; precioUnit = precio3; categoriaProd = 1; puntosProd = pts3; stockRef = &stock3; break;
                    case 4: nombreProd = "Pastillas de freno (juego)"; precioUnit = precio4; categoriaProd = 2; puntosProd = pts4; stockRef = &stock4; break;
                    case 5: nombreProd = "Disco de freno (unidad)"; precioUnit = precio5; categoriaProd = 2; puntosProd = pts5; stockRef = &stock5; break;
                    case 6: nombreProd = "Amortiguador (unidad)"; precioUnit = precio6; categoriaProd = 2; puntosProd = pts6; stockRef = &stock6; break;
                    case 7: nombreProd = "Batería 12V"; precioUnit = precio7; categoriaProd = 3; puntosProd = pts7; stockRef = &stock7; break;
                    case 8: nombreProd = "Alternador"; precioUnit = precio8; categoriaProd = 3; puntosProd = pts8; stockRef = &stock8; break;
                    case 9: nombreProd = "Bombillo LED (unidad)"; precioUnit = precio9; categoriaProd = 3; puntosProd = pts9; stockRef = &stock9; break;
                    case 10: nombreProd = "Limpiaparabrisas (par)"; precioUnit = precio10; categoriaProd = 4; puntosProd = pts10; stockRef = &stock10; break;
                    case 11: nombreProd = "Aromatizante"; precioUnit = precio11; categoriaProd = 4; puntosProd = pts11; stockRef = &stock11; break;
                    case 12: nombreProd = "Cera para auto"; precioUnit = precio12; categoriaProd = 4; puntosProd = pts12; stockRef = &stock12; break;
                }
                if (cantidad <= *stockRef) {
                    *stockRef -= cantidad;
                    banderaCompra = true;
                    subtotalCliente += (precioUnit * cantidad);
                }
            } else {
                // Si decide salir por completo de este cliente sin comprar
                cout << "\nCliente descartado. Regresando al menú principal.\n";
                stock1 += tStock1; stock2 += tStock2; stock3 += tStock3;
                stock4 += tStock4; stock5 += tStock5; stock6 += tStock6;
                stock7 += tStock7; stock8 += tStock8; stock9 += tStock9;
                stock10 += tStock10; stock11 += tStock11; stock12 += tStock12;
                goto siguienteCliente; // Salta directo a preguntar si desea ingresar otro cliente
            }
        }

        // Promoción especial: Cambio de aceite (Aceite + Filtro) -> 8% adicional[cite: 2]
        if (cantFiltroComprado > 0 && cantAceiteComprado > 0) {
            double subtotalCombo = (cantFiltroComprado * precio1) + (cantAceiteComprado * precio3);
            double descCombo = subtotalCombo * 0.08;
            descuentoCliente += descCombo;
            desgloseFactura += "   * [PROMO COMBO] Aceite + Filtro (8% desc. adicional): -" + to_string((int)descCombo) + " Lps.\n";
        }

        double netoCliente = subtotalCliente - descuentoCliente;
        double isvCliente = netoCliente * 0.15; // 15% aplicado al total DESPUÉS de descuentos[cite: 2]
        double totalLempiras = netoCliente + isvCliente;
        double totalDolares = totalLempiras / 26.42; //[cite: 2]

        // Impresión de Factura
        cout << fixed << setprecision(2);
        cout << "\n======================================================================\n";
        cout << "                           FACTURA COMERCIAL                          \n";
        cout << "======================================================================\n";
        cout << " Cliente: " << nombreCliente << "\n";
        cout << " Tipo de Cliente: " << nombreTipoCliente << "\n";
        cout << "----------------------------------------------------------------------\n";
        cout << " DESGLOSE DE PRODUCTOS:\n";
        cout << desgloseFactura;
        cout << "----------------------------------------------------------------------\n";
        cout << " Subtotal Inicial:          " << subtotalCliente << " Lps.\n";
        cout << " Total Descuentos:         -" << descuentoCliente << " Lps.\n";
        cout << " Subtotal Neto:             " << netoCliente << " Lps.\n";
        cout << " Impuesto ISV (15%):        " << isvCliente << " Lps.\n";
        cout << "----------------------------------------------------------------------\n";
        cout << " >> TOTAL A PAGAR (HNL):    " << totalLempiras << " Lps.\n";
        cout << " >> TOTAL A PAGAR (USD):    " << totalDolares << " USD\n";
        cout << " Puntos Acumulados:         " << puntosCliente << " pts.[cite: 2]\n";
        cout << "======================================================================\n";

        int metodoPago = 0;
        string nombrePago = "";
        cout << "\n--- METODO DE PAGO ---\n";
        cout << "1. Efectivo (Ingresar monto y calcular cambio)[cite: 2]\n";
        cout << "2. Transferencia (N. de referencia y bancos)[cite: 2]\n";
        cout << "3. [Cancelar compra y devolver stock]\n";
        cout << "Opcion: ";
        cin >> metodoPago;

        while (cin.fail() || metodoPago < 1 || metodoPago > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opcion invalida. Ingrese (1-3): ";
            cin >> metodoPago;
        }

        if (metodoPago == 3) {
            stock1 += tStock1; stock2 += tStock2; stock3 += tStock3;
            stock4 += tStock4; stock5 += tStock5; stock6 += tStock6;
            stock7 += tStock7; stock8 += tStock8; stock9 += tStock9;
            stock10 += tStock10; stock11 += tStock11; stock12 += tStock12;

            totalUnidades1 -= tStock1; totalUnidades2 -= tStock2; totalUnidades3 -= tStock3;
            totalUnidades4 -= tStock4; totalUnidades5 -= tStock5; totalUnidades6 -= tStock6;
            totalUnidades7 -= tStock7; totalUnidades8 -= tStock8; totalUnidades9 -= tStock9;
            totalUnidades10 -= tStock10; totalUnidades11 -= tStock11; totalUnidades12 -= tStock12;

            cout << "\n[!] Compra anulada y stock devuelto.\n";
            goto siguienteCliente;
        }

        if (metodoPago == 1) {
            contEfectivo++;
            nombrePago = "Efectivo";
            double efectivoRecibido;
            cout << "Ingrese efectivo recibido: ";
            cin >> efectivoRecibido;
            while (cin.fail() || efectivoRecibido < totalLempiras) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Monto insuficiente. Ingrese nuevamente: ";
                cin >> efectivoRecibido;
            }
            cout << "Cambio para el cliente: " << (efectivoRecibido - totalLempiras) << " Lps.\n";
        } else {
            contTransferencia++;
            nombrePago = "Transferencia";
            string refTrans, bOrigen, bDestino;
            cout << "Número de comprobante/referencia: ";
            cin >> refTrans;
            cout << "Banco de emisión: ";
            cin >> bOrigen;
            cout << "Banco de destino: ";
            cin >> bDestino;
            cout << "Transferencia registrada por la cantidad exacta de " << totalLempiras << " Lps.\n";
        }

        totalDescuentosDia += descuentoCliente;
        totalIsvDia += isvCliente;
        totalVentasDia += totalLempiras;

        siguienteCliente:
        cout << "\n¿Desea ingresar otro cliente? (S/N): ";[cite: 2]
        cin >> continuarCliente;
        while (continuarCliente != 'S' && continuarCliente != 's' && continuarCliente != 'N' && continuarCliente != 'n') {
            cout << "Ingrese S o N: ";
            cin >> continuarCliente;
        }

    } while (continuarCliente == 'S' || continuarCliente == 's');

    // =======================================================
    // MODULO DE ESTADISTICAS (Al terminar todas las ventas con 'N')[cite: 2, 3]
    // =======================================================
    cout << fixed << setprecision(2);
    cout << "\n=======================================================\n";
    cout << "             REPORTE ESTADISTICO DEL DIA               \n";
    cout << "=======================================================\n";

    string nombresProd[12] = {
        "Filtro de aceite", "Bujía (unidad)", "Aceite 10W-30 (litro)",
        "Pastillas de freno (juego)", "Disco de freno (unidad)", "Amortiguador (unidad)",
        "Batería 12V", "Alternador", "Bombillo LED (unidad)",
        "Limpiaparabrisas (par)", "Aromatizante", "Cera para auto"
    };
    int unidadesProd[12] = {
        totalUnidades1, totalUnidades2, totalUnidades3,
        totalUnidades4, totalUnidades5, totalUnidades6,
        totalUnidades7, totalUnidades8, totalUnidades9,
        totalUnidades10, totalUnidades11, totalUnidades12
    };

    int maxUnidades = unidadesProd[0];
    string prodMasVendido = nombresProd[0];
    for (int i = 0; i < 12; i++) {
        if (unidadesProd[i] > maxUnidases_o_similar || unidadesProd[i] > maxUnidades) {
            maxUnidades = unidadesProd[i];
            prodMasVendido = nombresProd[i];
        }
    }

    int minConVentas = -1;
    string prodMenosVendido = "Ninguno";
    int minUnidades = 0;
    for (int i = 0; i < 12; i++) {
        if (unidadesProd[i] > 0) {
            if (minConVentas == -1 || unidadesProd[i] < minConVentas) {
                minConVentas = unidadesProd[i];
                prodMenosVendido = nombresProd[i];
            }
        }
    }
    if (minConVentas != -1) minUnidades = minConVentas;

    cout << "1. Producto más vendido: " << prodMasVendido << " (" << maxUnidades << " unidades)[cite: 2, 3]\n";
    cout << "2. Producto menos vendido: " << prodMenosVendido << " (" << minUnidades << " unidades)[cite: 2, 3]\n";
    cout << "3. Ganancia por categoría (total vendido sin ISV)[cite: 2, 3]:\n";
    cout << "   - Motor y Afinación: " << dineroMotorAfinacion << " Lps.\n";
    cout << "   - Frenos y Suspensión: " << dineroFrenosSuspension << " Lps.\n";
    cout << "   - Eléctrico: " << dineroElectrico << " Lps.\n";
    cout << "   - Accesorios: " << dineroAccesorios << " Lps.\n";
    cout << "4. Total descuentos aplicados del día: " << totalDescuentosDia << " Lps.[cite: 3]\n";
    cout << "5. Total ISV recaudado: " << totalIsvDia << " Lps.[cite: 3]\n";
    cout << "6. Total general vendido: " << totalVentasDia << " Lps. / " << (totalVentasDia / 26.42) << " USD[cite: 3]\n";

    string metodoMasUtilizado = "Empate";
    if (contEfectivo > contTransferencia) metodoMasUtilizado = "Efectivo";
    else if (contTransferencia > contEfectivo) metodoMasUtilizado = "Transferencia";
    else metodoMasUtilizado = "Empate entre Efectivo y Transferencia";

    cout << "7. Método de pago más utilizado: " << metodoMasUtilizado << " (Efectivo: " << contEfectivo << ", Transferencia: " << contTransferencia << ")[cite: 3]\n";
    cout << "=======================================================\n";
    cout << "¡Gracias por utilizar el sistema de Auto Repuestos Puma Motor Parts!\n";

    return 0;
}
