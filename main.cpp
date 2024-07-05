#include <iostream>
#include <vector>
#include <chrono>
#if defined(_WIN32) || defined(_WIN64)
#include <conio>
#elif __linux__
#include <unistd.h>
#include <termios.h>
#endif
#include "general.h"
#include "management.h"
#include "colors.h"
#include "generate.h"

// vector<Person> persons;
void clearConsole()
{
  try
  {

#ifdef _WIN32
    std::system("cls");
#elif __linux__
    std::system("clear");
#endif
  }
  catch (const std::exception &e)
  {
  }
}

void customPause()
{
  std::cout << GREEN << "========================================================" << RESET << std::endl;
  std::cout << "Presiona cualquier tecla para continuar..." << std::endl;
  std::cout << GREEN << "========================================================" << RESET << std::endl;
#if defined(_WIN32) || defined(_WIN64)
  std::cout << "Presiona cualquier tecla para continuar...";
  _getch();
#else

  // Configurar el terminal para desactivar el eco y la espera por Enter
  termios oldt, newt;
  tcgetattr(STDIN_FILENO, &oldt); // Obtener la configuración actual del terminal
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);        // Desactivar la entrada canónica y el eco
  tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Aplicar la nueva configuración

  // Leer una tecla
  char ch;
  read(STDIN_FILENO, &ch, 1);

  // Restaurar la configuración del terminal
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
}
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
  std::cout << "Preparado en " << elapsed.count() << " seconds. " << std::endl;
  while (true)
  {
    clearConsole();
    std::cout << GREEN << "========================================================" << RESET << std::endl;
    std::cout << GREEN << "Seleccione la opcion deseada" << RESET << std::endl;
    std::cout << GREEN << "========================================================" << RESET << std::endl;
    std::cout << YELLOW << "[1] Generar datos de prueba" << RESET << std::endl;
    std::cout << YELLOW << "[2] Gestionar registro" << RESET << std::endl;
    std::cout << RED << "[3] Salir" << RESET << std::endl;
    std::cout << GREEN << "========================================================" << RESET << std::endl;
    int option;
    std::cout << "Opcion: ";
    std::cin >> option;
    std::cout << GREEN << "========================================================" << RESET << std::endl;
    if (option == 1)
    {
      clearConsole();
      std::cout << GREEN << "========================================================" << RESET << std::endl;
      std::cout << GREEN << "Ingrese la cantidad de registros a generar" << RESET << std::endl;
      std::cout << GREEN << "========================================================" << RESET << std::endl;
      std::cout << "Cantidad: ";
      int totalRecords;
      std::cin >> totalRecords;
      std::cout << GREEN << "========================================================" << RESET << std::endl;
      std::cout << "Generando..." << std::endl;
      start = std::chrono::high_resolution_clock::now();
      std::cout << "Proceso iniciado" << std::endl;
      generate_data::Generate::start(totalRecords);
      std::cout << "Proceso preparando los datos" << std::endl;
      management_cpp::Management::prepareData(personsList);
      end = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> elapsed = end - start;
      std::cout << "Preparado en " << elapsed.count() << " seconds." << std::endl;
      customPause();
    }
    else if (option == 2)
    {
      while (true)
      {
        clearConsole();
        std::cout << GREEN << "========================================================" << RESET << std::endl;
        std::cout << GREEN << "Seleccione una operacion" << RESET << std::endl;
        std::cout << GREEN << "========================================================" << RESET << std::endl;
        std::cout << YELLOW << "[1] Buscar por DNI" << RESET << std::endl;
        std::cout << YELLOW << "[2] Crear nuevo registro" << RESET << std::endl;
        std::cout << YELLOW << "[3] Eliminar registro" << RESET << std::endl; // Nueva opción añadida
        std::cout << RED << "[4] Salir" << RESET << std::endl;
        std::cout << GREEN << "========================================================" << RESET << std::endl;
        std::cout << "Opcion: ";
        std::cin >> option;
        std::cout << GREEN << "========================================================" << RESET << std::endl;
        if (option == 1)
        {
          clearConsole();
          std::cout << GREEN << "========================================================" << RESET << std::endl;
          std::cout << GREEN << "Ingrese el DNI" << RESET << std::endl;
          std::cout << GREEN << "========================================================" << RESET << std::endl;
          int dni;
          std::cout << "DNI: ";
          std::cin >> dni;
          std::cout << GREEN << "========================================================" << RESET << std::endl;
          Person person = management_cpp::Management::findByDNI(personsList, dni);
          if (person.dni != 0 && person.name != "")
          {
            std::cout << BLUE << "Registro encontrado:" << RESET << std::endl;
            std::cout << YELLOW << "DNI: " << RESET << person.dni << std::endl;
            std::cout << YELLOW << "Nombre: " << RESET << person.name << std::endl;
            std::cout << YELLOW << "Nacionalidad: " << RESET << person.nationality << std::endl;
            std::cout << YELLOW << "Dirección: " << RESET << person.address.department << ", " << person.address.province << ", " << person.address.district << ", " << person.address.city << std::endl;
            std::cout << YELLOW << "Telefono: " << RESET << person.phoneNumber << std::endl;
            std::cout << YELLOW << "Email: " << RESET << person.email << std::endl;
            std::cout << YELLOW << "Estado Civil: " << RESET << person.civilStatus << std::endl;
          }
          else
          {
            std::cout << "Registro no encontrado." << std::endl;
          }
          customPause();
        }
        else if (option == 2)
        {
          clearConsole();
          std::cout << GREEN << "========================================================" << RESET << std::endl;
          std::cout << GREEN << "Ingrese los datos de la persona" << RESET << std::endl;
          std::cout << GREEN << "========================================================" << RESET << std::endl;
          Person newPerson = Person();
          std::string _dni = "";
          std::cout << YELLOW << "DNI: " << RESET;
          std::cin >> _dni;
          newPerson.dni = std::stoi(_dni);
          getline(std::cin, newPerson.name);
          std::cout << YELLOW << "Nombre: " << RESET;
          std::cin;
          getline(std::cin, newPerson.name);
          std::cout << YELLOW << "Apellido: " << RESET;
          std::cin;
          getline(std::cin, newPerson.lastName);
          std::cout << YELLOW << "Nacionalidad: " << RESET;
          std::cin;
          getline(std::cin, newPerson.nationality);
          std::cout << YELLOW << "Departamento: " << RESET;
          std::cin;
          getline(std::cin, newPerson.address.department);
          std::cout << YELLOW << "Provincia: " << RESET;
          std::cin;
          getline(std::cin, newPerson.address.province);
          std::cout << YELLOW << "Distrito: " << RESET;
          std::cin;
          getline(std::cin, newPerson.address.district);
          std::cout << YELLOW << "Ciudad: " << RESET;
          std::cin;
          getline(std::cin, newPerson.address.city);
          std::cout << YELLOW << "Telefono: " << RESET;
          std::cin;
          getline(std::cin, newPerson.phoneNumber);
          std::cout << YELLOW << "Correo: " << RESET;
          std::cin;
          getline(std::cin, newPerson.email);
          std::cout << YELLOW << "Estatus Civil [M/S]: " << RESET;
          std::cin;
          getline(std::cin, newPerson.civilStatus);
          if (management_cpp::Management::createNewPerson(personsList, newPerson))
            std::cout << "Se ha creado el registro" << std::endl;
          customPause();
        }
        else if (option == 3)
        {
          clearConsole();
          std::cout << GREEN << "========================================================" << RESET << std::endl;
          std::cout << GREEN << "Ingrese el DNI" << RESET << std::endl;
          std::cout << GREEN << "========================================================" << RESET << std::endl;
          int dni;
          std::cout << "DNI: ";
          std::cin >> dni;
          std::cout << GREEN << "========================================================" << RESET << std::endl;
          bool success = management_cpp::Management::deleteByDNI(personsList, dni);
          if (success)
          {
            std::cout << "Registro eliminado exitosamente." << std::endl;
          }
          else
          {
            std::cout << "Registro no encontrado." << std::endl;
          }
          customPause();
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
