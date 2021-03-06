/*
	Copyright (c) 2015 Xavier Leclercq

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

#include "ZoneFileTests.h"
#include "Ishiko/DNS/DNSCore.h"
#include <fstream>

void AddZoneFileTests(TestHarness& theTestHarness)
{
	TestSequence& zoneFileTestSequence = theTestHarness.appendTestSequence("ZoneFile tests");

	new HeapAllocationErrorsTest("Creation test 1", ZoneFileCreationTest1, zoneFileTestSequence);
	new FileComparisonTest("write test 1", ZoneFileWriteTest1, zoneFileTestSequence);
	new FileComparisonTest("write test 2", ZoneFileWriteTest2, zoneFileTestSequence);
}

TestResult::EOutcome ZoneFileCreationTest1()
{
	Ishiko::DNS::StartOfAuthorityRecord soaRecord("example.org.", Ishiko::DNS::ResourceRecord::CLASS_IN,
		86400, "ns1.example.org.", "hostmaster.example.org.", 1485619377, 1200, 120, 604800, 3600);
	Ishiko::DNS::ZoneFile zonefile(Ishiko::DNS::DomainName("example.org."), soaRecord);
	return TestResult::ePassed;
}

TestResult::EOutcome ZoneFileWriteTest1(FileComparisonTest& test)
{
	boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ZoneFileWriteTest1.txt");
	std::ofstream stream(outputPath.c_str());

	Ishiko::DNS::StartOfAuthorityRecord soaRecord("example.org.", Ishiko::DNS::ResourceRecord::CLASS_IN,
		86400, "ns1.example.org.", "hostmaster.example.org.", 1485619377, 1200, 120, 604800, 3600);
	Ishiko::DNS::ZoneFile zonefile(Ishiko::DNS::DomainName("example.org."), soaRecord);
	zonefile.write(stream);

	test.setOutputFilePath(outputPath);
	test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "ZoneFileWriteTest1.txt");

	return TestResult::ePassed;
}

TestResult::EOutcome ZoneFileWriteTest2(FileComparisonTest& test)
{
	boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ZoneFileWriteTest2.txt");
	std::ofstream stream(outputPath.c_str());

	Ishiko::DNS::StartOfAuthorityRecord soaRecord("example.org.", Ishiko::DNS::ResourceRecord::CLASS_IN,
		86400, "ns1.example.org.", "hostmaster.example.org.", 1485619377, 1200, 120, 604800, 3600);
	Ishiko::DNS::ZoneFile zonefile(Ishiko::DNS::DomainName("example.org."), soaRecord);
	std::shared_ptr<Ishiko::DNS::NameServerRecord> newRecord = 
		std::make_shared<Ishiko::DNS::NameServerRecord>("example.org.", Ishiko::DNS::ResourceRecord::CLASS_IN, 86400, "ns1.example.org.");
	zonefile.append(newRecord);
	zonefile.write(stream);

	test.setOutputFilePath(outputPath);
	test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "ZoneFileWriteTest2.txt");

	return TestResult::ePassed;
}
