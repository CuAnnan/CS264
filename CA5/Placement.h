#ifndef PLACEMENTHEADER_H
#define PLACEMENTHEADER_H

#include "Module.h"
#include <string>
#include <iostream>

using namespace std;

/**
 * Placement class definition.
 * @extends Module
 */
class Placement:public Module
{
    public:
        /**
         * Default constructor, zeroes everything and then explicitly sets credits to 15
         */
        Placement() : Module(), _description("")
        {
            // this is required by the spec. I'm not sure if it's possible to say "set this parent property"
            setCredits(15);
        };

        /**
         * Everything constructor, doesn't allow the setting of credits per reading of the specification
         */
        Placement(string name, string description, int students) : Module(name, students, 15), _description(description){};

        /**
         * Equality operator overload.
         */

        const bool operator==(Placement& that) const;

        /**
         * Setter and getter for description
         */
        const string getDescription() const;
        void setDescription(string _description);

        /**
         * toString method
         */
        const string toStr(unsigned int padding=0) const;


    private:
        /**
         * the description of the module.
         */
        string _description;
};

#endif