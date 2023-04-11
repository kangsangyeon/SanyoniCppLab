#include <iostream>
#include <chrono>
#include <functional>
#include <chrono>
#include <thread>

#include <Windows.h>

static constexpr size_t TEST_COUNT = 5'000'000;

void RunTest(std::string _testName, int _testCount, std::function<void()> _test)
{
	auto _start = std::chrono::system_clock::now();
	for (size_t i = 0; i < _testCount; i++)
		_test();

	auto _end = std::chrono::system_clock::now();
	auto _elapsedTimeNanos
		= std::chrono::duration_cast<std::chrono::nanoseconds>(_end - _start);
	auto _elapsedTimeMicros
		= std::chrono::duration_cast<std::chrono::microseconds>(_end - _start);
	auto _elapsedTimeMillis
		= std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start);

	std::cout << "TEST: " << _testName << std::endl;
	std::cout << "  Test Count: " << _testCount << std::endl;
	std::cout << "  Elapsed Time: " << std::endl;
	std::cout << "      (millis): " << _elapsedTimeMillis.count() << "ms" << std::endl;
	std::cout << "      (micros): " << _elapsedTimeMicros.count() << "us" << std::endl;
	std::cout << "      (nanos): " << _elapsedTimeNanos.count() << "ns" << std::endl;
	std::cout << std::endl;
}

int main()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));

	std::cout << "call GetAsyncKeyState()" << std::endl;
	auto _start = GetAsyncKeyState(VK_RIGHT);

	// wait for 2 seconds...
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));

	std::cout << "call GetAsyncKeyState()" << std::endl;
	auto _end = GetAsyncKeyState(VK_RIGHT);

	// 
	std::cout << "start: " << _start << std::endl;
	std::cout << "end: " << _end << std::endl;

	std::this_thread::sleep_for(std::chrono::milliseconds(2000));

	return 0;
}
