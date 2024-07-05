#ifndef INIT_H
#define INIT_H

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <vector>

namespace init
{
  class ConfigCreate
  {
  public:
    ConfigCreate() = default;
    ~ConfigCreate()
    {
      if (file.is_open())
      {
        file.close();
      }
    }

    void Open(const std::string &filename)
    {
      if (file.is_open())
      {
        file.close();
      }
      file.clear(); // Limpia cualquier estado de error
      file.open(filename);
      if (!file)
      {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
      }
    }

    void Close()
    {
      if (file.is_open())
      {
        file.close();
      }
    }

    void PutSection(const std::string &section)
    {
      if (file.is_open())
      {
        file << "[" << section << "]" << std::endl;
      }
    }

    void PutValue(const std::string &key, const std::string &value)
    {
      if (file.is_open())
      {
        file << key << "=" << value << std::endl;
      }
    }

    void PutComment(const std::string &comment)
    {
      if (file.is_open())
      {
        file << "# " << comment << std::endl;
      }
    }

    void PutBlankLine()
    {
      if (file.is_open())
      {
        file << std::endl;
      }
    }

  private:
    std::ofstream file;
  };

  class ConfigRead
  {
  public:
    ConfigRead() = default;
    ~ConfigRead()
    {
      if (file.is_open())
      {
        file.close();
      }
    }

    void Open(const std::string &filename)
    {
      if (file.is_open())
      {
        file.close();
      }
      file.clear(); // Limpia cualquier estado de error
      file.open(filename);
      if (!file)
      {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
      }
    }

    void Close()
    {
      if (file.is_open())
      {
        file.close();
      }
    }

    bool GetSection(const std::string &section)
    {
      if (!file.is_open())
      {
        return false;
      }

      file.clear();
      file.seekg(0); // Volver al inicio del archivo

      std::string line;
      while (std::getline(file, line))
      {
        if (line == "[" + section + "]")
        {
          return true;
        }
      }

      return false;
    }

    std::unordered_map<std::string, std::string> GetValues()
    {
      std::unordered_map<std::string, std::string> values;
      if (!file.is_open())
      {
        return values;
      }

      std::string line;
      while (std::getline(file, line))
      {
        if (line.empty() || line[0] == '#' || line[0] == '[')
        {
          continue; // Saltar líneas en blanco, comentarios y secciones
        }

        size_t pos = line.find('=');
        if (pos != std::string::npos)
        {
          std::string key = line.substr(0, pos);
          std::string value = line.substr(pos + 1);
          values[key] = value;
        }
      }

      return values;
    }

    std::string GetValue(const std::string &section, const std::string &key)
    {
      if (GetSection(section))
      {
        std::string line;
        while (std::getline(file, line))
        {
          if (line.empty() || line[0] == '#' || line[0] == '[')
          {
            continue; // Saltar líneas en blanco, comentarios y secciones
          }

          size_t pos = line.find('=');
          if (pos != std::string::npos)
          {
            std::string current_key = line.substr(0, pos);
            if (current_key == key)
            {
              return line.substr(pos + 1);
            }
          }
        }
      }
      return ""; // Valor por defecto si no se encuentra
    }

    void SetValue(const std::string &filename, const std::string &section, const std::string &key, const std::string &newValue)
    {
      std::ifstream infile(filename);
      std::stringstream buffer;
      buffer << infile.rdbuf();
      std::string content = buffer.str();
      infile.close();

      size_t sectionPos = content.find("[" + section + "]");
      if (sectionPos == std::string::npos)
      {
        std::cerr << "Section not found: " << section << std::endl;
        return;
      }

      size_t keyPos = content.find(key + "=", sectionPos);
      if (keyPos == std::string::npos)
      {
        std::cerr << "Key not found: " << key << std::endl;
        return;
      }

      size_t valuePos = content.find('=', keyPos) + 1;
      size_t endLinePos = content.find('\n', valuePos);

      content.replace(valuePos, endLinePos - valuePos, newValue);

      std::ofstream outfile(filename);
      outfile << content;
      outfile.close();
    }

  private:
    std::ifstream file;
  };

} // namespace init

#endif