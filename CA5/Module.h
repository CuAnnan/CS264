#ifndef MODULEHEADER_H
#define MODULEHEADER_H

#include <string>

using namespace std;

/**
 * Class definition for Module
 * This method does nothing more interesting than having getters and setters.
 * It's essentially a POCO, Plain Old C++ Object
 * Normally when I comment code it's to explain to the other person what a method does
 * Here I am demonstrating that I understand why I am including it.
 * I am, as an informed design choice, not including a destructor for this class.
 * It doesn't require one as, even though strings are not technically primitives, C++ handles the resource allocation internally. 
 * All work, commenting included, is my own. I detest ChatGPT, it gets in my way every time I try to use it (as we were advised to do for the Team Project)
 */
class Module
{
    public:
        /**
         * Default constructor, zero everything out
         */
        Module() : _students(0), _credits(2), _name("") {}
        /**
         * Copy constructor, prevents modification by using const
         * which seems the thing to do.
         * @param other The rhs instance to copy
         */
        Module(const Module& other):_students(other._students), _credits(other._credits), _name(other._name){};
        /**
         * Specify everything
         * @param name      The name of the module
         * @param students  The number of students in the module
         * @param credits   The number of credits the module is worth
         */
        Module(const string name, const int students, const int credits):_name(name), _students(students), _credits(credits){};

        /**
         * Equality operator overload.
         * We do this because we don't want to just check if it points to the same object instance, but if the values of the object instance are the same.
         * As this is a naive POJO, we can't guarantee that two copies won't be made (eg if it comes out of a database as part of multiple queries, multiple instances can be spun up)
         */
        const bool operator==(const Module& that) const;

        /**
         * getter and setter for name
         */
        string getName() const;
        void setName(string name);

        /**
         * getter and setter for students
         */
        unsigned int getStudents() const;
        void setStudents(const unsigned int students);

        /**
         * getter and setter for credits
         */
        unsigned int getCredits() const;
        void setCredits(const unsigned int credits);

        /**
         * While not, strictly, called for by the spec in the assignment; this allows for easier debugging and stringing together of multiple modules into a single toString method later
         */
        virtual const string toString(const unsigned int padding=0) const;


    /*
     * Since we have to access these properties for the child class, exposing them to the implementation makes life easier.
     * The .toString and == operator overload are much nastier with .getName() everywhere instead of just ._name and ->_name
     */
    protected:
        /**
         * The name of the module.
         * Defaults to a blank string
         */
        string _name;
        /**
         * The number of students it has.
         * I'm somewhat surprised we don't need to have a vector of students and to add students to it, and derive count or keep track of it somehow.
         * Defaults to 0
         */
        unsigned int _students;
        /**
         * The amount of credits the module is worth
         * Defaults to 2
         */
        unsigned int _credits;
};

#endif