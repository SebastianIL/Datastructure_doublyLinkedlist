

#include <cstddef>
#include <iostream>
#include <time.h>
#include <string.h>
using namespace std;
#include <fstream>
#include <sstream>
#include "lista.h"
#include "persona.h"
template<typename T>
void merge(LinkedList<T>&lista, int low, int high, int mid)
{

  int n1 = high - low + 1;
  int n2 = mid - high;

  T L[n1], M[n2];

  for (int i = 0; i < n1; i++)
    L[i] = lista.get(low + i);
  for (int j = 0; j < n2; j++)
    M[j] = lista.get(high + 1 + j);

 
  int i, j, k;
  i = 0;
  j = 0;
  k = low;


  while (i < n1 && j < n2) {
    if (L[i] < M[j]) {
      lista.set(k,L[i]);
      i++;
    } else {
      lista.set(k,M[j]);
      j++;
    }
    k++;
  }

  while (i < n1) {
    lista.set(k,L[i]);
    i++;
    k++;
  }

  while (j < n2) {
    lista.set(k,M[j]);
    j++;
    k++;
  
  }
  return;
}


template<typename T>
void mergeSort(LinkedList<T> &lista, int low, int high)
 {
  if (low < high) {

    int m = low + (high - low) / 2;

    mergeSort<T>(lista, low, m);
    mergeSort<T>(lista, m + 1, high);
    merge<T>(lista, low, m, high);
  }

}

template<typename T, typename S>
int busquedaSecuencial(Queue<Persona> & lista, S busco)
{
  int posicion = 0;
  for(int i=0; i< lista.size();i++){
    Persona obtained = lista.get(i);
    if(obtained.getLastName()==busco){
      posicion=i;
    }
  }
  return posicion;
}

template<typename T, typename S>
int busquedaBin(LinkedList<T> & lista, S x, int low, int high){
   int mid; 
   if (low < high) {
     mid = (low + high) / 2; 
     //Persona find =lista.get(mid);
      if (x == lista.get(mid)){
       return mid;
      }
      else if (x >= lista.get(mid)) {    
        return busquedaBin(lista, x, mid + 1, high);
      }
      else {                      // x is on the right side
        return busquedaBin(lista, x, low, mid - 1);
    }
  } else
     return false;
}

  

int main(int argc, char * argv[]) {

  cout<<argv[0]<<endl;
  cout<<argv[1]<<endl;
  
  // Lectura de archivo.
  Queue<Persona> personas;
  
  ifstream myFile;    
  myFile.open(argv[1]); // O(1)
    string line; // O(1)
   getline(myFile,line);
  // Lectura de lineas y separacion de datos
    while (getline(myFile,line)) {
      
        
      string id, first_name, last_name, zip, city;

        id= line.substr(0,line.find(','));
        line= line.substr(line.find(',')+1,line.size());
        first_name= line.substr(0,line.find(','));
        line= line.substr(line.find(',')+1,line.size());
        last_name = line.substr(0,line.find(','));
        line= line.substr(line.find(',')+1,line.size());
        zip= line.substr(0,line.find(','));
        line= line.substr(line.find(',')+1,line.size());
        city= line.substr(0,line.find(','));
        line= line.substr(line.find(',')+1,line.size());
        

      stringstream ss;
      int id_;
      int zip_;
      ss<<id;ss >> id_;
      stringstream ds;
      ds<<zip;ds>>zip_;
      Persona persona = Persona(id_,zip_,first_name,last_name,city);
      personas.addLast(persona);
      
    }
  // O(n)
    myFile.close(); // O(1)

    
    //¿Cuáles son las cinco ciudades con mayor número de personas registradas?

  LinkedList<string> allCities;
LinkedList<City> ordC;
  for(int i =0; i<personas.size(); i++){
    Persona persona = personas.get(i);   
    allCities.addLast(persona.getCity());
  }
  mergeSort(allCities, 0, allCities.size()-1);

  for (int n =0; n<allCities.size()-1; n++){
    int x=0;
    int i=n;
      while(n<allCities.size() && allCities.get(n)==allCities.get(i)){
        n++;
        x++;          
      }    
  ordC.addLast(City(allCities.get(i),x));
  }

  Queue<int> population;
  for(int i =0; i<ordC.size(); i++){
    City c = ordC.get(i);   
    population.enqueue(c.getPopulation());
  }
  cout<<"Estas son las 5 ciudades con mayor población: "<<endl;
  for(int i=0;i<5;i++){
    City  fc = ordC.remove(population.getMax());
    population.dequeueMax();
    cout<<fc<<endl;
  }

  cout<<"Complejidad del ejercicio 1: "<<endl<<"   Mejor caso: O(n)"<<endl<<"   Peor caso: O(n^2)"<<endl<<endl;
  
  // Pregunta al usuario un nombre “first_name” y debes imprimir ¿Con qué frecuencia se repite ese nombre en la lista ligada?
  string name;
  cout<<"Que nombre quieres buscar?"<<endl;
  cin>>name;
  int counter=0;
  for (int i = 0; i<personas.size();i++){
    Persona obtained = personas.get(i);
    if(obtained.getFirstName()==name){
      counter++;
    }
  }
  cout<<"Esta nombre se encuentra "<<counter<<" veces"<<endl<<endl;

  cout<<"Complejidad del ejercicio 2: "<<endl<<"   Mejor caso: O(n)"<<endl<<"   Peor caso: O(n)"<<endl<<endl;
  
  // ¿Cuántos habitantes existen por ciudad?
  string op;
  cout<<"¿Quiere saber cuantos habitantes hay por ciudad? (si/no)"<<endl;
  cin>>op;
  if(op=="si"){
    ordC.print();
    }

  cout<<"Complejidad del ejercicio 3: "<<endl<<"   Mejor caso: O(1)"<<endl<<"   Peor caso: O(1)"<<endl<<endl;
  // Muestra ordenada la lista ligada, utilizando el last_name como atributo para ordenar. ¿Qué método de ordenamiento utilizarás y por qué?
  cout<<"Presione cualquier tecla para continuar con el ordenamiento por apellidos"<<endl;
  system("pause");
  mergeSort<Persona>(personas, 0, personas.size()-1);
  personas.print();    
  cout<<"Complejidad del ejercicio 4: "<<endl<<"   Mejor caso: O(n)"<<endl<<"   Peor caso: O(nlog(n))"<<endl<<endl;
  
  // Implementa la búsqueda binaria para encontrar una persona, utilizando  el last_name como atributo para buscar.
  cout<<"Elija el apellido de la persona que desea buscar"<<endl;
  string lasttemp;
  cin>> lasttemp;
  //int busq = busquedaSecuencial<Persona,string>(personas, lasttemp);
  LinkedList<string> allLnames;
  for(int i =0; i<personas.size(); i++){
    Persona persona = personas.get(i);   
    allLnames.addLast(persona.getLastName());
  }
  
  mergeSort(allLnames, 0, allLnames.size()-1);
  int busq2;
  busq2= busquedaBin<string,string>(allLnames, lasttemp, 0, allLnames.size());
  //Persona busquedacomp = personas.get(busq);
  Persona busquedacomp2 = personas.get(busq2);
  cout<<busquedacomp2<<" "<<busq2<<endl;
  cout<<"Complejidad del ejercicio 5: "<<endl<<"   Mejor caso: O(1)"<<endl<<"   Peor caso: O(log(n))"<<endl<<endl;

  
}
