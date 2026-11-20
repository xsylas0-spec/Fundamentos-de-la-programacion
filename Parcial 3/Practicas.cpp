#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

struct Alumno {
    int matricula;
    char nombre[50];
    char carrera[50];
    float promedio;
};

bool comparar(Alumno a, Alumno b) {
    return a.promedio > b.promedio;
}

int main() {
    Alumno alumnos[100] = {
        {1012, "Juan", "Sistemas", 9.2},
        {1020, "ismael", "Sistemas", 10.0},
        {1080, "PEDRO", "Mecatronico", 7.0}
    };
    int n = 3;

    // 1- Guardar alumnos en texto
    ofstream archivo("alumnos.txt");
    if (archivo) {
        for (int i = 0; i < n; i++) {
            archivo << alumnos[i].matricula << " "
                    << alumnos[i].nombre << " "
                    << alumnos[i].carrera << " "
                    << alumnos[i].promedio << endl;
        }
        archivo.close();
        cout << "Archivo de texto creado\n";
    } else {
        cout << "Error: no se pudo crear alumnos.txt\n";
    }

    // 2- Leer y reconstruir
    Alumno leidos[100];
    int cantidad = 0;
    ifstream lectura("alumnos.txt");
    if (lectura) {
        while (cantidad < 100 &&
               lectura >> leidos[cantidad].matricula
                       >> leidos[cantidad].nombre
                       >> leidos[cantidad].carrera
                       >> leidos[cantidad].promedio) {
            cantidad++;
        }
        lectura.close();
        cout << "\nDatos leidos:\n";
        for (int i = 0; i < cantidad; i++) {
            cout << leidos[i].matricula << " "
                 << leidos[i].nombre << " "
                 << leidos[i].carrera << " "
                 << leidos[i].promedio << endl;
        }
    } else {
        cout << "\nError: no se pudo abrir alumnos.txt\n";
    }

    // 3- Agregar alumno sin borrar datos
    ofstream agregar("alumnos.txt", ios::app);
    if (agregar) {
        agregar << 1080 << " "
                << "wey" << " "
                << "Mecatronica" << " "
                << 5.0 << endl;
        agregar.close();
        cout << "\nAlumno agregado\n";
    }

    // Volver a leer para que el arreglo incluya al alumno agregado
    cantidad = 0;
    ifstream relectura("alumnos.txt");
    if (relectura) {
        while (cantidad < 100 &&
               relectura >> leidos[cantidad].matricula
                         >> leidos[cantidad].nombre
                         >> leidos[cantidad].carrera
                         >> leidos[cantidad].promedio) {
            cantidad++;
        }
        relectura.close();
    }

    // 4- Guardar en binario
    ofstream binario("alumnos.dat", ios::binary);
    // Escribe el bloque de memoria completo del arreglo en una sola
    // operación: (bytes por struct) * (cantidad de alumnos).
    // El cast a char* es necesario porque write() espera bytes.
    if (binario) {
        binario.write((char*)leidos, sizeof(Alumno) * cantidad);
        binario.close();
    }

    ifstream txt("alumnos.txt", ios::binary);
    txt.seekg(0, ios::end);
    long tamTexto = txt.tellg();
    txt.close();

    ifstream dat("alumnos.dat", ios::binary);
    dat.seekg(0, ios::end);
    long tamBinario = dat.tellg();
    dat.close();

    cout << "\nTamano del archivo texto: "
         << tamTexto << " bytes\n";
    cout << "Tamano del archivo binario: "
         << tamBinario << " bytes\n";

    // 5- Manejo de errores
    ifstream error("archivo_inexistente.txt");
    if (!error) {
        cout << "\nError: el archivo no existe.\n";
    }

    // 6- Generar reporte por promedio
    sort(leidos, leidos + cantidad, comparar);

    ofstream reporte("reporte.txt");
    if (reporte) {
        reporte << "REPORTE ORDENADO POR PROMEDIO\n\n";
        for (int i = 0; i < cantidad; i++) {
            reporte << leidos[i].matricula << " "
                    << leidos[i].nombre << " "
                    << leidos[i].carrera << " "
                    << leidos[i].promedio << endl;
        }
        reporte.close();
        cout << "\nReporte generado\n";
    }

    return 0;
}
