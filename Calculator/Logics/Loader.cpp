#include "Loader.h"

void Loader::getFabric(std::string const& path) {
  HMODULE hm = LoadLibraryA(path.c_str());
  creator = nullptr;

  if (hm == nullptr) return;
  creator = reinterpret_cast<Fabric>(GetProcAddress(hm, "create"));
}

Loader::Loader(std::string const& path)
  : path(path), creator(nullptr), end(false)
{
  this->hfind = FindFirstFileA((this->path + std::string("\\*.dll")).c_str(), &winfd);
  
  if (hfind != INVALID_HANDLE_VALUE)
    getFabric(this->path + "\\" + winfd.cFileName);
  else
    end = true;
}

Loader::~Loader() noexcept {
  FindClose(hfind);
}

bool Loader::isEnd() const {
  return end;
}

std::unique_ptr<Operator> Loader::get() const noexcept {
  return unqOperator(creator? creator() : nullptr);
}

std::unique_ptr<Operator> Loader::next() {
  if (end) 
    return nullptr;

  if (FindNextFileA(hfind, &winfd) == NULL) {
    end = true;
    creator = nullptr;
    return nullptr;
  }

  getFabric(this->path + "\\" + winfd.cFileName);
  return get();
}