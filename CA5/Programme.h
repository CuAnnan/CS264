#ifndef PROGRAMMEHEADER_H
#define PROGRAMMEHEADER_H

#include <string>
#include "Module.h";

using namespace std;

// This class is more or less identical to the Zoo class from lectures.
// While I didn't copy and paste it. I definitely looked at how that class worked and that informed everything I did here.


/**
 * Definition of the Programme class
 */
class Programme
{
    public:
        /**
         * I am explicitly disallowing the default constructor.
         * It's not unsafe to do. It's explicit. And it will remind me when I come to write the implementation that you can't
         */
        Programme() = delete;

        /**
         * I'm only allowing a full constructor. All of this data is philosophically required
         */
        Programme(const string name, const int year, const int maxModules = 5);

        /**
         * Copy constructor
         */
        Programme(const Programme& other);

        /**
         * Because we can't use smart pointers, I have to use a destructor.
         */
        ~Programme();
        

        // I actually think this should be a bool which returns a value based on whether or not the module was successfully added
        // but the spec is specific that it has to be a void.
        // I think returning a true or false gives better control flow.
        void addModule(Module* m);
        
        /*
         * Setters and getters
         */

        const string getName() const;
        void setName(const string name);

        const unsigned int getYear() const;
        void setYear(const unsigned int);

        // toString method
        const string toStr() const;


    private:
        string _name;
        unsigned int _year;
        unsigned int _maxModules;
        unsigned int _moduleCount;
        Module** _modules;
};


#endif