/*
    Copyright (c) 2017 Xavier Leclercq

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

#include "TextRecord.h"
#include <boost/endian/conversion.hpp>

namespace Ishiko
{
namespace DNS
{

TextRecord::TextRecord()
{
}

TextRecord::TextRecord(const std::string& domainName,
                       uint32_t ttl,
                       const std::string& text)
    : ResourceRecord(domainName, TYPE_TXT, CLASS_IN, ttl),
    m_TXT(text)
{
}

Result TextRecord::initializeFromBuffer(const char* startPos,
                                        const char* endPos,
                                        const char** currentPos)
{
    Result result(Result::eSuccess);

    const char* localCurrentPos = *currentPos;

    if (result.update(initializeFromBufferBase(startPos, endPos, &localCurrentPos)).succeeded())
    {
        if ((localCurrentPos + 2) <= endPos)
        {
            uint16_t size = boost::endian::big_to_native(*(const uint16_t*)(localCurrentPos));
            localCurrentPos += 2;
            if ((localCurrentPos + size) <= endPos)
            {
                m_TXT.assign(localCurrentPos, size);
                *currentPos = localCurrentPos;
            }
            else
            {
                result.update(Result::eError);
            }
        }
        else
        {
            result.update(Result::eError);
        }
    }

    return result;
}

const std::string& TextRecord::text() const
{
    return m_TXT;
}

void TextRecord::writeBinary(std::ostream& stream) const
{
    writeBinaryBase(stream);
    uint16_t tmp = boost::endian::native_to_big((uint16_t)m_TXT.size());
    stream.write((const char*)&tmp, 2);
    stream.write(m_TXT.c_str(), m_TXT.size());
}

void TextRecord::writeText(std::ostream& stream) const
{
}

}
}
