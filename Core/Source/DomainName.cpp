/*
	Copyright (c) 2009-2015 Xavier Leclercq

	Permission is hereby granted, free of charge, to any person obtaining a
	copy of this software and associated documentation files (the "Software"),
	to deal in the Software without restriction, including without limitation
	the rights to use, copy, modify, merge, publish, distribute, sublicense,
	and/or sell copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
	THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
	IN THE SOFTWARE.
*/

#include "DomainName.h"
#include <stdint.h>

namespace Ishiko
{
namespace DNS
{

DomainName::DomainName(const std::string& domainName)
	: m_name(domainName)
{
}

DomainName::DomainName(std::istream& stream)
{
	uint8_t labelSize;
	stream.read((char*)&labelSize, 1);
	while (labelSize)
	{
		char buffer[255];
		stream.read(buffer, labelSize);
		m_name.append(buffer, labelSize);
		m_name.append(".");

		stream.read((char*)&labelSize, 1);
	}
}

uint16_t DomainName::length() const
{
	uint16_t result = 1;

	size_t prevPos = 0;
	size_t nextPos = m_name.find('.', 1);
	while (nextPos != std::string::npos)
	{
		uint8_t labelSize = (uint8_t)(nextPos - prevPos);
		
		result += (1 + labelSize);

		prevPos = nextPos + 1;
		nextPos = m_name.find('.', prevPos);
	}
	if (m_name.size() > prevPos)
	{
		uint8_t labelSize = m_name.size() - prevPos;

		result += (1 + labelSize);
	}

	return result;
}

void DomainName::write(std::ostream& stream) const
{
	size_t prevPos = 0;
	size_t nextPos = m_name.find('.', 1);
	while (nextPos != std::string::npos)
	{
		uint8_t labelSize = (uint8_t)(nextPos - prevPos);
		stream.write((char*)&labelSize, 1);
		stream.write(m_name.c_str() + prevPos, labelSize);

		prevPos = nextPos + 1;
		nextPos = m_name.find('.', prevPos);
	}
	if (m_name.size() > prevPos)
	{
		uint8_t labelSize = m_name.size() - prevPos;
		stream.write((char*)&labelSize, 1);
		stream.write(m_name.c_str() + prevPos, labelSize);
	}
	stream.write("", 1);
}

const std::string& DomainName::str() const
{
	return m_name;
}

bool DomainName::operator==(const DomainName& other) const
{
	return (m_name == other.m_name);
}

bool DomainName::operator==(const std::string& other) const
{
	return (m_name == other);
}

bool DomainName::operator!=(const DomainName& other) const
{
	return (m_name != other.m_name);
}

bool DomainName::operator!=(const std::string& other) const
{
	return (m_name != other);
}

}
}
