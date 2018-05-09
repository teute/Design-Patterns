#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Beverage
{
public:
	Beverage() {
		description = "Unknown Beverage";
	}

	~Beverage() {}

	virtual string getDescription() {
		return description;
	}

	virtual double cost() = 0;

protected:
	string description;
};

class CondimentDecorator : public Beverage
{
public:
	CondimentDecorator(shared_ptr<Beverage> bev) : beverage(bev) {}

	virtual string getDescription() = 0;

protected:
	shared_ptr<Beverage> beverage;
};

class Espresso : public Beverage
{
public:
	Espresso() {
		description = "Espresso";
	}

	double cost() {
		return 1.99;
	}
};

class HouseBlend : public Beverage
{
public:
	HouseBlend() {
		description = "House Blend Coffee";
	}

	double cost() {
		return .89;
	}
};

class DarkRoast : public Beverage
{
public:
	DarkRoast() {
		description = "Dark Roast Coffee";
	}

	double cost() {
		return .89;
	}
};

class Mocha : public CondimentDecorator
{
public:
	Mocha(shared_ptr<Beverage> bev) : CondimentDecorator(bev) {}

	string getDescription() {
		return beverage->getDescription() + ", Mocha";
	}

	double cost() {
		return .20 + beverage->cost();
	}
};

class Whip : public CondimentDecorator
{
public:
	Whip(shared_ptr<Beverage> bev) : CondimentDecorator(bev) {}

	string getDescription() {
		return beverage->getDescription() + ", Whip";
	}

	double cost() {
		return .15 + beverage->cost();
	}
};

class Soy : public CondimentDecorator
{
public:
	Soy(shared_ptr<Beverage> bev) : CondimentDecorator(bev) {}

	string getDescription() {
		return beverage->getDescription() + ", Soy";
	}

	double cost() {
		return .10 + beverage->cost();
	}
};
//=========================
class I // Common base class
{
public:
	virtual ~I() {}
	virtual void do_it() = 0;
};

class A : public I // Subject base class
{
public:
	~A() { cout << "A dtor" << endl; }

	void do_it() { cout << 'A'; }
};

class D : public I // Decorator base class
{
public:
	D(I* inner) { m_wrappee = inner; }
	~D() { delete m_wrappee; }
	void do_it() { m_wrappee->do_it(); }

private:
	I* m_wrappee;
};

class X : public D // Concrete decorator class
{
public:
	X(I* core) : D(core) {}
	~X() { cout << "X dtor" << " "; }
	void do_it() {
		D::do_it();
		cout << 'X';
	}
};

class Y : public D // Concrete decorator class
{
public:
	Y(I* core) : D(core) {}
	~Y() { cout << "Y dtor" << " "; }
	void do_it() {
		D::do_it();
		cout << 'Y';
	}
};

class Z : public D // Concrete decorator class
{
public:
	Z(I* core) : D(core) {}
	~Z() { cout << "Z dtor" << " "; }
	void do_it() {
		D::do_it();
		cout << 'Z';
	}
};

int main()
{
	shared_ptr<Beverage> beverage(new Espresso());
	cout << beverage->getDescription() << " $" << beverage->cost() << endl;

	shared_ptr<Beverage> beverage2(new DarkRoast());
	shared_ptr<Beverage> beverage3(new Mocha(beverage2));
	shared_ptr<Beverage> beverage4(new Mocha(beverage3));
	shared_ptr<Beverage> beverage5(new Whip(beverage4));
	cout << beverage5->getDescription() << " $" << beverage5->cost() << endl;

	I* anX = new X(new A);
	I* anXY = new Y(new X(new A));
	I* anXYZ = new Z(new Y(new X(new A)));
	anX->do_it(); cout << endl;
	anXY->do_it(); cout << endl;
	anXYZ->do_it(); cout << endl;
	delete anX; delete anXY; delete anXYZ;

	return 0;
}