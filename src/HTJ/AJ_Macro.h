#pragma once

#define STRING std::wstring
#define LOG(x) std::cout << "log: " << x << std::endl
#define LOGW(x) std::wcout << "log: " << x << std::endl
#define INPUT(y) std::cin >> y
#define Request(M, V)      \
  std::cout << M << " =>"; \
  INPUT(V)
#define APPPAUSE std::cin.get();
#define Arry(type) std::vector<type>

namespace AJimpa
{
  enum AJDebugtype
  {
    Information,
    Warning,
    Error,
    System,
  };

  void Debug(std::string Message, AJDebugtype Type)
  {
    std::cout << Type << ": " << Message << std::endl;
  }

}