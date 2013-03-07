#include "stdafx.h"
#include "PerformanceTest.h"
#include "../PipeManLib/Client.h"
#include "../PipeManLib/Server.h"
#include <mutex>
#include <thread>

using std::mutex;
using std::thread;

void barrier(mutex& lock)
{
	lock_guard<mutex> lk(lock);
}

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

	// This is the data rate we are targeting, in MBPS
	static const int minDatarate = 100;

	// Total size of each buffer, and the number of buffers total we will move
	static const size_t bufSize = 0x1000 * 0x1000;
	static const size_t moveCount = 1000;



	// First, create a client and a server in their own threads:
	thread client([&startLock] () {
		CClientNative client(TEST_NAME);

		// Wait at the barrier:
		barrier(startLock);

		// Now we pull out samples until there aren't anymore:
		while(client.Flip());
	});
	thread server([&startLock] () {
		CServerNative server(TEST_NAME, 16, bufSize);

		// Wait at the barrier:
		barrier(startLock);

		// Attempt to send the number of requested buffers:
		for(size_t i = moveCount; i--;)
		{
			// Simulate a fill operation:
			char* pBuf = (char*)server.Get();
			for(size_t j = 0; j < bufSize; j++)
				pBuf[j] = (char)j;

			// Flip:
			bool ok = server.Flip(50);
			EXPECT_TRUE(ok) << "The server generated samples faster than the client could dispatch them";
			if(!ok)
				return;
		}
	});

	// Mark the start time and then start the threads running:
	clock_t startTime = clock();
	startLock.unlock();

	// Wait for the client and server to complete:
	client.join();
	server.join();

	// Compute the datarate, in mbps:
	int duration = clock() - startTime;
	int datarate = (bufSize * moveCount) / (1024 * 1024 * 1024);

	// Verify we transferred enough data in time:
	EXPECT_LT(minDatarate, datarate) << "The processing loop could only process samples at " << datarate << " MBPS";
}