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

long startMemory;
long endMemory;
std::chrono::time_point<std::chrono::steady_clock> startTime;
std::chrono::time_point<std::chrono::steady_clock> endTime;
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

  // startMemory = getMemory();
  // startTime = getTime();
  std::cout << "Proceso iniciado" << std::endl;
  management_cpp::Management::prepareData(personsList);
  // endMemory = getMemory();
  // endTime = getTime();
  // calculateMemoryAndTime(startMemory, endMemory, startTime, endTime);
  customPause();
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
      std::cin.clear();

      std::cout << GREEN << "========================================================" << RESET << std::endl;
      std::cout << "Generando..." << std::endl;

      startMemory = getMemory();
      startTime = getTime();
      generate_data::Generate::start(totalRecords);
      management_cpp::Management::prepareData(personsList);
      endMemory = getMemory();
      endTime = getTime();
      calculateMemoryAndTime(startMemory, endMemory, startTime, endTime);

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
        std::cout << YELLOW << "[3] Modificar registro" << RESET << std::endl;
        std::cout << YELLOW << "[4] Eliminar registro" << RESET << std::endl; // Nueva opción añadida
        std::cout << RED << "[5] Salir" << RESET << std::endl;
        std::cout << GREEN << "========================================================" << RESET << std::endl;
        std::cout << "Opcion: ";
        std::cin >> option;
        std::cin.clear();

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
          std::cin.clear();

          std::cout << GREEN << "========================================================" << RESET << std::endl;
          startMemory = getMemory();
          startTime = getTime();
          Person person = management_cpp::Management::findByDNI(personsList, dni);
          endMemory = getMemory();
          endTime = getTime();
          calculateMemoryAndTime(startMemory, endMemory, startTime, endTime);
          std::cout << GREEN << "========================================================" << RESET << std::endl;
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
          std::cin.clear();
          std::cout << YELLOW << "Nombre: " << RESET;
          std::cin;
          getline(std::cin, newPerson.name);
          std::cin.clear();
          std::cout << YELLOW << "Apellido: " << RESET;
          std::cin;
          getline(std::cin, newPerson.lastName);
          std::cin.clear();
          std::cout << YELLOW << "Nacionalidad: " << RESET;
          std::cin;
          getline(std::cin, newPerson.nationality);
          std::cin.clear();
          std::cout << YELLOW << "Departamento: " << RESET;
          std::cin;
          getline(std::cin, newPerson.address.department);
          std::cin.clear();
          std::cout << YELLOW << "Provincia: " << RESET;
          std::cin;
          getline(std::cin, newPerson.address.province);
          std::cin.clear();
          std::cout << YELLOW << "Distrito: " << RESET;
          std::cin;
          getline(std::cin, newPerson.address.district);
          std::cin.clear();
          std::cout << YELLOW << "Ciudad: " << RESET;
          std::cin;
          getline(std::cin, newPerson.address.city);
          std::cin.clear();
          std::cout << YELLOW << "Telefono: " << RESET;
          std::cin;
          getline(std::cin, newPerson.phoneNumber);
          std::cin.clear();
          std::cout << YELLOW << "Correo: " << RESET;
          std::cin;
          getline(std::cin, newPerson.email);
          std::cin.clear();
          std::cout << YELLOW << "Estatus Civil [M/S]: " << RESET;
          std::cin;
          getline(std::cin, newPerson.civilStatus);
          std::cin.clear();
          std::cout << GREEN << "========================================================" << RESET << std::endl;
          startMemory = getMemory();
          startTime = getTime();
          if (management_cpp::Management::createNewPerson(personsList, newPerson))
            std::cout << "Se ha creado el registro" << std::endl;
          endMemory = getMemory();
          endTime = getTime();
          calculateMemoryAndTime(startMemory, endMemory, startTime, endTime);
          std::cout << GREEN << "========================================================" << RESET << std::endl;
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
          std::cin.clear();
          std::cout << GREEN << "========================================================" << RESET << std::endl;
          Person person = management_cpp::Management::findByDNI(personsList, dni);
          if (person.dni != 0 && person.name != "")
          {
            while (true)
            {
              clearConsole();
              std::cout << GREEN << "========================================================" << RESET << std::endl;
              std::cout << GREEN << "Datos actuales" << RESET << std::endl;
              std::cout << GREEN << "========================================================" << RESET << std::endl;
              std::cout << YELLOW << "DNI: " << RESET << person.dni << std::endl;
              std::cout << YELLOW << "Nombre: " << RESET << person.name << std::endl;
              std::cout << YELLOW << "Nacionalidad: " << RESET << person.nationality << std::endl;
              std::cout << YELLOW << "Dirección: " << RESET << person.address.department << ", " << person.address.province << ", " << person.address.district << ", " << person.address.city << std::endl;
              std::cout << YELLOW << "Telefono: " << RESET << person.phoneNumber << std::endl;
              std::cout << YELLOW << "Email: " << RESET << person.email << std::endl;
              std::cout << YELLOW << "Estado Civil: " << RESET << person.civilStatus << std::endl;
              std::cout << GREEN << "========================================================" << RESET << std::endl;
              std::cout << GREEN << "Seleccione una operacion" << RESET << std::endl;
              std::cout << GREEN << "========================================================" << RESET << std::endl;
              std::cout << YELLOW << "[1] Cambiar Nombre" << RESET << std::endl;
              std::cout << YELLOW << "[2] Cambiar Nacionalidad" << RESET << std::endl;
              std::cout << YELLOW << "[3] Cambiar Direccion" << RESET << std::endl;
              std::cout << YELLOW << "[4] Cambiar Telefono" << RESET << std::endl;
              std::cout << YELLOW << "[5] Cambiar Correo" << RESET << std::endl;
              std::cout << YELLOW << "[6] Cambiar Estado Civil" << RESET << std::endl;
              std::cout << BLUE << "[7] Guardar todos los cambios" << RESET << std::endl;
              std::cout << RED << "[8] Salir" << RESET << std::endl;
              std::cout << GREEN << "========================================================" << RESET << std::endl;
              int option;
              std::cout << "Opcion: ";
              std::cin >> option;
              std::cin.clear();
              std::cout << GREEN << "========================================================" << RESET << std::endl;
              if (option == 1)
              {
                std::string newName;
                std::cout << "Nuevo Nombre: ";
                std::cin >> newName;
                person.name = newName;
                std::cin.clear();
              }
              else if (option == 2)
              {
                std::string newNationality;
                std::cout << "Nueva Nacionalidad: ";
                std::cin >> newNationality;
                person.nationality = newNationality;
                std::cin.clear();
              }
              else if (option == 3)
              {
                while (true)
                {
                  clearConsole();
                  std::cout << GREEN << "========================================================" << RESET << std::endl;
                  std::cout << GREEN << "Datos actuales" << RESET << std::endl;
                  std::cout << GREEN << "========================================================" << RESET << std::endl;
                  std::cout << YELLOW << "Departamento: " << RESET << person.address.department << std::endl;
                  std::cout << YELLOW << "Provincia: " << RESET << person.address.province << std::endl;
                  std::cout << YELLOW << "Ciudad: " << RESET << person.address.city << std::endl;
                  std::cout << YELLOW << "Distrito: " << RESET << person.address.district << std::endl;
                  std::cout << GREEN << "========================================================" << RESET << std::endl;
                  std::cout << GREEN << "Seleccione una operacion" << RESET << std::endl;
                  std::cout << GREEN << "========================================================" << RESET << std::endl;
                  std::cout << YELLOW << "[1] Cambiar Departamento" << RESET << std::endl;
                  std::cout << YELLOW << "[2] Cambiar Provincia" << RESET << std::endl;
                  std::cout << YELLOW << "[3] Cambiar Ciudad" << RESET << std::endl;
                  std::cout << YELLOW << "[4] Cambiar Distrito" << RESET << std::endl;
                  std::cout << RED << "[5] Salir" << RESET << std::endl;
                  std::cout << GREEN << "========================================================" << RESET << std::endl;
                  int option;
                  std::cout << "Opcion: ";
                  std::cin >> option;
                  std::cin.clear();
                  std::cout << GREEN << "========================================================" << RESET << std::endl;
                  std::string t;
                  getline(std::cin, t);
                  if (option == 1)
                  {
                    std::cout << "Nuevo Departamento: ";
                    std::cin;
                    getline(std::cin, person.address.department);
                  }
                  else if (option == 2)
                  {
                    std::cout << "Nueva Provincia: ";
                    std::cin;
                    getline(std::cin, person.address.province);
                    std::cin.clear();
                  }
                  else if (option == 3)
                  {
                    std::cout << "Nueva Ciudad: ";
                    std::cin;
                    getline(std::cin, person.address.city);
                    std::cin.clear();
                  }
                  else if (option == 4)
                  {
                    std::cout << "Nuevo Distrito: ";
                    std::cin;
                    getline(std::cin, person.address.district);
                    std::cin.clear();
                  }
                  else if (option == 5)
                  {
                    break;
                  }
                }
              }
              else if (option == 4)
              {
                std::string newPhoneNumber;
                std::cout << "Nuevo Telefono: ";
                std::cin >> newPhoneNumber;
                person.phoneNumber = newPhoneNumber;
                std::cin.clear();
              }
              else if (option == 5)
              {
                std::string newEmail;
                std::cout << "Nuevo Correo: ";
                std::cin >> newEmail;
                person.email = newEmail;
                std::cin.clear();
              }
              else if (option == 6)
              {
                std::string newCivilStatus;
                std::cout << "Nuevo Estado Civil [M: Married, S: Single]:";
                std::cin >> newCivilStatus;
                person.civilStatus = newCivilStatus;
                std::cin.clear();
              }
              else if (option == 7)
              {
                startMemory = getMemory();
                startTime = getTime();
                management_cpp::Management::updateByDNI(personsList, person);
                endMemory = getMemory();
                endTime = getTime();
                calculateMemoryAndTime(startMemory, endMemory, startTime, endTime);
                std::cout << "Registro actualizado exitosamente." << std::endl;
                std::cout << GREEN << "========================================================" << RESET << std::endl;
                break;
              }
              else if (option == 8)
              {
                break;
              }
            }
          }
          else
          {
            std::cout << "Registro no encontrado." << std::endl;
          }
          customPause();
        }
        else if (option == 4)
        {
          clearConsole();
          std::cout << GREEN << "========================================================" << RESET << std::endl;
          std::cout << GREEN << "Ingrese el DNI" << RESET << std::endl;
          std::cout << GREEN << "========================================================" << RESET << std::endl;
          int dni;
          std::cout << "DNI: ";
          std::cin >> dni;
          std::cout << GREEN << "========================================================" << RESET << std::endl;
          startMemory = getMemory();
          startTime = getTime();
          bool success = management_cpp::Management::deleteByDNI(personsList, dni);
          endMemory = getMemory();
          endTime = getTime();
          calculateMemoryAndTime(startMemory, endMemory, startTime, endTime);
          if (success)
          {
            std::cout << "Registro eliminado exitosamente." << std::endl;
          }
          else
          {
            std::cout << "Registro no encontrado." << std::endl;
          }
          std::cout << GREEN << "========================================================" << RESET << std::endl;
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
      std::cout << GREEN << "========================================================" << RESET << std::endl;
      std::cout << GREEN << "Gracias por usar el sistema" << RESET << std::endl;
      std::cout << GREEN << "========================================================" << RESET << std::endl;
      break;
    }
  }
  personsList.clear();
  personsList.shrink_to_fit();

  return 0;
}
