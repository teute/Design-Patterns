#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Pizza
{
public:
	virtual ~Pizza() {}

	virtual void prepare() {
		cout << "Preparing " << name << endl;
		cout << "Tossing dough..." << endl;
		cout << "Adding sauce..." << endl;
		cout << "Adding toppings: " << endl;
		for (vector<string>::iterator itr = toppings.begin(); itr != toppings.end(); ++itr) {
			cout << '\t' << *itr << endl;
		}
	}

	virtual void bake() {
		cout << "Bake for 25 minutes at 350" << endl;
	}

	virtual void cut() {
		cout << "Cutting the pizza into diagonal slices" << endl;
	}

	virtual void box() {
		cout << "Place pizza in official PizzaStore box" << endl;
	}

	string getName() {
		return name;
	}

protected:
	string name;
	string dough;
	string sauce;
	vector<string> toppings;
};

class NYStyleCheesePizza : public Pizza
{
public:
	NYStyleCheesePizza() {
		name = "NY Style Sauce and Cheese Pizza";
		dough = "Thin Crust Dough";
		sauce = "Marinara Sauce";

		toppings.push_back("Grated Reggiano Cheese");
	}

	~NYStyleCheesePizza() {}
};

class ChicagoStyleCheesePizza : public Pizza
{
public:
	ChicagoStyleCheesePizza() {
		name = "Chicago Style Deep Dish Cheese Pizza";
		dough = "Extra Thick Crust Dough";
		sauce = "Plum Tomato Sauce";

		toppings.push_back("Shredded Mozzarella Cheese");
	}

	~ChicagoStyleCheesePizza() {}

	void cut() {
		cout << "Cutting the pizza into square slices" << endl;
	}
};

class PizzaStore
{
public:
	Pizza* orderPizza(string type) {
		Pizza* pizza = createPizza(type);

		pizza->prepare();
		pizza->bake();
		pizza->cut();
		pizza->box();

		return pizza;
	}

	virtual ~PizzaStore() {}

	virtual Pizza* createPizza(string type) = 0;
};

class NYPizzaStore : public PizzaStore
{
public:
	Pizza* createPizza(string type) {
		if (type == "cheese") {
			return new NYStyleCheesePizza();
		}
		else if (type == "veggie") {
			return nullptr;
		}
		else if (type == "clam") {
			return nullptr;
		}
		return nullptr;
	}
};

class ChicagoPizzaStore : public PizzaStore
{
public:
	Pizza* createPizza(string type) {
		if (type == "cheese") {
			return new ChicagoStyleCheesePizza();
		}
		else if (type == "veggie") {
			return nullptr;
		}
		else if (type == "clam") {
			return nullptr;
		}
		return nullptr;
	}
};

class CarliforniaPizzaStore : public PizzaStore
{
public:
	Pizza* createPizza(string type) {
		return nullptr;
	}
};

int main()
{
	PizzaStore* nyStore = new NYPizzaStore();
	PizzaStore* chicagoStore = new ChicagoPizzaStore();

	Pizza* pizza = nyStore->orderPizza("cheese");
	cout << "Ethan ordered a " << pizza->getName() << endl << endl;
	delete pizza;

	pizza = chicagoStore->orderPizza("cheese");
	cout << "Joel ordered a " << pizza->getName() << endl;

	delete pizza;
	delete nyStore;
	delete chicagoStore;

	return 0;
}
