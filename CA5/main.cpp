#include "Module.h"
#include "Placement.h"
#include "Programme.h"

#include <iostream>

using namespace std;

/**
 * Main
 * This implements the classes in a "real" setting.
 */
int main()
{
    Module* m1 = new Module();
    m1->setName("CS264");
    m1->setStudents(181);
    m1->setCredits(5);

    Module* m2 = new Module();
    m2->setName("CS264");
    m2->setStudents(181);
    m2->setCredits(5);

    Placement *pl1 = new Placement();
    pl1->setName("CS35");
    pl1->setStudents(155);
    pl1->setDescription("This definitely works");
    
    
    Programme *pr1 = new Programme("CSSE", 3);

    pr1->addModule(m1);
    pr1->addModule(pl1);
    // this not be added because m1 is equal to m2 despite being different pointers.
    pr1->addModule(m2);

    cout << pr1->toStr() <<endl;

    delete m2;
    delete pr1;
    delete pl1;
    delete m1;
}
