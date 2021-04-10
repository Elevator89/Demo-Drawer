#pragma once

#include <exception>
#include <string>

class Exception : public std::exception
{
public:
	Exception(const std::string& message);
	virtual ~Exception();

	const char* what() const noexcept override;

private:
	const std::string m_message;
};
