#include <exception>
#include <string>

// custom exception to use for debugging
struct GeneralException : public std::exception
{
protected:
	std::string errorMsg;

public:
	GeneralException(std::string str)
	{
		errorMsg = str;
	}
	const char* what() const throw()
	{
		return errorMsg.c_str();
	}
};

struct NoFileFoundException : public GeneralException
{
protected:
	const char* errorMsg;

public:
	NoFileFoundException(std::string str) : GeneralException("Unable to load asset, file was : " + str) {}
};
