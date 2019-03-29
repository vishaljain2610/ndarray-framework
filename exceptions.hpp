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

struct DimensionError : public std::exception
{	
	const char* what() const throw()
	{
		return "Check compatibility of dimensions.";
	}
};

struct UnequalShapeError : public std::exception
{	
	const char* what() const throw()
	{
		return "ERROR: Check compatibility of Shape.";
	}
};

struct UnequalSizeError : public std::exception
{	
	const char* what() const throw()
	{
		return "ERROR: Check compatibility of Size.";
	}
};

struct SizeError : public std::exception
{	
	const char* what() const throw()
	{
		return "ERROR: Check compatibility of Size.";
	}
};

struct ArrayOutOfBounds : public std::exception
{	
	const char* what() const throw()
	{
		return "ERROR: Array Out Of Bounds.";
	}
};

#endif /* EXCEPTIONS_H */
