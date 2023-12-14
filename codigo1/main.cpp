#include <algorithm>
#include <bits/stdc++.h>
#include <iostream>
#include <vector>

using namespace std;

int cantidadProcesos;
vector<int> procesos;
vector<int> arrivalTime;
vector<int> burstTime;
vector<int> waitingTime;
double turnaroundTime;
int quantumTime; // para RR

void simuladorFCFS() {
  int indice;
  vector<int>::iterator it;
  vector<int> auxVprocesos = procesos;
  vector<int> auxVarrivalTime = arrivalTime;
  vector<int> auxVburstTime = burstTime;
  sort(auxVarrivalTime.begin(), auxVarrivalTime.end());

  for (int i = 0; i < cantidadProcesos; i++) {
    it = find(arrivalTime.begin(), arrivalTime.end(), auxVarrivalTime[i]);
    indice = it - arrivalTime.begin();
    procesos[i] = auxVprocesos[indice];
    burstTime[i] = auxVburstTime[indice];
  }

  arrivalTime = auxVarrivalTime;

  //Calculo tiempo de espera
  //int waitingTimeTotal = 0;
  int tiempoAcumuladoBurst = 0;
  waitingTime.push_back(0);
  for (int i = 1; i < cantidadProcesos; i++){
    tiempoAcumuladoBurst = tiempoAcumuladoBurst + burstTime[i-1];
    waitingTime.push_back(tiempoAcumuladoBurst - arrivalTime[i]);
  }

  cout << "Proceso\t arrivalTime\t burstTime\t waitingTime" << endl;

  for (int i = 0; i < cantidadProcesos; i++) {
    cout << procesos[i] << "\t" << arrivalTime[i] << "\t" << burstTime[i] << "\t" << waitingTime[i] << endl;
  }

  //Calculo del turnAroundTime
  turnaroundTime = 0;
  for (int i = 1; i < cantidadProcesos; i++){
      turnaroundTime = turnaroundTime + burstTime[i-1];
  }

  turnaroundTime = turnaroundTime/cantidadProcesos;

  cout << "promedio de turnaroundTime: " << turnaroundTime <<endl;

  int aux=0;
  for(int i = 0 ; i < cantidadProcesos; i++){
    aux= aux + waitingTime[i];
  }

  cout << "promedio de waitingTime: "<< aux/cantidadProcesos <<endl;
  
}




void simuladorSJN() {
  int indice;
  vector<int>::iterator it;
  vector<int> auxVprocesos = procesos;
  vector<int> auxVarrivalTime = arrivalTime;
  vector<int> auxVburstTime = burstTime;
  sort(auxVarrivalTime.begin(), auxVarrivalTime.end());

  for (int i = 0; i < cantidadProcesos; i++) {
    it = find(arrivalTime.begin(), arrivalTime.end(), auxVarrivalTime[i]);
    indice = it - arrivalTime.begin();
    procesos[i] = auxVprocesos[indice];
    burstTime[i] = auxVburstTime[indice];
  }

  arrivalTime = auxVarrivalTime;

  //Calculo tiempo de espera
  //int waitingTimeTotal = 0;
  int tiempoAcumuladoBurst = 0;
  waitingTime.push_back(0);
  for (int i = 1; i < cantidadProcesos; i++){
    tiempoAcumuladoBurst = tiempoAcumuladoBurst + burstTime[i-1];
    waitingTime.push_back(tiempoAcumuladoBurst - arrivalTime[i]);
  }

  cout << "Proceso\t arrivalTime\t burstTime\t waitingTime" << endl;

  for (int i = 0; i < cantidadProcesos; i++) {
    cout << procesos[i] << "\t" << arrivalTime[i] << "\t" << burstTime[i] << "\t" << waitingTime[i] << endl;
  }

  //Calculo del turnAroundTime
  int burstTimeTotal = 0;
  int turnaroundTimeTotal = 0;
  for (int i = 0; i < cantidadProcesos; i++){
    burstTimeTotal = burstTimeTotal + burstTime[i];
      turnaroundTimeTotal = turnaroundTimeTotal + 
 (burstTimeTotal- arrivalTime[i]);
  }

  turnaroundTime = turnaroundTimeTotal/cantidadProcesos;

  cout << "promedio de turnaroundTime: " << turnaroundTime <<endl;

  int aux=0;
  for(int i = 0 ; i < cantidadProcesos; i++){
    aux= aux + waitingTime[i];
  }

  cout << "promedio de waitingTime: "<< aux/cantidadProcesos <<endl;

  
}

void simuladorRR() {}

int main() {
  int aux;
  cout << "Dar cantidad de procesos: ";
  cin >> cantidadProcesos;

  for (int i = 0; i < cantidadProcesos; i++) {
    procesos.push_back(i+1);
    cout << "Ingrese el tiempo de arrivalTime del Proceso " << i + 1 << ": ";
    cin >> aux;
    arrivalTime.push_back(aux);

    cout << "Ingrese el tiempo de burstTime del Proceso" << i + 1 << ": ";
    cin >> aux;
    burstTime.push_back(aux);
  }

  cout << "Ingrese quantum de tiempo para Round Robin: ";
  cin >> quantumTime;

  cout << endl;
  cout << "Simulacion resultados para algoritmo FCFS:" << endl;
  simuladorFCFS();
  cout << endl;
  cout << "Simulacion resultados para algoritmo SJN:" << endl;
  simuladorSJN();
  cout << endl;
  cout << "Simulacion resultados para algoritmo Robin:" << endl;
  simuladorRR();

  return 0;
}
