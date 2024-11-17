#pragma once
#include <string>

namespace Error {

void Unhandled(int Line, const std::string& File);

void ResourceNotReady(const std::string& Name);

void UnknownResource(const std::string& Name);

}; // namespace Error
