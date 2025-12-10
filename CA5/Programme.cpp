#include "Programme.h"
#include "Module.h"
#include <string>
#include <iostream>

using namespace std;

/**
 * The only constructor for the Programme. It requires you set all required properties.
 * @param name          The name of the module
 * @param year          The year that the module is for.
 * @param maxModules    This is the maximum number of modules the module can have
 */
Programme::Programme(string name, int year, int maxModules)
{
    this->_name = name;
    this->_year = year;
    this->_maxModules = maxModules;
    this->_modules = new Module*[maxModules];
    this->_moduleCount = 0;
}

/**
 * Destructor, frees up the memory taken by modules array, but not the memory for each module itself.
 * This is a part of the specification which uses has-a (blank diamond) not owns-a (solid diamond) notation.
 * We have to do this as a module could conceivably belong to more than one Programme.
 */
Programme::~Programme()
{
    if(this->_moduleCount == 0) return;
    delete[] this->_modules;
}


/**
 * Add a module to the Programme.
 * @param m The module to add.
 */
void Programme::addModule(Module* m)
{
    if(this->_moduleCount >= this->_maxModules) return;
    // don't add a duplicate module
    for(int i = 0; i < this->_moduleCount; i++)
    {
        if(*this->_modules[i] == m) return;
    }

    this->_modules[this->_moduleCount++] = m;
}

/**
 * Get the name of the module
 */
const string Programme::getName() const
{
    return this->_name;
}

/**
 * Setter for the name of the module
 * @param name The new name to give the module
 */
void Programme::setName(const string name)
{
    this->_name = name;
}

/**
 * Getter for the year of the module
 * @return The year the programme is available to
 */
const unsigned int Programme::getYear() const
{
    return this->_year;
}

/**
 * Setter for the year of the module.
 * @param year The Year the program is available to.
 */
void Programme::setYear(const unsigned int year)
{
    this->_year = year;
}

/**
 * A method to return a formatted string representation of the object. Each module or placement is indented using its own toStr
 * @param padding   The (optional) padding to prefix the toString with
 * @return The string represenation of the object.
 */
const string Programme::toStr(const unsigned int padding) const
{
    string prefix = "";
    for(int i = 0; i < padding; i++)
    {
        prefix += "\t";
    }
    string out = prefix+"[Programme: name=\""+this->_name+"\" year="+to_string(this->_year)+"";

    for(int i = 0; i < this->_moduleCount; i++)
    {
        out += "\n"+(this->_modules[i])->toStr(padding + 1);
    }
    
    return out+"\n"+prefix+"]";
}