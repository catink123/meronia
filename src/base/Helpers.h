#pragma once
#include <stdexcept>

#define DECLARE_RUNTIME_ERROR(Name) \
class Name : public std::runtime_error \
{ \
public: \
    Name(const std::string& msg): std::runtime_error(msg) \
    { \
    } \
}