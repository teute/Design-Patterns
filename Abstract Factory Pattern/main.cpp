#include <iostream>
#include <string>
#include <vector>

using namespace std;

// TODO: refactor to use smart pointers instead of raw pointers

class Dough;
class Sauce;
class Cheese;
class Veggies;
class Pepperoni;
class Clams;

/*struct VeggieBunch
{
	Veggies* veggies = nullptr;
	int length = 0;
};*/

class PizzaIngredientFactory
{
public:
	virtual Dough* createDough() = 0;
	virtual Sauce* createSauce() = 0;
	virtual Cheese* createCheese() = 0;
	//virtual Veggies* createVeggies() = 0;
	//virtual Pepperoni* createPepperoni() = 0;
	//virtual Clams* createClam() = 0;
};

class Dough
{
public:
	Dough(string name) {
		this->name = name;
	}

	~Dough() {}

	string getName() {
		return name;
	}

private:
	string name;
};

class Sauce
{
public:
	Sauce(string name) {
		this->name = name;
	}

	~Sauce() {}

	string getName() {
		return name;
	}
private:
	string name;
};

class Cheese
{
public:
	Cheese(string name) {
		this->name = name;
	}

	~Cheese() {}

	string getName() {
		return name;
	}
private:
	string name;
};

/*class Veggies
{
public:
};

class Pepperoni
{
public:
};

class Clams
{
public:
};*/

class ThinCrustDough : public Dough
{
public:
	ThinCrustDough() : Dough("Thin Crust Dough") {}
};

class ThickCrustDough : public Dough
{
public:
	ThickCrustDough() : Dough("Thick Crust Dough") {}
};

class MarinaraSauce : public Sauce
{
public:
	MarinaraSauce() : Sauce("Marinara Sauce") {}
};

class PlumTomatoSauce : public Sauce
{
public:
	PlumTomatoSauce() : Sauce("Plum Tomato Sauce") {}
};

class ReggianoCheese : public Cheese
{
public:
	ReggianoCheese() : Cheese("Reggiano Cheese") {}
};

class MozzarellaCheese : public Cheese
{
public:
	MozzarellaCheese() : Cheese("Mozzarella Cheese") {}
};

class NYPizzaIngredientFactory : public PizzaIngredientFactory
{
public:
	Dough* createDough() {
		return new ThinCrustDough();
	}

	Sauce* createSauce() {
		return new MarinaraSauce();
	}

	Cheese* createCheese() {
		return new ReggianoCheese();
	}
};

class ChicagoPizzaIngredientFactory : public PizzaIngredientFactory
{
public:
	Dough* createDough() {
		return new ThickCrustDough();
	}

	Sauce* createSauce() {
		return new PlumTomatoSauce();
	}

	Cheese* createCheese() {
		return new MozzarellaCheese();
	}
};

class Pizza
{
public:
	Pizza() {
		slices = "diagonal";
	}

	virtual ~Pizza() {
		if (dough != nullptr)
			delete dough;
		if (sauce != nullptr)
			delete sauce;
		if (cheese != nullptr)
			delete cheese;
	}

	virtual void prepare() = 0;

	virtual void bake() {
		cout << "Bake for 25 minutes at 350" << endl;
	}

	virtual void cut() {
		cout << "Cutting the pizza into " << slices << " slices" << endl;
	}

	virtual void box() {
		cout << "Place pizza in official PizzaStore box" << endl;
	}

	string getName() {
		return name;
	}

	void setName(string name) {
		this->name = name;
	}

	void setSlices(string slices) {
		this->slices = slices;
	}

	/*friend ostream &operator<<(ostream& strm, Pizza& pizza) {
		cout << "Preparing " << pizza.getName() << endl;
		cout << "Tossing " << pizza.dough->getName() << "..." << endl;
		cout << "Adding " << pizza.sauce->getName() << "..." << endl;
		cout << "Adding toppings: " << endl;
		cout << '\t' << pizza.cheese->getName() << endl;
	}*/

protected:
	string name;
	string slices;
	Dough* dough;
	Sauce* sauce;
	Cheese* cheese;
};

class CheesePizza : public Pizza
{
public:
	CheesePizza(PizzaIngredientFactory* ingredientFactory) {
		this->ingredientFactory = ingredientFactory;
	}

	~CheesePizza() {
		if (ingredientFactory != nullptr)
			delete ingredientFactory;
	}

	void prepare() {
		cout << "Preparing " << getName() << endl;
		dough = ingredientFactory->createDough();
		sauce = ingredientFactory->createSauce();
		cheese = ingredientFactory->createCheese();

		cout << "Tossing " << dough->getName() << "..." << endl;
		cout << "Adding " << sauce->getName() << "..." << endl;
		cout << "Adding toppings: " << endl;
		cout << '\t' << cheese->getName() << endl;
	}

private:
	PizzaIngredientFactory* ingredientFactory;
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
	Pizza* createPizza(string item) {
		Pizza* pizza = nullptr;
		PizzaIngredientFactory* ingredientFactory = new NYPizzaIngredientFactory();

		if (item == "cheese") {
			pizza = new CheesePizza(ingredientFactory);
			pizza->setName("New York Style Cheese Pizza");
		}
		else if (item == "veggie") {
			return nullptr;
		}
		else if (item == "clam") {
			return nullptr;
		}
		return pizza;
	}
};

class ChicagoPizzaStore : public PizzaStore
{
public:
	Pizza* createPizza(string item) {
		Pizza* pizza = nullptr;
		PizzaIngredientFactory* ingredientFactory = new ChicagoPizzaIngredientFactory();

		if (item == "cheese") {
			pizza = new CheesePizza(ingredientFactory);
			pizza->setName("Chicago Style Deep Dish Cheese Pizza");
			pizza->setSlices("square");
		}
		else if (item == "veggie") {
			return nullptr;
		}
		else if (item == "clam") {
			return nullptr;
		}
		return pizza;
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