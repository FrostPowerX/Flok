#include "Error.h"

#include <iostream>

namespace Error {

void Error::Unhandled(const int Line, const std::string& File) {
  std::cerr << "Something went wrong at " << File << ":" << Line << '\n';

#ifdef _DEBUG
  abort();
#endif

}

void Error::ResourceNotReady(const std::string& Name) {
  std::cerr << "Resource Not Ready: " << Name << "\n";

#ifdef _DEBUG
  abort();
#endif
}

void Error::UnknownResource(const std::string& Name) {
  std::cerr << "Unknown resource name: " << Name << "\n";

#ifdef _DEBUG
  abort();
#endif
}

}