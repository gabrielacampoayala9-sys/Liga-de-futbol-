#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct configLiga {
    string nombre;
    int puntosVictoria;
    int puntosEmpate;
    int puntosDerrota;
    vector<string> grupos;
};
struct partido {
    string fecha;
    string local;
    string visitante;
    int golesLocal; 
    int golesVisitante;
};

struct grupo {
    string nombre;
    int PJ=0, PG=0, PE=0, PP=0;
    int GF=0, GC=0, DG=0, PTS=0;
};

bool leerConfig(configLiga &config) {
    ifstream file("../data/config.txt");
    if (!file) {
        cout << "Error: no se pudo abrir config.txt\n";
        return false;
    }

    string linea;
    while (getline(file, linea)){
        if (linea.empty() || linea[0] == '#') continue;

        string clave, valor; 
        stringstream ss(linea);
        getline(ss, clave, '=');
        getline(ss, valor);

        if (clave == "liga") config.nombre = valor;
        else if (clave == "puntos_victoria") config.puntosVictoria = stoi(valor);
        else if (clave == "puntos_empate")config.puntosEmpate = stoi(valor);
        else if (clave == "puntos_derrota")config.puntosDerrota = stoi(valor);
        else if (clave == "grupo")config.grupos.push_back(valor);

    }

    return true;
}

vector <partido> leerPartidos() {
    vector<partido> partidos;
    ifstream file("../data/partidos.txt");

    if (!file) return partidos;

    string linea;
    while (getline(file, linea)){
        stringstream ss(linea);
        partido p;
        string temp;

        getline(ss, p.fecha, ',');
        getline(ss, p.local,',');
        getline(ss, p.visitante, ',');
        getline(ss, temp, ','); p.golesLocal = stoi(temp);
        getline(ss, temp, ','); p.golesVisitante = stoi(temp);

        partidos.push_back(p);
    }
    return partidos;
}

void guardarPartido(partido p) {
    ofstream file("../data/partidos.txt", ios::app);
    file << p.fecha << "," << p.local << "," << p.visitante << ","
         << p.golesLocal << "," << p.golesVisitante << endl;
}

void actualizarGrupo(grupo *e, int gf, int gc, configLiga config) {
    e->PJ++;
    e->GF += gf;
    e->GC += gc;
    e->DG = e->GF - e->GC;

    if (gf > gc) {
        e->PG++;
        e->PTS += config.puntosVictoria;
    } else if (gf == gc) {
        e->PE++;
        e->PTS += config.puntosEmpate;
    } else {
        e->PP++;
        e->PTS += config.puntosDerrota;
    }

}

vector<grupo> construirTabla(vector<partido> partidos,configLiga config) {
    vector<grupo> tabla;
     
    for (size_t i = 0; i < config.grupos.size(); i++) {
        grupo e;
        e.nombre = config.grupos[i];
        tabla.push_back(e);
    }

    for (size_t i = 0; i < partidos.size(); i++) {
        partido p = partidos[i];

        for (size_t j = 0; j < tabla.size(); j++) {
            grupo &e = tabla[j];

            if (e.nombre == p.local)
                actualizarGrupo(&e, p.golesLocal, p.golesVisitante, config);

            if (e.nombre == p.visitante)
                actualizarGrupo(&e, p.golesVisitante, p.golesLocal, config);
        }
    }

    return tabla;
}




bool comparar (grupo a, grupo b) {
    if (a.PTS != b.PTS) return a.PTS > b.PTS;
    if (a.DG != b.DG) return a.DG > b.DG;
    return a.GF > b.GF;
}

void mostrarTabla(vector<grupo> tabla) {
    sort(tabla.begin(), tabla.end(), comparar);

    cout << "# grupo PJ PG PE PP GF GC DG PTS\n";
    int i = 1;
     
    for (size_t j = 0; j < tabla.size(); j++) {
        grupo g = tabla[j];

        cout << i++ << " " << g.nombre << " "
             << g.PJ << " " << g.PG << " " << g.PE << " "
             << g.PP << " " << g.GF << " " << g.GC << " "
             << g.DG << " " << g.PTS << endl;
    } 
}

void registrarPartido(configLiga config) {
    partido p;

    cout << "Grupos:\n";
    for (int i = 0; i < config.grupos.size(); i++) {
        cout << i << ". " << config.grupos[i] << endl;
    }

    int l, v;
    cout << "Seleccione grupo local: "; cin >> l;
    cout << "Seleccione grupo visitante: "; cin >> v;

    if (l == v) {
        cout << "Error: grupos iguales\n";
        return;
    }

    p.local = config.grupos[l];
    p.visitante = config.grupos[v];

    cout << "Fecha: "; cin >> p.fecha;
    cout << "Goles Local" ; cin >> p.golesLocal;
    cout << "Goles Visitante: "; cin >> p.golesVisitante;

    guardarPartido(p);




}

int menu(string nombre) {
    cout << "\n=== " << nombre << " ===\n";
    cout << "1. Ver tabla\n";
    cout << "2. Registrar partido\n";
    cout << "3. Salir\n";
    cout << "Opcion: ";
    int op; cin >> op;
    return op;

}

int main() {
    configLiga config;

    if (!leerConfig(config)) return 1;

    int op;
    do {
        op = menu(config.nombre);

       if (op == 1) {
            vector<partido> partidos = leerPartidos();
            vector<grupo> tabla = construirTabla(partidos, config);
            mostrarTabla(tabla);
        }
        else if (op == 2) {
            registrarPartido(config);
        }
   
   
    } while (op != 3);

    return 0;
    
}
