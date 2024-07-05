#include <iostream>
#include <vector>
#include <chrono>
#include "general.h"
#include "management.h"
#include "colors.h"
#include "generate.h"

// vector<Person> persons;

int main()
{
  std::vector<std::vector<Person>> personsList;

  std::cout << std::endl;
  std::cout << BLACK << BG_GREEN << "*************** Sistema de Registro Nacional ***************" << RESET << std::endl;
  std::cout << std::endl;

  auto start = std::chrono::high_resolution_clock::now();
  std::cout << "Proceso iniciado" << std::endl;
  management_cpp::Management::prepareData(personsList);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::cout << "Preparado en " << elapsed.count() << " seconds. " << personsList.size() << " registros leidos." << std::endl;
  while (true)
  {
    std::cout << GREEN << "============================" << RESET << std::endl;
    std::cout << GREEN << "Seleccione la opcion deseada" << RESET << std::endl;
    std::cout << GREEN << "============================" << RESET << std::endl;
    std::cout << YELLOW << "[1] Generar datos de prueba" << RESET << std::endl;
    std::cout << YELLOW << "[2] Gestionar registro" << RESET << std::endl;
    std::cout << RED << "[3] Salir" << RESET << std::endl;
    std::cout << GREEN << "============================" << RESET << std::endl;
    int option;
    std::cout << "Opcion: ";
    std::cin >> option;
    std::cout << GREEN << "============================" << RESET << std::endl;
    if (option == 1)
    {
      std::cout << GREEN << "============================" << RESET << std::endl;
      std::cout << GREEN << "Ingrese la cantidad de registros a generar" << RESET << std::endl;
      std::cout << GREEN << "============================" << RESET << std::endl;
      std::cout << "Cantidad: ";
      int totalRecords;
      std::cin >> totalRecords;
      std::cout << GREEN << "============================" << RESET << std::endl;
      std::cout << "Generando..." << std::endl;
      start = std::chrono::high_resolution_clock::now();
      std::cout << "Proceso iniciado" << std::endl;
      generate_data::Generate::start(totalRecords);
      std::cout << "Proceso preparando los datos" << std::endl;
      management_cpp::Management::prepareData(personsList);
      end = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> elapsed = end - start;
      std::cout << "Preparado en " << elapsed.count() << " seconds." << std::endl;
    }
    else if (option == 2)
    {
      while (true)
      {
        std::cout << GREEN << "============================" << RESET << std::endl;
        std::cout << GREEN << "Seleccione una operacion" << RESET << std::endl;
        std::cout << GREEN << "============================" << RESET << std::endl;
        std::cout << YELLOW << "[1] Buscar por DNI" << RESET << std::endl;
        std::cout << YELLOW << "[2] Crear nuevo registro" << RESET << std::endl;
        std::cout << YELLOW << "[3] Eliminar registro" << RESET << std::endl; // Nueva opción añadida
        std::cout << RED << "[4] Salir" << RESET << std::endl;
        std::cout << GREEN << "============================" << RESET << std::endl;
        std::cout << "Opcion: ";
        std::cin >> option;
        std::cout << GREEN << "============================" << RESET << std::endl;
        if (option == 1)
        {
          int dni;
          std::cout << "DNI: ";
          std::cin >> dni;
          std::cout << GREEN << "============================" << RESET << std::endl;
          Person person = management_cpp::Management::findByDNI(personsList, dni);
          if (person.dni != 0)
          {
            std::cout << "Registro encontrado:" << std::endl;
            std::cout << "DNI: " << person.dni << std::endl;
            std::cout << "Nombre: " << person.name << std::endl;
            std::cout << "Nacionalidad: " << person.nationality << std::endl;
            std::cout << "Dirección: " << person.address.department << ", " << person.address.province << ", " << person.address.district << ", " << person.address.city << std::endl;
            std::cout << "Telefono: " << person.phoneNumber << std::endl;
            std::cout << "Email: " << person.email << std::endl;
            std::cout << "Estado Civil: " << person.civilStatus << std::endl;
          }
          else
          {
            std::cout << "Registro no encontrado." << std::endl;
          }
        }
        else if (option == 2)
        {
          Person newPerson = Person();
          std::string _dni = "";
          std::cout << "DNI: ";
          std::cin >> _dni;
          newPerson.dni = std::stoi(_dni);
          getline(std::cin, newPerson.name);
          std::cout << "Nombre: ";
          std::cin;
          getline(std::cin, newPerson.name);
          std::cout << "Apellido: ";
          std::cin;
          getline(std::cin, newPerson.lastName);
          std::cout << "Nacionalidad: ";
          std::cin;
          getline(std::cin, newPerson.nationality);
          std::cout << "Departamento: ";
          std::cin;
          getline(std::cin, newPerson.address.department);
          std::cout << "Provincia: ";
          std::cin;
          getline(std::cin, newPerson.address.province);
          std::cout << "Distrito: ";
          std::cin;
          getline(std::cin, newPerson.address.district);
          std::cout << "Ciudad: ";
          std::cin;
          getline(std::cin, newPerson.address.city);
          std::cout << "Telefono: ";
          std::cin;
          getline(std::cin, newPerson.phoneNumber);
          std::cout << "Correo: ";
          std::cin;
          getline(std::cin, newPerson.email);
          std::cout << "Estatus Civil [M/S]: ";
          std::cin;
          getline(std::cin, newPerson.civilStatus);
          if (management_cpp::Management::createNewPerson(personsList, newPerson))
            std::cout << "Se ha creado el registro" << std::endl;
        }
        else if (option == 3)
        {
          int dni;
          std::cout << "DNI del registro a eliminar: ";
          std::cin >> dni;
          bool success = management_cpp::Management::deleteByDNI(personsList, dni);
          if (success)
          {
            std::cout << "Registro eliminado exitosamente." << std::endl;
          }
          else
          {
            std::cout << "Registro no encontrado." << std::endl;
          }
        }
        else
        {
          break;
        }
      }
    }

    else
    {
      std::cout << GREEN << "Gracias por usar el sistema" << RESET << std::endl;
      std::cout << std::endl;
      break;
    }

    personsList.clear();
    personsList.shrink_to_fit();
  }

  return 0;
}
