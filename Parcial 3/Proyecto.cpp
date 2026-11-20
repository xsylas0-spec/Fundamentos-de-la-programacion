#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

struct Alumno  { string nombre; string matricula; float calif[3]; int grupo; double promedio; };
struct Maestro { string nombre; string materia; };
struct Grupo   { string nombre; string carrera; int num_grupo; };

// funcion para calcular promedio sin repertir 
double calcularPromedio(const Alumno& a) {
    return (a.calif[0] + a.calif[1] + a.calif[2]) / 3.0;
}

int main() {
    int opcion = 0; int n, zz;
    // n se usa para capturar cantidad de alumnos, maestros o grupos y para leer del archivo de datos.txt
    // zz se usa para capturar grupos y que no se repitan los nombres de los
    vector<Alumno> alumno; vector<Maestro> maestro; vector<Grupo> grupo;

    bool inicio = true;   // la primea vez que se ejecuta el menu, 
    //se carga el archivo de datos.txt automaticamente

    do {
        if (inicio) { // coso super importante que hace que cargue la informacion del los datos.txt
            opcion = 6;
            cout << "Primero se usa la opcion 5 para cargar los datos del archivo datos.txt\n";
            cout << "Despues en la opcion 6 se puede cargar el archivo de datos.txt manualmente\n";
            inicio = false;
        } else {
            cout << "\n--- MENU PRINCIPAL ---\n";
            cout << "1. Capturar Alumnos\n";
            cout << "2. Capturar grupos y carreras\n";
            cout << "3. Capturar maestros\n";
            cout << "4. Mostrar Reportes\n";
            cout << "5. Guardar datos en archivo\n";
            cout << "6. Cargar datos del archivo\n";
            cout << "7. Generar reporte de texto (por promedio) y guardar\n";
            cout << "8. Guardar y salir\n";
            cin >> opcion;

            // para cerrar el prograrma con Ctrl+D
            if (cin.eof()) break;

            // Si escriben letras en el menu, evita el ciclo infinito
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Opcion invalida.\n";
                opcion = 0;
                continue;
            }
        }

        switch (opcion)
        {
        case 1: {
            // No se pueden capturar alumnos sin grupos (evita salirse de rango)
            if (grupo.empty()) {
                cout << "Primero captura al menos un grupo.\n";
                break;
            }
            cout << "Cuantos alumnos son?" << endl;
            cin >> n;
            if (cin.eof()) return 0;
            if (cin.fail() || n < 1) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Cantidad invalida.\n";
                break;
            }
            for (int i = 0; i < n; i++) {
                Alumno a;

                cout << "Nombre del alumno " << i+1 << ": ";
                getline(cin >> ws, a.nombre);
                cout << "Matricula " << i+1 << ": ";
                getline(cin >> ws, a.matricula); // cambios de getline para espacions

                cout << "calificaciones\n";
                for (int o = 0; o < 3; o++) {
                    while (true) {
                        cout << "Calificacion " << o+1 << ": ";
                        cin >> a.calif[o];
                        if (cin.eof()) return 0;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(10000, '\n');
                            cout << "No puede ingresar letras.\n";
                        } else if (a.calif[o] < 0 || a.calif[o] > 100) {
                            cout << "La calificacion debe estar entre 0 y 100.\n";
                        } else {
                            break;
                        }
                    }
                }

                // pa ver si existe un grupo
                while (true) {
                    cout << "Grupo (1-" << grupo.size() << "): ";
                    cin >> a.grupo;
                    if (cin.eof()) return 0;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Ingrese un numero.\n";
                    } else if (a.grupo < 1 || a.grupo > (int)grupo.size()) {
                        cout << "Ese grupo no existe.\n";
                    } else {
                        break;
                    }
                }

                a.promedio = calcularPromedio(a);
                alumno.push_back(a);
            }
            break;
        }
        case 2:
            cout << "Cuantos grupos quieres capturar? ";
            cin >> n;
            if (cin.eof()) return 0;
            if (cin.fail() || n < 1) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Cantidad invalida.\n"; //mas verificaciones
                break;
            }
            zz = grupo.size();
            for (int i = zz; i < zz + n; i++) {  //zz 
                Grupo g;
                cout << "Nombre del grupo " << i+1 << ": ";
                getline(cin >> ws, g.nombre);
                cout << "Carrera del grupo " << i+1 << ": ";
                getline(cin >> ws, g.carrera);
                g.num_grupo = i+1;
                grupo.push_back(g);
            }
            break;

        case 3:
            cout << "Cuantos maestros quieres capturar? ";
            cin >> n;
            if (cin.eof()) return 0;
            if (cin.fail() || n < 1) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Cantidad invalida.\n";  //mas verificaciones
                break;
            }
            for (int i = 0; i < n; i++) {
                Maestro m;
                cout << "Nombre del maestro " << i+1 << ": ";
                getline(cin >> ws, m.nombre);
                cout << "Materia que imparte: ";
                getline(cin >> ws, m.materia);
                maestro.push_back(m);
            }
            break;

        case 4: { //reporte en cosola
            if (alumno.empty()) {
                cout << "No hay alumnos capturados.\n";
                break;
            }

            cout << "\n--Reporte--" << endl;

            // Promedio de cada alumno
            cout << "\n-- Promedio de cada alumno --\n";
            for (size_t i = 0; i < alumno.size(); i++) {
                alumno[i].promedio = calcularPromedio(alumno[i]);
                cout << alumno[i].nombre << " (" << alumno[i].matricula << "): ";
                cout << alumno[i].promedio << endl;
            }

            // Mejor promedio por grupo
            cout << "\n-- Mejor promedio por grupo --\n";
            for (size_t g = 0; g < grupo.size(); g++) {
                int mejor = -1;
                for (size_t i = 0; i < alumno.size(); i++) {
                    if (alumno[i].grupo == (int)g + 1) {
                        if (mejor == -1 || alumno[i].promedio > alumno[mejor].promedio)
                            mejor = i;
                    }
                }
                cout << grupo[g].nombre << ": ";
                if (mejor == -1) cout << "sin alumnos\n";
                else cout << alumno[mejor].nombre << " (" << alumno[mejor].promedio << ")\n";
            }

            // Alumnos por carrera
            cout << "\n-- Alumnos por carrera --\n";
            vector<string> carreras;
            vector<int> cuenta;
            for (size_t i = 0; i < alumno.size(); i++) {
                string car = grupo[alumno[i].grupo - 1].carrera;
                bool encontrada = false;
                for (size_t c = 0; c < carreras.size(); c++) {
                    if (carreras[c] == car) { cuenta[c]++; encontrada = true; break; }
                }
                if (!encontrada) { carreras.push_back(car); cuenta.push_back(1); }
            }
            for (size_t c = 0; c < carreras.size(); c++)
                cout << carreras[c] << ": " << cuenta[c] << endl;
            break;
        }

        

        // Cargar datos del archivo al inicio y durante el programa 
        case 6: {
            ifstream in("datos.txt");
            if (!in) {
                // la primeravez que ejecuta el programa, no hay datos.txt
                cout << "No hay datos guardados todavia. Se trabaja con datos vacios.\n";
                break;
            }
            //Estructura de datos.txt

            // cantidad de grupos
            // nombre del grupo
            // carrera del grupo
            
            // cantidad de maestros
            // nombre del maestro
            // materia del maestro

            // cantidad de alumnos
            // nombre del alumno
            // matricula del alumno
            // calificacion1 calificacion2 calificacion3 grupo

            // vectores temportales
            vector<Grupo> g2; vector<Maestro> m2; vector<Alumno> a2;
            bool ok = true;

            in >> n; //Lee el primer dato que hay en el txt
            in.ignore(numeric_limits<streamsize>::max(), '\n'); // ignora hasta el enter
            // lee la cantidad de grupos y los guarda en el vector temporal
            for (int i = 0; i < n && in; i++) { // lee la cantidad de grupos y los guarda en el vector temporal
                Grupo g;
                getline(in, g.nombre);
                getline(in, g.carrera);
                g.num_grupo = i+1;
                g2.push_back(g);
            } // con getline consigue los datos 
            //Entonces una vez que sabe cuantos grupos hay lee linea por linea y los guarda en el vector temporal
            // lo mismo para maestros y alumnos

            in >> n;
            in.ignore(numeric_limits<streamsize>::max(), '\n');
            for (int i = 0; i < n && in; i++) {
                Maestro m;
                getline(in, m.nombre);
                getline(in, m.materia);
                m2.push_back(m);
            } // con getline consigue los datos

            in >> n;
            in.ignore(numeric_limits<streamsize>::max(), '\n');
            for (int i = 0; i < n && in; i++) {
                Alumno a;
                getline(in, a.nombre);
                getline(in, a.matricula);
                in >> a.calif[0] >> a.calif[1] >> a.calif[2] >> a.grupo;
                in.ignore(numeric_limits<streamsize>::max(), '\n');
                if (!in || a.grupo < 1 || a.grupo > (int)g2.size()) { ok = false; break; }
                a.promedio = calcularPromedio(a);
                a2.push_back(a);
            }

            if (!in || !ok) {
                cout << "El archivo datos.txt esta danado o incompleto. No se cargo nada.\n";
                break;
            }

            grupo = g2; maestro = m2; alumno = a2;
            cout << "Datos cargados: " << grupo.size() << " grupos, "
                 << maestro.size() << " maestros, " << alumno.size() << " alumnos.\n";
            break;
        }

        // reporte de texto por promedio y guardar datos
        case 7: {
            if (alumno.empty()) {
                cout << "No hay alumnos para el reporte.\n";
                break;
            }

            // ordenada de mayor a menor promedio
            vector<Alumno> ordenados = alumno;
            for (size_t i = 0; i < ordenados.size() - 1; i++) {
                for (size_t j = 0; j < ordenados.size() - 1 - i; j++) {
                    if (calcularPromedio(ordenados[j]) < calcularPromedio(ordenados[j+1])) {
                        Alumno temp = ordenados[j];
                        ordenados[j] = ordenados[j+1];
                        ordenados[j+1] = temp;
                    }
                }
            }

            ofstream rep("reporte.txt");
            if (!rep) {
                cout << "No se pudo crear reporte.txt.\n";
                break;
            }

            // Formato del reporte.txt: tabla con columnas alineadas
            rep.setf(ios::left);
            rep << "REPORTE DE ALUMNOS (ordenado por promedio, de mayor a menor)\n";
            rep << string(78, '=') << "\n"; // este es para darle "estetica al reporte"
            rep.width(5);  rep << "#"; 
            rep.width(24); rep << "Nombre";
            rep.width(12); rep << "Matricula";
            rep.width(18); rep << "Grupo";
            rep << "Promedio\n";
            rep << string(78, '-') << "\n";
            //esta parte tube que buscar porque ni idea como hacer un reporte de texto decente

            rep.setf(ios::fixed);
            rep.precision(2);
            for (size_t i = 0; i < ordenados.size(); i++) {
                rep.width(5);  rep << i+1;
                rep.width(24); rep << ordenados[i].nombre;
                rep.width(12); rep << ordenados[i].matricula;
                rep.width(18); rep << grupo[ordenados[i].grupo - 1].nombre;
                rep << calcularPromedio(ordenados[i]) << "\n";
            }

            cout << "Reporte generado en reporte.txt.\n";
        }

         case 8:  // SALIR Y GUARDAR
         case 5: { // guardar datos en archivo de datos.txt
            ofstream out("datos.txt");
            if (!out) {
                cout << "No se pudo abrir datos.txt para guardar.\n";
                break;
            }

            out << grupo.size() << "\n";
            for (size_t i = 0; i < grupo.size(); i++)
                out << grupo[i].nombre << "\n" << grupo[i].carrera << "\n";

            out << maestro.size() << "\n";
            for (size_t i = 0; i < maestro.size(); i++)
                out << maestro[i].nombre << "\n" << maestro[i].materia << "\n";

            out << alumno.size() << "\n";
            for (size_t i = 0; i < alumno.size(); i++) {
                out << alumno[i].nombre << "\n" << alumno[i].matricula << "\n";
                out << alumno[i].calif[0] << " " << alumno[i].calif[1] << " "
                    << alumno[i].calif[2] << " " << alumno[i].grupo << "\n";
            }

            if (!out) cout << "Error al escribir en datos.txt.\n";
            else cout << "Datos guardados en datos.txt.\n";
            break;
            
        }
        default:
            if (opcion != 8) cout << "Opcion invalida.\n";
            break;
        }

    } while (opcion != 8);
    return 0;
}