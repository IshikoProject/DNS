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

#ifndef _ISHIKO_DNS_CORE_ZONEFILE_H_
#define _ISHIKO_DNS_CORE_ZONEFILE_H_

#include "DomainName.h"
#include "StartOfAuthorityRecord.h"
#include <vector>
#include <ostream>

namespace Ishiko
{
namespace DNS
{

// A zone file is a text file that describes a DNS zone.
class ZoneFile
{
public:
	ZoneFile(const DomainName& origin,
		const StartOfAuthorityRecord& soaRecord);

	void write(std::ostream& stream) const;

	void append(std::shared_ptr<ResourceRecord> record);

private:
	DomainName m_origin;
	StartOfAuthorityRecord m_soaRecord;
	std::vector<std::shared_ptr<ResourceRecord> > m_records;
};

}
}

#endif
