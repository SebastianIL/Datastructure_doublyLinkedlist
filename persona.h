#include <cstddef>
#include <iostream>
using namespace std;

class Persona{
  private:
    string first_name,last_name,city;
    int id, zip;
  public:
    
      Persona(int id = 0, int zip = 0, string fname = "", string lname = "", string city = ""){
        this->id = id;
        this->zip = zip;
        this->first_name = fname;
        this->last_name = lname;
        this->city = city;
      }
    string getCity(){
      return city;
    }
    string getFirstName(){
      return first_name;
    }
    string getLastName(){
      return last_name;
    }
    

/*
Agrega las sobre cargas de operadores necesarias en la clase Persona.
*/
 bool operator>(const Persona & persona){
      return (this->last_name >= persona.last_name);
    }

bool operator<(const Persona & persona){
      return ( this->last_name <= persona.last_name);
    } 

friend ostream & operator<<( ostream &, const Persona &);

};

class City{
  private:
    string name;
    int population;
  public:

    City(string _name = " ", int _pop=0){
      name=_name;
      population=_pop;
    }
    int getPopulation(){
      return population;
    }
friend ostream & operator<<( ostream &, const City &);
};

ostream & operator<< (ostream & salida, const Persona & persona){
      
  salida<<to_string(persona.id)<<" "<<to_string(persona.zip)<<" "<<persona.first_name<<" "<<persona.last_name<<" "<<persona.city;
  return salida;
} 

ostream & operator<< (ostream & salida, const City & city){
      
  salida<<"City: "<<city.name<<endl<<"   Población "<<to_string(city.population)<<endl;
  return salida;
} 