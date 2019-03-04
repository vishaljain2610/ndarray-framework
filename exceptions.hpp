#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
#include <exception>
#include <string>


struct ValueError : public std::exception
{	
	const char* what() const throw()
	{
		return "Cannot broadcast arrays. Check compatibility of dimensions.";
	}
};


#endif /* EXCEPTIONS_H */
