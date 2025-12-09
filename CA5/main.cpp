#include "Module.h"
#include "Placement.h"
#include "Programme.h"

#include <iostream>

using namespace std;


int main()
{
    Module* m1 = new Module();
    m1->setName("CS264");
    m1->setStudents(181);
    m1->setCredits(5);

    Placement *pl1 = new Placement();
    pl1->setName("P135");
    
    
    Programme *pr1 = new Programme("CSSE", 3);

    pr1->addModule(m1);
    pr1->addModule(pl1);

    cout << pr1->toStr() <<endl;


    delete pr1;
    delete pl1;
    delete m1;
}
