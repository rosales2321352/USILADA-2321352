#include <iostream>
#include <sys/stat.h>

#ifndef GENERAL_DATA_H
#define GENERAL_DATA_H

struct Address
{
  std::string department;
  std::string province;
  std::string district;
  std::string city;
};

struct Person
{
  int dni;
  std::string name;
  std::string lastName;
  std::string nationality;
  Address address;
  std::string phoneNumber;
  std::string email;
  std::string civilStatus;
};

bool fileExists(const std::string &name)
{

  struct stat buffer;
  bool result = (stat(name.c_str(), &buffer) == 0);
  std::cout << "Database file: " << name << std::endl;
  return result;
}

int getDigit(int number, int digitPosition)
{
  return (number / digitPosition) % 10;
}

void countingSortForRadix(std::vector<Person> &data, int digitPosition)
{
  const int base = 10;
  int size = data.size();
  std::vector<int> countArray(base, 0);
  std::vector<Person> outputArray(size);

  // Contar las ocurrencias de cada dígito
  for (int i = 0; i < size; ++i)
  {
    int digit = getDigit(data[i].dni, digitPosition);
    countArray[digit]++;
  }

  // Sumar las posiciones
  for (int i = 1; i < base; ++i)
  {
    countArray[i] += countArray[i - 1];
  }

  // Construir el arreglo de salida
  for (int i = size - 1; i >= 0; --i)
  {
    int digit = getDigit(data[i].dni, digitPosition);
    outputArray[countArray[digit] - 1] = data[i];
    countArray[digit]--;
  }

  // Copiar el arreglo de salida a data
  for (int i = 0; i < size; ++i)
  {
    data[i] = outputArray[i];
  }
}
std::vector<Person> radixSort(std::vector<Person> &data)
{
  try
  {
    int maxDni = 0;
    for (const auto &person : data)
    {
      maxDni = std::max(maxDni, person.dni);
    }

    // Ejecutar Counting Sort para cada dígito (posición)
    for (int digitPosition = 1; maxDni / digitPosition > 0; digitPosition *= 10)
    {
      countingSortForRadix(data, digitPosition);
    }

    return data;
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
    return data;
  }
}

std::vector<Person> countingSort(std::vector<Person> &data)
{
  try
  {

    int size = data.size();
    int _max = 0;
    for (int i = 0; i < size; i++)
    {
      _max = std::max(_max, data[i].dni);
    }
    std::vector<int> countArray(_max + 1, 0);
    for (int i = 0; i < size; i++)
    {
      countArray[data[i].dni]++;
    }
    for (int i = 1; i <= _max; i++)
    {
      countArray[i] += countArray[i - 1];
    }
    std::vector<Person> outputArray(size);
    for (int i = size - 1; i >= 0; i--)
    {
      outputArray[countArray[data[i].dni] - 1] = data[i];
      countArray[data[i].dni]--;
    }
    data = outputArray;
    outputArray.clear();
    outputArray.shrink_to_fit();
    return data;
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
    return data;
  }
}

bool binarySearch(const std::vector<Person> &persons, int dni, Person &result)
{
  int left = 0;
  int right = persons.size() - 1;

  while (left <= right)
  {
    int mid = left + (right - left) / 2;
    if (persons[mid].dni == dni)
    {
      result = persons[mid];
      return true;
    }
    if (persons[mid].dni < dni)
    {
      left = mid + 1;
    }
    else
    {
      right = mid - 1;
    }
  }

  return false;
}

#endif
#include <iostream>
#include <sys/stat.h>

#ifndef GENERAL_DATA_H
#define GENERAL_DATA_H

struct Address
{
  std::string department;
  std::string province;
  std::string district;
  std::string city;
};

struct Person
{
  int dni;
  std::string name;
  std::string lastName;
  std::string nationality;
  Address address;
  std::string phoneNumber;
  std::string email;
  std::string civilStatus;
};

bool fileExists(const std::string &name)
{

  struct stat buffer;
  bool result = (stat(name.c_str(), &buffer) == 0);
  std::cout << "Database file: " << name << std::endl;
  return result;
}

int getDigit(int number, int digitPosition)
{
  return (number / digitPosition) % 10;
}

void countingSortForRadix(std::vector<Person> &data, int digitPosition)
{
  const int base = 10;
  int size = data.size();
  std::vector<int> countArray(base, 0);
  std::vector<Person> outputArray(size);

  // Contar las ocurrencias de cada dígito
  for (int i = 0; i < size; ++i)
  {
    int digit = getDigit(data[i].dni, digitPosition);
    countArray[digit]++;
  }

  // Sumar las posiciones
  for (int i = 1; i < base; ++i)
  {
    countArray[i] += countArray[i - 1];
  }

  // Construir el arreglo de salida
  for (int i = size - 1; i >= 0; --i)
  {
    int digit = getDigit(data[i].dni, digitPosition);
    outputArray[countArray[digit] - 1] = data[i];
    countArray[digit]--;
  }

  // Copiar el arreglo de salida a data
  for (int i = 0; i < size; ++i)
  {
    data[i] = outputArray[i];
  }
}
std::vector<Person> radixSort(std::vector<Person> &data)
{
  try
  {
    int maxDni = 0;
    for (const auto &person : data)
    {
      maxDni = std::max(maxDni, person.dni);
    }

    // Ejecutar Counting Sort para cada dígito (posición)
    for (int digitPosition = 1; maxDni / digitPosition > 0; digitPosition *= 10)
    {
      countingSortForRadix(data, digitPosition);
    }

    return data;
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
    return data;
  }
}

std::vector<Person> countingSort(std::vector<Person> &data)
{
  try
  {

    int size = data.size();
    int _max = 0;
    for (int i = 0; i < size; i++)
    {
      _max = std::max(_max, data[i].dni);
    }
    std::vector<int> countArray(_max + 1, 0);
    for (int i = 0; i < size; i++)
    {
      countArray[data[i].dni]++;
    }
    for (int i = 1; i <= _max; i++)
    {
      countArray[i] += countArray[i - 1];
    }
    std::vector<Person> outputArray(size);
    for (int i = size - 1; i >= 0; i--)
    {
      outputArray[countArray[data[i].dni] - 1] = data[i];
      countArray[data[i].dni]--;
    }
    data = outputArray;
    outputArray.clear();
    outputArray.shrink_to_fit();
    return data;
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
    return data;
  }
}

bool binarySearch(const std::vector<Person> &persons, int dni, Person &result)
{
  int left = 0;
  int right = persons.size() - 1;

  while (left <= right)
  {
    int mid = left + (right - left) / 2;
    if (persons[mid].dni == dni)
    {
      result = persons[mid];
      return true;
    }
    if (persons[mid].dni < dni)
    {
      left = mid + 1;
    }
    else
    {
      right = mid - 1;
    }
  }

  return false;
}

#endif