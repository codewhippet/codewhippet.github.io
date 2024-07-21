#include <coroutine>
#include <stdio.h>

// -----------------------------------------------------------------------------
// First example

struct MyFirstCoroutine
{
	struct promise_type
	{
		std::suspend_always yield_value(int i)
		{
			return {};
		}

		MyFirstCoroutine get_return_object()
		{
			return MyFirstCoroutine(std::coroutine_handle<promise_type>::from_promise(*this));
		}

		std::suspend_never initial_suspend() { return {}; }
		std::suspend_never final_suspend() noexcept { return {}; }

		void return_void() {}
		void unhandled_exception() {}
	};

	std::coroutine_handle<promise_type> MyHandle;

	MyFirstCoroutine(std::coroutine_handle<promise_type> handle)
		: MyHandle(handle)
	{
	}
};

MyFirstCoroutine DoStuff()
{
	printf("Doing first thing\n");
	co_yield 0;
	printf("Doing second thing\n");
}

void CallStuff()
{
	auto doingStuff = DoStuff();
	doingStuff.MyHandle.resume();
}

MyFirstCoroutine DoMoreStuff()
{
	printf("Doing first thing\n");
	co_yield 0;
	printf("Doing second thing\n");
	co_yield 0;
	printf("Doing third thing\n");
	co_yield 0;
	printf("Doing fourth thing\n");
}

void CallMoreStuff()
{
	auto doingStuff = DoMoreStuff();
	doingStuff.MyHandle.resume();
	doingStuff.MyHandle.resume();
	doingStuff.MyHandle.resume();
}

// -----------------------------------------------------------------------------

void CoroutinesForDinosaurs()
{
	CallStuff();
	CallMoreStuff();
}
