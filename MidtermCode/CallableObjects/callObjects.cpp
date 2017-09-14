/////////////////////////////////////////////////////////////////////////
// callObject.cpp - demonstrate midterm questions regarding            //
//                  callable objects                                   //
//                                                                     //
// WENYU ZHANG, CSE687 - Object Oriented Design, Spring 2017           //
/////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <functional>

template <typename CallObj>
void Executor(CallObj& co) {
	co();
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
	std::cout << "Demonstrating Callable Objects:\n" << std::endl;
	Executor(hello);          // invoke by function
	Functor myFunctor;
	Executor(myFunctor);      // invoke by functor
	// invoke by function pointer
	std::function<void()> lambda = []() { std::cout << "Hello from lambda!\n"; };
	Executor(lambda);         // invoke by lambda

}