#include "stdafx.h"
#include "PerformanceTest.h"
#include <mutex>
#include <thread>

using std::mutex;
using std::thread;

PerformanceTest::PerformanceTest(void)
{
}

PerformanceTest::~PerformanceTest(void)
{
}

TEST_F(PerformanceTest, VerifyBigBufferSpeed)
{
	mutex startLock;
	startLock.lock();

	// First, create a client and a server in their own threads:
	thread client([] () {
	});
	thread serve([] () {
	});
}