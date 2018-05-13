#include <iostream>

using namespace std;

class Singleton
{
public:
	static Singleton& getInstance() {
		static Singleton instance;
		return instance;
	}

	/* Override the default copy constructor and assignment operator so so that
	a copy cannot be made of the singleton */
	Singleton(Singleton const&) = delete;		// copy constructor
	void operator=(Singleton const&) = delete;	// assignment operator

	void foo() {
		cout << "Singleton" << endl;
	}

private:
	Singleton() {}
};

int main()
{
	cout << &Singleton::getInstance() << endl;
	Singleton::getInstance().foo();
	cout << &Singleton::getInstance() << endl;

	return 0;
}