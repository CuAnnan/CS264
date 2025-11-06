#include "Inheritance.h"
#include <iostream>
#include <string>

using namespace std;

Mammal::Mammal()
{
    sprintf(this->name, "Mammal %d", ++this->count);
}

Mammal::Mammal(char* name)
{
    this->count++;
    this->name = name;
}

void Mammal::eat()
{
    cout << "Mammals eat food"<<endl;
}

Mammal::~Mammal()
{
    delete this->name;
}

Dog::Dog()
{
    sprintf(this->name, "Dog %d", ++this->count);
}

Dog::Dog(char* name)
{
    this->name = name;
}

void Dog::eat()
{
    cout << "Dogs eat dog food"<<endl;
}

Dog::~Dog()
{
    delete this->name;
}

void Cat::eat()
{
    cout << "Cats eat cat food"<<endl;
}



int main()
{
    Mammal* mammals[5];
    mammals[0] = new Mammal();
    mammals[1] = new Mammal("Frank");
    mammals[2] = new Dog("Doggo");
    
    return 0;
}