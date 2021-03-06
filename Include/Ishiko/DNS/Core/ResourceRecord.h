/*
    Copyright (c) 2010-2017 Xavier Leclercq

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

#ifndef _ISHIKO_DNS_CORE_RESOURCERECORD_H_
#define _ISHIKO_DNS_CORE_RESOURCERECORD_H_

#include "DomainName.h"
#include "TTL.h"
#include "Result.h"
#include <ostream>
#include <stdint.h>
#include <memory>

namespace Ishiko
{
namespace DNS
{

class ResourceRecord
{
public:
    enum TYPE
    {
        TYPE_A = 1,
        TYPE_NS = 2,
        TYPE_CNAME = 5,
        TYPE_SOA = 6,
        TYPE_MX = 15,
        TYPE_TXT = 16,
        TYPE_AAAA = 28
    };

    enum CLASS
    {
        CLASS_IN = 1
    };

public:
    static Result createFromBuffer(const char* startPos,
        const char* endPos, const char** currentPos,
        std::shared_ptr<ResourceRecord>& newRecord);

    ResourceRecord();
    ResourceRecord(const std::string& domainName,
        TYPE type, CLASS cl, uint32_t ttl);
    virtual ~ResourceRecord();

    virtual void writeBinary(std::ostream& stream) const = 0;
    virtual void writeText(std::ostream& stream) const = 0;

    const DomainName& name() const;
    TYPE type() const;
    CLASS cl() const;
    const TTL& ttl() const;

protected:
    Result initializeFromBufferBase(const char* startPos,
        const char* endPos, const char** currentPos);
    void writeBinaryBase(std::ostream& stream) const;
    void writeTextBase(std::ostream& stream) const;

private:
    DomainName m_NAME;
    uint16_t m_TYPE;
    uint16_t m_CLASS;
    TTL m_TTL;
};

}
}

#endif
