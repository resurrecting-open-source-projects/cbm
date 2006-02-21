#ifndef CBM_ERRNOERROR_HPP
#define CBM_ERRNOERROR_HPP

#include <cerrno>
#include <cstring>
#include <stdexcept>
#include <string>

class ErrnoError : public std::runtime_error {
    public:
	ErrnoError(const std::string& description, int error = errno) 
	    : std::runtime_error(description + ": " + std::strerror(error)) {}
};

#endif
