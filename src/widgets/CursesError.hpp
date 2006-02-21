#ifndef CBM_WIDGETS_CURSESERROR_HPP
#define CBM_WIDGETS_CURSESERROR_HPP

#include <stdexcept>
#include <string>

class CursesError : public std::runtime_error {
    public:
	CursesError(const std::string& description) : std::runtime_error(description) {}
};

#endif
