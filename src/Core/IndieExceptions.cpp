/*
** EPITECH PROJECT, 2018
** IndieExceptions
** File description:
** Implementation of IndieExceptions
*/

#include "IndieExceptions.hpp"

IndieExceptions::IndieExceptions(std::string const &message,
					std::string const &component) : std::exception()
{
	this->type = component;
	this->msg = this->type + ": " + message;
}

const char *IndieExceptions::what() const noexcept
{
	return this->msg.c_str();
}

InvalidMap::InvalidMap(std::string const &msg) : IndieExceptions(msg, "InvalidMap")
{

}

ResourceNotFound::ResourceNotFound(std::string const &msg) : IndieExceptions(msg, "ResourceNotFound")
{

}

InitialisationFailed::InitialisationFailed(std::string const &msg) : IndieExceptions(msg, "InitialisationFailed")
{

}

InitError::InitError(std::string const &msg) : IndieExceptions(msg, "InitError")
{

}
