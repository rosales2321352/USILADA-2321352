#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include <mutex>
#include <thread>
#include <future>
#include "general.h"

std::mutex mtx;
namespace database_cpp
{
  class Database
  {
  public:
    Database();
    ~Database();

    static void writeString(const std::string &str, std::ofstream &outFile);
    static std::string readString(std::ifstream &inFile);
    static void writePerson(const Person &person, std::ofstream &outFile);
    static Person readPerson(std::ifstream &inFile);
    static void writePersons(const std::vector<Person> &persons, const std::string &filename);
    static void writeManyPersons(std::vector<std::vector<Person>> &persons, const std::string &filename);
    static void readPersons(const std::string &filename, std::vector<std::vector<Person>> &personsList, int sizeOfBlock);
  };

  void Database::writeString(const std::string &str, std::ofstream &outFile)
  {
    size_t length = str.size();
    outFile.write(reinterpret_cast<const char *>(&length), sizeof(length));
    outFile.write(str.c_str(), length);
  }

  std::string Database::readString(std::ifstream &inFile)
  {
    size_t length;
    inFile.read(reinterpret_cast<char *>(&length), sizeof(length));
    std::string str(length, ' ');
    inFile.read(&str[0], length);
    return str;
  }

  void Database::writePerson(const Person &person, std::ofstream &outFile)
  {
    try
    {

      std::lock_guard<std::mutex> lock(mtx);
      outFile.write(reinterpret_cast<const char *>(&person.dni), sizeof(person.dni));
      writeString(person.name, outFile);
      writeString(person.lastName, outFile);
      writeString(person.nationality, outFile);
      writeString(person.address.department, outFile);
      writeString(person.address.province, outFile);
      writeString(person.address.district, outFile);
      writeString(person.address.city, outFile);
      writeString(person.phoneNumber, outFile);
      writeString(person.email, outFile);
      writeString(person.civilStatus, outFile);
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
    }
  }

  Person Database::readPerson(std::ifstream &inFile)
  {
    Person person;
    try
    {
      inFile.read(reinterpret_cast<char *>(&person.dni), sizeof(person.dni));
      person.name = readString(inFile);
      person.lastName = readString(inFile);
      person.nationality = readString(inFile);
      person.address.department = readString(inFile);
      person.address.province = readString(inFile);
      person.address.district = readString(inFile);
      person.address.city = readString(inFile);
      person.phoneNumber = readString(inFile);
      person.email = readString(inFile);
      person.civilStatus = readString(inFile);
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
    }
    return person;
  }

  void Database::writePersons(const std::vector<Person> &persons, const std::string &filename)
  {
    std::ofstream outFile(filename, std::ios::binary);
    for (const auto &person : persons)
    {
      writePerson(person, outFile);
    }
    outFile.close();
  }

  void Database::writeManyPersons(std::vector<std::vector<Person>> &personsList, const std::string &filename)
  {
    std::ofstream outFile(filename, std::ios::binary);
    for (const auto &personList : personsList)
    {
      for (const auto &person : personList)
      {
        writePerson(person, outFile);
      }
    }
    outFile.close();
  }

  void Database::readPersons(const std::string &filename, std::vector<std::vector<Person>> &personsList, int sizeOfBlock)
  {
    std::ifstream inFile(filename, std::ios::binary);
    int count = 0;
    int total_count = 0;
    long total_memory = 0;
    std::vector<Person> persons;
    std::chrono::duration<double> total_time = std::chrono::duration<double>::zero();
    while (inFile.peek() != EOF)
    {

      Person person = readPerson(inFile);

      persons.push_back(person);
      if (persons.size() == sizeOfBlock || inFile.peek() == EOF)
      {
        long startMemory = getMemory();
        std::chrono::time_point<std::chrono::steady_clock> startTime = getTime();
        persons = countingSort(persons);
        long endMemory = getMemory();
        std::chrono::time_point<std::chrono::steady_clock> endTime = getTime();
        total_memory += getMemoryUsage(startMemory, endMemory);
        total_time += getElapsedTime(startTime, endTime);
        personsList.push_back(persons);
        persons.clear();
        count = 0;
      }
      count++;
      total_count++;
    }

    inFile.close();
    std::cout << "Total de registros leidos: " << total_count << std::endl;
    std::cout << "Total de memoria usada: " << total_memory << " kb" << std::endl;
    std::cout << "Tiempo de ejecución: " << total_time.count() << " segundos" << std::endl;
  }

}

#endif