#include <iostream>
#include <chrono>
#include <functional>

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
	/*
	* GetKeyState()
	*/
	RunTest("GetKeyState()", TEST_COUNT, []()-> void
	{
		GetKeyState(VK_RIGHT);
	});

	/*
	* GetKeyboardState()
	*/

	BYTE _keyboardStates[256];
	RunTest("GetKeyboardState()", TEST_COUNT, [&_keyboardStates]()-> void
	{
		GetKeyboardState(_keyboardStates);
	});

	/*
	* GetAsyncKeyState()
	*/

	RunTest("GetAsyncKeyState()", TEST_COUNT, []()-> void
	{
		GetAsyncKeyState(VK_RIGHT);
	});

	return 0;
}
