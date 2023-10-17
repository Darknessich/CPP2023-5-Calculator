#pragma once
#include <string>
#include <memory>
#include <windows.h>
#include <exception>

#include "Operators/Operator.h"

class LoaderErr : public std::exception {
public:
  using std::exception::exception;
};

class Loader {
  using unqOperator = std::unique_ptr<Operator>;
  using Fabric = Operator*(*)(void);

  void getFabric(std::string const& path);
public:
  Loader(std::string const& path);
  ~Loader() noexcept;

  unqOperator get() const noexcept;
  unqOperator next();
  bool isEnd() const;

private:
  std::string path;
  
  HANDLE hfind;
  WIN32_FIND_DATAA winfd;
  
  Fabric creator;
  bool end;
};