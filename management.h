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
    static bool createNewPerson(std::vector<std::vector<Person>> &personsList, const Person &person);
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
      init::ConfigRead configRead;
      configRead.Open("config.ini");
      std::string filename = configRead.GetValue("Database", "filename");
      Person person;
      for (auto &personList : personsList)
      {
        int index = binaryGetPosition(personList, dni, person);
        if (index != -1)
        {
          personList.erase(personList.begin() + index);
          break;
        }
      }
      database_cpp::Database::writeManyPersons(personsList, filename);
      return true;
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
      return false;
    }
  }

  bool Management::createNewPerson(std::vector<std::vector<Person>> &personsList, const Person &person)
  {
    try
    {

      init::ConfigRead configRead;
      configRead.Open("config.ini");
      int sizeOfBlock = std::stoi(configRead.GetValue("Order", "sizeOfBlock"));
      std::string filename = configRead.GetValue("Database", "filename");
      bool new_vector = true;
      for (auto &personList : personsList)
      {
        if (personList.size() < sizeOfBlock)
        {
          personList.push_back(person);
          new_vector = false;
          break;
        }
      }

      if (new_vector)
      {
        personsList.push_back({person});
      }
      database_cpp::Database::writeManyPersons(personsList, filename);
      return true;
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
      return false;
    }
  }

}

#endif
