/*
    Copyright (c) 2015-2017 Xavier Leclercq

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

#include "NameServerRecord.h"
#include <boost/endian/conversion.hpp>

namespace Ishiko
{
namespace DNS
{

NameServerRecord::NameServerRecord()
{
}

NameServerRecord::NameServerRecord(const std::string& domainName,
                                   CLASS cl, 
                                   uint32_t ttl, 
                                   const std::string& nsDomainName)
    : ResourceRecord(domainName, TYPE_NS, cl, ttl),
    m_NSDNAME(nsDomainName)
{
}

Result NameServerRecord::initializeFromBuffer(const char* startPos,
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
            DomainName tempDomainName;
            if (result.update(tempDomainName.initializeFromBuffer(startPos, endPos, &localCurrentPos)).succeeded())
            {
                if (size == tempDomainName.length())
                {
                    m_NSDNAME.swap(tempDomainName);
                    *currentPos = localCurrentPos;
                }
                else
                {
                    result.update(Result::eError);
                }
            }
        }
        else
        {
            result.update(Result::eError);
        }
    }

    return result;
}

const DomainName& NameServerRecord::nameServer() const
{
    return m_NSDNAME;
}

void NameServerRecord::writeBinary(std::ostream& stream) const
{
    writeBinaryBase(stream);
    uint16_t tmp = boost::endian::native_to_big(m_NSDNAME.length());
    stream.write((const char*)&tmp, 2);
    m_NSDNAME.writeBinary(stream);
}

void NameServerRecord::writeText(std::ostream& stream) const
{
    writeTextBase(stream);
    stream << " ";
    m_NSDNAME.writeText(stream);
}

}
}
