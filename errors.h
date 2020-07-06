#pragma once
#include <exception>
#include <cstring>
#include <string>

class repoError : public std::exception
{
private:
	char error[1001];
public:
	repoError() {}
	repoError(const char* const Message) { strcpy(this->error, Message); }
	const char* what() const throw() {
		return this->error;
	}
};

class validationError : public std::exception
{
private:
	char error[1001];
public:
	validationError() {}
	validationError(const char* const Message) { strcpy(this->error, Message); }
	const char* what() const throw() {
		return this->error;
	}
};

class serviceError : public std::exception
{
private:
	char error[1001];
public:
	serviceError() {}
	serviceError(const char* const Message) { strcpy(this->error, Message); }
	const char* what() const throw() {
		return this->error;
	}
};