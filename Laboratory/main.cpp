#include <iostream>

using namespace std;

class WeaponBehaviour /* Interface */
{
public:
	virtual void fight() = 0;
};

class SwordBehaviour : public WeaponBehaviour
{
public:
	void fight() {
		cout << "Swinging a sword." << endl;
	}
};

class KnifeBehaviour : public WeaponBehaviour
{
public:
	void fight() {
		cout << "Cutting with a knife" << endl;
	}
};

class BowAndArrowBehaviour : public WeaponBehaviour
{
public:
	void fight() {
		cout << "Shooting an arrow with a bow." << endl;
	}
};

class AxeBehaviour : public WeaponBehaviour
{
public:
	void fight() {
		cout << "Chopping with an axe." << endl;
	}
};

class Character
{
public:
	Character() {
		weapon = nullptr;
	}

	virtual ~Character() {
		if (weapon != nullptr) { // release memory before object is destroyed
			delete weapon;
			weapon = nullptr;
			//cout << "Released character memory!" << endl;
		}
	}

	void fight() {
		if (weapon != nullptr)
			weapon->fight();
	}

	void setWeapon(WeaponBehaviour* w) {
		if (weapon != nullptr) {
			delete weapon;
			weapon = nullptr;
		}

		if (w != nullptr) {
			weapon = w;
		}
	}

private:
	WeaponBehaviour* weapon;
};

class King : public Character
{
public:
	King() {
		setWeapon(new SwordBehaviour());
	}

	virtual ~King() {}
};

class Knight : public Character
{
public:
	Knight() {
		setWeapon(new BowAndArrowBehaviour());
	}

	virtual ~Knight() {}
};

int main(int argc, char* argv[])
{
	Character* king = new King();
	Character* knight = new Knight();

	king->fight();
	knight->fight();
	king->setWeapon(new AxeBehaviour()); // dynamically change weapon behaviour/algorithm
	king->fight();

	delete king;
	king = nullptr;
	
	delete knight;
	knight = nullptr;

	return 0;
}