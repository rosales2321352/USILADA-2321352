#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "init.h"
#include "database.h"
#include "general.h"

namespace management_cpp
{
  class Management
  {
  public:
    Management();
    ~Management();

    static void prepareData(std::vector<std::vector<Person>> &personsList);
    static Person findByDNI(std::vector<std::vector<Person>> &personsList, const int &dni);
    static bool deleteByDNI(std::vector<std::vector<Person>> &personsList, const int &dni); // Declaración de la nueva función
  };

  void Management::prepareData(std::vector<std::vector<Person>> &personsList)
  {
    try
    {
      init::ConfigRead configRead;
      configRead.Open("config.ini");
      std::string filename = configRead.GetValue("Database", "filename");
      int sizeOfBlock = std::stoi(configRead.GetValue("Order", "sizeOfBlock"));
      configRead.Close();
      database_cpp::Database::readPersons(filename, personsList, sizeOfBlock);
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
    }
  }

  Person Management::findByDNI(std::vector<std::vector<Person>> &personsList, const int &dni)
  {
    try
    {
      Person person;
      for (const auto &personList : personsList)
      {
        if (binarySearch(personList, dni, person))
        {
          return person;
        }
      }
      return person;
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
      return Person();
    }
  }

  // Implementación de la función deleteByDNI
  bool Management::deleteByDNI(std::vector<std::vector<Person>> &personsList, const int &dni) 
  {
    try
    {
      for (auto &personList : personsList)
      {
        auto it = std::find_if(personList.begin(), personList.end(), [dni](const Person &person) {
          return person.dni == dni;
        });

        if (it != personList.end())
        {
          personList.erase(it);
          return true;
        }
      }
      return false;
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
      return false;
    }
  }

}

#endif
