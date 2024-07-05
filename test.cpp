#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "general.h"
#include "database.h"

int main()
{
  // Crear algunos registros de ejemplo
  std::vector<Person> persons = {
      {1000000, "Alice", "Smith", "Peru", {"Lima", "Lima", "Ate", "City1"}, "123456789", "a@a.com", "Single"}};

  // Escribir los registros en un archivo binario
  std::string filename = "persons.dat";
  database_cpp::Database::writePersons(persons, filename);
  std::cout << "Personas escritas en el archivo: " << filename << std::endl;

  // Leer los registros desde el archivo binario
  std::vector<Person> readPersonsList = database_cpp::Database::readPersons(filename);

  // Imprimir los registros leídos
  for (const auto &person : readPersonsList)
  {
    std::cout << person.dni << " " << person.name << " " << person.lastName << " " << person.nationality << std::endl;
  }

  return 0;
}