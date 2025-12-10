#include "Module.h"
#include <string>
#include <iostream>

using namespace std;


/**
 * Implementation of missing methods for Module.
 * Both the default and copy constructors are defined in the header file because they instantiate only instantiate primitive values
 * Yes. I know that strings aren't technically primitives. But they're essentially primitives for the purposes of deconstrcutors.
 */


/**
 * Getter for name
 * @return The name of the module
 */
string Module::getName() const
{
    return this->_name;
}

/**
 * Setter for name
 * @param name The name to give the module.
 */
void Module::setName(const string name)
{
    this->_name = name;
}

/**
 * Getter for the number of students
 * @return The number of students in the module
 */
unsigned int Module::getStudents() const
{
    return this->_students;
}

/**
 * Setter for the number of students.
 * @param students The number of students in the module.
 */
void Module::setStudents(const unsigned int students)
{
    this->_students = students;
}

/**
 * Getter for credits
 * @return The number of credits this module is worth.
 */
unsigned int Module::getCredits() const
{
    return this->_credits;
}

/**
 * Setter for credits
 * @param credits The number of credits this module is worth.
 */
void Module::setCredits(const unsigned int credits)
{
    this->_credits = credits;
}

/**
 * Operator overloader for equality
 * Sameness is defined as the name and credit values BOTH being the same.
 * @param that The module to compare to this module for equality
 * @returns True if the modules are the same. 
 */
bool Module::operator==(Module* that)
{
    return (this->_name.compare(that->_name) == 0) && this->_credits == that->_credits;
}


/**
 * toString helper function
 * @param padding the number of tabs to prefix the string with.
 * @return The object's string representation
 */
const string Module::toStr(const unsigned int padding) const
{
    string out = "";
    for(int i = 0; i < padding; i++)
    {
        out = out + "\t";
    }
    out += "[Module: name=\""+this->_name+"\" students="+to_string(this->_students)+" credits="+to_string(this->_credits)+"]";
    return out;
}