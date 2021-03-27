#ifndef OUTOFRANGEEXCEPTION_H
#define OUTOFRANGEEXCEPTION_H

#include <exception>
#include <string>
#include <sstream>

template <typename T>
class OutOfRangeException : public std::exception
{
public:
	OutOfRangeException(std::string name, T value, T minValue, T maxValue) :
		m_name(name),
		m_value(value),
		m_minValue(minValue),
		m_maxValue(maxValue)
	{}

	virtual ~OutOfRangeException() {}

	const char* what() const noexcept override
	{
		std::stringstream ss;
		ss << "Value " << m_name << "=" << m_value
		   << " is out of range [" << m_minValue << ", " << m_maxValue << "]";
		return ss.str().c_str();
	}

private:
	std::string m_name;
	T m_value;
	T m_minValue;
	T m_maxValue;
};

#endif // OUTOFRANGEEXCEPTION_H
