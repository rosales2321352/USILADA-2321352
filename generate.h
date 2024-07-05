#ifndef GENERATE_H
#define GENERATE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <future>
#include "init.h"
#include "database.h"
#include "general.h"

std::vector<std::string> names;
std::vector<std::string> last_names;
std::vector<std::string> last_names_2;
std::vector<std::string> nationalities = {"Peru"};
std::vector<std::string> departments = {"Lima"};
std::vector<std::string> provinces = {"Lima"};
std::vector<std::string> districts = {"Ate", "La Victoria"};
std::vector<std::string> cities = {"City1", "City2"};
std::vector<std::string> civil_statuses = {"Single", "Married"};

namespace generate_data
{

  class Generate
  {
  public:
    Generate();
    ~Generate();

    static void start(int totalRecords);

  private:
    static void preparateData(std::string filenameOfBack);

  private:
    static void generate(const std::string &filename, int totalRecords, int blockSize, int numThreads);

  private:
    static void writeBlock(const std::string &filename, int start, int end);

  private:
    static Person generatePerson(int index);
  };

  std::string getRandomString(const std::vector<std::string> &list)
  {
    int index = rand() % list.size();
    return list[index];
  }

  std::string getRandomEmail(std::string name)
  {
    return name + "@example.com";
  }

  void Generate::start(int totalRecords)
  {
    try
    {
      init::ConfigRead configRead;
      configRead.Open("config.ini");
      std::string filename = configRead.GetValue("Database", "filename");
      if (totalRecords == 0)
        totalRecords = std::stoi(configRead.GetValue("Data of Test", "totalRecords"));
      std::string blockSize = configRead.GetValue("Data of Test", "blockSize");
      std::string numThreads = configRead.GetValue("Data of Test", "numThreads");
      std::string bankOfData = configRead.GetValue("Data of Test", "bankOfData");
      configRead.Close();

      preparateData(bankOfData);
      if (names.size() == 0 || last_names.size() == 0 || last_names_2.size() == 0)
      {
        std::cerr << "No se encontraron registros de prueba" << std::endl;
        return;
      }

      generate(filename, totalRecords, std::stoi(blockSize), std::stoi(numThreads));
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
    }
  }

  void Generate::preparateData(std::string filenameOfBack)
  {
    try
    {
      std::ifstream fin(filenameOfBack);

      if (!fin.is_open())
      {
        std::cerr << "Error: No se pudo abrir el archivo." << std::endl;
        return;
      }

      std::string line;
      while (getline(fin, line))
      {
        std::stringstream ss(line);
        std::string word;
        getline(ss, word, ',');
        names.push_back(word);
        getline(ss, word, ',');
        last_names.push_back(word);
        getline(ss, word, ',');
        last_names_2.push_back(word);
      }

      std::cout << std::endl;

      fin.close();
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
    }
  }

  void Generate::generate(const std::string &filename, int totalRecords, int blockSize, int numThreads)
  {
    try
    {
      std::ofstream outfile(filename, std::ios::out | std::ios::trunc);
      outfile.close();

      std::vector<std::future<void>> futures;

      std::ofstream outfile_(filename, std::ios::binary | std::ios::out | std::ios::app);

      for (int i = 0; i < totalRecords; ++i)
      {
        Person person = generatePerson(i);
        database_cpp::Database::writePerson(person, outfile_);
        if (i % 1000000 == 0)
        {
          std::cout << "Progreso: " << (i / 1000000) << " millones de registros generados.\n";
        }
      }
      outfile_.close();

      // for (int i = 0; i < totalRecords; i += blockSize * numThreads)
      // {
      //   for (int j = 0; j < numThreads; ++j)
      //   {
      //     int start = i + j * blockSize;
      //     int end = std::min(start + blockSize, totalRecords);
      //     if (start < totalRecords)
      //     {
      //       futures.push_back(async(std::launch::async, writeBlock, filename, start, end));
      //     }
      //   }
      //   if (i % 1000000 == 0)
      //   {
      //     std::cout << "Progreso: " << (i / 1000000) << " millones de registros generados.\n";
      //   }
      //   // Espera a que todos los hilos terminen antes de continuar
      //   for (auto &f : futures)
      //   {
      //     f.get();
      //   }
      //   futures.clear();
      // }
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
    }
  }

  Person Generate::generatePerson(int index)
  {
    Person person;
    try
    {
      person.dni = 10000000 + index;
      person.name = "TestName";                     // getRandomString(names);
      person.lastName = "TestLastName";             // getRandomString(last_names);
      person.nationality = "TestNationality";       // getRandomString(nationalities);
      person.address.department = "TestDepartment"; // getRandomString(departments);
      person.address.province = "TestProvince";     // getRandomString(provinces);
      person.address.district = "TestDistrict";     // getRandomString(districts);
      person.address.city = "TestCity";             // getRandomString(cities);
      person.phoneNumber = "12345678";
      person.email = "TestEmail";             // getRandomEmail("example_" + std::to_string(person.dni));
      person.civilStatus = "TestCivilStatus"; // getRandomString(civil_statuses);
      // person.name = getRandomString(names);
      // person.lastName = getRandomString(last_names);
      // person.nationality = getRandomString(nationalities);
      // person.address.department = getRandomString(departments);
      // person.address.province = getRandomString(provinces);
      // person.address.district = getRandomString(districts);
      // person.address.city = getRandomString(cities);
      // person.phoneNumber = "12345678";
      // person.email = getRandomEmail("example_" + std::to_string(person.dni));
      // person.civilStatus = getRandomString(civil_statuses);

      // std::cout << person.dni << " " << person.name << " " << person.lastName << " " << person.nationality << " " << person.address.department << " " << person.address.province << " " << person.address.district << " " << person.address.city << " " << person.phoneNumber << " " << person.email << " " << person.civilStatus << std::endl;
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
    }
    return person;
  }

  void Generate::writeBlock(const std::string &filename, int start, int end)
  {
    try
    {

      std::ofstream outfile(filename, std::ios::binary | std::ios::out | std::ios::app);
      for (int i = start; i < end; ++i)
      {
        Person person = generatePerson(start);
        database_cpp::Database::writePerson(person, outfile);
      }
      outfile.close();
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
    }
  }
}

#endif