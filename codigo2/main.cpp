/*
Integrantes:
Marvin Nuñez
Xavier Lopez
Daniel
Kevin
*/


#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Proceso {
  int id, tiempoSubida, tiempoRafaga, 
      tiempoRestante, tiempoRespuesta, tiempoEspera;
};

//------------------TODOS LOS RESULTADOS CALCULADOS EN LAS FUNCIONES DE ABAJO---------------
void mostrarResultados(const vector<Proceso>& procesos) {
  double tiempoTotalEspera = 0;
  double tiempoTotalRespuesta = 0;

  cout << endl;
  cout << "Procesos\tTiempo de subida\tTiempo de rafaga\tTiempo de espera\tTiempo de respuesta" <<endl;

  for (const auto& process : procesos) {
      tiempoTotalEspera += process.tiempoEspera;
      tiempoTotalRespuesta += process.tiempoRespuesta;

    cout << process.id << "\t\t" << process.tiempoSubida << "\t\t" << process.tiempoRafaga << "\t\t"<< process.tiempoEspera << "\t\t" << process.tiempoRespuesta << endl;
    }

  double tiempoPromedioEspera = tiempoTotalEspera/procesos.size();
  double tiempoPromedioRespuesta = tiempoTotalRespuesta/procesos.size();

  cout<<endl;
  cout << "Tiempo Promedio de Espera: " << tiempoPromedioEspera << endl;
  cout << "Tiempo Promedio de Respuesta: " << tiempoPromedioRespuesta << endl;
}


void calcularTiempoEsperaTiempoRespuesta(vector<Proceso>& procesos) {
  procesos[0].tiempoRespuesta = procesos[0].tiempoRafaga;
  procesos[0].tiempoEspera = 0;

  for (size_t i = 1; i < procesos.size(); i++) {
    procesos[i].tiempoRespuesta = procesos[i-1].tiempoRespuesta + procesos[i].tiempoRafaga;
    procesos[i].tiempoEspera = procesos[i].tiempoRespuesta - procesos[i].tiempoSubida;
  }
}


void simuladorFCFS(vector<Proceso>& procesos) {
  sort(procesos.begin(), procesos.end(), [](const Proceso& a, const Proceso& b) {
    return a.tiempoSubida < b.tiempoSubida;
  });

  calcularTiempoEsperaTiempoRespuesta(procesos);
  mostrarResultados(procesos);
}

void simuladorSJN(vector<Proceso>& procesos) {
  sort(procesos.begin(), procesos.end(), [](const Proceso& a, const Proceso& b) {
    return a.tiempoRafaga < b.tiempoRafaga;
  });

  calcularTiempoEsperaTiempoRespuesta(procesos);
  mostrarResultados(procesos);
}

void simuladorRR(vector<Proceso>& procesos, int quantumTime) {
  queue<int> readyQueue;
  int tiempoActual = 0;

  for (auto& process : procesos) {
    process.tiempoRestante = process.tiempoRafaga;
  }

  int procesoActual = 0;
  int procesosCompletados = 0;

  while (procesosCompletados < procesos.size()) {
    if (procesos[procesoActual].tiempoRestante > 0) {
      int tiempoEjecutado = min(quantumTime, procesos[procesoActual].tiempoRestante);
      procesos[procesoActual].tiempoRestante -= tiempoEjecutado;
      tiempoActual += tiempoEjecutado;

      if (procesos[procesoActual].tiempoRestante == 0) {
                procesosCompletados++;
                procesos[procesoActual].tiempoRespuesta = tiempoActual - procesos[procesoActual].tiempoSubida;
            }

            while (procesoActual < procesos.size() && procesos[procesoActual].tiempoSubida <= tiempoActual) {
                readyQueue.push(procesoActual);
                procesoActual++;
            }
        } else {
            procesoActual++;
        }

        if (!readyQueue.empty()) {
            int proximoProceso = readyQueue.front();
            readyQueue.pop();
            readyQueue.push(procesoActual);
            procesoActual = proximoProceso;
        }
    }

    for (auto& process : procesos) {
        process.tiempoEspera = process.tiempoRespuesta - process.tiempoRafaga;
    }

    mostrarResultados(procesos);
}

int main() {

    int n, quantumTime;

    cout << "Dar cantidad de procesos: ";
    cin >> n;

    vector<Proceso> procesos(n);

    for (int i = 0; i < n; i++) {
        procesos[i].id = i + 1;
        cout << "Ingrese el tiempo de llegada del Proceso" << i+1 << ": ";
        cin >> procesos[i].tiempoSubida;
        cout << "Ingrese el tiempo de subida del Proceso" << i + 1 << ": ";
        cin >> procesos[i].tiempoRafaga;
    }


  cout << endl;
  cout << "Simulacion resultados para algoritmo FCFS:" << endl;
  simuladorFCFS(procesos);
  cout << endl;
  cout << "Simulacion resultados para algoritmo SJN:" << endl;
  simuladorSJN(procesos);
  cout << endl;
  cout << "Ingrese quantum de tiempo para Round Robin: ";
  cin >> quantumTime;
  cout << endl;
  cout << "Simulacion resultados para algoritmo Robin:" << endl;
  simuladorRR(procesos, quantumTime);

  return 0;
}
