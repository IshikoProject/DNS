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

#ifndef _ISHIKO_DNS_CORE_HEADERMESSAGESECTION_H_
#define _ISHIKO_DNS_CORE_HEADERMESSAGESECTION_H_

#include "Result.h"
#include <ostream>
#include <stdint.h>

namespace Ishiko
{
namespace DNS
{

class HeaderMessageSection
{
public:
    HeaderMessageSection();
    HeaderMessageSection(bool isResponse);

    Result initializeFromBuffer(const char* startPos,
        const char* endPos, const char** currentPos);

    void write(std::ostream& stream) const;

    bool isResponse() const;
    uint16_t questionCount() const;
    void setQuestionCount(uint16_t count);
    uint16_t answerCount() const;
    void setAnswerCount(uint16_t count);

    void swap(HeaderMessageSection& other);

private:
    uint16_t m_ID;
    uint16_t m_bitField;
    uint16_t m_QDCOUNT;
    uint16_t m_ANCOUNT;
    uint16_t m_NSCOUNT;
    uint16_t m_ARCOUNT;
};

inline
void swap(HeaderMessageSection& hs1, HeaderMessageSection& hs2)
{
    hs1.swap(hs2);
}

}
}

#endif
