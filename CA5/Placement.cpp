#include "Placement.h"
#include <string>
#include <iostream>

using namespace std;


/**
 * Setter for description
 * @param description The new value to set description to
 */
void Placement::setDescription(string description)
{
    this->_description = description;
}

/**
 * The getter for description
 */
const string Placement::getDescription() const
{
    return this->_description;
}

/**
 * The overloaded operator for equality comparison.
 * @param that The other Placement to compare this one to
 * @return Returns true if they have the same name, credits and description.
 */
const bool Placement::operator==(Placement &that) const
{
    return (this->_name.compare(that._name) == 0) && this->_credits == that._credits && this->_description == that._description;
}


/**
 * The toStr helper function for Placements.
 * This is identical in functionality to how Module's works, which it should be.
 */
const string Placement::toStr(unsigned int padding) const
{
    string out = "";
    for(int i = 0; i < padding; i++)
    {
        out += "\t";
    }
    out += "[Placement: name=\""+this->_name+"\" students="+to_string(this->_students)+" credits="+to_string(this->_credits)+" description=\""+this->_description+"\"]";
    return out;
}