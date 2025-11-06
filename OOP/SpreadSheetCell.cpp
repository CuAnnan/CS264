#include "SpreadSheetCell.h"
#include <iostream>
using namespace std;

/*
This is the implmentation file for the SpreadsheetCell class methods.
 */

SpreadSheetCell::SpreadSheetCell(void)
{
    cout << "Constructor called" << endl;
}

SpreadSheetCell::SpreadSheetCell(double initialValue)
{
    cout << "Constructor with initial value called" << endl;
    value_ = initialValue;
}

// copy constructor implementation                          // this is an initialiser list
                                                            // these values get initialised before
                                                            // the constructor body is executed
                                                            // which is important for const members
SpreadSheetCell::SpreadSheetCell(const SpreadSheetCell& src):value_(src.value_)
{
    cout << "Copy constructor called" << endl;
    value_ = src.value_;
}

SpreadSheetCell::~SpreadSheetCell()
{
    cout << "Destructor called" << endl;
}

SpreadSheetCell& SpreadSheetCell::operator=(const SpreadSheetCell& rhs)
{
    cout << "Assignment operator called" << endl;
    // self-assignment guard
    if (this == &rhs)
        return *this;

    // do the copy
    value_ = rhs.value_;

    // return the existing object so we can chain this operator
    return *this;
}

void SpreadSheetCell::setValue(double inValue)
{
    // this, in this case, is a pointer to the memory address for the current instance of the class
    // the -> operator dereferences the pointer and accesses the member of the class
    this->value_ = inValue;
    (*this); // this dereferences the pointer to the current instance of the class
    (*this).value_ = inValue; // this is equivalent to the above assignment
}

const SpreadSheetCell SpreadSheetCell::add(const SpreadSheetCell &cell) const
{
    // const SpreadSheetCell newCell;
    // newCell.setValue(cell.getValue());
    // return newCell;
    // check notes.
    return nullptr;
}


double SpreadSheetCell::getValue()
{
    return value_;
}

int main()
{
    SpreadSheetCell cell(5.0);
    cout << "Cell value: " << cell.getValue() << endl;
    cell.setValue(10.0);
    cout << "Updated cell value: " << cell.getValue() << endl;

    SpreadSheetCell* pCell = new SpreadSheetCell(15.0);
    cout << "Pointer cell value: " << pCell->getValue() << endl;
    pCell->setValue(20.0);
    cout << "Updated pointer cell value: " << pCell->getValue() << endl;
    delete pCell; // Clean up dynamically allocated memory

    return 0;
}