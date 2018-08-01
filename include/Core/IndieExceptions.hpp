/*
** EPITECH PROJECT, 2018
** IndieExceptions
** File description:
** Declaration of IndieExceptions
*/

#ifndef INDIE_STUDIO_INDIEEXCEPTIONS_HPP
	#define INDIE_STUDIO_INDIEEXCEPTIONS_HPP

#include <exception>
#include <string>

class IndieExceptions : public std::exception
{
public:
	explicit IndieExceptions(std::string const &msg, std::string const &type = "Unknown");
	const char *what() const noexcept final;
private:
	std::string msg;
	std::string type;
};

class InvalidMap : public IndieExceptions
{
public:
	explicit InvalidMap(std::string const &);
};

class ResourceNotFound : public IndieExceptions
{
public:
	explicit ResourceNotFound(std::string const &);
};

class InitialisationFailed : public IndieExceptions
{
public:
	explicit InitialisationFailed(std::string const &);
};

class InitError : public IndieExceptions
{
public:
	explicit InitError(std::string const &);
};

#endif //INDIE_STUDIO_INDIEEXCEPTIONS_HPP
