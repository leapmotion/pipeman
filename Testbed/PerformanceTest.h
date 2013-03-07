#pragma once

/// <summary>
/// This test verifies that the named pipe system transfers data at a certain
/// minimum transfer rate
/// </summary>
class PerformanceTest:
	public testing::Test
{
public:
	PerformanceTest(void);
	~PerformanceTest(void);
};

