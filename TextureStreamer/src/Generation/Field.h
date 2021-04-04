#ifndef FIELD_H
#define FIELD_H

#include "Exceptions/OutOfRangeException.h"

template <typename T>
class Field
{
public:
	Field(unsigned int width, unsigned int height, T clearValue) :
		m_width(width),
		m_height(height),
		m_clearValue(clearValue)
	{
		m_data = new T[m_height * m_width];
		for(unsigned int i = 0; i < m_height * m_width; ++i)
			m_data[i] = m_clearValue;
	}

	virtual ~Field() {}

	T GetCell(unsigned int x, unsigned int y)
	{
		if( x >= m_width ) throw OutOfRangeException<unsigned int>("x", x, 0, m_width - 1);
		if( y >= m_height ) throw OutOfRangeException<unsigned int>("y", y, 0, m_height - 1);
		return m_data[y * m_width + x];
	}

	void SetCell(unsigned int x, unsigned int y, T value)
	{
		if( x >= m_width ) throw OutOfRangeException<unsigned int>("x", x, 0, m_width - 1);
		if( y >= m_height ) throw OutOfRangeException<unsigned int>("y", y, 0, m_height - 1);
		m_data[y * m_width + x] = value;
	}

	void Clear()
	{
		for(unsigned int i = 0; i < m_height * m_width; ++i)
			m_data[i] = m_clearValue;
	}

	inline const T* GetData() const
	{
		return m_data;
	}

	inline unsigned int GetWidth() const
	{
		return m_width;
	}

	inline unsigned int GetHeight() const
	{
		return m_height;
	}

private:
	unsigned int m_width;
	unsigned int m_height;
	T m_clearValue;

	T* m_data;
};

#endif // FIELD_H
