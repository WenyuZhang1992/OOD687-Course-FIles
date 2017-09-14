/////////////////////////////////////////////////////////////////////////
// Threads2.cpp - demonstrate midterm questions regarding threads      //
//                                                                     //
// WENYU ZHANG, CSE687 - Object Oriented Design, Spring 2017           //
/////////////////////////////////////////////////////////////////////////
#ifdef TEST_THREADS2
#include <iostream>
#include <functional>
#include <thread>

template <class CallObj>
std::thread threadCreator(CallObj& co) {
	std::thread t(co);
	return t;
}

void hello() {
	std::cout << "Hello from hello()!\n";
}

class Functor {
public:
	Functor() {}
	void operator()() { std::cout << "Hello from Functor!\n"; }
};

int main() {
	std::cout << "Demonstrate creating threads asynchronously:\n" << std::endl;

	std::thread t1 = threadCreator(hello);
	t1.join();

	Functor myFunctor;
	std::thread t2 = threadCreator(myFunctor);
	t2.join();

	std::function<void()> f = []() { std::cout << "Hello from lambda!\n"; };
	std::thread t3 = threadCreator(f);
	t3.join();
}

#endif // !TEST_THREADS2