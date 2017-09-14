/////////////////////////////////////////////////////////////////////////
// threads.cpp - demonstrate midterm questions regarding threads       //
//                                                                     //
// WENYU ZHANG, CSE687 - Object Oriented Design, Spring 2017           //
/////////////////////////////////////////////////////////////////////////
#ifdef TEST_THREADS
#include <iostream>
#include <functional>
#include <thread>

void run(int param1, int param2) {
	std::cout << "Two arguments are " << param1 << " and " << param2 << std::endl;
}

class Functor {
public:
	Functor(int param1, int param2)
		:param1_(param1),
		param2_(param2)
	{}

	void operator()() { std::cout << "Two arguments are " << param1_ << " and " << param2_ << std::endl; }

private:
	int param1_;
	int param2_;
};

int main() {
	std::cout << "Demonstrating Threads using callable objects:\n";
	std::thread t1(run, 1, 2);
	t1.join();

	Functor myFunctor(1, 2);
	std::thread t2(myFunctor);
	t2.join();

	int param1 = 1;
	int param2 = 2;
	std::function<void()> lambda = [param1, param2]() {std::cout << "Two arguments are " << param1 << " and " << param2 << std::endl; };
	std::thread t3(lambda);
	t3.join();
}
#endif // !TEST_THREADS
