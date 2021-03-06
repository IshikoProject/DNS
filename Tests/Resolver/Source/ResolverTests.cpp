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

#include "ResolverTests.h"
#include "Ishiko/DNS/DNSResolver.h"
#include <fstream>

void AddResolverTests(TestHarness& theTestHarness)
{
	TestSequence& resolverTestSequence = theTestHarness.appendTestSequence("Resolver tests");

	new HeapAllocationErrorsTest("Creation test 1", ResolverCreationTest1, resolverTestSequence);
	new FileComparisonTest("getResourceRecords test 1", ResolverGetResourceRecordsTest1, resolverTestSequence);
}

TestResult::EOutcome ResolverCreationTest1()
{
	Ishiko::DNS::Resolver resolver;
	return TestResult::ePassed;
}

TestResult::EOutcome ResolverGetResourceRecordsTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ResolverGetResourceRecordsTest1.txt");
    std::ofstream stream(outputPath.c_str());

	Ishiko::DNS::Resolver resolver;

    std::vector<std::shared_ptr<Ishiko::DNS::ResourceRecord> > records;
	resolver.getResourceRecords("needfulsoftware.com", records);

    for (auto record : records)
    {
        record->writeText(stream);
    }

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "ResolverGetResourceRecordsTest1.txt");


	return TestResult::ePassed;
}
